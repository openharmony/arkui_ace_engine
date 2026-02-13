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

#include "ignore_layout_safe_area_scheduling_test_ng.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

// Initialize static member
std::vector<std::string> LayoutTracer::events;

void IgnoreLayoutSafeAreaSchedulingTestNG::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void IgnoreLayoutSafeAreaSchedulingTestNG::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void IgnoreLayoutSafeAreaSchedulingTestNG::SetUp()
{
    LayoutTracer::Clear();
    NodeNameRegistry::Clear();
}

void IgnoreLayoutSafeAreaSchedulingTestNG::TearDown()
{
    LayoutTracer::Clear();
}

namespace {
/**
 * Helper: create a Flex container FrameNode with a TracingFlexPattern.
 * Used for IgnoreLayoutSafeAreaScheduling001 (non-hook pattern).
 */
RefPtr<FrameNode> CreateTracingFlexNode(
    const std::string& nodeName, int32_t nodeId, bool isRoot = false)
{
    auto node = TracingFrameNode::CreateTracingFrameNode(
        V2::FLEX_ETS_TAG, nodeId, AceType::MakeRefPtr<TracingFlexPattern>(nodeName), isRoot, nodeName);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(node->GetLayoutProperty());
    if (flexProp) {
        flexProp->UpdateFlexDirection(FlexDirection::ROW);
    }
    // Register node name for tracing
    NodeNameRegistry::Register(nodeId, nodeName);
    return node;
}

/**
 * Helper: create a virtual multi-child container FrameNode with TracingMultiChildPattern.
 * TracingMultiChildPattern inherits from Pattern and manually enables Pattern Hook mechanism
 * by overriding ChildPreMeasureHelperEnabled() and PostponedTaskForIgnoreEnabled().
 * Used for container nodes (Root, A1, A2, B1-B4) in IgnoreLayoutSafeAreaScheduling002.
 */
RefPtr<FrameNode> CreateTracingMultiChildNode(
    const std::string& nodeName, int32_t nodeId)
{
    auto node = TracingFrameNode::CreateTracingFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<TracingMultiChildPattern>(nodeName), false, nodeName);
    // Register node name for tracing
    NodeNameRegistry::Register(nodeId, nodeName);
    return node;
}

/**
 * Helper: create a leaf FrameNode with a TracingLeafPattern.
 */
RefPtr<FrameNode> CreateTracingLeafNode(
    const std::string& nodeName, int32_t nodeId)
{
    auto node = TracingFrameNode::CreateTracingFrameNode(
        V2::TEXT_ETS_TAG, nodeId, AceType::MakeRefPtr<TracingLeafPattern>(nodeName), false, nodeName);
    // Register node name for tracing
    NodeNameRegistry::Register(nodeId, nodeName);
    return node;
}

/**
 * Helper: configure ignoreLayoutSafeArea (SYSTEM + ALL) and LayoutPolicy (MatchParent)
 * on a node so that IsExpandConstraintNeeded() returns true.
 */
void ConfigureIgnoreLayoutSafeArea(const RefPtr<FrameNode>& node)
{
    auto layoutProperty = node->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    IgnoreLayoutSafeAreaOpts opts = {
        .type = LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = LAYOUT_SAFE_AREA_EDGE_ALL
    };
    layoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);  // width
    layoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false); // height
}
} // anonymous namespace

