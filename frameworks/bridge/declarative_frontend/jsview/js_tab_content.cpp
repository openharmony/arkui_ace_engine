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

#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"

#include <optional>

#include "base/log/ace_trace.h"
#include "bridge/declarative_frontend/jsview/models/tab_content_model_impl.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TabContentModel> TabContentModel::instance_ = nullptr;

TabContentModel* TabContentModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::TabContentModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::TabContentModelNG());
        } else {
            instance_.reset(new Framework::TabContentModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSTabContent::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUsePartialUpdate()) {
        CreateForPartialUpdate(info);
        return;
    }
    TabContentModel::GetInstance()->Create();
}

void JSTabContent::CreateForPartialUpdate(const JSCallbackInfo& info)
{
    if (info.Length() <= 0 && !info[0]->IsFunction()) {
        TabContentModel::GetInstance()->Create();
        return;
    }

    JSRef<JSVal> builderFunctionJS = info[0];
    auto builderFunc = [context = info.GetExecutionContext(), builder = std::move(builderFunctionJS)]() {
        JAVASCRIPT_EXECUTION_SCOPE(context)
        JSRef<JSFunc>::Cast(builder)->Call(JSRef<JSObject>());
    };
    TabContentModel::GetInstance()->Create(std::move(builderFunc));
}

void JSTabContent::SetTabBar(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        return;
    }

    std::string infoStr;
    if (ParseJsString(info[0], infoStr)) {
        TabContentModel::GetInstance()->SetTabBar(infoStr, std::nullopt, nullptr, true);
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> builderFuncParam = paramObject->GetProperty("builder");
    if (builderFuncParam->IsFunction()) {
        auto tabBarBuilder = AceType::MakeRefPtr<JsFunction>(info.This(), JSRef<JSFunc>::Cast(builderFuncParam));
        auto tabBarBuilderFunc = [execCtx = info.GetExecutionContext(),
                                     tabBarBuilderFunc = std::move(tabBarBuilder)]() {
            if (tabBarBuilderFunc) {
                ACE_SCOPED_TRACE("JSTabContent::Execute TabBar builder");
                JAVASCRIPT_EXECUTION_SCOPE(execCtx);
                tabBarBuilderFunc->ExecuteJS();
            }
        };
        TabContentModel::GetInstance()->SetTabBar(std::nullopt, std::nullopt, std::move(tabBarBuilderFunc), false);
        return;
    }

    JSRef<JSVal> textParam = paramObject->GetProperty("text");
    auto isTextEmpty = textParam->IsEmpty() || textParam->IsUndefined() || textParam->IsNull();
    std::optional<std::string> textOpt = std::nullopt;
    if (!isTextEmpty) {
        std::string text;
        if (ParseJsString(textParam, text)) {
            textOpt = text;
        }
    }

    JSRef<JSVal> iconParam = paramObject->GetProperty("icon");
    auto isIconEmpty = iconParam->IsEmpty() || iconParam->IsUndefined() || iconParam->IsNull();
    std::optional<std::string> iconOpt = std::nullopt;
    if (!isIconEmpty) {
        std::string icon;
        if (ParseJsMedia(iconParam, icon)) {
            iconOpt = icon;
        }
    }
    TabContentModel::GetInstance()->SetTabBar(textOpt, iconOpt, nullptr, false);
}

void JSTabContent::Pop()
{
    TabContentModel::GetInstance()->Pop();
}

void JSTabContent::JSBind(BindingTarget globalObj)
{
    JSClass<JSTabContent>::Declare("TabContent");
    JSClass<JSTabContent>::StaticMethod("create", &JSTabContent::Create);
    JSClass<JSTabContent>::StaticMethod("pop", &JSTabContent::Pop);
    JSClass<JSTabContent>::StaticMethod("tabBar", &JSTabContent::SetTabBar);
    JSClass<JSTabContent>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabContent>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabContent>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabContent>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabContent>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabContent>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabContent>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabContent>::StaticMethod("width", &JSTabContent::SetTabContentWidth);
    JSClass<JSTabContent>::StaticMethod("height", &JSTabContent::SetTabContentHeight);
    JSClass<JSTabContent>::StaticMethod("size", &JSTabContent::SetTabContentSize);
    JSClass<JSTabContent>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabContent>::Inherit<JSContainerBase>();
    JSClass<JSTabContent>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework
