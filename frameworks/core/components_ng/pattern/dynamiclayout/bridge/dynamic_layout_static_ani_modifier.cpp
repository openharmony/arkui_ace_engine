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
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/dynamiclayout/algorithm_param_base.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_model_ng.h"
#include "core/components_ng/pattern/dynamiclayout/dynamic_layout_node.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/interfaces/ani/ani_api.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"
#include "core/components/common/properties/alignment.h"
#include "core/common/container.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr inline int32_t TOP_LEFT = 0;
constexpr inline int32_t TOP_CENTER = 1;
constexpr inline int32_t TOP_RIGHT = 2;
constexpr inline int32_t CENTER_LEFT = 3;
constexpr inline int32_t CENTER = 4;
constexpr inline int32_t CENTER_RIGHT = 5;
constexpr inline int32_t BOTTOM_LEFT = 6;
constexpr inline int32_t BOTTOM_CENTER = 7;
constexpr inline int32_t BOTTOM_RIGHT = 8;

constexpr inline int32_t FLEX_START = 0;
constexpr inline int32_t FLEX_CENTER = 1;
constexpr inline int32_t FLEX_END = 2;
constexpr inline int32_t SPACE_BETWEEN = 3;
constexpr inline int32_t SPACE_AROUND = 4;
constexpr inline int32_t SPACE_EVENLY = 5;

OHOS::Ace::Alignment ConvertLocalizedAlignmentToAlignment(ArkUI_Int32 ordinal)
{
    switch (ordinal) {
        case TOP_LEFT: return OHOS::Ace::Alignment::TOP_LEFT;
        case TOP_CENTER: return OHOS::Ace::Alignment::TOP_CENTER;
        case TOP_RIGHT: return OHOS::Ace::Alignment::TOP_RIGHT;
        case CENTER_LEFT: return OHOS::Ace::Alignment::CENTER_LEFT;
        case CENTER: return OHOS::Ace::Alignment::CENTER;
        case CENTER_RIGHT: return OHOS::Ace::Alignment::CENTER_RIGHT;
        case BOTTOM_LEFT: return OHOS::Ace::Alignment::BOTTOM_LEFT;
        case BOTTOM_CENTER: return OHOS::Ace::Alignment::BOTTOM_CENTER;
        case BOTTOM_RIGHT: return OHOS::Ace::Alignment::BOTTOM_RIGHT;
        default: return OHOS::Ace::Alignment::CENTER;
    }
}

FlexAlign ConvertMainAxisAlign(ArkUI_Int32 ordinal)
{
    switch (ordinal) {
        case FLEX_START: return FlexAlign::FLEX_START;
        case FLEX_CENTER: return FlexAlign::CENTER;
        case FLEX_END: return FlexAlign::FLEX_END;
        case SPACE_BETWEEN: return FlexAlign::SPACE_BETWEEN;
        case SPACE_AROUND: return FlexAlign::SPACE_AROUND;
        case SPACE_EVENLY: return FlexAlign::SPACE_EVENLY;
        default: return FlexAlign::FLEX_START;
    }
}

FlexAlign ConvertCrossAxisAlign(ArkUI_Int32 ordinal)
{
    switch (ordinal) {
        case FLEX_START: return FlexAlign::FLEX_START;
        case FLEX_CENTER: return FlexAlign::CENTER;
        case FLEX_END: return FlexAlign::FLEX_END;
        default: return FlexAlign::CENTER;
    }
}

CalcDimension ConvertLengthMetricsToDimension(const ArkUILayoutAlgorithmLengthMetrics& metrics)
{
    if (metrics.isResource) {
        std::vector<ResourceObjectParams> params;
        auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
            metrics.resource.resId, metrics.resource.resType, params, metrics.resource.bundleName,
            metrics.resource.moduleName, Container::CurrentIdSafely());
        CalcDimension dimension;
        if (ResourceParseUtils::ParseResDimensionVpNG(resourceObject, dimension) && !dimension.IsNegative()) {
            return dimension;
        }
        return CalcDimension(0, DimensionUnit::VP);
    }
    auto unit = static_cast<OHOS::Ace::DimensionUnit>(metrics.unit);
    auto value = metrics.value;
    if (Negative(value)) {
        return CalcDimension(0, DimensionUnit::VP);
    }
    if (unit == OHOS::Ace::DimensionUnit::PERCENT) {
        value /= 100.0f;
    }
    return Dimension(value, unit);
}
}

bool SetDynamicLayoutStackOptions(ArkUINodeHandle node, ArkUIStackLayoutAlgorithm algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto stackParams =
        AceType::MakeRefPtr<StackLayoutAlgorithmParam>(ConvertLocalizedAlignmentToAlignment(algorithm.alignContent));
    DynamicLayoutModelNG::SetParams(AceType::Claim(frameNode), stackParams, DynamicLayoutType::STACK_LAYOUT);
    return true;
}

bool SetDynamicLayoutRowOptions(ArkUINodeHandle node, ArkUIRowLayoutAlgorithm algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(false);
    linearParams->SetSpace(ConvertLengthMetricsToDimension(algorithm.space));
    linearParams->SetMainAxisAlign(ConvertMainAxisAlign(algorithm.justifyContent));
    linearParams->SetCrossAxisAlign(ConvertCrossAxisAlign(algorithm.alignItems));
    linearParams->SetIsReverse(static_cast<bool>(algorithm.isReverse));
    DynamicLayoutModelNG::SetParams(AceType::Claim(frameNode), linearParams, DynamicLayoutType::ROW_LAYOUT);
    return true;
}

