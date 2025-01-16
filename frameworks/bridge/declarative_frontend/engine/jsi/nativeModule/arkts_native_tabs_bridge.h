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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_TABS_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_TABS_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"

namespace OHOS::Ace::NG {
class TabsBridge : public CommonBridge {
public:
    static ArkUINativeModuleValue SetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
};
} // namespace OHOS::Ace::NG

#endif