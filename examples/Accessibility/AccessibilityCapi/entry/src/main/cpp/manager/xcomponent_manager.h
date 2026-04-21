/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef NATIVE_XCOMPONENT_XCOMPONENT_MANAGER_H
#define NATIVE_XCOMPONENT_XCOMPONENT_MANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <native_window/external_window.h>
#include <napi/native_api.h>
#include <string>
#include <unordered_map>

namespace NativeXComponentSample {

class AccessibilityManager;
class XComponentManager {
public:
    XComponentManager();
    ~XComponentManager();
    std::string singleInstanceId = "XComponentIdSingle";
    void RegisterCallback(OH_NativeXComponent *nativeXComponent);

    struct XSurface {
        OH_NativeXComponent *xcomponent;
        OHNativeWindow *window;
    };

public:

    // manager xcomponent
    void SetNativeXComponent(const std::string &id, OH_NativeXComponent *nativeXComponent, OHNativeWindow *window);

    XSurface GetXSurface(const std::string &id) const
    {
        auto it = nativeXComponentMap_.find(id);
        return it != nativeXComponentMap_.end() ? it->second : XSurface{};
    }

private:
    std::unordered_map<std::string, XSurface> nativeXComponentMap_;

    OH_NativeXComponent_Callback renderCallback_;
    OH_NativeXComponent_MouseEvent_Callback mouseCallback_;
    AccessibilityManager *accessibilityManager;
};
}  // namespace NativeXComponentSample

#endif // NATIVE_XCOMPONENT_XCOMPONENT_MANAGER_H