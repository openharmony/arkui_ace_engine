/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_container_span_modifier.h"

#include "core/components_ng/pattern/text/span_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;

void SetContainerSpanTextBackgroundStyle(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length,
    void* style)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    if (SystemProperties::ConfigChangePerform() && style) {
        auto textBackgroundStyle = reinterpret_cast<TextBackgroundStyle*>(style);
        SpanModelNG::SetTextBackgroundStyleByBaseSpan(uiNode, *textBackgroundStyle);
        return;
    }
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    font.backgroundColor = Color(color);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    SpanModelNG::SetTextBackgroundStyleByBaseSpan(uiNode, font);
}

void ResetContainerSpanTextBackgroundStyle(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    TextBackgroundStyle font;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(0, OHOS::Ace::DimensionUnit::VP);
    font.backgroundColor = Color(0x00000000);
    font.backgroundRadius = borderRadius;
    font.backgroundRadius->multiValued = true;
    SpanModelNG::SetTextBackgroundStyleByBaseSpan(uiNode, font);
}

} // namespace

namespace NodeModifier {
const ArkUIContainerSpanModifier* GetContainerSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIContainerSpanModifier modifier = {
        .setContainerSpanTextBackgroundStyle = SetContainerSpanTextBackgroundStyle,
        .resetContainerSpanTextBackgroundStyle = ResetContainerSpanTextBackgroundStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIContainerSpanModifier* GetCJUIContainerSpanModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIContainerSpanModifier modifier = {
        .setContainerSpanTextBackgroundStyle = SetContainerSpanTextBackgroundStyle,
        .resetContainerSpanTextBackgroundStyle = ResetContainerSpanTextBackgroundStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
