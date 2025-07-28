/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_CONSTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_CONSTS_H

#include <cstdint>

namespace OHOS::Ace {
enum ContainerType {
    STAGE_CONTAINER = 1,
    FA_CONTAINER = 2,
    PA_SERVICE_CONTAINER = 3,
    PA_DATA_CONTAINER = 4,
    PA_FORM_CONTAINER = 5,
    FA_SUBWINDOW_CONTAINER = 6,
    DC_CONTAINER = 7,
    WINDOW_FREE_CONTAINER = 9,
    COMPONENT_SUBWINDOW_CONTAINER = 10,
    PLUGIN_SUBCONTAINER = 20,
};

constexpr int32_t INSTANCE_ID_UNDEFINED = -1;
constexpr int32_t INSTANCE_ID_PLATFORM = -2;
constexpr int32_t CONTAINER_ID_DIVIDE_SIZE = 100000;
constexpr int32_t MIN_PLUGIN_SUBCONTAINER_ID = PLUGIN_SUBCONTAINER * CONTAINER_ID_DIVIDE_SIZE;
constexpr int32_t MIN_SUBCONTAINER_ID = COMPONENT_SUBWINDOW_CONTAINER * CONTAINER_ID_DIVIDE_SIZE;
constexpr int32_t MIN_PA_SERVICE_ID = PA_SERVICE_CONTAINER * CONTAINER_ID_DIVIDE_SIZE;
constexpr int32_t WINDOW_FREE_CONTAINER_ID = WINDOW_FREE_CONTAINER * CONTAINER_ID_DIVIDE_SIZE;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_CONTAINER_CONSTS_H
