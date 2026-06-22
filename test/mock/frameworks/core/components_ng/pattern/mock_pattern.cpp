/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/pattern.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/box_layout_algorithm.h"

namespace OHOS::Ace::NG {
int32_t Pattern::OnRecvCommand(const std::string& command)
{
    return 0;
}

void Pattern::OnColorModeChange(uint32_t colorMode) {}

void Pattern::AddResObj(const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{}

void Pattern::AddResCache(const std::string& key, const std::string& value) {}

std::string Pattern::GetResCacheMapByKey(const std::string& key)
{
    return std::string();
}

void Pattern::RemoveResObj(const std::string& key) {}

void Pattern::UnRegisterResource(const std::string& key) {}

ScopeFocusAlgorithm Pattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm();
}

FocusPattern Pattern::GetFocusPattern() const
{
    return {};
}

RefPtr<AccessibilityProperty> Pattern::CreateAccessibilityProperty()
{
    return nullptr;
}

RefPtr<LayoutAlgorithm> Pattern::CreateLayoutAlgorithm()
{
    return nullptr;
}

RefPtr<EventHub> Pattern::CreateEventHub()
{
    return MakeRefPtr<EventHub>();
}

void Pattern::ReadFontScaleFromEnv()
{}

void Pattern::CheckLocalized()
{}

RefPtr<VerticalOverflowHandler> Pattern::GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host)
{
    return nullptr;
}

void Pattern::PropagateForegroundColorToChildren() {}

void Pattern::UpdateChildRenderContext(
    const RefPtr<RenderContext>& renderContext, std::list<RefPtr<FrameNode>>& childrenList)
{}

std::optional<SizeF> Pattern::GetHostFrameSize() const
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        return std::nullopt;
    }
    return frameNode->GetGeometryNode()->GetMarginFrameSize();
}

std::optional<OffsetF> Pattern::GetHostFrameOffset() const
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        return std::nullopt;
    }
    return frameNode->GetGeometryNode()->GetFrameOffset();
}

std::optional<OffsetF> Pattern::GetHostFrameGlobalOffset() const
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        return std::nullopt;
    }
    return frameNode->GetGeometryNode()->GetFrameOffset() + frameNode->GetGeometryNode()->GetParentGlobalOffset();
}

std::optional<SizeF> Pattern::GetHostContentSize() const
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        return std::nullopt;
    }
    const auto& content = frameNode->GetGeometryNode()->GetContent();
    if (!content) {
        return std::nullopt;
    }
    return content->GetRect().GetSize();
}

int32_t Pattern::GetHostInstanceId() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, INSTANCE_ID_UNDEFINED);
    return host->GetInstanceId();
}

PipelineContext* Pattern::GetContext() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetContext();
}

RenderContext* Pattern::GetRenderContext() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetRenderContext().GetRawPtr();
}

void Pattern::MarkDirty(PropertyChangeFlag flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(flag);
}

bool Pattern::IsNeedAdjustByAspectRatio()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_RETURN(host, false);
    return layoutProperty->HasAspectRatio();
}

int32_t Pattern::GetThemeScopeId() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    return host->GetThemeScopeId();
}

bool Pattern::HandleTextBoxComponentCommand(
    const std::string& command, std::string& cmd, std::unique_ptr<JsonValue>& json, std::unique_ptr<JsonValue>& params)
{
    json = JsonUtil::ParseJsonString(command);
    CHECK_NULL_RETURN(json && !json->IsNull(), false);
    cmd = json->GetString("cmd");
    CHECK_NULL_RETURN(!cmd.empty(), false);
    params = json->GetValue("params");
    CHECK_NULL_RETURN(params && params->IsObject(), false);
    return true;
}

void Pattern::AttachToFrameNode(const WeakPtr<FrameNode>&) {}
RefPtr<FrameNode> Pattern::GetHost() const { return nullptr; }

} // namespace OHOS::Ace::NG
