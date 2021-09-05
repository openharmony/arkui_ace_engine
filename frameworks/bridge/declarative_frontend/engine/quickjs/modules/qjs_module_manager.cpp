/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_module_manager.h"

#include "base/log/log.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_curves_module.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_matrix4_module.h"
#include "frameworks/bridge/declarative_frontend/engine/quickjs/modules/qjs_router_module.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"

namespace OHOS::Ace::Framework {

ModuleManager* ModuleManager::GetInstance()
{
    static ModuleManager instance;
    return &instance;
}

bool ModuleManager::InitModule(JSContext* ctx, const std::string& moduleName, JSValue& jsObject)
{
    static const std::unordered_map<std::string, void (*)(JSContext* ctx, JSValue& jsObject)> MODULE_LIST = {
        { "system.router", [](JSContext* ctx, JSValue& jsObject) { InitRouterModule(ctx, jsObject); } },
        { "ohos.router", [](JSContext* ctx, JSValue& jsObject) { InitRouterModule(ctx, jsObject); } },
        { "system.curves", [](JSContext* ctx, JSValue& jsObject) { InitCurvesModule(ctx, jsObject); } },
        { "ohos.curves", [](JSContext* ctx, JSValue& jsObject) { InitCurvesModule(ctx, jsObject); } },
        { "system.matrix4", [](JSContext* ctx, JSValue& jsObject) { InitMatrix4Module(ctx, jsObject); } },
        { "ohos.matrix4", [](JSContext* ctx, JSValue& jsObject) { InitMatrix4Module(ctx, jsObject); } },
    };
    auto iter = MODULE_LIST.find(moduleName);
    if (iter != MODULE_LIST.end()) {
        iter->second(ctx, jsObject);
        LOGD("ModuleManager InitModule is %{private}s", moduleName.c_str());
        return true;
    } else {
        LOGE("register module is not found");
        return false;
    }
}
} // namespace OHOS::Ace::Framework