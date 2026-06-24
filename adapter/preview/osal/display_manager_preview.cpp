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

#include "base/display_manager/display_manager.h"
#include "base/utils/system_properties.h"

namespace OHOS::Ace {

namespace {
class DisplayManagerPreview : public DisplayManager {
    DECLARE_ACE_TYPE(DisplayManagerPreview, DisplayManager);
public:
    bool ConvertScreenIdToRsScreenId(uint64_t screenId, uint64_t& rsScreenId) override
    {
        rsScreenId = screenId;
        return true;
    }

    // Preview environment has no real display service; return UNKNOWN.
    FoldDisplayMode GetFoldDisplayMode() override
    {
        return FoldDisplayMode::UNKNOWN;
    }

    // Preview has no Rosen IPC; populate BaseDisplayInfo from SystemProperties.
    // SystemProperties::GetDeviceWidth/Height are set by the preview harness
    // via InitDeviceInfo(). DeviceOrientation only has PORTRAIT/LANDSCAPE,
    // so ROTATION_180/270 cannot be represented.
    RefPtr<BaseDisplayInfo> GetCachedDisplayInfo(uint64_t displayId) override
    {
        auto info = AceType::MakeRefPtr<BaseDisplayInfo>();
        info->SetDisplayId(displayId);
        info->SetWidth(SystemProperties::GetDeviceWidth());
        info->SetHeight(SystemProperties::GetDeviceHeight());
        auto orientation = SystemProperties::GetDeviceOrientation();
        info->SetRotation(orientation == DeviceOrientation::LANDSCAPE
            ? Rotation::ROTATION_90 : Rotation::ROTATION_0);
        return info;
    }

    // Preview has no display change events; return 0 to indicate not registered.
    uint64_t RegisterDisplaySizeChangeCallback(DisplaySizeChangeCallback callback) override
    {
        return 0;
    }

    // No-op: no listeners registered in preview.
    void UnregisterDisplaySizeChangeCallback(uint64_t callbackId) override {}
};
} // namespace

DisplayManager& DisplayManager::GetInstance()
{
    static DisplayManagerPreview instance;
    return instance;
}
} // namespace OHOS::Ace
