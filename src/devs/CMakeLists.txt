INCLUDE_DIRECTORIES(
  ${PARADEVS_BINARY_DIR}/src
  ${PARADEVS_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS}
  ${GLIBMM_INCLUDE_DIRS}
  ${LIBXML_INCLUDE_DIRS})

LINK_DIRECTORIES(
  ${GLIBMM_LIBRARY_DIRS}
  ${LIBXML_LIBRARY_DIR})

SET(DEVS_CPP Coordinator.cpp Dynamics.cpp EventTable.cpp
  InternalEvent.cpp Links.cpp Message.cpp Model.cpp Node.cpp RootCoordinator.cpp
  Simulator.cpp)

SET(DEVS_HPP Builder.hpp Coordinator.hpp Dynamics.hpp EventTable.hpp
  InternalEvent.hpp Links.hpp Message.hpp Model.hpp Node.hpp RootCoordinator.hpp
  Simulator.hpp Time.hpp)

ADD_LIBRARY(pdevs SHARED ${DEVS_CPP};${DEVS_HPP})

SET_TARGET_PROPERTIES(pdevs PROPERTIES ${PARADEVS_LIBRARY_PROPERTIES})
SET_TARGET_PROPERTIES(pdevs PROPERTIES OUTPUT_NAME
  "paradevs-pdevs-${PARADEVS_VERSION_SHORT}")

TARGET_LINK_LIBRARIES(pdevs
  ${GLIBMM_LIBRARIES}
  ${LIBXML_LIBRARIES}
  ${GTHREAD_LIBRARIES})

INSTALL(TARGETS pdevs
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

INSTALL(FILES ${DEVS_HPP} DESTINATION ${PARADEVS_INCLUDE_DIRS}/devs)