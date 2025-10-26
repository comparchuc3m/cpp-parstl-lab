add_executable(sqtransform)
target_sources(sqtransform PRIVATE main.cpp)
target_link_libraries(sqtransform PRIVATE TBB::tbb)