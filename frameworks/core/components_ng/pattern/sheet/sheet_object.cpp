/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/sheet/sheet_object.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/animation/curve.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {

BorderWidthProperty SheetObject::PostProcessBorderWidth(const BorderWidthProperty& borderWidth)
{
    NG::BorderWidthProperty result = borderWidth;
    bool bottomDimenInvalid = !(sheetType_ == SheetType::SHEET_CENTER || sheetType_ == SheetType::SHEET_POPUP ||
        sheetType_ == SheetType::SHEET_BOTTOM_OFFSET);
    if (bottomDimenInvalid) {
        result.bottomDimen = 0.0_vp;
    }
    return result;
}

void SheetObject::DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper)
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto sheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(sheetLayoutAlgorithm);

    if (sheetLayoutAlgorithm->GetSheetMaxHeight() > 0) {
        pattern->SetSheetMaxHeight(
            sheetLayoutAlgorithm->GetSheetMaxHeight() - pattern->GetSheetTopSafeAreaNoProcess());
        pattern->SetSheetMaxWidth(sheetLayoutAlgorithm->GetSheetMaxWidth());
        pattern->SetPageHeight(sheetLayoutAlgorithm->GetSheetMaxHeight());
        pattern->SetCenterHeight(sheetLayoutAlgorithm->GetCenterHeight());
        if (!NearEqual(pattern->GetSheetOffsetX(), sheetLayoutAlgorithm->GetSheetOffsetX()) ||
            !NearEqual(pattern->GetSheetOffsetY(), sheetLayoutAlgorithm->GetSheetOffsetY())) {
            pattern->SetSheetOffsetX(sheetLayoutAlgorithm->GetSheetOffsetX());
            pattern->SetSheetOffsetY(sheetLayoutAlgorithm->GetSheetOffsetY());
            pattern->SetSheetArrowOffset(OffsetF(pattern->GetSheetPopupInfo().arrowOffsetX, .0f));
            pattern->SetWindowChanged(true);
        }
    }
    pattern->GetArrowOffsetByPlacement(sheetLayoutAlgorithm);
    pattern->InitialLayoutProps();
    pattern->UpdateDragBarStatus();
    pattern->CheckBuilderChange();
}

RefPtr<InterpolatingSpring> SheetObject::GetSheetTransitionCurve(float dragVelocity) const
{
    return AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
}

std::function<void()> SheetObject::GetSheetTransitionFinishEvent(bool isTransitionIn)
{
    const std::function<void()> event = [weak = pattern_, isTransitionIn]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (isTransitionIn) {
            if (!pattern->GetAnimationBreak()) {
                pattern->SetAnimationProcess(false);
                pattern->ChangeSheetPage(pattern->GetHeight());
            } else {
                pattern->SetAnimationBreak(false);
            }
            pattern->AvoidAiBar();
            pattern->FireOnDetentsDidChange(pattern->GetHeight());
            pattern->SetSpringBack(false);
        } else {
            pattern->SetAnimationProcess(false);
            const auto& overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            overlayManager->FireAutoSave(host);
            pattern->OnDisappear();
            overlayManager->RemoveSheet(host);
            pattern->FireCallback("false");
        }
    };
    return event;
}

std::function<void()> SheetObject::GetSheetAnimationEvent(bool isTransitionIn, float offset)
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(pattern, nullptr);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(pattern, nullptr);
    std::function<void()> event;
    if (isTransitionIn) {
        event = [context, offset]() {
            if (context) {
                context->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
            }
        };
    } else {
        event = [context, weak = pattern_, offset, isTransitionIn]() {
            if (context) {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->SheetTransitionAction(offset, false, isTransitionIn);
                pattern->DismissSheetShadow(context);
            }
        };
    }
    return event;
}

