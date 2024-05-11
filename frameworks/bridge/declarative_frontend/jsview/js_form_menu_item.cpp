/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_menu_item.h"

#include "want.h"

#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/jsview/js_form_menu_item.h"
#include "bridge/declarative_frontend/jsview/models/form_model_impl.h"
#include "bridge/declarative_frontend/jsview/models/menu_item_model_impl.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_utils.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {
constexpr int NUM_CALL_0 = 0;
constexpr int NUM_WANT_1 = 1;
constexpr int NUM_ID_2 = 2;
constexpr int NUM_FUN_4 = 4;

void JSFormMenuItem::JSBind(BindingTarget globalObj)
{
    JSClass<JSFormMenuItem>::Declare("FormMenuItem");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSFormMenuItem>::StaticMethod("create", &JSMenuItem::Create, opt);
    JSClass<JSFormMenuItem>::StaticMethod("onClick", &JSFormMenuItem::JsOnClick);
    JSClass<JSFormMenuItem>::StaticMethod("onAppear", &JSFormMenuItem::JsOnAppear);
    JSClass<JSFormMenuItem>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSFormMenuItem>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSFormMenuItem>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSFormMenuItem::RequestPublishFormWithSnapshot(JSRef<JSVal> wantValue, RefPtr<JsFunction> jsCBFunc)
{
    RefPtr<WantWrap> wantWrap = CreateWantWrapFromNapiValue(wantValue);
    if (!wantWrap) {
        TAG_LOGE(AceLogTag::ACE_FORM, "onTap wantWrap is NULL.");
        return;
    }
    int64_t formId = 0;
    AAFwk::Want& want = const_cast<AAFwk::Want&>(wantWrap->GetWant());
    if (!FormModel::GetInstance()->RequestPublishFormWithSnapshot(want, formId)) {
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue(formId));
        jsCBFunc->ExecuteJS(1, params);
    }
}

void JSFormMenuItem::JsOnAppear(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAppear();
        return;
    }

    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnAppear(std::move(onAppear));
    }
}

void JSFormMenuItem::JsOnClick(const JSCallbackInfo& info)
{
    bool retFlag;
    OnClickParameterCheck(info, retFlag);
    if (retFlag) {
        return;
    }

    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[NUM_CALL_0]));
    RefPtr<JsFunction> jsCallBackFunc = nullptr;
    if (!info[ NUM_FUN_4]->IsUndefined() && info[ NUM_FUN_4]->IsFunction()) {
        jsCallBackFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[ NUM_FUN_4]));
    }

    std::string compId;
    JSViewAbstract::ParseJsString(info[NUM_ID_2], compId);
    JSRef<JSVal> wantValue = JSRef<JSVal>::Cast(info[NUM_WANT_1]);
    if (wantValue->IsNull()) {
        TAG_LOGI(AceLogTag::ACE_FORM, "JsOnClick wantValue is null");
        return;
    }
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());

    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode,
        jsCBFunc = std::move(jsCallBackFunc), wantValue] (GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onTap");
        func->Execute(info);
        RequestPublishFormWithSnapshot(wantValue, jsCBFunc);
    };

    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = targetNode,
        jsCBFunc = std::move(jsCallBackFunc), wantValue](const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
        RequestPublishFormWithSnapshot(wantValue, jsCBFunc);
    };
    ViewAbstractModel::GetInstance()->SetOnClick(std::move(onTap), std::move(onClick));
}

void JSFormMenuItem::OnClickParameterCheck(const JSCallbackInfo& info, bool& retFlag)
{
    retFlag = true;
    if (info[NUM_CALL_0]->IsUndefined() || !info[NUM_CALL_0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        TAG_LOGE(AceLogTag::ACE_FORM, "JsOnClick bad parameter info[0]");
        return;
    }

    if (info[NUM_WANT_1]->IsUndefined() || !info[NUM_WANT_1]->IsObject() || info[NUM_ID_2]->IsUndefined() ||
        !info[NUM_ID_2]->IsString()) {
        TAG_LOGE(AceLogTag::ACE_FORM, "JsOnClick bad parameter info[1] and info[2]");
        return;
    }
    retFlag = false;
}
} // namespace OHOS::Ace::Framework