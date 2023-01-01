function(short_module module_name)
add_executable(
    "${module_name}"
    "${module_name}.c"
    main.c
)

target_include_directories(
    "${module_name}"
    PRIVATE include
)
endfunction()