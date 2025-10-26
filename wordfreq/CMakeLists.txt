add_executable(wordseq)
target_sources(wordseq PRIVATE seq.cpp)
target_link_libraries(wordseq PRIVATE TBB::tbb)

add_executable(wordpar)
target_sources(wordpar PRIVATE par.cpp)
target_link_libraries(wordpar PRIVATE TBB::tbb)