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

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_mask_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_property.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_layout_algorithm.h"
#include "core/components_ng/pattern/overlay/sheet_wrapper_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DOUBLE_SIZE = 2;
constexpr Dimension WINDOW_EDGE_SPACE = 6.0_vp;
constexpr Dimension ARROW_VERTICAL_P1_OFFSET_X = 8.0_vp;
constexpr Dimension ARROW_VERTICAL_P5_OFFSET_X = 8.0_vp;
std::map<Placement, std::vector<Placement>> PLACEMENT_STATES = {
    { Placement::BOTTOM_LEFT,
        {
            Placement::BOTTOM_LEFT,
            Placement::TOP_LEFT,
            Placement::RIGHT_TOP,
            Placement::LEFT_TOP,
            Placement::NONE,
        } },
    { Placement::BOTTOM,
        {
            Placement::BOTTOM,
            Placement::TOP,
            Placement::RIGHT,
            Placement::LEFT,
            Placement::NONE,
        } },
    { Placement::BOTTOM_RIGHT,
        {
            Placement::BOTTOM_RIGHT,
            Placement::TOP_RIGHT,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::TOP_LEFT,
        {
            Placement::TOP_LEFT,
            Placement::BOTTOM_LEFT,
            Placement::RIGHT_TOP,
            Placement::LEFT_TOP,
            Placement::NONE,
        } },
    { Placement::TOP,
        {
            Placement::TOP,
            Placement::BOTTOM,
            Placement::RIGHT,
            Placement::LEFT,
            Placement::NONE,
        } },
    { Placement::TOP_RIGHT,
        {
            Placement::TOP_RIGHT,
            Placement::BOTTOM_RIGHT,
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_BOTTOM,
            Placement::NONE,
        } },
    { Placement::LEFT_TOP,
        {
            Placement::LEFT_TOP,
            Placement::RIGHT_TOP,
            Placement::BOTTOM_LEFT,
            Placement::TOP_LEFT,
            Placement::NONE,
        } },
    { Placement::LEFT,
        {
            Placement::LEFT,
            Placement::RIGHT,
            Placement::BOTTOM,
            Placement::TOP,
            Placement::NONE,
        } },
    { Placement::LEFT_BOTTOM,
        {
            Placement::LEFT_BOTTOM,
            Placement::RIGHT_BOTTOM,
            Placement::BOTTOM_RIGHT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
    { Placement::RIGHT_TOP,
        {
            Placement::RIGHT_TOP,
            Placement::LEFT_TOP,
            Placement::BOTTOM_LEFT,
            Placement::TOP_LEFT,
            Placement::NONE,
        } },
    { Placement::RIGHT,
        {
            Placement::RIGHT,
            Placement::LEFT,
            Placement::BOTTOM,
            Placement::TOP,
            Placement::NONE,
        } },
    { Placement::RIGHT_BOTTOM,
        {
            Placement::RIGHT_BOTTOM,
            Placement::LEFT_BOTTOM,
            Placement::BOTTOM_RIGHT,
            Placement::TOP_RIGHT,
            Placement::NONE,
        } },
};
}   // namespace

void SheetWrapperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    InitParameter(layoutWrapper);
    BoxLayoutAlgorithm::PerformMeasureSelf(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto child = sheetWrapperPattern->GetSheetPageNode();
    CHECK_NULL_VOID(child);
    auto sheetLayoutProperty = child->GetLayoutProperty();
    CHECK_NULL_VOID(sheetLayoutProperty);
    sheetLayoutProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    auto layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    auto childConstraint = layoutProp->CreateChildConstraint();
    child->Measure(childConstraint);
    GetSheetPageSize(layoutWrapper);
    MeasureSheetMask(layoutWrapper);
}

void SheetWrapperLayoutAlgorithm::MeasureSheetMask(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);

    if (!sheetWrapperPattern->ShowInUEC()) {
        return;
    }
    auto maskNode = sheetWrapperPattern->GetSheetMaskNode();
    CHECK_NULL_VOID(maskNode);
    auto index = host->GetChildIndexById(maskNode->GetId());
    auto maskWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(maskWrapper);
    auto rect = sheetWrapperPattern->GetMainWindowRect();
    auto layoutProp = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProp);
    auto constraint = layoutProp->CreateChildConstraint();
    constraint.selfIdealSize = OptionalSizeF(rect.Width(), rect.Height());
    maskWrapper->Measure(constraint);
}

