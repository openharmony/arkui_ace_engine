/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_scroll_theme.h"
#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/scroll_model_impl.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scrollable.h"
#include "core/components_ng/pattern/scroll/inner/scroll_bar.h"
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
            jsScroller->SetInstanceId(Container::CurrentId());
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
    JSScrollTheme::ApplyTheme();
}

void JSScroll::SetScrollable(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(AXIS.size())) {
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
        auto onScrollBegin = [func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& dx, const Dimension& dy) -> ScrollInfo {
            ScrollInfo scrollInfo { .dx = dx, .dy = dy };
            auto params = ConvertToJSValues(dx, dy);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                return scrollInfo;
            }

            if (!result->IsObject()) {
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

void JSScroll::JSBind(BindingTarget globalObj)
{
    JSClass<JSScroll>::Declare("Scroll");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSScroll>::StaticMethod("create", &JSScroll::Create, opt);
    JSClass<JSScroll>::StaticMethod("scrollable", &JSScroll::SetScrollable, opt);
    JSClass<JSScroll>::StaticMethod("onScrollBegin", &JSScroll::OnScrollBeginCallback, opt);
    JSClass<JSScroll>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSScroll>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSScroll>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSScroll>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSScroll>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSScroll>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSScroll>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSScroll>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
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
    JSClass<JSScroll>::StaticMethod("enablePaging", &JSScroll::SetEnablePaging);
    JSClass<JSScroll>::StaticMethod("clip", &JSScrollable::JsClip);
    JSClass<JSScroll>::StaticMethod("initialOffset", &JSScroll::SetInitialOffset);
    JSClass<JSScroll>::InheritAndBind<JSScrollableBase>(globalObj);
}

void JSScroll::SetScrollBar(const JSCallbackInfo& args)
{
    if (args.Length() < 1) {
        return;
    }
    int32_t displayMode;
    if (args[0]->IsNull() || args[0]->IsUndefined() || !ParseJsInt32(args[0], displayMode)) {
        displayMode = static_cast<int32_t>(DisplayMode::AUTO);
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
        return;
    }
    if (!ParseJsDimensionVp(args[0], scrollBarWidth) || args[0]->IsNull() || args[0]->IsUndefined() ||
        (args[0]->IsString() && args[0]->ToString().empty()) || LessNotEqual(scrollBarWidth.Value(), 0.0) ||
        scrollBarWidth.Unit() == DimensionUnit::PERCENT) {
        scrollBarWidth = theme->GetNormalWidth();
    }
    ScrollModel::GetInstance()->SetScrollBarWidth(scrollBarWidth);
}

void JSScroll::SetScrollBarColor(const JSCallbackInfo& args)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(theme);
    Color color(theme->GetForegroundColor());
    JSViewAbstract::ParseJsColor(args[0], color);
    ScrollModel::GetInstance()->SetScrollBarColor(color);
}

void JSScroll::SetEdgeEffect(const JSCallbackInfo& args)
{
    auto edgeEffect = EdgeEffect::NONE;
    auto effectEdge = EffectEdge::ALL;
    if (args.Length() > 0) {
        edgeEffect = JSScrollable::ParseEdgeEffect(args[0], EdgeEffect::NONE);
    }
    auto alwaysEnabled = true;
    if (args.Length() > 1) {
        alwaysEnabled = JSScrollable::ParseAlwaysEnable(args[1], true);
        effectEdge = JSScrollable::ParseEffectEdge(args[1]);
    }
    ScrollModel::GetInstance()->SetEdgeEffect(edgeEffect, alwaysEnabled, effectEdge);
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
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    int32_t froward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollForward"), froward);
    if (froward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        froward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
        froward = 0;
    }
    int32_t backward = 0;
    JSViewAbstract::ParseJsInt32(obj->GetProperty("scrollBackward"), backward);
    if (backward < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
        backward > static_cast<int32_t>(NestedScrollMode::PARALLEL)) {
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
        friction = -1.0;
    }
    ScrollModel::GetInstance()->SetFriction(friction);
}

void JSScroll::SetScrollSnap(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
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

void JSScroll::SetEnablePaging(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsBoolean()) {
        return;
    }
    ScrollModel::GetInstance()->SetEnablePaging(args[0]->ToBoolean());
}

void JSScroll::SetInitialOffset(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    CalcDimension xOffset;
    ParseJsDimensionVp(obj->GetProperty("xOffset"), xOffset);
    CalcDimension yOffset;
    ParseJsDimensionVp(obj->GetProperty("yOffset"), yOffset);
    ScrollModel::GetInstance()->SetInitialOffset(NG::OffsetT(xOffset, yOffset));
}
} // namespace OHOS::Ace::Framework
