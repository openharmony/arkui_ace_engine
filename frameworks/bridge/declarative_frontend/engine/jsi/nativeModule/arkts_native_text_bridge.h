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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_TEXT_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_TEXT_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class TextBridge {
public:
    static ArkUINativeModuleValue SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextCase(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextCase(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMaxLines(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxLines(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ReSetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetContent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextController(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOptimizeTrailingSpace(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOptimizeTrailingSpace(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSelection(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelection(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextSelectableMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextSelectableMode(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetMarqueeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetMarqueeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnMarqueeStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnMarqueeStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetTextContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetTextContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo);

private:
    static void ParseAIEntityColorAndPreview(
        ArkUIRuntimeCallInfo* runtimeCallInfo, struct ArkUITextDetectConfigStruct& arkUITextDetectConfig,
        RefPtr<ResourceObject>& colorResObj, RefPtr<ResourceObject>& decColorResObj,
        ArkUINodeHandle nativeNode);
};
} // namespace OHOS::Ace::NG

#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_TEXT_BRIDGE_H
