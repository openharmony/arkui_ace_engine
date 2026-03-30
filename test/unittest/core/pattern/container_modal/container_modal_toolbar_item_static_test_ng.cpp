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

#include "gtest/gtest.h"

#include "core/components_ng/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_model_static.h"
#include "core/components_ng/pattern/toolbaritem/toolbaritem_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ContainerModalToolbarItemStaticTestNg : public testing::Test {};

/**
 * @tc.name: ToolBarItemModelStaticCreateFrameNode001
 * @tc.desc: Verify CreateFrameNode creates toolbar item node with ToolBarItemPattern.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalToolbarItemStaticTestNg, ToolBarItemModelStaticCreateFrameNode001, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode = ToolBarItemModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetTag(), V2::TOOLBARITEM_ETS_TAG);
    EXPECT_NE(frameNode->GetPattern<ToolBarItemPattern>(), nullptr);
}

/**
 * @tc.name: ToolBarItemModelStaticCreateFrameNode002
 * @tc.desc: Verify CreateFrameNode returns the same frame node when node id is reused.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalToolbarItemStaticTestNg, ToolBarItemModelStaticCreateFrameNode002, TestSize.Level1)
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto firstNode = ToolBarItemModelStatic::CreateFrameNode(nodeId);
    auto secondNode = ToolBarItemModelStatic::CreateFrameNode(nodeId);
    ASSERT_NE(firstNode, nullptr);
    ASSERT_NE(secondNode, nullptr);
    EXPECT_EQ(firstNode, secondNode);
}

/**
 * @tc.name: ToolBarItemModelStaticSetPlacement001
 * @tc.desc: Verify SetPlacement updates ToolBarItemPattern placement.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalToolbarItemStaticTestNg, ToolBarItemModelStaticSetPlacement001, TestSize.Level1)
{
    auto frameNode = ToolBarItemModelStatic::CreateFrameNode(ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ToolBarItemPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_EQ(pattern->GetPlacement(), 0);

    constexpr int32_t placement = 3;
    ToolBarItemModelStatic::SetPlacement(AceType::RawPtr(frameNode), placement);
    EXPECT_EQ(pattern->GetPlacement(), placement);
}

/**
 * @tc.name: ToolBarItemModelStaticSetPlacement002
 * @tc.desc: Verify SetPlacement handles null frame node safely.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalToolbarItemStaticTestNg, ToolBarItemModelStaticSetPlacement002, TestSize.Level1)
{
    ToolBarItemModelStatic::SetPlacement(nullptr, 1);
    SUCCEED();
}

/**
 * @tc.name: ToolBarItemModelStaticSetPlacement003
 * @tc.desc: Verify SetPlacement handles non-ToolBarItemPattern frame node safely.
 * @tc.type: FUNC
 */
HWTEST_F(ContainerModalToolbarItemStaticTestNg, ToolBarItemModelStaticSetPlacement003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("NonToolbarItem", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->GetPattern<ToolBarItemPattern>(), nullptr);

    ToolBarItemModelStatic::SetPlacement(AceType::RawPtr(frameNode), 2);
    EXPECT_EQ(frameNode->GetPattern<ToolBarItemPattern>(), nullptr);
}
} // namespace OHOS::Ace::NG

