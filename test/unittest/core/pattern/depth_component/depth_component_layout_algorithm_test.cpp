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

// TDD coverage for DepthComponentLayoutAlgorithm (Measure / AdjustFrameSize / Layout).

#include "depth_component_test_base.h"

namespace OHOS::Ace::NG {

class DepthComponentLayoutAlgorithmTestNg : public DepthComponentTestBase {};

namespace {
// Build a wrapper whose host uses a plain Pattern (so child Measure stays lightweight) with a
// preset frame size, and register it as a child of the host wrapper.
RefPtr<LayoutWrapperNode> AppendPlainChild(const RefPtr<LayoutWrapperNode>& hostWrapper, float w, float h)
{
    auto childId = ElementRegister::GetInstance()->MakeUniqueId();
    auto child = FrameNode::CreateFrameNode("plainChild", childId, AceType::MakeRefPtr<Pattern>());
    auto childGeo = AceType::MakeRefPtr<GeometryNode>();
    childGeo->Reset();
    childGeo->SetFrameSize(SizeF(w, h));
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(child, childGeo, child->GetLayoutProperty());
    childWrapper->SetLayoutAlgorithm(
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>()));
    hostWrapper->AppendChild(childWrapper);
    return childWrapper;
}

// Wrapper without a seeded layout constraint (used to exercise the null-constraint CHECK path).
RefPtr<LayoutWrapperNode> CreateWrapperWithoutConstraint()
{
    auto host = DepthComponentTestBase::CreateNode({});
    auto geo = AceType::MakeRefPtr<GeometryNode>();
    geo->Reset();
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(host, geo, host->GetLayoutProperty());
    auto pattern = host->GetPattern<DepthComponentPattern>();
    wrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(pattern->CreateLayoutAlgorithm()));
    return wrapper;
}
} // namespace

// ===================== Measure: null guards =====================

