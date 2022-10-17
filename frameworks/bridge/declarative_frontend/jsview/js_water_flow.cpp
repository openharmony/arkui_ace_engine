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
    if (args.Length() > 1) {
        LOGW("Arg is wrong, it is supposed to have at most one argument");
        return;
    }

    // create waterflow component
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    auto waterflowComponent = AceType::MakeRefPtr<V2::WaterFlowComponent>(componentChildren);
    CHECK_NULL_VOID(waterflowComponent);

    if (args.Length() == 1) {
        if (!args[0]->IsObject()) {
            LOGE("The arg must be object");
            return;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        auto footerObject = obj->GetProperty("footer");
        if (footerObject->IsFunction()) {
            ScopedViewStackProcessor builderViewStackProcessor;
            auto builderFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSFunc>::Cast(footerObject));
            builderFunc->Execute();
            RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
            waterflowComponent->SetFooterComponent(customComponent);
        }
        auto scroller = obj->GetProperty("scroller");
        if (scroller->IsObject()) {
            auto *jsScroller = JSRef<JSObject>::Cast(scroller)->Unwrap<JSScroller>();
            CHECK_NULL_VOID(jsScroller);
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
    JSClass<JSWaterFlow>::StaticMethod("columnsTemplate", &JSWaterFlow::SetColumnsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("itemConstraintSize", &JSWaterFlow::SetItemConstraintSize, opt);
    JSClass<JSWaterFlow>::StaticMethod("rowsTemplate", &JSWaterFlow::SetRowsTemplate, opt);
    JSClass<JSWaterFlow>::StaticMethod("onReachStart", &JSWaterFlow::ReachStartCallback);
    JSClass<JSWaterFlow>::StaticMethod("onReachEnd", &JSWaterFlow::ReachEndCallback);
    JSClass<JSWaterFlow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSWaterFlow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSWaterFlow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSWaterFlow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSWaterFlow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSWaterFlow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSWaterFlow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSWaterFlow>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);

    JSClass<JSWaterFlow>::Inherit<JSContainerBase>();
    JSClass<JSWaterFlow>::Inherit<JSViewAbstract>();
    JSClass<JSWaterFlow>::Bind<>(globalObj);
}

void JSWaterFlow::SetColumnsGap(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("Arg is wrong, it is supposed to have at least 1 argument");
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
        LOGW("Arg is wrong, it is supposed to have at least 1 argument");
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
            waterflow->SetLayoutDirection(LAYOUT_DIRECTION[value]);
        }
    }
}
void JSWaterFlow::SetColumnsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (waterflow) {
        waterflow->SetColumnsArgs(value);
    }
}

void JSWaterFlow::SetItemConstraintSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGI("waterflow create error, info is invalid");
        return;
    }
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);

    JSRef<JSVal> minWidthValue = sizeObj->GetProperty("minWidth");
    Dimension minWidth;
    if (ParseJsDimensionVp(minWidthValue, minWidth)) {
        waterflow->SetMinWidth(minWidth);
    }

    JSRef<JSVal> maxWidthValue = sizeObj->GetProperty("maxWidth");
    Dimension maxWidth;
    if (ParseJsDimensionVp(maxWidthValue, maxWidth)) {
        waterflow->SetMaxWidth(maxWidth);
    }

    JSRef<JSVal> minHeightValue = sizeObj->GetProperty("minHeight");
    Dimension minHeight;
    if (ParseJsDimensionVp(minHeightValue, minHeight)) {
        waterflow->SetMinHeight(minHeight);
    }

    JSRef<JSVal> maxHeightValue = sizeObj->GetProperty("maxHeight");
    Dimension maxHeight;
    if (ParseJsDimensionVp(maxHeightValue, maxHeight)) {
        waterflow->SetMaxHeight(maxHeight);
    }
}

void JSWaterFlow::SetRowsTemplate(const std::string& value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto waterflow = AceType::DynamicCast<V2::WaterFlowComponent>(component);
    if (waterflow) {
        waterflow->SetRowsArgs(value);
    }
}

void JSWaterFlow::ReachStartCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::WaterFlowComponent::SetOnReachStart, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSWaterFlow::ReachEndCallback(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&V2::WaterFlowComponent::SetOnReachEnd, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}
} // namespace OHOS::Ace::Framework
