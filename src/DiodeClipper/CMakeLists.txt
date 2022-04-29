add_library(DiodeClipper OBJECT
    DiodeClipper.cpp
)

target_include_directories(DiodeClipper 
    PUBLIC
        ./include
        ../include
)