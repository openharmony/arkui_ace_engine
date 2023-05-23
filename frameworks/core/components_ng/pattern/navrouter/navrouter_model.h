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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVEROUTER_NAVEROUTER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVEROUTER_NAVEROUTER_MODEL_H

#include <mutex>

#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace {
class NavRouterModel {
public:
    static NavRouterModel* GetInstance();
    virtual ~NavRouterModel() = default;

    virtual void Create() = 0;
    virtual void SetOnStateChange(std::function<void(bool isActivated)>&& onStateChange) = 0;
    virtual void SetNavRouteMode(int32_t value) = 0;

private:
    static std::unique_ptr<NavRouterModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVEROUTER_NAVEROUTER_MODEL_H