/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "test/unittest/core/layout/layout_wrapper_test_ng.h"

namespace OHOS::Ace::NG {

/**
 * @tc.name: LayoutWrapperTest001
 * @tc.desc: Test GetOrCreateChildByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call GetOrCreateChildByIndex and set input index is INDEX_NUM_0.
     * @tc.expected: the return value is null.
     */
    RefPtr<LayoutWrapper> testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_FALSE);
    EXPECT_EQ(testWrapper, nullptr);

    /**
     * @tc.steps: step3. call GetOrCreateChildByIndex and set input index is INDEX_ERROR_NUM.
     * @tc.expected: the return value is null.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_ERROR_NUM, TEST_FALSE);
    EXPECT_EQ(testWrapper, nullptr);

    /**
     * @tc.steps: step4. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step5. call GetOrCreateChildByIndex and set input index is INDEX_NUM_0.
     * @tc.expected: the return value is the same as secondLayoutWrapper.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_FALSE);
    EXPECT_EQ(testWrapper, firstChildLayoutWrapper);

    /**
     * @tc.steps: step6. call GetOrCreateChildByIndex and set input addToRenderTree is TEST_TRUE.
     * @tc.expected: testWrapper->isActive_ is true.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_TRUE);

    EXPECT_TRUE(AceType::DynamicCast<LayoutWrapperNode>(layoutWrapper->GetOrCreateChildByIndex(0))->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest002
 * @tc.desc: Test GetOrCreateChildByIndex.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest002, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call GetOrCreateChildByIndex and set layoutWrapper->currentChildCount_ is CHILD_COUNT.
     * @tc.expected: the return value is null and layoutWrapper->layoutWrapperBuilder_ is null.
     */
    layoutWrapper->currentChildCount_ = CHILD_COUNT;
    RefPtr<LayoutWrapper> testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_FALSE);
    EXPECT_EQ(testWrapper, nullptr);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
     * @tc.steps: step3. create wrapperBuilder and set it to layoutWrapper->layoutWrapperBuilder_.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateLayoutWrapperBuilder();
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call GetOrCreateChildByIndex and set index is INDEX_NUM_0.
     * @tc.expected: the return value is null.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_FALSE);
    EXPECT_EQ(testWrapper, nullptr);

    /**
     * @tc.steps: step5. call GetOrCreateChildByIndex and set layoutWrapperBuilder_->wrapperMap_ is not null.
     * @tc.expected: the return value is not null.
     */
    layoutWrapper->layoutWrapperBuilder_->startIndex_ = -1;
    layoutWrapper->layoutWrapperBuilder_->wrapperMap_ = { { 1, layoutWrapper } };
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_FALSE);
    ASSERT_NE(testWrapper, nullptr);

    /**
     * @tc.steps: step6. call GetOrCreateChildByIndex and set input addToRenderTree is TEST_TRUE.
     * @tc.expected: the return value is not null.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(INDEX_NUM_0, TEST_TRUE);
    EXPECT_TRUE(layoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest003
 * @tc.desc: Test SetCacheCount.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest003, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call SetCacheCount.
     * @tc.expected: layoutWrapperBuilder_->cacheCount_ is 0.
     */
    layoutWrapper->SetCacheCount(CACHE_COUNT);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
     * @tc.steps: step3. create wrapperBuilder and set it to layoutWrapper->layoutWrapperBuilder_.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateLayoutWrapperBuilder();
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call SetCacheCount.
     * @tc.expected: layoutWrapperBuilder_->cacheCount_ is equal to CACHE_COUNT.
     */
    layoutWrapper->SetCacheCount(CACHE_COUNT);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_->cacheCount_, CACHE_COUNT);
}

/**
 * @tc.name: LayoutWrapperTest004
 * @tc.desc: Test GetAllChildrenWithBuild.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest004, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call GetAllChildrenWithBuild.
     * @tc.expected: the return value is empty.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_TRUE(retCachedList.empty());

    /**
     * @tc.steps: step3. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step4. call GetAllChildrenWithBuild.
     * @tc.expected: the return value is not empty.
     */
    retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_TRUE(firstChildLayoutWrapper->isActive_);

    /**
     * @tc.steps: step5. call GetAllChildrenWithBuild again.
     * @tc.expected: the return value is not empty.
     */
    retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_FALSE(retCachedList.empty());
}

