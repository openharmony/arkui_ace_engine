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

#include "core/components_ng/pattern/sheet/side/sheet_side_object.h"

#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"

namespace OHOS::Ace::NG {

NG::BorderWidthProperty SheetSideObject::PostProcessBorderWidth(const NG::BorderWidthProperty& borderWidth)
{
    NG::BorderWidthProperty result = borderWidth;
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        result.leftDimen = 0.0_vp;
    } else {
        result.rightDimen = 0.0_vp;
    }
    return result;
}

void SheetSideObject::DirtyLayoutProcess(const RefPtr<LayoutAlgorithmWrapper>& layoutAlgorithmWrapper)
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto sideSheetLayoutAlgorithm =
        AceType::DynamicCast<SheetPresentationSideLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_VOID(sideSheetLayoutAlgorithm);
    if (sideSheetLayoutAlgorithm->GetSideSheetMaxWidth() > 0) {
        sheetMaxWidth_ = sideSheetLayoutAlgorithm->GetSideSheetMaxWidth();
        sheetWidth_ = sideSheetLayoutAlgorithm->GetSideSheetWidth();
        pattern->SetCenterHeight(sideSheetLayoutAlgorithm->GetCenterHeight());
        pattern->SetSheetMaxHeight(sideSheetLayoutAlgorithm->GetSideSheetMaxHeight());
    }
    UpdateDragBarStatus();
    UpdateSidePosition();
}

void SheetSideObject::UpdateDragBarStatus()
{
    auto pattern = GetPattern();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);

    auto titleColumn = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(titleColumn);
    auto sheetDragBar = AceType::DynamicCast<FrameNode>(titleColumn->GetFirstChild());
    CHECK_NULL_VOID(sheetDragBar);
    auto dragBarLayoutProperty = sheetDragBar->GetLayoutProperty();
    CHECK_NULL_VOID(dragBarLayoutProperty);

    dragBarLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
    sheetDragBar->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetSideObject::UpdateSidePosition()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);

    if (!sheetPattern->IsOnAppearing()
        && !sheetPattern->IsOnDisappearing() && !sheetPattern->IsDragging()) {
        sheetPattern->FireOnWidthDidChange();
        sheetPattern->FireOnHeightDidChange();
        bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (!isRTL) {
            context->UpdateTransformTranslate({ sheetMaxWidth_ - sheetWidth_, 0.0f, 0.0f });
        } else {
            context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
        }
    }
}

RefPtr<InterpolatingSpring> SheetSideObject::GetSheetTransitionCurve(float dragVelocity) const
{
    return AceType::MakeRefPtr<InterpolatingSpring>(
        0.0f, CURVE_MASS, CURVE_STIFFNESS, CURVE_DAMPING);
}

std::function<void()> SheetSideObject::GetSheetTransitionFinishEvent(bool isTransitionIn)
{
    const std::function<void()> event = [weak = pattern_, isTransitionIn]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (isTransitionIn) {
            if (!pattern->GetAnimationBreak()) {
                pattern->SetAnimationProcess(false);
                pattern->GetSheetObject()->SetCurrentOffset(0.0f);
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

std::function<void()> SheetSideObject::GetSheetAnimationEvent(bool isTransitionIn, float offset)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);

    std::function<void()> event;
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
    return event;
}


void SheetSideObject::ClipSheetNode()
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
    BorderRadiusProperty borderRadius(sheetTheme->GetSheetSideRadius());
    pattern->CalculateSheetRadius(borderRadius);
    // set 1px for avoiding doudble radius black lines.
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        borderRadius.radiusTopLeft = 1.0_px;
        borderRadius.radiusBottomLeft = 1.0_px;
    } else {
        borderRadius.radiusTopRight = 1.0_px;
        borderRadius.radiusBottomRight = 1.0_px;
    }
    renderContext->UpdateBorderRadius(borderRadius);
    // innerBorder need to adapt
}

void SheetSideObject::InitAnimationForOverlay(bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateRenderGroup(true, false, true);
    TAG_LOGD(AceLogTag::ACE_SHEET, "UpdateRenderGroup start");
    auto sheetParent = AceType::DynamicCast<FrameNode>(sheetNode->GetParent());
    CHECK_NULL_VOID(sheetParent);
    if (isTransitionIn) {
        if (isFirstTransition) {
            sheetNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_OPEN,
                WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
            TransformTranslateExit();
        }
        sheetPattern->FireOnTypeDidChange();
        sheetPattern->FireOnWidthDidChange();
        ACE_SCOPED_TRACE("Side Sheet starts the entrance animation");
    } else {
        sheetNode->OnAccessibilityEvent(AccessibilityEventType::PAGE_CLOSE,
            WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_SUBTREE);
        sheetParent->GetEventHub<EventHub>()->GetOrCreateGestureEventHub()->SetHitTestMode(HitTestMode::HTMTRANSPARENT);
    }
}

