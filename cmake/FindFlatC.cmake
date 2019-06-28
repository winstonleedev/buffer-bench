function(compile_flatbuffers_schema_to_cpp_opt SRC_FBS DST_FBS OPT)
    get_filename_component(SRC_FBS_DIR ${SRC_FBS} PATH)
    string(REGEX REPLACE "\\.fbs$" "_generated.h" GEN_HEADER ${SRC_FBS})
    add_custom_command(
            OUTPUT ${GEN_HEADER}
            COMMAND flatc -c --no-includes --gen-mutable
            --gen-object-api --gen-compare -o "${DST_FBS}"
            --cpp-ptr-type flatbuffers::unique_ptr # Used to test with C++98 STLs
            --reflect-names ${OPT}
            -I "${SRC_FBS_DIR}"
            "${SRC_FBS}"
            COMMENT "Running C++ flatc compiler on ${SRC_FBS}")
endfunction()

function(compile_flatbuffers_schema_to_cpp SRC_FBS DST_FBS)
    compile_flatbuffers_schema_to_cpp_opt(${SRC_FBS} ${DST_FBS} "")
endfunction()