/**
 * @tc.name: Measure001
 * @tc.desc: Measure is a safe no-op when the layout wrapper is null.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure001, TestSize.Level1)
{
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(nullptr); // CHECK_NULL_VOID
}

/**
 * @tc.name: Measure002
 * @tc.desc: Measure is a safe no-op when the property is not DepthComponentLayoutProperty.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure002, TestSize.Level1)
{
    auto plainNode = FrameNode::CreateFrameNode(
        "plain", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto geo = AceType::MakeRefPtr<GeometryNode>();
    geo->Reset();
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(plainNode, geo, plainNode->GetLayoutProperty());
    wrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>()));
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper)); // DynamicCast fails -> CHECK
}

/**
 * @tc.name: Measure003
 * @tc.desc: Measure is a safe no-op when there is no layout constraint.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure003, TestSize.Level1)
{
    auto wrapper = CreateWrapperWithoutConstraint();
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper)); // GetLayoutConstraint null -> CHECK
}

// ===================== Measure: sizing branches =====================

/**
 * @tc.name: Measure004
 * @tc.desc: Without layout policy, selfIdealSize drives the frame size.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure004, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetSize(SizeF(200.0f, 120.0f));
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    constraint.percentReference = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper));
    EXPECT_EQ(wrapper->GetGeometryNode()->GetFrameSize(), SizeF(200.0f, 120.0f));
}

/**
 * @tc.name: Measure005
 * @tc.desc: Width WRAP_CONTENT adopts the widest child.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure005, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    AppendPlainChild(wrapper, 250.0f, 100.0f);
    AppendPlainChild(wrapper, 180.0f, 90.0f);
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
    LayoutConstraintF constraint;
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    constraint.selfIdealSize.SetHeight(120.0f);
    constraint.percentReference = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper));
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Width(), 250.0f, 0.001f);
}

/**
 * @tc.name: Measure006
 * @tc.desc: Width MATCH_PARENT adopts the parent ideal width.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure006, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    LayoutConstraintF constraint;
    constraint.parentIdealSize.SetSize(SizeF(700.0f, 500.0f));
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    constraint.selfIdealSize.SetHeight(120.0f);
    constraint.percentReference = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper));
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Width(), 700.0f, 0.001f);
}

/**
 * @tc.name: Measure007
 * @tc.desc: Height MATCH_PARENT adopts the parent ideal height.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Measure007, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    ASSERT_NE(prop, nullptr);
    prop->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    LayoutConstraintF constraint;
    constraint.parentIdealSize.SetSize(SizeF(700.0f, 500.0f));
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    constraint.selfIdealSize.SetWidth(300.0f);
    constraint.percentReference = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    algo.Measure(AceType::RawPtr(wrapper));
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Height(), 500.0f, 0.001f);
}

// ===================== AdjustFrameSize =====================

/**
 * @tc.name: Adjust001
 * @tc.desc: Null wrapper is a safe no-op.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust001, TestSize.Level1)
{
    DepthComponentLayoutAlgorithm algo;
    OptionalSizeF frameSize;
    algo.AdjustFrameSize(nullptr, frameSize); // CHECK_NULL_VOID
}

/**
 * @tc.name: Adjust002
 * @tc.desc: Missing width with no parent ideal falls back to the default 640.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust002, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    DepthComponentLayoutAlgorithm algo;
    OptionalSizeF frameSize; // width / height unset
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Width(), DEFAULT_DEPTH_COMPONENT_WIDTH, 0.001f);
}

/**
 * @tc.name: Adjust003
 * @tc.desc: Missing width with a parent ideal adopts the parent value.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust003, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.parentIdealSize.SetSize(SizeF(320.0f, 240.0f));
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    OptionalSizeF frameSize;
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Width(), 320.0f, 0.001f);
}

/**
 * @tc.name: Adjust004
 * @tc.desc: Missing height with no parent ideal falls back to the default 480.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust004, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.selfIdealSize.SetWidth(100.0f); // width set, height unset
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    OptionalSizeF frameSize;
    frameSize.SetWidth(100.0f);
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Height(), DEFAULT_DEPTH_COMPONENT_HEIGHT, 0.001f);
}

/**
 * @tc.name: Adjust005
 * @tc.desc: Missing height with a parent ideal adopts the parent value.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust005, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.parentIdealSize.SetSize(SizeF(320.0f, 240.0f));
    constraint.maxSize = SizeF(1000.0f, 1000.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;
    OptionalSizeF frameSize;
    frameSize.SetWidth(320.0f);
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    EXPECT_NEAR(wrapper->GetGeometryNode()->GetFrameSize().Height(), 240.0f, 0.001f);
}

/**
 * @tc.name: Adjust006
 * @tc.desc: The resolved frame size is clamped to both the min and max bounds.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Adjust006, TestSize.Level1)
{
    // Adjust operates on the frameSize passed IN (already computed by Measure); it does NOT read
    // the constraint's selfIdealSize — only parentIdealSize/minSize/maxSize. So seed frameSize
    // itself outside the [min,max] window and verify Constrain clamps it on both directions.
    auto [host, wrapper] = CreateMeasureableNode({});
    auto prop = host->GetLayoutProperty<DepthComponentLayoutProperty>();
    LayoutConstraintF constraint;
    constraint.minSize = SizeF(100.0f, 100.0f);
    constraint.maxSize = SizeF(500.0f, 500.0f);
    prop->UpdateLayoutConstraint(constraint);
    DepthComponentLayoutAlgorithm algo;

    // Above maxSize -> clamped DOWN to max.
    OptionalSizeF frameSize;
    frameSize.SetSize(SizeF(2000.0f, 2000.0f));
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    auto clampedDown = wrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_NEAR(clampedDown.Width(), 500.0f, 0.001f);
    EXPECT_NEAR(clampedDown.Height(), 500.0f, 0.001f);

    // Below minSize -> clamped UP to min.
    frameSize.SetSize(SizeF(50.0f, 50.0f));
    algo.AdjustFrameSize(AceType::RawPtr(wrapper), frameSize);
    auto clampedUp = wrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_NEAR(clampedUp.Width(), 100.0f, 0.001f);
    EXPECT_NEAR(clampedUp.Height(), 100.0f, 0.001f);
}

// ===================== Layout =====================

/**
 * @tc.name: Layout001
 * @tc.desc: Non-positive frame size aborts Layout early.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Layout001, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    wrapper->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    DepthComponentLayoutAlgorithm algo;
    algo.Layout(AceType::RawPtr(wrapper)); // early return
}

/**
 * @tc.name: Layout002
 * @tc.desc: Null wrapper is a safe no-op.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Layout002, TestSize.Level1)
{
    DepthComponentLayoutAlgorithm algo;
    algo.Layout(nullptr); // CHECK_NULL_VOID
}

/**
 * @tc.name: Layout003
 * @tc.desc: A valid frame size with children offsets and lays out each child.
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Layout003, TestSize.Level1)
{
    auto [host, wrapper] = CreateMeasureableNode({});
    auto child = AppendPlainChild(wrapper, 100.0f, 50.0f);
    wrapper->GetGeometryNode()->SetFrameSize(SizeF(300.0f, 200.0f));
    DepthComponentLayoutAlgorithm algo;
    algo.Layout(AceType::RawPtr(wrapper));
    // Child should have received a margin frame offset (padding offset, default zero).
    EXPECT_FALSE(std::isnan(child->GetGeometryNode()->GetMarginFrameOffset().GetX()));
}

/**
 * @tc.name: Layout004
 * @tc.desc: Layout tolerates a non-DepthComponent property (DynamicCast null path).
 * @tc.type: FUNC
 */
HWTEST_F(DepthComponentLayoutAlgorithmTestNg, Layout004, TestSize.Level1)
{
    auto plainNode = FrameNode::CreateFrameNode(
        "plain", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    auto geo = AceType::MakeRefPtr<GeometryNode>();
    geo->SetFrameSize(SizeF(300.0f, 200.0f));
    auto wrapper = AceType::MakeRefPtr<LayoutWrapperNode>(plainNode, geo, plainNode->GetLayoutProperty());
    wrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<LayoutAlgorithm>()));
    DepthComponentLayoutAlgorithm algo;
    algo.Layout(AceType::RawPtr(wrapper)); // DynamicCast fails -> CHECK
}
} // namespace OHOS::Ace::NG
