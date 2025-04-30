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
#include "core/interfaces/native/implementation/shape_clip_peer.h"
#include "core/interfaces/native/implementation/shape_mask_peer.h"
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

/**
 * @tc.name: GetMarkNodeGroupTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetMarkNodeGroupTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getMarkNodeGroup, nullptr);
    auto checkValue = Converter::Convert<bool>(accessor_->getMarkNodeGroup(peer_));
    EXPECT_FALSE(checkValue);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetRenderGroup(fnode, true);
    checkValue = Converter::Convert<bool>(accessor_->getMarkNodeGroup(peer_));
    EXPECT_TRUE(checkValue);

    // invalid value
    checkValue = Converter::Convert<bool>(accessor_->getMarkNodeGroup(nullptr));
    EXPECT_FALSE(checkValue);
}

/**
 * @tc.name: SetMarkNodeGroupTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetMarkNodeGroupTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setMarkNodeGroup, nullptr);
    accessor_->setMarkNodeGroup(peer_, ARK_TRUE);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetRenderGroup(fnode);
    EXPECT_TRUE(checkValue);

    // invalid value
    accessor_->setMarkNodeGroup(nullptr, ARK_FALSE);
    checkValue = ViewAbstract::GetRenderGroup(fnode);
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: GetLengthMetricsUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetLengthMetricsUnitTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getLengthMetricsUnit, nullptr);
    auto checkValue = accessor_->getLengthMetricsUnit(peer_);
    EXPECT_EQ(checkValue, Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_DEFAULT);

    // valid value
    peer_->lengthMetricsUnit = RenderNodePeer::LengthMetricsUnit::PX;
    checkValue = accessor_->getLengthMetricsUnit(peer_);
    EXPECT_EQ(checkValue, Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_PX);

    // invalid value
    checkValue = accessor_->getLengthMetricsUnit(nullptr);
    EXPECT_EQ(checkValue, Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_DEFAULT);
}

/**
 * @tc.name: SetLengthMetricsUnitTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetLengthMetricsUnitTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setLengthMetricsUnit, nullptr);
    accessor_->setLengthMetricsUnit(peer_, Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_PX);
    EXPECT_EQ(peer_->lengthMetricsUnit, RenderNodePeer::LengthMetricsUnit::PX);

    // invalid value
    accessor_->setLengthMetricsUnit(nullptr, Ark_LengthMetricsUnit::ARK_LENGTH_METRICS_UNIT_DEFAULT);
    EXPECT_EQ(peer_->lengthMetricsUnit, RenderNodePeer::LengthMetricsUnit::PX);

    accessor_->setLengthMetricsUnit(peer_, Ark_LengthMetricsUnit(-1));
    EXPECT_EQ(peer_->lengthMetricsUnit, RenderNodePeer::LengthMetricsUnit::DEFAULT);
}

/**
 * @tc.name: GetShapeClipTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DISABLED_GetShapeClipTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getShapeClip, nullptr);
    auto checkValue = accessor_->getShapeClip(peer_);
    EXPECT_NE(checkValue->rect, nullptr);

    // valid value
    auto basicShape = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::BasicShape>();
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetClipShape(fnode, basicShape);
    checkValue = accessor_->getShapeClip(peer_);
    EXPECT_EQ(checkValue->rect, basicShape);

    // invalid value
    checkValue = accessor_->getShapeClip(nullptr);
    EXPECT_EQ(checkValue, nullptr);
}

/**
 * @tc.name: SetShapeClipTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DISABLED_SetShapeClipTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShapeClip, nullptr);

    auto basicShape = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::BasicShape>();
    auto clipPeer = PeerUtils::CreatePeer<ShapeClipPeer>();
    accessor_->setShapeClip(peer_, clipPeer);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetClipShape(fnode);
    EXPECT_EQ(checkValue, basicShape);

    // invalid value
    accessor_->setShapeClip(peer_, nullptr);
    checkValue = ViewAbstract::GetClipShape(fnode);
    EXPECT_EQ(checkValue, basicShape);
}

/**
 * @tc.name: GetShapeMaskTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DISABLED_GetShapeMaskTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getShapeMask, nullptr);
    // default value
    auto checkValue = accessor_->getShapeMask(peer_);
    EXPECT_EQ(checkValue->rect, nullptr);

    // valid value
    auto basicShape = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::BasicShape>();
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetMask(fnode, basicShape);
    checkValue = accessor_->getShapeMask(peer_);
    EXPECT_EQ(checkValue->rect, basicShape);

    // invalid value
    checkValue = accessor_->getShapeMask(nullptr);
    EXPECT_EQ(checkValue, nullptr);
}

/**
 * @tc.name: SetShapeMaskTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, DISABLED_SetShapeMaskTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setShapeMask, nullptr);

    auto basicShape = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::BasicShape>();
    auto clipPeer = PeerUtils::CreatePeer<ShapeMaskPeer>();
    accessor_->setShapeMask(peer_, clipPeer);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetMask(fnode);
    EXPECT_EQ(checkValue, basicShape);

    // invalid value
    accessor_->setShapeMask(peer_, nullptr);
    checkValue = ViewAbstract::GetMask(fnode);
    EXPECT_EQ(checkValue, basicShape);
}

/**
 * @tc.name: GetBorderColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetBorderColorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBorderColor, nullptr);

    Color color(0xffff0000);
    BorderColorProperty borderColors = {
        color, color, color, color, std::nullopt, std::nullopt
    };
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetBorderColor(fnode, borderColors);
    auto checkColor = Converter::Convert<BorderColorProperty>(accessor_->getBorderColor(peer_));
    EXPECT_EQ(checkColor.leftColor.value(), borderColors.leftColor.value());
    EXPECT_EQ(checkColor.rightColor.value(), borderColors.rightColor.value());
    EXPECT_EQ(checkColor.topColor.value(), borderColors.topColor.value());
    EXPECT_EQ(checkColor.bottomColor.value(), borderColors.bottomColor.value());
}

/**
 * @tc.name: SetBorderColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetBorderColorTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setBorderColor, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    Color color(0xffff0000);

    Ark_Edges arkColors = {
        .top = Converter::ArkValue<Opt_Length>(static_cast<float>(color.GetValue())),
        .right = Converter::ArkValue<Opt_Length>(static_cast<float>(color.GetValue())),
        .bottom = Converter::ArkValue<Opt_Length>(static_cast<float>(color.GetValue())),
        .left = Converter::ArkValue<Opt_Length>(static_cast<float>(color.GetValue()))
    };

    accessor_->setBorderColor(peer_, &arkColors);
    auto checkColor = ViewAbstract::GetBorderColor(fnode);
    EXPECT_EQ(checkColor.leftColor.value(), color);
    EXPECT_EQ(checkColor.rightColor.value(), color);
    EXPECT_EQ(checkColor.topColor.value(), color);
    EXPECT_EQ(checkColor.bottomColor.value(), color);
}

/**
 * @tc.name: GetBorderWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetBorderWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBorderWidth, nullptr);

    Dimension dimen(99);
    BorderWidthProperty borderWidths = {
        dimen, dimen, dimen, dimen, std::nullopt, std::nullopt
    };
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetBorderWidth(fnode, borderWidths);
    auto checkWidth = Converter::Convert<BorderWidthProperty>(accessor_->getBorderWidth(peer_));
    EXPECT_EQ(checkWidth.leftDimen.value(), borderWidths.leftDimen.value());
    EXPECT_EQ(checkWidth.rightDimen.value(), borderWidths.rightDimen.value());
    EXPECT_EQ(checkWidth.topDimen.value(), borderWidths.topDimen.value());
    EXPECT_EQ(checkWidth.bottomDimen.value(), borderWidths.bottomDimen.value());
}

/**
 * @tc.name: SetBorderWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetBorderWidthTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setBorderWidth, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    Dimension dimen(99);
    Ark_Edges arkWidths = {
        .top = Converter::ArkValue<Opt_Length>(dimen),
        .right = Converter::ArkValue<Opt_Length>(dimen),
        .bottom = Converter::ArkValue<Opt_Length>(dimen),
        .left = Converter::ArkValue<Opt_Length>(dimen)
    };

    accessor_->setBorderWidth(peer_, &arkWidths);
    auto checkWidth = ViewAbstract::GetBorderWidth(fnode);
    EXPECT_EQ(checkWidth.leftDimen.value(), dimen);
    EXPECT_EQ(checkWidth.rightDimen.value(), dimen);
    EXPECT_EQ(checkWidth.topDimen.value(), dimen);
    EXPECT_EQ(checkWidth.bottomDimen.value(), dimen);
}

/**
 * @tc.name: GetBorderStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetBorderStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBorderStyle, nullptr);

    BorderStyle style = BorderStyle::SOLID;
    BorderStyleProperty borderStyles = {
        style, style, style, style
    };
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetBorderStyle(fnode, borderStyles);
    auto checkStyle = Converter::Convert<BorderStyleProperty>(accessor_->getBorderStyle(peer_));
    EXPECT_EQ(checkStyle.styleLeft.value(), borderStyles.styleLeft.value());
    EXPECT_EQ(checkStyle.styleRight.value(), borderStyles.styleRight.value());
    EXPECT_EQ(checkStyle.styleTop.value(), borderStyles.styleTop.value());
    EXPECT_EQ(checkStyle.styleBottom.value(), borderStyles.styleBottom.value());
}

/**
 * @tc.name: SetBorderStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetBorderStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setBorderStyle, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    Ark_BorderStyle style = Ark_BorderStyle::ARK_BORDER_STYLE_SOLID;
    Ark_EdgeStyles arkStyles = {
        .top = Converter::ArkValue<Opt_BorderStyle>(style),
        .right = Converter::ArkValue<Opt_BorderStyle>(style),
        .bottom = Converter::ArkValue<Opt_BorderStyle>(style),
        .left = Converter::ArkValue<Opt_BorderStyle>(style)
    };

    accessor_->setBorderStyle(peer_, &arkStyles);
    auto checkStyle = ViewAbstract::GetBorderStyle(fnode);
    EXPECT_EQ(checkStyle.styleLeft.value(), Converter::OptConvert<BorderStyle>(style).value());
    EXPECT_EQ(checkStyle.styleRight.value(), Converter::OptConvert<BorderStyle>(style).value());
    EXPECT_EQ(checkStyle.styleTop.value(), Converter::OptConvert<BorderStyle>(style).value());
    EXPECT_EQ(checkStyle.styleBottom.value(), Converter::OptConvert<BorderStyle>(style).value());
    EXPECT_EQ(checkStyle.styleBottom.value(), Converter::OptConvert<BorderStyle>(style).value());
}

/**
 * @tc.name: GetBorderRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetBorderRadiusTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getBorderRadius, nullptr);

    Dimension dimen(9);
    BorderRadiusProperty borderRadiuses = {
        dimen, dimen, dimen, dimen
    };
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetBorderRadius(fnode, borderRadiuses);
    auto checkRadius = Converter::Convert<BorderRadiusProperty>(accessor_->getBorderRadius(peer_));

    EXPECT_EQ(checkRadius.radiusTopLeft.value().Value(), borderRadiuses.radiusTopLeft.value().Value());
    EXPECT_EQ(checkRadius.radiusTopRight.value().Value(), borderRadiuses.radiusTopRight.value().Value());
    EXPECT_EQ(checkRadius.radiusBottomLeft.value().Value(), borderRadiuses.radiusBottomLeft.value().Value());
    EXPECT_EQ(checkRadius.radiusBottomRight.value().Value(), borderRadiuses.radiusBottomRight.value().Value());
}

/**
 * @tc.name: SetBorderRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetBorderRadiusTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setBorderRadius, nullptr);
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);

    auto radius = 9.f;
    Ark_BorderRadiuses_graphics arkRadiuses{
        .topLeft = Converter::ArkValue<Ark_Number>(radius),
        .topRight = Converter::ArkValue<Ark_Number>(radius),
        .bottomLeft = Converter::ArkValue<Ark_Number>(radius),
        .bottomRight = Converter::ArkValue<Ark_Number>(radius),
    };

    accessor_->setBorderRadius(peer_, &arkRadiuses);
    auto checkRadius = ViewAbstract::GetBorderRadius(fnode);
    EXPECT_EQ(checkRadius.radiusTopLeft.value().Value(), radius);
    EXPECT_EQ(checkRadius.radiusTopRight.value().Value(), radius);
    EXPECT_EQ(checkRadius.radiusBottomLeft.value().Value(), radius);
    EXPECT_EQ(checkRadius.radiusBottomRight.value().Value(), radius);
}

/**
 * @tc.name: GetClipToFrameTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetClipToFrameTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getClipToFrame, nullptr);
    auto checkValue = Converter::Convert<bool>(accessor_->getClipToFrame(peer_));
    EXPECT_FALSE(checkValue);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetClipEdge(fnode, true);
    checkValue = Converter::Convert<bool>(accessor_->getClipToFrame(peer_));
    EXPECT_TRUE(checkValue);

    // invalid value
    checkValue = Converter::Convert<bool>(accessor_->getClipToFrame(nullptr));
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: SetClipToFrameTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetClipToFrameTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setClipToFrame, nullptr);
    accessor_->setClipToFrame(peer_, ARK_TRUE);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetClip(fnode);
    EXPECT_TRUE(checkValue);

    // invalid value
    accessor_->setClipToFrame(nullptr, ARK_FALSE);
    checkValue = ViewAbstract::GetClip(fnode);
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: GetOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetOpacityTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getOpacity, nullptr);
    auto checkValue = Converter::Convert<float>(accessor_->getOpacity(peer_));
    EXPECT_EQ(checkValue, 1.000000);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    ViewAbstract::SetOpacity(fnode, 0.5f);
    checkValue = Converter::Convert<float>(accessor_->getOpacity(peer_));
    EXPECT_EQ(checkValue, 0.500000);

    // invalid value
    checkValue = Converter::Convert<float>(accessor_->getOpacity(nullptr));
    EXPECT_EQ(checkValue, 1.000000);
}

/**
 * @tc.name: SetOpacityTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetOpacityTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setOpacity, nullptr);

    auto opacity = Converter::ArkValue<Ark_Number>(0.5f);
    accessor_->setOpacity(peer_, &opacity);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetOpacity(fnode);
    EXPECT_EQ(checkValue, 0.500000);

    // invalid value
    opacity = Converter::ArkValue<Ark_Number>(2.0f);
    accessor_->setOpacity(peer_, &opacity);
    checkValue = ViewAbstract::GetOpacity(fnode);
    EXPECT_EQ(checkValue, 1.000000);

    opacity = Converter::ArkValue<Ark_Number>(-1.0f);
    accessor_->setOpacity(peer_, &opacity);
    checkValue = ViewAbstract::GetOpacity(fnode);
    EXPECT_EQ(checkValue, 0.000000);
}

/**
 * @tc.name: GetSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetSizeTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getSize, nullptr);
    auto checkValue = accessor_->getSize(peer_);
    EXPECT_EQ(Converter::Convert<float>(checkValue.width), 0.000000);
    EXPECT_EQ(Converter::Convert<float>(checkValue.height), 0.000000);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto layoutProperty = fnode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(
        CalcLength(1.f, DimensionUnit::VP), CalcLength(2.f, DimensionUnit::VP)));
    checkValue = accessor_->getSize(peer_);
    EXPECT_EQ(Converter::Convert<float>(checkValue.width), 1.000000);
    EXPECT_EQ(Converter::Convert<float>(checkValue.height), 2.000000);

    // invalid value
    checkValue = accessor_->getSize(nullptr);
    EXPECT_EQ(Converter::Convert<float>(checkValue.width), 0.000000);
    EXPECT_EQ(Converter::Convert<float>(checkValue.height), 0.000000);
}

/**
 * @tc.name: SetSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetSizeTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSize, nullptr);

    Ark_Size size = {
        .width = Converter::ArkValue<Ark_Number>(1.f),
        .height = Converter::ArkValue<Ark_Number>(2.f),
    };
    accessor_->setSize(peer_, &size);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto layoutProperty = fnode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    auto calcSizeConv = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    ASSERT_TRUE(calcSizeConv.has_value());

    auto width = calcSizeConv.value().Width().value_or(CalcLength()).GetDimension();
    auto height = calcSizeConv.value().Height().value_or(CalcLength()).GetDimension();
    EXPECT_EQ(width.Value(), 1.000000);
    EXPECT_EQ(height.Value(), 2.000000);

    // invalid value
    size = {
        .width = Converter::ArkValue<Ark_Number>(-1.f),
        .height = Converter::ArkValue<Ark_Number>(-2.f),
    };
    accessor_->setSize(peer_, &size);

    fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    layoutProperty = fnode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    calcSizeConv = layoutProperty->GetCalcLayoutConstraint()->selfIdealSize;
    ASSERT_TRUE(calcSizeConv.has_value());

    width = calcSizeConv.value().Width().value_or(CalcLength()).GetDimension();
    height = calcSizeConv.value().Height().value_or(CalcLength()).GetDimension();
    EXPECT_EQ(width.Value(), 0.000000);
    EXPECT_EQ(height.Value(), 0.000000);
}

/**
 * @tc.name: GetPositionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, GetPositionTest, TestSize.Level1)
{
    // default value
    ASSERT_NE(accessor_->getPosition, nullptr);
    auto checkValue = Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPosition(peer_));
    EXPECT_EQ(checkValue.first.Value(), 0.000000);
    EXPECT_EQ(checkValue.second.Value(), 0.000000);

    // valid value
    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto offset = OffsetT<Dimension>(Dimension(10, DimensionUnit::VP), Dimension(20, DimensionUnit::VP));
    ViewAbstract::SetPosition(fnode, offset);
    checkValue = Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPosition(peer_));
    EXPECT_EQ(checkValue.first.Value(), 10.000000);
    EXPECT_EQ(checkValue.second.Value(), 20.000000);

    // invalid value
    checkValue = Converter::Convert<std::pair<Dimension, Dimension>>(accessor_->getPosition(nullptr));
    EXPECT_EQ(checkValue.first.Value(), 0.000000);
    EXPECT_EQ(checkValue.second.Value(), 0.000000);
}

/**
 * @tc.name: SetPositionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RenderNodeAccessorTest, SetPositionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setPosition, nullptr);

    Ark_Position position = {
        .x = Converter::ArkValue<Opt_Length>(1.f),
        .y = Converter::ArkValue<Opt_Length>(2.f)
    };
    accessor_->setPosition(peer_, &position);

    auto fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    auto checkValue = ViewAbstract::GetPosition(fnode);
    EXPECT_EQ(checkValue.GetX().Value(), 1.000000);
    EXPECT_EQ(checkValue.GetY().Value(), 2.000000);

    // invalid value
    accessor_->setPosition(peer_, nullptr);
    fnode = Referenced::RawPtr(peer_->node);
    ASSERT_NE(fnode, nullptr);
    checkValue = ViewAbstract::GetPosition(fnode);
    EXPECT_EQ(checkValue.GetX().Value(), 1.000000);
    EXPECT_EQ(checkValue.GetY().Value(), 2.000000);
}
} // namespace OHOS::Ace::NG