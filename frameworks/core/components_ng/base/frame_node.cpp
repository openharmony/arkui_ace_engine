/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"

#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/pipeline/base/element_register.h"

#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
#include "core/common/layout_inspector.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#endif
#include "ui/view/frame_node.h"
#include "ui/view/pattern.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/log/ace_performance_monitor.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/log/dump_log.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/thread/task_executor.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/container.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/manager/drag_drop/drag_drop_related_configuration.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include "core/components_ng/pattern/ui_extension/dynamic_component/dynamic_component_manager.h"
#endif
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"

namespace {
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr int32_t SUBSTR_LENGTH = 3;
const char DIMENSION_UNIT_VP[] = "vp";
constexpr int32_t SIZE_CHANGE_DUMP_SIZE = 5;
constexpr double MIN_WIDTH = 5.0;
constexpr double MIN_HEIGHT = 5.0;
constexpr double MIN_OPACITY = 0.1;
constexpr uint64_t MATRIX_CACHE_TIME_THRESHOLD = 15000000000;
/* suggestOpIncByte_s status mask, to indicate different aspects of node status
 * related with suggestion OPINC improvements.
 * for internal use; subject to change.
 */
// suggest opinc marked.
constexpr uint8_t SUGGEST_OPINC_MARKED_MASK = 1;
// Whether the node can be suggest opinc marked.
constexpr uint8_t CAN_SUGGEST_OPINC_MASK = 1 << 1;
// The node already activated for suggest opinc.
constexpr uint8_t SUGGEST_OPINC_ACTIVATED_ONCE = 1 << 2;
// The node already checked for suggest opinc.
constexpr uint8_t SUGGEST_OPINC_CHCKED_ONCE = 1 << 3;
// The node has checked through for lazy new nodes.
constexpr uint8_t SUGGEST_OPINC_CHECKED_THROUGH = 1 << 4;
// Node has rendergroup marked.
constexpr uint8_t APP_RENDER_GROUP_MARKED_MASK = 1 << 7;
// OPINC max ratio for scroll scope(height);
constexpr float HIGHT_RATIO_LIMIT = 0.8f;
// OPINC max ratio for scroll scope(width);
constexpr float WIDTH_RATIO_LIMIT = 1.0f;
// Min area for OPINC
constexpr int32_t MIN_OPINC_AREA = 10000;
} // namespace
namespace OHOS::Ace::NG {

class FrameNode::FrameProxy final : public RecursiveLock {
public:
    struct FrameChildNode {
        RefPtr<UINode> node;
        uint32_t startIndex = 0;
        uint32_t count = 0;
    };

    void Lock() override
    {
        ++inUse_;
    }

    void Unlock() override
    {
        --inUse_;
        if (!inUse_ && delayReset_) {
            auto it = &hostNode_->frameProxy_;
            while ((*it)) {
                if (this == (*it)->prevFrameProxy_.get()) {
                    auto me = std::move((*it)->prevFrameProxy_);
                    (*it)->prevFrameProxy_ = std::move(me->prevFrameProxy_);
                    break;
                }
                it = &(*it)->prevFrameProxy_;
            }
        }
    }

    RecursionGuard GetGuard()
    {
        return RecursionGuard(*this);
    }

    explicit FrameProxy(FrameNode* frameNode) : hostNode_(frameNode)
    {
        prevFrameProxy_ = std::move(hostNode_->frameProxy_);
        if (prevFrameProxy_ && !prevFrameProxy_->needResetChild_) {
            children_ = prevFrameProxy_->children_;
            cursor_ = children_.end();
            if (prevFrameProxy_->cursor_ != prevFrameProxy_->children_.end()) {
                cursor_ = std::find_if(children_.begin(), children_.end(),
                    [this](FrameChildNode& node) { return prevFrameProxy_->cursor_->node == node.node; });
            }
        }
    }

    void Build()
    {
        if (hostNode_ == nullptr || !children_.empty()) {
            return;
        }
        totalCount_ = 0;
        auto children = hostNode_->GetChildren();
        int32_t startIndex = 0;
        int32_t count = 0;
        for (const auto& child : children) {
            count = child->FrameCount();
            child->SetNodeIndexOffset(startIndex, count);
            children_.push_back({ child, startIndex, count });
            startIndex += count;
            totalCount_ += count;
        }
        cursor_ = children_.begin();
    }

    static void AddFrameNode(const RefPtr<UINode>& UiNode, std::list<RefPtr<LayoutWrapper>>& allFrameNodeChildren,
        std::map<uint32_t, RefPtr<LayoutWrapper>>& partFrameNodeChildren, uint32_t& count)
    {
        auto frameNode = AceType::DynamicCast<FrameNode>(UiNode);
        if (frameNode) {
            allFrameNodeChildren.emplace_back(frameNode);
            partFrameNodeChildren[count++] = frameNode;
            return;
        }
        auto lazyForEachNode = AceType::DynamicCast<LazyForEachNode>(UiNode);
        auto repeatVirtualScrollNode = AceType::DynamicCast<RepeatVirtualScrollNode>(UiNode);
        auto repeatVirtualScroll2Node = AceType::DynamicCast<RepeatVirtualScroll2Node>(UiNode);
        if (lazyForEachNode) {
            lazyForEachNode->BuildAllChildren();
        } else if (repeatVirtualScrollNode || repeatVirtualScroll2Node) {
            TAG_LOGE(AceLogTag::ACE_REPEAT, "repeatVirtualScroll not support in non scoll container!");
        } else {
            auto customNode = AceType::DynamicCast<CustomNode>(UiNode);
            if (customNode) {
                customNode->Render();
            }
        }
        for (const auto& child : UiNode->GetChildren()) {
            auto frameNode = AceType::DynamicCast<FrameNode>(child);
            if (frameNode) {
                allFrameNodeChildren.emplace_back(frameNode);
                partFrameNodeChildren[count++] = frameNode;
                continue;
            }
            AddFrameNode(child, allFrameNodeChildren, partFrameNodeChildren, count);
        }
    }

    ChildrenListWithGuard GetAllFrameChildren()
    {
        auto guard = GetGuard();
        if (allFrameNodeChildren_.empty()) {
            Build();
            uint32_t count = 0;
            for (const auto& child : children_) {
                AddFrameNode(child.node, allFrameNodeChildren_, partFrameNodeChildren_, count);
            }
        }
        return ChildrenListWithGuard(allFrameNodeChildren_, *this);
    }

    RefPtr<LayoutWrapper> FindFrameNodeByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
    {
        while (cursor_ != children_.end()) {
            if (cursor_->startIndex > index) {
                cursor_--;
                continue;
            }

            if (cursor_->startIndex + cursor_->count > index) {
                auto frameNode = AceType::DynamicCast<FrameNode>(cursor_->node->GetFrameChildByIndex(
                    index - cursor_->startIndex, needBuild, isCache, addToRenderTree));
                return frameNode;
            }
            cursor_++;
            if (cursor_ == children_.end()) {
                cursor_ = children_.begin();
                return nullptr;
            }
        }
        return nullptr;
    }

    RefPtr<LayoutWrapper> GetFrameNodeByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
    {
        auto itor = partFrameNodeChildren_.find(index);
        if (itor == partFrameNodeChildren_.end()) {
            Build();
            auto child = FindFrameNodeByIndex(index, needBuild, isCache, addToRenderTree);
            if (child && !isCache) {
                partFrameNodeChildren_[index] = child;
            }
            return child;
        }
        return itor->second;
    }

    /**
     * @brief Find child's index in parent's map. Only works on children that are already created and recorded.
     *
     * @param target child LayoutWrapper
     * @return index of children
     */
    int32_t GetChildIndex(const RefPtr<LayoutWrapper>& target) const
    {
        for (auto it : partFrameNodeChildren_) {
            if (it.second == target) {
                return it.first;
            }
        }
        return -1;
    }

    void ResetChildren(bool needResetChild = false)
    {
        if (inUse_) {
            if (SystemProperties::GetLayoutDetectEnabled()) {
                LOGF_ABORT("[%{public}d:%{public}s] reset children while in use",
                    hostNode_->GetId(), hostNode_->GetTag().c_str());
            } else {
                LOGW("[%{public}d:%{public}s] reset children while in use",
                    hostNode_->GetId(), hostNode_->GetTag().c_str());
            }
            delayReset_ = true;
            needResetChild_ = needResetChild;
            hostNode_->frameProxy_ = std::make_unique<FrameProxy>(hostNode_);
            return;
        }
        auto guard = GetGuard();
        delayReset_ = false;
        allFrameNodeChildren_.clear();
        partFrameNodeChildren_.clear();
        totalCount_ = 0;
        if (needResetChild) {
            children_.clear();
            cursor_ = children_.begin();
        }
    }

    void RemoveChildInRenderTree(uint32_t index)
    {
        auto itor = partFrameNodeChildren_.find(index);
        if (itor == partFrameNodeChildren_.end()) {
            return;
        }
        itor->second->SetActive(false);
        partFrameNodeChildren_.erase(itor);
        while (cursor_ != children_.end()) {
            if (cursor_->startIndex > index) {
                cursor_--;
                continue;
            }
            if (cursor_->startIndex + cursor_->count > index) {
                cursor_->node->DoRemoveChildInRenderTree(index - cursor_->startIndex);
                return;
            }
            cursor_++;
            if (cursor_ == children_.end()) {
                cursor_ = children_.begin();
                return;
            }
        }
    }

    void SetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false)
    {
        int32_t startIndex = showCache ? start - cacheStart : start;
        int32_t endIndex = showCache ? end + cacheEnd : end;
        for (auto itor = partFrameNodeChildren_.begin(); itor != partFrameNodeChildren_.end();) {
            int32_t index = itor->first;
            if ((startIndex <= endIndex && index >= startIndex && index <= endIndex) ||
                (startIndex > endIndex && (index <= endIndex || startIndex <= index))) {
                itor++;
            } else {
                itor = partFrameNodeChildren_.erase(itor);
            }
        }
        auto guard = GetGuard();
        for (const auto& child : children_) {
            child.node->DoSetActiveChildRange(
                start - child.startIndex, end - child.startIndex, cacheStart, cacheEnd, showCache);
        }
    }

    void SetActiveChildRange(
        const std::optional<ActiveChildSets>& activeChildSets, const std::optional<ActiveChildRange>& activeChildRange)
    {
        if (!activeChildSets.has_value()) {
            return;
        }
        for (auto itor = partFrameNodeChildren_.begin(); itor != partFrameNodeChildren_.end();) {
            int32_t index = itor->first;
            if (activeChildSets->activeItems.find(index) != activeChildSets->activeItems.end()) {
                itor++;
            } else {
                itor = partFrameNodeChildren_.erase(itor);
            }
        }
        auto guard = GetGuard();
        // repeat node will use active node sets, V1 node(as lazyforeach) will still use active ndoe range.
        for (const auto& child : children_) {
            if (child.node->GetTag() == V2::JS_REPEAT_ETS_TAG) {
                child.node->DoSetActiveChildRange(
                    activeChildSets->activeItems, activeChildSets->cachedItems, child.startIndex);
            } else if (activeChildRange.has_value()) {
                child.node->DoSetActiveChildRange(activeChildRange->start - child.startIndex,
                    activeChildRange->end - child.startIndex, activeChildRange->cacheStart, activeChildRange->cacheEnd);
            }
        }
    }

    void RecycleItemsByIndex(uint32_t start, uint32_t end)
    {
        for (auto it = partFrameNodeChildren_.begin(); it != partFrameNodeChildren_.end();) {
            if (it->first >= start && it->first < end) {
                it = partFrameNodeChildren_.erase(it);
            } else {
                it++;
            }
        }
    }

    void RemoveAllChildInRenderTreeAfterReset()
    {
        Build();
        auto guard = GetGuard();
        for (const auto& child : children_) {
            child.node->DoRemoveChildInRenderTree(0, true);
        }
    }

    void RemoveAllChildInRenderTree()
    {
        SetAllChildrenInactive();
        ResetChildren();
        hostNode_->frameProxy_->RemoveAllChildInRenderTreeAfterReset();
    }

    uint32_t GetTotalCount()
    {
        return totalCount_;
    }

    void SetAllChildrenInactive()
    {
        auto guard = GetGuard();
        for (const auto& child : partFrameNodeChildren_) {
            child.second->SetActive(false);
        }
    }

    std::string Dump()
    {
        if (totalCount_ == 0) {
            return "totalCount is 0";
        }
        std::string info = "FrameChildNode:[";
        auto guard = GetGuard();
        for (const auto& child : children_) {
            info += std::to_string(child.node->GetId());
            info += "-";
            info += std::to_string(child.startIndex);
            info += "-";
            info += std::to_string(child.count);
            info += ",";
        }
        info += "] partFrameNodeChildren:[";
        for (const auto& child : partFrameNodeChildren_) {
            info += std::to_string(child.second->GetHostNode()->GetId());
            info += ",";
        }
        info += "] TotalCount:";
        info += std::to_string(totalCount_);
        return info;
    }

    void SetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
    {
        auto guard = GetGuard();
        for (const auto& child : children_) {
            child.node->OnSetCacheCount(cacheCount, itemConstraint);
        }
    }

private:
    std::list<FrameChildNode> children_;
    std::list<FrameChildNode>::iterator cursor_ = children_.begin();
    std::list<RefPtr<LayoutWrapper>> allFrameNodeChildren_;
    std::map<uint32_t, RefPtr<LayoutWrapper>> partFrameNodeChildren_;
    std::unique_ptr<FrameProxy> prevFrameProxy_;
    int32_t totalCount_ = 0;
    FrameNode* hostNode_ { nullptr };
    uint32_t inUse_ = 0;
    bool delayReset_ = false;
    bool needResetChild_ = false;
}; // namespace OHOS::Ace::NG

FrameNode::FrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot, bool isLayoutNode)
    : UINode(tag, nodeId, isRoot), LayoutWrapper(WeakClaim(this)), pattern_(pattern)
{
    isLayoutNode_ = isLayoutNode;
    frameProxy_ = std::make_unique<FrameProxy>(this);
    renderContext_->InitContext(IsRootNode(), pattern_->GetContextParam(), isLayoutNode);
    paintProperty_ = pattern->CreatePaintProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
    accessibilityProperty_ = pattern->CreateAccessibilityProperty();
    // first create make layout property dirty.
    layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    layoutProperty_->SetHost(WeakClaim(this));
    layoutSeperately_ = true;
    paintProperty_->SetHost(WeakClaim(this));
}

FrameNode::~FrameNode()
{
    ResetPredictNodes();
    for (const auto& destroyCallback : destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    if (removeCustomProperties_) {
        removeCustomProperties_();
        removeCustomProperties_ = nullptr;
    }

    pattern_->DetachFromFrameNode(this);
    if (IsOnMainTree()) {
        OnDetachFromMainTree(false, GetContextWithCheck());
    }
    HandleAreaChangeDestruct();
    CleanupPipelineResources();
    FireOnNodeDestroyCallback();
    FireOnExtraNodeDestroyCallback();
    FireFrameNodeDestructorCallback();
    if (kitNode_) {
        kitNode_->Reset();
    }
}

void FrameNode::CreateEventHubInner()
{
    if (eventHub_ || !pattern_) {
        return;
    }
    eventHub_ = pattern_->CreateEventHub();
    if (eventHub_) {
        eventHub_->AttachHost(WeakClaim(this));
    }
}

RefPtr<FrameNode> FrameNode::CreateFrameNodeWithTree(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    auto newChild = CreateFrameNode(tag, nodeId, pattern, true);
    newChild->SetDepth(1);
    return newChild;
}

RefPtr<FrameNode> FrameNode::GetOrCreateFrameNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return frameNode;
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    return CreateFrameNode(tag, nodeId, pattern);
}

RefPtr<FrameNode> FrameNode::GetOrCreateCommonNode(const std::string& tag, int32_t nodeId, bool isLayoutNode,
    const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto commonNode = GetFrameNode(tag, nodeId);
    if (commonNode) {
        commonNode->isLayoutNode_ = isLayoutNode;
        return commonNode;
    }
    auto pattern = patternCreator ? patternCreator() : MakeRefPtr<Pattern>();
    return CreateCommonNode(tag, nodeId, isLayoutNode, pattern);
}

RefPtr<FrameNode> FrameNode::GetFrameNode(const std::string& tag, int32_t nodeId)
{
    auto frameNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetTag() != tag) {
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = frameNode->GetParent();
        if (parent) {
            parent->RemoveChild(frameNode);
        }
        return nullptr;
    }
    return frameNode;
}

RefPtr<FrameNode> FrameNode::GetFrameNodeOnly(const std::string& tag, int32_t nodeId)
{
    auto frameNode = ElementRegister::GetInstance()->GetSpecificItemById<FrameNode>(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (frameNode->GetTag() != tag) {
        return nullptr;
    }
    return frameNode;
}

RefPtr<FrameNode> FrameNode::CreateFrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

RefPtr<FrameNode> FrameNode::CreateCommonNode(
    const std::string& tag, int32_t nodeId, bool isLayoutNode, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

bool FrameNode::GetIsLayoutNode()
{
    return isLayoutNode_;
}

bool FrameNode::GetIsFind()
{
    return isFind_;
}

void FrameNode::SetIsFind(bool isFind)
{
    isFind_ = isFind;
}

void FrameNode::GetOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& children)
{
    GenerateOneDepthVisibleFrameWithTransition(children);
    if (overlayNode_) {
        children.emplace_back(overlayNode_);
    }
}

void FrameNode::GetOneDepthVisibleFrameWithOffset(std::list<RefPtr<FrameNode>>& children, OffsetF& offset)
{
    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    offset += context->GetPaintRectWithoutTransform().GetOffset();
    GenerateOneDepthVisibleFrameWithOffset(children, offset);
    if (overlayNode_) {
        children.emplace_back(overlayNode_);
    }
}

bool FrameNode::IsSupportDrawModifier()
{
    CHECK_NULL_RETURN(pattern_, false);
    return pattern_->IsSupportDrawModifier();
}

void FrameNode::ProcessOffscreenNode(const RefPtr<FrameNode>& node, bool needRemainActive)
{
    CHECK_NULL_VOID(node);
    if (node->GetRenderContext()) {
        node->GetRenderContext()->SetDrawNode();
    }
    auto task = [weak = AceType::WeakClaim(AceType::RawPtr(node)), needRemainActive]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->ProcessOffscreenTask();
        node->MarkModifyDone();
        node->UpdateLayoutPropertyFlag();
        bool isActive = node->IsActive();
        node->SetActive();
        node->isLayoutDirtyMarked_ = true;
        auto pipeline = node->GetContext();
        if (pipeline) {
            pipeline->FlushUITaskWithSingleDirtyNode(node);
        }
        auto predictLayoutNode = std::move(node->predictLayoutNode_);
        for (auto& node : predictLayoutNode) {
            auto frameNode = node.Upgrade();
            if (frameNode && pipeline) {
                pipeline->FlushUITaskWithSingleDirtyNode(frameNode);
            }
        }
        if (pipeline) {
            pipeline->FlushSyncGeometryNodeTasks();
        }

        auto paintProperty = node->GetPaintProperty<PaintProperty>();
        auto wrapper = node->CreatePaintWrapper();
        if (wrapper != nullptr) {
            wrapper->FlushRender();
        }
        paintProperty->CleanDirty();
        CHECK_NULL_VOID(pipeline);
        pipeline->FlushModifier();
        pipeline->FlushMessages();
        if (needRemainActive) {
            node->SetActive(isActive);
        } else {
            node->SetActive(false);
        }
    };
    auto pipeline = node->GetContext();
    if (pipeline && pipeline->IsLayouting()) {
        pipeline->AddAfterLayoutTask(task);
        return;
    }
    task();
}

void FrameNode::InitializePatternAndContext()
{
    pattern_->AttachToFrameNode(WeakClaim(this));
    accessibilityProperty_->SetHost(WeakClaim(this));
    renderContext_->SetRequestFrame([weak = WeakClaim(this)] {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (frameNode->IsOnMainTree()) {
            auto context = frameNode->GetContext();
            CHECK_NULL_VOID(context);
            context->RequestFrame();
            return;
        }
        frameNode->hasPendingRequest_ = true;
    });
    renderContext_->SetHostNode(WeakClaim(this));
    // Initialize FocusHub
    if (pattern_->GetFocusPattern().GetFocusType() != FocusType::DISABLE) {
        GetOrCreateFocusHub();
    }
}

void FrameNode::DumpLayoutInfo()
{
    auto layoutInfoString = layoutProperty_->LayoutInfoToString();
    if (!layoutInfoString.empty()) {
        DumpLog::GetInstance().AddDesc(std::string("LayoutInfo: ").append(layoutInfoString.c_str()));
    }
    const auto& flexItemProperty = layoutProperty_->GetFlexItemProperty();
    if (flexItemProperty) {
        auto flexLayoutInfoString = flexItemProperty->FlexLayoutInfoToString();
        if (!flexLayoutInfoString.empty()) {
            DumpLog::GetInstance().AddDesc(std::string("FlexLayoutInfo: ").append(flexLayoutInfoString.c_str()));
        }
    }
}

void FrameNode::DumpSafeAreaInfo()
{
    auto&& opts = layoutProperty_->GetSafeAreaExpandOpts();
    if (opts) {
        DumpLog::GetInstance().AddDesc(
            opts->ToString().append(",hostPageId: ").append(std::to_string(GetPageId()).c_str()));
    }
    auto&& ignoreLayoutSafeAreaOpts = layoutProperty_->GetIgnoreLayoutSafeAreaOpts();
    if (ignoreLayoutSafeAreaOpts) {
        DumpLog::GetInstance().AddDesc(ignoreLayoutSafeAreaOpts->ToString());
    }
    if (layoutProperty_->GetSafeAreaInsets()) {
        DumpLog::GetInstance().AddDesc(layoutProperty_->GetSafeAreaInsets()->ToString());
    }
    if (SelfOrParentExpansive()) {
        DumpLog::GetInstance().AddDesc(std::string("selfAdjust: ")
                                           .append(geometryNode_->GetSelfAdjust().ToString().c_str())
                                           .append(",parentAdjust: ")
                                           .append(geometryNode_->GetParentAdjust().ToString().c_str()));
    }
    CHECK_NULL_VOID(GetTag() == V2::PAGE_ETS_TAG);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    DumpLog::GetInstance().AddDesc(std::string("ignoreSafeArea: ")
                                       .append(std::to_string(manager->IsIgnoreSafeArea()))
                                       .append(std::string(", isNeedAvoidWindow: ").c_str())
                                       .append(std::to_string(manager->IsNeedAvoidWindow()))
                                       .append(std::string(", isFullScreen: ").c_str())
                                       .append(std::to_string(manager->IsFullScreen()))
                                       .append(std::string(", isKeyboardAvoidMode").c_str())
                                       .append(std::to_string(static_cast<int32_t>(manager->GetKeyBoardAvoidMode())))
                                       .append(std::string(", isUseCutout").c_str())
                                       .append(std::to_string(manager->GetUseCutout())));
}

void FrameNode::DumpAlignRulesInfo()
{
    auto& flexItemProperties = layoutProperty_->GetFlexItemProperty();
    CHECK_NULL_VOID(flexItemProperties);
    auto rulesToString = flexItemProperties->AlignRulesToString();
    CHECK_NULL_VOID(!rulesToString.empty());
    DumpLog::GetInstance().AddDesc(std::string("AlignRules: ").append(rulesToString));
}

void FrameNode::DumpExtensionHandlerInfo()
{
    if (!extensionHandler_) {
        return;
    }
    DumpLog::GetInstance().AddDesc(std::string("ExtensionHandler: HasCustomerMeasure: ")
                                       .append(extensionHandler_->HasCustomerMeasure() ? "true" : "false")
                                       .append(", HasCustomerLayout: ")
                                       .append(extensionHandler_->HasCustomerLayout() ? "true" : "false"));
}

void FrameNode::DumpCommonInfo()
{
    DumpLog::GetInstance().AddDesc(std::string("FrameRect: ").append(geometryNode_->GetFrameRect().ToString()));
    DumpLog::GetInstance().AddDesc(
        std::string("PaintRect without transform: ").append(renderContext_->GetPaintRectWithoutTransform().ToString()));
    if (renderContext_->GetBackgroundColor()->ColorToString().compare("#00000000") != 0) {
        DumpLog::GetInstance().AddDesc(
            std::string("BackgroundColor: ").append(renderContext_->GetBackgroundColor()->ColorToString()));
    }
    if (geometryNode_->GetParentLayoutConstraint().has_value())
        DumpLog::GetInstance().AddDesc(std::string("ParentLayoutConstraint: ")
                                           .append(geometryNode_->GetParentLayoutConstraint().value().ToString()));
    if (!(NearZero(GetOffsetRelativeToWindow().GetY()) && NearZero(GetOffsetRelativeToWindow().GetX()))) {
        DumpLog::GetInstance().AddDesc(std::string("top: ")
                                           .append(std::to_string(GetOffsetRelativeToWindow().GetY()))
                                           .append(" left: ")
                                           .append(std::to_string(GetOffsetRelativeToWindow().GetX())));
    }
    if (static_cast<int32_t>(IsActive()) != 1) {
        DumpLog::GetInstance().AddDesc(
            std::string("Active: ").append(std::to_string(static_cast<int32_t>(IsActive()))));
    }
    if (IsFreeze()) {
        DumpLog::GetInstance().AddDesc(std::string("Freeze: 1"));
        if (IsUserFreeze()) {
            DumpLog::GetInstance().AddDesc(std::string("UserFreeze: 1"));
        }
    }
    if (static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)) != 0) {
        DumpLog::GetInstance().AddDesc(std::string("Visible: ")
                                           .append(PrintVisibilityDumpInfo().c_str()));
    }
    if (layoutProperty_->GetPaddingProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Padding: ").append(layoutProperty_->GetPaddingProperty()->ToString().c_str()));
    }
    if (layoutProperty_->GetSafeAreaPaddingProperty()) {
        DumpLog::GetInstance().AddDesc(std::string("SafeArea Padding: ")
                                           .append(layoutProperty_->GetSafeAreaPaddingProperty()->ToString().c_str()));
    }
    if (layoutProperty_->GetBorderWidthProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Border: ").append(layoutProperty_->GetBorderWidthProperty()->ToString().c_str()));
    }
    if (renderContext_->HasBorderRadius()) {
        DumpLog::GetInstance().AddDesc(
            std::string("BorderRadius: ").append(renderContext_->GetBorderRadius()->ToString().c_str()));
    }
    if (layoutProperty_->GetMarginProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Margin: ").append(layoutProperty_->GetMarginProperty()->ToString().c_str()));
    }
    if (layoutProperty_->GetLayoutRect()) {
        DumpLog::GetInstance().AddDesc(
            std::string("LayoutRect: ").append(layoutProperty_->GetLayoutRect().value().ToString().c_str()));
    }
    DumpExtensionHandlerInfo();
    DumpSafeAreaInfo();
    if (layoutProperty_->GetCalcLayoutConstraint()) {
        DumpLog::GetInstance().AddDesc(std::string("User defined constraint: ")
                                           .append(layoutProperty_->GetCalcLayoutConstraint()->ToString().c_str()));
    }
    if (!propInspectorId_->empty()) {
        DumpLog::GetInstance().AddDesc(std::string("compid: ").append(propInspectorId_.value_or("")));
    }
    if (layoutProperty_->GetPaddingProperty() || layoutProperty_->GetBorderWidthProperty() ||
        layoutProperty_->GetMarginProperty() || layoutProperty_->GetCalcLayoutConstraint()) {
        DumpLog::GetInstance().AddDesc(
            std::string("ContentConstraint: ")
                .append(layoutProperty_->GetContentLayoutConstraint().has_value()
                            ? layoutProperty_->GetContentLayoutConstraint().value().ToString()
                            : "NA"));
    }
    if (NearZero(renderContext_->GetZIndexValue(ZINDEX_DEFAULT_VALUE))) {
        DumpLog::GetInstance().AddDesc(
            std::string("zIndex: ").append(std::to_string(renderContext_->GetZIndexValue(ZINDEX_DEFAULT_VALUE))));
    }
    if (GetTag() == V2::ROOT_ETS_TAG) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        DumpLog::GetInstance().AddDesc(std::string("dpi: ").append(std::to_string(pipeline->GetDensity())));
    }
    auto layoutPolicy = layoutProperty_->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        std::string layoutPolicyStr = layoutPolicy.value().ToString();
        if (layoutPolicyStr.length() > 0) {
            DumpLog::GetInstance().AddDesc(layoutPolicyStr);
        }
    }
    DumpAlignRulesInfo();
    DumpDragInfo();
    DumpOverlayInfo();
    DumpLayoutInfo();
    if (frameProxy_->Dump().compare("totalCount is 0") != 0) {
        DumpLog::GetInstance().AddDesc(std::string("FrameProxy: ").append(frameProxy_->Dump().c_str()));
    }
    if (isRemoving_) {
        DumpLog::GetInstance().AddDesc(std::string("IsRemoving: True"));
    }
}

void FrameNode::DumpDragInfo()
{
    DumpLog::GetInstance().AddDesc("------------start print dragInfo");
    DumpLog::GetInstance().AddDesc(std::string("Draggable: ")
                                       .append(draggable_ ? "true" : "false")
                                       .append(" UserSet: ")
                                       .append(userSet_ ? "true" : "false")
                                       .append(" CustomerSet: ")
                                       .append(customerSet_ ? "true" : "false"));
    auto dragPreviewStr =
        std::string("DragPreview: Has customNode: ").append(dragPreviewInfo_.customNode ? "YES" : "NO");
    dragPreviewStr.append(" Has pixelMap: ").append(dragPreviewInfo_.pixelMap ? "YES" : "NO");
    dragPreviewStr.append(" extraInfo: ").append(dragPreviewInfo_.extraInfo.c_str());
    dragPreviewStr.append(" inspectorId: ").append(dragPreviewInfo_.inspectorId.c_str());
    DumpLog::GetInstance().AddDesc(dragPreviewStr);
    auto eventHub = GetEventHub<EventHub>();
    DumpLog::GetInstance().AddDesc(std::string("Event: ")
                                       .append("OnDragStart: ")
                                       .append(eventHub && eventHub->HasOnDragStart() ? "YES" : "NO")
                                       .append(" OnDragEnter: ")
                                       .append(eventHub && eventHub->HasOnDragEnter() ? "YES" : "NO")
                                       .append(" OnDragLeave: ")
                                       .append(eventHub && eventHub->HasOnDragLeave() ? "YES" : "NO")
                                       .append(" OnDragMove: ")
                                       .append(eventHub && eventHub->HasOnDragMove() ? "YES" : "NO")
                                       .append(" OnDrop: ")
                                       .append(eventHub && eventHub->HasOnDrop() ? "YES" : "NO")
                                       .append(" OnDragEnd: ")
                                       .append(eventHub && eventHub->HasOnDragEnd() ? "YES" : "NO"));
    DumpLog::GetInstance().AddDesc(std::string("DefaultOnDragStart: ")
                                       .append(eventHub && eventHub->HasDefaultOnDragStart() ? "YES" : "NO")
                                       .append(" CustomerOnDragEnter: ")
                                       .append(eventHub && eventHub->HasCustomerOnDragEnter() ? "YES" : "NO")
                                       .append(" CustomerOnDragLeave: ")
                                       .append(eventHub && eventHub->HasCustomerOnDragLeave() ? "YES" : "NO")
                                       .append(" CustomerOnDragMove: ")
                                       .append(eventHub && eventHub->HasCustomerOnDragMove() ? "YES" : "NO")
                                       .append(" CustomerOnDrop: ")
                                       .append(eventHub && eventHub->HasCustomerOnDrop() ? "YES" : "NO")
                                       .append(" CustomerOnDragEnd: ")
                                       .append(eventHub && eventHub->HasCustomerOnDragEnd() ? "YES" : "NO"));
    DumpLog::GetInstance().AddDesc("------------end print dragInfo");
}

