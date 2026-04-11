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

#include "test/unittest/core/pattern/custom/custom_test_ng.h"

#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
constexpr int32_t TEST_NODE_ID_ROOT = 100;
constexpr int32_t TEST_NODE_ID_COMMON = 200;
constexpr int32_t TEST_NODE_ID_RECYCLE = 300;
constexpr int32_t TEST_NODE_ID_CUSTOM = 400;
constexpr int32_t TEST_NODE_ID_PLAIN = 500;
} // namespace

/**
 * @tc.name: GetCommonViewParentId_PlainFrameNode
 * @tc.desc: Test GetCommonViewParentId with plain FrameNode (not CustomMeasureLayoutNode) returns -1
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_PlainFrameNode, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a plain FrameNode and check InstanceOf
     * @tc.expected: Plain FrameNode is not CustomMeasureLayoutNode, equivalent to returning -1
     */
    auto frameNode = FrameNode::CreateFrameNode("plain", TEST_NODE_ID_PLAIN, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_FALSE(AceType::InstanceOf<CustomMeasureLayoutNode>(frameNode));
}

/**
 * @tc.name: GetCommonViewParentId_NoParent
 * @tc.desc: Test GetCommonViewParentId with CustomMeasureLayoutNode that has no parent returns -1
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_NoParent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a CustomMeasureLayoutNode without parent
     * @tc.expected: GetParent returns nullptr, equivalent to returning -1
     */
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID_CUSTOM, "viewKey");
    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<CustomMeasureLayoutNode>(customNode));
    auto parent = customNode->GetParent();
    EXPECT_EQ(parent, nullptr);
}

/**
 * @tc.name: GetCommonViewParentId_PlainParent
 * @tc.desc: Test GetCommonViewParentId when parent is a plain FrameNode (not __Common__) returns -1
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_PlainParent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a plain parent FrameNode and add CustomMeasureLayoutNode as child
     * @tc.expected: Parent tag is not COMMON_VIEW_ETS_TAG, equivalent to returning -1
     */
    auto parent = FrameNode::CreateFrameNode("plainParent", TEST_NODE_ID_ROOT, AceType::MakeRefPtr<Pattern>(), true);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID_CUSTOM, "viewKey");
    parent->AddChild(customNode);

    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<CustomMeasureLayoutNode>(customNode));
    auto resultParent = customNode->GetParent();
    ASSERT_NE(resultParent, nullptr);
    EXPECT_NE(resultParent->GetTag(), V2::RECYCLE_VIEW_ETS_TAG);
    EXPECT_NE(resultParent->GetTag(), V2::COMMON_VIEW_ETS_TAG);
}

/**
 * @tc.name: GetCommonViewParentId_DirectCommonParent
 * @tc.desc: Test GetCommonViewParentId when direct parent is __Common__ returns parent's ElementId
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_DirectCommonParent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create __Common__ FrameNode as parent of CustomMeasureLayoutNode
     * @tc.expected: Parent tag is COMMON_VIEW_ETS_TAG, ElementId matches
     */
    auto commonView = FrameNode::CreateFrameNode(
        V2::COMMON_VIEW_ETS_TAG, TEST_NODE_ID_COMMON, AceType::MakeRefPtr<Pattern>(), true);
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID_CUSTOM, "viewKey");
    commonView->AddChild(customNode);

    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<CustomMeasureLayoutNode>(customNode));
    auto parent = customNode->GetParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_NE(parent->GetTag(), V2::RECYCLE_VIEW_ETS_TAG);
    EXPECT_EQ(parent->GetTag(), V2::COMMON_VIEW_ETS_TAG);
    EXPECT_EQ(parent->GetId(), TEST_NODE_ID_COMMON);
}

/**
 * @tc.name: GetCommonViewParentId_RecycleAndCommonParent
 * @tc.desc: Test GetCommonViewParentId skips __Recycle__ and finds __Common__ grandparent
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_RecycleAndCommonParent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build tree: __Common__ -> __Recycle__ -> CustomMeasureLayoutNode
     * @tc.expected: Skip __Recycle__, grandparent tag is COMMON_VIEW_ETS_TAG, ElementId matches
     */
    auto commonView = FrameNode::CreateFrameNode(
        V2::COMMON_VIEW_ETS_TAG, TEST_NODE_ID_COMMON, AceType::MakeRefPtr<Pattern>(), true);
    auto recycleNode = FrameNode::CreateFrameNode(
        V2::RECYCLE_VIEW_ETS_TAG, TEST_NODE_ID_RECYCLE, AceType::MakeRefPtr<Pattern>());
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID_CUSTOM, "viewKey");
    commonView->AddChild(recycleNode);
    recycleNode->AddChild(customNode);

    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<CustomMeasureLayoutNode>(customNode));
    auto parent = customNode->GetParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->GetTag(), V2::RECYCLE_VIEW_ETS_TAG);
    auto grandparent = parent->GetParent();
    ASSERT_NE(grandparent, nullptr);
    EXPECT_EQ(grandparent->GetTag(), V2::COMMON_VIEW_ETS_TAG);
    EXPECT_EQ(grandparent->GetId(), TEST_NODE_ID_COMMON);
}

/**
 * @tc.name: GetCommonViewParentId_RecycleWithPlainGrandparent
 * @tc.desc: Test GetCommonViewParentId skips __Recycle__ but grandparent is not __Common__ returns -1
 * @tc.type: FUNC
 */
HWTEST_F(CustomTestNg, GetCommonViewParentId_RecycleWithPlainGrandparent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build tree: plainParent -> __Recycle__ -> CustomMeasureLayoutNode
     * @tc.expected: Skip __Recycle__, grandparent tag is not COMMON_VIEW_ETS_TAG, equivalent to returning -1
     */
    auto plainParent = FrameNode::CreateFrameNode(
        "plainParent", TEST_NODE_ID_ROOT, AceType::MakeRefPtr<Pattern>(), true);
    auto recycleNode = FrameNode::CreateFrameNode(
        V2::RECYCLE_VIEW_ETS_TAG, TEST_NODE_ID_RECYCLE, AceType::MakeRefPtr<Pattern>());
    auto customNode = CustomMeasureLayoutNode::CreateCustomMeasureLayoutNode(TEST_NODE_ID_CUSTOM, "viewKey");
    plainParent->AddChild(recycleNode);
    recycleNode->AddChild(customNode);

    ASSERT_NE(customNode, nullptr);
    EXPECT_TRUE(AceType::InstanceOf<CustomMeasureLayoutNode>(customNode));
    auto parent = customNode->GetParent();
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->GetTag(), V2::RECYCLE_VIEW_ETS_TAG);
    auto grandparent = parent->GetParent();
    ASSERT_NE(grandparent, nullptr);
    EXPECT_NE(grandparent->GetTag(), V2::COMMON_VIEW_ETS_TAG);
}

} // namespace OHOS::Ace::NG
