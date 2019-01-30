include(GNUInstallDirs)

# Check Qt Packages
find_package(
    Qt5

    COMPONENTS
        Core
        Network
        Xml

    REQUIRED
)
###

# Set Custom Variables
set(HEADERS_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}/lib${PROJECT_NAME})
###

# Add Source Files
set(
    CPP_SOURCES
  
    CardDAV.cpp
    CalDAV.cpp

    dto/Contact.cpp
    dto/CardDAVResponseItem.cpp
#    dto/CalDAVItem.cpp

    utils/NetworkHelper.cpp
    utils/CardDAVReply.cpp
    utils/XMLHelper.cpp
    utils/Environment.cpp
)
###

# Create and Link Executable
add_library(
    ${PROJECT_NAME}
    SHARED

    ${CPP_SOURCES}
)
target_link_libraries(
    ${PROJECT_NAME}

    Qt5::Core
    Qt5::Network
    Qt5::Xml
)
###

# Set Flags for Library
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES
  PUBLIC_HEADER "CardDAV.hpp;CalDAV.hpp;dto/CardDAVItem.hpp;dto/CalDAVItem.hpp;utils/WebDAVReply.hpp"
)
###

# Set Installables
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${HEADERS_INSTALL_DIR}
)
###