void SheetWrapperLayoutAlgorithm::InitParameter(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto sheetPage = sheetWrapperPattern->GetSheetPageNode();
    CHECK_NULL_VOID(sheetPage);
    auto sheetPattern = DynamicCast<SheetPresentationPattern>(sheetPage->GetPattern());
    CHECK_NULL_VOID(sheetPattern);
    sheetRadius_ = BorderRadiusProperty(sheetTheme->GetSheetRadius());
    sheetPattern->CalculateSheetRadius(sheetRadius_);
    auto layoutProperty = sheetPage->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    auto needAvoidKeyboard = sheetStyle.sheetKeyboardAvoidMode == SheetKeyboardAvoidMode::POPUP_SHEET;
    placement_ = sheetStyle.placement.value_or(Placement::BOTTOM);
    sheetPopupInfo_.Reset();    // everytime sheetWrapper changed, we need to reset sheetPopupInfo to default value
    sheetPopupInfo_.finalPlacement = placement_;
    sheetPopupInfo_.placementOnTarget = sheetStyle.placementOnTarget.value_or(true);
    windowGlobalRect_ = pipeline->GetDisplayWindowRectInfo();
    windowEdgeWidth_ = WINDOW_EDGE_SPACE.ConvertToPx();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        // global rect need to reduce the top and bottom safe area
        windowGlobalRect_ = pipeline->GetCurrentWindowRect();
        auto safeArea = pipeline->GetSafeArea();
        RectF floatContainerModal;
        RectF titleRect;
        // get window rect title height
        pipeline->GetContainerModalButtonsRect(floatContainerModal, titleRect);
        auto offsetY = safeArea.top_.Length() + titleRect.Height();
        auto height = windowGlobalRect_.Height() - offsetY - safeArea.bottom_.Length();
        auto manager = pipeline->GetSafeAreaManager();
        CHECK_NULL_VOID(manager);
        auto keyboardInset = manager->GetKeyboardInset();
        auto focusHub = sheetPage->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        auto isFocused = focusHub->IsCurrentFocus();
        if (keyboardInset.Length() != 0 && isFocused && needAvoidKeyboard) {
            sheetPopupInfo_.keyboardShow = true;
            height -= keyboardInset.Length() - safeArea.bottom_.Length();
            sheetPopupInfo_.showArrow =
                !IsTargetNodeHideByKeyboard(keyboardInset, sheetWrapperPattern->GetTargetNode());
        }
        // windowRect neet to set as origin point, because sheet offset is relative to window rect
        windowGlobalRect_ = Rect(0.f, offsetY, windowGlobalRect_.Width(), height);
    }
}

void SheetWrapperLayoutAlgorithm::GetSheetPageSize(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto sheetPage = sheetWrapperPattern->GetSheetPageNode();
    CHECK_NULL_VOID(sheetPage);
    auto sheetGeometryNode = sheetPage->GetGeometryNode();
    CHECK_NULL_VOID(sheetGeometryNode);
    sheetWidth_ = sheetGeometryNode->GetFrameSize().Width();
    sheetHeight_ = sheetGeometryNode->GetFrameSize().Height();
    DecreaseArrowHeightWhenArrowIsShown(sheetPage);
    // when sheetWidth > global rect - 2 * windowEdgeSpace, windowEdgeSpace is set to the half of left space
    if (GreatNotEqual(sheetWidth_, windowGlobalRect_.Width() - DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx())) {
        windowEdgeWidth_ = (windowGlobalRect_.Width() - sheetWidth_) / DOUBLE_SIZE;
    }
}

void SheetWrapperLayoutAlgorithm::DecreaseArrowHeightWhenArrowIsShown(const RefPtr<FrameNode>& sheetNode)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }

    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto prePopupInfo = sheetPattern->GetSheetPopupInfo();
    if (!prePopupInfo.showArrow) {
        return;
    }

    switch (prePopupInfo.finalPlacement) {
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
            sheetHeight_ -= SHEET_ARROW_HEIGHT.ConvertToPx();
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
            sheetWidth_ -= SHEET_ARROW_HEIGHT.ConvertToPx();
            break;
        }
        default:
            break;
    }
}

