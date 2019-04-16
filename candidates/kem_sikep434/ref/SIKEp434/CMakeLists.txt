set( LIBRARY_FILES_P434
        api.h api.c )

add_library(sikep434_ref ${LIBRARY_FILES_P434})

add_executable(kat_SIKEp434 PQCtestKAT_kem.c)

target_link_libraries(kat_SIKEp434 sikep434_ref sike_ref_for_test)
