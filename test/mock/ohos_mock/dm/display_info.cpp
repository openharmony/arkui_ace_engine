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

#include "display_info.h"

namespace OHOS::Rosen {
int32_t DisplayInfo::GetDpi() const
{
    return dpi_;
}

DisplayId DisplayInfo::GetDisplayId() const
{
    return 0;
}

float DisplayInfo::GetVirtualPixelRatio() const
{
    return densityInCurRes_;
}

float DisplayInfo::GetDensityInCurResolution() const
{
    return densityInCurRes_;
}

int32_t DisplayInfo::GetWidth() const
{
    return width_;
}

int32_t DisplayInfo::GetHeight() const
{
    return height_;
}

int32_t DisplayInfo::GetPhysicalWidth() const
{
    return width_;
}

int32_t DisplayInfo::GetPhysicalHeight() const
{
    return height_;
}
}
