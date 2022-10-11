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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/window/drag_window.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"

namespace OHOS::Ace::NG {

enum class DragType {
    COMMON,
    GRID,
};

class ACE_EXPORT DragDropManager : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropManager, AceType);

public:
    DragDropManager() = default;
    ~DragDropManager() override = default;

    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<PixelMap>& pixelMap, const GestureEvent& info);
    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<FrameNode>& frameNode, const GestureEvent& info);

    void AddDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        dragFrameNodes_.insert(dragFrameNode);
    }

    void AddGridDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        gridDragFrameNodes_.insert(dragFrameNode);
    }

    void UpdateDragWindowPosition(int32_t globalX, int32_t globalY);
    void OnDragStart(float globalX, float globalY);
    void OnDragMove(float globalX, float globalY, const std::string& extraInfo);
    void OnDragEnd(float globalX, float globalY, const std::string& extraInfo);
    void onDragCancel();
    void OnItemDragStart(float globalX, float globalY);
    void OnItemDragMove(float globalX, float globalY, int32_t draggedIndex);
    void OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex);
    void onItemDragCancel();
    void AddDataToClipboard(const std::string& extraInfo);
    void GetExtraInfoFromClipboard(std::string& extraInfo);
    void RestoreClipboardData();
    void DestroyDragWindow();
    RefPtr<FrameNode> CreateDragRootNode(const RefPtr<UINode>& customNode);

private:
    RefPtr<FrameNode> FindDragFrameNodeByPosition(float globalX, float globalY, DragType dragType);
    void FireOnDragEvent(const RefPtr<FrameNode>& frameNode, const RefPtr<OHOS::Ace::DragEvent>& event,
        DragEventType type, const std::string& extraInfo);
    void FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, const OHOS::Ace::ItemDragInfo& itemDragInfo,
        DragEventType type, int32_t draggedIndex, int32_t insertIndex = 0);
    void CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height);

    std::set<WeakPtr<FrameNode>> dragFrameNodes_;
    std::set<WeakPtr<FrameNode>> gridDragFrameNodes_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<FrameNode> preTargetFrameNode_;
    RefPtr<FrameNode> preGridTargetFrameNode_;
    RefPtr<Clipboard> clipboard_;
    std::function<void(const std::string&)> clipboardCallback_ = nullptr;
    std::function<void(const std::string&)> deleteDataCallback_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(DragDropManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
