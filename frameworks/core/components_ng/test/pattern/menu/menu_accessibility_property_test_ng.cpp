/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#define private public
#define protected public
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TARGET_ID = 3;
constexpr float CURRENT_OFFSET = -0.5f;
constexpr MenuType TYPE = MenuType::MENU;
} // namespace
class MenuAccessibilityPropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
    void SetUp() override;
    void TearDown() override;
    void InitMenuTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<MenuAccessibilityProperty> menuAccessibilityProperty_;
};

void MenuAccessibilityPropertyTestNg::SetUp() {}

void MenuAccessibilityPropertyTestNg::TearDown()
{
    frameNode_ = nullptr;
    menuAccessibilityProperty_ = nullptr;
}

void MenuAccessibilityPropertyTestNg::InitMenuTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::MENU_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuPattern>(TARGET_ID, TYPE); });
    ASSERT_NE(frameNode_, nullptr);

    menuAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<MenuAccessibilityProperty>();
    ASSERT_NE(menuAccessibilityProperty_, nullptr);
}

/**
 * @tc.name: MenuAccessibilityPropertyIsScrollable001
 * @tc.desc: Test IsScrollable of menuAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAccessibilityPropertyTestNg, MenuAccessibilityPropertyIsScrollable001, TestSize.Level1)
{
    InitMenuTestNg();

    EXPECT_FALSE(menuAccessibilityProperty_->IsScrollable());

    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(frameNode_, 0);
    scroll->MarkModifyDone();
    EXPECT_TRUE(menuAccessibilityProperty_->IsScrollable());
}

/**
 * @tc.name: MenuAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of menuAccessibilityProperty.
 * @tc.type: FUNC
 */
HWTEST_F(MenuAccessibilityPropertyTestNg, MenuAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    InitMenuTestNg();

    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    scrollPattern->SetAxis(Axis::VERTICAL);
    scrollPattern->scrollableDistance_ = 1.0f;
    scrollPattern->currentOffset_ = CURRENT_OFFSET;
    auto scroll =
        FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), scrollPattern);
    ASSERT_NE(scroll, nullptr);
    scroll->MountToParent(frameNode_, 0);

    menuAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = menuAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}
} // namespace OHOS::Ace::NG
