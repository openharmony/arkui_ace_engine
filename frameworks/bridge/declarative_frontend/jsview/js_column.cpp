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

#include "frameworks/bridge/declarative_frontend/jsview/js_column.h"

#include "base/log/ace_trace.h"
#include "core/components_ng/pattern/linear_layout/column_model.h"
#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/column_model_impl.h"

namespace OHOS::Ace {
ColumnModel* ColumnModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ColumnModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ColumnModelNG instance;
        return &instance;
    } else {
        static Framework::ColumnModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
std::string JSColumn::inspectorTag_ = "";

void JSColumn::Create(const JSCallbackInfo& info)
{
    std::optional<CalcDimension> space;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> spaceVal = obj->GetProperty("space");
        CalcDimension value;
        if (ParseJsDimensionVp(spaceVal, value)) {
            space = value.IsValid() ? value : Dimension();
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            space = Dimension();
        }
    }

    HorizontalAlignDeclaration* declaration = nullptr;
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> useAlign = obj->GetProperty("useAlign");
        if (useAlign->IsObject()) {
            declaration = JSRef<JSObject>::Cast(useAlign)->Unwrap<HorizontalAlignDeclaration>();
        }
    }
    ColumnModel::GetInstance()->Create(space, declaration, inspectorTag_);
}

void JSColumn::CreateWithWrap(const JSCallbackInfo& info)
{
    ColumnModel::GetInstance()->CreateWithWrap();
}

void JSColumn::SetInspectorTag(const std::string& inspectorTag)
{
    inspectorTag_ = inspectorTag;
}

void JSColumn::ClearInspectorTag()
{
    inspectorTag_.clear();
}

void JSColumn::SetAlignItems(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::STRETCH))) {
        ColumnModel::GetInstance()->SetAlignItems(static_cast<FlexAlign>(value));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ColumnModel::GetInstance()->SetAlignItems(FlexAlign::CENTER);
    }
}

void JSColumn::SetJustifyContent(int32_t value)
{
    if ((value == static_cast<int32_t>(FlexAlign::FLEX_START)) ||
        (value == static_cast<int32_t>(FlexAlign::FLEX_END)) || (value == static_cast<int32_t>(FlexAlign::CENTER)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_BETWEEN)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_AROUND)) ||
        (value == static_cast<int32_t>(FlexAlign::SPACE_EVENLY))) {
        ColumnModel::GetInstance()->SetJustifyContent(static_cast<FlexAlign>(value));
    } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        ColumnModel::GetInstance()->SetJustifyContent(FlexAlign::FLEX_START);
    }
}

void JSColumn::SetReverse(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ColumnModel::GetInstance()->SetIsReverse(info[0]->ToBoolean());
    } else {
        ColumnModel::GetInstance()->SetIsReverse(true);
    }
}

void JSColumn::JSBind(BindingTarget globalObj)
{
    JSClass<JSColumn>::Declare("Column");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSColumn>::StaticMethod("create", &JSColumn::Create, opt);
    JSClass<JSColumn>::StaticMethod("createWithWrap", &JSColumn::CreateWithWrap, opt);
    JSClass<JSColumn>::StaticMethod("fillParent", &JSFlex::SetFillParent, opt);
    JSClass<JSColumn>::StaticMethod("wrapContent", &JSFlex::SetWrapContent, opt);
    JSClass<JSColumn>::StaticMethod("justifyContent", &JSColumn::SetJustifyContent, opt);
    JSClass<JSColumn>::StaticMethod("alignItems", &JSColumn::SetAlignItems, opt);
    JSClass<JSColumn>::StaticMethod("reverse", &JSColumn::SetReverse, opt);
    JSClass<JSColumn>::StaticMethod("alignContent", &JSFlex::SetAlignContent, opt);
    JSClass<JSColumn>::StaticMethod("height", &JSFlex::JsHeight, opt);
    JSClass<JSColumn>::StaticMethod("width", &JSFlex::JsWidth, opt);
    JSClass<JSColumn>::StaticMethod("size", &JSFlex::JsSize, opt);
    JSClass<JSColumn>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSColumn>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSColumn>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSColumn>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSColumn>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSColumn>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSColumn>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSColumn>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSColumn>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSColumn>::StaticMethod("onPan", &JSInteractableView::JsOnPan);
    JSClass<JSColumn>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSColumn>::StaticMethod("pointLight", &JSViewAbstract::JsPointLight, opt);
    JSClass<JSColumn>::InheritAndBind<JSContainerBase>(globalObj);

    JSClass<HorizontalAlignDeclaration>::Declare("HorizontalAlignDeclaration");
    JSClass<HorizontalAlignDeclaration>::Bind(
        globalObj, HorizontalAlignDeclaration::ConstructorCallback, HorizontalAlignDeclaration::DestructorCallback);
}

void HorizontalAlignDeclaration::ConstructorCallback(const JSCallbackInfo& args)
{
    auto align = HorizontalAlign::CENTER;
    if (args.Length() > 0 && args[0]->IsNumber()) {
        auto value = args[0]->ToNumber<int32_t>();
        if (value >= static_cast<int32_t>(HorizontalAlign::START) &&
            value <= static_cast<int32_t>(HorizontalAlign::END)) {
            align = static_cast<HorizontalAlign>(value);
        }
    }
    auto obj = new HorizontalAlignDeclaration(align);
    args.SetReturnValue(obj);
}

void HorizontalAlignDeclaration::DestructorCallback(HorizontalAlignDeclaration* obj)
{
    delete obj;
}

} // namespace OHOS::Ace::Framework
