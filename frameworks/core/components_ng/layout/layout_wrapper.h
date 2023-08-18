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

#include <map>
#include <optional>
#include <string>
#include <unordered_map>

#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/magic_layout_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
class FrameNode;

class ACE_FORCE_EXPORT LayoutWrapper : public virtual AceType {
    DECLARE_ACE_TYPE(LayoutWrapper, AceType)
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

    virtual RefPtr<LayoutWrapper> GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree = true) = 0;
    virtual RefPtr<LayoutWrapper> GetChildByIndex(uint32_t index) = 0;
    virtual const std::list<RefPtr<LayoutWrapper>>& GetAllChildrenWithBuild(bool addToRenderTree = true) = 0;
    virtual void RemoveChildInRenderTree(uint32_t index) = 0;
    virtual void RemoveAllChildInRenderTree() = 0;

    RefPtr<FrameNode> GetHostNode() const;
    virtual const std::string& GetHostTag() const = 0;
    virtual bool IsActive() const = 0;
    virtual void SetActive(bool active = true) = 0;

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

    virtual bool SkipMeasureContent() const;

    virtual void SetCacheCount(
        int32_t cacheCount = 0, const std::optional<LayoutConstraintF>& itemConstraint = std::nullopt) = 0;
    virtual float GetBaselineDistance() const = 0;
    virtual bool CheckShouldRunOnMain()
    {
        return true;
    }

    virtual bool CheckNeedForceMeasureAndLayout() = 0;

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

    bool IsContraintNoChanged() const
    {
        return isConstraintNotChanged_;
    }
    virtual void SetLongPredictTask() {}

    static void ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint);

    // apply keyboard avoidance on content rootNodes
    void AvoidKeyboard();
    // expand the SafeArea of expansive nodes, which are previously recorded during Layout traversal
    void ExpandSafeArea();

    // save geometry states before SafeArea expansion / keyboard avoidance
    void SaveGeoState();
    // restore to the geometry state after last Layout and before SafeArea expansion and keyboard avoidance
    void RestoreGeoState();

protected:
    void CreateRootConstraint();
    void ApplyConstraint(LayoutConstraintF constraint);

    void OffsetNodeToSafeArea();
    // keyboard avoidance is done by offsetting, to expand into keyboard area, reverse the offset.
    void ExpandIntoKeyboard();

    WeakPtr<FrameNode> hostNode_;

    bool isConstraintNotChanged_ = false;
    bool isRootNode_ = false;
    bool isOverlayNode_ = false;
    std::optional<bool> skipMeasureContent_;
    std::optional<bool> needForceMeasureAndLayout_;

    ACE_DISALLOW_COPY_AND_MOVE(LayoutWrapper);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_LAYOUTS_LAYOUT_WRAPPER_H
