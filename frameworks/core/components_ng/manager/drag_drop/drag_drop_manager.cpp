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

#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"

#include "base/geometry/ng/point_t.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<DragDropProxy> DragDropManager::CreateAndShowDragWindow(
    const RefPtr<PixelMap>& pixelMap, const GestureEvent& info)
{
#if !defined(PREVIEW)
    if (dragWindow_) {
        LOGW("CreateAndShowDragWindow: There is a drag window, create drag window failed.");
        return nullptr;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);

    pipeline->SetIsDragged(true);

    auto rect = pipeline->GetCurrentWindowRect();
    dragWindow_ = DragWindow::CreateDragWindow("APP_DRAG_WINDOW",
        static_cast<int32_t>(info.GetGlobalPoint().GetX()) + rect.Left(),
        static_cast<int32_t>(info.GetGlobalPoint().GetY()) + rect.Top(), pixelMap->GetWidth(),
        pixelMap->GetHeight());
    dragWindow_->SetOffset(rect.Left(), rect.Top());
    dragWindow_->DrawPixelMap(pixelMap);
#endif
    auto proxy = MakeRefPtr<DragDropProxy>();
    return proxy;
}

void DragDropManager::UpdateDragWindowPosition(int32_t globalX, int32_t globalY)
{
#if !defined(PREVIEW)
    CHECK_NULL_VOID(dragWindow_);
    dragWindow_->MoveTo(globalX, globalY);
#endif
}

RefPtr<FrameNode> DragDropManager::FindDragFrameNodeByPosition(float globalX, float globalY)
{
    if (dragFrameNodes_.empty()) {
        return nullptr;
    }

    std::map<int32_t, RefPtr<FrameNode>> hitFrameNodes;
    for (const auto& weakNode: dragFrameNodes_) {
        auto frameNode = weakNode.Upgrade();
        if (!frameNode) {
            continue;
        }

        auto geometryNode = frameNode->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }

        auto globalFrameRect = geometryNode->GetFrameRect();
        globalFrameRect.SetOffset(frameNode->GetGlobalOffset());

        if (globalFrameRect.IsInRegion(PointF(globalX, globalY))) {
            hitFrameNodes.insert(std::make_pair(frameNode->GetDepth(), frameNode));
        }
    }

    if (hitFrameNodes.empty()) {
        return nullptr;
    }
    return hitFrameNodes.rbegin()->second;
}

void DragDropManager::OnDragStart(float globalX, float globalY)
{
    preTargetFrameNode_ = FindDragFrameNodeByPosition(globalX, globalY);
}

void DragDropManager::OnDragMove(float globalX, float globalY, const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    UpdateDragWindowPosition(static_cast<int32_t>(globalX), static_cast<int32_t>(globalY));

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    event->SetX(pipeline->ConvertPxToVp(Dimension(globalX, DimensionUnit::PX)));
    event->SetY(pipeline->ConvertPxToVp(Dimension(globalY, DimensionUnit::PX)));

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY);
    if (!dragFrameNode) {
        if (preTargetFrameNode_) {
            FireOnDragEvent(
                preTargetFrameNode_, event, DragEventType::LEAVE, extraInfo);
            preTargetFrameNode_ = nullptr;
        }

        return;
    }

    if (dragFrameNode == preTargetFrameNode_) {
        FireOnDragEvent(dragFrameNode, event, DragEventType::MOVE, extraInfo);
        return;
    }

    if (preTargetFrameNode_) {
        FireOnDragEvent(preTargetFrameNode_, event, DragEventType::LEAVE, extraInfo);
    }

    FireOnDragEvent(dragFrameNode, event, DragEventType::ENTER, extraInfo);
    preTargetFrameNode_ = dragFrameNode;
}

void DragDropManager::OnDragEnd(float globalX, float globalY, const std::string& extraInfo)
{
    preTargetFrameNode_ = nullptr;

    auto dragFrameNode = FindDragFrameNodeByPosition(globalX, globalY);
    if (!dragFrameNode) {
        return;
    }

    auto eventHub = dragFrameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    if (!eventHub->HasOnDrop()) {
        return;
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    event->SetX(pipeline->ConvertPxToVp(Dimension(globalX, DimensionUnit::PX)));
    event->SetY(pipeline->ConvertPxToVp(Dimension(globalY, DimensionUnit::PX)));

    eventHub->FireOnDrop(event, extraInfo);
}

void DragDropManager::onDragCancel()
{
    preTargetFrameNode_ = nullptr;
}

void DragDropManager::FireOnDragEvent(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::DragEvent>& event,
    DragEventType type, const std::string& extraInfo)
{
    auto eventHub = frameNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);

    switch (type) {
        case DragEventType::ENTER:
            eventHub->FireOnDragEnter(event, extraInfo);
            break;
        case DragEventType::MOVE:
            eventHub->FireOnDragMove(event, extraInfo);
            break;
        case DragEventType::LEAVE:
            eventHub->FireOnDragLeave(event, extraInfo);
            break;
        case DragEventType::DROP:
            eventHub->FireOnDrop(event, extraInfo);
            break;
        default:
            break;
    }
}

void DragDropManager::AddDataToClipboard(const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    auto newData = JsonUtil::Create(true);
    newData->Put("customDragInfo", extraInfo.c_str());

    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }
    if (!clipboardCallback_) {
        auto callback = [weakManager = WeakClaim(this), addData = newData->ToString()](const std::string& data) {
            auto dragDropManager = weakManager.Upgrade();
            if (dragDropManager) {
                auto clipboardAllData = JsonUtil::Create(true);
                clipboardAllData->Put("preData", data.c_str());
                clipboardAllData->Put("newData", addData.c_str());
                dragDropManager->clipboard_->SetData(clipboardAllData->ToString(), CopyOptions::Local, true);
            }
        };
        clipboardCallback_ = callback;
    }
    clipboard_->GetData(clipboardCallback_);
}

void DragDropManager::GetExtraInfoFromClipboard(std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }

    std::string* extraInfoPtr = &extraInfo;
    if (!clipboardCallback_) {
        auto callback = [extraInfoPtr](const std::string& data) {
            auto json = JsonUtil::ParseJsonString(data);
            auto newData = JsonUtil::ParseJsonString(json->GetString("newData"));
            *extraInfoPtr = newData->GetString("customDragInfo");
        };
        clipboardCallback_ = callback;
    }

    if (clipboardCallback_) {
        clipboard_->GetData(clipboardCallback_, true);
    }
}

void DragDropManager::RestoreClipboardData()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);

    if (!clipboard_) {
        clipboard_ = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    }

    if (!deleteDataCallback_) {
        auto callback = [weakManager = WeakClaim(this)](const std::string& data) {
            auto dragDropManager = weakManager.Upgrade();
            if (dragDropManager) {
                auto json = JsonUtil::ParseJsonString(data);
                dragDropManager->clipboard_->SetData(json->GetString("preData"));
            }
        };
        deleteDataCallback_ = callback;
    }
    clipboard_->GetData(deleteDataCallback_);
}

void DragDropManager::DestroyDragWindow()
{
#if !defined(PREVIEW)
    CHECK_NULL_VOID(dragWindow_);
    dragWindow_->Destroy();
    dragWindow_ = nullptr;
#endif
}

} // namespace OHOS::Ace::NG