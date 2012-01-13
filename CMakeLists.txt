cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/bootstrap.cmake")



####################################
# Settings
####################################
set (CMAKE_SKIP_ASSEMBLY_SOURCE_RULES ON)
set (CMAKE_SKIP_PREPROCESSED_SOURCE_RULES ON)
set (CMAKE_VERBOSE_MAKEFILE ON) # print full commands during compilation
set (CMAKE_RULE_MESSAGES OFF CACHE BOOL "")


####################################
# Other parameters
####################################


project ( nao_spy )
file (GLOB NAO_SPY_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
qi_create_lib(nao_spy ${NAO_SPY_SRC})


qi_use_lib(nao_spy ALCOMMON ALMEMORYFASTACCESS)
