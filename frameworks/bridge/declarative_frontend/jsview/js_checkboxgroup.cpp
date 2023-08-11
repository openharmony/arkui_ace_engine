/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
namespace {
constexpr float CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE = -1.0f;
}
std::unique_ptr<CheckBoxGroupModel> CheckBoxGroupModel::instance_ = nullptr;
std::mutex CheckBoxGroupModel::mutex_;

CheckBoxGroupModel* CheckBoxGroupModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
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
    JSClass<JSCheckboxGroup>::StaticMethod("unselectedColor", &JSCheckboxGroup::UnSelectedColor);
    JSClass<JSCheckboxGroup>::StaticMethod("mark", &JSCheckboxGroup::Mark);
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
    JSClass<JSCheckboxGroup>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCheckboxGroup::Create(const JSCallbackInfo& info)
{
    std::optional<std::string> checkboxGroupName = std::make_optional("");
    if ((info.Length() >= 1) && info[0]->IsObject()) {
        auto paramObject = JSRef<JSObject>::Cast(info[0]);
        auto groupName = paramObject->GetProperty("group");
        if (groupName->IsString()) {
            checkboxGroupName = groupName->ToString();
        }
    }

    CheckBoxGroupModel::GetInstance()->Create(checkboxGroupName);
}

void ParseSelectAllObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (eventInfo) {
            if (eventInfo->GetStatus() == 0) {
                auto newJSVal = JSRef<JSVal>::Make(ToJSValue(true));
                func->ExecuteJS(1, &newJSVal);
            } else {
                auto newJSVal = JSRef<JSVal>::Make(ToJSValue(false));
                func->ExecuteJS(1, &newJSVal);
            }
        }
    };
    CheckBoxGroupModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCheckboxGroup::SetSelectAll(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        LOGE("The arg is wrong, it is supposed to have 1 or 2 arguments");
        return;
    }
    bool selectAll = false;
    if (info.Length() > 0 && info[0]->IsBoolean()) {
        selectAll = info[0]->ToBoolean();
    }
    CheckBoxGroupModel::GetInstance()->SetSelectAll(selectAll);
    if (info.Length() > 1 && info[1]->IsFunction()) {
        ParseSelectAllObject(info, info[1]);
    }
}

void JSCheckboxGroup::SetOnChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGI("args not function");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsEventFunction<CheckboxGroupResult, 1>>(
        JSRef<JSFunc>::Cast(args[0]), CheckboxGroupResultEventToJSValue);
    auto onChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultWidth = checkBoxTheme->GetDefaultWidth();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    CalcDimension value(width);
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        value = width;
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultHeight = checkBoxTheme->GetDefaultHeight();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    ParseJsDimensionVp(jsValue, value);
    if (value.IsNegative()) {
        value = height;
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
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(info[0], selectedColor)) {
        selectedColor = theme->GetActiveColor();
    }

    CheckBoxGroupModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSCheckboxGroup::UnSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color unSelectedColor;
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(info[0], unSelectedColor)) {
        unSelectedColor = theme->GetInactiveColor();
    }

    CheckBoxGroupModel::GetInstance()->SetUnSelectedColor(unSelectedColor);
}

void JSCheckboxGroup::Mark(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object.");
        return;
    }

    auto markObj = JSRef<JSObject>::Cast(info[0]);
    auto strokeColorValue = markObj->GetProperty("strokeColor");
    Color strokeColor;
    auto theme = GetTheme<CheckboxTheme>();
    if (!ParseJsColor(strokeColorValue, strokeColor)) {
        strokeColor = theme->GetPointColor();
    }
    CheckBoxGroupModel::GetInstance()->SetCheckMarkColor(strokeColor);

    auto sizeValue = markObj->GetProperty("size");
    CalcDimension size;
    if ((ParseJsDimensionVp(sizeValue, size)) && (size.Unit() != DimensionUnit::PERCENT) &&
        (size.ConvertToVp() >= 0)) {
        CheckBoxGroupModel::GetInstance()->SetCheckMarkSize(size);
    } else {
        CheckBoxGroupModel::GetInstance()->SetCheckMarkSize(Dimension(CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE));
    }
    
    auto strokeWidthValue = markObj->GetProperty("strokeWidth");
    CalcDimension strokeWidth;
    if ((ParseJsDimensionVp(strokeWidthValue, strokeWidth)) && (strokeWidth.Unit() != DimensionUnit::PERCENT) &&
        (strokeWidth.ConvertToVp() >= 0)) {
        CheckBoxGroupModel::GetInstance()->SetCheckMarkWidth(strokeWidth);
    } else {
        CheckBoxGroupModel::GetInstance()->SetCheckMarkWidth(theme->GetCheckStroke());
    }
}

