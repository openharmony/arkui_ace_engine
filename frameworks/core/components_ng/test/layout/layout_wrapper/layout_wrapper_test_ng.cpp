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

#include "gtest/gtest.h"

#include <algorithm>

#define protected public
#define private public

#include "base/log/ace_trace.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/flex/flex_layout_algorithm.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/syntax/lazy_layout_wrapper_builder.h"
#include "core/components_ng/syntax/lazy_for_each_model.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID = 1;
constexpr int32_t SECOND_NODE_ID = 2;
constexpr int32_t THIRD_NODE_ID = 3;

constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float ROW_HEIGHT = 120.0f;

const SizeF CONTAINER_SIZE {RK356_WIDTH, RK356_HEIGHT};
SizeF FRAME_SIZE {0, 0};
OptionalSize SELF_IDEAL_SIZE {0, 0};

const std::string TEST_TAG = "";
const std::string ROW_FRAME_NODE = "rowFrameNode";
const std::string FIRST_FRAME_NODE = "TabContent";
const std::string SECOND_FRAME_NODE = "secondFrameNode";
const std::string THIRD_FRAME_NODE = "thirdFrameNode";

constexpr bool TEST_TRUE = true;
constexpr bool TEST_FALSE = false;
}
class LayoutWrapperTestNg : public testing::Test {};

/**
 * @tc.name: LayoutWrapperTest001
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. call GetOrCreateChildByIndex and set input index is 0.
    * @tc.expected: the return testWrapper is null.
    */
    RefPtr<LayoutWrapper> testWrapper = layoutWrapper->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(testWrapper, nullptr);

    /**
     * @tc.steps: step3. call GetOrCreateChildByIndex and set input index is -1.
     * @tc.expected: step3. the return value is null.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(-1, false);
    EXPECT_EQ(testWrapper, nullptr);

    /**
     * @tc.steps: step4. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step5. call GetOrCreateChildByIndex and set input index is 0.
     * @tc.expected: the return testWrapper is the same as secondLayoutWrapper.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(testWrapper, secondLayoutWrapper);

    /**
     * @tc.steps: step6. call GetOrCreateChildByIndex and set input addToRenderTree is true.
     * @tc.expected: the return testWrapper->isActive_ is true.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(0, true);
    EXPECT_TRUE(testWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest002
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetOrCreateChildByIndex and set layoutWrapper->currentChildCount_ is 1.
     * @tc.expected: the return testWrapper is nullptr and layoutWrapper->layoutWrapperBuilder_ is null.
     */
    layoutWrapper->currentChildCount_ = 1;
    RefPtr<LayoutWrapper> testWrapper = layoutWrapper->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(testWrapper, nullptr);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
     * @tc.steps: step3. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call GetOrCreateChildByIndex.
     * @tc.expected: the return testWrapper is null.
     */
    testWrapper = layoutWrapper->GetOrCreateChildByIndex(0, false);
    EXPECT_EQ(testWrapper, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest003
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call SetCacheCount.
     * @tc.expected: layoutWrapperBuilder_->cacheCount_ is 0.
     */
    layoutWrapper->SetCacheCount(1);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
     * @tc.steps: step3. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call SetCacheCount and set layoutWrapper->layoutWrapperBuilder_ is not null.
     * @tc.expected: layoutWrapperBuilder_->cacheCount_ is 1.
     */
    layoutWrapper->SetCacheCount(1);
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_->cacheCount_, 1);
}

/**
 * @tc.name: LayoutWrapperTest004
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetAllChildrenWithBuild.
     * @tc.expected: the return retCachedList is empty.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_TRUE(retCachedList.empty());

    /**
     * @tc.steps: step3. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step4. call GetAllChildrenWithBuild.
     * @tc.expected: the return retCachedList is not empty.
     */
    retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_TRUE(secondLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest005
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call GetAllChildrenWithBuild and set child->isActive_ is true.
     * @tc.expected: the return retCachedList is not empty.
     */
    secondLayoutWrapper->isActive_ = TEST_TRUE;
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_TRUE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_TRUE(secondLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest006
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call GetAllChildrenWithBuild.
     * @tc.expected: the return retCachedList is the same as layoutWrapper->children_.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_FALSE);
    EXPECT_EQ(retCachedList, layoutWrapper->children_);
}

