/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/event/axis_event.h"

namespace OHOS::Ace {
AxisEvent AxisEvent::CreateScaleEvent(float scale) const
{
    (void)scale;
    return *this;
}

bool AxisEventChecker::IsAxisEventSequenceCorrect(const AxisEvent& event)
{
    preActionOld_ = preActionNew_;
    preActionNew_ = event.action;
    return true;
}

AxisAction AxisEventChecker::GetPreAction() const
{
    return preActionNew_;
}
} // namespace OHOS::Ace
