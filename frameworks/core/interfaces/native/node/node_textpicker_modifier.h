/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TEXT_PICKER_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TEXT_PICKER_MODIFIER_H

#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUITextPickerModifier* GetTextPickerModifier();
const CJUITextPickerModifier* GetCJUITextPickerModifier();
void GetPickerTextStyle(uint32_t color, const char* fontInfo, int32_t styleVal, NG::PickerTextStyle& textStyle);
void SetSelectedIndexSingle(FrameNode* frameNode, uint32_t* selectedValues, const int32_t size);
void SetSelectedIndexMulti(FrameNode* frameNode, uint32_t* selectedValues, const int32_t size);
void SetSelectedIndexMultiInternal(FrameNode* frameNode, uint32_t count,
    std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues);
void SetSelectedIndexSingleInternal(const std::vector<NG::TextCascadePickerOptions>& options, uint32_t count,
    uint32_t& selectedValue, std::vector<uint32_t>& selectedValues);
void SetSelectedInternal(
    uint32_t count, std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues);
void ProcessCascadeSelected(
    const std::vector<NG::TextCascadePickerOptions>& options, uint32_t index, std::vector<uint32_t>& selectedValues);
void SetTextPickerOnChange(ArkUINodeHandle node, void* extraParam);
void SetTextPickerOnScrollStop(ArkUINodeHandle node, void* extraParam);
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_TEXT_PICKER_MODIFIER_H
