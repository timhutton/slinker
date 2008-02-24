PROJECT (Slinker)

#-----------------------------------------------------------------------------
# include the source files that make up the project itself:

SET(SRCS_Slinker
  src/App.cpp
  src/App.h
  src/MainFrame.cpp
  src/MainFrame.h
  src/SlinkerGrid.cpp
  src/SlinkerGrid.h
  src/RuleDepictionDialog.cpp
  src/RuleDepictionDialog.h
  src/DrawSlinkerGrid.cpp
  src/DrawSlinkerGrid.h
  src/IDs.h
  src/next_combination.h
  src/wxWidgets_standard_headers.h
  )

#-----------------------------------------------------------------------------

# wxWidgets is required to build the project
FIND_PACKAGE(wxWidgets REQUIRED)

INCLUDE( ${wxWidgets_USE_FILE} )
INCLUDE_DIRECTORIES( ${wxWidgets_INCLUDE_DIRS} )
LINK_LIBRARIES( ${wxWidgets_LIBRARIES} )

#-----------------------------------------------------------------------------

# this is where everything is brought together:
ADD_EXECUTABLE(Slinker
  WIN32
  ${SRCS_Slinker} 
  )

#==============================================================================
# CPack commands - for making distributables

INSTALL(TARGETS Slinker
  RUNTIME DESTINATION bin
)

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Slinker")
SET(CPACK_PACKAGE_VENDOR "")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.txt")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt") //
SET(CPACK_PACKAGE_VERSION_MAJOR "0")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Slinker ${Slinker_VERSION_MAJOR}.${Slinker_VERSION_MINOR}")
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  #SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\Slinker.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY}")
  #SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.my-project-home-page.org")
  #SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  SET(CPACK_NSIS_CONTACT "tim.hutton@gmail.com")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ENDIF(WIN32 AND NOT UNIX)
SET(CPACK_PACKAGE_EXECUTABLES "Slinker" "Slinker")
SET(CPACK_SOURCE_IGNORE_FILES "/\\\\.svn/" "~$" ".pcs$" "Doxyfile")

INCLUDE(CPack)