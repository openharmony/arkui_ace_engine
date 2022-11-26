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

#include "view_abstract_model_ng.h"

namespace OHOS::Ace::NG {

OffsetF GetMenuPosition(const RefPtr<FrameNode>& targetNode)
{
    // show menu at bottom center point of targetNode
    auto frameSize = targetNode->GetGeometryNode()->GetMarginFrameSize();
    auto position = targetNode->GetPaintRectOffset() + OffsetF(frameSize.Width() / 2, frameSize.Height());
    return position;
}

void CreateCustomMenu(std::function<void()>& buildFunc, const RefPtr<NG::FrameNode>& targetNode, bool isContextMenu,
    const NG::OffsetF& offset)
{
    NG::ScopedViewStackProcessor builderViewStackProcessor;
    buildFunc();
    auto customNode = NG::ViewStackProcessor::GetInstance()->Finish();
    NG::ViewAbstract::BindMenuWithCustomNode(customNode, targetNode, isContextMenu, offset);
}

void ViewAbstractModelNG::BindMenu(std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    GestureEventFunc event;
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (!params.empty()) {
        event = [params, weakTarget](GestureEvent& /* info */) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            // menu already created
            if (params.empty()) {
                NG::ViewAbstract::ShowMenu(targetNode->GetId(), GetMenuPosition(targetNode));
                return;
            }
            NG::ViewAbstract::BindMenuWithItems(std::move(params), targetNode, GetMenuPosition(targetNode));
            params.clear();
        };
    } else if (buildFunc) {
        event = [builderFunc = std::move(buildFunc), weakTarget](const GestureEvent& /* info */) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            CreateCustomMenu(builderFunc, targetNode, false, GetMenuPosition(targetNode));
        };
    } else {
        LOGE("empty param or null builder");
        return;
    }
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    auto onClick = AceType::MakeRefPtr<NG::ClickEvent>(std::move(event));
    gestureHub->AddClickEvent(onClick);

    // delete menu when target node is removed from render tree
    auto eventHub = targetNode->GetEventHub<NG::EventHub>();
    auto destructor = [id = targetNode->GetId()]() {
        auto pipeline = NG::PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto overlayManager = pipeline->GetOverlayManager();
        CHECK_NULL_VOID(overlayManager);
        overlayManager->DeleteMenu(id);
    };
    eventHub->SetOnDisappear(destructor);
}

void ViewAbstractModelNG::BindContextMenu(ResponseType type, std::function<void()>&& buildFunc)
{
    auto targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    auto hub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    auto weakTarget = AceType::WeakClaim(AceType::RawPtr(targetNode));
    if (type == ResponseType::RIGHT_CLICK) {
        OnMouseEventFunc event = [builder = std::move(buildFunc), weakTarget](MouseInfo& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            if (info.GetButton() == MouseButton::RIGHT_BUTTON && info.GetAction() == MouseAction::RELEASE) {
                CreateCustomMenu(builder, targetNode, true,
                    NG::OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY()));
                info.SetStopPropagation(true);
            }
        };
        auto inputHub = targetNode->GetOrCreateInputEventHub();
        CHECK_NULL_VOID(inputHub);
        auto mouseCallback = AceType::MakeRefPtr<InputEvent>(std::move(event));
        inputHub->AddOnMouseEvent(mouseCallback);
    } else if (type == ResponseType::LONG_PRESS) {
        // create or show menu on long press
        auto event = [builder = std::move(buildFunc), weakTarget](const GestureEvent& info) mutable {
            auto targetNode = weakTarget.Upgrade();
            CHECK_NULL_VOID(targetNode);
            CreateCustomMenu(builder, targetNode, true,
                NG::OffsetF(info.GetGlobalLocation().GetX(), info.GetGlobalLocation().GetY()));
        };
        auto longPress = AceType::MakeRefPtr<NG::LongPressEvent>(std::move(event));

        hub->SetLongPressEvent(longPress, false, true);
    } else {
        LOGE("The arg responseType is invalid.");
        return;
    }
}
} // namespace OHOS::Ace::NG
