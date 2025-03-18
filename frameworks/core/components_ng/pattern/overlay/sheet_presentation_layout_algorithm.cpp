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
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DOUBLE_SIZE = 2;
} // namespace

void SheetPresentationLayoutAlgorithm::InitParameter()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    // if 2in1, enableHoverMode is true by default.
    auto enableHoverMode = sheetStyle_.enableHoverMode.value_or(sheetTheme->IsOuterBorderEnable() ? true : false);
    hoverModeArea_ = sheetStyle_.hoverModeArea.value_or(
        sheetTheme->IsOuterBorderEnable() ? HoverModeAreaType::TOP_SCREEN : HoverModeAreaType::BOTTOM_SCREEN);
    auto safeAreaManager = pipeline->GetSafeAreaManager();
    auto keyboardInsert = safeAreaManager->GetKeyboardInset();
    isKeyBoardShow_ = keyboardInsert.IsValid();
    isHoverMode_ = enableHoverMode ? pipeline->IsHalfFoldHoverStatus() : false;
}

void SheetPresentationLayoutAlgorithm::CalculateSheetHeightInOtherScenes(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto foldCreaseRect = sheetPattern->GetFoldScreenRect();
    if (sheetType_ == SheetType::SHEET_CENTER && isHoverMode_) {
        float upScreenHeight = foldCreaseRect.Top() - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx();
        float downScreenHeight = sheetMaxHeight_ - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - foldCreaseRect.Bottom();
        TAG_LOGD(AceLogTag::ACE_SHEET, "upScreenHeight: %{public}f, downScreenHeight: %{public}f.", upScreenHeight,
            downScreenHeight);
        sheetHeight_ = std::min(sheetHeight_,
            (hoverModeArea_ == HoverModeAreaType::TOP_SCREEN || isKeyBoardShow_) ? upScreenHeight : downScreenHeight);
    }
}

void SheetPresentationLayoutAlgorithm::CalculateSheetOffsetInOtherScenes(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto foldCreaseRect = sheetPattern->GetFoldScreenRect();
    auto frameSizeHeight = geometryNode->GetFrameSize().Height();
    if (sheetType_ == SheetType::SHEET_CENTER && isHoverMode_) {
        float upScreenHeight = foldCreaseRect.Top() - SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx();
        float downScreenHeight = sheetMaxHeight_ - SHEET_HOVERMODE_DOWN_HEIGHT.ConvertToPx() - foldCreaseRect.Bottom();
        sheetOffsetY_ = (hoverModeArea_ == HoverModeAreaType::TOP_SCREEN || isKeyBoardShow_)
                            ? (SHEET_HOVERMODE_UP_HEIGHT.ConvertToPx() +
                                  (upScreenHeight - frameSizeHeight) / DOUBLE_SIZE)
                            : (foldCreaseRect.Bottom() + (downScreenHeight - frameSizeHeight) / DOUBLE_SIZE);
    }
}

