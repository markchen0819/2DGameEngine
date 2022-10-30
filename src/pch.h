#pragma once
#include <iostream>
#include <glm/ext/vector_float3.hpp>

#include "GameWindow.h"
#include "Experiment/ScreenSaverMovement.h"
#include "Logging.h"
#include "Camera.h"
#include "InputManager.h"

#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h";
#include "Graphics/Node.h"
#include "Graphics/Renderer.h"

#include "Physics/CollisionManager.h"
#include "Physics/CollisionCircle.h"
#include "Physics/CollisionAABB.h"
#include "Physics/CollisionOBB.h"
#include "Physics/PhysicsManager.h"


#include "EventSystem/Event.h"
#include "EventSystem/EventSystem.h"

#include "Components/Component.h"
#include "GameObject.h" // need forward declaration of component
#include "Components/TransformComponent.h"
#include "Components/RenderComponent.h"
#include "Components/PhysicComponent.h"


#include "UserDefined/TriangleObject.h"