void SheetSideObject::SetFinishEventForAnimationOption(
    AnimationOption& option, bool isTransitionIn, bool isFirstTransition)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    if (isTransitionIn) {
        option.SetOnFinishEvent(
            [sheetWK = WeakClaim(RawPtr(sheetNode)), isFirst = isFirstTransition] {
                auto sheetNode = sheetWK.Upgrade();
                CHECK_NULL_VOID(sheetNode);
                auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
                CHECK_NULL_VOID(pattern);
                pattern->OnAppear();
                pattern->SendMessagesBeforeFirstTransitionIn(true);
                pattern->AvoidAiBar();
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

AnimationOption SheetSideObject::GetAnimationOptionForOverlay(bool isTransitionIn, bool isFirstTransition)
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

void SheetSideObject::TransformTranslateEnter()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRTL) {
        context->UpdateTransformTranslate({ 0.0f, 0.0f, 0.0f });
    } else {
        context->UpdateTransformTranslate({ sheetMaxWidth_ - sheetWidth_, 0.0f, 0.0f });
    }
}

void SheetSideObject::TransformTranslateExit()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_VOID(sheetNode);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    bool isRTL = AceApplicationInfo::GetInstance().IsRightToLeft();
    if (isRTL) {
        context->UpdateTransformTranslate({ -sheetWidth_, 0.0f, 0.0f });
    } else {
        context->UpdateTransformTranslate({ sheetMaxWidth_, 0.0f, 0.0f });
    }
}

std::function<void()> SheetSideObject::GetAnimationPropertyCallForOverlay(bool isTransitionIn)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_RETURN(sheetPattern, nullptr);
    auto sheetNode = sheetPattern->GetHost();
    CHECK_NULL_RETURN(sheetNode, nullptr);
    auto context = sheetNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);

    std::function<void()> event;
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
    return event;
}

void SheetSideObject::OnLanguageConfigurationUpdate()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->CheckLocalized();
    CHECK_NULL_VOID(sheetPattern->GetShowState());
    CHECK_NULL_VOID(!sheetPattern->GetIsPlayTransition());
    TransformTranslateEnter();
}

PaddingPropertyF SheetSideObject::GetSheetSafeAreaPadding() const
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, PaddingPropertyF());
    auto safeArea = pipeline->GetSafeArea();
    PaddingPropertyF padding;
    padding.left = 0.0f;
    padding.right = 0.0f;
    padding.top = CalcLength(safeArea.top_.Length()).GetDimension().ConvertToPx();
    padding.bottom = CalcLength(safeArea.bottom_.Length()).GetDimension().ConvertToPx();
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        padding.left = CalcLength(safeArea.left_.Length()).GetDimension().ConvertToPx();
    } else {
        padding.right = CalcLength(safeArea.right_.Length()).GetDimension().ConvertToPx();
    }
    return padding;
}

void SheetSideObject::HandleDragStart()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    sheetPattern->InitScrollProps();
    sheetPattern->SetIsDragging(true);
    if (sheetPattern->GetAnimation() && sheetPattern->GetAnimationProcess()) {
        AnimationUtils::StopAnimation(sheetPattern->GetAnimation());
        sheetPattern->SetAnimationBreak(true);
    }
    currentOffset_ = 0.0f;
}

void SheetSideObject::HandleDragUpdate(const GestureEvent& info)
{
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        HandleDragUpdateForRTL(info);
    } else {
        HandleDragUpdateForLTR(info);
    }
}

void SheetSideObject::HandleDragUpdateForLTR(const GestureEvent& info)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto lastOffset = currentOffset_;
    if (currentOffset_ + mainDelta < 0) {
        return; // can't drag left
    }
    currentOffset_ = currentOffset_ + mainDelta;
    if (NearEqual(currentOffset_, lastOffset)) {
        return;
    }
    auto offsetX = sheetMaxWidth_ - sheetWidth_ + currentOffset_;
    renderContext->UpdateTransformTranslate({ offsetX, 0.0f, 0.0f });
    sheetPattern->onWidthDidChange(sheetWidth_ - currentOffset_);
}

