# Master Tuner

Retunes any track from a source reference (usually 440 Hz) to any target reference (432, 444, 415 Baroque, 528, or custom). Load audio, hear it, download the retuned WAV.

## Controls

| Control | What it does |
|---|---|
| **Source ref (Hz)** | The tuning the track is currently in (default 440) |
| **Target ref (Hz)** | The tuning to convert to (default 432) |
| **Presets** | 432, 440, 444, 415 (Baroque), 528, 396 |
| **Ratio / Cents / Semitones** | Live readout of the exact shift (440→432 = ×0.982, −31.8¢) |
| **Varispeed** | Tape-style — pitch + tempo shift together. Cleanest, zero artifacts. |
| **Keep tempo** | Pitch-only (overlap-add algorithm). Holds tempo; slightly less clean. |
| **Mono** | Sum to mono |
| **Play Original / Retuned / Stop** | A/B monitoring |
| **Download retuned WAV** | Renders and saves the converted file |

## The math
- Ratio = target ÷ source
- Cents = 1200 · log₂(ratio)
- 440 → 432 = −31.77 cents

## Build ladder
- [x] 📋 Spec
- [x] 🔊 Browser prototype — `master-tuner.html` (working)
- [ ] 🎛️ Max for Live
- [ ] 💿 VST3/AU

## Honest notes
- **Varispeed** engine is exact and artifact-free (verified math).
- **Keep-tempo** (OLA) engine is real but was not audio-tested at build time — treat as beta; varispeed is the reliable fallback.
- For artifact-free, tempo-preserving retuning *inside Ableton*, use the **Shifter** device on the Master track at the cents value the tool shows.
