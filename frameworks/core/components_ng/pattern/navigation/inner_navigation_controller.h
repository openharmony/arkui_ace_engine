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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_INNER_NAVIGATION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_INNER_NAVIGATION_CONTROLLER_H

#include "base/memory/ace_type.h"
#include "interfaces/inner_api/ace/navigation_controller.h"

namespace OHOS {
namespace Ace {
namespace NG {
class NavigationPattern;
}

/**
 * @class InnerNavigationController
 */
class InnerNavigationController : public OHOS::Ace::NavigationController {
public:
    explicit InnerNavigationController(const WeakPtr<NG::NavigationPattern>& pattern, int32_t containerId);
    bool IsNavDestinationInTopStack() override;
    int32_t GetTopHandle() override;
    void SetInPIPMode(int32_t handle) override;
    void PopInPIP(bool destroy = false) override;
    void PushInPIP(int32_t handle) override;
    void DeletePIPMode(int32_t handle) override;

private:
    WeakPtr<NG::NavigationPattern> weakNavigationPattern_;
    int32_t containerId_;
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_NAVIGATION_INNER_NAVIGATION_CONTROLLER_H
