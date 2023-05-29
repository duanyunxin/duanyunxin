cmake_minimum_required(VERSION 3.8)
project(algo_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(least_squared
                src/least_squared.cpp)
add_executable(lof
                src/lof.cpp)
add_executable(sliding_window_filter
                src/sliding_window_filter.cpp)
add_executable(nonlinear_least_squared
                src/nonlinear_least_squared.cpp)
add_executable(finite_difference_jocobian
                src/finite_difference_jocobian.cpp)
add_executable(gauss_newton_method
                src/gauss_newton_method.cpp)
# add_executable(levenberg_marquardt
#                 src/levenberg_marquardt.cpp)
add_executable(spline_curve
                src/spline_curve.cpp)

install(TARGETS
  least_squared
  lof
  sliding_window_filter
  nonlinear_least_squared
  finite_difference_jocobian
  gauss_newton_method
  # levenberg_marquardt
  spline_curve

  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
