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

#ifndef FOUNDATION_DM_DISPLAY_MANAGER_H
#define FOUNDATION_DM_DISPLAY_MANAGER_H

#include <cstdint>
#include <vector>

#include "refbase.h"
#include "display_info.h"

namespace OHOS::Rosen {
class Display {
public:
    int32_t GetWidth() const;
    int32_t GetHeight() const;

    int32_t GetPhysicalWidth() const;
    int32_t GetPhysicalHeight() const;

    float GetVirtualPixelRatio() const;

    sptr<DisplayInfo> GetDisplayInfo();
    sptr<DisplayInfo> GetDisplayInfoWithCache() const;

    float virtualPixelRatio_ = 1.0f;

    sptr<DisplayInfo> displayInfo_ = std::make_shared<DisplayInfo>();
};

class DisplayManager {
public:
    static DisplayManager& GetInstance();
    std::vector<sptr<Display>> GetAllDisplays(int32_t userId = -1);

    /**
     * @brief Obtain the id of the default display.
     *
     * @return Default display id.
     */
    DisplayId GetDefaultDisplayId();

    /**
     * @brief Get the default display object.
     *
     * @return Default display object.
     */
    sptr<Display> GetDefaultDisplay();

    sptr<Display> GetDisplayById(DisplayId displayId);

    /**
     * @brief Get the default display object by means of sync.
     *
     * @return Default display id.
     */
    sptr<Display> GetDefaultDisplaySync(bool isFromNapi = false, int32_t userId = -1);

    sptr<Display> defaultDisplay_ = std::make_shared<Display>();
private:
    DisplayManager();
    ~DisplayManager();
};
} // namespace OHOS::Rosen

#endif // FOUNDATION_DM_DISPLAY_MANAGER_H
