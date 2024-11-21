
function(create_test name)
	add_executable(${name} ${name}.cpp)
	target_link_libraries(${name} PRIVATE fastvec)
	target_compile_options(${name} PRIVATE -fsanitize=address,undefined)
	target_link_options(${name} PRIVATE -fsanitize=address,undefined)
	add_test(
		NAME ${name}
		COMMAND $<TARGET_FILE:${name}>
	)
	set_tests_properties(${name} PROPERTIES CONFIGURATIONS Debug)
endfunction()

create_test(pushpop)
create_test(emplaceback)
