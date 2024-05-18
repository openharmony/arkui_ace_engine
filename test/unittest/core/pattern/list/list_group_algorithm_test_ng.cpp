/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "list_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ListGroupAlgTestNg : public ListTestNg {
public:
};

/**
 * @tc.name: ListItemGroupLayoutAlgorithm001
 * @tc.desc: ListItemGroup  Measure
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_NeedMeasureItem001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 3;
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
    // FrameNode = 2 * 3
    CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone(frameNode_);

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();

    /* *
     * @tc.steps: step3. build a object about ListItemGroupLayoutAlgorithm
     */
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    EXPECT_TRUE(listItemGroupAl->forwardLayout_ && listItemGroupAl->headerIndex_ >= 0);

    bool resTypeInit = listItemGroupAl->NeedMeasureItem();
    EXPECT_TRUE(resTypeInit);

    listItemGroupAl->headerMainSize_ = 3.1;
    listItemGroupAl->endPos_ = 1.1;

    bool resType = listItemGroupAl->NeedMeasureItem();
    EXPECT_FALSE(resType);

    // init data
    listItemGroupAl->headerMainSize_ = 0.0f;
    listItemGroupAl->startPos_ = 0.0f;
    listItemGroupAl->endPos_ = 0.0f;
    listItemGroupAl->referencePos_ = 0.0f;
    listItemGroupAl->totalMainSize_ = 0.0f;
    listItemGroupAl->footerMainSize_ = 0.0f;

    // LessNotEqual check
    listItemGroupAl->totalMainSize_ = 10.1;
    listItemGroupAl->footerMainSize_ = 3.1;
    listItemGroupAl->startPos_ = 8.1;

    resType = listItemGroupAl->NeedMeasureItem();
    EXPECT_FALSE(resType);
}

/**
 * @tc.name: ListItemGroupLayoutAlgorithm002
 * @tc.desc: ListItemGroup  Measure
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_NeedMeasureItem002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 3;
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
    // FrameNode = 2 * 3
    CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone(frameNode_);

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();

    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();

    /* *
     * @tc.steps: step3. build a object about ListItemGroupLayoutAlgorithm
     */
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    EXPECT_TRUE(listItemGroupAl->forwardLayout_ && listItemGroupAl->headerIndex_ >= 0);

    // forwardLayout equ false, GreatNotEqual
    listItemGroupAl->forwardLayout_ = false;
    listItemGroupAl->headerMainSize_ = 3.1;
    listItemGroupAl->referencePos_ = 10.1;
    listItemGroupAl->totalMainSize_ = 10.1;
    listItemGroupAl->endPos_ = 1.1;

    bool resType = listItemGroupAl->NeedMeasureItem();
    EXPECT_FALSE(resType);

    // init data
    listItemGroupAl->headerMainSize_ = 0.0f;
    listItemGroupAl->startPos_ = 0.0f;
    listItemGroupAl->endPos_ = 0.0f;
    listItemGroupAl->referencePos_ = 0.0f;
    listItemGroupAl->totalMainSize_ = 0.0f;
    listItemGroupAl->footerMainSize_ = 0.0f;

    // forwardLayout false
    listItemGroupAl->forwardLayout_ = false;
    listItemGroupAl->totalMainSize_ = 10.1;
    listItemGroupAl->footerMainSize_ = 3.1;
    listItemGroupAl->startPos_ = 8.1;
    listItemGroupAl->referencePos_ = 10.1;

    resType = listItemGroupAl->NeedMeasureItem();
    EXPECT_FALSE(resType);

    listItemGroupAl->startPos_ = 6.1;
    resType = listItemGroupAl->NeedMeasureItem();
    EXPECT_TRUE(resType);
}

/**
 * @tc.name: ListItemGroupLayoutAlgorithm_Layout
 * @tc.desc: set layoutWrapper Property null
 * @tc.type: FUNC
 */