/**
 * @tc.name: LayoutWrapperTest005
 * @tc.desc: Test GetAllChildrenWithBuild TEST_TRUE.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest005, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step3. call GetAllChildrenWithBuild and set child->isActive_ is TEST_TRUE.
     * @tc.expected: the return value is not empty.
     */
    firstChildLayoutWrapper->isActive_ = TEST_TRUE;
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_TRUE(firstChildLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest006
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest006, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step3. call GetAllChildrenWithBuild.
     * @tc.expected: the return value is the same as layoutWrapper->children_.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_FALSE);
    EXPECT_EQ(retCachedList, layoutWrapper->cachedList_);
}

/**
 * @tc.name: LayoutWrapperTest007
 * @tc.desc: Test GetAllChildrenWithBuild TEST_FALSE.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest007, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step3. create wrapperBuilder and set it to layoutWrapper->layoutWrapperBuilder_.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateLayoutWrapperBuilder();
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call GetAllChildrenWithBuild and set layoutWrapper->layoutWrapperBuilder_ is not null.
     * @tc.expected: the return value is not empty.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_FALSE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_FALSE(firstChildLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest008
 * @tc.desc: Test RemoveChildInRenderTree.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest008, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);
    EXPECT_FALSE(layoutWrapper->isActive_);

    /**
     * @tc.steps: step3. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step4. call RemoveChildInRenderTree and set input wrapper is secondLayoutWrapper.
     * @tc.expected: firstChildLayoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveChildInRenderTree(firstChildLayoutWrapper);
    EXPECT_FALSE(firstChildLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest009
 * @tc.desc: Test RemoveChildInRenderTree.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest009, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step3. create firstChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    layoutWrapper->AppendChild(firstChildLayoutWrapper);

    /**
     * @tc.steps: step3. call RemoveChildInRenderTree and set input index is NODE_ID_1.
     * @tc.expected: layoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveChildInRenderTree(NODE_ID_1);
    EXPECT_FALSE(firstChildLayoutWrapper->isActive_);

    /**
     * @tc.steps: step4. call RemoveChildInRenderTree and set input index is NODE_ID_0.
     * @tc.expected: the return layoutWrapper->isActive_ is true.
     */
    layoutWrapper->isActive_ = TEST_TRUE;
    layoutWrapper->RemoveChildInRenderTree(NODE_ID_0);
    EXPECT_TRUE(layoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest010
 * @tc.desc: Test RemoveAllChildInRenderTree.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest010, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call RemoveChildInRenderTree.
     * @tc.expected: layoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(layoutWrapper->isActive_);

    /**
     * @tc.steps: step3. create two layoutWrapper and append them to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> firstChildLayoutWrapper = CreateChildLayoutWrapper(FIRST_CHILD_FRAME_NODE, NODE_ID_1);
    RefPtr<LayoutWrapperNode> secondChildLayoutWrapper = CreateChildLayoutWrapper(SECOND_CHILD_FRAME_NODE, NODE_ID_2);

    firstChildLayoutWrapper->isActive_ = TEST_TRUE;
    secondChildLayoutWrapper->isActive_ = TEST_TRUE;

    layoutWrapper->AppendChild(firstChildLayoutWrapper);
    layoutWrapper->AppendChild(secondChildLayoutWrapper);

    /**
     * @tc.steps: step4. call RemoveAllChildInRenderTree.
     * @tc.expected: the firstChildLayoutWrapper->isActive_ and  secondChildLayoutWrapper->isActive_ are false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(firstChildLayoutWrapper->isActive_);
    EXPECT_FALSE(secondChildLayoutWrapper->isActive_);

    /**
     * @tc.steps: step5. create thirdChildLayoutWrapper and append it to layoutWrapper.
     */
    RefPtr<LayoutWrapperNode> thirdChildLayoutWrapper = CreateChildLayoutWrapper(THIRD_CHILD_FRAME_NODE, NODE_ID_3);
    thirdChildLayoutWrapper->isActive_ = TEST_TRUE;
    layoutWrapper->AppendChild(thirdChildLayoutWrapper);

    /**
     * @tc.steps: step6. create wrapperBuilder and set it to layoutWrapper->layoutWrapperBuilder_.
     */
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = CreateLayoutWrapperBuilder();
    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step7. call RemoveChildInRenderTree.
     * @tc.expected: thirdChildLayoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(thirdChildLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest011
 * @tc.desc: Test ResetHostNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest011, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call ResetHostNode.
     * @tc.expected: layoutWrapper->hostNode_.refCounter_ is null.
     */
    layoutWrapper->ResetHostNode();
    EXPECT_EQ(layoutWrapper->hostNode_.refCounter_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest012
 * @tc.desc: Test GetHostNode.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest012, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostNode.
     * @tc.expected: the return value is the same as rowFrameNode.
     */
    RefPtr<FrameNode> hostNode = layoutWrapper->GetHostNode();
    EXPECT_EQ(hostNode, rowFrameNode);
}

/**
 * @tc.name: LayoutWrapperTest013
 * @tc.desc: Test GetHostTag.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest013, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostTag.
     * @tc.expected: the return retHostTag is the same as ROW_FRAME_NODE.
     */
    std::string hostTag = layoutWrapper->GetHostTag();
    EXPECT_EQ(hostTag, ROW_FRAME_NODE);

    /**
     * @tc.steps: step3. call GetHostTag and set hostNode_ is null.
     * @tc.expected: the return value is the same as TEST_TAG.
     */
    layoutWrapper->hostNode_ = nullptr;
    hostTag = layoutWrapper->GetHostTag();
    EXPECT_EQ(hostTag, TEST_TAG);
}

/**
 * @tc.name: LayoutWrapperTest014
 * @tc.desc: Test GetHostDepth.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest014, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostDepth and set hostNode_ is not null.
     * @tc.expected: the return value is equal to HOST_DEPTH.
     */
    int32_t hostDepth = layoutWrapper->GetHostDepth();
    EXPECT_EQ(hostDepth, Infinity<int32_t>());

    /**
     * @tc.steps: step3. call GetHostDepth and set hostNode_ is null.
     * @tc.expected: the return value is equal to ERROR_HOST_DEPTH.
     */
    layoutWrapper->hostNode_ = nullptr;
    hostDepth = layoutWrapper->GetHostDepth();
    EXPECT_EQ(hostDepth, ERROR_HOST_DEPTH);
}

