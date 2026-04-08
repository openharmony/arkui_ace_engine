/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/common/container_scope.h"

namespace OHOS::Ace {
int32_t ContainerScope::CurrentId()
{
    return 0;
}

int32_t ContainerScope::CurrentLocalId()
{
    return 0;
}

int32_t ContainerScope::DefaultId()
{
    return 0;
}

int32_t ContainerScope::SingletonId()
{
    return 0;
}

int32_t ContainerScope::RecentActiveId()
{
    return 0;
}

int32_t ContainerScope::RecentForegroundId()
{
    return 0;
}

std::pair<int32_t, InstanceIdGenReason> ContainerScope::CurrentIdWithReason()
{
    return { 0, InstanceIdGenReason::UNDEFINED };
}

const std::string ContainerScope::ReasonToDescription(InstanceIdGenReason reason)
{
    (void)reason;
    return {};
}

const std::set<int32_t> ContainerScope::GetAllUIContexts()
{
    return {};
}

void ContainerScope::Add(int32_t id)
{
    (void)id;
}

void ContainerScope::Remove(int32_t id)
{
    (void)id;
}

void ContainerScope::RemoveAndCheck(int32_t id)
{
    (void)id;
}

uint32_t ContainerScope::ContainerCount()
{
    return 0;
}

void ContainerScope::UpdateCurrent(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateLocalCurrent(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateSingleton(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateRecentActive(int32_t id)
{
    (void)id;
}

void ContainerScope::UpdateRecentForeground(int32_t id)
{
    (void)id;
}
} // namespace OHOS::Ace
