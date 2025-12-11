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

#include "bridge/declarative_frontend/jsview/canvas/js_canvas.h"

#include "base/error/error_code.h"
#include "base/log/ace_scoring_log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/jsview/canvas/js_drawing_rendering_context.h"
#include "bridge/declarative_frontend/jsview/canvas/js_rendering_context_base.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/models/canvas/canvas_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_pattern.h"

namespace OHOS::Ace {
CanvasModel* CanvasModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::CanvasModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::CanvasModelNG instance;
        return &instance;
    } else {
        static Framework::CanvasModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {

void JSCanvas::ParseCanvasParams(const JSRef<JSObject>& params)
{
    CanvasUnit unit = CanvasUnit::DEFAULT;
    auto unitJSValue = params->GetProperty("unit");
    if (unitJSValue->IsNumber()) {
        unit = static_cast<CanvasUnit>(unitJSValue->ToNumber<int32_t>());
    }
    CanvasModel::GetInstance()->UpdateUnit(unit);
    auto aiOptionsValue = params->GetProperty("imageAIOptions");
    if (aiOptionsValue->IsObject()) {
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        panda::Local<JsiValue> value = aiOptionsValue.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        CanvasModel::GetInstance()->SetImageAIOptions(optionsValue);
    }
}

void JSCanvas::Create(const JSCallbackInfo& info)
{
    auto pattern = CanvasModel::GetInstance()->Create();
    CHECK_NULL_VOID(pattern);
    if (info[0]->IsUndefined()) {
        CanvasModel::GetInstance()->DetachRenderContext();
        CanvasModel::GetInstance()->SetImmediateRender(false);
    } else if (info[0]->IsObject()) {
        auto* jsContext = JSRef<JSObject>::Cast(info[0])->Unwrap<JSRenderingContextBase>();
        CanvasModel::GetInstance()->SetImmediateRender(jsContext == nullptr);
        if (jsContext) {
            if (jsContext->IsBuiltIn()) {
                JSException::Throw(ERROR_CODE_CANVAS_ERROR_CONTEXT, "%s",
                    "The context created in system cannot be bound to other canvas component");
            }
            jsContext->SetInstanceId(Container::CurrentId());
            jsContext->SetCanvasPattern(pattern);
            jsContext->SetAntiAlias();
            jsContext->SetDensity();
        } else {
            ParseCanvasParams(JSRef<JSObject>::Cast(info[0]));
        }
    }

    if (info.Length() > 1) {
        auto options = info[1];
        if (!options->IsObject()) {
            return;
        }
        auto engine = EngineHelper::GetCurrentEngine();
        CHECK_NULL_VOID(engine);
        NativeEngine* nativeEngine = engine->GetNativeEngine();
        CHECK_NULL_VOID(nativeEngine);
        panda::Local<JsiValue> value = options.Get().GetLocalHandle();
        JSValueWrapper valueWrapper = value;
        ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
        napi_value optionsValue = nativeEngine->ValueToNapiValue(valueWrapper);
        CanvasModel::GetInstance()->SetImageAIOptions(optionsValue);
    }
}

void JSCanvas::JSBind(BindingTarget globalObj)
{
    JSClass<JSCanvas>::Declare("Canvas");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCanvas>::StaticMethod("create", &JSCanvas::Create, opt);
    JSClass<JSCanvas>::StaticMethod("onReady", &JSCanvas::OnReady);
    JSClass<JSCanvas>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSCanvas>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCanvas>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSCanvas>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCanvas>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCanvas>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCanvas>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCanvas>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCanvas>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCanvas>::StaticMethod("enableAnalyzer", &JSCanvas::EnableAnalyzer);
    JSClass<JSCanvas>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCanvas::OnReady(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    if (Container::IsCurrentUsePartialUpdate()) {
        auto* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto targetNode = AceType::WeakClaim(frameNode);
        auto readyEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                              bool needDrawingContext, CanvasUnit unit) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Canvas.onReady");
            PipelineContext::SetCallBackNode(node);
            if (!needDrawingContext) {
                func->Execute();
                return;
            }
            auto frameNode = node.Upgrade();
            if (!frameNode) {
                return;
            }
            auto pattern = frameNode->GetPattern<NG::CanvasPattern>();
            if (!pattern) {
                return;
            }
            JSRef<JSObject> jsDrawingContext = JSClass<JSDrawingRenderingContext>::NewInstance();
            auto drawingContext = Referenced::Claim(jsDrawingContext->Unwrap<JSDrawingRenderingContext>());
            drawingContext->SetBuiltIn(true);
            drawingContext->SetInstanceId(Container::CurrentId());
            drawingContext->SetCanvasPattern(pattern);
            drawingContext->SetUnit(unit);
            pattern->SetUpdateContextCallback(
                [drawingContext = drawingContext](CanvasUnit unit) { drawingContext->SetUnit(unit); });
            pattern->SetRSCanvasForDrawingContext();
            JSRef<JSVal> params[] = { jsDrawingContext };
            func->ExecuteJS(1, params);
        };
        CanvasModel::GetInstance()->SetOnReady(std::move(readyEvent));
    } else {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto readyEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                              uint32_t accountableCanvasElement) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Canvas.onReady");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        CanvasModel::GetInstance()->SetOnReady(std::move(readyEvent));
    }
}

void JSCanvas::EnableAnalyzer(bool enable)
{
    CanvasModel::GetInstance()->EnableAnalyzer(enable);
}
} // namespace OHOS::Ace::Framework
