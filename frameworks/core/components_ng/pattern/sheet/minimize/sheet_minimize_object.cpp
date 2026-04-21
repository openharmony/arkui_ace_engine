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

#include "core/components_ng/pattern/sheet/minimize/sheet_minimize_object.h"
#include "core/components_ng/pattern/sheet/minimize/sheet_presentation_minimize_layout_algorithm.h"


#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {

constexpr float DEFAULT_SCALE = 1.05f;
constexpr float HALF = 0.5f;
constexpr int32_t DEFAULT_DURATION = 30;

constexpr Dimension SHEET_MINIMIZE_BORDER_RADIUS = 12.0_vp;

NG::BorderWidthProperty SheetMinimizeObject::PostProcessBorderWidth(const NG::BorderWidthProperty& borderWidth)
{
    return borderWidth;
}

void SheetMinimizeObject::DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper)
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto minimizeSheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationMinimizeLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(minimizeSheetLayoutAlgorithm);
    if (minimizeSheetLayoutAlgorithm->GetMinimizeSheetMaxWidth() > 0) {
        sheetMaxWidth_ = minimizeSheetLayoutAlgorithm->GetMinimizeSheetMaxWidth();
        sheetWidth_ = minimizeSheetLayoutAlgorithm->GetMinimizeSheetWidth();
        pattern->SetSheetMaxHeight(minimizeSheetLayoutAlgorithm->GetMinimizeSheetMaxHeight());
    }
    if (GreatNotEqual(minimizeSheetLayoutAlgorithm->GetSheetHeight(), 0.0f)) {
        SetSheetHeight(minimizeSheetLayoutAlgorithm->GetSheetHeight());
    }
    UpdateDragBarStatus();
    UpdateMinimizePosition();
}

void SheetMinimizeObject::UpdateDragBarStatus()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);

    auto sheetPattern = host->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetDragBar = sheetPattern->GetDragBarNode();
    CHECK_NULL_VOID(sheetDragBar);
    auto dragBarLayoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);

    dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
}

void SheetMinimizeObject::UpdateMinimizePosition()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    dragOffsetAddUp_ = OffsetF(0.0f, 0.0f);
}

RefPtr<InterpolatingSpring> SheetMinimizeObject::GetSheetTransitionCurve(float dragVelocity) const
{
    return AceType::MakeRefPtr<InterpolatingSpring>(
        0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
}

std::function<void()> SheetMinimizeObject::GetSheetTransitionFinishEvent(bool isTransitionIn)
{
    const std::function<void()> event = [weak = pattern_, isTransitionIn]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (isTransitionIn) {
            if (!pattern->GetAnimationBreak()) {
                pattern->SetAnimationProcess(false);
            } else {
                pattern->SetAnimationBreak(false);
            }
            pattern->AvoidAiBar();
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

std::function<void()> SheetMinimizeObject::GetSheetAnimationEvent(bool isTransitionIn, float offset)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());

    std::function<void()> event;
    if (!sheetStyle.interactive.value_or(false)) {
        if (isTransitionIn) {
            event = [weak = WeakClaim(this)]() {
                auto sheetObject = weak.Upgrade();
                CHECK_NULL_VOID(sheetObject);
                sheetObject->TransformTranslateEnter();
            };
        } else {
            event = [context, weak = pattern_, objWeak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto sheetObject = objWeak.Upgrade();
                CHECK_NULL_VOID(sheetObject);
                sheetObject->TransformTranslateExit();
                pattern->DismissSheetShadow(context);
            };
        }
    } else {
        CreatePropertyCallback();
        auto property = sheetPattern->GetProperty();
        CHECK_NULL_RETURN(property, nullptr);
        event = [weak = pattern_, isTransitionIn, objWeak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto sheetObject = objWeak.Upgrade();
            CHECK_NULL_VOID(sheetObject);
        };
    }
    return event;
}

void SheetMinimizeObject::ClipSheetNode()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
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
    BorderRadiusProperty borderRadius(SHEET_MINIMIZE_BORDER_RADIUS);
    renderContext->UpdateBorderRadius(borderRadius);
}

