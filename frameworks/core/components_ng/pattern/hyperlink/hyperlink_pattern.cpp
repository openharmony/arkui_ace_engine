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

#include "base/json/json_util.h"
#ifdef ENABLE_DRAG_FRAMEWORK
#include "core/common/udmf/udmf_client.h"
#endif

namespace OHOS::Ace::NG {
void HyperlinkPattern::OnAttachToFrameNode() {}

void HyperlinkPattern::EnableDrag()
{
    auto dragStart = [weak = WeakClaim(this)](const RefPtr<OHOS::Ace::DragEvent>& event,
                        const std::string& /* extraParams */) -> DragDropInfo {
        DragDropInfo info;
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_RETURN(hyperlinkPattern, info);
        std::string address = hyperlinkPattern->GetAddress();
        std::string content = hyperlinkPattern->GetTextForDisplay();
        auto json = JsonUtil::Create(true);
        json->Put("url", address.c_str());
        json->Put("title", content.c_str());
        auto param = json->ToString();
        info.extraInfo = param;
#ifdef ENABLE_DRAG_FRAMEWORK
        RefPtr<UnifiedData> unifiedData = UdmfClient::GetInstance()->CreateUnifiedData();
        if (content.empty()) {
            UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, "");
        } else {
            UdmfClient::GetInstance()->AddLinkRecord(unifiedData, address, content);
        }
        event->SetData(unifiedData);
#endif
        return info;
    };
    auto eventHub = GetHost()->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDragStart(std::move(dragStart));
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

    auto inputHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    InitInputEvent(inputHub);

    if (host->IsDraggable()) {
        EnableDrag();
    }
}

void HyperlinkPattern::LinkToAddress()
{
#if defined(PREVIEW)
    LOGW("Unable to jump in preview.");
    return;
#else
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->HyperlinkStartAbility(address_);
#endif
}

void HyperlinkPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& /* info */) {
        auto hyperlinkPattern = weak.Upgrade();
        CHECK_NULL_VOID(hyperlinkPattern);
        hyperlinkPattern->LinkToAddress();
    };
    gestureHub->SetUserOnClick(std::move(clickCallback));
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

void HyperlinkPattern::OnHoverEvent(bool isHovered)
{
    LOGD("Hyperlink OnHoverEvent in. isHovered: %{public}d", isHovered);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();

    if (isHovered) {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_POINTING);
    } else {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    }
}

void HyperlinkPattern::OnMouseEvent(MouseInfo& info)
{
    LOGD("Hyperlink OnMouseEvent in. Button: %{public}d, Action: %{public}d", info.GetButton(), info.GetAction());
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frame = GetHost();
    CHECK_NULL_VOID(frame);
    auto frameId = frame->GetId();

    if (frame->IsOutOfTouchTestRegion({ static_cast<float>(info.GetGlobalLocation().GetX()),
        static_cast<float>(info.GetGlobalLocation().GetY()) }, 0)) {
        pipeline->ChangeMouseStyle(frameId, MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(frameId);
    } else {
        pipeline->SetMouseStyleHoldNode(frameId);
        pipeline->ChangeMouseStyle(frameId, MouseFormat::HAND_POINTING);
    }
}

void HyperlinkPattern::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    json->Put("address", address_.c_str());
}
} // namespace OHOS::Ace::NG
