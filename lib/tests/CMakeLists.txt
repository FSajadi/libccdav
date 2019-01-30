find_package(
  Qt5
  REQUIRED

  COMPONENTS
    Test
    Network
    Xml
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(
    CPP_SOURCES

    ../CardDAV.cpp
    ../CalDAV.cpp

    ../dto/Contact.cpp
    ../dto/CardDAVResponseItem.cpp
#    ../dto/CardDAVItem.cpp
#    ../dto/CalDAVItem.cpp

    ../utils/NetworkHelper.cpp
    ../utils/CardDAVReply.cpp
    ../utils/XMLHelper.cpp
    ../utils/Environment.cpp
)

set(
  TEST_SOURCES

  TestCardDAV.cpp
)

add_executable(
  ${PROJECT_NAME}_test

  ${TEST_SOURCES}
  ${CPP_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME}_test

    Qt5::Test
    Qt5::Network
    Qt5::Xml
)

add_test(${PROJECT_NAME}_test ${PROJECT_NAME}_test)
