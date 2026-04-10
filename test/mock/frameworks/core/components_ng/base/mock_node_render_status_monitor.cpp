/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/node_render_status_monitor.h"

namespace OHOS::Ace::NG {
MonitorRegisterResult NodeRenderStatusMonitor::RegisterNodeRenderStatusListener(
    FrameNode* frameNode, NodeRenderStatusHandleFunc&& func, MonitorSourceType type)
{
    (void)frameNode;
    (void)func;
    (void)type;
    return {};
}

void NodeRenderStatusMonitor::UnRegisterNodeRenderStatusListener(FrameNode* frameNode, int32_t id)
{
    (void)frameNode;
    (void)id;
}

void NodeRenderStatusMonitor::WalkThroughAncestorForStateListener() {}

bool NodeRenderStatusMonitor::IsRegisterNodeRenderStateChangeCallbackExceedLimit()
{
    return false;
}

NodeRenderState NodeRenderStatusMonitor::GetNodeCurrentRenderState(FrameNode* frameNode)
{
    (void)frameNode;
    return NodeRenderState::ABOUT_TO_RENDER_OUT;
}

void NodeRenderStatusMonitor::NotifyFrameNodeRelease(FrameNode* frameNode)
{
    (void)frameNode;
}
} // namespace OHOS::Ace::NG
