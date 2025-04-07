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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_FUNCTION_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_FUNCTION_H

#include "base/memory/ace_type.h"
#include "core/accessibility/accessibility_utils.h"

namespace OHOS::Accessibility {
}

namespace OHOS::Ace::NG {

#define DEFINE_ACTION_FUNCTIONS(TYPE) \
public: \
    void Set##TYPE(const Action##TYPE& action##TYPE) \
    { \
        action##TYPE##_ = action##TYPE; \
    } \
    bool CheckRegister##TYPE() const \
    { \
        return action##TYPE##_ == nullptr; \
    } \
    Action##TYPE GetFunc() const \
    {  \
        return action##TYPE##_; \
    } \
protected: \
    Action##TYPE action##TYPE##_;

using ActionNotifyChildAction = std::function<AccessibilityActionResult(NotifyChildActionType childActionType)>;

/**
 * @brief maintaining the callbacks for components
 * @details maintaining the callbacks for components inner handle in accessibility action or hover
 * @note
 * @attention
 * @since
 */
class ACE_FORCE_EXPORT AccessibilityPropertyInnerFunction {
    /**
     * @brief bubble up the action to ancestor after descendants handled accessibility action
     *
     * @details callback function prototype: ActionNotifyChildAction
     *          register function: SetNotifyChildAction(const ActionNotifyChildAction& actionNotifyChildAction)
     *          use register function to register callback.
     *          when descendants handled accessibility action, will bubble up to the ancestor component, notifying the
     *          ancestor that accessibility action has occurred. The ancestor component can decide on subsequent
     *          processing and whether to continue bubbling up
     * @param [in] NotifyChildActionType the accessibility action type that handled by descendants
     *
     * @return AccessibilityActionResult: the result of ancestor handle or continuing to bubble up
     *
     * @attention it will be executed on the UI thread, so be aware of thread safety.
     */
    DEFINE_ACTION_FUNCTIONS(NotifyChildAction)

public:
    AccessibilityPropertyInnerFunction() = default;

    ~AccessibilityPropertyInnerFunction() = default;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_FUNCTION_H
