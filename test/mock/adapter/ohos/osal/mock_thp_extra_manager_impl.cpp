/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "adapter/ohos/osal/thp_extra_manager_impl.h"

namespace OHOS::Ace::NG {
void* THPExtraManagerImpl::lib_ = nullptr;

bool THPExtraManagerImpl::Init(void)
{
    return false;
}

const char* THPExtraManagerImpl::ThpExtraRunCommand(const char* command, const char* parameters)
{
    (void)command;
    (void)parameters;
    return "";
}

int32_t THPExtraManagerImpl::GetHeight(void) const
{
    return 0;
}

int32_t THPExtraManagerImpl::GetWidth(void) const
{
    return 0;
}
} // namespace OHOS::Ace::NG
