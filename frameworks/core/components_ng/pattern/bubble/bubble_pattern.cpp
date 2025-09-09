/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/bubble/bubble_pattern.h"

#include "base/subwindow/subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "base/log/dump_log.h"
#include "core/common/container_scope.h"
#include "core/common/window_animation_config.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float VISIABLE_ALPHA = 1.0f;
constexpr float INVISIABLE_ALPHA = 0.0f;
constexpr int32_t ENTRY_ANIMATION_DURATION = 250;
constexpr int32_t EXIT_ANIMATION_DURATION = 100;
const Dimension INVISIABLE_OFFSET = 8.0_px;
} // namespace

bool BubblePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto bubbleLayoutAlgorithm = DynamicCast<BubbleLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(bubbleLayoutAlgorithm, false);

    showArrow_ = bubbleLayoutAlgorithm->ShowArrow();
    arrowPosition_ = bubbleLayoutAlgorithm->GetArrowPosition();
    childOffset_ = bubbleLayoutAlgorithm->GetChildOffset();
    childSize_ = bubbleLayoutAlgorithm->GetChildSize();
    touchRegion_ = bubbleLayoutAlgorithm->GetTouchRegion();
    hostWindowRect_ = bubbleLayoutAlgorithm->GetHostWindowRect();
    targetOffset_ = bubbleLayoutAlgorithm->GetTargetOffset();
    targetSize_ = bubbleLayoutAlgorithm->GetTargetSize();
    arrowPlacement_ = bubbleLayoutAlgorithm->GetArrowPlacement();
    clipPath_ = bubbleLayoutAlgorithm->GetClipPath();
    clipFrameNode_ = bubbleLayoutAlgorithm->GetClipFrameNode();
    arrowOffsetsFromClip_ = bubbleLayoutAlgorithm->GetArrowOffsetsFromClip();
    arrowWidth_ = bubbleLayoutAlgorithm->GetArrowWidth();
    arrowHeight_ = bubbleLayoutAlgorithm->GetArrowHeight();
    border_ = bubbleLayoutAlgorithm->GetBorder();
    dumpInfo_ = bubbleLayoutAlgorithm->GetDumpInfo();
    arrowBuildPlacement_ = bubbleLayoutAlgorithm->GetArrowBuildPlacement();
    paintProperty->UpdatePlacement(bubbleLayoutAlgorithm->GetArrowPlacement());
    if (delayShow_) {
        delayShow_ = false;
        if (transitionStatus_ == TransitionStatus::INVISIABLE) {
            StartEnteringAnimation(nullptr);
        }
    }
    return true;
}

void BubblePattern::OnModifyDone()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (context->GetColorMode() != colorMode_ && !isCustomPopup_) {
        colorMode_ = context->GetColorMode();
        UpdateBubbleText();
    }
    UpdateAgingTextSize();
    Pattern::OnModifyDone();
    InitTouchEvent();
}

void BubblePattern::AddPipelineCallBack()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->AddWindowSizeChangeCallback(host->GetId());
    pipelineContext->AddWindowStateChangedCallback(host->GetId());
}

void BubblePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    auto pipelineContext = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineContext);
    hasOnAreaChange_ = pipelineContext->HasOnAreaChangeNode(targetNode->GetId());
    auto eventHub = targetNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    OnAreaChangedFunc onAreaChangedFunc = [popupNodeWk = WeakPtr<FrameNode>(host), weak = WeakClaim(this)](
                                              const RectF& /* oldRect */, const OffsetF& /* oldOrigin */,
                                              const RectF& /* rect */, const OffsetF& /* origin */) {
        auto popupNode = popupNodeWk.Upgrade();
        CHECK_NULL_VOID(popupNode);
        popupNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->PopBubble(true);
        }
    };
    eventHub->AddInnerOnAreaChangedCallback(host->GetId(), std::move(onAreaChangedFunc));

    halfFoldHoverCallbackId_ =
        pipelineContext->RegisterHalfFoldHoverChangedCallback([weak = WeakClaim(this)](bool isHalfFoldHover) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            AnimationOption option;
            auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.35f, 1.0f, 0.0f);
            option.SetCurve(curve);
            auto context = host->GetContext();
            CHECK_NULL_VOID(context);
            AnimationUtils::Animate(option, [host, context]() {
                host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
                context->FlushUITasks();
            }, nullptr, nullptr, host->GetContextRefPtr());
        });
}

void BubblePattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
    auto targetNode = FrameNode::GetFrameNode(targetTag_, targetNodeId_);
    CHECK_NULL_VOID(targetNode);
    if (!hasOnAreaChange_) {
        pipeline->RemoveOnAreaChangeNode(targetNode->GetId());
    }
    pipeline->UnRegisterHalfFoldHoverChangedCallback(halfFoldHoverCallbackId_);
}

void BubblePattern::InitTouchEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (touchEvent_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleTouchEvent(info);
        }
    };
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

void BubblePattern::HandleTouchEvent(const TouchEventInfo& info)
{
    if (info.GetTouches().empty()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(clickPos);
    }
}

void BubblePattern::HandleTouchDown(const Offset& clickPosition)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto bubbleRenderProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(bubbleRenderProp);
    if (touchRegion_.IsInRegion(PointF(clickPosition.GetX(), clickPosition.GetY()))) {
        return;
    }
    auto autoCancel = bubbleRenderProp->GetAutoCancel().value_or(true);
    if (autoCancel) {
        TAG_LOGD(AceLogTag::ACE_DIALOG, "handle popup touch down event");
        if (!GetInteractiveDismiss()) {
            return;
        }
        if (HasOnWillDismiss()) {
            auto pipelineNg = host->GetContextRefPtr();
            CHECK_NULL_VOID(pipelineNg);
            auto overlayManager = pipelineNg->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->SetDismissPopupId(targetNodeId_);
            CallOnWillDismiss(static_cast<int32_t>(DismissReason::TOUCH_OUTSIDE));
            return;
        }
        PopBubble();
    }
}

void BubblePattern::RegisterButtonOnHover()
{
    if (mouseEventInitFlag_) {
        return;
    }
    auto paintProps = GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(paintProps);
    auto primaryButtonShow = paintProps->GetPrimaryButtonShow().value_or(false);
    auto secondaryButtonShow = paintProps->GetSecondaryButtonShow().value_or(false);
    auto custom = paintProps->GetUseCustom().value_or(false);
    if (custom) {
        return;
    }
    if (!primaryButtonShow && !secondaryButtonShow) {
        return;
    }
    auto buttonRowNode = GetButtonRowNode();
    for (const auto& child : buttonRowNode->GetChildren()) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(buttonNode);
        if (buttonNode->GetTag() != V2::BUTTON_ETS_TAG) {
            return;
        }
        auto inputHub = buttonNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto mouseTask = [weak = WeakClaim(this), buttonNodeWK = WeakPtr<FrameNode>(buttonNode)](bool isHover) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto buttonNode = buttonNodeWK.Upgrade();
            CHECK_NULL_VOID(buttonNode);
            pattern->ButtonOnHover(isHover, buttonNode);
        };
        auto mouseEvent = MakeRefPtr<InputEvent>(std::move(mouseTask));
        inputHub->AddOnHoverEvent(mouseEvent);
    }
    mouseEventInitFlag_ = true;
}

void BubblePattern::ButtonOnHover(bool isHover, const RefPtr<NG::FrameNode>& buttonNode)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = GetPopupTheme();
    CHECK_NULL_VOID(theme);
    isHover_ = isHover;
    auto hoverColor = theme->GetButtonHoverColor();
    auto backgroundColor = theme->GetButtonBackgroundColor();
    if (isHover) {
        // normal to hover
        Animation(renderContext, hoverColor, theme->GetHoverAnimationDuration(), Curves::FRICTION);
    } else {
        // hover to normal
        Animation(renderContext, backgroundColor, theme->GetHoverAnimationDuration(), Curves::FRICTION);
    }
}

void BubblePattern::RegisterButtonOnTouch()
{
    if (touchEventInitFlag_) {
        return;
    }
    auto paintProps = GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(paintProps);
    auto primaryButtonShow = paintProps->GetPrimaryButtonShow().value_or(false);
    auto secondaryButtonShow = paintProps->GetSecondaryButtonShow().value_or(false);
    auto custom = paintProps->GetUseCustom().value_or(false);
    if (custom) {
        return;
    }
    if (!primaryButtonShow && !secondaryButtonShow) {
        return;
    }

    auto buttonRowNode = GetButtonRowNode();
    for (const auto& child : buttonRowNode->GetChildren()) {
        auto buttonNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(buttonNode);
        if (buttonNode->GetTag() != V2::BUTTON_ETS_TAG) {
            return;
        }
        auto gestureHub = buttonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        auto touchCallback = [weak = WeakClaim(this), buttonNodeWK = WeakPtr<FrameNode>(buttonNode)]
            (const TouchEventInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto buttonNode = buttonNodeWK.Upgrade();
            CHECK_NULL_VOID(buttonNode);
            pattern->ButtonOnPress(info, buttonNode);
        };
        auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gestureHub->AddTouchEvent(touchEvent);
    }
    touchEventInitFlag_ = true;
}

