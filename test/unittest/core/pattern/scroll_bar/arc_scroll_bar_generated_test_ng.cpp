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

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_layout_algorithm.h"
#include "core/components_ng/pattern/arc_scroll_bar/arc_scroll_bar_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_layout_property.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class ArcScrollBarPatternTestNg : public TestNG {
public:
    void SetUp() override
    {
        TestNG::SetUp();
    }

    void TearDown() override
    {
        TestNG::TearDown();
    }

protected:
    RefPtr<FrameNode> CreateArcScrollBarFrameNode()
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode = FrameNode::GetOrCreateFrameNode(
            V2::ARC_SCROLL_BAR_ETS_TAG,
            nodeId,
            []() { return AceType::MakeRefPtr<ArcScrollBarPattern>(); });
        return frameNode;
    }
};

// ============================================================================
// ArcScrollBarPattern Tests
// ============================================================================

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test ArcScrollBarPattern basic attachment to frameNode
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar frameNode
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Get pattern from frameNode
     * @tc.expected: pattern is not null and attached
     */
    auto pattern = frameNode->GetPattern<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->GetHost());
    EXPECT_EQ(pattern->GetHost()->GetTag(), V2::ARC_SCROLL_BAR_ETS_TAG);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone with valid host and event hub
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, OnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar frameNode
     * @tc.expected: frameNode created successfully
     */
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnModifyDone
     * @tc.expected: gesture hub is created and hit test mode is set
     */
    pattern->OnModifyDone();

    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = eventHub->GetGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->GetHitTestMode(), HitTestMode::HTMTRANSPARENT);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone when host is null
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, OnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without attaching to frameNode
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call OnModifyDone with null host
     * @tc.expected: should return early without crash
     */
    pattern->OnModifyDone();
    EXPECT_FALSE(pattern->GetHost());
}

/**
 * @tc.name: CreateLayoutAlgorithm001
 * @tc.desc: Test CreateLayoutAlgorithm returns ArcScrollBarLayoutAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar pattern
     * @tc.expected: pattern created successfully
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateLayoutAlgorithm
     * @tc.expected: returns ArcScrollBarLayoutAlgorithm instance
     */
    auto layoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    auto arcScrollBarLayoutAlgorithm = AceType::DynamicCast<ArcScrollBarLayoutAlgorithm>(layoutAlgorithm);
    ASSERT_NE(arcScrollBarLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: Test CreateNodePaintMethod with valid scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar pattern with scrollBar
     * @tc.expected: pattern created successfully
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create and set ArcScrollBar
     * @tc.expected: scrollBar is set
     */
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    pattern->scrollBar_ = scrollBar;

    /**
     * @tc.steps: step3. Call CreateNodePaintMethod
     * @tc.expected: paint method is created with overlay modifier
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    auto arcScrollBarPaintMethod = AceType::DynamicCast<ArcScrollBarPaintMethod>(paintMethod);
    ASSERT_NE(arcScrollBarPaintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: Test CreateNodePaintMethod when scrollBar is null
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern without scrollBar
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->scrollBar_ = nullptr;

    /**
     * @tc.steps: step2. Call CreateNodePaintMethod
     * @tc.expected: paint method is created without overlay modifier
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod003
 * @tc.desc: Test CreateNodePaintMethod when scrollBar doesn't need paint
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateNodePaintMethod003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with scrollBar
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    pattern->scrollBar_ = scrollBar;

    /**
     * @tc.steps: step2. Call CreateNodePaintMethod
     * @tc.expected: paint method is created
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod004
 * @tc.desc: Test CreateNodePaintMethod when overlay modifier already exists
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateNodePaintMethod004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern with existing overlay modifier
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    pattern->scrollBar_ = scrollBar;

    auto existingOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    pattern->scrollBarOverlayModifier_ = existingOverlayModifier;

    /**
     * @tc.steps: step2. Call CreateNodePaintMethod
     * @tc.expected: existing overlay modifier is reused
     */
    auto paintMethod = pattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    EXPECT_EQ(pattern->GetScrollBarOverlayModifier(), existingOverlayModifier);
}

/**
 * @tc.name: UseInnerScrollBar001
 * @tc.desc: Test UseInnerScrollBar returns true
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UseInnerScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar pattern
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call UseInnerScrollBar
     * @tc.expected: returns true
     */
    EXPECT_TRUE(pattern->UseInnerScrollBar());
}

