/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_navdestination.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<NavDestinationModel> NavDestinationModel::instance_ = nullptr;
std::mutex NavDestinationModel::mutex_;

NavDestinationModel* NavDestinationModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        instance_.reset(new NG::NavDestinationModelNG());
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

namespace {

bool ParseCommonTitle(const JSRef<JSVal>& jsValue)
{
    auto jsObj = JSRef<JSObject>::Cast(jsValue);
    bool isCommonTitle = false;
    bool hasSubTitle = false;
    auto subtitle = jsObj->GetProperty("sub");
    if (subtitle->IsString()) {
        NavDestinationModel::GetInstance()->SetSubtitle(subtitle->ToString());
        isCommonTitle = true;
        hasSubTitle = true;
    }
    auto title = jsObj->GetProperty("main");
    if (title->IsString()) {
        NavDestinationModel::GetInstance()->SetTitle(title->ToString(), hasSubTitle);
        isCommonTitle = true;
    }

    return isCommonTitle;
}

} // namespace

void JSNavDestination::Create()
{
    NavDestinationModel::GetInstance()->Create();
}

void JSNavDestination::Create(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 && !info[0]->IsFunction()) {
        NavDestinationModel::GetInstance()->Create();
        return;
    }

    auto builderFunctionJS = info[0];
    auto builderFunc = [context = info.GetExecutionContext(), builder = std::move(builderFunctionJS)]() {
        JAVASCRIPT_EXECUTION_SCOPE(context)
        JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
    };
    NavDestinationModel::GetInstance()->Create(std::move(builderFunc));
}

void JSNavDestination::SetHideTitleBar(bool hide)
{
    NavDestinationModel::GetInstance()->SetHideTitleBar(hide);
}

void JSNavDestination::SetTitle(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (info[0]->IsString()) {
        NavDestinationModel::GetInstance()->SetTitle(info[0]->ToString(), false);
    } else if (info[0]->IsObject()) {
        if (ParseCommonTitle(info[0])) {
            return;
        }

        // CustomBuilder | NavigationCustomTitle
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> builderObject = jsObj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
            ACE_SCORING_EVENT("Navdestination.title.builder");
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavDestinationModel::GetInstance()->SetCustomTitle(customNode);
        }
        JSRef<JSVal> height = jsObj->GetProperty("height");
        if (height->IsNumber()) {
            if (height->ToNumber<int32_t>() == 0 || height->ToNumber<int32_t>() == 1) {
                NavDestinationModel::GetInstance()->SetTitleHeight(height->ToNumber<int32_t>());
                return;
            }
            CalcDimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight) || titleHeight.Value() < 0) {
                return;
            }
            NavDestinationModel::GetInstance()->SetTitleHeight(titleHeight);
            return;
        } else {
            CalcDimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight) || titleHeight.Value() <= 0) {
                return;
            }
            NavDestinationModel::GetInstance()->SetTitleHeight(titleHeight);
        }
    } else {
        LOGE("arg is not [String|Function].");
        NavDestinationModel::GetInstance()->SetTitle("", false);
    }
}

void JSNavDestination::SetOnShown(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }

    auto onShownCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onShown = [execCtx = info.GetExecutionContext(), func = std::move(onShownCallback)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("NavDestination.onShown");
        JSRef<JSVal> params[1];
        params[0] = JSRef<JSVal>::Make(ToJSValue("undefined"));
        func->ExecuteJS(1, params);
    };
    NavDestinationModel::GetInstance()->SetOnShown(std::move(onShown));
    info.ReturnSelf();
}

void JSNavDestination::SetOnHidden(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    auto onHiddenCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onHidden = [execCtx = info.GetExecutionContext(), func = std::move(onHiddenCallback)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("NavDestination.onHidden");
        func->ExecuteJS();
    };
    NavDestinationModel::GetInstance()->SetOnHidden(std::move(onHidden));
    info.ReturnSelf();
}

void JSNavDestination::SetOnBackPressed(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    auto onBackPressedCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onBackPressed = [execCtx = info.GetExecutionContext(), func = std::move(onBackPressedCallback)]() -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("NavDestination.onBackPressed");
        return (func->ExecuteJS())->ToBoolean();
    };
    NavDestinationModel::GetInstance()->SetOnBackPressed(std::move(onBackPressed));
    info.ReturnSelf();
}

void JSNavDestination::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavDestination>::Declare("NavDestination");
    JSClass<JSNavDestination>::StaticMethod("create", &JSNavDestination::Create);
    JSClass<JSNavDestination>::StaticMethod("title", &JSNavDestination::SetTitle);
    JSClass<JSNavDestination>::StaticMethod("hideTitleBar", &JSNavDestination::SetHideTitleBar);
    JSClass<JSNavDestination>::StaticMethod("onShown", &JSNavDestination::SetOnShown);
    JSClass<JSNavDestination>::StaticMethod("onHidden", &JSNavDestination::SetOnHidden);
    JSClass<JSNavDestination>::StaticMethod("onBackPressed", &JSNavDestination::SetOnBackPressed);
    JSClass<JSNavDestination>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNavDestination>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNavDestination>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNavDestination>::StaticMethod("id", &JSViewAbstract::JsId);
    JSClass<JSNavDestination>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework
