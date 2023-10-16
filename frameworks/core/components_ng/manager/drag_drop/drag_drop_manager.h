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
#include "core/gestures/velocity_tracker.h"

namespace OHOS::Ace::NG {
enum class DragDropMgrState : int32_t {
    IDLE,
    ABOUT_TO_PREVIEW,
    DRAGGING
};

class ACE_EXPORT DragDropManager : public virtual AceType {
    DECLARE_ACE_TYPE(DragDropManager, AceType);

public:
    DragDropManager() = default;
    ~DragDropManager() override = default;

    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<PixelMap>& pixelMap, const GestureEvent& info);
    RefPtr<DragDropProxy> CreateAndShowDragWindow(const RefPtr<UINode>& customNode, const GestureEvent& info);
    RefPtr<DragDropProxy> CreateTextDragDropProxy();

    void AddDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        dragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void RemoveDragFrameNode(int32_t id)
    {
        dragFrameNodes_.erase(id);
        gridDragFrameNodes_.erase(id);
        listDragFrameNodes_.erase(id);
        textFieldDragFrameNodes_.erase(id);
    }

    void AddGridDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        gridDragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void AddListDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        listDragFrameNodes_.try_emplace(id, dragFrameNode);
    }

    void AddTextFieldDragFrameNode(int32_t id, const WeakPtr<FrameNode>& dragFrameNode)
    {
        textFieldDragFrameNodes_.try_emplace(id, dragFrameNode);
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
    void UpdateDragAllowDrop(const RefPtr<FrameNode>& dragFrameNode, const bool isCopy);
    void RequireSummary();
    void ClearSummary();
    void SetSummaryMap(const std::map<std::string, int64_t>& summaryMap)
    {
        summaryMap_ = summaryMap;
    }
    void ResetRecordSize(uint32_t recordSize = 0);
    uint32_t GetRecordSize() const;
    Rect GetDragWindowRect(const Point& point);
    RefPtr<DragDropProxy> CreateFrameworkDragDropProxy();
    void UpdatePixelMapPosition(int32_t globalX, int32_t globalY);
    std::string GetExtraInfo();
    void SetExtraInfo(const std::string& extraInfo);
    void ClearExtraInfo();
#endif // ENABLE_DRAG_FRAMEWORK
    void UpdateDragEvent(RefPtr<OHOS::Ace::DragEvent>& event, const Point& point);
    bool CheckDragDropProxy(int64_t id) const;

    bool IsWindowConsumed()
    {
        return isWindowConsumed_;
    }

    void SetIsWindowConsumed(bool consumed)
    {
        isWindowConsumed_ = consumed;
    }

    bool IsDragged() const
    {
        return isDragged_;
    }

    void SetIsDragged(bool isDragged)
    {
        if (isDragged && isDragged_ != isDragged && notifyInDraggedCallback_) {
            notifyInDraggedCallback_();
        }
        isDragged_ = isDragged;
    }

    void SetIsDragCancel(bool isDragCancel)
    {
        isDragCancel_ = isDragCancel;
    }

    void SetIsMouseDrag(bool isMouseDragged)
    {
        isMouseDragged_ = isMouseDragged;
    }

    void SetIsDragWindowShow(bool isDragWindowShow)
    {
        isDragWindowShow_ = isDragWindowShow;
    }

    bool IsDragWindowShow()
    {
        return isDragWindowShow_;
    }

    RefPtr<FrameNode> FindTargetInChildNodes(const RefPtr<UINode> parentNode,
        std::vector<RefPtr<FrameNode>> hitFrameNodes, bool findDrop);

    void SetNotifyInDraggedCallback(const std::function<void(void)>& callback)
    {
        notifyInDraggedCallback_ = callback;
    }

    bool IsDragging()
    {
        return dragDropState_ == DragDropMgrState::DRAGGING;
    }

    bool IsAboutToPreview()
    {
        return dragDropState_ == DragDropMgrState::ABOUT_TO_PREVIEW;
    }

    void ResetDragging(DragDropMgrState dragDropMgrState = DragDropMgrState::IDLE)
    {
        dragDropState_ = dragDropMgrState;
    }

private:
    RefPtr<FrameNode> FindDragFrameNodeByPosition(float globalX, float globalY, DragType dragType, bool findDrop);
    void FireOnDragEvent(
        const RefPtr<FrameNode>& frameNode, const Point& point, DragEventType type, const std::string& extraInfo);
    void FireOnItemDragEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, DragEventType type, int32_t draggedIndex, int32_t insertIndex = 0);
    bool FireOnItemDropEvent(const RefPtr<FrameNode>& frameNode, DragType dragType,
        const ItemDragInfo& itemDragInfo, int32_t draggedIndex, int32_t insertIndex, bool isSuccess);
    int32_t GetItemIndex(const RefPtr<FrameNode>& frameNode, DragType dragType, float globalX, float globalY);
    void CreateDragWindow(const GestureEvent& info, uint32_t width, uint32_t height);
    RefPtr<FrameNode> CreateDragRootNode(const RefPtr<UINode>& customNode);
    void ClearVelocityInfo();
    void UpdateVelocityTrackerPoint(const Point& point, bool isEnd = false);
    void PrintDragFrameNode(const Point& point, const RefPtr<FrameNode>& dragFrameNode);
    void FireOnDragEventWithDragType(const RefPtr<EventHub>& eventHub, DragEventType type,
        RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams);

    std::map<int32_t, WeakPtr<FrameNode>> dragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> gridDragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> listDragFrameNodes_;
    std::map<int32_t, WeakPtr<FrameNode>> textFieldDragFrameNodes_;
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
    uint32_t recordSize_ = 0;
#endif // ENABLE_DRAG_FRAMEWORK
    int64_t currentId_ = -1;

    std::function<void(void)> notifyInDraggedCallback_ = nullptr;
    bool isDragged_ = false;
    bool isMouseDragged_ = false;
    bool isWindowConsumed_ = false;
    bool isDragWindowShow_ = false;
    VelocityTracker velocityTracker_;
    DragDropMgrState dragDropState_ = DragDropMgrState::IDLE;
    Rect previewRect_ { -1, -1, -1, -1 };

    ACE_DISALLOW_COPY_AND_MOVE(DragDropManager);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_MANAGER_H
