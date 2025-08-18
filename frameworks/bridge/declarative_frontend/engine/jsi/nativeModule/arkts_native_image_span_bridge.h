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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_IMAGE_SPAN_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_IMAGE_SPAN_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class ImageSpanBridge {
public:
    static ArkUINativeModuleValue SetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetObjectFit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextBackgroundStyle(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextBackgroundStyle(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetBaselineOffset(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetBaselineOffset(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetAlt(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetAlt(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetOnComplete(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnComplete(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetOnError(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnError(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetBorderRadius(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetColorFilter(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetColorFilter(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue SetImageSpanSrc(ArkUIRuntimeCallInfo *runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_IMAGE_SPAN_BRIDGE_H