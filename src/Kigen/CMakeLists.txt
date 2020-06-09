set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../include/Kigen)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Files
set(FILES_HEADER
    ##[[
    ${INCROOT}/action/detail/ActionLeaves.hpp
    ${INCROOT}/action/detail/ActionNode.hpp
    ${INCROOT}/action/detail/LogicNode.hpp
    ${INCROOT}/action/Action.hpp
    ${INCROOT}/action/ActionControl.hpp
    ${INCROOT}/action/ActionRegistry.hpp
    #]]

    ${INCROOT}/application/DefaultApplicationLoop.hpp
    ${INCROOT}/application/BasicApplication.hpp
    ${INCROOT}/application/ApplicationClock.hpp
    ${INCROOT}/application/IApplication.hpp

    ${INCROOT}/conversion/to_string.hpp

    ${INCROOT}/graphics/Vector.hpp
    ${INCROOT}/graphics/Window.hpp

    ${INCROOT}/input/AbstractDevice.hpp
    ${INCROOT}/input/InputControl.hpp
    ${INCROOT}/input/KeyActionType.hpp
    ${INCROOT}/input/Keyboard.hpp
    ${INCROOT}/input/Mouse.hpp
    ${INCROOT}/input/WindowStatus.hpp

    ${INCROOT}/resource/ResourceControl.hpp
    ${INCROOT}/resource/ResourceExceptions.hpp
    ${INCROOT}/resource/ResourceHolder.hpp
    ${INCROOT}/resource/ResourceLoader.hpp
    ${INCROOT}/resource/SFML_LoaderMakers.hpp

    ${INCROOT}/state/State.hpp
    ${INCROOT}/state/StateControl.hpp

    ${INCROOT}/utils/locator/IService.hpp
    ${INCROOT}/utils/locator/ListOfServices.hpp
    ${INCROOT}/utils/locator/Locator.hpp
    ${INCROOT}/utils/locator/Locator.inl
    ${INCROOT}/utils/locator/NullService.hpp
    ${INCROOT}/utils/Assertion.hpp
    ${INCROOT}/utils/Destructible.hpp
    ${INCROOT}/utils/Logger.hpp
    ${INCROOT}/utils/Next.hpp
    ${INCROOT}/utils/NonCopyable.hpp
    ${INCROOT}/utils/NonMovable.hpp
    ${INCROOT}/utils/Palette.hpp
    ${INCROOT}/utils/Random.hpp
    ${INCROOT}/utils/StopWatch.hpp
    ${INCROOT}/utils/Type.hpp
    ${INCROOT}/utils/Utils.hpp
    ${INCROOT}/utils/Yield.hpp

    ${INCROOT}/world/component/Component.hpp
    ${INCROOT}/world/component/DrawableCircle.hpp
    ${INCROOT}/world/component/DrawableComponent.hpp
    ${INCROOT}/world/component/DrawableDebugBody.hpp
    ${INCROOT}/world/component/PhysicsBody.hpp

    ${INCROOT}/world/message/Communicable.hpp
    ${INCROOT}/world/message/Message.hpp
    ${INCROOT}/world/message/MessageBus.hpp

    ${INCROOT}/world/physics/shape/Circle.hpp
    ${INCROOT}/world/physics/shape/Polygon.hpp
    ${INCROOT}/world/physics/shape/Shape.hpp
    ${INCROOT}/world/physics/Collision.hpp
    ${INCROOT}/world/physics/Manifold.hpp
    ${INCROOT}/world/physics/Math.hpp
    ${INCROOT}/world/physics/Models.hpp
    ${INCROOT}/world/physics/PhysicsConstants.hpp
    ${INCROOT}/world/physics/PhysicsLaw.hpp
    ${INCROOT}/world/physics/PhysicsScene.hpp
    ${INCROOT}/world/physics/RigidBody.hpp

    ${INCROOT}/world/Entity.hpp
    ${INCROOT}/world/World.hpp

    ${INCROOT}/defines.hpp
    )

set(FILES_SRC
    ##[[
    ${SRCROOT}/action/Action.cpp
    #]]

    ${SRCROOT}/application/ApplicationClock.cpp
    ${SRCROOT}/application/BasicApplication.cpp

    ${SRCROOT}/conversion/to_string.cpp

    ${SRCROOT}/graphics/Vector.cpp
    ${SRCROOT}/graphics/Window.cpp

    ${SRCROOT}/input/InputControl.cpp
    ${SRCROOT}/input/Keyboard.cpp
    ${SRCROOT}/input/Mouse.cpp
    ${SRCROOT}/input/WindowStatus.cpp

    ${SRCROOT}/state/State.cpp
    ${SRCROOT}/state/StateControl.cpp

    ${SRCROOT}/utils/locator/Locator.cpp
    ${SRCROOT}/utils/locator/NullService.cpp
    ${SRCROOT}/utils/Logger.cpp
    ${SRCROOT}/utils/Random.cpp
    ${SRCROOT}/utils/StopWatch.cpp

    ${SRCROOT}/world/component/Component.cpp
    ${SRCROOT}/world/component/DrawableCircle.cpp
    ${SRCROOT}/world/component/DrawableDebugBody.cpp
    ${SRCROOT}/world/component/PhysicsBody.cpp

    ${SRCROOT}/world/message/Message.cpp
    ${SRCROOT}/world/message/MessageBus.cpp

    ${SRCROOT}/world/physics/law/EnergyLossLaw.cpp
    ${SRCROOT}/world/physics/law/GravitationLaw.cpp
    ${SRCROOT}/world/physics/shape/Circle.cpp
    ${SRCROOT}/world/physics/shape/Polygon.cpp
    ${SRCROOT}/world/physics/Collision.cpp
    ${SRCROOT}/world/physics/Manifold.cpp
    ${SRCROOT}/world/physics/Math.cpp
    ${SRCROOT}/world/physics/PhysicsScene.cpp
    ${SRCROOT}/world/physics/RigidBody.cpp
    ${SRCROOT}/world/Entity.cpp
    ${SRCROOT}/world/World.cpp
    )

add_library(kigen STATIC ${FILES_HEADER} ${FILES_SRC})


