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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RICH_EDITOR_BRIDGE_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RICH_EDITOR_BRIDGE_H

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"

namespace OHOS::Ace::NG {
class RichEditorBridge {
public:
    static ArkUINativeModuleValue SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnIMEInputComplete(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDidChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAboutToDelete(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetCopyOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetCaretColor(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnSubmit(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetAboutToIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnReady(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDeleteComplete(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnEditingChange(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue SetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnPaste(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnCut(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableKeyboardOnFocus(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnablePreviewText(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEditMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnterKeyType(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetBarState(ArkUIRuntimeCallInfo *runtimeCallInfo);

    static ArkUINativeModuleValue SetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxLength(ArkUIRuntimeCallInfo *runtimeCallInfo);

    static ArkUINativeModuleValue SetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo);
    static ArkUINativeModuleValue ResetMaxLines(ArkUIRuntimeCallInfo *runtimeCallInfo);

    static ArkUINativeModuleValue SetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetStopBackPress(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetKeyboardAppearance(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetOnDidIMEInput(ArkUIRuntimeCallInfo* runtimeCallInfo);

    static ArkUINativeModuleValue SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
    static ArkUINativeModuleValue ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo);
private:
    static void ParseAIEntityColor(
        ArkUIRuntimeCallInfo* runtimeCallInfo, struct ArkUITextDetectConfigStruct& arkUITextDetectConfig);
};
}

#endif  // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_ENGINE_JSI_NATIVEMODULE_ARKTS_NATIVE_RICH_EDITOR_H