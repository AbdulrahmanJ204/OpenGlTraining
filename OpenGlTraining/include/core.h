#pragma once
#include<intrin.h> // for __debugbreak();
#include"spdlog/spdlog.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm.hpp>	
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imGui/imgui.h"
#include "imGui/imgui_impl_glfw.h"
#include "imGui/imgui_impl_opengl3.h"

#include "GLErrorManager.h"
#include "myImGuiManager.h"

#include "stb_image\stb_image.h"

// Standard library stuff
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <math.h>
#include <fstream>
#include <sstream>
#include <array>
#include <algorithm>