void JSCheckboxGroup::JsPadding(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }
    NG::PaddingPropertyF oldPadding({ 0.0f, 0.0f, 0.0f, 0.0f });
    bool flag = GetOldPadding(info, oldPadding);
    NG::PaddingProperty newPadding = GetNewPadding(info);
    CheckBoxGroupModel::GetInstance()->SetPadding(oldPadding, newPadding, flag);
}

bool JSCheckboxGroup::GetOldPadding(const JSCallbackInfo& info, NG::PaddingPropertyF& padding)
{
    if (info[0]->IsObject()) {
        auto argsPtrItem = JsonUtil::ParseJsonString(info[0]->ToString());
        if (!argsPtrItem || argsPtrItem->IsNull()) {
            LOGE("Js Parse object failed. argsPtr is null. %s", info[0]->ToString().c_str());
            return false;
        }
        if (argsPtrItem->Contains("top") || argsPtrItem->Contains("bottom") || argsPtrItem->Contains("left") ||
            argsPtrItem->Contains("right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
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

            padding.left = leftDimen.ConvertToPx();
            padding.right = rightDimen.ConvertToPx();
            padding.top = topDimen.ConvertToPx();
            padding.bottom = bottomDimen.ConvertToPx();
            return true;
        }
    }

    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        return false;
    }

    padding.left = length.ConvertToPx();
    padding.right = length.ConvertToPx();
    padding.top = length.ConvertToPx();
    padding.bottom = length.ConvertToPx();
    return true;
}

NG::PaddingProperty JSCheckboxGroup::GetNewPadding(const JSCallbackInfo& info)
{
    NG::PaddingProperty padding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    if (info[0]->IsObject()) {
        std::optional<CalcDimension> left;
        std::optional<CalcDimension> right;
        std::optional<CalcDimension> top;
        std::optional<CalcDimension> bottom;
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);

        CalcDimension leftDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("left"), leftDimen)) {
            left = leftDimen;
        }
        CalcDimension rightDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("right"), rightDimen)) {
            right = rightDimen;
        }
        CalcDimension topDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("top"), topDimen)) {
            top = topDimen;
        }
        CalcDimension bottomDimen;
        if (ParseJsDimensionVp(paddingObj->GetProperty("bottom"), bottomDimen)) {
            bottom = bottomDimen;
        }
        if (left.has_value() || right.has_value() || top.has_value() || bottom.has_value()) {
            padding = GetPadding(top, bottom, left, right);
            return padding;
        }
    }
    CalcDimension length;
    if (!ParseJsDimensionVp(info[0], length)) {
        length.Reset();
    }

    padding.SetEdges(NG::CalcLength(length.IsNonNegative() ? length : CalcDimension()));
    return padding;
}

NG::PaddingProperty JSCheckboxGroup::GetPadding(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right)
{
    NG::PaddingProperty padding(
        { NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp) });
    if (left.has_value()) {
        if (left.value().Unit() == DimensionUnit::CALC) {
            padding.left = NG::CalcLength(
                left.value().IsNonNegative() ? left.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.left = NG::CalcLength(left.value().IsNonNegative() ? left.value() : CalcDimension());
        }
    }
    if (right.has_value()) {
        if (right.value().Unit() == DimensionUnit::CALC) {
            padding.right = NG::CalcLength(
                right.value().IsNonNegative() ? right.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.right = NG::CalcLength(right.value().IsNonNegative() ? right.value() : CalcDimension());
        }
    }
    if (top.has_value()) {
        if (top.value().Unit() == DimensionUnit::CALC) {
            padding.top = NG::CalcLength(
                top.value().IsNonNegative() ? top.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.top = NG::CalcLength(top.value().IsNonNegative() ? top.value() : CalcDimension());
        }
    }
    if (bottom.has_value()) {
        if (bottom.value().Unit() == DimensionUnit::CALC) {
            padding.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value().CalcValue() : CalcDimension().CalcValue());
        } else {
            padding.bottom = NG::CalcLength(
                bottom.value().IsNonNegative() ? bottom.value() : CalcDimension());
        }
    }
    return padding;
}
} // namespace OHOS::Ace::Framework
