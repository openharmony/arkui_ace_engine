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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H

#include <cstdint>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/constraint_flags.h"
#include "core/components_ng/property/layout_constraint.h"
#include "ui/properties/safe_area_insets.h"

namespace OHOS::Ace::NG {
class FrameNode;
class UINode;
class LayoutProperty;
struct SafeAreaInsets;
struct SafeAreaExpandOpts;

class RecursiveLock {
public:
    virtual void Lock() {}
    virtual void Unlock() {}
};

class RecursionGuard final {
public:
    RecursionGuard(RecursiveLock& lock) : lock_(lock)
    {
        lock_.Lock();
    }
    ~RecursionGuard()
    {
        lock_.Unlock();
    }
    RecursionGuard(const RecursionGuard& rhs) : lock_(rhs.lock_)
    {
        lock_.Lock();
    }

private:
    RecursiveLock& lock_;
};

class ChildrenListWithGuard final {
public:
    ChildrenListWithGuard(const std::list<RefPtr<LayoutWrapper>>& children, RecursiveLock& lock)
        : children_(children), guard_(lock)
    {}
    auto begin() const
    {
        return children_.begin();
    }
    auto end() const
    {
        return children_.end();
    }
    auto rbegin() const
    {
        return children_.rbegin();
    }
    auto rend() const
    {
        return children_.rend();
    }
    auto empty() const
    {
        return children_.empty();
    }
    auto size() const
    {
        return children_.size();
    }
    auto& front() const
    {
        return children_.front();
    }
    auto& back() const
    {
        return children_.back();
    }
    operator std::list<RefPtr<LayoutWrapper>>() const
    {
        return children_;
    }

private:
    const std::list<RefPtr<LayoutWrapper>>& children_;
    RecursionGuard guard_;
};

struct ActiveChildRange {
    int32_t start = -1;
    int32_t end = -1;
    int32_t cacheStart = 0;
    int32_t cacheEnd = 0;
};

struct ActiveChildSets {
    std::set<int32_t> activeItems;
    std::set<int32_t> cachedItems;
};

enum class IgnoreStrategy {
    NORMAL = 0,
    FROM_MARGIN,
    STRIDE_OVER,
    AXIS_INSENSITIVE
};
class ACE_FORCE_EXPORT LayoutWrapper : public virtual AceType {
    DECLARE_ACE_TYPE(LayoutWrapper, AceType);
public:
    LayoutWrapper(WeakPtr<FrameNode> hostNode) : hostNode_(std::move(hostNode)) {}
    ~LayoutWrapper() override = default;

    virtual const RefPtr<LayoutAlgorithmWrapper>& GetLayoutAlgorithm(bool needReset = false) = 0;
    // This will call child and self measure process.
    virtual void Measure(const std::optional<LayoutConstraintF>& parentConstraint) = 0;

    // Called to perform layout children.
    virtual void Layout() = 0;

    virtual int32_t GetTotalChildCount() const = 0;
    virtual const RefPtr<GeometryNode>& GetGeometryNode() const = 0;
    virtual const RefPtr<LayoutProperty>& GetLayoutProperty() const = 0;

    virtual RefPtr<LayoutWrapper> GetOrCreateChildByIndex(
        uint32_t index, bool addToRenderTree = true, bool isCache = false) = 0;
    /**
     * @param isCache if false, child is added to render tree and AttachToMainTree is called.
     */
    virtual RefPtr<LayoutWrapper> GetChildByIndex(uint32_t index, bool isCache = false) = 0;
    virtual ChildrenListWithGuard GetAllChildrenWithBuild(bool addToRenderTree = true) = 0;
    virtual void RemoveChildInRenderTree(uint32_t index) = 0;
    virtual void RemoveAllChildInRenderTree() = 0;
    /**
     * @param cacheStart number of items to cache before @c start
     * @param cacheEnd number of items to cache after @c end
     * @param showCached whether to set cached items as active
     * @note To deactivate all children, set @c start and @c end to -1
     */
    virtual void SetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart = 0, int32_t cacheEnd = 0, bool showCached = false) = 0;
    virtual void SetActiveChildRange(const std::optional<ActiveChildSets>& activeChildSets,
        const std::optional<ActiveChildRange>& activeChildRange = std::nullopt)
    {}
    virtual void RecycleItemsByIndex(int32_t start, int32_t end) = 0;

