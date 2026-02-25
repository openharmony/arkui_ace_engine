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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PIPELINE_IGNORE_LAYOUT_SAFE_AREA_SCHEDULING_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PIPELINE_IGNORE_LAYOUT_SAFE_AREA_SCHEDULING_TEST_NG_H

#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/list/list_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_algorithm.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

/**
 * ============================================================================
 * ignoreLayoutSafeArea Layout Flow Tracing Test Framework
 * ============================================================================
 * 
 * This test framework verifies two implementation approaches of ignoreLayoutSafeArea mechanism:
 * 1. IgnoreLayoutSafeAreaScheduling001: Container Proactive Packing Mechanism (Example 2)
 * 2. IgnoreLayoutSafeAreaScheduling002: Non-intrusive Pattern Hook Mechanism (Example 1)
 * 
 * Reference: IgnoreLayoutSafeArea_Trace_Example.md
 * 
 * ----------------------------------------------------------------------------
 * Four Key Execution Behaviors
 * ----------------------------------------------------------------------------
 * 
 * Measure Stage:
 *   ✓ Complete Measure: FrameNode::Measure → LayoutAlgorithm::Measure fully executed
 *      Event format: "Node:Measure"
 * 
 *   ⊗ PreMeasure Skip: FrameNode::Measure triggered, but PreMeasure returns true and exits early
 *      Event format: "Node:PreMeasure(skip)"
 *      Applicable to: Pattern Hook mechanism
 * 
 *   ✗ Measure Not Called: Container algorithm skips via continue after IsExpandConstraintNeeded() check
 *      Event format: No event recorded
 *      Applicable to: Container Proactive Packing mechanism
 *
 * Layout Stage:
 *   ✓ Complete Layout: FrameNode::Layout → LayoutAlgorithm::Layout fully executed
 *      Event format: "Node:Layout"
 * 
 *   ⊗ Delay Skip Layout: FrameNode::Layout triggered, but GetDelaySelfLayoutForIgnore()=true exits early
 *      Event format: "Node:Layout(skip)"
 *      Applicable to: Both mechanisms
 * 
 * Other Events:
 *   "Node:PostTaskForIgnore": Container packs ignore child nodes after Measure completes
 *   "Node:PostponedTaskForIgnore": Process ignore child nodes in postponed task (Pattern Hook mechanism)
 * 
 * ============================================================================
 */

/**
 * NodeNameRegistry - Registry to map FrameNode to node names for tracing.
 */
class NodeNameRegistry {
public:
    static std::map<int32_t, std::string> nodeNames;
    
    static void Register(int32_t nodeId, const std::string& nodeName)
    {
        nodeNames[nodeId] = nodeName;
    }
    
    static std::string GetName(int32_t nodeId)
    {
        auto it = nodeNames.find(nodeId);
        return (it != nodeNames.end()) ? it->second : "Unknown";
    }
    
    static void Clear()
    {
        nodeNames.clear();
    }
};

// Initialize static member
inline std::map<int32_t, std::string> NodeNameRegistry::nodeNames;

/**
 * LayoutTracer - Global event recorder for layout scheduling verification.
 * Records detailed events including FrameNode and Algorithm level operations.
 */
