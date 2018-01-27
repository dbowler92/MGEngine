//EngineConfig.h
//Created 15/04/17
//Created By Daniel Bowler
//
//Used to set the state of the game engine

#pragma once

//
//TODO: Change these...
// 
//Folder for debug dumps
#define DEBUG_DUMPS_FOLDER "Dumps/"

//Application assets folders 
#define ASSETS_FOLDER "../Assets/"
#define SHADER_ASSETS_FOLDER ASSETS_FOLDER"Shaders/"
#define SHADER_COMPILED_ASSETS_FOLDER SHADER_ASSETS_FOLDER"Compiled/"
#define TEXTURE_ASSETS_FOLDER ASSETS_FOLDER"Textures/"

//Engine assets folder
#define ENGINE_ASSETS_FILDER ASSETS_FOLDER"/EngineAssets/"
#define ENGINE_SHADER_ASSETS_FOLDER ENGINE_ASSETS_FILDER"Shaders/"
#define ENGINE_SHADER_COMPILED_ASSETS_FOLDER ENGINE_SHADER_ASSETS_FOLDER"/Compiled/"
#define ENGINE_TEXTURE_ASSETS_FOLDER ENGINE_ASSETS_FILDER"/Textures/"

//Should stop executing program on warning or error messages?
#define ENGINE_CONFIG_STOP_EXECUTION_ON_ERROR_MSG 1
#define ENGINE_CONFIG_STOP_EXECUTION_ON_WARNING_MSG 0
