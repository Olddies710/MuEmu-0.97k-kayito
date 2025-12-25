cmake_minimum_required(VERSION 3.16)

project(MuEmuServers LANGUAGES CXX)

option(USE_MYSQL "Use MySQL connector" OFF)
set(MYSQL_CONNECTOR_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/mysql-connector-8.0.33/Release" CACHE PATH "MySQL Connector/C++ root")

find_package(Threads REQUIRED)

function(add_muserver_target target_name target_dir)
  file(GLOB sources CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/${target_dir}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/${target_dir}/*.h"
  )

  if(WIN32)
    file(GLOB rc_files CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${target_dir}/*.rc")
    list(APPEND sources ${rc_files})
  endif()

  add_executable(${target_name} ${sources})

  target_include_directories(${target_name} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/${target_dir}"
    "${CMAKE_CURRENT_SOURCE_DIR}/Platform"
  )

  if(USE_MYSQL)
    target_compile_definitions(${target_name} PRIVATE MYSQL)
    if(EXISTS "${MYSQL_CONNECTOR_ROOT}/include")
      target_include_directories(${target_name} PRIVATE "${MYSQL_CONNECTOR_ROOT}/include")
    endif()
  endif()

  if(WIN32)
    target_link_libraries(${target_name} PRIVATE ws2_32 dbghelp)
  else()
    target_link_libraries(${target_name} PRIVATE Threads::Threads)
  endif()
endfunction()

if(BUILD_GAMESERVER)
  add_muserver_target(GameServer GameServer)
endif()

if(BUILD_CONNECTSERVER)
  add_muserver_target(ConnectServer ConnectServer)
endif()

if(BUILD_JOINSERVER)
  add_muserver_target(JoinServer JoinServer)
endif()

if(BUILD_DATASERVER)
  add_muserver_target(DataServer DataServer)
endif()
