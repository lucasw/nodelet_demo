cmake_minimum_required(VERSION 2.8.3)
project(nodelet_demo)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  nodelet
  roscpp
  roslint
  std_msgs
)

roslint_cpp()

# generate_dynamic_reconfigure_options(
#   cfg/Delay.cfg
# )

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES nodelet_demo
  CATKIN_DEPENDS nodelet roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(nodelet_demo
  src/nodelet_demo.cpp)
# add_dependencies(nodelet_demo ${PROJECT_NAME}_gencfg)
target_link_libraries(nodelet_demo ${catkin_LIBRARIES})

# TODO(lucasw) is this needed?
# if(catkin_EXPORTED_LIBRARIES)
#   add_dependencies(nodelet_demo ${catkin_EXPORTED_LIBRARIES})
# endif()

add_executable(nodelet_demo_node src/nodelet_demo_node.cpp)
target_link_libraries(nodelet_demo_node ${catkin_LIBRARIES})

install(TARGETS nodelet_demo nodelet_demo_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(FILES
  nodelet_demo.xml
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)
