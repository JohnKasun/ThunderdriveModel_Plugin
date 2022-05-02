add_subdirectory(SimpleFilter)
add_subdirectory(DiodeClipper)
add_subdirectory(ThunderdriveProcessor)

include_directories(include)

target_sources(ThunderdrivePlugin
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp
)

target_link_libraries(ThunderdriveProcessor
    PRIVATE
        SimpleFilter
        DiodeClipper)

target_link_libraries(ThunderdrivePlugin
    PRIVATE
        SimpleFilter
        ThunderdriveProcessor
        DiodeClipper
)

target_link_libraries(TestingTarget
    PRIVATE
        SimpleFilter
        ThunderdriveProcessor
        DiodeClipper
)