void FrameNode::DumpOnSizeChangeInfo()
{
    for (auto it = onSizeChangeDumpInfos.rbegin(); it != onSizeChangeDumpInfos.rend(); ++it) {
        DumpLog::GetInstance().AddDesc(std::string("onSizeChange Time: ")
                                           .append(ConvertTimestampToStr(it->onSizeChangeTimeStamp))
                                           .append(" lastFrameRect: ")
                                           .append(it->lastFrameRect.ToString())
                                           .append(" currFrameRect: ")
                                           .append(it->currFrameRect.ToString()));
    }
}

void FrameNode::DumpKeyboardShortcutInfo()
{
    auto eventHub = GetEventHub<EventHub>();
    if (!eventHub) {
        return;
    }
    auto keyboardShortcuts = eventHub->GetKeyboardShortcut();
    std::string result;
    for (auto& keyboardShortcut : keyboardShortcuts) {
        result.append("KeyboardShortcut: ")
            .append("keys: ")
            .append(std::to_string(keyboardShortcut.keys))
            .append(" value: ")
            .append(keyboardShortcut.value);
    }
    DumpLog::GetInstance().AddDesc(result);
}

void FrameNode::DumpOverlayInfo()
{
    if (!layoutProperty_->IsOverlayNode()) {
        return;
    }
    DumpLog::GetInstance().AddDesc(std::string("IsOverlayNode: ").append(std::string("true")));
    Dimension offsetX, offsetY;
    layoutProperty_->GetOverlayOffset(offsetX, offsetY);
    DumpLog::GetInstance().AddDesc(
        std::string("OverlayOffset: ").append(offsetX.ToString()).append(std::string(", ")).append(offsetY.ToString()));
}

void FrameNode::DumpSimplifyCommonInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("$rect", GetTransformRectRelativeToWindow().ToBounds().c_str());
    json->Put("$debugLine", "");
}

void FrameNode::DumpPadding(const std::unique_ptr<NG::PaddingProperty>& padding, std::string label,
    std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(padding);
    NG::CalcLength defaultValue = NG::CalcLength(
        Dimension(0, padding->left.value_or(CalcLength()).GetDimension().Unit()));
    if (padding->left.value_or(defaultValue) != defaultValue || padding->right.value_or(defaultValue) != defaultValue ||
        padding->top.value_or(defaultValue) != defaultValue || padding->bottom.value_or(defaultValue) != defaultValue) {
        json->Put(label.c_str(), padding->ToString().c_str());
    }
}

void FrameNode::DumpBorder(const std::unique_ptr<NG::BorderWidthProperty>& border, std::string label,
    std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(border);
    Dimension defaultValue(0, border->leftDimen.value_or(Dimension()).Unit());
    if (border->leftDimen.value_or(defaultValue) != defaultValue ||
        border->rightDimen.value_or(defaultValue) != defaultValue ||
        border->topDimen.value_or(defaultValue) != defaultValue ||
        border->bottomDimen.value_or(defaultValue) != defaultValue) {
        json->Put(label.c_str(), border->ToString().c_str());
    }
}

void FrameNode::DumpSimplifySafeAreaInfo(std::unique_ptr<JsonValue>& json)
{
    auto&& opts = layoutProperty_->GetSafeAreaExpandOpts();
    if (opts && (opts->type != NG::SAFE_AREA_TYPE_NONE || opts->edges != NG::SAFE_AREA_EDGE_NONE)) {
        json->Put("SafeAreaExpandOpts", opts->ToString().c_str());
    }
    if (layoutProperty_->GetSafeAreaInsets()) {
        json->Put("SafeAreaInsets", layoutProperty_->GetSafeAreaInsets()->ToString().c_str());
    }
    if (SelfOrParentExpansive()) {
        RectF defaultValue(0.0, 0.0, 0.0, 0.0);
        auto rect = geometryNode_->GetSelfAdjust();
        auto parentRect = geometryNode_->GetParentAdjust();
        if (rect != defaultValue) {
            json->Put("SelfAdjust", rect.ToString().c_str());
        }
        if (parentRect != defaultValue) {
            json->Put("ParentSelfAdjust", parentRect.ToString().c_str());
        }
    }
    CHECK_NULL_VOID(GetTag() == V2::PAGE_ETS_TAG);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    if (manager->KeyboardSafeAreaEnabled()) {
        json->Put("KeyboardInset: ", manager->GetKeyboardInset().ToString().c_str());
    }
    json->Put("IgnoreSafeArea", manager->IsIgnoreSafeArea());
    json->Put("IsNeedAvoidWindow", manager->IsNeedAvoidWindow());
    json->Put("IsFullScreen", manager->IsFullScreen());
    json->Put("IsKeyboardAvoidMode", static_cast<int32_t>(manager->GetKeyBoardAvoidMode()));
    json->Put("IsUseCutout", manager->GetUseCutout());
}

void FrameNode::DumpSimplifyOverlayInfo(std::unique_ptr<JsonValue>& json)
{
    if (!layoutProperty_->IsOverlayNode()) {
        return;
    }
    json->Put("IsOverlayNode", true);
    Dimension offsetX;
    Dimension offsetY;
    layoutProperty_->GetOverlayOffset(offsetX, offsetY);
    json->Put("OverlayOffset", (offsetX.ToString() + "," + offsetY.ToString()).c_str());
}

bool FrameNode::CheckVisibleOrActive()
{
    if (layoutTags_.find(GetTag()) != layoutTags_.end()) {
        return layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE) == VisibleType::VISIBLE && IsActive();
    } else {
        return true;
    }
}

void FrameNode::DumpSimplifyInfo(std::unique_ptr<JsonValue>& json)
{
    CHECK_NULL_VOID(json);
    DumpSimplifyCommonInfo(json);
    if (pattern_) {
        auto child = JsonUtil::Create();
        pattern_->DumpSimplifyInfo(child);
        json->Put("$attrs", std::move(child));
    }
}

void FrameNode::DumpInfo()
{
    DumpCommonInfo();
    DumpOnSizeChangeInfo();
    DumpKeyboardShortcutInfo();
    if (pattern_) {
        pattern_->DumpInfo();
    }
    if (renderContext_) {
        renderContext_->DumpInfo();
    }
}

void FrameNode::DumpAdvanceInfo()
{
    DumpCommonInfo();
    DumpOnSizeChangeInfo();
    DumpKeyboardShortcutInfo();
    if (pattern_) {
        pattern_->DumpInfo();
        pattern_->DumpAdvanceInfo();
    }
    if (renderContext_) {
        renderContext_->DumpInfo();
        renderContext_->DumpAdvanceInfo();
    }
}

void FrameNode::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap, bool needsRecordData)
{
    if (pattern_) {
        pattern_->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    }
}

bool FrameNode::CheckAutoSave()
{
    if (pattern_) {
        return pattern_->CheckAutoSave();
    }
    return false;
}

void FrameNode::MouseToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    std::string hoverEffect = "HoverEffect.Auto";
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto inputEventHub = eventHub_ ? eventHub_->GetOrCreateInputEventHub() : nullptr;
    if (inputEventHub) {
        hoverEffect = inputEventHub->GetHoverEffectStr();
    }
    json->PutExtAttr("hoverEffect", hoverEffect.c_str(), filter);
}

void FrameNode::TouchToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    bool touchable = true;
    bool monopolizeEvents = false;
    std::string hitTestMode = "HitTestMode.Default";
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto gestureEventHub = eventHub_ ? eventHub_->GetOrCreateGestureEventHub() : nullptr;
    std::vector<DimensionRect> responseRegion;
    std::vector<DimensionRect> mouseResponseRegion;
    if (gestureEventHub) {
        touchable = gestureEventHub->GetTouchable();
        hitTestMode = GestureEventHub::GetHitTestModeStr(gestureEventHub);
        responseRegion = gestureEventHub->GetResponseRegion();
        mouseResponseRegion = gestureEventHub->GetMouseResponseRegion();
        monopolizeEvents = gestureEventHub->GetMonopolizeEvents();
    }
    json->PutExtAttr("touchable", touchable, filter);
    json->PutExtAttr("hitTestBehavior", hitTestMode.c_str(), filter);
    json->PutExtAttr("monopolizeEvents", monopolizeEvents, filter);
    auto jsArr = JsonUtil::CreateArray(true);
    for (int32_t i = 0; i < static_cast<int32_t>(responseRegion.size()); ++i) {
        auto iStr = std::to_string(i);
        jsArr->Put(iStr.c_str(), responseRegion[i].ToJsonString().c_str());
    }
    json->PutExtAttr("responseRegion", jsArr, filter);
    for (int32_t i = 0; i < static_cast<int32_t>(mouseResponseRegion.size()); ++i) {
        auto iStr = std::to_string(i);
        jsArr->Put(iStr.c_str(), mouseResponseRegion[i].ToJsonString().c_str());
    }
    json->PutExtAttr("mouseResponseRegion", jsArr, filter);
}

void FrameNode::GeometryNodeToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    bool hasIdealWidth = false;
    bool hasIdealHeight = false;
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (layoutProperty_ && layoutProperty_->GetCalcLayoutConstraint()) {
        auto selfIdealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
        hasIdealWidth = selfIdealSize.has_value() && selfIdealSize.value().Width().has_value();
        hasIdealHeight = selfIdealSize.has_value() && selfIdealSize.value().Height().has_value();
    }

    auto jsonSize = json->GetValue("size");
    if (!hasIdealWidth) {
        auto idealWidthVpStr = std::to_string(Dimension(geometryNode_->GetFrameSize().Width()).ConvertToVp());
        auto widthStr = (idealWidthVpStr.substr(0, idealWidthVpStr.find(".") + SUBSTR_LENGTH) + DIMENSION_UNIT_VP);
        json->PutExtAttr("width", widthStr.c_str(), filter);
        if (jsonSize) {
            jsonSize->Put("width", widthStr.c_str());
        }
    }

    if (!hasIdealHeight) {
        auto idealHeightVpStr = std::to_string(Dimension(geometryNode_->GetFrameSize().Height()).ConvertToVp());
        auto heightStr = (idealHeightVpStr.substr(0, idealHeightVpStr.find(".") + SUBSTR_LENGTH) + DIMENSION_UNIT_VP);
        json->PutExtAttr("height", heightStr.c_str(), filter);
        if (jsonSize) {
            jsonSize->Put("height", heightStr.c_str());
        }
    }
}

bool FrameNode::IsJsCustomPropertyUpdated() const
{
    for (const auto& iter : customPropertyMap_) {
        if (!iter.second.empty() && iter.second[1] == "0") {
            return false;
        }
    }
    return true;
}

void FrameNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (renderContext_) {
        renderContext_->ToJsonValue(json, filter);
    }
    // scrollable in AccessibilityProperty
    ACE_PROPERTY_TO_JSON_VALUE(accessibilityProperty_, AccessibilityProperty);
    ACE_PROPERTY_TO_JSON_VALUE(layoutProperty_, LayoutProperty);
    ACE_PROPERTY_TO_JSON_VALUE(paintProperty_, PaintProperty);
    ACE_PROPERTY_TO_JSON_VALUE(pattern_, Pattern);
    if (eventHub_) {
        eventHub_->ToJsonValue(json, filter);
    }
    FocusHub::ToJsonValue(GetFocusHub(), json, filter);
    MouseToJsonValue(json, filter);
    TouchToJsonValue(json, filter);
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
#if defined(PREVIEW)
        GeometryNodeToJsonValue(json, filter);
#endif
    } else {
        GeometryNodeToJsonValue(json, filter);
    }
    json->PutFixedAttr("id", propInspectorId_.value_or("").c_str(), filter, FIXED_ATTR_ID);
    json->Put("isLayoutDirtyMarked", isLayoutDirtyMarked_);
    json->Put("isRenderDirtyMarked", isRenderDirtyMarked_);
    json->Put("isMeasureBoundary", isMeasureBoundary_);
    json->Put("hasPendingRequest", hasPendingRequest_);
    json->Put("isFirstBuilding", isFirstBuilding_);
    ExtraCustomPropertyToJsonValue(json, filter);
    if (IsCNode() || !IsJsCustomPropertyUpdated()) {
        auto jsonNode = JsonUtil::Create(true);
        for (const auto &iter : customPropertyMap_) {
            jsonNode->Put(iter.first.c_str(), iter.second[0].c_str());
        }
        if (!customPropertyMap_.empty()) {
            json->Put("customProperty", jsonNode->ToString().c_str());
        }
    } else if (getCustomPropertyMapFunc_) {
        json->Put("customProperty", getCustomPropertyMapFunc_().c_str());
    }
}

void FrameNode::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
    if (layoutProperty_) {
        layoutProperty_->ToTreeJson(json, config);
    } else {
        LayoutProperty lp;
        lp.ToTreeJson(json, config);
    }
    if (paintProperty_) {
        paintProperty_->ToTreeJson(json, config);
    }
    if (pattern_) {
        pattern_->ToTreeJson(json, config);
    }
    auto id = propInspectorId_.value_or("");
    if (!id.empty()) {
        json->Put(TreeKey::ID, id.c_str());
    }
    if (!config.contentOnly) {
        auto eventHub = eventHub_ ? eventHub_->GetOrCreateGestureEventHub() : nullptr;
        if (eventHub) {
            json->Put(TreeKey::CLICKABLE, eventHub->IsClickable());
            json->Put(TreeKey::LONG_CLICKABLE, eventHub->IsLongClickable());
        }
    }
    auto accessibilityProperty = GetAccessibilityProperty<AccessibilityProperty>();
    if (accessibilityProperty) {
        auto accessibilityText = accessibilityProperty->GetAccessibilityText();
        if (!accessibilityText.empty()) {
            json->Put("accessilityContent", accessibilityText.c_str());
        }
    }
}

void FrameNode::FromJson(const std::unique_ptr<JsonValue>& json)
{
    if (renderContext_) {
        renderContext_->FromJson(json);
    }
    accessibilityProperty_->FromJson(json);
    layoutProperty_->FromJson(json);
    paintProperty_->FromJson(json);
    pattern_->FromJson(json);
    if (eventHub_) {
        eventHub_->FromJson(json);
    }
}

void FrameNode::UpdateGeometryTransition()
{
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition) {
        layoutProperty_->UpdateGeometryTransition("");
        layoutProperty_->UpdateGeometryTransition(geometryTransition->GetId());
        MarkDirtyNode();
    }
    auto children = GetChildren();
    for (const auto& child : children) {
        child->UpdateGeometryTransition();
    }
}

void FrameNode::TriggerRsProfilerNodeMountCallbackIfExist()
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    CHECK_NULL_VOID(renderContext_);
    auto callback = LayoutInspector::GetRsProfilerNodeMountCallback();
    if (callback) {
        auto parent = GetParent();
        int32_t parentId = -1;
        if (parent != nullptr) {
            parentId = parent->GetId();
        }
        FrameNodeInfo info { renderContext_->GetNodeId(), GetId(), GetTag(), GetDebugLine(),  parentId };
        callback(info);
    }
#endif
}

void FrameNode::OnAttachToMainTree(bool recursive)
{
    TriggerRsProfilerNodeMountCallbackIfExist();
    if (eventHub_) {
        eventHub_->FireOnAttach();
        eventHub_->FireOnAppear();
        eventHub_->FireEnabledTask();
    }
    renderContext_->OnNodeAppear(recursive);
    pattern_->OnAttachToMainTree();

    if (isActive_ && SystemProperties::GetDeveloperModeOn()) {
        PaintDebugBoundary(SystemProperties::GetDebugBoundaryEnabled());
    }
    bool forceMeasure = !GetPattern()->ReusedNodeSkipMeasure();
    // node may have been measured before AttachToMainTree
    if (geometryNode_->GetParentLayoutConstraint().has_value() && !UseOffscreenProcess() && forceMeasure) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    }
    UINode::OnAttachToMainTree(recursive);
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto predictLayoutNode = std::move(predictLayoutNode_);
    for (auto& node : predictLayoutNode) {
        auto frameNode = node.Upgrade();
        if (frameNode && frameNode->isLayoutDirtyMarked_) {
            context->AddDirtyLayoutNode(frameNode);
        }
    }

    if (isPropertyDiffMarked_) {
        context->AddDirtyPropertyNode(Claim(this));
    }
    if (!hasPendingRequest_) {
        return;
    }
    context->RequestFrame();
    hasPendingRequest_ = false;
}

void FrameNode::OnAttachToBuilderNode(NodeStatus nodeStatus)
{
    pattern_->OnAttachToBuilderNode(nodeStatus);
}

bool FrameNode::RenderCustomChild(int64_t deadline)
{
    if (!pattern_->RenderCustomChild(deadline)) {
        return false;
    }
    return UINode::RenderCustomChild(deadline);
}

void FrameNode::NotifyColorModeChange(uint32_t colorMode)
{
    FireColorNDKCallback();

    if (GetLocalColorMode() != ColorMode::COLOR_MODE_UNDEFINED) {
        return;
    }

    auto parentNode = AceType::DynamicCast<FrameNode>(GetParent());
    bool parentRerender = parentNode ? parentNode->GetRerenderable() : GetRerenderable();
    // bool parentActive = parentNode ? parentNode->IsActive() : true;
    SetRerenderable(parentRerender && ((IsVisible() && IsActive()) || CheckMeasureAnyway()));
    
    if (GetRerenderable()) {
        SetDarkMode(GetContext()->GetColorMode() == ColorMode::DARK);
    }

    if (pattern_) {
        pattern_->OnThemeScopeUpdate(GetThemeScopeId());
        pattern_->OnColorConfigurationUpdate();
        pattern_->OnColorModeChange(colorMode);
    }

    auto frameNode = AceType::DynamicCast<FrameNode>(this);
    if (frameNode && frameNode->GetOverlayNode()) {
        frameNode->GetOverlayNode()->NotifyColorModeChange(colorMode);
    }

    UINode::NotifyColorModeChange(colorMode);
}

void FrameNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if (configurationUpdateCallback_) {
        auto cb = configurationUpdateCallback_;
        cb(configurationChange);
    }
    if (configurationChange.languageUpdate) {
        pattern_->OnLanguageConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (configurationChange.colorModeUpdate) {
        pattern_->OnColorConfigurationUpdate();
        if (colorModeUpdateCallback_) {
            // copy it first in case of changing colorModeUpdateCallback_ in the callback
            auto cb = colorModeUpdateCallback_;
            cb();
        }
        FireColorNDKCallback();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (configurationChange.directionUpdate) {
        pattern_->OnDirectionConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (configurationChange.dpiUpdate) {
        pattern_->OnDpiConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (configurationChange.fontUpdate) {
        pattern_->OnFontConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (configurationChange.iconUpdate) {
        pattern_->OnIconConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (configurationChange.skinUpdate) {
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (configurationChange.fontScaleUpdate) {
        pattern_->OnFontScaleConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    FireFontNDKCallback(configurationChange);
    OnPropertyChangeMeasure();
}

void FrameNode::OnPropertyChangeMeasure() const
{
    auto layoutProperty = GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->OnPropertyChangeMeasure();
}

void FrameNode::MarkDirtyWithOnProChange(PropertyChangeFlag extraFlag)
{
    MarkDirtyNode(extraFlag);
    auto layoutProperty = GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->OnPropertyChangeMeasure();
}

void FrameNode::FireColorNDKCallback()
{
    std::shared_lock<std::shared_mutex> lock(colorModeCallbackMutex_);
    if (ndkColorModeUpdateCallback_) {
        auto colorModeChange = ndkColorModeUpdateCallback_;
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        colorModeChange(context->GetColorMode() == ColorMode::DARK);
    }
}

void FrameNode::SetNDKColorModeUpdateCallback(const std::function<void(int32_t)>&& callback)
{
    std::unique_lock<std::shared_mutex> lock(colorModeCallbackMutex_);
    ndkColorModeUpdateCallback_ = callback;
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    colorMode_ = context->GetColorMode();
}

void FrameNode::FireFontNDKCallback(const ConfigurationChange& configurationChange)
{
    std::shared_lock<std::shared_mutex> lock(fontSizeCallbackMutex_);
    if ((configurationChange.fontScaleUpdate || configurationChange.fontWeightScaleUpdate) && ndkFontUpdateCallback_) {
        auto fontChangeCallback = ndkFontUpdateCallback_;
        auto pipeline = GetContextWithCheck();
        CHECK_NULL_VOID(pipeline);
        fontChangeCallback(pipeline->GetFontScale(), pipeline->GetFontWeightScale());
    }
}

void FrameNode::NotifyVisibleChange(VisibleType preVisibility, VisibleType currentVisibility)
{
    if ((preVisibility != currentVisibility &&
            (preVisibility == VisibleType::GONE || currentVisibility == VisibleType::GONE)) &&
        SelfExpansive()) {
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    pattern_->OnVisibleChange(currentVisibility == VisibleType::VISIBLE);
    UpdateChildrenVisible(preVisibility, currentVisibility);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto colorMode = pipeline->GetColorMode() == ColorMode::DARK ? 1 : 0;
    if (SystemProperties::ConfigChangePerform() && (colorMode != CheckIsDarkMode())) {
        auto parentNode = AceType::DynamicCast<FrameNode>(GetParent());
        if (parentNode && parentNode->GetRerenderable()) {
            pipeline->SetIsSystemColorChange(false);
            SetRerenderable(true);
            NotifyColorModeChange(colorMode);
        }
    }
}

void FrameNode::TryVisibleChangeOnDescendant(VisibleType preVisibility, VisibleType currentVisibility)
{
    auto layoutProperty = GetLayoutProperty();
    if (layoutProperty && layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        return;
    }
    NotifyVisibleChange(preVisibility, currentVisibility);
}

void FrameNode::OnDetachFromMainTree(bool recursive, PipelineContext* context)
{
    for (auto [_, callback] : removeToolbarItemCallbacks_) {
        if (callback) {
            callback();
        }
    }
    auto focusHub = GetFocusHub();
    if (focusHub) {
        auto focusView = focusHub->GetFirstChildFocusView();
        if (focusView) {
            focusView->FocusViewClose(true);
        }
        focusHub->RemoveSelf();
    }
    pattern_->OnDetachFromMainTree();
    if (eventHub_) {
        eventHub_->OnDetachClear();
    }
    CHECK_NULL_VOID(renderContext_);
    renderContext_->OnNodeDisappear(recursive);
    if (context) {
        const auto& safeAreaManager = context->GetSafeAreaManager();
        if (safeAreaManager) {
            safeAreaManager->RemoveRestoreNode(WeakClaim(this));
        }
    }
    auto accessibilityProperty = GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->OnAccessibilityDetachFromMainTree();
}

void FrameNode::SwapDirtyLayoutWrapperOnMainThread(const RefPtr<LayoutWrapper>& dirty)
{
    CHECK_NULL_VOID(dirty);

    // update new layout constrain.
    layoutProperty_->UpdateLayoutConstraint(dirty->GetLayoutProperty());

    // active change flag judge.
    SetActive(dirty->IsActive());
    if (!isActive_) {
        return;
    }

    // update layout size.
    bool frameSizeChange = geometryNode_->GetFrameSize() != dirty->GetGeometryNode()->GetFrameSize();
    bool frameOffsetChange = geometryNode_->GetFrameOffset() != dirty->GetGeometryNode()->GetFrameOffset();
    bool contentSizeChange = geometryNode_->GetContentSize() != dirty->GetGeometryNode()->GetContentSize();
    bool contentOffsetChange = geometryNode_->GetContentOffset() != dirty->GetGeometryNode()->GetContentOffset();

    SetGeometryNode(dirty->GetGeometryNode());

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsRunning(WeakClaim(this))) {
        geometryTransition->DidLayout(dirty);
        if (geometryTransition->IsNodeOutAndActive(WeakClaim(this))) {
            isLayoutDirtyMarked_ = true;
        }
    } else if (frameSizeChange || frameOffsetChange || HasPositionProp() ||
               (pattern_->GetContextParam().has_value() && contentSizeChange)) {
        renderContext_->SyncGeometryProperties(RawPtr(dirty->GetGeometryNode()));
    }

    // clean layout flag.
    layoutProperty_->CleanDirty();
    DirtySwapConfig config { frameSizeChange, frameOffsetChange, contentSizeChange, contentOffsetChange };
    // check if need to paint content.
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_VOID(layoutAlgorithmWrapper);
    config.skipMeasure = layoutAlgorithmWrapper->SkipMeasure() || dirty->SkipMeasureContent();
    config.skipLayout = layoutAlgorithmWrapper->SkipLayout();
    if ((config.skipMeasure == false) && (config.skipLayout == false)) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        if (eventHub_) {
            eventHub_->FireLayoutNDKCallback(pipeline);
        }
        if (GetInspectorId().has_value()) {
            pipeline->OnLayoutCompleted(GetInspectorId()->c_str());
        }
    }
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    needRerender = needRerender || pattern_->OnDirtyLayoutWrapperSwap(dirty, config.skipMeasure, config.skipLayout);
    if (needRerender || CheckNeedRender(paintProperty_->GetPropertyChangeFlag())) {
        MarkDirtyNode(true, true, PROPERTY_UPDATE_RENDER);
    }

    // update border.
    if (layoutProperty_->GetBorderWidthProperty()) {
        if (!renderContext_->HasBorderColor()) {
            BorderColorProperty borderColorProperty;
            borderColorProperty.SetColor(Color::BLACK);
            renderContext_->UpdateBorderColor(borderColorProperty);
        }
        if (!renderContext_->HasBorderStyle()) {
            BorderStyleProperty borderStyleProperty;
            borderStyleProperty.SetBorderStyle(BorderStyle::SOLID);
            renderContext_->UpdateBorderStyle(borderStyleProperty);
        }
        if (!renderContext_->HasDashGap()) {
            BorderWidthProperty dashGapProperty;
            dashGapProperty.SetBorderWidth(Dimension(-1));
            renderContext_->UpdateDashGap(dashGapProperty);
        }
        if (!renderContext_->HasDashWidth()) {
            BorderWidthProperty dashWidthProperty;
            dashWidthProperty.SetBorderWidth(Dimension(-1));
            renderContext_->UpdateDashWidth(dashWidthProperty);
        }
        if (layoutProperty_->GetLayoutConstraint().has_value()) {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(),
                layoutProperty_->GetLayoutConstraint()->percentReference.Width()));
        } else {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth()));
        }
    }

    // update background
    if (builderFunc_) {
        auto builderNode = builderFunc_();
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        if (builderNode) {
            builderNode->MountToParent(columnNode);
        }
        SetBackgroundLayoutConstraint(columnNode);
        renderContext_->CreateBackgroundPixelMap(columnNode);
        builderFunc_ = nullptr;
        backgroundNode_ = columnNode;
    }

    // update focus state
    auto focusHub = GetFocusHub();
    if (focusHub && focusHub->IsCurrentFocus()) {
        focusHub->ClearFocusState(false);
        focusHub->PaintFocusState(false);
    }

    // rebuild child render node.
    RebuildRenderContextTree();
}

void FrameNode::SetMeasureCallback(const std::function<void(RefPtr<Kit::FrameNode>)>& measureCallback)
{
    measureCallback_ = std::move(measureCallback);
}

void FrameNode::SetBackgroundLayoutConstraint(const RefPtr<FrameNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.scaleProperty = ScaleProperty::CreateScaleProperty();
    auto paintRect = renderContext_->GetPaintRectWithoutTransform();
    layoutConstraint.percentReference.SetWidth(paintRect.Width());
    layoutConstraint.percentReference.SetHeight(paintRect.Height());
    layoutConstraint.maxSize.SetWidth(paintRect.Width());
    layoutConstraint.maxSize.SetHeight(paintRect.Height());
    customNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
}

void FrameNode::AdjustGridOffset()
{
    if (!isActive_) {
        return;
    }
    if (layoutProperty_->UpdateGridOffset(Claim(this))) {
        renderContext_->SyncGeometryProperties(RawPtr(GetGeometryNode()));
    }
}

void FrameNode::ClearUserOnAreaChange()
{
    if (eventHub_) {
        eventHub_->ClearUserOnAreaChanged();
    }
}

void FrameNode::SetOnAreaChangeCallback(OnAreaChangedFunc&& callback)
{
    InitLastArea();
    CreateEventHubInner();
    CHECK_NULL_VOID(eventHub_);
    eventHub_->SetOnAreaChanged(std::move(callback));
}

void FrameNode::TriggerOnAreaChangeCallback(uint64_t nanoTimestamp)
{
    if (!IsActive()) {
        if (IsDebugInspectorId()) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnAreaChange Node(%{public}s/%{public}d) is inActive", GetTag().c_str(),
                GetId());
        }
        return;
    }
#ifdef WINDOW_SCENE_SUPPORTED
    auto container = Container::Current();
    if (container && container->IsDynamicRender() &&
        container->GetUIContentType() == UIContentType::DYNAMIC_COMPONENT) {
        DynamicComponentManager::TriggerOnAreaChangeCallback(this, nanoTimestamp);
        return;
    }
#endif
    if (eventHub_ && (eventHub_->HasOnAreaChanged() || eventHub_->HasInnerOnAreaChanged()) && lastFrameRect_ &&
        lastParentOffsetToWindow_) {
        auto currFrameRect = geometryNode_->GetFrameRect();
        if (renderContext_ && renderContext_->GetPositionProperty()) {
            if (renderContext_->GetPositionProperty()->HasPosition()) {
                auto renderPosition = ContextPositionConvertToPX(
                    renderContext_, layoutProperty_->GetLayoutConstraint()->percentReference);
                currFrameRect.SetOffset(
                    { static_cast<float>(renderPosition.first), static_cast<float>(renderPosition.second) });
            }
        }
        bool logFlag = IsDebugInspectorId();
        auto currParentOffsetToWindow =
            CalculateOffsetRelativeToWindow(nanoTimestamp, logFlag) - currFrameRect.GetOffset();
        if (logFlag) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT,
                "OnAreaChange Node(%{public}s/%{public}d) rect:%{public}s lastRect:%{public}s "
                "parentRectToWindow:%{public}s lastParentRectToWindow:%{public}s",
                GetTag().c_str(), GetId(), currFrameRect.ToString().c_str(), (*lastFrameRect_).ToString().c_str(),
                currParentOffsetToWindow.ToString().c_str(), (*lastParentOffsetToWindow_).ToString().c_str());
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnAreaChange End of calculation %{public}s",
                currFrameRect != *lastFrameRect_ || currParentOffsetToWindow != *lastParentOffsetToWindow_
                    ? "non-execution"
                    : "execution");
        }
        eventHub_->HandleOnAreaChange(
            lastFrameRect_, lastParentOffsetToWindow_, currFrameRect, currParentOffsetToWindow);
    }
    pattern_->OnAreaChangedInner();
}

void FrameNode::SetOnSizeChangeCallback(OnSizeChangedFunc&& callback)
{
    if (!lastFrameNodeRect_) {
        lastFrameNodeRect_ = std::make_unique<RectF>();
    }
    CreateEventHubInner();
    CHECK_NULL_VOID(eventHub_);
    eventHub_->SetOnSizeChanged(std::move(callback));
}

void FrameNode::AddInnerOnSizeChangeCallback(int32_t id, OnSizeChangedFunc&& callback)
{
    if (!lastFrameNodeRect_) {
        lastFrameNodeRect_ = std::make_unique<RectF>();
    }
    CreateEventHubInner();
    CHECK_NULL_VOID(eventHub_);
    eventHub_->AddInnerOnSizeChanged(id, std::move(callback));
}

void FrameNode::SetJSFrameNodeOnSizeChangeCallback(OnSizeChangedFunc&& callback)
{
    if (!lastFrameNodeRect_) {
        lastFrameNodeRect_ = std::make_unique<RectF>();
    }
    CreateEventHubInner();
    CHECK_NULL_VOID(eventHub_);
    eventHub_->SetJSFrameNodeOnSizeChangeCallback(std::move(callback));
}