class LayoutTracer {
public:
    static std::vector<std::string> events;
    static void Clear()
    {
        events.clear();
    }
    static void Record(const std::string& event)
    {
        events.push_back(event);
    }
    static void RecordFrameNodeMeasure(const std::string& nodeName)
    {
        events.push_back(nodeName + ":FrameNode::Measure");
    }
    static void RecordFrameNodePreMeasure(const std::string& nodeName, bool skip)
    {
        events.push_back(nodeName + ":FrameNode::PreMeasure(" + (skip ? "skip" : "execute") + ")");
    }
    static void RecordFrameNodePostTaskForIgnore(const std::string& nodeName, const std::string& bundleContent)
    {
        events.push_back(nodeName + ":FrameNode::PostTaskForIgnore(bundle: " + bundleContent + ")");
    }
    static void RecordFrameNodeLayout(const std::string& nodeName)
    {
        events.push_back(nodeName + ":FrameNode::Layout");
    }
    static void RecordFrameNodePostponedTaskForIgnore(const std::string& nodeName)
    {
        events.push_back(nodeName + ":FrameNode::PostponedTaskForIgnore");
    }
    static void RecordAlgorithmMeasure(const std::string& nodeName)
    {
        events.push_back(nodeName + ":Algorithm::Measure");
    }
    static void RecordAlgorithmLayout(const std::string& nodeName)
    {
        events.push_back(nodeName + ":Algorithm::Layout");
    }
    static void RecordFlushPostponedLayoutTask(const std::string& bundleContent)
    {
        events.push_back("FlushPostponedLayoutTask(bundle: " + bundleContent + ")");
    }
    static void RecordFlushPostponedLayoutTaskEnd(const std::string& bundleContent)
    {
        events.push_back("FlushPostponedLayoutTask End(bundle: " + bundleContent + ")");
    }
};

/**
 * TracingFlexAlgorithm - Subclass of FlexLayoutAlgorithm that records Measure/Layout events.
 * Used for container nodes in IgnoreLayoutSafeAreaScheduling001 (Container Proactive Packing Mechanism).
 * 
 * Event format:
 * - "Node:Measure" = ✓ Complete Measure (FrameNode::Measure → LayoutAlgorithm::Measure fully executed)
 * - "Node:Layout" = ✓ Complete Layout (FrameNode::Layout → LayoutAlgorithm::Layout fully executed)
 */
class TracingFlexAlgorithm : public FlexLayoutAlgorithm {
    DECLARE_ACE_TYPE(TracingFlexAlgorithm, FlexLayoutAlgorithm);

public:
    explicit TracingFlexAlgorithm(const std::string& nodeName) : nodeName_(nodeName) {}
    ~TracingFlexAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        LayoutTracer::Record(nodeName_ + ":Measure");
        FlexLayoutAlgorithm::Measure(layoutWrapper);
    }

    void Layout(LayoutWrapper* layoutWrapper) override
    {
        LayoutTracer::Record(nodeName_ + ":Layout");
        FlexLayoutAlgorithm::Layout(layoutWrapper);
    }

private:
    std::string nodeName_;
};

/**
 * TracingScrollAlgorithm - Subclass of ScrollLayoutAlgorithm that records Measure/Layout events.
 * Used for container nodes in IgnoreLayoutSafeAreaScheduling002 (Non-intrusive Pattern Hook Mechanism).
 *
 * Event format:
 * - "Node:Measure" = ✓ Complete Measure (FrameNode::Measure → LayoutAlgorithm::Measure fully executed)
 * - "Node:Layout" = ✓ Complete Layout (FrameNode::Layout → LayoutAlgorithm::Layout fully executed)
 * - "Node:PostTaskForIgnore" = Container packs ignore child nodes after Measure completes
 */
class TracingScrollAlgorithm : public ScrollLayoutAlgorithm {
    DECLARE_ACE_TYPE(TracingScrollAlgorithm, ScrollLayoutAlgorithm);

public:
    explicit TracingScrollAlgorithm(const std::string& nodeName)
        : ScrollLayoutAlgorithm(0.0f), nodeName_(nodeName) {}
    ~TracingScrollAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        // Record Measure event (Algorithm level)
        LayoutTracer::Record(nodeName_ + ":Measure");
        ScrollLayoutAlgorithm::Measure(layoutWrapper);
    }

    void Layout(LayoutWrapper* layoutWrapper) override
    {
        // Record Layout event
        LayoutTracer::Record(nodeName_ + ":Layout");
        ScrollLayoutAlgorithm::Layout(layoutWrapper);
    }

private:
    std::string nodeName_;
};

