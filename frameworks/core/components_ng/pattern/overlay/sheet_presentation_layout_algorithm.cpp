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

#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_HALF_SIZE = 2;
} // namespace

void SheetPresentationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    sheetStyle_ = layoutProperty->GetSheetStyleValue();
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (!layoutConstraint) {
        LOGE("fail to measure sheet due to layoutConstraint is nullptr");
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto maxSize = layoutConstraint->maxSize;
    if (layoutWrapper->GetGeometryNode() && layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()) {
        auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
        layoutConstraint = parentConstraint.value();
        layoutProperty->UpdateLayoutConstraint(layoutConstraint.value());
        maxSize = layoutConstraint->maxSize;
        sheetMaxHeight_ = maxSize.Height();
        sheetMaxWidth_ = maxSize.Width();
        sheetWidth_ = GetWidthByScreenSizeType(maxSize);
        sheetHeight_ = GetHeightByScreenSizeType(maxSize);
        SizeF idealSize(sheetWidth_, sheetHeight_);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
        layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
        auto childConstraint = CreateSheetChildConstraint(layoutProperty);
        layoutConstraint->percentReference = SizeF(sheetWidth_, sheetHeight_);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Measure(childConstraint);
        }
        if ((sheetType_ == SheetType::SHEET_CENTER || sheetType_ == SheetType::SHEET_POPUP)
            && (sheetStyle_.sheetMode.value_or(SheetMode::LARGE) == SheetMode::AUTO)) {
            auto&& children = layoutWrapper->GetAllChildrenWithBuild();
            auto secondIter = std::next(children.begin(), 1);
            auto secondChild = *secondIter;
            CHECK_NULL_VOID(secondChild);
            auto&& scrollChild = secondChild->GetAllChildrenWithBuild();
            auto builder = scrollChild.front();
            CHECK_NULL_VOID(builder);
            auto operatoration = children.front();
            CHECK_NULL_VOID(operatoration);
            auto operatorGeometryNode = operatoration->GetGeometryNode();
            CHECK_NULL_VOID(operatorGeometryNode);
            auto builderGeometryNode = builder->GetGeometryNode();
            CHECK_NULL_VOID(builderGeometryNode);
            sheetHeight_ =
                operatorGeometryNode->GetFrameSize().Height() + builderGeometryNode->GetFrameSize().Height();
            auto maxHeight = std::min(sheetMaxHeight_, sheetMaxWidth_) * POPUP_LARGE_SIZE;
            if (sheetHeight_ > maxHeight) {
                sheetHeight_ = maxHeight;
            } else if (sheetHeight_ < 0.0f) {
                sheetHeight_ = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
            } else if (sheetHeight_ < SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()) {
                sheetHeight_ = SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx();
            }
            SizeF idealSize(sheetWidth_, sheetHeight_);
            layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
            childConstraint.maxSize.SetWidth(sheetWidth_);
            childConstraint.maxSize.SetHeight(sheetHeight_);
        }
    }
}

void SheetPresentationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    if (sheetType_ == SheetType::SHEET_BOTTOMLANDSPACE) {
        sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / SHEET_HALF_SIZE;
    } else if (sheetType_ == SheetType::SHEET_CENTER) {
        sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / SHEET_HALF_SIZE;
    } else if (sheetType_ == SheetType::SHEET_POPUP) {
        auto frameNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(frameNode);
        auto parent = DynamicCast<FrameNode>(frameNode->GetParent());
        CHECK_NULL_VOID(parent);
        auto parentOffset = parent->GetPaintRectOffset();
        OffsetF popupStyleSheetOffset = GetPopupStyleSheetOffset();
        sheetOffsetX_ = popupStyleSheetOffset.GetX() - parentOffset.GetX();
        sheetOffsetY_ = popupStyleSheetOffset.GetY() - parentOffset.GetY();
    }
    OffsetF positionOffset;
    positionOffset.SetX(sheetOffsetX_);
    positionOffset.SetY(sheetOffsetY_);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(positionOffset);
    OffsetF translate(0.0f, 0.0f);
    if (sheetType_ == SheetType::SHEET_POPUP) {
        translate += OffsetF(0, SHEET_ARROW_HEIGHT.ConvertToPx());
    }
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
        child->Layout();
        translate += OffsetF(0, child->GetGeometryNode()->GetFrameSize().Height());
    }
}