RectF FrameNode::GetRectWithRender()
{
    RectF currFrameRect;
    if (renderContext_) {
        currFrameRect = renderContext_->GetPaintRectWithoutTransform();
    }
    if (renderContext_ && renderContext_->GetPositionProperty()) {
        if (renderContext_->GetPositionProperty()->HasPosition()) {
            auto renderPosition =
                ContextPositionConvertToPX(renderContext_, layoutProperty_->GetLayoutConstraint()->percentReference);
            currFrameRect.SetOffset(
                { static_cast<float>(renderPosition.first), static_cast<float>(renderPosition.second) });
        }
    }
    return currFrameRect;
}

bool FrameNode::CheckAncestorPageShow()
{
    auto pageNode = GetPageNode();
    if (!pageNode) {
        return true;
    }
    return pageNode->GetPattern<PagePattern>()->IsOnShow();
}

void FrameNode::TriggerOnSizeChangeCallback()
{
    if (!IsActive() || !CheckAncestorPageShow()) {
        return;
    }
    if (eventHub_ && (eventHub_->HasOnSizeChanged() || eventHub_->HasInnerOnSizeChanged()) && lastFrameNodeRect_) {
        auto currFrameRect = GetRectWithRender();
        if (currFrameRect.GetSize() != (*lastFrameNodeRect_).GetSize()) {
            onSizeChangeDumpInfo dumpInfo { GetCurrentTimestamp(), *lastFrameNodeRect_, currFrameRect };
            if (onSizeChangeDumpInfos.size() >= SIZE_CHANGE_DUMP_SIZE) {
                onSizeChangeDumpInfos.erase(onSizeChangeDumpInfos.begin());
            }
            onSizeChangeDumpInfos.emplace_back(dumpInfo);
            if (eventHub_->HasOnSizeChanged()) {
                eventHub_->FireOnSizeChanged(*lastFrameNodeRect_, currFrameRect);
            }
            if (eventHub_->HasInnerOnSizeChanged()) {
                eventHub_->FireInnerOnSizeChanged(*lastFrameNodeRect_, currFrameRect);
            }
            eventHub_->FireJSFrameNodeOnSizeChanged(*lastFrameNodeRect_, currFrameRect);
            *lastFrameNodeRect_ = currFrameRect;
        }
    }
}

bool FrameNode::IsFrameDisappear() const
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, true);
    bool isFrameDisappear = !context->GetOnShow() || !IsOnMainTree() || !IsVisible();
    if (isFrameDisappear) {
        return true;
    }
    bool curFrameIsActive = isActive_;
    bool curIsVisible = IsVisible();
    auto parent = GetParent();
    while (parent) {
        auto parentFrame = AceType::DynamicCast<FrameNode>(parent);
        if (!parentFrame) {
            parent = parent->GetParent();
            continue;
        }
        if (!parentFrame->isActive_) {
            curFrameIsActive = false;
            break;
        }
        if (!parentFrame->IsVisible()) {
            curIsVisible = false;
            break;
        }
        parent = parent->GetParent();
    }
    return !curIsVisible || !curFrameIsActive;
}

bool FrameNode::IsFrameDisappear(uint64_t timestamp)
{
    auto context = GetContext();
    CHECK_NULL_RETURN(context, true);
    auto isOnShow = context->GetOnShow();
    auto isOnMainTree = AllowVisibleAreaCheck();
    auto isSelfVisible = IsVisible();
    if (!isSelfVisible) {
        SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::SELF_INVISIBLE);
    }
    if (!isOnMainTree) {
        SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::IS_NOT_ON_MAINTREE);
    }
    if (!isOnShow) {
        SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::BACKGROUND);
    }
    bool isFrameDisappear = !isOnShow || !isOnMainTree || !isSelfVisible;
    if (isFrameDisappear) {
        cachedIsFrameDisappear_ = { timestamp, true };
        return true;
    }
    auto result = IsFrameAncestorDisappear(timestamp);
    if (result) {
        SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::ANCESTOR_INVISIBLE);
    }
    return result;
}

bool FrameNode::IsFrameAncestorDisappear(uint64_t timestamp)
{
    bool curFrameIsActive = isActive_;
    bool curIsVisible = IsVisible();
    bool result = !curIsVisible || !curFrameIsActive;
    RefPtr<FrameNode> parentUi = GetAncestorNodeOfFrame(false);
    if (!parentUi) {
        cachedIsFrameDisappear_ = { timestamp, result };
        return result;
    }

    auto parentIsFrameDisappear = parentUi->cachedIsFrameDisappear_;
    if (parentIsFrameDisappear.first == timestamp) {
        result = result || parentIsFrameDisappear.second;
        cachedIsFrameDisappear_ = { timestamp, result };
        return result;
    }
    result = result || (parentUi->IsFrameAncestorDisappear(timestamp));
    cachedIsFrameDisappear_ = { timestamp, result };
    return result;
}

void FrameNode::TriggerVisibleAreaChangeCallback(uint64_t timestamp, bool forceDisappear)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    CHECK_NULL_VOID(eventHub_);
    ProcessThrottledVisibleCallback(forceDisappear);
    auto hasInnerCallback = eventHub_->HasVisibleAreaCallback(false);
    auto hasUserCallback = eventHub_->HasVisibleAreaCallback(true);
    if (!hasInnerCallback && !hasUserCallback) {
        return;
    }
    auto& visibleAreaUserRatios = eventHub_->GetVisibleAreaRatios(true);
    auto& visibleAreaUserCallback = eventHub_->GetVisibleAreaCallback(true);
    auto& visibleAreaInnerRatios = eventHub_->GetVisibleAreaRatios(false);
    auto& visibleAreaInnerCallback = eventHub_->GetVisibleAreaCallback(false);
    if (forceDisappear || IsFrameDisappear(timestamp)) {
        if (IsDebugInspectorId()) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT,
                "OnVisibleAreaChange Node(%{public}s/%{public}d) lastRatio(User:%{public}s/Inner:%{public}s) "
                "forceDisappear:%{public}d frameDisappear:%{public}d ",
                GetTag().c_str(), GetId(), std::to_string(lastVisibleRatio_).c_str(),
                std::to_string(lastInnerVisibleRatio_).c_str(), forceDisappear, IsFrameDisappear(timestamp));
        }
        if (!NearEqual(lastInnerVisibleRatio_, VISIBLE_RATIO_MIN)) {
            ProcessAllVisibleCallback(visibleAreaInnerRatios, visibleAreaInnerCallback, VISIBLE_RATIO_MIN,
                lastInnerVisibleCallbackRatio_, false, true);
            lastInnerVisibleRatio_ = VISIBLE_RATIO_MIN;
        }
        if (!NearEqual(lastVisibleRatio_, VISIBLE_RATIO_MIN)) {
            ProcessAllVisibleCallback(
                visibleAreaUserRatios, visibleAreaUserCallback, VISIBLE_RATIO_MIN, lastVisibleCallbackRatio_);
            lastVisibleRatio_ = VISIBLE_RATIO_MIN;
        }
        return;
    }
    auto visibleResult = GetCacheVisibleRect(timestamp, IsDebugInspectorId());
    SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::VISIBLE_AREA_CHANGE);
    if (hasInnerCallback) {
        if (isCalculateInnerVisibleRectClip_) {
            ProcessVisibleAreaChangeEvent(visibleResult.innerVisibleRect, visibleResult.innerFrameRect,
                visibleAreaInnerRatios, visibleAreaInnerCallback, false);
        } else {
            ProcessVisibleAreaChangeEvent(visibleResult.visibleRect, visibleResult.frameRect, visibleAreaInnerRatios,
                visibleAreaInnerCallback, false);
        }
    }
    if (hasUserCallback) {
        ProcessVisibleAreaChangeEvent(
            visibleResult.visibleRect, visibleResult.frameRect, visibleAreaUserRatios, visibleAreaUserCallback, true);
    }
}

void FrameNode::ProcessVisibleAreaChangeEvent(const RectF& visibleRect, const RectF& frameRect,
    const std::vector<double>& visibleAreaRatios, VisibleCallbackInfo& visibleAreaCallback, bool isUser)
{
    double currentVisibleRatio =
        std::clamp(CalculateCurrentVisibleRatio(visibleRect, frameRect), VISIBLE_RATIO_MIN, VISIBLE_RATIO_MAX);
    if (IsDebugInspectorId()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT,
            "OnVisibleAreaChange Node(%{public}s/%{public}d) Ratio(cur:%{public}s/last:%{public}s)", GetTag().c_str(),
            GetId(), std::to_string(currentVisibleRatio).c_str(), std::to_string(lastVisibleRatio_).c_str());
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnVisibleAreaChange End of calculation %{public}s",
            NearEqual(currentVisibleRatio, lastVisibleRatio_) ? "non-execution" : "execution");
    }
    if (isUser) {
        if (!NearEqual(currentVisibleRatio, lastVisibleRatio_)) {
            auto lastVisibleCallbackRatio = lastVisibleCallbackRatio_;
            ProcessAllVisibleCallback(
                visibleAreaRatios, visibleAreaCallback, currentVisibleRatio, lastVisibleCallbackRatio);
            lastVisibleRatio_ = currentVisibleRatio;
        }
    } else {
        if (!NearEqual(currentVisibleRatio, lastInnerVisibleRatio_)) {
            auto lastVisibleCallbackRatio = lastInnerVisibleCallbackRatio_;
            ProcessAllVisibleCallback(visibleAreaRatios, visibleAreaCallback, currentVisibleRatio,
                lastVisibleCallbackRatio, false, true);
            lastInnerVisibleRatio_ = currentVisibleRatio;
        }
    }
}

double FrameNode::CalculateCurrentVisibleRatio(const RectF& visibleRect, const RectF& renderRect)
{
    if (visibleRect.IsEmpty() || renderRect.IsEmpty()) {
        return 0.0;
    }
    return visibleRect.Width() * visibleRect.Height() / (renderRect.Width() * renderRect.Height());
}

void FrameNode::ProcessAllVisibleCallback(const std::vector<double>& visibleAreaUserRatios,
    VisibleCallbackInfo& visibleAreaUserCallback, double currentVisibleRatio, double lastVisibleRatio,
    bool isThrottled, bool isInner)
{
    bool isHandled = false;
    bool isVisible = false;
    double* lastVisibleCallbackRatio = isThrottled ? &lastThrottledVisibleCbRatio_ :
        (isInner ? &lastInnerVisibleCallbackRatio_ : &lastVisibleCallbackRatio_);

    for (const auto& callbackRatio : visibleAreaUserRatios) {
        if (GreatNotEqual(currentVisibleRatio, callbackRatio) && LessOrEqual(lastVisibleRatio, callbackRatio)) {
            *lastVisibleCallbackRatio = currentVisibleRatio;
            isVisible = true;
            isHandled = true;
        } else if (LessNotEqual(currentVisibleRatio, callbackRatio) && GreatOrEqual(lastVisibleRatio, callbackRatio)) {
            *lastVisibleCallbackRatio = currentVisibleRatio;
            isVisible = false;
            isHandled = true;
        } else if (NearEqual(callbackRatio, VISIBLE_RATIO_MIN) && NearEqual(currentVisibleRatio, callbackRatio)) {
            *lastVisibleCallbackRatio = VISIBLE_RATIO_MIN;
            currentVisibleRatio = VISIBLE_RATIO_MIN;
            isVisible = false;
            isHandled = true;
        } else if (NearEqual(callbackRatio, VISIBLE_RATIO_MAX) && NearEqual(currentVisibleRatio, callbackRatio)) {
            *lastVisibleCallbackRatio = VISIBLE_RATIO_MAX;
            currentVisibleRatio = VISIBLE_RATIO_MAX;
            isVisible = true;
            isHandled = true;
        }
    }

    auto callback = visibleAreaUserCallback.callback;
    if (isHandled && callback) {
        if (GetTag() == V2::WEB_ETS_TAG) {
            TAG_LOGI(AceLogTag::ACE_UIEVENT, "exp=%{public}d ratio=%{public}s %{public}d-%{public}s reason=%{public}d",
                isVisible, std::to_string(currentVisibleRatio).c_str(), GetId(),
                std::to_string(GetAccessibilityId()).c_str(), static_cast<int32_t>(visibleAreaChangeTriggerReason_));
        }
        callback(isVisible, currentVisibleRatio);
    }
}

void FrameNode::ThrottledVisibleTask()
{
    CHECK_NULL_VOID(eventHub_);
    auto& userRatios = eventHub_->GetThrottledVisibleAreaRatios();
    auto& userCallback = eventHub_->GetThrottledVisibleAreaCallback();
    if (!userCallback.callback) {
        throttledCallbackOnTheWay_ = false;
        return;
    }
    if (!throttledCallbackOnTheWay_) {
        return;
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto visibleAreaRealTime = pipeline->GetVisibleAreaRealTime();
    auto visibleResult = GetCacheVisibleRect(pipeline->GetVsyncTime());
    RectF frameRect = visibleResult.frameRect;
    RectF visibleRect = visibleResult.visibleRect;
    double ratio = IsFrameDisappear() ? VISIBLE_RATIO_MIN
                                      : std::clamp(CalculateCurrentVisibleRatio(visibleRect, frameRect),
                                          VISIBLE_RATIO_MIN, VISIBLE_RATIO_MAX);
    if (visibleAreaRealTime) {
        if (NearEqual(ratio, lastThrottledVisibleRatio_)) {
            throttledCallbackOnTheWay_ = false;
            return;
        }
        ProcessAllVisibleCallback(userRatios, userCallback, ratio, lastThrottledVisibleCbRatio_, true);
        lastThrottledVisibleRatio_ = ratio;
        throttledCallbackOnTheWay_ = false;
        lastThrottledTriggerTime_ = GetCurrentTimestamp();
    } else {
        if (!NearEqual(ratio, lastThrottledVisibleRatio_)) {
            ProcessAllVisibleCallback(userRatios, userCallback, ratio, lastThrottledVisibleCbRatio_, true);
            lastThrottledVisibleRatio_ = ratio;
        }
        throttledCallbackOnTheWay_ = false;
        lastThrottledTriggerTime_ = GetCurrentTimestamp();
    }
}

void FrameNode::ProcessThrottledVisibleCallback(bool forceDisappear)
{
    CHECK_NULL_VOID(eventHub_);
    auto& visibleAreaUserCallback = eventHub_->GetThrottledVisibleAreaCallback();
    CHECK_NULL_VOID(visibleAreaUserCallback.callback);

    if (forceDisappear && !NearEqual(lastThrottledVisibleCbRatio_, VISIBLE_RATIO_MIN)) {
        auto& userRatios = eventHub_->GetThrottledVisibleAreaRatios();
        ProcessAllVisibleCallback(
            userRatios, visibleAreaUserCallback, VISIBLE_RATIO_MIN, lastThrottledVisibleCbRatio_, true);
        return;
    }

    auto task = [weak = WeakClaim(this)]() {
        auto node = weak.Upgrade();
        CHECK_NULL_VOID(node);
        node->ThrottledVisibleTask();
    };

    auto pipeline = GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto executor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(executor);

    if (throttledCallbackOnTheWay_) {
        return;
    }

    throttledCallbackOnTheWay_ = true;
    int64_t interval = GetCurrentTimestamp() - lastThrottledTriggerTime_;
    if (interval < visibleAreaUserCallback.period) {
        executor->PostDelayedTask(std::move(task), TaskExecutor::TaskType::UI, visibleAreaUserCallback.period,
            "ThrottledVisibleChangeCallback", PriorityType::IDLE);
    } else {
        executor->PostTask(
            std::move(task), TaskExecutor::TaskType::UI, "ThrottledVisibleChangeCallback", PriorityType::IDLE);
    }
}

void FrameNode::SetActive(bool active, bool needRebuildRenderContext)
{
    bool activeChanged = false;
    if (active && !isActive_) {
        pattern_->OnActive();
        isActive_ = true;
        activeChanged = true;
    }
    if (!active && isActive_) {
        pattern_->OnInActive();
        isActive_ = false;
        activeChanged = true;
    }
    CHECK_NULL_VOID(activeChanged);
    auto parent = GetAncestorNodeOfFrame(false);
    if (parent) {
        parent->MarkNeedSyncRenderTree();
        if (needRebuildRenderContext) {
            auto pipeline = GetContext();
            CHECK_NULL_VOID(pipeline);
            auto task = [weak = AceType::WeakClaim(AceType::RawPtr(parent))]() {
                auto parent = weak.Upgrade();
                CHECK_NULL_VOID(parent);
                parent->RebuildRenderContextTree();
            };
            pipeline->AddAfterLayoutTask(task);
        }
    }
    if (isActive_ && SystemProperties::GetDeveloperModeOn()) {
        PaintDebugBoundary(SystemProperties::GetDebugBoundaryEnabled());
    }
}

void FrameNode::SetGeometryNode(const RefPtr<GeometryNode>& node)
{
    if (node == nullptr) {
        TAG_LOGW(AceLogTag::ACE_DEFAULT_DOMAIN, "SetGeometryNode failed: tag:%{public}s, id:%{public}d] ",
            GetTag().c_str(), GetId());
    }
    geometryNode_ = node;
}

void FrameNode::SetNodeFreeze(bool isFreeze)
{
    CHECK_NULL_VOID(renderContext_);
    if (SystemProperties::IsPageTransitionFreeze()) {
        renderContext_->UpdateFreeze(isFreeze);
    }
}

void FrameNode::CreateLayoutTask(bool forceUseMainThread, LayoutType layoutTaskType)
{
    if (!isLayoutDirtyMarked_ && (layoutTaskType == LayoutType::NONE)) {
        return;
    }
    SetRootMeasureNode(true);
    UpdateLayoutPropertyFlag();
    SetSkipSyncGeometryNode(false);
    if (layoutProperty_->GetLayoutRect()) {
        SetActive(true, true);
        Measure(std::nullopt);
        Layout();
    } else {
        if (layoutTaskType != LayoutType::LAYOUT_FOR_IGNORE) {
            auto layoutConstraint = GetLayoutConstraint();
            ACE_SCOPED_TRACE_COMMERCIAL("CreateTaskMeasure[%s][self:%d][parent:%d][layoutConstraint:%s]"
                             "[layoutPriority:%d][pageId:%d][depth:%d]",
                GetTag().c_str(), GetId(), GetAncestorNodeOfFrame(false) ? GetAncestorNodeOfFrame(false)->GetId() : 0,
                layoutConstraint.ToString().c_str(), GetLayoutPriority(), GetPageId(), GetDepth());
            SetIgnoreLayoutProcess(layoutTaskType == LayoutType::MEASURE_FOR_IGNORE);
            Measure(layoutConstraint);
            ResetIgnoreLayoutProcess();
        } else {
            // LayoutTask for postponed layouting on ignoreLayoutSafeArea-container node, which should skip measuring.
        }

        {
            ACE_SCOPED_TRACE_COMMERCIAL("CreateTaskLayout[%s][self:%d][parent:%d][layoutPriority:%d]"
                             "[pageId:%d][depth:%d]",
                GetTag().c_str(), GetId(), GetAncestorNodeOfFrame(false) ? GetAncestorNodeOfFrame(false)->GetId() : 0,
                GetLayoutPriority(), GetPageId(), GetDepth());
            SetIgnoreLayoutProcess(layoutTaskType == LayoutType::LAYOUT_FOR_IGNORE);
            Layout();
            ResetIgnoreLayoutProcess();
        }
    }
    SetRootMeasureNode(false);
}

std::optional<UITask> FrameNode::CreateRenderTask(bool forceUseMainThread)
{
    if (!isRenderDirtyMarked_) {
        return std::nullopt;
    }
    auto wrapper = CreatePaintWrapper();
    CHECK_NULL_RETURN(wrapper, std::nullopt);
    auto task = [weak = WeakClaim(this), wrapper, paintProperty = paintProperty_]() {
        auto self = weak.Upgrade();
        ACE_SCOPED_TRACE("FrameNode[%s][id:%d][parentId:%d]::RenderTask", self->GetTag().c_str(),
            self->GetId(), self->GetParent()? self->GetParent()->GetId() : -1);
        auto pipeline = PipelineContext::GetCurrentContext();
        if (pipeline) {
            auto id = pipeline->GetInstanceId();
            ArkUIPerfMonitor::GetPerfMonitor(id)->RecordRenderNode();
        }
        wrapper->FlushRender();
        paintProperty->CleanDirty();
        auto eventHub = self->GetEventHub<NG::EventHub>();
        if (self->GetInspectorId() || (eventHub && eventHub->HasNDKDrawCompletedCallback())) {
            CHECK_NULL_VOID(pipeline);
            pipeline->SetNeedRenderNode(weak);
        }
    };
    if (forceUseMainThread || wrapper->CheckShouldRunOnMain()) {
        return UITask(std::move(task), MAIN_TASK);
    }
    return UITask(std::move(task), wrapper->CanRunOnWhichThread());
}

LayoutConstraintF FrameNode::GetLayoutConstraint() const
{
    if (geometryNode_->GetParentLayoutConstraint().has_value()) {
        return geometryNode_->GetParentLayoutConstraint().value();
    }
    LayoutConstraintF layoutConstraint;
    layoutConstraint.scaleProperty = ScaleProperty::CreateScaleProperty();
    auto rootWidth = PipelineContext::GetCurrentRootWidth();
    auto rootHeight = PipelineContext::GetCurrentRootHeight();
    layoutConstraint.percentReference.SetWidth(rootWidth);
    layoutConstraint.percentReference.SetHeight(rootHeight);
    layoutConstraint.maxSize.SetWidth(rootWidth);
    layoutConstraint.maxSize.SetHeight(rootHeight);
    return layoutConstraint;
}

void FrameNode::UpdateLayoutPropertyFlag()
{
    auto selfFlag = layoutProperty_->GetPropertyChangeFlag();
    if (!CheckUpdateByChildRequest(selfFlag)) {
        return;
    }
    if (CheckForceParentMeasureFlag(selfFlag)) {
        return;
    }
    auto flag = PROPERTY_UPDATE_NORMAL;
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->UpdateLayoutPropertyFlag();
        child->AdjustParentLayoutFlag(flag);
        if (CheckForceParentMeasureFlag(selfFlag)) {
            break;
        }
    }
    if (CheckForceParentMeasureFlag(flag)) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
}

void FrameNode::ForceUpdateLayoutPropertyFlag(PropertyChangeFlag propertyChangeFlag)
{
    layoutProperty_->UpdatePropertyChangeFlag(propertyChangeFlag);
}

void FrameNode::AdjustParentLayoutFlag(PropertyChangeFlag& flag)
{
    flag = flag | layoutProperty_->GetPropertyChangeFlag();
}

RefPtr<LayoutWrapperNode> FrameNode::CreateLayoutWrapper(bool forceMeasure, bool forceLayout)
{
    return UpdateLayoutWrapper(nullptr, forceMeasure, forceLayout);
}

RefPtr<LayoutWrapperNode> FrameNode::UpdateLayoutWrapper(
    RefPtr<LayoutWrapperNode> layoutWrapper, bool forceMeasure, bool forceLayout)
{
    CHECK_NULL_RETURN(layoutProperty_, nullptr);
    CHECK_NULL_RETURN(pattern_, nullptr);
    if (layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE) == VisibleType::GONE) {
        if (!layoutWrapper) {
            layoutWrapper =
                MakeRefPtr<LayoutWrapperNode>(WeakClaim(this), MakeRefPtr<GeometryNode>(), layoutProperty_->Clone());
        } else {
            layoutWrapper->Update(WeakClaim(this), MakeRefPtr<GeometryNode>(), layoutProperty_->Clone());
        }
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(nullptr, true, true));
        isLayoutDirtyMarked_ = false;
        return layoutWrapper;
    }

    pattern_->BeforeCreateLayoutWrapper();
    if (forceMeasure) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }
    if (forceLayout) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    }
    auto flag = layoutProperty_->GetPropertyChangeFlag();
    // It is necessary to copy the layoutProperty property to prevent the layoutProperty property from being
    // modified during the layout process, resulting in the problem of judging whether the front-end setting value
    // changes the next time js is executed.
    if (!layoutWrapper) {
        layoutWrapper =
            MakeRefPtr<LayoutWrapperNode>(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    } else {
        layoutWrapper->Update(WeakClaim(this), geometryNode_->Clone(), layoutProperty_->Clone());
    }
    do {
        if (CheckNeedMeasure(flag) || forceMeasure) {
            layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm()));
            bool forceChildMeasure = CheckMeasureFlag(flag) || CheckMeasureSelfAndChildFlag(flag) || forceMeasure;
            UpdateChildrenLayoutWrapper(layoutWrapper, forceChildMeasure, false);
            break;
        }
        if (CheckNeedLayout(flag) || forceLayout) {
            layoutWrapper->SetLayoutAlgorithm(
                MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm(), true, false));
            UpdateChildrenLayoutWrapper(layoutWrapper, false, false);
            break;
        }
        layoutWrapper->SetLayoutAlgorithm(MakeRefPtr<LayoutAlgorithmWrapper>(nullptr, true, true));
    } while (false);
    // check position flag.
    layoutWrapper->SetOutOfLayout(renderContext_->HasPosition());
    layoutWrapper->SetActive(isActive_);
    layoutWrapper->SetIsOverlayNode(layoutProperty_->IsOverlayNode());
    isLayoutDirtyMarked_ = false;
    return layoutWrapper;
}

void FrameNode::UpdateChildrenLayoutWrapper(const RefPtr<LayoutWrapperNode>& self, bool forceMeasure, bool forceLayout)
{
    const auto& children = GetChildren();
    for (const auto& child : children) {
        child->AdjustLayoutWrapperTree(self, forceMeasure, forceLayout);
    }
}

void FrameNode::AdjustLayoutWrapperTree(const RefPtr<LayoutWrapperNode>& parent, bool forceMeasure, bool forceLayout)
{
    ACE_DCHECK(parent);
    CHECK_NULL_VOID(layoutProperty_);
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsNodeOutAndActive(WeakClaim(this))) {
        return;
    }
    auto layoutWrapper = CreateLayoutWrapper(forceMeasure, forceLayout);
    parent->AppendChild(layoutWrapper, layoutProperty_->IsOverlayNode());
}

RefPtr<ContentModifier> FrameNode::GetContentModifier()
{
    CHECK_NULL_RETURN(pattern_, nullptr);
    auto wrapper = CreatePaintWrapper();
    CHECK_NULL_RETURN(wrapper, nullptr);
    auto paintMethod = pattern_->CreateNodePaintMethod();
    if (!paintMethod || extensionHandler_ || renderContext_->GetAccessibilityFocus().value_or(false)) {
        paintMethod = pattern_->CreateDefaultNodePaintMethod();
    }
    CHECK_NULL_RETURN(paintMethod, nullptr);
    auto contentModifier = DynamicCast<ContentModifier>(paintMethod->GetContentModifier(AceType::RawPtr(wrapper)));
    return contentModifier;
}

RefPtr<PaintWrapper> FrameNode::CreatePaintWrapper()
{
    pattern_->BeforeCreatePaintWrapper();
    isRenderDirtyMarked_ = false;
    if (kitNode_ && kitNode_->GetPattern()) {
        auto method = kitNode_->GetPattern()->CreateNodePaintMethod();
        auto paintWrapper = MakeRefPtr<PaintWrapper>(
            renderContext_, geometryNode_->Clone(), paintProperty_->Clone(), extensionHandler_);
        paintWrapper->SetKitNodePaintMethod(method);
        return paintWrapper;
    }
    auto paintMethod = pattern_->CreateNodePaintMethod();
    if (paintMethod || extensionHandler_ || renderContext_->GetAccessibilityFocus().value_or(false)) {
        // It is necessary to copy the layoutProperty property to prevent the paintProperty_ property from being
        // modified during the paint process, resulting in the problem of judging whether the front-end setting value
        // changes the next time js is executed.
        if (!paintMethod) {
            paintMethod = pattern_->CreateDefaultNodePaintMethod();
        }

        auto paintWrapper = MakeRefPtr<PaintWrapper>(
            renderContext_, geometryNode_->Clone(), paintProperty_->Clone(), extensionHandler_);
        paintWrapper->SetNodePaintMethod(paintMethod);
        return paintWrapper;
    }
    return nullptr;
}

void FrameNode::PostIdleTask(std::function<void(int64_t deadline, bool canUseLongPredictTask)>&& task)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddPredictTask(std::move(task));
}

void FrameNode::UpdateLayoutConstraint(const MeasureProperty& calcLayoutConstraint)
{
    layoutProperty_->UpdateCalcLayoutProperty(calcLayoutConstraint);
}

void FrameNode::RebuildRenderContextTree()
{
    if (!needSyncRenderTree_) {
        return;
    }
    auto pipeline = GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("RebuildRenderContextTree doesn't run on UI thread!");
    }
    frameChildren_.clear();
    std::list<RefPtr<FrameNode>> children;
    // generate full children list, including disappear children.
    GenerateOneDepthVisibleFrameWithTransition(children);
    if (overlayNode_) {
        auto property = overlayNode_->GetLayoutProperty();
        if (property && property->GetVisibilityValue(VisibleType::VISIBLE) == VisibleType::VISIBLE) {
            children.push_back(overlayNode_);
        }
    }
    if (accessibilityFocusPaintNode_) {
        children.push_back(accessibilityFocusPaintNode_);
    }
    for (const auto& child : children) {
        frameChildren_.emplace(child);
    }
    renderContext_->RebuildFrame(this, children);
    pattern_->OnRebuildFrame();
    if (isDeleteRsNode_) {
        auto parentFrameNode = GetParentFrameNode();
        if (parentFrameNode) {
            parentFrameNode->MarkNeedSyncRenderTree();
            parentFrameNode->RebuildRenderContextTree();
        }
    }
    needSyncRenderTree_ = false;
}

void FrameNode::MarkModifyDone()
{
    pattern_->OnModifyDone();
    auto pipeline = PipelineContext::GetCurrentContextSafely();
    if (pipeline) {
        auto privacyManager = pipeline->GetPrivacySensitiveManager();
        if (privacyManager) {
            if (IsPrivacySensitive()) {
                LOGI("store sensitive node, %{public}d", GetId());
                privacyManager->StoreNode(AceType::WeakClaim(this));
            } else {
                privacyManager->RemoveNode(AceType::WeakClaim(this));
            }
        }
    }
    if (!isRestoreInfoUsed_) {
        isRestoreInfoUsed_ = true;
        int32_t restoreId = GetRestoreId();
        if (pipeline && restoreId >= 0) {
            // store distribute node
            pipeline->StoreNode(restoreId, AceType::WeakClaim(this));
            // restore distribute node info
            std::string restoreInfo;
            if (pipeline->GetRestoreInfo(restoreId, restoreInfo)) {
                pattern_->OnRestoreInfo(restoreInfo);
            }
        }
    }
    if (eventHub_) {
        eventHub_->MarkModifyDone();
    }
    renderContext_->OnModifyDone();
#if (defined(__aarch64__) || defined(__x86_64__))
    if (Recorder::IsCacheAvaliable()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask([weak = WeakPtr(pattern_)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnAfterModifyDone();
        });
    }
#endif
}

[[deprecated("using AfterMountToParent")]] void FrameNode::OnMountToParentDone()
{
    pattern_->OnMountToParentDone();
}

void FrameNode::AfterMountToParent()
{
    if (pattern_) {
        pattern_->AfterMountToParent();
    }
}

void FrameNode::FlushUpdateAndMarkDirty()
{
    MarkDirtyNode();
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag)
{
    if (IsFreeze()) {
        // store the flag.
        layoutProperty_->UpdatePropertyChangeFlag(extraFlag);
        paintProperty_->UpdatePropertyChangeFlag(extraFlag);
        return;
    }
    if (CheckNeedMakePropertyDiff(extraFlag)) {
        if (isPropertyDiffMarked_) {
            return;
        }
        auto context = GetContextWithCheck();
        CHECK_NULL_VOID(context);
        context->AddDirtyPropertyNode(Claim(this));
        isPropertyDiffMarked_ = true;
        return;
    }
    MarkDirtyNode(IsMeasureBoundary(), IsRenderBoundary(), extraFlag);
}

