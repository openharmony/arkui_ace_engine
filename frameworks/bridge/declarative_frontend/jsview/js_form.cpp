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

#include "frameworks/bridge/declarative_frontend/jsview/js_form.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/models/form_model_impl.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"

#if !defined(WEARABLE_PRODUCT)
#include "frameworks/core/components/form/form_component.h"
#endif

namespace OHOS::Ace {

std::unique_ptr<FormModel> FormModel::instance_ = nullptr;
std::mutex FormModel::mutex_;

FormModel* FormModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::FormModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::FormModelNG());
            } else {
                instance_.reset(new Framework::FormModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSForm::Create(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }
    auto obj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> id = obj->GetProperty("id");
    JSRef<JSVal> name = obj->GetProperty("name");
    JSRef<JSVal> bundle = obj->GetProperty("bundle");
    JSRef<JSVal> ability = obj->GetProperty("ability");
    JSRef<JSVal> module = obj->GetProperty("module");
    JSRef<JSVal> dimension = obj->GetProperty("dimension");
    JSRef<JSVal> temporary = obj->GetProperty("temporary");
    JSRef<JSVal> wantValue = obj->GetProperty("want");
    JSRef<JSVal> renderingMode = obj->GetProperty("renderingMode");
    JSRef<JSVal> shape = obj->GetProperty("shape");
    RequestFormInfo formInfo;
    if (id->IsString()) {
        if (!StringUtils::IsNumber(id->ToString())) {
            TAG_LOGE(AceLogTag::ACE_FORM, "Invalid form id : %{public}s", id->ToString().c_str());
            return;
        }
        int64_t inputFormId = StringUtils::StringToLongInt(id->ToString().c_str(), -1);
        if (inputFormId == -1) {
            TAG_LOGE(AceLogTag::ACE_FORM, "StringToLongInt failed : %{public}s", id->ToString().c_str());
            return;
        }
        formInfo.id = inputFormId;
    } else if (id->IsNumber()) {
        formInfo.id = id->ToNumber<int64_t>();
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "JSForm Create, info.id: %{public}" PRId64, formInfo.id);
    formInfo.cardName = name->ToString();
    formInfo.bundleName = bundle->ToString();
    formInfo.abilityName = ability->ToString();
    formInfo.moduleName = module->ToString();
    if (!dimension->IsNull() && !dimension->IsEmpty()) {
        formInfo.dimension = dimension->ToNumber<int32_t>();
    }
    formInfo.temporary = temporary->ToBoolean();
    if (!wantValue->IsNull() && wantValue->IsObject()) {
        formInfo.wantWrap = CreateWantWrapFromNapiValue(wantValue);
    }
    if (!renderingMode->IsNull() && !renderingMode->IsEmpty()) {
        formInfo.renderingMode = renderingMode->ToNumber<int32_t>();
    }
    if (!shape->IsNull() && !shape->IsEmpty()) {
        formInfo.shape = shape->ToNumber<int32_t>();
    }
    FormModel::GetInstance()->Create(formInfo);
}

void JSForm::SetSize(const JSCallbackInfo& info)
{
    JSViewAbstract::JsSize(info);

    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }
    Dimension width = 0.0_vp;
    Dimension height = 0.0_vp;

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> widthValue = sizeObj->GetProperty("width");
    if (!widthValue->IsNull() && !widthValue->IsEmpty()) {
        if (widthValue->IsNumber()) {
            width = Dimension(widthValue->ToNumber<double>(), DimensionUnit::VP);
        } else if (widthValue->IsString()) {
            width = StringUtils::StringToDimension(widthValue->ToString(), true);
        }
    }

    JSRef<JSVal> heightValue = sizeObj->GetProperty("height");
    if (!heightValue->IsNull() && !heightValue->IsEmpty()) {
        if (heightValue->IsNumber()) {
            height = Dimension(heightValue->ToNumber<double>(), DimensionUnit::VP);
        } else if (heightValue->IsString()) {
            height = StringUtils::StringToDimension(heightValue->ToString(), true);
        }
    }
    FormModel::GetInstance()->SetSize(width, height);
}

