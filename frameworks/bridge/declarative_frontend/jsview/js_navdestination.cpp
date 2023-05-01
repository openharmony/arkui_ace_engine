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

#include <vector>

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navrouter/navdestination_view.h"

namespace OHOS::Ace::Framework {

namespace {

bool ParseCommonTitle(const JSRef<JSVal>& jsValue)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return false;
    }

    auto jsObj = JSRef<JSObject>::Cast(jsValue);
    bool isCommonTitle = false;
    bool hasSubTitle = false;
    auto subtitle = jsObj->GetProperty("sub");
    if (subtitle->IsString()) {
        NG::NavDestinationView::SetSubtitle(subtitle->ToString());
        isCommonTitle = true;
        hasSubTitle = true;
    }
    auto title = jsObj->GetProperty("main");
    if (title->IsString()) {
        NG::NavDestinationView::SetTitle(title->ToString(), hasSubTitle);
        isCommonTitle = true;
    }

    return isCommonTitle;
}

} // namespace

void JSNavDestination::Create()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::NavDestinationView::Create();
}

void JSNavDestination::Create(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    CreateForPartialUpdate(info);
}

void JSNavDestination::CreateForPartialUpdate(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 && !info[0]->IsFunction()) {
        NG::NavDestinationView::Create();
        return;
    }

    auto builderFunctionJS = info[0];
    auto builderFunc = [context = info.GetExecutionContext(), builder = std::move(builderFunctionJS)]() {
        JAVASCRIPT_EXECUTION_SCOPE(context)
        JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
    };
    NG::NavDestinationView::Create(std::move(builderFunc));
}

void JSNavDestination::SetHideTitleBar(bool hide)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::NavDestinationView::SetHideTitleBar(hide);
}

void JSNavDestination::SetTitle(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (info[0]->IsString()) {
        NG::NavDestinationView::SetTitle(info[0]->ToString(), false);
    } else if (info[0]->IsObject()) {
        if (ParseCommonTitle(info[0])) {
            return;
        }

        // CustomBuilder | NavigationCustomTitle
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> builderObject = jsObj->GetProperty("builder");
        if (builderObject->IsFunction()) {
            RefPtr<NG::UINode> customNode;
            {
                NG::ScopedViewStackProcessor builderViewStackProcessor;
                JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
                ACE_SCORING_EVENT("Navdestination.title.builder");
                jsBuilderFunc.Execute();
                customNode = NG::ViewStackProcessor::GetInstance()->Finish();
            }
            NG::NavDestinationView::SetCustomTitle(customNode);
        }

        JSRef<JSVal> height = jsObj->GetProperty("height");
        if (height->IsNumber()) {
            if (height->ToNumber<int32_t>() == 0) {
                NG::NavDestinationView::SetTitleHeight(NG::FULL_SINGLE_LINE_TITLEBAR_HEIGHT);
                return;
            }
            if (height->ToNumber<int32_t>() == 1) {
                NG::NavDestinationView::SetTitleHeight(NG::FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
                return;
            }
            Dimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight)) {
                return;
            }
            NG::NavDestinationView::SetTitleHeight(titleHeight);
            return;
        }
    } else {
        LOGE("arg is not [String|Function].");
        NG::NavDestinationView::SetTitle("", false);
    }
}

void JSNavDestination::SetOnShown(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    if (info.Length() < 1) {
        LOGW("The arg is wrong, it is supposed to have at least one argument");
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    if (dataSourceObj_->IsEmpty()) {
        return;
    }
    auto sizeFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("size"));
    if (!sizeFunc->IsEmpty()) {
        return;
    }
    auto index = sizeFunc->Call(JSRef<JSObject>());
    auto getFunc = JSRef<JSFunc>::Cast(dataSourceObj_->GetProperty("getParamByIndex"));
    if (!getFunc->IsEmpty()) {
        return;
    }
    JSRef<JSVal> params[1];
    params[0] = index;
    auto param = getFunc->Call(JSRef<JSObject>(), 1, params);
    params[0] = param;
    auto onShownCallback = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onShown = [execCtx = info.GetExecutionContext(), func = std::move(onShownCallback), params = params]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("NavDestination.onShown");
        func->ExecuteJS(1, params);
    };
    NG::NavDestinationView::SetOnShown(std::move(onShown));
    info.ReturnSelf();
}

void JSNavDestination::SetOnHidden(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
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
    NG::NavDestinationView::SetOnHidden(std::move(onHidden));
    info.ReturnSelf();
}

void JSNavDestination::SetOnBackPressed(const JSCallbackInfo& info)
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
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
    NG::NavDestinationView::SetOnBackPressed(std::move(onBackPressed));
    info.ReturnSelf();
}

void JSNavDestination::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavDestination>::Declare("NavDestination");
    JSClass<JSNavDestination>::StaticMethod("create", &JSNavDestination::Create);
    JSClass<JSNavDestination>::StaticMethod("title", &JSNavDestination::SetTitle);
    JSClass<JSNavDestination>::StaticMethod("hideTitleBar", &JSNavDestination::SetHideTitleBar);
    JSClass<JSNavDestination>::CustomMethod("onShown", &JSNavDestination::SetOnShown);
    JSClass<JSNavDestination>::StaticMethod("onHidden", &JSNavDestination::SetOnHidden);
    JSClass<JSNavDestination>::StaticMethod("onBackPressed", &JSNavDestination::SetOnBackPressed);
    JSClass<JSNavDestination>::Inherit<JSContainerBase>();
    JSClass<JSNavDestination>::Inherit<JSViewAbstract>();
    JSClass<JSNavDestination>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
