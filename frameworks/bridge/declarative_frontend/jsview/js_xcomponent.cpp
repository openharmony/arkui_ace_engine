/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "bridge/declarative_frontend/jsview/models/xcomponent_model_impl.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "frameworks/core/components_ng/base/view_abstract_model.h"
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
    if (type == "node") {
        return XComponentType::NODE;
    }
    return XComponentType::SURFACE;
}
} // namespace

XComponentModel* XComponentModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::XComponentModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::XComponentModelNG instance;
        return &instance;
    } else {
        static Framework::XComponentModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void SetControllerOnCreated(
    const WeakPtr<NG::FrameNode>& targetNode, const JSRef<JSObject>& object, const JsiExecutionContext& execCtx)
{
    auto jsCreatedFunc = object->GetProperty("onSurfaceCreated");
    if (jsCreatedFunc->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(jsCreatedFunc));
        auto onSurfaceCreated = [execCtx, func = std::move(jsFunc), node = targetNode](
                                    const std::string& surfaceId, const std::string& xcomponentId) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("XComponentController.onSurfaceCreated");
            PipelineContext::SetCallBackNode(node);
            auto jsVal = JSRef<JSVal>::Make(ToJSValue(surfaceId));
            func->ExecuteJS(1, &jsVal);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnCreated surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        XComponentModel::GetInstance()->SetControllerOnCreated(std::move(onSurfaceCreated));
    }
}

void SetControllerOnChanged(
    const WeakPtr<NG::FrameNode>& targetNode, const JSRef<JSObject>& object, const JsiExecutionContext& execCtx)
{
    auto jsChangedFunc = object->GetProperty("onSurfaceChanged");
    if (jsChangedFunc->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(jsChangedFunc));
        auto onSurfaceChanged = [execCtx, func = std::move(jsFunc), node = targetNode](
                                    const std::string& surfaceId, const NG::RectF& rect) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("XComponentController.onSurfaceChanged");
            PipelineContext::SetCallBackNode(node);
            JSRef<JSObject> rectObj = JSRef<JSObject>::New();
            rectObj->SetProperty("offsetX", rect.Left());
            rectObj->SetProperty("offsetY", rect.Top());
            rectObj->SetProperty("surfaceWidth", rect.Width());
            rectObj->SetProperty("surfaceHeight", rect.Height());
            auto jsSurfaceId = JSRef<JSVal>::Make(ToJSValue(surfaceId));
            JSRef<JSVal> params[2] = { jsSurfaceId, rectObj };
            func->ExecuteJS(2, params);
        };
        XComponentModel::GetInstance()->SetControllerOnChanged(std::move(onSurfaceChanged));
    }
}

void SetControllerOnDestroyed(
    const WeakPtr<NG::FrameNode>& targetNode, const JSRef<JSObject>& object, const JsiExecutionContext& execCtx)
{
    auto jsDestroyedFunc = object->GetProperty("onSurfaceDestroyed");
    if (jsDestroyedFunc->IsFunction()) {
        auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(jsDestroyedFunc));
        auto onSurfaceDestroyed = [execCtx, func = std::move(jsFunc), node = targetNode](
                                      const std::string& surfaceId, const std::string& xcomponentId) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("XComponentController.onSurfaceDestroyed");
            PipelineContext::SetCallBackNode(node);
            auto jsVal = JSRef<JSVal>::Make(ToJSValue(surfaceId));
            func->ExecuteJS(1, &jsVal);
            TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
                xcomponentId.c_str(), surfaceId.c_str());
        };
        XComponentModel::GetInstance()->SetControllerOnDestroyed(std::move(onSurfaceDestroyed));
    }
}

void SetControllerCallback(const JSRef<JSObject>& object, const JsiExecutionContext& execCtx)
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SetControllerOnCreated(targetNode, object, execCtx);
    SetControllerOnChanged(targetNode, object, execCtx);
    SetControllerOnDestroyed(targetNode, object, execCtx);
}