void SheetObject::ClipSheetNode()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto sheetSize = geometryNode->GetFrameSize();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sheetTheme = pipeline->GetTheme<SheetTheme>();
    CHECK_NULL_VOID(sheetTheme);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    pattern->ResetClipShape();
    auto sheetType = pattern->GetSheetType();
    BorderRadiusProperty borderRadius(sheetTheme->GetSheetRadius());
    pattern->CalculateSheetRadius(borderRadius);
    if (pattern->IsSheetBottom()) {
        // set 1px for avoiding doudble radius black lines.
        borderRadius.radiusBottomLeft = 1.0_px;
        borderRadius.radiusBottomRight = 1.0_px;
    }
    renderContext->UpdateBorderRadius(borderRadius);
    if (sheetTheme->IsOuterBorderEnable() && !sheetStyle.borderWidth.has_value()) {
        renderContext->UpdateOuterBorderRadius(borderRadius);
    }
    if (sheetType == SheetType::SHEET_POPUP && pattern->GetSheetPopupInfo().showArrow) {
        std::string clipPath = pattern->GetPopupStyleSheetClipPath(sheetSize, borderRadius);
        auto path = AceType::MakeRefPtr<Path>();
        path->SetValue(clipPath);
        path->SetBasicShapeType(BasicShapeType::PATH);
        renderContext->UpdateClipShape(path);
    }
}

void SheetObject::InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto sheetParent = AceType::DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        sheetPattern->SetCurrentHeight(overlayManager->GetSheetHeight());
        if (isFirstTransition) {
            float offset = sheetPattern->ComputeTransitionOffset(overlayManager->GetSheetHeight());
            sheetPattern->SheetTransitionAction(offset, true, isTransitionIn);
        }
        sheetPattern->FireOnTypeDidChange();
        sheetPattern->FireOnWidthDidChange();
        ACE_SCOPED_TRACE("Sheet start admission");
        sheetPattern->SetBottomStyleHotAreaInSubwindow();
    }
}

void SheetObject::SetFinishEventForAnimationOption(
    AnimationOption& option, bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    if (isTransitionIn) {
        option.SetOnFinishEvent([sheetWK = WeakClaim(RawPtr(sheetNode)), isFirst = isFirstTransition] {
            auto sheetNode = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheetNode);
            auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(pattern);
            if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
                isFirst) {
                pattern->OnAppear();
            }
            pattern->AvoidAiBar();
            const auto& overlay = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            pattern->FireOnDetentsDidChange(overlay->GetSheetHeight());
            pattern->FireOnHeightDidChange();
        });
    } else {
        option.SetOnFinishEvent([sheetWK = WeakClaim(RawPtr(sheetNode))] {
            auto sheet = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto pattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(pattern);
            auto overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            if (!sheet->GetPattern<SheetPresentationPattern>()->IsExecuteOnDisappear()) {
                sheet->GetPattern<SheetPresentationPattern>()->OnDisappear();
            }
            overlayManager->FireAutoSave(sheet);
            overlayManager->RemoveSheet(sheet);
        });
    }
}

AnimationOption SheetObject::GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    AnimationOption option;
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, option);
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    sheetPattern->SetSheetAnimationOption(option);
    if (isTransitionIn && sheetPattern->IsFoldStatusChanged()) {
        option.SetDuration(0);
        option.SetCurve(Curves::LINEAR);
    }
    SetFinishEventForAnimationOption(option, isTransitionIn, isFirstTransition);
    return option;
}

std::function<void()> SheetObject::GetAnimationPropertyCallForOverlay(bool isTransitionIn)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    const auto& overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_RETURN(overlayManager, nullptr);
    // compute the starting point of animation
    float offset = sheetPattern->ComputeTransitionOffset(overlayManager->GetSheetHeight());
    const std::function<void()> event = [sheetWK = WeakClaim(RawPtr(sheetNode)), offset, isTransitionIn]() {
        auto sheetNode = sheetWK.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        sheetPattern->SheetTransitionAction(offset, false, isTransitionIn);
    };
    return event;
}

void SheetObject::HandleDragStart()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->InitScrollProps();
    sheetPattern->SetIsDragging(true);
    if (sheetPattern->GetAnimation() && sheetPattern->GetAnimationProcess()) {
        AnimationUtils::StopAnimation(sheetPattern->GetAnimation());
        sheetPattern->SetAnimationBreak(true);
    }
    sheetPattern->SetCurrentOffset(0.0f);
    sheetPattern->SetIsDirectionUp(true);
}

