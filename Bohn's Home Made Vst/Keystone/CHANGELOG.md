# Keystone — Changelog

All notable changes to Keystone are logged here. Newest first.

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
