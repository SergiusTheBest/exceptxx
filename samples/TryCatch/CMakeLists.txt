add_executable(TryCatch Main.cpp)
target_link_libraries(TryCatch exceptxx::exceptxx)
set_target_properties(TryCatch PROPERTIES FOLDER Samples)