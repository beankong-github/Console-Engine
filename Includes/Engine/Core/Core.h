#pragma once

#if EngineDLL 
# define Engine_API __declspec(dllexport)
#else
# define Engine_API __declspec(dllimport)
#endif