add_subdirectory(SimpleFilter)
add_subdirectory(ThunderdriveProcessor)

include_directories(include)

target_sources(ThunderdrivePlugin
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp
)

target_link_libraries(ThunderdriveProcessor
    PRIVATE
        SimpleFilter)

target_link_libraries(ThunderdrivePlugin
    PRIVATE
        SimpleFilter
        ThunderdriveProcessor
)

target_link_libraries(TestingTarget
    PRIVATE
        SimpleFilter
        ThunderdriveProcessor
)