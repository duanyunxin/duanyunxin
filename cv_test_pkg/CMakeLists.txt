cmake_minimum_required(VERSION 3.8)
project(cv_test_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(extract_boundary
                src/extract_boundary.cpp)
target_link_libraries(extract_boundary ${OpenCV_LIBS})

add_executable(calc_distance
                src/calc_distance.cpp)
target_link_libraries(calc_distance ${OpenCV_LIBS})

install(TARGETS
  extract_boundary
  calc_distance

  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
