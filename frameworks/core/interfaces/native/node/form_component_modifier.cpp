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

#include "core/interfaces/native/node/form_component_modifier.h"

#include "core/components_ng/pattern/form/form_model_ng.h"

namespace OHOS::Ace::NG {
const int32_t DEFAULT_VISIBILITY = 0;
const int32_t DEFAULT_FORM_DIM = 1;
const bool DEFAULT_ALLOW_UPDATE = true;
void SetFormVisibility(ArkUINodeHandle node, ArkUI_Int32 visible)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType visibility = static_cast<VisibleType>(visible);
    FormModelNG::SetVisibility(frameNode, visibility);
}

void AllowUpdate(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::AllowUpdate(frameNode, value);
}

void SetDimension(ArkUINodeHandle node, ArkUI_Int32 dimension)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetDimension(frameNode, dimension);
}

void SetModuleName(ArkUINodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string moduleName(value);
    FormModelNG::SetModuleName(frameNode, moduleName);
}

void SetFormSize(ArkUINodeHandle node, ArkUI_Float32 widthValue, ArkUI_Int32 widthUnit,
    ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetSize(frameNode,
        Dimension(widthValue, static_cast<OHOS::Ace::DimensionUnit>(widthUnit)),
        Dimension(heightValue, static_cast<OHOS::Ace::DimensionUnit>(heightUnit)));
}

void ResetFormVisibility(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType visibility = static_cast<VisibleType>(DEFAULT_VISIBILITY);
    FormModelNG::SetVisibility(frameNode, visibility);
}

void DisallowUpdate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::AllowUpdate(frameNode, DEFAULT_ALLOW_UPDATE);
}

void ResetDimension(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetDimension(frameNode, DEFAULT_FORM_DIM);
}

void ResetModuleName(ArkUINodeHandle node) {}

void ResetFormSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = 0.0_vp;
    Dimension height = 0.0_vp;
    FormModelNG::SetSize(frameNode, width, height);
}

namespace NodeModifier {
const ArkUIFormComponentModifier* GetFormComponentModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIFormComponentModifier modifier = {
        .setFormVisibility = SetFormVisibility,
        .allowUpdate = AllowUpdate,
        .setDimension = SetDimension,
        .setModuleName = SetModuleName,
        .setFormSize = SetFormSize,
        .resetFormVisibility = ResetFormVisibility,
        .disallowUpdate = DisallowUpdate,
        .resetDimension = ResetDimension,
        .resetModuleName = ResetModuleName,
        .resetFormSize = ResetFormSize,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIFormComponentModifier* GetCJUIFormComponentModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIFormComponentModifier modifier = {
        .setFormVisibility = SetFormVisibility,
        .allowUpdate = AllowUpdate,
        .setDimension = SetDimension,
        .setModuleName = SetModuleName,
        .setFormSize = SetFormSize,
        .resetFormVisibility = ResetFormVisibility,
        .disallowUpdate = DisallowUpdate,
        .resetDimension = ResetDimension,
        .resetModuleName = ResetModuleName,
        .resetFormSize = ResetFormSize,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