/**
 * @tc.name: LayoutWrapperTest007
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call RemoveChildInRenderTree and set input is null.
     * @tc.expected: layoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveChildInRenderTree(nullptr);
    EXPECT_FALSE(layoutWrapper->isActive_);

    /**
     * @tc.steps: step3. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step4. call RemoveChildInRenderTree and set input is secondLayoutWrapper.
     * @tc.expected: secondLayoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveChildInRenderTree(secondLayoutWrapper);
    EXPECT_FALSE(secondLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest008
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call RemoveChildInRenderTree and set input is SECOND_NODE_ID.
     * @tc.expected: layoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveChildInRenderTree(SECOND_NODE_ID);
    EXPECT_FALSE(secondLayoutWrapper->isActive_);

    /**
     * @tc.steps: step4. call RemoveChildInRenderTree and set input is 0.
     * @tc.expected: the return layoutWrapper->isActive_ is true.
     */
    layoutWrapper->isActive_ = TEST_TRUE;
    layoutWrapper->RemoveChildInRenderTree(0);
    EXPECT_TRUE(layoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest009
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call RemoveChildInRenderTree.
     * @tc.expected: layoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(layoutWrapper->isActive_);

    /**
     * @tc.steps: step3. append two child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    auto thirdFrameNode =
        FrameNode::CreateFrameNode(THIRD_FRAME_NODE, THIRD_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> thirdGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> thirdLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(thirdFrameNode, thirdGeometryNode, thirdFrameNode->GetLayoutProperty());

    secondLayoutWrapper->isActive_ = TEST_TRUE;
    thirdLayoutWrapper->isActive_ = TEST_TRUE;

    layoutWrapper->AppendChild(secondLayoutWrapper);
    layoutWrapper->AppendChild(thirdLayoutWrapper);

    /**
     * @tc.steps: step4. call RemoveAllChildInRenderTree.
     * @tc.expected: the secondLayoutWrapper->isActive_ is false and the thirdLayoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(secondLayoutWrapper->isActive_);
    EXPECT_FALSE(thirdLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest010
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call ResetHostNode.
     * @tc.expected: layoutWrapper->hostNode_.refCounter_ is null.
     */
    layoutWrapper->ResetHostNode();
    EXPECT_EQ(layoutWrapper->hostNode_.refCounter_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest011
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest011, TestSize.Level1)
{
     /**
     * @tc.steps: step1. create a layoutwrapper pointer.
     */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostNode.
     * @tc.expected: the return retHostNode is the same as rowFrameNode.
     */
    RefPtr<FrameNode> retHostNode = layoutWrapper->GetHostNode();
    EXPECT_EQ(retHostNode, rowFrameNode);

    /**
     * @tc.steps: step3. call GetWeakHostNode.
     * @tc.expected: the return retWeakHostNode is the same as rowFrameNode.
     */
    WeakPtr<FrameNode> retWeakHostNode = layoutWrapper->GetWeakHostNode();
    EXPECT_EQ(retWeakHostNode, rowFrameNode);
}

/**
 * @tc.name: LayoutWrapperTest012
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest012, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostTag.
     * @tc.expected: the return retHostTag is the same as ROW_FRAME_NODE.
     */
    std::string retHostTag = layoutWrapper->GetHostTag();
    EXPECT_EQ(retHostTag, ROW_FRAME_NODE);

    /**
     * @tc.steps: step3. call GetHostTag and set hostNode_ is null.
     * @tc.expected: the return retHostTag is the same as TEST_TAG.
     */
    layoutWrapper->hostNode_ = nullptr;
    retHostTag = layoutWrapper->GetHostTag();
    EXPECT_EQ(retHostTag, TEST_TAG);
}

/**
 * @tc.name: LayoutWrapperTest013
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest013, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetHostDepth.
     * @tc.expected: the return retHostDepth is 0.
     */
    int32_t retHostDepth = layoutWrapper->GetHostDepth();
    EXPECT_EQ(retHostDepth, 0);

    /**
     * @tc.steps: step3. call GetHostDepth and set hostNode_ is null.
     * @tc.expected: the return retHostDepth is -1.
     */
    layoutWrapper->hostNode_ = nullptr;
    retHostDepth = layoutWrapper->GetHostDepth();
    EXPECT_EQ(retHostDepth, -1);
}

