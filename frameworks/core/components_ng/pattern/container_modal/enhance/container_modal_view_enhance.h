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
    static RefPtr<FrameNode> BuildMenuItemIcon(InternalResource::ResourceId resourceId);
    static RefPtr<FrameNode> BuildGestureRow(RefPtr<FrameNode>& containerNode);

protected:
    static RefPtr<FrameNode> BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle = false);
    static RefPtr<FrameNode> AddControlButtons(RefPtr<FrameNode>& containerNode, RefPtr<FrameNode>& containerTitleRow);
    static RefPtr<FrameNode> BuildCustomButtonRow(RefPtr<FrameNode>& containerRow);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_ENHANCE_H
