/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_TEXT_AREA_MODIFIER_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_TEXT_AREA_MODIFIER_H

#pragma once

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
    const ArkUITextAreaModifier* GetTextAreaModifier();
    const CJUITextAreaModifier* GetCJUITextAreaModifier();
    void SetOnTextAreaChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaChangeWithPreviewText(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaPaste(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaSelectionChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaEditChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaContentSizeChange(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaInputFilterError(ArkUINodeHandle node, void* extraParam);
    void SetTextAreaOnTextContentScroll(ArkUINodeHandle node, void* extraParam);
    void SetTextAreaOnSubmit(ArkUINodeHandle node, void* extraParam);
    void SetOnTextAreaWillChange(ArkUINodeHandle node, void* extraParam);

    void ResetOnTextAreaChange(ArkUINodeHandle node);
    void ResetOnTextAreaChangeWithPreviewText(ArkUINodeHandle node);
    void ResetOnTextAreaPaste(ArkUINodeHandle node);
    void ResetOnTextAreaSelectionChange(ArkUINodeHandle node);
    void ResetOnTextAreaEditChange(ArkUINodeHandle node);
    void ResetOnTextAreaContentSizeChange(ArkUINodeHandle node);
    void ResetOnTextAreaInputFilterError(ArkUINodeHandle node);
    void ResetTextAreaOnTextContentScroll(ArkUINodeHandle node);
    void ResetTextAreaOnSubmit(ArkUINodeHandle node);
    void ResetOnTextAreaWillChange(ArkUINodeHandle node);
    void SetTextAreaOnWillInsertValue(ArkUINodeHandle node, void* extraParam);
    void SetTextAreaOnDidInsertValue(ArkUINodeHandle node, void* extraParam);
    void SetTextAreaOnWillDeleteValue(ArkUINodeHandle node, void* extraParam);
    void SetTextAreaOnDidDeleteValue(ArkUINodeHandle node, void* extraParam);
} // namespace OHOS::Ace::NG::NodeModifier
#endif