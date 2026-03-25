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

#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/frame_node.h"
#include "base/json/json_util.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

#include <iterator>

namespace OHOS::Ace::NG {
UINode::UINode(const std::string& tag, int32_t nodeId, bool isRoot)
    : tag_(tag), nodeId_(nodeId), accessibilityId_(nodeId), isRoot_(isRoot)
{}

bool UINode::MaybeOnDelete() const
{
    return false;
}
void UINode::AddChild(const RefPtr<UINode>& child, int32_t slot, bool silently, bool addDefaultTransition,
    bool addModalUiextension)
{
    (void)slot;
    (void)silently;
    (void)addDefaultTransition;
    (void)addModalUiextension;
    if (!child) {
        return;
    }
    children_.push_back(child);
    child->SetParent(WeakClaim(this), false);
}

std::list<RefPtr<UINode>>::iterator UINode::RemoveChild(const RefPtr<UINode>& child, bool allowTransition)
{
    (void)allowTransition;
    if (!child) {
        return children_.end();
    }
    for (auto iter = children_.begin(); iter != children_.end(); ++iter) {
        if (*iter != child) {
            continue;
        }
        child->SetParent(WeakPtr<UINode>(), false);
        return children_.erase(iter);
    }
    return children_.end();
}

void UINode::FireCustomDisappear() {}

void UINode::SetParent(const WeakPtr<UINode>& parent, bool needDetect)
{
    (void)needDetect;
    parent_ = parent;
}

void UINode::DumpTree(int32_t depth, bool hasJson, const std::string& desc)
{
    (void)depth;
    (void)hasJson;
    (void)desc;
}
} // namespace OHOS::Ace::NG


namespace OHOS::Ace::NG {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"

UINode::~UINode() = default;

std::atomic_int32_t UINode::count_ = 0;

void UINode::AttachContext(PipelineContext* context, bool recursive)
{
}

void UINode::AttachToMainTree(bool recursive)
{
}

void UINode::AttachToMainTree(bool recursive, PipelineContext* context)
{
}

HitTestResult UINode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint, TouchRestrict& touchRestrict, AxisTestResult& onAxisResult)
{
    return {};
}

RefPtr<LayoutWrapperNode> UINode::CreateLayoutWrapper(bool forceMeasure , bool forceLayout)
{
    return {};
}

int32_t UINode::CurrentFrameCount() const
{
    return {};
}

void UINode::DetachContext(bool recursive)
{
}

void UINode::DetachFromMainTree(bool recursive , bool needCheckThreadSafeNodeTree)
{
}

void UINode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
}

void UINode::DumpSimplifyInfoWithParamConfig(std::shared_ptr<JsonValue>& json, ParamConfig config)
{
    (void)config;
    if (json) {
        json->Put("$type", tag_.c_str());
    }
}

void UINode::DumpSimplifyTree(int32_t depth, std::shared_ptr<JsonValue>& current)
{
    DumpSimplifyTreeWithParamConfig(depth, current, true, {}, nullptr);
}

void UINode::DumpSimplifyTreeBase(std::shared_ptr<JsonValue>& current)
{
    if (current) {
        current->Put("$type", tag_.c_str());
    }
}

void UINode::DumpSimplifyTreeWithParamConfig(int32_t depth, std::shared_ptr<JsonValue>& current, bool onlyNeedVisible, ParamConfig config , std::function<std::pair<bool, bool>(const RefPtr<UINode>&)> dumpChecker)
{
    (void)depth;
    (void)onlyNeedVisible;
    (void)config;
    (void)dumpChecker;
    if (!current) {
        return;
    }
    current->Put("$type", tag_.c_str());
    if (children_.empty()) {
        return;
    }
    auto childrenJson = JsonUtil::CreateArray();
    for (const auto& child : children_) {
        if (!child) {
            continue;
        }
        auto childJson = JsonUtil::CreateSharedPtrJson();
        child->DumpSimplifyTreeWithParamConfig(0, childJson, true, {}, nullptr);
        childrenJson->Put(childJson);
    }
    current->PutRef("$children", std::move(childrenJson));
}

bool UINode::DumpTreeByComponentName(const std::string& name)
{
    return {};
}

bool UINode::DumpTreeById(int32_t depth, const std::string& id, bool hasJson)
{
    return {};
}

void UINode::DumpTreeJsonForDiff(std::unique_ptr<JsonValue>& json)
{
}

void UINode::DumpViewDataPageNodes(RefPtr<ViewDataWrap> viewDataWrap, bool skipSubAutoFillContainer , bool needsRecordData)
{
}

void UINode::FindTopNavDestination(std::list<RefPtr<FrameNode>>& result)
{
    if (result.empty()) {
        auto frame = AceType::DynamicCast<FrameNode>(Claim(this));
        if (frame && frame->GetTag() == V2::NAVIGATION_VIEW_ETS_TAG) {
            auto navGroup = AceType::DynamicCast<NavigationGroupNode>(frame);
            auto pattern = navGroup ? navGroup->GetPattern<NavigationPattern>() : nullptr;
            auto stack = pattern ? pattern->GetNavigationStack() : nullptr;
            if (stack && !stack->GetAllNavDestinationNodes().empty()) {
                const auto& top = stack->GetAllNavDestinationNodes().back().second;
                auto topFrame = AceType::DynamicCast<FrameNode>(top);
                if (topFrame) {
                    result.emplace_back(topFrame);
                }
            }
        }
    }
    for (const auto& child : children_) {
        if (!child) {
            continue;
        }
        child->FindTopNavDestination(result);
    }
}

