cmake_minimum_required(VERSION 3.8)
project(algo_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)

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
add_executable(spline_curve
                src/spline_curve.cpp)
add_executable(gradient_descent
                src/gradient_descent.cpp)
add_executable(wrap_to_pi
                src/wrap_to_pi.cpp)
add_executable(mutex_test
                src/mutex_test.cpp)
add_executable(mahalanobis_dis
                src/mahalanobis_dis.cpp)
add_executable(calc_distance
                src/calc_distance.cpp)
add_executable(cosine_similarity
                src/cosine_similarity.cpp)

install(TARGETS
  least_squared
  lof
  sliding_window_filter
  nonlinear_least_squared
  finite_difference_jocobian
  gauss_newton_method
  spline_curve
  gradient_descent
  wrap_to_pi
  mutex_test
  mahalanobis_dis
  calc_distance
  cosine_similarity

  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
