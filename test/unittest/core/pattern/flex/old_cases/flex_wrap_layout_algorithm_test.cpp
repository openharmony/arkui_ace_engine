/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "base/memory/ref_counter.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/flex/wrap_layout_algorithm.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "base/utils/utils.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protectd public

namespace OHOS::Ace::NG {
namespace {

using namespace testing;
using namespace testing::ext;

const float LAYOUT_WIDTH = 1.0f;
const float LAYOUT_HEIGHT = 2.0f;
const float LAYOUT_FROW = 3.0f;

class WrapLayoutAlgorithmTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    RefPtr<LayoutWrapperNode> CreateLayoutWrapper();
    RefPtr<LayoutWrapperNode> CreateParam();
};

void WrapLayoutAlgorithmTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
}

void WrapLayoutAlgorithmTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

RefPtr<LayoutWrapperNode> WrapLayoutAlgorithmTest::CreateParam()
{
    auto layoutWrapper = CreateLayoutWrapper();
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    flexProp->UpdateFlexGrow(LAYOUT_FROW);
    SizeF size(LAYOUT_WIDTH, LAYOUT_HEIGHT);
    layoutWrapper->geometryNode_->SetFrameSize(size);
    return layoutWrapper;
}

RefPtr<LayoutWrapperNode> WrapLayoutAlgorithmTest::CreateLayoutWrapper()
{
    FrameNode *node = new (FrameNode)(V2::FLEX_ETS_TAG, 0, AceType::MakeRefPtr<FlexLayoutPattern>(true));
    RefCounter* ref = ThreadSafeRef::Create();
    ref->IncStrongRef();
    WeakPtr<FrameNode> wrapFrameNode(node, ref);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        wrapFrameNode, geometryNode, node->GetLayoutProperty());

    RefPtr<LayoutAlgorithm> layoutAlgorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    layoutWrapper->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm);
    layoutWrapper->layoutProperty_ = AceType::MakeRefPtr<FlexLayoutProperty>();
    layoutWrapper->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->layoutProperty_->safeAreaPadding_ = std::make_unique<PaddingProperty>();
    layoutWrapper->layoutProperty_->padding_ = std::make_unique<PaddingProperty>();
    layoutWrapper->layoutProperty_->margin_ = std::make_unique<MarginProperty>();

    layoutWrapper->layoutProperty_->safeAreaExpandOpts_ = std::make_unique<SafeAreaExpandOpts>();
    layoutWrapper->layoutProperty_->safeAreaInsets_ = std::make_unique<SafeAreaInsets>();
    layoutWrapper->layoutProperty_->borderWidth_ = std::make_unique<BorderWidthProperty>();
    layoutWrapper->layoutProperty_->outerBorderWidth_ = std::make_unique<BorderWidthProperty>();

    layoutWrapper->layoutProperty_->positionProperty_ = std::make_unique<PositionProperty>();
    layoutWrapper->layoutProperty_->flexItemProperty_ = std::make_unique<FlexItemProperty>();
    layoutWrapper->layoutProperty_->gridProperty_ = std::make_unique<GridProperty>();
    layoutWrapper->layoutProperty_->geometryTransition_ = AceType::MakeRefPtr<NG::GeometryTransition>("", true, true);
    return layoutWrapper;
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout001, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL_REVERSE);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    SizeF size(1.1, 2.2);
    float param = wrapLayoutAlgorithm->GetMainAxisLengthOfSize(size);
    EXPECT_DOUBLE_EQ(param, size.Width());
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout002, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL_REVERSE);

    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));


    SizeF size(1.1, 2.2);
    float param = wrapLayoutAlgorithm->GetMainAxisLengthOfSize(size);
    EXPECT_DOUBLE_EQ(param, size.Height());
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout003, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL_REVERSE);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));
    
    SizeF size(1.1, 2.2);
    float param = wrapLayoutAlgorithm->GetCrossAxisLengthOfSize(size);
    EXPECT_DOUBLE_EQ(param, size.Height());
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout004, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL_REVERSE);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));
    
    SizeF size(1.1, 2.2);
    float param = wrapLayoutAlgorithm->GetCrossAxisLengthOfSize(size);
    EXPECT_DOUBLE_EQ(param, size.Width());
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout005, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    flexProp->UpdateCrossAlignment(WrapAlignment::STRETCH);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    OffsetF translate(2.0, 3.0);
    layoutWrapper->geometryNode_->SetMarginFrameOffset(translate);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);
    ContentInfo content(362.2, 362.2, 362, list);
    auto layoutNode = CreateLayoutWrapper();
    wrapLayoutAlgorithm->StretchItemsInContent(layoutNode.GetRawPtr(), content);

    float height = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()->selfIdealSize.Height().value_or(0.0);
    EXPECT_TRUE(NearEqual<float>(content.crossLength, height));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout006, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateCrossAlignment(WrapAlignment::STRETCH);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    OffsetF translate(2.0, 3.0);
    layoutWrapper->geometryNode_->SetMarginFrameOffset(translate);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);

    ContentInfo content(362.2, 362.2, 362, list);
    auto layoutNode = CreateLayoutWrapper();
    wrapLayoutAlgorithm->StretchItemsInContent(layoutNode.GetRawPtr(), content);

    float width = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()->selfIdealSize.Width().value_or(0.0);
    EXPECT_TRUE(NearEqual<float>(content.crossLength, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout007, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);

    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateCrossAlignment(WrapAlignment::SPACE_AROUND);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    OffsetF translate(2.0, 3.0);
    layoutWrapper->geometryNode_->SetMarginFrameOffset(translate);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);

    ContentInfo content(362.2, 362.2, 362, list);
    auto layoutNode = CreateLayoutWrapper();
    wrapLayoutAlgorithm->StretchItemsInContent(layoutNode.GetRawPtr(), content);

    float width = layoutWrapper->GetGeometryNode()->GetParentLayoutConstraint()->selfIdealSize.Width().value_or(0.0);
    EXPECT_FALSE(NearEqual<float>(content.crossLength, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout008, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->layoutConstraint_->selfIdealSize.SetHeight(1.0);
    flexProp->layoutConstraint_->selfIdealSize.SetWidth(1.0);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);
    EXPECT_TRUE(wrapLayoutAlgorithm->hasIdealWidth_);
    EXPECT_TRUE(wrapLayoutAlgorithm->hasIdealHeight_);

    float height = flexProp->layoutConstraint_->selfIdealSize.Height().value_or(0.0);
    float width = flexProp->layoutConstraint_->selfIdealSize.Width().value_or(0.0);
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, height));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout009, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->layoutConstraint_->selfIdealSize.SetHeight(1.0);
    flexProp->layoutConstraint_->selfIdealSize.SetWidth(1.0);
    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);

    EXPECT_TRUE(wrapLayoutAlgorithm->hasIdealWidth_);
    EXPECT_TRUE(wrapLayoutAlgorithm->hasIdealHeight_);
    float height = flexProp->layoutConstraint_->selfIdealSize.Height().value_or(0.0);
    float width = flexProp->layoutConstraint_->selfIdealSize.Width().value_or(0.0);
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, height));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout010, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->layoutConstraint_->percentReference.SetWidth(1.0);
    flexProp->layoutConstraint_->percentReference.SetHeight(1.0);
    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(1012);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    
    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);
    float width = flexProp->layoutConstraint_->percentReference.Width();
    float height = flexProp->layoutConstraint_->percentReference.Height();
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, width));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, height));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout011, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->layoutConstraint_->parentIdealSize.SetWidth(1.0);
    flexProp->layoutConstraint_->parentIdealSize.SetHeight(1.0);
    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    flexProp->layoutConstraint_->percentReference.SetHeight(1.0);
    flexProp->layoutConstraint_->percentReference.SetWidth(1.0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(1012);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    
    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);
    float height = flexProp->layoutConstraint_->parentIdealSize.Height().value_or(0.0);
    float width = flexProp->layoutConstraint_->parentIdealSize.Width().value_or(0.0);
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, height));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout012, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);

    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(1000);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    
    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);
    float width = flexProp->layoutConstraint_->maxSize.Width();
    float height = flexProp->layoutConstraint_->maxSize.Height();
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, width));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, height));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout013, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);

    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(1000);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));
    
    wrapLayoutAlgorithm->PerformLayoutInitialize(flexProp);
    float height = flexProp->layoutConstraint_->maxSize.Height();
    float width = flexProp->layoutConstraint_->maxSize.Width();
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->mainLengthLimit_, height));
    EXPECT_TRUE(NearEqual<float>(wrapLayoutAlgorithm->crossLengthLimit_, width));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout014, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);

    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    float crossLength = 1.0;
    float mainLeftLength = 2.0;
    float crossLeftLength = 3.0;
    SizeF size = wrapLayoutAlgorithm->GetLeftSize(crossLength, mainLeftLength, crossLeftLength);
    EXPECT_TRUE(NearEqual<float>(mainLeftLength, size.Height()));
    EXPECT_TRUE(NearEqual<float>((crossLeftLength - crossLength), size.Width()));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout015, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);

    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    float crossLength = 1.0;
    float mainLeftLength = 2.0;
    float crossLeftLength = 3.0;
    SizeF size = wrapLayoutAlgorithm->GetLeftSize(crossLength, mainLeftLength, crossLeftLength);
    EXPECT_TRUE(NearEqual<float>(mainLeftLength, size.Width()));
    EXPECT_TRUE(NearEqual<float>((crossLeftLength - crossLength), size.Height()));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout016, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    flexProp->UpdateLayoutDirection(TextDirection::RTL);
    flexProp->layoutConstraint_->parentIdealSize.SetWidth(1.0);
    flexProp->layoutConstraint_->parentIdealSize.SetHeight(1.0);
    flexProp->layoutConstraint_->maxSize.SetHeight(2.0);
    flexProp->layoutConstraint_->maxSize.SetWidth(2.0);
    flexProp->layoutConstraint_->percentReference.SetHeight(3.0);
    flexProp->layoutConstraint_->percentReference.SetWidth(3.0);

    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    OffsetF startPosition(1.0, 1.0);
    OffsetF spaceBetweenContentsOnCrossAxis(2.0, 2.0);
    float height = startPosition.GetX() + flexProp->layoutConstraint_->maxSize.Width();
    wrapLayoutAlgorithm->LayoutWholeWrap(startPosition,
        spaceBetweenContentsOnCrossAxis, AccessibilityManager::RawPtr(wrapper));
    EXPECT_TRUE(NearEqual<float>(startPosition.GetX(), height));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout017, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    Dimension value(10);
    flexProp->UpdateSpace(value);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    SizeF size(1.0, 2.0);
    layoutWrapper->geometryNode_->SetFrameSize(size);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);
    ContentInfo content(0.0, 0.0, 0, list);
    FlexItemProperties flexItemProperties;
    wrapLayoutAlgorithm->GetFlexItemProperties(content, flexItemProperties);
    float sum = size.Width() + flexProp->GetSpaceValue({}).value_;
    EXPECT_TRUE(NearEqual<float>(sum, wrapLayoutAlgorithm->currentMainLength_));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout018, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateWrapDirection(WrapDirection::VERTICAL);
    Dimension value(10);
    flexProp->UpdateSpace(value);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    SizeF size(1.0, 2.0);
    layoutWrapper->geometryNode_->SetFrameSize(size);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);
    ContentInfo content(0.0, 0.0, 0, list);
    FlexItemProperties flexItemProperties;
    wrapLayoutAlgorithm->GetFlexItemProperties(content, flexItemProperties);
    float sum = size.Height() + flexProp->GetSpaceValue({}).value_;
    EXPECT_TRUE(NearEqual<float>(sum, wrapLayoutAlgorithm->currentMainLength_));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout019, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));

    auto layoutWrapper = CreateLayoutWrapper();
    auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(flexProp, nullptr);
    flexProp->UpdateFlexGrow(2.0);
    std::list<RefPtr<LayoutWrapper>> list;
    list.push_back(layoutWrapper);
    ContentInfo content(0.0, 0.0, 0, list);
    FlexItemProperties flexItemProperties;
    flexItemProperties.totalGrow = 1;
    wrapLayoutAlgorithm->GetFlexItemProperties(content, flexItemProperties);
    EXPECT_TRUE(NearEqual<float>(flexItemProperties.totalGrow, 3));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout020, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProperty = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    flexProperty->UpdateWrapDirection(WrapDirection::HORIZONTAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));
    FlexItemProperties flexItemProperties;
    flexItemProperties.totalGrow = 1.0;

    LayoutConstraintF layoutConstraintF = {
        .minSize = { 2, 0 },
        .maxSize = { 2, 0 },
        .percentReference = { 2, 0 },
        .parentIdealSize = { 2, 0 },
        .selfIdealSize = {2, 0},
    };
    auto layoutWrapper = CreateParam();
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraintF;
    wrapLayoutAlgorithm->CalcFlexGrowLayout(layoutWrapper, flexItemProperties, 2.0);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_TRUE(NearEqual<float>(geometryNode->GetParentLayoutConstraint()->selfIdealSize.Width().value_or(0.0), 7.0));
}

