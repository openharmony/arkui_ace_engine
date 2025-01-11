/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_H

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ContainerModalView : public AceType {
public:
    static RefPtr<FrameNode> Create(RefPtr<FrameNode>& content);
    static bool ConfigCustomWindowMask(RefPtr<PipelineContext>& pipeline, bool enable);

protected:
    static RefPtr<FrameNode> AddControlButtons(RefPtr<FrameNode>& controlButtonsRow);
    static RefPtr<FrameNode> BuildTitleContainer(RefPtr<FrameNode>& containerNode, bool isFloatingTitle = false);
    static RefPtr<FrameNode> BuildTitle(RefPtr<FrameNode>& containerNode, bool isFloatingTitle = false);
    static RefPtr<FrameNode> BuildTitleRow(bool isFloatingTitle = false);
    static RefPtr<FrameNode> BuildControlButton(InternalResource::ResourceId icon, GestureEventFunc&& clickCallback,
        bool isCloseButton = false, bool canDrag = false);
    static void AddButtonHover(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode);
    static void AddButtonMouse(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode);
    static void AddButtonStyleMouseEvent(RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn);
    static void AddButtonHoverEvent(
        RefPtr<InputEventHub>& inputHub, RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn);
    static void AddButtonOnEvent(
        RefPtr<InputEventHub>& inputHub, RefPtr<FrameNode>& buttonNode, RefPtr<FrameNode>& imageNode, bool isCloseBtn);

private:
    static float baseScale;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CONTAINER_MODAL_CONTAINER_MODAL_VIEW_H
