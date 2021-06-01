/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STACK_STACK_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STACK_STACK_ELEMENT_H

#include "core/pipeline/base/component_group_element.h"

namespace OHOS::Ace {

class ACE_EXPORT StackElement : public ComponentGroupElement, public FocusGroup {
    DECLARE_ACE_TYPE(StackElement, ComponentGroupElement, FocusGroup);

enum class Operation {
    NONE,
    TOAST_PUSH,
    TOAST_POP,
    DIALOG_PUSH,
    DIALOG_POP,
    TEXT_OVERLAY_POP,
    POPUP_POP,
    PANEL_PUSH,
    PANEL_POP,
};

struct ToastInfo {
    int32_t toastId = -1;
    RefPtr<Element> child;
};

public:
    void PerformBuild() override;
    void PushComponent(const RefPtr<Component>& newComponent, bool directBuild = false, bool disableTouchEvent = true);
    void PopComponent(bool directBuild = false);
    void PushPanel(const RefPtr<Component>& newComponent, bool disableTouch);
    void PopPanel(bool direct = false);
    void PushToastComponent(const RefPtr<Component>& newComponent, int32_t toastId);
    void PopToastComponent(int32_t toastPopId);
    bool PushDialog(const RefPtr<Component>& newComponent);
    bool PopDialog(bool directBuild = false);
    void PopTextOverlay(bool directBuild = false);
    void PopPopup(const ComposeId& id);

protected:
    void OnFocus() override;
    bool RequestNextFocus(bool vertical, bool reverse, const Rect& rect) override;

private:
    void PerformPushToast(int32_t toastId);
    void PerformPopToastById(int32_t toastId);
    void PerformPopToast();
    void PerformPushChild();
    void PerformPushPanel();
    void PerformPopDialog();
    void PerformPopTextOverlay();
    void PerformPopPopup(const ComposeId& id);
    void ResetBuildOperation();
    void PerformOperationBuild();

    void EnableTouchEventAndRequestFocus();

    RefPtr<Component> newComponent_;
    bool isPop_ { false };
    Operation operation_ { Operation::NONE };
    RefPtr<Component> newToastComponent_;
    int32_t toastId_ { 0 };
    int32_t toastPopId_ { 0 };
    std::vector<ToastInfo> toastStack_;
    bool isWaitingForBuild_ = false;
    bool disableTouchEvent_ = true;
    ComposeId popupId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_STACK_STACK_ELEMENT_H
