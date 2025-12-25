cmake_minimum_required(VERSION 3.16)

project(MuEmuMuServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_GAMESERVER "Build GameServer" ON)
option(BUILD_CONNECTSERVER "Build ConnectServer" ON)
option(BUILD_JOINSERVER "Build JoinServer" ON)
option(BUILD_DATASERVER "Build DataServer" ON)

add_subdirectory(Source/MuServer)
