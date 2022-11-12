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

#include "bridge/declarative_frontend/jsview/js_checkbox.h"

#include <optional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/checkbox_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace {

std::unique_ptr<CheckBoxModel> CheckBoxModel::instance_ = nullptr;

CheckBoxModel* CheckBoxModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::CheckBoxModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::CheckBoxModelNG());
        } else {
            instance_.reset(new Framework::CheckBoxModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSCheckbox::Create(const JSCallbackInfo& info)
{
    auto checkboxName = std::optional<std::string>();
    auto checkboxGroup = std::optional<std::string>();
    if ((info.Length() >= 1) && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto name = paramObject->GetProperty("name");
        auto group = paramObject->GetProperty("group");
        if (name->IsString()) {
            checkboxName = name->ToString();
        }
        if (group->IsString()) {
            checkboxGroup = group->ToString();
        }
    }
    CheckBoxModel::GetInstance()->Create(checkboxName, checkboxGroup, V2::CHECK_BOX_ETS_TAG);
}

void JSCheckbox::JSBind(BindingTarget globalObj)
{
    JSClass<JSCheckbox>::Declare("Checkbox");

    JSClass<JSCheckbox>::StaticMethod("create", &JSCheckbox::Create);
    JSClass<JSCheckbox>::StaticMethod("select", &JSCheckbox::SetSelect);
    JSClass<JSCheckbox>::StaticMethod("onChange", &JSCheckbox::SetOnChange);
    JSClass<JSCheckbox>::StaticMethod("selectedColor", &JSCheckbox::SelectedColor);
    JSClass<JSCheckbox>::StaticMethod("width", &JSCheckbox::JsWidth);
    JSClass<JSCheckbox>::StaticMethod("height", &JSCheckbox::JsHeight);
    JSClass<JSCheckbox>::StaticMethod("size", &JSCheckbox::JsSize);
    JSClass<JSCheckbox>::StaticMethod("padding", &JSCheckbox::JsPadding);
    JSClass<JSCheckbox>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCheckbox>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCheckbox>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCheckbox>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCheckbox>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCheckbox>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCheckbox>::Inherit<JSViewAbstract>();
    JSClass<JSCheckbox>::Bind<>(globalObj);
}

void JSCheckbox::SetSelect(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsBoolean()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments, arg is not a bool");
        return;
    }

    CheckBoxModel::GetInstance()->SetSelect(info[0]->ToBoolean());
}

void JSCheckbox::SetOnChange(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](bool select) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("CheckBox.onChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(select));
        func->ExecuteJS(1, &newJSVal);
    };
    CheckBoxModel::GetInstance()->SetOnChange(onChange);
    args.ReturnSelf();
}

void JSCheckbox::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsWidth(info[0]);
}

void JSCheckbox::JsWidth(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetWidth(NG::CalcLength(value));
        return;
    }
    CheckBoxModel::GetInstance()->SetWidth(value);
}

void JSCheckbox::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsHeight(info[0]);
}

void JSCheckbox::JsHeight(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetHeight(NG::CalcLength(value));
        return;
    }
    CheckBoxModel::GetInstance()->SetHeight(value);
}

void JSCheckbox::JsSize(const JSCallbackInfo& info)
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
    JsWidth(sizeObj->GetProperty("width"));
    JsHeight(sizeObj->GetProperty("height"));
}

void JSCheckbox::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        return;
    }

    CheckBoxModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSCheckbox::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    if (!info[0]->IsString() && !info[0]->IsNumber() && !info[0]->IsObject()) {
        LOGE("arg is not a string, number or object.");
        return;
    }

    Dimension value;
    if (!ParseJsDimensionVp(info[0], value)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetPadding(NG::CalcLength(value));
        return;
    }
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return;
        }
        if (argsPtrItem->Contains("top") || argsPtrItem->Contains("bottom") || argsPtrItem->Contains("left") ||
            argsPtrItem->Contains("right")) {
            Dimension topDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension leftDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension rightDimen = Dimension(0.0, DimensionUnit::VP);
            Dimension bottomDimen = Dimension(0.0, DimensionUnit::VP);
            ParseJsonDimensionVp(argsPtrItem->GetValue("top"), topDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("left"), leftDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("right"), rightDimen);
            ParseJsonDimensionVp(argsPtrItem->GetValue("bottom"), bottomDimen);
            if (leftDimen == 0.0_vp) {
                leftDimen = rightDimen;
            }
            if (topDimen == 0.0_vp) {
                topDimen = bottomDimen;
            }
            if (leftDimen == 0.0_vp) {
                leftDimen = topDimen;
            }
            NG::PaddingPropertyF padding;
            padding.left = leftDimen.ConvertToPx();
            padding.right = rightDimen.ConvertToPx();
            padding.top = topDimen.ConvertToPx();
            padding.bottom = bottomDimen.ConvertToPx();
            CheckBoxModel::GetInstance()->SetPadding(padding);
            return;
        }
    }
    Dimension length;
    if (!JSViewAbstract::ParseJsDimensionVp(info[0], length)) {
        return;
    }
    NG::PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    CheckBoxModel::GetInstance()->SetPadding(padding);
}

} // namespace OHOS::Ace::Framework