void BubblePattern::ButtonOnPress(const TouchEventInfo& info, const RefPtr<NG::FrameNode>& buttonNode)
{
    if (info.GetTouches().empty()) {
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    CHECK_NULL_VOID(buttonNode);
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto theme = GetPopupTheme();
    CHECK_NULL_VOID(theme);
    auto pressColor = theme->GetButtonPressColor();
    auto hoverColor = theme->GetButtonHoverColor();
    auto backgroundColor = theme->GetButtonBackgroundColor();
    if (touchType == TouchType::DOWN) {
        if (isHover_) {
            // hover to press
            Animation(renderContext, pressColor, theme->GetHoverToPressAnimationDuration(), Curves::SHARP);
        } else {
            // normal to press
            Animation(renderContext, pressColor, theme->GetHoverAnimationDuration(), Curves::SHARP);
        }
    } else if (touchType == TouchType::UP) {
        if (isHover_) {
            // press to hover
            Animation(renderContext, hoverColor, theme->GetHoverToPressAnimationDuration(), Curves::SHARP);
        } else {
            // press to normal
            Animation(renderContext, backgroundColor, theme->GetHoverAnimationDuration(), Curves::SHARP);
        }
    }
}

RefPtr<FrameNode> BubblePattern::GetButtonRowNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_RETURN(columnNode, nullptr);
    auto lastColumnNode = AceType::DynamicCast<FrameNode>(columnNode->GetLastChild());
    CHECK_NULL_RETURN(lastColumnNode, nullptr);
    auto buttonRowNode = AceType::DynamicCast<FrameNode>(lastColumnNode->GetLastChild());
    CHECK_NULL_RETURN(buttonRowNode, nullptr);
    if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        if (buttonRowNode->GetTag() != V2::ROW_ETS_TAG) {
            return nullptr;
        }
    } else {
        if (buttonRowNode->GetTag() != V2::FLEX_ETS_TAG) {
            return nullptr;
        }
    }
    if (buttonRowNode->GetChildren().empty()) {
        return nullptr;
    }
    return buttonRowNode;
}

void BubblePattern::PopBubble(bool tips)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineNg = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineNg);
    auto overlayManager = pipelineNg->GetOverlayManager();
    auto instanceId = pipelineNg->GetInstanceId();
    CHECK_NULL_VOID(overlayManager);
    auto popupInfo = overlayManager->GetPopupInfo(targetNodeId_);
    if (!popupInfo.isCurrentOnShow || (tips && !popupInfo.isTips)) {
        return;
    }
    popupInfo.markNeedUpdate = true;
    CHECK_NULL_VOID(host);
    auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    auto isTips = layoutProp->GetIsTips().value_or(false);
    if (showInSubWindow) {
        if (isTips) {
            SubwindowManager::GetInstance()->HideTipsNG(targetNodeId_, 0, instanceId);
        } else {
            SubwindowManager::GetInstance()->HidePopupNG(targetNodeId_, instanceId);
        }
    } else {
        if (isTips) {
            overlayManager->HideTips(targetNodeId_, popupInfo, 0);
        } else {
            overlayManager->HidePopup(targetNodeId_, popupInfo);
        }
    }
}

RefPtr<PopupTheme> BubblePattern::GetPopupTheme()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto popupTheme = pipelineContext->GetTheme<PopupTheme>();
    CHECK_NULL_RETURN(popupTheme, nullptr);
    return popupTheme;
}

void BubblePattern::Animation(
    RefPtr<RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption option = AnimationOption();
    option.SetCurve(curve);
    option.SetDuration(duration);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(
        option, [buttonContext = renderContext, color = endColor]() { buttonContext->UpdateBackgroundColor(color); },
        nullptr, nullptr, host->GetContextRefPtr());
}