void SheetMinimizeObject::InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto sheetParent = AceType::DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        if (isFirstTransition) {
            TransformTranslateExit();
            sheetPattern->GetBuilderInitHeight();
        }
        sheetPattern->FireOnTypeDidChange();
        ACE_SCOPED_TRACE("Minimize Sheet starts the entrance animation");
    }
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    if (sheetStyle.interactive.value_or(false)) {
        CreatePropertyCallback();
        auto property = sheetPattern->GetProperty();
        CHECK_NULL_VOID(property);
        auto renderContext = sheetNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
    }
}

void SheetMinimizeObject::SetFinishEventForAnimationOption(
    AnimationOption& option, bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    if (isTransitionIn) {
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode)), isFirst = isFirstTransition, objWeak = WeakClaim(this)] {
                auto sheetObject = objWeak.Upgrade();
                CHECK_NULL_VOID(sheetObject);
                auto sheetNode = sheetWK.Upgrade();
                CHECK_NULL_VOID(sheetNode);
                auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
                CHECK_NULL_VOID(pattern);
                pattern->OnAppear();
                pattern->AvoidAiBar();
                sheetObject->FireHeightDidChange();
                pattern->FireOnWidthDidChange();
            });
    } else {
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode))] {
            auto sheet = sheetWK.Upgrade();
            CHECK_NULL_VOID(sheet);
            auto pattern = sheet->GetPattern<SheetPresentationPattern>();
            CHECK_NULL_VOID(pattern);
            auto overlayManager = pattern->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            pattern->OnDisappear();
            overlayManager->FireAutoSave(sheet);
            overlayManager->RemoveSheet(sheet);
        });
    }
}

AnimationOption SheetMinimizeObject::GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    AnimationOption option;
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, option);
    const RefPtr<InterpolatingSpring> curve =
        AceType::MakeRefPtr<InterpolatingSpring>(0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
    option.SetCurve(curve);
    option.SetFillMode(FillMode::FORWARDS);
    option.SetDuration(SHEET_ANIMATION_DURATION);
    SetFinishEventForAnimationOption(option, isTransitionIn, isFirstTransition);
    return option;
}

void SheetMinimizeObject::TransformTranslateEnter()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
}

void SheetMinimizeObject::TransformTranslateExit()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
}

std::function<void()> SheetMinimizeObject::GetAnimationPropertyCallForOverlay(bool isTransitionIn)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto layoutProperty = sheetNode->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());

    std::function<void()> event;
    if (!sheetStyle.interactive.value_or(false)) {
        if (isTransitionIn) {
            event = [weak = WeakClaim(this)]() {
                auto sheetObject = weak.Upgrade();
                CHECK_NULL_VOID(sheetObject);
                sheetObject->TransformTranslateEnter();
            };
        } else {
            event = [context, weak = pattern_, objWeak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                auto sheetObject = objWeak.Upgrade();
                CHECK_NULL_VOID(sheetObject);
                sheetObject->TransformTranslateExit();
                pattern->DismissSheetShadow(context);
            };
        }
    } else {
        event = [weak = pattern_, isTransitionIn, objWeak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto sheetObject = objWeak.Upgrade();
            CHECK_NULL_VOID(sheetObject);
        };
    }
    return event;
}

void SheetMinimizeObject::OnLanguageConfigurationUpdate()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->CheckLocalized();
    CHECK_NULL_VOID(sheetPattern->GetShowState());
    CHECK_NULL_VOID(!sheetPattern->GetIsPlayTransition());
    TransformTranslateEnter();
}

PaddingPropertyF SheetMinimizeObject::GetSheetSafeAreaPadding() const
{
    PaddingPropertyF padding;
    padding.left = 0.0f;
    padding.right = 0.0f;
    padding.top = 0.0f;
    padding.bottom = 0.0f;
    return padding;
}

void SheetMinimizeObject::HandleDragStart()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    InitScrollProps();
    sheetPattern->SetIsDragging(false);
    currentOffset_ = 0.0f;

    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto geometry = host->GetGeometryNode();
    CHECK_NULL_VOID(geometry);
    // with parent padding
    dragStartOffset_ = geometry->GetMarginFrameOffset();
    const auto& overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto sheetDragPauseFunc = overlayManager->GetOnSheetMiniDragStartCallback();
    if (sheetDragPauseFunc) {
        sheetDragPauseFunc();
    }
    HandleDragStartAnimation();
}