void FrameNode::ProcessFreezeNode()
{
    MarkDirtyNode();
}

void FrameNode::OnFreezeStateChange()
{
    if (IsFreeze()) {
        return;
    }
    // unlock freeze, mark dirty to process freeze node.
    auto layoutFlag = layoutProperty_->GetPropertyChangeFlag();
    auto paintFlag = paintProperty_->GetPropertyChangeFlag();
    if (CheckNoChanged(layoutFlag | paintFlag)) {
        return;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddDirtyFreezeNode(this);
}

RefPtr<FrameNode> FrameNode::GetAncestorNodeOfFrame(bool checkBoundary) const
{
    if (checkBoundary && IsWindowBoundary()) {
        return nullptr;
    }
    auto parent = GetParent();
    while (parent) {
        auto parentFrame = DynamicCast<FrameNode>(parent);
        if (parentFrame) {
            return parentFrame;
        }
        parent = parent->GetParent();
    }
    return nullptr;
}

RefPtr<FrameNode> FrameNode::GetPageNode()
{
    if (GetTag() == "page") {
        return Claim(this);
    }
    auto parent = GetParent();
    while (parent && parent->GetTag() != "page") {
        parent = parent->GetParent();
    }
    return AceType::DynamicCast<FrameNode>(parent);
}

RefPtr<FrameNode> FrameNode::GetFirstAutoFillContainerNode()
{
    if (IsAutoFillContainerNode()) {
        return Claim(this);
    }
    auto parent = GetParent();
    while (parent && !parent->IsAutoFillContainerNode()) {
        parent = parent->GetParent();
    }
    return AceType::DynamicCast<FrameNode>(parent);
}

void FrameNode::NotifyFillRequestSuccess(
    RefPtr<ViewDataWrap> viewDataWrap, RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    if (pattern_) {
        pattern_->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
    }
}

void FrameNode::NotifyFillRequestFailed(int32_t errCode, const std::string& fillContent, bool isPopup)
{
    if (pattern_) {
        pattern_->NotifyFillRequestFailed(errCode, fillContent, isPopup);
    }
}

void FrameNode::MarkNeedRenderOnly()
{
    MarkNeedRender(IsRenderBoundary());
}

void FrameNode::MarkNeedRender(bool isRenderBoundary)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    // If it has dirtyLayoutBox, need to mark dirty after layout done.
    paintProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    if (isRenderDirtyMarked_ || isLayoutDirtyMarked_) {
        return;
    }
    isRenderDirtyMarked_ = true;
    if (isRenderBoundary) {
        context->AddDirtyRenderNode(Claim(this));
        return;
    }
    auto parent = GetAncestorNodeOfFrame(false);
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    }
}

bool FrameNode::RequestParentDirty()
{
    auto parent = GetAncestorNodeOfFrame(false);
    CHECK_NULL_RETURN(parent, false);
    parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
    return true;
}

void FrameNode::MarkDirtyNode(bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag)
{
    layoutProperty_->UpdatePropertyChangeFlag(extraFlag);
    paintProperty_->UpdatePropertyChangeFlag(extraFlag);
    auto layoutFlag = layoutProperty_->GetPropertyChangeFlag();
    auto paintFlag = paintProperty_->GetPropertyChangeFlag();
    if (CheckNoChanged(layoutFlag | paintFlag)) {
        return;
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);

    if (CheckNeedRequestMeasureAndLayout(layoutFlag)) {
        if ((!isMeasureBoundary && IsNeedRequestParentMeasure())) {
            if (RequestParentDirty()) {
                return;
            }
        }
        if (isLayoutDirtyMarked_) {
            return;
        }
        isLayoutDirtyMarked_ = true;
        context->AddDirtyLayoutNode(Claim(this));
        return;
    }
    layoutProperty_->CleanDirty();
    MarkNeedRender(isRenderBoundary);
}

bool FrameNode::IsNeedRequestParentMeasure() const
{
    auto layoutFlag = layoutProperty_->GetPropertyChangeFlag();
    if (layoutFlag == PROPERTY_UPDATE_BY_CHILD_REQUEST) {
        const auto& calcLayoutConstraint = layoutProperty_->GetCalcLayoutConstraint();
        if (calcLayoutConstraint && calcLayoutConstraint->selfIdealSize &&
            calcLayoutConstraint->selfIdealSize->IsValid()) {
            return false;
        }
    }
    return CheckNeedRequestParentMeasure(layoutFlag);
}

void FrameNode::OnGenerateOneDepthVisibleFrame(std::list<RefPtr<FrameNode>>& visibleList)
{
    if (isLayoutNode_) {
        UINode::GenerateOneDepthVisibleFrame(visibleList);
        if (overlayNode_) {
            visibleList.emplace_back(overlayNode_);
        }
        return;
    }
    if (isActive_ && IsVisible()) {
        visibleList.emplace_back(Claim(this));
    }
}

void FrameNode::OnGenerateOneDepthAllFrame(std::list<RefPtr<FrameNode>>& allList)
{
    allList.emplace_back(Claim(this));
}

void FrameNode::OnGenerateOneDepthVisibleFrameWithTransition(std::list<RefPtr<FrameNode>>& visibleList)
{
    if (isLayoutNode_) {
        UINode::GenerateOneDepthVisibleFrameWithTransition(visibleList);
        if (overlayNode_) {
            visibleList.emplace_back(overlayNode_);
        }
        return;
    }

    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    // skip if 1.not active or 2.not visible and has no transition out animation.
    if (!isActive_ || (!IsVisible() && !context->HasTransitionOutAnimation())) {
        return;
    }
    visibleList.emplace_back(Claim(this));
}

void FrameNode::OnGenerateOneDepthVisibleFrameWithOffset(std::list<RefPtr<FrameNode>>& visibleList, OffsetF& offset)
{
    if (isLayoutNode_) {
        isFind_ = true;
        offset += GetGeometryNode()->GetFrameOffset();
        UINode::GenerateOneDepthVisibleFrameWithOffset(visibleList, offset);
        if (overlayNode_) {
            visibleList.emplace_back(overlayNode_);
        }
        return;
    }

    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    // skip if 1.not active or 2.not visible and has no transition out animation.
    if (!isActive_ || (!IsVisible() && !context->HasTransitionOutAnimation())) {
        return;
    }
    visibleList.emplace_back(Claim(this));
}

bool FrameNode::IsMeasureBoundary()
{
    return isMeasureBoundary_ || pattern_->IsMeasureBoundary();
}

bool FrameNode::IsRenderBoundary()
{
    return pattern_->IsRenderBoundary();
}

const RefPtr<Pattern>& FrameNode::GetPattern() const
{
    return pattern_;
}

bool FrameNode::IsAtomicNode() const
{
    if (kitNode_ && kitNode_->GetPattern()) {
        return kitNode_->GetPattern()->IsAtomicNode();
    }
    return pattern_->IsAtomicNode();
}

HitTestMode FrameNode::GetHitTestMode() const
{
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    return gestureHub ? gestureHub->GetHitTestMode() : HitTestMode::HTMDEFAULT;
}

void FrameNode::SetHitTestMode(HitTestMode mode)
{
    auto gestureHub = GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(mode);
}

bool FrameNode::GetTouchable() const
{
    CHECK_NULL_RETURN(eventHub_, true);
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetTouchable() : true;
}

bool FrameNode::GetMonopolizeEvents() const
{
    CHECK_NULL_RETURN(eventHub_, false);
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetMonopolizeEvents() : false;
}

// get paint rect include graphic properties
RectF FrameNode::GetPaintRectWithTransform() const
{
    return renderContext_->GetPaintRectWithTransform();
}

VectorF FrameNode::GetTransformScale() const
{
    return renderContext_->GetTransformScaleValue({ 1.0f, 1.0f });
}

bool FrameNode::IsPaintRectWithTransformValid()
{
    auto& paintRectWithTransform = GetOrRefreshMatrixFromCache().paintRectWithTransform;
    if (NearZero(paintRectWithTransform.Width()) || NearZero(paintRectWithTransform.Height())) {
        return true;
    }
    return false;
}

bool FrameNode::IsOutOfTouchTestRegion(const PointF& parentRevertPoint, const TouchEvent& touchEvent,
    std::vector<RectF>* regionList)
{
    bool isInChildRegion = false;
    auto paintRect = renderContext_->GetPaintRectWithoutTransform();
    if (pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent)) {
        paintRect = pattern_->ExpandDefaultResponseRegion(paintRect);
    }
    std::vector<RectF> responseRegionList;
    if (regionList) {
        responseRegionList = *regionList;
    } else {
        responseRegionList = GetResponseRegionList(paintRect, static_cast<int32_t>(touchEvent.sourceType));
    }

    auto revertPoint = parentRevertPoint;
    MapPointTo(revertPoint, GetOrRefreshMatrixFromCache().revertMatrix);
    auto subRevertPoint = revertPoint - paintRect.GetOffset();
    auto clip = renderContext_->GetClipEdge().value_or(false);
    if (!InResponseRegionList(revertPoint, responseRegionList) || !GetTouchable()) {
        if (clip) {
            return true;
        }
        for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
            const auto& child = iter->Upgrade();
            if (child && !child->IsOutOfTouchTestRegion(subRevertPoint, touchEvent)) {
                isInChildRegion = true;
                break;
            }
        }
        if (!isInChildRegion) {
            return true;
        }
    }
    return false;
}

void FrameNode::AddJudgeToTargetComponent(RefPtr<TargetComponent>& targetComponent)
{
    CHECK_NULL_VOID(eventHub_);
    auto gestureHub = eventHub_->GetGestureEventHub();
    if (gestureHub) {
        auto callback = gestureHub->GetOnGestureJudgeBeginCallback();
        targetComponent->SetOnGestureJudgeBegin(std::move(callback));
        auto callbackNative = gestureHub->GetOnGestureJudgeNativeBeginCallback();
        if (callbackNative) {
            targetComponent->SetOnGestureJudgeNativeBegin(std::move(callbackNative));
        }

        if (!targetComponent->IsInnerNodeGestureRecognizerJudgeSet()) {
            auto gestureRecognizerJudgeCallback = gestureHub->GetOnGestureRecognizerJudgeBegin();
            targetComponent->SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeCallback));
        }

        auto pattern = GetPattern();
        if (pattern) {
            if (GetExposeInnerGestureFlag()) {
                auto gestureRecognizerJudgeCallback = gestureHub->GetOnGestureRecognizerJudgeBegin();
                pattern->AddInnerOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeCallback));
            } else {
                pattern->RecoverInnerOnGestureRecognizerJudgeBegin();
            }
        }
    }
}

void FrameNode::AddNodeToRegisterTouchTest()
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto eventMgr = context->GetEventManager();
    CHECK_NULL_VOID(eventMgr);
    auto gestureEventHub = GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureEventHub);
    CHECK_NULL_VOID(gestureEventHub->GetOnTouchTestDoneCallbackForInner());
    eventMgr->AddTouchDoneFrameNode(AceType::WeakClaim(this));
}

RectF FrameNode::CheckResponseRegionForStylus(RectF& rect, const TouchEvent& touchEvent)
{
    if (!pattern_ || !pattern_->IsResponseRegionExpandingNeededForStylus(touchEvent)) {
        return rect;
    }
    return pattern_->ExpandDefaultResponseRegion(rect);
}

HitTestResult FrameNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    auto& cacheMatrixInfo = GetOrRefreshMatrixFromCache();
    auto paintRect = cacheMatrixInfo.paintRectWithTransform;
    if (!isActive_) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "%{public}s/%{public}d is inActive, needn't do touch test. Rect is %{public}s",
            GetTag().c_str(), GetId(), paintRect.ToString().c_str());
        int32_t parentId = -1;
        auto parent = GetAncestorNodeOfFrame(true);
        if (parent) {
            parentId = parent->GetId();
        }
        AddFrameNodeSnapshot(true, parentId, std::vector<RectF>(), EventTreeType::TOUCH);

        return HitTestResult::OUT_OF_REGION;
    }

    if (eventHub_ && !eventHub_->IsEnabled()) {
        if (hasBindTips_) {
            TipsTouchTest(globalPoint, parentLocalPoint, parentRevertPoint, touchRestrict, result,
                responseLinkResult, isDispatch);
        }
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "%{public}s/%{public}d eventHub not enabled, needn't do touch test",
            GetTag().c_str(), GetId());
        return HitTestResult::OUT_OF_REGION;
    }

    auto origRect = renderContext_->GetPaintRectWithoutTransform();
    auto localMat = cacheMatrixInfo.localMatrix;
    if (!touchRestrict.touchEvent.isMouseTouchTest) {
        localMat_ = localMat;
    }

    int32_t parentId = -1;
    auto parent = GetAncestorNodeOfFrame(true);
    if (parent) {
        parentId = parent->GetId();
    }
    auto checkedResponseRegionForStylus = CheckResponseRegionForStylus(origRect, touchRestrict.touchEvent);
    auto responseRegionList =
        GetResponseRegionList(checkedResponseRegionForStylus, static_cast<int32_t>(touchRestrict.sourceType));
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "TouchTest: point is " SEC_PLD(%{public}s) " in %{public}s, depth: %{public}d",
            SEC_PARAM(parentRevertPoint.ToString().c_str()), GetTag().c_str(), GetDepth());
        for ([[maybe_unused]] const auto& rect : responseRegionList) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "TouchTest: responseRegionList is " SEC_PLD(%{public}s)
                ", point is " SEC_PLD(%{public}s),
                SEC_PARAM(rect.ToString().c_str()), SEC_PARAM(parentRevertPoint.ToString().c_str()));
        }
    }
    {
        ACE_DEBUG_SCOPED_TRACE("FrameNode::IsOutOfTouchTestRegion");
        bool isOutOfRegion = IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent, &responseRegionList);
        AddFrameNodeSnapshot(!isOutOfRegion, parentId, responseRegionList, touchRestrict.touchTestType);
        if ((!isDispatch) && isOutOfRegion) {
            return HitTestResult::OUT_OF_REGION;
        }
    }

    RefPtr<TargetComponent> targetComponent;
    if (targetComponent_.Upgrade()) {
        targetComponent = targetComponent_.Upgrade();
    } else {
        targetComponent = MakeRefPtr<TargetComponent>();
        targetComponent_ = targetComponent;
    }
    targetComponent->SetNode(WeakClaim(this));

    HitTestResult testResult = HitTestResult::OUT_OF_REGION;
    bool preventBubbling = false;
    // Child nodes are repackaged into gesture groups (parallel gesture groups, exclusive gesture groups, etc.)
    // based on the gesture attributes set by the current parent node (high and low priority, parallel gestures,
    // etc.), the newComingTargets is the template object to collect child nodes gesture and used by gestureHub to
    // pack gesture group.
    TouchTestResult newComingTargets;
    auto tmp = parentLocalPoint - paintRect.GetOffset();
    auto preLocation = tmp;
    renderContext_->GetPointWithTransform(tmp);
    const auto localPoint = tmp;
    auto localTransformOffset = preLocation - localPoint;

    auto revertPoint = parentRevertPoint;
    MapPointTo(revertPoint, cacheMatrixInfo.revertMatrix);
    auto subRevertPoint = revertPoint - origRect.GetOffset();
    bool consumed = false;

    HitTestMode onTouchInterceptresult = HitTestMode::HTMDEFAULT;
    if (touchRestrict.inputEventType != InputEventType::MOUSE_BUTTON &&
            touchRestrict.touchEvent.type != TouchType::HOVER_ENTER) {
        onTouchInterceptresult = TriggerOnTouchIntercept(touchRestrict.touchEvent);
    }
    TouchResult touchRes;
    if (onTouchInterceptresult != HitTestMode::HTMBLOCK) {
        std::vector<TouchTestInfo> touchInfos;
        CollectTouchInfos(globalPoint, subRevertPoint, touchInfos);
        touchRes = GetOnChildTouchTestRet(touchInfos);
        if ((touchRes.strategy != TouchTestStrategy::DEFAULT) && touchRes.id.empty()) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "onChildTouchTest result is: "
                "id = " SEC_PLD(%{public}s) ", strategy = %{public}d.",
                SEC_PARAM(touchRes.id.c_str()), static_cast<int32_t>(touchRes.strategy));
            touchRes.strategy = TouchTestStrategy::DEFAULT;
        }

        auto childNode = GetDispatchFrameNode(touchRes);
        if (childNode != nullptr) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, SEC_PLD(%{public}s) " do TouchTest, parameter isDispatch is true.",
                SEC_PARAM(childNode->GetInspectorId()->c_str()));
            auto hitResult = childNode->TouchTest(globalPoint, localPoint, subRevertPoint, touchRestrict,
                newComingTargets, touchId, responseLinkResult, true);
            if (touchRes.strategy == TouchTestStrategy::FORWARD ||
                touchRes.strategy == TouchTestStrategy::FORWARD_COMPETITION) {
                touchRestrict.childTouchTestList.emplace_back(touchRes.id);
            }
            if (hitResult == HitTestResult::STOP_BUBBLING) {
                preventBubbling = true;
                consumed = true;
            }

            if (hitResult == HitTestResult::BUBBLING) {
                consumed = true;
            }
        }
    }

    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        if (GetHitTestMode() == HitTestMode::HTMBLOCK) {
            break;
        }
        if (onTouchInterceptresult != HitTestMode::HTMBLOCK) {
            if (touchRes.strategy == TouchTestStrategy::FORWARD) {
                break;
            }
        }

        const auto& child = iter->Upgrade();
        if (!child) {
            continue;
        }
        if (onTouchInterceptresult != HitTestMode::HTMBLOCK) {
            std::string id;
            if (child->GetInspectorId().has_value()) {
                id = child->GetInspectorId().value();
            }
            if (touchRes.strategy == TouchTestStrategy::FORWARD_COMPETITION && touchRes.id == id) {
                continue;
            }
        }

        auto childHitResult = child->TouchTest(
            globalPoint, localPoint, subRevertPoint, touchRestrict, newComingTargets, touchId, responseLinkResult);
        if (childHitResult == HitTestResult::STOP_BUBBLING) {
            preventBubbling = true;
            consumed = true;
            if ((child->GetHitTestMode() == HitTestMode::HTMBLOCK) ||
                (child->GetHitTestMode() == HitTestMode::HTMDEFAULT) ||
                (child->GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ||
                ((child->GetHitTestMode() != HitTestMode::HTMTRANSPARENT) && IsExclusiveEventForChild())) {
                break;
            }
        }

        // In normal process, the node block the brother node.
        if (childHitResult == HitTestResult::BUBBLING &&
            ((child->GetHitTestMode() == HitTestMode::HTMDEFAULT) ||
                (child->GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ||
                ((child->GetHitTestMode() != HitTestMode::HTMTRANSPARENT) && IsExclusiveEventForChild()))) {
            consumed = true;
            break;
        }
    }

    AddJudgeToTargetComponent(targetComponent);
    AddNodeToRegisterTouchTest();

    // first update HitTestResult by children status.
    if (consumed) {
        testResult = preventBubbling ? HitTestResult::STOP_BUBBLING : HitTestResult::BUBBLING;
        consumed = false;
    } else if (GetHitTestMode() == HitTestMode::HTMBLOCK) {
        testResult = HitTestResult::STOP_BUBBLING;
    }

    if (!preventBubbling && (GetHitTestMode() != HitTestMode::HTMNONE) &&
        (isDispatch || (InResponseRegionList(revertPoint, responseRegionList)))) {
        pattern_->OnTouchTestHit(touchRestrict.hitTestType);
        consumed = true;
        if (touchRestrict.hitTestType == SourceType::TOUCH) {
            auto gestureHub = GetOrCreateGestureEventHub();
            if (gestureHub) {
                TouchTestResult finalResult;
                ResponseLinkResult newComingResponseLinkTargets;
                const auto coordinateOffset = globalPoint - localPoint - localTransformOffset;
                preventBubbling = gestureHub->ProcessTouchTestHit(coordinateOffset, touchRestrict, newComingTargets,
                    finalResult, touchId, localPoint, targetComponent, newComingResponseLinkTargets);
                newComingTargets.swap(finalResult);
                TriggerShouldParallelInnerWith(newComingResponseLinkTargets, responseLinkResult);
                responseLinkResult.splice(responseLinkResult.end(), std::move(newComingResponseLinkTargets));
            }
        } else if (touchRestrict.hitTestType == SourceType::MOUSE) {
            preventBubbling = ProcessMouseTestHit(globalPoint, localPoint, touchRestrict, newComingTargets);
        }
    }

    result.splice(result.end(), std::move(newComingTargets));
    if (touchRestrict.hitTestType == SourceType::TOUCH) {
        // combine into exclusive recognizer group.
        auto gestureHub = GetOrCreateGestureEventHub();
        if (gestureHub) {
            gestureHub->CombineIntoExclusiveRecognizer(globalPoint, localPoint, result, touchId);
        }
    }

    // consumed by children and return result.
    if (!consumed) {
        return testResult;
    }

    if (testResult == HitTestResult::OUT_OF_REGION) {
        // consume only by self.
        if (preventBubbling) {
            return HitTestResult::STOP_BUBBLING;
        }
        return (GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ? HitTestResult::SELF_TRANSPARENT
                                                                      : HitTestResult::BUBBLING;
    }
    // consume by self and children.
    return testResult;
}

void FrameNode::TipsTouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result,
    ResponseLinkResult& responseLinkResult, bool isDispatch)
{
    auto& cacheMatrixInfo = GetOrRefreshMatrixFromCache();
    auto paintRect = cacheMatrixInfo.paintRectWithTransform;
    auto defaultResponseRegion = renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList =
        GetResponseRegionList(defaultResponseRegion, static_cast<int32_t>(touchRestrict.sourceType));
    RefPtr<TargetComponent> targetComponent = targetComponent_.Upgrade();
    if (!targetComponent) {
        targetComponent = MakeRefPtr<TargetComponent>();
        targetComponent_ = targetComponent;
    }
    targetComponent->SetNode(WeakClaim(this));
    TouchTestResult newComingTargets;
    auto tmp = parentLocalPoint - paintRect.GetOffset();
    renderContext_->GetPointWithTransform(tmp);
    const auto localPoint = tmp;
    auto revertPoint = parentRevertPoint;
    if ((GetHitTestMode() != HitTestMode::HTMNONE) &&
        (isDispatch || (InResponseRegionList(revertPoint, responseRegionList)))) {
        if (touchRestrict.hitTestType == SourceType::MOUSE) {
            ProcessTipsMouseTestHit(globalPoint, localPoint, touchRestrict, newComingTargets);
        }
    }
    result.splice(result.end(), std::move(newComingTargets));
}

bool FrameNode::ProcessMouseTestHit(const PointF& globalPoint, const PointF& localPoint,
    TouchRestrict& touchRestrict, TouchTestResult& newComingTargets)
{
    CHECK_NULL_RETURN(eventHub_, false);
    auto mouseHub = eventHub_->GetInputEventHub();
    if (!mouseHub) {
        return false;
    }

    const auto coordinateOffset = globalPoint - localPoint;
    if (touchRestrict.touchEvent.IsPenHoverEvent()) {
        return mouseHub->ProcessPenHoverTestHit(coordinateOffset, newComingTargets);
    }

    return mouseHub->ProcessMouseTestHit(coordinateOffset, newComingTargets);
}

bool FrameNode::ProcessTipsMouseTestHit(const PointF& globalPoint, const PointF& localPoint,
    TouchRestrict& touchRestrict, TouchTestResult& newComingTargets)
{
    CHECK_NULL_RETURN(eventHub_, false);
    auto mouseHub = eventHub_->GetInputEventHub();
    if (!mouseHub) {
        return false;
    }
    const auto coordinateOffset = globalPoint - localPoint;
    return mouseHub->ProcessTipsMouseTestHit(coordinateOffset, newComingTargets);
}

std::vector<RectF> FrameNode::GetResponseRegionList(const RectF& rect, int32_t sourceType)
{
    std::vector<RectF> responseRegionList;
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    if (!gestureHub) {
        responseRegionList.emplace_back(rect);
        return responseRegionList;
    }
    auto scaleProperty = ScaleProperty::CreateScaleProperty(GetContext());
    bool isMouseEvent = (static_cast<SourceType>(sourceType) == SourceType::MOUSE);
    if (isMouseEvent) {
        if (gestureHub->GetResponseRegion().empty() && (gestureHub->GetMouseResponseRegion().empty())) {
            responseRegionList.emplace_back(rect);
            return responseRegionList;
        }
    } else {
        if (gestureHub->GetResponseRegion().empty()) {
            responseRegionList.emplace_back(rect);
            return responseRegionList;
        }
    }

    if (isMouseEvent && (!gestureHub->GetMouseResponseRegion().empty())) {
        for (const auto& region : gestureHub->GetMouseResponseRegion()) {
            auto x = ConvertToPx(region.GetOffset().GetX(), scaleProperty, rect.Width());
            auto y = ConvertToPx(region.GetOffset().GetY(), scaleProperty, rect.Height());
            auto width = ConvertToPx(region.GetWidth(), scaleProperty, rect.Width());
            auto height = ConvertToPx(region.GetHeight(), scaleProperty, rect.Height());
            if (!x.has_value() || !y.has_value() || !width.has_value() || !height.has_value()) {
                continue;
            }
            RectF mouseRegion(rect.GetOffset().GetX() + x.value(), rect.GetOffset().GetY() + y.value(), width.value(),
                height.value());
            responseRegionList.emplace_back(mouseRegion);
        }
        return responseRegionList;
    }
    for (const auto& region : gestureHub->GetResponseRegion()) {
        auto x = ConvertToPx(region.GetOffset().GetX(), scaleProperty, rect.Width());
        auto y = ConvertToPx(region.GetOffset().GetY(), scaleProperty, rect.Height());
        auto width = ConvertToPx(region.GetWidth(), scaleProperty, rect.Width());
        auto height = ConvertToPx(region.GetHeight(), scaleProperty, rect.Height());
        if (!x.has_value() || !y.has_value() || !width.has_value() || !height.has_value()) {
            continue;
        }
        RectF responseRegion(
            rect.GetOffset().GetX() + x.value(), rect.GetOffset().GetY() + y.value(), width.value(), height.value());
        responseRegionList.emplace_back(responseRegion);
    }
    return responseRegionList;
}

std::vector<RectF> FrameNode::GetResponseRegionListForRecognizer(int32_t sourceType)
{
    auto paintRect = renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList = GetResponseRegionList(paintRect, sourceType);
    return responseRegionList;
}

std::vector<RectF> FrameNode::GetResponseRegionListForTouch(const RectF& windowRect)
{
    ACE_LAYOUT_TRACE_BEGIN("GetResponseRegionListForTouch");
    std::vector<RectF> responseRegionList;
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    if (!gestureHub) {
        ACE_LAYOUT_TRACE_END()
        return responseRegionList;
    }
    if (!renderContext_) {
        ACE_LAYOUT_TRACE_END()
        return responseRegionList;
    }
    bool isAccessibilityClickable = gestureHub->IsAccessibilityClickable();
    if (!isAccessibilityClickable) {
        ACE_LAYOUT_TRACE_END()
        return responseRegionList;
    }
    auto offset = GetPositionToScreenWithTransform();
    auto rect = renderContext_->GetPaintRectWithoutTransform();
    RectF rectToScreen{offset.GetX(), offset.GetY(), rect.Width(), rect.Height()};
    if (rectToScreen.Left() >= windowRect.Right() || rectToScreen.Right() <= windowRect.Left() ||
        rectToScreen.Top() >= windowRect.Bottom() || rectToScreen.Bottom() <= windowRect.Top()) {
        ACE_LAYOUT_TRACE_END()
        return responseRegionList;
    }
    if (gestureHub->GetResponseRegion().empty()) {
        RectF rectToScreen{round(offset.GetX()), round(offset.GetY()), round(rect.Width()), round(rect.Height())};
        responseRegionList.emplace_back(rectToScreen);
        ACE_LAYOUT_TRACE_END()
        return responseRegionList;
    }

    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    for (const auto& region : gestureHub->GetResponseRegion()) {
        auto x = ConvertToPx(region.GetOffset().GetX(), scaleProperty, rect.Width());
        auto y = ConvertToPx(region.GetOffset().GetY(), scaleProperty, rect.Height());
        auto width = ConvertToPx(region.GetWidth(), scaleProperty, rect.Width());
        auto height = ConvertToPx(region.GetHeight(), scaleProperty, rect.Height());
        if (!x.has_value() || !y.has_value() || !width.has_value() || !height.has_value()) {
            continue;
        }
        RectF responseRegion(round(offset.GetX() + x.value()), round(offset.GetY() + y.value()),
            round(width.value()), round(height.value()));
        responseRegionList.emplace_back(responseRegion);
    }
    ACE_LAYOUT_TRACE_END()
    return responseRegionList;
}

void FrameNode::GetResponseRegionListByTraversal(std::vector<RectF>& responseRegionList, const RectF& windowRect)
{
    auto rootRegionList = GetResponseRegionListForTouch(windowRect);
    if (!rootRegionList.empty()) {
        for (auto rect : rootRegionList) {
            responseRegionList.push_back(rect.IntersectRectT(windowRect));
        }
        return;
    }
    for (auto childWeak = frameChildren_.rbegin(); childWeak != frameChildren_.rend(); ++childWeak) {
        const auto& child = childWeak->Upgrade();
        if (!child) {
            continue;
        }
        child->GetResponseRegionListByTraversal(responseRegionList, windowRect);
    }
}

bool FrameNode::InResponseRegionList(const PointF& parentLocalPoint, const std::vector<RectF>& responseRegionList)
{
    if (IsPaintRectWithTransformValid()) {
        return false;
    }
    for (const auto& rect : responseRegionList) {
        if (rect.IsInRegion(parentLocalPoint)) {
            return true;
        }
    }
    return false;
}

HitTestResult FrameNode::MouseTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    MouseTestResult& onMouseResult, MouseTestResult& onHoverResult, RefPtr<FrameNode>& hoverNode)
{
    // unuseable function. do nothing.
    return HitTestResult::BUBBLING;
}

bool CheckChildHitTestReslut(HitTestResult childHitResult, const RefPtr<OHOS::Ace::NG::FrameNode>& child,
    bool& preventBubbling, bool& consumed, bool isExclusiveEventForChild)
{
    consumed = false;
    if (childHitResult == HitTestResult::STOP_BUBBLING) {
        preventBubbling = true;
        consumed = true;
        return ((child->GetHitTestMode() == HitTestMode::HTMBLOCK) ||
                (child->GetHitTestMode() == HitTestMode::HTMDEFAULT) ||
                (child->GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ||
                ((child->GetHitTestMode() != HitTestMode::HTMTRANSPARENT) && isExclusiveEventForChild));
    } else if (childHitResult == HitTestResult::BUBBLING) {
        consumed = true;
        return ((child->GetHitTestMode() == HitTestMode::HTMDEFAULT) ||
                (child->GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ||
                ((child->GetHitTestMode() != HitTestMode::HTMTRANSPARENT) && isExclusiveEventForChild));
    }
    return false;
}


HitTestResult FrameNode::AxisTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, AxisTestResult& axisResult)
{
    if (!isActive_ || (eventHub_ && !eventHub_->IsEnabled())) {
        TAG_LOGW(AceLogTag::ACE_UIEVENT, "%{public}s/%{public}d is inActive, needn't do touch test",
            GetTag().c_str(), GetId());
        return HitTestResult::OUT_OF_REGION;
    }
    {
        ACE_DEBUG_SCOPED_TRACE("FrameNode::IsOutOfTouchTestRegion");
        if (IsOutOfTouchTestRegion(parentRevertPoint, touchRestrict.touchEvent)) {
            return HitTestResult::OUT_OF_REGION;
        }
    }
    HitTestResult testResult = HitTestResult::OUT_OF_REGION;
    bool preventBubbling = false;
    AxisTestResult newComingTargets;
    auto localPoint = parentLocalPoint - renderContext_->GetPaintRectWithTransform().GetOffset();
    renderContext_->GetPointWithTransform(localPoint);
    auto revertPoint = parentRevertPoint;
    MapPointTo(revertPoint, GetOrRefreshMatrixFromCache().revertMatrix);
    auto subRevertPoint = revertPoint - renderContext_->GetPaintRectWithoutTransform().GetOffset();
    bool consumed = false;
    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        if (GetHitTestMode() == HitTestMode::HTMBLOCK) {
            break;
        }
        const auto& child = iter->Upgrade();
        if (!child) {
            continue;
        }
        auto childHitResult = child->AxisTest(globalPoint, localPoint, subRevertPoint, touchRestrict, newComingTargets);
        if (CheckChildHitTestReslut(childHitResult, child, preventBubbling, consumed, IsExclusiveEventForChild())) {
            break;
        }
    }
    CollectSelfAxisResult(
        globalPoint, localPoint, consumed, revertPoint, axisResult, preventBubbling, testResult, touchRestrict);

    axisResult.splice(axisResult.begin(), std::move(newComingTargets));
    if (!consumed) {
        return testResult;
    }
    if (testResult == HitTestResult::OUT_OF_REGION && preventBubbling) {
        return HitTestResult::STOP_BUBBLING;
    } else {
        return (GetHitTestMode() == HitTestMode::HTMTRANSPARENT_SELF) ? HitTestResult::SELF_TRANSPARENT
                                                                      : HitTestResult::BUBBLING;
    }
    return testResult;
}

