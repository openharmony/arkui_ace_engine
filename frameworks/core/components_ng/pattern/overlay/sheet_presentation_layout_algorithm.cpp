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

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SHEET_HALF_SIZE = 2;
constexpr Dimension WINDOW_EDGE_SPACE = 6.0_vp;
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
std::map<Placement, std::vector<Placement>> DIRECTIONS_STATES = {
    { Placement::BOTTOM,
        {
            Placement::BOTTOM,
        } },
};
std::map<Placement, std::vector<Placement>> PLACEMENT_STATES = {
    { Placement::BOTTOM,
        {
            Placement::BOTTOM,
            Placement::BOTTOM_RIGHT,
            Placement::BOTTOM_LEFT,
        } },
};
} // namespace

void SheetPresentationLayoutAlgorithm::InitParameter()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    sheetRadius_ = sheetTheme->GetSheetRadius().ConvertToPx();
}

void SheetPresentationLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    sheetStyle_ = layoutProperty->GetSheetStyleValue();
    auto layoutConstraint = layoutProperty->GetLayoutConstraint();
    if (!layoutConstraint) {
        TAG_LOGE(AceLogTag::ACE_SHEET, "fail to measure sheet due to layoutConstraint is nullptr");
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
        sheetWidth_ = GetWidthByScreenSizeType(maxSize, layoutWrapper);
        sheetHeight_ = GetHeightByScreenSizeType(maxSize);
        if (sheetStyle_.width.has_value()) {
            float width = 0.0f;
            if (sheetStyle_.width->Unit() == DimensionUnit::PERCENT) {
                width = sheetStyle_.width->ConvertToPxWithSize(maxSize.Width());
            } else {
                width = sheetStyle_.width->ConvertToPx();
            }
            if (width > maxSize.Width() || width < 0.0f) {
                width = sheetWidth_;
            }
            sheetWidth_ = width;
        }
        SizeF idealSize(sheetWidth_, sheetHeight_);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
        layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
        auto childConstraint = CreateSheetChildConstraint(layoutProperty);
        layoutConstraint->percentReference = SizeF(sheetWidth_, sheetHeight_);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Measure(childConstraint);
        }
        auto scrollNode = layoutWrapper->GetChildByIndex(1);
        CHECK_NULL_VOID(scrollNode);
        childConstraint.selfIdealSize.SetWidth(childConstraint.maxSize.Width());
        scrollNode->Measure(childConstraint);
        if ((sheetType_ == SheetType::SHEET_CENTER || sheetType_ == SheetType::SHEET_POPUP ||
            (sheetType_ == SheetType::SHEET_BOTTOM_OFFSET))
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
            float sheetMaxHeight = sheetMaxHeight_;
            if (SheetInSplitWindow()) {
                auto pipelineContext = PipelineContext::GetCurrentContext();
                auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
                sheetMaxHeight = windowGlobalRect.Height() - SHEET_SPLIT_STATUS_BAR.ConvertToPx()-
                    SHEET_SPLIT_AI_BAR.ConvertToPx();
            }
            auto maxHeight = std::min(sheetMaxHeight, sheetMaxWidth_) * POPUP_LARGE_SIZE;
            maxHeight = SheetInSplitWindow()
                ? maxHeight : std::max(maxHeight, static_cast<float>(SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()));
            if (LessNotEqual(sheetHeight_, 0.0f)) {
                sheetHeight_ = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
            } else if (LessOrEqual(sheetHeight_, SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()) && !SheetInSplitWindow()) {
                sheetHeight_ = SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx();
            } else if (GreatOrEqual(sheetHeight_, maxHeight)) {
                sheetHeight_ = maxHeight;
            }
            SizeF idealSize(sheetWidth_, sheetHeight_);
            layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
            childConstraint.maxSize.SetWidth(sheetWidth_);
            childConstraint.maxSize.SetHeight(sheetHeight_);
            secondChild->Measure(childConstraint);
        }
    }
}

void SheetPresentationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    const auto& pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / SHEET_HALF_SIZE;
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
        // need to subtract the SheetWrapper relative to the upper left corner of the window,
        // which is the offset of the upper left corner of the bubble relative to the SheetWrapper
        sheetOffsetX_ = popupStyleSheetOffset.GetX() - parentOffset.GetX();
        sheetOffsetY_ = popupStyleSheetOffset.GetY() - parentOffset.GetY();
    } else if (sheetType_ == SheetType::SHEET_BOTTOM_OFFSET) {
        sheetOffsetY_ = (sheetMaxHeight_ - sheetHeight_ + sheetStyle_.bottomOffset->GetY());
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet layout info, sheetOffsetX_ is: %{public}f, sheetOffsetY_ is: %{public}f",
        sheetOffsetX_, sheetOffsetY_);
    OffsetF positionOffset;
    positionOffset.SetX(sheetOffsetX_);
    positionOffset.SetY(0.0f);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    // This step is only to determine the position of x, because y is to be done by the bit movement effect
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