/**
 * TracingBoxAlgorithm - Subclass of BoxLayoutAlgorithm that records Measure/Layout events.
 * Used for leaf nodes (C1-C8) in both test cases.
 * 
 * Event format:
 * - "Node:Measure" = ✓ Complete Measure (FrameNode::Measure → LayoutAlgorithm::Measure fully executed)
 * - "Node:Layout" = ✓ Complete Layout (FrameNode::Layout → LayoutAlgorithm::Layout fully executed)
 */
class TracingBoxAlgorithm : public BoxLayoutAlgorithm {
    DECLARE_ACE_TYPE(TracingBoxAlgorithm, BoxLayoutAlgorithm);

public:
    explicit TracingBoxAlgorithm(const std::string& nodeName) : nodeName_(nodeName) {}
    ~TracingBoxAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        LayoutTracer::Record(nodeName_ + ":Measure");
        BoxLayoutAlgorithm::Measure(layoutWrapper);
    }

    void Layout(LayoutWrapper* layoutWrapper) override
    {
        LayoutTracer::Record(nodeName_ + ":Layout");
        BoxLayoutAlgorithm::Layout(layoutWrapper);
    }

private:
    std::string nodeName_;
};

/**
 * TracingFlexPattern - Subclass of FlexLayoutPattern that creates TracingFlexAlgorithm.
 * Used for container nodes in IgnoreLayoutSafeAreaScheduling001 (Container Proactive Packing Mechanism).
 * 
 * FlexLayoutPattern characteristics:
 * - ChildPreMeasureHelperEnabled() returns false (does NOT use Pattern Hook)
 * - PostponedTaskForIgnoreEnabled() returns false (returns false, creates LAYOUT_FOR_IGNORE tasks)
 */
class TracingFlexPattern : public FlexLayoutPattern {
    DECLARE_ACE_TYPE(TracingFlexPattern, FlexLayoutPattern);

public:
    explicit TracingFlexPattern(const std::string& nodeName)
        : FlexLayoutPattern(false), nodeName_(nodeName)
    {}
    ~TracingFlexPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TracingFlexAlgorithm>(nodeName_);
    }

private:
    std::string nodeName_;
};

/**
 * TracingFrameNode - Subclass of FrameNode that intercepts Measure and Layout calls.
 * Used to detect PreMeasure(skip), PostTaskForIgnore, and Layout(skip) events.
 *
 * Overrides Measure (virtual) to detect:
 * - "Node:PreMeasure(skip)" = ⊗ PreMeasure Skip (FrameNode::Measure triggered,
 * but PreMeasure returns true and exits early)
 * - "Node:PostTaskForIgnore" = Container packs ignore child nodes after Measure completes (hook pattern only)
 *
 * Overrides Layout (virtual) to detect:
 * - "Node:Layout(skip)" = ⊗ Delay Skip Layout (FrameNode::Layout triggered, but
 * GetDelaySelfLayoutForIgnore()=true exits early)
 *
 * Note: FrameNode::PreMeasure and FrameNode::PostTaskForIgnore are non-virtual functions,
 * so they cannot be overridden by subclasses. Detection is done via state inspection in the
 * Measure override instead.
 */
