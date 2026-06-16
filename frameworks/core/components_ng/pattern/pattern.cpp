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

#include "core/components_ng/pattern/pattern.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"
#include "core/components_ng/pattern/corner_mark/corner_mark.h"
#include "core/components_ng/property/accessibility_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
int32_t Pattern::OnRecvCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return RET_FAILED;
    }
    auto event = json->GetString("cmd");
    if (event.compare("click") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto eventHub = host->GetEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, RET_FAILED);
        if (!eventHub->IsEnabled()) {
            return RET_FAILED;
        }
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, RET_FAILED);
        auto clickEventFunc = gestureHub->GetClickEvent();
        CHECK_NULL_RETURN(clickEventFunc, RET_FAILED);
        GestureEvent info;
        clickEventFunc(info);
        return RET_SUCCESS;
    } else if (event.compare("ShowCornerMark") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto cornerMark = AceType::MakeRefPtr<CornerMark>();
        CHECK_NULL_RETURN(cornerMark, RET_FAILED);
        return cornerMark->ResponseShowCornerMarkEvent(host, command);
    } else {
        return OnInjectionEvent(command);
    }
    return RET_FAILED;
}

void Pattern::OnColorModeChange(uint32_t colorMode)
{
    if (resourceMgr_) {
        resourceMgr_->ReloadResources();
    }
}

void Pattern::AddResObj(const std::string& key, const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResource(key, resObj, std::move(updateFunc));
}

void Pattern::AddResCache(const std::string& key, const std::string& value)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResCache(key, value);
}

std::string Pattern::GetResCacheMapByKey(const std::string& key)
{
    if (resourceMgr_ == nullptr) {
        return "";
    }
    return resourceMgr_->GetResCacheMapByKey(key);
}

void Pattern::RemoveResObj(const std::string& key)
{
    if (resourceMgr_) {
        resourceMgr_->RemoveResource(key);
        if (resourceMgr_->Empty()) {
            resourceMgr_ = nullptr;
        }
    }
}

void Pattern::UnRegisterResource(const std::string& key)
{
    RemoveResObj(key);
}

ScopeFocusAlgorithm Pattern::GetScopeFocusAlgorithm()
{
    return ScopeFocusAlgorithm();
}

FocusPattern Pattern::GetFocusPattern() const
{
    return {};
}

void Pattern::ReadFontScaleFromEnv()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    envFontScale_ = pipeline->ResolveFontScaleFromEnv(host);
}

GestureEventFunc Pattern::GetLongPressEventRecorder()
{
    auto longPressCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            return;
        }
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto host = pattern->GetHost();
        CHECK_NULL_VOID(host);
        auto inspectorId = host->GetInspectorId().value_or("");
        auto text = host->GetAccessibilityProperty<NG::AccessibilityProperty>()->GetGroupText(true);
        auto desc = host->GetAutoEventParamValue("");

        Recorder::EventParamsBuilder builder;
        builder.SetId(inspectorId)
            .SetType(host->GetTag())
            .SetEventType(Recorder::LONG_PRESS)
            .SetText(text)
            .SetHost(host)
            .SetDescription(desc);
        if (Recorder::EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_RECT)) {
            auto rect = host->GetTransformRectRelativeToWindow().ToBounds();
            builder.SetExtra(Recorder::KEY_NODE_RECT, std::move(rect));
        }
        Recorder::EventRecorder::Get().OnEvent(std::move(builder));
    };
    return longPressCallback;
}

RefPtr<AccessibilityProperty> Pattern::CreateAccessibilityProperty()
{
    return MakeRefPtr<AccessibilityProperty>();
}

RefPtr<LayoutAlgorithm> Pattern::CreateLayoutAlgorithm()
{
    return MakeRefPtr<BoxLayoutAlgorithm>();
}

RefPtr<EventHub> Pattern::CreateEventHub()
{
    return MakeRefPtr<EventHub>();
}

