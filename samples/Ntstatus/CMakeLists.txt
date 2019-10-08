add_executable(Ntstatus Main.cpp)
target_link_libraries(Ntstatus exceptxx::exceptxx)
set_target_properties(Ntstatus PROPERTIES FOLDER Samples)