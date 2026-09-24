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
int32_t Display::GetWidth() const
{
    return displayInfo_->GetWidth();
}

int32_t Display::GetHeight() const
{
    return displayInfo_->GetHeight();
}

int32_t Display::GetPhysicalWidth() const
{
    return displayInfo_->GetPhysicalWidth();
}

int32_t Display::GetPhysicalHeight() const
{
    return displayInfo_->GetPhysicalHeight();
}

sptr<DisplayInfo> Display::GetDisplayInfo() const
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

DMError Display::GetLiveCreaseRegion(FoldCreaseRegion& region) const
{
    if (!liveCreaseRegionValid_) {
        return DMError::DM_ERROR;
    }
    region = liveCreaseRegion_;
    return DMError::DM_OK;
}

DMError Display::GetAvailableArea(DMRect& area) const
{
    return DMError::DM_ERROR;
}


DisplayManager& DisplayManager::GetInstance()
{
    static DisplayManager instance;
    return instance;
}

DisplayManager::DisplayManager() {}

DisplayManager::~DisplayManager() {}

sptr<Display> DisplayManager::GetDefaultDisplay()
{
    return defaultDisplay_;
}

sptr<Display> DisplayManager::GetDisplayById(DisplayId displayId, bool isGetActualInfo)
{
    return defaultDisplay_;
}

std::vector<sptr<Display>> DisplayManager::GetAllDisplays(int32_t userId)
{
    return { defaultDisplay_ };
}

DisplayId DisplayManager::GetDefaultDisplayId()
{
    return 0;
}

sptr<Display> DisplayManager::GetDefaultDisplaySync(bool isFromNapi, int32_t userId)
{
    return defaultDisplay_;
}

DMError DisplayManager::RegisterDisplayAttributeListener(std::vector<std::string>& attributes,
    sptr<IDisplayAttributeListener> listener)
{
    attributeListener_ = listener;
    return DMError::DM_OK;
}

DMError DisplayManager::UnRegisterDisplayAttributeListener(sptr<IDisplayAttributeListener> listener)
{
    attributeListener_ = nullptr;
    return DMError::DM_OK;
}

DMError DisplayManager::RegisterDisplayListener(const sptr<IDisplayListener>& listener)
{
    displayListener_ = listener;
    return DMError::DM_OK;
}

DMError DisplayManager::UnregisterDisplayListener(sptr<IDisplayListener> listener)
{
    displayListener_ = nullptr;
    return DMError::DM_OK;
}

bool DisplayManager::IsFoldable()
{
    return false;
}

FoldStatus DisplayManager::GetFoldStatus()
{
    return FoldStatus::UNKNOWN;
}

sptr<FoldCreaseRegion> DisplayManager::GetCurrentFoldCreaseRegion()
{
    return nullptr;
}

DMError DisplayManager::GetExpandAvailableArea(DisplayId displayId, DMRect& rect)
{
    return DMError::DM_ERROR;
}
}
