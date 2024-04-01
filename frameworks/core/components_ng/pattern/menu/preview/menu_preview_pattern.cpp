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

#include "core/components_ng/pattern/menu/preview/menu_preview_pattern.h"

#include "core/animation/animation_pub.h"
#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PAN_MAX_VELOCITY = 2000.0f;

// custom preview animation params when hover image
const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 280.0f, 30.0f);

RefPtr<MenuPattern> GetMenuPattern(const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_RETURN(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menuNode, nullptr);
    return menuNode->GetPattern<MenuPattern>();
}

bool ShowPreviewAnimationAfterHoverImage(const RefPtr<RenderContext>& context, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern, float scaleFrom, float scaleTo)
{
    CHECK_NULL_RETURN(menuPattern, false);
    if (!menuPattern->GetIsShowHoverImage()) {
        return false;
    }
    CHECK_NULL_RETURN(context, false);
    CHECK_NULL_RETURN(menuTheme, false);
    context->UpdateOpacity(0.0);
    // custom preview update opacity
    AnimationOption option;
    option.SetDuration(menuTheme->GetHoverImageSwitchToPreviewOpacityDuration());
    option.SetDelay(menuTheme->GetHoverImageDelayDuration());
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option, [context]() {
            CHECK_NULL_VOID(context);
            context->UpdateOpacity(1.0);
        },
        option.GetOnFinishEvent());

    // custom preview update scale from hover image size to final scale
    auto scaleBefore = LessNotEqual(scaleFrom, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleFrom;
    auto scaleAfter = LessNotEqual(scaleTo, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleTo;
    context->UpdateTransformScale(VectorF(scaleBefore, scaleBefore));

    AnimationOption scaleOption = AnimationOption();
    scaleOption.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    scaleOption.SetDelay(menuTheme->GetHoverImageDelayDuration());
    AnimationUtils::Animate(
        scaleOption,
        [context, scaleAfter]() {
            CHECK_NULL_VOID(context);
            context->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));
        },
        scaleOption.GetOnFinishEvent());
    return true;
}

void ShowScaleAnimation(const RefPtr<RenderContext>& context, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern, float scaleFrom, float scaleTo)
{
    if (ShowPreviewAnimationAfterHoverImage(context, menuTheme, menuPattern, scaleFrom, scaleTo)) {
        return;
    }
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(menuTheme);
    auto scaleBefore { -1.0f };
    auto scaleAfter { -1.0f };
    if (menuPattern != nullptr) {
        scaleBefore = menuPattern->GetPreviewBeforeAnimationScale();
        scaleAfter = menuPattern->GetPreviewAfterAnimationScale();
    }
    auto previewBeforeAnimationScale =
        LessOrEqual(scaleBefore, 0.0) ? menuTheme->GetPreviewBeforeAnimationScale() : scaleBefore;
    auto previewAfterAnimationScale =
        LessOrEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;

    auto springMotionResponse = menuTheme->GetSpringMotionResponse();
    auto springMotionDampingFraction = menuTheme->GetSpringMotionDampingFraction();
    AnimationOption scaleOption;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(springMotionResponse, springMotionDampingFraction);
    scaleOption.SetCurve(motion);
    DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_STARTED);
    scaleOption.SetOnFinishEvent(
        []() { DragEventActuator::ExecutePreDragAction(PreDragStatus::PREVIEW_LIFT_FINISHED); });
    context->UpdateTransformScale(VectorF(previewBeforeAnimationScale, previewBeforeAnimationScale));
    AnimationUtils::Animate(
        scaleOption,
        [context, previewAfterAnimationScale]() {
            CHECK_NULL_VOID(context);
            context->UpdateTransformScale(VectorF(previewAfterAnimationScale, previewAfterAnimationScale));
        },
        scaleOption.GetOnFinishEvent());
}

void ShowGatherAnimation(const RefPtr<FrameNode>& imageNode, const RefPtr<FrameNode>& menuNode)
{
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto manager = mainPipeline->GetOverlayManager();
    CHECK_NULL_VOID(manager);
    manager->UpdateGatherNodeToTop();
    auto gatherNode = manager->GetGatherNode();
    CHECK_NULL_VOID(gatherNode);
    auto menuWrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(menuWrapperPattern);
    auto textNode = menuWrapperPattern->GetBadgeNode();
    CHECK_NULL_VOID(textNode);
    auto menuPattern = GetMenuPattern(menuNode);
    CHECK_NULL_VOID(menuPattern);
    mainPipeline->AddAfterRenderTask([weakImageNode = AceType::WeakClaim(AceType::RawPtr(imageNode)),
        weakManager = AceType::WeakClaim(AceType::RawPtr(manager)),
        weakTextNode = AceType::WeakClaim(AceType::RawPtr(textNode)),
        weakMenuPattern = AceType::WeakClaim(AceType::RawPtr(menuPattern))]() {
        auto imageNode = weakImageNode.Upgrade();
        auto manager = weakManager.Upgrade();
        auto textNode = weakTextNode.Upgrade();
        auto menuPattern = weakMenuPattern.Upgrade();
        DragAnimationHelper::PlayGatherAnimation(imageNode, manager);
        DragAnimationHelper::CalcBadgeTextPosition(menuPattern, manager, imageNode, textNode);
        DragAnimationHelper::ShowBadgeAnimation(textNode);
    });
}

} // namespace
void MenuPreviewPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitPanEvent(gestureHub);
}