void Pattern::CheckLocalized()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    if (layoutProperty->IsPositionLocalizedEdges()) {
        layoutProperty->CheckPositionLocalizedEdges(layoutDirection);
    }
    layoutProperty->CheckMarkAnchorPosition(layoutDirection);
    if (layoutProperty->IsOffsetLocalizedEdges()) {
        layoutProperty->CheckOffsetLocalizedEdges(layoutDirection);
    }
    layoutProperty->CheckLocalizedPadding(layoutProperty, layoutDirection);
    layoutProperty->CheckLocalizedMargin(layoutProperty, layoutDirection);
    layoutProperty->CheckLocalizedEdgeWidths(layoutProperty, layoutDirection);
    layoutProperty->CheckLocalizedEdgeColors(layoutDirection);
    layoutProperty->CheckLocalizedBorderRadiuses(layoutDirection);
    layoutProperty->CheckLocalizedOuterBorderColor(layoutDirection);
    layoutProperty->CheckLocalizedBorderImageSlice(layoutDirection);
    layoutProperty->CheckLocalizedBorderImageWidth(layoutDirection);
    layoutProperty->CheckLocalizedBorderImageOutset(layoutDirection);
    layoutProperty->CheckLocalizedAlignment(layoutDirection);
    // Reset for safeAreaExpand's Cache in GeometryNode
    host->ResetSafeAreaPadding();
    layoutProperty->CheckLocalizedSafeAreaPadding(layoutDirection);
    layoutProperty->CheckIgnoreLayoutSafeArea(layoutDirection);
    layoutProperty->CheckBackgroundLayoutSafeAreaEdges(layoutDirection);
}

RefPtr<VerticalOverflowHandler> Pattern::GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host)
{
    return nullptr;
}

void Pattern::PropagateForegroundColorToChildren()
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    const auto& children = frameNode->GetChildren();
    if (children.empty()) {
        return;
    }
    const auto& renderContext = frameNode->GetRenderContext();
    if (!renderContext->HasForegroundColor() && !renderContext->HasForegroundColorStrategy()) {
        return;
    }
    std::list<RefPtr<FrameNode>> childrenList {};
    std::queue<RefPtr<FrameNode>> queue {};
    queue.emplace(frameNode);
    RefPtr<FrameNode> parentNode;
    while (!queue.empty()) {
        parentNode = queue.front();
        queue.pop();
        auto childs = parentNode->GetChildren();
        if (childs.empty()) {
            continue;
        }
        for (auto child : childs) {
            if (!AceType::InstanceOf<NG::FrameNode>(child)) {
                continue;
            }
            auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
            auto childRenderContext = childFrameNode->GetRenderContext();
            if (childRenderContext->HasForegroundColorFlag() && childRenderContext->GetForegroundColorFlagValue()) {
                continue;
            }
            queue.emplace(childFrameNode);
            childrenList.emplace_back(childFrameNode);
        }
    }
    UpdateChildRenderContext(renderContext, childrenList);
}

void Pattern::UpdateChildRenderContext(
    const RefPtr<RenderContext>& renderContext, std::list<RefPtr<FrameNode>>& childrenList)
{
    bool isForegroundColor = renderContext->HasForegroundColor();
    for (auto child : childrenList) {
        auto childRenderContext = child->GetRenderContext();
        if (!childRenderContext->HasForegroundColor() && !childRenderContext->HasForegroundColorStrategy()) {
            if (isForegroundColor) {
                childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
                childRenderContext->ResetForegroundColorStrategy();
                childRenderContext->UpdateForegroundColorFlag(false);
            } else {
                childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
                childRenderContext->ResetForegroundColor();
                childRenderContext->UpdateForegroundColorFlag(false);
            }
        } else {
            if (!childRenderContext->HasForegroundColorFlag()) {
                continue;
            }
            if (childRenderContext->GetForegroundColorFlagValue()) {
                continue;
            }
            if (isForegroundColor) {
                childRenderContext->UpdateForegroundColor(renderContext->GetForegroundColorValue());
                childRenderContext->ResetForegroundColorStrategy();
                childRenderContext->UpdateForegroundColorFlag(false);
            } else {
                childRenderContext->UpdateForegroundColorStrategy(renderContext->GetForegroundColorStrategyValue());
                childRenderContext->ResetForegroundColor();
                childRenderContext->UpdateForegroundColorFlag(false);
            }
        }
    }
}

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

void Pattern::DetachFromFrameNode(FrameNode* frameNode)
{
    onDetach_ = true;
    OnDetachFromFrameNode(frameNode);
    onDetach_ = false;
    frameNode_.Reset();
}

void Pattern::AttachToFrameNode(const WeakPtr<FrameNode>& frameNode)
{
    if (frameNode_ == frameNode) {
        return;
    }
    frameNode_ = frameNode;
    OnAttachToFrameNode();
}

RefPtr<FrameNode> Pattern::GetHost() const
{
    if (onDetach_ && SystemProperties::DetectGetHostOnDetach()) {
        LOGF_ABORT("fatal: can't GetHost at detaching period");
    }
    return frameNode_.Upgrade();
}
} // namespace OHOS::Ace::NG