std::shared_ptr<InnerXComponentController> GetXComponentController(
    const JSRef<JSObject>& controller, std::optional<std::string>& id, const JsiExecutionContext& execCtx)
{
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    auto* jsXComponentController = controller->Unwrap<JSXComponentController>();
    if (jsXComponentController) {
        jsXComponentController->SetInstanceId(Container::CurrentId());
        if (id.has_value()) {
            XComponentClient::GetInstance().AddControllerToJSXComponentControllersMap(
                id.value(), jsXComponentController);
        }
        xcomponentController = jsXComponentController->GetController();
    }
    return xcomponentController;
}

void JSXComponent::JSBind(BindingTarget globalObj)
{
    JSClass<JSXComponent>::Declare("XComponent");
    JSClass<JSXComponent>::StaticMethod("create", &JSXComponent::Create);
    JSClass<JSXComponent>::StaticMethod("onLoad", &JSXComponent::JsOnLoad);
    JSClass<JSXComponent>::StaticMethod("onDestroy", &JSXComponent::JsOnDestroy);
    JSClass<JSXComponent>::StaticMethod("onAppear", &JSXComponent::JsOnAppear);
    JSClass<JSXComponent>::StaticMethod("onDisAppear", &JSXComponent::JsOnDisAppear);
    JSClass<JSXComponent>::StaticMethod("onAttach", &JSXComponent::JsOnAttach);
    JSClass<JSXComponent>::StaticMethod("onDetach", &JSXComponent::JsOnDetach);

    JSClass<JSXComponent>::StaticMethod("onTouch", &JSXComponent::JsOnTouch);
    JSClass<JSXComponent>::StaticMethod("onClick", &JSXComponent::JsOnClick);
    JSClass<JSXComponent>::StaticMethod("onKeyEvent", &JSXComponent::JsOnKeyEvent);
    JSClass<JSXComponent>::StaticMethod("onMouse", &JSXComponent::JsOnMouse);
    JSClass<JSXComponent>::StaticMethod("onHover", &JSXComponent::JsOnHover);
    JSClass<JSXComponent>::StaticMethod("onFocus", &JSXComponent::JsOnFocus);
    JSClass<JSXComponent>::StaticMethod("onBlur", &JSXComponent::JsOnBlur);

    JSClass<JSXComponent>::StaticMethod("backgroundColor", &JSXComponent::JsBackgroundColor);
    JSClass<JSXComponent>::StaticMethod("backgroundImage", &JSXComponent::JsBackgroundImage);
    JSClass<JSXComponent>::StaticMethod("backgroundImageSize", &JSXComponent::JsBackgroundImageSize);
    JSClass<JSXComponent>::StaticMethod("backgroundImagePosition", &JSXComponent::JsBackgroundImagePosition);
    JSClass<JSXComponent>::StaticMethod("opacity", &JSXComponent::JsOpacity);
    JSClass<JSXComponent>::StaticMethod("blur", &JSXComponent::JsBlur);
    JSClass<JSXComponent>::StaticMethod("backdropBlur", &JSXComponent::JsBackdropBlur);
    JSClass<JSXComponent>::StaticMethod("grayscale", &JSXComponent::JsGrayscale);
    JSClass<JSXComponent>::StaticMethod("brightness", &JSXComponent::JsBrightness);
    JSClass<JSXComponent>::StaticMethod("saturate", &JSXComponent::JsSaturate);
    JSClass<JSXComponent>::StaticMethod("contrast", &JSXComponent::JsContrast);
    JSClass<JSXComponent>::StaticMethod("invert", &JSXComponent::JsInvert);
    JSClass<JSXComponent>::StaticMethod("sepia", &JSXComponent::JsSepia);
    JSClass<JSXComponent>::StaticMethod("hueRotate", &JSXComponent::JsHueRotate);
    JSClass<JSXComponent>::StaticMethod("colorBlend", &JSXComponent::JsColorBlend);
    JSClass<JSXComponent>::StaticMethod("sphericalEffect", &JSXComponent::JsSphericalEffect);
    JSClass<JSXComponent>::StaticMethod("lightUpEffect", &JSXComponent::JsLightUpEffect);
    JSClass<JSXComponent>::StaticMethod("pixelStretchEffect", &JSXComponent::JsPixelStretchEffect);
    JSClass<JSXComponent>::StaticMethod("linearGradientBlur", &JSXComponent::JsLinearGradientBlur);
    JSClass<JSXComponent>::StaticMethod("enableAnalyzer", &JSXComponent::JsEnableAnalyzer);
    JSClass<JSXComponent>::StaticMethod("renderFit", &JSXComponent::JsRenderFit);
    JSClass<JSXComponent>::StaticMethod("enableSecure", &JSXComponent::JsEnableSecure);
    JSClass<JSXComponent>::StaticMethod("hdrBrightness", &JSXComponent::JsHdrBrightness);
    JSClass<JSXComponent>::StaticMethod("blendMode", &JSXComponent::JsBlendMode);
    JSClass<JSXComponent>::StaticMethod("enableTransparentLayer", &JSXComponent::JsEnableTransparentLayer);

    JSClass<JSXComponent>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSXComponent::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }
    XComponentOptions options;
    JSRef<JSObject> controllerObj;
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto aiOptions = paramObject->GetProperty("imageAIOptions");
    ExtractInfoToXComponentOptions(options, controllerObj, info);
    if (options.id == std::nullopt && options.xcomponentController == nullptr &&
        (options.xcomponentType == XComponentType::SURFACE || options.xcomponentType == XComponentType::TEXTURE)) {
        XComponentModel::GetInstance()->Create(options.xcomponentType);
    } else {
        XComponentModel::GetInstance()->Create(
            options.id, options.xcomponentType, options.libraryName, options.xcomponentController);
    }
    if (!options.libraryName.has_value() && options.xcomponentController && !controllerObj->IsUndefined()) {
        SetControllerCallback(controllerObj, info.GetExecutionContext());
    }

    auto detachCallback = [](const std::string& xcomponentId) {
        XComponentClient::GetInstance().DeleteControllerFromJSXComponentControllersMap(xcomponentId);
        XComponentClient::GetInstance().DeleteFromJsValMapById(xcomponentId);
    };
    XComponentModel::GetInstance()->SetDetachCallback(std::move(detachCallback));

    if (info.Length() > 1 && info[1]->IsString()) {
        auto soPath = info[1]->ToString();
        XComponentModel::GetInstance()->SetSoPath(soPath);
    }
    ParseImageAIOptions(aiOptions);

    if (options.xcomponentType == XComponentType::SURFACE && options.screenId.has_value()) {
        XComponentModel::GetInstance()->SetScreenId(options.screenId.value());
    }
}

