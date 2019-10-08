add_executable(Win32 Main.cpp)
target_link_libraries(Win32 exceptxx::exceptxx)
set_target_properties(Win32 PROPERTIES FOLDER Samples)