bool BubblePattern::PostTask(const TaskExecutor::Task& task, const std::string& name)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    return taskExecutor->PostTask(task, TaskExecutor::TaskType::UI, name);
}

void BubblePattern::StartEnteringTransitionEffects(
    const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish)
{
    auto popupId = popupNode->GetId();
    auto pattern = popupNode->GetPattern<BubblePattern>();
    pattern->transitionStatus_ = TransitionStatus::ENTERING;
    auto layoutProp = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    layoutProp->UpdateVisibility(VisibleType::VISIBLE, false);
    auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    auto isBlock = layoutProp->GetBlockEventValue(true);
    auto& renderContext = popupNode->GetRenderContext();
    auto isTips = layoutProp->GetIsTips().value_or(false);
    renderContext->SetTransitionInCallback(
        [weak = WeakClaim(this), finish, showInSubWindow, popupId, isBlock, isTips]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->transitionStatus_ != TransitionStatus::ENTERING) {
                return;
            }
            pattern->transitionStatus_ = TransitionStatus::NORMAL;
            if (showInSubWindow && !isTips) {
                std::vector<Rect> rects;
                if (!isBlock) {
                    auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                        pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
                    rects.emplace_back(rect);
                } else {
                    auto parentWindowRect = pattern->GetHostWindowRect();
                    auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                        pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
                    rects.emplace_back(parentWindowRect);
                    rects.emplace_back(rect);
                }
                auto subWindowMgr = SubwindowManager::GetInstance();
                subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_POPUP, popupId, pattern->GetContainerId());
            }
            if (finish) {
                finish();
            }
        });
}

void BubblePattern::StartExitingTransitionEffects(
    const RefPtr<FrameNode>& popupNode, const std::function<void()>& finish)
{
    auto pattern = popupNode->GetPattern<BubblePattern>();
    pattern->transitionStatus_ = TransitionStatus::EXITING;
    auto layoutProperty = popupNode->GetLayoutProperty();
    layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    auto renderContext = popupNode->GetRenderContext();
    renderContext->SetTransitionOutCallback(
        [weak = WeakClaim(this), finish]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->transitionStatus_ != TransitionStatus::EXITING) {
                return;
            }
            pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
            if (finish) {
                finish();
            }
        });
}

void BubblePattern::StartEnteringAnimation(std::function<void()> finish)
{
    if (!arrowPlacement_.has_value()) {
        delayShow_ = true;
        finish_ = finish;
        return;
    }
    if (IsOnShow()) {
        return;
    }

    if (transitionStatus_ == TransitionStatus::INVISIABLE) {
        ResetToInvisible();
    }

    StartOffsetEnteringAnimation();
    if (finish) {
        StartAlphaEnteringAnimation(finish);
    } else {
        StartAlphaEnteringAnimation(finish_);
    }
}

void BubblePattern::StartOffsetEnteringAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption optionPosition;
    optionPosition.SetDuration(ENTRY_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOffset(OffsetT<Dimension>());
            renderContext->SyncGeometryProperties(nullptr);
        },
        nullptr, nullptr, host->GetContextRefPtr());
}

void BubblePattern::StartAlphaEnteringAnimation(std::function<void()> finish)
{
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(ENTRY_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupId = host->GetId();
    auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    auto isBlock = layoutProp->GetBlockEventValue(true);
    auto isTips = layoutProp->GetIsTips().value_or(false);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->transitionStatus_ = TransitionStatus::ENTERING;
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(VISIABLE_ALPHA);
        },
        [weak = WeakClaim(this), finish, showInSubWindow, popupId, isBlock, isTips]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->transitionStatus_ != TransitionStatus::ENTERING) {
                return;
            }
            pattern->transitionStatus_ = TransitionStatus::NORMAL;
            if (showInSubWindow && !isTips) {
                std::vector<Rect> rects;
                if (!isBlock) {
                    auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                        pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
                    rects.emplace_back(rect);
                } else {
                    auto parentWindowRect = pattern->GetHostWindowRect();
                    auto rect = Rect(pattern->GetChildOffset().GetX(), pattern->GetChildOffset().GetY(),
                        pattern->GetChildSize().Width(), pattern->GetChildSize().Height());
                    rects.emplace_back(parentWindowRect);
                    rects.emplace_back(rect);
                }
                auto subWindowMgr = SubwindowManager::GetInstance();
                subWindowMgr->SetHotAreas(rects, SubwindowType::TYPE_POPUP, popupId, pattern->GetContainerId());
            }
            if (finish) {
                finish();
            }
        }, nullptr, host->GetContextRefPtr());
}

