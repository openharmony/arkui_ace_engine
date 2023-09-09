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
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
#include "core/components_ng/pattern/scroll/scroll_model.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<ScrollModel> ScrollModel::instance_ = nullptr;
std::mutex ScrollModel::mutex_;

ScrollModel* ScrollModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const std::vector<Axis> AXIS = { Axis::VERTICAL, Axis::HORIZONTAL, Axis::FREE, Axis::NONE };

bool ParseJsDimensionArray(const JSRef<JSVal>& jsValue, std::vector<Dimension>& result)
{
    if (!jsValue->IsArray()) {
        LOGE("args is not array orobject!");
        return false;
    }
    JSRef<JSArray> array = JSRef<JSArray>::Cast(jsValue);
    for (size_t i = 0; i < array->Length(); i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        CalcDimension dimension;
        if (JSViewAbstract::ParseJsDimensionVp(value, dimension)) {
            result.emplace_back(static_cast<Dimension>(dimension));
        } else {
            return false;
        }
    }
    return true;
}

bool CheckSnapPaginations(std::vector<Dimension> snapPaginations)
{
    CHECK_NULL_RETURN(!snapPaginations.empty(), false);
    float preValue = (*snapPaginations.begin()).Value();
    CHECK_NULL_RETURN(!Negative(preValue), false);
    auto unit = (*snapPaginations.begin()).Unit();
    for (auto iter = snapPaginations.begin() + 1; iter < snapPaginations.end(); ++iter) {
        if (Negative((*iter).Value()) || (*iter).Unit() != unit || LessOrEqual((*iter).Value(), preValue)) {
            LOGE("Invalid snapPagination");
            return false;
        }
        preValue = (*iter).Value();
    }
    return true;
}
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
                proxy = ScrollModel::GetInstance()->CreateScrollBarProxy();
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

void JSScroll::SetScrollEnabled(const JSCallbackInfo& args)
{
    ScrollModel::GetInstance()->SetScrollEnabled(args[0]->IsBoolean() ? args[0]->ToBoolean() : true);
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

void JSScroll::OnScrollFrameBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollFrameBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                      const Dimension& offset, ScrollState state) -> ScrollFrameResult {
            OHOS::Ace::ScrollFrameResult scrollRes { .offset = offset };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollRes);
            auto params = ConvertToJSValues(offset, state);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollBegin, result is empty.");
                return scrollRes;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollBegin, result is not object.");
                return scrollRes;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("offsetRemain");
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollRes;
        };
        ScrollModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollFrameBegin));
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

void JSScroll::OnScrollStartCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto scrollStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Call(JSRef<JSObject>(), 0, nullptr);
        };
        ScrollModel::GetInstance()->SetOnScrollStart(std::move(scrollStart));
    }
    args.SetReturnValue(args.This());
}

void JSScroll::OnScrollStopCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto scrollStop = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Call(JSRef<JSObject>(), 0, nullptr);
        };
        ScrollModel::GetInstance()->SetOnScrollStop(std::move(scrollStop));
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
    JSClass<JSScroll>::StaticMethod("onScrollFrameBegin", &JSScroll::OnScrollFrameBeginCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScroll", &JSScroll::OnScrollCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEdge", &JSScroll::OnScrollEdgeCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollEnd", &JSScroll::OnScrollEndCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollStart", &JSScroll::OnScrollStartCallback, opt);
    JSClass<JSScroll>::StaticMethod("onScrollStop", &JSScroll::OnScrollStopCallback, opt);
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
    JSClass<JSScroll>::StaticMethod("width", &JSScroll::JsWidth);
    JSClass<JSScroll>::StaticMethod("height", &JSScroll::JsHeight);
    JSClass<JSScroll>::StaticMethod("nestedScroll", &JSScroll::SetNestedScroll);
    JSClass<JSScroll>::StaticMethod("enableScrollInteraction", &JSScroll::SetScrollEnabled);
    JSClass<JSScroll>::StaticMethod("friction", &JSScroll::SetFriction);
    JSClass<JSScroll>::StaticMethod("scrollSnap", &JSScroll::SetScrollSnap);
    JSClass<JSScroll>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSScroll::SetScrollBar(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        LOGE("args is invalid");
        return;
    }
    int32_t displayMode;
    if (args[0]->IsNull() || args[0]->IsUndefined() || !ParseJsInt32(args[0], displayMode)) {
        displayMode = static_cast<int32_t>(NG::DisplayMode::AUTO);
    }
    ScrollModel::GetInstance()->SetDisplayMode(displayMode);
}

