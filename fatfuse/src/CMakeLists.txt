
target_sources(fatx
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/image_access.c
		${CMAKE_CURRENT_SOURCE_DIR}/read_bootsec.c
		${CMAKE_CURRENT_SOURCE_DIR}/file_allocation_table.c)