void SheetPresentationLayoutAlgorithm::ComputeWidthAndHeight(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
    LayoutConstraintF layoutConstraint = parentConstraint.value();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    auto maxSize = layoutConstraint.maxSize;
    sheetMaxHeight_ = maxSize.Height();
    sheetMaxWidth_ = maxSize.Width();
    auto showInSubWindow = sheetStyle_.showInSubWindow.value_or(false);
    auto parentHeightConstraint = sheetMaxHeight_;
    auto parentWidthConstraint = sheetMaxWidth_;
    if (showInSubWindow) {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto sheetWrapper = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(sheetWrapper);
        auto sheetWrapperPattern = sheetWrapper->GetPattern<SheetWrapperPattern>();
        CHECK_NULL_VOID(sheetWrapperPattern);
        auto mainWindowRect = sheetWrapperPattern->GetMainWindowRect();
        parentHeightConstraint = mainWindowRect.Height();
        parentWidthConstraint = mainWindowRect.Width();
    }
    sheetWidth_ = GetWidthByScreenSizeType(parentWidthConstraint, layoutWrapper);
    sheetHeight_ = GetHeightByScreenSizeType(parentHeightConstraint, parentWidthConstraint, layoutWrapper);
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
    InitParameter();
    if (layoutWrapper->GetGeometryNode() && layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()) {
        ComputeWidthAndHeight(layoutWrapper);
        CalculateSheetHeightInOtherScenes(layoutWrapper);
        AddArrowHeightToSheetSize();
        SizeF idealSize(sheetWidth_, sheetHeight_);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
        layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
        auto childConstraint = CreateSheetChildConstraint(layoutProperty, layoutWrapper);
        layoutConstraint->percentReference = SizeF(sheetWidth_, sheetHeight_);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Measure(childConstraint);
        }
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        auto scrollNode = sheetPattern->GetSheetScrollNode();
        CHECK_NULL_VOID(scrollNode);
        childConstraint.selfIdealSize.SetWidth(childConstraint.maxSize.Width());
        scrollNode->Measure(childConstraint);
        if ((sheetType_ == SheetType::SHEET_CENTER || sheetType_ == SheetType::SHEET_POPUP ||
            (sheetType_ == SheetType::SHEET_BOTTOM_OFFSET))
            && (sheetStyle_.sheetHeight.sheetMode.value_or(SheetMode::LARGE) == SheetMode::AUTO)) {
            auto&& children = layoutWrapper->GetAllChildrenWithBuild();
            auto secondChild = AceType::DynamicCast<LayoutWrapper>(scrollNode);
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
            childConstraint = CreateSheetChildConstraint(layoutProperty, layoutWrapper);
            secondChild->Measure(childConstraint);
        }
    }
}

void SheetPresentationLayoutAlgorithm::ComputeCenterStyleOffset(LayoutWrapper* layoutWrapper)
{
    auto showInSubWindow = sheetStyle_.showInSubWindow.value_or(false);
    if (!showInSubWindow) {
        sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / DOUBLE_SIZE;
        return;
    }
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapper = AceType::DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(sheetWrapper);
    auto sheetWrapperPattern = sheetWrapper->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto mainWindowRect = sheetWrapperPattern->GetMainWindowRect();
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetFrameSize = geometryNode->GetFrameSize();

    // compute sheet offset when show in subwindow
    RectF containerModal;
    RectF buttonsRect;
    auto hostWindowId = SubwindowManager::GetInstance()->GetParentContainerId(sheetWrapperPattern->GetSubWindowId());
    ContainerScope scope(hostWindowId);
    auto container = AceEngine::Get().GetContainer(hostWindowId);
    CHECK_NULL_VOID(container);
    auto mainWindowContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    sheetOffsetY_ = mainWindowRect.GetY() + mainWindowRect.Height() / DOUBLE_SIZE
        - sheetFrameSize.Height() / DOUBLE_SIZE;
    if (mainWindowContext && mainWindowContext->GetContainerModalButtonsRect(containerModal, buttonsRect)) {
        sheetOffsetY_ += buttonsRect.Height() / DOUBLE_SIZE;
        if (LessOrEqual(sheetOffsetY_, mainWindowRect.GetY() + buttonsRect.Height())) {
            sheetOffsetY_ = mainWindowRect.GetY() + buttonsRect.Height();
        }
    }
    sheetOffsetX_ = mainWindowRect.GetX() + (mainWindowRect.Width()  - sheetFrameSize.Width()) / DOUBLE_SIZE;
    std::vector<Rect> rects;
    auto rect = Rect(sheetOffsetX_, sheetOffsetY_,
        sheetFrameSize.Width(), sheetFrameSize.Height());
    rects.emplace_back(rect);
    SubwindowManager::GetInstance()->SetHotAreas(rects, SubwindowType::TYPE_SHEET,
        host->GetId(), sheetWrapperPattern->GetSubWindowId());
}

