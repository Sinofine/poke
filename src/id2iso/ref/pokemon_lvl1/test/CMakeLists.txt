set(SOURCE_FILES_ID2ISO_TESTS
    ${ID2ISOX_DIR}/test/test_id2iso.c
)

add_executable(pokemon_id2iso_test ${SOURCE_FILES_ID2ISO_TESTS})
target_link_libraries(pokemon_id2iso_test ${LIB_ID2ISO_${SVARIANT_UPPER}})
target_include_directories(pokemon_id2iso_test PRIVATE ${INC_ID2ISO})

add_test(pokemon_id2iso_test pokemon_id2iso_test)