OffsetF SheetPresentationLayoutAlgorithm::GetPopupStyleSheetOffset()
{
    OffsetF sheetOffset;
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_RETURN(targetNode, OffsetF());
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, OffsetF());
    auto targetSize = geometryNode->GetFrameSize();
    auto targetOffset = targetNode->GetPaintRectOffset();
    auto targetSpace = SHEET_TARGET_SPACE.ConvertToPx();
    float offsetX = targetOffset.GetX() + (targetSize.Width() - sheetWidth_) / SHEET_HALF_SIZE;
    float offsetY = targetOffset.GetY() + targetSize.Height() + targetSpace;
    sheetOffset.SetX(offsetX);
    sheetOffset.SetY(offsetY);
    return sheetOffset;
}

float SheetPresentationLayoutAlgorithm::GetHeightByScreenSizeType(const SizeF& maxSize) const
{
    float height = maxSize.Height();
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOMPC:
        case SheetType::SHEET_BOTTOMLANDSPACE:
            height = maxSize.Height();
            break;
        case SheetType::SHEET_CENTER:
            height = GetHeightBySheetStyle();
            break;
        case SheetType::SHEET_POPUP:
            height = GetHeightBySheetStyle() + SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        default:
            break;
    }

    return height;
}

float SheetPresentationLayoutAlgorithm::GetWidthByScreenSizeType(const SizeF& maxSize) const
{
    float width = maxSize.Width();
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOMPC:
            width = maxSize.Width();
            break;
        case SheetType::SHEET_BOTTOMLANDSPACE:
        case SheetType::SHEET_CENTER:
            width = SHEET_LANDSCAPE_WIDTH.ConvertToPx();
            break;
        case SheetType::SHEET_POPUP:
            width = SHEET_POPUP_WIDTH.ConvertToPx();
            break;
        default:
            break;
    }
    return width;
}

float SheetPresentationLayoutAlgorithm::GetHeightBySheetStyle() const
{
    float height = 0.0f;
    if (sheetStyle_.height.has_value()) {
        auto maxHeight = std::min(sheetMaxHeight_, sheetMaxWidth_) * POPUP_LARGE_SIZE;
        if (sheetStyle_.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle_.height->ConvertToPxWithSize(maxHeight);
        } else {
            height = sheetStyle_.height->ConvertToPx();
        }
        if (height > maxHeight) {
            height = maxHeight;
        } else if (height < 0.0f) {
            height = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
        } else if (height < SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()) {
            height = SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx();
        }
    } else {
        height = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
    }
    return height;
}

LayoutConstraintF SheetPresentationLayoutAlgorithm::CreateSheetChildConstraint(
    RefPtr<SheetPresentationProperty> layoutprop)
{
    auto childConstraint = layoutprop->CreateChildConstraint();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, childConstraint);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_RETURN(sheetTheme, childConstraint);

    childConstraint.maxSize.SetWidth(sheetWidth_);
    auto maxHeight = sheetHeight_;
    if ((sheetStyle_.isTitleBuilder.has_value()) &&
        ((sheetType_ == SheetType::SHEET_CENTER) || (sheetType_ == SheetType::SHEET_POPUP))) {
        maxHeight -= SHEET_OPERATION_AREA_HEIGHT.ConvertToPx();
    }
    childConstraint.maxSize.SetHeight(maxHeight);
    childConstraint.parentIdealSize = OptionalSizeF(sheetWidth_, sheetHeight_);
    childConstraint.percentReference = SizeF(sheetWidth_, sheetHeight_);
    return childConstraint;
}
} // namespace OHOS::Ace::NG