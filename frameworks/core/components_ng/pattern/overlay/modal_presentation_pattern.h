/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_MODAL_PRESENTATION_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_MODAL_PRESENTATION_PATTERN_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/autofill/auto_fill_trigger_state_holder.h"
#include "core/components_ng/manager/focus/focus_view.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/popup_base_pattern.h"

namespace OHOS::Ace::NG {
enum class ContentCoverDismissReason {
    BACK_PRESSED = 0,
    TOUCH_OUTSIDE,
    CLOSE_BUTTON,
};

class ACE_EXPORT ModalPresentationPattern : public PopupBasePattern,
    public FocusView, public AutoFillTriggerStateHolder {
    DECLARE_ACE_TYPE(ModalPresentationPattern, PopupBasePattern, FocusView, AutoFillTriggerStateHolder);

public:
    ModalPresentationPattern(int32_t targetId, ModalTransition type, std::function<void(const std::string&)>&& callback)
        : targetId_(targetId), type_(type), callback_(std::move(callback))
    {}
    ~ModalPresentationPattern() override = default;

    bool IsMeasureBoundary() const override
    {
        return true;
    }

    bool IsAtomicNode() const override
    {
        return false;
    }

    int32_t GetTargetId() const override
    {
        return targetId_;
    }

    ModalTransition GetType() const
    {
        return type_;
    }

    void SetType(ModalTransition type)
    {
        type_ = type;
    }

    void FireCallback(const std::string& value)
    {
        if (callback_) {
            callback_(value);
        }
    }

    void SetHasTransitionEffect(const bool hasTransitionEffect)
    {
        hasTransitionEffect_ = hasTransitionEffect;
    }

    bool HasTransitionEffect() const
    {
        return hasTransitionEffect_;
    }

    void UpdateOnWillDismiss(const std::function<void(int32_t)>&& onWillDismiss) //todo
    {
        onWillDismiss_ = std::move(onWillDismiss);
    }

    bool HasOnWillDismiss() const
    {
        if (onWillDismiss_) {
            return true;
        }
        return false;
    }

    void CallOnWillDismiss(const int32_t reason)
    {
        if (onWillDismiss_) {
            onWillDismiss_(reason);
        }
    }

    void ModalInteractiveDismiss();

    void BeforeCreateLayoutWrapper() override;

    void UpdateOnDisappear(std::function<void()>&& onDisappear) {
        onDisappear_ = std::move(onDisappear);
        isExecuteOnDisappear_ = false;
    }

    void OnDisappear() {
        if (onDisappear_) {
            isExecuteOnDisappear_ = true;
            onDisappear_();
        }
    }

    void UpdateOnWillDisappear(std::function<void()>&& onWillDisappear)
    {
        onWillDisappear_ = std::move(onWillDisappear);
    }

    void OnWillDisappear();

    void UpdateOnAppear(std::function<void()>&& onAppear)
    {
        onAppear_ = std::move(onAppear);
    }

    void OnAppear()
    {
        if (onAppear_) {
            onAppear_();
        }
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::SCOPE, true };
    }

    std::list<int32_t> GetRouteOfFirstScope() override
    {
        return { 0 };
    }

    bool IsExecuteOnDisappear() const
    {
        return isExecuteOnDisappear_;
    }

    bool IsUIExtension() const
    {
        return isUIExtension_;
    }

    void SetProhibitedRemoveByRouter(bool prohibitedRemoveByRouter)
    {
        prohibitedRemoveByRouter_ = prohibitedRemoveByRouter;
    }

    bool IsProhibitedRemoveByRouter() const
    {
        return prohibitedRemoveByRouter_;
    }

    void SetProhibitedRemoveByNavigation(bool prohibitedRemoveByNavigation)
    {
        prohibitedRemoveByNavigation_ = prohibitedRemoveByNavigation;
    }

    bool IsProhibitedRemoveByNavigation() const
    {
        return prohibitedRemoveByNavigation_;
    }

    bool AvoidKeyboard() const override
    {
        // If UIExtensionComponent uses ModalPage, ModalPage will avoid KeyBoard.
        return isUIExtension_;
    }

    void UpdateUIExtensionMode(bool isUIExtension)
    {
        isUIExtension_ = isUIExtension;
    }

    bool AvoidBottom() const override
    {
        // If UIExtensionComponent uses ModalPage, ModalPage will not avoid bottom.
        return !isUIExtension_;
    }

    void RegisterModalBgColorResFunc(const RefPtr<NG::FrameNode>& modalNode,
        NG::ModalStyle& modalStyle);

    bool TriggerAutoSaveWhenInvisible() override
    {
        return true;
    }

    void SetEnableSafeArea(bool enableSafeArea)
    {
        enableSafeArea_ = enableSafeArea;
    }

    bool GetEnableSafeArea() const
    {
        return enableSafeArea_;
    }

    bool IsEnableChildrenMatchParent() override
    {
        return true;
    }

private:
    void OnAttachToFrameNode() override;
    bool isUIExtension_ = false;
    bool prohibitedRemoveByRouter_ = false;
    bool prohibitedRemoveByNavigation_ = true;
    int32_t targetId_ = -1;
    ModalTransition type_ = ModalTransition::DEFAULT;
    bool hasTransitionEffect_ = false;
    std::function<void(const int32_t& info)> onWillDismiss_;
    std::function<void(const std::string&)> callback_;
    std::function<void()> onDisappear_;
    std::function<void()> onWillDisappear_;
    std::function<void()> onAppear_;
    bool isExecuteOnDisappear_ = false;
    bool enableSafeArea_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(ModalPresentationPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_MODAL_PRESENTATION_PATTERN_H