void FrameNode::CollectSelfAxisResult(const PointF& globalPoint, const PointF& localPoint, bool& consumed,
    const PointF& parentRevertPoint, AxisTestResult& axisResult, bool& preventBubbling, HitTestResult& testResult,
    TouchRestrict& touchRestrict)
{
    if (consumed) {
        testResult = preventBubbling ? HitTestResult::STOP_BUBBLING : HitTestResult::BUBBLING;
        consumed = false;
    } else if (GetHitTestMode() == HitTestMode::HTMBLOCK) {
        testResult = HitTestResult::STOP_BUBBLING;
    }
    auto origRect = renderContext_->GetPaintRectWithoutTransform();
    auto resRegionList = GetResponseRegionList(origRect, static_cast<int32_t>(touchRestrict.touchEvent.sourceType));
    if (SystemProperties::GetDebugEnabled()) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "AxisTest: point is %{public}s in %{public}s, depth: %{public}d",
            parentRevertPoint.ToString().c_str(), GetTag().c_str(), GetDepth());
        for (const auto& rect : resRegionList) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "AxisTest: resRegionList is %{public}s, point is %{public}s",
                rect.ToString().c_str(), parentRevertPoint.ToString().c_str());
        }
    }
    if (preventBubbling) {
        return;
    }
    if (GetHitTestMode() == HitTestMode::HTMNONE) {
        return;
    }
    if (InResponseRegionList(parentRevertPoint, resRegionList)) {
        consumed = true;
        auto inputHub = eventHub_ ? eventHub_->GetInputEventHub() : nullptr;
        if (inputHub) {
            const auto coordinateOffset = globalPoint - localPoint;
            inputHub->ProcessAxisTestHit(coordinateOffset, axisResult);
        }
    }
}

void FrameNode::AnimateHoverEffect(bool isHovered) const
{
    auto renderContext = GetRenderContext();
    if (!renderContext) {
        return;
    }
    HoverEffectType animationType = HoverEffectType::UNKNOWN;
    auto inputEventHub = eventHub_ ? eventHub_->GetInputEventHub() : nullptr;
    if (inputEventHub) {
        animationType = inputEventHub->GetHoverEffect();
        if (animationType == HoverEffectType::UNKNOWN || animationType == HoverEffectType::AUTO) {
            animationType = inputEventHub->GetHoverEffectAuto();
        }
    }
    if (animationType == HoverEffectType::SCALE) {
        renderContext->AnimateHoverEffectScale(isHovered);
    } else if (animationType == HoverEffectType::BOARD) {
        renderContext->AnimateHoverEffectBoard(isHovered);
    }
}

RefPtr<FocusHub> FrameNode::GetOrCreateFocusHub()
{
    if (focusHub_) {
        return focusHub_;
    }
    if (!pattern_) {
        focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this));
    } else {
        auto focusPattern = pattern_->GetFocusPattern();
        focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this), focusPattern);
    }
    return focusHub_;
}

const RefPtr<DragDropRelatedConfigurations>& FrameNode::GetOrCreateDragDropRelatedConfigurations()
{
    if (dragDropRelatedConfigurations_) {
        return dragDropRelatedConfigurations_;
    }
    dragDropRelatedConfigurations_ = MakeRefPtr<DragDropRelatedConfigurations>();
    return dragDropRelatedConfigurations_;
}

const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(FocusType type, bool focusable, FocusStyleType focusStyleType,
    const std::unique_ptr<FocusPaintParam>& paintParamsPtr)
{
    if (focusHub_) {
        return focusHub_;
    }
    focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this), type, focusable);
    focusHub_->SetFocusStyleType(focusStyleType);
    if (paintParamsPtr) {
        focusHub_->SetFocusPaintParamsPtr(paintParamsPtr);
    }
    return focusHub_;
}

const RefPtr<FocusHub>& FrameNode::GetOrCreateFocusHub(const FocusPattern& focusPattern)
{
    if (focusHub_) {
        return focusHub_;
    }
    focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this), focusPattern);
    return focusHub_;
}

void FrameNode::OnWindowShow()
{
    pattern_->OnWindowShow();
}

void FrameNode::OnWindowHide()
{
    pattern_->OnWindowHide();
}

void FrameNode::OnWindowFocused()
{
    if (renderContext_) {
        renderContext_->UpdateWindowFocusState(true);
    }
    pattern_->OnWindowFocused();
}

void FrameNode::OnWindowUnfocused()
{
    if (renderContext_) {
        renderContext_->UpdateWindowFocusState(false);
    }
    pattern_->OnWindowUnfocused();
}

void FrameNode::OnWindowActivated()
{
    if (renderContext_) {
        renderContext_->UpdateWindowActiveState(true);
    }
    pattern_->OnWindowActivated();
}

void FrameNode::OnWindowDeactivated()
{
    if (renderContext_) {
        renderContext_->UpdateWindowActiveState(false);
    }
    pattern_->OnWindowDeactivated();
}

std::pair<float, float> FrameNode::ContextPositionConvertToPX(
    const RefPtr<RenderContext>& context, const SizeF& percentReference)
{
    std::pair<float, float> position;
    CHECK_NULL_RETURN(context, position);
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
    position.first =
        ConvertToPx(context->GetPositionProperty()->GetPosition()->GetX(), scaleProperty, percentReference.Width())
            .value_or(0.0);
    position.second =
        ConvertToPx(context->GetPositionProperty()->GetPosition()->GetY(), scaleProperty, percentReference.Height())
            .value_or(0.0);
    return position;
}

void FrameNode::OnPixelRoundFinish(const SizeF& pixelGridRoundSize)
{
    CHECK_NULL_VOID(pattern_);
    pattern_->OnPixelRoundFinish(pixelGridRoundSize);
}

void FrameNode::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    pattern_->OnWindowSizeChanged(width, height, type);
}

/* @deprecated  This func will be deleted, please use GetTransformRelativeOffset() instead. */
// a node collect ancestor node position upto root node, if a node has "position" property
// then node will use position value but not paint rect result value
OffsetF FrameNode::GetOffsetRelativeToWindow() const
{
    auto offset = geometryNode_->GetFrameOffset();
    auto parent = GetAncestorNodeOfFrame(true);
    if (renderContext_ && renderContext_->GetPositionProperty()) {
        if (renderContext_->GetPositionProperty()->HasPosition()) {
            auto renderPosition =
                ContextPositionConvertToPX(renderContext_, layoutProperty_->GetLayoutConstraint()->percentReference);
            offset.SetX(static_cast<float>(renderPosition.first));
            offset.SetY(static_cast<float>(renderPosition.second));
        }
    }
    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        if (parentRenderContext && parentRenderContext->GetPositionProperty()) {
            if (parentRenderContext->GetPositionProperty()->HasPosition()) {
                auto parentLayoutProperty = parent->GetLayoutProperty();
                CHECK_NULL_RETURN(parentLayoutProperty, offset);
                auto parentRenderContextPosition = ContextPositionConvertToPX(
                    parentRenderContext, parentLayoutProperty->GetLayoutConstraint()->percentReference);
                offset.AddX(static_cast<float>(parentRenderContextPosition.first));
                offset.AddY(static_cast<float>(parentRenderContextPosition.second));
                parent = parent->GetAncestorNodeOfFrame(true);
                continue;
            }
        }
        if (parentRenderContext) {
            offset += parentRenderContext->GetPaintRectWithoutTransform().GetOffset();
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }

    return offset;
}

// returns a node's collected offset(see GetOffsetRelativeToWindow)
// with offset of window to screen
// ex. textInput component wrap offset relative to screen into a config and send to ime framework
OffsetF FrameNode::GetPositionToScreen()
{
    auto offsetCurrent = GetOffsetRelativeToWindow();
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    auto windowManager = pipelineContext->GetWindowManager();
    auto container = Container::CurrentSafely();
    if (container && windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        auto windowScale = container->GetWindowScale();
        offsetCurrent = offsetCurrent * windowScale;
    }
    OffsetF offset(windowOffset.GetX() + offsetCurrent.GetX(), windowOffset.GetY() + offsetCurrent.GetY());
    return offset;
}

// returns a node's offset relative to parent and consider graphic transform rotate properties
OffsetF FrameNode::GetPositionToParentWithTransform() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto offset = context->GetPaintRectWithoutTransform().GetOffset();
    PointF pointTmp(offset.GetX(), offset.GetY());
    context->GetPointTransformRotate(pointTmp);
    offset.SetX(pointTmp.GetX());
    offset.SetY(pointTmp.GetY());
    return offset;
}

// returns a node's offset collected offset(see GetPositionToWindowWithTransform)
// then plus window's offset relative to screen
OffsetF FrameNode::GetPositionToScreenWithTransform()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    OffsetF nodeOffset = GetPositionToWindowWithTransform();
    auto windowManager = pipelineContext->GetWindowManager();
    auto container = Container::CurrentSafely();
    if (container && windowManager && windowManager->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING) {
        auto windowScale = container->GetWindowScale();
        nodeOffset = nodeOffset * windowScale;
    }
    OffsetF offset(windowOffset.GetX() + nodeOffset.GetX(), windowOffset.GetY() + nodeOffset.GetY());
    return offset;
}

// returns a node's offset relative to window
// and consider every ancestor node's graphic transform rotate properties
// ancestor will check boundary of window scene(exclude)
OffsetF FrameNode::GetPositionToWindowWithTransform(bool fromBottom) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto rect = context->GetPaintRectWithoutTransform();
    OffsetF offset;
    if (!fromBottom) {
        offset = rect.GetOffset();
    } else {
        OffsetF offsetBottom(rect.GetX() + rect.Width(), rect.GetY() + rect.Height());
        offset = offsetBottom;
    }

    PointF pointNode(offset.GetX(), offset.GetY());
    context->GetPointTransformRotate(pointNode);
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        offset = parentRenderContext->GetPaintRectWithoutTransform().GetOffset();
        PointF pointTmp(offset.GetX() + pointNode.GetX(), offset.GetY() + pointNode.GetY());
        parentRenderContext->GetPointTransformRotate(pointTmp);
        pointNode.SetX(pointTmp.GetX());
        pointNode.SetY(pointTmp.GetY());
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    offset.SetX(pointNode.GetX());
    offset.SetY(pointNode.GetY());
    return offset;
}

VectorF FrameNode::GetTransformScaleRelativeToWindow() const
{
    VectorF finalScale {1.0f, 1.0f};
    auto context = GetRenderContext();
    if (context) {
        auto scale = GetTransformScale();
        finalScale.x = scale.x;
        finalScale.y = scale.y;
    }

    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        auto contextParent = parent->GetRenderContext();
        if (contextParent) {
            auto scale = parent->GetTransformScale();
            finalScale.x *= scale.x;
            finalScale.y *= scale.y;
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return finalScale;
}

// returns a node's rect relative to window
// and accumulate every ancestor node's graphic properties such as rotate and transform
// detail graphic properites see RosenRenderContext::GetPaintRectWithTransform
// ancestor will check boundary of window scene(exclude)
RectF FrameNode::GetTransformRectRelativeToWindow(bool checkBoundary) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, RectF());
    RectF rect = context->GetPaintRectWithTransform();
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        if (checkBoundary && parent->IsWindowBoundary()) {
            break;
        }
        rect = ApplyFrameNodeTranformToRect(rect, parent);
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return rect;
}

// returns a node's offset relative to window
// and accumulate every ancestor node's graphic properties such as rotate and transform
// detail graphic properites see RosenRenderContext::GetPaintRectWithTransform
// ancestor will check boundary of window scene(exclude)
OffsetF FrameNode::GetTransformRelativeOffset() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto offset = context->GetPaintRectWithTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame(true);

    while (parent) {
        auto parentRenderContext = parent->GetRenderContext();
        offset += parentRenderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }

    return offset;
}

OffsetF FrameNode::GetPaintRectOffset(bool excludeSelf, bool checkBoundary) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    OffsetF offset = excludeSelf ? OffsetF() : context->GetPaintRectWithTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame(checkBoundary);
    while (parent) {
        if (!checkBoundary && parent->CheckTopWindowBoundary()) {
            break;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(checkBoundary);
    }
    return offset;
}

OffsetF FrameNode::GetPaintRectOffsetNG(bool excludeSelf, bool checkBoundary) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    OffsetF offset = excludeSelf ? OffsetF() : context->GetPaintRectWithoutTransform().GetOffset();
    Point point = Matrix4::Invert(context->GetRevertMatrix()) * Point(offset.GetX(), offset.GetY());
    auto parent = GetAncestorNodeOfFrame(checkBoundary);
    while (parent) {
        if (!checkBoundary && parent->CheckTopWindowBoundary()) {
            break;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        auto parentOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
        point = point + Offset(parentOffset.GetX(), parentOffset.GetY());
        auto parentMatrix = Matrix4::Invert(renderContext->GetRevertMatrix());
        point = parentMatrix * point;
        parent = parent->GetAncestorNodeOfFrame(checkBoundary);
    }
    return OffsetF(point.GetX(), point.GetY());
}

std::vector<Point> GetRectPoints(SizeF& frameSize)
{
    std::vector<Point> pointList;
    pointList.push_back(Point(0, 0));
    pointList.push_back(Point(frameSize.Width(), 0));
    pointList.push_back(Point(0, frameSize.Height()));
    pointList.push_back(Point(frameSize.Width(), frameSize.Height()));
    return pointList;
}

RectF GetBoundingBox(std::vector<Point>& pointList)
{
    Point pMax = pointList[0];
    Point pMin = pointList[0];

    for (auto &point: pointList) {
        if (point.GetX() > pMax.GetX()) {
            pMax.SetX(point.GetX());
        }
        if (point.GetX() < pMin.GetX()) {
            pMin.SetX(point.GetX());
        }
        if (point.GetY() > pMax.GetY()) {
            pMax.SetY(point.GetY());
        }
        if (point.GetY() < pMin.GetY()) {
            pMin.SetY(point.GetY());
        }
    }
    return RectF(pMin.GetX(), pMin.GetY(), pMax.GetX() - pMin.GetX(), pMax.GetY() - pMin.GetY());
}

// returns node offset relate to parent and consider transform matrix of parent
bool FrameNode::GetRectPointToParentWithTransform(std::vector<Point>& pointList, const RefPtr<FrameNode>& parent) const
{
    auto renderContext = parent->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto parentOffset = renderContext->GetPaintRectWithoutTransform().GetOffset();
    auto parentMatrix = Matrix4::Invert(renderContext->GetRevertMatrix());
    for (auto& point: pointList) {
        point = point + Offset(parentOffset.GetX(), parentOffset.GetY());
        point = parentMatrix * point;
    }
    return true;
}

// returns node accumulated offset upto an ancestor has no renderContext or window
// and consider each ancestor's transform matrix
RectF FrameNode::GetPaintRectToWindowWithTransform()
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, RectF());
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, RectF());
    auto frameSize = geometryNode->GetFrameSize();
    auto pointList = GetRectPoints(frameSize);
    GetRectPointToParentWithTransform(pointList, Claim(this));
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        if (GetRectPointToParentWithTransform(pointList, parent)) {
            parent = parent->GetAncestorNodeOfFrame(true);
        } else {
            return RectF();
        }
    }
    return GetBoundingBox(pointList);
}

// returns a node's geometry offset relative to window
// used when a node is in the process of layout
// because offset during layout is NOT synced to renderContext yet
OffsetF FrameNode::GetParentGlobalOffsetDuringLayout() const
{
    OffsetF offset {};
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        offset += parent->geometryNode_->GetFrameOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return offset;
}

// returns a node's offset relative to window
// and accumulate every ancestor node's graphic translate properties
// error means any ancestor node renderContext has hasScales_ bool
std::pair<OffsetF, bool> FrameNode::GetPaintRectGlobalOffsetWithTranslate(bool excludeSelf, bool checkBoundary) const
{
    bool error = false;
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, std::make_pair(OffsetF(), error));
    OffsetF offset = excludeSelf ? OffsetF() : context->GetPaintRectWithTranslate().first.GetOffset();
    auto parent = GetAncestorNodeOfFrame(checkBoundary);
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, std::make_pair(OffsetF(), error));
        auto [rect, err] = renderContext->GetPaintRectWithTranslate();
        error = error || err;
        CHECK_NULL_RETURN(rect.IsValid(), std::make_pair(offset + parent->GetPaintRectOffset(), error));
        offset += rect.GetOffset();
        parent = parent->GetAncestorNodeOfFrame(checkBoundary);
    }
    return std::make_pair(offset, error);
}

// returns a node's offset relative to page node
// and accumulate every ancestor node's graphic properties such as rotate and transform
// most of applications has page offset of status bar height
OffsetF FrameNode::GetPaintRectOffsetToPage() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    OffsetF offset = context->GetPaintRectWithTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        // Eliminate the impact of default page transition
        offset += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return (parent && parent->GetTag() == V2::PAGE_ETS_TAG) ? offset : OffsetF();
}

std::optional<RectF> FrameNode::GetViewPort(bool checkBoundary) const
{
    if (viewPort_.has_value()) {
        return viewPort_;
    }
    auto parent = GetAncestorNodeOfFrame(checkBoundary);
    while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
        auto parentViewPort = parent->GetSelfViewPort();
        if (parentViewPort.has_value()) {
            return parentViewPort;
        }
        parent = parent->GetAncestorNodeOfFrame(checkBoundary);
    }
    return std::nullopt;
}

void FrameNode::OnNotifyMemoryLevel(int32_t level)
{
    pattern_->OnNotifyMemoryLevel(level);
}

int32_t FrameNode::GetAllDepthChildrenCount()
{
    int32_t result = 0;
    std::list<RefPtr<FrameNode>> children;
    children.emplace_back(Claim(this));
    while (!children.empty()) {
        auto& node = children.front();
        if (!node->IsInternal()) {
            result++;
            node->GenerateOneDepthVisibleFrame(children);
        }
        children.pop_front();
    }
    return result;
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, WindowsContentChangeTypes windowsContentChangeType) const
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.windowContentChangeTypes = windowsContentChangeType;
        event.nodeId = GetAccessibilityId();
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
    }
}

void FrameNode::OnAccessibilityEventForVirtualNode(AccessibilityEventType eventType, int64_t accessibilityId)
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.windowContentChangeTypes = WindowsContentChangeTypes::CONTENT_CHANGE_TYPE_INVALID;
        event.nodeId = accessibilityId;
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
    }
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, int32_t startIndex, int32_t endIndex)
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.nodeId = GetAccessibilityId();
        event.startIndex = startIndex;
        event.endIndex = endIndex;
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibilityWithNode(event, Claim(this));
    }
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, std::string beforeText, std::string latestContent)
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.nodeId = GetAccessibilityId();
        event.beforeText = beforeText;
        event.latestContent = latestContent;
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibilityWithNode(event, Claim(this));
    }
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, int64_t stackNodeId, WindowsContentChangeTypes windowsContentChangeType)
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.windowContentChangeTypes = windowsContentChangeType;
        event.nodeId = GetAccessibilityId();
        event.stackNodeId = stackNodeId;
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
    }
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, std::string textAnnouncedForAccessibility)
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        if (eventType != AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY) {
            return;
        }
        AccessibilityEvent event;
        event.type = eventType;
        event.nodeId = GetAccessibilityId();
        event.textAnnouncedForAccessibility = textAnnouncedForAccessibility;
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibilityWithNode(event, Claim(this));
    }
}

void FrameNode::OnRecycle()
{
    for (const auto& destroyCallback : destroyCallbacksMap_) {
        if (destroyCallback.second) {
            destroyCallback.second();
        }
    }
    layoutProperty_->ResetGeometryTransition();
    pattern_->OnRecycle();
    UINode::OnRecycle();
}

void FrameNode::OnReuse()
{
    pattern_->OnReuse();
    UINode::OnReuse();
    if (SystemProperties::GetDeveloperModeOn()) {
        PaintDebugBoundary(SystemProperties::GetDebugBoundaryEnabled());
    }
}

bool FrameNode::MarkRemoving()
{
    bool pendingRemove = false;
    if (!layoutProperty_ || !geometryNode_) {
        return pendingRemove;
    }

    isRemoving_ = true;

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr) {
        geometryTransition->Build(WeakClaim(this), false);
        pendingRemove = true;
    }

    const auto children = GetChildren();
    for (const auto& child : children) {
        pendingRemove = child->MarkRemoving() || pendingRemove;
    }
    return pendingRemove;
}

void FrameNode::AddHotZoneRect(const DimensionRect& hotZoneRect)
{
    auto gestureHub = GetOrCreateGestureEventHub();
    gestureHub->AddResponseRect(hotZoneRect);
}

void FrameNode::RemoveLastHotZoneRect() const
{
    auto gestureHub = eventHub_ ? eventHub_->GetOrCreateGestureEventHub() : nullptr;
    gestureHub->RemoveLastResponseRect();
}

bool FrameNode::OnRemoveFromParent(bool allowTransition)
{
    // the node set isInDestroying state when destroying in pop animation
    // when in isInDestroying state node should not DetachFromMainTree preventing pop page from being white
    if (IsDestroyingState() && GetContext() && !GetContext()->IsDestroyed()) {
        return false;
    }
    // kick out transition animation if needed, wont re-entry if already detached.
    DetachFromMainTree(!allowTransition);
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, false);
    if (!allowTransition || RemoveImmediately()) {
        // directly remove, reset parent and depth
        ResetParent();
        return true;
    }
    // delayed remove, will move self into disappearing children
    return false;
}

RefPtr<FrameNode> FrameNode::FindChildByPosition(float x, float y)
{
    std::map<int32_t, RefPtr<FrameNode>> hitFrameNodes;
    std::list<RefPtr<FrameNode>> children;
    GenerateOneDepthAllFrame(children);
    for (const auto& child : children) {
        if (!child->IsActive()) {
            continue;
        }
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }

        auto globalFrameRect = geometryNode->GetFrameRect();
        globalFrameRect.SetOffset(child->GetOffsetRelativeToWindow());

        if (globalFrameRect.IsInRegion(PointF(x, y))) {
            hitFrameNodes.insert(std::make_pair(child->GetDepth(), child));
        }
    }

    if (hitFrameNodes.empty()) {
        return nullptr;
    }

    return hitFrameNodes.rbegin()->second;
}

RefPtr<FrameNode> FrameNode::FindChildByPositionWithoutChildTransform(float x, float y)
{
    std::map<int32_t, RefPtr<FrameNode>> hitFrameNodes;
    std::list<RefPtr<FrameNode>> children;
    GenerateOneDepthAllFrame(children);
    auto parentOffset = GetPositionToWindowWithTransform();
    for (const auto& child : children) {
        if (!child->IsActive()) {
            continue;
        }
        auto geometryNode = child->GetGeometryNode();
        if (!geometryNode) {
            continue;
        }

        auto globalFrameRect = geometryNode->GetFrameRect();
        auto childOffset = geometryNode->GetFrameOffset();
        childOffset += parentOffset;
        globalFrameRect.SetOffset(childOffset);

        if (globalFrameRect.IsInRegion(PointF(x, y))) {
            hitFrameNodes.insert(std::make_pair(child->GetDepth(), child));
        }
    }

    if (hitFrameNodes.empty()) {
        return nullptr;
    }

    return hitFrameNodes.rbegin()->second;
}

RefPtr<NodeAnimatablePropertyBase> FrameNode::GetAnimatablePropertyFloat(const std::string& propertyName) const
{
    auto iter = nodeAnimatablePropertyMap_.find(propertyName);
    if (iter == nodeAnimatablePropertyMap_.end()) {
        return nullptr;
    }
    return iter->second;
}

RefPtr<FrameNode> FrameNode::FindChildByName(const RefPtr<FrameNode>& parentNode, const std::string& nodeName)
{
    CHECK_NULL_RETURN(parentNode, nullptr);
    const auto& children = parentNode->GetChildren();
    for (const auto& child : children) {
        auto childFrameNode = AceType::DynamicCast<FrameNode>(child);
        if (childFrameNode && childFrameNode->GetInspectorId().value_or("") == nodeName) {
            return childFrameNode;
        }
        auto childFindResult = FindChildByName(childFrameNode, nodeName);
        if (childFindResult) {
            return childFindResult;
        }
    }
    return nullptr;
}

void FrameNode::CreateAnimatablePropertyFloat(const std::string& propertyName, float value,
    const std::function<void(float)>& onCallbackEvent, const PropertyUnit& propertyType)
{
    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    auto iter = nodeAnimatablePropertyMap_.find(propertyName);
    if (iter != nodeAnimatablePropertyMap_.end()) {
        return;
    }
    auto property = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(value, std::move(onCallbackEvent));
    context->AttachNodeAnimatableProperty(property);
    if (propertyType == PropertyUnit::PIXEL_POSITION) {
        property->SetPropertyUnit(propertyType);
    }
    nodeAnimatablePropertyMap_.emplace(propertyName, property);
}

void FrameNode::DeleteAnimatablePropertyFloat(const std::string& propertyName)
{
    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    RefPtr<NodeAnimatablePropertyBase> propertyRef = GetAnimatablePropertyFloat(propertyName);
    if (propertyRef) {
        context->DetachNodeAnimatableProperty(propertyRef);
        nodeAnimatablePropertyMap_.erase(propertyName);
    }
}

void FrameNode::UpdateAnimatablePropertyFloat(const std::string& propertyName, float value)
{
    auto iter = nodeAnimatablePropertyMap_.find(propertyName);
    if (iter == nodeAnimatablePropertyMap_.end()) {
        return;
    }
    auto property = AceType::DynamicCast<NodeAnimatablePropertyFloat>(iter->second);
    CHECK_NULL_VOID(property);
    property->Set(value);
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_ANIMATION);
    }
}

void FrameNode::CreateAnimatableArithmeticProperty(const std::string& propertyName,
    RefPtr<CustomAnimatableArithmetic>& value,
    std::function<void(const RefPtr<CustomAnimatableArithmetic>&)>& onCallbackEvent)
{
    auto context = GetRenderContext();
    CHECK_NULL_VOID(context);
    auto iter = nodeAnimatablePropertyMap_.find(propertyName);
    if (iter != nodeAnimatablePropertyMap_.end()) {
        return;
    }
    auto property = AceType::MakeRefPtr<NodeAnimatableArithmeticProperty>(value, std::move(onCallbackEvent));
    context->AttachNodeAnimatableProperty(property);
    nodeAnimatablePropertyMap_.emplace(propertyName, property);
}

void FrameNode::UpdateAnimatableArithmeticProperty(
    const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value)
{
    auto iter = nodeAnimatablePropertyMap_.find(propertyName);
    if (iter == nodeAnimatablePropertyMap_.end()) {
        return;
    }
    auto property = AceType::DynamicCast<NodeAnimatableArithmeticProperty>(iter->second);
    CHECK_NULL_VOID(property);
    property->Set(value);
}

std::string FrameNode::ProvideRestoreInfo()
{
    return pattern_->ProvideRestoreInfo();
}

bool FrameNode::RemoveImmediately() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, true);
    // has transition out animation, need to wait for animation end
    return !context->HasTransitionOutAnimation();
}

std::vector<RefPtr<FrameNode>> FrameNode::GetNodesById(const std::unordered_set<int32_t>& set)
{
    std::vector<RefPtr<FrameNode>> nodes;
    for (auto nodeId : set) {
        auto uiNode = ElementRegister::GetInstance()->GetUINodeById(nodeId);
        if (!uiNode) {
            continue;
        }
        auto frameNode = DynamicCast<FrameNode>(uiNode);
        if (frameNode) {
            nodes.emplace_back(frameNode);
        }
    }
    return nodes;
}

std::vector<FrameNode*> FrameNode::GetNodesPtrById(const std::unordered_set<int32_t>& set)
{
    std::vector<FrameNode*> nodes;
    for (auto nodeId : set) {
        NG::FrameNode* frameNode = ElementRegister::GetInstance()->GetFrameNodePtrById(nodeId);
        if (!frameNode) {
            continue;
        }
        nodes.emplace_back(frameNode);
    }
    return nodes;
}

double FrameNode::GetPreviewScaleVal() const
{
    double scale = 1.0;
    auto maxWidth = DragDropManager::GetMaxWidthBaseOnGridSystem(GetContextRefPtr());
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, scale);
    auto width = geometryNode->GetFrameRect().Width();
    if (GetTag() != V2::WEB_ETS_TAG && width != 0 && width > maxWidth && previewOption_.isScaleEnabled) {
        scale = maxWidth / width;
    }
    return scale;
}

bool FrameNode::IsPreviewNeedScale() const
{
    return GetPreviewScaleVal() < 1.0f;
}

int32_t FrameNode::GetNodeExpectedRate()
{
    if (sceneRateMap_.empty()) {
        return 0;
    }
    auto iter = std::max_element(
        sceneRateMap_.begin(), sceneRateMap_.end(), [](auto a, auto b) { return a.second < b.second; });
    return iter->second;
}

void FrameNode::TryPrintDebugLog(const std::string& scene, float speed, SceneStatus status)
{
    if (SystemProperties::GetDebugEnabled()) {
        const std::string sceneStatusStrs[] = { "START", "RUNNING", "END" };
        LOGD("%{public}s  AddFRCSceneInfo scene:%{public}s   speed:%{public}f  status:%{public}s", GetTag().c_str(),
            scene.c_str(), std::abs(speed), sceneStatusStrs[static_cast<int32_t>(status)].c_str());
    }
}

void FrameNode::AddFRCSceneInfo(const std::string& scene, float speed, SceneStatus status)
{
    TryPrintDebugLog(scene, speed, status);

    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto frameRateManager = pipelineContext->GetFrameRateManager();
    CHECK_NULL_VOID(frameRateManager);

    frameRateManager->SetDragScene(status == SceneStatus::END ? 0 : 1);
    auto expectedRate = renderContext->CalcExpectedFrameRate(scene, std::abs(speed));
    auto nodeId = GetId();
    auto iter = sceneRateMap_.find(scene);
    EventReport::FrameRateDurationsStatistics(expectedRate, scene, status);

    switch (status) {
        case SceneStatus::START: {
            if (iter == sceneRateMap_.end()) {
                if (sceneRateMap_.empty()) {
                    frameRateManager->AddNodeRate(nodeId);
                }
                sceneRateMap_.emplace(scene, expectedRate);
                frameRateManager->UpdateNodeRate(nodeId, GetNodeExpectedRate());
            }
            return;
        }
        case SceneStatus::RUNNING: {
            if (iter != sceneRateMap_.end() && iter->second != expectedRate) {
                iter->second = expectedRate;
                auto nodeExpectedRate = GetNodeExpectedRate();
                frameRateManager->UpdateNodeRate(nodeId, nodeExpectedRate);
            }
            return;
        }
        case SceneStatus::END: {
            if (iter != sceneRateMap_.end()) {
                sceneRateMap_.erase(iter);
                if (sceneRateMap_.empty()) {
                    frameRateManager->RemoveNodeRate(nodeId);
                } else {
                    auto nodeExpectedRate = GetNodeExpectedRate();
                    frameRateManager->UpdateNodeRate(nodeId, nodeExpectedRate);
                }
            }
            return;
        }
        default:
            return;
    }
}

