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

#include "frameworks/bridge/declarative_frontend/jsview/js_row.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/linear_layout/row_model.h"
#include "core/components_ng/pattern/linear_layout/row_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/row_model_impl.h"

namespace OHOS::Ace {
RowModel* RowModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::RowModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::RowModelNG instance;
        return &instance;
    } else {
        static Framework::RowModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSRow::Create(const JSCallbackInfo& info)
{
    std::optional<CalcDimension> space;
    RefPtr<ResourceObject> spaceResObj;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> spaceVal = obj->GetProperty("space");
        CalcDimension value;
        if (ParseJsDimensionVp(spaceVal, value, spaceResObj)) {
            space = value;
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            space = Dimension();
        }
    }
    VerticalAlignDeclaration* declaration = nullptr;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> useAlign = obj->GetProperty("useAlign");
        if (useAlign->IsObject()) {
            declaration = JSRef<JSObject>::Cast(useAlign)->Unwrap<VerticalAlignDeclaration>();
        }
    }

    if (SystemProperties::ConfigChangePerform() && spaceResObj) {
        RowModel::GetInstance()->Create(spaceResObj, declaration, "");
    } else {
        RowModel::GetInstance()->Create(space, declaration, "");
    }
}

void JSRow::CreateWithWrap(const JSCallbackInfo& info)
{
    RowModel::GetInstance()->CreateWithWrap();
}

void JSRow::SetAlignItems(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
        RowModel::GetInstance()->SetAlignItems(static_cast<FlexAlign>(value));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        RowModel::GetInstance()->SetAlignItems(FlexAlign::CENTER);
        // FIXME: we have a design issue here, setters return void, can not signal error to JS
    }
}

void JSRow::SetJustifyContent(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
        RowModel::GetInstance()->SetJustifyContent(static_cast<FlexAlign>(value));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        RowModel::GetInstance()->SetJustifyContent(FlexAlign::FLEX_START);
    }
}

void JSRow::SetReverse(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        RowModel::GetInstance()->SetIsReverse(info[0]->ToBoolean());
    } else {
        RowModel::GetInstance()->SetIsReverse(true);
    }
}

void JSRow::JSBind(BindingTarget globalObj)
{
    JSClass<JSRow>::Declare("Row");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRow>::StaticMethod("create", &JSRow::Create, opt);
    JSClass<JSRow>::StaticMethod("createWithWrap", &JSRow::CreateWithWrap, opt);
    JSClass<JSRow>::StaticMethod("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSRow>::StaticMethod("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSRow>::StaticMethod("justifyContent", &JSRow::SetJustifyContent, opt);
    JSClass<JSRow>::StaticMethod("alignItems", &JSRow::SetAlignItems, opt);
    JSClass<JSRow>::StaticMethod("reverse", &JSRow::SetReverse, opt);
    JSClass<JSRow>::StaticMethod("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSRow>::StaticMethod("height", &JSFlex::JsHeight, opt);
    JSClass<JSRow>::StaticMethod("width", &JSFlex::JsWidth, opt);
    JSClass<JSRow>::StaticMethod("size", &JSFlex::JsSize, opt);
    JSClass<JSRow>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRow>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSRow>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSRow>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSRow>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSRow>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRow>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRow>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRow>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRow>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSRow>::StaticMethod("pointLight", &JSViewAbstract::JsPointLight, opt);
    JSClass<JSRow>::InheritAndBind<JSContainerBase>(globalObj);

    JSClass<VerticalAlignDeclaration>::Declare("VerticalAlignDeclaration");
    JSClass<VerticalAlignDeclaration>::Bind(
        globalObj, VerticalAlignDeclaration::ConstructorCallback, VerticalAlignDeclaration::DestructorCallback);
}

void VerticalAlignDeclaration::ConstructorCallback(const JSCallbackInfo& args)
{
    auto align = VerticalAlign::CENTER;
    if (args.Length() > 0 && args[0]->IsNumber()) {
        auto value = args[0]->ToNumber<int32_t>();
        if (value >= static_cast<int32_t>(VerticalAlign::TOP) && value <= static_cast<int32_t>(VerticalAlign::BOTTOM)) {
            align = static_cast<VerticalAlign>(value);
        }
    }
    auto obj = new VerticalAlignDeclaration(align);
    args.SetReturnValue(obj);
}

void VerticalAlignDeclaration::DestructorCallback(VerticalAlignDeclaration* obj)
{
    delete obj;
}

} // namespace OHOS::Ace::Framework
