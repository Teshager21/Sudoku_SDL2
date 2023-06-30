add_test( TestName.SubTest_1 /home/teshager/Dev/cpp/Sudoku_SDL2/test/tests [==[--gtest_filter=TestName.SubTest_1]==] --gtest_also_run_disabled_tests)
set_tests_properties( TestName.SubTest_1 PROPERTIES WORKING_DIRECTORY /home/teshager/Dev/cpp/Sudoku_SDL2/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set( tests_TESTS TestName.SubTest_1)