void JSXComponent::ExtractInfoToXComponentOptions(
    XComponentOptions& options, JSRef<JSObject>& controllerObj, const JSCallbackInfo& info)
{
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto id = paramObject->GetProperty("id");
    auto type = paramObject->GetProperty("type");
    auto libraryNameValue = paramObject->GetProperty("libraryname");
    auto controller = paramObject->GetProperty("controller");
    auto screenIdValue = paramObject->GetProperty("screenId");

    if (id->IsString()) {
        options.id = id->ToString();
    }
    if (libraryNameValue->IsString()) {
        options.libraryName = libraryNameValue->ToString();
    }
    if (controller->IsObject()) {
        controllerObj = JSRef<JSObject>::Cast(controller);
        options.xcomponentController = GetXComponentController(controllerObj, options.id, info.GetExecutionContext());
    }
    if (type->IsString()) {
        options.xcomponentType = ConvertToXComponentType(type->ToString());
    } else if (type->IsNumber()) {
        options.xcomponentType = static_cast<XComponentType>(type->ToNumber<int32_t>());
    }
    if (screenIdValue->IsNumber()) {
        options.screenId = screenIdValue->ToNumber<uint64_t>();
    }
}

void* JSXComponent::Create(const XComponentParams& params)
{
    std::shared_ptr<InnerXComponentController> xcomponentController = nullptr;
    if (params.controller) {
        xcomponentController = params.controller->GetController();
    }
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(XComponentModel::GetInstance()->Create(params.elmtId,
        static_cast<float>(params.width), static_cast<float>(params.height), params.xcomponentId,
        static_cast<XComponentType>(params.xcomponentType), params.libraryName, xcomponentController));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->SetIsArkTsFrameNode(true);
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
    auto* jsXComponent = new JSXComponent();
    jsXComponent->SetFrameNode(frameNode);
    taskExecutor->PostTask(
        [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))]() {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            auto xcPattern = frameNode->GetPattern<NG::XComponentPattern>();
            CHECK_NULL_VOID(xcPattern);
            xcPattern->XComponentSizeInit();
            xcPattern->SetXcomponentInit(true);
        },
        TaskExecutor::TaskType::JS, "ArkUIXComponentCreate");

    return jsXComponent;
}

