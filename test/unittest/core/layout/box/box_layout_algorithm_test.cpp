/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include <optional>

#include "gtest/gtest.h"
#define protected public
#define private public
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_model_ng.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/property.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class BoxLayoutAlgorithmTest : public TestNG {
public:
    void SetUp() override
    {
        ViewStackProcessor::GetInstance()->ClearStack();
    }
    RefPtr<FrameNode> CreateBox(const std::function<void()>& callback)
    {
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        auto frameNode =
            FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<Pattern>(); });
        stack->Push(frameNode);
        frameNode->SetExclusiveEventForChild(true);
        if (callback) {
            callback();
        }
        RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
        ViewStackProcessor::GetInstance()->PopContainer();
        return AceType::DynamicCast<FrameNode>(element);
    }
};

/**
 * @tc.name: BoxLayoutAlgorithmTest_MeasureTest
 * @tc.desc: Test the functionality of Measure.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, MeasureTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    RefPtr<FrameNode> row;
    auto layoutWrapper = CreateBox([this, &row]() {
        ViewAbstract::SetWidth(CalcLength(720.0f));
        ViewAbstract::SetHeight(CalcLength(120.0f));
        ViewAbstract::SetMaxWidth(CalcLength(300.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
        row = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. update constraint and call Measure.
     * @tc.expected: expect the geometryNode is not nullptr and the measure result is correct.
     */
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Measure(Referenced::RawPtr(layoutWrapper));
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    const auto& content = geometryNode->GetContent();
    ASSERT_EQ(content, nullptr);
    auto boxSize = geometryNode->GetFrameSize();
    EXPECT_EQ(boxSize.ToString(), SizeF(300.0f, 120.0f).ToString());
    auto rowSize = row->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(rowSize.ToString(), SizeF(100.0f, 60.0f).ToString());
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_LayoutTest
 * @tc.desc: Test the functionality of Layout.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, LayoutTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    RefPtr<FrameNode> row1, row2;
    auto layoutWrapper = CreateBox([this, &row1, &row2]() {
        ViewAbstract::SetMaxWidth(CalcLength(300.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(150.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. update constraint and call Measure and Layout.
     * @tc.expected: expect the geometryNode is not nullptr and their layout results are both correct.
     */
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();

    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Measure(Referenced::RawPtr(layoutWrapper));
    boxLayoutAlgorithm.Layout(Referenced::RawPtr(layoutWrapper));
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    const auto& content = geometryNode->GetContent();
    ASSERT_EQ(content, nullptr);
    auto boxSize = geometryNode->GetFrameSize();
    auto boxOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(boxSize.ToString(), SizeF(150.0f, 100.0f).ToString());
    EXPECT_EQ(boxOffset.ToString(), OffsetF(0.0f, 0.0f).ToString());
    auto row1Offset = row1->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(row1Offset.ToString(), OffsetF(25.0f, 0.0f).ToString());
    auto row2Offset = row2->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(row2Offset.ToString(), OffsetF(0.0f, 20.0f).ToString());
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_MeasureContentTest001
 * @tc.desc: Test the functionality of MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, MeasureContentTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    auto layoutWrapper = CreateBox([]() {
        ViewAbstract::SetWidth(CalcLength(720.0f));
        ViewAbstract::SetHeight(CalcLength(120.0f));
        ViewAbstract::SetMaxWidth(CalcLength(300.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Perform constraint updates.
     */
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();
    layoutWrapper->hostNode_ = TestNG::CreateRow(nullptr);

    /**
     * @tc.steps: step3. call MeasureContent.
     * @tc.expected: expect the host is not null and the measureContent result is null caused by rowFrameNode is not
     * AtomicNode.
     */
    auto host = layoutWrapper->GetHostNode();
    EXPECT_NE(host, nullptr);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    auto size = boxLayoutAlgorithm.MeasureContent(
        layoutProperty->GetContentLayoutConstraint().value(), Referenced::RawPtr(layoutWrapper));
    EXPECT_FALSE(size);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_MeasureContentTest002
 * @tc.desc: Test the functionality of MeasureContent.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, MeasureContentTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    auto layoutWrapper = CreateBox([]() {});
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Perform constraint updates.
     */
    LayoutConstraintF layoutConstraint = { .maxSize = { 200.0f, 200.0f }, .percentReference = { 300.0f, 300.0f } };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step3. call MeasureContent.
     * @tc.expected: expect the host is not null.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.MeasureContent(layoutConstraint, Referenced::RawPtr(layoutWrapper));
    auto host = layoutWrapper->GetHostNode();
    EXPECT_NE(host, nullptr);

    /**
     * @tc.steps: step4. Set measureType_ = MeasureType::MATCH_PARENT and selfIdealSize is not Valid.
     * @tc.expected: return percentReference.
     */
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    std::optional<SizeF> sizeTemp =
        boxLayoutAlgorithm.MeasureContent(layoutConstraint, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sizeTemp.value().width_, 300.0f);
    EXPECT_EQ(sizeTemp.value().height_, 300.0f);

    /**
     * @tc.steps: step5. set measureType_ = MeasureType::MATCH_CONTENT.
     * @tc.expected: return minSize.
     */
    layoutConstraint.minSize.SetSizeT(SizeF(721.0f, 121.0f));
    layoutProperty->measureType_ = MeasureType::MATCH_CONTENT;
    sizeTemp = boxLayoutAlgorithm.MeasureContent(layoutConstraint, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sizeTemp.value().width_, 721.0f);
    EXPECT_EQ(sizeTemp.value().height_, 121.0f);

    /**
     * @tc.steps: step6. set selfIdealSize valid.
     * @tc.expected: return selfIdealSize.
     */
    layoutConstraint.selfIdealSize.SetSize(SizeF(719.0f, 119.0f));
    sizeTemp = boxLayoutAlgorithm.MeasureContent(layoutConstraint, Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(sizeTemp.value().width_, 719.0f);
    EXPECT_EQ(sizeTemp.value().height_, 119.0f);
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformLayoutTest
 * @tc.desc: Test the functionality of PerformLayout.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, PerformLayoutTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    RefPtr<FrameNode> row;
    auto layoutWrapper = CreateBox([this, &row]() {
        ViewAbstract::SetWidth(CalcLength(720.0f));
        ViewAbstract::SetHeight(CalcLength(120.0f));
        ViewAbstract::SetMaxWidth(CalcLength(300.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
        row = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Perform constraint updates.
     */
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(LayoutConstraintF());
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step3. call Measure and PerformLayout.
     * @tc.expected: expect the layout result is correct.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    boxLayoutAlgorithm.Measure(Referenced::RawPtr(layoutWrapper));
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    SizeF size { 100.0f, 100.0f };
    geometryNode->SetContentSize(size);
    boxLayoutAlgorithm.PerformLayout(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->content_->ToString(), RectF(OffsetF(100.0f, 10.0f), SizeF(100.0f, 100.0f)).ToString());
    auto boxOffset = geometryNode->GetFrameOffset();
    EXPECT_EQ(boxOffset.ToString(), OffsetF(0.0f, 0.0f).ToString());
    auto rowOffset = row->GetGeometryNode()->GetFrameOffset();
    EXPECT_EQ(rowOffset.ToString(), OffsetF(100.0f, 30.0f).ToString());
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildListTest001
 * @tc.desc: Test the functionality of PerformMeasureSelfWithChildList.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, PerformMeasureSelfWithChildListTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    auto layoutWrapper = CreateBox([]() {
        ViewAbstract::SetMaxWidth(CalcLength(200.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Perform constraint updates.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.parentIdealSize.SetSize(SizeF(300.0f, 120.0f));
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step3. call PerformMeasureSelfWithChildList.
     * @tc.expected: expect the MeasureType has been changed correctly and the measure result is correct.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    layoutWrapper->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    auto type = layoutWrapper->GetLayoutProperty()->measureType_;
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(type, MeasureType::MATCH_PARENT);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_EQ(geometryNode->GetFrameSize().ToString(), SizeF(200.0f, 120.0f).ToString());

    /**
     * @tc.steps: step4. call SetContentSize.
     * @tc.expected: expect the measure result is correct.
     */
    SizeF size { 0.1, 0.1 };
    geometryNode->SetContentSize(size);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(
        Referenced::RawPtr(layoutWrapper), layoutWrapper->GetAllChildrenWithBuild());
    EXPECT_EQ(geometryNode->content_->ToString(), RectF(OffsetF(0.0f, 0.0f), SizeF(0.1f, 0.1f)).ToString());
}

/**
 * @tc.name: BoxLayoutAlgorithmTest_PerformMeasureSelfWithChildListTest002
 * @tc.desc: Test the functionality of PerformMeasureSelfWithChildList.
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, PerformMeasureSelfWithChildListTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutWrapper, initial layout parameter and expect it is not nullptr.
     */
    RefPtr<FrameNode> row1, row2, row3;
    auto layoutWrapper = CreateBox([this, &row1, &row2, &row3]() {
        ViewAbstract::SetMaxWidth(CalcLength(600.0f));
        ViewAbstract::SetMaxHeight(CalcLength(300.0f));
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
            ViewAbstract::SetVisibility(VisibleType::GONE);
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(720.0f));
            ViewAbstract::SetHeight(CalcLength(120.0f));
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
    });
    ASSERT_NE(layoutWrapper, nullptr);

    /**
     * @tc.steps: step2. Perform element updates.
     */
    LayoutConstraintF parentLayoutConstraint;
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    /**
     * @tc.steps: step3. selfIdealSize isn't valid and content isn't valid.
     * @tc.expected: expect the size is zero.
     */
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    childList = layoutWrapper->GetAllChildrenWithBuild();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_FALSE(geometryNode->GetContent());
    layoutProperty->measureType_ = MeasureType::MATCH_PARENT;
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.Measure(Referenced::RawPtr(layoutWrapper));
    EXPECT_EQ(geometryNode->GetFrameSize().ToString(), SizeF(600.0f, 120.0f).ToString());

    /**
     * @tc.steps: step4. selfIdealSize isn't valid and parentIdealSize height is valid.
     * @tc.expected: expect the size is same as height.
     */
    parentLayoutConstraint.parentIdealSize.SetSize(SizeF(0.0f, 120.0f));
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(geometryNode->GetFrameSize().ToString(), SizeF(0.0f, 120.0f).ToString());

    /**
     * @tc.steps: step5. selfIdealSize isn't valid and parentIdealSize width is valid.
     * @tc.expected: expect the size is same as width and constrained by max width.
     */
    parentLayoutConstraint.parentIdealSize.SetSize(SizeF(720.0f, 0.0f));
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(geometryNode->GetFrameSize().ToString(), SizeF(600.0f, 0.0f).ToString());

    /**
     * @tc.steps: step6. selfIdealSize is valid.
     * @tc.expected: expect the size is same as selfIdealSize.
     */
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(500.0f, 60.0f));
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);
    EXPECT_EQ(geometryNode->GetFrameSize().ToString(), SizeF(500.0f, 60.0f).ToString());
}

/**
 * @tc.name: CalcSingleSideMarginFrame001
 * @tc.desc:test CalcSingleSideMarginFrame
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, CalcSingleSideMarginFrame001, TestSize.Level1)
{
    RefPtr<FrameNode> row1, row2, row3;
    auto layoutWrapper = CreateBox([this, &row1, &row2, &row3]() {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetHeight(CalcLength(120.0f));
            ViewAbstract::SetMargin(CalcLength(10.0f));
        });
        row3 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(50.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
            ViewAbstract::SetMargin(CalcLength(10.0f));
        });
    });
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_FALSE(geometryNode->GetContent());
    LayoutConstraintF parentLayoutConstraint;
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto childLayoutProperty = row2->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    childList = layoutWrapper->GetAllChildrenWithBuild();
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);

    EXPECT_TRUE(NearEqual(geometryNode->GetFrameSize().Height(), 140.0f));
}

/**
 * @tc.name: CalcSingleSideMarginFrame002
 * @tc.desc:test CalcSingleSideMarginFrame
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, CalcSingleSideMarginFrame002, TestSize.Level1)
{
    RefPtr<FrameNode> row1, row2;
    auto layoutWrapper = CreateBox([this, &row1, &row2]() {
        row1 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(60.0f));
            ViewAbstract::SetHeight(CalcLength(60.0f));
        });
        row2 = CreateRow([](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(120.0f));
            ViewAbstract::SetAspectRatio(1.0f);
        });
    });
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_FALSE(geometryNode->GetContent());

    LayoutConstraintF parentLayoutConstraint;
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto childLayoutProperty = row2->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    childList = layoutWrapper->GetAllChildrenWithBuild();
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);

    EXPECT_TRUE(NearEqual(geometryNode->GetFrameSize().Width(), 120.0f));
    EXPECT_TRUE(NearEqual(geometryNode->GetFrameSize().Height(), 120.0f));
}

/**
 * @tc.name: CalcLayoutPolicySingleSide001
 * @tc.desc:test CalcLayoutPolicySingleSide
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, CalcLayoutPolicySingleSide001, TestSize.Level1)
{
    MarginPropertyF margin = { .left = 10.0f, .right = 20.0f, .top = 30.0f, .bottom = 5.0f };
    float maxWidth = 50.0f;
    float maxHeight = 50.0f;
    OptionalSizeF singleSideFrame;
    singleSideFrame.SetWidth(30.0f);

    BoxLayoutAlgorithm::CalcSingleSideMarginFrame(margin, singleSideFrame, maxWidth, maxHeight);
    EXPECT_EQ(maxWidth, 60.0f);
    EXPECT_EQ(maxHeight, 50.0f);
}

/**
 * @tc.name: WrapAndMatchParent001
 * @tc.desc:test parent wrap and child match parent
 * @tc.type: FUNC
 */
HWTEST_F(BoxLayoutAlgorithmTest, WrapAndMatchParent001, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    auto layoutWrapper = CreateBox([this, &row1]() {
        row1 = CreateRow([](RowModelNG model) {
        });
    });
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_FALSE(geometryNode->GetContent());

    LayoutConstraintF parentLayoutConstraint;
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutProperty->UpdateContentConstraint();

    auto childLayoutProperty = row1->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    auto childGeometryNode = row1->GetGeometryNode();
    ASSERT_NE(childGeometryNode, nullptr);
    childGeometryNode->SetFrameSize(SizeF(60.0f, 60.0f));
    BoxLayoutAlgorithm boxLayoutAlgorithm;
    std::list<RefPtr<LayoutWrapper>> childList;
    childList = layoutWrapper->GetAllChildrenWithBuild();
    boxLayoutAlgorithm.PerformMeasureSelfWithChildList(Referenced::RawPtr(layoutWrapper), childList);

    EXPECT_TRUE(NearEqual(geometryNode->GetFrameSize().Height(), 0.0f));
}
} // namespace OHOS::Ace::NG
