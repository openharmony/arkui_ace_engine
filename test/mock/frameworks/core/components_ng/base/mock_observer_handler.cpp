/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/base/observer_handler.h"

namespace OHOS::Ace::NG {
UIObserverHandler& UIObserverHandler::GetInstance()
{
    static UIObserverHandler instance;
    return instance;
}

void UIObserverHandler::HandleLayoutDoneCallBack() {}

void UIObserverHandler::HandleDrawCommandSendCallBack() {}

void UIObserverHandler::NotifyDensityChange(double density)
{
    (void)density;
}
} // namespace OHOS::Ace::NG