OffsetF SheetWrapperLayoutAlgorithm::GetPopupStyleSheetOffset(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, OffsetF());
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_RETURN(sheetWrapperPattern, OffsetF());
    auto targetNode = sheetWrapperPattern->GetTargetNode();
    CHECK_NULL_RETURN(targetNode, OffsetF());
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, OffsetF());
    auto targetSize = geometryNode->GetFrameSize();
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        targetSize = targetNode->GetPaintRectWithTransform().GetSize();
    }
    auto targetOffset = targetNode->GetPaintRectOffset();
    if (sheetWrapperPattern->GetSubWindowId() != INVALID_SUBWINDOW_ID) {
        if (sheetWrapperPattern->ShowInUEC()) {
            auto UECId = SubwindowManager::GetInstance()->GetParentContainerId(sheetWrapperPattern->GetSubWindowId());
            auto container = AceEngine::Get().GetContainer(UECId);
            CHECK_NULL_RETURN(container, OffsetF());
            auto mainWindowContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_RETURN(mainWindowContext, OffsetF());
            auto UECWindowGlobalRect = mainWindowContext->GetDisplayWindowRectInfo();
            targetOffset = OffsetF(targetNode->GetPaintRectOffset().GetX() + UECWindowGlobalRect.Left(),
                targetNode->GetPaintRectOffset().GetY() + UECWindowGlobalRect.Top());
        } else {
            auto mainWindowRect = sheetWrapperPattern->GetMainWindowRect();
            targetOffset = OffsetF(targetNode->GetPaintRectOffset().GetX() + mainWindowRect.Left(),
                targetNode->GetPaintRectOffset().GetY() + mainWindowRect.Top());
        }
    }
    return GetOffsetInAvoidanceRule(layoutWrapper, targetSize, targetOffset);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetInAvoidanceRule(
    LayoutWrapper* layoutWrapper, const SizeF& targetSize, const OffsetF& targetOffset)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        sheetPopupInfo_.finalPlacement = AvoidanceRuleOfPlacement(layoutWrapper, targetSize, targetOffset);
    } else {
        // before api 16, only placement bottom is used
        sheetPopupInfo_.finalPlacement = AvoidanceRuleBottom(Placement::BOTTOM, targetSize, targetOffset);
    }
    TAG_LOGI(AceLogTag::ACE_SHEET, "finalPlacement %{public}s",
        PlacementUtils::ConvertPlacementToString(sheetPopupInfo_.finalPlacement).c_str());
    if (getOffsetFunc_.find(sheetPopupInfo_.finalPlacement) == getOffsetFunc_.end()) {
        TAG_LOGW(AceLogTag::ACE_SHEET, "It is an invalid Placement for current PopSheet.");
        return OffsetF(0.f, 0.f);
    }
    auto offsetFunc = getOffsetFunc_[sheetPopupInfo_.finalPlacement];
    CHECK_NULL_RETURN(offsetFunc, OffsetF());
    /*
     * steps 1. get sheet offset and restrict in window global rect
     * steps 2. check whether need to show arrow
     * steps 3. get arrow offset and check whether it is overlap sheet radius
     */
    return (this->*offsetFunc)(targetSize, targetOffset);
}

