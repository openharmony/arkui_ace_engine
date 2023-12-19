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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_CONTROLLER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_CONTROLLER_H

#include <memory>

namespace OHOS {
namespace Ace {
#ifndef ACE_EXPORT
#define ACE_EXPORT __attribute__((visibility("default")))
#endif
class UIContent;
/**
 * @class NavigationController
 */
class ACE_EXPORT NavigationController {
public:
    /**
     * @brief Get NavigationController by containId and navigationId.
     * @param uiContent The uiContent.
     * @param navigationId The navigation id.
     * @return Returns the NavigationController.
     */
    static NavigationController* GetNavigationController(
        UIContent* uiContent, const std::string& navigationId);

    NavigationController() = default;
    virtual ~NavigationController() = default;

    /**
     * @brief The stack top is NavDestination or not.
     * @return Returns the result of this interface.
     */
    virtual bool IsNavDestinationInTopStack() { return false; };
    /**
     * @brief Get top navDestination handle in the stack top.
     * @return Returns handle of this interface
     */
    virtual int32_t GetTopHandle() { return 0; };
    /**
     * @brief Set PIPMode by handle.
     * @param handle The node handle.
     */
    virtual void SetInPIPMode(int32_t handle) {};
    /**
     * @brief Pop top stack by handle.
     * @param destroy The true will delete PIPMode.
     */
    virtual void PopInPIP(bool destroy = false) {};
    /**
     * @brief Push stack by handle.
     * @param handle The node handle.
     */
    virtual void PushInPIP(int32_t handle) {};
    /**
     * @brief Delete PIPMode by handle.
     * @param handle The node handle.
     */
    virtual void DeletePIPMode(int32_t handle) {};
};
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_CONTROLLER_H
