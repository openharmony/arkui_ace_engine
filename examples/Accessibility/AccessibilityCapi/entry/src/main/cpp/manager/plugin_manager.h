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
#ifndef NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
#define NATIVE_XCOMPONENT_PLUGIN_MANAGER_H

#include <ace/xcomponent/native_interface_xcomponent.h>
#include <js_native_api.h>
#include <js_native_api_types.h>
#include <napi/native_api.h>
#include <string>

#include "xcomponent_manager.h"
namespace NativeXComponentSample {

class AbilityInfo {
public:
    napi_ref uiAbility;
    napi_ref windowStage;
    napi_ref window;
    napi_env env;
    void Init(napi_env env, napi_value uiAbility, napi_value windowStage);
    napi_value getWindow();
    ~AbilityInfo();
};

class PluginManager {
public:
    PluginManager();
    ~PluginManager();

    static PluginManager *GetInstance()
    {
        return &PluginManager::pluginManager_;
    }

    static AbilityInfo &GetAbilityInfo()
    {
        return m_abilityInfo;
    }

    void AttachXComponent(const std::string &id, OH_NativeXComponent *nativeXComponent, OHNativeWindow *window);
    void Export(napi_env env, napi_value exports);

private:
    static PluginManager pluginManager_;
    static AbilityInfo m_abilityInfo;
    XComponentManager *xcomponentMgr;
};
}  // namespace NativeXComponentSample
#endif  // NATIVE_XCOMPONENT_PLUGIN_MANAGER_H
