add_executable(squares)
target_sources(squares PRIVATE main.cpp)
target_link_libraries(squares PRIVATE TBB::tbb)