// Get the offset of the popupSheet relative to the upper left corner of the window
OffsetF SheetPresentationLayoutAlgorithm::GetPopupStyleSheetOffset()
{
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_RETURN(targetNode, OffsetF());
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, OffsetF());
    auto targetSize = geometryNode->GetFrameSize();
    auto targetOffset = targetNode->GetPaintRectOffset();
    return GetOffsetInAvoidanceRule(targetSize, targetOffset);
}

OffsetF SheetPresentationLayoutAlgorithm::GetOffsetInAvoidanceRule(const SizeF& targetSize, const OffsetF& targetOffset)
{
    // The current default Placement is Placement::BOTTOM
    auto placement = Placement::BOTTOM;
    auto targetPlacement = AvoidanceRuleOfPlacement(placement, targetSize, targetOffset);
    if (getOffsetFunc_.find(targetPlacement) == getOffsetFunc_.end()) {
        TAG_LOGW(AceLogTag::ACE_SHEET, "It is an invalid Placement for current PopSheet.");
        return {};
    }
    auto offsetFunc = getOffsetFunc_[targetPlacement];
    CHECK_NULL_RETURN(offsetFunc, OffsetF());
    return (this->*offsetFunc)(targetSize, targetOffset);
}

Placement SheetPresentationLayoutAlgorithm::AvoidanceRuleOfPlacement(
    const Placement& currentPlacement, const SizeF& targetSize, const OffsetF& targetOffset)
{
    Placement targetPlacement = currentPlacement;
    TAG_LOGD(AceLogTag::ACE_SHEET, "Init PopupSheet placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(targetPlacement).c_str());
    // Step1: Determine the direction
    auto& directionVec = DIRECTIONS_STATES[targetPlacement];
    for (auto placement : directionVec) {
        auto& placementFunc = directionCheckFunc_[placement];
        if (placementFunc == nullptr) {
            continue;
        }
        if ((this->*placementFunc)(targetSize, targetOffset)) {
            targetPlacement = placement;
            break;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "After step1, placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(targetPlacement).c_str());
    // Step2: Determine the Placement in that direction
    auto& placementVec = PLACEMENT_STATES[targetPlacement];
    for (auto placement : placementVec) {
        auto& placementFunc = placementCheckFunc_[placement];
        if (placementFunc == nullptr) {
            continue;
        }
        if ((this->*placementFunc)(targetSize, targetOffset)) {
            targetPlacement = placement;
            break;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "After step2, placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(targetPlacement).c_str());
    return targetPlacement;
}

bool SheetPresentationLayoutAlgorithm::CheckDirectionBottom(const SizeF& targetSize, const OffsetF& targetOffset)
{
    // Generalized bottom direction,
    // determine whether the space below the component is enough to place the sheet of size
    return true;
}

bool SheetPresentationLayoutAlgorithm::CheckPlacementBottom(const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    return GreatOrEqual(
        windowGlobalRect.Width() - WINDOW_EDGE_SPACE.ConvertToPx(),
        targetOffset.GetX() + targetSize.Width() / SHEET_HALF_SIZE + sheetWidth_ / SHEET_HALF_SIZE) &&
        LessOrEqual(
            WINDOW_EDGE_SPACE.ConvertToPx(),
            targetOffset.GetX() + targetSize.Width() / SHEET_HALF_SIZE - sheetWidth_ / SHEET_HALF_SIZE);
}

bool SheetPresentationLayoutAlgorithm::CheckPlacementBottomLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    return LessOrEqual(WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX()) &&
           GreatOrEqual(windowGlobalRect.Width() - WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + sheetWidth_);
}

bool SheetPresentationLayoutAlgorithm::CheckPlacementBottomRight(const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    return LessOrEqual(WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + targetSize.Width() - sheetWidth_) &&
           GreatOrEqual(
               windowGlobalRect.Width() - WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + targetSize.Width());
}

OffsetF SheetPresentationLayoutAlgorithm::GetOffsetWithBottom(const SizeF& targetSize, const OffsetF& targetOffset)
{
    arrowOffsetX_ = sheetWidth_ / SHEET_HALF_SIZE;
    return OffsetF(targetOffset.GetX() + (targetSize.Width() - sheetWidth_) / SHEET_HALF_SIZE,
        targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());
}

OffsetF SheetPresentationLayoutAlgorithm::GetOffsetWithBottomLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    arrowOffsetX_ = targetSize.Width() / SHEET_HALF_SIZE;
    auto sheetOffset =
        OffsetF(targetOffset.GetX(), targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());

    // if the arrow overlaps the sheet left corner, move sheet to the 6vp from the left edge
    if (LessNotEqual(arrowOffsetX_ - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), sheetRadius_)) {
        sheetOffset.SetX(WINDOW_EDGE_SPACE.ConvertToPx());
        arrowOffsetX_ = targetOffset.GetX() + targetSize.Width() / SHEET_HALF_SIZE - sheetOffset.GetX();
        TAG_LOGD(AceLogTag::ACE_SHEET, "Adjust sheet to the left boundary of the screen");
    }

    // if the arrow still overlaps the sheet left corner, the arrow will become a right angle.
    if (LessNotEqual(arrowOffsetX_ - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(), sheetRadius_)) {
        isRightAngleArrow_ = true;
        TAG_LOGD(AceLogTag::ACE_SHEET, "Need to switch the arrow into the right-angle arrow");
    }
    return sheetOffset;
}

OffsetF SheetPresentationLayoutAlgorithm::GetOffsetWithBottomRight(const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    arrowOffsetX_ = sheetWidth_ - targetSize.Width() / SHEET_HALF_SIZE;
    auto sheetOffset = OffsetF(targetOffset.GetX() + targetSize.Width() - sheetWidth_,
        targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());

    // if the arrow overlaps the sheet right corner, move sheet to the 6vp from the right edge
    if (GreatNotEqual(arrowOffsetX_ + sheetRadius_ + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), sheetWidth_)) {
        sheetOffset.SetX(windowGlobalRect.Width() - WINDOW_EDGE_SPACE.ConvertToPx() - sheetWidth_);
        arrowOffsetX_ = targetOffset.GetX() + targetSize.Width() / SHEET_HALF_SIZE - sheetOffset.GetX();
        TAG_LOGD(AceLogTag::ACE_SHEET, "Adjust sheet to the right boundary of the screen");
    }

    // if the arrow still overlaps the sheet right corner, the arrow will become a right angle.
    if (GreatNotEqual(arrowOffsetX_ + sheetRadius_ + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), sheetWidth_)) {
        isRightAngleArrow_ = true;
        TAG_LOGD(AceLogTag::ACE_SHEET, "Need to switch the arrow into the right angle arrow");
    }
    return sheetOffset;
}

