INCLUDE_DIRECTORIES(
  ${PARADEVS_BINARY_DIR}/src
  ${PARADEVS_SOURCE_DIR}/src
  ${PARADEVS_SOURCE_DIR}/src/tests/corsen/lib
  ${Boost_INCLUDE_DIRS}
  ${GLIBMM_INCLUDE_DIRS}
  ${LIBXML_INCLUDE_DIRS})

LINK_DIRECTORIES(
  ${GLIBMM_LIBRARY_DIRS}
  ${LIBXML_LIBRARY_DIR})

SET(CORSEN_HPP Constantes.h Coordinates.h ElevationFileStream.h Functions.h
  LayersFileStream.h OutletFileStream.h Parameters.h SoilFileStream.h
  ContextData.h Corsen.hpp Exception.h Graph.hpp LayersTextFileStream.h Outlet.h
  Singleton.h Vertex.h ContextFileReader.h DrainFileStream.h FileStream.h
  Layer.h Node.h ParametersFileStream.h SlopeFileStream.h XmlReader.h)

SET(CORSEN_CPP Corsen.cpp Functions.cpp Graph.cpp)

ADD_LIBRARY(corsen SHARED ${CORSEN_HPP};${CORSEN_CPP})

TARGET_LINK_LIBRARIES(corsen
  ${Boost_LIBRARIES}
  ${GLIBMM_LIBRARIES}
  ${LIBXML_LIBRARIES}
  ${GTHREAD_LIBRARIES})