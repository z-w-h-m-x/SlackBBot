cmake_minimum_required(VERSION 3.6)

project(SlackBot VERSION 0.0.1.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./bin/)

configure_file (
    ${PROJECT_SOURCE_DIR}/include/ProgramInfo.h.in
    ${PROJECT_SOURCE_DIR}/include/ProgramInfo.h
)

include_directories(
    include/
    thirdparty/
)

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
endif()

aux_source_directory(src/Plugin SlackBotPLUGIN_FILES)
aux_source_directory(src SlackBot_SRC)
aux_source_directory(src/Data SlackBot_Data_SRC)
aux_source_directory(src/Processor SlackBot_Processor_SRC)
aux_source_directory(src/Plugin SlackBot_Plugin_SRC)
aux_source_directory(src/Message SlackBot_Message_SRC)
aux_source_directory(src/Network Network)
aux_source_directory(src/Network/ReportingServer Network_Server)
aux_source_directory(src/Network/Client Network_Client)

aux_source_directory(plugins/dev-test Plugin_DevTest_FILES)

find_package(SDL2 REQUIRED)
# find_package(SDL2_net REQUIRED)

add_library(Plugin_DevTest SHARED ${Plugin_DevTest_FILES} include/Plugin/Plugin/Plugin_Base.cpp)

set_target_properties(Plugin_DevTest PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./bin/plugin/)
set_target_properties(Plugin_DevTest PROPERTIES PREFIX "")

add_executable(slackbot
    ${SlackBot_SRC}
    ${SlackBot_Processor_SRC}
    ${SlackBot_Plugin_SRC}
    ${SlackBot_Data_SRC}
    ${Network}
    ${Network_Server}
    ${Network_Client}
    ${SlackBot_Message_SRC}
    src/Processor/QOE/qoeArg.cpp
)

target_link_libraries(slackbot
    SDL2::SDL2
    # SDL2_net::SDL2_net
    # requirements of httplib.h when dev with mingw 
    $<$<BOOL:${MINGW}>:ws2_32>
    $<$<BOOL:${MINGW}>:crypt32>
    $<$<BOOL:${MINGW}>:cryptui>
)

file(COPY "include/Plugin/Plugin/" DESTINATION "./bin/include/${PROJECT_NAME}/")
file(COPY "doc/" DESTINATION "./bin/PluginDevelopmentDocumentation/")
#file(COPY "NOTICE.txt" DESTINATION "./bin/")

file(COPY "include/Message/MessageDefinition.h" DESTINATION "./bin/include/${PROJECT_NAME}/Message/")