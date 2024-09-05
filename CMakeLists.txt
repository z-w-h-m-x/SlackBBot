cmake_minimum_required(VERSION 3.5)

project(QNTBOT)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)


include_directories(
    include/
    thirdparty/
)

aux_source_directory(src/Plugin QNTBOTPLUGIN_FILE)
aux_source_directory(src QNTBOT_SRC)
aux_source_directory(src/Processor QNTBOT_Processor)

find_package(SDL2 REQUIRED)
# find_package(SDL2_net REQUIRED)

add_library(QNTBOT_Plugin SHARED ${QNTBOTPLUGIN_FILE})

add_executable(qntbot
    ${QNTBOT_SRC}
    ${QNTBOT_Processor}
    src/Processor/QOE/qoeArg.cpp
)

target_link_libraries(qntbot
    SDL2::SDL2
    # SDL2_net::SDL2_net
    QNTBOT_Plugin
    $<$<BOOL:${MINGW}>:ws2_32>
    $<$<BOOL:${MINGW}>:crypt32>
    $<$<BOOL:${MINGW}>:cryptui>
)