/**
 * @tc.name: LayoutWrapperTest015
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest015, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->layoutProperty_ is null.
     */
    layoutWrapper->layoutProperty_ = nullptr;
    layoutWrapper->Measure(parentLayoutConstraint);

    /**
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    FRAME_SIZE.width_ = layoutWrapper->geometryNode_->GetFrameSize().Width();
    FRAME_SIZE.height_ = layoutWrapper->geometryNode_->GetFrameSize().Height();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest016
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest016, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->geometryNode_ is null.
     * @tc.expected: layoutWrapper->geometryNode_ is null.
     */
    layoutWrapper->geometryNode_ = nullptr;
    layoutWrapper->Measure(parentLayoutConstraint);
    EXPECT_EQ(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest017
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest017, TestSize.Level0)
{
    /**
     * @tc.steps: step1. call CreateLayoutWrapper create a layoutwrapper pointer.
     */
    RefPtr<LayoutWrapperNode> layoutWrapper = CreateLayoutWrapper(ROW_FRAME_NODE, NODE_ID_0);

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->hostNode_ is null.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->hostNode_ = nullptr;
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest018
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest018, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->layoutAlgorithm_ is null.
     * @tc.expected: FRAME_SIZE is the same as TEST_FRAME_SIZE.
     */
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE, TEST_FRAME_SIZE);
}

/**
 * @tc.name: LayoutWrapperTest019
 * @tc.desc: Test Measure.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest019, TestSize.Level0)
{
    /**
     * @tc.steps: step1. create layoutwrapper.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, NODE_ID_0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
     */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call UpdateParentConstraint update parentLayoutConstraint.
     */
    LayoutConstraintF parentLayoutConstraint;
    UpdateParentConstraint(layoutWrapper, parentLayoutConstraint);

    /**
     * @tc.steps: step4. call Measure and set layoutProperty_->geometryTransition_ is not null.
     * @tc.expected: FRAME_SIZE.width_ is RK356_WIDTH and FRAME_SIZE.height_ is ROW_HEIGHT.
     */
    layoutWrapper->GetLayoutProperty()->geometryTransition_ =
        AceType::MakeRefPtr<GeometryTransition>("test", rowFrameNode);
    layoutWrapper->Measure(parentLayoutConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, ROW_HEIGHT);
}

}