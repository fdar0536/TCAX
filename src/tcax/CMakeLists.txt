add_executable(tcax
        tcc.h
        tcc.c
        syl.h
        syl.c
        tm.h
        tm.cpp
        tcax.h
        tcax.cpp
        map.h
        map.c
        strmap.h
        strmap.c
        string.h
        string.c
        tccmap.h
        tccmap.c
        py.h
        py.cpp
        main.cpp)

#boost
LIST(APPEND tcax_includes ${Boost_INCLUDE_DIRS})
LIST(APPEND tcax_libs ${Boost_LOCALE_LIBRARY})

#python
LIST(APPEND tcax_includes ${Python_INCLUDE_DIRS})
LIST(APPEND tcax_libs ${Python_LIBRARIES})

#freetype2
LIST(APPEND tcax_includes ${FREETYPE_INCLUDE_DIRS})
LIST(APPEND tcax_libs ${FREETYPE_LIBRARIES})

target_link_libraries(tcax ${tcax_libs})
target_include_directories(tcax PUBLIC ${tcax_includes})