class TracingFrameNode : public FrameNode {
    DECLARE_ACE_TYPE(TracingFrameNode, FrameNode);

public:
    TracingFrameNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot,
        const std::string& nodeName)
        : FrameNode(tag, nodeId, pattern, isRoot), nodeName_(nodeName) {}
    
    ~TracingFrameNode() override = default;

    static RefPtr<TracingFrameNode> CreateTracingFrameNode(
        const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot,
        const std::string& nodeName)
    {
        auto node = MakeRefPtr<TracingFrameNode>(tag, nodeId, pattern, isRoot, nodeName);
        node->InitializePatternAndContext();
        return node;
    }

    /**
     * Override Measure (virtual) to detect PreMeasure(skip) and PostTaskForIgnore events.
     *
     * Why not override PreMeasure/PostTaskForIgnore directly?
     * - FrameNode::PreMeasure and FrameNode::PostTaskForIgnore are non-virtual functions.
     *   Defining them in a subclass only results in name hiding, not overriding.
     *   When FrameNode::Measure() calls PreMeasure() or PostTaskForIgnore() internally,
     *   C++ static dispatch always resolves to FrameNode's own versions.
     * Detection approach:
     * - PreMeasure(skip): When PreMeasure returns true (skip), ChildPreMeasureHelper calls
     *   SetHasPreMeasured() and Measure returns early. We detect this by checking
     *   CheckHasPreMeasured() before and after calling FrameNode::Measure().
     * - PostTaskForIgnore: When the hook pattern (ChildPreMeasureHelperEnabled=true) collects
     *   delay children, delayLayoutChildren_ is populated via AddDelayLayoutChild() and is NOT
     *   cleared until PostponedTaskForIgnore() runs later. We detect this by checking
     *   GetDelayLayoutChildren() after FrameNode::Measure().
     */
    void Measure(const std::optional<LayoutConstraintF>& parentConstraint) override
    {
        // Save pre-state to detect PreMeasure skip
        bool hadPreMeasured = CheckHasPreMeasured();

        // Call parent's full Measure (internally calls non-virtual PreMeasure and PostTaskForIgnore)
        FrameNode::Measure(parentConstraint);

        // Detect PreMeasure skip: if hasPreMeasured_ was just set, Measure returned early
        if (!hadPreMeasured && CheckHasPreMeasured()) {
            LayoutTracer::Record(nodeName_ + ":PreMeasure(skip)");
        }
    }

    void Layout() override
    {
        // Replicate FrameNode::Layout logic to detect skip
        // Check and consume the delaySelfLayoutForIgnore flag
        if (GetDelaySelfLayoutForIgnore()) {
            // Layout is skipped due to delaySelfLayoutForIgnore
            LayoutTracer::Record(nodeName_ + ":Layout(skip)");
            return;  // Match FrameNode::Layout behavior
        }

        // Normal Layout path - call parent implementation
        FrameNode::Layout();
    }

private:
    std::string nodeName_;
};

/**
 * TracingScrollPattern - Subclass of ScrollPattern that creates TracingScrollAlgorithm.
 * Used for container nodes in IgnoreLayoutSafeAreaScheduling002 (Non-intrusive Pattern Hook Mechanism).
 * 
 * ScrollPattern characteristics (from base class ScrollablePattern):
 * - ChildPreMeasureHelperEnabled() returns true (enables Pattern Hook)
 * - PostponedTaskForIgnoreEnabled() returns true (returns true, directly applies ignoreAdjust + Layout)
 *
 * Overrides PostponedTaskForIgnore to trace detailed execution flow:
 * - "Node:PostponedTaskForIgnore" = Process ignore child nodes in postponed task
 * (applyignoreAdjust+ call child->Layout())
 * 
 * Note: PreMeasure(skip) events are recorded by TracingFrameNode::ChildPreMeasureHelper, not here.
 */
class TracingScrollPattern : public ScrollPattern {
    DECLARE_ACE_TYPE(TracingScrollPattern, ScrollPattern);

public:
    explicit TracingScrollPattern(const std::string& nodeName) : nodeName_(nodeName) {}
    ~TracingScrollPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto algorithm = MakeRefPtr<TracingScrollAlgorithm>(nodeName_);
        algorithm->SetScrollableDistance(GetScrollableDistance());
        return algorithm;
    }

private:
    std::string nodeName_;
};

/**
 * TracingMultiChildAlgorithm - Simple layout algorithm for multi-child containers.
 * Used for virtual container nodes in IgnoreLayoutSafeAreaScheduling002.
 * 
 * This algorithm simply measures and layouts all children sequentially,
 * without virtual scrolling or complex positioning logic.
 *
 * Event format:
 * - "Node:Measure" = ✓ Complete Measure
 * - "Node:Layout" = ✓ Complete Layout
 */
