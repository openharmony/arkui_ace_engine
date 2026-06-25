/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <cstdint>
#include <string>

#include <js_native_api.h>
#include <js_native_api_types.h>
#include <hilog/log.h>

#include "container.h"

namespace NativeXComponentSample {
    namespace {
        void OnSurfaceCreatedCB(OH_NativeXComponent *component, void *window)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceCreatedCB");
            if ((component == nullptr) || (window == nullptr)) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceCreatedCB: component or window is null");
                return;
            }

            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceCreatedCB: Unable to get XComponent id");
                return;
            }
        }

        void OnSurfaceChangedCB(OH_NativeXComponent *component, void *window)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceChangedCB");
            if ((component == nullptr) || (window == nullptr)) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceChangedCB: component or window is null");
                return;
            }

            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceChangedCB: Unable to get XComponent id");
                return;
            }
            std::string id(idStr);
            auto container = Container::GetInstance(id);
            if (container != nullptr) {
                container->OnSurfaceChanged(component, window);
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "surface changed");
            }
        }

        void OnSurfaceDestroyedCB(OH_NativeXComponent *component, void *window)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "OnSurfaceDestroyedCB");
            if ((component == nullptr) || (window == nullptr)) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceDestroyedCB: component or window is null");
                return;
            }

            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "OnSurfaceDestroyedCB: Unable to get XComponent id");
                return;
            }

            std::string id(idStr);
            Container::Release(id);
        }

        void DispatchTouchEventCB(OH_NativeXComponent *component, void *window)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchTouchEventCB");
            if ((component == nullptr) || (window == nullptr)) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "DispatchTouchEventCB: component or window is null");
                return;
            }

            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                             "DispatchTouchEventCB: Unable to get XComponent id");
                return;
            }

            std::string id(idStr);
            Container *render = Container::GetInstance(id);
            if (render != nullptr) {
                render->OnTouchEvent(component, window);
            }
        }

        void DispatchMouseEventCB(OH_NativeXComponent *component, void *window)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchMouseEventCB");
            int32_t ret;
            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
            if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                return;
            }

            std::string id(idStr);
            auto render = Container::GetInstance(id);
            if (render != nullptr) {
                render->OnMouseEvent(component, window);
            }
        }


        void DispatchHoverEventCB(OH_NativeXComponent *component, bool isHover)
        {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "DispatchHoverEventCB");
            int32_t ret;
            char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {};
            uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
            ret = OH_NativeXComponent_GetXComponentId(component, idStr, &idSize);
            if (ret != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
                return;
            }

            std::string id(idStr);
            auto container = Container::GetInstance(id);
            if (container != nullptr) {
                container->OnHoverEvent(component, isHover);
            }
        }
    } // namespace

    std::unordered_map<std::string, Container *> Container::instance_;

    Container::Container(const std::string &id)
    {
        this->id_ = id;
    }

    Container *Container::GetInstance(const std::string &id)
    {
        if (instance_.find(id) == instance_.end()) {
            Container *instance = new Container(id);
            instance_[id] = instance;
            return instance;
        } else {
            return instance_[id];
        }
    }

    void Container::Release(const std::string &id)
    {
        Container *render = Container::GetInstance(id);
        if (render != nullptr) {
        }
    }

    void Container::OnSurfaceChanged(OH_NativeXComponent *component, void *window)
    {
        char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
        uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
        if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                         "OnSurfaceChanged: Unable to get XComponent id");
            return;
        }
        double offsetX;
        double offsetY;
        OH_NativeXComponent_GetXComponentOffset(component, window, &offsetX, &offsetY);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "OH_NativeXComponent_GetXComponentOffset",
                     "offsetX = %{public}lf, offsetY = %{public}lf", offsetX, offsetY);
        uint64_t width;
        uint64_t height;
        OH_NativeXComponent_GetXComponentSize(component, window, &width, &height);
    }

    void Container::OnTouchEvent(OH_NativeXComponent *component, void *window)
    {
        char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
        uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
        if (OH_NativeXComponent_GetXComponentId(component, idStr, &idSize) != OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Callback",
                         "DispatchTouchEventCB: Unable to get XComponent id");
            return;
        }
        OH_NativeXComponent_TouchEvent touchEvent;
        OH_NativeXComponent_GetTouchEvent(component, window, &touchEvent);
        std::string id(idStr);
        Container *container = Container::GetInstance(id);
        float tiltX = 0.0f;
        float tiltY = 0.0f;
        OH_NativeXComponent_TouchPointToolType toolType =
            OH_NativeXComponent_TouchPointToolType::OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN;
        OH_NativeXComponent_GetTouchPointToolType(component, 0, &toolType);
        OH_NativeXComponent_GetTouchPointTiltX(component, 0, &tiltX);
        OH_NativeXComponent_GetTouchPointTiltY(component, 0, &tiltY);
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "OnTouchEvent",
                     "touch info: toolType = %{public}d, tiltX = %{public}lf, tiltY = %{public}lf", toolType, tiltX,
                     tiltY);
    }

    void Container::RegisterCallback(OH_NativeXComponent* nativeXComponent)
    {
        containerCallback_.OnSurfaceCreated = OnSurfaceCreatedCB;
        containerCallback_.OnSurfaceChanged = OnSurfaceChangedCB;
        containerCallback_.OnSurfaceDestroyed = OnSurfaceDestroyedCB;
        containerCallback_.DispatchTouchEvent = DispatchTouchEventCB;
        OH_NativeXComponent_RegisterCallback(nativeXComponent, &containerCallback_);

        mouseCallback_.DispatchMouseEvent = DispatchMouseEventCB;
        mouseCallback_.DispatchHoverEvent = DispatchHoverEventCB;
        OH_NativeXComponent_RegisterMouseEventCallback(nativeXComponent, &mouseCallback_);
        OH_NativeXComponent_RegisterOnTouchInterceptCallback(
            nativeXComponent, [](OH_NativeXComponent*, ArkUI_UIInputEvent*) -> HitTestMode {
                OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "callback",
                    "OH_NativeXComponent_RegisterOnTouchInterceptCallback");
                return HitTestMode::HTM_TRANSPARENT;
            });
    }

    void Container::OnMouseEvent(OH_NativeXComponent *component, void *window)
    {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Container", "OnMouseEvent");
        OH_NativeXComponent_MouseEvent mouseEvent;
        int32_t ret = OH_NativeXComponent_GetMouseEvent(component, window, &mouseEvent);
        if (ret == OH_NATIVEXCOMPONENT_RESULT_SUCCESS) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Container",
                         "MouseEvent Info: x = %{public}f, y = %{public}f, action = %{public}d, button = %{public}d",
                         mouseEvent.x, mouseEvent.y, mouseEvent.action, mouseEvent.button);
        } else {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Container", "GetMouseEvent error");
        }
    }

    void Container::OnHoverEvent(OH_NativeXComponent *component, bool isHover)
    {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Container", "OnHoverEvent isHover_ = %{public}d", isHover);
    }
} // namespace NativeXComponentSample
