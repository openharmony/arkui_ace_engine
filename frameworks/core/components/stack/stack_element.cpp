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

#include "core/components/stack/stack_element.h"

#include "core/components/bubble/bubble_element.h"
#include "core/components/dialog/dialog_element.h"
#include "core/components/drop_filter/drop_filter_element.h"
#include "core/components/page/page_element.h"
#include "core/components/picker/picker_base_element.h"
#include "core/components/popup/popup_component.h"
#include "core/components/text_overlay/text_overlay_element.h"

namespace OHOS::Ace {

void StackElement::PushComponent(const RefPtr<Component>& newComponent, bool directBuild, bool disableTouchEvent)
{
    newComponent_ = newComponent;
    disableTouchEvent_ = disableTouchEvent;
    if (directBuild) {
        PerformBuild();
        return;
    }
    MarkDirty();
}

void StackElement::PopComponent(bool directBuild)
{
    isPop_ = true;
    if (directBuild) {
        PerformBuild();
        return;
    }
    MarkDirty();
}

void StackElement::PushToastComponent(const RefPtr<Component>& newComponent, int32_t toastId)
{
    LOGD("PushToastComponent toastId = %{private}d", toastId);
    operation_ = Operation::TOAST_PUSH;
    newToastComponent_ = newComponent;
    toastId_ = toastId;
    isWaitingForBuild_ = true;
    MarkDirty();
}

void StackElement::PopToastComponent(int32_t toastPopId)
{
    LOGD("PopToastComponent toastId = %{private}d", toastPopId);
    if (isWaitingForBuild_) {
        LOGE("StackElement: waiting for performBuild. Not ready for pop toast.");
        return;
    }
    operation_ = Operation::TOAST_POP;
    toastPopId_ = toastPopId;
    isWaitingForBuild_ = true;
    MarkDirty();
}

bool StackElement::PushDialog(const RefPtr<Component>& newComponent)
{
    // send event to accessibility when show dialog.
    auto context = context_.Upgrade();
    if (context) {
        AccessibilityEvent stackEvent;
        stackEvent.eventType = "ejectdismiss";
        context->SendEventToAccessibility(stackEvent);
    }

    if (isWaitingForBuild_) {
        LOGE("StackElement: waiting for performBuild. Not ready for push dialog.");
        return false;
    }
    newComponent_ = newComponent;
    isWaitingForBuild_ = true;
    operation_ = Operation::DIALOG_PUSH;
    // dialog need to disable the touch event of all other children in stack
    disableTouchEvent_ = true;
    MarkDirty();
    return true;
}

void StackElement::PushPanel(const RefPtr<Component>& newComponent, bool disableTouch)
{
    PushDialog(newComponent);
    disableTouchEvent_ = disableTouch;
    operation_ = Operation::PANEL_PUSH;
}

void StackElement::PopPanel(bool directBuild)
{
    PopDialog(directBuild);
}

bool StackElement::PopDialog(bool directBuild)
{
    // send event to accessibility when pop dialog.
    auto context = context_.Upgrade();
    if (context) {
        AccessibilityEvent stackEvent;
        stackEvent.eventType = "ejectdismiss";
        context->SendEventToAccessibility(stackEvent);
    }

    if (isWaitingForBuild_) {
        LOGE("StackElement: waiting for performBuild. Not ready for pop dialog.");
        return false;
    }
    isWaitingForBuild_ = true;
    operation_ = Operation::DIALOG_POP;
    if (directBuild) {
        PerformBuild();
        return true;
    }
    MarkDirty();
    return true;
}

void StackElement::PopTextOverlay(bool directBuild)
{
    isPop_ = true;
    operation_ = Operation::TEXT_OVERLAY_POP;
    if (directBuild) {
        PerformBuild();
        return;
    }
    MarkDirty();
}

void StackElement::PopPopup(const ComposeId& id)
{
    isPop_ = true;
    popupId_ = id;
    operation_ = Operation::POPUP_POP;
    MarkDirty();
}

void StackElement::PerformPushToast(int32_t toastId)
{
    LOGD("PerformPushToast toastId = %{private}d", toastId_);
    if (newToastComponent_) {
        RefPtr<Element> child = UpdateChild(nullptr, newToastComponent_);
        if (child != nullptr) {
            ToastInfo toastInfo = { toastId, child };
            toastStack_.push_back(toastInfo);
        }
        newToastComponent_ = nullptr;
    }
}

void StackElement::PerformPopToastById(int32_t toastId)
{
    LOGD("PerformPopToastById toastId = %{private}d", toastId);
    if (toastStack_.empty()) {
        return;
    }
    if (toastId == toastStack_.back().toastId) {
        while (!toastStack_.empty()) {
            UpdateChild(toastStack_.back().child, nullptr);
            toastStack_.pop_back();
        }
    } else {
        for (auto it = toastStack_.begin(); it != toastStack_.end(); ++it) {
            if (it->toastId == toastId) {
                UpdateChild(it->child, nullptr);
                toastStack_.erase(it);
                return;
            }
        }
    }
}

void StackElement::PerformPopToast()
{
    LOGD("PerformPopToast");
    if (!toastStack_.empty()) {
        UpdateChild(toastStack_.back().child, nullptr);
        toastStack_.pop_back();
    }
}

void StackElement::PerformPushChild()
{
    if (!newComponent_) {
        return;
    }
    if (!UpdateChild(nullptr, newComponent_)) {
        return;
    }
    // set all other children in stack disable touch event
    for (auto child = (++children_.rbegin()); child != children_.rend(); ++child) {
        auto renderNode = (*child)->GetRenderNode();
        if (renderNode) {
            renderNode->SetDisableTouchEvent(disableTouchEvent_);
        }
    }
    newComponent_ = nullptr;
    auto renderNode = GetRenderNode();
    if (!renderNode) {
        LOGE("Stack render node not exists!");
        return;
    }
    renderNode->MarkNeedLayout();
    if (!focusNodes_.empty() && focusNodes_.back()->IsFocusable()) {
        focusNodes_.back()->RequestFocus();
    }
}

void StackElement::PerformPushPanel()
{
    PerformPushChild();
}

void StackElement::PerformPopDialog()
{
    bool hasDialog = std::any_of(children_.begin(), children_.end(), [](const RefPtr<Element>& child) {
        return AceType::InstanceOf<DialogElement>(child) || AceType::InstanceOf<PickerBaseElement>(child) ||
               AceType::InstanceOf<DropFilterElement>(child);
    });
    if (!hasDialog) {
        EnableTouchEventAndRequestFocus();
        return;
    }
    for (auto iter = children_.rbegin(); iter != children_.rend();) {
        const auto& currentChild = *iter;
        bool isDialog = false;
        if (AceType::InstanceOf<DialogElement>(currentChild) || AceType::InstanceOf<PickerBaseElement>(currentChild) ||
            AceType::InstanceOf<DropFilterElement>(currentChild)) {
            isDialog = true;
        }
        bool isToast = std::any_of(toastStack_.begin(), toastStack_.end(),
            [currentChild](const ToastInfo& toast) { return toast.child == currentChild; });
        if (isToast) {
            // if overlay is a toast, skip it
            ++iter;
        } else {
            UpdateChild(*iter, nullptr);
            if (isDialog) {
                break;
            }
            iter = children_.rbegin();
        }
    }
    EnableTouchEventAndRequestFocus();
}

void StackElement::PerformPopTextOverlay()
{
    if (isPop_) {
        auto child = children_.end();
        while (child != children_.begin()) {
            child--;
            if (AceType::InstanceOf<TextOverlayElement>(*child)) {
                UpdateChild(*child, nullptr);
                break;
            }
        }
        isPop_ = false;
        if (IsFocusable()) {
            RequestFocus();
        }
    }
}

void StackElement::PerformPopPopup(const ComposeId& id)
{
    if (!isPop_) {
        return;
    }
    for (auto iter = children_.rbegin(); iter != children_.rend(); iter++) {
        auto child = DynamicCast<BubbleElement>(*iter);
        if (child && child->GetId() == id) {
            child->FirePopEvent();
            UpdateChild(child, nullptr);
            break;
        }
    }
    isPop_ = false;
    if (IsFocusable()) {
        RequestFocus();
    }
}

void StackElement::ResetBuildOperation()
{
    operation_ = Operation::NONE;
    isWaitingForBuild_ = false;
}

void StackElement::PerformBuild()
{
    LOGD("PerformBuild operation_ = %{private}d", operation_);
    // do special build for dialog and toast
    if (operation_ != Operation::NONE) {
        PerformOperationBuild();
        if (newComponent_ || isPop_) {
            MarkDirty();
        } else {
            return;
        }
    }
    // push component
    if (newComponent_) {
        if (!UpdateChild(nullptr, newComponent_)) {
            return;
        }
        for (auto child = (++children_.rbegin()); child != children_.rend(); ++child) {
            auto renderNode = (*child)->GetRenderNode();
            if (renderNode) {
                renderNode->SetDisableTouchEvent(disableTouchEvent_);
            }
        }
        newComponent_ = nullptr;
        auto renderNode = GetRenderNode();
        if (renderNode) {
            renderNode->MarkNeedLayout();
        }
        if (!focusNodes_.empty() && focusNodes_.back()->IsFocusable()) {
            focusNodes_.back()->RequestFocus();
        }
        return;
    }
    // pop component
    if (isPop_) {
        auto child = children_.end();
        while (child != children_.begin()) {
            child--;
            bool isNotToast = std::none_of(toastStack_.begin(), toastStack_.end(),
                [child](const ToastInfo& toast) { return toast.child == *child; });
            if (isNotToast) {
                UpdateChild(*child, nullptr);
                break;
            }
        }
        isPop_ = false;
        EnableTouchEventAndRequestFocus();
        return;
    }
    ComponentGroupElement::PerformBuild();
}

void StackElement::PerformOperationBuild()
{
    switch (operation_) {
        case Operation::TOAST_POP:
            PerformPopToastById(toastPopId_);
            break;
        case Operation::TOAST_PUSH:
            PerformPopToast();
            PerformPushToast(toastId_);
            break;
        case Operation::DIALOG_POP:
            PerformPopDialog();
            break;
        case Operation::PANEL_PUSH:
            PerformPushPanel();
            break;
        case Operation::DIALOG_PUSH:
            PerformPushChild();
            break;
        case Operation::TEXT_OVERLAY_POP:
            PerformPopTextOverlay();
            break;
        case Operation::POPUP_POP:
            PerformPopPopup(popupId_);
            break;
        default:
            LOGD("Don't need operation.");
            break;
    }
    ResetBuildOperation();
}

bool StackElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    // Only consider the top node.
    return false;
}

void StackElement::OnFocus()
{
    if (focusNodes_.empty()) {
        itLastFocusNode_ = focusNodes_.end();
        return;
    }
    // Only focus on the top focusable child.
    itLastFocusNode_ = focusNodes_.end();
    while (itLastFocusNode_ != focusNodes_.begin()) {
        --itLastFocusNode_;
        if ((*itLastFocusNode_)->RequestFocusImmediately()) {
            FocusNode::OnFocus();
            return;
        }
    }

    // Not found any focusable node, clear focus.
    itLastFocusNode_ = focusNodes_.end();
}

void StackElement::EnableTouchEventAndRequestFocus()
{
    for (auto& child : children_) {
        auto renderNode = child->GetRenderNode();
        if (renderNode) {
            renderNode->SetDisableTouchEvent(false);
        }
    }
    if (IsFocusable()) {
        RequestFocus();
    }
}

} // namespace OHOS::Ace