void SheetPresentationLayoutAlgorithm::ComputePopupStyleOffset(LayoutWrapper* layoutWrapper)
{
    sheetOffsetX_ = sheetPopupInfo_.sheetOffsetX;
    sheetOffsetY_ = sheetPopupInfo_.sheetOffsetY;
    auto showInSubWindow = sheetStyle_.showInSubWindow.value_or(false);
    if (showInSubWindow) {
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto sheetWrapper = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(sheetWrapper);
        auto sheetWrapperPattern = sheetWrapper->GetPattern<SheetWrapperPattern>();
        CHECK_NULL_VOID(sheetWrapperPattern);
        if (sheetWrapperPattern->ShowInUEC()) {
            auto UECId = SubwindowManager::GetInstance()->GetParentContainerId(sheetWrapperPattern->GetSubWindowId());
            auto container = AceEngine::Get().GetContainer(UECId);
            CHECK_NULL_VOID(container);
            auto mainWindowContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            auto UECWindowGlobalRect = mainWindowContext->GetDisplayWindowRectInfo();
            sheetOffsetX_ += UECWindowGlobalRect.Left();
            sheetOffsetY_ += UECWindowGlobalRect.Top();
        } else {
            auto mainWindowRect = sheetWrapperPattern->GetMainWindowRect();
            sheetOffsetX_ += mainWindowRect.GetX();
            sheetOffsetY_ += mainWindowRect.GetY();
        }
        std::vector<Rect> rects;
        auto rect = Rect(sheetOffsetX_, sheetOffsetY_,
            host->GetGeometryNode()->GetFrameSize().Width(), host->GetGeometryNode()->GetFrameSize().Height());
        rects.emplace_back(rect);
        auto subWindowMgr = SubwindowManager::GetInstance();
        subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_SHEET, host->GetId(),
            sheetWrapperPattern->GetSubWindowId());
    }
}

void SheetPresentationLayoutAlgorithm::LayoutTitleBuilder(const NG::OffsetF& translate,
    LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto titleBuilderNode = sheetPattern->GetTitleBuilderNode();
    CHECK_NULL_VOID(titleBuilderNode);
    auto index = host->GetChildIndexById(titleBuilderNode->GetId());
    auto titleBuilderWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(titleBuilderWrapper);
    auto geometryNode = titleBuilderWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(translate);
    titleBuilderWrapper->Layout();
}

void SheetPresentationLayoutAlgorithm::LayoutCloseIcon(const NG::OffsetF& translate,
    LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetCloseNode = sheetPattern->GetSheetCloseIcon();
    CHECK_NULL_VOID(sheetCloseNode);
    auto index = host->GetChildIndexById(sheetCloseNode->GetId());
    auto closeIconWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(closeIconWrapper);
    auto geometryNode = closeIconWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto sheetGeometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    auto closeIconX = sheetGeometryNode->GetFrameSize().Width() -
                      static_cast<float>(SHEET_CLOSE_ICON_WIDTH.ConvertToPx()) -
                      static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    if (AceApplicationInfo::GetInstance().IsRightToLeft() &&
        AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        closeIconX = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    }
    auto closeIconY = static_cast<float>(sheetTheme->GetTitleTextMargin().ConvertToPx());
    OffsetF positionOffset;
    positionOffset.SetX(closeIconX + translate.GetX());
    positionOffset.SetY(closeIconY + translate.GetY());
    geometryNode->SetMarginFrameOffset(positionOffset);
    closeIconWrapper->Layout();
}

void SheetPresentationLayoutAlgorithm::LayoutScrollNode(const NG::OffsetF& translate,
    LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto index = host->GetChildIndexById(scrollNode->GetId());
    auto scrollWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(scrollWrapper);

    auto offset = translate;
    auto titleBuilder = sheetPattern->GetTitleBuilderNode();
    if (titleBuilder) {
        auto titleBuilderNode = titleBuilder->GetGeometryNode();
        CHECK_NULL_VOID(titleBuilderNode);
        offset += OffsetF(0, titleBuilderNode->GetFrameSize().Height());
    }
    auto geometryNode = scrollWrapper->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(offset);
    scrollWrapper->Layout();
}

void SheetPresentationLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    const auto& pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / DOUBLE_SIZE;
    if (sheetType_ == SheetType::SHEET_BOTTOMLANDSPACE) {
        sheetOffsetX_ = (sheetMaxWidth_ - sheetWidth_) / DOUBLE_SIZE;
    } else if (sheetType_ == SheetType::SHEET_CENTER) {
        ComputeCenterStyleOffset(layoutWrapper);
    } else if (sheetType_ == SheetType::SHEET_POPUP) {
        ComputePopupStyleOffset(layoutWrapper);
    } else if (sheetType_ == SheetType::SHEET_BOTTOM_OFFSET) {
        sheetOffsetY_ = (sheetMaxHeight_ - sheetHeight_ + sheetStyle_.bottomOffset->GetY());
        sheetOffsetX_ = sheetOffsetX_ + sheetStyle_.bottomOffset->GetX();
    }
    CalculateSheetOffsetInOtherScenes(layoutWrapper);
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
        UpdateTranslateOffsetWithPlacement(translate);
    }
    LayoutCloseIcon(translate, layoutWrapper);
    LayoutTitleBuilder(translate, layoutWrapper);
    LayoutScrollNode(translate, layoutWrapper);
}

void SheetPresentationLayoutAlgorithm::UpdateTranslateOffsetWithPlacement(OffsetF& translate)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        translate += OffsetF(0, SHEET_ARROW_HEIGHT.ConvertToPx());
        return;
    }
    if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
        !sheetPopupInfo_.showArrow) {
        return;
    }
    // child content should not show in arrow, so that child layout need translate to avoid sheet arrow.
    switch (sheetPopupInfo_.finalPlacement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM: {
            translate += OffsetF(0.f, SHEET_ARROW_HEIGHT.ConvertToPx());
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT: {
            translate += OffsetF(SHEET_ARROW_HEIGHT.ConvertToPx(), 0.f);
            break;
        }
        default:
            break;
    }
}

float SheetPresentationLayoutAlgorithm::GetHeightByScreenSizeType(const float parentConstraintHeight,
    const float parentConstraintWidth, LayoutWrapper* layoutWrapper) const
{
    float height = parentConstraintHeight;
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
        case SheetType::SHEET_BOTTOMLANDSPACE:
            height = parentConstraintHeight;
            break;
        case SheetType::SHEET_BOTTOM_OFFSET:
        case SheetType::SHEET_CENTER:
            height = GetHeightBySheetStyle(parentConstraintHeight, parentConstraintWidth, layoutWrapper);
            break;
        case SheetType::SHEET_POPUP:
            height = GetHeightBySheetStyle(parentConstraintHeight, parentConstraintWidth, layoutWrapper) +
                SHEET_ARROW_HEIGHT.ConvertToPx();
            // The sheet height can only be confirmed after the placement is confirmed.
            if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
                height -= SHEET_ARROW_HEIGHT.ConvertToPx();
            }
            break;
        default:
            break;
    }

    return height;
}

float SheetPresentationLayoutAlgorithm::GetWidthByScreenSizeType(const float parentConstraintWidth,
    LayoutWrapper* layoutWrapper) const
{
    float sheetWidth = parentConstraintWidth;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, sheetWidth);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, sheetWidth);
    switch (sheetType_) {
        case SheetType::SHEET_BOTTOM:
            if (sheetPattern->IsPhoneInLandScape()) {
                sheetWidth = std::min(static_cast<float>(SHEET_LANDSCAPE_WIDTH.ConvertToPx()), parentConstraintWidth);
                break;
            }
            [[fallthrough]];
        case SheetType::SHEET_BOTTOM_FREE_WINDOW:
            sheetWidth = parentConstraintWidth;
            break;
        case SheetType::SHEET_BOTTOMLANDSPACE:
            [[fallthrough]];
        case SheetType::SHEET_CENTER:
            sheetWidth = SHEET_LANDSCAPE_WIDTH.ConvertToPx();
            break;
        case SheetType::SHEET_POPUP:
            sheetWidth = SHEET_POPUP_WIDTH.ConvertToPx();
            break;
        default:
            break;
    }

    if (!sheetStyle_.width.has_value()) {
        return sheetWidth;
    }
    auto width = 0.0f;
    if (sheetStyle_.width->Unit() == DimensionUnit::PERCENT) {
        width = sheetStyle_.width->ConvertToPxWithSize(parentConstraintWidth);
    } else {
        width = sheetStyle_.width->ConvertToPx();
    }
    if (LessNotEqual(width, 0.0f) || width > parentConstraintWidth) {
        width = sheetWidth;
    }
    return width;
}

