add_executable(Std Main.cpp)
target_link_libraries(Std exceptxx::exceptxx)
set_target_properties(Std PROPERTIES FOLDER Samples)