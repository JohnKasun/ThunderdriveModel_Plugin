add_library(SimpleFilter OBJECT 
    SimpleFilter.cpp
    SimpleFilterIf.cpp
)

target_include_directories(SimpleFilter 
    PUBLIC 
        ./include
        ../include
)