void JSForm::SetDimension(int32_t value)
{
    FormModel::GetInstance()->SetDimension(value);
}

void JSForm::AllowUpdate(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsBoolean()) {
        return;
    }

    auto allowUpdate = info[0]->ToBoolean();
    FormModel::GetInstance()->AllowUpdate(allowUpdate);
}

void JSForm::SetVisibility(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsNumber()) {
        return;
    }

    auto type = info[0]->ToNumber<int32_t>();
    FormModel::GetInstance()->SetVisibility(VisibleType(type));
}

void JSForm::SetModuleName(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsString()) {
        return;
    }

    auto moduleName = info[0]->ToString();
    FormModel::GetInstance()->SetModuleName(moduleName);
}

void JSForm::JsOnAcquired(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onAcquired = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onAcquired");
            std::vector<std::string> keys = { "id", "idString", "isLocked" };
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnAcquired(std::move(onAcquired));
    }
}

void JSForm::JsOnError(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onError");
            std::vector<std::string> keys = { "errcode", "msg" };
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnError(std::move(onError));
    }
}

void JSForm::JsOnUninstall(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onUninstall = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onUninstall");
            std::vector<std::string> keys = { "id", "idString", "isLocked" };
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnUninstall(std::move(onUninstall));
    }
}

void JSForm::JsOnRouter(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onRouter = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onRouter");
            std::vector<std::string> keys = { "action" };
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnRouter(std::move(onRouter));
    }
}

void JSForm::JsOnLoad(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onLoad = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onLoad");
            std::vector<std::string> keys;
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnLoad(std::move(onLoad));
    }
}

void JSForm::JsOnUpdate(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onUpdate = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onUpdate");
            std::vector<std::string> keys = { "id", "idString" };
            func->Execute(keys, param);
        };
        FormModel::GetInstance()->SetOnUpdate(std::move(onUpdate));
    }
}

void JSForm::JsObscured(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Obscured reasons undefined");
        return;
    }
    if (!info[0]->IsArray()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "Obscured reasons not Array");
        return;
    }
    auto obscuredArray = JSRef<JSArray>::Cast(info[0]);
    size_t size = obscuredArray->Length();
    std::vector<ObscuredReasons> reasons;
    reasons.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        JSRef<JSVal> reason = obscuredArray->GetValueAt(i);
        if (reason->IsNumber()) {
            reasons.push_back(static_cast<ObscuredReasons>(reason->ToNumber<int32_t>()));
        }
    }
    FormModel::GetInstance()->SetObscured(reasons);
}

void JSForm::JSBind(BindingTarget globalObj)
{
    JSClass<JSForm>::Declare("FormComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSForm>::StaticMethod("create", &JSForm::Create, opt);
    JSClass<JSForm>::StaticMethod("size", &JSForm::SetSize, opt);
    JSClass<JSForm>::StaticMethod("dimension", &JSForm::SetDimension, opt);
    JSClass<JSForm>::StaticMethod("allowUpdate", &JSForm::AllowUpdate, opt);
    JSClass<JSForm>::StaticMethod("visibility", &JSForm::SetVisibility, opt);
    JSClass<JSForm>::StaticMethod("moduleName", &JSForm::SetModuleName, opt);
    JSClass<JSForm>::StaticMethod("clip", &JSViewAbstract::JsClip, opt);
    JSClass<JSForm>::StaticMethod("obscured", &JSForm::JsObscured);

    JSClass<JSForm>::StaticMethod("onAcquired", &JSForm::JsOnAcquired);
    JSClass<JSForm>::StaticMethod("onError", &JSForm::JsOnError);
    JSClass<JSForm>::StaticMethod("onUninstall", &JSForm::JsOnUninstall);
    JSClass<JSForm>::StaticMethod("onRouter", &JSForm::JsOnRouter);
    JSClass<JSForm>::StaticMethod("onLoad", &JSForm::JsOnLoad);
    JSClass<JSForm>::StaticMethod("onUpdate", &JSForm::JsOnUpdate);
    JSClass<JSForm>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSForm>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSForm>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSForm>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSForm>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSForm>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSForm>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSForm>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSForm>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework
