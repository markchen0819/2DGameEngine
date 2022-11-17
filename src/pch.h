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
#include <stack>
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

#include "GameEngine/DataDriven/JSONConstants.h"
#include "rapidjson/filereadstream.h"

#include <functional>
#include "GameEngine/EventSystem/EventType.h"
#include "GameEngine/EventSystem/Event.h"
#include "GameEngine/EventSystem/EventListener.h"
#include "GameEngine/EventSystem/EventSystem.h"

#include "GameEngine/Window/GameWindow.h"
#include "GameEngine/Window/FrameRateController.h"
#include "Experiment/ScreenSaverMovement.h"
#include "GameEngine/Logging/Logging.h"
#include "GameEngine/InputSystem/InputManager.h"

#include "GameEngine/Graphics/Shader.h"
#include "GameEngine/Graphics/Texture.h"
#include "GameEngine/Graphics/Color.h"
#include "GameEngine/Graphics/Material.h"
#include "GameEngine/Graphics/Vertex.h"
#include "GameEngine/Graphics/Mesh.h";
#include "GameEngine/Graphics/Transform.h"
#include "GameEngine/Graphics/Node.h"
#include "GameEngine/Graphics/Renderer.h"
#include "GameEngine/Graphics/Camera.h"

#include "GameEngine/Physics/ShapeType.h"
#include "GameEngine/Debug/CollisionAreaObject.h"
#include "GameEngine/Physics/CollisionShape.h"
#include "GameEngine/Physics/CollisionManager.h"
#include "GameEngine/Physics/CollisionCircle.h"
#include "GameEngine/Physics/CollisionAABB.h"
#include "GameEngine/Physics/CollisionOBB.h"
#include "GameEngine/Physics/Body.h"
#include "GameEngine/Physics/PhysicsManager.h"

#include "GameEngine/Components/Component.h" 
#include "GameEngine/Scene/GameObject.h"
#include "GameEngine/Components/TransformComponent.h"
#include "GameEngine/Components/RenderComponent.h"
#include "GameEngine/Components/PhysicComponent.h"

#include "GameEngine/DataDriven/ResourceManager.h"
#include "GameEngine/DataDriven/ObjectFactory.h"
#include "GameEngine/Scene/Root.h"
#include "GameEngine/Scene/Scene.h"

#include "GameEngine/ServiceLocator.h"
#include "GameEngine/GameEngine.h"


// User Codes
#include "UserDefined/SelfRotateComponent.h"
#include "UserDefined/PlayerControlComponent.h"
#include "UserDefined/Level2.h"
#include "UserDefined/Game.h"
