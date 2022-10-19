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

#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void DragDropProxy::OnDragStart(const GestureEvent& info, const std::string& extraInfo)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->OnDragStart(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()));

    manager->AddDataToClipboard(extraInfo);
}

void DragDropProxy::OnDragMove(const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    std::string extraInfo;
    manager->GetExtraInfoFromClipboard(extraInfo);

    manager->OnDragMove(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()), extraInfo);
}

void DragDropProxy::OnDragEnd(const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    std::string extraInfo;
    manager->GetExtraInfoFromClipboard(extraInfo);
    manager->OnDragEnd(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()), extraInfo);
    manager->RestoreClipboardData();
}

void DragDropProxy::onDragCancel()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->onDragCancel();
}

void DragDropProxy::OnItemDragStart(const GestureEvent& info)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->OnItemDragStart(
        static_cast<float>(info.GetGlobalPoint().GetX()), static_cast<float>(info.GetGlobalPoint().GetY()));
}

void DragDropProxy::OnItemDragMove(const GestureEvent& info, int32_t draggedIndex)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->OnItemDragMove(static_cast<float>(info.GetGlobalPoint().GetX()),
        static_cast<float>(info.GetGlobalPoint().GetY()), draggedIndex);
}

void DragDropProxy::OnItemDragEnd(const GestureEvent& info, int32_t draggedIndex)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->OnItemDragEnd(static_cast<float>(info.GetGlobalPoint().GetX()),
        static_cast<float>(info.GetGlobalPoint().GetY()), draggedIndex);
}

void DragDropProxy::onItemDragCancel()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->onItemDragCancel();
}

void DragDropProxy::DestroyDragWindow()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);

    manager->DestroyDragWindow();
}

} // namespace OHOS::Ace::NG