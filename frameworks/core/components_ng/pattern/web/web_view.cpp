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

#include "core/components_ng/pattern/web/web_view.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void WebView::Create(const std::string& src, const RefPtr<WebController>& webController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
}

void WebView::SetOnPageStart(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& OnPageStart)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(OnPageStart));
}

void WebView::SetOnPageFinish(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onPageEnd)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(onPageEnd));
}

void WebView::SetOnHttpErrorReceive(
    std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onHttpErrorReceive)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(onHttpErrorReceive));
}

void WebView::SetOnErrorReceive(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& onErrorReceive)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(onErrorReceive));
}

void WebView::SetOnConsole(std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>&& onConsole)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebView::SetJsEnabled(bool isJsEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateJsEnabled(isJsEnabled);
}

} // namespace OHOS::Ace::NG