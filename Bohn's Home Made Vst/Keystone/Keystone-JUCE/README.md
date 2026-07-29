# Keystone — JUCE plugin (VST3 / AU) source

This is the **real plugin codebase** for Keystone — the source a commercial VST3/AU is built from. It is rung 💿 *source*, not a shipped product (see the honest status below).

## What's here

```
Keystone-JUCE/
├── CMakeLists.txt            # build config (fetches JUCE 8.0.4)
└── Source/
    ├── GeoVerbEngine.h       # the geometry-driven FDN reverb DSP (no JUCE dep)
    ├── PluginProcessor.h/.cpp# JUCE plugin + parameters (APVTS)
    └── PluginEditor.h/.cpp   # GUI: knobs + preset menu
```

## How to build it

You need a C++ toolchain and CMake (≥3.22). JUCE is fetched automatically.

```bash
cd Keystone-JUCE
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Output VST3/AU lands in `build/Keystone_artefacts/…`. `COPY_PLUGIN_AFTER_BUILD` also installs it to your system plugin folder. In Ableton, rescan plugins and load **Keystone**.

- **macOS:** needs Xcode command-line tools. Builds VST3 + AU.
- **Windows:** needs Visual Studio 2022 (build tools). Builds VST3.
- To use a local JUCE instead of fetching: see the commented Option B in `CMakeLists.txt`.

## Honest status — this is source, not a finished product

I wrote this codebase but **could not compile, run, or hear it** from the environment it was authored in. So treat it as a **first-draft engine that needs a build + tuning pass**:

- It may need small fixes to compile cleanly on your toolchain/JUCE version.
- The reverb algorithm (an 8-line FDN with Householder feedback, one-pole damping, and Schroeder diffusion) is a legitimate architecture, but its *sound* has never been auditioned. Real reverb quality comes from tuning delay ratios, diffusion, and modulation **by ear** — that pass hasn't happened.

## The honest road to "commercial grade"

Writing the code is one step. A commercial product also requires (all of which need your hardware, ears, and accounts — I can't do them from here):

- [ ] **Build & debug** on macOS and Windows until it compiles and runs clean
- [ ] **Sound design pass** — tune the DSP by ear until the reverb is genuinely good; add modulation to avoid metallic tails; validate against reference reverbs
- [ ] **Real early reflections** per preset (image-source), and verify each chamber's dimensions against a cited source
- [ ] **QA** — no clicks/denormals/crashes; test many sample rates, buffer sizes, and hosts (Ableton, Logic, FL, Reaper)
- [ ] **CPU optimization** and parameter smoothing (avoid zipper noise on automation)
- [ ] **GUI polish** — a designed interface, not stock rotary knobs
- [ ] **Presets** finalized and bundled; state save/recall tested
- [ ] **pluginval** passing at strictness 10
- [ ] **Code signing / notarization** (Apple), installer packaging
- [ ] **Licensing, branding, docs, support** — the business layer

That checklist is what "commercial grade" actually means. This repo gets you to the top of it with a working codebase; the rest is a build-test-listen loop that lives on your side, and I can help with every code-level step of it via the update system.

## Reference

The browser prototype `../keystone.html` is the **sound/behaviour reference** — the JUCE port aims to match and then exceed it.
