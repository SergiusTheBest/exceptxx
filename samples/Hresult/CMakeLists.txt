add_executable(Hresult Main.cpp)
target_link_libraries(Hresult exceptxx::exceptxx)
set_target_properties(Hresult PROPERTIES FOLDER Samples)