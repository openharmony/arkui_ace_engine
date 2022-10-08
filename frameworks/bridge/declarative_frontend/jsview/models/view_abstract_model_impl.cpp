/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/event/ace_event_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void ViewAbstractModelImpl::SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    auto impl = inspector->GetInspectorFunctionImpl();
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>(1, 1);
    tapGesture->SetOnActionId([func = std::move(tapEventFunc), impl](GestureEvent& info) {
        if (impl) {
            impl->UpdateEventInfo(info);
        }
        func(info);
    });
    auto click = ViewStackProcessor::GetInstance()->GetBoxComponent();
    click->SetOnClick(tapGesture);

    auto onClickId = EventMarker([func = std::move(clickEventFunc), impl](const BaseEventInfo* info) {
        const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
        if (!clickInfo) {
            return;
        }
        auto newInfo = *clickInfo;
        if (impl) {
            impl->UpdateEventInfo(newInfo);
        }
        func(clickInfo);
    });
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnClickId(onClickId);
    }
}

void ViewAbstractModelImpl::SetOnTouch(TouchEventFunc&& touchEventFunc)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    auto impl = inspector->GetInspectorFunctionImpl();
    auto onTouchId = EventMarker(
        [func = std::move(touchEventFunc), impl](BaseEventInfo* info) {
            if (impl) {
                impl->UpdateEventInfo(*info);
            }
            auto* touchInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(info);
            func(*touchInfo);
        },
        "onTouch");
    auto touchComponent = ViewStackProcessor::GetInstance()->GetTouchListenerComponent();
    touchComponent->SetOnTouchId(onTouchId);
}

void ViewAbstractModelImpl::SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback)
{
    auto onKeyId = EventMarker(
        [func = std::move(onKeyCallback)](BaseEventInfo* info) {
            auto* keyInfo = TypeInfoHelper::DynamicCast<KeyEventInfo>(info);
            func(*keyInfo);
        },
        "onKey", 0);
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(true);
    if (focusableComponent) {
        focusableComponent->SetOnKeyId(onKeyId);
    }
}

void ViewAbstractModelImpl::SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) {}

void ViewAbstractModelImpl::SetOnHover(OnHoverEventFunc&& onHoverEventFunc)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOnHoverId(onHoverEventFunc);
}

void ViewAbstractModelImpl::SetOnDelete(std::function<void()>&& onDeleteCallback)
{
    auto onDeleteId = EventMarker(std::move(onDeleteCallback));
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetOnDeleteId(onDeleteId);
    }
}

void ViewAbstractModelImpl::SetOnAppear(std::function<void()>&& onAppearCallback)
{
    auto onAppearId = EventMarker(std::move(onAppearCallback));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(component);
    component->SetOnAppearEventId(onAppearId);
}

void ViewAbstractModelImpl::SetOnDisAppear(std::function<void()>&& onDisAppearCallback)
{
    auto onDisAppearId = EventMarker(std::move(onDisAppearCallback));
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(component);
    component->SetOnDisappearEventId(onDisAppearId);
}

void ViewAbstractModelImpl::SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback)
{
    auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
    CHECK_NULL_VOID(inspector);
    inspector->SetAccessibilityEvent(EventMarker(std::move(onAccessibilityCallback)));
}

void ViewAbstractModelImpl::SetOnRemoteMessage(RemoteCallback&& onRemoteCallback)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetRemoteMessageEvent(EventMarker(std::move(onRemoteCallback)));
}

void ViewAbstractModelImpl::SetTouchable(bool touchable)
{
    auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
    CHECK_NULL_VOID(mainComponent);
    mainComponent->SetTouchable(touchable);
}

void ViewAbstractModelImpl::SetFocusable(bool focusable)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(focusable);
    }
}

void ViewAbstractModelImpl::SetFocusNode(bool focus)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetFocusNode(!focus);
    }
}

} // namespace OHOS::Ace::Framework
