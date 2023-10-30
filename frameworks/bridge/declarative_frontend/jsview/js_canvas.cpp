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
#include "bridge/declarative_frontend/jsview/models/canvas_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/custom_paint/canvas_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<CanvasModel> CanvasModel::instance_ = nullptr;
std::mutex CanvasModel::mutex_;
CanvasModel* CanvasModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CanvasModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CanvasModelNG());
            } else {
                instance_.reset(new Framework::CanvasModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {

void JSCanvas::Create(const JSCallbackInfo& info)
{
    auto pattern = CanvasModel::GetInstance()->Create();
    CHECK_NULL_VOID(pattern);
    auto canvasPattern = CanvasModel::GetInstance()->GetTaskPool(pattern);
    if (info.Length() > 0 && info[0]->IsObject()) {
        JSCanvasRenderer* jsContext = JSRef<JSObject>::Cast(info[0])->Unwrap<JSCanvasRenderer>();
        if (jsContext) {
            jsContext->SetCanvasPattern(canvasPattern);
            jsContext->SetAntiAlias();
        }
    }
    CanvasModel::GetInstance()->PushCanvasPattern(pattern);
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
    JSClass<JSCanvas>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSCanvas::OnReady(const JSCallbackInfo& info)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS, "Canvas onReady begins");
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    std::function<void(uint32_t)> readyEvent;
    if (Container::IsCurrentUsePartialUpdate()) {
        readyEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                         uint32_t accountableCanvasElement) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Canvas.onReady");
            ViewStackModel::GetInstance()->StartGetAccessRecordingFor(accountableCanvasElement);
            func->Execute();
            ViewStackModel::GetInstance()->StopGetAccessRecording();
        };
    } else {
        readyEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                         uint32_t accountableCanvasElement) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Canvas.onReady");
            func->Execute();
        };
    }
    CanvasModel::GetInstance()->SetOnReady(std::move(readyEvent));
}
} // namespace OHOS::Ace::Framework