    virtual void SetActiveChildRange(const std::set<int32_t>& activeIndexes, const std::set<int32_t>& cachedIndexes) {}
    virtual void RecycleItemsByIndex(const std::set<int32_t>& indexes) {}

    RefPtr<FrameNode> GetHostNode() const;
    virtual const std::string& GetHostTag() const = 0;
    virtual bool IsActive() const = 0;
    virtual void SetActive(bool active = true, bool needRebuildRenderContext = false) = 0;

    bool IsRootMeasureNode() const
    {
        return isRootNode_;
    }

    void SetRootMeasureNode(bool isRoot = true)
    {
        isRootNode_ = isRoot;
    }

    virtual bool IsOutOfLayout() const
    {
        return false;
    }

    virtual OffsetF GetParentGlobalOffsetWithSafeArea(bool checkBoundary = false, bool checkPosition = false) const;

    virtual bool SkipMeasureContent() const;

    virtual void SetCacheCount(
        int32_t cacheCount = 0, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt) = 0;
    virtual float GetBaselineDistance() const = 0;
    virtual bool CheckShouldRunOnMain()
    {
        return true;
    }

    virtual bool CheckNeedForceMeasureAndLayout() = 0;

    virtual bool ReachResponseDeadline() const
    {
        return false;
    }

    void SetIsOverlayNode(bool isOverlayNode)
    {
        isOverlayNode_ = isOverlayNode;
    }

    // ------------------------------------------------------------------------
    // performance check
    void AddNodeFlexLayouts();
    void AddNodeLayoutTime(int64_t time);
    // ------------------------------------------------------------------------

    virtual void BuildLazyItem() {}

    bool ConstraintChanged() const
    {
        return !isConstraintNotChanged_;
    }
    const ConstraintFlags& GetConstraintChanges() const
    {
        return constraintChanges_;
    }
    const ConstraintFlags& GetContentChanges() const
    {
        return contentConstraintChanges_;
    }

    virtual void SetLongPredictTask() {}

