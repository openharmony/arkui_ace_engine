/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_GLOBAL_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_GLOBAL_CONTROLLER_H

#include <atomic>
#include <cstdint>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/gestures/drag_event.h"

namespace OHOS::Ace::NG {
class FrameNode;
class ACE_FORCE_EXPORT DragDropGlobalController {
public:
    ~DragDropGlobalController();

    static DragDropGlobalController& GetInstance();

    void PublishMenuStatusWithNode(bool isShowing, const RefPtr<FrameNode>& targetNode = nullptr);
    void UpdateMenuShowingStatus(bool isShowing);
    bool IsMenuShowing() const;
    bool IsInMoving() const;
    void ResetDragDropInitiatingStatus();
    void UpdateDragDropInitiatingStatus(const RefPtr<FrameNode>& frameNode,
        const DragDropInitiatingStatus& dragStatus);
    void SetPrepareDragFrameNode(const WeakPtr<FrameNode>& prepareDragFrameNode);
    const WeakPtr<FrameNode> GetPrepareDragFrameNode() const;
    void SetPreDragStatus(PreDragStatus preDragStatus);
    PreDragStatus GetPreDragStatus() const;
    void UpdateDragFilterShowingStatus(bool isShowing);
    bool IsDragFilterShowing() const;

    void SetDragStartRequestStatus(DragStartRequestStatus dragStartRequestStatus);

    DragStartRequestStatus GetDragStartRequestStatus();

    void SetAsyncDragCallback(std::function<void()> asyncDragCallbac);

    std::function<void()> GetAsyncDragCallback();
private:
    DragDropGlobalController() = default;

private:
    mutable std::shared_mutex mutex_;
    // this is the real time menu show status flag, need to change to pair with menu target node in future
    bool isContextMenuShowing_ = false;
    ACE_DISALLOW_COPY_AND_MOVE(DragDropGlobalController);
    RefPtr<FrameNode> currentDragNode_ = nullptr;
    WeakPtr<FrameNode> prepareDragFrameNode_;
    WeakPtr<FrameNode> menuLiftingTargetNode_;
    PreDragStatus preDragStatus_ = PreDragStatus::ACTION_DETECTING_STATUS;

    bool isDragFilterShowing_ = false;

    DragStartRequestStatus dragStartRequestStatus_{DragStartRequestStatus::READY};
    std::function<void()> asyncDragCallback_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_DRAG_DROP_DRAG_DROP_GLOBAL_CONTROLLER_H
