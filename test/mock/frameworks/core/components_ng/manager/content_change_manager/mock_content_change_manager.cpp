/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/content_change_manager/content_change_manager.h"

namespace OHOS::Ace::NG {
ContentChangeManager::ContentChangeManager(const RefPtr<TaskExecutor>& taskExecutor) : taskExecutor_(taskExecutor) {}

#ifndef IS_RELEASE_VERSION
std::string ContentChangeManager::DumpInfo() const
{
    return {};
}
#endif

void ContentChangeManager::OnVsyncStart() {}

void ContentChangeManager::OnVsyncEnd(const RectF& rootRect)
{
    (void)rootRect;
}
} // namespace OHOS::Ace::NG
