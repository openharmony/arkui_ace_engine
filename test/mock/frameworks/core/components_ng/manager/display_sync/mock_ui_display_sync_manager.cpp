/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/manager/display_sync/ui_display_sync_manager.h"

namespace OHOS::Ace {
UIDisplaySyncManager::UIDisplaySyncManager() = default;
UIDisplaySyncManager::~UIDisplaySyncManager() noexcept = default;

void UIDisplaySyncManager::DispatchFunc(int64_t nanoTimestamp)
{
    (void)nanoTimestamp;
}

bool UIDisplaySyncManager::SetVsyncPeriod(int64_t vsyncPeriod)
{
    vsyncPeriod_ = vsyncPeriod;
    return true;
}

int32_t UIDisplaySyncManager::GetAnimatorRate()
{
    return INVALID_ANIMATOR_EXPECTED_RATE;
}

int32_t UIDisplaySyncManager::GetDisplaySyncRate() const
{
    return 0;
}

uint32_t UIDisplaySyncManager::GetDisplaySyncType() const
{
    return 0;
}

int32_t UIDisplaySyncManager::GetMonitorVsyncRate() const
{
    return 0;
}

bool UIDisplaySyncManager::SetRefreshRateMode(int32_t refreshRateMode)
{
    refreshRateMode_ = refreshRateMode;
    return true;
}
} // namespace OHOS::Ace
