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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_BRIDGE_ARKTS_NATIVE_SHAPE_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_BRIDGE_ARKTS_NATIVE_SHAPE_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class ShapeBridge {
public:
    static void RegisterShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static ArkUINativeModuleValue CreateShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue CreateShapeDetached(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue PopShape(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetViewPort(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMesh(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetShapeInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShapeInitialize(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SHAPE_BRIDGE_ARKTS_NATIVE_SHAPE_BRIDGE_H