float SheetPresentationLayoutAlgorithm::ComputeMaxHeight(const float parentConstraintHeight,
    const float parentConstraintWidth, LayoutWrapper* layoutWrapper) const
{
    float sheetMaxHeight = parentConstraintHeight;
    if (SheetInSplitWindow()) {
        sheetMaxHeight = parentConstraintHeight - SHEET_SPLIT_STATUS_BAR.ConvertToPx() -
            SHEET_SPLIT_AI_BAR.ConvertToPx();
    }
    NG::RectF floatButtons;
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, 0.0f);
    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_RETURN(sheetPattern, 0.0f);
    auto maxHeight = (std::min(sheetMaxHeight, parentConstraintWidth)) * POPUP_LARGE_SIZE;
    if (sheetPattern->GetWindowButtonRect(floatButtons)) {
        maxHeight = sheetMaxHeight - DOUBLE_SIZE *
            (floatButtons.Height() + SHEET_BLANK_MINI_HEIGHT.ConvertToPx());
    } else if (sheetStyle_.showInSubWindow.value_or(false)) {
        auto sheetWrapper = AceType::DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_RETURN(sheetWrapper, 0.0f);
        auto sheetWrapperPattern = sheetWrapper->GetPattern<SheetWrapperPattern>();
        CHECK_NULL_RETURN(sheetWrapperPattern, 0.0f);
        RectF containerModal;
        RectF buttonsRect;
        auto subwindowId = sheetWrapperPattern->GetSubWindowId();
        auto currentId = SubwindowManager::GetInstance()->GetParentContainerId(subwindowId);
        ContainerScope scope(currentId);
        auto mainWindowContext = PipelineContext::GetContextByContainerId(currentId);
        if (mainWindowContext && mainWindowContext->GetContainerModalButtonsRect(containerModal, buttonsRect)) {
            maxHeight = (std::min(parentConstraintHeight - buttonsRect.Height(),
                parentConstraintWidth)) * POPUP_LARGE_SIZE;
        }
    }
    return maxHeight;
}

float SheetPresentationLayoutAlgorithm::GetHeightBySheetStyle(const float parentConstraintHeight,
    const float parentConstraintWidth, LayoutWrapper* layoutWrapper) const
{
    float height = 0.0f;
    bool isMediumOrLargeMode = false;
    if (sheetStyle_.sheetHeight.sheetMode == SheetMode::MEDIUM ||
        sheetStyle_.sheetHeight.sheetMode == SheetMode::LARGE) {
        isMediumOrLargeMode =  true;
    }
    if (sheetStyle_.sheetHeight.height.has_value() || isMediumOrLargeMode) {
        auto maxHeight = ComputeMaxHeight(parentConstraintHeight, parentConstraintWidth, layoutWrapper);
        if (sheetStyle_.sheetHeight.height->Unit() == DimensionUnit::PERCENT) {
            height = sheetStyle_.sheetHeight.height->ConvertToPxWithSize(maxHeight);
        } else if (isMediumOrLargeMode) {
            height = SHEET_BIG_WINDOW_HEIGHT.ConvertToPx();
        } else {
            height = sheetStyle_.sheetHeight.height->ConvertToPx();
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
    RefPtr<SheetPresentationProperty> layoutprop, LayoutWrapper* layoutWrapper)
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
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_RETURN(host, childConstraint);
        auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_RETURN(sheetPattern, childConstraint);
        auto operationNode = sheetPattern->GetTitleBuilderNode();
        CHECK_NULL_RETURN(operationNode, childConstraint);
        auto titleGeometryNode = operationNode->GetGeometryNode();
        CHECK_NULL_RETURN(titleGeometryNode, childConstraint);
        auto titleHeiht = titleGeometryNode->GetFrameSize().Height();
        maxHeight -= titleHeiht;
    }
    auto maxWidth = sheetWidth_;
    if (sheetType_ == SheetType::SHEET_POPUP) {
        UpdateMaxSizeWithPlacement(maxWidth, maxHeight);
    }
    if (sheetPopupInfo_.finalPlacement != Placement::NONE) {
        childConstraint.maxSize.SetWidth(maxWidth);
    }
    childConstraint.maxSize.SetHeight(maxHeight);
    childConstraint.parentIdealSize = OptionalSizeF(sheetWidth_, sheetHeight_);
    childConstraint.percentReference = SizeF(sheetWidth_, sheetHeight_);
    return childConstraint;
}

