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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_INFO_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_INFO_MANAGER_H

#include <memory>
#include <unordered_map>

#include "ui/base/referenced.h"

namespace OHOS::Ace {

class AxisInfo;
class MouseInfo;

class EventInfoManager : public virtual Referenced {
public:
    int32_t AddAxisInfo(const std::shared_ptr<AxisInfo>& info);
    int32_t RemoveAxisInfo(int32_t eventId);

    int32_t AddMouseInfo(const std::shared_ptr<MouseInfo>& info);
    int32_t RemoveMouseInfo(int32_t eventId);

private:
    int32_t axisNextId_ { 0 };
    std::unordered_map<int32_t, std::shared_ptr<AxisInfo>> axisMap_;

    int32_t mouseNextId_ { 0 };
    std::unordered_map<int32_t, std::shared_ptr<MouseInfo>> mouseMap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_EVENT_INFO_MANAGER_H
