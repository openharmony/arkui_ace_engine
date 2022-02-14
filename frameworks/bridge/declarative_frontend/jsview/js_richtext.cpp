/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_v2/richtext/rich_text_component.h"

namespace OHOS::Ace::Framework {
void JSRichText::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGI("richtext create error; info is non-valid");
    }

    auto component = AceType::MakeRefPtr<V2::RichTextComponent>();
    ViewStackProcessor::GetInstance()->Push(component);

    std::string data;
    ParseJsString(info[0], data);
    Component->SetData(data);
}

void JSRichText::JSBind(BindingTarget globalObj)
{
    JSClass<JSRichText>::Declare("RichText");
    JSClass<JSRichText>::StaticMethod("create", &JSRichText::Create);
    JSClass<JSRichText>::StaticMethod("onStart", &JSRichText::OnStart);
    JSClass<JSRichText>::StaticMethod("onComplete", &JSRichText::OnComplete);
    JSClass<JSRichText>::Inherit<JSViewAbstract>();
    JSClass<JSRichText>::Bind<>(globalObj);
}

void JSRichText::OnStart(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto eventMarker = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto richText = AceType::DynamicCast<V2::RichTextComponent>(component);
        if (richText) {
            richText->SetPageStartedEventId(eventMarker);
        }
    }
}

void JSRichText::OnComplete(const JSCallbackInfo& info)
{
    if (info.Length() > 0 && info[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto eventMarker = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        auto richText = AceType::DynamicCast<V2::RichTextComponent>(component);
        if (richText) {
            richText->SetPageFinishedEventId(eventMarker);
        }
    }
}
} // namespace OHOS::Ace::Framework