void JSXComponent::ParseImageAIOptions(const JSRef<JSVal>& jsValue)
{
    if (!jsValue->IsObject()) {
        return;
    }
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_VOID(nativeEngine);
    panda::Local<JsiValue> value = jsValue.Get().GetLocalHandle();
    JSValueWrapper valueWrapper = value;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
    XComponentModel::GetInstance()->SetImageAIOptions(optionsValue);
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onLoad = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                      const std::string& xcomponentId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onLoad");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "load", xcomponentId };
        func->ExecuteNew(keys, "");
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onLoad triggers", xcomponentId.c_str());
    };
    XComponentModel::GetInstance()->SetOnLoad(std::move(onLoad));
}

void JSXComponent::RegisterOnCreate(const JsiExecutionContext& execCtx, const Local<JSValueRef>& func)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(frameNode_);
    CHECK_NULL_VOID(frameNode);

    if (!func->IsFunction(execCtx.vm_)) {
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

    if (!func->IsFunction(execCtx.vm_)) {
        return;
    }

    auto jsFunc = panda::Global<panda::FunctionRef>(execCtx.vm_, Local<panda::FunctionRef>(func));
    auto onDestroy = [execCtx, funcRef = std::move(jsFunc), node = AceType::WeakClaim(AceType::RawPtr(frameNode))](
                         const std::string& xcomponentId) {
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
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDestroy = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                         const std::string& xcomponentId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("XComponent.onDestroy");
        PipelineContext::SetCallBackNode(node);
        std::vector<std::string> keys = { "destroy" };
        func->Execute(keys, "");
        TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "XComponent[%{public}s] onDestroy", xcomponentId.c_str());
    };
    XComponentModel::GetInstance()->SetOnDestroy(std::move(onDestroy));
}

void JSXComponent::JsOnAppear(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSInteractableView::JsOnAppear(args);
}

void JSXComponent::JsOnDisAppear(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSInteractableView::JsOnDisAppear(args);
}

void JSXComponent::JsOnAttach(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSInteractableView::JsOnAttach(args);
}

void JSXComponent::JsOnDetach(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSInteractableView::JsOnDetach(args);
}

void JSXComponent::JsOnTouch(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSInteractableView::JsOnTouch(args);
}

void JSXComponent::JsOnClick(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnClick(args);
}

void JSXComponent::JsOnKeyEvent(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnKeyEvent(args);
}

void JSXComponent::JsOnMouse(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnMouse(args);
}

void JSXComponent::JsOnHover(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnHover(args);
}


void JSXComponent::JsOnFocus(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnFocus(args);
}

void JSXComponent::JsOnBlur(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    auto libraryName = XComponentModel::GetInstance()->GetLibraryName();
    if (!XComponentModel::IsCommonEventAvailable(type, libraryName)) {
        return;
    }
    JSViewAbstract::JsOnBlur(args);
}

void JSXComponent::JsBackgroundColor(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (!XComponentModel::IsBackGroundColorAvailable(type)) {
        return;
    }
    if (args.Length() < 1) {
        return;
    }
    Color backgroundColor;
    if (!ParseJsColor(args[0], backgroundColor)) {
        backgroundColor = (type == XComponentType::SURFACE) ? Color::BLACK : Color::TRANSPARENT;
    }
    ViewAbstractModel::GetInstance()->SetBackgroundColor(backgroundColor);
}

