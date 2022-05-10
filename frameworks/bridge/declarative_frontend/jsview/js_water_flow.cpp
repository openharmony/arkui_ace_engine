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

#include "frameworks/bridge/declarative_frontend/jsview/js_water_flow.h"

#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_scroller.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_v2/water_flow/water_flow_component.h"

namespace OHOS::Ace::Framework {
namespace {
const std::vector<FlexDirection> LAYOUT_DIRECTION = { FlexDirection::ROW, FlexDirection::COLUMN,
    FlexDirection::ROW_REVERSE, FlexDirection::COLUMN_REVERSE };
} // namespace

void JSWaterFlow::Create(const JSCallbackInfo& args)
{
    LOGI("Create component: WaterFLow");
    if (args.Length() < 1) {
        LOGE("Arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    if (!args[0]->IsObject()) {
        LOGE("Arg is not object");
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    JSRef<JSVal> crossSplice = obj->GetProperty("crossSplice");
    if (!crossSplice->IsNumber()) {
        LOGW("Args is invalid");
        return;
    }

    // create waterflow component
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    auto waterflowComponent =
        AceType::MakeRefPtr<V2::WaterFlowComponent>(componentChildren, crossSplice->ToNumber<int32_t>());

    // mainLength
    JSRef<JSVal> jsMainLength = obj->GetProperty("mainLength");
    Dimension mainLength;
    if (ParseJsDimensionVp(jsMainLength, mainLength)) {
        waterflowComponent->SetMainLength(mainLength);
    } else {
        LOGW("The parameter of mainLength not exists.");
    }

    // scroller
    if (args.Length() > 1 && args[1]->IsObject()) {
        JSScroller* jsScroller = JSRef<JSObject>::Cast(args[1])->Unwrap<JSScroller>();
        if (jsScroller) {
            auto positionController = AceType::MakeRefPtr<V2::WaterFlowPositionController>();
            jsScroller->SetController(positionController);
            waterflowComponent->SetController(positionController);

            // Init scroll bar proxy.
            auto proxy = jsScroller->GetScrollBarProxy();
            if (!proxy) {
                proxy = AceType::MakeRefPtr<ScrollBarProxy>();
                jsScroller->SetScrollBarProxy(proxy);
            }
            waterflowComponent->SetScrollBarProxy(proxy);
        }
    } else {
        LOGW("The parameter of scroller not exists.");
    }

    ViewStackProcessor::GetInstance()->Push(waterflowComponent);
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
    JSClass<JSWaterFlow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWaterFlow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);

    JSClass<JSWaterFlow>::Inherit<JSContainerBase>();
    JSClass<JSWaterFlow>::Inherit<JSViewAbstract>();
    JSClass<JSWaterFlow>::Bind<>(globalObj);
}

void JSWaterFlow::SetColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("Arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension colGap;
    if (!ParseJsDimensionVp(info[0], colGap)) {
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (waterflow) {
        waterflow->SetColumnsGap(colGap);
    }
}

void JSWaterFlow::SetRowsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("Arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension rowGap;
    if (!ParseJsDimensionVp(info[0], rowGap)) {
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (waterflow) {
        waterflow->SetRowsGap(rowGap);
    }
}

void JSWaterFlow::SetLayoutDirection(int32_t value)
{
    if (value >= 0 && value < static_cast<int32_t>(LAYOUT_DIRECTION.size())) {
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
        if (waterflow) {
            // not support the other layoutDirection except default for now.
            waterflow->SetLayoutDirection(FlexDirection::COLUMN);
        }
    }
}
} // namespace OHOS::Ace::Framework
