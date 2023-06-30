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

#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"

#include "base/utils/utils.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void DragDropProxy::OnTextDragStart(const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));
#ifndef ENABLE_DRAG_FRAMEWORK
    manager->AddDataToClipboard(extraInfo);
#else
    manager->SetExtraInfo(extraInfo);
#endif // ENABLE_DRAG_FRAMEWORK
}

void DragDropProxy::OnDragStart(
    const GestureEvent& info, const std::string& extraInfo, const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->OnDragStart(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()), frameNode);
#ifndef ENABLE_DRAG_FRAMEWORK
    manager->AddDataToClipboard(extraInfo);
#else
    manager->SetExtraInfo(extraInfo);
#endif // ENABLE_DRAG_FRAMEWORK
}

void DragDropProxy::OnDragMove(const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

#ifdef ENABLE_DRAG_FRAMEWORK
    std::string extraInfo = manager->GetExtraInfo();
#else
    std::string extraInfo;
    manager->GetExtraInfoFromClipboard(extraInfo);
#endif // ENABLE_DRAG_FRAMEWORK

    manager->OnDragMove(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()), extraInfo);
}

void DragDropProxy::OnDragEnd(const GestureEvent& info, bool isTextDragEnd)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));
#ifdef ENABLE_DRAG_FRAMEWORK
    std::string extraInfo = manager->GetExtraInfo();
#else
    std::string extraInfo;
    manager->GetExtraInfoFromClipboard(extraInfo);
#endif // ENABLE_DRAG_FRAMEWORK
    if (isTextDragEnd) {
        manager->OnTextDragEnd(static_cast<float>(info.GetGlobalPoint().GetX()),
            static_cast<float>(info.GetGlobalPoint().GetY()), extraInfo);
    } else {
        manager->OnDragEnd(static_cast<float>(info.GetGlobalPoint().GetX()),
            static_cast<float>(info.GetGlobalPoint().GetY()), extraInfo);
    }
#ifndef ENABLE_DRAG_FRAMEWORK
    manager->RestoreClipboardData();
#endif // ENABLE_DRAG_FRAMEWORK
}

void DragDropProxy::onDragCancel()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->onDragCancel();
}

void DragDropProxy::OnItemDragStart(const GestureEvent& info, const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->OnItemDragStart(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()), frameNode);
}

void DragDropProxy::OnItemDragMove(const GestureEvent& info, int32_t draggedIndex, DragType dragType)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->OnItemDragMove(static_cast<float>(info.GetGlobalPoint().GetX()),
        static_cast<float>(info.GetGlobalPoint().GetY()), draggedIndex, dragType);
}

void DragDropProxy::OnItemDragEnd(const GestureEvent& info, int32_t draggedIndex, DragType dragType)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->OnItemDragEnd(static_cast<float>(info.GetGlobalPoint().GetX()),
        static_cast<float>(info.GetGlobalPoint().GetY()), draggedIndex, dragType);
}

void DragDropProxy::onItemDragCancel()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->onItemDragCancel();
}

void DragDropProxy::DestroyDragWindow()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));

    manager->DestroyDragWindow();
}

} // namespace OHOS::Ace::NG