/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/scroll_bar/js_scroll_bar.h"

#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/models/scroll_bar_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"

#define AXIS_SIZE 3

namespace OHOS::Ace {
std::unique_ptr<ScrollBarModel> ScrollBarModel::instance_ = nullptr;
std::mutex ScrollBarModel::mutex_;

ScrollBarModel* ScrollBarModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::ScrollBarModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::ScrollBarModelNG());
            } else {
                instance_.reset(new Framework::ScrollBarModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
}

namespace OHOS::Ace::Framework {
void JSScrollBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSScrollBar>::Declare("ScrollBar");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScrollBar>::StaticMethod("create", &JSScrollBar::Create, opt);

    JSClass<JSScrollBar>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSScrollBar>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSScrollBar>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSScrollBar>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSScrollBar>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScrollBar>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSScrollBar>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScrollBar>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScrollBar>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSScrollBar>::StaticMethod("enableNestedScroll", &JSScrollBar::JsSetEnableNestedScroll);
    JSClass<JSScrollBar>::StaticMethod("scrollBarColor", &JSScrollBar::JsSetScrollBarColor);

    JSClass<JSScrollBar>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSScrollBar::Create(const JSCallbackInfo& info)
{
    bool proxyFlag = false;
    RefPtr<ScrollProxy> proxy;
    int directionNum = -1;
    int stateNum = -1;
    bool infoflag = false;
    if (info.Length() > 0 && info[0]->IsObject()) {
        infoflag = true;
        auto obj = JSRef<JSObject>::Cast(info[0]);
        auto scrollerValue = obj->GetProperty("scroller");
        if (scrollerValue->IsObject() && JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>()) {
            auto jsScroller = JSRef<JSObject>::Cast(scrollerValue)->Unwrap<JSScroller>();
            jsScroller->SetInstanceId(Container::CurrentId());
            auto scrollBarProxy = jsScroller->GetScrollBarProxy();
            proxyFlag = true;
            proxy = ScrollBarModel::GetInstance()->GetScrollBarProxy(scrollBarProxy);
            jsScroller->SetScrollBarProxy(proxy);
        }

        auto directionValue = obj->GetProperty("direction");
        if (directionValue->IsNumber()) {
            directionNum = directionValue->ToNumber<int32_t>();
        }

        auto stateValue = obj->GetProperty("state");
        if (stateValue->IsNumber()) {
            stateNum = stateValue->ToNumber<int32_t>();
        }
    }

    ScrollBarModel::GetInstance()->Create(proxy, infoflag, proxyFlag, directionNum, stateNum);
}

void JSScrollBar::JsSetEnableNestedScroll(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        ScrollBarModel::GetInstance()->SetEnableNestedScroll(false);
        return;
    }

    ScrollBarModel::GetInstance()->SetEnableNestedScroll(args[0]->ToBoolean());
}

void JSScrollBar::JsSetScrollBarColor(const JSCallbackInfo& args)
{
    Color color;
    if (!JSViewAbstract::ParseColorMetricsToColor(args[0], color)) {
        ScrollBarModel::GetInstance()->ResetScrollBarColor();
    }
    ScrollBarModel::GetInstance()->SetScrollBarColor(color);
}
} // namespace OHOS::Ace::Framework
