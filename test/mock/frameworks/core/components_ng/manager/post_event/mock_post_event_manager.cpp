/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/manager/post_event/post_event_manager.h"

namespace OHOS::Ace::NG {
bool PostEventManager::PostEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent& touchEvent)
{
    (void)uiNode;
    (void)touchEvent;
    return false;
}

bool PostEventManager::PostTouchEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent&& touchEvent)
{
    (void)uiNode;
    (void)touchEvent;
    return false;
}

bool PostEventManager::PostTouchEventWithStrategy(const RefPtr<NG::UINode>& uiNode, TouchEvent&& touchEvent)
{
    (void)uiNode;
    (void)touchEvent;
    return false;
}

bool PostEventManager::PostMouseEvent(const RefPtr<NG::UINode>& uiNode, MouseEvent&& mouseEvent)
{
    (void)uiNode;
    (void)mouseEvent;
    return false;
}

bool PostEventManager::PostMouseEventWithStrategy(const RefPtr<NG::UINode>& uiNode, MouseEvent&& mouseEvent)
{
    (void)uiNode;
    (void)mouseEvent;
    return false;
}

bool PostEventManager::PostAxisEvent(const RefPtr<NG::UINode>& uiNode, AxisEvent&& axisEvent)
{
    (void)uiNode;
    (void)axisEvent;
    return false;
}

bool PostEventManager::PostAxisEventWithStrategy(const RefPtr<NG::UINode>& uiNode, AxisEvent&& axisEvent)
{
    (void)uiNode;
    (void)axisEvent;
    return false;
}

void PostEventManager::SetPassThroughResult(bool passThroughResult)
{
    passThroughResult_ = passThroughResult;
}

RefPtr<FrameNode> PostEventManager::GetPostTargetNode()
{
    return targetNode_.Upgrade();
}
} // namespace OHOS::Ace::NG
