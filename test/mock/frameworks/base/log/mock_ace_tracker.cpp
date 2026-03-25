/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "base/log/ace_tracker.h"

namespace OHOS::Ace {
void AceTracker::Start() {}

std::string AceTracker::Stop()
{
    return {};
}

AceScopedTracker::AceScopedTracker(const std::string& tag) : tag_(tag), markTime_(0) {}

AceScopedTracker::~AceScopedTracker() = default;
} // namespace OHOS::Ace
