/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_API_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_API_BRIDGE_H

#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/js_object_template.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace::NG {
using ArkUINativeModuleValue = panda::Local<panda::JSValueRef>;
using ArkUIRuntimeCallInfo = panda::JsiRuntimeCallInfo;
class ArkUINativeModule {
public:
    static ArkUINativeModuleValue GetFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetArkUINativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static void RegisterButtonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterDividerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavigationAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterImageAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavRouterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavigatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_API_BRIDGE_H
