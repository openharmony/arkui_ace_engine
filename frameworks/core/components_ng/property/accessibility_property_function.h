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

namespace OHOS::Ace {
class TouchEventInfo;

namespace NG {
class FrameNode;

struct SecCompEnhanceEvent {
    std::vector<uint8_t> dataBuffer;
    TimeStamp time;
};

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
    Action##TYPE Get##TYPE##Func() const \
    {  \
        return action##TYPE##_; \
    } \
protected: \
    Action##TYPE action##TYPE##_;

using ActionNotifyChildAction = std::function<AccessibilityActionResult(const RefPtr<FrameNode>& node,
    NotifyChildActionType childActionType)>;

using ActionAccessibilityActionIntercept =
    std::function<AccessibilityActionInterceptResult(AccessibilityInterfaceAction action)>;

using ActionAccessibilityTransparentCallback = std::function<void(TouchEventInfo& eventInfo)>;

using ActionSpecificSupportActionCallback = std::function<void()>;

using ActionSecurityClickAction = std::function<void(const SecCompEnhanceEvent& event)>;

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
     *          register function: SetNotifyChildAction(const RefPtr<FrameNode>& node,
     *              const ActionNotifyChildAction& actionNotifyChildAction)
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
    DEFINE_ACTION_FUNCTIONS(NotifyChildAction);

    /**
     * @brief set the target's specificSupportActionCallback by other component, will update target's support action
     *
     * @details callback function prototype: ActionSpecificSupportActionCallback
     *          register function: SetSpecificSupportActionCallback()
     *          use register function to register callback.
     *          when one component want influence another target component's support action, set target's callback
     * @param [in] void
     *
     * @return void
     *
     * @attention it will be executed on the UI thread, so be aware of thread safety.
     */
    DEFINE_ACTION_FUNCTIONS(SpecificSupportActionCallback);

    /**
     * @brief the click action will by handle in this callback with sec enhance data
     *
     * @details callback function prototype: ActionSecurityClickAction
     *          register function: SetSecurityClickAction(const SecCompEnhanceEvent& event)
     *          use register function to register callback.
     *          when sec comp want to handle accessibility click with data.
     * @param [in] SecCompEnhanceEvent the enhance data from accessibility
     *
     * @return void
     *
     * @attention it will be executed on the UI thread, so be aware of thread safety.
     */
    DEFINE_ACTION_FUNCTIONS(SecurityClickAction);
public:
    AccessibilityPropertyInnerFunction() = default;

    virtual ~AccessibilityPropertyInnerFunction() = default;
};

/**
 * @brief maintaining the callbacks for interfaces of accessibility property of callback
 * @details maintaining the callbacks for interfaces of accessibility property of callback
 * @note
 * @attention
 * @since
 */
class ACE_FORCE_EXPORT AccessibilityPropertyInterfaceFunction {
    /**
     * @brief when register interface of onAccessibilityActionIntercept,
     *        saving the callback and processing before accessibility click
     *
     * @details callback function prototype: ActionNAccessibilityActionIntercept
     *          register function:
     *              SetAccessibilityActionIntercept(
     *                  const ActionNAccessibilityActionIntercept& actionNAccessibilityActionIntercept)
     *          use register function to register callback.
     *          when the result is ACTION_INTERCEPT, will intercept click action
     *          when the result is ACTION_CONTINUE, will continue process click action
     *          when the result is ACTION_RISE,
     *              will bubble up to the ancestor component to check and process AccessibilityActionIntercept
     * @param [in] AccessibilityInterfaceAction the accessibility action type that handled by registered component
     *
     * @return ActionAccessibilityActionIntercept: the result of intercept or continue handle or continuing to bubble up
     *
     * @attention it will be executed on the UI thread, so be aware of thread safety.
     */
    DEFINE_ACTION_FUNCTIONS(AccessibilityActionIntercept)

    /**
     * @brief when register interface of onAccessibilityHoverTransparent,
     *        saving the callback and processing after hover
     *
     * @details callback function prototype: ActionAccessibilityTransparentCallback
     *          register function:
     *              SetAccessibilityTransparentCallback(
     *                  const ActionAccessibilityTransparentCallback& actionAccessibilityTransparentCallback)
     *          use register function to register callback.
     * @param [in] TouchEventInfo the original touch event needed return to developer
     */
    DEFINE_ACTION_FUNCTIONS(AccessibilityTransparentCallback)
public:
    AccessibilityPropertyInterfaceFunction() = default;

    virtual ~AccessibilityPropertyInterfaceFunction() = default;
};
} // namespace NG
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_COMPONENTS_NG_PROPERTIES_ACCESSIBILITY_PROPERTY_FUNCTION_H
