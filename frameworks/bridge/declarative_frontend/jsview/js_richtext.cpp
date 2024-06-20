/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_richtext.h"

#include <string>

#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/richtext_model_impl.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/richtext_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<RichTextModel> RichTextModel::instance_ = nullptr;
std::mutex RichTextModel::mutex_;
RichTextModel* RichTextModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::RichTextModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::RichTextModelNG());
            } else {
                instance_.reset(new Framework::RichTextModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSRichText::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    std::string data;

    if (ParseJsString(info[0], data)) {
        RichTextModel::GetInstance()->Create(data);
    } else {
        TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "richtext component failed to parse data");
    }
}

void JSRichText::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichText>::Declare("RichText");
    JSClass<JSRichText>::StaticMethod("create", &JSRichText::Create);
    JSClass<JSRichText>::StaticMethod("onStart", &JSRichText::OnStart);
    JSClass<JSRichText>::StaticMethod("onComplete", &JSRichText::OnComplete);
    JSClass<JSRichText>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSRichText>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSRichText>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSRichText>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSRichText>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSRichText>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSRichText::OnStart(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onStartEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };

        RichTextModel::GetInstance()->SetOnPageStart(onStartEvent);
    }
}

void JSRichText::OnComplete(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onCompleteEvent = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                                   const BaseEventInfo* info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };

        RichTextModel::GetInstance()->SetOnPageFinish(onCompleteEvent);
    }
}
} // namespace OHOS::Ace::Framework
