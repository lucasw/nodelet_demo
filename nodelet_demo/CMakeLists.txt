cmake_minimum_required(VERSION 3.0)
project(nodelet_demo VERSION 0.0.1)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  dynamic_reconfigure
  nodelet
  nodelet_topic_tools
  roscpp
  roslint
  std_msgs
)

# TODO(lucasw) make utility.cpp pass in the future
roslint_cpp(
  src/${PROJECT_NAME}.cpp
  src/${PROJECT_NAME}_node.cpp
  include/${PROJECT_NAME}/${PROJECT_NAME}.h
)
roslint_python()

add_compile_options(-std=c++11)

# generate_dynamic_reconfigure_options(
#   cfg/Delay.cfg
# )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES ${PROJECT_NAME}
  CATKIN_DEPENDS
  dynamic_reconfigure
  nodelet
  roscpp
  std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/nodelet_demo.cpp
  src/utility.cpp)
# add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_gencfg)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

# TODO(lucasw) is this needed?
# if(catkin_EXPORTED_LIBRARIES)
#   add_dependencies(${PROJECT_NAME} ${catkin_EXPORTED_LIBRARIES})
# endif()

add_executable(${PROJECT_NAME}_node src/${PROJECT_NAME}_node.cpp)
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})

install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)

install(FILES
  ${PROJECT_NAME}.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
