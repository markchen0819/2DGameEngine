#pragma once

#include <glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../dependencies/rapidjson/document.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <string>
#include <vector>
#include <unordered_map>
#include <cerrno>
#include <cstdarg>
#include <stdlib.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "DataDriven/JSONConstants.h"
#include "rapidjson/filereadstream.h"

#include <functional>
#include "EventSystem/EventType.h"
#include "EventSystem/Event.h"
#include "EventSystem/EventListener.h"
#include "EventSystem/EventSystem.h"

#include "GameWindow.h"
#include "Experiment/ScreenSaverMovement.h"
#include "Logging.h"
#include "InputManager.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Color.h"
#include "Graphics/Material.h"
#include "Graphics/Vertex.h"
#include "Graphics/Mesh.h";
#include "Graphics/Transform.h"
#include "Graphics/Node.h"
#include "Graphics/Renderer.h"
#include "Camera.h"

#include "Physics/ShapeType.h"
#include "Debug/CollisionAreaObject.h"
#include "Physics/CollisionShape.h"
#include "Physics/CollisionManager.h"
#include "Physics/CollisionCircle.h"
#include "Physics/CollisionAABB.h"
#include "Physics/CollisionOBB.h"
#include "Physics/Body.h"
#include "Physics/PhysicsManager.h"

#include "Components/Component.h" 
#include "GameObject.h"
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"
#include "Components/PhysicComponent.h"

#include "DataDriven/ResourceManager.h"
#include "DataDriven/ObjectFactory.h"
