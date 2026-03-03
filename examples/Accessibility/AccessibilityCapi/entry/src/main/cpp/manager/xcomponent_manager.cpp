/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <cstdint>
#include <string>

#include <hilog/log.h>
#include <native_buffer/native_buffer.h>
#include <native_window/external_window.h>

#include "common/common.h"

#include "manager/AccessibilityManager.h"
#include "xcomponent_manager.h"


/**
 * @brief Callback for surface created event
 * @param component Pointer to the native XComponent
 * @param window Pointer to the window
 */
void OnSurfaceCreatedCB(OH_NativeXComponent *component, void *window)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback",
        "OnSurfaceCreatedCB");
    if ((component == nullptr) || (window == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
            "OnSurfaceCreatedCB: component or window is null");
        return;
    }

    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) !=
        OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
            "OnSurfaceCreatedCB: Unable to get XComponent id");
        return;
    }

    std::string id(idStr);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback",
        "OnSurfaceCreatedCB component id is %{public}s", id.c_str());

    auto plugin = NativeXComponentSample::PluginManager::GetInstance();
    plugin->AttachXComponent(id, component,
        reinterpret_cast<::OHNativeWindow *>(window));
}

/**
 * @brief Callback for surface changed event
 * @param component Pointer to the native XComponent
 * @param window Pointer to the window
 */
void OnSurfaceChangedCB(OH_NativeXComponent *component, void *window)
{
}

/**
 * @brief Callback for surface destroyed event
 * @param component Pointer to the native XComponent
 * @param window Pointer to the window
 */
void OnSurfaceDestroyedCB(OH_NativeXComponent *component, void *window)
{
}

/**
 * @brief Callback for touch event dispatch
 * @param component Pointer to the native XComponent
 * @param window Pointer to the window
 */
void DispatchTouchEventCB(OH_NativeXComponent *component, void *window)
{
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback",
        "DispatchTouchEventCB");
    OH_NativeXComponent_TouchEvent touchEvent;
}

/**
 * @brief Callback for hover event dispatch
 * @param xComponent Pointer to the native XComponent
 * @param isHover Whether the mouse is hovering
 */
void DispatchHoverEvent(::OH_NativeXComponent *xComponent, bool isHover)
{
}


namespace NativeXComponentSample {

/**
 * @brief Constructor for XComponentManager
 */
XComponentManager::XComponentManager()
    : accessibilityManager(new AccessibilityManager())
{
}

/**
 * @brief Destructor for XComponentManager
 */
XComponentManager::~XComponentManager()
{
    delete accessibilityManager;
}

/**
 * @brief Registers callbacks for XComponent events
 * @param nativeXComponent Pointer to the native XComponent
 */
void XComponentManager::RegisterCallback(OH_NativeXComponent *nativeXComponent)
{
    renderCallback_.OnSurfaceCreated = ::OnSurfaceCreatedCB;
    renderCallback_.OnSurfaceChanged = ::OnSurfaceChangedCB;
    renderCallback_.OnSurfaceDestroyed = ::OnSurfaceDestroyedCB;
    renderCallback_.DispatchTouchEvent = ::DispatchTouchEventCB;
    int ret = OH_NativeXComponent_RegisterCallback(nativeXComponent,
        &renderCallback_);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "XComponentManager",
        "RegisterCallback %{public}d", ret);
}

/**
 * @brief Sets the native XComponent for a specific ID
 * @param id The XComponent ID
 * @param nativeXComponent Pointer to the native XComponent
 * @param window Pointer to the native window
 */
void XComponentManager::SetNativeXComponent(const std::string &id,
    OH_NativeXComponent *nativeXComponent, OHNativeWindow *window)
{
    if (nativeXComponent == nullptr) {
        return;
    }
    auto it = nativeXComponentMap_.find(id);
    if (id.c_str() == singleInstanceId) {
        accessibilityManager->Initialize(nativeXComponent);
    } else {
        accessibilityManager->Initialize(id, nativeXComponent);
    }
    if (it != nativeXComponentMap_.end()) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN,
            "SetNativeXComponent", "%{public}s already exists",
                     id.data());
        return;
    } else {
        nativeXComponentMap_.emplace(id, XSurface{nativeXComponent, window});
    }
}

} // namespace NativeXComponentSample
