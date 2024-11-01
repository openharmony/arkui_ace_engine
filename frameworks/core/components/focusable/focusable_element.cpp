/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/focusable/focusable_element.h"

#include "core/components/focusable/focusable_component.h"
#include "core/components/touch_listener/touch_listener_component.h"

namespace OHOS::Ace {

constexpr int32_t TOUCH_ELEMENT_UPPER_LEVEL = 5;

void FocusableElement::Update()
{
    UpdateAccessibilityNode();
    auto focusableComponent = DynamicCast<FocusableComponent>(component_);
    if (!focusableComponent) {
        LOGE("Can not dynamicCast to focusableComponent!");
        return;
    }
    SetElementId(focusableComponent->GetElementId());

    // Save isNode
    isNode_ = focusableComponent->IsFocusNode();

    // Save isDeleteDisabled
    isDeleteDisabled_ = focusableComponent->IsDeleteDisabled();

    // Save focusable
    SetFocusable(focusableComponent->IsFocusable());

    // Save show
    SetShow(focusableComponent->CanShow());

    // Save enabled
    SetEnabled(focusableComponent->IsEnabled());

    // Save styles
    boxStyle_ = focusableComponent->GetBoxStyle();
    focusedBoxStyle_ = focusableComponent->GetFocusedBoxStyle();

    // Save callback id.
    const auto& onClickId = focusableComponent->GetOnClickId();
    const auto& onFocusId = focusableComponent->GetOnFocusId();
    const auto& onBlurId = focusableComponent->GetOnBlurId();
    const auto& onKeyId = focusableComponent->GetOnKeyId();
    const auto& onDeleteId = focusableComponent->GetOnDeleteId();
    onFocusMove_ = focusableComponent->GetOnFocusMove();
    onFocus_ = focusableComponent->GetOnFocus();
    onBlur_ = focusableComponent->GetOnBlur();
    tabIndex_ = focusableComponent->GetTabIndex();
    inspectorKey_ = focusableComponent->GetInspectorKey();
    isFocusOnTouch_ = focusableComponent->IsFocusOnTouch();
    isDefaultFocus_ = focusableComponent->IsDefaultFocus();
    isDefaultGroupFocus_ = focusableComponent->IsDefaultGroupFocus();

    if (isFocusOnTouch_) {
        if (!SetFocusOnTouchCallback()) {
            LOGW("Set focus on touch callback failed");
        }
    }

    if (!onClickId.IsEmpty()) {
        auto context = context_.Upgrade();
        if (context) {
            if (context->GetIsDeclarative()) {
                SetOnClickCallback(AceAsyncEvent<void(const std::shared_ptr<ClickInfo>&)>::Create(onClickId, context_));
            } else {
                SetOnClickCallback(AceAsyncEvent<void()>::Create(onClickId, context_));
            }
        }
    }
    if (!onFocusId.IsEmpty()) {
        SetOnFocusCallback(AceAsyncEvent<void()>::Create(onFocusId, context_));
    }
    if (!onBlurId.IsEmpty()) {
        SetOnBlurCallback(AceAsyncEvent<void()>::Create(onBlurId, context_));
    }
    if (!onKeyId.IsEmpty()) {
        auto context = context_.Upgrade();
        if (context) {
            if (context->GetIsDeclarative()) {
                SetOnKeyCallback(AceSyncEvent<void(const std::shared_ptr<KeyEventInfo>&)>::Create(onKeyId, context_));
            } else {
                SetOnKeyCallback([callback = AceSyncEvent<void(const KeyEvent&, bool&)>::Create(onKeyId, context_)](
                                     const KeyEvent& event) {
                    bool result = false;
                    callback(event, result);
                    return result;
                });
            }
        }
    }
    if (!onDeleteId.IsEmpty()) {
        SetOnDeleteCallback(AceAsyncEvent<void()>::Create(onDeleteId, context_));
    }

    if (renderNode_) {
        renderNode_->UpdateAll(focusableComponent);
    }

    const auto& focusableController = focusableComponent->GetFocusableController();
    if (focusableController) {
        focusableController->SetRequestFocusImpl([weak = WeakClaim(this)](bool flag) {
            auto element = weak.Upgrade();
            if (!element) {
                return;
            }
            if (flag) {
                element->RequestFocus();
            } else {
                element->LostSelfFocus();
            }
        });
    }
}

bool FocusableElement::SetFocusOnTouchCallback()
{
    int32_t loop = 0;
    auto parent = GetElementParent().Upgrade();
    while (parent) {
        auto element = AceType::DynamicCast<TouchListenerElement>(parent);
        if (element) {
            auto render = element->GetRenderNode();
            if (!render) {
                parent = parent->GetElementParent().Upgrade();
                ++loop;
                continue;
            }
            auto renderTouch = AceType::DynamicCast<RenderTouchListener>(render);
            if (!renderTouch) {
                parent = parent->GetElementParent().Upgrade();
                ++loop;
                continue;
            }
            renderTouch->SetOnTouchFocusEventCallback(
                [wp = AceType::WeakClaim(this), wcontext = GetContext()]() {
                    auto focusNode = wp.Upgrade();
                    auto context = wcontext.Upgrade();
                    if (!focusNode) {
                        return;
                    }
                    if (!focusNode->IsFocusableWholePath() && context) {
                        context->RootLostFocus();
                    } else {
                        focusNode->RequestFocusImmediately();
                    }
            });
            return true;
        }
        parent = parent->GetElementParent().Upgrade();
        ++loop;
        if (loop == TOUCH_ELEMENT_UPPER_LEVEL) {
            break;
        }
    }
    return false;
}

bool FocusableElement::IsFocusable() const
{
    return isNode_ ? FocusNode::IsFocusable() : FocusGroup::IsFocusable();
}

bool FocusableElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    return isNode_ ? FocusNode::OnKeyEvent(keyEvent) : FocusGroup::OnKeyEvent(keyEvent);
}

void FocusableElement::OnClick()
{
    FocusNode::OnClick();
}

void FocusableElement::HandleFocus()
{
    if (isNode_ && renderNode_) {
        renderNode_->MoveWhenOutOfViewPort(false);
    }
    FocusNode::HandleFocus();
}

void FocusableElement::OnFocus()
{
    if (isNode_) {
        if (renderNode_ != nullptr) {
            renderNode_->Update(focusedBoxStyle_);
            renderNode_->ChangeStatus(RenderStatus::FOCUS);
        }
        FocusNode::OnFocus();
    } else {
        FocusGroup::OnFocus();
    }
}

void FocusableElement::OnBlur()
{
    if (isNode_) {
        if (renderNode_ != nullptr) {
            renderNode_->Update(boxStyle_);
            renderNode_->ChangeStatus(RenderStatus::BLUR);
        }
        FocusNode::OnBlur();
    } else {
        FocusGroup::OnBlur();
    }
}

bool FocusableElement::RequestNextFocus(bool vertical, bool reverse, const Rect& rect)
{
    return false;
}

bool FocusableElement::IsChild() const
{
    return isNode_;
}

void FocusableElement::DumpFocusTree(int32_t depth)
{
    isNode_ ? FocusNode::DumpFocusTree(depth) : FocusGroup::DumpFocusTree(depth);
}

bool FocusableElement::AcceptFocusByRectOfLastFocus(const Rect& rect)
{
    return isNode_ ? FocusNode::AcceptFocusByRectOfLastFocus(rect) : FocusGroup::AcceptFocusByRectOfLastFocus(rect);
}

} // namespace OHOS::Ace
