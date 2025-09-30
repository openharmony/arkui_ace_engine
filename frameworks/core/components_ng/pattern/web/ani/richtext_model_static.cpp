/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/ani/richtext_model_static.h"

#include "core/components_ng/base/node_flag.h"

#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_web_pattern.h"
#else
#if !defined(ANDROID_PLATFORM) && !defined(IOS_PLATFORM)
#include "core/components_ng/pattern/web/web_pattern.h"
#else
#include "core/components_ng/pattern/web/cross_platform/web_pattern.h"
#endif
#endif // ARKUI_CAPI_UNITTEST

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
RefPtr<NG::FrameNode> RichTextModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    frameNode->AddFlag(NodeFlag::WEB_TAG);
    return frameNode;
}

void RichTextModelStatic::SetRichTextOptions(FrameNode *frameNode, const std::string& options)
{
    CHECK_NULL_VOID(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebData(options);
}
void RichTextModelStatic::SetOnPageStart(FrameNode *frameNode, std::function<void(const BaseEventInfo*)>&& onStarted)
{
    CHECK_NULL_VOID(frameNode);
    auto func = onStarted;
    auto onPageStartedEvent = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(onPageStartedEvent));
}
void RichTextModelStatic::SetOnPageFinish(FrameNode *frameNode, std::function<void(const BaseEventInfo*)>&& onFinish)
{
    CHECK_NULL_VOID(frameNode);
    auto func = onFinish;
    auto onPageFinishEvent = [func](const std::shared_ptr<BaseEventInfo>& info) { func(info.get()); };
    auto webEventHub = frameNode->GetEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(onPageFinishEvent));
}
} // namespace OHOS::Ace::NG
