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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navrouter/navdestination_view.h"

namespace OHOS::Ace::Framework {

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
        auto builderObject = JSRef<JSObject>::Cast(info[0])->GetProperty("builder");
        if (builderObject->IsFunction()) {
            RefPtr<NG::UINode> customNode;
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            JsFunction jsBuilderFunc(info.This(), JSRef<JSObject>::Cast(builderObject));
            ACE_SCORING_EVENT("NavDestination.title.builder");
            jsBuilderFunc.Execute();
            customNode = NG::ViewStackProcessor::GetInstance()->Finish();
            NG::NavDestinationView::SetCustomTitle(customNode);
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