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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_BRIDGE_ARKTS_NATIVE_QRCODE_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_BRIDGE_ARKTS_NATIVE_QRCODE_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class QRCodeBridge {
public:
    static void RegisterQRCodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static ArkUINativeModuleValue CreateQRCode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetQRColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetQRColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetQRBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetQRBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContentOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetContentOpacity(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetQRValue(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_QRCODE_BRIDGE_ARKTS_NATIVE_QRCODE_BRIDGE_H
