/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/common_text/text_border_utils.h"

#include <optional>
#include "base/utils/utils.h"
#include "base/utils/system_properties.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int DEFAULT_LENGTH = 4;
} // namespace

BorderStyle ConvertBorderStyle(int32_t value)
{
    auto style = static_cast<BorderStyle>(value);
    if (style < BorderStyle::SOLID || style > BorderStyle::NONE) {
        style = BorderStyle::SOLID;
    }
    return style;
}

void ParseBorderColor(NG::BorderColorProperty& borderColors, const RefPtr<ResourceObject>& topResObj,
    const RefPtr<ResourceObject>& rightResObj, const RefPtr<ResourceObject>& bottomResObj,
    const RefPtr<ResourceObject>& leftResObj)
{
    borderColors.resMap_.clear();
    if (topResObj != nullptr) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.topColor = result;
        };
        borderColors.AddResource("borderColor.top", topResObj, std::move(updateFunc));
    }
    if (rightResObj != nullptr) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.rightColor = result;
        };
        borderColors.AddResource("borderColor.right", rightResObj, std::move(updateFunc));
    }
    if (bottomResObj != nullptr) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.bottomColor = result;
        };
        borderColors.AddResource("borderColor.bottom", bottomResObj, std::move(updateFunc));
    }
    if (leftResObj != nullptr) {
        auto&& updateFunc = [](const RefPtr<ResourceObject>& resObj, NG::BorderColorProperty& borderColors) {
            Color result;
            ResourceParseUtils::ParseResColor(resObj, result);
            borderColors.leftColor = result;
        };
        borderColors.AddResource("borderColor.left", leftResObj, std::move(updateFunc));
    }
}

void SetBorderWidthCommon(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length, SetBorderWidthFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    std::optional<CalcDimension> topDimen;
    std::optional<CalcDimension> rightDimen;
    std::optional<CalcDimension> bottomDimen;
    std::optional<CalcDimension> leftDimen;
    if (values[NUM_0] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]) != OHOS::Ace::DimensionUnit::INVALID) {
        topDimen = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    }
    if (values[NUM_1] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]) != OHOS::Ace::DimensionUnit::INVALID) {
        rightDimen = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    }
    if (values[NUM_2] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]) != OHOS::Ace::DimensionUnit::INVALID) {
        bottomDimen = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    }
    if (values[NUM_3] != -1 &&
        static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]) != OHOS::Ace::DimensionUnit::INVALID) {
        leftDimen = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    }
    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = leftDimen;
    borderWidth.rightDimen = rightDimen;
    borderWidth.topDimen = topDimen;
    borderWidth.bottomDimen = bottomDimen;
    borderWidth.multiValued = true;
    setFunc(frameNode, borderWidth);
}

void ResetBorderWidthCommon(ArkUINodeHandle node, SetBorderWidthFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(0));
    setFunc(frameNode, borderWidth);
}

void SetBorderColorCommon(ArkUINodeHandle node, const ArkUI_Uint32* colors,
    void* res, SetBorderColorFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::ResetResObj(frameNode, "borderColor");
    NG::BorderColorProperty borderColors;
    borderColors.topColor = Color(colors[NUM_0]);
    borderColors.rightColor = Color(colors[NUM_1]);
    borderColors.bottomColor = Color(colors[NUM_2]);
    borderColors.leftColor = Color(colors[NUM_3]);
    borderColors.multiValued = true;
    if (SystemProperties::ConfigChangePerform()) {
        std::vector<RefPtr<ResourceObject>> objs;
        if (res) {
            objs = *(reinterpret_cast<const std::vector<RefPtr<ResourceObject>>*>(res));
        }
        if (objs.empty()) {
            objs.resize(DEFAULT_LENGTH);
            NG::NodeInfo nodeInfo = ResourceParseUtils::MakeNativeNodeInfo(frameNode);
            ResourceParseUtils::CompleteResourceObjectFromColor(objs[NUM_0],
                borderColors.topColor.value(), nodeInfo);
            ResourceParseUtils::CompleteResourceObjectFromColor(objs[NUM_1],
                borderColors.rightColor.value(), nodeInfo);
            ResourceParseUtils::CompleteResourceObjectFromColor(objs[NUM_2],
                borderColors.bottomColor.value(), nodeInfo);
            ResourceParseUtils::CompleteResourceObjectFromColor(objs[NUM_3],
                borderColors.leftColor.value(), nodeInfo);
        }
        ParseBorderColor(borderColors, objs[NUM_0], objs[NUM_1], objs[NUM_2], objs[NUM_3]);
    }
    setFunc(frameNode, borderColors);
}

void ResetBorderColorCommon(ArkUINodeHandle node, SetBorderColorFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::ResetResObj(frameNode, "borderColor");
    NG::BorderColorProperty borderColors;
    borderColors.SetColor(Color::BLACK);
    setFunc(frameNode, borderColors);
}

void SetBorderStyleCommon(ArkUINodeHandle node, const ArkUI_Int32* styles,
    ArkUI_Int32 length, SetBorderStyleFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == NUM_1) {
        NG::BorderStyleProperty borderStyle;
        borderStyle.SetBorderStyle(ConvertBorderStyle(styles[NUM_0]));
        setFunc(frameNode, borderStyle);
        return;
    }
    if (length == DEFAULT_LENGTH) {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = ConvertBorderStyle(styles[NUM_3]);
        borderStyles.styleRight = ConvertBorderStyle(styles[NUM_1]);
        borderStyles.styleTop = ConvertBorderStyle(styles[NUM_0]);
        borderStyles.styleBottom = ConvertBorderStyle(styles[NUM_2]);
        borderStyles.multiValued = true;
        setFunc(frameNode, borderStyles);
    }
}

void ResetBorderStyleCommon(ArkUINodeHandle node, SetBorderStyleFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderStyleProperty borderStyles;
    borderStyles.SetBorderStyle(BorderStyle::SOLID);
    setFunc(frameNode, borderStyles);
}

void SetBorderRadiusCommon(ArkUINodeHandle node, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length, SetBorderRadiusFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != DEFAULT_LENGTH) {
        return;
    }
    NG::BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(values[NUM_0], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_0]));
    borderRadius.radiusTopRight = Dimension(values[NUM_1], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_1]));
    borderRadius.radiusBottomLeft = Dimension(values[NUM_2], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_2]));
    borderRadius.radiusBottomRight = Dimension(values[NUM_3], static_cast<OHOS::Ace::DimensionUnit>(units[NUM_3]));
    borderRadius.multiValued = true;
    setFunc(frameNode, borderRadius);
}

void ResetBorderRadiusCommon(ArkUINodeHandle node, SetBorderRadiusFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(Dimension(0));
    setFunc(frameNode, borderRadius);
}

} // namespace OHOS::Ace