    static void ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint);

    // apply keyboard avoidance on content rootNodes
    bool AvoidKeyboard(bool isFocusOnPage = true);
    // expand the SafeArea of expansive nodes, which are previously recorded during Layout traversal
    void ExpandSafeArea();
    void AdjustNotExpandNode();
    void AdjustFixedSizeNode(RectF& frame);
    void ExpandHelper(const std::unique_ptr<SafeAreaExpandOpts>& opts, RectF& frame);
    ExpandEdges GetAccumulatedSafeAreaExpand(bool includingSelf = false,
        IgnoreLayoutSafeAreaOpts options = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
            .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL },
        IgnoreStrategy strategy = IgnoreStrategy::NORMAL);
    void ResetSafeAreaPadding();

    bool SkipSyncGeometryNode() const
    {
        return needSkipSyncGeometryNode_;
    }

    void SetSkipSyncGeometryNode(bool needSkip = true)
    {
        needSkipSyncGeometryNode_ = needSkip;
    }

    RectF GetFrameRectWithoutSafeArea() const;
    RectF GetFrameRectWithSafeArea(bool checkPosition = false) const;
    void AddChildToExpandListIfNeeded(const WeakPtr<FrameNode>& node);
    void ApplyConstraintWithoutMeasure(const std::optional<LayoutConstraintF>& constraint);
    RectF GetBackGroundAccumulatedSafeAreaExpand();

    bool GetIgnoreLayoutProcess()
    {
        return ignoreLayoutProcess_;
    }

    // Paired with GetHasPreMeasured. Once a node being collected as a measure-delayed child, set true.
    void SetHasPreMeasured()
    {
        hasPreMeasured_ = true;
    }

    // Paired with SetHasPreMeasured. To avoid re-entering PreMeasure in the delayed measure process.
    bool GetHasPreMeasured()
    {
        return std::exchange(hasPreMeasured_, false);
    }

    bool CheckHasPreMeasured() const
    {
        return hasPreMeasured_;
    }

    void SetEscapeDelayForIgnore(bool noDelay)
    {
        escapeDelayForIgnore_ = noDelay;
    }

    bool GetEscapeDelayForIgnore() const
    {
        return escapeDelayForIgnore_;
    }

    bool PredictMeasureResult(LayoutWrapper* childWrapper, const std::optional<LayoutConstraintF>& parentConstraint);

    // Paired with GetDelaySelfLayoutForIgnore. Once a node being collected as a layout-delayed child, set true.
    void SetDelaySelfLayoutForIgnore()
    {
        delaySelfLayoutForIgnore_ = true;
    }

    // Paired with SetDelaySelfLayoutForIgnore. Access to skip THE JUST first layout after SetDelaySelfLayoutForIgnore,
    // and valid layout should be called during PostponedTaskForIgnore.
    bool GetDelaySelfLayoutForIgnore()
    {
        return std::exchange(delaySelfLayoutForIgnore_, false);
    }

    bool IsIgnoreOptsValid();

    bool IsScrollableAxisInsensitive()
    {
        return isScrollableAxis_;
    }

protected:
    void CreateRootConstraint();
    void ApplyConstraint(LayoutConstraintF constraint);

    void OffsetNodeToSafeArea();
    // keyboard avoidance is done by offsetting, to expand into keyboard area, reverse the offset.
    OffsetF ExpandIntoKeyboard();
    bool CheckValidSafeArea();
    float GetPageCurrentOffset();

    void SetIgnoreLayoutProcess(bool switchTo)
    {
        ignoreLayoutProcess_ = switchTo;
    }

    void ResetIgnoreLayoutProcess()
    {
        ignoreLayoutProcess_ = false;
    }

    enum class StartPoint {
        NORMAL = 0,
        INCLUDING_SELF,
        FROM_MARGIN
    };
    bool AccumulateExpandCacheHit(ExpandEdges& totalExpand, const PaddingPropertyF& innerSpace);
    ExpandEdges GetAccumulatedSafeAreaExpandForAllEdges(
        StartPoint startPoint = StartPoint::NORMAL, LayoutSafeAreaType ignoreType = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM);
    void GetAccumulatedSafeAreaExpandHelper(RectF& adjustingRect, ExpandEdges& totalExpand, bool fromSelf = false,
        LayoutSafeAreaType ignoreType = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM);
    void ParseSafeAreaPaddingSides(const PaddingPropertyF& parentSafeAreaPadding,
        const PaddingPropertyF& parentInnerSpace, const RectF& adjustingRect, ExpandEdges& rollingExpand);
    WeakPtr<FrameNode> hostNode_;

    ConstraintFlags constraintChanges_;
    ConstraintFlags contentConstraintChanges_;

    bool isConstraintNotChanged_ = false;
    bool isRootNode_ = false;
    bool isOverlayNode_ = false;
    bool needSkipSyncGeometryNode_ = false;
    std::optional<bool> skipMeasureContent_;
    std::optional<bool> needForceMeasureAndLayout_;
    bool ignoreLayoutProcess_ = false;
    bool hasPreMeasured_ = false;
    bool delaySelfLayoutForIgnore_ = false;
    bool escapeDelayForIgnore_ = false;
    bool isScrollableAxis_ = false;
private:
    void AdjustChildren(const OffsetF& offset, bool parentScrollable);
    void AdjustChild(RefPtr<UINode> node, const OffsetF& offset, bool parentScrollable);

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapper);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