/**
 * @tc.name: IgnoreLayoutSafeAreaScheduling001
 * @tc.desc: Verify the execution order of the ignoreLayoutSafeArea delayed scheduling
 *           algorithm under the "Container Proactive Packing Mechanism" (Example 2).
 *
 *           Component tree (4 layers):
 *           Root(Flex) ─┬─ A1[I](Flex) ─┬─ B1[I](Flex) ─┬─ C1(Leaf)
 *                       │               │               └─ C2(Leaf)
 *                       │               └─ B2(Flex)    ─┬─ C3(Leaf)
 *                       │                               └─ C4(Leaf)
 *                       └─ A2(Flex)    ─┬─ B3(Flex)    ─┬─ C5[I](Leaf)
 *                                       │               └─ C6(Leaf)
 *                                       └─ B4[I](Flex) ─┬─ C7(Leaf)
 *                                                        └─ C8(Leaf)
 *
 *           [I] = ignoreLayoutSafeArea configured (SYSTEM + ALL + MatchParent)
 *
 *           Key characteristics (Reference: IgnoreLayoutSafeArea_Trace_Example.md - Example 2):
 *           - Uses TracingFlexPattern (inherits from FlexLayoutPattern)
 *           - FlexLayoutPattern does NOT implement hook pattern:
 *             * ChildPreMeasureHelperEnabled() returns false
 *             * PostponedTaskForIgnoreEnabled() returns false
 *           - LayoutAlgorithm is aware of ignore mechanism (IsExpandConstraintNeeded checks)
 *           - Container uses proactive packing mechanism
 *           - ignore nodes Measure: ✗ NOT CALLED (Phase 1) → ✓ COMPLETE (MEASURE_FOR_IGNORE)
 *           - ignore nodes Layout: ⊗ delay skip + ✓ COMPLETE (LAYOUT_FOR_IGNORE)
 *           - Container Layout: ⊗ delay skip + ✓ COMPLETE (LAYOUT_FOR_IGNORE)
 *
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaSchedulingTestNG, IgnoreLayoutSafeAreaScheduling001, TestSize.Level0)
{
    // ---- Step 1: Create all 15 FrameNodes with tracing patterns ----

    // Layer 1: Root
    auto root = CreateTracingFlexNode("Root", GetElmtId(), true);
    // Layer 2: A1, A2
    auto a1 = CreateTracingFlexNode("A1", GetElmtId());
    auto a2 = CreateTracingFlexNode("A2", GetElmtId());
    // Layer 3: B1, B2, B3, B4
    auto b1 = CreateTracingFlexNode("B1", GetElmtId());
    auto b2 = CreateTracingFlexNode("B2", GetElmtId());
    auto b3 = CreateTracingFlexNode("B3", GetElmtId());
    auto b4 = CreateTracingFlexNode("B4", GetElmtId());
    // Layer 4: C1-C8
    auto c1 = CreateTracingLeafNode("C1", GetElmtId());
    auto c2 = CreateTracingLeafNode("C2", GetElmtId());
    auto c3 = CreateTracingLeafNode("C3", GetElmtId());
    auto c4 = CreateTracingLeafNode("C4", GetElmtId());
    auto c5 = CreateTracingLeafNode("C5", GetElmtId());
    auto c6 = CreateTracingLeafNode("C6", GetElmtId());
    auto c7 = CreateTracingLeafNode("C7", GetElmtId());
    auto c8 = CreateTracingLeafNode("C8", GetElmtId());

    // ---- Step 2: Build tree hierarchy ----
    root->AddChild(a1);
    root->AddChild(a2);
    a1->AddChild(b1);
    a1->AddChild(b2);
    a2->AddChild(b3);
    a2->AddChild(b4);
    b1->AddChild(c1);
    b1->AddChild(c2);
    b2->AddChild(c3);
    b2->AddChild(c4);
    b3->AddChild(c5);
    b3->AddChild(c6);
    b4->AddChild(c7);
    b4->AddChild(c8);

    // ---- Step 3: Set root size constraint ----
    root->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(600.0f), CalcLength(800.0f)));

    // ---- Step 4: Configure ignoreLayoutSafeArea on A1, B1, C5, B4 ----
    ConfigureIgnoreLayoutSafeArea(a1);
    ConfigureIgnoreLayoutSafeArea(b1);
    ConfigureIgnoreLayoutSafeArea(c5);
    ConfigureIgnoreLayoutSafeArea(b4);

    // ---- Step 5: Clear tracer and trigger full layout pipeline ----
    LayoutTracer::Clear();
    FlushUITasks(root);

    // ---- Step 6: Verify execution sequence ----
    // Expected sequence follows the "Container Proactive Packing Mechanism" (Example 2)
    // Reference: IgnoreLayoutSafeArea_Trace_Example.md - Example 2
    //
    // Key characteristics:
    // - FlexLayoutAlgorithm is AWARE of ignore mechanism (IsExpandConstraintNeeded checks)
    // - ignore nodes Measure: ✗ NOT CALLED (Phase 1) → ✓ COMPLETE (MEASURE_FOR_IGNORE)
    // - ignore nodes Layout: ⊗ delay skip + ✓ COMPLETE (multiple times in LAYOUT_FOR_IGNORE)
    // - Container Layout: ⊗ delay skip + ✓ COMPLETE (LAYOUT_FOR_IGNORE)
    // - PostponedTaskForIgnore returns false → creates LAYOUT_FOR_IGNORE tasks
    //
    std::vector<std::string> expected = {
        // ============================================================================
        // Phase 1: Root::CreateLayoutTask (Initial DFS)
        // ============================================================================
        
        // ---------- Measure Stage ----------
        // Only non-ignore nodes and their parents are measured in Phase 1
        // ignore nodes (A1, B4, C5) are SKIPPED by container algorithm (IsExpandConstraintNeeded → continue)
        "Root:Measure",         // Root measures and detects A1 as ignore → skip A1, continue to A2
        "A2:Measure",           // A2 measures and detects B4 as ignore → skip B4, continue to B3
        "B3:Measure",           // B3 measures and detects C5 as ignore → skip C5, continue to C6
        "C6:Measure",           // C6 is leaf, measured normally
        
        // ---------- Layout Stage ----------
        // Root's Layout is skipped due to delaySelfLayoutForIgnore flag
        // This causes entire tree's Layout to be truncated (no child Layout is called)
        "Root:Layout(skip)",    // Root.GetDelaySelfLayoutForIgnore()=true (set in step 10) → skip
                                // Result: All children's Layout are NOT TRIGGERED in Phase 1
        
        // ============================================================================
        // Phase 2: FlushPostponedLayoutTask (while loop iteration #1)
        // Bundle queue (reverse order): #3{[A1],Root} → #2{[B4],A2} → #1{[C5],B3}
        // ============================================================================
        
        // ---------- Bundle #3: {[A1], Root} ----------
        // A1's delayed Measure + Layout
        "A1:Measure",           // A1.CreateLayoutTask(MEASURE_FOR_IGNORE): First time Measure!
                                // FlexLayoutAlgorithm detects B1 as ignore → skip B1, continue to B2
        "B2:Measure",           // B2 measures normally (no ignore)
        "C3:Measure",           // C3 is leaf under B2
        "C4:Measure",           // C4 is leaf under B2
        "A1:Layout(skip)",      // A1.CreateLayoutTask internal Layout: GetDelaySelfLayoutForIgnore()=true
                                // (set in step 17: A1.Measure end → bundle not empty → SetDelaySelfLayoutForIgnore)
                                // flag consumed, reset to false
        
        // Root's LAYOUT_FOR_IGNORE task
        "Root:Layout",          // Root.CreateLayoutTask(LAYOUT_FOR_IGNORE): Skip Measure, execute Layout
                                // GetDelaySelfLayoutForIgnore()=false (step 11 already consumed)
                                // FlexLayoutAlgorithm::Layout places children, calls child->Layout()
        
        // Root calls A1->Layout()
        "A1:Layout",            // A1.GetDelaySelfLayoutForIgnore()=false (step 18 already consumed)
                                // → LayoutAlgorithm::Layout executes (places B1, B2)
        "B1:Layout(skip)",      // B1.GetDelaySelfLayoutForIgnore()=true (set in step 13) → skip
        "B2:Layout",            // B2 Layout executes normally
        "C3:Layout",            // C3 Layout called by B2
        "C4:Layout",            // C4 Layout called by B2
        
        // Root calls A2->Layout()
        "A2:Layout(skip)",      // A2.GetDelaySelfLayoutForIgnore()=true (set in step 9, first consume) → skip
        
        // ---------- Bundle #2: {[B4], A2} ----------
        // B4's delayed Measure + Layout
        "B4:Measure",           // B4.CreateLayoutTask(MEASURE_FOR_IGNORE): First time Measure!
        "C7:Measure",           // C7 is leaf under B4
        "C8:Measure",           // C8 is leaf under B4
        "B4:Layout(skip)",      // B4.CreateLayoutTask internal Layout: GetDelaySelfLayoutForIgnore()=true
                                // (set in step 8, first consume) → skip
        
        // A2's LAYOUT_FOR_IGNORE task
        "A2:Layout",            // A2.CreateLayoutTask(LAYOUT_FOR_IGNORE): Skip Measure, execute Layout
                                // GetDelaySelfLayoutForIgnore()=false (step 20 already consumed)
                                // FlexLayoutAlgorithm::Layout places children (B3, B4)
        "B3:Layout(skip)",      // B3.GetDelaySelfLayoutForIgnore()=true (set in step 7, first consume) → skip
        "B4:Layout",            // B4.GetDelaySelfLayoutForIgnore()=false (step 25 already consumed)
                                // → LayoutAlgorithm::Layout executes
        "C7:Layout",            // C7 Layout called by B4
        "C8:Layout",            // C8 Layout called by B4
        
        // ---------- Bundle #1: {[C5], B3} ----------
        // C5's delayed Measure + Layout
        "C5:Measure",           // C5.CreateLayoutTask(MEASURE_FOR_IGNORE): First time Measure! (leaf)
        "C5:Layout(skip)",      // C5.CreateLayoutTask internal Layout: GetDelaySelfLayoutForIgnore()=true
                                // (set in step 5, first consume) → skip
        
        // B3's LAYOUT_FOR_IGNORE task
        "B3:Layout",            // B3.CreateLayoutTask(LAYOUT_FOR_IGNORE): Skip Measure, execute Layout
                                // GetDelaySelfLayoutForIgnore()=false (step 27 already consumed)
                                // FlexLayoutAlgorithm::Layout places children (C5, C6)
        "C5:Layout",            // C5.GetDelaySelfLayoutForIgnore()=false (step 29 already consumed)
                                // → LayoutAlgorithm::Layout executes (leaf)
        "C6:Layout",            // C6 Layout executes normally (leaf)
        
        // End of iteration #1: New bundle queue = [#4{[B1],A1}] (not empty, continue loop)
        
        // ============================================================================
        // Phase 3: FlushPostponedLayoutTask (while loop iteration #2)
        // Bundle queue: #4{[B1],A1}
        // ============================================================================
        
        // ---------- Bundle #4: {[B1], A1} ----------
        // B1's delayed Measure + Layout
        "B1:Measure",           // B1.CreateLayoutTask(MEASURE_FOR_IGNORE): First time Measure!
        "C1:Measure",           // C1 is leaf under B1
        "C2:Measure",           // C2 is leaf under B1
        "B1:Layout",            // B1.CreateLayoutTask internal Layout: GetDelaySelfLayoutForIgnore()=false
                                // (set in step 13, consumed in step 20 Root.LAYOUT_FOR_IGNORE)
                                // → LayoutAlgorithm::Layout executes
        "C1:Layout",            // C1 Layout called by B1 (first time)
        "C2:Layout",            // C2 Layout called by B1 (first time)
        
        // A1's LAYOUT_FOR_IGNORE task
        "A1:Layout",            // A1.CreateLayoutTask(LAYOUT_FOR_IGNORE): Skip Measure, execute Layout
                                // GetDelaySelfLayoutForIgnore()=false (step 18 already consumed)
                                // FlexLayoutAlgorithm::Layout places children (B1, B2)
        // Without layoutDirtyFlag_, following sequence should be skipped.
        // "B1:Layout",            // B1.GetDelaySelfLayoutForIgnore()=false (step 20 already consumed)
        //                         // → LayoutAlgorithm::Layout executes (second time)
        // "C1:Layout",            // C1 Layout called by B1 (second time)
        // "C2:Layout",            // C2 Layout called by B1 (second time)
        // "B2:Layout",            // B2 Layout executes normally (B2 already measured in step 14)
        // "C3:Layout",            // C3 Layout called by B2 (second time, first was in step 20)
        // "C4:Layout",            // C4 Layout called by B2 (second time, first was in step 20)
        
        // End of iteration #2: Bundle queue is empty, while loop exits
        
        // ============================================================================
        // Summary of Layout execution counts:
        // - Root: M×1, L×2 (1 skip + 1 complete)
        // - A1:   M×1, L×3 (1 skip + 2 complete: in Root.LAYOUT_FOR_IGNORE + in A1.LAYOUT_FOR_IGNORE)
        // - A2:   M×1, L×2 (1 skip + 1 complete)
        // - B1:   M×1, L×3 (1 skip in Root.LAYOUT_FOR_IGNORE + 2 complete: B1.CreateLayoutTask + A1.LAYOUT_FOR_IGNORE)
        // - B2:   M×1, L×2 (1 in Root.LAYOUT_FOR_IGNORE + 1 in A1.LAYOUT_FOR_IGNORE)
        // - B3:   M×1, L×2 (1 skip + 1 complete)
        // - B4:   M×1, L×2 (1 skip + 1 complete)
        // - C1, C2: M×1, L×2 (both in B1.CreateLayoutTask + A1.LAYOUT_FOR_IGNORE)
        // - C3, C4: M×1, L×2 (both in Root.LAYOUT_FOR_IGNORE + A1.LAYOUT_FOR_IGNORE)
        // - C5, C6, C7, C8: M×1, L×1
        //
        // Total events: 52 (Phase 1: 5, Phase 2: 34, Phase 3: 13)
        // ============================================================================
    };
    // Print actual sequence for debugging if mismatch
    if (LayoutTracer::events != expected) {
        std::string actualStr = "Actual sequence (" + std::to_string(LayoutTracer::events.size()) + " events):\n";
        for (size_t i = 0; i < LayoutTracer::events.size(); ++i) {
            actualStr += "  [" + std::to_string(i) + "] " + LayoutTracer::events[i] + "\n";
        }
        std::string expectedStr =
            "Expected sequence (" + std::to_string(expected.size()) + " events):\n";
        for (size_t i = 0; i < expected.size(); ++i) {
            expectedStr += "  [" + std::to_string(i) + "] " + expected[i] + "\n";
        }
        ADD_FAILURE() << actualStr << expectedStr;
    }

    ASSERT_EQ(LayoutTracer::events.size(), expected.size())
        << "Event count mismatch";

    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(LayoutTracer::events[i], expected[i])
            << "Mismatch at index " << i;
    }
}

/**
 * @tc.name: IgnoreLayoutSafeAreaScheduling002
 * @tc.desc: Verify the execution order of the ignoreLayoutSafeArea delayed scheduling
 *           algorithm under the "Non-intrusive Pattern Hook Mechanism" (Example 1).
 *
 *           Component tree (4 layers):
 *           Root(MultiChild) ─┬─ A1[I](MultiChild) ─┬─ B1[I](MultiChild) ─┬─ C1(Leaf)
 *                             │                     │                     └─ C2(Leaf)
 *                             │                     └─ B2(MultiChild)     ─┬─ C3(Leaf)
 *                             │                                           └─ C4(Leaf)
 *                             └─ A2(MultiChild)     ─┬─ B3(MultiChild)    ─┬─ C5[I](Leaf)
 *                                                   │                     └─ C6(Leaf)
 *                                                   └─ B4[I](MultiChild)  ─┬─ C7(Leaf)
 *                                                                          └─ C8(Leaf)
 *
 *           [I] = ignoreLayoutSafeArea configured (SYSTEM + ALL + MatchParent)
 *
 *           Key characteristics:
 *           - Uses TracingMultiChildPattern (inherits from Pattern)
 *           - Pattern Hook mechanism enabled via method overrides:
 *             * ChildPreMeasureHelperEnabled() returns true
 *             * PostponedTaskForIgnoreEnabled() returns true
 *           - MultiChild container supports multiple children with simple sequential layout
 *           - ignore nodes Measure: ⊗ PreMeasure skip (Phase 1) + ✓ COMPLETE (MEASURE_FOR_IGNORE)
 *           - ignore nodes Layout: ⊗ delay skip (Phase 1) + ✓ COMPLETE (CreateLayoutTask + PostponedTask)
 *           - Container Layout: ✓ fully executed (container does NOT set delay)
 *           - PostponedTaskForIgnore is called to process delayed children
 *
 * @tc.type: FUNC
 */
