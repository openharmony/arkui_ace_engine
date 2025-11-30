/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_DM_DISPLAY_INFO_H
#define FOUNDATION_DM_DISPLAY_INFO_H

#include <cstdint>

namespace OHOS::Rosen {
using DisplayId = uint64_t;

class DisplayInfo {
public:
    DisplayId GetDisplayId() const;
    int32_t GetDpi() const;
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    int32_t GetPhysicalWidth() const;
    int32_t GetPhysicalHeight() const;

    float GetDensityInCurResolution() const;
    float GetVirtualPixelRatio() const;

    float densityInCurRes_ = 1.0f;
    int32_t dpi_ = 320;
    int32_t width_ = 720;
    int32_t height_ = 1280;
};
} // namespace OHOS::Rosen
#endif //FOUNDATION_DM_DISPLAY_INFO_H
