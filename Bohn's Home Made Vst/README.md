# Bohn's Home Made Vst

Bohn's personal plugin workspace and **update system**. Everything here lives in git, so it persists between chat sessions — nothing is lost when a session ends.

## How the update system works

1. **Each plugin is its own separate folder** — self-contained, with its own files, spec, and version history.
2. **To change a plugin,** in any chat working on this repo, say what you want:
   - *"update Keystone: add the Grand Gallery preset"*
   - *"update Master Tuner: add a 444 Hz preset"*
3. Claude makes the change, **bumps the version**, logs it in that plugin's `CHANGELOG.md`, and pushes. The update persists.
4. **Start a fresh chat anytime** — the repo remembers every plugin and every version.

## Each plugin folder contains

| File | Purpose |
|---|---|
| `SPEC.md` | What the plugin is, its controls, and the full vision |
| `CHANGELOG.md` | Version history — what changed, when |
| the working files | browser prototype (`.html`) now; Max for Live / JUCE source later |

## Plugin index

| Plugin | What it does | Status |
|---|---|---|
| **Keystone** | Geometric psychoacoustic environment — a reverb that transports sound into simulated ancient chambers (every wonder as a preset) | 🔊 working browser prototype (v0.2.0) |
| **Master Tuner** | Retunes any track from 440 to 432 / any Hz | 🔊 working browser prototype (v0.1.0) |

## Status legend & the honest ladder

Every plugin climbs the same ladder — the folder always says which rung it's on:

1. **📋 Spec** — the vision + controls written down
2. **🔊 Browser prototype** — real working DSP you can hear (Web Audio), but not a plugin
3. **🎛️ Max for Live** — runs natively in Ableton (no compiling)
4. **💿 VST3/AU** — a real installable plugin (built with JUCE)

Nothing here is called a "VST" until it actually reaches rung 4. Honest labels only.