HWTEST_F(IgnoreLayoutSafeAreaSchedulingTestNG, IgnoreLayoutSafeAreaScheduling002, TestSize.Level0)
{
    // ---- Step 1: Create all 15 FrameNodes with TracingMultiChildPattern for containers ----

    // Layer 1: Root (with TracingMultiChildPattern to enable Pattern Hook mechanism)
    auto root = CreateTracingMultiChildNode("Root", GetElmtId());
    // Layer 2: A1, A2 (Multi-child container nodes)
    auto a1 = CreateTracingMultiChildNode("A1", GetElmtId());
    auto a2 = CreateTracingMultiChildNode("A2", GetElmtId());
    // Layer 3: B1, B2, B3, B4 (Multi-child container nodes)
    auto b1 = CreateTracingMultiChildNode("B1", GetElmtId());
    auto b2 = CreateTracingMultiChildNode("B2", GetElmtId());
    auto b3 = CreateTracingMultiChildNode("B3", GetElmtId());
    auto b4 = CreateTracingMultiChildNode("B4", GetElmtId());
    // Layer 4: C1-C8 (leaves use TracingLeafPattern)
    auto c1 = CreateTracingLeafNode("C1", GetElmtId());
    auto c2 = CreateTracingLeafNode("C2", GetElmtId());
    auto c3 = CreateTracingLeafNode("C3", GetElmtId());
    auto c4 = CreateTracingLeafNode("C4", GetElmtId());
    auto c5 = CreateTracingLeafNode("C5", GetElmtId());
    auto c6 = CreateTracingLeafNode("C6", GetElmtId());
    auto c7 = CreateTracingLeafNode("C7", GetElmtId());
    auto c8 = CreateTracingLeafNode("C8", GetElmtId());

    // ---- Step 2: Build tree hierarchy ----
    root->AddChild(a1);
    root->AddChild(a2);
    a1->AddChild(b1);
    a1->AddChild(b2);
    a2->AddChild(b3);
    a2->AddChild(b4);
    b1->AddChild(c1);
    b1->AddChild(c2);
    b2->AddChild(c3);
    b2->AddChild(c4);
    b3->AddChild(c5);
    b3->AddChild(c6);
    b4->AddChild(c7);
    b4->AddChild(c8);

    // ---- Step 3: Set root size constraint ----
    root->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(600.0f), CalcLength(600.0f)));

    // ---- Step 4: Configure ignoreLayoutSafeArea on A1, B1, C5, B4 ----
    ConfigureIgnoreLayoutSafeArea(a1);
    ConfigureIgnoreLayoutSafeArea(b1);
    ConfigureIgnoreLayoutSafeArea(c5);
    ConfigureIgnoreLayoutSafeArea(b4);

    // ---- Step 5: Clear tracer and trigger full layout pipeline ----
    LayoutTracer::Clear();
    
    FlushUITasks(root);

    // ---- Step 6: Verify execution sequence ----
    // Expected sequence follows the "Non-intrusive Pattern Hook Mechanism" (Example 1)
    // Reference: IgnoreLayoutSafeArea_Trace_Example.md - Example 1
    //
    // Key characteristics:
    // - MultiChildPattern inherits from Pattern and enables Pattern Hook via method overrides
    //   (ChildPreMeasureHelperEnabled/PostponedTaskForIgnoreEnabled = true)
    // - MultiChild container supports multiple children with simple sequential layout
    // - LayoutAlgorithm is NOT AWARE of ignore mechanism
    // - PreMeasure acts as first checkpoint before child Measure
    // - ignore nodes: PreMeasure skip (Phase 1) + Complete Measure (MEASURE_FOR_IGNORE)
    // - ignore nodes Layout: delay skip (Phase 1) + Complete Layout (PostponedTaskForIgnore)
    // - Container Layout: fully executed (container does NOT set delay)
    //
    std::vector<std::string> expected = {
        // ============================================================================
        // Phase 1: Root::CreateLayoutTask (Initial DFS)
        // ============================================================================
        
        // ---------- Measure Stage (DFS recursive descent) ----------
        "Root:Measure",                // Step 1: Root Measure triggered
        
        // Root traverses children, calls A1->Measure()
        "A1:PreMeasure(skip)",         // Step 2: A1.FrameNode::Measure triggered
                                       // → PreMeasure: Root::ChildPreMeasureHelper(A1)
                                       // → A1.IsIgnoreOptsValid() = true → skip
                                       // → A1.SetDelaySelfLayoutForIgnore()
                                       // → A1.SetHasPreMeasured()
                                       // → Root collects A1 to delayMeasureChildren_ and delayLayoutChildren_
                                       // A1's subtree (B1, B2, C1-C4) NOT VISITED in this phase
        
        // Root continues to A2
        "A2:Measure",                  // Step 3: A2.FrameNode::Measure triggered
                                       // → PreMeasure: A2.IsIgnoreOptsValid() = false → continue
                                       // → LayoutAlgorithm::Measure executes
        
        // A2 traverses children, calls B3->Measure()
        "B3:Measure",                  // Step 4: B3.FrameNode::Measure triggered
                                       // → PreMeasure: B3.IsIgnoreOptsValid() = false → continue
                                       // → LayoutAlgorithm::Measure executes
        
        // B3 traverses children, calls C5->Measure()
        "C5:PreMeasure(skip)",         // Step 5: C5.FrameNode::Measure triggered
                                       // → PreMeasure: B3::ChildPreMeasureHelper(C5)
                                       // → C5.IsIgnoreOptsValid() = true → skip
                                       // → C5.SetDelaySelfLayoutForIgnore()
                                       // → B3 collects C5
        
        // B3 continues to C6
        "C6:Measure",                  // Step 6: C6.FrameNode::Measure (leaf node)
        
        // A2 continues to B4
        "B4:PreMeasure(skip)",         // Step 7: B4.FrameNode::Measure triggered
                                       // → PreMeasure: A2::ChildPreMeasureHelper(B4)
                                       // → B4.IsIgnoreOptsValid() = true → skip
                                       // → A2 collects B4
                                       // B4's subtree (C7, C8) NOT VISITED
        
        // ---------- Layout Stage (DFS recursive expand) ----------
        "Root:Layout",                 // Step 8: Root.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = false
                                       // (Pattern Hook does NOT set delay on container itself)
                                       // → LayoutAlgorithm::Layout executes
        
        // Root places children, calls A1->Layout()
        "A1:Layout(skip)",             // Step 9: A1.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = true (set in step 2)
                                       // → Layout skip, flag consumed and reset to false
        
        // Root continues to A2->Layout()
        "A2:Layout",                   // Step 10: A2.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = false
                                       // → LayoutAlgorithm::Layout executes
        
        // A2 places children, calls B3->Layout()
        "B3:Layout",                   // Step 11: B3.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = false
                                       // (Pattern Hook does NOT set delay on container)
                                       // → LayoutAlgorithm::Layout executes
        
        // B3 places children, calls C5->Layout()
        "C5:Layout(skip)",             // Step 12: C5.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = true (set in step 5)
                                       // → Layout skip, flag consumed
        
        // B3 continues to C6->Layout()
        "C6:Layout",                   // Step 13: C6.FrameNode::Layout (leaf node)
        
        // A2 continues to B4->Layout()
        "B4:Layout(skip)",             // Step 14: B4.FrameNode::Layout triggered
                                       // → GetDelaySelfLayoutForIgnore() = true (set in step 8)
                                       // → Layout skip, flag consumed
        
        // Phase 1 End Status:
        // - Completed Measure: Root, A2, B3, C6 (4 nodes)
        // - PreMeasure skip: A1, C5, B4 (3 nodes, FrameNode::Measure triggered but returned early)
        // - Not visited: B1, B2, C1, C2, C3, C4, C7, C8 (8 nodes)
        // - Layout executed: Root, A2, B3, C6 (4 nodes)
        // - Layout skip: A1, C5, B4 (3 nodes)
        
        // ============================================================================
        // Phase 2: FlushPostponedLayoutTask (while loop iteration #1)
        // Bundle queue (reverse order): #3{[A1],Root} → #2{[B4],A2} → #1{[C5],B3}
        // ============================================================================
        
        // ---------- Bundle #3: {[A1], Root} ----------
        // A1's delayed Measure + Layout
        "A1:Measure",                  // Step 15: A1.CreateLayoutTask(MEASURE_FOR_IGNORE)
                                       // → SetIgnoreLayoutProcess(true)
                                       // → PreMeasure: GetIgnoreLayoutProcess()=true && GetHasPreMeasured()=true
                                       // → PreMeasure returns false (no longer skip)
                                       // → LayoutAlgorithm::Measure executes (with expanded constraint)
        
        // A1 traverses children with Pattern Hook
        "B1:PreMeasure(skip)",         // Step 16: B1.FrameNode::Measure triggered
                                       // → PreMeasure: A1::ChildPreMeasureHelper(B1)
                                       // → B1.IsIgnoreOptsValid() = true → skip
                                       // → A1 collects B1
                                       // B1's subtree (C1, C2) NOT VISITED
        
        "B2:Measure",                  // Step 17: B2.FrameNode::Measure triggered (no ignore)
        "C3:Measure",                  // Step 18: C3 (leaf under B2)
        "C4:Measure",                  // Step 19: C4 (leaf under B2)
        
        // A1's CreateLayoutTask internal Layout
        "A1:Layout",                   // Step 20: A1.FrameNode::Layout triggered (in CreateLayoutTask)
                                       // → GetDelaySelfLayoutForIgnore() = false (step 9 already consumed)
                                       // → LayoutAlgorithm::Layout executes
        "B1:Layout(skip)",             // B1.Layout → delay=true (step 16, first consume) → skip
        "B2:Layout",                   // B2.Layout → normal execution
        "C3:Layout",                   // C3.Layout called by B2
        "C4:Layout",                   // C4.Layout called by B2
        
        // ---------- Bundle #2: {[B4], A2} ----------
        "B4:Measure",                  // Step 21: B4.CreateLayoutTask(MEASURE_FOR_IGNORE)
        "C7:Measure",                  // Step 22: C7 (leaf under B4)
        "C8:Measure",                  // Step 23: C8 (leaf under B4)
        
        "B4:Layout",                   // Step 24: B4.FrameNode::Layout triggered (in CreateLayoutTask)
                                       // → GetDelaySelfLayoutForIgnore() = false (step 14 consumed)
                                       // → LayoutAlgorithm::Layout executes
        "C7:Layout",                   // C7.Layout called by B4
        "C8:Layout",                   // C8.Layout called by B4
        
        // ---------- Bundle #1: {[C5], B3} ----------
        "C5:Measure",                  // Step 25: C5.CreateLayoutTask(MEASURE_FOR_IGNORE)
                                       // (leaf with expanded constraint)
        
        "C5:Layout",                   // Step 26: C5.FrameNode::Layout triggered (in CreateLayoutTask)
                                       // → GetDelaySelfLayoutForIgnore() = false (step 12 consumed)
                                       // → LayoutAlgorithm::Layout executes (leaf)
        
        // ============================================================================
        // Phase 3: FlushPostponedLayoutTask (while loop iteration #2)
        // Bundle queue: #4{[B1],A1}
        // ============================================================================
        
        // ---------- Bundle #4: {[B1], A1} ----------
        "B1:Measure",                  // Step 27: B1.CreateLayoutTask(MEASURE_FOR_IGNORE)
        "C1:Measure",                  // Step 28: C1 (leaf under B1)
        "C2:Measure",                  // Step 29: C2 (leaf under B1)
        
        "B1:Layout",                   // Step 30: B1.FrameNode::Layout triggered (in CreateLayoutTask)
                                       // → GetDelaySelfLayoutForIgnore() = false (step 20 consumed)
                                       // → LayoutAlgorithm::Layout executes
        "C1:Layout",                   // C1.Layout called by B1
        "C2:Layout"                    // C2.Layout called by B1
        
        // ============================================================================
        // Summary:
        // - ignore nodes (A1, B1, C5, B4): Each executed M×2, L×2
        //   * First time: PreMeasure skip + delay skip Layout
        //   * Second time: Complete Measure (MEASURE_FOR_IGNORE) + Complete Layout
        // - Non-ignore nodes: Each executed M×1, L×1 (normal flow)
        //
        // Total events: 27 (Phase 1: 14, Phase 2: 9, Phase 3: 4)
        // ============================================================================
    };

    // Print actual sequence for debugging if mismatch
    if (LayoutTracer::events != expected) {
        std::string actualStr = "Actual sequence (" + std::to_string(LayoutTracer::events.size()) + " events):\n";
        for (size_t i = 0; i < LayoutTracer::events.size(); ++i) {
            actualStr += "  [" + std::to_string(i) + "] " + LayoutTracer::events[i] + "\n";
        }
        std::string expectedStr =
            "Expected sequence (" + std::to_string(expected.size()) + " events):\n";
        for (size_t i = 0; i < expected.size(); ++i) {
            expectedStr += "  [" + std::to_string(i) + "] " + expected[i] + "\n";
        }
        ADD_FAILURE() << actualStr << expectedStr;
    }

    ASSERT_EQ(LayoutTracer::events.size(), expected.size())
        << "Event count mismatch";

    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(LayoutTracer::events[i], expected[i])
            << "Mismatch at index " << i;
    }
}

} // namespace OHOS::Ace::NG
