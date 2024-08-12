set(PROJECT_NAME SimpleMod)

################################################################################
# Source groups
################################################################################
set(includes__Memory
    "../Memory/GameData.cpp"
    "../Memory/GameData.h"
    "../Memory/Hooks.cpp"
    "../Memory/Hooks.h"
    "../Memory/SlimMem.cpp"
    "../Memory/SlimMem.h"
)
source_group("includes\\Memory" FILES ${includes__Memory})

set(includes__SDK
    "../SDK/BlockLegacy.cpp"
    "../SDK/BlockLegacy.h"
    "../SDK/C_EntityList.cpp"
    "../SDK/C_EntityList.h"
    "../SDK/ClientInstance.cpp"
    "../SDK/ClientInstance.h"
    "../SDK/Entity.cpp"
    "../SDK/Entity.h"
    "../SDK/GameMode.cpp"
    "../SDK/GameMode.h"
    "../SDK/LoopbackPacketSender.cpp"
    "../SDK/LoopbackPacketSender.h"
    "../SDK/Packet.cpp"
    "../SDK/Packet.h"
    "../SDK/TextHolder.h"
)
source_group("includes\\SDK" FILES ${includes__SDK})

set(includes__SimpleMod
    "Config/ConfigManager.cpp"
    "Config/ConfigManager.h"
    "Hwid_user.cpp"
    "Hwid_user.h"
    "Module/Modules/SimpleUser.cpp"
    "Module/Modules/SimpleUser.h"
)
source_group("includes\\SimpleMod" FILES ${includes__SimpleMod})

set(includes__SimpleMod__Command
    "Command/CommandMgr.cpp"
    "Command/CommandMgr.h"
    "Command/Commands/IMCCommand.cpp"
    "Command/Commands/IMCCommand.h"
)
source_group("includes\\SimpleMod\\Command" FILES ${includes__SimpleMod__Command})

set(includes__SimpleMod__Command__Commands
    "Command/Commands/BindCommand.cpp"
    "Command/Commands/BindCommand.h"
    "Command/Commands/CommandRequestCommand.cpp"
    "Command/Commands/CommandRequestCommand.h"
    "Command/Commands/ConfigCommand.cpp"
    "Command/Commands/ConfigCommand.h"
    "Command/Commands/GameModeCommand.cpp"
    "Command/Commands/GameModeCommand.h"
    "Command/Commands/HelpCommand.cpp"
    "Command/Commands/HelpCommand.h"
    "Command/Commands/ModulesCommand.cpp"
    "Command/Commands/ModulesCommand.h"
    "Command/Commands/PanicCommand.cpp"
    "Command/Commands/PanicCommand.h"
    "Command/Commands/PlaysoundCommand.cpp"
    "Command/Commands/PlaysoundCommand.h"
    "Command/Commands/SpammerCommand.cpp"
    "Command/Commands/SpammerCommand.h"
    "Command/Commands/TeleportCommand.cpp"
    "Command/Commands/TeleportCommand.h"
    "Command/Commands/TestCommand.cpp"
    "Command/Commands/TestCommand.h"
    "Command/Commands/UserCommand.cpp"
    "Command/Commands/UserCommand.h"
)
source_group("includes\\SimpleMod\\Command\\Commands" FILES ${includes__SimpleMod__Command__Commands})

set(includes__SimpleMod__Menu
    "Menu/bytes.hpp"
    "Menu/DrawUtils.cpp"
    "Menu/DrawUtils.h"
    "Menu/GuiControls.cpp"
    "Menu/GuiControls.h"
    "Menu/Guiprogram.cpp"
    "Menu/Guiprogram.h"
    "Menu/hashes.hpp"
)
source_group("includes\\SimpleMod\\Menu" FILES ${includes__SimpleMod__Menu})

set(includes__SimpleMod__Module
    "Module/ModuleManager.cpp"
    "Module/ModuleManager.h"
    "Module/Modules/IModule.cpp"
    "Module/Modules/IModule.h"
)
source_group("includes\\SimpleMod\\Module" FILES ${includes__SimpleMod__Module})

set(includes__SimpleMod__Module__Modules__Combat
    "Module/Modules/Killaura.cpp"
    "Module/Modules/Killaura.h"
    "Module/Modules/Reach.cpp"
    "Module/Modules/Reach.h"
    "Module/Modules/TpAura.cpp"
    "Module/Modules/TpAura.h"
)
source_group("includes\\SimpleMod\\Module\\Modules\\Combat" FILES ${includes__SimpleMod__Module__Modules__Combat})

set(includes__SimpleMod__Module__Modules__Misc
    "Module/Modules/Derp.cpp"
    "Module/Modules/Derp.h"
    "Module/Modules/NoPacket.cpp"
    "Module/Modules/NoPacket.h"
    "Module/Modules/PacketLogs.cpp"
    "Module/Modules/PacketLogs.h"
    "Module/Modules/Spammer.cpp"
    "Module/Modules/Spammer.h"
)
source_group("includes\\SimpleMod\\Module\\Modules\\Misc" FILES ${includes__SimpleMod__Module__Modules__Misc})

set(includes__SimpleMod__Module__Modules__Movement
    "Module/Modules/AirJump.cpp"
    "Module/Modules/AirJump.h"
    "Module/Modules/fly.cpp"
    "Module/Modules/fly.h"
    "Module/Modules/GuiMod.cpp"
    "Module/Modules/GuiMod.h"
    "Module/Modules/Jetpack.cpp"
    "Module/Modules/Jetpack.h"
    "Module/Modules/NoWeb.cpp"
    "Module/Modules/NoWeb.h"
)
source_group("includes\\SimpleMod\\Module\\Modules\\Movement" FILES ${includes__SimpleMod__Module__Modules__Movement})

