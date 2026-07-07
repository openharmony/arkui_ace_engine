/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_swiper_controller_binding.h"

#include <memory>
#include <string>
#include <vector>

#include "base/error/error_code.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t LENGTH_TWO = 2;

struct SwiperControllerAsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
};

napi_value CreateErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(errCode);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

void HandleDeferred(const std::shared_ptr<SwiperControllerAsyncContext>& asyncContext, int32_t errorCode,
    const std::string& message)
{
    auto env = asyncContext->env;
    CHECK_NULL_VOID(env);
    auto deferred = asyncContext->deferred;
    CHECK_NULL_VOID(deferred);

    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value result = nullptr;
    if (errorCode == ERROR_CODE_NO_ERROR) {
        napi_get_null(env, &result);
        napi_resolve_deferred(env, deferred, result);
    } else {
        result = CreateErrorValue(env, errorCode, message);
        napi_reject_deferred(env, deferred, result);
    }
    napi_close_handle_scope(env, scope);
}

void ReturnPromise(const JSCallbackInfo& info, napi_value result)
{
    CHECK_NULL_VOID(result);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    if (!jsPromise->IsObject()) {
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}

const NG::NodeModifier::ArkUICustomSwiperControllerModifier* GetSwiperControllerModifier()
{
    static const NG::NodeModifier::ArkUICustomSwiperControllerModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("Swiper");
        if (module == nullptr) {
            LOGF_ABORT("Can't find swiper dynamic module");
        }
        cachedModifier = reinterpret_cast<const NG::NodeModifier::ArkUICustomSwiperControllerModifier*>(
            module->GetCustomModifier("swiperController"));
    }
    return cachedModifier;
}
} // namespace

void JSSwiperControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiperController>::Declare("SwiperController");
    JSClass<JSSwiperController>::CustomMethod("swipeTo", &JSSwiperControllerBinding::SwipeTo);
    JSClass<JSSwiperController>::CustomMethod("showNext", &JSSwiperControllerBinding::ShowNext);
    JSClass<JSSwiperController>::CustomMethod("showPrevious", &JSSwiperControllerBinding::ShowPrevious);
    JSClass<JSSwiperController>::CustomMethod("changeIndex", &JSSwiperControllerBinding::ChangeIndex);
    JSClass<JSSwiperController>::CustomMethod("finishAnimation", &JSSwiperControllerBinding::FinishAnimation);
    JSClass<JSSwiperController>::CustomMethod("preloadItems", &JSSwiperControllerBinding::PreloadItems);
    JSClass<JSSwiperController>::CustomMethod("startFakeDrag", &JSSwiperControllerBinding::StartFakeDrag);
    JSClass<JSSwiperController>::CustomMethod("fakeDragBy", &JSSwiperControllerBinding::FakeDragBy);
    JSClass<JSSwiperController>::CustomMethod("stopFakeDrag", &JSSwiperControllerBinding::StopFakeDrag);
    JSClass<JSSwiperController>::CustomMethod("isFakeDragging", &JSSwiperControllerBinding::IsFakeDragging);
    JSClass<JSSwiperController>::Bind(
        globalObj, JSSwiperControllerBinding::Constructor, JSSwiperControllerBinding::Destructor);
}

void JSSwiperControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSSwiperController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSSwiperControllerBinding::Destructor(JSSwiperController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSSwiperControllerBinding::SwipeTo(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (args.Length() < 1 || !args[0]->IsNumber()) {
        LOGE("Param is not valid");
        return;
    }
    if (auto* modifier = GetSwiperControllerModifier()) {
        modifier->swipeTo(controller_, args[0]->ToNumber<int32_t>());
    }
}

void JSSwiperControllerBinding::ShowNext(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (auto* modifier = GetSwiperControllerModifier()) {
        modifier->showNext(controller_);
    }
}

void JSSwiperControllerBinding::ShowPrevious(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (auto* modifier = GetSwiperControllerModifier()) {
        modifier->showPrevious(controller_);
    }
}

void JSSwiperControllerBinding::ChangeIndex(const JSCallbackInfo& args)
{
    if (!controller_ || args.Length() < 1 || !args[0]->IsNumber()) {
        return;
    }
    auto* modifier = GetSwiperControllerModifier();
    CHECK_NULL_VOID(modifier);
    int32_t index = args[0]->ToNumber<int32_t>();
    if (args.Length() > 1 && args[1]->IsNumber()) {
        modifier->changeIndexWithMode(controller_, index, args[1]->ToNumber<int32_t>());
        return;
    }
    bool useAnimation = false;
    if (args.Length() > 1 && args[1]->IsBoolean()) {
        useAnimation = args[1]->ToBoolean();
    }
    modifier->changeIndex(controller_, index, useAnimation);
}

void JSSwiperControllerBinding::FinishAnimation(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(controller_);
    auto* modifier = GetSwiperControllerModifier();
    CHECK_NULL_VOID(modifier);

    if (args.Length() > 0 && args[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onFinish = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.finishAnimation");
            PipelineContext::SetCallBackNode(node);
            TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperController finishAnimation callback execute.");
            func->Execute();
        };

        modifier->setFinishCallback(controller_, onFinish);
        modifier->finishAnimation(controller_);
        return;
    }

    modifier->finishAnimation(controller_);
}

void JSSwiperControllerBinding::PreloadItems(const JSCallbackInfo& args)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && args.Length() == 1) {
        NewPreloadItems(args);
        return;
    }

    OldPreloadItems(args);
}