class TracingMultiChildAlgorithm : public LayoutAlgorithm {
    DECLARE_ACE_TYPE(TracingMultiChildAlgorithm, LayoutAlgorithm);

public:
    explicit TracingMultiChildAlgorithm(const std::string& nodeName)
        : nodeName_(nodeName) {}
    ~TracingMultiChildAlgorithm() override = default;

    void Measure(LayoutWrapper* layoutWrapper) override
    {
        // Record Measure event
        LayoutTracer::Record(nodeName_ + ":Measure");
        
        // Set self size first (use parent constraint's ideal size)
        auto selfIdealSize = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint()->selfIdealSize;
        auto width = selfIdealSize.Width().value_or(600.0f);
        auto height = selfIdealSize.Height().value_or(600.0f);
        layoutWrapper->GetGeometryNode()->SetFrameSize(SizeF(width, height));
        
        // Get self size to set as parentIdealSize for children
        auto selfSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
        
        // Create child constraint with parentIdealSize set to self size
        auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        layoutConstraint.parentIdealSize = OptionalSizeF(selfSize.Width(), selfSize.Height());
        
        // Measure all children
        for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->Measure(layoutConstraint);
        }
    }

    void Layout(LayoutWrapper* layoutWrapper) override
    {
        // Record Layout event
        LayoutTracer::Record(nodeName_ + ":Layout");
        
        // Layout all children vertically (simple stack layout)
        float offsetY = 0.0f;
        for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
            child->GetGeometryNode()->SetMarginFrameOffset(OffsetF(0.0f, offsetY));
            child->Layout();
            offsetY += child->GetGeometryNode()->GetFrameSize().Height();
        }
    }

private:
    std::string nodeName_;
};

/**
 * TracingMultiChildPattern - Simple multi-child container pattern with Pattern Hook support.
 * Used for container nodes in IgnoreLayoutSafeAreaScheduling002.
 * 
 * Inherits from Pattern and manually enables Pattern Hook mechanism by overriding:
 * - ChildPreMeasureHelperEnabled() - returns true for IgnoreLayoutSafeArea support
 * - PostponedTaskForIgnoreEnabled() - returns true for deferred layout scheduling
 * - PostponedTaskForIgnore() - records event for tracing
 */
class TracingMultiChildPattern : public Pattern {
    DECLARE_ACE_TYPE(TracingMultiChildPattern, Pattern);

public:
    explicit TracingMultiChildPattern(const std::string& nodeName) : nodeName_(nodeName) {}
    ~TracingMultiChildPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TracingMultiChildAlgorithm>(nodeName_);
    }

    // Enable Pattern Hook mechanism for IgnoreLayoutSafeArea
    bool ChildPreMeasureHelperEnabled() override
    {
        return true;
    }

    bool PostponedTaskForIgnoreEnabled() override
    {
        return true;
    }

    // Not an atomic node - has children
    bool IsAtomicNode() const override
    {
        return false;
    }

private:
    std::string nodeName_;
};

/**
 * TracingLeafPattern - Subclass of Pattern that creates TracingBoxAlgorithm.
 * Used for leaf nodes (C1-C8) in both test cases.
 * 
 * Leaf nodes characteristics:
 * - IsAtomicNode() returns true (leaf node)
 * - Each leaf node executes M×1, L×1 (follows normal flow)
 */
class TracingLeafPattern : public Pattern {
    DECLARE_ACE_TYPE(TracingLeafPattern, Pattern);

public:
    explicit TracingLeafPattern(const std::string& nodeName)
        : nodeName_(nodeName)
    {}
    ~TracingLeafPattern() override = default;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<TracingBoxAlgorithm>(nodeName_);
    }

    bool IsAtomicNode() const override
    {
        return true;
    }

private:
    std::string nodeName_;
};

/**
 * Test class for verifying ignoreLayoutSafeArea scheduling flow.
 */
class IgnoreLayoutSafeAreaSchedulingTestNG : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PIPELINE_IGNORE_LAYOUT_SAFE_AREA_SCHEDULING_TEST_NG_H
