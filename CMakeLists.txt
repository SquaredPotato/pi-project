cmake_minimum_required(VERSION 3.0)
project(column)

set (CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -lpthread -lm -lwiringPi -lboost_serialization -lboost_system -lboost_filesystem"   )
set(CMAKE_REQUIRED_FLAGS -std=c++17)


if (WIN32)

	# boost librarys
	set (BOOST_ROOT         "C:/Program Files/boost"                )
	set (BOOST_INCLUDEDIR   "C:/Program Files/boost/include"        )
	set (BOOST_LIBRARYDIR   "C:/Program Files/boost/lib"            )

	#mysql librarys
	set (LIBMYSQLCLIENT_INCLUDE_DIR "C:/Program Files/MySQL/MySQL Connector C++ 1.1.9/include"    )
	set (LIBMYSQLCLIENT_LIBRARIES   "C:/Program Files/MySQL/MySQL Connector C++ 1.1.9/lib"        )

else()

	# boost librarys
	set (BOOST_ROOT		    "/usr/local/boost/1_70_0/"	    	)
	set (BOOST_INCLUDEDIR	"/usr/local/boost/1_70_0/include"	)
	set (BOOST_LIBRARYDIR	"/usr/local/boost/1_70_0/lib"		)

endif ()


find_package(Boost 1.70.0 COMPONENTS REQUIRED)

link_directories(${LIBMYSQLCLIENT_LIBRARIES})

if (NOT Boost_FOUND)
    message (FATAL_ERROR "Fatal error: Boost (version >= 1.70.0) required."     )
else()
    message (STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}"                 )
    message (STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}"                    )
    message (STATUS "Boost_VERSION: ${Boost_VERSION}"                           )

    include_directories (${Boost_INCLUDE_DIRS})
    link_directories (${Boost_LIBRARY_DIRS})
endif()

file (GLOB SOURCE_FILES
        "src/*.hpp"
        "src/*.cpp"
        )

include_directories (~/include ./include)

add_executable (column ${SOURCE_FILES})
