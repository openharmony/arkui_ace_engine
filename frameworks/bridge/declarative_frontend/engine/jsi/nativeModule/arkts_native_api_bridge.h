/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "ecmascript/napi/include/jsnapi.h"

#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/engine/js_object_template.h"
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "core/components/common/properties/text_style.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG {
using ArkUINativeModuleValue = panda::Local<panda::JSValueRef>;
using ArkUIRuntimeCallInfo = panda::JsiRuntimeCallInfo;
using panda::JSValueRef;
using panda::Local;
using panda::ecmascript::EcmaVM;
class ArkUINativeModule {
public:
    static ArkUINativeModuleValue PreviewMockComponent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetFrameNodeByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetPageInfoByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetNavigationInfoByUniqueId(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetArkUINativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetUIState(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSupportedUIState(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetFrameNodeByKey(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue GetAttachedFrameNodeById(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue RequireDynamicSyncScene(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFrameRateRange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMarqueeFrameRateRange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue LoadNativeModule(ArkUIRuntimeCallInfo* runtimeCallInfo);

    // ArkTSCard start
    static ArkUINativeModuleValue GetArkUINativeModuleForm(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static void RegisterArkUINativeModuleFormLite(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterArkUINativeModuleFormFull(
        Local<panda::ObjectRef> object, EcmaVM* vm, bool isLiteSetRegistered);
    // ArkTSCard end
private:
    static void RegisterScrollableAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterButtonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterToggleAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterDividerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavigationAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterImageAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavRouterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNavigatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNodeContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterXComponentNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRenderNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterFrameNodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterPanelAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterLineAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterPathAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterPolygonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterPolylineAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSideBarContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCalendarPickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTabAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterStepperItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterStepperAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterFormAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterMenuItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterMenuAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterMarqueeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterDatePickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterAlphabetIndexerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSelectAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRadioAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSliderAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRatingAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTimepickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTextpickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterThemeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterWaterFlowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCheckboxAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterDataPanelAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterScrollAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterGridItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterProgressAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterPluginAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCommonShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterShapeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRectAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSwiperAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterListAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterGridAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterListItemGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterQRCodeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterLoadingProgressAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTextClockAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterListItemAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTextTimerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterXComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTabContentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRefreshAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterFlexAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterResourceAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterBadgeAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterScrollBarAttributes(Local<panda::ObjectRef> object, EcmaVM *vm);
    static void RegisterIndicatorComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterWebAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterImageAnimatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterLazyVGridLayoutAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
#ifdef WINDOW_SCENE_SUPPORTED
    static void RegisterEmbeddedComponentAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
#endif
    static void RegisterCanvasAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterVideoAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterContainerPickerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterGlobalMethods(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterNativeUtils(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCommonAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterColumnAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterStackAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterTextAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCounterAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterCheckboxGroupAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterBlankAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSpanAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterGridColAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterGridRowAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSymbolGlyphAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterSymbolSpanAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    static void RegisterRelativeContainerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm);
    // ArkTSCard start
    static void RegisterFrameNodeAttributesForm(Local<panda::ObjectRef> object, EcmaVM* vm);
    // ArkTSCard end
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_API_BRIDGE_H