set(includes__SimpleMod__Module__Modules__Player
    "Module/Modules/NoFall.cpp"
    "Module/Modules/NoFall.h"
)
source_group("includes\\SimpleMod\\Module\\Modules\\Player" FILES ${includes__SimpleMod__Module__Modules__Player})

set(includes__SimpleMod__Module__Modules__World
    "Module/Modules/Nuker.cpp"
    "Module/Modules/Nuker.h"
)
source_group("includes\\SimpleMod\\Module\\Modules\\World" FILES ${includes__SimpleMod__Module__Modules__World})

set(includes__Utils
    "../Utils/easylogging++.cc"
    "../Utils/easylogging++.h"
    "../Utils/HMath.h"
    "../Utils/Json.hpp"
    "../Utils/Keys.h"
    "../Utils/logger.cpp"
    "../Utils/logger.h"
    "../Utils/TextFormat.cpp"
    "../Utils/TextFormat.h"
    "../Utils/TimerUtil.cpp"
    "../Utils/TimerUtil.h"
    "../Utils/Utils.cpp"
    "../Utils/Utils.h"
)
source_group("includes\\Utils" FILES ${includes__Utils})

set(includes__include__ImGui
    "../include/ImGui/imconfig.h"
    "../include/ImGui/imgui.cpp"
    "../include/ImGui/imgui.h"
    "../include/ImGui/imgui_demo.cpp"
    "../include/ImGui/imgui_draw.cpp"
    "../include/ImGui/imgui_internal.h"
    "../include/ImGui/imgui_tables.cpp"
    "../include/ImGui/imgui_widgets.cpp"
    "../include/ImGui/imstb_rectpack.h"
    "../include/ImGui/imstb_textedit.h"
    "../include/ImGui/imstb_truetype.h"
)
source_group("includes\\include\\ImGui" FILES ${includes__include__ImGui})

set(includes__include__ImGui__GL
    "../include/ImGui/GL.h"
    "../include/ImGui/GL/GLx64/glew.h"
    "../include/ImGui/GL/GLx64/glxew.h"
    "../include/ImGui/GL/GLx64/wglew.h"
    "../include/ImGui/GL/GLx86/glew.h"
    "../include/ImGui/GL/GLx86/glxew.h"
    "../include/ImGui/GL/GLx86/wglew.h"
    "../include/ImGui/gl3w.cpp"
    "../include/ImGui/gl3w.h"
    "../include/ImGui/glcorearb.h"
)
source_group("includes\\include\\ImGui\\GL" FILES ${includes__include__ImGui__GL})

set(includes__include__ImGui__backends
    "../include/ImGui/backends/imgui_impl_dx11.cpp"
    "../include/ImGui/backends/imgui_impl_dx11.h"
    "../include/ImGui/backends/imgui_impl_opengl2.cpp"
    "../include/ImGui/backends/imgui_impl_opengl2.h"
    "../include/ImGui/backends/imgui_impl_opengl3.cpp"
    "../include/ImGui/backends/imgui_impl_opengl3.h"
    "../include/ImGui/backends/imgui_impl_opengl3_loader.h"
    "../include/ImGui/backends/imgui_impl_win32.cpp"
    "../include/ImGui/backends/imgui_impl_win32.h"
)
source_group("includes\\include\\ImGui\\backends" FILES ${includes__include__ImGui__backends})

set(includes__include__Minhook
    "../include/MinHook/MinHook.h"
)
source_group("includes\\include\\Minhook" FILES ${includes__include__Minhook})

set(
    "Loader.cpp"
    "Loader.h"
)
source_group("源文件" FILES ${})

set(ALL_FILES
    ${includes__Memory}
    ${includes__SDK}
    ${includes__SimpleMod}
    ${includes__SimpleMod__Command}
    ${includes__SimpleMod__Command__Commands}
    ${includes__SimpleMod__Menu}
    ${includes__SimpleMod__Module}
    ${includes__SimpleMod__Module__Modules__Combat}
    ${includes__SimpleMod__Module__Modules__Misc}
    ${includes__SimpleMod__Module__Modules__Movement}
    ${includes__SimpleMod__Module__Modules__Player}
    ${includes__SimpleMod__Module__Modules__World}
    ${includes__Utils}
    ${includes__include__ImGui}
    ${includes__include__ImGui__GL}
    ${includes__include__ImGui__backends}
    ${includes__include__Minhook}
    ${}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/pch.h>"
)

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE SimpleMod)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION_RELEASE "FALSE"
    )
endif()
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
            MultiThreadedDebugDLL
        >
        $<$<CONFIG:Release>:
            MultiThreadedDLL
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
    )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "SIMPLEMOD_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "UNICODE;"
        "_UNICODE"
    )
elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
            "_DEBUG"
        ">"
        "$<$<CONFIG:Release>:"
            "NDEBUG"
        ">"
        "WIN32;"
        "SIMPLEMOD_EXPORTS;"
        "_WINDOWS;"
        "_USRDLL;"
        "_MBCS"
    )
endif()

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Zi
            >
            $<$<CONFIG:Release>:
                /Od;
                /Oi-;
                /RTC1;
                ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
        )
    endif()
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG;
            /SUBSYSTEM:WINDOWS
        )
    endif()
endif()

################################################################################
# Dependencies
################################################################################
if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "$<$<CONFIG:Debug>:"
            "libcurl.dll.a;"
            "libcurl_object;"
            "libcrypto.a"
        ">"
        "opengl32;"
        "d3d11;"
        "d3dcompiler;"
        "dxgi"
    )
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")

