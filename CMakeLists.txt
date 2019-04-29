cmake_minimum_required(VERSION 3.13)
project(HydroLib2)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_FLAGS_DEBUG "-E")

#add_executable(Test test.cpp  lib/Script.cpp lib/Script.h lib/Operation.cpp lib/Operation.h lib/OpStack.cpp lib/OpStack.h lib/ScriptSource.cpp lib/ScriptSource.h lib/hydro_types.h lib/TextScriptSource.cpp lib/TextScriptSource.h lib/Value.cpp lib/Value.h lib/Log.cpp lib/Log.h lib/Context.cpp lib/HydroObject.cpp lib/HydroObject.h lib/Scheduler.cpp lib/Scheduler.h lib/Time.cpp lib/Time.h lib/HydroObject.h lib/HydroObject.cpp)
#add_executable(HydroLib2 main.cpp lib/Script.cpp lib/Script.h lib/Operation.cpp lib/Operation.h lib/OpStack.cpp lib/OpStack.h lib/ScriptSource.cpp lib/ScriptSource.h lib/hydro_types.h lib/TextScriptSource.cpp lib/TextScriptSource.h lib/Value.cpp lib/Value.h lib/Log.cpp lib/Log.h lib/BinQueue.cpp lib/BinQueue.h lib/HydroObject.h lib/HydroObject.cpp)
add_executable(tests tests/testScript.cpp lib/Script.cpp lib/Script.h lib/Operation.cpp lib/Operation.h  lib/HydroObject.cpp lib/OpStack.cpp lib/OpStack.h lib/ScriptSource.cpp lib/ScriptSource.h lib/hydro_types.h lib/TextScriptSource.cpp lib/TextScriptSource.h lib/Value.cpp lib/Value.h lib/Log.cpp lib/Log.h lib/BinQueue.cpp lib/BinQueue.h lib/Context.cpp lib/HydroObject.h lib/Scheduler.cpp lib/Scheduler.h lib/Clock.cpp lib/Clock.h lib/HydroObject.h lib/HydroObject.cpp lib/ObjPeriodic.cpp lib/ObjPeriodic.h)