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

#include "display_manager.h"

namespace OHOS::Rosen {
sptr<DisplayInfo> Display::GetDisplayInfo()
{
    return displayInfo_;
}

sptr<DisplayInfo> Display::GetDisplayInfoWithCache() const
{
    return displayInfo_;
}

float Display::GetVirtualPixelRatio() const
{
    return displayInfo_->GetVirtualPixelRatio();
}


DisplayManager& DisplayManager::GetInstance()
{
    static DisplayManager instance;
    return instance;
}

sptr<Display> DisplayManager::GetDefaultDisplay()
{
    return defaultDisplay_;
}

sptr<Display> DisplayManager::GetDisplayById(DisplayId displayId)
{
    return defaultDisplay_;
}
}
