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

#include "frameworks/bridge/declarative_frontend/jsview/js_canvas.h"

#include "base/log/ace_scoring_log.h"
#include "core/common/container.h"
#include "core/components/custom_paint/custom_paint_component.h"
#include "core/components_ng/pattern/custom_paint/custom_paint_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSCanvas::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        auto pattern = NG::CustomPaintView::Create();
        if (info[0]->IsObject()) {
            JSCanvasRenderer* jsContext = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasRenderer>();
            if (jsContext) {
                jsContext->SetCustomPaintPattern(pattern);
                jsContext->SetAntiAlias();
            }
        }
        return;
    }

    RefPtr<OHOS::Ace::CustomPaintComponent> paintChild = AceType::MakeRefPtr<OHOS::Ace::CustomPaintComponent>();
    if (info[0]->IsObject()) {
        JSCanvasRenderer* jsContext = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasRenderer>();
        if (jsContext) {
            jsContext->SetComponent(paintChild->GetTaskPool());
            jsContext->SetAntiAlias();
        }
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(paintChild);
    ViewStackProcessor::GetInstance()->Push(paintChild);
}

void JSCanvas::JSBind(BindingTarget globalObj)
{
    JSClass<JSCanvas>::Declare("Canvas");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSCanvas>::StaticMethod("create", &JSCanvas::Create, opt);
    JSClass<JSCanvas>::StaticMethod("onReady", &JSCanvas::OnReady);
    JSClass<JSCanvas>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSCanvas>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSCanvas>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSCanvas>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSCanvas>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSCanvas>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSCanvas>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSCanvas>::Inherit<JSViewAbstract>();
    JSClass<JSCanvas>::Bind<>(globalObj);
}

void JSCanvas::OnReady(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto readyEvent_ = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Canvas.onReady");
            func->Execute();
        };
        NG::CustomPaintView::SetOnReady(std::move(readyEvent_));
        return;
    }

    auto container = Container::Current();
    if (!container) {
        LOGE("No container");
        return;
    }
    auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!context) {
        LOGE("No PipelineContext");
        return;
    }
    auto component = AceType::DynamicCast<CustomPaintComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!component) {
        LOGE("No CustomPaintComponent");
        return;
    }

    auto elmtId = component->GetElementId();
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto readyEvent_ =
        Container::IsCurrentUsePartialUpdate()
            ? EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc),
                              accountableCanvasElement = elmtId]() {
                  JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                  ACE_SCORING_EVENT("Canvas.onReady");
                  LOGD("Canvas elmtId %{public}d executing JS onReady function - start", accountableCanvasElement);
                  ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(accountableCanvasElement);
                  func->Execute();
                  ViewStackProcessor::GetInstance()->StopGetAccessRecording();
                  LOGD("Canvas elmtId %{public}d executing JS onReady function - end", accountableCanvasElement);
              })
            : EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
                  JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                  ACE_SCORING_EVENT("Canvas.onReady");
                  func->Execute();
              });
    component->SetOnReadyEvent(readyEvent_, context);
}
} // namespace OHOS::Ace::Framework