void JSScroll::SetScrollBarWidth(const JSCallbackInfo& args)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension scrollBarWidth;
    if (args.Length() < 1) {
        LOGE("args is invalid");
        return;
    }
    if (!ParseJsDimensionVp(args[0], scrollBarWidth) || args[0]->IsNull() || args[0]->IsUndefined() ||
        (args[0]->IsString() && args[0]->ToString().empty()) || LessNotEqual(scrollBarWidth.Value(), 0.0) ||
        scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        scrollBarWidth = theme->GetNormalWidth();
    }
    ScrollModel::GetInstance()->SetScrollBarWidth(scrollBarWidth);
}

void JSScroll::SetScrollBarColor(const std::string& scrollBarColor)
{
    if (scrollBarColor.empty()) {
        return;
    }
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    Color color(theme->GetForegroundColor());
    Color::ParseColorString(scrollBarColor, color);
    ScrollModel::GetInstance()->SetScrollBarColor(color);
}

void JSScroll::SetEdgeEffect(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        LOGE("args is invalid");
        return;
    }
    int32_t edgeEffect;
    if (args[0]->IsNull() || args[0]->IsUndefined() || !ParseJsInt32(args[0], edgeEffect) ||
        edgeEffect < static_cast<int32_t>(EdgeEffect::SPRING) || edgeEffect > static_cast<int32_t>(EdgeEffect::NONE)) {
        edgeEffect = static_cast<int32_t>(EdgeEffect::NONE);
    }
    ScrollModel::GetInstance()->SetEdgeEffect(static_cast<EdgeEffect>(edgeEffect));
}

void JSScroll::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    ScrollModel::GetInstance()->SetHasWidth(true);
}

void JSScroll::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    ScrollModel::GetInstance()->SetHasHeight(true);
}

void JSScroll::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        ScrollModel::GetInstance()->SetNestedScroll(nestedOpt);
        LOGW("Invalid params");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        LOGW("ScrollFroward params invalid");
        backward = 0;
    }
    nestedOpt.forward = static_cast<NestedScrollMode>(froward);
    nestedOpt.backward = static_cast<NestedScrollMode>(backward);
    ScrollModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSScroll::SetFriction(const JSCallbackInfo& info)
{
    double friction = -1.0;
    if (!JSViewAbstract::ParseJsDouble(info[0], friction)) {
        LOGW("Friction params invalid,can not convert to double");
        friction = -1.0;
    }
    ScrollModel::GetInstance()->SetFriction(friction);
}

void JSScroll::SetScrollSnap(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        LOGW("Invalid params");
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    auto snapAlignValue = obj->GetProperty("snapAlign");
    int32_t snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    if (snapAlignValue->IsNull() || snapAlignValue->IsUndefined() || !ParseJsInt32(snapAlignValue, snapAlign) ||
        snapAlign < static_cast<int32_t>(ScrollSnapAlign::NONE) ||
        snapAlign > static_cast<int32_t>(ScrollSnapAlign::END)) {
        snapAlign = static_cast<int32_t>(ScrollSnapAlign::NONE);
    }

    auto paginationValue = obj->GetProperty("snapPagination");
    CalcDimension intervalSize;
    std::vector<Dimension> snapPaginations;
    if (!ParseJsDimensionVp(paginationValue, intervalSize) || intervalSize.IsNegative()) {
        intervalSize = CalcDimension(0.0);
    }
    if (!ParseJsDimensionArray(paginationValue, snapPaginations) || !CheckSnapPaginations(snapPaginations)) {
        std::vector<Dimension>().swap(snapPaginations);
    }

    bool enableSnapToStart = true;
    bool enableSnapToEnd = true;
    ParseJsBool(obj->GetProperty("enableSnapToStart"), enableSnapToStart);
    ParseJsBool(obj->GetProperty("enableSnapToEnd"), enableSnapToEnd);
    std::pair<bool, bool> enableSnapToSide = { enableSnapToStart, enableSnapToEnd };
    ScrollModel::GetInstance()->SetScrollSnap(
        static_cast<ScrollSnapAlign>(snapAlign), intervalSize, snapPaginations, enableSnapToSide);
}
} // namespace OHOS::Ace::Framework