void JSXComponent::JsBackgroundImage(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBackgroundImage(args);
}

void JSXComponent::JsBackgroundImageSize(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBackgroundImageSize(args);
}

void JSXComponent::JsBackgroundImagePosition(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBackgroundImagePosition(args);
}


void JSXComponent::JsOpacity(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type == XComponentType::SURFACE || type == XComponentType::COMPONENT) {
        return;
    }
    JSViewAbstract::JsOpacity(args);
}

void JSXComponent::JsBlur(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBlur(args);
}

void JSXComponent::JsBackdropBlur(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBackdropBlur(args);
}

void JSXComponent::JsGrayscale(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
   // JSViewAbstract::JsGrayscale(args);
}

void JSXComponent::JsBrightness(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsBrightness(args);
}

void JSXComponent::JsSaturate(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsSaturate(args);
}

void JSXComponent::JsContrast(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsContrast(args);
}

void JSXComponent::JsInvert(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsInvert(args);
}

void JSXComponent::JsSepia(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsSepia(args);
}

void JSXComponent::JsHueRotate(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsHueRotate(args);
}

void JSXComponent::JsColorBlend(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsColorBlend(args);
}

void JSXComponent::JsSphericalEffect(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsSphericalEffect(args);
}

void JSXComponent::JsLightUpEffect(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsLightUpEffect(args);
}

void JSXComponent::JsPixelStretchEffect(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsPixelStretchEffect(args);
}

void JSXComponent::JsLinearGradientBlur(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::NODE) {
        return;
    }
    JSViewAbstract::JsLinearGradientBlur(args);
}

void JSXComponent::JsEnableAnalyzer(bool enable)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    XComponentModel::GetInstance()->EnableAnalyzer(enable);
}

void JSXComponent::JsRenderFit(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE || args.Length() != 1) {
        return;
    }
    if (type == XComponentType::TEXTURE) {
        JSViewAbstract::JSRenderFit(args);
        return;
    }

    // set RenderFit on SurfaceNode when type is SURFACE
    RenderFit renderFit = RenderFit::RESIZE_FILL;
    if (args[0]->IsNumber()) {
        int32_t fitNumber = args[0]->ToNumber<int32_t>();
        if (fitNumber >= static_cast<int32_t>(RenderFit::CENTER) &&
            fitNumber <= static_cast<int32_t>(RenderFit::RESIZE_COVER_BOTTOM_RIGHT)) {
            renderFit = static_cast<RenderFit>(fitNumber);
        }
    }
    XComponentModel::GetInstance()->SetRenderFit(renderFit);
}

void JSXComponent::JsEnableSecure(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::SURFACE || args.Length() != 1) {
        return;
    }
    // set isSecure on SurfaceNode when type is SURFACE
    if (args[0]->IsBoolean()) {
        bool isSecure = args[0]->ToBoolean();
        XComponentModel::GetInstance()->EnableSecure(isSecure);
    }
}

void JSXComponent::JsHdrBrightness(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::SURFACE || args.Length() != 1) {
        return;
    }
    // set hdrBrightness on SurfaceNode when type is SURFACE
    if (args[0]->IsNumber()) {
        float hdrBrightness = args[0]->ToNumber<float>();
        XComponentModel::GetInstance()->HdrBrightness(std::clamp(hdrBrightness, 0.0f, 1.0f));
    } else {
        XComponentModel::GetInstance()->HdrBrightness(1.0f);
    }
}

void JSXComponent::JsBlendMode(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type == XComponentType::TEXTURE && Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }

    JSViewAbstract::JsBlendMode(args);
}

void JSXComponent::JsEnableTransparentLayer(const JSCallbackInfo& args)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::SURFACE || args.Length() != 1) {
        return;
    }
    // set isTransparentLayer on SurfaceNode when type is SURFACE
    if (args[0]->IsBoolean()) {
        bool isTransparentLayer = args[0]->ToBoolean();
        XComponentModel::GetInstance()->EnableTransparentLayer(isTransparentLayer);
    }
}
} // namespace OHOS::Ace::Framework
