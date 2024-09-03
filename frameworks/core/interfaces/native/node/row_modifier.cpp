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
#include "core/interfaces/native/node/row_modifier.h"

#include "core/components_ng/pattern/linear_layout/row_model_ng.h"

namespace OHOS::Ace::NG {
constexpr FlexAlign DEFAULT_ROW_JUSTIFY_CONTENT = FlexAlign::FLEX_START;
constexpr FlexAlign DEFAULT_ROW_ALIGN_ITEMS = FlexAlign::CENTER;
const int32_t ERROR_INT_CODE = -1;

void SetRowJustifyContent(ArkUINodeHandle node, int32_t flexAlign)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetJustifyContent(frameNode, static_cast<FlexAlign>(flexAlign));
}

void ResetRowJustifyContent(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetJustifyContent(frameNode, DEFAULT_ROW_JUSTIFY_CONTENT);
}

void SetRowAlignItems(ArkUINodeHandle node, int32_t verticalAlign)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetAlignItems(frameNode, static_cast<FlexAlign>(verticalAlign));
}

void ResetRowAlignItems(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetAlignItems(frameNode, DEFAULT_ROW_ALIGN_ITEMS);
}

ArkUI_Int32 GetRowJustifyContent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RowModelNG::GetJustifyContent(frameNode));
}

ArkUI_Int32 GetRowAlignItems(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(RowModelNG::GetAlignItems(frameNode));
}

void SetRowSpace(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto space = CalcDimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    RowModelNG::SetSpace(frameNode, space);
}

void ResetRowSpace(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto space = CalcDimension(0.0, DimensionUnit::PX);
    RowModelNG::SetSpace(frameNode, space);
}

void SetRowReverse(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetIsReverse(frameNode, value);
}

void ResetRowReverse(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RowModelNG::SetIsReverse(frameNode, false);
}

namespace NodeModifier {
const ArkUIRowModifier* GetRowModifier()
{
    static const ArkUIRowModifier modifier = {
        SetRowJustifyContent, ResetRowJustifyContent, SetRowAlignItems,
        ResetRowAlignItems, GetRowJustifyContent, GetRowAlignItems,
        SetRowSpace, ResetRowSpace,
        SetRowReverse,
        ResetRowReverse,
    };
    return &modifier;
}

const CJUIRowModifier* GetCJUIRowModifier()
{
    static const CJUIRowModifier modifier = {
        SetRowJustifyContent, ResetRowJustifyContent, SetRowAlignItems,
        ResetRowAlignItems, GetRowJustifyContent, GetRowAlignItems,
        SetRowSpace, ResetRowSpace,
    };
    return &modifier;
}
}
}