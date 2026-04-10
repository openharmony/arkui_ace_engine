/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include <algorithm>

#include "core/components_ng/property/safe_area_insets.h"

namespace OHOS::Ace::NG {
SafeAreaInsets SafeAreaInsets::Combine(const SafeAreaInsets& other) const
{
    SafeAreaInsets result;
    result.left_ = left_.Combine(other.left_);
    result.top_ = top_.Combine(other.top_);
    result.right_ = right_.Combine(other.right_);
    result.bottom_ = bottom_.Combine(other.bottom_);
    return result;
}

SafeAreaInsets::Inset SafeAreaInsets::Inset::Combine(const Inset& other) const
{
    Inset result;
    if (IsValid() && other.IsValid()) {
        result.start = std::min(start, other.start);
        result.end = std::max(end, other.end);
        return result;
    }
    return other.IsValid() ? other : *this;
}
} // namespace OHOS::Ace::NG
