/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/log/ace_performance_monitor.h"
#include "base/log/ace_trace.h"
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
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/base/extension_handler.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/target_component.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/paint_wrapper.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace {
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
constexpr int32_t SUBSTR_LENGTH = 3;
const char DIMENSION_UNIT_VP[] = "vp";
constexpr int32_t SIZE_CHANGE_DUMP_SIZE = 5;
constexpr double MIN_WIDTH = 5.0;
constexpr double MIN_HEIGHT = 5.0;
constexpr double MIN_OPACITY = 0.1;
} // namespace
namespace OHOS::Ace::NG {

const std::set<std::string> FrameNode::layoutTags_ = { "Flex", "Stack", "Row", "Column", "WindowScene", "root",
    "__Common__", "Swiper", "Grid", "GridItem", "page", "stage", "FormComponent", "Tabs", "TabContent" };

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
                    [this](FrameChildNode& node) {
                        return prevFrameProxy_->cursor_->node == node.node;
                    });
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
        if (lazyForEachNode) {
            lazyForEachNode->BuildAllChildren();
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
        if (allFrameNodeChildren_.empty()) {
            Build();
            uint32_t count = 0;
            auto guard = GetGuard();
            for (const auto& child : children_) {
                AddFrameNode(child.node, allFrameNodeChildren_, partFrameNodeChildren_, count);
            }
        }
        return ChildrenListWithGuard(allFrameNodeChildren_, *this);
    }

    RefPtr<LayoutWrapper> FindFrameNodeByIndex(uint32_t index, bool needBuild, bool isCache)
    {
        while (cursor_ != children_.end()) {
            if (cursor_->startIndex > index) {
                cursor_--;
                continue;
            }

            if (cursor_->startIndex + cursor_->count > index) {
                auto frameNode = AceType::DynamicCast<FrameNode>(
                    cursor_->node->GetFrameChildByIndex(index - cursor_->startIndex, needBuild, isCache));
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

    RefPtr<LayoutWrapper> GetFrameNodeByIndex(uint32_t index, bool needBuild, bool isCache)
    {
        auto itor = partFrameNodeChildren_.find(index);
        if (itor == partFrameNodeChildren_.end()) {
            Build();
            auto child = FindFrameNodeByIndex(index, needBuild, isCache);
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
            LOGF("[%{public}d:%{public}s] reset children while in use",
                hostNode_->GetId(), hostNode_->GetTag().c_str());
            if (SystemProperties::GetDebugEnabled()) {
                abort();
            } else {
                LogBacktrace();
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

    void SetActiveChildRange(int32_t start, int32_t end)
    {
        for (auto itor = partFrameNodeChildren_.begin(); itor != partFrameNodeChildren_.end();) {
            int32_t index = itor->first;
            if ((start <= end && index >= start && index <= end) ||
                (start > end && (index <= end || start <= index))) {
                itor++;
            } else {
                partFrameNodeChildren_.erase(itor++);
            }
        }
        auto guard = GetGuard();
        for (const auto& child : children_) {
            child.node->DoSetActiveChildRange(start - child.startIndex, end - child.startIndex);
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
    uint32_t totalCount_ = 0;
    FrameNode* hostNode_ { nullptr };
    uint32_t inUse_ = 0;
    bool delayReset_ = false;
    bool needResetChild_ = false;
}; // namespace OHOS::Ace::NG

FrameNode::FrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
    : UINode(tag, nodeId, isRoot), LayoutWrapper(WeakClaim(this)), pattern_(pattern)
{
    frameProxy_ = std::make_unique<FrameProxy>(this);
    renderContext_->InitContext(IsRootNode(), pattern_->GetContextParam());
    paintProperty_ = pattern->CreatePaintProperty();
    layoutProperty_ = pattern->CreateLayoutProperty();
    eventHub_ = pattern->CreateEventHub();
    accessibilityProperty_ = pattern->CreateAccessibilityProperty();
    // first create make layout property dirty.
    layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    layoutProperty_->SetHost(WeakClaim(this));
}

FrameNode::~FrameNode()
{
    for (const auto& destroyCallback : destroyCallbacks_) {
        destroyCallback();
    }

    if (removeCustomProperties_) {
        removeCustomProperties_();
        removeCustomProperties_ = nullptr;
    }

    pattern_->DetachFromFrameNode(this);
    if (IsOnMainTree()) {
        OnDetachFromMainTree(false);
    }
    TriggerVisibleAreaChangeCallback(true);
    CleanVisibleAreaUserCallback();
    CleanVisibleAreaInnerCallback();
    if (eventHub_) {
        eventHub_->ClearOnAreaChangedInnerCallbacks();
    }
    auto pipeline = GetContext();
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

RefPtr<FrameNode> FrameNode::CreateFrameNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto frameNode = MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot);
    ElementRegister::GetInstance()->AddUINode(frameNode);
    frameNode->InitializePatternAndContext();
    return frameNode;
}

bool FrameNode::IsSupportDrawModifier()
{
    CHECK_NULL_RETURN(pattern_, false);
    return pattern_->IsSupportDrawModifier();
}

void FrameNode::ProcessOffscreenNode(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    node->ProcessOffscreenTask();
    node->MarkModifyDone();
    node->UpdateLayoutPropertyFlag();
    node->SetActive();
    node->isLayoutDirtyMarked_ = true;
    auto pipeline = PipelineContext::GetCurrentContext();
    node->CreateLayoutTask();
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
    pipeline->FlushMessages();
    node->SetActive(false);
}

void FrameNode::InitializePatternAndContext()
{
    eventHub_->AttachHost(WeakClaim(this));
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

void FrameNode::DumpSafeAreaInfo()
{
    if (layoutProperty_->GetSafeAreaExpandOpts()) {
        DumpLog::GetInstance().AddDesc(layoutProperty_->GetSafeAreaExpandOpts()->ToString());
    }
    if (layoutProperty_->GetSafeAreaInsets()) {
        DumpLog::GetInstance().AddDesc(layoutProperty_->GetSafeAreaInsets()->ToString());
    }
    CHECK_NULL_VOID(GetTag() == V2::PAGE_ETS_TAG);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    CHECK_NULL_VOID(manager);
    DumpLog::GetInstance().AddDesc(std::string("ignoreSafeArea: ")
                                    .append(std::to_string(manager->IsIgnoreAsfeArea()))
                                    .append(std::string(", isNeedAvoidWindow: ").c_str())
                                    .append(std::to_string(manager->IsNeedAvoidWindow()))
                                    .append(std::string(", isFullScreen: ").c_str())
                                    .append(std::to_string(manager->IsFullScreen())));
}

void FrameNode::DumpCommonInfo()
{
    if (!geometryNode_->GetFrameRect().ToString().compare(renderContext_->GetPaintRectWithoutTransform().ToString())) {
        DumpLog::GetInstance().AddDesc(std::string("FrameRect: ").append(geometryNode_->GetFrameRect().ToString()));
    }
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

    if (static_cast<int32_t>(layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)) != 0) {
        DumpLog::GetInstance().AddDesc(std::string("Visible: ")
                                           .append(std::to_string(static_cast<int32_t>(
                                               layoutProperty_->GetVisibility().value_or(VisibleType::VISIBLE)))));
    }
    if (layoutProperty_->GetPaddingProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Padding: ").append(layoutProperty_->GetPaddingProperty()->ToString().c_str()));
    }
    if (layoutProperty_->GetBorderWidthProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Border: ").append(layoutProperty_->GetBorderWidthProperty()->ToString().c_str()));
    }
    if (layoutProperty_->GetMarginProperty()) {
        DumpLog::GetInstance().AddDesc(
            std::string("Margin: ").append(layoutProperty_->GetMarginProperty()->ToString().c_str()));
    }
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
                .append(layoutProperty_->GetContentLayoutConstraint().has_value() ?
                            layoutProperty_->GetContentLayoutConstraint().value().ToString() : "NA"));
    }
    DumpDragInfo();
    DumpOverlayInfo();
    if (frameProxy_->Dump().compare("totalCount is 0") != 0) {
        DumpLog::GetInstance().AddDesc(std::string("FrameProxy: ").append(frameProxy_->Dump().c_str()));
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
    DumpLog::GetInstance().AddDesc(
        std::string("DragPreviewMode: ")
            .append(previewOption_.mode == DragPreviewMode::DISABLE_SCALE ? "DISABLE_SCALE" : "AUTO"));
    auto eventHub = GetEventHub<EventHub>();
    DumpLog::GetInstance().AddDesc(std::string("Event: ")
                                        .append("OnDragStart: ")
                                        .append(eventHub->HasOnDragStart() ? "YES" : "NO")
                                        .append(" OnDragEnter: ")
                                        .append(eventHub->HasOnDragEnter() ? "YES" : "NO")
                                        .append(" OnDragLeave: ")
                                        .append(eventHub->HasOnDragLeave() ? "YES" : "NO")
                                        .append(" OnDragMove: ")
                                        .append(eventHub->HasOnDragMove() ? "YES" : "NO")
                                        .append(" OnDrop: ")
                                        .append(eventHub->HasOnDrop() ? "YES" : "NO")
                                        .append(" OnDragEnd: ")
                                        .append(eventHub->HasOnDragEnd() ? "YES" : "NO"));
    DumpLog::GetInstance().AddDesc(std::string("DefaultOnDragStart: ")
                                        .append(eventHub->HasDefaultOnDragStart() ? "YES" : "NO")
                                        .append(" CustomerOnDragEnter: ")
                                        .append(eventHub->HasCustomerOnDragEnter() ? "YES" : "NO")
                                        .append(" CustomerOnDragLeave: ")
                                        .append(eventHub->HasCustomerOnDragLeave() ? "YES" : "NO")
                                        .append(" CustomerOnDragMove: ")
                                        .append(eventHub->HasCustomerOnDragMove() ? "YES" : "NO")
                                        .append(" CustomerOnDrop: ")
                                        .append(eventHub->HasCustomerOnDrop() ? "YES" : "NO")
                                        .append(" CustomerOnDragEnd: ")
                                        .append(eventHub->HasCustomerOnDragEnd() ? "YES" : "NO"));
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

void FrameNode::DumpInfo()
{
    DumpCommonInfo();
    DumpOnSizeChangeInfo();
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
    if (pattern_) {
        pattern_->DumpInfo();
        pattern_->DumpAdvanceInfo();
    }
    if (renderContext_) {
        renderContext_->DumpInfo();
        renderContext_->DumpAdvanceInfo();
    }
}

void FrameNode::DumpViewDataPageNode(RefPtr<ViewDataWrap> viewDataWrap)
{
    if (pattern_) {
        pattern_->DumpViewDataPageNode(viewDataWrap);
    }
}

bool FrameNode::CheckAutoSave()
{
    if (pattern_) {
        return pattern_->CheckAutoSave();
    }
    return false;
}

void FrameNode::FocusToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    bool enabled = true;
    bool focusable = false;
    bool focused = false;
    bool defaultFocus = false;
    bool groupDefaultFocus = false;
    bool focusOnTouch = false;
    int32_t tabIndex = 0;
    auto focusHub = GetFocusHub();
    if (focusHub) {
        enabled = focusHub->IsEnabled();
        focusable = focusHub->IsFocusable();
        focused = focusHub->IsCurrentFocus();
        defaultFocus = focusHub->IsDefaultFocus();
        groupDefaultFocus = focusHub->IsDefaultGroupFocus();
        focusOnTouch = focusHub->IsFocusOnTouch().value_or(false);
        tabIndex = focusHub->GetTabIndex();
    }
    json->PutExtAttr("enabled", enabled, filter);
    json->PutFixedAttr("focusable", focusable, filter, FIXED_ATTR_FOCUSABLE);
    json->PutFixedAttr("focused", focused, filter, FIXED_ATTR_FOCUSED);
    json->PutExtAttr("defaultFocus", defaultFocus, filter);
    json->PutExtAttr("groupDefaultFocus", groupDefaultFocus, filter);
    json->PutExtAttr("focusOnTouch", focusOnTouch, filter);
    json->PutExtAttr("tabIndex", tabIndex, filter);
}

void FrameNode::MouseToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    std::string hoverEffect = "HoverEffect.Auto";
    auto inputEventHub = GetOrCreateInputEventHub();
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
    auto gestureEventHub = GetOrCreateGestureEventHub();
    std::vector<DimensionRect> responseRegion;
    std::vector<DimensionRect> mouseResponseRegion;
    if (gestureEventHub) {
        touchable = gestureEventHub->GetTouchable();
        hitTestMode = gestureEventHub->GetHitTestModeStr();
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
    if (layoutProperty_ && layoutProperty_->GetCalcLayoutConstraint()) {
        auto selfIdealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
        hasIdealWidth = selfIdealSize.has_value() && selfIdealSize.value().Width().has_value();
        hasIdealHeight = selfIdealSize.has_value() && selfIdealSize.value().Height().has_value();
    }

    auto jsonSize = json->GetValue("size");
    if (!hasIdealWidth) {
        auto idealWidthVpStr = std::to_string(Dimension(geometryNode_->GetFrameSize().Width()).ConvertToVp());
        auto widthStr =
            (idealWidthVpStr.substr(0, idealWidthVpStr.find(".") + SUBSTR_LENGTH) + DIMENSION_UNIT_VP);
        json->PutExtAttr("width", widthStr.c_str(), filter);
        if (jsonSize) {
            jsonSize->Put("width", widthStr.c_str());
        }
    }

    if (!hasIdealHeight) {
        auto idealHeightVpStr = std::to_string(Dimension(geometryNode_->GetFrameSize().Height()).ConvertToVp());
        auto heightStr =
            (idealHeightVpStr.substr(0, idealHeightVpStr.find(".") + SUBSTR_LENGTH) + DIMENSION_UNIT_VP);
        json->PutExtAttr("height", heightStr.c_str(), filter);
        if (jsonSize) {
            jsonSize->Put("height", heightStr.c_str());
        }
    }
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
    FocusToJsonValue(json, filter);
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

void FrameNode::OnAttachToMainTree(bool recursive)
{
    eventHub_->FireOnAppear();
    renderContext_->OnNodeAppear(recursive);
    pattern_->OnAttachToMainTree();
    if (attachFunc_) {
        attachFunc_(GetId());
    }
    // node may have been measured before AttachToMainTree
    if (geometryNode_->GetParentLayoutConstraint().has_value() && !UseOffscreenProcess()) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE_SELF);
    }
    if (GetNodeStatus() == NodeStatus::BUILDER_NODE_ON_MAINTREE) {
        const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
        if (geometryTransition) {
            layoutProperty_->UpdateGeometryTransition("");
            layoutProperty_->UpdateGeometryTransition(geometryTransition->GetId());
            MarkDirtyNode();
        }
    }
    UINode::OnAttachToMainTree(recursive);

    if (!hasPendingRequest_) {
        return;
    }
    auto context = GetContext();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    hasPendingRequest_ = false;
}

void FrameNode::OnAttachToBuilderNode(NodeStatus nodeStatus)
{
    pattern_->OnAttachToBuilderNode(nodeStatus);
}

void FrameNode::OnConfigurationUpdate(const ConfigurationChange& configurationChange)
{
    if (configurationChange.languageUpdate) {
        pattern_->OnLanguageConfigurationUpdate();
        MarkModifyDone();
        MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (configurationChange.colorModeUpdate) {
        pattern_->OnColorConfigurationUpdate();
        if (colorModeUpdateCallback_) {
            colorModeUpdateCallback_();
        }
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
}

void FrameNode::NotifyVisibleChange(bool isVisible)
{
    pattern_->OnVisibleChange(isVisible);
    UpdateChildrenVisible(isVisible);
}

void FrameNode::TryVisibleChangeOnDescendant(bool isVisible)
{
    auto layoutProperty = GetLayoutProperty();
    if (layoutProperty &&
        layoutProperty->GetVisibilityValue(VisibleType::VISIBLE) != VisibleType::VISIBLE) {
        return;
    }
    NotifyVisibleChange(isVisible);
}

void FrameNode::OnDetachFromMainTree(bool recursive)
{
    auto focusHub = GetFocusHub();
    if (focusHub) {
        auto focusView = focusHub->GetFirstChildFocusView();
        if (focusView) {
            focusView->FocusViewClose();
        } else {
            focusHub->RemoveSelf();
        }
    }
    pattern_->OnDetachFromMainTree();
    if (detachFunc_) {
        detachFunc_(GetId());
    }
    eventHub_->FireOnDisappear();
    renderContext_->OnNodeDisappear(recursive);
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
    if ((config.skipMeasure == false) && (config.skipLayout == false) && GetInspectorId().has_value()) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->OnLayoutCompleted(GetInspectorId()->c_str());
    }
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(dirty, config);
    // TODO: temp use and need to delete.
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

void FrameNode::SetBackgroundLayoutConstraint(const RefPtr<FrameNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.scaleProperty = ScaleProperty::CreateScaleProperty();
    layoutConstraint.percentReference.SetWidth(geometryNode_->GetFrameSize().Width());
    layoutConstraint.percentReference.SetHeight(geometryNode_->GetFrameSize().Height());
    layoutConstraint.maxSize.SetWidth(geometryNode_->GetFrameSize().Width());
    layoutConstraint.maxSize.SetHeight(geometryNode_->GetFrameSize().Height());
    customNode->GetGeometryNode()->SetParentLayoutConstraint(layoutConstraint);
}

void FrameNode::AdjustGridOffset()
{
    if (!isActive_) {
        return;
    }
    if (layoutProperty_->UpdateGridOffset(Claim(this))) {
        renderContext_->UpdateOffset(OffsetT<Dimension>());
        renderContext_->UpdateAnchor(OffsetT<Dimension>());
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
    eventHub_->SetOnAreaChanged(std::move(callback));
}

void FrameNode::TriggerOnAreaChangeCallback(uint64_t nanoTimestamp)
{
    if (!IsActive()) {
        return;
    }
    if ((eventHub_->HasOnAreaChanged() || eventHub_->HasInnerOnAreaChanged()) && lastFrameRect_ &&
        lastParentOffsetToWindow_) {
        auto currFrameRect = GetRectWithRender();
        auto currParentOffsetToWindow = CalculateOffsetRelativeToWindow(nanoTimestamp) - currFrameRect.GetOffset();
        if (currFrameRect != *lastFrameRect_ || currParentOffsetToWindow != *lastParentOffsetToWindow_) {
            if (eventHub_->HasInnerOnAreaChanged()) {
                eventHub_->FireInnerOnAreaChanged(
                    *lastFrameRect_, *lastParentOffsetToWindow_, currFrameRect, currParentOffsetToWindow);
            }
            if (eventHub_->HasOnAreaChanged()) {
                eventHub_->FireOnAreaChanged(
                    *lastFrameRect_, *lastParentOffsetToWindow_, currFrameRect, currParentOffsetToWindow);
            }
            *lastFrameRect_ = currFrameRect;
            *lastParentOffsetToWindow_ = currParentOffsetToWindow;
        }
    }
    pattern_->OnAreaChangedInner();
}

void FrameNode::SetOnSizeChangeCallback(OnSizeChangedFunc&& callback)
{
    if (!lastFrameNodeRect_) {
        lastFrameNodeRect_ = std::make_unique<RectF>();
    }
    eventHub_->SetOnSizeChanged(std::move(callback));
}


void FrameNode::SetJSFrameNodeOnSizeChangeCallback(OnSizeChangedFunc&& callback)
{
    if (!lastFrameNodeRect_) {
        lastFrameNodeRect_ = std::make_unique<RectF>();
    }
    eventHub_->SetJSFrameNodeOnSizeChangeCallback(std::move(callback));
}

RectF FrameNode::GetRectWithRender()
{
    auto currFrameRect = geometryNode_->GetFrameRect();
    if (renderContext_ && renderContext_->GetPositionProperty()) {
        if (renderContext_->GetPositionProperty()->HasPosition()) {
            auto renderPosition = ContextPositionConvertToPX(
                renderContext_, layoutProperty_->GetLayoutConstraint()->percentReference);
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
    if (eventHub_->HasOnSizeChanged() && lastFrameNodeRect_) {
        auto currFrameRect = GetRectWithRender();
        if (currFrameRect.GetSize() != (*lastFrameNodeRect_).GetSize()) {
            onSizeChangeDumpInfo dumpInfo { GetCurrentTimestamp(), *lastFrameNodeRect_, currFrameRect };
            if (onSizeChangeDumpInfos.size() >= SIZE_CHANGE_DUMP_SIZE) {
                onSizeChangeDumpInfos.erase(onSizeChangeDumpInfos.begin());
            }
            onSizeChangeDumpInfos.emplace_back(dumpInfo);
            eventHub_->FireOnSizeChanged(*lastFrameNodeRect_, currFrameRect);
            eventHub_->FireJSFrameNodeOnSizeChanged(*lastFrameNodeRect_, currFrameRect);
            *lastFrameNodeRect_ = currFrameRect;
        }
    }
}

void FrameNode::TriggerVisibleAreaChangeCallback(bool forceDisappear)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);

    bool isFrameDisappear = forceDisappear || !context->GetOnShow() || !IsOnMainTree() || !IsVisible();
    if (!isFrameDisappear) {
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
        isFrameDisappear = !curIsVisible || !curFrameIsActive;
    }

    CHECK_NULL_VOID(eventHub_);
    auto& visibleAreaUserRatios = eventHub_->GetVisibleAreaRatios(true);
    auto& visibleAreaUserCallback = eventHub_->GetVisibleAreaCallback(true);
    auto& visibleAreaInnerRatios = eventHub_->GetVisibleAreaRatios(false);
    auto& visibleAreaInnerCallback = eventHub_->GetVisibleAreaCallback(false);

    if (isFrameDisappear) {
        if (!NearEqual(lastVisibleRatio_, VISIBLE_RATIO_MIN)) {
            ProcessAllVisibleCallback(visibleAreaUserRatios, visibleAreaUserCallback,
                VISIBLE_RATIO_MIN, lastVisibleCallbackRatio_);
            ProcessAllVisibleCallback(visibleAreaInnerRatios, visibleAreaInnerCallback,
                VISIBLE_RATIO_MIN, lastVisibleCallbackRatio_);
            lastVisibleRatio_ = VISIBLE_RATIO_MIN;
        }
        return;
    }

    RectF frameRect;
    RectF visibleRect;
    GetVisibleRect(visibleRect, frameRect);
    double currentVisibleRatio =
        std::clamp(CalculateCurrentVisibleRatio(visibleRect, frameRect), VISIBLE_RATIO_MIN, VISIBLE_RATIO_MAX);
    if (!NearEqual(currentVisibleRatio, lastVisibleRatio_)) {
        auto lastVisibleCallbackRatio = lastVisibleCallbackRatio_;
        ProcessAllVisibleCallback(visibleAreaUserRatios, visibleAreaUserCallback,
            currentVisibleRatio, lastVisibleCallbackRatio);
        ProcessAllVisibleCallback(visibleAreaInnerRatios, visibleAreaInnerCallback,
            currentVisibleRatio, lastVisibleCallbackRatio);
        lastVisibleRatio_ = currentVisibleRatio;
    }
}

double FrameNode::CalculateCurrentVisibleRatio(const RectF& visibleRect, const RectF& renderRect)
{
    if (!visibleRect.IsValid() || !renderRect.IsValid()) {
        return 0.0;
    }
    return visibleRect.Width() * visibleRect.Height() / (renderRect.Width() * renderRect.Height());
}

void FrameNode::ProcessAllVisibleCallback(const std::vector<double>& visibleAreaUserRatios,
    VisibleCallbackInfo& visibleAreaUserCallback, double currentVisibleRatio, double lastVisibleRatio)
{
    bool isHandled = false;
    bool isVisible = false;
    for (const auto& callbackRatio : visibleAreaUserRatios) {
        if (isHandled) {
            break;
        }
        if (GreatNotEqual(currentVisibleRatio, callbackRatio) && LessOrEqual(lastVisibleRatio, callbackRatio)) {
            lastVisibleCallbackRatio_ = currentVisibleRatio;
            isVisible = true;
            isHandled = true;
        } else if (LessNotEqual(currentVisibleRatio, callbackRatio) && GreatOrEqual(lastVisibleRatio, callbackRatio)) {
            lastVisibleCallbackRatio_ = currentVisibleRatio;
            isVisible = false;
            isHandled = true;
        } else if (NearEqual(callbackRatio, VISIBLE_RATIO_MIN) && NearEqual(currentVisibleRatio, callbackRatio)) {
            lastVisibleCallbackRatio_ = VISIBLE_RATIO_MIN;
            currentVisibleRatio = VISIBLE_RATIO_MIN;
            isVisible = false;
            isHandled = true;
        } else if (NearEqual(callbackRatio, VISIBLE_RATIO_MAX) && NearEqual(currentVisibleRatio, callbackRatio)) {
            lastVisibleCallbackRatio_ = VISIBLE_RATIO_MAX;
            currentVisibleRatio = VISIBLE_RATIO_MAX;
            isVisible = true;
            isHandled = true;
        }
    }

    auto callback = visibleAreaUserCallback.callback;
    if (isHandled && callback) {
        callback(isVisible, currentVisibleRatio);
    }
}

void FrameNode::SetActive(bool active)
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
    if (activeChanged) {
        auto parent = GetAncestorNodeOfFrame();
        if (parent) {
            parent->MarkNeedSyncRenderTree();
        }
        if (isActive_ && SystemProperties::GetDeveloperModeOn()) {
            PaintDebugBoundary(SystemProperties::GetDebugBoundaryEnabled());
        }
    }
}

void FrameNode::SetGeometryNode(const RefPtr<GeometryNode>& node)
{
    geometryNode_ = node;
}

void FrameNode::CreateLayoutTask(bool forceUseMainThread)
{
    if (!isLayoutDirtyMarked_) {
        return;
    }
    SetRootMeasureNode(true);
    UpdateLayoutPropertyFlag();
    SetSkipSyncGeometryNode(false);
    {
        ACE_SCOPED_TRACE("CreateTaskMeasure[%s][self:%d][parent:%d]", GetTag().c_str(), GetId(),
            GetAncestorNodeOfFrame() ? GetAncestorNodeOfFrame()->GetId() : 0);
        Measure(GetLayoutConstraint());
    }
    {
        ACE_SCOPED_TRACE("CreateTaskLayout[%s][self:%d][parent:%d]", GetTag().c_str(), GetId(),
            GetAncestorNodeOfFrame() ? GetAncestorNodeOfFrame()->GetId() : 0);
        Layout();
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
        ACE_SCOPED_TRACE("FrameNode[%s][id:%d]::RenderTask", self->GetTag().c_str(), self->GetId());
        ArkUIPerfMonitor::GetInstance().RecordRenderNode();
        wrapper->FlushRender();
        paintProperty->CleanDirty();

        if (self->GetInspectorId()) {
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            pipeline->SetNeedRenderNode(self);
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

OffsetF FrameNode::GetParentGlobalOffset() const
{
    auto parent = GetAncestorNodeOfFrame();
    if (!parent) {
        return { 0.0f, 0.0f };
    }
    return parent->geometryNode_->GetParentGlobalOffset();
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
    if (!paintMethod  || extensionHandler_ || renderContext_->GetAccessibilityFocus().value_or(false)) {
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
    auto paintMethod = pattern_->CreateNodePaintMethod();
    if (paintMethod || extensionHandler_ || renderContext_->GetAccessibilityFocus().value_or(false)) {
        // It is necessary to copy the layoutProperty property to prevent the paintProperty_ property from being
        // modified during the paint process, resulting in the problem of judging whether the front-end setting value
        // changes the next time js is executed.

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
    for (const auto& child : children) {
        frameChildren_.emplace(child);
    }
    renderContext_->RebuildFrame(this, children);
    pattern_->OnRebuildFrame();
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
    eventHub_->MarkModifyDone();
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

void FrameNode::OnMountToParentDone()
{
    pattern_->OnMountToParentDone();
}

void FrameNode::FlushUpdateAndMarkDirty()
{
    MarkDirtyNode();
}

void FrameNode::MarkDirtyNode(PropertyChangeFlag extraFlag, bool childExpansiveAndMark)
{
    if (CheckNeedMakePropertyDiff(extraFlag)) {
        if (isPropertyDiffMarked_) {
            return;
        }
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        context->AddDirtyPropertyNode(Claim(this));
        isPropertyDiffMarked_ = true;
        return;
    }
    MarkDirtyNode(IsMeasureBoundary(), IsRenderBoundary(), extraFlag, childExpansiveAndMark);
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

void FrameNode::NotifyFillRequestSuccess(RefPtr<PageNodeInfoWrap> nodeWrap, AceAutoFillType autoFillType)
{
    if (pattern_) {
        pattern_->NotifyFillRequestSuccess(nodeWrap, autoFillType);
    }
}

void FrameNode::NotifyFillRequestFailed(int32_t errCode)
{
    if (pattern_) {
        pattern_->NotifyFillRequestFailed(errCode);
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
    auto parent = GetAncestorNodeOfFrame();
    if (parent) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_RENDER_BY_CHILD_REQUEST);
    }
}

bool FrameNode::RequestParentDirty(bool childExpansiveAndMark)
{
    auto parent = GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(parent, false);
    parent->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST, childExpansiveAndMark);
    return true;
}

void FrameNode::MarkDirtyNode(
    bool isMeasureBoundary, bool isRenderBoundary, PropertyChangeFlag extraFlag, bool childExpansiveAndMark)
{
    if (CheckNeedRender(extraFlag)) {
        paintProperty_->UpdatePropertyChangeFlag(extraFlag);
    }
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
        auto&& opts = GetLayoutProperty()->GetSafeAreaExpandOpts();
        auto selfExpansiveToMark = opts && opts->ExpansiveToMark();
        if ((!isMeasureBoundary && IsNeedRequestParentMeasure()) || selfExpansiveToMark) {
            bool parentStopMark = false;
            auto parent = GetAncestorNodeOfFrame();
            if (parent) {
                auto parentPattern = parent->GetPattern();
                parentStopMark = parentPattern && parentPattern->StopExpandMark();
            }
            // case 1: child not expand and mark, but self expand, need to check if parent stop expand mark
            // case 2: child and self not expand, regular mark parent
            // case 3: child expand and mark, need to check parent stop expand
            bool needMarkParent =
                !childExpansiveAndMark || ((childExpansiveAndMark || selfExpansiveToMark) && !parentStopMark);
            if (needMarkParent && RequestParentDirty(selfExpansiveToMark)) {
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
    return pattern_->IsAtomicNode();
}

HitTestMode FrameNode::GetHitTestMode() const
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetHitTestMode() : HitTestMode::HTMDEFAULT;
}

void FrameNode::SetHitTestMode(HitTestMode mode)
{
    auto gestureHub = eventHub_->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    gestureHub->SetHitTestMode(mode);
}

bool FrameNode::GetTouchable() const
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetTouchable() : true;
}

bool FrameNode::GetMonopolizeEvents() const
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    return gestureHub ? gestureHub->GetMonopolizeEvents() : false;
}

RectF FrameNode::GetPaintRectWithTransform() const
{
    return renderContext_->GetPaintRectWithTransform();
}

VectorF FrameNode::GetTransformScale() const
{
    return renderContext_->GetTransformScaleValue({ 1.0f, 1.0f });
}

bool FrameNode::IsOutOfTouchTestRegion(const PointF& parentRevertPoint, int32_t sourceType)
{
    bool isInChildRegion = false;
    auto paintRect = renderContext_->GetPaintRectWithoutTransform();
    auto responseRegionList = GetResponseRegionList(paintRect, sourceType);
    auto renderContext = GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);

    auto revertPoint = parentRevertPoint;
    renderContext->GetPointWithRevert(revertPoint);
    auto subRevertPoint = revertPoint - paintRect.GetOffset();
    auto clip = renderContext->GetClipEdge().value_or(false);
    if (!InResponseRegionList(revertPoint, responseRegionList) || !GetTouchable()) {
        if (clip) {
            LOGD("TouchTest: frameNode use clip, point is out of region in %{public}s", GetTag().c_str());
            return true;
        }
        for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
            const auto& child = iter->Upgrade();
            if (child && !child->IsOutOfTouchTestRegion(subRevertPoint, sourceType)) {
                LOGD("TouchTest: point is out of region in %{public}s, but is in child region", GetTag().c_str());
                isInChildRegion = true;
                break;
            }
        }
        if (!isInChildRegion) {
            LOGD("TouchTest: point is out of region in %{public}s", GetTag().c_str());
            return true;
        }
    }
    return false;
}

void FrameNode::AddJudgeToTargetComponent(RefPtr<TargetComponent>& targetComponent)
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    if (gestureHub) {
        auto callback = gestureHub->GetOnGestureJudgeBeginCallback();
        targetComponent->SetOnGestureJudgeBegin(std::move(callback));
        auto callbackNative = gestureHub->GetOnGestureJudgeNativeBeginCallback();
        if (callbackNative) {
            targetComponent->SetOnGestureJudgeNativeBegin(std::move(callbackNative));
        }
    }
}

HitTestResult FrameNode::TouchTest(const PointF& globalPoint, const PointF& parentLocalPoint,
    const PointF& parentRevertPoint, TouchRestrict& touchRestrict, TouchTestResult& result, int32_t touchId,
    bool isDispatch)
{
    if (!isActive_ || !eventHub_->IsEnabled() || bypass_) {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("%{public}s is inActive, need't do touch test", GetTag().c_str());
        }
        return HitTestResult::OUT_OF_REGION;
    }
    auto& translateIds = NGGestureRecognizer::GetGlobalTransIds();
    auto& translateCfg = NGGestureRecognizer::GetGlobalTransCfg();
    auto paintRect = renderContext_->GetPaintRectWithTransform();
    auto origRect = renderContext_->GetPaintRectWithoutTransform();
    auto localMat = renderContext_->GetLocalTransformMatrix();
    auto param = renderContext_->GetTrans();
    localMat_ = localMat;
    if (param.empty()) {
        translateCfg[GetId()] = { .id = GetId(), .localMat = localMat };
    } else {
        translateCfg[GetId()] = { param[0], param[1], param[2], param[3], param[4], param[5], param[6], param[7],
            param[8], GetId(), localMat };
    }

    if (GetInspectorId().has_value() && GetInspectorId()->find("SCBScreen-Temp") != std::string::npos &&
        static_cast<int>(translateCfg[GetId()].degree) != 0) {
        translateCfg[GetId()].degree = 0.0;
        translateCfg[GetId()].localMat = Matrix4();
    }
    int32_t parentId = -1;
    auto parent = GetAncestorNodeOfFrame();
    if (parent) {
        AncestorNodeInfo ancestorNodeInfo { parent->GetId() };
        translateIds[GetId()] = ancestorNodeInfo;
        parentId = parent->GetId();
    }

    auto responseRegionList = GetResponseRegionList(origRect, static_cast<int32_t>(touchRestrict.sourceType));
    if (SystemProperties::GetDebugEnabled()) {
        LOGI("TouchTest: point is %{public}s in %{public}s, depth: %{public}d", parentRevertPoint.ToString().c_str(),
            GetTag().c_str(), GetDepth());
        for (const auto& rect : responseRegionList) {
            LOGI("TouchTest: responseRegionList is %{public}s, point is %{public}s", rect.ToString().c_str(),
                parentRevertPoint.ToString().c_str());
        }
    }
    {
        ACE_DEBUG_SCOPED_TRACE("FrameNode::IsOutOfTouchTestRegion");
        bool isOutOfRegion = IsOutOfTouchTestRegion(parentRevertPoint, static_cast<int32_t>(touchRestrict.sourceType));
        AddFrameNodeSnapshot(!isOutOfRegion, parentId, responseRegionList);
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
    AddJudgeToTargetComponent(targetComponent);

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
    renderContext_->GetPointWithRevert(revertPoint);
    auto subRevertPoint = revertPoint - origRect.GetOffset();
    bool consumed = false;

    auto onTouchInterceptresult = TriggerOnTouchIntercept(touchRestrict.touchEvent);
    TouchResult touchRes;
    if (onTouchInterceptresult != HitTestMode::HTMBLOCK) {
        std::vector<TouchTestInfo> touchInfos;
        CollectTouchInfos(globalPoint, subRevertPoint, touchInfos);
        touchRes = GetOnChildTouchTestRet(touchInfos);
        if ((touchRes.strategy != TouchTestStrategy::DEFAULT) && touchRes.id.empty()) {
            TAG_LOGW(AceLogTag::ACE_UIEVENT, "onChildTouchTest result is: id = %{public}s, strategy = %{public}d.",
                touchRes.id.c_str(), static_cast<int32_t>(touchRes.strategy));
            touchRes.strategy = TouchTestStrategy::DEFAULT;
        }

        auto childNode = GetDispatchFrameNode(touchRes);
        if (childNode != nullptr) {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "%{public}s do TouchTest, parameter isDispatch is true.",
                childNode->GetInspectorId()->c_str());
            auto hitResult = childNode->TouchTest(
                globalPoint, localPoint, subRevertPoint, touchRestrict, newComingTargets, touchId, true);
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

        auto childHitResult =
            child->TouchTest(globalPoint, localPoint, subRevertPoint, touchRestrict, newComingTargets, touchId);
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
            auto gestureHub = eventHub_->GetGestureEventHub();
            if (gestureHub) {
                TouchTestResult finalResult;
                const auto coordinateOffset = globalPoint - localPoint - localTransformOffset;
                preventBubbling = gestureHub->ProcessTouchTestHit(coordinateOffset, touchRestrict, newComingTargets,
                    finalResult, touchId, localPoint, targetComponent);
                newComingTargets.swap(finalResult);
            }
        } else if (touchRestrict.hitTestType == SourceType::MOUSE) {
            auto mouseHub = eventHub_->GetInputEventHub();
            if (mouseHub) {
                const auto coordinateOffset = globalPoint - localPoint;
                preventBubbling = mouseHub->ProcessMouseTestHit(coordinateOffset, newComingTargets);
            }
        }
    }

    result.splice(result.end(), std::move(newComingTargets));
    if (touchRestrict.hitTestType == SourceType::TOUCH) {
        // combine into exclusive recognizer group.
        auto gestureHub = eventHub_->GetGestureEventHub();
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

std::vector<RectF> FrameNode::GetResponseRegionList(const RectF& rect, int32_t sourceType)
{
    std::vector<RectF> responseRegionList;
    auto gestureHub = eventHub_->GetGestureEventHub();
    if (!gestureHub) {
        responseRegionList.emplace_back(rect);
        return responseRegionList;
    }
    auto scaleProperty = ScaleProperty::CreateScaleProperty();
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

bool FrameNode::InResponseRegionList(const PointF& parentLocalPoint, const std::vector<RectF>& responseRegionList) const
{
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

HitTestResult FrameNode::AxisTest(
    const PointF& globalPoint, const PointF& parentLocalPoint, AxisTestResult& onAxisResult)
{
    const auto& rect = renderContext_->GetPaintRectWithTransform();
    // TODO: disableTouchEvent || disabled_ need handle

    // TODO: Region need change to RectList
    if (!rect.IsInRegion(parentLocalPoint)) {
        return HitTestResult::OUT_OF_REGION;
    }

    bool preventBubbling = false;

    const auto localPoint = parentLocalPoint - rect.GetOffset();
    const auto& children = GetChildren();
    for (auto iter = children.rbegin(); iter != children.rend(); ++iter) {
        auto& child = *iter;
        auto childHitResult = child->AxisTest(globalPoint, localPoint, onAxisResult);
        if (childHitResult == HitTestResult::STOP_BUBBLING) {
            preventBubbling = true;
        }
        // In normal process, the node block the brother node.
        if (childHitResult == HitTestResult::BUBBLING) {
            // TODO: add hit test mode judge.
            break;
        }
    }

    AxisTestResult axisResult;
    bool isPrevent = false;
    auto inputHub = eventHub_->GetInputEventHub();
    if (inputHub) {
        const auto coordinateOffset = globalPoint - localPoint;
        isPrevent = inputHub->ProcessAxisTestHit(coordinateOffset, axisResult);
    }

    if (!preventBubbling) {
        preventBubbling = isPrevent;
        onAxisResult.splice(onAxisResult.end(), std::move(axisResult));
    }
    if (preventBubbling) {
        return HitTestResult::STOP_BUBBLING;
    }
    return HitTestResult::BUBBLING;
}

void FrameNode::AnimateHoverEffect(bool isHovered) const
{
    auto renderContext = GetRenderContext();
    if (!renderContext) {
        return;
    }
    HoverEffectType animationType = HoverEffectType::UNKNOWN;
    auto inputEventHub = eventHub_->GetInputEventHub();
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

RefPtr<FocusHub> FrameNode::GetOrCreateFocusHub() const
{
    if (!pattern_) {
        return eventHub_->GetOrCreateFocusHub();
    }
    auto focusPattern = pattern_->GetFocusPattern();
    return eventHub_->GetOrCreateFocusHub(focusPattern);
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
    pattern_->OnWindowFocused();
}

void FrameNode::OnWindowUnfocused()
{
    pattern_->OnWindowUnfocused();
}

std::pair<float, float> FrameNode::ContextPositionConvertToPX(
    const RefPtr<RenderContext>& context, const SizeF& percentReference) const
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

        offset += parent->geometryNode_->GetFrameOffset();
        parent = parent->GetAncestorNodeOfFrame(true);
    }

    return offset;
}

OffsetF FrameNode::GetPositionToScreen()
{
    auto offsetCurrent = GetOffsetRelativeToWindow();
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    OffsetF offset(windowOffset.GetX() + offsetCurrent.GetX(), windowOffset.GetY() + offsetCurrent.GetY());
    return offset;
}

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

OffsetF FrameNode::GetPositionToScreenWithTransform()
{
    auto pipelineContext = GetContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    OffsetF nodeOffset = GetPositionToWindowWithTransform();
    OffsetF offset(windowOffset.GetX() + nodeOffset.GetX(), windowOffset.GetY() + nodeOffset.GetY());
    return offset;
}

OffsetF FrameNode::GetPositionToWindowWithTransform() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto offset = context->GetPaintRectWithoutTransform().GetOffset();
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

RectF FrameNode::GetTransformRectRelativeToWindow() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, RectF());
    RectF rect = context->GetPaintRectWithTransform();
    auto parent = GetAncestorNodeOfFrame(true);
    while (parent) {
        rect = ApplyFrameNodeTranformToRect(rect, parent);
        parent = parent->GetAncestorNodeOfFrame(true);
    }
    return rect;
}

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

OffsetF FrameNode::GetPaintRectOffset(bool excludeSelf) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    OffsetF offset = excludeSelf ? OffsetF() : context->GetPaintRectWithTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame();
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return offset;
}

OffsetF FrameNode::GetPaintRectCenter(bool checkWindowBoundary) const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    auto trans = context->GetPaintRectWithTransform();
    auto offset = trans.GetOffset();
    auto center = offset + OffsetF(trans.Width() / 2.0f, trans.Height() / 2.0f);
    auto parent = GetAncestorNodeOfFrame();
    while (parent) {
        if (checkWindowBoundary && parent->IsWindowBoundary()) {
            break;
        }
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        auto scale = renderContext->GetTransformScale();
        if (scale) {
            center.SetX(center.GetX() * scale.value().x);
            center.SetY(center.GetY() * scale.value().y);
        }
        center += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return center;
}

OffsetF FrameNode::GetParentGlobalOffsetDuringLayout() const
{
    OffsetF offset {};
    auto parent = GetAncestorNodeOfFrame();
    while (parent) {
        offset += parent->geometryNode_->GetFrameOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return offset;
}

std::pair<OffsetF, bool> FrameNode::GetPaintRectGlobalOffsetWithTranslate(bool excludeSelf) const
{
    bool error = false;
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, std::make_pair(OffsetF(), error));
    OffsetF offset = excludeSelf ? OffsetF() : context->GetPaintRectWithTranslate().first.GetOffset();
    auto parent = GetAncestorNodeOfFrame();
    while (parent) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, std::make_pair(OffsetF(), error));
        auto [rect, err] = renderContext->GetPaintRectWithTranslate();
        error = error || err;
        CHECK_NULL_RETURN(rect.IsValid(), std::make_pair(offset + parent->GetPaintRectOffset(), error));
        offset += rect.GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return std::make_pair(offset, error);
}

OffsetF FrameNode::GetPaintRectOffsetToPage() const
{
    auto context = GetRenderContext();
    CHECK_NULL_RETURN(context, OffsetF());
    OffsetF offset = context->GetPaintRectWithTransform().GetOffset();
    auto parent = GetAncestorNodeOfFrame();
    while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
        auto renderContext = parent->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, OffsetF());
        offset += renderContext->GetPaintRectWithTransform().GetOffset();
        parent = parent->GetAncestorNodeOfFrame();
    }
    return (parent && parent->GetTag() == V2::PAGE_ETS_TAG) ? offset : OffsetF();
}

std::optional<RectF> FrameNode::GetViewPort() const
{
    if (viewPort_.has_value()) {
        return viewPort_;
    }
    auto parent = GetAncestorNodeOfFrame();
    while (parent && parent->GetTag() != V2::PAGE_ETS_TAG) {
        auto parentViewPort = parent->GetSelfViewPort();
        if (parentViewPort.has_value()) {
            return parentViewPort;
        }
        parent = parent->GetAncestorNodeOfFrame();
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
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
    }
}

void FrameNode::OnAccessibilityEvent(
    AccessibilityEventType eventType, std::string beforeText, std::string latestContent) const
{
    if (AceApplicationInfo::GetInstance().IsAccessibilityEnabled()) {
        AccessibilityEvent event;
        event.type = eventType;
        event.nodeId = GetAccessibilityId();
        event.beforeText = beforeText;
        event.latestContent = latestContent;
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->SendEventToAccessibility(event);
    }
}

void FrameNode::OnRecycle()
{
    for (const auto& destroyCallback : destroyCallbacks_) {
        destroyCallback();
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

    const auto& children = GetChildren();
    for (const auto& child : children) {
        pendingRemove = child->MarkRemoving() || pendingRemove;
    }
    return pendingRemove;
}

void FrameNode::AddHotZoneRect(const DimensionRect& hotZoneRect) const
{
    auto gestureHub = GetOrCreateGestureEventHub();
    gestureHub->AddResponseRect(hotZoneRect);
}

void FrameNode::RemoveLastHotZoneRect() const
{
    auto gestureHub = GetOrCreateGestureEventHub();
    gestureHub->RemoveLastResponseRect();
}

bool FrameNode::OnRemoveFromParent(bool allowTransition)
{
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

void FrameNode::CreateAnimatablePropertyFloat(
    const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent,
    const PropertyUnit& propertyType)
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
    auto maxWidth = GridSystemManager::GetInstance().GetMaxWidthWithColumnType(GridColumnType::DRAG_PANEL);
    auto geometryNode = GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, scale);
    auto width = geometryNode->GetFrameRect().Width();
    if (GetTag() != V2::WEB_ETS_TAG && width != 0 && width > maxWidth &&
        previewOption_.mode != DragPreviewMode::DISABLE_SCALE) {
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

void FrameNode::AddFRCSceneInfo(const std::string& scene, float speed, SceneStatus status)
{
    if (SystemProperties::GetDebugEnabled()) {
        const std::string sceneStatusStrs[] = {"START", "RUNNING", "END"};
        LOGI("%{public}s  AddFRCSceneInfo scene:%{public}s   speed:%{public}f  status:%{public}s", GetTag().c_str(),
            scene.c_str(), std::abs(speed), sceneStatusStrs[static_cast<int32_t>(status)].c_str());
    }

    auto renderContext = GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto pipelineContext = GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto frameRateManager = pipelineContext->GetFrameRateManager();
    CHECK_NULL_VOID(frameRateManager);

    auto expectedRate = renderContext->CalcExpectedFrameRate(scene, std::abs(speed));
    auto nodeId = GetId();
    auto iter = sceneRateMap_.find(scene);
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

void FrameNode::CheckSecurityComponentStatus(std::vector<RectF>& rect)
{
    auto paintRect = GetTransformRectRelativeToWindow();
    if (IsSecurityComponent()) {
        bypass_ = CheckRectIntersect(paintRect, rect);
    }
    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        const auto& child = iter->Upgrade();
        if (child) {
            child->CheckSecurityComponentStatus(rect);
        }
    }
    rect.push_back(paintRect);
}

bool FrameNode::CheckRectIntersect(const RectF& dest, std::vector<RectF>& origin)
{
    for (auto originRect : origin) {
        if (originRect.IsInnerIntersectWith(dest)) {
            return true;
        }
    }
    return false;
}

bool FrameNode::HaveSecurityComponent()
{
    if (IsSecurityComponent()) {
        return true;
    }
    for (auto iter = frameChildren_.rbegin(); iter != frameChildren_.rend(); ++iter) {
        const auto& child = iter->Upgrade();
        if (child && child->HaveSecurityComponent()) {
            return true;
        }
    }
    return false;
}

bool FrameNode::IsSecurityComponent()
{
    return GetTag() == V2::LOCATION_BUTTON_ETS_TAG || GetTag() == V2::PASTE_BUTTON_ETS_TAG ||
           GetTag() == V2::SAVE_BUTTON_ETS_TAG;
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
    auto res = layoutProperty_->UpdatePercentSensitive(percentHeight, percentWidth);
    if (res.first) {
        auto parent = GetAncestorNodeOfFrame();
        if (parent && parent->layoutAlgorithm_) {
            parent->layoutAlgorithm_->SetPercentWidth(true);
        }
    }
    if (res.second) {
        auto parent = GetAncestorNodeOfFrame();
        if (parent && parent->layoutAlgorithm_) {
            parent->layoutAlgorithm_->SetPercentHeight(true);
        }
    }
}

// This will call child and self measure process.
void FrameNode::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    ACE_LAYOUT_SCOPED_TRACE("Measure[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(),
        GetId(), GetAncestorNodeOfFrame() ? GetAncestorNodeOfFrame()->GetId() : 0, GetInspectorIdValue("").c_str());
    ArkUIPerfMonitor::GetInstance().RecordLayoutNode();

    if (SelfOrParentExpansive() && needRestoreSafeArea_) {
        RestoreGeoState();
        needRestoreSafeArea_ = false;
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
        isLayoutDirtyMarked_ = false;
        return;
    }
    if (!isActive_) {
        layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_MEASURE);
    }

    if (layoutAlgorithm_->SkipMeasure()) {
        isLayoutDirtyMarked_ = false;
        return;
    }

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsRunning(WeakClaim(this))) {
        geometryTransition->WillLayout(Claim(this));
    }
    auto preConstraint = layoutProperty_->GetLayoutConstraint();
    auto contentConstraint = layoutProperty_->GetContentLayoutConstraint();
    layoutProperty_->BuildGridProperty(Claim(this));

    if (parentConstraint) {
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
            ACE_SCOPED_TRACE("SkipMeasure");
            layoutAlgorithm_->SetSkipMeasure();
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
    if (pattern_ && pattern_->IsNeedAdjustByAspectRatio()) {
        const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
        auto aspectRatio = magicItemProperty.GetAspectRatioValue();
        // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and
        // aspectRatio are all set, the height is not used.
        auto width = geometryNode_->GetFrameSize().Width();
        auto height = width / aspectRatio;
        geometryNode_->SetFrameSize(SizeF({ width, height }));
    }

    layoutProperty_->UpdatePropertyChangeFlag(PROPERTY_UPDATE_LAYOUT);
}

// Called to perform layout children.
void FrameNode::Layout()
{
    ACE_LAYOUT_SCOPED_TRACE("Layout[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(),
        GetId(), GetAncestorNodeOfFrame() ? GetAncestorNodeOfFrame()->GetId() : 0, GetInspectorIdValue("").c_str());
    if (SelfOrParentExpansive()) {
        if (IsRootMeasureNode() && !needRestoreSafeArea_ && SelfExpansive()) {
            GetGeometryNode()->RestoreCache();
        } else if (needRestoreSafeArea_) {
            // if safeArea not restored in measure because of constraint not changed and so on,
            // restore this node
            RestoreGeoState();
            needRestoreSafeArea_ = false;
        }
    }
    int64_t time = GetSysTimestamp();
    OffsetNodeToSafeArea();
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr) {
        if (!IsRootMeasureNode() && geometryTransition->IsNodeInAndActive(Claim(this))) {
            SetSkipSyncGeometryNode();
        }
    }
    if (CheckNeedLayout(layoutProperty_->GetPropertyChangeFlag())) {
        if (!layoutProperty_->GetLayoutConstraint()) {
            const auto& parentLayoutConstraint = geometryNode_->GetParentLayoutConstraint();
            if (parentLayoutConstraint) {
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
        GetLayoutAlgorithm()->SetSkipLayout();
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    bool isFocusOnPage = pipeline->CheckPageFocus();
    AvoidKeyboard(isFocusOnPage);
    bool needSyncRsNode = false;
    DirtySwapConfig config;
    bool willSyncGeoProperties = OnLayoutFinish(needSyncRsNode, config);
    // skip wrapping task if node will not sync
    CHECK_NULL_VOID(willSyncGeoProperties);
    auto task = [weak = WeakClaim(this), needSync = needSyncRsNode, dirtyConfig = config]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->SyncGeometryNode(needSync, dirtyConfig);
    };
    pipeline->AddSyncGeometryNodeTask(task);
    if (IsRootMeasureNode()) {
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        CHECK_NULL_VOID(safeAreaManager);
        safeAreaManager->SetRootMeasureNodeId(GetId());
    }
    if (SelfOrParentExpansive()) {
        auto pipeline = GetContext();
        CHECK_NULL_VOID(pipeline);
        auto safeAreaManager = pipeline->GetSafeAreaManager();
        CHECK_NULL_VOID(safeAreaManager);
        safeAreaManager->AddNeedExpandNode(GetHostNode());
    }
    // if a node has geo transition but not the root node, add task only but not flush
    // or add to expand list, self node will be added to expand list in next layout
    if (geometryTransition != nullptr && !IsRootMeasureNode()) {
        return;
    }
    if (geometryTransition != nullptr) {
        pipeline->FlushSyncGeometryNodeTasks();
    }
}

bool FrameNode::SelfExpansive()
{
    auto&& opts = GetLayoutProperty()->GetSafeAreaExpandOpts();
    return opts && opts->Expansive();
}

bool FrameNode::ParentExpansive()
{
    auto parent = GetAncestorNodeOfFrame();
    CHECK_NULL_RETURN(parent, false);
    auto parentLayoutProperty = parent->GetLayoutProperty();
    CHECK_NULL_RETURN(parentLayoutProperty, false);
    auto&& parentOpts = parentLayoutProperty->GetSafeAreaExpandOpts();
    return parentOpts && parentOpts->Expansive();
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

bool FrameNode::OnLayoutFinish(bool& needSyncRsNode, DirtySwapConfig& config)
{
    isLayoutComplete_ = true;
    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    bool hasTransition = geometryTransition != nullptr && geometryTransition->IsRunning(WeakClaim(this));
    if (!isActive_ && !hasTransition) {
        layoutAlgorithm_.Reset();
        return false;
    }
    if (needSkipSyncGeometryNode_ && (!geometryTransition || !geometryTransition->IsNodeInAndActive(Claim(this)))) {
        layoutAlgorithm_.Reset();
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
    }
    renderContext_->SavePaintRect(true, layoutProperty_->GetPixelRound());
    renderContext_->SyncPartialRsProperties();
    config = { .frameSizeChange = frameSizeChange,
        .frameOffsetChange = frameOffsetChange,
        .contentSizeChange = contentSizeChange,
        .contentOffsetChange = contentOffsetChange };
    // check if need to paint content.
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(layoutAlgorithm_);
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    config.skipMeasure = layoutAlgorithmWrapper->SkipMeasure();
    config.skipLayout = layoutAlgorithmWrapper->SkipLayout();
    if (!config.skipMeasure && !config.skipLayout && GetInspectorId()) {
        auto pipeline = GetContext();
        CHECK_NULL_RETURN(pipeline, false);
        pipeline->OnLayoutCompleted(GetInspectorId()->c_str());
    }
    auto needRerender = pattern_->OnDirtyLayoutWrapperSwap(Claim(this), config);
    needRerender =
        needRerender || pattern_->OnDirtyLayoutWrapperSwap(Claim(this), config.skipMeasure, config.skipLayout);
    if (needRerender || (extensionHandler_ && extensionHandler_->NeedRender()) ||
        CheckNeedRender(paintProperty_->GetPropertyChangeFlag())) {
        MarkDirtyNode(true, true, PROPERTY_UPDATE_RENDER);
    }
    layoutAlgorithm_.Reset();
    return true;
}

void FrameNode::SyncGeometryNode(bool needSyncRsNode, const DirtySwapConfig& config)
{
    if (SystemProperties::GetSyncDebugTraceEnabled()) {
        ACE_LAYOUT_SCOPED_TRACE("SyncGeometryNode[%s][self:%d][parent:%d][key:%s]", GetTag().c_str(),
            GetId(), GetParent() ? GetParent()->GetId() : 0, GetInspectorIdValue("").c_str());
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
        if (layoutProperty_->GetLayoutConstraint().has_value()) {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(),
                layoutProperty_->GetLayoutConstraint()->percentReference.Width()));
        } else {
            renderContext_->UpdateBorderWidthF(ConvertToBorderWidthPropertyF(layoutProperty_->GetBorderWidthProperty(),
                ScaleProperty::CreateScaleProperty(), PipelineContext::GetCurrentRootWidth()));
        }
    }
    if (needSyncRsNode) {
        pattern_->BeforeSyncGeometryProperties(config);
        renderContext_->SyncGeometryProperties(RawPtr(geometryNode_), true, layoutProperty_->GetPixelRound());
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
    RebuildRenderContextTree();

    /* Adjust components' position which have been set grid properties */
    AdjustGridOffset();
}

RefPtr<LayoutWrapper> FrameNode::GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache)
{
    auto child = frameProxy_->GetFrameNodeByIndex(index, true, isCache);
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
    return frameProxy_->GetFrameNodeByIndex(index, false, isCache);
}

FrameNode* FrameNode::GetFrameNodeChildByIndex(uint32_t index, bool isCache)
{
    auto frameNode = DynamicCast<FrameNode>(frameProxy_->GetFrameNodeByIndex(index, true, isCache));
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

void FrameNode::SetActiveChildRange(int32_t start, int32_t end)
{
    frameProxy_->SetActiveChildRange(start, end);
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
    return layoutAlgorithm_->SkipMeasure();
}

bool FrameNode::CheckNeedForceMeasureAndLayout()
{
    PropertyChangeFlag flag = layoutProperty_->GetPropertyChangeFlag();
    return CheckNeedMeasure(flag) || CheckNeedLayout(flag);
}

OffsetF FrameNode::GetOffsetInScreen()
{
    auto frameOffset = GetPaintRectOffset();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF(0.0f, 0.0f));
    auto window = pipelineContext->GetWindow();
    CHECK_NULL_RETURN(window, OffsetF(0.0f, 0.0f));
    auto windowOffset = window->GetCurrentWindowRect().GetOffset();
    frameOffset += OffsetT<float> { windowOffset.GetX(), windowOffset.GetY() };
    return frameOffset;
}

RefPtr<PixelMap> FrameNode::GetPixelMap()
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
    if (needRebuild) {
        frameProxy_->ResetChildren(true);
    }
    needSyncRenderTree_ = true;
}

RefPtr<UINode> FrameNode::GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache)
{
    if (index != 0) {
        return nullptr;
    }
    return Claim(this);
}

const RefPtr<LayoutAlgorithmWrapper>& FrameNode::GetLayoutAlgorithm(bool needReset)
{
    if ((!layoutAlgorithm_ || (needReset && layoutAlgorithm_->IsExpire())) && pattern_) {
        layoutAlgorithm_ = MakeRefPtr<LayoutAlgorithmWrapper>(pattern_->CreateLayoutAlgorithm());
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

void FrameNode::DoSetActiveChildRange(int32_t start, int32_t end)
{
    if (start <= end) {
        if (start > 0 || end < 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    } else {
        if (end < 0 && start > 0) {
            SetActive(false);
            SetJSViewActive(false);
        } else {
            SetJSViewActive(true);
        }
    }
}

void FrameNode::OnInspectorIdUpdate(const std::string& id)
{
    renderContext_->UpdateNodeName(id);
    if (Recorder::EventRecorder::Get().IsExposureRecordEnable()) {
        if (exposureProcessor_) {
            return;
        }
        auto* context = GetContext();
        if (context) {
            context->AddAfterRenderTask([weak = WeakClaim(this), inspectorId = id]() {
                auto host = weak.Upgrade();
                CHECK_NULL_VOID(host);
                host->RecordExposureIfNeed(inspectorId);
            });
        }
    }
    auto parent = GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(parent);
    if (parent->GetTag() == V2::RELATIVE_CONTAINER_ETS_TAG) {
        parent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void FrameNode::RecordExposureIfNeed(const std::string& inspectorId)
{
    auto pageUrl = Recorder::GetPageUrlByNode(Claim(this));
    exposureProcessor_ = MakeRefPtr<Recorder::ExposureProcessor>(pageUrl, inspectorId);
    if (!exposureProcessor_->IsNeedRecord()) {
        return;
    }
    auto pipeline = GetContext();
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
    std::vector<double> ratios = {exposureProcessor_->GetRatio()};
    pipeline->AddVisibleAreaChangeNode(Claim(this), ratios, callback, false);
}

void FrameNode::AddFrameNodeSnapshot(bool isHit, int32_t parentId, std::vector<RectF> responseRegionList)
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto eventMgr = context->GetEventManager();
    CHECK_NULL_VOID(eventMgr);

    FrameNodeSnapshot info = {
        .nodeId = GetId(),
        .parentNodeId = parentId,
        .tag = GetTag(),
        .comId = propInspectorId_.value_or(""),
        .monopolizeEvents = GetMonopolizeEvents(),
        .isHit = isHit,
        .hitTestMode = static_cast<int32_t>(GetHitTestMode()),
        .responseRegionList = responseRegionList
    };
    eventMgr->GetEventTreeRecord().AddFrameNodeSnapshot(std::move(info));
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

void FrameNode::SearchExtensionElementInfoByAccessibilityIdNG(int64_t elementId, int32_t mode,
    int64_t offset, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    if (pattern_) {
        pattern_->SearchExtensionElementInfoByAccessibilityId(elementId, mode, offset, output);
    }
}

void FrameNode::SearchElementInfosByTextNG(int64_t elementId, const std::string& text,
    int64_t offset, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    if (pattern_) {
        pattern_->SearchElementInfosByText(elementId, text, offset, output);
    }
}

void FrameNode::FindFocusedExtensionElementInfoNG(int64_t elementId, int32_t focusType,
    int64_t offset, Accessibility::AccessibilityElementInfo& output)
{
    if (pattern_) {
        pattern_->FindFocusedElementInfo(elementId, focusType, offset, output);
    }
}

void FrameNode::FocusMoveSearchNG(int64_t elementId, int32_t direction,
    int64_t offset, Accessibility::AccessibilityElementInfo& output)
{
    if (pattern_) {
        pattern_->FocusMoveSearch(elementId, direction, offset, output);
    }
}

bool FrameNode::TransferExecuteAction(int64_t elementId, const std::map<std::string, std::string>& actionArguments,
    int32_t action, int64_t offset)
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
    auto gestureHub = eventHub_->GetGestureEventHub();
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

OffsetF FrameNode::CalculateOffsetRelativeToWindow(uint64_t nanoTimestamp)
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
            auto result = currOffset + parentTimestampOffset.second;
            SetCachedGlobalOffset({ nanoTimestamp, result });
            return result;
        } else {
            auto result = currOffset + parent->CalculateOffsetRelativeToWindow(nanoTimestamp);
            SetCachedGlobalOffset({ nanoTimestamp, result });
            return result;
        }
    } else {
        SetCachedGlobalOffset({ nanoTimestamp, currOffset });
        return currOffset;
    }
}

RefPtr<FrameNode> FrameNode::GetNodeContainer()
{
    if (GetTag() == "NodeContainer") {
        return Claim(this);
    }
    auto parent = GetParent();
    while (parent && parent->GetTag() != "NodeContainer") {
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

HitTestMode FrameNode::TriggerOnTouchIntercept(const TouchEvent& touchEvent)
{
    auto gestureHub = eventHub_->GetGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, HitTestMode::HTMDEFAULT);
    auto onTouchIntercept = gestureHub->GetOnTouchIntercept();
    CHECK_NULL_RETURN(onTouchIntercept, HitTestMode::HTMDEFAULT);
    TouchEventInfo event("touchEvent");
    event.SetTimeStamp(touchEvent.time);
    event.SetPointerEvent(touchEvent.pointerEvent);
    TouchLocationInfo changedInfo("onTouch", touchEvent.id);
    PointF lastLocalPoint(touchEvent.x, touchEvent.y);
    NGGestureRecognizer::Transform(lastLocalPoint, Claim(this), false, false);
    auto localX = static_cast<float>(lastLocalPoint.GetX());
    auto localY = static_cast<float>(lastLocalPoint.GetY());
    changedInfo.SetLocalLocation(Offset(localX, localY));
    changedInfo.SetGlobalLocation(Offset(touchEvent.x, touchEvent.y));
    changedInfo.SetScreenLocation(Offset(touchEvent.screenX, touchEvent.screenY));
    changedInfo.SetTouchType(touchEvent.type);
    changedInfo.SetForce(touchEvent.force);
    if (touchEvent.tiltX.has_value()) {
        changedInfo.SetTiltX(touchEvent.tiltX.value());
    }
    if (touchEvent.tiltY.has_value()) {
        changedInfo.SetTiltY(touchEvent.tiltY.value());
    }
    changedInfo.SetSourceTool(touchEvent.sourceTool);
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
    event.SetSourceTool(touchEvent.sourceTool);
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
        TouchLocationInfo info("onTouch", item.id);
        info.SetGlobalLocation(Offset(globalX, globalY));
        info.SetLocalLocation(Offset(localX, localY));
        info.SetScreenLocation(Offset(screenX, screenY));
        info.SetTouchType(touchEvent.type);
        info.SetForce(item.force);
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
    pattern_->OnAttachContext(context);
}

void FrameNode::DetachContext(bool recursive)
{
    CHECK_NULL_VOID(context_);
    pattern_->OnDetachContext(context_);
    UINode::DetachContext(recursive);
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

bool FrameNode::IsContextTransparent()
{
    ACE_SCOPED_TRACE("Transparent detection");
    const auto& rect = renderContext_->GetPaintRectWithTransform();
    auto width = rect.Width();
    auto height = rect.Height();
    if (renderContext_->GetOpacity().has_value() && renderContext_->GetOpacity().value() <= MIN_OPACITY) {
        return true;
    }
    if (layoutTags_.find(GetTag()) == layoutTags_.end()) {
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

} // namespace OHOS::Ace::NG
