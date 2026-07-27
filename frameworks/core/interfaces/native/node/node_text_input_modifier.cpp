/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_text_input_modifier.h"
 
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUITextInputModifier* GetTextInputModifier()
{
    static const ArkUITextInputModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextInput");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITextInputModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUITextInputModifier* GetCJUITextInputModifier()
{
    static const CJUITextInputModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextInput");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUITextInputModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}
const ArkUITextInputCustomModifier* GetTextInputCustomModifier()
{
    static const ArkUITextInputCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextInput");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITextInputCustomModifier*>(module->GetCustomModifier());
    }
    return cachedModifier;
}

#define TEXT_INPUT_MODIFIER_CALL(field, ...)            \
    do {                                                \
        auto* modifier = GetTextInputModifier();        \
        if (modifier) {                                 \
            modifier->field(__VA_ARGS__);               \
        }                                               \
    } while (false)

void SetOnTextInputChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputChange, node, extraParam);
}

void SetOnTextInputChangeWithPreviewText(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputChangeWithPreviewText, node, extraParam);
}

void SetTextInputOnSubmit(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnSubmit, node, extraParam);
}

void SetOnTextInputCut(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputCut, node, extraParam);
}

void SetOnTextInputPaste(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputPaste, node, extraParam);
}

void SetOnTextInputSelectionChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputSelectionChange, node, extraParam);
}

void SetOnTextInputEditChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputEditChange, node, extraParam);
}

void SetOnTextInputContentSizeChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputContentSizeChange, node, extraParam);
}

void SetOnTextInputInputFilterError(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputInputFilterError, node, extraParam);
}

void SetTextInputOnTextContentScroll(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnTextContentScroll, node, extraParam);
}

void SetOnTextInputWillChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputWillChange, node, extraParam);
}

void SetTextInputOnWillInsert(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnWillInsert, node, extraParam);
}

void SetTextInputOnDidInsert(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnDidInsert, node, extraParam);
}

void SetTextInputOnWillDelete(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnWillDelete, node, extraParam);
}

void SetTextInputOnDidDelete(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setTextInputOnDidDelete, node, extraParam);
}

void SetOnTextInputWillCopy(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputWillCopy, node, extraParam);
}

void SetOnTextInputCopy(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputCopy, node, extraParam);
}

void SetOnTextInputWillCut(ArkUINodeHandle node, void* extraParam)
{
    TEXT_INPUT_MODIFIER_CALL(setOnTextInputWillCut, node, extraParam);
}

void ResetOnTextInputChange(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputChange, node);
}

void ResetOnTextInputChangeWithPreviewText(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputChangeWithPreviewText, node);
}

void ResetTextInputOnSubmit(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetTextInputOnSubmit, node);
}

void ResetOnTextInputCut(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputCut, node);
}

void ResetOnTextInputPaste(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputPaste, node);
}

void ResetOnTextInputSelectionChange(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputSelectionChange, node);
}

void ResetOnTextInputEditChange(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputEditChange, node);
}

void ResetOnTextInputContentSizeChange(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputContentSizeChange, node);
}

void ResetOnTextInputInputFilterError(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputInputFilterError, node);
}

void ResetTextInputOnTextContentScroll(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetTextInputOnTextContentScroll, node);
}

void ResetOnTextInputWillChange(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputWillChange, node);
}

void ResetOnTextInputWillCopy(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputWillCopy, node);
}

void ResetOnTextInputCopy(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputCopy, node);
}

void ResetOnTextInputWillCut(ArkUINodeHandle node)
{
    TEXT_INPUT_MODIFIER_CALL(resetOnTextInputWillCut, node);
}

#undef TEXT_INPUT_MODIFIER_CALL
}
}
