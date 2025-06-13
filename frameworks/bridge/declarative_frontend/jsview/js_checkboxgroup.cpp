/*
 * Copyright (c) 2021-2025 Huawei Device Co., Ltd.
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
    JSClass<JSCheckboxGroup>::StaticMethod("selectedColor", &JSCheckboxGroup::SelectedColor);
    JSClass<JSCheckboxGroup>::StaticMethod("unselectedColor", &JSCheckboxGroup::UnSelectedColor);
    JSClass<JSCheckboxGroup>::StaticMethod("mark", &JSCheckboxGroup::Mark);
    JSClass<JSCheckboxGroup>::StaticMethod("responseRegion", &JSCheckboxGroup::JsResponseRegion);
    JSClass<JSCheckboxGroup>::StaticMethod("size", &JSCheckboxGroup::JsSize);
    JSClass<JSCheckboxGroup>::StaticMethod("padding", &JSCheckboxGroup::JsPadding);
    JSClass<JSCheckboxGroup>::StaticMethod("checkboxShape", &JSCheckboxGroup::SetCheckboxGroupStyle);
    JSClass<JSCheckboxGroup>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCheckboxGroup>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCheckboxGroup>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCheckboxGroup>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCheckboxGroup>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCheckboxGroup>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCheckboxGroup>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
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

    auto vm = info.GetVm();
    auto jsFunc = JSRef<JSFunc>::Cast(changeEventVal);
    auto func = jsFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto changeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (eventInfo) {
            PipelineContext::SetCallBackNode(node);
            if (eventInfo->GetStatus() == 0) {
                panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, true) };
                func->Call(vm, func.ToLocal(), params, 1);
            } else {
                panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, false) };
                func->Call(vm, func.ToLocal(), params, 1);
            }
        }
    };
    CheckBoxGroupModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSCheckboxGroup::SetSelectAll(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info.Length() > 2) {
        return;
    }
    bool selectAll = false;

    JSRef<JSVal> changeEventVal;
    auto selectedVal = info[0];
    if (selectedVal->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(selectedVal);
        selectedVal = obj->GetProperty("value");
        changeEventVal = obj->GetProperty("$value");
    } else if (info.Length() > 1) {
        changeEventVal = info[1];
    }
    if (selectedVal->IsBoolean()) {
        selectAll = selectedVal->ToBoolean();
    }

    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "checkboxgroup select all %{public}d", selectAll);
    CheckBoxGroupModel::GetInstance()->SetSelectAll(selectAll);
    if (changeEventVal->IsFunction()) {
        ParseSelectAllObject(info, changeEventVal);
    }
}


void JSCheckboxGroup::JsResponseRegion(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsResponseRegion(info);
        return;
    }
    if (info.Length() < 1) {
        return;
    }
    std::vector<DimensionRect> result;
    if (!JSViewAbstract::ParseJsResponseRegionArray(info[0], result)) {
        return;
    }
    CheckBoxGroupModel::GetInstance()->SetResponseRegion(result);
}

void JSCheckboxGroup::JsSize(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        JSViewAbstract::JsWidth(JSVal::Undefined());
        JSViewAbstract::JsHeight(JSVal::Undefined());
        return;
    }
    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSViewAbstract::JsWidth(sizeObj->GetProperty("width"));
    JSViewAbstract::JsHeight(sizeObj->GetProperty("height"));
}

void JSCheckboxGroup::SelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        CheckBoxGroupModel::GetInstance()->ResetSelectedColor();
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetSelectedColor(selectedColor);
}

void JSCheckboxGroup::UnSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color unSelectedColor;
    if (!ParseJsColor(info[0], unSelectedColor)) {
        CheckBoxGroupModel::GetInstance()->ResetUnSelectedColor();
        return;
    }

    CheckBoxGroupModel::GetInstance()->SetUnSelectedColor(unSelectedColor);
}

void JSCheckboxGroup::Mark(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    auto markObj = JSRef<JSObject>::Cast(info[0]);
    auto strokeColorValue = markObj->GetProperty("strokeColor");
    auto theme = GetTheme<CheckboxTheme>();
    Color strokeColor = theme->GetPointColor();
    if (!ParseJsColor(strokeColorValue, strokeColor)) {
        CheckBoxGroupModel::GetInstance()->ResetCheckMarkColor();
    } else {
        CheckBoxGroupModel::GetInstance()->SetCheckMarkColor(strokeColor);
    }
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
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        if (jsObj->HasProperty("top") || jsObj->HasProperty("bottom")
            || jsObj->HasProperty("left") || jsObj->HasProperty("right")) {
            CalcDimension topDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension leftDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension rightDimen = CalcDimension(0.0, DimensionUnit::VP);
            CalcDimension bottomDimen = CalcDimension(0.0, DimensionUnit::VP);
            ParseJsDimensionVp(jsObj->GetProperty("top"), topDimen);
            ParseJsDimensionVp(jsObj->GetProperty("left"), leftDimen);
            ParseJsDimensionVp(jsObj->GetProperty("right"), rightDimen);
            ParseJsDimensionVp(jsObj->GetProperty("bottom"), bottomDimen);
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
    NG::PaddingProperty padding({ NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp),
        NG::CalcLength(0.0_vp), std::nullopt, std::nullopt });
    if (info[0]->IsObject()) {
        JSRef<JSObject> paddingObj = JSRef<JSObject>::Cast(info[0]);
        CommonCalcDimension commonCalcDimension;
        ParseCommonMarginOrPaddingCorner(paddingObj, commonCalcDimension);
        if (commonCalcDimension.left.has_value() || commonCalcDimension.right.has_value() ||
            commonCalcDimension.top.has_value() || commonCalcDimension.bottom.has_value()) {
            padding = GetPadding(commonCalcDimension.top, commonCalcDimension.bottom, commonCalcDimension.left,
                commonCalcDimension.right);
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
    NG::PaddingProperty padding({ NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp), NG::CalcLength(0.0_vp),
        NG::CalcLength(0.0_vp), std::nullopt, std::nullopt });
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

void JSCheckboxGroup::SetCheckboxGroupStyle(int32_t checkBoxGroupStyle)
{
    CheckBoxStyle curCheckBoxGroupStyle = static_cast<CheckBoxStyle>(checkBoxGroupStyle);
    CheckBoxGroupModel::GetInstance()->SetCheckboxGroupStyle(curCheckBoxGroupStyle);
}
} // namespace OHOS::Ace::Framework