/**
 * @tc.name: CreateScrollBar001
 * @tc.desc: Test CreateScrollBar returns ArcScrollBar instance
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CreateScrollBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar pattern
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call CreateScrollBar
     * @tc.expected: returns ArcScrollBar instance
     */
    auto scrollBar = pattern->CreateScrollBar();
    ASSERT_NE(scrollBar, nullptr);
    auto arcScrollBar = AceType::DynamicCast<ArcScrollBar>(scrollBar);
    ASSERT_NE(arcScrollBar, nullptr);
}

/**
 * @tc.name: SetBarCollectClickAndLongPressTargetCallback001
 * @tc.desc: Test SetBarCollectClickAndLongPressTargetCallback is empty override
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, SetBarCollectClickAndLongPressTargetCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar pattern
     * @tc.expected: pattern created
     */
    auto pattern = AceType::MakeRefPtr<ArcScrollBarPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Call SetBarCollectClickAndLongPressTargetCallback
     * @tc.expected: should complete without crash (empty override)
     */
    pattern->SetBarCollectClickAndLongPressTargetCallback();
}

// ============================================================================
// ArcScrollBarLayoutAlgorithm Tests
// ============================================================================

/**
 * @tc.name: Measure001
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Measure with valid layoutWrapper
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Measure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar frameNode
     * @tc.expected: frameNode created
     */
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Create layoutWrapper with constraints
     * @tc.expected: layoutWrapper created
     */
    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(200.0f, 200.0f));
    layoutConstraint.percentReference.SetSizeT(SizeF(300.0f, 300.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step3. Call Measure
     * @tc.expected: geometryNode has size constrained to maxSize
     */
    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // When no parentIdealSize, idealSize uses maxSize, then constrained to [minSize, maxSize]
    EXPECT_EQ(frameSize.Width(), 200.0f);
    EXPECT_EQ(frameSize.Height(), 200.0f);
}

/**
 * @tc.name: Measure002
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Measure with zero constraints
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Measure002, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set zero size constraint
     * @tc.expected: constraint is applied
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(0.0f, 0.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 0.0f);
    EXPECT_EQ(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: Measure003
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Measure with min/max size constraints
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Measure003, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set min and max size constraints
     * @tc.expected: constraints are applied
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize.SetSizeT(SizeF(50.0f, 50.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(150.0f, 150.0f));
    layoutConstraint.percentReference.SetSizeT(SizeF(300.0f, 300.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // When no parentIdealSize, idealSize uses maxSize (150), constrained to [min, max]
    EXPECT_EQ(frameSize.Width(), 150.0f);
    EXPECT_EQ(frameSize.Height(), 150.0f);
}

/**
 * @tc.name: Measure004
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Measure with padding
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Measure004, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set padding
     * @tc.expected: padding is applied
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(200.0f, 200.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    PaddingProperty padding;
    padding.left = CalcLength(10.0f);
    padding.right = CalcLength(10.0f);
    padding.top = CalcLength(5.0f);
    padding.bottom = CalcLength(5.0f);
    layoutProperty->UpdatePadding(padding);

    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Size calculation includes padding, but final result is constrained to [minSize, maxSize]
    // maxSize is 200.0f, so even with padding the result is constrained to 200
    EXPECT_EQ(frameSize.Width(), 200.0f);
    EXPECT_EQ(frameSize.Height(), 200.0f);
}

/**
 * @tc.name: Measure005
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Measure with parent size
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Measure005, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set parent ideal size
     * @tc.expected: parent size is used when ideal size is not set
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize.SetSize(SizeF(100.0f, 100.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(200.0f, 200.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // When parentIdealSize is set, it should be used (constrained to maxSize)
    EXPECT_EQ(frameSize.Width(), 100.0f);
    EXPECT_EQ(frameSize.Height(), 100.0f);
}

/**
 * @tc.name: Layout001
 * @tc.desc: Test ArcScrollBarLayoutAlgorithm Layout (empty implementation)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, Layout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar frameNode
     * @tc.expected: frameNode created
     */
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Call Layout
     * @tc.expected: should complete without crash (empty implementation)
     */
    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
}

// ============================================================================
// ArcScrollBarPaintMethod Tests
// ============================================================================

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test UpdateOverlayModifier with valid paintWrapper and scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBarPaintMethod
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    /**
     * @tc.steps: step2. Create and set scrollBar with properties
     * @tc.expected: scrollBar is configured
     */
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->positionModeUpdate_ = true;
    scrollBar->SetArcBackgroundColor(Color::RED);
    scrollBar->SetArcForegroundColor(Color::BLUE);
    scrollBar->SetHoverAnimationType(HoverAnimationType::GROW);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::APPEAR);
    scrollBar->needAdaptAnimation_ = true;
    paintMethod->SetScrollBar(scrollBar);

    /**
     * @tc.steps: step3. Create overlay modifier
     * @tc.expected: modifier created
     */
    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    /**
     * @tc.steps: step4. Create mock PaintWrapper
     * @tc.expected: paintWrapper created
     */
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step5. Call UpdateOverlayModifier
     * @tc.expected: overlay modifier is updated
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

/**
 * @tc.name: UpdateOverlayModifier002
 * @tc.desc: Test UpdateOverlayModifier when paintWrapper is null
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBarPaintMethod
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    paintMethod->SetScrollBar(scrollBar);

    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier with null paintWrapper
     * @tc.expected: should return early without crash
     */
    paintMethod->UpdateOverlayModifier(nullptr);
}

/**
 * @tc.name: UpdateOverlayModifier003
 * @tc.desc: Test UpdateOverlayModifier when scrollBarOverlayModifier is null
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBarPaintMethod without overlay modifier
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    paintMethod->SetScrollBar(scrollBar);
    // Not setting overlay modifier

    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier
     * @tc.expected: should return early without crash
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

/**
 * @tc.name: UpdateOverlayModifier004
 * @tc.desc: Test UpdateOverlayModifier when scrollBar is null
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBarPaintMethod without scrollBar
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);
    // Not setting scrollBar

    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier
     * @tc.expected: should return early without crash
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

/**
 * @tc.name: UpdateOverlayModifier005
 * @tc.desc: Test UpdateOverlayModifier when positionModeUpdate is false
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBarPaintMethod with positionModeUpdate=false
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->positionModeUpdate_ = false; // Don't update position mode
    scrollBar->SetArcBackgroundColor(Color::GREEN);
    scrollBar->SetArcForegroundColor(Color(0xFFFF00));
    paintMethod->SetScrollBar(scrollBar);

    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier
     * @tc.expected: position mode should not be updated
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

/**
 * @tc.name: UpdateOverlayModifier006
 * @tc.desc: Test UpdateOverlayModifier with different animation types
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, UpdateOverlayModifier006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create paint method with various animation types
     * @tc.expected: paintMethod created
     */
    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    ASSERT_NE(paintMethod, nullptr);

    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetHoverAnimationType(HoverAnimationType::NONE);
    scrollBar->SetOpacityAnimationType(OpacityAnimationType::NONE);
    scrollBar->SetArcBackgroundColor(Color(0x00FFFF));
    scrollBar->SetArcForegroundColor(Color(0xFF00FF));
    paintMethod->SetScrollBar(scrollBar);

    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier
     * @tc.expected: animation types are set to NONE after update
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(scrollBar->GetHoverAnimationType(), HoverAnimationType::NONE);
    EXPECT_EQ(scrollBar->GetOpacityAnimationType(), OpacityAnimationType::NONE);
}

// ============================================================================
// Boundary Value Tests
// ============================================================================

