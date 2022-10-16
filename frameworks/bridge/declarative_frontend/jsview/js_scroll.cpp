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

#include "bridge/declarative_frontend/jsview/js_scroll.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/scroll_model_impl.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/scroll/scroll_model.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ScrollModel> ScrollModel::instance_ = nullptr;

ScrollModel* ScrollModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::ScrollModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::ScrollModelNG());
        } else {
            instance_.reset(new Framework::ScrollModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::FREE, Axis::NONE };
} // namespace

void JSScroll::Create(const JSCallbackInfo& info)
{
    ScrollModel::GetInstance()->Create();
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(info[0])->Unwrap<JSScroller>();
        if (jsScroller) {
            auto positionController = ScrollModel::GetInstance()->GetOrCreateController();
            jsScroller->SetController(positionController);
            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                proxy = AceType::MakeRefPtr<ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(proxy);
            }
            ScrollModel::GetInstance()->SetScrollBarProxy(proxy);
        }
    }
    // init scroll bar
    std::pair<bool, Color> barColor;
    barColor.first = false;
    std::pair<bool, Dimension> barWidth;
    barWidth.first = false;
    ScrollModel::GetInstance()->InitScrollBar(GetTheme<ScrollBarTheme>(), barColor, barWidth, EdgeEffect::NONE);
}

void JSScroll::SetScrollable(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(AXIS.size())) {
        LOGE("value is not valid: %{public}d", value);
        return;
    }
    ScrollModel::GetInstance()->SetAxis(AXIS[value]);
}

void JSScroll::OnScrollBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& dx, const Dimension& dy) -> ScrollInfo {
            ScrollInfo scrollInfo { .dx = dx, .dy = dy };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollInfo);
            auto params = ConvertToJSValues(dx, dy);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollBegin, result is empty.");
                return scrollInfo;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollBegin, result is not object.");
                return scrollInfo;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("dxRemain");
            if (dxRemainValue->IsNumber()) {
                scrollInfo.dx = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            auto dyRemainValue = resObj->GetProperty("dyRemain");
            if (dyRemainValue->IsNumber()) {
                scrollInfo.dy = Dimension(dyRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollInfo;
        };
        ScrollModel::GetInstance()->SetOnScrollBegin(std::move(onScrollBegin));
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScroll = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                            const Dimension& xOffset, const Dimension& yOffset) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(xOffset, yOffset);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
        ScrollModel::GetInstance()->SetOnScroll(std::move(onScroll));
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollEdgeCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto scrollEdge = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                              const NG::ScrollEdge& side) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            auto params = ConvertToJSValues(side);
            func->Call(JSRef<JSObject>(), 1, params.data());
        };
        ScrollModel::GetInstance()->SetOnScrollEdge(std::move(scrollEdge));
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollEndCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto scrollEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Call(JSRef<JSObject>(), 0, nullptr);
        };
        ScrollModel::GetInstance()->SetOnScrollEnd(std::move(scrollEnd));
    }
    args.SetReturnValue(args.This());
}

void JSScroll::JSBind(BindingTarget globalObj)
{
    JSClass<JSScroll>::Declare("Scroll");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScroll>::StaticMethod("create", &JSScroll::Create, opt);
    JSClass<JSScroll>::StaticMethod("scrollable", &JSScroll::SetScrollable, opt);
    JSClass<JSScroll>::StaticMethod("onScrollBegin", &JSScroll::OnScrollBeginCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScroll", &JSScroll::OnScrollCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEdge", &JSScroll::OnScrollEdgeCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEnd", &JSScroll::OnScrollEndCallback, opt);
    JSClass<JSScroll>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSScroll>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScroll>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSScroll>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScroll>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScroll>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSScroll>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSScroll>::StaticMethod("edgeEffect", &JSScroll::SetEdgeEffect, opt);
    JSClass<JSScroll>::StaticMethod("scrollBar", &JSScroll::SetScrollBar, opt);
    JSClass<JSScroll>::StaticMethod("scrollBarColor", &JSScroll::SetScrollBarColor, opt);
    JSClass<JSScroll>::StaticMethod("scrollBarWidth", &JSScroll::SetScrollBarWidth, opt);
    JSClass<JSScroll>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSScroll>::Inherit<JSContainerBase>();
    JSClass<JSScroll>::Inherit<JSViewAbstract>();
    JSClass<JSScroll>::Bind<>(globalObj);
}

void JSScroll::SetScrollBar(int displayMode)
{
    ScrollModel::GetInstance()->SetDisplayMode(displayMode);
}

void JSScroll::SetScrollBarWidth(const std::string& scrollBarWidth)
{
    if (scrollBarWidth.empty()) {
        return;
    }
    ScrollModel::GetInstance()->SetScrollBarWidth(StringUtils::StringToDimension(scrollBarWidth));
}

void JSScroll::SetScrollBarColor(const std::string& scrollBarColor)
{
    if (scrollBarColor.empty()) {
        return;
    }
    ScrollModel::GetInstance()->SetScrollBarColor(Color::FromString(scrollBarColor));
}

void JSScroll::SetEdgeEffect(int edgeEffect)
{
    ScrollModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

} // namespace OHOS::Ace::Framework
