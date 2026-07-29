// GeoVerbEngine.h — Keystone's geometry-driven reverb (Geo-Verb)
// Self-contained FDN (feedback delay network) reverb whose delay lengths,
// decay, and diffusion are derived live from room geometry.
//
// STATUS: first-draft DSP. Compiles as plain C++ (no JUCE dependency here).
// Needs a build + listening/tuning pass on real hardware — see README.
#pragma once
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>

class GeoVerbEngine
{
public:
    static constexpr int kLines = 8;   // FDN size
    static constexpr int kDiff  = 4;   // diffusion allpasses

    void prepare (double sr)
    {
        sampleRate = sr;
        const int maxLen = (int) (sr * 0.6) + 4;
        for (int i = 0; i < kLines; ++i)
        {
            line[i].assign ((size_t) maxLen, 0.0f);
            writeIdx[i] = 0;
            dampState[i] = 0.0f;
        }
        for (int a = 0; a < kDiff; ++a)
        {
            const int L = std::max (16, (int) (sr * diffTime[a]));
            dif[a].assign ((size_t) L + 4, 0.0f);
            difWrite[a] = 0;
            difLen[a]   = L;
        }
        update();
    }

    void reset()
    {
        for (int i = 0; i < kLines; ++i) { std::fill (line[i].begin(), line[i].end(), 0.0f); dampState[i] = 0.0f; }
        for (int a = 0; a < kDiff; ++a)   std::fill (dif[a].begin(),  dif[a].end(),  0.0f);
    }

    // dims in metres; round/absorb/proj/mix in 0..1; size is a multiplier
    void setParams (float sizeMul, float W, float H, float D,
                    float round, float absorb, float proj, float mixv)
    {
        size = sizeMul; width = W * sizeMul; height = H * sizeMul; depth = D * sizeMul;
        roundness = round; absorption = absorb; projection = proj; mix = mixv;
        update();
    }

    float getRT60() const { return rt60; }

    void update()
    {
        const float c = 343.0f;
        const float V = std::max (0.1f, width * height * depth);
        const float S = std::max (0.1f, 2.0f * (width*height + width*depth + height*depth));
        const float A = std::max (0.5f, S * absorption);
        rt60 = std::min (8.0f, std::max (0.15f, 0.161f * V / A));

        const float base[kLines] = {
            width, height, depth,
            (width + height) * 0.5f, (height + depth) * 0.5f, (width + depth) * 0.5f,
            (width + height + depth) * 0.333f,
            std::max (width, std::max (height, depth))
        };
        const int maxD = (int) (sampleRate * 0.45);
        for (int i = 0; i < kLines; ++i)
        {
            const float metres = std::max (0.5f, base[i]) * (0.9f + 0.02f * i);
            int d = (int) (metres / c * sampleRate);
            d = std::min (maxD, std::max (8, d));
            delaySamp[i] = d;
            fbGain[i] = std::pow (10.0f, -3.0f * (d / (float) sampleRate) / rt60);
        }
        // damping coefficient: more absorption -> darker tail (lower one-pole coeff)
        dampCoef = std::clamp (0.55f - absorption * 0.6f, 0.05f, 0.55f) + 0.2f;
        diffAmt  = std::clamp (roundness, 0.0f, 0.98f);
        (void) projection; // reserved for future early-reflection source placement
    }

    inline float readLine (int i, int d) const
    {
        const int len = (int) line[i].size();
        int idx = writeIdx[i] - d; if (idx < 0) idx += len;
        return line[i][(size_t) idx];
    }

    void process (float* left, float* right, int numSamples)
    {
        for (int n = 0; n < numSamples; ++n)
        {
            const float inL = left[n];
            const float inR = right != nullptr ? right[n] : inL;
            const float in  = 0.5f * (inL + inR);

            std::array<float, kLines> v {};
            for (int i = 0; i < kLines; ++i) v[i] = readLine (i, delaySamp[i]);

            // Householder feedback mixing
            float sum = 0.0f; for (float x : v) sum += x;
            sum *= 2.0f / kLines;

            for (int i = 0; i < kLines; ++i)
            {
                float mixed = v[i] - sum;
                dampState[i] += dampCoef * (mixed - dampState[i]);   // one-pole LP
                const float fb = dampState[i] * fbGain[i];
                const int len = (int) line[i].size();
                line[i][(size_t) writeIdx[i]] = in + fb;
                writeIdx[i] = (writeIdx[i] + 1) % len;
            }

            // wet = alternating tap sum
            float wet = 0.0f;
            for (int i = 0; i < kLines; ++i) wet += (i & 1 ? -v[i] : v[i]);
            wet *= 1.0f / kLines;

            // Schroeder allpass diffusion (roundness)
            for (int a = 0; a < kDiff; ++a)
            {
                const int len = (int) dif[a].size();
                int rIdx = difWrite[a] - difLen[a]; if (rIdx < 0) rIdx += len;
                const float buf = dif[a][(size_t) rIdx];
                const float x = wet - diffAmt * buf;
                dif[a][(size_t) difWrite[a]] = x;
                difWrite[a] = (difWrite[a] + 1) % len;
                wet = buf + diffAmt * x;
            }

            const float dG = std::cos (mix * 1.57079633f);
            const float wG = std::sin (mix * 1.57079633f);
            left[n] = inL * dG + wet * wG;
            if (right != nullptr) right[n] = inR * dG + wet * wG;
        }
    }

private:
    double sampleRate = 44100.0;

    std::array<std::vector<float>, kLines> line;
    std::array<int, kLines>   writeIdx {};
    std::array<int, kLines>   delaySamp {};
    std::array<float, kLines> fbGain {};
    std::array<float, kLines> dampState {};

    std::array<std::vector<float>, kDiff> dif;
    std::array<int, kDiff> difWrite {};
    std::array<int, kDiff> difLen {};
    const std::array<float, kDiff> diffTime { 0.0047f, 0.0071f, 0.0103f, 0.0143f };

    float size = 1, width = 5, height = 5, depth = 10;
    float roundness = 0.1f, absorption = 0.05f, projection = 0.4f, mix = 0.35f;
    float rt60 = 1.0f, dampCoef = 0.4f, diffAmt = 0.1f;
};
