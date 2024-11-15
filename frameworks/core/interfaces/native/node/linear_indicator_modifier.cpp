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
#include "core/interfaces/native/node/linear_indicator_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_model_ng.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_theme.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

void SetLinearIndicatorIndicatorStyleSpace(ArkUINodeHandle node, ArkUI_Float32 space, ArkUI_Int32 unit)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetIndicatorStyleSpace(
        frameNode, CalcDimension(space, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetLinearIndicatorIndicatorStyleSpace(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    LinearIndicatorModelNG::SetIndicatorStyleSpace(frameNode, linearIndicatorTheme->GetDefaultSpace());
}

void SetLinearIndicatorIndicatorStyleStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 strokeWidth, ArkUI_Int32 unit)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetIndicatorStyleStrokeWidth(
        frameNode, CalcDimension(strokeWidth, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetLinearIndicatorIndicatorStyleStrokeWidth(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    LinearIndicatorModelNG::SetIndicatorStyleStrokeWidth(frameNode, linearIndicatorTheme->GetDefaultStrokeWidth());
}

void SetLinearIndicatorIndicatorStyleStrokeRadius(ArkUINodeHandle node, ArkUI_Float32 strokeRadius, ArkUI_Int32 unit)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetIndicatorStyleStrokeRadius(
        frameNode, CalcDimension(strokeRadius, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void ResetLinearIndicatorIndicatorStyleStrokeRadius(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    LinearIndicatorModelNG::SetIndicatorStyleStrokeRadius(frameNode, linearIndicatorTheme->GetDefaultStrokeRadius());
}

void SetLinearIndicatorIndicatorStyleTrackBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 trackBackgroundColor)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetIndicatorStyleTrackBackgroundColor(frameNode, Color(trackBackgroundColor));
}

void ResetLinearIndicatorIndicatorStyleTrackBackgroundColor(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    Color color = linearIndicatorTheme->GetTrackBackgroundColor();
    LinearIndicatorModelNG::SetIndicatorStyleTrackBackgroundColor(frameNode, color);
}

void SetLinearIndicatorIndicatorStyleTrackColor(ArkUINodeHandle node, ArkUI_Uint32 trackColor)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetIndicatorStyleTrackColor(frameNode, Color(trackColor));
}

void ResetLinearIndicatorIndicatorStyleTrackColor(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    Color color = linearIndicatorTheme->GetTrackColor();
    LinearIndicatorModelNG::SetIndicatorStyleTrackColor(frameNode, color);
}

void SetLinearIndicatorIndicatorLoop(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetLoop(frameNode, static_cast<bool>(value));
}

void ResetLinearIndicatorIndicatorLoop(ArkUINodeHandle node)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto linearIndicatorTheme = pipeline->GetTheme<LinearIndicatorTheme>();
    CHECK_NULL_VOID(linearIndicatorTheme);
    LinearIndicatorModelNG::SetLoop(frameNode, linearIndicatorTheme->GetDefaultLoop());
}

void SetLinearIndicatorOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int index, float progress)>*>(callback);
        LinearIndicatorModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        LinearIndicatorModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetLinearIndicatorOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    LinearIndicatorModelNG::SetOnChange(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUILinearIndicatorModifier* GetLinearIndicatorModifier()
{
    static const ArkUILinearIndicatorModifier modifier = { SetLinearIndicatorIndicatorStyleSpace,
        ResetLinearIndicatorIndicatorStyleSpace, SetLinearIndicatorIndicatorStyleStrokeWidth,
        ResetLinearIndicatorIndicatorStyleStrokeWidth, SetLinearIndicatorIndicatorStyleStrokeRadius,
        ResetLinearIndicatorIndicatorStyleStrokeRadius, SetLinearIndicatorIndicatorStyleTrackBackgroundColor,
        ResetLinearIndicatorIndicatorStyleTrackBackgroundColor, SetLinearIndicatorIndicatorStyleTrackColor,
        ResetLinearIndicatorIndicatorStyleTrackColor, SetLinearIndicatorIndicatorLoop,
        ResetLinearIndicatorIndicatorLoop, SetLinearIndicatorOnChange, ResetLinearIndicatorOnChange };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
