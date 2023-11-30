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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_pattern_lock_modifier.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_CIRCLE_RADIUS_API9 = 14.0_vp;
constexpr Dimension DEFAULT_CIRCLE_RADIUS = 6.0_vp;
constexpr double DEFAULT_SIDE_LENGTH_NUMBER = 288.0f;
constexpr double DEFAULT_SIDE_LENGTH_NUMBER_API9 = 300.0f;
static constexpr Dimension DEFAULT_PATH_STROKE_WIDTH_API9 = 34.0_vp;
static constexpr Dimension DEFAULT_PATH_STROKE_WIDTH = 12.0_vp;

void SetPatternLockActiveColor(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
}

void ResetPatternLockActiveColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        PatternLockModelNG::SetActiveColor(frameNode, Color::BLACK);
    } else {
        PatternLockModelNG::SetActiveColor(frameNode, Color::FromString("#ff182431"));
    }
}

void ResetPatternLockCircleRadius(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        PatternLockModelNG::SetCircleRadius(frameNode, DEFAULT_CIRCLE_RADIUS);
    } else {
        PatternLockModelNG::SetCircleRadius(frameNode, DEFAULT_CIRCLE_RADIUS_API9);
    }
}

void SetPatternLockCircleRadius(NodeHandle node, const struct StringAndDouble *value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension radius;
    if (value->valueStr != nullptr) {
        radius = StringUtils::StringToCalcDimension(value->valueStr, false, DimensionUnit::VP);
    } else {
        radius = CalcDimension(value->value, DimensionUnit::VP);
    }

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (radius.IsNonNegative()) {
            PatternLockModelNG::SetCircleRadius(frameNode, radius);
        }
    } else {
        if (radius.IsNonPositive()) {
            ResetPatternLockCircleRadius(frameNode);
        } else {
            PatternLockModelNG::SetCircleRadius(frameNode, radius);
        }
    }
}

void SetPatternLockSelectedColor(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
}

void ResetPatternLockSelectedColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        PatternLockModelNG::SetSelectedColor(frameNode, Color::BLACK);
    } else {
        PatternLockModelNG::SetSelectedColor(frameNode, Color::FromString("#ff182431"));
    }
}

void SetPatternLockSideLength(NodeHandle node, double number, int8_t unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockSideLength(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension sideLength(DEFAULT_SIDE_LENGTH_NUMBER, DimensionUnit::VP);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetMinPlatformVersion() < static_cast<int32_t>(PlatformVersion::VERSION_TEN)) {
        sideLength.SetValue(DEFAULT_SIDE_LENGTH_NUMBER_API9);
    }
    PatternLockModelNG::SetSideLength(frameNode, Dimension(sideLength.Value(), sideLength.Unit()));
}

void SetPatternLockAutoReset(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, static_cast<bool>(value));
}

void ResetPatternLockAutoReset(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, true);
}

void SetPatternLockPathStrokeWidth(NodeHandle node, const struct StringAndDouble *pathStrokeWidthStruct)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension pathStrokeWidth;
    if (pathStrokeWidthStruct->value == -1) {
        auto pipeline = PipelineBase::GetCurrentContext();
        if (pipeline->GetMinPlatformVersion() < static_cast<int32_t>(PlatformVersion::VERSION_TEN)) {
            pathStrokeWidth = DEFAULT_PATH_STROKE_WIDTH_API9;
        } else {
            pathStrokeWidth = DEFAULT_PATH_STROKE_WIDTH;
        }
    } else if (pathStrokeWidthStruct->valueStr != nullptr) {
        pathStrokeWidth =
            StringUtils::StringToCalcDimension(std::string(pathStrokeWidthStruct->valueStr), false, DimensionUnit::VP);
        PatternLockModelNG::SetStrokeWidth(frameNode, pathStrokeWidth);
    } else {
        pathStrokeWidth = CalcDimension(pathStrokeWidthStruct->value, DimensionUnit::VP);
        PatternLockModelNG::SetStrokeWidth(frameNode, pathStrokeWidth);
    }
}

void ResetPatternLockPathStrokeWidth(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension pathStrokeWidth;
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline->GetMinPlatformVersion() < static_cast<int32_t>(PlatformVersion::VERSION_TEN)) {
        pathStrokeWidth = DEFAULT_PATH_STROKE_WIDTH_API9;
    } else {
        pathStrokeWidth = DEFAULT_PATH_STROKE_WIDTH;
    }
    PatternLockModelNG::SetStrokeWidth(frameNode, pathStrokeWidth);
}

void SetPatternLockRegularColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
}

void ResetPatternLockRegularColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        PatternLockModelNG::SetRegularColor(frameNode, Color::BLACK);
    } else {
        PatternLockModelNG::SetRegularColor(frameNode, Color::FromString("#ff182431"));
    }
}

void SetPatternLockPathColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
}

void ResetPatternLockPathColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        PatternLockModelNG::SetPathColor(frameNode, Color::BLUE);
    } else {
        PatternLockModelNG::SetPathColor(frameNode, Color::FromString("#33182431"));
    }
}

ArkUIPatternLockModifierAPI GetPatternLockModifier()
{
    static const ArkUIPatternLockModifierAPI modifier = {
        SetPatternLockActiveColor, ResetPatternLockActiveColor, SetPatternLockCircleRadius,
        ResetPatternLockCircleRadius, SetPatternLockSelectedColor, ResetPatternLockSelectedColor,
        SetPatternLockSideLength, ResetPatternLockSideLength, SetPatternLockAutoReset,
        ResetPatternLockAutoReset, SetPatternLockPathStrokeWidth, ResetPatternLockPathStrokeWidth,
        SetPatternLockRegularColor, ResetPatternLockRegularColor, SetPatternLockPathColor,
        ResetPatternLockPathColor
    };
    return modifier;
}
} // namespace OHOS::Ace::NG