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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_TEXT_INPUT_MODIFIER_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_TEXT_INPUT_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
    const ArkUITextInputModifier* GetTextInputModifier();
    const CJUITextInputModifier* GetCJUITextInputModifier();
    void SetOnTextInputChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputChangeWithPreviewText(ArkUINodeHandle node, void* extraParam);
    void SetTextInputOnSubmit(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputCut(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputPaste(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputSelectionChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputEditChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputContentSizeChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextInputInputFilterError(ArkUINodeHandle node, void* extraParam);
    void SetTextInputOnTextContentScroll(ArkUINodeHandle node, void* extraParam);

    void ResetOnTextInputChange(ArkUINodeHandle node);
    void ResetOnTextInputChangeWithPreviewText(ArkUINodeHandle node);
    void ResetTextInputOnSubmit(ArkUINodeHandle node);
    void ResetOnTextInputCut(ArkUINodeHandle node);
    void ResetOnTextInputPaste(ArkUINodeHandle node);
    void ResetOnTextInputSelectionChange(ArkUINodeHandle node);
    void ResetOnTextInputEditChange(ArkUINodeHandle node);
    void ResetOnTextInputContentSizeChange(ArkUINodeHandle node);
    void ResetOnTextInputInputFilterError(ArkUINodeHandle node);
    void ResetTextInputOnTextContentScroll(ArkUINodeHandle node);

    void SetTextInputOnWillInsert(ArkUINodeHandle node, void* extraParam);
    void SetTextInputOnDidInsert(ArkUINodeHandle node, void* extraParam);
    void SetTextInputOnWillDelete(ArkUINodeHandle node, void* extraParam);
    void SetTextInputOnDidDelete(ArkUINodeHandle node, void* extraParam);
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_TEXT_INPUT_MODIFIER_H