/**
 * @tc.name: BoundaryValueMeasure001
 * @tc.desc: Test Measure with very small constraint (0.1f)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueMeasure001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set very small size constraint
     * @tc.expected: should use maxSize (0.1f)
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(0.1f, 0.1f));
    layoutConstraint.minSize.SetSizeT(SizeF(0.0f, 0.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 0.1f);
    EXPECT_EQ(frameSize.Height(), 0.1f);
}

/**
 * @tc.name: BoundaryValueMeasure002
 * @tc.desc: Test Measure with very large constraint (10000.0f)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueMeasure002, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set very large size constraint
     * @tc.expected: should use maxSize (10000.0f)
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(10000.0f, 10000.0f));
    layoutConstraint.percentReference.SetSizeT(SizeF(10000.0f, 10000.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 10000.0f);
    EXPECT_EQ(frameSize.Height(), 10000.0f);
}

/**
 * @tc.name: BoundaryValueMeasure003
 * @tc.desc: Test Measure with negative minSize (should be clamped to 0)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueMeasure003, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set negative minSize
     * @tc.expected: should be clamped to non-negative (use maxSize 200.0f)
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize.SetSizeT(SizeF(-100.0f, -100.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(200.0f, 200.0f));
    layoutConstraint.percentReference.SetSizeT(SizeF(300.0f, 300.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Negative minSize should be treated as 0, result constrained to [0, 200] = 200.0f
    EXPECT_EQ(frameSize.Width(), 200.0f);
    EXPECT_EQ(frameSize.Height(), 200.0f);
}

/**
 * @tc.name: BoundaryValueMeasure004
 * @tc.desc: Test Measure with minSize > maxSize (minSize should win)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueMeasure004, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set minSize greater than maxSize
     * @tc.expected: should be constrained to maxSize
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.minSize.SetSizeT(SizeF(300.0f, 300.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(100.0f, 100.0f));
    layoutConstraint.percentReference.SetSizeT(SizeF(200.0f, 200.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // When min > max, Constrain should still use maxSize
    EXPECT_EQ(frameSize.Width(), 100.0f);
    EXPECT_EQ(frameSize.Height(), 100.0f);
}

/**
 * @tc.name: BoundaryValueMeasure005
 * @tc.desc: Test Measure with float max value
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueMeasure005, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set constraint to max float value
     * @tc.expected: should handle without overflow
     */
    LayoutConstraintF layoutConstraint;
    float maxFloat = std::numeric_limits<float>::max();
    layoutConstraint.maxSize.SetSizeT(SizeF(maxFloat, maxFloat));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Should use maxFloat as the size
    EXPECT_EQ(frameSize.Width(), maxFloat);
    EXPECT_EQ(frameSize.Height(), maxFloat);
}

/**
 * @tc.name: BoundaryValuePadding001
 * @tc.desc: Test Measure with large padding values
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValuePadding001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(100.0f, 100.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    /**
     * @tc.steps: step2. Set padding larger than constraint
     * @tc.expected: should handle gracefully (size constrained to maxSize)
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0f);  // Larger than max width
    padding.right = CalcLength(200.0f);
    padding.top = CalcLength(200.0f);   // Larger than max height
    padding.bottom = CalcLength(200.0f);
    layoutProperty->UpdatePadding(padding);

    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Even with large padding, final size is constrained to maxSize
    EXPECT_EQ(frameSize.Width(), 100.0f);
    EXPECT_EQ(frameSize.Height(), 100.0f);
}

/**
 * @tc.name: BoundaryValuePadding002
 * @tc.desc: Test Measure with negative padding values
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValuePadding002, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(200.0f, 200.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);

    /**
     * @tc.steps: step2. Set negative padding
     * @tc.expected: negative padding increases effective size, but constrained to maxSize
     */
    PaddingProperty padding;
    padding.left = CalcLength(-10.0f);
    padding.right = CalcLength(-10.0f);
    padding.top = CalcLength(-20.0f);
    padding.bottom = CalcLength(-20.0f);
    layoutProperty->UpdatePadding(padding);

    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // With negative padding, effective size increases but is constrained to maxSize
    EXPECT_EQ(frameSize.Width(), 200.0f);
    EXPECT_EQ(frameSize.Height(), 200.0f);
}

/**
 * @tc.name: BoundaryValueParentSize001
 * @tc.desc: Test Measure with zero parent size
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueParentSize001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize.SetSize(SizeF(0.0f, 0.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(100.0f, 100.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // When parentIdealSize is 0, it should be used
    EXPECT_EQ(frameSize.Width(), 0.0f);
    EXPECT_EQ(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: BoundaryValueParentSize002
 * @tc.desc: Test Measure with negative parent size
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueParentSize002, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.parentIdealSize.SetSize(SizeF(-50.0f, -50.0f));
    layoutConstraint.maxSize.SetSizeT(SizeF(100.0f, 100.0f));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Negative parent size should be used (constrained to maxSize, result is -50 clamped to 0)
    EXPECT_EQ(frameSize.Width(), 0.0f);
    EXPECT_EQ(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: BoundaryValueColor001
 * @tc.desc: Test with full range of color values
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar with min color value
     * @tc.expected: scrollBar created
     */
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetArcBackgroundColor(Color(0x00000000)); // Transparent black
    scrollBar->SetArcForegroundColor(Color(0x00FFFFFF)); // Transparent white

    auto paintMethod = AceType::MakeRefPtr<ArcScrollBarPaintMethod>();
    paintMethod->SetScrollBar(scrollBar);

    auto scrollBarOverlayModifier = AceType::MakeRefPtr<ArcScrollBarOverlayModifier>();
    paintMethod->SetScrollBarOverlayModifier(scrollBarOverlayModifier);

    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto paintWrapper = frameNode->CreatePaintWrapper();
    ASSERT_NE(paintWrapper, nullptr);

    /**
     * @tc.steps: step2. Call UpdateOverlayModifier with transparent colors
     * @tc.expected: should handle gracefully
     */
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));

    /**
     * @tc.steps: step3. Test with max color value
     */
    scrollBar->SetArcBackgroundColor(Color(0xFFFFFFFF)); // Opaque white
    scrollBar->SetArcForegroundColor(Color(0xFF000000)); // Opaque black
    paintMethod->UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
}