void SheetMinimizeObject::HandleDragUpdate(const GestureEvent& info)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    OffsetF gestureOffset(info.GetOffsetX(), info.GetOffsetY());
    gestureOffset = gestureOffset + dragOffsetAddUp_;
    renderContext->UpdateTransformTranslate({ gestureOffset.GetX(), gestureOffset.GetY(), 0.0f });
}

void SheetMinimizeObject::HandleDragUpdateForLTR(const GestureEvent& info)
{
}

void SheetMinimizeObject::HandleDragUpdateForRTL(const GestureEvent& info)
{
}

void SheetMinimizeObject::HandleDragEnd(float dragVelocity)
{
}

void SheetMinimizeObject::HandleDragEndForLTR(float dragVelocity)
{
}

void SheetMinimizeObject::HandleDragEndForRTL(float dragVelocity)
{
}

void SheetMinimizeObject::HandleDragStartAnimation()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->HasTransformScale()) {
        prevScale_ = renderContext->GetTransformScaleValue({ 1.0f, 1.0f });
    } else {
        renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    }

    AnimationOption option;
    /* 0.5:init velocity, 350:stiffness, 35:damping */
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.5, 1, 350, 35));
    option.SetDuration(DEFAULT_DURATION);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
            CHECK_NULL_VOID(sheetObject);
            auto sheetPattern = sheetObject->GetPattern();
            CHECK_NULL_VOID(sheetPattern);
            auto host = sheetPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            auto newScale = sheetObject->prevScale_ * DEFAULT_SCALE;
            renderContext->UpdateTransformScale(newScale);
        },
        option.GetOnFinishEvent(), nullptr, context
    );
}

void SheetMinimizeObject::HandleTransformScale()
{
    AnimationOption option;
    /* 0.5:init velocity, 350:stiffness, 35:damping */
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.5, 1, 350, 35));
    option.SetDuration(DEFAULT_DURATION);
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    AnimationUtils::Animate(option, [weak = WeakClaim(this)]() {
            auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
            CHECK_NULL_VOID(sheetObject);
            auto sheetPattern = sheetObject->GetPattern();
            CHECK_NULL_VOID(sheetPattern);
            auto host = sheetPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformScale(sheetObject->prevScale_);
        },
        option.GetOnFinishEvent(), nullptr, context
    );
}

SheetPositionInfo SheetMinimizeObject::GetSheetPositionInfo()
{
    SheetPositionInfo resInfo = SheetPositionInfo();
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, resInfo);
    auto sheetObject = sheetPattern->GetHost();
    auto parent = sheetObject->GetParentFrameNode();
    CHECK_NULL_RETURN(parent, resInfo);
    auto parentGeometry = parent->GetGeometryNode();
    CHECK_NULL_RETURN(parentGeometry, resInfo);
    CHECK_NULL_RETURN(parentGeometry->GetPadding(), resInfo);
    float left = parentGeometry->GetPadding()->left.value_or(0.0f);
    float top = parentGeometry->GetPadding()->top.value_or(0.0f);
    float right = parentGeometry->GetPadding()->right.value_or(0.0f);
    float bottom = parentGeometry->GetPadding()->bottom.value_or(0.0f);

    auto sheetMiniDeviceMarginWidth = sheetPattern->GetSheetMiniDeviceMarginWidth();
    auto sheetMiniDeviceMarginHeight = sheetPattern->GetSheetMiniDeviceMarginHeight();
    CHECK_NULL_RETURN(sheetMiniDeviceMarginWidth, resInfo);
    CHECK_NULL_RETURN(sheetMiniDeviceMarginHeight, resInfo);

    resInfo.parentLeftConstraint = left + sheetMiniDeviceMarginWidth.value().ConvertToPx();
    resInfo.parentTopConstraint = top + sheetMiniDeviceMarginHeight.value().ConvertToPx();
    resInfo.parentRightConstraint =
        parentGeometry->GetFrameSize().Width() - right - sheetMiniDeviceMarginWidth.value().ConvertToPx();
    resInfo.parentBottomConstraint =
        parentGeometry->GetFrameSize().Height() - bottom - sheetMiniDeviceMarginHeight.value().ConvertToPx();

    resInfo.sheetOffset = dragOffsetAddUp_ + dragStartOffset_;
    auto sheetObjectGeometry = sheetObject->GetGeometryNode();
    CHECK_NULL_RETURN(sheetObjectGeometry, resInfo);
    resInfo.sheetWidth = sheetObjectGeometry->GetMarginFrameSize().Width();
    resInfo.sheetHeight = sheetObjectGeometry->GetMarginFrameSize().Height();
    
    return resInfo;
}

