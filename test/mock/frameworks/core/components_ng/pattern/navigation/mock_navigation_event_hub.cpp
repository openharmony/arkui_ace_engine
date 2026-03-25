/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/components_ng/pattern/navigation/navigation_event_hub.h"

namespace OHOS::Ace::NG {
void NavigationEventHub::FireOnAppear() {}

void NavigationEventHub::FireNavBarStateChangeEvent(bool isVisible)
{
    isVisible_ = isVisible;
    if (onNavBarStateChangeEvent_) {
        onNavBarStateChangeEvent_(isVisible);
    }
}
} // namespace OHOS::Ace::NG