void BubblePattern::StartExitingAnimation(std::function<void()> finish)
{
    StartOffsetExitingAnimation();
    StartAlphaExitingAnimation(finish);
}

void BubblePattern::StartOffsetExitingAnimation()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption optionPosition;
    optionPosition.SetDuration(EXIT_ANIMATION_DURATION);
    optionPosition.SetCurve(Curves::FRICTION);
    AnimationUtils::Animate(
        optionPosition,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOffset(pattern->GetInvisibleOffset());
            renderContext->SyncGeometryProperties(nullptr);
        },
        nullptr, nullptr, host->GetContextRefPtr());
}

void BubblePattern::StartAlphaExitingAnimation(std::function<void()> finish)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    AnimationOption optionAlpha;
    optionAlpha.SetDuration(EXIT_ANIMATION_DURATION);
    optionAlpha.SetCurve(Curves::SHARP);
    AnimationUtils::Animate(
        optionAlpha,
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->transitionStatus_ = TransitionStatus::EXITING;
            auto renderContext = pattern->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateOpacity(INVISIABLE_ALPHA);
        },
        [weak = WeakClaim(this), finish]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            if (pattern->transitionStatus_ != TransitionStatus::EXITING) {
                return;
            }
            pattern->transitionStatus_ = TransitionStatus::INVISIABLE;
            if (finish) {
                finish();
            }
        }, nullptr, host->GetContextRefPtr());
}

bool BubblePattern::IsOnShow()
{
    return (transitionStatus_ == TransitionStatus::ENTERING) || (transitionStatus_ == TransitionStatus::NORMAL);
}

bool BubblePattern::IsExiting()
{
    return transitionStatus_ == TransitionStatus::EXITING;
}

OffsetT<Dimension> BubblePattern::GetInvisibleOffset()
{
    if (!arrowPlacement_.has_value()) {
        return OffsetT<Dimension>();
    }

    OffsetT<Dimension> offset;
    switch (arrowPlacement_.value()) {
        case Placement::LEFT:
        case Placement::LEFT_TOP:
        case Placement::LEFT_BOTTOM:
            offset.AddX(INVISIABLE_OFFSET);
            break;
        case Placement::RIGHT:
        case Placement::RIGHT_TOP:
        case Placement::RIGHT_BOTTOM:
            offset.AddX(INVISIABLE_OFFSET * -1);
            break;
        case Placement::TOP:
        case Placement::TOP_LEFT:
        case Placement::TOP_RIGHT:
            offset.AddY(INVISIABLE_OFFSET);
            break;
        case Placement::BOTTOM:
        case Placement::BOTTOM_LEFT:
        case Placement::BOTTOM_RIGHT:
            offset.AddY(INVISIABLE_OFFSET * -1);
            break;
        default:
            break;
    }
    return offset;
}

RefPtr<RenderContext> BubblePattern::GetRenderContext()
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext();
}

void BubblePattern::ResetToInvisible()
{
    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    renderContext->UpdateOpacity(INVISIABLE_ALPHA);
    renderContext->UpdateOffset(GetInvisibleOffset());
    renderContext->SyncGeometryProperties(nullptr);
}

void BubblePattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "Popup OnWindowSizeChanged, reason: %{public}d", type);
    switch (type) {
        case WindowSizeChangeReason::MAXIMIZE:
        case WindowSizeChangeReason::RECOVER:
        case WindowSizeChangeReason::ROTATION:
        case WindowSizeChangeReason::HIDE:
        case WindowSizeChangeReason::TRANSFORM:
        case WindowSizeChangeReason::CUSTOM_ANIMATION:
        case WindowSizeChangeReason::FULL_TO_SPLIT:
        case WindowSizeChangeReason::SPLIT_TO_FULL:
        case WindowSizeChangeReason::FULL_TO_FLOATING:
        case WindowSizeChangeReason::FLOATING_TO_FULL:
        case WindowSizeChangeReason::PIP_START:
        case WindowSizeChangeReason::PIP_SHOW:
        case WindowSizeChangeReason::PIP_AUTO_START:
        case WindowSizeChangeReason::PIP_RATIO_CHANGE:
        case WindowSizeChangeReason::PIP_RESTORE:
        case WindowSizeChangeReason::UPDATE_DPI_SYNC:
        case WindowSizeChangeReason::DRAG_MOVE:
        case WindowSizeChangeReason::MAXIMIZE_TO_SPLIT:
        case WindowSizeChangeReason::SPLIT_TO_MAXIMIZE:
        case WindowSizeChangeReason::PAGE_ROTATION:
        case WindowSizeChangeReason::SPLIT_DRAG_START:
        case WindowSizeChangeReason::SPLIT_DRAG:
        case WindowSizeChangeReason::SPLIT_DRAG_END:
        case WindowSizeChangeReason::RESIZE_BY_LIMIT:
        case WindowSizeChangeReason::MAXIMIZE_IN_IMPLICT:
        case WindowSizeChangeReason::RECOVER_IN_IMPLICIT: {
            auto host = GetHost();
            CHECK_NULL_VOID(host);
            auto pipelineNg = host->GetContextRefPtr();
            CHECK_NULL_VOID(pipelineNg);
            auto overlayManager = pipelineNg->GetOverlayManager();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->HideAllPopups();
            auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
            CHECK_NULL_VOID(layoutProp);
            auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
            if (showInSubWindow) {
                auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
                    pipelineNg->GetInstanceId(), SubwindowType::TYPE_POPUP);
                CHECK_NULL_VOID(subwindow);
                subwindow->HidePopupNG(targetNodeId_);
            }
            break;
        }
        default: break;
    }
}

void BubblePattern::OnWindowHide()
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "Popup OnWindowHide start");
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineNg = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipelineNg);
    auto overlayManager = pipelineNg->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->HideAllPopups();
    CHECK_NULL_VOID(host);
    auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    if (showInSubWindow) {
        auto subwindow = SubwindowManager::GetInstance()->GetSubwindowByType(
            pipelineNg->GetInstanceId(), SubwindowType::TYPE_POPUP);
        CHECK_NULL_VOID(subwindow);
        subwindow->HidePopupNG(targetNodeId_);
    }
}


void BubblePattern::UpdateText(const RefPtr<UINode>& node, const RefPtr<PopupTheme>& popupTheme)
{
    if (node->GetTag() == V2::TEXT_ETS_TAG) {
        auto textNode = DynamicCast<FrameNode>(node);
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        auto parentNode = node->GetParent();
        if (parentNode && parentNode->GetTag() == V2::BUTTON_ETS_TAG &&
            !(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            if (popupTheme->GetPopupDoubleButtonIsSameStyle()) {
                textLayoutProperty->UpdateTextColor(popupTheme->GetButtonFontColor());
            }
        } else if (!isSetMessageColor_) {
            if ((Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
                textLayoutProperty->UpdateTextColor(popupTheme->GetFontColor());
            } else {
                textLayoutProperty->UpdateTextColor(popupTheme->GetFontPrimaryColor());
            }
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    } else {
        for (const auto& childNode : node->GetChildren()) {
            UpdateText(childNode, popupTheme);
        }
    }
}

void BubblePattern::DumpInfo()
{
    DumpLog::GetInstance().AddDesc("enableArrow: " + std::to_string(dumpInfo_.enableArrow));
    DumpLog::GetInstance().AddDesc("mask: " + std::to_string(dumpInfo_.mask));
    DumpLog::GetInstance().AddDesc("targetTag: " + dumpInfo_.targetNode + ", targetID: "
        + std::to_string(dumpInfo_.targetID));
    DumpLog::GetInstance().AddDesc("targetOffset: " + dumpInfo_.targetOffset.ToString());
    DumpLog::GetInstance().AddDesc("targetSize: " + dumpInfo_.targetSize.ToString());
    DumpLog::GetInstance().AddDesc("touchRegion: " + dumpInfo_.touchRegion.ToString());
    DumpLog::GetInstance().AddDesc("avoid top: " + std::to_string(dumpInfo_.top)
        + ", bottom: " + std::to_string(dumpInfo_.bottom));
    DumpLog::GetInstance().AddDesc("userOffset: " + dumpInfo_.userOffset.ToString());
    DumpLog::GetInstance().AddDesc("targetSpace: " + dumpInfo_.targetSpace.ToString());
    DumpLog::GetInstance().AddDesc("originPlacement: " + dumpInfo_.originPlacement);
    DumpLog::GetInstance().AddDesc("finalPlacement: " + dumpInfo_.finalPlacement);
    DumpLog::GetInstance().AddDesc("enableHoverMode: " + std::to_string(dumpInfo_.enableHoverMode));
    DumpLog::GetInstance().AddDesc("avoidKeyboard: " + std::to_string(dumpInfo_.avoidKeyboard));
}

void BubblePattern::UpdateBubbleText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->SetNeedCallChildrenUpdate(false);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto popupTheme = context->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(popupTheme);
    UpdateText(host, popupTheme);
    host->MarkDirtyNode();
}

void BubblePattern::UpdateStyleOption(BlurStyle blurStyle, bool needUpdateShadow)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupTheme = GetPopupTheme();
    CHECK_NULL_VOID(popupTheme);
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto popupPaintProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    auto renderContext = childNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto defaultBGcolor = popupTheme->GetDefaultBGColor();
    auto backgroundColor = popupPaintProp->GetBackgroundColor().value_or(defaultBGcolor);
    renderContext->UpdateBackgroundColor(backgroundColor);
    BlurStyleOption styleOption;
    styleOption.blurStyle = blurStyle;
    styleOption.colorMode = static_cast<ThemeColorMode>(popupTheme->GetBgThemeColorMode());
    renderContext->UpdateBackBlurStyle(styleOption);
    if (needUpdateShadow) {
        auto shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultSM);
        renderContext->UpdateBackShadow(shadow);
    }
}