int32_t UINode::FrameCount() const
{
    return {};
}

void UINode::GenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
}

RefPtr<UINode> UINode::GetChildAtIndex(int32_t index) const
{
    if (index < 0 || index >= static_cast<int32_t>(children_.size())) {
        return nullptr;
    }
    auto iter = children_.begin();
    std::advance(iter, index);
    return *iter;
}

int32_t UINode::GetChildIndex(const RefPtr<UINode>& child) const
{
    int32_t index = 0;
    for (const auto& node : children_) {
        if (node == child) {
            return index;
        }
        ++index;
    }
    return -1;
}

RefPtr<PipelineContext> UINode::GetContextRefPtr() const
{
    return {};
}

PipelineContext* UINode::GetContext() const
{
    return nullptr;
}

RefPtr<UINode> UINode::GetFrameChildByIndexWithoutExpanded(uint32_t index)
{
    return {};
}

int32_t UINode::GetFrameNodeIndex(const RefPtr<FrameNode>& node, bool isExpanded)
{
    return {};
}

RefPtr<FrameNode> UINode::GetParentFrameNode() const
{
    return {};
}

bool UINode::IsContextTransparent()
{
    return {};
}

void UINode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
}

void UINode::MarkNeedFrameFlushDirty(PropertyChangeFlag extraFlag)
{
}

bool UINode::MarkRemoving()
{
    return {};
}

bool UINode::MaybeRelease()
{
    return {};
}

void UINode::MountToParent(const RefPtr<UINode>& parent, int32_t slot , bool silently , bool addDefaultTransition , bool addModalUiextension)
{
}

bool UINode::NeedRequestAutoSave()
{
    return {};
}

void UINode::NotifyChange(int32_t changeIdx, int32_t count, int64_t id, NotificationType notificationType)
{
}

void UINode::NotifyColorModeChange(uint32_t colorMode)
{
}

void UINode::NotifyColorModeChange(uint32_t colorMode, bool recursive)
{
}

void UINode::NotifyWebPattern(bool isRegister)
{
}

void UINode::OnDelete()
{
}

void UINode::OnDetachFromMainTree(bool recursive , PipelineContext* context)
{
}

void UINode::OnGenerateOneDepthVisibleFrameWithOffset(std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset)
{
}

void UINode::OnRecycle()
{
}

bool UINode::OnRemoveFromParent(bool allowTransition)
{
    return {};
}

void UINode::OnReuse()
{
}

void UINode::RebuildRenderContextTree()
{
}

void UINode::RemoveChildAtIndex(int32_t index)
{
}

bool UINode::RemoveImmediately() const
{
    return {};
}

bool UINode::RenderCustomChild(int64_t deadline)
{
    return {};
}

void UINode::SetDestroying(bool isDestroying , bool cleanStatus)
{
}

void UINode::SetFreeze(bool isFreeze, bool isForceUpdateFreezeVaule , bool isUserFreeze)
{
}

void UINode::SetJSViewActive(bool active, bool isLazyForEachNode , bool isReuse)
{
}

bool UINode::SetParentLayoutConstraint(const SizeF& size) const
{
    return {};
}

void UINode::SetThemeScopeId(int32_t themeScopeId)
{
}

int32_t UINode::GetThemeScopeId() const
{
    return -1;
}

void UINode::TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility)
{
}

void UINode::UpdateConfigurationUpdate()
{
}

void UINode::UpdateConfigurationUpdate(const ConfigurationChange& configurationChange)
{
}

void UINode::UpdateDrawLayoutChildObserver(bool isClearLayoutObserver, bool isClearDrawObserver)
{
}

void UINode::UpdateDrawLayoutChildObserver(const RefPtr<UINode>& child)
{
}

void UINode::UpdateGeometryTransition()
{
}

void UINode::UpdateLayoutPropertyFlag()
{
}

void UINode::UpdateThemeScopeId(int32_t themeScopeId)
{
}

void UINode::UpdateThemeScopeUpdate(int32_t themeScopeId)
{
}

void UINode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
}

void UINode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
}

void UINode::Build(std::shared_ptr<std::list<ExtraInfo>> extraInfos)
{
}

void UINode::ClearSubtreeLayoutAlgorithm(bool includeSelf, bool clearEntireTree)
{
}

void UINode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
}

std::string UINode::GetCurrentCustomNodeInfo()
{
    return "";
}

void UINode::GetNodeListByComponentName(
    int32_t pageId, std::vector<int32_t>& nodeList, const std::string& componentName, bool isRegex)
{
    (void)pageId;
    (void)nodeList;
    (void)componentName;
    (void)isRegex;
}

RefPtr<UINode> UINode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    return {};
}

void UINode::GetInspectorValue()
{
}

void UINode::MarkNeedSyncRenderTree(bool needRebuild)
{
}

HitTestResult UINode::MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint, MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    return {};
}

void UINode::OnAttachToMainTree(bool recursive)
{
}

void UINode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
}

void UINode::OnSetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
{
}

void UINode::PaintDebugBoundaryTreeAll(bool flag)
{
}

void UINode::SetActive(bool active, bool needRebuildRenderContext)
{
}

int32_t UINode::TotalChildCount() const
{
    return {};
}

HitTestResult UINode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint, const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId, ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    return {};
}

void UINode::UpdateChildrenFreezeState(bool isFreeze, bool isForceUpdateFreezeVaule)
{
}
#pragma clang diagnostic pop
} // namespace OHOS::Ace::NG
