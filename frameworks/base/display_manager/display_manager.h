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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_DISPLAY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_DISPLAY_MANAGER_H

#include <functional>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/system_properties.h"
#include "core/common/display_info.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT DisplayManager : public virtual AceType {
    DECLARE_ACE_TYPE(DisplayManager, AceType);

public:
    static DisplayManager& GetInstance();
    virtual bool ConvertScreenIdToRsScreenId(uint64_t screenId, uint64_t& rsScreenId) = 0;
    virtual FoldDisplayMode GetFoldDisplayMode() = 0;

    // Preview has no Rosen IPC; populate BaseDisplayInfo from SystemProperties.
    // SystemProperties::GetDeviceWidth/Height are set by the preview harness
    // via InitDeviceInfo(). DeviceOrientation only has PORTRAIT/LANDSCAPE,
    // so ROTATION_180/270 cannot be represented.
    virtual RefPtr<BaseDisplayInfo> GetCachedDisplayInfo(uint64_t displayId)
    {
        auto info = AceType::MakeRefPtr<BaseDisplayInfo>();
        info->SetDisplayId(displayId);
        info->SetWidth(SystemProperties::GetDeviceWidth());
        info->SetHeight(SystemProperties::GetDeviceHeight());
        auto orientation = SystemProperties::GetDeviceOrientation();
        info->SetRotation(orientation == DeviceOrientation::LANDSCAPE ? Rotation::ROTATION_90 : Rotation::ROTATION_0);
        return info;
    };
    // Triggered when display width/height/rotation changes.
    // May execute on a Binder thread, NOT guaranteed to be on the UI thread.
    using DisplaySizeChangeCallback = std::function<void(
        int32_t /* width */, int32_t /* height */, Rotation /* rotation */, uint64_t /* displayId */)>;
    // Returns callbackId > 0 on success, 0 if listener registration failed or callback is null.
    virtual uint64_t RegisterDisplaySizeChangeCallback(DisplaySizeChangeCallback callback)
    {
        return 0;
    };
    virtual void UnregisterDisplaySizeChangeCallback(uint64_t callbackId) {};
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_DISPLAY_MANAGER_H