OffsetF SheetMinimizeObject::CalcDragOutOfBoundsPosition()
{
    SheetPositionInfo sheetInfo = GetSheetPositionInfo();

    // check: bottom -> right -> top -> left
    auto fixOffet = OffsetF(0.0f, 0.0f);
    auto sheetObjectBottom = sheetInfo.sheetOffset.GetY() + sheetInfo.sheetHeight;
    if (sheetObjectBottom > sheetInfo.parentBottomConstraint) {
        fixOffet = OffsetF(0.0f, sheetInfo.parentBottomConstraint - sheetObjectBottom);
        dragOffsetAddUp_ = dragOffsetAddUp_ + fixOffet;
        sheetInfo.sheetOffset = dragOffsetAddUp_ + dragStartOffset_;
    }
    auto sheetObjectRight = sheetInfo.sheetOffset.GetX() + sheetInfo.sheetWidth;
    if (sheetObjectRight > sheetInfo.parentRightConstraint) {
        fixOffet = OffsetF(sheetInfo.parentRightConstraint - sheetObjectRight, 0.0f);
        dragOffsetAddUp_ = dragOffsetAddUp_ + fixOffet;
        sheetInfo.sheetOffset = dragOffsetAddUp_ + dragStartOffset_;
    }
    auto sheetObjectTop = sheetInfo.sheetOffset.GetY();
    if (sheetObjectTop < sheetInfo.parentTopConstraint) {
        fixOffet = OffsetF(0.0f, sheetInfo.parentTopConstraint - sheetObjectTop);
        dragOffsetAddUp_ = dragOffsetAddUp_ + fixOffet;
        sheetInfo.sheetOffset = dragOffsetAddUp_ + dragStartOffset_;
    }
    auto sheetObjectleft = sheetInfo.sheetOffset.GetX();
    if (sheetObjectleft < sheetInfo.parentLeftConstraint) {
        fixOffet = OffsetF(sheetInfo.parentLeftConstraint - sheetObjectleft, 0.0f);
        dragOffsetAddUp_ = dragOffsetAddUp_ + fixOffet;
        sheetInfo.sheetOffset = dragOffsetAddUp_ + dragStartOffset_;
    }

    return dragOffsetAddUp_;
}

