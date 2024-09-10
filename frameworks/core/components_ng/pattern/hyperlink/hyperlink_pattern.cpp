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

#include "core/components_ng/pattern/hyperlink/hyperlink_pattern.h"

#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/common/font_manager.h"
#include "core/common/udmf/udmf_client.h"

namespace OHOS::Ace::NG {
void HyperlinkPattern::OnAttachToFrameNode()
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        fontManager->AddFontNodeNG(host);
    }
}

void HyperlinkPattern::OnDetachFromFrameNode(FrameNode* node)
{
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = WeakClaim(node);
    pipeline->RemoveFontNodeNG(frameNode);
}

void HyperlinkPattern::EnableDrag()
{
    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                         const std::string& /* extraParams */) -> DragDropInfo {
        DragDropInfo info;
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_RETURN(hyperlinkPattern, info);
        auto host = hyperlinkPattern->GetHost();
        CHECK_NULL_RETURN(host, info);
        auto hyperlinkLayoutProperty = host->GetLayoutProperty<HyperlinkLayoutProperty>();
        CHECK_NULL_RETURN(hyperlinkLayoutProperty, info);
        std::string address = hyperlinkLayoutProperty->GetAddress().value_or("");
        std::string content = hyperlinkPattern->GetTextForDisplay();
        auto json = JsonUtil::Create(true);
        json->Put("url", address.c_str());
        json->Put("title", content.c_str());
        auto param = json->ToString();
        info.extraInfo = param;
        RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        if (content.empty()) {
            UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, "");
        } else {
            UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, content);
        }
        event->SetData(unifiedData);
        return info;
    };
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDefaultOnDragStart(std::move(dragStart));
}

void HyperlinkPattern::OnModifyDone()
{
    TextPattern::OnModifyDone();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);

    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    InitClickEvent(gestureHub);
    InitTouchEvent(gestureHub);

    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitInputEvent(inputHub);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);

    isLinked_ = false;
    auto enabled = hub->IsEnabled();
    auto hyperlinkLayoutProperty = host->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(hyperlinkLayoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);
    auto renderContext = host->GetRenderContext();
    if (!enabled) {
        hyperlinkLayoutProperty->UpdateTextColor(
            hyperlinkLayoutProperty->GetColor().value_or(theme->GetTextColor()).BlendOpacity(theme->GetOpacity()));
        renderContext->UpdateForegroundColor(
            hyperlinkLayoutProperty->GetColor().value_or(theme->GetTextColor()).BlendOpacity(theme->GetOpacity()));
    } else {
        hyperlinkLayoutProperty->UpdateTextColor(hyperlinkLayoutProperty->GetColor().value_or(theme->GetTextColor()));
        renderContext->UpdateForegroundColor(hyperlinkLayoutProperty->GetColor().value_or(theme->GetTextColor()));
    }
    if (host->IsDraggable()) {
        EnableDrag();
    }
}

void HyperlinkPattern::LinkToAddress()
{
#if defined(PREVIEW)
    return;
#else
    isLinked_ = true;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hyperlinkLayoutProperty = host->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(hyperlinkLayoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);
    auto color = theme->GetTextColor();
    hyperlinkLayoutProperty->UpdateTextColor(
        hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextLinkedColor()));
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateForegroundColor(
        hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextLinkedColor()));
    hyperlinkLayoutProperty->UpdateTextDecoration(theme->GetTextUnSelectedDecoration());
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    auto address = hyperlinkLayoutProperty->GetAddress().value_or("");
    pipeline->HyperlinkStartAbility(address);
#endif
}

void HyperlinkPattern::InitInputEvent(const RefPtr<InputEventHub>& inputHub)
{
    if (!onHoverEvent_) {
        auto onHoverTask = [wp = WeakClaim(this)](bool isHovered) {
            auto pattern = wp.Upgrade();
            if (pattern) {
                pattern->OnHoverEvent(isHovered);
            }
        };
        onHoverEvent_ = MakeRefPtr<InputEvent>(onHoverTask);
        inputHub->AddOnHoverEvent(onHoverEvent_);
    }
    if (!onMouseEvent_) {
        auto onMouseTask = [wp = WeakClaim(this)](MouseInfo& info) {
            auto pattern = wp.Upgrade();
            if (pattern) {
                pattern->OnMouseEvent(info);
            }
        };
        onMouseEvent_ = MakeRefPtr<InputEvent>(onMouseTask);
        inputHub->AddOnMouseEvent(onMouseEvent_);
    }
}

void HyperlinkPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (onTouchEvent_) {
        return;
    }
    auto touchAfterTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_VOID(hyperlinkPattern);
        if (info.IsPreventDefault() && !hyperlinkPattern->isTouchPreventDefault_) {
            hyperlinkPattern->isTouchPreventDefault_ = info.IsPreventDefault();
        }
        hyperlinkPattern->OnTouchEvent(info);
    };
    gestureHub->RemoveTouchEvent(onTouchEvent_);
    onTouchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchAfterTask));
    gestureHub->AddTouchAfterEvent(onTouchEvent_);
}

void HyperlinkPattern::OnTouchEvent(const TouchEventInfo& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto hyperlinkLayoutProperty = host->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(hyperlinkLayoutProperty);
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    auto touchInfo = touchList.front();
    auto touchType = touchInfo.GetTouchType();
    auto color = theme->GetTextColor();
    if (touchType == TouchType::DOWN) {
        hyperlinkLayoutProperty->UpdateTextDecoration(theme->GetTextSelectedDecoration());
        if (isLinked_) {
            hyperlinkLayoutProperty->UpdateTextDecorationColor(
                hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextLinkedColor()));
        } else {
            hyperlinkLayoutProperty->UpdateTextColor(hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(
                theme->GetTextTouchedColor()));
            hyperlinkLayoutProperty->UpdateTextDecorationColor(
                hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextTouchedColor()));
            renderContext->UpdateForegroundColor(
                hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextTouchedColor()));
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else if (touchType == TouchType::UP) {
        hyperlinkLayoutProperty->UpdateTextDecoration(theme->GetTextUnSelectedDecoration());
        if (!isLinked_) {
            hyperlinkLayoutProperty->UpdateTextColor(hyperlinkLayoutProperty->GetColor().value_or(color));
            renderContext->UpdateForegroundColor(hyperlinkLayoutProperty->GetColor().value_or(color));
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void HyperlinkPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (clickListener_) {
        return;
    }
    auto clickAfterCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_VOID(hyperlinkPattern);
        if (!info.IsPreventDefault() && !hyperlinkPattern->isTouchPreventDefault_) {
            hyperlinkPattern->LinkToAddress();
        }
        hyperlinkPattern->isTouchPreventDefault_ = false;
    };
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickAfterCallback));
    gestureHub->AddClickAfterEvent(clickListener_);
}

void HyperlinkPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool HyperlinkPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if ((event.code == KeyCode::KEY_SPACE || event.code == KeyCode::KEY_ENTER)) {
        LinkToAddress();
        return true;
    }
    return false;
}

void HyperlinkPattern::OnHoverEvent(bool isHovered)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<HyperlinkTheme>();
    CHECK_NULL_VOID(theme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameId = host->GetId();
    auto hyperlinkLayoutProperty = host->GetLayoutProperty<HyperlinkLayoutProperty>();
    CHECK_NULL_VOID(hyperlinkLayoutProperty);
    auto color = theme->GetTextColor();
    if (isHovered) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_POINTING);
        hyperlinkLayoutProperty->UpdateTextDecoration(theme->GetTextSelectedDecoration());
        if (isLinked_) {
            hyperlinkLayoutProperty->UpdateTextDecorationColor(
                hyperlinkLayoutProperty->GetColor().value_or(color).BlendColor(theme->GetTextLinkedColor()));
        } else {
            hyperlinkLayoutProperty->UpdateTextDecorationColor(hyperlinkLayoutProperty->GetColor().value_or(color));
        }
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
        hyperlinkLayoutProperty->UpdateTextDecoration(theme->GetTextUnSelectedDecoration());
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void HyperlinkPattern::OnMouseEvent(MouseInfo& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();
    TouchEvent touchEvent;

    if (frame->IsOutOfTouchTestRegion(
        { static_cast<float>(info.GetLocalLocation().GetX()) + GetHostFrameOffset()->GetX(),
            static_cast<float>(info.GetLocalLocation().GetY()) + GetHostFrameOffset()->GetY() },
        touchEvent)) {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    } else {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(
            frameId, MouseFormat::HAND_POINTING, 0, info.GetAction() == MouseAction::WINDOW_LEAVE);
    }
}
} // namespace OHOS::Ace::NG
