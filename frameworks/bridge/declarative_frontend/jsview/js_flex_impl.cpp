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

#include "frameworks/bridge/declarative_frontend/jsview/js_flex_impl.h"

#include "core/components_ng/pattern/flex/flex_model.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/flex_model_impl.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"
#include "frameworks/core/components_ng/pattern/flex/flex_model_ng.h"

namespace OHOS::Ace::Framework {

void JSFlexImpl::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGD("No input args, use default row setting");
        FlexModel::GetInstance()->CreateFlexRow();
        return;
    }
    if (!info[0]->IsObject()) {
        LOGD("arg is not a object, use default row setting");
        FlexModel::GetInstance()->CreateFlexRow();
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> wrapVal = obj->GetProperty("wrap");
    if (wrapVal->IsNumber()) {
        auto wrapNum = wrapVal->ToNumber<int32_t>();
        if (wrapNum == 0) {
            CreateFlexComponent(info);
        } else {
            CreateWrapComponent(info, wrapNum);
        }
    } else {
        CreateFlexComponent(info);
    }
}

void JSFlexImpl::CreateFlexComponent(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        FlexModel::GetInstance()->CreateFlexRow();
        return;
    }
    if (!info[0]->IsObject()) {
        FlexModel::GetInstance()->CreateFlexRow();
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> directionVal = obj->GetProperty("direction");
    JSRef<JSVal> justifyVal = obj->GetProperty("justifyContent");
    JSRef<JSVal> alignItemVal = obj->GetProperty("alignItems");
    FlexModel::GetInstance()->CreateFlexRow();
    if (directionVal->IsNumber()) {
        auto direction = directionVal->ToNumber<int32_t>();
        if (direction >= 0 && direction <= DIRECTION_MAX_VALUE) {
            FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(direction));
        }
    }
    if (justifyVal->IsNumber()) {
        auto mainAlign = justifyVal->ToNumber<int32_t>();
        if (mainAlign >= 0 && mainAlign <= MAIN_ALIGN_MAX_VALUE) {
            FlexModel::GetInstance()->SetMainAxisAlign(static_cast<FlexAlign>(mainAlign));
        }
    } else if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9) {
        FlexModel::GetInstance()->SetMainAxisAlign(FlexAlign::FLEX_START);
    }
    if (alignItemVal->IsNumber()) {
        auto crossAlign = alignItemVal->ToNumber<int32_t>();
        if (crossAlign >= 0 && crossAlign <= CROSS_ALIGN_MAX_VALUE) {
            FlexModel::GetInstance()->SetCrossAxisAlign(static_cast<FlexAlign>(crossAlign));
        }
    } else if (PipelineBase::GetCurrentContext() && PipelineBase::GetCurrentContext()->GetMinPlatformVersion() > 9) {
        FlexModel::GetInstance()->SetCrossAxisAlign(FlexAlign::FLEX_START);
    }
}

void JSFlexImpl::CreateWrapComponent(const JSCallbackInfo& info, int32_t wrapVal)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> directionVal = obj->GetProperty("direction");
    JSRef<JSVal> justifyVal = obj->GetProperty("justifyContent");
    JSRef<JSVal> alignItemVal = obj->GetProperty("alignItems");
    JSRef<JSVal> alignContentVal = obj->GetProperty("alignContent");
    FlexModel::GetInstance()->CreateWrap();
    if (directionVal->IsNumber()) {
        auto direction = directionVal->ToNumber<int32_t>();
        if (direction >= 0 && direction <= DIRECTION_MAX_VALUE) {
            FlexModel::GetInstance()->SetDirection(static_cast<FlexDirection>(direction));
            // WrapReverse means wrapVal = 2. Wrap means wrapVal = 1.
            if (direction <= 1) {
                direction += 2 * (wrapVal - 1);
            } else {
                direction -= 2 * (wrapVal - 1);
            }
            FlexModel::GetInstance()->SetWrapDirection(static_cast<WrapDirection>(direction));
        }
    } else {
        // No direction set case: wrapVal == 2 means FlexWrap.WrapReverse.
        WrapDirection wrapDirection = wrapVal == 2 ? WrapDirection::HORIZONTAL_REVERSE : WrapDirection::HORIZONTAL;
        FlexModel::GetInstance()->SetWrapDirection(wrapDirection);
    }
    if (justifyVal->IsNumber()) {
        auto mainAlign = justifyVal->ToNumber<int32_t>();
        if (mainAlign >= 0 && mainAlign <= MAIN_ALIGN_MAX_VALUE) {
            FlexModel::GetInstance()->SetWrapMainAlignment(WRAP_TABLE[mainAlign]);
        }
    }
    if (alignItemVal->IsNumber()) {
        auto crossAlign = alignItemVal->ToNumber<int32_t>();
        if (crossAlign >= 0 && crossAlign <= CROSS_ALIGN_MAX_VALUE) {
            FlexModel::GetInstance()->SetWrapCrossAlignment(WRAP_TABLE[crossAlign]);
        }
    }
    if (alignContentVal->IsNumber()) {
        auto alignContent = alignContentVal->ToNumber<int32_t>();
        if (alignContent >= 0 && alignContent <= MAIN_ALIGN_MAX_VALUE) {
            FlexModel::GetInstance()->SetWrapAlignment(WRAP_TABLE[alignContent]);
        }
    }
}

void JSFlexImpl::JsFlexWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    JsFlexWidth(info[0]);
}

void JSFlexImpl::JsFlexWidth(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsWidth(jsValue);
    FlexModel::GetInstance()->SetFlexWidth();
}

void JSFlexImpl::JsFlexHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    JsFlexHeight(info[0]);
}

void JSFlexImpl::JsFlexHeight(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsHeight(jsValue);
    FlexModel::GetInstance()->SetFlexHeight();
}

void JSFlexImpl::JsFlexSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JsFlexWidth(sizeObj->GetProperty("width"));
    JsFlexHeight(sizeObj->GetProperty("height"));
}

void JSFlexImpl::JSBind(BindingTarget globalObj)
{
    JSClass<JSFlexImpl>::Declare("Flex");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSFlexImpl>::StaticMethod("create", &JSFlexImpl::Create, opt);

    JSClass<JSFlexImpl>::StaticMethod("width", &JSFlexImpl::JsFlexWidth);
    JSClass<JSFlexImpl>::StaticMethod("height", &JSFlexImpl::JsFlexHeight);
    JSClass<JSFlexImpl>::StaticMethod("size", &JSFlexImpl::JsFlexSize);

    JSClass<JSFlexImpl>::StaticMethod("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSFlexImpl>::StaticMethod("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSFlexImpl>::StaticMethod("justifyContent", &JSFlex::SetJustifyContent, opt);
    JSClass<JSFlexImpl>::StaticMethod("alignItems", &JSFlex::SetAlignItems, opt);
    JSClass<JSFlexImpl>::StaticMethod("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSFlexImpl>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSFlexImpl>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSFlexImpl>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSFlexImpl>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSFlexImpl>::StaticMethod("onPan", &JSInteractableView::JsOnPan);
    JSClass<JSFlexImpl>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSFlexImpl>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSFlexImpl>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSFlexImpl>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