/**
 * @tc.name: BoundaryValueWidth001
 * @tc.desc: Test Measure with width=0, height=valid
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueWidth001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(0.0f, 100.0f)); // Width=0, Height=100
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 0.0f);
    EXPECT_EQ(frameSize.Height(), 100.0f);
}

/**
 * @tc.name: BoundaryValueWidth002
 * @tc.desc: Test Measure with width=valid, height=0
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueWidth002, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(100.0f, 0.0f)); // Width=100, Height=0
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 100.0f);
    EXPECT_EQ(frameSize.Height(), 0.0f);
}

/**
 * @tc.name: BoundaryValueInfinity001
 * @tc.desc: Test Measure with infinity constraint
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueInfinity001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    LayoutConstraintF layoutConstraint;
    float inf = std::numeric_limits<float>::infinity();
    layoutConstraint.maxSize.SetSizeT(SizeF(inf, inf));
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    // Should use infinity as the size
    EXPECT_TRUE(std::isinf(frameSize.Width()));
    EXPECT_TRUE(std::isinf(frameSize.Height()));
}

/**
 * @tc.name: BoundaryValueAspectRatio001
 * @tc.desc: Test Measure with extreme aspect ratios
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, BoundaryValueAspectRatio001, TestSize.Level1)
{
    auto frameNode = CreateArcScrollBarFrameNode();
    ASSERT_NE(frameNode, nullptr);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutProperty = AceType::DynamicCast<ScrollBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Test with very wide aspect ratio
     */
    LayoutConstraintF layoutConstraint;
    layoutConstraint.maxSize.SetSizeT(SizeF(1000.0f, 1.0f)); // 1000:1 ratio
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    ArcScrollBarLayoutAlgorithm layoutAlgorithm;
    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 1000.0f);
    EXPECT_EQ(frameSize.Height(), 1.0f);

    /**
     * @tc.steps: step3. Test with very tall aspect ratio
     */
    layoutConstraint.maxSize.SetSizeT(SizeF(1.0f, 1000.0f)); // 1:1000 ratio
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    layoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    frameSize = geometryNode->GetFrameSize();
    EXPECT_EQ(frameSize.Width(), 1.0f);
    EXPECT_EQ(frameSize.Height(), 1000.0f);
}

// ============================================================================
// ArcScrollBar (inner/arc_scroll_bar.cpp) Tests
// ============================================================================

/**
 * @tc.name: InBarTouchRegion001
 * @tc.desc: Test InBarTouchRegion when NeedScrollBar returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, InBarTouchRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar with NeedScrollBar=false
     * @tc.expected: scrollBar created
     */
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetDisplayMode(DisplayMode::AUTO);
    scrollBar->SetScrollable(false); // Make NeedScrollBar return false

    /**
     * @tc.steps: step2. Call InBarTouchRegion
     * @tc.expected: returns false when NeedScrollBar is false
     */
    Point testPoint(100.0f, 100.0f);
    EXPECT_FALSE(scrollBar->InBarTouchRegion(testPoint));
}