OffsetF SheetMinimizeObject::CalcDragAdsorbePosition()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, OffsetF(0.0f, 0.0f));

    SheetPositionInfo sheetInfo = GetSheetPositionInfo();
    OffsetF sheetObjectCentor;
    sheetObjectCentor.SetX(sheetInfo.sheetOffset.GetX() + HALF * sheetInfo.sheetWidth);
    sheetObjectCentor.SetY(sheetInfo.sheetOffset.GetY() + HALF * sheetInfo.sheetHeight);
    OffsetF sheetParentCentor;
    sheetParentCentor.SetX(
        sheetInfo.parentLeftConstraint + HALF * (sheetInfo.parentRightConstraint - sheetInfo.parentLeftConstraint));
    sheetParentCentor.SetY(
        sheetInfo.parentTopConstraint + HALF * (sheetInfo.parentBottomConstraint - sheetInfo.parentTopConstraint));

    SheetMiniDefaultShowPosition showPosition = SheetMiniDefaultShowPosition::RightTop; // default
    if (sheetObjectCentor.GetX() < sheetParentCentor.GetX()) {
        if (sheetObjectCentor.GetY() < sheetParentCentor.GetY()) {
            showPosition = SheetMiniDefaultShowPosition::LeftTop;
        } else {
            showPosition = SheetMiniDefaultShowPosition::LeftBottom;
        }
    } else {
        if (sheetObjectCentor.GetY() < sheetParentCentor.GetY()) {
            showPosition = SheetMiniDefaultShowPosition::RightTop;
        } else {
            showPosition = SheetMiniDefaultShowPosition::RightBottom;
        }
    }
    sheetPattern->SetSheetMiniDefaultShowPosition(showPosition);

    auto fixOffet = OffsetF(0.0f, 0.0f);
    if (showPosition == SheetMiniDefaultShowPosition::LeftTop ||
        showPosition == SheetMiniDefaultShowPosition::LeftBottom) {
        fixOffet.SetX(sheetInfo.parentLeftConstraint - sheetInfo.sheetOffset.GetX());
    }
    if (showPosition == SheetMiniDefaultShowPosition::RightTop ||
        showPosition == SheetMiniDefaultShowPosition::RightBottom) {
        fixOffet.SetX(sheetInfo.parentRightConstraint - sheetInfo.sheetOffset.GetX() - sheetInfo.sheetWidth);
    }

    dragOffsetAddUp_ = dragOffsetAddUp_ + fixOffet;
    return dragOffsetAddUp_;
}

void SheetMinimizeObject::HandleEndPosition()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto finalShowPosition = CalcDragOutOfBoundsPosition();
    finalShowPosition = CalcDragAdsorbePosition();

    AnimationOption optionX;
    auto curveX = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.3, 0.9);
    optionX.SetCurve(curveX);
    optionX.SetDuration(DEFAULT_DURATION);
    AnimationOption optionY;
    auto curveY = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.4, 0.8);
    optionY.SetCurve(curveY);
    optionY.SetDuration(DEFAULT_DURATION);

    AnimationUtils::Animate(optionX, [finalShowPosition, weak = WeakClaim(this)]() {
            auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
            CHECK_NULL_VOID(sheetObject);
            auto sheetPattern = sheetObject->GetPattern();
            CHECK_NULL_VOID(sheetPattern);
            auto host = sheetPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformTranslate({ finalShowPosition.GetX(), 0.0f, 0.0f });
        },
        optionX.GetOnFinishEvent(), nullptr, context
    );
    AnimationUtils::Animate(optionY, [finalShowPosition, weak = WeakClaim(this)]() {
            auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
            CHECK_NULL_VOID(sheetObject);
            auto sheetPattern = sheetObject->GetPattern();
            CHECK_NULL_VOID(sheetPattern);
            auto host = sheetPattern->GetHost();
            CHECK_NULL_VOID(host);
            auto renderContext = host->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateTransformTranslate({ finalShowPosition.GetX(), finalShowPosition.GetY(), 0.0f });
        },
        optionY.GetOnFinishEvent(), nullptr, context
    );
}

void SheetMinimizeObject::HandleDragEndResumeAurora()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    const auto& overlayManager = sheetPattern->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto sheetDragResumeFunc = overlayManager->GetOnSheetMiniDragResumeCallback();
    if (sheetDragResumeFunc) {
        sheetDragResumeFunc();
    }
}

void SheetMinimizeObject::HandleDragEndAnimation()
{
    // start animation to reset transformscale.
    HandleTransformScale();

    HandleEndPosition();

    HandleDragEndResumeAurora();
}

void SheetMinimizeObject::HandleOnDragCancel()
{
    HandleDragEndAnimation();
}

void SheetMinimizeObject::HandleOnDragEnd(const GestureEvent& info)
{
    OffsetF gestureOffset(info.GetOffsetX(), info.GetOffsetY());
    dragOffsetAddUp_ = dragOffsetAddUp_ + gestureOffset;
    HandleDragEndAnimation();
}

