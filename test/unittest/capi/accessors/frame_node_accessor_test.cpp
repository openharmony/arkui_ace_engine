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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "accessor_test_base.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "gmock/gmock.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
const auto POS_INVALID = -1;
const auto POS_0 = 0;
const auto POS_1 = 1;
const auto POS_2 = 2;
const auto CHILD_COUNT_0 = 0;
const auto CHILD_COUNT_1 = 1;
const auto CHILD_COUNT_2 = 2;
const auto CHILD_COUNT_3 = 3;
const Ark_Boolean ARK_FALSE = Converter::ArkValue<Ark_Boolean>(false);
const Ark_Boolean ARK_TRUE = Converter::ArkValue<Ark_Boolean>(true);

} // namespace

class FrameNodeAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIFrameNodeAccessor,
        &GENERATED_ArkUIAccessors::getFrameNodeAccessor, FrameNodePeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->ctor(nullptr);
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
    peer_->node = NG::FrameNode::CreateFrameNode("page",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
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
    peer_->node = NG::FrameNode::CreateFrameNode("CustomFrameNode",
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
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
    auto childPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    Ark_FrameNode arkChild;
    arkChild.ptr = Referenced::RawPtr(childPeer->node);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_0);
    EXPECT_EQ(childPeer->node->GetParentFrameNode(), nullptr);
    accessor_->appendChild(peer_, &arkChild);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    accessor_->insertChildAfter(peer_, &arkChild3, &arkChild1);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    
    accessor_->insertChildAfter(peer_, &arkChild3, &arkChild2);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(childPeer2, &arkChild3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    accessor_->insertChildAfter(peer_, &arkChild3, &arkChild1);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    accessor_->appendChild(peer_, &arkChild3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_2);
    accessor_->removeChild(peer_, &arkChild2);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild3);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_INVALID);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef3), POS_1);
    accessor_->removeChild(peer_, &arkChild2);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    accessor_->appendChild(peer_, &arkChild3);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    Ark_Number pos0 = Converter::ArkValue<Ark_Number>(POS_0);
    Ark_Number pos1 = Converter::ArkValue<Ark_Number>(POS_1);
    Ark_Number pos2 = Converter::ArkValue<Ark_Number>(POS_2);

    EXPECT_EQ(accessor_->getChild(peer_, &pos0), arkChild1.ptr);
    EXPECT_EQ(accessor_->getChild(peer_, &pos1), arkChild2.ptr);
    EXPECT_EQ(accessor_->getChild(peer_, &pos2), nullptr);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_2);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef1), POS_0);
    EXPECT_EQ(currentUINodeRef->GetChildIndex(childUINodeRef2), POS_1);
    EXPECT_EQ(accessor_->getFirstChild(peer_), arkChild1.ptr);
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
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto nextPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);
    Ark_FrameNode arkNext;
    arkNext.ptr = Referenced::RawPtr(nextPeer->node);

    auto prevPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);
    Ark_FrameNode arkPrev;
    arkPrev.ptr = Referenced::RawPtr(prevPeer->node);

    accessor_->appendChild(rootPeer, &arkPrev);
    accessor_->appendChild(rootPeer, &arkCurrent);
    accessor_->appendChild(rootPeer, &arkNext);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getNextSibling(peer_), arkNext.ptr);
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
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto nextPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);
    Ark_FrameNode arkNext;
    arkNext.ptr = Referenced::RawPtr(nextPeer->node);

    auto prevPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);
    Ark_FrameNode arkPrev;
    arkPrev.ptr = Referenced::RawPtr(prevPeer->node);

    accessor_->appendChild(rootPeer, &arkPrev);
    accessor_->appendChild(rootPeer, &arkNext);
    accessor_->appendChild(rootPeer, &arkCurrent);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getNextSibling(peer_), nullptr);
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
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto nextPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);
    Ark_FrameNode arkNext;
    arkNext.ptr = Referenced::RawPtr(nextPeer->node);

    auto prevPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);
    Ark_FrameNode arkPrev;
    arkPrev.ptr = Referenced::RawPtr(prevPeer->node);

    accessor_->appendChild(rootPeer, &arkPrev);
    accessor_->appendChild(rootPeer, &arkCurrent);
    accessor_->appendChild(rootPeer, &arkNext);
    auto childList = rootPeer->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_3);
    EXPECT_EQ(accessor_->getPreviousSibling(peer_), arkPrev.ptr);
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
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto nextPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto nextUINodeRef = AceType::DynamicCast<UINode>(nextPeer->node);
    Ark_FrameNode arkNext;
    arkNext.ptr = Referenced::RawPtr(nextPeer->node);

    auto prevPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto prevUINodeRef = AceType::DynamicCast<UINode>(prevPeer->node);
    Ark_FrameNode arkPrev;
    arkPrev.ptr = Referenced::RawPtr(prevPeer->node);

    accessor_->appendChild(rootPeer, &arkCurrent);
    accessor_->appendChild(rootPeer, &arkPrev);
    accessor_->appendChild(rootPeer, &arkNext);
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

    auto childPeer1 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef1 = AceType::DynamicCast<UINode>(childPeer1->node);
    Ark_FrameNode arkChild1;
    arkChild1.ptr = Referenced::RawPtr(childPeer1->node);

    auto childPeer2 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef2 = AceType::DynamicCast<UINode>(childPeer2->node);
    Ark_FrameNode arkChild2;
    arkChild2.ptr = Referenced::RawPtr(childPeer2->node);

    auto childPeer3 = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto childUINodeRef3 = AceType::DynamicCast<UINode>(childPeer3->node);
    Ark_FrameNode arkChild3;
    arkChild3.ptr = Referenced::RawPtr(childPeer3->node);

    accessor_->appendChild(peer_, &arkChild1);
    accessor_->appendChild(peer_, &arkChild2);
    accessor_->appendChild(peer_, &arkChild3);
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
    EXPECT_EQ(accessor_->getParent(peer_), nullptr);
    EXPECT_EQ(accessor_->getParent(nullptr), nullptr);
    auto invalidPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    invalidPeer->node = nullptr;
    EXPECT_EQ(accessor_->getParent(invalidPeer), nullptr);

    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer_->node);
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto otherPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto otherUINodeRef = AceType::DynamicCast<UINode>(otherPeer->node);
    Ark_FrameNode arkOther;
    arkOther.ptr = Referenced::RawPtr(otherPeer->node);

    accessor_->appendChild(rootPeer, &arkCurrent);
    accessor_->appendChild(rootPeer, &arkOther);
    EXPECT_EQ(accessor_->getParent(peer_), arkRoot.ptr);
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
    Ark_FrameNode arkCurrent;
    arkCurrent.ptr = Referenced::RawPtr(peer_->node);

    auto rootPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto rootUINodeRef = AceType::DynamicCast<UINode>(rootPeer->node);
    Ark_FrameNode arkRoot;
    arkRoot.ptr = Referenced::RawPtr(rootPeer->node);

    auto otherPeer = static_cast<FrameNodePeer*>(CreatePeerInstance());
    auto otherUINodeRef = AceType::DynamicCast<UINode>(otherPeer->node);
    Ark_FrameNode arkOther;
    arkOther.ptr = Referenced::RawPtr(otherPeer->node);

    accessor_->appendChild(rootPeer, &arkCurrent);
    accessor_->appendChild(rootPeer, &arkOther);
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

} // namespace OHOS::Ace::NG