void SheetObject::HandleDragUpdate(const GestureEvent& info)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetType = sheetPattern->GetSheetType();
    if (sheetType == SheetType::SHEET_POPUP) {
        return;
    }
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto tempOffset = sheetPattern->GetCurrentOffset();
    auto detentSize = sheetPattern->GetSheetDetentHeight().size();
    if (detentSize <= 0) {
        return;
    }
    auto height = sheetPattern->GetSheetHeightBeforeDragUpdate();
    auto maxDetentSize = sheetPattern->GetMaxSheetHeightBeforeDragUpdate();
    if (GreatOrEqual((height - sheetPattern->GetCurrentOffset()), maxDetentSize)) {
        if (LessNotEqual(mainDelta, 0) && GreatNotEqual(sheetPattern->GetSheetMaxHeight(), 0.0f)) {
            auto friction = sheetPattern->CalculateFriction(
                (height - sheetPattern->GetCurrentOffset()) / sheetPattern->GetSheetMaxHeight(),
                sheetPattern->GetRadio());
            mainDelta = mainDelta * friction;
        }
    }
    sheetPattern->SetCurrentOffset(sheetPattern->GetCurrentOffset() + mainDelta);
    if (NearEqual(sheetPattern->GetCurrentOffset(), tempOffset)) {
        return;
    }
    auto pageHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto offset = pageHeight - height + sheetPattern->GetCurrentOffset();
    if (LessOrEqual(offset, (pageHeight - sheetPattern->GetSheetMaxHeight()))) {
        offset = pageHeight - sheetPattern->GetSheetMaxHeight();
        sheetPattern->SetCurrentOffset(height - sheetPattern->GetSheetMaxHeight());
    }
    if (sheetPattern->IsNeedChangeScrollHeight(height - sheetPattern->GetCurrentOffset())) {
        sheetPattern->ChangeSheetPage(height - sheetPattern->GetCurrentOffset());
    }
    sheetPattern->HandleFollowAccessibilityEvent(height - sheetPattern->GetCurrentOffset());
    auto renderContext = host->GetRenderContext();
    renderContext->UpdateTransformTranslate({ 0.0f, offset, 0.0f });
    if (sheetPattern->IsSheetBottomStyle()) {
        sheetPattern->OnHeightDidChange(sheetPattern->GetHeight() -
            sheetPattern->GetCurrentOffset() + sheetPattern->GetSheetHeightUp());
    }
}