void FrameNode::GetPercentSensitive()
{
    auto res = layoutProperty_->GetPercentSensitive();
    if (res.first) {
        if (layoutAlgorithm_) {
            layoutAlgorithm_->SetPercentWidth(true);
        }
    }
    if (res.second) {
        if (layoutAlgorithm_) {
            layoutAlgorithm_->SetPercentHeight(true);
        }
    }
}

void FrameNode::UpdatePercentSensitive()
{
    bool percentHeight = layoutAlgorithm_ ? layoutAlgorithm_->GetPercentHeight() : true;
    bool percentWidth = layoutAlgorithm_ ? layoutAlgorithm_->GetPercentWidth() : true;
    auto res = layoutProperty_->UpdatePercentSensitive(percentWidth, percentHeight);
    if (res.first) {
        auto parent = GetAncestorNodeOfFrame(true);
        if (parent && parent->layoutAlgorithm_) {
            parent->layoutAlgorithm_->SetPercentWidth(true);
        }
    }
    if (res.second) {
        auto parent = GetAncestorNodeOfFrame(true);
        if (parent && parent->layoutAlgorithm_) {
            parent->layoutAlgorithm_->SetPercentHeight(true);
        }
    }
}

// This will call child and self measure process.
void FrameNode::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    ACE_LAYOUT_TRACE_BEGIN("Measure[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(), GetId(),
        GetAncestorNodeOfFrame(true) ? GetAncestorNodeOfFrame(true)->GetId() : 0, GetInspectorIdValue("").c_str());
    if (SystemProperties::GetMeasureDebugTraceEnabled()) {
        ACE_MEASURE_SCOPED_TRACE("MeasureInfo[frameRect:%s][parentConstraint:%s][calcConstraint:%s]",
            GetGeometryNode()->GetFrameRect().ToString().c_str(),
            parentConstraint.has_value() ? parentConstraint.value().ToString().c_str() : "NA",
            layoutProperty_->GetCalcLayoutConstraint() ? layoutProperty_->GetCalcLayoutConstraint()->ToString().c_str()
                                                       : "NA");
    }
    auto pipeline = GetContext();
    if (pipeline) {
        auto id = pipeline->GetInstanceId();
        ArkUIPerfMonitor::GetPerfMonitor(id)->RecordLayoutNode();
    }
    isLayoutComplete_ = false;
    if (!oldGeometryNode_) {
        oldGeometryNode_ = geometryNode_->Clone();
    }
    pattern_->BeforeCreateLayoutWrapper();
    GetLayoutAlgorithm(true);

    if (layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE) == VisibleType::GONE) {
        layoutAlgorithm_->SetSkipMeasure();
        layoutAlgorithm_->SetSkipLayout();
        geometryNode_->SetFrameSize(SizeF());
        geometryNode_->UpdateMargin(MarginPropertyF());
        isLayoutDirtyMarked_ = false;
        ACE_SCOPED_TRACE("SkipMeasure [%s][self:%d] reason: VisibleType::GONE", GetTag().c_str(), GetId());
        ACE_LAYOUT_TRACE_END()
        return;
    }
    if (!isActive_) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }

    if (layoutAlgorithm_->SkipMeasure()) {
        isLayoutDirtyMarked_ = false;
        ACE_LAYOUT_TRACE_END()
        ACE_SCOPED_TRACE("SkipMeasure [%s][self:%d] reason: SkipMeasure", GetTag().c_str(), GetId());
        return;
    }

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsRunning(WeakClaim(this))) {
        geometryTransition->WillLayout(Claim(this));
    }
    auto preConstraint = layoutProperty_->GetLayoutConstraint();
    auto contentConstraint = layoutProperty_->GetContentLayoutConstraint();
    layoutProperty_->BuildGridProperty(Claim(this));

    if (layoutProperty_->GetLayoutRect()) {
        layoutProperty_->UpdateLayoutConstraintWithLayoutRect();
    } else if (parentConstraint) {
        ApplyConstraint(*parentConstraint);
    } else {
        CreateRootConstraint();
    }

    layoutProperty_->UpdateContentConstraint();
    geometryNode_->UpdateMargin(layoutProperty_->CreateMargin());
    geometryNode_->UpdatePaddingWithBorder(layoutProperty_->CreatePaddingAndBorder());

    isConstraintNotChanged_ = layoutProperty_->ConstraintEqual(preConstraint, contentConstraint);

    isLayoutDirtyMarked_ = false;

    if (isConstraintNotChanged_) {
        if (!CheckNeedForceMeasureAndLayout()) {
            ACE_SCOPED_TRACE(
                "SkipMeasure [%s][self:%d] reason:ConstraintNotChanged and no force-flag", GetTag().c_str(), GetId());
            layoutAlgorithm_->SetSkipMeasure();
            ACE_LAYOUT_TRACE_END()
            return;
        }
    } else {
        contentConstraintChanges_.UpdateFlags(contentConstraint, layoutProperty_->GetContentLayoutConstraint());
        constraintChanges_.UpdateFlags(preConstraint, layoutProperty_->GetLayoutConstraint());
    }

    GetPercentSensitive();

    if (extensionHandler_ && !extensionHandler_->HasDrawModifier()) {
        auto extensionLayoutConstraint =
            ExtensionLayoutConstraint::Create(GetLayoutProperty()->GetLayoutConstraint().value());
        extensionHandler_->SetInnerMeasureImpl([this](const ExtensionLayoutConstraint&) {
            auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->CreateContentConstraint(), this);
            if (size.has_value()) {
                geometryNode_->SetContentSize(size.value());
            }
            layoutAlgorithm_->Measure(this);
        });
        extensionHandler_->Measure(extensionLayoutConstraint);
    } else {
        auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->CreateContentConstraint(), this);
        if (size.has_value()) {
            geometryNode_->SetContentSize(size.value());
        }
        layoutAlgorithm_->Measure(this);
    }

    if (overlayNode_) {
        overlayNode_->Measure(layoutProperty_->CreateChildConstraint());
    }
    UpdatePercentSensitive();
    // check aspect radio.
    if (pattern_ && pattern_->IsNeedAdjustByAspectRatio() && !layoutProperty_->GetLayoutRect()) {
        const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
        auto aspectRatio = magicItemProperty.GetAspectRatioValue();
        // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and
        // aspectRatio are all set, the height is not used.
        auto width = geometryNode_->GetFrameSize().Width();
        auto height = width / aspectRatio;
        geometryNode_->SetFrameSize(SizeF({ width, height }));
    }

    if (pipeline && pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE) {
        auto size = geometryNode_->GetFrameSize();
        geometryNode_->SetFrameSize(SizeF({ round(size.Width()), round(size.Height()) }));
    }

    if (measureCallback_) {
        measureCallback_(kitNode_);
    }

    layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
    if (SystemProperties::GetMeasureDebugTraceEnabled()) {
        ACE_MEASURE_SCOPED_TRACE("MeasureFinish[frameRect:%s][contentSize:%s]",
            GetGeometryNode()->GetFrameRect().ToString().c_str(),
            GetGeometryNode()->GetContentSize().ToString().c_str());
    }
    ACE_LAYOUT_TRACE_END()
}

// Called to perform layout children.
void FrameNode::Layout()
{
    ACE_LAYOUT_TRACE_BEGIN("Layout[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(), GetId(),
        GetAncestorNodeOfFrame(true) ? GetAncestorNodeOfFrame(true)->GetId() : 0, GetInspectorIdValue("").c_str());
    if (SystemProperties::GetMeasureDebugTraceEnabled()) {
        ACE_MEASURE_SCOPED_TRACE("LayoutInfo[frameRect:%s]", GetGeometryNode()->GetFrameRect().ToString().c_str());
    }
    if (layoutProperty_->GetLayoutRect()) {
        GetGeometryNode()->SetFrameOffset(layoutProperty_->GetLayoutRect().value().GetOffset());
    }
    int64_t time = GetSysTimestamp();
    OffsetNodeToSafeArea();
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr) {
        if (geometryTransition->IsNodeInAndActive(Claim(this))) {
            if (IsRootMeasureNode()) {
                UINode::SetGeometryTransitionInRecursive(true);
            } else {
                SetSkipSyncGeometryNode();
            }
        }
    }
    if (CheckNeedLayout(layoutProperty_->GetPropertyChangeFlag()) || GetIgnoreLayoutProcess()) {
        if (!layoutProperty_->GetLayoutConstraint()) {
            const auto& parentLayoutConstraint = geometryNode_->GetParentLayoutConstraint();
            if (layoutProperty_->GetLayoutRect()) {
                layoutProperty_->UpdateLayoutConstraintWithLayoutRect();
            } else if (parentLayoutConstraint) {
                layoutProperty_->UpdateLayoutConstraint(parentLayoutConstraint.value());
            } else {
                LayoutConstraintF layoutConstraint;
                layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
                layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
                layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
            }
            layoutProperty_->UpdateContentConstraint();
        }

        if (extensionHandler_ && !extensionHandler_->HasDrawModifier()) {
            extensionHandler_->SetInnerLayoutImpl(
                [this](int32_t, int32_t, int32_t, int32_t) { GetLayoutAlgorithm()->Layout(this); });
            const auto& rect = geometryNode_->GetFrameRect();
            extensionHandler_->Layout(rect.Width(), rect.Height(), rect.GetX(), rect.GetY());
        } else {
            GetLayoutAlgorithm()->Layout(this);
        }

        if (overlayNode_) {
            LayoutOverlay();
        }
        time = GetSysTimestamp() - time;
        AddNodeFlexLayouts();
        AddNodeLayoutTime(time);
    } else {
        ACE_SCOPED_TRACE("SkipLayout [%s][self:%d]", GetTag().c_str(), GetId());
        GetLayoutAlgorithm()->SetSkipLayout();
    }
    if (SystemProperties::GetMeasureDebugTraceEnabled()) {
        ACE_MEASURE_SCOPED_TRACE(
            "LayoutFinish[frameRect:%s]", GetGeometryNode()->GetFrameRect().ToString().c_str());
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID_LAYOUT_TRACE_END(pipeline);
    auto stageManager = pipeline->GetStageManager();
    CHECK_NULL_VOID(stageManager);
    bool isFocusOnPage = stageManager->CheckPageFocus();
    bool needSyncRsNode = false;
    DirtySwapConfig config;
    bool willSyncGeoProperties = OnLayoutFinish(needSyncRsNode, config);
    needSyncRsNode |= AvoidKeyboard(isFocusOnPage);
    if (GetIsGeometryTransitionIn()) {
        renderContext_->SetFrameWithoutAnimation(renderContext_->GetPaintRectWithoutTransform());
        SetIsGeometryTransitionIn(false);
    }
    // skip wrapping task if node will not sync
    CHECK_NULL_VOID_LAYOUT_TRACE_END(willSyncGeoProperties);
    auto task = [weak = WeakClaim(this), needSync = needSyncRsNode, dirtyConfig = config]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->SyncGeometryNode(needSync, dirtyConfig);
    };
    pipeline->AddSyncGeometryNodeTask(task);
    if (SelfOrParentExpansive()) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID_LAYOUT_TRACE_END(pipeline);
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        CHECK_NULL_VOID_LAYOUT_TRACE_END(safeAreaManager);
        safeAreaManager->AddNeedExpandNode(GetHostNode());
    }
    // if a node has geo transition but not the root node, add task only but not flush
    // or add to expand list, self node will be added to expand list in next layout
    if (geometryTransition != nullptr && !IsRootMeasureNode()) {
        ACE_LAYOUT_TRACE_END()
        return;
    }
    if (geometryTransition != nullptr) {
        pipeline->FlushSyncGeometryNodeTasks();
    }
    ACE_LAYOUT_TRACE_END()
}

bool FrameNode::SelfExpansive()
{
    auto&& opts = GetLayoutProperty()->GetSafeAreaExpandOpts();
    return opts && (opts->Expansive() || opts->switchToNone);
}

bool FrameNode::SelfExpansiveToKeyboard()
{
    auto && opts = GetLayoutProperty()->GetSafeAreaExpandOpts();
    return opts && opts->ExpansiveToKeyboard();
}

bool FrameNode::ParentExpansive()
{
    auto parent = GetAncestorNodeOfFrame(false);
    CHECK_NULL_RETURN(parent, false);
    auto parentLayoutProperty = parent->GetLayoutProperty();
    CHECK_NULL_RETURN(parentLayoutProperty, false);
    auto&& parentOpts = parentLayoutProperty->GetSafeAreaExpandOpts();
    return parentOpts && parentOpts->Expansive();
}

void FrameNode::ProcessSafeAreaPadding()
{
    pattern_->ProcessSafeAreaPadding();
}

void FrameNode::UpdateFocusState()
{
    auto focusHub = GetFocusHub();
    if (focusHub && focusHub->IsCurrentFocus()) {
        focusHub->ClearFocusState(false);
        focusHub->PaintFocusState(false);
    }
}

bool FrameNode::SelfOrParentExpansive()
{
    return SelfExpansive() || ParentExpansive();
}

void FrameNode::ProcessAccessibilityVirtualNode()
{
    if (!hasAccessibilityVirtualNode_) {
        return;
    }
    auto accessibilityProperty = GetAccessibilityProperty<AccessibilityProperty>();
    auto virtualNode = accessibilityProperty->GetAccessibilityVirtualNode();
    auto virtualFrameNode = AceType::DynamicCast<NG::FrameNode>(virtualNode);
    if (virtualFrameNode) {
        auto constraint = GetLayoutConstraint();
        virtualFrameNode->ApplyConstraint(constraint);
        ProcessOffscreenNode(virtualFrameNode);
    }
}

void FrameNode::UpdateAccessibilityNodeRect()
{
    if (!AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        return;
    }
    auto context = GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto accessibilityManager = context->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->UpdateAccessibilityNodeRect(Claim(this));
}

bool FrameNode::OnLayoutFinish(bool& needSyncRsNode, DirtySwapConfig& config)
{
    auto context = GetContext();
    if (isLayoutNode_ && context) {
        context->AddLayoutNode(Claim(this));
    }
    isLayoutComplete_ = true;
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    bool hasTransition = geometryTransition != nullptr && geometryTransition->IsRunning(WeakClaim(this));
    if (!isActive_ && !hasTransition) {
        layoutAlgorithm_.Reset();
        ACE_SCOPED_TRACE("OnLayoutFinish[%s][self:%d] !isActive && !hasTransition", GetTag().c_str(), GetId());
        return false;
    }
    if (needSkipSyncGeometryNode_ && (!geometryTransition || !geometryTransition->IsNodeInAndActive(Claim(this)))) {
        layoutAlgorithm_.Reset();
        ACE_SCOPED_TRACE("OnLayoutFinish[%s][self:%d] needSkipSyncGeometryNode", GetTag().c_str(), GetId());
        return false;
    }
    // update layout size.
    bool frameSizeChange = true;
    bool frameOffsetChange = true;
    bool contentSizeChange = true;
    bool contentOffsetChange = true;
    if (oldGeometryNode_) {
        frameSizeChange = geometryNode_->GetFrameSize() != oldGeometryNode_->GetFrameSize();
        frameOffsetChange = geometryNode_->GetFrameOffset() != oldGeometryNode_->GetFrameOffset();
        contentSizeChange = geometryNode_->GetContentSize() != oldGeometryNode_->GetContentSize();
        contentOffsetChange = geometryNode_->GetContentOffset() != oldGeometryNode_->GetContentOffset();
        oldGeometryNode_.Reset();
    }

    // clean layout flag.
    layoutProperty_->CleanDirty();
    needSyncRsNode = frameSizeChange || frameOffsetChange ||
                     (pattern_->GetContextParam().has_value() && contentSizeChange) || HasPositionProp() ||
                     SelfOrParentExpansive();
    if (hasTransition) {
        geometryTransition->DidLayout(Claim(this));
        if (geometryTransition->IsNodeOutAndActive(WeakClaim(this))) {
            isLayoutDirtyMarked_ = true;
        }
        needSyncRsNode = false;
    } else {
        auto borderRadius = renderContext_->GetBorderRadius();
        if (borderRadius.has_value()) {
            renderContext_->SetBorderRadius(borderRadius.value());
        }
        auto outerBorderRadius = renderContext_->GetOuterBorderRadius();
        if (outerBorderRadius.has_value()) {
            renderContext_->SetOuterBorderRadius(outerBorderRadius.value());
        }
    }
    if (GetTag() != V2::PAGE_ETS_TAG) {
        renderContext_->SavePaintRect(true, layoutProperty_->GetPixelRound());
        if (needSyncRsNode) {
            renderContext_->SyncPartialRsProperties();
        }
    }
    config = { .frameSizeChange = frameSizeChange,
        .frameOffsetChange = frameOffsetChange,
        .contentSizeChange = contentSizeChange,
        .contentOffsetChange = contentOffsetChange };
    // check if need to paint content.
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(layoutAlgorithm_);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    config.skipMeasure = layoutAlgorithmWrapper->SkipMeasure();
    config.skipLayout = layoutAlgorithmWrapper->SkipLayout();
    if (!config.skipMeasure && !config.skipLayout) {
        CHECK_NULL_RETURN(context, false);
        if (GetInspectorId()) {
            context->OnLayoutCompleted(GetInspectorId()->c_str());
        }
        if (eventHub_) {
            eventHub_->FireLayoutNDKCallback(context);
        }
    }
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(Claim(this), config);
    needRerender =
        needRerender || pattern_->OnDirtyLayoutWrapperSwap(Claim(this), config.skipMeasure, config.skipLayout);
    if (needRerender || (extensionHandler_ && extensionHandler_->NeedRender()) ||
        CheckNeedRender(paintProperty_->GetPropertyChangeFlag())) {
        MarkDirtyNode(true, true, PROPERTY_UPDATE_RENDER);
    }
    layoutAlgorithm_.Reset();

    UpdateAccessibilityNodeRect();
    ProcessAccessibilityVirtualNode();
    CHECK_NULL_RETURN(context, false);
    context->SendUpdateVirtualNodeFocusEvent();
    return true;
}

void FrameNode::SyncGeometryNode(bool needSyncRsNode, const DirtySwapConfig& config)
{
    if (SystemProperties::GetSyncDebugTraceEnabled()) {
        ACE_LAYOUT_TRACE_BEGIN("SyncGeometryNode[%s][self:%d][parent:%d][key:%s][paintRect:%s][needSyncRsNode:%d]",
            GetTag().c_str(), GetId(), GetParent() ? GetParent()->GetId() : 0, GetInspectorIdValue("").c_str(),
            renderContext_->GetPaintRectWithoutTransform().ToString().c_str(), needSyncRsNode);
        ACE_LAYOUT_TRACE_END()
    }
    if (!needSyncRsNode) {
        ACE_SCOPED_TRACE("SyncGeometryNode[%s][self:%d] don't needSyncRsNode", GetTag().c_str(), GetId());
    }

    // update border.
    if (layoutProperty_->GetBorderWidthProperty()) {
        if (!renderContext_->HasBorderColor()) {
            BorderColorProperty borderColorProperty;
            borderColorProperty.SetColor(Color::BLACK);
            renderContext_->UpdateBorderColor(borderColorProperty);
        }
        if (!renderContext_->HasBorderStyle()) {
            BorderStyleProperty borderStyleProperty;
            borderStyleProperty.SetBorderStyle(BorderStyle::SOLID);
            renderContext_->UpdateBorderStyle(borderStyleProperty);
        }
        if (!renderContext_->HasDashGap()) {
            BorderWidthProperty dashGapProperty;
            dashGapProperty.SetBorderWidth(Dimension(-1));
            renderContext_->UpdateDashGap(dashGapProperty);
        }
        if (!renderContext_->HasDashWidth()) {
            BorderWidthProperty dashWidthProperty;
            dashWidthProperty.SetBorderWidth(Dimension(-1));
            renderContext_->UpdateDashWidth(dashWidthProperty);
        }
        if (layoutProperty_->GetLayoutConstraint().has_value()) {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(),
                layoutProperty_->GetLayoutConstraint()->percentReference.Width()));
        } else {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth()));
        }
    }

    pattern_->OnSyncGeometryNode(config);
    if (needSyncRsNode) {
        pattern_->BeforeSyncGeometryProperties(config);
        renderContext_->SyncGeometryProperties(RawPtr(geometryNode_), true, layoutProperty_->GetPixelRound());
        if (SystemProperties::GetSyncDebugTraceEnabled()) {
            ACE_LAYOUT_TRACE_BEGIN("TriggerOnSizeChangeNode:[%s][id:%d]", GetTag().c_str(), GetId());
            ACE_LAYOUT_TRACE_END()
        }
        TriggerOnSizeChangeCallback();
    }

    // update background
    if (builderFunc_) {
        auto builderNode = builderFunc_();
        auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            AceType::MakeRefPtr<LinearLayoutPattern>(true));
        if (builderNode) {
            builderNode->MountToParent(columnNode);
        }
        SetBackgroundLayoutConstraint(columnNode);
        renderContext_->CreateBackgroundPixelMap(columnNode);
        builderFunc_ = nullptr;
        backgroundNode_ = columnNode;
    }

    // update focus state
    UpdateFocusState();

    // rebuild child render node.
    if (!isLayoutNode_) {
        RebuildRenderContextTree();
    } else if (GetParent()) {
        GetParent()->RebuildRenderContextTree();
    }

    /* Adjust components' position which have been set grid properties */
    AdjustGridOffset();
}

RefPtr<LayoutWrapper> FrameNode::GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache)
{
    auto child = frameProxy_->GetFrameNodeByIndex(index, true, isCache, addToRenderTree);
    if (child) {
        child->SetSkipSyncGeometryNode(SkipSyncGeometryNode());
        if (addToRenderTree) {
            child->SetActive(true);
        }
    }
    return child;
}

RefPtr<LayoutWrapper> FrameNode::GetChildByIndex(uint32_t index, bool isCache)
{
    return frameProxy_->GetFrameNodeByIndex(index, false, isCache, false);
}

FrameNode* FrameNode::GetFrameNodeChildByIndex(uint32_t index, bool isCache, bool isExpand)
{
    auto frameNode = isExpand ? DynamicCast<FrameNode>(frameProxy_->GetFrameNodeByIndex(index, true, isCache, false))
                              : DynamicCast<FrameNode>(UINode::GetFrameChildByIndexWithoutExpanded(index));
    return RawPtr(frameNode);
}

FrameNode* FrameNode::GetFrameNodeChildByIndexWithoutBuild(uint32_t index)
{
    auto frameNode = DynamicCast<FrameNode>(UINode::GetFrameChildByIndex(index, false, false, false));
    return RawPtr(frameNode);
}

int32_t FrameNode::GetChildTrueIndex(const RefPtr<LayoutWrapper>& child) const
{
    return frameProxy_->GetChildIndex(child);
}

uint32_t FrameNode::GetChildTrueTotalCount() const
{
    return frameProxy_->GetTotalCount();
}

ChildrenListWithGuard FrameNode::GetAllChildrenWithBuild(bool addToRenderTree)
{
    const auto& children = frameProxy_->GetAllFrameChildren();
    {
        auto guard = frameProxy_->GetGuard();
        for (const auto& child : children) {
            if (addToRenderTree) {
                child->SetActive(true);
            }
            child->SetSkipSyncGeometryNode(SkipSyncGeometryNode());
        }
    }

    return children;
}

void FrameNode::RemoveAllChildInRenderTree()
{
    frameProxy_->RemoveAllChildInRenderTree();
}

void FrameNode::SetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCached)
{
    frameProxy_->SetActiveChildRange(start, end, cacheStart, cacheEnd, showCached);
}

void FrameNode::SetActiveChildRange(
    const std::optional<ActiveChildSets>& activeChildSets, const std::optional<ActiveChildRange>& activeChildRange)
{
    frameProxy_->SetActiveChildRange(activeChildSets, activeChildRange);
}

void FrameNode::RecycleItemsByIndex(int32_t start, int32_t end)
{
    frameProxy_->RecycleItemsByIndex(start, end);
}

void FrameNode::RemoveChildInRenderTree(uint32_t index)
{
    frameProxy_->RemoveChildInRenderTree(index);
}

bool FrameNode::SkipMeasureContent() const
{
    return layoutAlgorithm_ && layoutAlgorithm_->SkipMeasure();
}

bool FrameNode::CheckNeedForceMeasureAndLayout()
{
    PropertyChangeFlag flag = layoutProperty_->GetPropertyChangeFlag();
    return CheckNeedMeasure(flag) || CheckNeedLayout(flag);
}

OffsetF FrameNode::GetOffsetInScreen()
{
    auto frameOffset = GetPaintRectOffset(false, true);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF(0.0f, 0.0f));
    auto window = pipelineContext->GetWindow();
    CHECK_NULL_RETURN(window, OffsetF(0.0f, 0.0f));
    auto windowOffset = window->GetCurrentWindowRect().GetOffset();
    frameOffset += OffsetT<float> { windowOffset.GetX(), windowOffset.GetY() };
    return frameOffset;
}

OffsetF FrameNode::GetOffsetInSubwindow(const OffsetF& subwindowOffset)
{
    auto frameOffset = GetOffsetInScreen();
    frameOffset -= subwindowOffset;
    return frameOffset;
}

RefPtr<PixelMap> FrameNode::GetDragPixelMap()
{
    auto gestureHub = GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, nullptr);
    RefPtr<PixelMap> pixelMap = gestureHub->GetPixelMap();
    // if gesture already have pixel map return directly
    if (pixelMap) {
        return pixelMap;
    }
    CHECK_NULL_RETURN(renderContext_, nullptr);
    pixelMap = renderContext_->GetThumbnailPixelMap();
    gestureHub->SetPixelMap(pixelMap);
    return pixelMap;
}

float FrameNode::GetBaselineDistance() const
{
    const auto& children = frameProxy_->GetAllFrameChildren();
    if (children.empty()) {
        return geometryNode_->GetBaselineDistance();
    }
    float distance = 0.0;
    {
        auto guard = frameProxy_->GetGuard();
        for (const auto& child : children) {
            float childBaseline = child->GetBaselineDistance();
            distance = NearZero(distance) ? childBaseline : std::min(distance, childBaseline);
        }
    }
    return distance;
}

void FrameNode::MarkNeedSyncRenderTree(bool needRebuild)
{
    if (isLayoutNode_ && GetParent()) {
        GetParent()->MarkNeedSyncRenderTree(needRebuild);
    }
    if (needRebuild) {
        frameProxy_->ResetChildren(true);
    }
    needSyncRenderTree_ = true;
}

RefPtr<UINode> FrameNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree)
{
    if (index != 0) {
        return nullptr;
    }
    return Claim(this);
}

RefPtr<UINode> FrameNode::GetFrameChildByIndexWithoutExpanded(uint32_t index)
{
    return GetFrameChildByIndex(index, false);
}

const RefPtr<LayoutAlgorithmWrapper>& FrameNode::GetLayoutAlgorithm(bool needReset)
{
    if ((!layoutAlgorithm_ || (needReset && layoutAlgorithm_->IsExpire())) && pattern_) {
        if (kitNode_ && kitNode_->GetPattern()) {
            layoutAlgorithm_ =
                LayoutAlgorithmWrapper::CreateLayoutAlgorithmWrapper(kitNode_->GetPattern()->CreateLayoutAlgorithm());
        } else {
            layoutAlgorithm_ = MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm());
        }
    }
    if (needReset) {
        layoutAlgorithm_->SetNeedMeasure();
    }
    return layoutAlgorithm_;
}

void FrameNode::SetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
{
    frameProxy_->SetCacheCount(cacheCount, itemConstraint);
}

void FrameNode::LayoutOverlay()
{
    auto size = geometryNode_->GetFrameSize();
    auto align = Alignment::TOP_LEFT;
    Dimension offsetX, offsetY;
    auto childLayoutProperty = overlayNode_->GetLayoutProperty();
    childLayoutProperty->GetOverlayOffset(offsetX, offsetY);
    auto offset = OffsetF(offsetX.ConvertToPx(), offsetY.ConvertToPx());
    if (childLayoutProperty->GetPositionProperty()) {
        align = childLayoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }

    auto childSize = overlayNode_->GetGeometryNode()->GetMarginFrameSize();
    auto translate = Alignment::GetAlignPosition(size, childSize, align) + offset;
    overlayNode_->GetGeometryNode()->SetMarginFrameOffset(translate);
    overlayNode_->Layout();
}

void FrameNode::DoRemoveChildInRenderTree(uint32_t index, bool isAll)
{
    isActive_ = false;
    SetActive(false);
}

void FrameNode::DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache)
{
    if (showCache) {
        start -= cacheStart;
        end += cacheEnd;
    }
    if (start <= end) {
        if (start > 0 || end < 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetActive(true);
            SetJSViewActive(true);
        }
    } else {
        if (end < 0 && start > 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetActive(true);
            SetJSViewActive(true);
        }
    }
}

void FrameNode::OnInspectorIdUpdate(const std::string& id)
{
    renderContext_->UpdateNodeName(id);
    ElementRegister::GetInstance()->AddFrameNodeByInspectorId(id, AceType::WeakClaim(this));
    auto parent = GetAncestorNodeOfFrame(true);
    if (parent && parent->GetTag() == V2::RELATIVE_CONTAINER_ETS_TAG) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (Recorder::EventRecorder::Get().IsExposureRecordEnable()) {
        if (exposureProcessor_) {
            return;
        }
        auto* context = GetContext();
        CHECK_NULL_VOID(context);
        context->AddAfterRenderTask([weak = WeakClaim(this), inspectorId = id]() {
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            auto pageUrl = Recorder::GetPageUrlByNode(host);
            host->exposureProcessor_ = MakeRefPtr<Recorder::ExposureProcessor>(pageUrl, inspectorId);
            if (!host->exposureProcessor_->IsNeedRecord()) {
                return;
            }
            host->RecordExposureInner();
        });
    }
}

void FrameNode::OnAutoEventParamUpdate(const std::string& value)
{
    if (value.empty()) {
        return;
    }
    auto paramJson = JsonUtil::ParseJsonString(value);
    if (paramJson == nullptr || !paramJson->IsValid() || !paramJson->IsObject()) {
        return;
    }
    if (paramJson->Contains(Recorder::ORIGIN_PARAM)) {
        propAutoEventParam_ = paramJson->GetValue(Recorder::ORIGIN_PARAM)->ToString();
    }
    if (exposureProcessor_ && exposureProcessor_->isListening()) {
        return;
    }
    if (!paramJson->Contains(Recorder::EXPOSURE_CONFIG_PARAM)) {
        return;
    }
    auto exposureCfg = paramJson->GetValue(Recorder::EXPOSURE_CONFIG_PARAM);
    if (exposureCfg && exposureCfg->IsObject()) {
        auto ratio = exposureCfg->GetDouble(Recorder::EXPOSURE_CONFIG_RATIO);
        auto duration = exposureCfg->GetInt(Recorder::EXPOSURE_CONFIG_DURATION);
        if (duration <= 0) {
            return;
        }
        auto* context = GetContext();
        CHECK_NULL_VOID(context);
        context->AddAfterRenderTask([weak = WeakClaim(this), ratio, duration]() {
            auto host = weak.Upgrade();
            CHECK_NULL_VOID(host);
            if (host->exposureProcessor_ && host->exposureProcessor_->isListening()) {
                return;
            }
            auto pageUrl = Recorder::GetPageUrlByNode(host);
            host->exposureProcessor_ =
                MakeRefPtr<Recorder::ExposureProcessor>(pageUrl, host->GetInspectorIdValue(""), ratio, duration);
            if (!host->exposureProcessor_->IsNeedRecord()) {
                return;
            }
            host->RecordExposureInner();
        });
    }
}

