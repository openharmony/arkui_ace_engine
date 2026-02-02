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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_RICH_EDITOR_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_RICH_EDITOR_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIRichEditorModifier* GetRichEditorModifier();
const CJUIRichEditorModifier* GetCJUIRichEditorModifier();
void SetRichEditorNapiOnSelectionChange(ArkUINodeHandle node, void* callback);
void ResetRichEditorOnSelectionChange(ArkUINodeHandle node);
void SetRichEditorNapiOnReady(ArkUINodeHandle node, void* extraParam);
void ResetRichEditorOnReady(ArkUINodeHandle node);
void SetRichEditorNapiOnPaste(ArkUINodeHandle node, void* callback);
void ResetRichEditorOnPaste(ArkUINodeHandle node);
void SetRichEditorDetectEnable(ArkUINodeHandle node, ArkUI_Uint32 value);
void ResetRichEditorDetectEnable(ArkUINodeHandle node);
void SetRichEditorNapiDataDetectorConfigWithEvent(
    ArkUINodeHandle node, const struct ArkUITextDetectConfigStruct* arkUITextDetectConfig);
void ResetRichEditorDataDetectorConfigWithEvent(ArkUINodeHandle node);
void SetRichEditorNapiOnEditingChange(ArkUINodeHandle node, void* extraParam);
void ResetRichEditorOnEditingChange(ArkUINodeHandle node);
void SetRichEditorNapiOnSubmit(ArkUINodeHandle node, void* extraParam);
void ResetRichEditorOnSubmit(ArkUINodeHandle node);
void SetRichEditorNapiOnCut(ArkUINodeHandle node, void* extraParam);
void ResetRichEditorOnCut(ArkUINodeHandle node);
void SetRichEditorNapiOnCopy(ArkUINodeHandle node, void* extraParam);
void ResetRichEditorOnCopy(ArkUINodeHandle node);
void SetRichEditorNapiEditMenuOptions(ArkUINodeHandle node, ArkUIEditOptionsParam* optionsParam);
void ParseFontSize(FrameNode* frameNode, struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style);
void ParseShadow(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style);
void ParseDecoration(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style);
void ParseTextBackgroundStyle(struct OHOS::Ace::UpdateSpanStyle& updateSpanStyle, TextStyle& textStyle,
    const ArkUIRichEditorTextStyle& style);
void ParseFontSize(FrameNode* frameNode, struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle);
void ParseShadow(struct ArkUIRichEditorTextStyle& textStyle, const struct OHOS::Ace::UpdateSpanStyle& typingStyle);
void ParseDecoration(struct ArkUIRichEditorTextStyle& textStyle, const struct OHOS::Ace::UpdateSpanStyle& typingStyle);
void ParseTextBackgroundStyle(struct ArkUIRichEditorTextStyle& textStyle,
    const struct OHOS::Ace::UpdateSpanStyle& typingStyle);
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_RichEditor_MODIFIER_H