/**
 * @tc.name: LayoutWrapperTest014
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest014, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->layoutProperty_ is null.
     */
    layoutWrapper->layoutProperty_ = nullptr;
    layoutWrapper->Measure(parentConstraint);

    /**
    * @tc.expected: FRAME_SIZE.Width() is 0 and FRAME_SIZE.Height() is 0.
    */
    FRAME_SIZE.width_= layoutWrapper->geometryNode_->GetFrameSize().Width();
    FRAME_SIZE.height_ = layoutWrapper->geometryNode_->GetFrameSize().Height();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest015
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest015, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->geometryNode_ is null.
     * @tc.expected: layoutWrapper->geometryNode_ is null.
     */
    layoutWrapper->geometryNode_ = nullptr;
    layoutWrapper->Measure(parentConstraint);
    EXPECT_EQ(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest016
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest016, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->hostNode_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->hostNode_ = nullptr;
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest017
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest017, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->layoutAlgorithm_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest018
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest018, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutProperty_->geometryTransition_ is not null.
     * @tc.expected: FRAME_SIZE.width_ is RK356_WIDTH and FRAME_SIZE.height_ is ROW_HEIGHT.
     */
    layoutWrapper->GetLayoutProperty()->geometryTransition_ = AceType::MakeRefPtr<GeometryTransition>(rowFrameNode);
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, ROW_HEIGHT);
}

/**
 * @tc.name: LayoutWrapperTest019
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest019, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutAlgorithm_->skipMeasure_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->layoutAlgorithm_->skipMeasure_ = TEST_TRUE;
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest020
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest020, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure.
     * @tc.expected: FRAME_SIZE.Width() is RK356_WIDTH and FRAME_SIZE.Height() is ROW_HEIGHT.
     */
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, ROW_HEIGHT);

    /**
    * @tc.steps: step4. UpdateAspectRatio and UpdateLayoutWeight.
    */
    MagicItemProperty magicItemProperty;
    magicItemProperty.UpdateAspectRatio(0.5);
    magicItemProperty.UpdateLayoutWeight(0.5);

    layoutWrapper->layoutProperty_->magicItemProperty_ = std::make_unique<MagicItemProperty>(magicItemProperty);

    /**
     * @tc.steps: step5. call Measure.
     * @tc.expected: FRAME_SIZE.Height() is twice as much RK356_WIDTH.
     */
    layoutWrapper->Measure(parentConstraint);
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(FRAME_SIZE.height_, RK356_WIDTH * 2);

    /**
     * @tc.steps: step6. call Measure and set layoutProperty_->calcLayoutConstraint_is not null.
     * @tc.expected: SELF_IDEAL_SIZE.Height() is twice as much RK356_WIDTH.
     */
    layoutWrapper->layoutProperty_->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    layoutWrapper->Measure(parentConstraint);
    SELF_IDEAL_SIZE.width_ = layoutWrapper->geometryNode_->parentLayoutConstraint_->selfIdealSize.Width();
    SELF_IDEAL_SIZE.height_ = layoutWrapper->geometryNode_->parentLayoutConstraint_->selfIdealSize.Height();
    EXPECT_EQ(SELF_IDEAL_SIZE.width_, RK356_WIDTH);
    EXPECT_EQ(SELF_IDEAL_SIZE.height_, RK356_WIDTH * 2);
}

/**
 * @tc.name: LayoutWrapperTest021
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest021, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Measure and set layoutWrapper->needForceMeasureAndLayout_ is TEST_FALSE.
     * @tc.expected: layoutWrapper->skipMeasureContent_ is true.
     */
    layoutWrapper->needForceMeasureAndLayout_ = std::make_optional(TEST_FALSE);
    layoutWrapper->Measure(parentConstraint);
    EXPECT_TRUE(layoutWrapper->skipMeasureContent_);
}

