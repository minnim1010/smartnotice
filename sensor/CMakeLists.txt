cmake_minimum_required(VERSION 3.7)	# CMake 최소 버전 선택
project(sensor)	# 프로젝트 이름 결정

set(CMAKE_CXX_STANDARD 17)	# 사용할 C++ 언어 버전 선택

set(SOURCE_FILES main.cc ../include/parson.c)	# SOURCE_FILES 변수 설정
set(MOSQUITTO_LIBS
	/usr/lib/arm-linux-gnueabihf/libmosquitto.so)

add_executable(sensor ${SOURCE_FILES})	# 바이너리 파일 이름 선택
target_link_libraries(sensor ${MOSQUITTO_LIBS} ${PYTHON_LIBRARIES})
