/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

bool BubblePattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool skipLayout)
{
    if (skipMeasure && skipLayout) {
        return false;
    }
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto bubbleLayoutAlgorithm = DynamicCast<BubbleLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(bubbleLayoutAlgorithm, false);
    showTopArrow_ = bubbleLayoutAlgorithm->ShowTopArrow();
    showBottomArrow_ = bubbleLayoutAlgorithm->ShowBottomArrow();
    showCustomArrow_ = bubbleLayoutAlgorithm->ShowCustomArrow();
    arrowPosition_ = bubbleLayoutAlgorithm->GetArrowPosition();
    childOffset_ = bubbleLayoutAlgorithm->GetChildOffset();
    childSize_ = bubbleLayoutAlgorithm->GetChildSize();
    touchRegion_ = bubbleLayoutAlgorithm->GetTouchRegion();
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto paintProperty = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    paintProperty->UpdatePlacement(bubbleLayoutAlgorithm->GetArrowPlacement());
    return true;
}

void BubblePattern::OnModifyDone()
{
    InitTouchEvent();
    RegisterButtonOnHover();
    RegisterButtonOnTouch();
}

void BubblePattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetRenderContext()->SetClipToFrame(true);
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
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(clickPos);
    }
}

void BubblePattern::HandleTouchDown(const Offset& clickPosition)
{
    // TODO: need to check click position
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto bubbleRenderProp = host->GetPaintProperty<BubbleRenderProperty>();
    CHECK_NULL_VOID(bubbleRenderProp);
    if (touchRegion_.IsInRegion(PointF(clickPosition.GetX(), clickPosition.GetY()))) {
        LOGI("Contains the touch region.");
        return;
    }
    auto autoCancel = bubbleRenderProp->GetAutoCancel().value_or(true);
    if (autoCancel) {
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
        auto mouseTask = [weak = WeakClaim(this), buttonNode](bool isHover) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PopupTheme>();
    if (isHover) {
        auto hoverColor = theme->GetButtonHoverColor();
        renderContext->UpdateBackgroundColor(hoverColor);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else {
        auto backgroundColor = theme->GetButtonBackgroundColor();
        renderContext->UpdateBackgroundColor(backgroundColor);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
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
        auto touchCallback = [weak = WeakClaim(this), buttonNode](const TouchEventInfo& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ButtonOnPress(info, buttonNode);
        };
        auto touchEvent = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
        gestureHub->AddTouchEvent(touchEvent);
    }
    touchEventInitFlag_ = true;
}

void BubblePattern::ButtonOnPress(const TouchEventInfo& info, const RefPtr<NG::FrameNode>& buttonNode)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PopupTheme>();
    CHECK_NULL_VOID(theme);
    if (touchType == TouchType::DOWN) {
        auto pressColor = theme->GetButtonPressColor();
        renderContext->UpdateBackgroundColor(pressColor);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else if (touchType == TouchType::UP) {
        auto backgroundColor = theme->GetButtonBackgroundColor();
        renderContext->UpdateBackgroundColor(backgroundColor);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

RefPtr<FrameNode> BubblePattern::GetButtonRowNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto columnNode = AceType::DynamicCast<FrameNode>(host->GetLastChild());
    CHECK_NULL_RETURN(host, nullptr);
    auto buttonRowNode = AceType::DynamicCast<FrameNode>(columnNode->GetLastChild());
    CHECK_NULL_RETURN(host, nullptr);
    if (buttonRowNode->GetTag() != V2::ROW_ETS_TAG) {
        return nullptr;
    }
    if (buttonRowNode->GetChildren().empty()) {
        return nullptr;
    }
    return buttonRowNode;
}

void BubblePattern::PopBubble()
{
    LOGI("BubblePattern::PopBubble from click");
    auto pipelineNg = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineNg);
    auto overlayManager = pipelineNg->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto popupInfo = overlayManager->GetPopupInfo(targetNodeId_);
    if (!popupInfo.isCurrentOnShow) {
        return;
    }
    popupInfo.markNeedUpdate = true;
    popupInfo.popupId = -1;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProp = host->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    auto showInSubWindow = layoutProp->GetShowInSubWindow().value_or(false);
    if (showInSubWindow) {
        SubwindowManager::GetInstance()->HidePopupNG(targetNodeId_);
    } else {
        overlayManager->UpdatePopupNode(targetNodeId_, popupInfo);
    }
}

} // namespace OHOS::Ace::NG