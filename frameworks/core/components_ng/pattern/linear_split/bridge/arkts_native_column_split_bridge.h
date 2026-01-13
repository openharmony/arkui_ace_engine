/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_SPLIT_BRIDGE_ARKTS_NATIVE_COLUMN_SPLIT_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_SPLIT_BRIDGE_ARKTS_NATIVE_COLUMN_SPLIT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class ColumnSplitBridge {
public:
    static void RegisterColumnSplitAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static ArkUINativeModuleValue CreateColumnSplit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetResizable(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetDivider(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetDivider(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetColumnSplitClip(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static bool GetNativeNode(
        ArkUINodeHandle& nativeNode, const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm);
    static bool IsJsView(const Local<JSValueRef>& jsVal, panda::ecmascript::EcmaVM* vm);
};
}
#endif
// FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_SPLIT_BRIDGE_ARKTS_NATIVE_COLUMN_SPLIT_BRIDGE_H
