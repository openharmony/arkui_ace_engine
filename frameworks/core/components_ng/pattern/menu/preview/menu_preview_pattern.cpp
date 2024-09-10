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

#include "core/components_ng/manager/drag_drop/utils/drag_animation_helper.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float PAN_MAX_VELOCITY = 2000.0f;

// custom preview animation params when hover image
const RefPtr<Curve> CUSTOM_PREVIEW_ANIMATION_CURVE =
    AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 328.0f, 34.0f);

RefPtr<MenuPattern> GetMenuPattern(const RefPtr<FrameNode>& menuWrapper)
{
    CHECK_NULL_RETURN(menuWrapper, nullptr);
    auto menuWrapperPattern = menuWrapper->GetPattern<MenuWrapperPattern>();
    CHECK_NULL_RETURN(menuWrapperPattern, nullptr);
    auto menuNode = menuWrapperPattern->GetMenu();
    CHECK_NULL_RETURN(menuNode, nullptr);
    return menuNode->GetPattern<MenuPattern>();
}

void ShowScaleAnimation(const RefPtr<RenderContext>& context, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern)
{
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(menuTheme);
    auto scaleBefore { -1.0f };
    auto scaleAfter { -1.0f };
    if (menuPattern != nullptr) {
        CHECK_NULL_VOID(!menuPattern->GetIsShowHoverImage());
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
    auto menuWrapper = GetMenuWrapper();
    auto menuPattern = GetMenuPattern(menuWrapper);
    DragAnimationHelper::UpdateGatherNodeToTop();
    UpdateShowScale(context, menuTheme, menuPattern);

    isFirstShow_ = false;
    return false;
}

void MenuPreviewPattern::UpdateShowScale(const RefPtr<RenderContext>& context, const RefPtr<MenuTheme>& menuTheme,
    const RefPtr<MenuPattern>& menuPattern)
{
    if (hasPreviewTransitionEffect_) {
        CHECK_NULL_VOID(context);
        CHECK_NULL_VOID(menuTheme);
        auto scaleAfter { -1.0f };
        if (menuPattern != nullptr) {
            scaleAfter = menuPattern->GetPreviewAfterAnimationScale();
        }
        auto previewAfterAnimationScale =
            LessOrEqual(scaleAfter, 0.0) ? menuTheme->GetPreviewAfterAnimationScale() : scaleAfter;

        context->UpdateTransformScale(VectorF(previewAfterAnimationScale, previewAfterAnimationScale));
    } else {
        ShowScaleAnimation(context, menuTheme, menuPattern);
    }
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
    auto mainPipeline = PipelineContext::GetMainPipelineContext();
    CHECK_NULL_VOID(mainPipeline);
    auto dragDropManager = mainPipeline->GetDragDropManager();
    CHECK_NULL_VOID(dragDropManager);
    auto menuWrapper = GetMenuWrapper();
    auto menuPattern = GetMenuPattern(menuWrapper);
    CHECK_NULL_VOID(menuPattern);
    auto dragTargetNode = FrameNode::GetFrameNode(menuPattern->GetTargetTag(), menuPattern->GetTargetId());
    CHECK_NULL_VOID(dragTargetNode);
    auto eventHub = dragTargetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto targetGestureHub = eventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(targetGestureHub);
    auto dragEventActuator = targetGestureHub->GetDragEventActuator();
    auto actionStartTask = [actuator = AceType::WeakClaim(AceType::RawPtr(dragEventActuator))](
                               const GestureEvent& info) {
        auto dragEventActuator = actuator.Upgrade();
        CHECK_NULL_VOID(dragEventActuator);
        dragEventActuator->RestartDragTask(info);
    };
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
    auto panEvent = MakeRefPtr<PanEvent>(std::move(actionStartTask), nullptr, std::move(actionEndTask), nullptr);
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
    TAG_LOGI(AceLogTag::ACE_MENU, "will hide menu");
    wrapperPattern->HideMenu();
}
} // namespace OHOS::Ace::NG
