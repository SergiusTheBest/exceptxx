add_executable(Errno Main.cpp)
target_link_libraries(Errno exceptxx::exceptxx)
set_target_properties(Errno PROPERTIES FOLDER Samples)