# Keystone — Changelog

All notable changes to Keystone are logged here. Newest first.

## [0.3.0] — 2026-07-17
- **JUCE VST3/AU codebase added** (`Keystone-JUCE/`) — climbs toward rung 💿.
- Real-time geometry reverb engine (`GeoVerbEngine.h`): 8-line FDN, Householder feedback, one-pole damping from absorption, Schroeder diffusion from roundness, delay lengths derived from room dimensions, RT60 from Sabine.
- JUCE plugin wrapper: APVTS parameters (size, W/H/D, roundness, absorption, projection, mix), state save/recall, stereo/mono bus support.
- Editor with rotary knobs + 7-chamber preset menu + environment label.
- CMake build (fetches JUCE 8.0.4); builds VST3, AU, Standalone.
- **Honest status:** source only — authored without the ability to compile, run, or hear it. Needs a build + debug + by-ear tuning pass. See `Keystone-JUCE/README.md` for the full commercial-readiness checklist.

## [0.2.0] — 2026-07-17
- **First working browser prototype** (`keystone.html`) — climbs to rung 🔊.
- Real geometry-driven convolution reverb: impulse response generated live from room dimensions (image-source early reflections + Sabine-decay diffuse tail).
- Controls wired: Size, Width, Height, Depth ("Breath"), Roundness (sharp↔rounded diffusion), Absorption, Projection placement, Mix, Mono, editable Environment name.
- Live readout: RT60, room volume, lowest room mode; IR waveform view.
- 7 presets with real dimensions: King's Chamber, Queen's Chamber, Grand Gallery, Subterranean Chamber (Giza), Hypogeum Oracle Room, Newgrange Chamber, Hagia Sophia.
- Load a sound (loops) or Test-clap to hear the space; works fully offline.
- Not audio-tested at build time — treat DSP as prototype-grade; report anything that sounds off and it gets fixed in the next update.

## [0.1.0] — 2026-07-17
- **Spec written.** Defined Keystone as a geometric psychoacoustic environment (engine: Geo-Verb).
- Locked the control set: Size, Width/Height/Depth ("Breath"), Roundness, Absorption, Projection placement, Mix, Mono, Environment name.
- Defined the preset system: every wonder / every chamber, starting with the four Great Pyramid chambers (King's, Queen's, Grand Gallery, Subterranean) with real dimensions.
- Status: 📋 Spec. Next rung: 🔊 browser prototype (Web Audio convolution with geometry-driven impulse response).
