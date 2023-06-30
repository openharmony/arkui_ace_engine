/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/jsview/js_refresh.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/refresh_model_impl.h"
#include "core/components/refresh/refresh_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_FRICTION = 62;
constexpr int32_t MAX_FRICTION = 100;
} // namespace
std::unique_ptr<RefreshModel> RefreshModel::instance_ = nullptr;
std::mutex RefreshModel::mutex_;

RefreshModel* RefreshModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RefreshModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RefreshModelNG());
            } else {
                instance_.reset(new Framework::RefreshModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void ParseRefreshingObject(const JSCallbackInfo& info, const JSRef<JSObject>& refreshing)
{
    JSRef<JSVal> changeEventVal = refreshing->GetProperty("changeEvent");
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    auto changeEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        if (param != "true" && param != "false") {
            LOGE("param is not equal true or false, invalid.");
            return;
        }
        bool newValue = StringToBool(param);
        ACE_SCORING_EVENT("Refresh.ChangeEvent");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(newValue));
        func->ExecuteJS(1, &newJSVal);
    };
    RefreshModel::GetInstance()->SetChangeEvent(std::move(changeEvent));
}

void JSRefresh::JSBind(BindingTarget globalObj)
{
    JSClass<JSRefresh>::Declare("Refresh");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSRefresh>::StaticMethod("create", &JSRefresh::Create, opt);
    JSClass<JSRefresh>::StaticMethod("pop", &JSRefresh::Pop);
    JSClass<JSRefresh>::StaticMethod("onStateChange", &JSRefresh::OnStateChange);
    JSClass<JSRefresh>::StaticMethod("onRefreshing", &JSRefresh::OnRefreshing);
    JSClass<JSRefresh>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRefresh>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRefresh>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRefresh>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSRefresh::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("refresh create error, info is non-valid");
        return;
    }
    RefPtr<RefreshTheme> theme = GetTheme<RefreshTheme>();
    if (!theme) {
        LOGE("Refresh Theme is null");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto refreshing = paramObject->GetProperty("refreshing");
    auto jsOffset = paramObject->GetProperty("offset");
    auto friction = paramObject->GetProperty("friction");
    RefreshModel::GetInstance()->Create();
    RefreshModel::GetInstance()->SetLoadingDistance(theme->GetLoadingDistance());
    RefreshModel::GetInstance()->SetRefreshDistance(theme->GetRefreshDistance());
    RefreshModel::GetInstance()->SetProgressDistance(theme->GetProgressDistance());
    RefreshModel::GetInstance()->SetProgressDiameter(theme->GetProgressDiameter());
    RefreshModel::GetInstance()->SetMaxDistance(theme->GetMaxDistance());
    RefreshModel::GetInstance()->SetShowTimeDistance(theme->GetShowTimeDistance());
    RefreshModel::GetInstance()->SetTextStyle(theme->GetTextStyle());
    RefreshModel::GetInstance()->SetProgressColor(theme->GetProgressColor());
    RefreshModel::GetInstance()->SetProgressBackgroundColor(theme->GetBackgroundColor());

    if (refreshing->IsBoolean()) {
        RefreshModel::GetInstance()->SetRefreshing(refreshing->ToBoolean());
    } else {
        JSRef<JSObject> refreshingObj = JSRef<JSObject>::Cast(refreshing);
        ParseRefreshingObject(info, refreshingObj);
        RefreshModel::GetInstance()->SetRefreshing(refreshingObj->GetProperty("value")->ToBoolean());
    }
    CalcDimension offset;
    if (ParseJsDimensionVp(jsOffset, offset)) {
        if (LessNotEqual(offset.Value(), 0.0) || offset.Unit() == DimensionUnit::PERCENT) {
            RefreshModel::GetInstance()->SetRefreshDistance(theme->GetRefreshDistance());
        } else {
            RefreshModel::GetInstance()->SetUseOffset(true);
            RefreshModel::GetInstance()->SetIndicatorOffset(offset);
        }
    }
    ParsFrictionData(friction);
    ParseCustomBuilder(info);
}

void JSRefresh::ParseCustomBuilder(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        LOGE("Invalid params");
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto builder = paramObject->GetProperty("builder");
    if (builder->IsFunction()) {
        RefPtr<NG::UINode> customNode;
        {
            NG::ScopedViewStackProcessor builderViewStackProcessor;
            JsFunction Jsfunc(info.This(), JSRef<JSObject>::Cast(builder));
            Jsfunc.Execute();
            customNode = NG::ViewStackProcessor::GetInstance()->Finish();
        }
        RefreshModel::GetInstance()->SetCustomBuilder(customNode);
    }
}

void JSRefresh::Pop()
{
    RefreshModel::GetInstance()->Pop();
}

void JSRefresh::OnStateChange(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGI("refresh onStateChange error, param is non-valid");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onStateChange = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](const int32_t& value) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Refresh.OnStateChange");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(value));
        func->ExecuteJS(1, &newJSVal);
    };
    RefreshModel::GetInstance()->SetOnStateChange(std::move(onStateChange));
}

void JSRefresh::OnRefreshing(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        LOGI("refresh onRefreshing error, param is non-valid");
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    auto onRefreshing = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Refresh.OnRefreshing");
        auto newJSVal = JSRef<JSVal>::Make();
        func->ExecuteJS(1, &newJSVal);
    };
    RefreshModel::GetInstance()->SetOnRefreshing(std::move(onRefreshing));
}

void JSRefresh::ParsFrictionData(const JsiRef<JsiValue>& friction)
{
    int32_t frictionNumber = DEFAULT_FRICTION;
    if (friction->IsString()) {
        frictionNumber = StringUtils::StringToInt(friction->ToString());
        if ((frictionNumber == 0 && friction->ToString() != "0") || frictionNumber < 0 ||
            frictionNumber > MAX_FRICTION) {
            frictionNumber = DEFAULT_FRICTION;
        }
    } else if (friction->IsNumber()) {
        frictionNumber = friction->ToNumber<int32_t>();
        if (frictionNumber < 0 || frictionNumber > MAX_FRICTION) {
            frictionNumber = DEFAULT_FRICTION;
        }
        if (friction->ToNumber<int32_t>() <= 0) {
            RefreshModel::GetInstance()->IsRefresh(true);
        }
    }
    RefreshModel::GetInstance()->SetFriction(frictionNumber);
}
} // namespace OHOS::Ace::Framework
