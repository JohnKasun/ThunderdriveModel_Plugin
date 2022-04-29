add_library(ThunderdriveProcessor OBJECT 
    ThunderdriveProcessor.cpp
)

target_include_directories(ThunderdriveProcessor 
    PUBLIC 
        ./include
        ../include
)