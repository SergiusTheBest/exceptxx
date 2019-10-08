add_executable(Assert Main.cpp)
target_link_libraries(Assert exceptxx::exceptxx)
set_target_properties(Assert PROPERTIES FOLDER Samples)