float SheetPresentationLayoutAlgorithm::GetHeightByScreenSizeType(const SizeF& maxSize) const
{
    float height = maxSize.Height();
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
        case SheetType::SHEET_BOTTOMLANDSPACE:
            height = maxSize.Height();
            break;
        case SheetType::SHEET_BOTTOM_OFFSET:
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

float SheetPresentationLayoutAlgorithm::GetWidthByScreenSizeType(const SizeF& maxSize,
    LayoutWrapper* layoutWrapper) const
{
    float width = maxSize.Width();
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, width);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, width);
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
            if (sheetPattern->IsPhoneInLandScape()) {
                width = std::min(static_cast<float>(SHEET_LANDSCAPE_WIDTH.ConvertToPx()), maxSize.Width());
                break;
            }
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
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
    bool isMediumOrLargeMode = false;
    if (sheetStyle_.sheetMode == SheetMode::MEDIUM || sheetStyle_.sheetMode == SheetMode::LARGE) {
        isMediumOrLargeMode =  true;
    }
    if (sheetStyle_.height.has_value() || isMediumOrLargeMode) {
        float sheetMaxHeight = sheetMaxHeight_;
        if (SheetInSplitWindow()) {
            sheetMaxHeight = sheetMaxHeight_ - SHEET_SPLIT_STATUS_BAR.ConvertToPx()-
                SHEET_SPLIT_AI_BAR.ConvertToPx();
        }
        auto maxHeight = std::min(sheetMaxHeight, sheetMaxWidth_) * POPUP_LARGE_SIZE;
        if (sheetStyle_.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle_.height->ConvertToPxWithSize(maxHeight);
        } else if (isMediumOrLargeMode) {
            height = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
        } else {
            height = sheetStyle_.height->ConvertToPx();
        }
        maxHeight = SheetInSplitWindow()
            ? maxHeight : std::max(maxHeight, static_cast<float>(SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()));
        if (LessNotEqual(height, 0.0f)) {
            height = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
        } else if (LessOrEqual(height, SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx()) && !SheetInSplitWindow()) {
            height = SHEET_BIG_WINDOW_MIN_HEIGHT.ConvertToPx();
        } else if (GreatOrEqual(height, maxHeight)) {
            height = maxHeight;
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

bool SheetPresentationLayoutAlgorithm::SheetInSplitWindow() const
{
    //whether window in up and down split mode
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto windowManager = pipelineContext->GetWindowManager();
    auto windowGlobalRect = pipelineContext->GetDisplayWindowRectInfo();
    int32_t deviceHeight = SystemProperties::GetDeviceHeight();
    if (sheetType_ == SheetType::SHEET_CENTER && windowManager && windowGlobalRect.Height() < deviceHeight &&
        (windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
        windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_SPLIT_SECONDARY)) {
        return true;
    }
    return false;
}
} // namespace OHOS::Ace::NG