/**
 * @tc.name: LayoutWrapperTest022
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest022, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update the layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->layoutProperty_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->layoutProperty_ = nullptr;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest023
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest023, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update the layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->geometryNode_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->geometryNode_ = nullptr;
    layoutWrapper->Layout();
    EXPECT_EQ(layoutWrapper->geometryNode_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest024
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest024, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update the layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->hostNode_ is null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->hostNode_ = nullptr;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest025
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest025, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. update the layoutProperty_->layoutConstraint_.
    */
    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->layoutAlgorithm_ is not null.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest026
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest026, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->layoutAlgorithm_->skipLayout_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->layoutAlgorithm_->skipLayout_ = TEST_TRUE;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest027
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest027, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->skipMeasureContent_ is default value.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);

    /**
     * @tc.steps: step4. call Layout and set layoutWrapper->skipMeasureContent_ is TEST_TRUE.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->skipMeasureContent_ = TEST_TRUE;
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest028
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest028, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null and update layoutProperty_->layoutConstraint_.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = CONTAINER_SIZE;
    parentConstraint.percentReference = CONTAINER_SIZE;
    parentConstraint.selfIdealSize.SetSize(SizeF(RK356_WIDTH, ROW_HEIGHT));

    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentConstraint);

    /**
     * @tc.steps: step3. call Layout and set layoutWrapper->skipMeasureContent_ is default value.
     * @tc.expected: FRAME_SIZE is the default value.
     */
    layoutWrapper->Layout();
    FRAME_SIZE = layoutWrapper->geometryNode_->GetFrameSize();
    EXPECT_EQ(FRAME_SIZE.width_, 0);
    EXPECT_EQ(FRAME_SIZE.height_, 0);
}

/**
 * @tc.name: LayoutWrapperTest029
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest029, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->layoutAlgorithm_ is not null.
    */
    auto rowLayoutPattern = rowFrameNode->GetPattern<LinearLayoutPattern>();
    auto rowLayoutAlgorithm = rowLayoutPattern->CreateLayoutAlgorithm();

    layoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));

    /**
     * @tc.steps: step3. call SkipMeasureContent.
     * @tc.expected: the return retSkipMeasureContent is false.
     */
    bool retSkipMeasureContent = layoutWrapper->SkipMeasureContent();
    EXPECT_FALSE(retSkipMeasureContent);

    /**
     * @tc.steps: step4. call SkipMeasureContent and set layoutWrapper->skipMeasureContent_ is true.
     * @tc.expected: the return retSkipMeasureContent is true.
     */
    layoutWrapper->skipMeasureContent_ = std::make_optional(TEST_TRUE);
    retSkipMeasureContent = layoutWrapper->SkipMeasureContent();
    EXPECT_TRUE(retSkipMeasureContent);
}

/**
 * @tc.name: LayoutWrapperTest030
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest030, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call CheckNeedForceMeasureAndLayout.
     * @tc.expected: the return retCheck is true.
     */
    bool retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);

    /**
     * @tc.steps: step3. call CheckNeedForceMeasureAndLayout again.
     * @tc.expected: the return retCheck is true.
     */
    retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest031
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest031, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call CheckNeedForceMeasureAndLayout again.
     * @tc.expected: the return retCheck is false.
     */
    layoutWrapper->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    bool retCheck = layoutWrapper->CheckNeedForceMeasureAndLayout();
    EXPECT_FALSE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest032
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest032, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call CheckChildNeedForceMeasureAndLayout.
     * @tc.expected: the return retCheck is true.
     */
    bool retCheck = layoutWrapper->CheckChildNeedForceMeasureAndLayout();
    EXPECT_TRUE(retCheck);
}