void SheetObject::HandleDragEnd(float dragVelocity)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->SetIsNeedProcessHeight(true);
    sheetPattern->SetIsDragging(false);
    auto sheetDetentsSize = sheetPattern->GetSheetDetentHeight().size();
    if ((sheetDetentsSize == 0) ||
        (sheetPattern->GetSheetType() == SheetType::SHEET_POPUP) ||
        sheetPattern->IsShowInSubWindowTwoInOne()) {
        return;
    }
    float upHeight = 0.0f;
    float downHeight = 0.0f;
    auto height = sheetPattern->GetSheetHeightBeforeDragUpdate();
    auto currentSheetHeight =
        GreatNotEqual((height - sheetPattern->GetCurrentOffset()), sheetPattern->GetSheetMaxHeight()) ?
            sheetPattern->GetSheetMaxHeight() : (height - sheetPattern->GetCurrentOffset());
    sheetPattern->SetStartProp(currentSheetHeight);
    TAG_LOGD(AceLogTag::ACE_SHEET, "Sheet HandleDragEnd, current height is: %{public}f", currentSheetHeight);

    // record the drag position
    uint32_t detentsLowerPos = 0;
    uint32_t detentsUpperPos = 0;
    sheetPattern->ComputeDetentsPos(currentSheetHeight, upHeight, downHeight, detentsLowerPos, detentsUpperPos);

    // when drag velocity is under the threshold and the sheet height is not in the middle of lower and upper bound.
    if ((LessNotEqual(std::abs(dragVelocity), SHEET_VELOCITY_THRESHOLD)) &&
        (!NearEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight)))) {
        // check whether the lower or upper index is closer to the current height of the sheet page
        if (GreatNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            if (NearZero(downHeight)) {
                sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE_DOWN, std::abs(dragVelocity));
            } else {
                sheetPattern->SetDetentsIndex(detentsLowerPos);
                sheetPattern->ChangeSheetHeight(downHeight);
                sheetPattern->SheetTransition(true, std::abs(dragVelocity));
            }
        } else if (LessNotEqual(std::abs(currentSheetHeight - upHeight), std::abs(currentSheetHeight - downHeight))) {
            sheetPattern->SetDetentsIndex(detentsUpperPos);
            sheetPattern->ChangeSheetHeight(upHeight);
            sheetPattern->SheetTransition(true, std::abs(dragVelocity));
        }
    } else {
        // when drag velocity is over the threshold
        if (GreatOrEqual(dragVelocity, 0.0f)) {
            if (NearZero(downHeight)) {
                sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE_DOWN, std::abs(dragVelocity));
            } else {
                sheetPattern->SetDetentsIndex(detentsLowerPos);
                sheetPattern->ChangeSheetHeight(downHeight);
                sheetPattern->SheetTransition(true, std::abs(dragVelocity));
            }
        } else {
            sheetPattern->SetDetentsIndex(detentsUpperPos);
            sheetPattern->ChangeSheetHeight(upHeight);
            sheetPattern->SheetTransition(true, std::abs(dragVelocity));
        }
    }

    // match the sorted detents index to the unsorted one
    auto detentHeight = sheetPattern->GetSheetDetentHeight()[sheetPattern->GetDetentsIndex()];
    auto unSortedSheetDentents = sheetPattern->GetUnSortedSheetDentents();
    auto pos = std::find(unSortedSheetDentents.begin(), unSortedSheetDentents.end(), detentHeight);
    if (pos != std::end(unSortedSheetDentents)) {
        auto idx = static_cast<uint32_t>(std::distance(unSortedSheetDentents.begin(), pos));
        sheetPattern->SetDetentsFinalIndex(idx);
    }
}

void SheetObject::OnScrollStartRecursive(float position, float velocity)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->InitScrollProps();
    if (sheetPattern->GetAnimation() && sheetPattern->GetAnimationProcess()) {
        AnimationUtils::StopAnimation(sheetPattern->GetAnimation());
        sheetPattern->SetAnimationBreak(true);
    }
    sheetPattern->SetCurrentOffset(0.0f);
    isSheetNeedScroll_ = false;
    sheetPattern->SetIsDirectionUp(true);
    sheetPattern->GetCurrentBroadcastDetentsIndex();
}

ScrollResult SheetObject::HandleScroll(float scrollOffset, int32_t source, NestedState state, float velocity)
{
    ScrollResult result = {scrollOffset, true};
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, result);
    if (state == NestedState::CHILD_CHECK_OVER_SCROLL) {
        return {scrollOffset, true};
    }
    if (GreatOrEqual(sheetPattern->GetCurrentOffset(), 0.0) && (source == SCROLL_FROM_UPDATE) && !isSheetNeedScroll_) {
        isSheetNeedScroll_ = true;
    }
    if (!isSheetNeedScroll_ || sheetPattern->IsScrollOutOfBoundary()) {
        return {scrollOffset, true};
    }
    ScrollState scrollState = source == SCROLL_FROM_ANIMATION ? ScrollState::FLING : ScrollState::SCROLL;
    if (state == NestedState::CHILD_SCROLL) {
        if (scrollState == ScrollState::SCROLL) {
            return HandleScrollWithSheet(scrollOffset);
        }
        HandleDragEnd(scrollOffset > 0 ? SHEET_VELOCITY_THRESHOLD : -SHEET_VELOCITY_THRESHOLD);
        isSheetPosChanged_ = false;
    } else if (state == NestedState::CHILD_OVER_SCROLL) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }
    return {0, true};
}

