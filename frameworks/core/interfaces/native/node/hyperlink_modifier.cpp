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

#include "core/interfaces/native/node/hyperlink_modifier.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
} // namespace
void SetHyperlinkColor(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetColor(frameNode, Color(color));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        pattern->RegisterResource<Color>("Color", resObj, Color(color));
    } else {
        pattern->UnRegisterResource("Color");
    }
}

void ResetHyperlinkColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto hyperlinkTheme = themeManager->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(hyperlinkTheme);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    pattern->UnRegisterResource("Color");
    HyperlinkModelNG::SetColor(frameNode, Color(hyperlinkTheme->GetTextColor()));
}

void SetHyperlinkDraggable(ArkUINodeHandle node, ArkUI_Bool draggable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, draggable);
}

void ResetHyperlinkDraggable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HyperlinkModelNG::SetDraggable(frameNode, false);
}

void SetHyperlinkResponseRegion(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (int32_t i = 0; i < length / NUM_4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * NUM_4 + NUM_0], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_0]));
        CalcDimension yDimen =
            CalcDimension(values[i * NUM_4 + NUM_1], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_1]));
        CalcDimension widthDimen =
            CalcDimension(values[i * NUM_4 + NUM_2], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i * NUM_4 + NUM_3], static_cast<DimensionUnit>(units[i * NUM_4 + NUM_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    HyperlinkModelNG::SetResponseRegion(frameNode, region, true);
}

void ResetHyperlinkResponseRegion(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    HyperlinkModelNG::SetResponseRegion(frameNode, region, false);
}

namespace NodeModifier {
const ArkUIHyperlinkModifier* GetHyperlinkModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIHyperlinkModifier modifier = {
        .setHyperlinkColor = SetHyperlinkColor,
        .resetHyperlinkColor = ResetHyperlinkColor,
        .setHyperlinkDraggable = SetHyperlinkDraggable,
        .resetHyperlinkDraggable = ResetHyperlinkDraggable,
        .setHyperlinkResponseRegion = SetHyperlinkResponseRegion,
        .resetHyperlinkResponseRegion = ResetHyperlinkResponseRegion,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIHyperlinkModifier* GetCJUIHyperlinkModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIHyperlinkModifier modifier = {
        .setHyperlinkColor = SetHyperlinkColor,
        .resetHyperlinkColor = ResetHyperlinkColor,
        .setHyperlinkDraggable = SetHyperlinkDraggable,
        .resetHyperlinkDraggable = ResetHyperlinkDraggable,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
