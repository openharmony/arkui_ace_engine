/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

namespace OHOS::Ace::NG {
namespace {
int64_t g_proxyId = 0;
} // namespace

RefPtr<DragDropProxy> DragDropManager::CreateAndShowDragWindow(
    const RefPtr<PixelMap>& pixelMap, const GestureEvent& info)
{
    return nullptr;
}

RefPtr<DragDropProxy> DragDropManager::CreateAndShowDragWindow(
    const RefPtr<UINode>& customNode, const GestureEvent& info)
{
    currentId_ = ++g_proxyId;
    return MakeRefPtr<DragDropProxy>(currentId_);
}

RefPtr<DragDropProxy> DragDropManager::CreateTextDragDropProxy()
{
    return nullptr;
}

void DragDropManager::CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height) {}

RefPtr<FrameNode> DragDropManager::CreateDragRootNode(const RefPtr<UINode>& customNode)
{
    return nullptr;
}

void DragDropManager::UpdateDragWindowPosition(int32_t globalX, int32_t globalY) {}

RefPtr<FrameNode> DragDropManager::FindDragFrameNodeByPosition(
    float globalX, float globalY, DragType dragType, bool findDrop)
{
    return nullptr;
}

bool DragDropManager::CheckDragDropProxy(int64_t id) const
{
    return false;
}

void DragDropManager::OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode) {}

void DragDropManager::OnDragMove(const Point& point, const std::string& extraInfo)
{
    currentId_ = static_cast<int32_t>(point.GetX());
}

void DragDropManager::OnDragEnd(const Point& point, const std::string& extraInfo) {}

void DragDropManager::OnTextDragEnd(float globalX, float globalY, const std::string& extraInfo) {}

void DragDropManager::onDragCancel() {}

void DragDropManager::FireOnDragEvent(
    const RefPtr<FrameNode>& frameNode, const Point& point, DragEventType type, const std::string& extraInfo)
{}

void DragDropManager::OnItemDragStart(float globalX, float globalY, const RefPtr<FrameNode>& frameNode) {}

void DragDropManager::OnItemDragMove(float globalX, float globalY, int32_t draggedIndex, DragType dragType) {}

void DragDropManager::OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType) {}

void DragDropManager::onItemDragCancel() {}

void DragDropManager::FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
    const OHOS::Ace::ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex)
{}

bool DragDropManager::FireOnItemDropEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
    const OHOS::Ace::ItemDragInfo& itemDragInfo, int32_t draggedIndex, int32_t insertIndex, bool isSuccess)
{
    return true;
}

void DragDropManager::AddDataToClipboard(const std::string& extraInfo) {}

void DragDropManager::GetExtraInfoFromClipboard(std::string& extraInfo) {}

void DragDropManager::RestoreClipboardData() {}

void DragDropManager::DestroyDragWindow() {}
} // namespace OHOS::Ace::NG
