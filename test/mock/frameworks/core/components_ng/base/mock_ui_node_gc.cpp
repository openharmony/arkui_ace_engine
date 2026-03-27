/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/ui_node_gc.h"

namespace OHOS::Ace::NG {
void UiNodeGc::OnReleaseFunc(OHOS::Ace::NG::UINode* frameNodeRawPtr)
{
    (void)frameNodeRawPtr;
}

void UiNodeGc::ReleaseNodeRawMemory(int64_t deadline, const RefPtr<TaskExecutor>& taskExecutor)
{
    (void)deadline;
    (void)taskExecutor;
}

void UiNodeGc::PostReleaseNodeRawMemoryTask(const RefPtr<TaskExecutor>& taskExecutor)
{
    (void)taskExecutor;
}
} // namespace OHOS::Ace::NG