void BubblePattern::OnColorConfigurationUpdate()
{
    // Tips: Color mode changes are already adapted, so ConfigChangePerform() control is not required.
    if (isTips_) {
        UpdateStyleOption(BlurStyle::COMPONENT_REGULAR, true);
    } else if (SystemProperties::ConfigChangePerform()) {
        UpdateStyleOption(popupParam_->GetBlurStyle(), false);
    }
    if (isCustomPopup_) {
        return;
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    colorMode_ = context->GetColorMode();
    UpdateBubbleText();
}

void BubblePattern::UpdateAgingTextSize()
{
    if (isCustomPopup_) {
        return;
    }
    CHECK_NULL_VOID(messageNode_);
    messageNode_->MarkDirtyNode();
}

void BubblePattern::UpdateBubbleText(const Color& value)
{
    auto messagenode = GetMessageNode();
    CHECK_NULL_VOID(messagenode);
    auto textLayoutProps = messagenode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProps);
    textLayoutProps->UpdateTextColor(value);
    messagenode->MarkModifyDone();
    messagenode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateBubbleBackGroundColor(const Color& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupPaintProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    popupPaintProp->UpdateBackgroundColor(value);
    CHECK_NULL_VOID(popupParam_);
    UpdateStyleOption(popupParam_->GetBlurStyle(), false);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateMaskColor(const Color& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupPaintProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    popupPaintProp->UpdateMaskColor(value);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateMask(bool maskValue)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupPaintProp = host->GetPaintProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupPaintProp);
    popupPaintProp->UpdateBlockEvent(maskValue);
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateArrowWidth(const CalcDimension& dimension)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupLayoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupLayoutProp);
    if (dimension.Value() > 0 && dimension.Unit() != DimensionUnit::PERCENT) {
        popupLayoutProp->UpdateArrowWidth(dimension);
    }

    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateArrowHeight(const CalcDimension& dimension)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto popupLayoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(popupLayoutProp);
    if (dimension.Value() > 0 && dimension.Unit() != DimensionUnit::PERCENT) {
        popupLayoutProp->UpdateArrowHeight(dimension);
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateWidth(const CalcDimension& dimension)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childNode = AceType::DynamicCast<FrameNode>(host->GetFirstChild());
    CHECK_NULL_VOID(childNode);
    auto childLayoutProperty = childNode->GetLayoutProperty();
    CHECK_NULL_VOID(childLayoutProperty);
    if (dimension.Value() > 0) {
        childLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(dimension), std::nullopt));
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void BubblePattern::UpdateRadius(const CalcDimension& dimension)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProps = host->GetLayoutProperty<BubbleLayoutProperty>();
    if (dimension.Value() >= 0) {
        layoutProps->UpdateRadius(dimension);
    }
    host->MarkModifyDone();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}


} // namespace OHOS::Ace::NG
