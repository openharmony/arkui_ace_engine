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

#include "bridge/declarative_frontend/jsview/js_scroll.h"

#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/scroll/scroll_component.h"

namespace OHOS::Ace::Framework {

void JSScroll::Create(const JSCallbackInfo& info)
{
    RefPtr<Component> child;
    auto scrollComponent = AceType::MakeRefPtr<OHOS::Ace::ScrollComponent>(child);
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(info[0])->Unwrap<JSScroller>();
        if (jsScroller) {
            auto positionController = AceType::MakeRefPtr<ScrollPositionController>();
            jsScroller->SetController(positionController);
            scrollComponent->SetScrollPositionController(positionController);
        }
    } else {
        auto positionController = AceType::MakeRefPtr<ScrollPositionController>();
        scrollComponent->SetScrollPositionController(positionController);
    }
    ViewStackProcessor::GetInstance()->Push(scrollComponent);
}

void JSScroll::SetScrollable(int32_t value)
{
    if (value >= 0 && value < 4) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto scrollComponent = AceType::DynamicCast<ScrollComponent>(component);
        if (scrollComponent) {
            scrollComponent->SetAxisDirection((Axis)value);
        }
    } else {
        LOGE("invalid value for SetScrollable");
    }
}

void JSScroll::OnScrollCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = EventMarker(
            [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<ScrollEventInfo>(info);
                if (!eventInfo) {
                    return;
                }
                auto params = ConvertToJSValues(eventInfo->GetScrollX(), eventInfo->GetScrollY());
                func->Call(JSRef<JSObject>(), params.size(), params.data());
            });
        auto scrollComponent =
            AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (scrollComponent) {
            if (!scrollComponent->GetScrollPositionController()) {
                scrollComponent->SetScrollPositionController(AceType::MakeRefPtr<ScrollPositionController>());
            }
            scrollComponent->SetOnScroll(onScroll);
        }
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollEdgeCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = EventMarker(
            [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                auto eventInfo = TypeInfoHelper::DynamicCast<ScrollEventInfo>(info);
                if (!eventInfo) {
                    return;
                }
                auto param = ConvertToJSValue(static_cast<int32_t>(eventInfo->GetType()));
                func->Call(JSRef<JSObject>(), 1, &param);
            });
        auto scrollComponent =
            AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (scrollComponent) {
            if (!scrollComponent->GetScrollPositionController()) {
                scrollComponent->SetScrollPositionController(AceType::MakeRefPtr<ScrollPositionController>());
            }
            scrollComponent->SetOnScrollEdge(onScroll);
        }
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollEndCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollStop = EventMarker(
            [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                func->Call(JSRef<JSObject>(), 0, nullptr);
            });
        auto scrollComponent =
            AceType::DynamicCast<ScrollComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (scrollComponent) {
            if (!scrollComponent->GetScrollPositionController()) {
                scrollComponent->SetScrollPositionController(AceType::MakeRefPtr<ScrollPositionController>());
            }
            scrollComponent->SetOnScrollEnd(onScrollStop);
        }
    }
    args.SetReturnValue(args.This());
}

void JSScroll::JSBind(BindingTarget globalObj)
{
    JSClass<JSScroll>::Declare("Scroll");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScroll>::StaticMethod("create", &JSScroll::Create, opt);
    JSClass<JSScroll>::StaticMethod("scrollable", &JSScroll::SetScrollable, opt);
    JSClass<JSScroll>::StaticMethod("onScroll", &JSScroll::OnScrollCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEdge", &JSScroll::OnScrollEdgeCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEnd", &JSScroll::OnScrollEndCallback, opt);
    JSClass<JSScroll>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSScroll>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScroll>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScroll>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScroll>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSScroll>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSScroll>::Inherit<JSContainerBase>();
    JSClass<JSScroll>::Inherit<JSViewAbstract>();
    JSClass<JSScroll>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