void SheetMinimizeObject::InitDragDropEvent()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);

    dragOffsetAddUp_ = OffsetF(0.0f, 0.0f);
    if (panEvent_) {
        return;
    }

    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
        CHECK_NULL_VOID(sheetObject);
        sheetObject->HandleDragStart();
    };

    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
        CHECK_NULL_VOID(sheetObject);
        sheetObject->HandleDragUpdate(info);
    };

    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
        CHECK_NULL_VOID(sheetObject);
        sheetObject->HandleOnDragCancel();
    };

    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto sheetObject = AceType::DynamicCast<SheetMinimizeObject>(weak.Upgrade());
        CHECK_NULL_VOID(sheetObject);
        sheetObject->HandleOnDragEnd(info);
    };

    PanDirection panDirection;
    panDirection.type = GetPanDirection();
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distanceMap);
}

void SheetMinimizeObject::ModifyFireSheetTransition(float dragVelocity)
{
    TAG_LOGD(AceLogTag::ACE_SHEET, "SideSheet ModifyFireSheetTransition");
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

    auto offsetX = 0.0f;
    auto width = sheetWidth_;
    offsetX = sheetMaxWidth_ - width;

    CreatePropertyCallback();
    auto property = sheetPattern->GetProperty();
    CHECK_NULL_VOID(property);

    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto interactive = sheetStyle.interactive.value_or(false);
    auto finishCallback =
        [weak = AceType::WeakClaim(RawPtr(sheetPattern)), interactive, offsetX, objWeak = WeakClaim(this)]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (!ref->GetAnimationBreak()) {
                ref->SetAnimationProcess(false);
            } else {
                ref->SetAnimationBreak(false);
            }
            auto sheetObject = objWeak.Upgrade();
            CHECK_NULL_VOID(sheetObject);
            if (!interactive && !NearEqual(sheetObject->GetMinimizeSheetWidth(), 0)) {
                ref->onWidthDidChange(sheetObject->GetMinimizeSheetWidth());
            }
            ref->AvoidAiBar();
            ref->SetSpringBack(false);
        };

    sheetPattern->SetAnimationProcess(true);
    auto pipeline = host->GetContextRefPtr();
    std::shared_ptr<AnimationUtils::Animation> animation = AnimationUtils::StartAnimation(
        option,
        [weak = AceType::WeakClaim(RawPtr(sheetPattern)), renderContext, offsetX, width, interactive]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (interactive) {
                ref->GetProperty()->Set(width);
            }
            if (renderContext && !interactive) {
                renderContext->UpdateTransformTranslate({ 0.0f, 0.0, 0.0f });
            }
        },
        finishCallback, nullptr, pipeline);
    sheetPattern->SetAnimation(animation);
}

void SheetMinimizeObject::CreatePropertyCallback()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    if (sheetPattern->GetProperty()) {
        return;
    }
    auto propertyCallback = [weak = AceType::WeakClaim(RawPtr(sheetPattern)), objWeak = WeakClaim(this)](
                                float position) {
        // The position is the displayed size
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->onWidthDidChange(static_cast<int>(position));

        auto sheetNode = ref->GetHost();
        CHECK_NULL_VOID(sheetNode);
        auto context = sheetNode->GetRenderContext();
        CHECK_NULL_VOID(context);
        auto sheetObject = objWeak.Upgrade();
        CHECK_NULL_VOID(sheetObject);
        context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    };
    ACE_UINODE_TRACE(sheetPattern->GetHost());
    auto property = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    sheetPattern->SetProperty(property);
}

SheetKeyboardAvoidMode SheetMinimizeObject::GetAvoidKeyboardModeByDefault() const
{
    return SheetKeyboardAvoidMode::NONE;
}

void SheetMinimizeObject::BeforeCreateLayoutWrapper()
{
    AvoidKeyboard(false);

    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollablePattern = scrollNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollablePattern);
    scrollablePattern->SetNeedFullSafeArea(false);
}

void SheetMinimizeObject::AvoidKeyboard(bool forceAvoid)
{
}

void SheetMinimizeObject::FireHeightDidChange()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto preDidHeight = pattern->GetPreDidHeight();
    if (NearEqual(preDidHeight, sheetHeight_)) {
        return;
    }
    pattern->OnHeightDidChange(sheetHeight_);
    pattern->SetPreDidHeight(sheetHeight_);
}
} // namespace OHOS::Ace::NG