void SheetPresentationLayoutAlgorithm::UpdateMaxSizeWithPlacement(float& maxWidth, float& maxHeight)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        maxHeight -= SHEET_ARROW_HEIGHT.ConvertToPx();
        return;
    }

    if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
        !sheetPopupInfo_.showArrow) {
        return;
    }

    switch (sheetPopupInfo_.finalPlacement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM:
            [[fallthrough]];
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            maxHeight -= SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT:
            [[fallthrough]];
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            maxWidth -= SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        }
        default:
            break;
    }
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

void SheetPresentationLayoutAlgorithm::UpdatePopupInfoAndRemeasure(LayoutWrapper* layoutWrapper,
    const SheetPopupInfo& sheetPopupInfo, const float& sheetWidth, const float& sheetHeight)
{
    if (sheetType_ != SheetType::SHEET_POPUP) {
        return;
    }
    sheetPopupInfo_ = sheetPopupInfo;
    sheetOffsetX_ = sheetPopupInfo.sheetOffsetX;
    sheetOffsetY_ = sheetPopupInfo.sheetOffsetY;
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    sheetWidth_ = sheetWidth;
    sheetHeight_ = sheetHeight;
    auto sheetPageWrapper = layoutWrapper->GetChildByIndex(0);
    CHECK_NULL_VOID(sheetPageWrapper);
    RemeasureForPopup(sheetPageWrapper);
}

void SheetPresentationLayoutAlgorithm::AddArrowHeightToSheetSize()
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) ||
        sheetType_ != SheetType::SHEET_POPUP) {
        return;
    }

    if ((sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) ||
        !sheetPopupInfo_.showArrow) {
        return;
    }

    switch (sheetPopupInfo_.finalPlacement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM:
            [[fallthrough]];
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            sheetHeight_ += SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT:
            [[fallthrough]];
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            sheetWidth_ += SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        }
        default:
            break;
    }
}

void SheetPresentationLayoutAlgorithm::RemeasureForPopup(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    if (layoutWrapper->GetGeometryNode() && layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()) {
        auto parentConstraint = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint();
        if (!parentConstraint.has_value()) {
            return;
        }
        auto layoutConstraint = parentConstraint.value();
        auto layoutProperty = AceType::DynamicCast<SheetPresentationProperty>(layoutWrapper->GetLayoutProperty());
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateLayoutConstraint(layoutConstraint);
        AddArrowHeightToSheetSize();
        TAG_LOGI(AceLogTag::ACE_SHEET, "remeasure size:(%{public}f, %{public}f)", sheetWidth_, sheetHeight_);
        SizeF idealSize(sheetWidth_, sheetHeight_);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
        layoutWrapper->GetGeometryNode()->SetContentSize(idealSize);
        auto childConstraint = CreateSheetChildConstraint(layoutProperty, Referenced::RawPtr(layoutWrapper));
        layoutConstraint.percentReference = SizeF(sheetWidth_, sheetHeight_);
        for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Measure(childConstraint);
        }
        auto host = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(host);
        auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        auto scrollNode = sheetPattern->GetSheetScrollNode();
        CHECK_NULL_VOID(scrollNode);
        childConstraint.selfIdealSize.SetWidth(childConstraint.maxSize.Width());
        scrollNode->Measure(childConstraint);
    }
}
} // namespace OHOS::Ace::NG