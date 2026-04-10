/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 */

#include "core/event/resample_algo.h"

namespace OHOS::Ace {
ResamplePoint ResampleAlgo::LinearInterpolation(const AvgPoint& history, const AvgPoint& current, uint64_t nanoTimeStamp)
{
    (void)history;
    (void)current;
    (void)nanoTimeStamp;
    return {};
}

ResamplePoint ResampleAlgo::GetResampleCoord(const std::vector<PointerEvent>&& history,
    const std::vector<PointerEvent>&& current, uint64_t nanoTimeStamp, CoordinateType coordinateType)
{
    (void)history;
    (void)current;
    (void)nanoTimeStamp;
    (void)coordinateType;
    return {};
}
} // namespace OHOS::Ace
