SET(SOURCES_PUBLIC 
	"dll.h"
	"serializer.h"
)

SET(SOURCES_PRIVATE 
	"private/dll.cpp"
	"private/serializer.cpp"
)

SET(SOURCES_TESTS
	"tests/serializer_tests.cpp"
	"tests/test_entry.cpp"
)

INCLUDE_DIRECTORIES(
	"${ENGINE_3RDPARTY_PATH}/jsoncpp/include"
)

ADD_ENGINE_LIBRARY(serialization ${SOURCES_PUBLIC} ${SOURCES_PRIVATE} ${SOURCES_TESTS})
TARGET_LINK_LIBRARIES(serialization core jsoncpp_lib_static)
