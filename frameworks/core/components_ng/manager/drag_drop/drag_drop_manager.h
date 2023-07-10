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

#include <cstdint>
#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "base/window/drag_window.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT DragDropManager : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropManager, AceType);

public:
    DragDropManager() = default;
    ~DragDropManager() override = default;

    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<PixelMap>& pixelMap, const GestureEvent& info);
    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<UINode>& customNode, const GestureEvent& info);
    RefPtr<DragDropProxy> CreateTextDragDropProxy();

    void AddDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        dragFrameNodes_.insert(dragFrameNode);
    }

    void RemoveDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        dragFrameNodes_.erase(dragFrameNode);
        gridDragFrameNodes_.erase(dragFrameNode);
        listDragFrameNodes_.erase(dragFrameNode);
        textFieldDragFrameNodes_.erase(dragFrameNode);
    }

    void AddGridDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        gridDragFrameNodes_.insert(dragFrameNode);
    }

    void AddListDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        listDragFrameNodes_.insert(dragFrameNode);
    }

    void AddTextFieldDragFrameNode(const WeakPtr<FrameNode>& dragFrameNode)
    {
        textFieldDragFrameNodes_.insert(dragFrameNode);
    }

    void UpdateDragWindowPosition(int32_t globalX, int32_t globalY);
    void OnDragStart(const Point& point, const RefPtr<FrameNode>& frameNode);
    void OnDragMove(const Point& point, const std::string& extraInfo);
    void OnDragEnd(const Point& point, const std::string& extraInfo);
    void OnTextDragEnd(float globalX, float globalY, const std::string& extraInfo);
    void onDragCancel();
    void OnItemDragStart(float globalX, float globalY, const RefPtr<FrameNode>& frameNode);
    void OnItemDragMove(float globalX, float globalY, int32_t draggedIndex, DragType dragType);
    void OnItemDragEnd(float globalX, float globalY, int32_t draggedIndex, DragType dragType);
    void onItemDragCancel();
    void AddDataToClipboard(const std::string& extraInfo);
    void GetExtraInfoFromClipboard(std::string& extraInfo);
    void RestoreClipboardData();
    void DestroyDragWindow();
#ifdef ENABLE_DRAG_FRAMEWORK
    void UpdateDragAllowDrop(const RefPtr<FrameNode>& dragFrameNode);
    void RequireSummary();
    void ClearSummary();
    void SetSummaryMap(const std::map<std::string, int64_t>& summaryMap)
    {
        summaryMap_ = summaryMap;
    }
    RefPtr<DragDropProxy> CreateFrameworkDragDropProxy();
    void UpdatePixelMapPosition(int32_t globalX, int32_t globalY);
    std::string GetExtraInfo();
    void SetExtraInfo(const std::string& extraInfo);
    void ClearExtraInfo();
#endif // ENABLE_DRAG_FRAMEWORK
    void UpdateDragEvent(RefPtr<OHOS::Ace::DragEvent>& event, const Point& point);
    bool CheckDragDropProxy(int64_t id) const;

    bool IsDragged() const
    {
        return isDragged_;
    }

    void SetIsDragged(bool isDragged)
    {
        isDragged_ = isDragged;
    }

    void SetIsDragCancel(bool isDragCancel)
    {
        isDragCancel_ = isDragCancel;
    }

    RefPtr<FrameNode> FindTargetInChildNodes(const RefPtr<UINode> parentNode,
        std::map<int32_t, RefPtr<FrameNode>> hitFrameNodes);

private:
    RefPtr<FrameNode> FindDragFrameNodeByPosition(float globalX, float globalY, DragType dragType);
    void FireOnDragEvent(
        const RefPtr<FrameNode>& frameNode, const Point& point, DragEventType type, const std::string& extraInfo);
    void FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex = 0);
    bool FireOnItemDropEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, int32_t draggedIndex, int32_t insertIndex, bool isSuccess);
    int32_t GetItemIndex(const RefPtr<FrameNode>& frameNode, DragType dragType, float globalX, float globalY);
    void CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height);
    RefPtr<FrameNode> CreateDragRootNode(const RefPtr<UINode>& customNode);

    std::set<WeakPtr<FrameNode>> dragFrameNodes_;
    std::set<WeakPtr<FrameNode>> gridDragFrameNodes_;
    std::set<WeakPtr<FrameNode>> listDragFrameNodes_;
    std::set<WeakPtr<FrameNode>> textFieldDragFrameNodes_;
    RefPtr<DragWindow> dragWindow_;
    RefPtr<FrameNode> draggedFrameNode_;
    RefPtr<FrameNode> preTargetFrameNode_;
    RefPtr<FrameNode> draggedGridFrameNode_;
    RefPtr<FrameNode> preGridTargetFrameNode_;
    RefPtr<FrameNode> dragWindowRootNode_;
    RefPtr<Clipboard> clipboard_;
    std::function<void(const std::string&)> addDataCallback_ = nullptr;
    std::function<void(const std::string&)> getDataCallback_ = nullptr;
    std::function<void(const std::string&)> deleteDataCallback_ = nullptr;
    std::string extraInfo_;
    std::unique_ptr<JsonValue> newData_ = nullptr;
    bool isDragCancel_ = false;
#ifdef ENABLE_DRAG_FRAMEWORK
    std::map<std::string, int64_t> summaryMap_;
#endif // ENABLE_DRAG_FRAMEWORK
    int64_t currentId_ = -1;

    bool isDragged_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(DragDropManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
