
Macro(GENERATE_EICROOT_LIBRARY LIBNAME LINKDEF_FILE)

  INCLUDE_DIRECTORIES( ${INCLUDE_DIRECTORIES} )

  # This is dumb of course; sorry, guys;
  CHANGE_FILE_EXTENSION(*.cxx *.h CXXHEADERS "${CXXSOURCES}")
  SET( HEADERS "${CXXHEADERS}" "${EXTRA_HEADERS}")
  SET( SOURCES "${CXXSOURCES}" "${EXTRA_SOURCES}")

  ROOT_GENERATE_DICTIONARY(G__${LIBNAME} ${HEADERS} LINKDEF ${LINKDEF_FILE})
  SET( SOURCES ${SOURCES} G__${LIBNAME}.cxx )

  ADD_LIBRARY( ${LIBNAME} SHARED ${SOURCES} )

  TARGET_LINK_LIBRARIES( ${LIBNAME} ${ROOT_LIBRARIES} ${DEPENDENCIES})

  INSTALL(TARGETS ${LIBNAME} DESTINATION lib)

  INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBNAME}.rootmap ${CMAKE_CURRENT_BINARY_DIR}/lib${LIBNAME}_rdict.pcm DESTINATION lib)

EndMacro(GENERATE_EICROOT_LIBRARY)
