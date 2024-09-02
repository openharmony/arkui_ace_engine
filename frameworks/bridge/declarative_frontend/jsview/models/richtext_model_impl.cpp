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

#include "bridge/declarative_frontend/jsview/models/richtext_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/web/web_component.h"

namespace OHOS::Ace::Framework {
void RichTextModelImpl::Create(const std::string& data)
{
    auto webComponent = AceType::MakeRefPtr<OHOS::Ace::WebComponent>("");
    if (webComponent) {
        webComponent->SetData(data);
        ViewStackProcessor::GetInstance()->Push(webComponent);
    }
}

void RichTextModelImpl::SetOnPageStart(std::function<void(const BaseEventInfo*)>&& onStarted)
{
    auto eventMarker = EventMarker(std::move(onStarted));
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetPageStartedEventId(eventMarker);
    }
}

void RichTextModelImpl::SetOnPageFinish(std::function<void(const BaseEventInfo*)>&& onFinish)
{
    auto eventMarker = EventMarker(std::move(onFinish));
    auto webComponent = AceType::DynamicCast<WebComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (webComponent) {
        webComponent->SetPageFinishedEventId(eventMarker);
    }
}
} // namespace OHOS::Ace::Framework