bool MenuPreviewPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN(isFirstShow_, false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto context = host->GetRenderContext();
    CHECK_NULL_RETURN(context, false);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto menuTheme = pipeline->GetTheme<NG::MenuTheme>();
    CHECK_NULL_RETURN(menuTheme, false);
    context->UpdateBackgroundColor(Color::TRANSPARENT);
    context->SetClipToBounds(true);
    auto shadow = context->GetBackShadow();
    if (!shadow.has_value()) {
        shadow = Shadow::CreateShadow(ShadowStyle::None);
    }

    auto previewAnimationDuration = menuTheme->GetPreviewAnimationDuration();
    auto previewBorderRadius = menuTheme->GetPreviewBorderRadius();
    auto delay = isShowHoverImage_ ? menuTheme->GetHoverImageDelayDuration() : 0;
    AnimationOption option;
    option.SetDuration(previewAnimationDuration);
    if (isShowHoverImage_) {
        option.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    } else {
        option.SetCurve(Curves::SHARP);
    }
    option.SetDelay(delay);
    AnimationUtils::Animate(
        option,
        [context, previewBorderRadius, shadow]() mutable {
            CHECK_NULL_VOID(context);
            auto color = shadow->GetColor();
            auto newColor = Color::FromARGB(100, color.GetRed(), color.GetGreen(), color.GetBlue());
            shadow->SetColor(newColor);
            context->UpdateBackShadow(shadow.value());
            BorderRadiusProperty borderRadius;
            borderRadius.SetRadius(previewBorderRadius);
            context->UpdateBorderRadius(borderRadius);
        },
        option.GetOnFinishEvent());
    if (!hasPreviewTransitionEffect_) {
        auto menuWrapper = GetMenuWrapper();
        auto menuPattern = GetMenuPattern(menuWrapper);
        ShowGatherAnimation(host, menuWrapper);
        ShowScaleAnimation(context, menuTheme, menuPattern, customPreviewScaleFrom_, customPreviewScaleTo_);
    }
    isFirstShow_ = false;
    return false;
}

RefPtr<FrameNode> MenuPreviewPattern::GetMenuWrapper() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto parent = host->GetParent();
    while (parent) {
        if (parent->GetTag() == V2::MENU_WRAPPER_ETS_TAG) {
            return AceType::DynamicCast<FrameNode>(parent);
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

void MenuPreviewPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(gestureHub);
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto offsetX = static_cast<float>(info.GetOffsetX());
        auto offsetY = static_cast<float>(info.GetOffsetY());
        auto offsetPerSecondX = info.GetVelocity().GetOffsetPerSecond().GetX();
        auto offsetPerSecondY = info.GetVelocity().GetOffsetPerSecond().GetY();
        auto velocity =
            static_cast<float>(std::sqrt(offsetPerSecondX * offsetPerSecondX + offsetPerSecondY * offsetPerSecondY));
        pattern->HandleDragEnd(offsetX, offsetY, velocity);
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    auto panEvent = MakeRefPtr<PanEvent>(nullptr, nullptr, std::move(actionEndTask), nullptr);
    gestureHub->AddPanEvent(panEvent, panDirection, 1, DEFAULT_PAN_DISTANCE);
}

void MenuPreviewPattern::HandleDragEnd(float offsetX, float offsetY, float velocity)
{
    if ((LessOrEqual(std::abs(offsetY), std::abs(offsetX)) || LessOrEqual(offsetY, 0.0f)) &&
        LessOrEqual(velocity, PAN_MAX_VELOCITY)) {
        return;
    }
    auto menuWrapper = GetMenuWrapper();
    CHECK_NULL_VOID(menuWrapper);
    auto wrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_VOID(wrapperPattern);
    wrapperPattern->HideMenu();
}

void MenuPreviewPattern::ShowHoverImagePreviewDisAppearAnimation(const RefPtr<RenderContext>& context,
    float scaleFrom, float scaleTo, int32_t duration)
{
    CHECK_NULL_VOID(isShowHoverImage_);
    CHECK_NULL_VOID(context);

    // custom preview update disappear opacity
    context->UpdateOpacity(1.0);
    AnimationOption option;
    option.SetDuration(duration);
    option.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        option, [context]() {
            CHECK_NULL_VOID(context);
            context->UpdateOpacity(0.0);
        },
        option.GetOnFinishEvent());

    // custom preview update scale from final scale to hover image size
    auto scaleBefore = LessNotEqual(scaleFrom, 0.0) ? 1.0f : scaleFrom;
    auto scaleAfter = LessNotEqual(scaleTo, 0.0) ? 1.0f : scaleTo;
    context->UpdateTransformScale(VectorF(scaleBefore, scaleBefore));

    AnimationOption scaleOption = AnimationOption();
    scaleOption.SetCurve(CUSTOM_PREVIEW_ANIMATION_CURVE);
    AnimationUtils::Animate(
        scaleOption,
        [context, scaleAfter]() {
            CHECK_NULL_VOID(context);
            context->UpdateTransformScale(VectorF(scaleAfter, scaleAfter));
        },
        scaleOption.GetOnFinishEvent());
}
} // namespace OHOS::Ace::NG
