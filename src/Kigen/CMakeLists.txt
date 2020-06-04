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
    ${INCROOT}/utils/NonCopyable.hpp
    ${INCROOT}/utils/NonMovable.hpp
    ${INCROOT}/utils/StopWatch.hpp
    ${INCROOT}/utils/Type.hpp
    ${INCROOT}/utils/Utils.hpp
    ${INCROOT}/utils/Yield.hpp

    ${INCROOT}/world/component/Component.hpp
    ${INCROOT}/world/component/DrawableCircleComponent.hpp
    ${INCROOT}/world/component/PhysicsComponent.hpp

    ${INCROOT}/world/physics/Manifold.hpp
    ${INCROOT}/world/physics/Math.hpp
    ${INCROOT}/world/physics/Models.hpp
    ${INCROOT}/world/physics/PhysicsScene.hpp
    ${INCROOT}/world/physics/RigidBody.hpp
    ${INCROOT}/world/physics/Shape.hpp

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
    ${SRCROOT}/utils/StopWatch.cpp

    ${SRCROOT}/world/component/Component.cpp
    ${SRCROOT}/world/component/DrawableCircleComponent.cpp
    ${SRCROOT}/world/component/PhysicsComponent.cpp
    ${SRCROOT}/world/physics/Manifold.cpp
    ${SRCROOT}/world/physics/PhysicsScene.cpp
    ${SRCROOT}/world/physics/RigidBody.cpp
    ${SRCROOT}/world/Entity.cpp
    ${SRCROOT}/world/World.cpp
    )

add_library(kigen STATIC ${FILES_HEADER} ${FILES_SRC})