ScrollResult SheetObject::HandleScrollWithSheet(float scrollOffset)
{
    ScrollResult result = {scrollOffset, true};
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, result);
    auto sheetType = sheetPattern->GetSheetType();
    auto sheetDetentsSize = sheetPattern->GetSheetDetentHeight().size();
    if ((sheetType == SheetType::SHEET_POPUP) || (sheetDetentsSize == 0) || sheetPattern->IsShowInSubWindowTwoInOne()) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }
    auto currentHeightPos = sheetPattern->GetSheetHeightBeforeDragUpdate();
    bool isDraggingUp = LessNotEqual(scrollOffset, 0.0f);
    bool isReachMaxSheetHeight = GreatOrEqual(currentHeightPos, sheetPattern->GetMaxSheetHeightBeforeDragUpdate());
    // When dragging up the sheet, and sheet height is larger than sheet content height,
    // the sheet height should be updated.
    // When dragging up the sheet, and sheet height is less than or equal to sheet content height,
    // the sheet content should scrolling.
    if ((NearZero(sheetPattern->GetCurrentOffset())) && isDraggingUp && isReachMaxSheetHeight) {
        isSheetNeedScroll_ = false;
        return {scrollOffset, true};
    }
    // When dragging up the sheet, and sheet height is larger than max height,
    // should set the coefficient of friction.
    bool isExceedMaxSheetHeight = GreatNotEqual(
        (currentHeightPos - sheetPattern->GetCurrentOffset()), sheetPattern->GetMaxSheetHeightBeforeDragUpdate());
    bool isNeedCalculateFriction = isExceedMaxSheetHeight && isDraggingUp;
    if (isNeedCalculateFriction && GreatNotEqual(sheetPattern->GetSheetMaxHeight(), 0.0f)) {
        auto friction = sheetPattern->CalculateFriction(
            (currentHeightPos - sheetPattern->GetCurrentOffset()) / sheetPattern->GetSheetMaxHeight(),
            sheetPattern->GetRadio());
        scrollOffset = scrollOffset * friction;
    }

    sheetPattern->SetCurrentOffset(sheetPattern->GetCurrentOffset() + scrollOffset);
    auto pageHeight = sheetPattern->GetPageHeightWithoutOffset();
    auto sheetOffsetInPage = pageHeight - currentHeightPos + sheetPattern->GetCurrentOffset();
    if (LessOrEqual(sheetOffsetInPage, pageHeight - sheetPattern->GetSheetMaxHeight())) {
        sheetOffsetInPage = pageHeight - sheetPattern->GetSheetMaxHeight();
        sheetPattern->SetCurrentOffset(currentHeightPos - sheetPattern->GetSheetMaxHeight());
    }
    if (sheetPattern->IsNeedChangeScrollHeight(currentHeightPos - sheetPattern->GetCurrentOffset())) {
        sheetPattern->ChangeSheetPage(currentHeightPos - sheetPattern->GetCurrentOffset());
    }
    sheetPattern->HandleFollowAccessibilityEvent(currentHeightPos - sheetPattern->GetCurrentOffset());
    result = {0, true};
    auto renderContext = sheetPattern->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, result);
    renderContext->UpdateTransformTranslate({ 0.0f, sheetOffsetInPage, 0.0f });
    isSheetPosChanged_ = NearZero(scrollOffset) ? false : true;
    if (sheetPattern->IsSheetBottomStyle()) {
        sheetPattern->OnHeightDidChange(sheetPattern->GetHeight() -
            sheetPattern->GetCurrentOffset() + sheetPattern->GetSheetHeightUp());
    }
    isSheetPosChanged_ = true;
    return result;
}

void SheetObject::OnScrollEndRecursive(const std::optional<float>& velocity)
{
    if (isSheetPosChanged_) {
        HandleDragEnd(velocity.value_or(0.f));
        isSheetPosChanged_ = false;
    }
}

bool SheetObject::HandleScrollVelocity(float velocity)
{
    if (isSheetPosChanged_) {
        HandleDragEnd(velocity);
        isSheetPosChanged_ = false;
    }
    // Use child edge effect
    if (!isSheetNeedScroll_) {
        return false;
    }
    return true;
}

