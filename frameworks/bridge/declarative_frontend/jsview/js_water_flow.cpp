/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/water_flow_model_impl.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/waterflow/water_flow_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<WaterFlowModel> WaterFlowModel::instance_ = nullptr;
std::mutex WaterFlowModel::mutex_;

WaterFlowModel* WaterFlowModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::WaterFlowModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::WaterFlowModelNG());
            } else {
                instance_.reset(new Framework::WaterFlowModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
namespace {
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };
} // namespace

void JSWaterFlow::Create(const JSCallbackInfo& args)
{
    if (args.Length() > 1) {
        LOGW("Arg is wrong, it is supposed to have at most one argument");
        return;
    }

    WaterFlowModel::GetInstance()->Create();

    if (args.Length() == 1) {
        if (!args[0]->IsObject()) {
            LOGE("The arg must be object");
            return;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto footerObject = obj->GetProperty("footer");
        if (footerObject->IsFunction()) {
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerObject));
            auto footerAction = [builderFunc]() { builderFunc->Execute(); };
            WaterFlowModel::GetInstance()->SetFooter(footerAction);
        }
        auto scroller = obj->GetProperty("scroller");
        if (scroller->IsObject()) {
            auto* jsScroller = JSRef<JSObject>::Cast(scroller)->Unwrap<JSScroller>();
            CHECK_NULL_VOID(jsScroller);
            auto positionController = WaterFlowModel::GetInstance()->CreateScrollController();
            jsScroller->SetController(positionController);

            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                proxy = WaterFlowModel::GetInstance()->CreateScrollBarProxy();
                jsScroller->SetScrollBarProxy(proxy);
            }
            WaterFlowModel::GetInstance()->SetScroller(positionController, proxy);
        }
    }
}

void JSWaterFlow::JSBind(BindingTarget globalObj)
{
    LOGD("JSWaterFlow:JSBind");
    JSClass<JSWaterFlow>::Declare("WaterFlow");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSWaterFlow>::StaticMethod("create", &JSWaterFlow::Create, opt);
    JSClass<JSWaterFlow>::StaticMethod("columnsGap", &JSWaterFlow::SetColumnsGap, opt);
    JSClass<JSWaterFlow>::StaticMethod("rowsGap", &JSWaterFlow::SetRowsGap, opt);
    JSClass<JSWaterFlow>::StaticMethod("layoutDirection", &JSWaterFlow::SetLayoutDirection, opt);
    JSClass<JSWaterFlow>::StaticMethod("columnsTemplate", &JSWaterFlow::SetColumnsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("itemConstraintSize", &JSWaterFlow::SetItemConstraintSize, opt);
    JSClass<JSWaterFlow>::StaticMethod("rowsTemplate", &JSWaterFlow::SetRowsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("nestedScroll", &JSWaterFlow::SetNestedScroll);
    JSClass<JSWaterFlow>::StaticMethod("onReachStart", &JSWaterFlow::ReachStartCallback);
    JSClass<JSWaterFlow>::StaticMethod("onReachEnd", &JSWaterFlow::ReachEndCallback);
    JSClass<JSWaterFlow>::StaticMethod("onScrollFrameBegin", &JSWaterFlow::ScrollFrameBeginCallback);
    JSClass<JSWaterFlow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSWaterFlow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSWaterFlow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSWaterFlow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSWaterFlow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSWaterFlow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWaterFlow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWaterFlow>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSWaterFlow>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSWaterFlow::SetColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("Arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension colGap;
    if (!ParseJsDimensionVp(info[0], colGap) || colGap.Value() < 0) {
        colGap.SetValue(0.0);
    }
    WaterFlowModel::GetInstance()->SetColumnsGap(colGap);
}

void JSWaterFlow::SetRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("Arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    CalcDimension rowGap;
    if (!ParseJsDimensionVp(info[0], rowGap) || rowGap.Value() < 0) {
        rowGap.SetValue(0.0);
    }
    WaterFlowModel::GetInstance()->SetRowsGap(rowGap);
}

void JSWaterFlow::SetLayoutDirection(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }
    auto value = static_cast<int32_t>(FlexDirection::COLUMN);
    auto jsValue = info[0];
    if (!jsValue->IsUndefined()) {
        ParseJsInteger<int32_t>(jsValue, value);
    }
    if (value >= 0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        WaterFlowModel::GetInstance()->SetLayoutDirection(LAYOUT_DIRECTION[value]);
    } else {
        WaterFlowModel::GetInstance()->SetLayoutDirection(FlexDirection::COLUMN);
    }
}

void JSWaterFlow::SetColumnsTemplate(const std::string& value)
{
    WaterFlowModel::GetInstance()->SetColumnsTemplate(value);
}

void JSWaterFlow::SetItemConstraintSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("waterflow create error, info is invalid");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    CalcDimension minWidth;
    if (ParseJsDimensionVp(minWidthValue, minWidth)) {
        WaterFlowModel::GetInstance()->SetItemMinWidth(minWidth);
    }

    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    CalcDimension maxWidth;
    if (ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        WaterFlowModel::GetInstance()->SetItemMaxWidth(maxWidth);
    }

    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    CalcDimension minHeight;
    if (ParseJsDimensionVp(minHeightValue, minHeight)) {
        WaterFlowModel::GetInstance()->SetItemMinHeight(minHeight);
    }

    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    CalcDimension maxHeight;
    if (ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        WaterFlowModel::GetInstance()->SetItemMaxHeight(maxHeight);
    }
}

void JSWaterFlow::SetRowsTemplate(const std::string& value)
{
    WaterFlowModel::GetInstance()->SetRowsTemplate(value);
}

void JSWaterFlow::SetNestedScroll(const JSCallbackInfo& args)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsObject()) {
        WaterFlowModel::GetInstance()->SetNestedScroll(nestedOpt);
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
    WaterFlowModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSWaterFlow::ReachStartCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachStart = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        WaterFlowModel::GetInstance()->SetOnReachStart(std::move(onReachStart));
    }
    args.ReturnSelf();
}

void JSWaterFlow::ReachEndCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onReachEnd = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])]() {
            func->Call(JSRef<JSObject>());
            return;
        };
        WaterFlowModel::GetInstance()->SetOnReachEnd(std::move(onReachEnd));
    }
    args.ReturnSelf();
}

void JSWaterFlow::ScrollFrameBeginCallback(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        auto onScrollBegin = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                                 const Dimension& offset, const ScrollState& state) -> ScrollFrameResult {
            ScrollFrameResult scrollRes { .offset = offset };
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, scrollRes);
            auto params = ConvertToJSValues(offset, state);
            auto result = func->Call(JSRef<JSObject>(), params.size(), params.data());
            if (result.IsEmpty()) {
                LOGE("Error calling onScrollFrameBegin, result is empty.");
                return scrollRes;
            }

            if (!result->IsObject()) {
                LOGE("Error calling onScrollFrameBegin, result is not object.");
                return scrollRes;
            }

            auto resObj = JSRef<JSObject>::Cast(result);
            auto dxRemainValue = resObj->GetProperty("offsetRemain");
            if (dxRemainValue->IsNumber()) {
                scrollRes.offset = Dimension(dxRemainValue->ToNumber<float>(), DimensionUnit::VP);
            }
            return scrollRes;
        };
        WaterFlowModel::GetInstance()->SetOnScrollFrameBegin(std::move(onScrollBegin));
    }
}
} // namespace OHOS::Ace::Framework
