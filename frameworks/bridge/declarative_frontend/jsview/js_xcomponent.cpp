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

#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "bridge/declarative_frontend/jsview/models/xcomponent_model_impl.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace {
namespace {
XComponentType ConvertToXComponentType(const std::string& type)
{
    if (type == "surface") {
        return XComponentType::SURFACE;
    }
    if (type == "component") {
        return XComponentType::COMPONENT;
    }
    return XComponentType::SURFACE;
}
} // namespace

std::unique_ptr<XComponentModel> XComponentModel::instance_ = nullptr;
std::mutex XComponentModel::mutex_;

XComponentModel* XComponentModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::XComponentModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::XComponentModelNG());
            } else {
                instance_.reset(new Framework::XComponentModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSXComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponent>::Declare("XComponent");
    JSClass<JSXComponent>::StaticMethod("create", &JSXComponent::Create);
    JSClass<JSXComponent>::StaticMethod("onLoad", &JSXComponent::JsOnLoad);
    JSClass<JSXComponent>::StaticMethod("onDestroy", &JSXComponent::JsOnDestroy);

    JSClass<JSXComponent>::StaticMethod("onAppear", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onDisAppear", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onTouch", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onClick", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onKeyEvent", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onMouse", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onHover", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onFocus", &JSXComponent::OmitEvent);
    JSClass<JSXComponent>::StaticMethod("onBlur", &JSXComponent::OmitEvent);

    JSClass<JSXComponent>::StaticMethod("backgroundColor", &JSXComponent::JsBackgroundColor);
    JSClass<JSXComponent>::StaticMethod("backgroundImage", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backgroundImageSize", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backgroundImagePosition", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("opacity", &JSXComponent::JsOpacity);
    JSClass<JSXComponent>::StaticMethod("blur", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("backdropBlur", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("grayscale", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("brightness", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("saturate", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("contrast", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("invert", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("sepia", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("hueRotate", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("colorBlend", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("sphericalEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("lightUpEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("pixelStretchEffect", &JSXComponent::OmitAttribute);
    JSClass<JSXComponent>::StaticMethod("linearGradientBlur", &JSXComponent::OmitAttribute);

    JSClass<JSXComponent>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSXComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto id = paramObject->GetProperty("id");
    if (!id->IsString()) {
        return;
    }

    auto type = paramObject->GetProperty("type");
    auto libraryname = paramObject->GetProperty("libraryname");
    auto controllerObj = paramObject->GetProperty("controller");
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    if (controllerObj->IsObject()) {
        auto* jsXComponentController = JSRef<JSObject>::Cast(controllerObj)->Unwrap<JSXComponentController>();
        if (jsXComponentController) {
            XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(
                id->ToString(), jsXComponentController);
            xcomponentController = jsXComponentController->GetController();
        }
    }
    XComponentType xcomponentType = XComponentType::SURFACE;
    if (type->IsString()) {
        xcomponentType = ConvertToXComponentType(type->ToString());
    } else if (type->IsNumber()) {
        xcomponentType = static_cast<XComponentType>(type->ToNumber<int32_t>());
    }
    XComponentModel::GetInstance()->Create(
        id->ToString(), xcomponentType, libraryname->ToString(), xcomponentController);

    auto detachCallback = [](const std::string& xcomponentId) {
        XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcomponentId);
        XComponentClient::GetInstance().DeleteFromJsValMapById(xcomponentId);
    };
    XComponentModel::GetInstance()->SetDetachCallback(std::move(detachCallback));

    if (info.Length() > 1 && info[1]->IsString()) {
        auto soPath = info[1]->ToString();
        XComponentModel::GetInstance()->SetSoPath(soPath);
    }
}

void* JSXComponent::Create(const XComponentParams& params)
{
    auto* jsXComponent = new JSXComponent();
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(XComponentModel::GetInstance()->Create(params.elmtId,
        static_cast<float>(params.width), static_cast<float>(params.height), params.xcomponentId,
        static_cast<XComponentType>(params.xcomponentType), params.libraryName, nullptr));
    jsXComponent->SetFrameNode(frameNode);
    auto pattern = frameNode->GetPattern<NG::XComponentPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetRenderType(static_cast<NodeRenderType>(params.renderType));
    pattern->SetExportTextureSurfaceId(params.surfaceId);

    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto taskExecutor = pipelineContext->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, nullptr);
    taskExecutor->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))]() {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto xcPattern = frameNode->GetPattern<NG::XComponentPattern>();
            CHECK_NULL_VOID(xcPattern);
            xcPattern->XComponentSizeInit();
            xcPattern->SetXcomponentInit(true);
        },
        TaskExecutor::TaskType::JS);

    return jsXComponent;
}

bool JSXComponent::ChangeRenderType(int32_t renderType)
{
    auto xcFrameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_RETURN(xcFrameNode, false);
    auto pattern = xcFrameNode->GetPattern<NG::XComponentPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->ChangeRenderType(static_cast<NodeRenderType>(renderType));
}

void JSXComponent::JsOnLoad(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onLoad = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                      const std::string& xcomponentId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onLoad");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "load", xcomponentId };
        func->ExecuteNew(keys, "");
    };
    XComponentModel::GetInstance()->SetOnLoad(std::move(onLoad));
}

void JSXComponent::RegisterOnCreate(const JsiExecutionContext& execCtx, const Local<JSValueRef>& func)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_VOID(frameNode);

    if (!func->IsFunction()) {
        return;
    }

    auto jsFunc = panda::Global<panda::FunctionRef>(execCtx.vm_, Local<panda::FunctionRef>(func));
    auto onLoad = [execCtx, funcRef = std::move(jsFunc), node = AceType::WeakClaim(AceType::RawPtr(frameNode))](
                      const std::string& xcomponentId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponentNode.onCreate");
        PipelineContext::SetCallBackNode(node);
        std::vector<Local<JSValueRef>> argv;
        JSRef<JSVal> jsVal;
        if (XComponentClient::GetInstance().GetJSVal(xcomponentId, jsVal)) {
            argv.emplace_back(jsVal->GetLocalHandle());
        }
        funcRef->Call(execCtx.vm_, JSNApi::GetGlobalObject(execCtx.vm_), argv.data(), argv.size());
    };
    XComponentModel::GetInstance()->RegisterOnCreate(frameNode, std::move(onLoad));
}

void JSXComponent::RegisterOnDestroy(const JsiExecutionContext& execCtx, const Local<JSValueRef>& func)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_VOID(frameNode);

    if (!func->IsFunction()) {
        return;
    }

    auto jsFunc = panda::Global<panda::FunctionRef>(execCtx.vm_, Local<panda::FunctionRef>(func));
    auto onDestroy = [execCtx, funcRef = std::move(jsFunc), node = AceType::WeakClaim(AceType::RawPtr(frameNode))]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponentNode.onDestroy");
        PipelineContext::SetCallBackNode(node);
        funcRef->Call(execCtx.vm_, JSNApi::GetGlobalObject(execCtx.vm_), nullptr, 0);
    };
    XComponentModel::GetInstance()->RegisterOnDestroy(frameNode, std::move(onDestroy));
}

void JSXComponent::JsOnDestroy(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsFunction()) {
        return;
    }
    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onDestroy = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onDestroy");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "destroy" };
        func->Execute(keys, "");
    };
    XComponentModel::GetInstance()->SetOnDestroy(std::move(onDestroy));
}

void JSXComponent::JsBackgroundColor(const JSCallbackInfo& args)
{
    if (!XComponentModel::GetInstance()->IsTexture()) {
        return;
    }
    JSViewAbstract::JsBackgroundColor(args);
}

void JSXComponent::JsOpacity(const JSCallbackInfo& args)
{
    if (!XComponentModel::GetInstance()->IsTexture()) {
        return;
    }
    JSViewAbstract::JsOpacity(args);
}

void JSXComponent::OmitEvent(const JSCallbackInfo& /* args */) {}

void JSXComponent::OmitAttribute(const JSCallbackInfo& /* args */) {}
} // namespace OHOS::Ace::Framework
