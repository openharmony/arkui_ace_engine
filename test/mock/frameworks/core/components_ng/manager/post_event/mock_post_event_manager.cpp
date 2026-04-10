/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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