/**
 * @tc.name: InBarHoverRegion001
 * @tc.desc: Test InBarHoverRegion when NeedScrollBar returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, InBarHoverRegion001, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetScrollable(false);

    Point testPoint(100.0f, 100.0f);
    EXPECT_FALSE(scrollBar->InBarHoverRegion(testPoint));
}

/**
 * @tc.name: InBarRectRegion001
 * @tc.desc: Test InBarRectRegion when NeedScrollBar returns false
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, InBarRectRegion001, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetScrollable(false);

    Point testPoint(100.0f, 100.0f);
    EXPECT_FALSE(scrollBar->InBarRectRegion(testPoint));
}

/**
 * @tc.name: SetRoundTrickRegion002
 * @tc.desc: Test SetRoundTrickRegion when barRegionSize - activeSize is zero
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, SetRoundTrickRegion002, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetDisplayMode(DisplayMode::AUTO);
    scrollBar->SetScrollable(true);

    /**
     * @tc.steps: step2. Call with barRegionSize - activeSize = 0 (early return)
     * @tc.expected: should return early without crash
     */
    double estimatedHeight = 200.0f;
    double barRegionSize = 100.0f;
    double activeSize = 100.0f; // barRegionSize - activeSize = 0
    double activeMainOffset = 0.0f;
    double normalWidth = 20.0f;
    Size size(200.0f, 200.0f);

    scrollBar->SetRoundTrickRegion(estimatedHeight, barRegionSize, activeSize, activeMainOffset, normalWidth, size);

    // Verify early return doesn't crash (trickStartAngle_ should be 0 for early return case)
    EXPECT_EQ(scrollBar->trickStartAngle_, 0.0f);
}

/**
 * @tc.name: SetRoundTrickRegion003
 * @tc.desc: Test SetRoundTrickRegion with estimatedHeight <= 0 (early return)
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, SetRoundTrickRegion003, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetDisplayMode(DisplayMode::AUTO);
    scrollBar->SetScrollable(true);

    /**
     * @tc.steps: step2. Call with estimatedHeight <= 0
     * @tc.expected: should return early
     */
    Offset offset(0.0f, 0.0f);
    Offset lastOffset(0.0f, 50.0f);
    Size size(200.0f, 200.0f);
    double estimatedHeight = 0.0f; // Early return condition

    scrollBar->SetRoundTrickRegion(offset, size, lastOffset, estimatedHeight);

    // Verify early return doesn't crash (trickStartAngle_ should remain 0)
    EXPECT_EQ(scrollBar->trickStartAngle_, 0.0f);
}

/**
 * @tc.name: CalcPatternOffset001
 * @tc.desc: Test CalcPatternOffset when not driving
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CalcPatternOffset001, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    scrollBar->SetDisplayMode(DisplayMode::AUTO);
    scrollBar->isDriving_ = false; // Not driving

    /**
     * @tc.steps: step2. Call CalcPatternOffset
     * @tc.expected: returns input offset when not driving
     */
    float scrollBarOffset = 50.0f;
    float result = scrollBar->CalcPatternOffset(scrollBarOffset);
    EXPECT_EQ(result, scrollBarOffset);
}

/**
 * @tc.name: CalcReservedHeight001
 * @tc.desc: Test CalcReservedHeight
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CalcReservedHeight001, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();

    /**
     * @tc.steps: step1. Call CalcReservedHeight
     * @tc.expected: reserved heights are set to 0
     */
    scrollBar->CalcReservedHeight();

    EXPECT_EQ(scrollBar->GetStartReservedHeight().Value(), 0.0f);
    EXPECT_EQ(scrollBar->GetEndReservedHeight().Value(), 0.0f);
}

/**
 * @tc.name: CalcReservedHeight002
 * @tc.desc: Test CalcReservedHeight with pipeline context
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, CalcReservedHeight002, TestSize.Level1)
{
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();

    /**
     * @tc.steps: step1. Create mock pipeline context
     */
    RefPtr<PipelineContext> context = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step2. Call CalcReservedHeight with context
     * @tc.expected: completes without crash
     */
    scrollBar->CalcReservedHeight(context);

    EXPECT_EQ(scrollBar->GetStartReservedHeight().Value(), 0.0f);
    EXPECT_EQ(scrollBar->GetEndReservedHeight().Value(), 0.0f);
}

/**
 * @tc.name: ArcScrollBarConstructor001
 * @tc.desc: Test ArcScrollBar constructor with default parameters
 * @tc.type: FUNC
 */
HWTEST_F(ArcScrollBarPatternTestNg, ArcScrollBarConstructor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ArcScrollBar with default constructor
     * @tc.expected: ArcScrollBar created with default values
     */
    auto scrollBar = AceType::MakeRefPtr<ArcScrollBar>();
    ASSERT_NE(scrollBar, nullptr);

    /**
     * @tc.steps: step2. Verify default values from constructor
     * @tc.expected: defaults are set correctly
     */
    EXPECT_EQ(scrollBar->GetDisplayMode(), DisplayMode::AUTO);
    EXPECT_EQ(scrollBar->GetShapeMode(), ShapeMode::ROUND);
    EXPECT_EQ(scrollBar->GetPositionMode(), PositionMode::RIGHT);
}

} // namespace OHOS::Ace::NG
