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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/log/ace_scoring_log.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/form/form_view.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

#if !defined(WEARABLE_PRODUCT)
#include "frameworks/core/components/form/form_component.h"
#endif

namespace OHOS::Ace::Framework {

void JSForm::Create(const JSCallbackInfo& info)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        LOGE("form create fail due to FormComponent construct param is empty or type is not Object");
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

    LOGD("js form create id:%{public}d, name:%{public}s, bundle:%{public}s, ability:%{public}s, module:%{public}s, "
         "temporary:%{public}s",
        id->ToNumber<int32_t>(), name->ToString().c_str(), bundle->ToString().c_str(), ability->ToString().c_str(),
        module->ToString().c_str(), temporary->ToString().c_str());

    RequestFormInfo fomInfo;
    fomInfo.id = id->ToNumber<int32_t>();
    fomInfo.cardName = name->ToString();
    fomInfo.bundleName = bundle->ToString();
    fomInfo.abilityName = ability->ToString();
    fomInfo.moduleName = module->ToString();
    if (!dimension->IsNull() && !dimension->IsEmpty()) {
        fomInfo.dimension = dimension->ToNumber<int32_t>();
    }
    fomInfo.temporary = temporary->ToBoolean();
    if (!wantValue->IsNull() && wantValue->IsObject()) {
        fomInfo.wantWrap = CreateWantWrapFromNapiValue(wantValue);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::FormView::Create(fomInfo);
        return;
    }

    RefPtr<FormComponent> form = AceType::MakeRefPtr<OHOS::Ace::FormComponent>();
    form->SetFormRequestInfo(fomInfo);
    form->SetInspectorTag("FormComponent");
    ViewStackProcessor::GetInstance()->Push(form, false);
    auto boxComponent = ViewStackProcessor::GetInstance()->GetBoxComponent();
    boxComponent->SetMouseAnimationType(HoverAnimationType::SCALE);
}

void JSForm::SetSize(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsSize(info);
        return;
    }

    if (info.Length() == 0 || !info[0]->IsObject()) {
        LOGW("form set size fail due to FormComponent construct param is empty or type is not Object");
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
    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetCardSize(width.IsValid() ? width : 0.0_vp, height.IsValid() ? height : 0.0_vp);
    }
}

void JSForm::SetDimension(int32_t value)
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::FormView::SetDimension(value);
        return;
    }

    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetDimension(value);
    }
}

void JSForm::AllowUpdate(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsBoolean()) {
        LOGE("param is not valid");
        return;
    }

    auto allowUpdate = info[0]->ToBoolean();
    if (Container::IsCurrentUseNewPipeline()) {
        NG::FormView::SetAllowUpdate(allowUpdate);
        return;
    }

    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetAllowUpdate(allowUpdate);
    }
}

void JSForm::SetVisibility(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsNumber()) {
        LOGE("param is not valid");
        return;
    }

    auto type = info[0]->ToNumber<int32_t>();
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewAbstract::SetVisibility(VisibleType(type));
        return;
    }

    auto component = ViewStackProcessor::GetInstance()->GetDisplayComponent();
    auto display = AceType::DynamicCast<DisplayComponent>(component);
    display->SetVisible(VisibleType(type));
}

void JSForm::SetModuleName(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 || !info[0]->IsString()) {
        LOGE("param is not valid");
        return;
    }

    auto moduleName = info[0]->ToString();
    if (Container::IsCurrentUseNewPipeline()) {
        NG::FormView::SetModuleName(moduleName);
        return;
    }

    auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (form) {
        form->SetModuleName(moduleName);
    }
}

void JSForm::JsOnAcquired(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 argument.");
        return;
    }
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onAcquired = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onAcquired");
            std::vector<std::string> keys = { "id" };
            func->Execute(keys, param);
        };
        NG::FormView::SetOnAcquired(std::move(onAcquired));
        return;
    }

    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());

        auto onAppearId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                LOGI("onAcquire send:%{public}s", param.c_str());
                std::vector<std::string> keys = { "id" };
                ACE_SCORING_EVENT("Form.onAcquired");
                func->Execute(keys, param);
            });
        form->SetOnAcquireFormEventId(onAppearId);
    }
}

void JSForm::JsOnError(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onError = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onError");
            std::vector<std::string> keys = { "errcode", "msg" };
            func->Execute(keys, param);
        };
        NG::FormView::SetOnError(std::move(onError));
        return;
    }

    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());

        auto onErrorId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                LOGI("onError send:%{public}s", param.c_str());
                std::vector<std::string> keys = { "errcode", "msg" };
                ACE_SCORING_EVENT("Form.onError");
                func->Execute(keys, param);
            });

        form->SetOnErrorEventId(onErrorId);
    }
}

void JSForm::JsOnUninstall(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onUninstall = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onUninstall");
            std::vector<std::string> keys = { "id" };
            func->Execute(keys, param);
        };
        NG::FormView::SetOnUninstall(std::move(onUninstall));
        return;
    }

    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());

        auto onUninstallId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                LOGI("onUninstall send:%{public}s", param.c_str());
                std::vector<std::string> keys = { "id" };
                ACE_SCORING_EVENT("Form.onUninstall");
                func->Execute(keys, param);
            });

        form->SetOnUninstallEventId(onUninstallId);
    }
}

void JSForm::JsOnRouter(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onRouter = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Form.onRouter");
            std::vector<std::string> keys = { "action" };
            func->Execute(keys, param);
        };
        NG::FormView::SetOnRouter(std::move(onRouter));
        return;
    }

    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto form = AceType::DynamicCast<FormComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());

        auto onRouterId =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                LOGI("onRouter send:%{public}s", param.c_str());
                std::vector<std::string> keys = { "action" };
                ACE_SCORING_EVENT("Form.onRouter");
                func->Execute(keys, param);
            });

        form->SetOnRouterEventId(onRouterId);
    }
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

    JSClass<JSForm>::StaticMethod("onAcquired", &JSForm::JsOnAcquired);
    JSClass<JSForm>::StaticMethod("onError", &JSForm::JsOnError);
    JSClass<JSForm>::StaticMethod("onUninstall", &JSForm::JsOnUninstall);
    JSClass<JSForm>::StaticMethod("onRouter", &JSForm::JsOnRouter);
    JSClass<JSForm>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSForm>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSForm>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSForm>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSForm>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSForm>::StaticMethod("onClick", &JSInteractableView::JsOnClick);

    JSClass<JSForm>::Inherit<JSViewAbstract>();
    JSClass<JSForm>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
