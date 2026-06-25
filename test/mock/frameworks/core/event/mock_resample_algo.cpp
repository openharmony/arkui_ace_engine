/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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