HWTEST_F(ListGroupAlgTestNg, ListItemGroupLayoutAlgorithm_Layout, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. create List/ListItemGroup and Set Space
     */
    int32_t groupNumber = 2;
    int32_t itemNumber = 3;
    ListModelNG model = CreateList();
    model.SetSpace(Dimension(SPACE));
    // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
    // FrameNode = 2 * 3
    CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
    CreateDone(frameNode_);

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);

    /* *
     * @tc.steps: step3. build a object about layoutWraper
     */
    RefPtr<LayoutWrapper> layoutWrapper = groupFrameNode->CreateLayoutWrapper(true, true);
    RefPtr<LayoutWrapperNode> layoutWrapper_ = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper);
    // Set LayoutProperty null , CHECK_NULL_VOID eq null
    layoutWrapper_->layoutProperty_ = nullptr;
    const auto &layoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_EQ(layoutProperty, nullptr);
    
    /* *
     * @tc.steps: step4. build a object about ListItemGroupLayoutAlgorithm
     */
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    listItemGroupAl->headerIndex_ = -1;
    listItemGroupAl->Layout(AceType::RawPtr<LayoutWrapper>(layoutWrapper));
}

/**
 * @tc.name: ListLayoutAlgorithmTest001
 * @tc.desc: Test the list layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListLayoutAlgorithmTest001, TestSize.Level1)
{
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    ASSERT_NE(listPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listLayoutProperty = frameNode->GetLayoutProperty<ListLayoutProperty>();
    listLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListLayoutAlgorithm listLayoutAlgorithm;
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    struct ListItemInfo listItemInfo1;
    listItemInfo1.startPos = 0.0f;
    listItemInfo1.endPos = 180.0f;
    listLayoutAlgorithm.contentMainSize_ = 720.0f;
    listLayoutAlgorithm.itemPosition_.empty();
    listLayoutAlgorithm.itemPosition_.emplace(std::make_pair(0, listItemInfo1));
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(listLayoutAlgorithm.itemPosition_.begin()->first);
    auto size = layoutWrapper->GetGeometryNode()->GetMarginFrameSize();
    float crossSize = 300.0f;
    int32_t startIndex = 0;
    listLayoutAlgorithm.LayoutItem(wrapper, 0, listLayoutAlgorithm.itemPosition_.begin()->second,
        startIndex, crossSize);
    float crossOffset = listLayoutAlgorithm.CalculateLaneCrossOffset(crossSize, size.Width());
    auto offset = OffsetF(crossSize - crossOffset - size.Width(), listItemInfo1.startPos);
    EXPECT_EQ(listLayoutAlgorithm.contentMainSize_ - size.Width(), crossOffset);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    EXPECT_EQ(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: ListItemLayoutAlgorithmTest001
 * @tc.desc: Test the listitem layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListItemLayoutAlgorithmTest001, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    ASSERT_NE(listItemPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listItemLayoutProperty = frameNode->GetLayoutProperty<ListItemLayoutProperty>();
    listItemLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listItemLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListItemLayoutAlgorithm listItemLayoutAlgorithm(0, 0, 0);
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    listItemLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    listItemLayoutAlgorithm.Layout(AceType::RawPtr(layoutWrapper));
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    EXPECT_EQ(layoutDirection, TextDirection::RTL);
}

/**
 * @tc.name: ListItemLayoutAlgorithmTest002
 * @tc.desc: Test the listitem layout from right to left
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(ListGroupAlgTestNg, ListItemLayoutAlgorithmTest002, TestSize.Level1)
{
    RefPtr<ListItemPattern> listItemPattern = AceType::MakeRefPtr<ListItemPattern>(nullptr, V2::ListItemStyle::NONE);
    ASSERT_NE(listItemPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, -1, listItemPattern);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = frameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    /**
     * @tc.steps: step2. call Layout function.
     */
    // set reverse true
    auto listItemLayoutProperty = frameNode->GetLayoutProperty<ListItemLayoutProperty>();
    listItemLayoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, geometryNode, listItemLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    ListItemLayoutAlgorithm listItemLayoutAlgorithm(0, 0, 0);
    LayoutConstraintF layoutConstraint;
    layoutWrapper->layoutProperty_->layoutConstraint_ = layoutConstraint;
    layoutWrapper->layoutProperty_->contentConstraint_ = layoutConstraint;
    listItemLayoutAlgorithm.Measure(AceType::RawPtr(layoutWrapper));
    bool value = listItemLayoutAlgorithm.IsRTLAndVertical(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(value, true);
}
} // namespace OHOS::Ace::NG