Placement SheetWrapperLayoutAlgorithm::AvoidanceRuleBottom(
    const Placement& currentPlacement, const SizeF& targetSize, const OffsetF& targetOffset)
{
    static std::map<Placement, std::vector<Placement>> PLACEMENT_STATES_BOTTOM = {
        { Placement::BOTTOM,
            {
                Placement::BOTTOM,
                Placement::BOTTOM_RIGHT,
                Placement::BOTTOM_LEFT,
            } },
    };
    Placement targetPlacement = currentPlacement;
    TAG_LOGD(AceLogTag::ACE_SHEET, "Init PopupSheet placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(targetPlacement).c_str());
    // Step1: Determine the Placement in direction Bottom
    auto& placementVec = PLACEMENT_STATES_BOTTOM[targetPlacement];
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
    TAG_LOGD(AceLogTag::ACE_SHEET, "After placementCheck, placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(targetPlacement).c_str());
    return targetPlacement;
}

Placement SheetWrapperLayoutAlgorithm::AvoidanceRuleOfPlacement(
    LayoutWrapper* layoutWrapper, const SizeF& targetSize, const OffsetF& targetOffset)
{
    auto finalPlacement = placement_;
    // step1: confirm the direction to place popup
    TAG_LOGD(AceLogTag::ACE_SHEET, "Init PopupSheet placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(finalPlacement).c_str());
    auto& placementStateVec = PLACEMENT_STATES[finalPlacement];
    for (auto placement : placementStateVec) {
        finalPlacement = placement;
        auto& directionFunc = directionCheckFunc_[placement];
        if (directionFunc == nullptr) {
            continue;
        }
        if ((this->*directionFunc)(targetSize, targetOffset)) {
            break;
        }
    }
    TAG_LOGD(AceLogTag::ACE_SHEET, "After directionCheck, placement: %{public}s",
        PlacementUtils::ConvertPlacementToString(finalPlacement).c_str());
    // step2: check whether placement direction is NONE;
    // if finalPlacement == None, it means nowhere can place the sheetPage after direction check.
    if (finalPlacement == Placement::NONE) {
        sheetPopupInfo_.placementRechecked = true;
        if (sheetPopupInfo_.placementOnTarget) {
            finalPlacement = placement_;
            // when placementOnTarget and avoid keyboard is set true, the best place is user set placement.
            if (sheetPopupInfo_.keyboardShow) {
                // aovid keyboard need decrease sheetHeight.
                sheetHeight_ = std::min(static_cast<double>(sheetHeight_),
                    (windowGlobalRect_.Height() - DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx()));
            }
        } else {
            SizeF bestSize = SizeF(0.f, 0.f);
            finalPlacement = RecheckBestPlacementWithInsufficientSpace(targetSize, targetOffset, bestSize);
            sheetHeight_ = bestSize.Height();
        }
    } else {
        sheetPopupInfo_.placementRechecked = false;
    }
    return finalPlacement;
}

bool SheetWrapperLayoutAlgorithm::CheckDirectionBottom(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float sheetPageAvoidHeight = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    /* if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show,
     * so that arrowHeight is no need to avoid.
     */
    if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPageAvoidHeight += SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    return GreatOrEqual(windowGlobalRect_.Width(), sheetWidth_ + DOUBLE_SIZE * windowEdgeWidth_) &&
        GreatOrEqual(windowGlobalRect_.Height() + windowGlobalRect_.Top() - targetOffset.GetY() - targetSize.Height(),
            sheetHeight_ + sheetPageAvoidHeight);
}

bool SheetWrapperLayoutAlgorithm::CheckDirectionTop(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float sheetPageAvoidHeight = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    /* if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show,
     * so that arrowHeight is no need to avoid.
     */
    if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPageAvoidHeight += SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    return GreatOrEqual(windowGlobalRect_.Width(), sheetWidth_ + DOUBLE_SIZE * windowEdgeWidth_) &&
        GreatOrEqual(targetOffset.GetY() - windowGlobalRect_.Top(),
            sheetHeight_ + sheetPageAvoidHeight);
}

bool SheetWrapperLayoutAlgorithm::CheckDirectionRight(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float sheetPageAvoidWidth = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    /* if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show,
     * so that arrowHeight is no need to avoid.
     */
    if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPageAvoidWidth += SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    return GreatOrEqual(windowGlobalRect_.Width() - targetOffset.GetX() - targetSize.Width(),
        sheetWidth_ + sheetPageAvoidWidth) &&
           GreatOrEqual(windowGlobalRect_.Height(), sheetHeight_ + DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx());
}

bool SheetWrapperLayoutAlgorithm::CheckDirectionLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float sheetPageAvoidWidth = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    /* if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show,
     * so that arrowHeight is no need to avoid.
     */
    if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPageAvoidWidth += SHEET_ARROW_HEIGHT.ConvertToPx();
    }
    return GreatOrEqual(targetOffset.GetX(), sheetWidth_ + sheetPageAvoidWidth) &&
        GreatOrEqual(windowGlobalRect_.Height(),
            sheetHeight_ + DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx());
}

Placement SheetWrapperLayoutAlgorithm::RecheckBestPlacementWithInsufficientSpace(
    const SizeF& targetSize, const OffsetF& targetOffset, SizeF& bestSize)
{
    auto expectedPlacement = Placement::NONE;
    auto& recheckPlacementVec = PLACEMENT_STATES[placement_];
    for (auto placement : recheckPlacementVec) {
        auto curLeftSpace = GetLeftSpaceWithPlacement(placement, targetSize, targetOffset);
        /* best placement need to meet the following conditions:
         * 1.space width >= sheetWidth
         * 2.space height is the biggest in every placement
         */
        if (curLeftSpace.Width() >= sheetWidth_ && curLeftSpace.Height() < sheetHeight_) {
            if (curLeftSpace.Height() > bestSize.Height()) {
                bestSize = curLeftSpace;
                expectedPlacement = placement;
            }
        }
    }
    TAG_LOGI(AceLogTag::ACE_SHEET, "get best size in insufficient space: %{public}s", bestSize.ToString().c_str());
    return expectedPlacement;
}

bool SheetWrapperLayoutAlgorithm::CheckPlacementBottom(const SizeF& targetSize, const OffsetF& targetOffset)
{
    return GreatOrEqual(
        windowGlobalRect_.Width() - WINDOW_EDGE_SPACE.ConvertToPx(),
        targetOffset.GetX() + targetSize.Width() / DOUBLE_SIZE + sheetWidth_ / DOUBLE_SIZE) &&
        LessOrEqual(
            WINDOW_EDGE_SPACE.ConvertToPx(),
            targetOffset.GetX() + targetSize.Width() / DOUBLE_SIZE - sheetWidth_ / DOUBLE_SIZE);
}

bool SheetWrapperLayoutAlgorithm::CheckPlacementBottomLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    return LessOrEqual(WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX()) &&
           GreatOrEqual(windowGlobalRect_.Width() - WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + sheetWidth_);
}

bool SheetWrapperLayoutAlgorithm::CheckPlacementBottomRight(const SizeF& targetSize, const OffsetF& targetOffset)
{
    return LessOrEqual(WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + targetSize.Width() - sheetWidth_) &&
           GreatOrEqual(
               windowGlobalRect_.Width() - WINDOW_EDGE_SPACE.ConvertToPx(), targetOffset.GetX() + targetSize.Width());
}

