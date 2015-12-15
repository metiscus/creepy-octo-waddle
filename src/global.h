#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <glad/glad.h>

#include <array>
//#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_map>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <rapidxml/rapidxml.hpp>
#pragma GCC diagnostic pop

#endif // GLOBAL_H_INCLUDED