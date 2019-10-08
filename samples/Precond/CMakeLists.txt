add_executable(Precond Main.cpp)
target_link_libraries(Precond exceptxx::exceptxx)
set_target_properties(Precond PROPERTIES FOLDER Samples)