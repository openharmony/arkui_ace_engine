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
#include "core/interfaces/native/implementation/render_node_peer_impl.h"
#include "accessor_test_base.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"
#include "node_api.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "gmock/gmock.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/render_node/render_node_pattern.h"

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

Ark_RenderNode GetRenderNode(Ark_Union_RenderNode_Undefined value)
{
    return value.selector != INTEROP_TAG_UNDEFINED ? value.value0 : nullptr;
}
} // namespace

class RenderNodeAccessorTest
    : public AccessorTestCtorBase<GENERATED_ArkUIRenderNodeAccessor,
        &GENERATED_ArkUIAccessors::getRenderNodeAccessor, RenderNodePeer> {
public:
    void* CreatePeerInstance() override
    {
        return PeerUtils::CreatePeer<RenderNodePeer>();
    }
    void DestroyPeer(RenderNodePeer* peer)
    {
        PeerUtils::DestroyPeer(peer);
    }
};

/**
 * @tc.name: AppendChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, AppendChildTest, TestSize.Level1)
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
HWTEST_F(RenderNodeAccessorTest, InsertChildAfterTest1, TestSize.Level1)
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

    Ark_Union_RenderNode_Undefined siblingUnion;
    TypeHelper::WriteToUnion<Ark_RenderNode>(siblingUnion) = childPeer1;
    accessor_->insertChildAfter(peer_, childPeer3, &siblingUnion);
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
HWTEST_F(RenderNodeAccessorTest, InsertChildAfterTest2, TestSize.Level1)
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
    
    Ark_Union_RenderNode_Undefined siblingUnion;
    TypeHelper::WriteToUnion<Ark_RenderNode>(siblingUnion) = childPeer2;
    accessor_->insertChildAfter(peer_, childPeer3, &siblingUnion);
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
HWTEST_F(RenderNodeAccessorTest, InsertChildAfterTest3, TestSize.Level1)
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

    Ark_Union_RenderNode_Undefined siblingUnion;
    TypeHelper::WriteToUnion<Ark_RenderNode>(siblingUnion) = childPeer1;
    accessor_->insertChildAfter(peer_, childPeer3, &siblingUnion);
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
HWTEST_F(RenderNodeAccessorTest, RemoveChildTest1, TestSize.Level1)
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
HWTEST_F(RenderNodeAccessorTest, RemoveChildTest2, TestSize.Level1)
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
HWTEST_F(RenderNodeAccessorTest, ClearChildrenTest, TestSize.Level1)
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
HWTEST_F(RenderNodeAccessorTest, GetChildTest, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getChild(peer_, &pos0));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, childPeer1->node);

    checkChild = GetRenderNode(accessor_->getChild(peer_, &pos1));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, childPeer2->node);

    checkChild = GetRenderNode(accessor_->getChild(peer_, &pos2));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, nullptr);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: GetFirstChildTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetFirstChildTest, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getFirstChild(peer_));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, childPeer1->node);
    DestroyPeer(childPeer1);
    DestroyPeer(childPeer2);
}

/**
 * @tc.name: GetNextSiblingTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetNextSiblingTest1, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getNextSibling(peer_));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, nextPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetNextSiblingTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetNextSiblingTest2, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getNextSibling(peer_));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, nullptr);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetPreviousSiblingTest1
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetPreviousSiblingTest1, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getPreviousSibling(peer_));
    ASSERT_NE(checkChild, nullptr);
    EXPECT_EQ(checkChild->node, prevPeer->node);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: GetPreviousSiblingTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetPreviousSiblingTest2, TestSize.Level1)
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

    auto checkChild = GetRenderNode(accessor_->getPreviousSibling(peer_));
    EXPECT_EQ(checkChild, nullptr);
    DestroyPeer(nextPeer);
    DestroyPeer(prevPeer);
    DestroyPeer(rootPeer);
}

/**
 * @tc.name: DisposeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DisposeTest, TestSize.Level1)
{
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
 * @tc.name: InvalidateTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DISABLED_InvalidateTest, TestSize.Level1)
{
}

/**
 * @tc.name: GetBackgroundColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetBackgoundColorTest, TestSize.Level1)
{
    // valid value
    ASSERT_NE(accessor_->getBackgroundColor, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetBackgroundColor(fnode, Color::RED);
    auto checkColor = Converter::Convert<int32_t>(accessor_->getBackgroundColor(peer_));
    EXPECT_EQ(checkColor, static_cast<int32_t>(Color::RED.GetValue()));

    // invalid value
    ASSERT_NE(accessor_->getBackgroundColor, nullptr);
    checkColor = Converter::Convert<int32_t>(accessor_->getBackgroundColor(nullptr));
    EXPECT_EQ(checkColor, static_cast<int32_t>(Color::TRANSPARENT.GetValue()));
}

/**
 * @tc.name: SetBackgroundColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetBackgoundColorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setBackgroundColor, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto color = static_cast<int32_t>(Color::RED.GetValue());
    auto arkColor = Converter::ArkValue<Ark_Number>(color);
    accessor_->setBackgroundColor(peer_, &arkColor);
    auto checkColor = static_cast<int32_t>(ViewAbstract::GetBackgroundColor(fnode).GetValue());
    EXPECT_EQ(checkColor, color);
}

/**
 * @tc.name: GetLabelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetLabelTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getLabel, nullptr);
    auto checkLabel = Converter::Convert<std::string>(accessor_->getLabel(peer_));
    EXPECT_EQ(checkLabel, "");

    // invalid value
    checkLabel = Converter::Convert<std::string>(accessor_->getLabel(nullptr));
    EXPECT_EQ(checkLabel, "");

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto pattern = fnode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);
    const std::string label = "Label";
    pattern->SetLabel(label);

    checkLabel = Converter::Convert<std::string>(accessor_->getLabel(peer_));
    EXPECT_EQ(checkLabel, label);
}

/**
 * @tc.name: SetLabelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetLabelTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLabel, nullptr);

    // invalid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto pattern = fnode->GetPattern<NG::RenderNodePattern>();
    CHECK_NULL_VOID(pattern);

    accessor_->setLabel(peer_, nullptr);
    auto checkLabel = pattern->GetLabel();
    EXPECT_EQ(checkLabel, "");

    // valid value
    const std::string label = "Label";
    auto arkLabel = Converter::ArkValue<Ark_String>(label);
    accessor_->setLabel(peer_, &arkLabel);
    checkLabel = pattern->GetLabel();
    EXPECT_EQ(checkLabel, label);
}

/**
 * @tc.name: GetFrameTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetFrameTest, TestSize.Level1)
{
    // invalid value
    ASSERT_NE(accessor_->getFrame, nullptr);
    auto checkFrame = accessor_->getFrame(nullptr);
    auto posX = Converter::Convert<int32_t>(checkFrame.x);
    auto posY = Converter::Convert<int32_t>(checkFrame.y);
    auto width = Converter::Convert<int32_t>(checkFrame.width);
    auto height = Converter::Convert<int32_t>(checkFrame.height);
    EXPECT_EQ(posX, 0);
    EXPECT_EQ(posY, 0);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 0);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    OffsetT<Dimension> offset(Dimension(1, DimensionUnit::VP), Dimension(2, DimensionUnit::VP));
    ViewAbstract::SetPosition(fnode, offset);

    auto layoutProperty = fnode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(3, DimensionUnit::VP), CalcLength(4, DimensionUnit::VP)));

    checkFrame = accessor_->getFrame(peer_);
    posX = Converter::Convert<int32_t>(checkFrame.x);
    posY = Converter::Convert<int32_t>(checkFrame.y);
    width = Converter::Convert<int32_t>(checkFrame.width);
    height = Converter::Convert<int32_t>(checkFrame.height);
    EXPECT_EQ(posX, 1);
    EXPECT_EQ(posY, 2);
    EXPECT_EQ(width, 3);
    EXPECT_EQ(height, 4);
}

/**
 * @tc.name: SetFrameTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetFrameTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setFrame, nullptr);

    Ark_Frame arkFrame = {
        .x = Converter::ArkValue<Ark_Number>(1),
        .y = Converter::ArkValue<Ark_Number>(2),
        .width = Converter::ArkValue<Ark_Number>(3),
        .height = Converter::ArkValue<Ark_Number>(4)
    };
    accessor_->setFrame(peer_, &arkFrame);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto positionValue = ViewAbstract::GetPosition(fnode);
    auto posX = positionValue.GetX().Value();
    auto posY = positionValue.GetY().Value();
    EXPECT_EQ(posX, 1);
    EXPECT_EQ(posY, 2);

    auto layoutProperty = fnode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto calcSizeConv = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    ASSERT_NE(calcSizeConv.has_value(), false);
    auto width = calcSizeConv.value().Width().value().GetDimension().Value();
    auto height = calcSizeConv.value().Height().value().GetDimension().Value();
    EXPECT_EQ(width, 3);
    EXPECT_EQ(height, 4);
}
} // namespace OHOS::Ace::NG