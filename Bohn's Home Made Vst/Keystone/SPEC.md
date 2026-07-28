# Keystone

**A geometric psychoacoustic environment.** Not just a reverb — an *environmental manipulator*. Sound coming into Keystone is transported into a simulated space, and you sculpt that space: its size, its geometry, its walls and shapes, where the sound is placed inside it. Every wonder of the ancient world is a preset — every chamber, every part of every pyramid — built from real dimensions and the mathematics of geometric resonance.

Engine codename: **Geo-Verb**.

## The core idea

The reverb's character is generated *live from room geometry*. Change the geometry → the impulse response is rebuilt → the sound now lives in a different space. This is the whole "sacred geometry of sound" project turned into an instrument: the room-mode equation `f = (c/2)·√[(nx/L)² + (ny/W)² + (nz/H)²]` and image-source early reflections drive a real reverb.

## Controls (the environmental manipulator)

| Control | What it does |
|---|---|
| **Size** | Master scale of the whole environment |
| **Width / Height / Depth ("Breath")** | Independent room dimensions — reshape the box |
| **Roundness** | Morph walls from sharp 90° (specular, modal, flutter) → rounded (diffuse, focusing). Physically: leaving the solvable-math regime |
| **Absorption** | Live stone ↔ damped — sets decay time (RT60 via Sabine) |
| **Projection placement** | Where the sound source sits inside the space (changes the early-reflection pattern you hear) |
| **Add walls / shapes** | Insert surfaces and objects into the room to reshape reflections (roadmap) |
| **Mix** | Dry ↔ wet (how much you're transported) |
| **Mono** | Sum to mono |
| **Environment name** | Name the space you've built — your own custom psychoacoustic environment |

## Preset system — every wonder, every chamber

Presets store full geometry + material + roundness + a name. Built from real published dimensions.

### Great Pyramid of Giza (each chamber separate)
- **King's Chamber** — ~10.47 × 5.23 × 5.81 m, granite (very live). The famous ~110–120 Hz resonance falls straight out of these dimensions.
- **Queen's Chamber** — smaller limestone chamber
- **Grand Gallery** — ~46.7 m long, ~2 m wide, ~8.6 m tall corbelled ceiling. Long, narrow, dramatic.
- **Subterranean Chamber** — rough-cut, deep

### Other wonders (roadmap presets)
- **El Castillo / Kukulkán, Chichén Itzá** — inner temple chamber (note: the *famous* sound is the exterior staircase chirp-echo, a separate special mode to model)
- **Newgrange** passage & corbelled chamber
- **Ħal Saflieni Hypogeum** — the Oracle Room (~110 Hz)
- **Hagia Sophia** — ~10 s reverberation dome
- **Stonehenge** — open-ring reflection (special case)
- **Chavín de Huántar** — the sound-maze galleries

## Build ladder (see workspace README)
- [ ] 📋 Spec ← **you are here**
- [ ] 🔊 Browser prototype (Web Audio convolution, geometry-driven IR, first presets)
- [ ] 🎛️ Max for Live
- [ ] 💿 VST3/AU (JUCE)

## Honest notes
- Presets are physically-grounded *approximations* — real chambers are irregular; published dimensions vary by source. Each preset should cite its dimension source when added.
- "Transported into that environment" = convolution with a geometry-derived impulse response. It's real acoustics, not metaphysics — and that's what makes it sound convincing.
