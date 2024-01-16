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

    Create([=](ListModelNG model) {
        // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
        // FrameNode = 2 * 3
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
        model.SetSpace(Dimension(SPACE));
    });

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(groupFrameNode, nullptr);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);

    groupPattern->headerIndex_ = 1;
    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();
    EXPECT_TRUE(groupPattern->headerIndex_ != 0);
    ASSERT_NE(layoutAl, nullptr);

    /* *
     * @tc.steps: step3. build a object about ListItemGroupLayoutAlgorithm
     */
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    ASSERT_NE(listItemGroupAl, nullptr);
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

    Create([=](ListModelNG model) {
        // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
        // FrameNode = 2 * 3
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
        model.SetSpace(Dimension(SPACE));
    });

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    ASSERT_NE(groupFrameNode, nullptr);
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);

    groupPattern->headerIndex_ = 1;
    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();
    EXPECT_TRUE(groupPattern->headerIndex_ != 0);
    ASSERT_NE(layoutAl, nullptr);

    /* *
     * @tc.steps: step3. build a object about ListItemGroupLayoutAlgorithm
     */
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    ASSERT_NE(listItemGroupAl, nullptr);
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

    Create([=](ListModelNG model) {
        // head + ListItem + SPACE + ListItem + SPACE + ListItem + Foot
        // FrameNode = 2 * 3
        CreateGroupWithSetting(groupNumber, Axis::VERTICAL, V2::ListItemGroupStyle::NONE, itemNumber);
        model.SetSpace(Dimension(SPACE));
    });

    /* *
     * @tc.steps: step2. get child frame node from index
     */
    auto groupFrameNode = GetChildFrameNode(frameNode_, 0);
    EXPECT_NE(groupFrameNode, nullptr);

    /* *
     * @tc.steps: step3. build a object about layoutWraper
     */
    RefPtr<LayoutWrapper> layoutWrapper = groupFrameNode->CreateLayoutWrapper(true, true);
    EXPECT_NE(layoutWrapper, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper_ = AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper);

    // Set LayoutProperty null , CHECK_NULL_VOID eq null
    layoutWrapper_->layoutProperty_ = nullptr;
    const auto &layoutProperty = layoutWrapper->GetLayoutProperty();
    EXPECT_EQ(layoutProperty, nullptr);
    
    /* *
     * @tc.steps: step4. build a object about ListItemGroupLayoutAlgorithm
     */
    auto groupPattern = groupFrameNode->GetPattern<ListItemGroupPattern>();
    ASSERT_NE(groupPattern, nullptr);

    RefPtr<LayoutAlgorithm> layoutAl = groupPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAl, nullptr);

    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupAl = AceType::DynamicCast<ListItemGroupLayoutAlgorithm>(layoutAl);
    ASSERT_NE(listItemGroupAl, nullptr);

    listItemGroupAl->headerIndex_ = -1;
    listItemGroupAl->Layout(AceType::RawPtr<LayoutWrapper>(layoutWrapper));
}
} // namespace OHOS::Ace::NG
