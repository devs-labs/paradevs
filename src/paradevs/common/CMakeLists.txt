INCLUDE_DIRECTORIES(
  ${PARADEVS_BINARY_DIR}/src
  ${PARADEVS_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS}
  ${GLIBMM_INCLUDE_DIRS}
  ${LIBXML_INCLUDE_DIRS})

LINK_DIRECTORIES(
  ${GLIBMM_LIBRARY_DIRS}
  ${LIBXML_LIBRARY_DIR})

SET(COMMON_HPP Bag.hpp Coordinator.hpp ExternalEvent.hpp InternalEvent.hpp
  Links.hpp Model.hpp Node.hpp Parameters.hpp RootCoordinator.hpp Scheduler.hpp
  Simulator.hpp Value.hpp)

INSTALL(FILES ${COMMON_HPP} DESTINATION ${PARADEVS_INCLUDE_DIRS}/common)

ADD_SUBDIRECTORY(scheduler)
ADD_SUBDIRECTORY(time)
ADD_SUBDIRECTORY(utils)