void JSSwiperControllerBinding::OldPreloadItems(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(controller_);
    auto* modifier = GetSwiperControllerModifier();
    CHECK_NULL_VOID(modifier);

    if (args.Length() != LENGTH_TWO || !args[0]->IsArray() || !args[1]->IsFunction()) {
        return;
    }

    auto indexArray = JSRef<JSArray>::Cast(args[0]);
    size_t size = indexArray->Length();
    std::vector<int32_t> indices;
    indices.reserve(size);
    for (size_t i = 0; i < size; i++) {
        int32_t index = -1;
        JSViewAbstract::ParseJsInt32(indexArray->GetValueAt(i), index);
        indices.emplace_back(index);
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[1]));
    auto onPreloadFinish =
        [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](int32_t errorCode, std::string message) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.preloadItems");
            TAG_LOGI(AceLogTag::ACE_SWIPER, "SwiperController preloadItems callback execute.");
            JSRef<JSObject> obj = JSRef<JSObject>::New();
            if (errorCode == ERROR_CODE_PARAM_INVALID) {
                obj->SetProperty<int32_t>("code", errorCode);
            }
            JSRef<JSVal> params[] = { obj };
            func->ExecuteJS(1, params);
        };

    modifier->setPreloadFinishCallback(controller_, onPreloadFinish);
    modifier->preloadItems(controller_, indices.data(), static_cast<int32_t>(indices.size()));
}

void JSSwiperControllerBinding::NewPreloadItems(const JSCallbackInfo& args)
{
    if (!controller_) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    auto* modifier = GetSwiperControllerModifier();
    CHECK_NULL_VOID(modifier);
    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto asyncContext = std::make_shared<SwiperControllerAsyncContext>();
    asyncContext->env = env;
    napi_value promise = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &promise);
    ScopeRAII scopeRaii(env);
    std::vector<int32_t> indices;
    if (args.Length() > 0 && args[0]->IsArray()) {
        auto indexArray = JSRef<JSArray>::Cast(args[0]);
        size_t size = indexArray->Length();
        indices.reserve(size);
        for (size_t i = 0; i < size; i++) {
            int32_t index = -1;
            JSViewAbstract::ParseJsInt32(indexArray->GetValueAt(i), index);
            indices.emplace_back(index);
        }
    }

    auto onPreloadFinish = [asyncContext](int32_t errorCode, std::string message) {
        CHECK_NULL_VOID(asyncContext);
        HandleDeferred(asyncContext, errorCode, message);
    };
    modifier->setPreloadFinishCallback(controller_, onPreloadFinish);
    modifier->preloadItems(controller_, indices.data(), static_cast<int32_t>(indices.size()));
    ReturnPromise(args, promise);
}

void JSSwiperControllerBinding::StartFakeDrag(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool ret = false;
    if (auto* modifier = GetSwiperControllerModifier()) {
        ret = modifier->startFakeDrag(controller_);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(ret)));
}

void JSSwiperControllerBinding::FakeDragBy(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool ret = false;
    if (args[0]->IsNumber()) {
        if (auto* modifier = GetSwiperControllerModifier()) {
            ret = modifier->fakeDragBy(controller_, args[0]->ToNumber<float>());
        }
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(ret)));
}

void JSSwiperControllerBinding::StopFakeDrag(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool ret = false;
    if (auto* modifier = GetSwiperControllerModifier()) {
        ret = modifier->stopFakeDrag(controller_);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(ret)));
}

void JSSwiperControllerBinding::IsFakeDragging(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool ret = false;
    if (auto* modifier = GetSwiperControllerModifier()) {
        ret = modifier->isFakeDragging(controller_);
    }
    args.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(ret)));
}
} // namespace OHOS::Ace::Framework
