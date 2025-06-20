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
#include "core/interfaces/native/node/blank_modifier.h"

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
void SetColor(ArkUINodeHandle node, ArkUI_Uint32 value, void* colorRawPtr)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::ResetResObj(frameNode, "blank.color");
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        BlankModelNG::SetColor(frameNode, colorResObj);
    } else {
        BlankModelNG::SetColor(frameNode, Color(value));
    }
}

void ResetColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::ResetResObj(frameNode, "blank.color");
    BlankModelNG::SetColor(frameNode, Color::TRANSPARENT);
}

void SetBlankHeight(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetHeight(frameNode, CalcDimension(heightValue, (DimensionUnit)heightUnit));
}

void ResetBlankHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetBlankMin(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(minValue, (DimensionUnit)minUnit));
}

void ResetBlankMin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(0.0, DimensionUnit::VP));
}

namespace NodeModifier {
const ArkUIBlankModifier* GetBlankModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIBlankModifier modifier = {
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIBlankModifier* GetCJUIBlankModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIBlankModifier modifier = {
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
}