void SheetSideObject::HandleDragUpdateForRTL(const GestureEvent& info)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto mainDelta = static_cast<float>(info.GetMainDelta());
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto lastOffset = currentOffset_;
    if (currentOffset_ + mainDelta > 0) {
        return; // can't drag right
    }
    currentOffset_ = currentOffset_ + mainDelta;
    if (NearEqual(currentOffset_, lastOffset)) {
        return;
    }
    auto offsetX = currentOffset_ < 0 ? currentOffset_ : 0.0f;
    renderContext->UpdateTransformTranslate({ offsetX, 0.0f, 0.0f });
    sheetPattern->onWidthDidChange(sheetWidth_ + currentOffset_);
}

void SheetSideObject::HandleDragEnd(float dragVelocity)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto host = sheetPattern->GetHost();
    CHECK_NULL_VOID(host);
    sheetPattern->SetIsNeedProcessHeight(true);
    sheetPattern->SetIsDragging(false);

    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        HandleDragEndForRTL(dragVelocity);
    } else {
        HandleDragEndForLTR(dragVelocity);
    }
}

void SheetSideObject::HandleDragEndForLTR(float dragVelocity)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto currentOffset = currentOffset_;

    if (LessNotEqual(std::abs(dragVelocity), SHEET_VELOCITY_THRESHOLD)) {
        if (GreatNotEqual(std::abs(currentOffset), sheetWidth_ - std::abs(currentOffset))) {
            sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE, std::abs(dragVelocity));
        } else {
            ModifyFireSheetTransition(std::abs(dragVelocity));
        }
    } else {
        if (LessNotEqual(dragVelocity, 0.0f)) {
            // return to the original state in the opposite direction.
            ModifyFireSheetTransition(std::abs(dragVelocity));
        } else {
            // when drag velocity is over the threshold.
            sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE, std::abs(dragVelocity));
        }
    }
}

void SheetSideObject::HandleDragEndForRTL(float dragVelocity)
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    auto currentOffset = currentOffset_;

    if (LessNotEqual(std::abs(dragVelocity), SHEET_VELOCITY_THRESHOLD)) {
        if (GreatNotEqual(std::abs(currentOffset), sheetWidth_ - std::abs(currentOffset))) {
            sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE, std::abs(dragVelocity));
        } else {
            ModifyFireSheetTransition(std::abs(dragVelocity));
        }
    } else {
        if (LessNotEqual(dragVelocity, 0.0f)) {
            // when drag velocity is over the threshold.
            sheetPattern->SheetInteractiveDismiss(BindSheetDismissReason::SLIDE, std::abs(dragVelocity));
        } else {
            // return to the original state in the opposite direction.
            ModifyFireSheetTransition(std::abs(dragVelocity));
        }
    }
}

void SheetSideObject::ModifyFireSheetTransition(float dragVelocity)
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
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        offsetX = 0;
    } else {
        offsetX = sheetMaxWidth_ - width;
    }

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
            ref->GetSheetObject()->SetCurrentOffset(0.0f);
        } else {
            ref->SetAnimationBreak(false);
        }

        ref->AvoidAiBar();
        ref->SetSpringBack(false);
    };

    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    auto interactive = sheetStyle.interactive.value_or(false);
    sheetPattern->SetAnimationProcess(true);
    property->Set(width - std::abs(currentOffset_));
    std::shared_ptr<AnimationUtils::Animation> animation = AnimationUtils::StartAnimation(option,
        [weak = AceType::WeakClaim(RawPtr(sheetPattern)),
            renderContext, offsetX, width, interactive]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            if (interactive) {
                ref->GetProperty()->Set(width);
            }
            if (renderContext) {
                renderContext->UpdateTransformTranslate({ offsetX, 0.0, 0.0f });
            }
        }, finishCallback);
    sheetPattern->SetAnimation(animation);
}

void SheetSideObject::CreatePropertyCallback()
{
    auto sheetPattern = GetPattern();
    CHECK_NULL_VOID(sheetPattern);
    if (sheetPattern->GetProperty()) {
        return;
    }
    auto propertyCallback = [weak = AceType::WeakClaim(RawPtr(sheetPattern))](float position) {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->onWidthDidChange(static_cast<int>(position));
    };
    auto property = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    sheetPattern->SetProperty(property);
}
} // namespace OHOS::Ace::NG
