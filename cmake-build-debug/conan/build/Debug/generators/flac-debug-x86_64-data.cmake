########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND flac_COMPONENT_NAMES FLAC::FLAC FLAC::FLAC++)
list(REMOVE_DUPLICATES flac_COMPONENT_NAMES)
if(DEFINED flac_FIND_DEPENDENCY_NAMES)
  list(APPEND flac_FIND_DEPENDENCY_NAMES Ogg)
  list(REMOVE_DUPLICATES flac_FIND_DEPENDENCY_NAMES)
else()
  set(flac_FIND_DEPENDENCY_NAMES Ogg)
endif()
set(Ogg_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(flac_PACKAGE_FOLDER_DEBUG "C:/Users/carlo/.conan2/p/b/flacae5b3ad9ee8ef/p")
set(flac_BUILD_MODULES_PATHS_DEBUG )


set(flac_INCLUDE_DIRS_DEBUG )
set(flac_RES_DIRS_DEBUG )
set(flac_DEFINITIONS_DEBUG "-DFLAC__NO_DLL")
set(flac_SHARED_LINK_FLAGS_DEBUG )
set(flac_EXE_LINK_FLAGS_DEBUG )
set(flac_OBJECTS_DEBUG )
set(flac_COMPILE_DEFINITIONS_DEBUG "FLAC__NO_DLL")
set(flac_COMPILE_OPTIONS_C_DEBUG )
set(flac_COMPILE_OPTIONS_CXX_DEBUG )
set(flac_LIB_DIRS_DEBUG "${flac_PACKAGE_FOLDER_DEBUG}/lib")
set(flac_BIN_DIRS_DEBUG )
set(flac_LIBRARY_TYPE_DEBUG STATIC)
set(flac_IS_HOST_WINDOWS_DEBUG 1)
set(flac_LIBS_DEBUG FLAC++ FLAC)
set(flac_SYSTEM_LIBS_DEBUG )
set(flac_FRAMEWORK_DIRS_DEBUG )
set(flac_FRAMEWORKS_DEBUG )
set(flac_BUILD_DIRS_DEBUG )
set(flac_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(flac_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${flac_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${flac_COMPILE_OPTIONS_C_DEBUG}>")
set(flac_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${flac_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${flac_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${flac_EXE_LINK_FLAGS_DEBUG}>")


set(flac_COMPONENTS_DEBUG FLAC::FLAC FLAC::FLAC++)
########### COMPONENT FLAC::FLAC++ VARIABLES ############################################

set(flac_FLAC_FLAC++_INCLUDE_DIRS_DEBUG )
set(flac_FLAC_FLAC++_LIB_DIRS_DEBUG "${flac_PACKAGE_FOLDER_DEBUG}/lib")
set(flac_FLAC_FLAC++_BIN_DIRS_DEBUG )
set(flac_FLAC_FLAC++_LIBRARY_TYPE_DEBUG STATIC)
set(flac_FLAC_FLAC++_IS_HOST_WINDOWS_DEBUG 1)
set(flac_FLAC_FLAC++_RES_DIRS_DEBUG )
set(flac_FLAC_FLAC++_DEFINITIONS_DEBUG )
set(flac_FLAC_FLAC++_OBJECTS_DEBUG )
set(flac_FLAC_FLAC++_COMPILE_DEFINITIONS_DEBUG )
set(flac_FLAC_FLAC++_COMPILE_OPTIONS_C_DEBUG "")
set(flac_FLAC_FLAC++_COMPILE_OPTIONS_CXX_DEBUG "")
set(flac_FLAC_FLAC++_LIBS_DEBUG FLAC++)
set(flac_FLAC_FLAC++_SYSTEM_LIBS_DEBUG )
set(flac_FLAC_FLAC++_FRAMEWORK_DIRS_DEBUG )
set(flac_FLAC_FLAC++_FRAMEWORKS_DEBUG )
set(flac_FLAC_FLAC++_DEPENDENCIES_DEBUG FLAC::FLAC)
set(flac_FLAC_FLAC++_SHARED_LINK_FLAGS_DEBUG )
set(flac_FLAC_FLAC++_EXE_LINK_FLAGS_DEBUG )
set(flac_FLAC_FLAC++_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(flac_FLAC_FLAC++_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${flac_FLAC_FLAC++_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${flac_FLAC_FLAC++_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${flac_FLAC_FLAC++_EXE_LINK_FLAGS_DEBUG}>
)
set(flac_FLAC_FLAC++_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${flac_FLAC_FLAC++_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${flac_FLAC_FLAC++_COMPILE_OPTIONS_C_DEBUG}>")
########### COMPONENT FLAC::FLAC VARIABLES ############################################

set(flac_FLAC_FLAC_INCLUDE_DIRS_DEBUG )
set(flac_FLAC_FLAC_LIB_DIRS_DEBUG "${flac_PACKAGE_FOLDER_DEBUG}/lib")
set(flac_FLAC_FLAC_BIN_DIRS_DEBUG )
set(flac_FLAC_FLAC_LIBRARY_TYPE_DEBUG STATIC)
set(flac_FLAC_FLAC_IS_HOST_WINDOWS_DEBUG 1)
set(flac_FLAC_FLAC_RES_DIRS_DEBUG )
set(flac_FLAC_FLAC_DEFINITIONS_DEBUG "-DFLAC__NO_DLL")
set(flac_FLAC_FLAC_OBJECTS_DEBUG )
set(flac_FLAC_FLAC_COMPILE_DEFINITIONS_DEBUG "FLAC__NO_DLL")
set(flac_FLAC_FLAC_COMPILE_OPTIONS_C_DEBUG "")
set(flac_FLAC_FLAC_COMPILE_OPTIONS_CXX_DEBUG "")
set(flac_FLAC_FLAC_LIBS_DEBUG FLAC)
set(flac_FLAC_FLAC_SYSTEM_LIBS_DEBUG )
set(flac_FLAC_FLAC_FRAMEWORK_DIRS_DEBUG )
set(flac_FLAC_FLAC_FRAMEWORKS_DEBUG )
set(flac_FLAC_FLAC_DEPENDENCIES_DEBUG Ogg::ogg)
set(flac_FLAC_FLAC_SHARED_LINK_FLAGS_DEBUG )
set(flac_FLAC_FLAC_EXE_LINK_FLAGS_DEBUG )
set(flac_FLAC_FLAC_NO_SONAME_MODE_DEBUG FALSE)

# COMPOUND VARIABLES
set(flac_FLAC_FLAC_LINKER_FLAGS_DEBUG
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${flac_FLAC_FLAC_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${flac_FLAC_FLAC_SHARED_LINK_FLAGS_DEBUG}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${flac_FLAC_FLAC_EXE_LINK_FLAGS_DEBUG}>
)
set(flac_FLAC_FLAC_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${flac_FLAC_FLAC_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${flac_FLAC_FLAC_COMPILE_OPTIONS_C_DEBUG}>")