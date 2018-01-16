project (polymorphic_c)

add_executable (demo_cpp cpp/main.cpp)
add_executable (demo_c c/main.c)
add_executable (demo_pc pc/main.c pc/polymorphic_c.c)