HWTEST_F(WrapLayoutAlgorithmTest, FlexWrapFrameNodeLayout021, TestSize.Level1)
{
    auto wrapLayoutAlgorithm = AccessibilityManager::MakeRefPtr<WrapLayoutAlgorithm>(false);
    auto wrapper = CreateLayoutWrapper();
    wrapper->AppendChild(CreateLayoutWrapper(), false);
    auto flexProperty = AceType::DynamicCast<FlexLayoutProperty>(wrapper->GetLayoutProperty());
    flexProperty->UpdateWrapDirection(WrapDirection::VERTICAL);
    wrapLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(wrapper));
    FlexItemProperties flexItemProperties;
    flexItemProperties.totalGrow = 1.0;
    LayoutConstraintF layoutConstraintF = {
        .minSize = { 2, 1 },
        .maxSize = { 2, 1 },
        .percentReference = { 2, 1 },
        .parentIdealSize = { 2, 1 },
        .selfIdealSize = {2, 1},
    };

    auto layoutWrapper = CreateParam();
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraintF;
    wrapLayoutAlgorithm->CalcFlexGrowLayout(layoutWrapper, flexItemProperties, 2.0);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    EXPECT_TRUE(NearEqual<float>(geometryNode->GetParentLayoutConstraint()->selfIdealSize.Height().value_or(0.0), 8.0));
}
}
}
