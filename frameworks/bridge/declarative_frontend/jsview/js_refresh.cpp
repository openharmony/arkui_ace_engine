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

#include "frameworks/bridge/declarative_frontend/jsview/js_refresh.h"
#include "core/components/refresh/refresh_component.h"
#include "core/components/refresh/refresh_theme.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace::Framework {

void ParseRefreshingObject(
    const JSCallbackInfo& info, const JSRef<JSObject>& refreshing, const RefPtr<RefreshComponent>& refreshComponent)
{
    JSRef<JSVal> changeEventVal = refreshing->GetProperty("changeEvent");
    if (changeEventVal->IsFunction()) {
        RefPtr<JsFunction> jsFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
        auto eventMarker =
            EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);

                if (param != "true" && param != "false") {
                    LOGE("param is not equal true or false, invalid.");
                    return;
                }

                bool newValue = StringToBool(param);
                JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(newValue));
                func->ExecuteJS(1, &newJSVal);
            });
        refreshComponent->SetChangeEvent(eventMarker);
    }
}

void JSRefresh::JSBind(BindingTarget globalObj)
{
    JSClass<JSRefresh>::Declare("Refresh");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRefresh>::StaticMethod("create", &JSRefresh::Create, opt);
    JSClass<JSRefresh>::StaticMethod("onStateChange", &JSRefresh::OnStateChange);
    JSClass<JSRefresh>::StaticMethod("onRefreshing", &JSRefresh::OnRefreshing);
    JSClass<JSRefresh>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRefresh>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRefresh>::Inherit<JSViewAbstract>();
    JSClass<JSRefresh>::Bind(globalObj);
}

void JSRefresh::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("refresh create error, info is non-valid");
        return;
    }

    RefPtr<RefreshComponent> refreshComponent = AceType::MakeRefPtr<RefreshComponent>();
    RefPtr<RefreshTheme> theme = GetTheme<RefreshTheme>();
    if (!theme) {
        LOGE("Refresh Theme is null");
        return;
    }
    refreshComponent->SetLoadingDistance(theme->GetLoadingDistance());
    refreshComponent->SetRefreshDistance(theme->GetRefreshDistance());
    refreshComponent->SetProgressDistance(theme->GetProgressDistance());
    refreshComponent->SetProgressDiameter(theme->GetProgressDiameter());
    refreshComponent->SetMaxDistance(theme->GetMaxDistance());
    refreshComponent->SetShowTimeDistance(theme->GetShowTimeDistance());
    refreshComponent->SetTextStyle(theme->GetTextStyle());
    refreshComponent->SetProgressColor(theme->GetProgressColor());
    refreshComponent->SetBackgroundColor(theme->GetBackgroundColor());

    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto refreshing = paramObject->GetProperty("refreshing");
    if (refreshing->IsBoolean()) {
        refreshComponent->SetRefreshing(refreshing->ToBoolean());
    } else {
        JSRef<JSObject> refreshingObj = JSRef<JSObject>::Cast(refreshing);
        ParseRefreshingObject(info, refreshingObj, refreshComponent);
        refreshComponent->SetRefreshing(refreshingObj->GetProperty("value")->ToBoolean());
    }

    auto jsOffset = paramObject->GetProperty("offset");
    Dimension offset;
    if (ParseJsDimensionVp(jsOffset, offset)) {
        if (LessOrEqual(offset.Value(), 0.0)) {
            refreshComponent->SetRefreshDistance(theme->GetRefreshDistance());
        } else {
            refreshComponent->SetUseOffset(true);
            refreshComponent->SetIndicatorOffset(offset);
        }
    }

    auto friction = paramObject->GetProperty("friction");
    if (friction->IsNumber()) {
        refreshComponent->SetFriction(friction->ToNumber<int32_t>());
        if (friction->ToNumber<int32_t>() <= 0) {
            refreshComponent->IsRefresh(true);
        }
    }
    ViewStackProcessor::GetInstance()->Push(refreshComponent);
}

void JSRefresh::OnStateChange(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&RefreshComponent::SetOnStateChange, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

void JSRefresh::OnRefreshing(const JSCallbackInfo& args)
{
    if (!JSViewBindEvent(&RefreshComponent::SetOnRefreshing, args)) {
        LOGW("Failed to bind event");
    }
    args.ReturnSelf();
}

} // namespace OHOS::Ace::Framework
