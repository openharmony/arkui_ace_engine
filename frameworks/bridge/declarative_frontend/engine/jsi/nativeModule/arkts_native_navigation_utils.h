/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_NAVIGATION_UTILS_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_NAVIGATION_UTILS_H

#include "core/interfaces/arkoala/arkoala_api.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::NG {
using ParamSendFunction = void(*)(ArkUINodeHandle, void*, ArkUI_Uint32);
class NativeNavigationUtils {
public:
    static void ParseBarItems(EcmaVM* vm, const Local<JSValueRef>& jsValue, std::vector<ArkUIBarItem>& items);
    static void ParseTitleOptions(const EcmaVM* vm, const Local<JSValueRef>& jsValue,
        ArkUINavigationTitlebarOptions& options);
    static void ParseAndSendFunctionParam(ArkUIRuntimeCallInfo* runtimeCallInfo, const Local<JSValueRef>& jsValue,
        ParamSendFunction& actionSendFunc, ParamSendFunction& symbolSendFunc);
    static void ParseBarItemsValue(EcmaVM* vm, const Local<panda::ObjectRef>& itemObject, ArkUIBarItem& toolBarItem);
    static void ParseBarItemsIcon(EcmaVM* vm, const Local<panda::ObjectRef>& itemObject, ArkUIBarItem& toolBarItem);
    static void UpdateNavigationBackgroundColor(const EcmaVM* vm, const Local<panda::ObjectRef>& obj,
        ArkUINavigationTitlebarOptions& options);
    static void AddBackgroundColorResource(
        const RefPtr<ResourceObject>& backgroundColorResObj, ArkUINavigationTitlebarOptions& options);

private:
    static void DeepCopyStringValue(char* des, uint32_t desLength, const std::string& src);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_NAVIGATION_UTILS_H