void FrameNode::SetExposureProcessor(const RefPtr<Recorder::ExposureProcessor>& processor)
{
    if (exposureProcessor_ && exposureProcessor_->isListening()) {
        return;
    } else {
        exposureProcessor_ = MakeRefPtr<Recorder::ExposureProcessor>(processor);
        exposureProcessor_->SetContainerId(processor->GetContainerId());
    }
    exposureProcessor_->OnVisibleChange(true, "");
    RecordExposureInner();
}

void FrameNode::RecordExposureInner()
{
    auto pipeline = GetContext();
    if (!pipeline) {
        auto piplineRef = PipelineContext::GetContextByContainerId(exposureProcessor_->GetContainerId());
        if (!piplineRef) {
            pipeline = Referenced::RawPtr(piplineRef);
        }
    }
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(RawPtr(exposureProcessor_)), weakNode = WeakClaim(this)](
                        bool visible, double ratio) {
        auto processor = weak.Upgrade();
        CHECK_NULL_VOID(processor);
        if (!visible) {
            auto host = weakNode.Upgrade();
            auto param = host ? host->GetAutoEventParamValue("") : "";
            processor->OnVisibleChange(false, param);
        } else {
            processor->OnVisibleChange(visible);
        }
    };
    std::vector<double> ratios = { exposureProcessor_->GetRatio() };
    pipeline->AddVisibleAreaChangeNode(Claim(this), ratios, callback, false);
    exposureProcessor_->SetListenState(true);
}

void FrameNode::AddFrameNodeSnapshot(
    bool isHit, int32_t parentId, std::vector<RectF> responseRegionList, EventTreeType type)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    auto eventMgr = context->GetEventManager();
    CHECK_NULL_VOID(eventMgr);

    FrameNodeSnapshot info = { .nodeId = GetId(),
        .parentNodeId = parentId,
        .tag = GetTag(),
        .comId = propInspectorId_.value_or(""),
        .monopolizeEvents = GetMonopolizeEvents(),
        .isHit = isHit,
        .hitTestMode = static_cast<int32_t>(GetHitTestMode()),
        .responseRegionList = responseRegionList,
        .active = isActive_ };
    eventMgr->GetEventTreeRecord(type).AddFrameNodeSnapshot(std::move(info));
}

int32_t FrameNode::GetUiExtensionId()
{
    if (pattern_) {
        return pattern_->GetUiExtensionId();
    }
    return -1;
}

int64_t FrameNode::WrapExtensionAbilityId(int64_t extensionOffset, int64_t abilityId)
{
    if (pattern_) {
        return pattern_->WrapExtensionAbilityId(extensionOffset, abilityId);
    }
    return -1;
}

void FrameNode::SearchExtensionElementInfoByAccessibilityIdNG(
    int64_t elementId, int32_t mode, int64_t offset, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    if (pattern_) {
        pattern_->SearchExtensionElementInfoByAccessibilityId(elementId, mode, offset, output);
    }
}

void FrameNode::SearchElementInfosByTextNG(int64_t elementId, const std::string& text, int64_t offset,
    std::list<Accessibility::AccessibilityElementInfo>& output)
{
    if (pattern_) {
        pattern_->SearchElementInfosByText(elementId, text, offset, output);
    }
}

void FrameNode::FindFocusedExtensionElementInfoNG(
    int64_t elementId, int32_t focusType, int64_t offset, Accessibility::AccessibilityElementInfo& output)
{
    if (pattern_) {
        pattern_->FindFocusedElementInfo(elementId, focusType, offset, output);
    }
}

void FrameNode::FocusMoveSearchNG(
    int64_t elementId, int32_t direction, int64_t offset, Accessibility::AccessibilityElementInfo& output)
{
    if (pattern_) {
        pattern_->FocusMoveSearch(elementId, direction, offset, output);
    }
}

bool FrameNode::TransferExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    bool isExecuted = false;
    if (pattern_) {
        isExecuted = pattern_->TransferExecuteAction(elementId, actionArguments, action, offset);
    }
    return isExecuted;
}

TouchResult FrameNode::GetOnChildTouchTestRet(const std::vector<TouchTestInfo>& touchInfo)
{
    TouchResult res;
    res.strategy = TouchTestStrategy::DEFAULT;

    auto func = GetOnTouchTestFunc();
    if (func == nullptr) {
        return res;
    }
    return func(touchInfo);
}

OnChildTouchTestFunc FrameNode::GetOnTouchTestFunc()
{
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    if (gestureHub == nullptr) {
        return nullptr;
    }
    auto& func = gestureHub->GetOnTouchTestFunc();
    return func;
}

void FrameNode::CollectTouchInfos(
    const PointF& globalPoint, const PointF& parentRevertPoint, std::vector<TouchTestInfo>& touchInfos)
{
    if (GetOnTouchTestFunc() == nullptr) {
        return;
    }

    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        const auto& child = iter->Upgrade();
        if (!child) {
            continue;
        }

        TouchTestInfo info;
        if (!child->GetInspectorId().has_value()) {
            continue;
        }
        info.id = child->GetInspectorId().value();
        info.windowPoint = globalPoint;
        info.currentCmpPoint = parentRevertPoint;

        auto renderContext = child->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        auto origRect = renderContext->GetPaintRectWithoutTransform();
        auto revertPoint = parentRevertPoint;
        renderContext->GetPointWithRevert(revertPoint);
        auto subRevertPoint = revertPoint - origRect.GetOffset();
        info.subCmpPoint = subRevertPoint;

        info.subRect = child->GetGeometryNode()->GetFrameRect();

        touchInfos.emplace_back(info);
    }
}

RefPtr<FrameNode> FrameNode::GetDispatchFrameNode(const TouchResult& touchRes)
{
    if (touchRes.strategy != TouchTestStrategy::FORWARD_COMPETITION &&
        touchRes.strategy != TouchTestStrategy::FORWARD) {
        return nullptr;
    }

    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        const auto& child = iter->Upgrade();
        if (!child) {
            continue;
        }
        std::string id = child->GetInspectorId().value_or("");
        if ((!touchRes.id.empty()) && (touchRes.id == id)) {
            return child;
        }
    }
    return nullptr;
}

OffsetF FrameNode::CalculateCachedTransformRelativeOffset(uint64_t nanoTimestamp)
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto offset = context->GetPaintRectWithTransform().GetOffset();

    auto parent = GetAncestorNodeOfFrame(true);
    if (parent) {
        auto parentTimestampOffset = parent->GetCachedTransformRelativeOffset();
        if (parentTimestampOffset.first == nanoTimestamp) {
            auto result = offset + parentTimestampOffset.second;
            SetCachedTransformRelativeOffset({ nanoTimestamp, result });
            return result;
        }
        auto result = offset + parent->CalculateCachedTransformRelativeOffset(nanoTimestamp);
        SetCachedTransformRelativeOffset({ nanoTimestamp, result });
        return result;
    }
    SetCachedTransformRelativeOffset({ nanoTimestamp, offset });
    return offset;
}

OffsetF FrameNode::CalculateOffsetRelativeToWindow(uint64_t nanoTimestamp, bool logFlag)
{
    auto currOffset = geometryNode_->GetFrameOffset();
    if (renderContext_ && renderContext_->GetPositionProperty()) {
        if (renderContext_->GetPositionProperty()->HasPosition()) {
            auto renderPosition =
                ContextPositionConvertToPX(renderContext_, layoutProperty_->GetLayoutConstraint()->percentReference);
            currOffset.SetX(static_cast<float>(renderPosition.first));
            currOffset.SetY(static_cast<float>(renderPosition.second));
        }
    }

    auto parent = GetAncestorNodeOfFrame(true);
    if (parent) {
        auto parentTimestampOffset = parent->GetCachedGlobalOffset();
        if (parentTimestampOffset.first == nanoTimestamp) {
            currOffset = currOffset + parentTimestampOffset.second;
            SetCachedGlobalOffset({ nanoTimestamp, currOffset });
        } else {
            currOffset = currOffset + parent->CalculateOffsetRelativeToWindow(nanoTimestamp, logFlag);
            SetCachedGlobalOffset({ nanoTimestamp, currOffset });
        }
    } else {
        SetCachedGlobalOffset({ nanoTimestamp, currOffset });
    }
    if (logFlag) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnAreaChange Node(%{public}s/%{public}d) offsetToWindow:%{public}s",
            GetTag().c_str(), GetId(), currOffset.ToString().c_str());
    }
    return currOffset;
}

RefPtr<FrameNode> FrameNode::GetNodeContainer()
{
    if (GetTag() == V2::NODE_CONTAINER_ETS_TAG) {
        return Claim(this);
    }
    auto parent = GetParent();
    while (parent && parent->GetTag() != V2::NODE_CONTAINER_ETS_TAG) {
        parent = parent->GetParent();
    }
    return AceType::DynamicCast<FrameNode>(parent);
}

void FrameNode::InitLastArea()
{
    if (!lastFrameRect_) {
        lastFrameRect_ = std::make_unique<RectF>();
    }
    if (!lastParentOffsetToWindow_) {
        lastParentOffsetToWindow_ = std::make_unique<OffsetF>();
    }
    if (!lastHostParentOffsetToWindow_) {
        lastHostParentOffsetToWindow_ = std::make_shared<OffsetF>();
    }
}

bool FrameNode::SetParentLayoutConstraint(const SizeF& size) const
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.UpdatePercentReference(size);
    layoutConstraint.UpdateMaxSizeWithCheck(size);
    layoutConstraint.UpdateIllegalParentIdealSizeWithCheck(OptionalSize(size));
    layoutProperty_->UpdateParentLayoutConstraint(layoutConstraint);
    return true;
}

void FrameNode::ForceSyncGeometryNode()
{
    CHECK_NULL_VOID(renderContext_);
    oldGeometryNode_.Reset();
    renderContext_->SavePaintRect();
    renderContext_->SyncGeometryProperties(RawPtr(geometryNode_));
}

bool FrameNode::IsGeometrySizeChange() const
{
    if (oldGeometryNode_ && geometryNode_) {
        return oldGeometryNode_->GetFrameSize() != geometryNode_->GetFrameSize();
    }
    return false;
}

const std::pair<uint64_t, OffsetF>& FrameNode::GetCachedGlobalOffset() const
{
    return cachedGlobalOffset_;
}

void FrameNode::SetCachedGlobalOffset(const std::pair<uint64_t, OffsetF>& timestampOffset)
{
    cachedGlobalOffset_ = timestampOffset;
}
const std::pair<uint64_t, OffsetF>& FrameNode::GetCachedTransformRelativeOffset() const
{
    return cachedTransformRelativeOffset_;
}

void FrameNode::SetCachedTransformRelativeOffset(const std::pair<uint64_t, OffsetF>& timestampOffset)
{
    cachedTransformRelativeOffset_ = timestampOffset;
}

void FrameNode::PaintDebugBoundary(bool flag)
{
    if (!isActive_) {
        return;
    }
    if (renderContext_) {
        renderContext_->PaintDebugBoundary(flag);
    }
}

void SetChangeInfo(const TouchEvent& touchEvent, TouchLocationInfo &changedInfo)
{
    changedInfo.SetGlobalLocation(Offset(touchEvent.x, touchEvent.y));
    changedInfo.SetScreenLocation(Offset(touchEvent.screenX, touchEvent.screenY));
    changedInfo.SetTouchType(touchEvent.type);
    changedInfo.SetForce(touchEvent.force);
    changedInfo.SetPressedTime(touchEvent.pressedTime);
    changedInfo.SetWidth(touchEvent.width);
    changedInfo.SetHeight(touchEvent.height);
    if (touchEvent.tiltX.has_value()) {
        changedInfo.SetTiltX(touchEvent.tiltX.value());
    }
    if (touchEvent.tiltY.has_value()) {
        changedInfo.SetTiltY(touchEvent.tiltY.value());
    }
    changedInfo.SetSourceTool(touchEvent.sourceTool);
    changedInfo.SetDeviceId(touchEvent.deviceId);
}

HitTestMode FrameNode::TriggerOnTouchIntercept(const TouchEvent& touchEvent)
{
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    CHECK_NULL_RETURN(gestureHub, HitTestMode::HTMDEFAULT);
    auto onTouchIntercept = gestureHub->GetOnTouchIntercept();
    CHECK_NULL_RETURN(onTouchIntercept, HitTestMode::HTMDEFAULT);
    TouchEventInfo event("touchEvent");
    event.SetTimeStamp(touchEvent.time);
    event.SetDeviceId(touchEvent.deviceId);
    event.SetPointerEvent(touchEvent.GetTouchEventPointerEvent());
    TouchLocationInfo changedInfo("onTouch", touchEvent.originalId);
    PointF lastLocalPoint(touchEvent.x, touchEvent.y);
    NGGestureRecognizer::Transform(lastLocalPoint, Claim(this), false, false);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    changedInfo.SetLocalLocation(Offset(localX, localY));
    SetChangeInfo(touchEvent, changedInfo);
    event.AddChangedTouchLocationInfo(std::move(changedInfo));

    AddTouchEventAllFingersInfo(event, touchEvent);
    event.SetSourceDevice(touchEvent.sourceType);
    event.SetForce(touchEvent.force);
    if (touchEvent.tiltX.has_value()) {
        event.SetTiltX(touchEvent.tiltX.value());
    }
    if (touchEvent.tiltY.has_value()) {
        event.SetTiltY(touchEvent.tiltY.value());
    }
    if (touchEvent.rollAngle.has_value()) {
        event.SetRollAngle(touchEvent.rollAngle.value());
    }
    event.SetSourceTool(touchEvent.sourceTool);
    EventTarget eventTarget;
    eventTarget.id = GetInspectorId().value_or("").c_str();
    event.SetTarget(eventTarget);
    auto result = onTouchIntercept(event);
    SetHitTestMode(result);
    return result;
}

void FrameNode::AddTouchEventAllFingersInfo(TouchEventInfo& event, const TouchEvent& touchEvent)
{
    // all fingers collection
    for (const auto& item : touchEvent.pointers) {
        float globalX = item.x;
        float globalY = item.y;
        float screenX = item.screenX;
        float screenY = item.screenY;
        PointF localPoint(globalX, globalY);
        NGGestureRecognizer::Transform(localPoint, Claim(this), false, false);
        auto localX = static_cast<float>(localPoint.GetX());
        auto localY = static_cast<float>(localPoint.GetY());
        TouchLocationInfo info("onTouch", item.originalId);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetTouchType(touchEvent.type);
        info.SetForce(item.force);
        info.SetPressedTime(item.downTime);
        info.SetWidth(item.width);
        info.SetHeight(item.height);
        if (item.tiltX.has_value()) {
            info.SetTiltX(item.tiltX.value());
        }
        if (item.tiltY.has_value()) {
            info.SetTiltY(item.tiltY.value());
        }
        info.SetSourceTool(item.sourceTool);
        event.AddTouchLocationInfo(std::move(info));
    }
}

void FrameNode::ChangeSensitiveStyle(bool isSensitive)
{
    pattern_->OnSensitiveStyleChange(isSensitive);
}

void FrameNode::AttachContext(PipelineContext* context, bool recursive)
{
    UINode::AttachContext(context, recursive);
    if (eventHub_) {
        eventHub_->OnAttachContext(context);
    }
    pattern_->OnAttachContext(context);
}

void FrameNode::DetachContext(bool recursive)
{
    CHECK_NULL_VOID(context_);
    pattern_->OnDetachContext(context_);
    if (eventHub_) {
        eventHub_->OnDetachContext(context_);
    }
    UINode::DetachContext(recursive);
}

void FrameNode::OnCollectRemoved()
{
    pattern_->OnCollectRemoved();
}

RectF FrameNode::ApplyFrameNodeTranformToRect(const RectF& rect, const RefPtr<FrameNode>& parent) const
{
    RectF newRect = rect;
    if (!parent) {
        return newRect;
    }

    auto parentRenderContext = parent->GetRenderContext();
    if (!parentRenderContext) {
        return newRect;
    }

    auto parentScale = parentRenderContext->GetTransformScale();
    auto offset = rect.GetOffset();
    if (parentScale) {
        newRect.SetWidth(rect.Width() * parentScale.value().x);
        newRect.SetHeight(rect.Height() * parentScale.value().y);
        offset = OffsetF(offset.GetX() * parentScale.value().x, offset.GetY() * parentScale.value().y);
    }
    offset += parentRenderContext->GetPaintRectWithTransform().GetOffset();
    newRect.SetOffset(offset);
    return newRect;
}

void FrameNode::GetVisibleRect(RectF& visibleRect, RectF& frameRect) const
{
    visibleRect = GetPaintRectWithTransform();
    frameRect = visibleRect;
    RefPtr<FrameNode> parentUi = GetAncestorNodeOfFrame(true);
    if (!parentUi) {
        visibleRect.SetWidth(0.0f);
        visibleRect.SetHeight(0.0f);
        return;
    }
    while (parentUi) {
        visibleRect = ApplyFrameNodeTranformToRect(visibleRect, parentUi);
        auto parentRect = parentUi->GetPaintRectWithTransform();
        visibleRect = visibleRect.Constrain(parentRect);
        if (visibleRect.IsEmpty()) {
            return;
        }
        frameRect = ApplyFrameNodeTranformToRect(frameRect, parentUi);
        parentUi = parentUi->GetAncestorNodeOfFrame(true);
    }
}

bool FrameNode::AllowVisibleAreaCheck() const
{
    return IsOnMainTree() || (pattern_ && pattern_->AllowVisibleAreaCheck());
}

void FrameNode::GetVisibleRectWithClip(RectF& visibleRect, RectF& visibleInnerRect, RectF& frameRect) const
{
    visibleRect = GetPaintRectWithTransform();
    frameRect = visibleRect;
    visibleInnerRect = visibleRect;
    RefPtr<FrameNode> parentUi = GetAncestorNodeOfFrame(true);
    if (!AllowVisibleAreaCheck() || !parentUi || IsFrameDisappear()) {
        visibleRect.SetWidth(0.0f);
        visibleRect.SetHeight(0.0f);
        visibleInnerRect.SetWidth(0.0f);
        visibleInnerRect.SetHeight(0.0f);
        return;
    }

    while (parentUi) {
        visibleRect = ApplyFrameNodeTranformToRect(visibleRect, parentUi);
        auto parentRect = parentUi->GetPaintRectWithTransform();
        if (!visibleRect.IsEmpty()) {
            visibleRect = visibleRect.Constrain(parentRect);
        }

        if (isCalculateInnerVisibleRectClip_) {
            visibleInnerRect = ApplyFrameNodeTranformToRect(visibleInnerRect, parentUi);
            auto parentContext = parentUi->GetRenderContext();
            if (!visibleInnerRect.IsEmpty() && ((parentContext && parentContext->GetClipEdge().value_or(false)) ||
                parentUi->IsWindowBoundary() || parentUi->GetTag() == V2::ROOT_ETS_TAG)) {
                visibleInnerRect = visibleInnerRect.Constrain(parentRect);
            }
        }

        if (visibleRect.IsEmpty() && (!isCalculateInnerVisibleRectClip_ || visibleInnerRect.IsEmpty())) {
            visibleInnerRect = visibleRect;
            return;
        }
        frameRect = ApplyFrameNodeTranformToRect(frameRect, parentUi);
        parentUi = parentUi->GetAncestorNodeOfFrame(true);
    }

    if (!isCalculateInnerVisibleRectClip_) {
        visibleInnerRect = visibleRect;
    }
}

CacheVisibleRectResult FrameNode::GetCacheVisibleRect(uint64_t timestamp, bool logFlag)
{
    RefPtr<FrameNode> parentUi = GetAncestorNodeOfFrame(true);
    auto rectToParent = GetPaintRectWithTransform();
    auto scale = GetTransformScale();
    auto innerScale = scale;
    if (renderContext_) {
        auto matrix4 = renderContext_->GetTransformMatrixValue(Matrix4());
        innerScale = { innerScale.x * static_cast<float>(matrix4.GetScaleX()),
            innerScale.y * static_cast<float>(matrix4.GetScaleY()) };
    }

    if (!parentUi || IsWindowBoundary()) {
        cachedVisibleRectResult_ = { timestamp,
            { rectToParent.GetOffset(), rectToParent.GetOffset(), rectToParent, rectToParent, scale, innerScale,
                rectToParent, rectToParent, rectToParent } };
        return cachedVisibleRectResult_.second;
    }

    CacheVisibleRectResult result;
    if (parentUi->cachedVisibleRectResult_.first == timestamp) {
        auto parentCacheVisibleRectResult = parentUi->cachedVisibleRectResult_.second;
        result = CalculateCacheVisibleRect(
            parentCacheVisibleRectResult, parentUi, rectToParent, { scale, innerScale }, timestamp);
    } else {
        CacheVisibleRectResult parentCacheVisibleRectResult = parentUi->GetCacheVisibleRect(timestamp, logFlag);
        result = CalculateCacheVisibleRect(
            parentCacheVisibleRectResult, parentUi, rectToParent, { scale, innerScale }, timestamp);
    }
    if (logFlag) {
        TAG_LOGD(AceLogTag::ACE_UIEVENT,
            "OnVisibleAreaChange Node(%{public}s/%{public}d) windowOffset:%{public}s visibleRect:%{public}s "
            "innerVisibleRect:%{public}s frameRect:%{public}s innerBoundaryRect:%{public}s",
            GetTag().c_str(), GetId(), result.windowOffset.ToString().c_str(), result.visibleRect.ToString().c_str(),
            result.innerVisibleRect.ToString().c_str(), result.frameRect.ToString().c_str(),
            result.innerBoundaryRect.ToString().c_str());
    }
    return result;
}

CacheVisibleRectResult FrameNode::CalculateCacheVisibleRect(CacheVisibleRectResult& parentCacheVisibleRect,
    const RefPtr<FrameNode>& parentUi, RectF& rectToParent, const std::pair<VectorF, VectorF>& pairScale,
    uint64_t timestamp)
{
    auto parentRenderContext = parentUi->GetRenderContext();
    OffsetF windowOffset;
    OffsetF innerWindowOffset;
    auto offset = rectToParent.GetOffset();
    auto innerOffset = rectToParent.GetOffset();
    if (parentRenderContext && parentRenderContext->GetTransformScale()) {
        auto parentScale = parentRenderContext->GetTransformScale();
        offset = OffsetF(offset.GetX() * parentScale.value().x, offset.GetY() * parentScale.value().y);
    }
    windowOffset = parentCacheVisibleRect.windowOffset + offset;

    innerOffset = OffsetF(innerOffset.GetX() * parentCacheVisibleRect.innerCumulativeScale.x,
        innerOffset.GetY() * parentCacheVisibleRect.innerCumulativeScale.y);
    innerWindowOffset = parentCacheVisibleRect.innerWindowOffset + innerOffset;

    RectF rect;
    rect.SetOffset(windowOffset);
    rect.SetWidth(rectToParent.Width() * parentCacheVisibleRect.cumulativeScale.x);
    rect.SetHeight(rectToParent.Height() * parentCacheVisibleRect.cumulativeScale.y);

    RectF innerRect;
    innerRect.SetOffset(innerWindowOffset);
    innerRect.SetWidth(rectToParent.Width() * parentCacheVisibleRect.innerCumulativeScale.x);
    innerRect.SetHeight(rectToParent.Height() * parentCacheVisibleRect.innerCumulativeScale.y);

    auto visibleRect = rect.Constrain(parentCacheVisibleRect.visibleRect);
    auto innerVisibleRect = innerRect;
    auto innerBoundaryRect = parentCacheVisibleRect.innerBoundaryRect;
    if (parentRenderContext && parentRenderContext->GetClipEdge().value_or(false)) {
        innerBoundaryRect = parentCacheVisibleRect.innerVisibleRect.Constrain(innerBoundaryRect);
    }
    innerVisibleRect = innerRect.Constrain(innerBoundaryRect);

    VectorF cumulativeScale = { pairScale.first.x * parentCacheVisibleRect.cumulativeScale.x,
        pairScale.first.y * parentCacheVisibleRect.cumulativeScale.y };
    VectorF innerCumulativeScale = { pairScale.second.x * parentCacheVisibleRect.innerCumulativeScale.x,
        pairScale.second.y * parentCacheVisibleRect.innerCumulativeScale.y };
    cachedVisibleRectResult_ = { timestamp,
        { windowOffset, innerWindowOffset, visibleRect, innerVisibleRect, cumulativeScale, innerCumulativeScale, rect,
            innerRect, innerBoundaryRect } };
    return { windowOffset, innerWindowOffset, visibleRect, innerVisibleRect, cumulativeScale, innerCumulativeScale,
        rect, innerRect, innerBoundaryRect };
}

bool FrameNode::IsContextTransparent()
{
    ACE_SCOPED_TRACE("Transparent detection");
    const auto& rect = renderContext_->GetPaintRectWithTransform();
    auto width = rect.Width();
    auto height = rect.Height();
    if (renderContext_->GetOpacity().has_value() && renderContext_->GetOpacity().value() <= MIN_OPACITY) {
        return true;
    }
    auto layoutTags = GetLayoutTags();
    if (layoutTags.find(GetTag()) == layoutTags.end()) {
        if (width > MIN_WIDTH && height > MIN_HEIGHT &&
            static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)) == 0) {
            return false;
        }
    } else {
        if (width > MIN_WIDTH && height > MIN_HEIGHT &&
            static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)) == 0 &&
            renderContext_->GetBackgroundColor()->ColorToString().compare("#00000000") != 0) {
            return false;
        }
    }
    for (const auto& item : GetChildren()) {
        if (!item->IsContextTransparent()) {
            return false;
        }
    }
    return true;
}

CacheMatrixInfo& FrameNode::GetOrRefreshMatrixFromCache(bool forceRefresh)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, cacheMatrixInfo_);
    auto nanoTimestamp = pipeline->GetVsyncTime();
    CHECK_NULL_RETURN(renderContext_, cacheMatrixInfo_);
    auto rect = renderContext_->GetPaintRectWithoutTransform();
    // the caller is trying to refresh cache forcedly or the cache is invalid
    if (!isTransformNotChanged_ || forceRefresh || prePaintRect_ != rect ||
        getCacheNanoTime_ + MATRIX_CACHE_TIME_THRESHOLD < nanoTimestamp) {
        cacheMatrixInfo_.revertMatrix = renderContext_->GetRevertMatrix();
        cacheMatrixInfo_.paintRectWithTransform = renderContext_->GetPaintRectWithTransform();
        cacheMatrixInfo_.localMatrix = Matrix4::CreateTranslate(-rect.GetOffset().GetX(),
            -rect.GetOffset().GetY(), 0) * cacheMatrixInfo_.revertMatrix;
        isTransformNotChanged_ = true;
        getCacheNanoTime_ = nanoTimestamp;
        prePaintRect_ = rect;
        return cacheMatrixInfo_;
    }

    // cache valid
    return cacheMatrixInfo_;
}

// apply the matrix to the given point specified by dst
void FrameNode::MapPointTo(PointF& dst, Matrix4& matrix)
{
    Point tmp(dst.GetX(), dst.GetY());
    auto transformPoint = matrix * tmp;
    dst.SetX(transformPoint.GetX());
    dst.SetY(transformPoint.GetY());
}

void FrameNode::SetSuggestOpIncMarked(bool flag)
{
    if (flag) {
        suggestOpIncByte_ |= SUGGEST_OPINC_MARKED_MASK;
    } else {
        suggestOpIncByte_ &= (~SUGGEST_OPINC_MARKED_MASK);
    }
}

bool FrameNode::GetSuggestOpIncMarked()
{
    return (suggestOpIncByte_ & SUGGEST_OPINC_MARKED_MASK) > 0;
}

void FrameNode::SetCanSuggestOpInc(bool flag)
{
    if (flag) {
        suggestOpIncByte_ |= CAN_SUGGEST_OPINC_MASK;
    } else {
        suggestOpIncByte_ &= (~CAN_SUGGEST_OPINC_MASK);
    }
}

bool FrameNode::GetCanSuggestOpInc()
{
    return (suggestOpIncByte_ & CAN_SUGGEST_OPINC_MASK) > 0;
}

void FrameNode::SetApplicationRenderGroupMarked(bool flag)
{
    if (flag) {
        suggestOpIncByte_ |= APP_RENDER_GROUP_MARKED_MASK;
    } else {
        suggestOpIncByte_ &= (~APP_RENDER_GROUP_MARKED_MASK);
    }
}

bool FrameNode::GetApplicationRenderGroupMarked()
{
    return (suggestOpIncByte_ & APP_RENDER_GROUP_MARKED_MASK) > 0;
}

void FrameNode::SetSuggestOpIncActivatedOnce()
{
    suggestOpIncByte_ |= SUGGEST_OPINC_ACTIVATED_ONCE;
}

bool FrameNode::GetSuggestOpIncActivatedOnce()
{
    return (suggestOpIncByte_ & SUGGEST_OPINC_ACTIVATED_ONCE) > 0;
}

void FrameNode::SetOpIncGroupCheckedThrough(bool flag)
{
    if (flag) {
        suggestOpIncByte_ |= SUGGEST_OPINC_CHECKED_THROUGH;
    } else {
        suggestOpIncByte_ &= (~SUGGEST_OPINC_CHECKED_THROUGH);
    }
}

bool FrameNode::GetOpIncGroupCheckedThrough()
{
    return (suggestOpIncByte_ & SUGGEST_OPINC_CHECKED_THROUGH) > 0;
}

void FrameNode::SetOpIncCheckedOnce()
{
    suggestOpIncByte_ |= SUGGEST_OPINC_CHCKED_ONCE;
}
bool FrameNode::GetOpIncCheckedOnce()
{
    return (suggestOpIncByte_ & SUGGEST_OPINC_CHCKED_ONCE) > 0;
}

bool FrameNode::MarkSuggestOpIncGroup(bool suggest, bool calc)
{
    CHECK_NULL_RETURN(renderContext_, false);
    renderContext_->SuggestOpIncNode(suggest, calc);
    SetSuggestOpIncMarked(suggest);
    return true;
}

OPINC_TYPE_E FrameNode::IsOpIncValidNode(const SizeF& boundary, Axis axis, int32_t childNumber)
{
    int32_t height = static_cast<int>(GetGeometryNode()->GetFrameSize().Height());
    int32_t width = static_cast<int>(GetGeometryNode()->GetFrameSize().Width());
    int32_t heightBoundary = static_cast<int>(boundary.Height() * HIGHT_RATIO_LIMIT);
    int32_t widthBoundary = static_cast<int>(boundary.Width() * WIDTH_RATIO_LIMIT);
    int32_t area = height * width;
    if (area >= MIN_OPINC_AREA &&
        ((axis == Axis::VERTICAL && height <= heightBoundary) ||
        (axis == Axis::HORIZONTAL && width <= widthBoundary)) &&
        HasMultipleChild()) {
        return OPINC_NODE;
    }
    return OPINC_INVALID;
}

bool FrameNode::HasMultipleChild()
{
    if (GetChildren().empty()) {
        return false;
    }
    if (GetChildren().size() > 1) {
        return true;
    }
    auto child = AceType::DynamicCast<FrameNode>(GetChildByIndex(0));
    CHECK_NULL_RETURN(child, false);
    return child->HasMultipleChild();
}

