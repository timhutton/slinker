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
