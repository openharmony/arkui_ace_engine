/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "accessor_test_base.h"
#include "gmock/gmock.h"
#include "ui/base/geometry/dimension.h"

#include "base/geometry/dimension_offset.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto POS_INVALID = -1;
const auto POS_0 = 0;
const auto POS_1 = 1;
const auto POS_2 = 2;
const auto MODE_0 = 0;
const auto CHILD_COUNT_0 = 0;
const auto CHILD_COUNT_1 = 1;
const auto CHILD_COUNT_2 = 2;
const auto CHILD_COUNT_3 = 3;
const Ark_Boolean ARK_FALSE = Converter::ArkValue<Ark_Boolean>(false);
const Ark_Boolean ARK_TRUE = Converter::ArkValue<Ark_Boolean>(true);

} // namespace

class FrameNodeAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIFrameNodeAccessor,
                                  &GENERATED_ArkUIAccessors::getFrameNodeAccessor, FrameNodePeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->construct(nullptr);
    }
    void DestroyPeer(FrameNodePeer* peer)
    {
        finalyzer_(peer);
        peer = nullptr;
    }
};

/**
 * @tc.name: IsModifiableTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, IsModifiableTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    EXPECT_EQ(ARK_TRUE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: IsModifiableTestNull
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, IsModifiableTestNull, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = nullptr;
    EXPECT_EQ(ARK_FALSE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: IsModifiableTestNotCustomNode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, IsModifiableTestNotCustomNode, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = NG::FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_EQ(ARK_FALSE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: IsModifiableTestNotCustomNode2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, IsModifiableTestNotCustomNode2, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = NG::FrameNode::CreateFrameNode(
        "CustomFrameNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_EQ(ARK_TRUE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: AppendChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, AppendChildTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto childPeer = CreatePeer();
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_0);
    EXPECT_EQ(childPeer->node->GetParentFrameNode(), nullptr);
    accessor_->appendChild(peer_, childPeer);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    auto childUINodeRef = AceType::DynamicCast<UINode>(childPeer->node);
    EXPECT_EQ(childPeer->node->GetParentFrameNode(), peer_->node);
    EXPECT_EQ(childList.back(), childUINodeRef);
    DestroyPeer(childPeer);
}

/**
 * @tc.name: InsertChildAfterTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, InsertChildAfterTest1, TestSize.Level1)
{
    ASSERT_NE(accessor_->insertChildAfter, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    accessor_->insertChildAfter(peer_, childPeer3, childPeer1);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_2);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: InsertChildAfterTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, InsertChildAfterTest2, TestSize.Level1)
{
    ASSERT_NE(accessor_->insertChildAfter, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);

    accessor_->insertChildAfter(peer_, childPeer3, childPeer2);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: InsertChildAfterTest3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, InsertChildAfterTest3, TestSize.Level1)
{
    ASSERT_NE(accessor_->insertChildAfter, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(childPeer2, childPeer3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    accessor_->insertChildAfter(peer_, childPeer3, childPeer1);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_INVALID);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: RemoveChildTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, RemoveChildTest1, TestSize.Level1)
{
    ASSERT_NE(accessor_->removeChild, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    accessor_->appendChild(peer_, childPeer3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_2);
    accessor_->removeChild(peer_, childPeer2);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: RemoveChildTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, RemoveChildTest2, TestSize.Level1)
{
    ASSERT_NE(accessor_->removeChild, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_1);
    accessor_->removeChild(peer_, childPeer2);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_1);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: ClearChildrenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, ClearChildrenTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->clearChildren, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    accessor_->clearChildren(peer_);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    accessor_->appendChild(peer_, childPeer3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    accessor_->clearChildren(peer_);
    childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_0);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: GetChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetChildTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getChild, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    Ark_Number pos0 = Converter::ArkValue<Ark_Number>(POS_0);
    Ark_Number pos1 = Converter::ArkValue<Ark_Number>(POS_1);
    Ark_Number pos2 = Converter::ArkValue<Ark_Number>(POS_2);
    Ark_Number mode0 = Converter::ArkValue<Ark_Number>(MODE_0);
    EXPECT_EQ(accessor_->getChild(peer_, &pos0, &mode0)->node, childPeer1->node);
    EXPECT_EQ(accessor_->getChild(peer_, &pos1, &mode0)->node, childPeer2->node);
    if (accessor_->getChild(peer_, &pos2, &mode0)) {
        EXPECT_EQ(accessor_->getChild(peer_, &pos2, &mode0)->node, nullptr);
    }
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: GetFirstChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetFirstChildTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getFirstChild, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    EXPECT_EQ(accessor_->getFirstChild(peer_)->node, childPeer1->node);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: GetNextSiblingTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetNextSiblingTest1, TestSize.Level1)
{
    ASSERT_NE(accessor_->getNextSibling, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto nextPeer = CreatePeer();
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);

    auto prevPeer = CreatePeer();
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);

    accessor_->appendChild(rootPeer, prevPeer);
    accessor_->appendChild(rootPeer, peer_);
    accessor_->appendChild(rootPeer, nextPeer);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getNextSibling(peer_)->node, nextPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetNextSiblingTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetNextSiblingTest2, TestSize.Level1)
{
    ASSERT_NE(accessor_->getNextSibling, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto nextPeer = CreatePeer();
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);

    auto prevPeer = CreatePeer();
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);

    accessor_->appendChild(rootPeer, prevPeer);
    accessor_->appendChild(rootPeer, nextPeer);
    accessor_->appendChild(rootPeer, peer_);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    if (accessor_->getNextSibling(peer_)) {
        EXPECT_EQ(accessor_->getNextSibling(peer_)->node, nullptr);
    }
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetPreviousSiblingTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetPreviousSiblingTest1, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviousSibling, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto nextPeer = CreatePeer();
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);

    auto prevPeer = CreatePeer();
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);

    accessor_->appendChild(rootPeer, prevPeer);
    accessor_->appendChild(rootPeer, peer_);
    accessor_->appendChild(rootPeer, nextPeer);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getPreviousSibling(peer_)->node, prevPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetPreviousSiblingTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetPreviousSiblingTest2, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviousSibling, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto nextPeer = CreatePeer();
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);

    auto prevPeer = CreatePeer();
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);

    accessor_->appendChild(rootPeer, peer_);
    accessor_->appendChild(rootPeer, prevPeer);
    accessor_->appendChild(rootPeer, nextPeer);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getPreviousSibling(peer_), nullptr);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetChildrenCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetChildrenCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getChildrenCount, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    EXPECT_EQ(accessor_->getChildrenCount(peer_), 0);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto childPeer1 = CreatePeer();
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);

    auto childPeer2 = CreatePeer();
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);

    auto childPeer3 = CreatePeer();
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);

    accessor_->appendChild(peer_, childPeer1);
    accessor_->appendChild(peer_, childPeer2);
    accessor_->appendChild(peer_, childPeer3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getChildrenCount(peer_), childList.size());
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: GetParentTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetParentTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getParent, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    if (accessor_->getParent(peer_)) {
        EXPECT_EQ(accessor_->getParent(peer_)->node, nullptr);
    }
    EXPECT_EQ(accessor_->getParent(nullptr), nullptr);
    auto invalidPeer = CreatePeer();
    invalidPeer->node = nullptr;
    EXPECT_EQ(accessor_->getParent(invalidPeer), nullptr);

    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto otherPeer = CreatePeer();
    auto otherUINodeRef = AceType::DynamicCast<UINode>(otherPeer->node);

    accessor_->appendChild(rootPeer, peer_);
    accessor_->appendChild(rootPeer, otherPeer);
    if (accessor_->getParent(peer_)) {
        EXPECT_EQ(accessor_->getParent(peer_)->node, rootPeer->node);
    }
    DestroyPeer(otherPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: DisposeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DisposeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getParent, nullptr);
    ASSERT_NE(accessor_->dispose, nullptr);

    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);

    auto rootPeer = CreatePeer();
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);

    auto otherPeer = CreatePeer();
    auto otherUINodeRef = AceType::DynamicCast<UINode>(otherPeer->node);

    accessor_->appendChild(rootPeer, peer_);
    accessor_->appendChild(rootPeer, otherPeer);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(rootUINodeRef->GetChildIndex(currentUINodeRef), POS_0);
    EXPECT_EQ(rootUINodeRef->GetChildIndex(otherUINodeRef), POS_1);

    accessor_->dispose(peer_);
    childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(rootUINodeRef->GetChildIndex(currentUINodeRef), POS_INVALID);
    EXPECT_EQ(rootUINodeRef->GetChildIndex(otherUINodeRef), POS_0);
    DestroyPeer(otherPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetOpacityTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOpacity, nullptr);
    auto opacity = Converter::Convert<float>(accessor_->getOpacity(peer_));
    EXPECT_FLOAT_EQ(opacity, 1.00);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetOpacity(fnode, 0.55f);
    opacity = Converter::Convert<float>(accessor_->getOpacity(peer_));
    EXPECT_FLOAT_EQ(opacity, 0.55);
}

/**
 * @tc.name: GetOpacityInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetOpacityInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOpacity, nullptr);
    auto opacity = Converter::Convert<float>(accessor_->getOpacity(nullptr));
    EXPECT_FLOAT_EQ(opacity, 1.00);
}

/**
 * @tc.name: GetPositionToWindowWithTransformDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetPositionToWindowWithTransformDefaultTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto position =
        Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPositionToWindowWithTransform(peer_));
    EXPECT_EQ(std::get<0>(position).Value(), 0.00);
    EXPECT_EQ(std::get<1>(position).Value(), 0.00);
}

/**
 * @tc.name: GetPositionToWindowWithTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetPositionToWindowWithTransformTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto renderCtx = peer_->node->GetRenderContext();
    renderCtx->UpdatePaintRect(RectF(11.f, 22.f, 33.f, 44.f));
    auto position =
        Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPositionToWindowWithTransform(peer_));
    EXPECT_EQ(std::get<0>(position).Value(), 11.00);
    EXPECT_EQ(std::get<1>(position).Value(), 22.00);
}

/**
 * @tc.name: GetPositionToWindowWithTransformInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, GetPositionToWindowWithTransformInvalidTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto position =
        Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPositionToWindowWithTransform(nullptr));
    EXPECT_EQ(std::get<0>(position).Value(), 0.00);
    EXPECT_EQ(std::get<1>(position).Value(), 0.00);
}

/**
 * @tc.name: ReuseImplTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, ReuseImplTest001, TestSize.Level1)
{
    ASSERT_NE(accessor_->reuse, nullptr);
    auto childPeer = CreatePeer();
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_0);
    EXPECT_EQ(childPeer->node->GetParentFrameNode(), nullptr);
    accessor_->reuse(peer_);
    DestroyPeer(childPeer);
}
} // namespace OHOS::Ace::NG