void SheetObject::ModifyFireSheetTransition(float dragVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "ModifyFireSheetTransition function enter");
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(
        dragVelocity / SHEET_VELOCITY_THRESHOLD, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    auto offset = sheetPattern->UpdateSheetTransitionOffset();
    CreatePropertyCallback();
    auto property = sheetPattern->GetProperty();
    CHECK_NULL_VOID(property);
    renderContext->AttachNodeAnimatableProperty(property);
    property->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);

    auto finishCallback = [weak = AceType::WeakClaim(RawPtr(sheetPattern))]() {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        if (!ref->GetAnimationBreak()) {
            ref->SetAnimationProcess(false);
            ref->ChangeSheetPage(ref->GetHeight());
        } else {
            ref->SetAnimationBreak(false);
        }
        ref->AvoidAiBar();
        ref->SetIsNeedProcessHeight(false);
        ref->FireOnDetentsDidChange(ref->GetHeight());
        ref->SetPreDidHeight(ref->GetHeight());
        ref->SetSpringBack(false);
    };

    sheetPattern->SetAnimationProcess(true);
    sheetPattern->HandleDragEndAccessibilityEvent();
    property->Set(sheetPattern->GetStartProp());
    sheetPattern->SetBottomStyleHotAreaInSubwindow();
    std::shared_ptr<AnimationUtils::Animation> animation = AnimationUtils::StartAnimation(option,
        [weak = AceType::WeakClaim(RawPtr(sheetPattern)), renderContext, offset]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (renderContext) {
                ref->GetProperty()->Set(ref->GetHeight() + ref->GetSheetHeightUp());
            }
        },
        finishCallback);
    sheetPattern->SetAnimation(animation);
}

void SheetObject::CreatePropertyCallback()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    if (sheetPattern->GetProperty()) {
        return;
    }
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto propertyCallback = [weak = AceType::WeakClaim(RawPtr(sheetPattern)), renderContext](float position) {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->OnHeightDidChange(static_cast<int>(position));

        /*
         * Variables in formulas:
         *   position:        Current sheet position (Y coordinate)
         *   position_delta:  Position change during drag gesture
         *   sheetHeightUp_:  Additional height when sheet is dragged upward
         *   height_:         Base height of the sheet component
         *   offset:          Vertical translation offset for sheet positioning
         *   pageHeight:      Full height of the containing page
         *   currentOffset_:  Accumulated vertical offset during dragging
         *   GetPageHeightWithoutOffset(): Gets page height excluding insets/offsets
         *   GetSheetHeightBeforeDragUpdate(): Sheet height prior to drag updates
         *
         * Position derivation:
         *   position = height_ - position_delta + sheetHeightUp_
         *
         * Offset calculation chain:
         *   offset = pageHeight - height + currentOffset_
         *          = GetPageHeightWithoutOffset() - GetSheetHeightBeforeDragUpdate() + position_delta
         *          = GetPageHeightWithoutOffset() - (height_ + sheetHeightUp_) + position_delta
         *          = GetPageHeightWithoutOffset() - (position + position_delta) + position_delta
         *
         * Simplified offset formula:
         *   offset = GetPageHeightWithoutOffset() - position
         */
        float targetTranslateY = ref->GetPageHeightWithoutOffset() - position;
        renderContext->UpdateTransformTranslate({0.0f, targetTranslateY, 0.0f});
        ref->ChangeSheetPage(position);
    };
    auto property = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    sheetPattern->SetProperty(property);
}

SheetKeyboardAvoidMode SheetObject::GetAvoidKeyboardModeByDefault() const
{
    if (sheetType_ == SheetType::SHEET_POPUP) {
        return SheetKeyboardAvoidMode::NONE;
    }
    return SheetKeyboardAvoidMode::TRANSLATE_AND_SCROLL;
}

void SheetObject::AvoidKeyboardInDirtyLayoutProcess()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    if (sheetType_ == SheetType::SHEET_POPUP) {
        return;
    }
    if (sheetPattern->IsWindowRotate()) {
        // When rotating the screen,
        // first switch the sheet to the position corresponding to the proportion before rotation
        sheetPattern->TranslateTo(sheetPattern->GetPageHeightWithoutOffset() - sheetPattern->GetHeight());
        sheetPattern->SetWindowRotate(false);
    } else {
        // After rotation, if need to avoid the keyboard, trigger the avoidance behavior
        AvoidKeyboard(false);
    }
}

void SheetObject::AvoidKeyboard(bool forceAvoid)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->AvoidKeyboard(forceAvoid);
}
} // namespace OHOS::Ace::NG