bool SetDynamicLayoutColumnOptions(ArkUINodeHandle node, ArkUIColumnLayoutAlgorithm algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto linearParams = AceType::MakeRefPtr<LinearLayoutAlgorithmParam>(true);
    linearParams->SetSpace(ConvertLengthMetricsToDimension(algorithm.space));
    linearParams->SetMainAxisAlign(ConvertMainAxisAlign(algorithm.justifyContent));
    linearParams->SetCrossAxisAlign(ConvertCrossAxisAlign(algorithm.alignItems));
    linearParams->SetIsReverse(static_cast<bool>(algorithm.isReverse));
    DynamicLayoutModelNG::SetParams(AceType::Claim(frameNode), linearParams, DynamicLayoutType::COLUMN_LAYOUT);
    return true;
}

bool SetDynamicLayoutCustomOptions(ArkUINodeHandle node, const ArkUICustomLayoutAlgorithm& algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto customParams = AceType::MakeRefPtr<CustomLayoutAlgorithmParam>();
    if (algorithm.onMeasureFunc) {
        auto onMeasureFunc = [fn = algorithm.onMeasureFunc](LayoutWrapper* layoutWrapper) {
            // Create LayoutConstraint
            CHECK_NULL_VOID(layoutWrapper);
            const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
            CHECK_NULL_VOID(layoutProperty);
            auto layoutConstraint = layoutProperty->GetLayoutConstraint().value_or(
                OHOS::Ace::NG::LayoutConstraintF());
            fn(layoutConstraint);
        };
        customParams->SetOnMeasureSize(std::move(onMeasureFunc));
    }
    if (algorithm.onPlaceChildrenFunc) {
        auto onPlaceChildrenFunc = [fn = algorithm.onPlaceChildrenFunc](LayoutWrapper* layoutWrapper) {
            CHECK_NULL_VOID(layoutWrapper);
            auto rect = layoutWrapper->GetGeometryNode()->GetFrameRect();
            OHOS::Ace::NG::OffsetF offset(rect.GetX(), rect.GetY());
            fn(offset);
        };
        customParams->SetOnPlaceChildren(std::move(onPlaceChildrenFunc));
    }
    DynamicLayoutModelNG::SetParams(AceType::Claim(frameNode), customParams, DynamicLayoutType::CUSTOM_LAYOUT);
    return true;
}

ArkUINodeHandle DynamicLayoutConstructImpl(ArkUI_Int32 id, ArkUI_Int32 flags)
{
    auto [frameNode, _] = DynamicLayoutNode::GetOrCreateDynamicLayoutNode("DynamicLayout", id, []() {
        return AceType::MakeRefPtr<StackPattern>();
    });
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

PresetFillType ConvertItemFillPolicy(ArkUI_Int32 ordinal)
{
    switch (ordinal) {
        case 0: return PresetFillType::BREAKPOINT_DEFAULT;
        case 1: return PresetFillType::BREAKPOINT_SM1MD2LG3;
        case 2: return PresetFillType::BREAKPOINT_SM2MD3LG5;
        default: return PresetFillType::BREAKPOINT_DEFAULT;
    }
}

bool SetDynamicLayoutGridOptions(ArkUINodeHandle node, ArkUIGridLayoutAlgorithm algorithm)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto gridParams = AceType::MakeRefPtr<GridLayoutAlgorithmParam>();
    if (algorithm.columnsTemplate != nullptr && algorithm.columnsTemplate[0] != '\0') {
        gridParams->SetColumnsTemplate(algorithm.columnsTemplate);
    }
    if (algorithm.itemFillPolicy >= 0) {
        gridParams->SetItemFillPolicy(ConvertItemFillPolicy(algorithm.itemFillPolicy));
    }
    gridParams->SetRowsGap(ConvertLengthMetricsToDimension(algorithm.rowsGap));
    gridParams->SetColumnsGap(ConvertLengthMetricsToDimension(algorithm.columnsGap));
    DynamicLayoutModelNG::SetParams(AceType::Claim(frameNode), gridParams, DynamicLayoutType::GRID_LAYOUT);
    return true;
}

const ArkUIAniDynamicLayoutModifier* GetArkUIAniDynamicLayoutModifier()
{
    static const ArkUIAniDynamicLayoutModifier impl = {
        .construct = OHOS::Ace::NG::DynamicLayoutConstructImpl,
        .setDynamicLayoutStackOptions = OHOS::Ace::NG::SetDynamicLayoutStackOptions,
        .setDynamicLayoutRowOptions = OHOS::Ace::NG::SetDynamicLayoutRowOptions,
        .setDynamicLayoutColumnOptions = OHOS::Ace::NG::SetDynamicLayoutColumnOptions,
        .setDynamicLayoutCustomOptions = OHOS::Ace::NG::SetDynamicLayoutCustomOptions,
        .setDynamicLayoutGridOptions = OHOS::Ace::NG::SetDynamicLayoutGridOptions,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG
