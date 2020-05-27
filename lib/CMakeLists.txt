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

###

# Set Installables
install(
    TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)


install(FILES   CardDAV.hpp CalDAV.hpp DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES   dto/CardDAVResponseItem.hpp dto/Contact.hpp DESTINATION ${CMAKE_INSTALL_LIBDIR}/dto)
install(FILES   utils/CardDAVReply.hpp utils/Environment.hpp utils/NetworkHelper.hpp utils/XMLHelper.hpp DESTINATION ${CMAKE_INSTALL_LIBDIR}/utils)

#
