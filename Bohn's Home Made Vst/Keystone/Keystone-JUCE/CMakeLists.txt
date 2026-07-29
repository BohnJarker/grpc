cmake_minimum_required(VERSION 3.22)
project(Keystone VERSION 0.3.0)

# --- Get JUCE ---------------------------------------------------------------
# Option A (default): fetch JUCE automatically.
# Option B: comment the block below and set -DJUCE_DIR=/path/to/JUCE, then
#           add_subdirectory(${JUCE_DIR} JUCE) instead.
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        8.0.4        # pin a known-good tag
)
FetchContent_MakeAvailable(JUCE)

# --- Plugin target ----------------------------------------------------------
juce_add_plugin(Keystone
    COMPANY_NAME            "Bohn's Home Made Vst"
    PLUGIN_MANUFACTURER_CODE Bohn
    PLUGIN_CODE              Kyst
    FORMATS                  VST3 AU Standalone
    PRODUCT_NAME            "Keystone"
    IS_SYNTH                 FALSE
    NEEDS_MIDI_INPUT         FALSE
    COPY_PLUGIN_AFTER_BUILD  TRUE)

target_sources(Keystone PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_compile_definitions(Keystone PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(Keystone PRIVATE
    juce::juce_audio_utils
    juce::juce_dsp
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)
