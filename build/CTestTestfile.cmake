# CMake generated Testfile for 
# Source directory: /home/elkhaldy/ensimag-malloc
# Build directory: /home/elkhaldy/ensimag-malloc/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(AllTestsAllocator "alloctest")
set_tests_properties(AllTestsAllocator PROPERTIES  _BACKTRACE_TRIPLES "/home/elkhaldy/ensimag-malloc/CMakeLists.txt;77;add_test;/home/elkhaldy/ensimag-malloc/CMakeLists.txt;0;")
subdirs("gtest")
