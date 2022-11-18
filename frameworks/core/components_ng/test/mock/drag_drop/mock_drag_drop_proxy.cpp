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
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void DragDropProxy::OnDragStart(
    const GestureEvent& info, const std::string& extraInfo, const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    CHECK_NULL_VOID(manager->CheckDragDropProxy(id_));
}

void DragDropProxy::OnDragMove(const GestureEvent& info) {}

void DragDropProxy::OnDragEnd(const GestureEvent& info) {}

void DragDropProxy::onDragCancel() {}

void DragDropProxy::OnItemDragStart(const GestureEvent& info, const RefPtr<FrameNode>& frameNode) {}

void DragDropProxy::OnItemDragMove(const GestureEvent& info, int32_t draggedIndex, DragType dragType) {}

void DragDropProxy::OnItemDragEnd(const GestureEvent& info, int32_t draggedIndex, DragType dragType) {}

void DragDropProxy::onItemDragCancel() {}

void DragDropProxy::DestroyDragWindow() {}
} // namespace OHOS::Ace::NG