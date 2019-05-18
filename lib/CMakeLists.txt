cmake_minimum_required(VERSION 3.10)
project(HydroLib2Lib)
SET(CMAKE_COLOR_MAKEFILE OFF)
set(CMAKE_CXX_STANDARD 11)

add_library(hydro2 STATIC Script.cpp Operation.cpp Operation.h  HydroObject.cpp OpStack.cpp OpStack.h hydro_types.h Value.cpp Value.h Log.cpp Log.h BinQueue.cpp BinQueue.h Context.cpp HydroObject.h Scheduler.cpp Scheduler.h Clock.cpp Clock.h HydroObject.h HydroObject.cpp ObjPeriodic.cpp ObjPeriodic.h ObjTime.cpp ObjTime.h ObjDaily.cpp ObjDaily.h SimpleObject.h)
