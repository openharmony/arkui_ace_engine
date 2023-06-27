/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_ui_extension.h"

#include <functional>
#include <string>

#include "base/log/ace_scoring_log.h"
#include "base/want/want_wrap.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<UIExtensionModel> UIExtensionModel::instance_ = nullptr;
std::mutex UIExtensionModel::mutex_;

UIExtensionModel* UIExtensionModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::UIExtensionModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::UIExtensionModelNG());
            } else {
                return nullptr;
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtension>::Declare("UIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUIExtension>::StaticMethod("create", &JSUIExtension::Create, opt);
    JSClass<JSUIExtension>::StaticMethod("onRelease", &JSUIExtension::OnRelease);
    JSClass<JSUIExtension>::StaticMethod("onResult", &JSUIExtension::OnResult);
    JSClass<JSUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }
    auto wantObj = JSRef<JSObject>::Cast(info[0]);
    RefPtr<OHOS::Ace::WantWrap> want = CreateWantWrapFromNapiValue(wantObj);
    UIExtensionModel::GetInstance()->Create(want);
}

void JSUIExtension::OnRelease(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onRelease = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId](int32_t releaseCode) {
        ContainerScope scope(instanceId);
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("UIExtensionComponent.onRelease");
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(releaseCode));
        func->ExecuteJS(1, &newJSVal);
    };
    UIExtensionModel::GetInstance()->SetOnRelease(std::move(onRelease));
}

void JSUIExtension::OnResult(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto instanceId = ContainerScope::CurrentId();
    auto onResult = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), instanceId]
        (int32_t code, const AAFwk::Want& want) {
            ContainerScope scope(instanceId);
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("UIExtensionComponent.onResult");
            auto engine = EngineHelper::GetCurrentEngine();
            CHECK_NULL_VOID(engine);
            NativeEngine* nativeEngine = engine->GetNativeEngine();
            CHECK_NULL_VOID(nativeEngine);
            auto nativeWant = WantWrap::ConvertToNativeValue(want, nativeEngine);
            auto wantJSVal = JsConverter::ConvertNativeValueToJsVal(nativeWant);
            JSRef<JSVal> jsParams[2] = { JSRef<JSVal>::Make(ToJSValue(code)), wantJSVal };
            func->ExecuteJS(2, jsParams);
        };
    UIExtensionModel::GetInstance()->SetOnResult(std::move(onResult));
}
} // namespace OHOS::Ace::Framework
