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
#include "core/interfaces/native/node/node_text_area_modifier.h"

#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const ArkUITextAreaModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextArea");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUITextAreaModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUITextAreaModifier* GetCJUITextAreaModifier()
{
    static const CJUITextAreaModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextArea");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUITextAreaModifier*>(module->GetCjModifier());
    }
    return cachedModifier;
}

const ArkUITextAreaCustomModifier* GetTextAreaCustomModifier()
{
    static const ArkUITextAreaCustomModifier* cachedCustomModifier = nullptr;
    if (cachedCustomModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TextArea");
        CHECK_NULL_RETURN(module, nullptr);
        cachedCustomModifier = reinterpret_cast<const ArkUITextAreaCustomModifier*>(module->GetCustomModifier());
    }
    return cachedCustomModifier;
}

#define TEXT_AREA_MODIFIER_CALL(field, ...)            \
    do {                                               \
        auto* modifier = GetTextAreaModifier();        \
        if (modifier) {                                \
            modifier->field(__VA_ARGS__);              \
        }                                              \
    } while (false)

void SetOnTextAreaEditChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaEditChange, node, extraParam);
}

void SetOnTextAreaChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaChange, node, extraParam);
}

void SetOnTextAreaPaste(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaPaste, node, extraParam);
}

void SetOnTextAreaSelectionChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaSelectionChange, node, extraParam);
}

void SetTextAreaOnSubmit(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnSubmit, node, extraParam);
}

void SetOnTextAreaContentSizeChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaContentSizeChange, node, extraParam);
}

void SetOnTextAreaInputFilterError(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaInputFilterError, node, extraParam);
}

void SetTextAreaOnTextContentScroll(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnTextContentScroll, node, extraParam);
}

void SetTextAreaOnWillInsertValue(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnWillInsertValue, node, extraParam);
}

void SetTextAreaOnDidInsertValue(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnDidInsertValue, node, extraParam);
}

void SetTextAreaOnWillDeleteValue(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnWillDeleteValue, node, extraParam);
}

void SetTextAreaOnDidDeleteValue(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setTextAreaOnDidDeleteValue, node, extraParam);
}

void SetOnTextAreaChangeWithPreviewText(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaChangeWithPreviewText, node, extraParam);
}

void SetOnTextAreaWillChange(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaWillChange, node, extraParam);
}

void SetOnTextAreaCopy(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaCopy, node, extraParam);
}

void SetOnTextAreaWillCopy(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaWillCopy, node, extraParam);
}

void SetOnTextAreaCut(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaCut, node, extraParam);
}

void SetOnTextAreaWillCut(ArkUINodeHandle node, void* extraParam)
{
    TEXT_AREA_MODIFIER_CALL(setOnTextAreaWillCut, node, extraParam);
}

void ResetOnTextAreaEditChange(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaEditChange, node);
}

void ResetOnTextAreaChange(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaChange, node);
}

void ResetOnTextAreaPaste(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaPaste, node);
}

void ResetOnTextAreaSelectionChange(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaSelectionChange, node);
}

void ResetTextAreaOnSubmit(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetTextAreaOnSubmit, node);
}

void ResetOnTextAreaContentSizeChange(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaContentSizeChange, node);
}

void ResetOnTextAreaInputFilterError(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaInputFilterError, node);
}

void ResetTextAreaOnTextContentScroll(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetTextAreaOnTextContentScroll, node);
}

void ResetOnTextAreaChangeWithPreviewText(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaChangeWithPreviewText, node);
}

void ResetOnTextAreaWillChange(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaWillChange, node);
}

void ResetOnTextAreaCopy(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaCopy, node);
}

void ResetOnTextAreaWillCopy(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaWillCopy, node);
}

void ResetOnTextAreaCut(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaCut, node);
}

void ResetOnTextAreaWillCut(ArkUINodeHandle node)
{
    TEXT_AREA_MODIFIER_CALL(resetOnTextAreaWillCut, node);
}

#undef TEXT_AREA_MODIFIER_CALL
}
}