/**
 * @tc.name: LayoutWrapperTest033
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest033, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call MountToHostOnMainThread.
     * @tc.expected: layoutWrapper->layoutWrapperBuilder_ is null.
     */
    layoutWrapper->MountToHostOnMainThread();
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
    * @tc.steps: step3. create a testLayoutWrapper pointer and set tag is "TabContent".
    */
    auto firstFrameNode =
        FrameNode::CreateFrameNode(FIRST_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<LayoutWrapper> testLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(firstFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step4. call MountToHostOnMainThread.
     * @tc.expected: testLayoutWrapper->layoutWrapperBuilder is null.
     */
    testLayoutWrapper->MountToHostOnMainThread();
    EXPECT_EQ(testLayoutWrapper->layoutWrapperBuilder_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest034
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest034, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call MountToHostOnMainThread.
     * @tc.expected: layoutWrapper->layoutWrapperBuilder_ is null.
     */
    layoutWrapper->MountToHostOnMainThread();
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest035
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest035, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. set secondLayoutWrapper->hostNode_ is null and append secondLayoutWrapper to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    secondLayoutWrapper->hostNode_ = nullptr;
    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. call MountToHostOnMainThread.
     * @tc.expected: layoutWrapper->layoutWrapperBuilder_ is null.
     */
    layoutWrapper->MountToHostOnMainThread();
    EXPECT_EQ(layoutWrapper->layoutWrapperBuilder_, nullptr);

    /**
     * @tc.steps: step4. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step5. call MountToHostOnMainThread.
     * @tc.expected: layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    layoutWrapper->MountToHostOnMainThread();
    ASSERT_NE(layoutWrapper->layoutWrapperBuilder_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest036
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest036, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
    * @tc.steps: step2. set layoutWrapper->lazyBuildFunction_ is not null.
    */
    auto lazyBuildFunction = [] (RefPtr<LayoutWrapper> testLayoutWrapper) {
        testLayoutWrapper = nullptr;
    };
    layoutWrapper->lazyBuildFunction_ = lazyBuildFunction;

    /**
     * @tc.steps: step3. call GetLazyBuildRange.
     * @tc.expected: the return retRange.first is -1 and retRange.second is 0.
     */
    layoutWrapper->BuildLazyItem();
    EXPECT_EQ(layoutWrapper->lazyBuildFunction_, nullptr);
}

/**
 * @tc.name: LayoutWrapperTest037
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest037, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. call GetLazyBuildRange.
     * @tc.expected: the return retRange.first is -1 and retRange.second is 0.
     */
    std::pair<int32_t, int32_t> retRange = layoutWrapper->GetLazyBuildRange();
    EXPECT_EQ(retRange.first, -1);
    EXPECT_EQ(retRange.second, 0);

    /**
     * @tc.steps: step4. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step5. call GetLazyBuildRange.
     * @tc.expected: the return retRange.first is 0 and retRange.second is 0.
     */
    retRange = layoutWrapper->GetLazyBuildRange();
    EXPECT_EQ(retRange.first, 0);
    EXPECT_EQ(retRange.second, 0);
}

/**
 * @tc.name: LayoutWrapperTest038
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest038, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call GetAllChildrenWithBuild and set layoutWrapper->layoutWrapperBuilder_ is not null.
     * @tc.expected: the return retCachedList is not empty.
     */
    std::list<RefPtr<LayoutWrapper>> retCachedList = layoutWrapper->GetAllChildrenWithBuild(TEST_FALSE);
    EXPECT_FALSE(retCachedList.empty());
    EXPECT_FALSE(secondLayoutWrapper->isActive_);
}

/**
 * @tc.name: LayoutWrapperTest039
 * @tc.desc: Test the operation of layout_wrapper.
 * @tc.type: FUNC
 */
HWTEST_F(LayoutWrapperTestNg, LayoutWrapperTest039, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create a layoutwrapper pointer.
    */
    auto rowFrameNode =
        FrameNode::CreateFrameNode(ROW_FRAME_NODE, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(rowFrameNode, geometryNode, rowFrameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. append a child to layoutWrapper.
     */
    auto secondFrameNode =
        FrameNode::CreateFrameNode(SECOND_FRAME_NODE, SECOND_NODE_ID, AceType::MakeRefPtr<Pattern>());
    RefPtr<GeometryNode> secondGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> secondLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(secondFrameNode, secondGeometryNode, secondFrameNode->GetLayoutProperty());

    secondLayoutWrapper->isActive_ = TEST_TRUE;
    layoutWrapper->AppendChild(secondLayoutWrapper);

    /**
     * @tc.steps: step3. set layoutWrapper->layoutWrapperBuilder_ is not null.
     */
    RefPtr<LazyForEachActuator> actuator = AceType::MakeRefPtr<LazyForEachActuator>();
    auto builder = AceType::DynamicCast<LazyForEachBuilder>(actuator);
    RefPtr<LazyForEachNode> host_ = AceType::MakeRefPtr<LazyForEachNode>(NODE_ID, builder);
    WeakPtr<LazyForEachNode> host(host_);
    RefPtr<LazyLayoutWrapperBuilder> wrapperBuilder = AceType::MakeRefPtr<LazyLayoutWrapperBuilder>(builder, host);

    layoutWrapper->layoutWrapperBuilder_ = wrapperBuilder;

    /**
     * @tc.steps: step4. call RemoveChildInRenderTree.
     * @tc.expected: secondLayoutWrapper->isActive_ is false.
     */
    layoutWrapper->RemoveAllChildInRenderTree();
    EXPECT_FALSE(secondLayoutWrapper->isActive_);
}
} // namespace OHOS::Ace::NG