OPINC_TYPE_E FrameNode::FindSuggestOpIncNode(std::string& path, const SizeF& boundary, int32_t depth, Axis axis)
{
    if (GetSuggestOpIncActivatedOnce()) {
        return OPINC_SUGGESTED_OR_EXCLUDED;
    }
    SetSuggestOpIncActivatedOnce();

    if (GetApplicationRenderGroupMarked()) {
        return OPINC_INVALID;
    }
    auto status = IsOpIncValidNode(boundary, axis);
    if (SystemProperties::GetDebugEnabled()) {
        const auto& hostTag = GetHostTag();
        path = path + " --> " + hostTag;
        LOGD("FindSuggestOpIncNode : %{public}s, with depth %{public}d, boundary: %{public}f, self: %{public}f, "
             "status: %{public}d",
            path.c_str(), depth, boundary.Height(), GetGeometryNode()->GetFrameSize().Height(), status);
    }
    if (status == OPINC_NODE) {
        MarkSuggestOpIncGroup(true, true);
        return OPINC_SUGGESTED_OR_EXCLUDED;
    } else if (status == OPINC_SUGGESTED_OR_EXCLUDED) {
        return OPINC_SUGGESTED_OR_EXCLUDED;
    } else if (status == OPINC_PARENT_POSSIBLE) {
        std::list<RefPtr<FrameNode>> childrens;
        GenerateOneDepthVisibleFrame(childrens);
        for (auto& child : childrens) {
            if (child) {
                status = child->FindSuggestOpIncNode(path, boundary, depth + 1, axis);
            }
            if (status == OPINC_INVALID) {
                    return OPINC_INVALID;
            }
        }
        return OPINC_PARENT_POSSIBLE;
    } else if (status == OPINC_INVALID) {
        return OPINC_INVALID;
    }
    return OPINC_SUGGESTED_OR_EXCLUDED;
}

void FrameNode::MarkAndCheckNewOpIncNode(Axis axis)
{
    if (!IsActive() || GetSuggestOpIncActivatedOnce() || GetApplicationRenderGroupMarked()) {
        return;
    }
    auto parent = GetAncestorNodeOfFrame(true);
    CHECK_NULL_VOID(parent);
    if (parent->GetSuggestOpIncActivatedOnce()) {
        SetSuggestOpIncActivatedOnce();
        auto status = IsOpIncValidNode(parent->GetGeometryNode()->GetFrameSize(), axis);
        ACE_SCOPED_TRACE("MarkAndCheckNewOpIncNode id:%d, tag:%s, status: %d", GetId(), GetTag().c_str(), status);
        if (status == OPINC_NODE) {
            SetCanSuggestOpInc(true);
            MarkSuggestOpIncGroup(true, true);
        }
    }
}

int FrameNode::GetValidLeafChildNumber(const RefPtr<FrameNode>& host, int32_t thresh)
{
    CHECK_NULL_RETURN(host, 0);
    auto total = 0;
    auto childSize = host->GetTotalChildCount();
    if (childSize < 1) {
        return 1;
    }
    for (auto i = 0; i < childSize; i++) {
        auto child = AceType::DynamicCast<FrameNode>(host->GetChildByIndex(i));
        if (!child) {
            continue;
        }
        total += GetValidLeafChildNumber(child, thresh);
        if (total >= thresh) {
            return total;
        }
    }
    return total;
}

void FrameNode::TriggerShouldParallelInnerWith(
    const ResponseLinkResult& currentRecognizers, const ResponseLinkResult& responseLinkRecognizers)
{
    auto gestureHub = eventHub_ ? eventHub_->GetGestureEventHub() : nullptr;
    CHECK_NULL_VOID(gestureHub);
    auto shouldBuiltInRecognizerParallelWithFunc = gestureHub->GetParallelInnerGestureToFunc();
    CHECK_NULL_VOID(shouldBuiltInRecognizerParallelWithFunc);
    std::map<GestureTypeName, std::vector<RefPtr<NGGestureRecognizer>>> sortedResponseLinkRecognizers;

    for (const auto& item : responseLinkRecognizers) {
        auto recognizer = AceType::DynamicCast<NGGestureRecognizer>(item);
        if (!recognizer) {
            continue;
        }
        auto type = recognizer->GetRecognizerType();
        sortedResponseLinkRecognizers[type].emplace_back(item);
    }

    for (const auto& item : currentRecognizers) {
        if (!item->IsSystemGesture() || item->GetRecognizerType() != GestureTypeName::PAN_GESTURE) {
            continue;
        }
        auto multiRecognizer = AceType::DynamicCast<MultiFingersRecognizer>(item);
        if (!multiRecognizer || multiRecognizer->GetTouchPointsSize() > 1) {
            continue;
        }
        auto iter = sortedResponseLinkRecognizers.find(item->GetRecognizerType());
        if (iter == sortedResponseLinkRecognizers.end() || iter->second.empty()) {
            continue;
        }
        auto result = shouldBuiltInRecognizerParallelWithFunc(item, iter->second);
        if (result && item != result) {
            item->SetBridgeMode(true);
            result->AddBridgeObj(item);
        }
    }
}

void FrameNode::GetInspectorValue()
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(OHOS_PLATFORM)
    if (GetTag() == V2::WEB_ETS_TAG) {
        UiSessionManager::GetInstance()->WebTaskNumsChange(1);
        auto pattern = GetPattern<NG::WebPattern>();
        CHECK_NULL_VOID(pattern);
        auto cb = [](std::shared_ptr<JsonValue> value, int32_t webId) {
            UiSessionManager::GetInstance()->AddValueForTree(webId, value->ToString());
            UiSessionManager::GetInstance()->WebTaskNumsChange(-1);
        };
        pattern->GetAllWebAccessibilityNodeInfos(cb, GetId());
    }
#endif
    UINode::GetInspectorValue();
}

void FrameNode::ClearSubtreeLayoutAlgorithm(bool includeSelf, bool clearEntireTree)
{
    // return when reaches a child that has no layoutAlgorithm and no need to clear the entire tree
    if (!layoutAlgorithm_ && !clearEntireTree) {
        return;
    }
    // include Self might be false for the first ClearSubtreeLayoutAlgorithm enter,
    // but children should always include themselves
    if (includeSelf) {
        layoutAlgorithm_.Reset();
    }
    for (const auto& child : GetChildren()) {
        child->ClearSubtreeLayoutAlgorithm(true, clearEntireTree);
    }
}

void FrameNode::OnSyncGeometryFrameFinish(const RectF& paintRect)
{
    if (syncedFramePaintRect_.has_value() && syncedFramePaintRect_.value() != paintRect) {
        AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_GEOMETRY_CHANGE);
        if (AnimationUtils::IsImplicitAnimationOpen()) {
            AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_ANIMATION);
        }
    }
    syncedFramePaintRect_ = paintRect;
}

void FrameNode::AddFrameNodeChangeInfoFlag(FrameNodeChangeInfoFlag changeFlag)
{
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    if (changeFlag == FRAME_NODE_CHANGE_GEOMETRY_CHANGE || changeFlag == FRAME_NODE_CHANGE_TRANSITION_START ||
        changeFlag == FRAME_NODE_CHANGE_TRANSFORM_CHANGE) {
        context->SetIsTransFlag(true);
    }
    if (changeInfoFlag_ == FRAME_NODE_CHANGE_INFO_NONE) {
        if (!context->AddChangedFrameNode(WeakClaim(this))) {
            return;
        }
    }
    changeInfoFlag_ = changeInfoFlag_ | changeFlag;
}

void FrameNode::RegisterNodeChangeListener()
{
    ACE_LAYOUT_SCOPED_TRACE("RegisterNodeChangeListener:%s,%d", GetTag().c_str(), GetId());
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->AddFrameNodeChangeListener(WeakClaim(this));
}

void FrameNode::UnregisterNodeChangeListener()
{
    ACE_LAYOUT_SCOPED_TRACE("UnregisterNodeChangeListener:%s,%d", GetTag().c_str(), GetId());
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RemoveFrameNodeChangeListener(GetId());
}

void FrameNode::ProcessFrameNodeChangeFlag()
{
    ACE_LAYOUT_SCOPED_TRACE("ProcessFrameNodeChangeFlag:%s,%d", GetTag().c_str(), GetId());
    auto changeFlag = FRAME_NODE_CHANGE_INFO_NONE;
    auto parent = Claim(this);
    while (parent) {
        if (parent->GetChangeInfoFlag() != FRAME_NODE_CHANGE_INFO_NONE) {
            changeFlag = changeFlag | parent->GetChangeInfoFlag();
        }
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    if (changeFlag == FRAME_NODE_CHANGE_INFO_NONE) {
        return;
    }
    auto pattern = GetPattern();
    if (pattern) {
        ACE_LAYOUT_SCOPED_TRACE("OnFrameNodeChanged:%s,%d", GetTag().c_str(), GetId());
        pattern->OnFrameNodeChanged(changeFlag);
    }
}

void FrameNode::OnNodeTransformInfoUpdate(bool changed)
{
    if (!changed) {
        return;
    }
    AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_TRANSFORM_CHANGE);
    if (AnimationUtils::IsImplicitAnimationOpen()) {
        AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_ANIMATION);
    }
}

void FrameNode::OnNodeTransitionInfoUpdate()
{
    AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_TRANSITION_START);
}

void FrameNode::NotifyWebPattern(bool isRegister)
{
#if !defined(PREVIEW) && !defined(ACE_UNITTEST) && defined(WEB_SUPPORTED) && defined(OHOS_PLATFORM)
    if (GetTag() == V2::WEB_ETS_TAG) {
        auto pattern = GetPattern<NG::WebPattern>();
        CHECK_NULL_VOID(pattern);
        if (isRegister) {
            auto callback = [](int64_t accessibilityId, const std::string data) {
                UiSessionManager::GetInstance()->ReportWebUnfocusEvent(accessibilityId, data);
            };
            pattern->RegisterTextBlurCallback(callback);
        } else {
            pattern->UnRegisterTextBlurCallback();
        }
    }
#endif
    UINode::NotifyWebPattern(isRegister);
}

uint32_t FrameNode::GetWindowPatternType() const
{
    CHECK_NULL_RETURN(pattern_, 0);
    return pattern_->GetWindowPatternType();
}

void FrameNode::NotifyChange(int32_t index, int32_t count, int64_t id, NotificationType notificationType)
{
    int32_t updateFrom = CalcAbsPosition(index, id);
    auto pattern = GetPattern();
    switch (notificationType) {
        case NotificationType::START_CHANGE_POSITION:
            ChildrenUpdatedFrom(updateFrom);
            break;
        case NotificationType::END_CHANGE_POSITION:
            pattern->NotifyDataChange(updateFrom, count);
            break;
        case NotificationType::START_AND_END_CHANGE_POSITION:
            ChildrenUpdatedFrom(updateFrom);
            pattern->NotifyDataChange(updateFrom, count);
            break;
        default:
            break;
    }
}

// for Grid refresh GridItems
void FrameNode::ChildrenUpdatedFrom(int32_t index)
{
    childrenUpdatedFrom_ = childrenUpdatedFrom_ >= 0 ? std::min(index, childrenUpdatedFrom_) : index;
}

void FrameNode::OnThemeScopeUpdate(int32_t themeScopeId)
{
    TAG_LOGD(AceLogTag::ACE_DEFAULT_DOMAIN, "WithTheme Node(%{public}s/%{public}d) OnThemeScopeUpdate id:%{public}d",
        GetTag().c_str(), GetId(), themeScopeId);
    if (pattern_->OnThemeScopeUpdate(themeScopeId)) {
        MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void FrameNode::DumpOnSizeChangeInfo(std::unique_ptr<JsonValue>& json)
{
    std::unique_ptr<JsonValue> children = JsonUtil::CreateArray(true);
    for (auto it = onSizeChangeDumpInfos.rbegin(); it != onSizeChangeDumpInfos.rend(); ++it) {
        std::unique_ptr<JsonValue> child = JsonUtil::Create(true);
        child->Put("onSizeChange Time", it->onSizeChangeTimeStamp);
        child->Put("lastFrameRect", it->lastFrameRect.ToString().c_str());
        child->Put("currFrameRect", it->currFrameRect.ToString().c_str());
        children->Put(child);
    }
    children->Put("SizeChangeInfo", children);
}

void FrameNode::DumpOverlayInfo(std::unique_ptr<JsonValue>& json)
{
    if (!layoutProperty_->IsOverlayNode()) {
        return;
    }
    json->Put("IsOverlayNode", "true");
    Dimension offsetX, offsetY;
    layoutProperty_->GetOverlayOffset(offsetX, offsetY);
    std::unique_ptr<JsonValue> children = JsonUtil::Create(true);
    children->Put("x", offsetX.ToString().c_str());
    children->Put("y", offsetY.ToString().c_str());
    json->Put("OverlayOffset", children);
}

void FrameNode::DumpDragInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("Draggable", draggable_ ? "true" : "false");
    json->Put("UserSet", userSet_ ? "true" : "false");
    json->Put("CustomerSet", customerSet_ ? "true" : "false");
    std::unique_ptr<JsonValue> dragPreview = JsonUtil::Create(true);
    dragPreview->Put("Has customNode", dragPreviewInfo_.customNode ? "YES" : "NO");
    dragPreview->Put("Has pixelMap", dragPreviewInfo_.pixelMap ? "YES" : "NO");
    dragPreview->Put("extraInfo", dragPreviewInfo_.extraInfo.c_str());
    dragPreview->Put("inspectorId", dragPreviewInfo_.inspectorId.c_str());
    json->Put("DragPreview", dragPreview);

    auto eventHub = GetEventHub<EventHub>();
    std::unique_ptr<JsonValue> event = JsonUtil::Create(true);
    event->Put("OnDragStart", eventHub && eventHub->HasOnDragStart() ? "YES" : "NO");
    event->Put("OnDragEnter", eventHub && eventHub->HasOnDragEnter() ? "YES" : "NO");
    event->Put("OnDragLeave", eventHub && eventHub->HasOnDragLeave() ? "YES" : "NO");
    event->Put("OnDragMove", eventHub && eventHub->HasOnDragMove() ? "YES" : "NO");
    event->Put("OnDrop", eventHub && eventHub->HasOnDrop() ? "YES" : "NO");
    event->Put("OnDragEnd", eventHub && eventHub->HasOnDragEnd() ? "YES" : "NO");
    event->Put("DefaultOnDragStart", eventHub && eventHub->HasDefaultOnDragStart() ? "YES" : "NO");
    event->Put("CustomerOnDragEnter", eventHub && eventHub->HasCustomerOnDragEnter() ? "YES" : "NO");
    event->Put("CustomerOnDragLeave", eventHub && eventHub->HasCustomerOnDragLeave() ? "YES" : "NO");
    event->Put("CustomerOnDragMove", eventHub && eventHub->HasCustomerOnDragMove() ? "YES" : "NO");
    event->Put("CustomerOnDrop", eventHub && eventHub->HasCustomerOnDrop() ? "YES" : "NO");
    event->Put("CustomerOnDragEnd", eventHub && eventHub->HasCustomerOnDragEnd() ? "YES" : "NO");
    json->Put("Event", event);
}

void FrameNode::DumpAlignRulesInfo(std::unique_ptr<JsonValue>& json)
{
    auto& flexItemProperties = layoutProperty_->GetFlexItemProperty();
    CHECK_NULL_VOID(flexItemProperties);
    auto rulesToString = flexItemProperties->AlignRulesToString();
    CHECK_NULL_VOID(!rulesToString.empty());
    json->Put("AlignRules", rulesToString.c_str());
}

void FrameNode::DumpSafeAreaInfo(std::unique_ptr<JsonValue>& json)
{
    if (layoutProperty_->GetSafeAreaExpandOpts()) {
        json->Put("SafeAreaExpandOpts", layoutProperty_->GetSafeAreaExpandOpts()->ToString().c_str());
    }
    if (layoutProperty_->GetSafeAreaInsets()) {
        json->Put("SafeAreaInsets", layoutProperty_->GetSafeAreaInsets()->ToString().c_str());
    }
    if (SelfOrParentExpansive()) {
        json->Put("selfAdjust", geometryNode_->GetSelfAdjust().ToString().c_str());
        json->Put("parentAdjust", geometryNode_->GetParentAdjust().ToString().c_str());
    }
    CHECK_NULL_VOID(GetTag() == V2::PAGE_ETS_TAG);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    json->Put("ignoreSafeArea", std::to_string(manager->IsIgnoreSafeArea()).c_str());
    json->Put("isNeedAvoidWindow", std::to_string(manager->IsNeedAvoidWindow()).c_str());
    json->Put("isFullScreen", std::to_string(manager->IsFullScreen()).c_str());
    json->Put("isKeyboardAvoidMode", std::to_string(static_cast<int32_t>(manager->GetKeyBoardAvoidMode())).c_str());
    json->Put("isUseCutout", std::to_string(manager->GetUseCutout()).c_str());
}

void FrameNode::DumpExtensionHandlerInfo(std::unique_ptr<JsonValue>& json)
{
    if (!extensionHandler_) {
        return;
    }
    std::unique_ptr<JsonValue> extensionHandler = JsonUtil::Create(true);
    extensionHandler->Put("HasCustomerMeasure", extensionHandler_->HasCustomerMeasure() ? "true" : "false");
    extensionHandler->Put("HasCustomerLayout", extensionHandler_->HasCustomerLayout() ? "true" : "false");
    json->Put("ExtensionHandler", extensionHandler);
}

void FrameNode::BuildLayoutInfo(std::unique_ptr<JsonValue>& json)
{
    if (geometryNode_->GetParentLayoutConstraint().has_value()) {
        json->Put("ParentLayoutConstraint", geometryNode_->GetParentLayoutConstraint().value().ToString().c_str());
    }
    if (!(NearZero(GetOffsetRelativeToWindow().GetY()) && NearZero(GetOffsetRelativeToWindow().GetX()))) {
        json->Put("top", GetOffsetRelativeToWindow().GetY());
        json->Put("left", GetOffsetRelativeToWindow().GetX());
    }
    if (static_cast<int32_t>(IsActive()) != 1) {
        json->Put("Active", static_cast<int32_t>(IsActive()));
    }
    if (static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)) != 0) {
        json->Put("Visible", static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)));
    }
    if (layoutProperty_->GetPaddingProperty()) {
        json->Put("Padding", layoutProperty_->GetPaddingProperty()->ToString().c_str());
    }
    if (layoutProperty_->GetSafeAreaPaddingProperty()) {
        json->Put("SafeArea Padding", layoutProperty_->GetSafeAreaPaddingProperty()->ToString().c_str());
    }
    if (layoutProperty_->GetBorderWidthProperty()) {
        json->Put("Border", layoutProperty_->GetBorderWidthProperty()->ToString().c_str());
    }
    if (layoutProperty_->GetMarginProperty()) {
        json->Put("Margin", layoutProperty_->GetMarginProperty()->ToString().c_str());
    }
    if (layoutProperty_->GetLayoutRect()) {
        json->Put("LayoutRect", layoutProperty_->GetLayoutRect().value().ToString().c_str());
    }
}

void FrameNode::DumpCommonInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("FrameRect", geometryNode_->GetFrameRect().ToString().c_str());
    json->Put("PaintRect without transform", renderContext_->GetPaintRectWithoutTransform().ToString().c_str());
    if (renderContext_->GetBackgroundColor()->ColorToString().compare("#00000000") != 0) {
        json->Put("BackgroundColor", renderContext_->GetBackgroundColor()->ColorToString().c_str());
    }
    BuildLayoutInfo(json);
    DumpExtensionHandlerInfo(json);
    DumpSafeAreaInfo(json);
    if (layoutProperty_->GetCalcLayoutConstraint()) {
        json->Put("User defined constraint", layoutProperty_->GetCalcLayoutConstraint()->ToString().c_str());
    }
    if (!propInspectorId_->empty()) {
        json->Put("compid", propInspectorId_.value_or("").c_str());
    }
    if (layoutProperty_->GetPaddingProperty() || layoutProperty_->GetBorderWidthProperty() ||
        layoutProperty_->GetMarginProperty() || layoutProperty_->GetCalcLayoutConstraint()) {
        json->Put("ContentConstraint", layoutProperty_->GetContentLayoutConstraint().has_value()
                                           ? layoutProperty_->GetContentLayoutConstraint().value().ToString().c_str()
                                           : "NA");
    }
    DumpAlignRulesInfo(json);
    DumpDragInfo(json);
    DumpOverlayInfo(json);
    if (frameProxy_->Dump().compare("totalCount is 0") != 0) {
        json->Put("FrameProxy", frameProxy_->Dump().c_str());
    }
}

void FrameNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    DumpCommonInfo(json);
    DumpOnSizeChangeInfo(json);
    if (pattern_) {
        pattern_->DumpInfo(json);
    }
    if (renderContext_) {
        renderContext_->DumpInfo(json);
    }
}

void FrameNode::DumpAdvanceInfo(std::unique_ptr<JsonValue>& json)
{
    DumpCommonInfo(json);
    DumpOnSizeChangeInfo(json);
    if (pattern_) {
        pattern_->DumpInfo(json);
        pattern_->DumpAdvanceInfo(json);
    }
    if (renderContext_) {
        renderContext_->DumpInfo(json);
        renderContext_->DumpAdvanceInfo(json);
    }
}

void FrameNode::ResetPredictNodes()
{
    auto predictLayoutNode = std::move(predictLayoutNode_);
    for (auto& node : predictLayoutNode) {
        auto frameNode = node.Upgrade();
        if (frameNode && frameNode->isLayoutDirtyMarked_) {
            frameNode->isLayoutDirtyMarked_ = false;
        }
    }
}

void FrameNode::SetJSCustomProperty(std::function<bool()> func, std::function<std::string(const std::string&)> getFunc,
    std::function<std::string()>&& getCustomPropertyMapFunc)
{
    func();
    if (IsCNode()) {
        return;
    }
    if (!getCustomProperty_) {
        getCustomProperty_ = getFunc;
    }
    if (getCustomPropertyMapFunc && (!getCustomPropertyMapFunc_)) {
        getCustomPropertyMapFunc_ = std::move(getCustomPropertyMapFunc);
    }
}

bool FrameNode::GetJSCustomProperty(const std::string& key, std::string& value)
{
    auto iter = customPropertyMap_.find(key);
    if (iter != customPropertyMap_.end() && !iter->second.empty()) {
        if (iter->second[1] == "1") {
            value = iter->second[0];
            return true;
        } else if (getCustomProperty_) {
            value = getCustomProperty_(key);
            iter->second[0] = value;
            iter->second[1] = "1";
            return true;
        }
    }
    return false;
}

bool FrameNode::GetCapiCustomProperty(const std::string& key, std::string& value)
{
    auto iter = customPropertyMap_.find(key);
    if (iter != customPropertyMap_.end()) {
        value = iter->second[0];
        return true;
    }
    return false;
}

void FrameNode::AddCustomProperty(const std::string& key, const std::string& value)
{
    customPropertyMap_[key] = {value, "1"};
}

void FrameNode::RemoveCustomProperty(const std::string& key)
{
    auto iter = customPropertyMap_.find(key);
    if (iter != customPropertyMap_.end()) {
        customPropertyMap_.erase(iter);
    }
}

void FrameNode::SetCustomPropertyMapFlagByKey(const std::string& key)
{
    auto& valueVector = customPropertyMap_[key];
    if (valueVector.empty()) {
        valueVector = {"", "0"};
    } else {
        valueVector[1] = "0";
    }
}

void FrameNode::AddExtraCustomProperty(const std::string& key, void* extraData)
{
    extraCustomPropertyMap_[key] = extraData;
}

void* FrameNode::GetExtraCustomProperty(const std::string& key) const
{
    auto iter = extraCustomPropertyMap_.find(key);
    if (iter != extraCustomPropertyMap_.end()) {
        return iter->second;
    }
    return nullptr;
}

void FrameNode::RemoveExtraCustomProperty(const std::string& key)
{
    auto iter = extraCustomPropertyMap_.find(key);
    if (iter != extraCustomPropertyMap_.end()) {
        extraCustomPropertyMap_.erase(iter);
    }
}

void FrameNode::ExtraCustomPropertyToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto mapIter = extraCustomPropertyMap_.find("ToJsonValue");
    if (mapIter == extraCustomPropertyMap_.end()) {
        return;
    }

    auto callback = reinterpret_cast<std::map<std::string, std::string>(*)(std::unordered_map<std::string, void*>)>(
        mapIter->second);
    CHECK_NULL_VOID(callback);
    auto jsonValue = callback(extraCustomPropertyMap_);
    for (auto iter = jsonValue.begin(); iter != jsonValue.end(); iter++) {
        json->PutExtAttr(iter->first.c_str(), iter->second.c_str(), filter);
    }
}

bool FrameNode::IsDebugInspectorId()
{
    if (!SystemProperties::GetDebugEnabled()) {
        return false;
    }
    auto debugInspectorId = SystemProperties::GetDebugInspectorId();
    return debugInspectorId == GetInspectorId().value_or("");
}

RefPtr<UINode> FrameNode::GetCurrentPageRootNode()
{
    auto pageNode = GetPageNode();
    CHECK_NULL_RETURN(pageNode, nullptr);
    auto jsView = pageNode->GetChildAtIndex(0);
    CHECK_NULL_RETURN(jsView, nullptr);
    if (jsView->GetTag() == V2::JS_VIEW_ETS_TAG) {
        auto rootNode = jsView->GetChildAtIndex(0);
        CHECK_NULL_RETURN(rootNode, nullptr);
        return rootNode;
    }
    return jsView;
}

std::list<RefPtr<FrameNode>> FrameNode::GetActiveChildren()
{
    std::list<RefPtr<FrameNode>> list;
    for (int32_t i = 0; i < TotalChildCount(); i++) {
        auto child = GetFrameNodeChildByIndex(i, false, false);
        if (child->IsActive()) {
            list.emplace_back(Referenced::Claim(child));
        }
    }
    return list;
}

void FrameNode::CleanVisibleAreaUserCallback(bool isApproximate)
{
    CHECK_NULL_VOID(eventHub_);
    auto hasInnerCallback = eventHub_->HasVisibleAreaCallback(false);
    auto hasUserCallback = eventHub_->HasVisibleAreaCallback(true);
    auto& throttledVisibleAreaCallback = eventHub_->GetThrottledVisibleAreaCallback();
    auto pipeline = GetContext();
    if (isApproximate) {
        eventHub_->CleanVisibleAreaCallback(true, isApproximate);
        if (!hasInnerCallback && !hasUserCallback && pipeline) {
            throttledCallbackOnTheWay_ = false;
            pipeline->RemoveVisibleAreaChangeNode(GetId());
        }
    } else {
        eventHub_->CleanVisibleAreaCallback(true, false);
        if (!hasInnerCallback && !throttledVisibleAreaCallback.callback && pipeline) {
            pipeline->RemoveVisibleAreaChangeNode(GetId());
        }
    }
}

void FrameNode::SetKitNode(const RefPtr<Kit::FrameNode>& node)
{
    kitNode_ = node;
}

bool FrameNode::GetCustomPropertyByKey(const std::string& key, std::string& value)
{
    auto iter = customPropertyMap_.find(key);
    if (iter != customPropertyMap_.end() && !iter->second.empty()) {
        value = iter->second[0];
        return true;
    }
    return false;
}

void FrameNode::AddNodeDestroyCallback(const std::string& callbackKey, std::function<void()>&& callback)
{
    if (!callback) {
        return;
    }
    destroyCallbacks_[callbackKey] = std::move(callback);
}

void FrameNode::RemoveNodeDestroyCallback(const std::string& callbackKey)
{
    auto iter = destroyCallbacks_.find(callbackKey);
    if (iter != destroyCallbacks_.end()) {
        destroyCallbacks_.erase(iter);
    }
}

void FrameNode::FireOnExtraNodeDestroyCallback()
{
    for (const auto& callback : destroyCallbacks_) {
        callback.second();
    }
}

void FrameNode::SetFrameNodeDestructorCallback(const std::function<void(int32_t)>&& callback)
{
    frameNodeDestructorCallback_ = callback;
}

void FrameNode::FireFrameNodeDestructorCallback()
{
    if (frameNodeDestructorCallback_) {
        frameNodeDestructorCallback_(GetId());
    }
}

const char* FrameNode::GetPatternTypeName() const
{
    return TypeInfoHelper::TypeName(RawPtr(pattern_));
}

const char* FrameNode::GetLayoutPropertyTypeName() const
{
    return TypeInfoHelper::TypeName(RawPtr(layoutProperty_));
}

const char* FrameNode::GetPaintPropertyTypeName() const
{
    return TypeInfoHelper::TypeName(RawPtr(paintProperty_));
}

const RefPtr<Kit::FrameNode>& FrameNode::GetKitNode() const
{
    return kitNode_;
}

bool FrameNode::IsDrawFocusOnTop() const
{
    auto accessibilityProperty = GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    return static_cast<FocusDrawLevel>(accessibilityProperty->GetFocusDrawLevel()) == FocusDrawLevel::TOP;
}

void FrameNode::AddVisibilityDumpInfo(const std::pair<uint64_t, std::pair<VisibleType, bool>>& dumpInfo)
{
    if (visibilityDumpInfos_.size() == SIZE_CHANGE_DUMP_SIZE) {
        visibilityDumpInfos_.pop_front();
    }
    visibilityDumpInfos_.push_back(dumpInfo);
}

std::string FrameNode::PrintVisibilityDumpInfo() const
{
    if (visibilityDumpInfos_.empty()) {
        return "" ;
    }
    std::string res = "[ ";
    for (auto it = visibilityDumpInfos_.rbegin(); it != visibilityDumpInfos_.rend(); ++it) {
        res += ("{" + std::to_string(it->first) + ", " +
            std::to_string(static_cast<int32_t>(it->second.first)) + ", " +
            std::to_string(static_cast<int32_t>(it->second.second)) + "}, ");
    }
    res += "]";
    return res;
}

int32_t FrameNode::OnRecvCommand(const std::string& command)
{
    auto pattern = GetPattern();
    CHECK_NULL_RETURN(pattern, RET_FAILED);
    return pattern->OnRecvCommand(command);
}

void FrameNode::HandleAreaChangeDestruct()
{
    if (eventHub_) {
        eventHub_->ClearOnAreaChangedInnerCallbacks();
        if (eventHub_->HasVisibleAreaCallback(true) || eventHub_->HasVisibleAreaCallback(false) ||
            eventHub_->HasThrottledVisibleAreaCallback()) {
            SetVisibleAreaChangeTriggerReason(VisibleAreaChangeTriggerReason::FRAMENODE_DESTROY);
            TriggerVisibleAreaChangeCallback(0, true);
            CleanVisibleAreaUserCallback(true);
            CleanVisibleAreaUserCallback();
            CleanVisibleAreaInnerCallback();
        }
    }
}

void FrameNode::AddToOcclusionMap(bool enable)
{
    auto context = GetContextWithCheck();
    CHECK_NULL_VOID(context);
    context->AddToOcclusionMap(GetId(), enable);
}

void FrameNode::CleanupPipelineResources()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->RemoveOnAreaChangeNode(GetId());
        pipeline->RemoveVisibleAreaChangeNode(GetId());
        pipeline->ChangeMouseStyle(GetId(), MouseFormat::DEFAULT);
        pipeline->FreeMouseStyleHoldNode(GetId());
        pipeline->RemoveStoredNode(GetRestoreId());
        auto dragManager = pipeline->GetDragDropManager();
        if (dragManager) {
            dragManager->RemoveDragFrameNode(GetId());
            dragManager->UnRegisterDragStatusListener(GetId());
        }
        auto frameRateManager = pipeline->GetFrameRateManager();
        if (frameRateManager) {
            frameRateManager->RemoveNodeRate(GetId());
        }
        pipeline->RemoveChangedFrameNode(GetId());
        pipeline->RemoveFrameNodeChangeListener(GetId());
        pipeline->GetNodeRenderStatusMonitor()->NotifyFrameNodeRelease(this);
    }
}
} // namespace OHOS::Ace::NG
