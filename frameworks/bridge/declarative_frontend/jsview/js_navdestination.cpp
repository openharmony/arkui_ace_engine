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

    JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> title = jsObj->GetProperty("main");
    bool isCommonTitle = false;
    if (title->IsString()) {
        NG::NavDestinationView::SetTitle(title->ToString());
        isCommonTitle = true;
    }
    JSRef<JSVal> subtitle = jsObj->GetProperty("sub");
    if (subtitle->IsString()) {
        NG::NavDestinationView::SetSubtitle(subtitle->ToString());
        isCommonTitle = true;
    }
    return isCommonTitle;
}

}

void JSNavDestination::Create()
{
    if (!Container::IsCurrentUseNewPipeline()) {
        return;
    }
    NG::NavDestinationView::Create();
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
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (info[0]->IsString()) {
        NG::NavDestinationView::SetTitle(info[0]->ToString());
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
            }
            if (height->ToNumber<int32_t>() == 1) {
                NG::NavDestinationView::SetTitleHeight(NG::FULL_DOUBLE_LINE_TITLEBAR_HEIGHT);
            }
            Dimension titleHeight;
            if (!JSContainerBase::ParseJsDimensionVp(height, titleHeight)) {
                return;
            }
            NG::NavDestinationView::SetTitleHeight(titleHeight);
        }
    } else {
        LOGE("arg is not [String|Function].");
    }
}

void JSNavDestination::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavDestination>::Declare("NavDestination");
    JSClass<JSNavDestination>::StaticMethod("create", &JSNavDestination::Create);
    JSClass<JSNavDestination>::StaticMethod("title", &JSNavDestination::SetTitle);
    JSClass<JSNavDestination>::StaticMethod("hideTitleBar", &JSNavDestination::SetHideTitleBar);
    JSClass<JSNavDestination>::Inherit<JSContainerBase>();
    JSClass<JSNavDestination>::Inherit<JSViewAbstract>();
    JSClass<JSNavDestination>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework