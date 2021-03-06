set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

#-----------------------------------------------------------------------
# CMAKE OPTIONS
#-----------------------------------------------------------------------

#option (PLUGINS_SWF_enable_zlib_decompression "Enable ZLIB decompression support for the SWF plugin" ON)

#-----------------------------------------------------------------------
# PREPROCESSOR SETTINGS
#-----------------------------------------------------------------------

if(WIN32)
	# add uppercase export definition
	add_definitions (-DVEKTRIX_UNITTESTBASE_EXPORTS)
endif()

#-----------------------------------------------------------------------
# SOURCE FILES & INCLUDE DIRECTORIES & LINK LIBRARIES
#-----------------------------------------------------------------------

# read the source files list
include (vektrix_UnitTests_src_files)

# the required include directories
set (include_dirs
	../tests
	../include
	${CMAKE_SOURCE_DIR}/core/include
	${vtx_plugins_include}
	${ois_include_dirs}
	${ogre_include_dirs}
	${boost_include_dirs}
	${directx_include_dirs}
)

# the required link libraries
set (libraries
	vektrix
	${ois_libraries}
	${ogre_libraries}
	${vtx_plugins_list}
	${directx_libraries}
	OpenGL32.lib
)

#-----------------------------------------------------------------------
# BUILD SETTINGS & COMPILATION
#-----------------------------------------------------------------------

if(WIN32 AND BUILD_USE_STATIC_CRT)
	# link statically against the MSVCRT
	link_static_crt()
endif()

# set the include directories
include_directories (${include_dirs})

# set additional link directories
link_directories (${boost_library_dirs})

# add the plugin library
add_executable (vektrix_UnitTests ${file_root})

# automatically update the source-files list with folders4cmake
auto_rebuild_src_files (vektrix_UnitTests)

#if(VTX_STATIC_LIB)
# remove "lib" prefix
set_target_properties (vektrix_UnitTests PROPERTIES PREFIX "")
#endif()

# link against the required libraries
target_link_libraries (vektrix_UnitTests ${libraries})

# output directory
set_target_properties (vektrix_UnitTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
