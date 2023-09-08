/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_ENHANCE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_ENHANCE_H

#include "base/geometry/ng/offset_t.h"
#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
namespace OHOS::Ace::NG {
class ACE_EXPORT ContainerModalViewEnhance : public ContainerModalView {
public:
    static RefPtr<FrameNode> Create(RefPtr<FrameNode>& content);
    static void SetEnableSplit(bool enableSplit)
    {
        enableSplit_ = enableSplit;
    }
protected:
    static RefPtr<FrameNode> BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle = false);
    static RefPtr<FrameNode> AddControlButtons(RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow);
    static void BondingMaxBtnGestureEvent(RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode);
    static void BondingMaxBtnInputEvent(RefPtr<FrameNode>& maximizeBtn, RefPtr<FrameNode>& containerNode);
    static RefPtr<FrameNode> ShowMaxMenu(const RefPtr<FrameNode>& targetNode, OffsetF menuPosition);
    static void BondingMenuItemEvent(RefPtr<FrameNode> item);
    static RefPtr<FrameNode> BuildMenuItem(std::string title, InternalResource::ResourceId resourceId,
        RefPtr<ClickEvent> event, bool chooseCurrent);
    static RefPtr<FrameNode> BuildMaximizeMenuItem();
    static RefPtr<FrameNode> BuildFullScreenMenuItem();
    static RefPtr<FrameNode> BuildDividerMenuItem();
    static RefPtr<FrameNode> BuildLeftSplitMenuItem();
    static RefPtr<FrameNode> BuildRightSplitMenuItem();
    static RefPtr<FrameNode> BuildMenuItemIcon(InternalResource::ResourceId resourceId);
    static RefPtr<FrameNode> BuildMenuItemPadding(PaddingProperty padding, RefPtr<FrameNode> node);
    static void ResetHoverTimer();
    static bool sIsMenuPending_;
    static bool sIsHovering;
    static bool enableSplit_;
    static CancelableCallback<void()> sContextTimer_;

private:
    static OffsetF RecalculateMenuOffset(OffsetF menuPosition);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_ENHANCE_H
