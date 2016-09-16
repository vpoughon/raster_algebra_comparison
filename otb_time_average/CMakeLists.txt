project(time_average)

cmake_minimum_required(VERSION 2.6)

FIND_PACKAGE(OTB)
IF(OTB_FOUND)
  INCLUDE(${OTB_USE_FILE})
ELSE(OTB_FOUND)
  MESSAGE(FATAL_ERROR
      "Cannot build OTB project without OTB.  Please set OTB_DIR.")
ENDIF(OTB_FOUND)

otb_create_application(
  NAME TimeAverage
  SOURCES appTimeAverage.cxx
  LINK_LIBRARIES ${${otb-module}_LIBRARIES})

otb_create_application(
  NAME FunctorTimeAverage
  SOURCES appFunctorTimeAverage.cxx
  LINK_LIBRARIES ${${otb-module}_LIBRARIES})
