/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/window_utils.h"

#include "dm/dm_common.h"

namespace OHOS::Ace {
DeviceOrientation WindowUtils::GetDeviceOrientation(int32_t windowOrientation)
{
    DeviceOrientation newOrientation =
        ((windowOrientation == static_cast<int32_t>(Rosen::DisplayOrientation::LANDSCAPE)) ||
            (windowOrientation == static_cast<int32_t>(Rosen::DisplayOrientation::LANDSCAPE_INVERTED)))
            ? DeviceOrientation::LANDSCAPE
            : DeviceOrientation::PORTRAIT;
    return newOrientation;
}
} // namespace OHOS::Ace
