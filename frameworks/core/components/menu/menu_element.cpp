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

#include "core/components/menu/menu_element.h"

#include "core/components/box/render_box.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {

void MenuElement::PerformBuild()
{
    data_ = AceType::DynamicCast<MenuComponent>(component_);
    if (!data_) {
        LOGE("component is null.");
        return;
    }

    auto popup = data_->GetPopup();
    if (!popup) {
        LOGE("popup of menu is null.");
        return;
    }

    popup->SetOptionClickedCallback([weak = WeakClaim(this)](std::size_t index) {
        auto refPtr = weak.Upgrade();
        if (!refPtr) {
            return;
        }
        refPtr->OnOptionCallback(index);
    });
    popup->SetPopupCanceledCallback([weak = WeakClaim(this)]() {
        auto refPtr = weak.Upgrade();
        if (!refPtr) {
            return;
        }
        refPtr->OnCanceledCallback();
    });
    if (!data_->GetOnCancel().IsEmpty()) {
        jsCancelCallback_ = AceAsyncEvent<void(const std::string&)>::Create(data_->GetOnCancel(), context_);
    }
    if (!data_->GetOnSuccess().IsEmpty()) {
        jsSuccessCallback_ = AceAsyncEvent<void(const std::string&)>::Create(data_->GetOnSuccess(), context_);
    }
    data_->SetTargetCallback([weak = WeakClaim(this)](const ComposeId& id, const Offset& point) {
        auto refPtr = weak.Upgrade();
        if (!refPtr) {
            return;
        }
        refPtr->OnTargetCallback(id, point);
    });
}

void MenuElement::OnTargetCallback(const ComposeId& id, const Offset& point)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("context is null.");
        return;
    }

    auto stack = context->GetLastStack();
    if (!stack) {
        LOGE("can not get last stack.");
        return;
    }

    if (!data_ || !data_->GetPopup()) {
        LOGE("can not get popup component.");
        return;
    }

    auto popup = data_->GetPopup();
    if (id.empty()) {
        popup->ShowDialog(stack, point, point, true);
        return;
    }

    const auto& targetElement = context->GetComposedElementById(id);
    if (!targetElement) {
        return;
    }
    const auto& targetRender = targetElement->GetRenderNode();
    if (!targetRender) {
        return;
    }
    Size targetSize = targetRender->GetLayoutSize();
    Offset targetGlobalOffset = targetRender->GetOffsetToStage();
    RefPtr<RenderBox> box = AceType::DynamicCast<RenderBox>(targetRender);
    if (box) {
        targetGlobalOffset += box->GetPaintPosition();
        targetSize = box->GetPaintSize();
    }

    Offset targetRightBottom(targetGlobalOffset.GetX() + targetSize.Width(),
        targetGlobalOffset.GetY() + targetSize.Height());

    popup->ShowDialog(stack, targetGlobalOffset, targetRightBottom, true);
}

void MenuElement::OnOptionCallback(std::size_t index)
{
    if (!jsSuccessCallback_) {
        return;
    }

    if (!data_ || !data_->GetPopup()) {
        LOGE("data component or popup is null.");
        return;
    }

    auto popup = data_->GetPopup();
    auto option = popup->GetSelectOption(index);
    if (!option) {
        LOGE("option of the index is null.");
        return;
    }

    std::string param = std::string("\"selected\",{\"value\":\"").append(option->GetValue().append("\"},null"));
    jsSuccessCallback_(param);
}

void MenuElement::OnCanceledCallback()
{
    if (!jsCancelCallback_) {
        return;
    }

    jsCancelCallback_("\"cancel\",{},null");
}

} // namespace OHOS::Ace