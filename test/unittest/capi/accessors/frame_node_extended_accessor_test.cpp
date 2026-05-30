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
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
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

class FrameNodeAccessorTest : public AccessorTestCtorBase<GENERATED_ArkUIFrameNodeExtenderAccessor,
                                  &GENERATED_ArkUIAccessors::getFrameNodeExtenderAccessor, FrameNodePeer> {
public:
    void* CreatePeerInstance() override
    {
        return accessor_->constructorFrameNode(false);
    }
    void DestroyPeer(FrameNodePeer* peer)
    {
        accessor_->destroyPeer(peer);
    }
};

/**
 * @tc.name: isModifiableTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_isModifiableTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    EXPECT_EQ(ARK_TRUE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: isModifiableTestNull
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, isModifiableTestNull, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = nullptr;
    EXPECT_EQ(ARK_FALSE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: isModifiableTestNotCustomNode
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, isModifiableTestNotCustomNode, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = NG::FrameNode::CreateFrameNode(
        "page", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_EQ(ARK_FALSE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: isModifiableTestNotCustomNode2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_isModifiableTestNotCustomNode2, TestSize.Level1)
{
    ASSERT_NE(accessor_->isModifiable, nullptr);
    peer_->node = NG::FrameNode::CreateFrameNode(
        "CustomFrameNode", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_EQ(ARK_TRUE, accessor_->isModifiable(peer_));
}

/**
 * @tc.name: appendChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_appendChildTest, TestSize.Level1)
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
 * @tc.name: insertChildAfterTestVariant1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_insertChildAfterTestVariant1, TestSize.Level1)
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
 * @tc.name: insertChildAfterTestVariant2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_insertChildAfterTestVariant2, TestSize.Level1)
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
 * @tc.name: insertChildAfterTestVariant3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_insertChildAfterTestVariant3, TestSize.Level1)
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
 * @tc.name: removeChildTestVariant1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_removeChildTestVariant1, TestSize.Level1)
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
 * @tc.name: removeChildTestVariant2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_removeChildTestVariant2, TestSize.Level1)
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
 * @tc.name: clearChildrenTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_clearChildrenTest, TestSize.Level1)
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
 * @tc.name: getChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getChildTest, TestSize.Level1)
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
    auto pos0 = Converter::ArkValue<Ark_Int32>(POS_0);
    auto pos1 = Converter::ArkValue<Ark_Int32>(POS_1);
    auto pos2 = Converter::ArkValue<Ark_Int32>(POS_2);
    auto mode0 = Converter::ArkValue<Ark_Number>(MODE_0);
    auto child0 = static_cast<FrameNodePeer*>(accessor_->getChild(peer_, pos0, &mode0));
    auto child1 = static_cast<FrameNodePeer*>(accessor_->getChild(peer_, pos1, &mode0));
    auto child2 = static_cast<FrameNodePeer*>(accessor_->getChild(peer_, pos2, &mode0));
    ASSERT_NE(child0, nullptr);
    EXPECT_EQ(child0->node, childPeer1->node);
    ASSERT_NE(child1, nullptr);
    EXPECT_EQ(child1->node, childPeer2->node);
    if (child2) {
        EXPECT_EQ(child2->node, nullptr);
    }
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: getFirstChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getFirstChildTest, TestSize.Level1)
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
    auto child = static_cast<FrameNodePeer*>(accessor_->getFirstChild(peer_));
    ASSERT_NE(child, nullptr);
    EXPECT_EQ(child->node, childPeer1->node);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: getNextSiblingTestVariant1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getNextSiblingTestVariant1, TestSize.Level1)
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
    auto next = static_cast<FrameNodePeer*>(accessor_->getNextSibling(peer_));
    ASSERT_NE(next, nullptr);
    EXPECT_EQ(next->node, nextPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: getNextSiblingTestVariant2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getNextSiblingTestVariant2, TestSize.Level1)
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
    auto next = static_cast<FrameNodePeer*>(accessor_->getNextSibling(peer_));
    if (next) {
        EXPECT_EQ(next->node, nullptr);
    }
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: getPreviousSiblingTestVariant1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getPreviousSiblingTestVariant1, TestSize.Level1)
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
    auto prev = static_cast<FrameNodePeer*>(accessor_->getPreviousSibling(peer_));
    ASSERT_NE(prev, nullptr);
    EXPECT_EQ(prev->node, prevPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: getPreviousSiblingTestVariant2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getPreviousSiblingTestVariant2, TestSize.Level1)
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
 * @tc.name: getChildrenCountTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getChildrenCountTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getChildrenCount, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto modeAllExpand = Converter::ArkValue<Ark_Number>(MODE_0);
    EXPECT_EQ(accessor_->getChildrenCount(peer_, &modeAllExpand), CHILD_COUNT_0);
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
    EXPECT_EQ(accessor_->getChildrenCount(peer_, &modeAllExpand), static_cast<Ark_Int32>(childList.size()));
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
    DestroyPeer(childPeer3);
}

/**
 * @tc.name: getParentTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getParentTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getParent, nullptr);
    ASSERT_NE(accessor_->appendChild, nullptr);
    auto parent = static_cast<FrameNodePeer*>(accessor_->getParent(peer_));
    if (parent) {
        EXPECT_EQ(parent->node, nullptr);
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
    parent = static_cast<FrameNodePeer*>(accessor_->getParent(peer_));
    ASSERT_NE(parent, nullptr);
    EXPECT_EQ(parent->node, rootPeer->node);
    DestroyPeer(otherPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: disposeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_disposeTest, TestSize.Level1)
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
 * @tc.name: getOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getOpacityTest, TestSize.Level1)
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
 * @tc.name: getOpacityTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, getOpacityTestInvalid, TestSize.Level1)
{
    ASSERT_NE(accessor_->getOpacity, nullptr);
    auto opacity = Converter::Convert<float>(accessor_->getOpacity(nullptr));
    EXPECT_FLOAT_EQ(opacity, 1.00);
}

/**
 * @tc.name: getPositionToWindowWithTransformTestDefault
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, getPositionToWindowWithTransformTestDefault, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto position = accessor_->getPositionToWindowWithTransform(peer_);
    EXPECT_FLOAT_EQ(position.x, 0.00);
    EXPECT_FLOAT_EQ(position.y, 0.00);
}

/**
 * @tc.name: getPositionToWindowWithTransformTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, DISABLED_getPositionToWindowWithTransformTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto renderCtx = peer_->node->GetRenderContext();
    renderCtx->UpdatePaintRect(RectF(11.f, 22.f, 33.f, 44.f));
    auto position = accessor_->getPositionToWindowWithTransform(peer_);
    EXPECT_FLOAT_EQ(position.x, 11.00);
    EXPECT_FLOAT_EQ(position.y, 22.00);
}

/**
 * @tc.name: getPositionToWindowWithTransformTestInvalid
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, getPositionToWindowWithTransformTestInvalid, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPositionToWindowWithTransform, nullptr);
    auto position = accessor_->getPositionToWindowWithTransform(nullptr);
    EXPECT_FLOAT_EQ(position.x, 0.00);
    EXPECT_FLOAT_EQ(position.y, 0.00);
}

/**
 * @tc.name: reuseTestVariant001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, reuseTestVariant001, TestSize.Level1)
{
    ASSERT_NE(accessor_->reuse, nullptr);
    auto childPeer = CreatePeer();
    auto childList = peer_->node->GetChildren();
    EXPECT_EQ(childList.size(), CHILD_COUNT_0);
    EXPECT_EQ(childPeer->node->GetParentFrameNode(), nullptr);
    accessor_->reuse(peer_);
    DestroyPeer(childPeer);
}

static std::vector<std::tuple<const char *, const char *>> nodeTypeList = {
    { "List", V2::LIST_ETS_TAG },
    { "ListItem", V2::LIST_ITEM_ETS_TAG },
    { "ListItemGroup", V2::LIST_ITEM_GROUP_ETS_TAG },
    { "Scroll", V2::SCROLL_ETS_TAG },
    { "WaterFlow", V2::WATERFLOW_ETS_TAG },
    { "FlowItem", V2::FLOW_ITEM_ETS_TAG },
    { "Grid", V2::GRID_ETS_TAG },
    { "GridItem", V2::GRID_ITEM_ETS_TAG },
    { "Column", V2::COLUMN_ETS_TAG },
    { "Row", V2::ROW_ETS_TAG },
    { "Stack", V2::STACK_ETS_TAG },
    { "Flex", V2::FLEX_ETS_TAG },
    { "RelativeContainer", V2::RELATIVE_CONTAINER_ETS_TAG },
    { "GridRow", V2::GRID_ROW_ETS_TAG },
    { "GridCol", V2::GRID_COL_ETS_TAG },
    { "Divider", V2::DIVIDER_ETS_TAG },
    { "Blank", V2::BLANK_ETS_TAG },
    { "Search", V2::SEARCH_ETS_TAG },
    { "Swiper", V2::SWIPER_ETS_TAG },
    { "TextArea", V2::TEXTAREA_ETS_TAG },
    { "TextInput", V2::TEXTINPUT_ETS_TAG },
    { "Text", V2::TEXT_ETS_TAG },
    { "Marquee", V2::MARQUEE_ETS_TAG },
    { "SymbolGlyph", "SymbolGlyph" },
    { "QRCode", V2::QRCODE_ETS_TAG },
    { "Badge", V2::BADGE_ETS_TAG },
    { "Progress", V2::PROGRESS_ETS_TAG },
    { "LoadingProgress", V2::LOADING_PROGRESS_ETS_TAG },
    { "TextClock", V2::TEXTCLOCK_ETS_TAG },
    { "TextTimer", V2::TEXTTIMER_ETS_TAG },
    { "Image", V2::IMAGE_ETS_TAG },
    { "Button", V2::BUTTON_ETS_TAG },
    { "CheckboxGroup", V2::CHECKBOXGROUP_ETS_TAG },
    { "Checkbox", NG::CHECK_BOX_ETS_TAG }, // V2 tag is Toggle, which is incorrect, so we use NG tag
    { "Radio", V2::RADIO_ETS_TAG },
    { "Rating", V2::RATING_ETS_TAG },
    { "Select", V2::SELECT_ETS_TAG },
    { "Slider", V2::SLIDER_ETS_TAG },
    { "Toggle", V2::TOGGLE_ETS_TAG },

#ifdef XCOMPONENT_SUPPORTED
    { "XComponent", V2::XCOMPONENT_ETS_TAG },
#endif
};

/**
 * @tc.name: createTypedFrameNodeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(FrameNodeAccessorTest, createTypedFrameNodeTest, TestSize.Level1)
{
    for (auto [type, expectedTag]: nodeTypeList) {
        auto inputValue = Converter::ArkValue<Ark_String>(type);
        auto result = static_cast<FrameNodePeer*>(accessor_->createTypedFrameNode(&inputValue, false));
        if (result == nullptr || result->node == nullptr) {
            ADD_FAILURE() << "Node ceation failure. Input type: " << type;
            continue;
        }
        auto resultTag = result->node->GetTag();
        EXPECT_EQ(resultTag, expectedTag) << "Input type: " << type;
        DestroyPeer(result);
    }
}
} // namespace OHOS::Ace::NG