SizeF SheetWrapperLayoutAlgorithm::GetLeftSpaceWithPlacement(
    const Placement& placement, const SizeF& targetSize, const OffsetF& targetOffset)
{
    float width = 0.f;
    float height = 0.f;
    float sheetPageAvoidHeight = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    float sheetPageAvoidWidth = (SHEET_TARGET_SPACE + WINDOW_EDGE_SPACE).ConvertToPx();
    switch (placement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM: {
            if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
                sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
                sheetPageAvoidHeight += SHEET_ARROW_HEIGHT.ConvertToPx();
            }
            width = windowGlobalRect_.Width() - DOUBLE_SIZE * windowEdgeWidth_;
            height = windowGlobalRect_.Height() + windowGlobalRect_.Top() -
                targetOffset.GetY() - targetSize.Height() - sheetPageAvoidHeight;
            break;
        }
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            if (GreatOrEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
                sheetPageAvoidHeight += SHEET_ARROW_HEIGHT.ConvertToPx();
            }
            width = windowGlobalRect_.Width() - DOUBLE_SIZE * windowEdgeWidth_;
            height = targetOffset.GetY() - windowGlobalRect_.Top() - sheetPageAvoidHeight;
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT: {
            if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
                sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
                sheetPageAvoidWidth += SHEET_ARROW_HEIGHT.ConvertToPx();
            }
            width = windowGlobalRect_.Width() - targetOffset.GetX() - targetSize.Width() - sheetPageAvoidWidth;
            height = windowGlobalRect_.Height() - DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx();
            break;
        }
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            if (GreatOrEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
                sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
                sheetPageAvoidWidth += SHEET_ARROW_HEIGHT.ConvertToPx();
            }
            width = targetOffset.GetX() - sheetPageAvoidWidth;
            height = windowGlobalRect_.Height() - DOUBLE_SIZE * WINDOW_EDGE_SPACE.ConvertToPx();
            break;
        }
        default:
            break;
    }
    return SizeF(width, height);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithBottom(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        sheetPopupInfo_.arrowOffsetX = sheetWidth_ / DOUBLE_SIZE;
        return OffsetF(targetOffset.GetX() + (targetSize.Width() - sheetWidth_) / DOUBLE_SIZE,
            targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());
    }

    float finalOffsetX = targetOffset.GetX() + (targetSize.Width() - sheetWidth_) / DOUBLE_SIZE;
    float finalOffsetY = targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx();
    RestrictOffsetInSpaceBottom(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithBottomLeft(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        sheetPopupInfo_.arrowOffsetX = targetSize.Width() / DOUBLE_SIZE;
        auto sheetOffset =
            OffsetF(targetOffset.GetX(), targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());

        // if the arrow overlaps the sheet left corner, move sheet to the 6vp from the left edge
        if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
            sheetRadius_.radiusTopLeft->ConvertToPx())) {
            sheetOffset.SetX(WINDOW_EDGE_SPACE.ConvertToPx());
            sheetPopupInfo_.arrowOffsetX = targetOffset.GetX() + targetSize.Width() / DOUBLE_SIZE - sheetOffset.GetX();
            TAG_LOGD(AceLogTag::ACE_SHEET, "Adjust sheet to the left boundary of the screen");
        }

        // if the arrow still overlaps the sheet left corner, the arrow will become a right angle.
        if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
            sheetRadius_.radiusTopLeft->ConvertToPx())) {
            TAG_LOGD(AceLogTag::ACE_SHEET, "Need to switch the arrow into the right-angle arrow");
        }
        return sheetOffset;
    }

    float finalOffsetX = targetOffset.GetX();
    float finalOffsetY = targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx();
    RestrictOffsetInSpaceBottom(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithBottomRight(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        sheetPopupInfo_.arrowOffsetX = sheetWidth_ - targetSize.Width() / DOUBLE_SIZE;
        auto sheetOffset = OffsetF(targetOffset.GetX() + targetSize.Width() - sheetWidth_,
            targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx());

        // if the arrow overlaps the sheet right corner, move sheet to the 6vp from the right edge
        if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + sheetRadius_.radiusTopRight->ConvertToPx() +
            ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), sheetWidth_)) {
            sheetOffset.SetX(windowGlobalRect_.Width() - WINDOW_EDGE_SPACE.ConvertToPx() - sheetWidth_);
            sheetPopupInfo_.arrowOffsetX = targetOffset.GetX() + targetSize.Width() / DOUBLE_SIZE - sheetOffset.GetX();
            TAG_LOGD(AceLogTag::ACE_SHEET, "Adjust sheet to the right boundary of the screen");
        }

        // if the arrow still overlaps the sheet right corner, the arrow will become a right angle.
        if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + sheetRadius_.radiusTopRight->ConvertToPx() +
            ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(), sheetWidth_)) {
            TAG_LOGD(AceLogTag::ACE_SHEET, "Need to switch the arrow into the right angle arrow");
        }
        return sheetOffset;
    }

    float finalOffsetX = targetOffset.GetX() + targetSize.Width() - sheetWidth_;
    float finalOffsetY = targetOffset.GetY() + targetSize.Height() + SHEET_TARGET_SPACE.ConvertToPx();
    RestrictOffsetInSpaceBottom(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusTopRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithTop(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() + (targetSize.Width() - sheetWidth_) / DOUBLE_SIZE;
    float finalOffsetY = targetOffset.GetY() -
        SHEET_TARGET_SPACE.ConvertToPx() - sheetHeight_ - SHEET_ARROW_HEIGHT.ConvertToPx();
    RestrictOffsetInSpaceTop(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithTopLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX();
    float finalOffsetY = targetOffset.GetY() -
        SHEET_TARGET_SPACE.ConvertToPx() - sheetHeight_ - SHEET_ARROW_HEIGHT.ConvertToPx();
    RestrictOffsetInSpaceTop(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithTopRight(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() + targetSize.Width() - sheetWidth_;
    float finalOffsetY = targetOffset.GetY() -
        SHEET_TARGET_SPACE.ConvertToPx() - sheetHeight_ - SHEET_ARROW_HEIGHT.ConvertToPx();
    RestrictOffsetInSpaceTop(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetWidth < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetWidth_, sheetRadius_.radiusBottomLeft->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInBottomOrTop(targetSize, targetOffset, finalOffsetX);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithLeft(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() -
        sheetWidth_ - SHEET_TARGET_SPACE.ConvertToPx() - SHEET_ARROW_HEIGHT.ConvertToPx();
    float finalOffsetY = targetOffset.GetY() + (targetSize.Height() - sheetHeight_) / DOUBLE_SIZE;
    RestrictOffsetInSpaceLeft(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithLeftTop(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() -
        sheetWidth_ - SHEET_TARGET_SPACE.ConvertToPx() - SHEET_ARROW_HEIGHT.ConvertToPx();
    float finalOffsetY = targetOffset.GetY();
    RestrictOffsetInSpaceLeft(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithLeftBottom(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() -
        sheetWidth_ - SHEET_TARGET_SPACE.ConvertToPx() - SHEET_ARROW_HEIGHT.ConvertToPx();
    float finalOffsetY = targetOffset.GetY() + targetSize.Height() - sheetHeight_;
    RestrictOffsetInSpaceLeft(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopRight->ConvertToPx() +
        sheetRadius_.radiusBottomRight->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithRight(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() + targetSize.Width() + SHEET_TARGET_SPACE.ConvertToPx();
    float finalOffsetY = targetOffset.GetY() + (targetSize.Height() - sheetHeight_) / DOUBLE_SIZE;
    RestrictOffsetInSpaceRight(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithRightTop(const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() + targetSize.Width() + SHEET_TARGET_SPACE.ConvertToPx();
    float finalOffsetY = targetOffset.GetY();
    RestrictOffsetInSpaceRight(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

OffsetF SheetWrapperLayoutAlgorithm::GetOffsetWithRightBottom(
    const SizeF& targetSize, const OffsetF& targetOffset)
{
    float finalOffsetX = targetOffset.GetX() + targetSize.Width() + SHEET_TARGET_SPACE.ConvertToPx();
    float finalOffsetY = targetOffset.GetY() + targetSize.Height() - sheetHeight_;
    RestrictOffsetInSpaceRight(finalOffsetX, finalOffsetY);
    if (!sheetPopupInfo_.showArrow) {
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    // if sheetHeight < sheetRadius * 2 + sheetArrowWidth, arrow is no need to show
    if (LessNotEqual(sheetHeight_, sheetRadius_.radiusTopLeft->ConvertToPx() +
        sheetRadius_.radiusBottomLeft->ConvertToPx() + SHEET_ARROW_WIDTH.ConvertToPx())) {
        sheetPopupInfo_.showArrow = false;
        return OffsetF(finalOffsetX, finalOffsetY);
    }
    SetArrowOffsetInRightOrLeft(targetSize, targetOffset, finalOffsetY);
    CheckIsArrowOverlapSheetRadius();
    return OffsetF(finalOffsetX, finalOffsetY);
}

void SheetWrapperLayoutAlgorithm::SetArrowOffsetInBottomOrTop(
    const SizeF& targetSize, const OffsetF& targetOffset, float sheetOffset)
{
    sheetPopupInfo_.arrowOffsetX = targetOffset.GetX() + targetSize.Width() / DOUBLE_SIZE - sheetOffset;

    sheetPopupInfo_.arrowOffsetX = std::clamp(static_cast<double>(sheetPopupInfo_.arrowOffsetX),
        ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
        sheetWidth_ - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx());
}

void SheetWrapperLayoutAlgorithm::SetArrowOffsetInRightOrLeft(
    const SizeF& targetSize, const OffsetF& targetOffset, float sheetOffset)
{
    sheetPopupInfo_.arrowOffsetY = targetOffset.GetY() + targetSize.Height() / DOUBLE_SIZE - sheetOffset;

    sheetPopupInfo_.arrowOffsetY = std::clamp(static_cast<double>(sheetPopupInfo_.arrowOffsetY),
        ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
        sheetHeight_ - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx());
}

void SheetWrapperLayoutAlgorithm::RestrictOffsetInSpaceBottom(float& offsetX, float& offsetY)
{
    offsetX = std::clamp(static_cast<double>(offsetX), static_cast<double>(windowEdgeWidth_),
        windowGlobalRect_.Width() - sheetWidth_ - windowEdgeWidth_);

    offsetY = std::clamp(static_cast<double>(offsetY), windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx(),
        std::max(windowGlobalRect_.Height() + windowGlobalRect_.Top() - sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx(),
            windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx()));

    if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) {
        sheetPopupInfo_.showArrow = false;
        offsetY = std::max(
            windowGlobalRect_.Height() + windowGlobalRect_.Top() - sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx(),
            windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx());
    }
}

void SheetWrapperLayoutAlgorithm::RestrictOffsetInSpaceTop(float& offsetX, float& offsetY)
{
    offsetX = std::clamp(static_cast<double>(offsetX), static_cast<double>(windowEdgeWidth_),
        windowGlobalRect_.Width() - sheetWidth_ - windowEdgeWidth_);

    offsetY = std::clamp(static_cast<double>(offsetY), windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx(),
        std::max(windowGlobalRect_.Height() + windowGlobalRect_.Top() - sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx(),
            windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx()));

    if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) {
        sheetPopupInfo_.showArrow = false;
        offsetY = windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx();
    }
}

void SheetWrapperLayoutAlgorithm::RestrictOffsetInSpaceLeft(float& offsetX, float& offsetY)
{
    offsetX = std::clamp(static_cast<double>(offsetX), static_cast<double>(windowEdgeWidth_),
        windowGlobalRect_.Width() - sheetWidth_ - windowEdgeWidth_);

    offsetY = std::clamp(static_cast<double>(offsetY), windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx(),
        windowGlobalRect_.Height() + windowGlobalRect_.Top() - sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx());
    
    if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) {
        sheetPopupInfo_.showArrow = false;
        offsetX = windowEdgeWidth_;
    }
}

void SheetWrapperLayoutAlgorithm::RestrictOffsetInSpaceRight(float& offsetX, float& offsetY)
{
    offsetX = std::clamp(static_cast<double>(offsetX), static_cast<double>(windowEdgeWidth_),
        windowGlobalRect_.Width() - sheetWidth_ - windowEdgeWidth_);

    offsetY = std::clamp(static_cast<double>(offsetY), windowGlobalRect_.Top() + WINDOW_EDGE_SPACE.ConvertToPx(),
        windowGlobalRect_.Height() + windowGlobalRect_.Top() - sheetHeight_ - WINDOW_EDGE_SPACE.ConvertToPx());
        
    if (sheetPopupInfo_.placementRechecked && sheetPopupInfo_.placementOnTarget) {
        sheetPopupInfo_.showArrow = false;
        offsetX = windowGlobalRect_.Width() - windowEdgeWidth_ - sheetWidth_;
    }
}

void SheetWrapperLayoutAlgorithm::CheckIsArrowOverlapSheetRadius()
{
    sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;
    switch (sheetPopupInfo_.finalPlacement) {
        case Placement::BOTTOM_LEFT:
            [[fallthrough]];
        case Placement::BOTTOM_RIGHT:
            [[fallthrough]];
        case Placement::BOTTOM: {
            if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
                sheetRadius_.radiusTopLeft->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_LEFT;
            } else if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
                sheetWidth_ - sheetRadius_.radiusTopRight->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::BOTTOM_RIGHT;
            }
            break;
        }
        case Placement::TOP_LEFT:
            [[fallthrough]];
        case Placement::TOP_RIGHT:
            [[fallthrough]];
        case Placement::TOP: {
            if (LessNotEqual(sheetPopupInfo_.arrowOffsetX - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
                sheetRadius_.radiusBottomLeft->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::TOP_LEFT;
            } else if (GreatNotEqual(sheetPopupInfo_.arrowOffsetX + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
                sheetWidth_ - sheetRadius_.radiusBottomRight->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::TOP_RIGHT;
            }
            break;
        }
        case Placement::RIGHT_TOP:
            [[fallthrough]];
        case Placement::RIGHT_BOTTOM:
            [[fallthrough]];
        case Placement::RIGHT: {
            if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
                sheetRadius_.radiusTopLeft->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::RIGHT_TOP;
            } else if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
                sheetHeight_ - sheetRadius_.radiusBottomLeft->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::RIGHT_BOTTOM;
            }
            break;
        }
        case Placement::LEFT_TOP:
            [[fallthrough]];
        case Placement::LEFT_BOTTOM:
            [[fallthrough]];
        case Placement::LEFT: {
            if (LessNotEqual(sheetPopupInfo_.arrowOffsetY - ARROW_VERTICAL_P5_OFFSET_X.ConvertToPx(),
                sheetRadius_.radiusTopRight->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::LEFT_TOP;
            } else if (GreatNotEqual(sheetPopupInfo_.arrowOffsetY + ARROW_VERTICAL_P1_OFFSET_X.ConvertToPx(),
                sheetHeight_ - sheetRadius_.radiusBottomRight->ConvertToPx())) {
                sheetPopupInfo_.arrowPosition = SheetArrowPosition::LEFT_BOTTOM;
            }
            break;
        }
        default:
            sheetPopupInfo_.arrowPosition = SheetArrowPosition::NONE;
            break;
    }
}

void SheetWrapperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::PerformLayout(layoutWrapper);
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto sheetPageNode = sheetWrapperPattern->GetSheetPageNode();
    CHECK_NULL_VOID(sheetPageNode);
    auto sheetPagePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPagePattern);
    auto sheetType = sheetPagePattern->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "before popup sheet page, origin size [%{public}f, %{public}f]",
            sheetWidth_, sheetHeight_);
        OffsetF popupOffset = GetPopupStyleSheetOffset(layoutWrapper);
        auto hostNode = layoutWrapper->GetHostNode();
        CHECK_NULL_VOID(hostNode);
        auto wrapperOffset = hostNode->GetPaintRectOffset();
        sheetPopupInfo_.sheetOffsetX = popupOffset.GetX() - wrapperOffset.GetX();
        sheetPopupInfo_.sheetOffsetY = popupOffset.GetY() - wrapperOffset.GetY();
        TAG_LOGI(AceLogTag::ACE_SHEET, "checked offset (%{public}f, %{public}f), checked size [%{public}f, %{public}f]",
            sheetPopupInfo_.sheetOffsetX, sheetPopupInfo_.sheetOffsetY, sheetWidth_, sheetHeight_);
        RemeasureForPopup(layoutWrapper);
    }
    auto index = host->GetChildIndexById(sheetPageNode->GetId());
    auto sheetPageWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(sheetPageWrapper);
    sheetPageWrapper->Layout();
    LayoutMaskNode(layoutWrapper);
}

void SheetWrapperLayoutAlgorithm::LayoutMaskNode(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    if (!sheetWrapperPattern->ShowInUEC()) {
        return;
    }
    auto maskNode = sheetWrapperPattern->GetSheetMaskNode();
    CHECK_NULL_VOID(maskNode);
    auto maskPattern = maskNode->GetPattern<SheetMaskPattern>();
    CHECK_NULL_VOID(maskPattern);
    auto index = host->GetChildIndexById(maskNode->GetId());
    auto maskWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(maskWrapper);
    auto rect = sheetWrapperPattern->GetMainWindowRect();
    auto subContainer = AceEngine::Get().GetContainer(sheetWrapperPattern->GetSubWindowId());
    CHECK_NULL_VOID(subContainer);
    auto subWindowContext = AceType::DynamicCast<NG::PipelineContext>(subContainer->GetPipelineContext());
    CHECK_NULL_VOID(subWindowContext);
    auto subWindowGlobalRect = subWindowContext->GetDisplayWindowRectInfo();
    auto contentOffset = OffsetF(rect.GetX() - subWindowGlobalRect.Left(),
        rect.GetY() - subWindowGlobalRect.Top());
    auto geometryNode = maskWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    geometryNode->SetMarginFrameOffset(contentOffset);

    auto currentId = Container::CurrentId();
    SubwindowManager::GetInstance()->DeleteHotAreas(currentId, maskNode->GetId(), SubwindowType::TYPE_SHEET);
    if (maskPattern->GetIsMaskInteractive()) {
        std::vector<Rect> rects;
        auto maskHotRect = Rect(rect.GetX(), rect.GetY(),
            maskNode->GetGeometryNode()->GetFrameSize().Width(), maskNode->GetGeometryNode()->GetFrameSize().Height());
        rects.emplace_back(maskHotRect);
        auto subWindowMgr = SubwindowManager::GetInstance();
        subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_SHEET, maskNode->GetId(), currentId);
    }
    maskWrapper->Layout();
}

void SheetWrapperLayoutAlgorithm::RemeasureForPopup(LayoutWrapper* layoutWrapper)
{
    UpdateSheetNodePopupInfo(layoutWrapper);
}

bool SheetWrapperLayoutAlgorithm::IsTargetNodeHideByKeyboard(
    const SafeAreaInsets::Inset& keyboardInset, const RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, false);
    auto windowHeight = windowGlobalRect_.Height();
    auto keyboardHeight = keyboardInset.Length();
    auto targetRect = targetNode->GetPaintRectToWindowWithTransform();
    return GreatOrEqual(targetRect.Top(), windowHeight - keyboardHeight);
}

void SheetWrapperLayoutAlgorithm::UpdateSheetNodePopupInfo(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto sheetWrapperPattern = host->GetPattern<SheetWrapperPattern>();
    CHECK_NULL_VOID(sheetWrapperPattern);
    auto sheetNode = sheetWrapperPattern->GetSheetPageNode();
    CHECK_NULL_VOID(sheetNode);
    auto index = host->GetChildIndexById(sheetNode->GetId());
    auto sheetPageWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(sheetPageWrapper);
    auto sheetPageNode = sheetPageWrapper->GetHostNode();
    CHECK_NULL_VOID(sheetPageNode);
    auto sheetPagePattern = sheetPageNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPagePattern);
    sheetPagePattern->UpdateSheetPopupInfo(sheetPopupInfo_);
    auto sheetPageLayoutAlgorithmWrapper = sheetPageWrapper->GetLayoutAlgorithm();
    CHECK_NULL_VOID(sheetPageLayoutAlgorithmWrapper);
    auto sheetPageLayoutAlgorithm =
        DynamicCast<SheetPresentationLayoutAlgorithm>(sheetPageLayoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(sheetPageLayoutAlgorithm);
    sheetPageLayoutAlgorithm->UpdatePopupInfoAndRemeasure(layoutWrapper, sheetPopupInfo_, sheetWidth_, sheetHeight_);
}
} // namespace OHOS::Ace::NG
