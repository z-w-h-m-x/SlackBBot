cmake_minimum_required(VERSION 3.6)

project(SlackBot)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)


include_directories(
    include/
    thirdparty/
)

aux_source_directory(src/Plugin SlackBotPLUGIN_FILES)
aux_source_directory(src SlackBot_SRC)
aux_source_directory(src/Processor SlackBot_Processor_SRC)
aux_source_directory(src/Plugin SlackBot_Plugin_SRC)

aux_source_directory(plugins/dev-test Plugin_DevTest_FILES)

find_package(SDL2 REQUIRED)
# find_package(SDL2_net REQUIRED)

add_library(SlackBot_Plugin SHARED ${SlackBotPLUGIN_FILES})
add_library(Plugin_DevTest SHARED ${Plugin_DevTest_FILES})

set_target_properties(Plugin_DevTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./bin/plugin/)

add_executable(slackbot
    ${SlackBot_SRC}
    ${SlackBot_Processor_SRC}
    ${SlackBot_Plugin_SRC}
    src/Processor/QOE/qoeArg.cpp
)

target_link_libraries(slackbot
    SDL2::SDL2
    # SDL2_net::SDL2_net
    SlackBot_Plugin
    # requirements of httplib.h when dev with mingw 
    $<$<BOOL:${MINGW}>:ws2_32>
    $<$<BOOL:${MINGW}>:crypt32>
    $<$<BOOL:${MINGW}>:cryptui>
)

file(COPY "include/Plugin/Plugin_Base.h" DESTINATION "./bin/include/${PROJECT_NAME}/Plugin_Base.h")
file(COPY "doc/" DESTINATION "./bin/PluginDevelopmentDocumentation/")