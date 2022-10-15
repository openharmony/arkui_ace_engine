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

#include "bridge/declarative_frontend/jsview/js_checkboxgroup.h"

#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/checkboxgroup_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

namespace OHOS::Ace {

std::unique_ptr<CheckBoxGroupModel> CheckBoxGroupModel::instance_ = nullptr;

CheckBoxGroupModel* CheckBoxGroupModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::CheckBoxGroupModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::CheckBoxGroupModelNG());
        } else {
            instance_.reset(new Framework::CheckBoxGroupModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

JSRef<JSVal> CheckboxGroupResultEventToJSValue(const CheckboxGroupResult& eventInfo)
{
    JSRef<JSObject> obj = JSRef<JSObject>::New();
    JSRef<JSArray> nameArr = JSRef<JSArray>::New();
    std::vector<std::string> nameList = eventInfo.GetNameList();
    for (int idx = 0; idx < static_cast<int32_t>(nameList.size()); ++idx) {
        JSRef<JSVal> name = JSRef<JSVal>::Make(ToJSValue(nameList[idx]));
        nameArr->SetValueAt(idx, name);
    }
    obj->SetPropertyObject("name", nameArr);
    obj->SetProperty("status", eventInfo.GetStatus());
    return JSRef<JSVal>::Cast(obj);
}

void JSCheckboxGroup::JSBind(BindingTarget globalObj)
{
    JSClass<JSCheckboxGroup>::Declare("CheckboxGroup");

    JSClass<JSCheckboxGroup>::StaticMethod("create", &JSCheckboxGroup::Create);
    JSClass<JSCheckboxGroup>::StaticMethod("selectAll", &JSCheckboxGroup::SetSelectAll);
    JSClass<JSCheckboxGroup>::StaticMethod("onChange", &JSCheckboxGroup::SetOnChange);
    JSClass<JSCheckboxGroup>::StaticMethod("selectedColor", &JSCheckboxGroup::SelectedColor);
    JSClass<JSCheckboxGroup>::StaticMethod("width", &JSCheckboxGroup::JsWidth);
    JSClass<JSCheckboxGroup>::StaticMethod("height", &JSCheckboxGroup::JsHeight);
    JSClass<JSCheckboxGroup>::StaticMethod("size", &JSCheckboxGroup::JsSize);
    JSClass<JSCheckboxGroup>::StaticMethod("padding", &JSCheckboxGroup::JsPadding);
    JSClass<JSCheckboxGroup>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCheckboxGroup>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCheckboxGroup>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCheckboxGroup>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCheckboxGroup>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCheckboxGroup>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCheckboxGroup>::Inherit<JSViewAbstract>();
    JSClass<JSCheckboxGroup>::Bind<>(globalObj);
}

void JSCheckboxGroup::Create(const JSCallbackInfo& info)
{
    std::optional<std::string> checkboxGroupName;
    if ((info.Length() >= 1) && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto groupName = paramObject->GetProperty("group");
        if (groupName->IsString()) {
            checkboxGroupName = groupName->ToString();
        }
    }

    CheckBoxGroupModel::GetInstance()->Create(checkboxGroupName);
}

void JSCheckboxGroup::SetSelectAll(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsBoolean()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments, arg is not a bool");
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetSelectAll(info[0]->ToBoolean());
}

void JSCheckboxGroup::SetOnChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGI("args not function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<CheckboxGroupResult, 1>>(
        JSRef<JSFunc>::Cast(args[0]), CheckboxGroupResultEventToJSValue);
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info){
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto *eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        func->Execute(*eventInfo);
    };
    CheckBoxGroupModel::GetInstance()->SetOnChange(onChange);
}

void JSCheckboxGroup::JsWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsWidth(info[0]);
}

void JSCheckboxGroup::JsWidth(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetWidth(NG::CalcLength(value));
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetWidth(value);
}

void JSCheckboxGroup::JsHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    JsHeight(info[0]);
}

void JSCheckboxGroup::JsHeight(const JSRef<JSVal>& jsValue)
{
    Dimension value;
    if (!ParseJsDimensionVp(jsValue, value)) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetHeight(NG::CalcLength(value));
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetHeight(value);
}

void JSCheckboxGroup::JsSize(const JSCallbackInfo& info)
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

void JSCheckboxGroup::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSCheckboxGroup::JsPadding(const JSCallbackInfo& info)
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
            CheckBoxGroupModel::GetInstance()->SetPadding(padding);
            return;
        }
    }
    Dimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return;
    }
    NG::PaddingPropertyF padding;
    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    CheckBoxGroupModel::GetInstance()->SetPadding(padding);
}

} // namespace OHOS::Ace::Framework
