/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <cstdint>
#include <memory>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class SelectOverlayTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SelectOverlayTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
}

void SelectOverlayTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

/**
 * @tc.name: SelectFrameNodeCreator001
 * @tc.desc: Test CreateSelectOverlayNode about using mouse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeCreator001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.isUsingMouse = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    EXPECT_NE(selectOverlayNode, nullptr);
}

/**
 * @tc.name: SelectFrameNodeCreator002
 * @tc.desc: Test CreateSelectOverlayNode about extension.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeCreator002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode2 = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode2->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode2->selectMenuInner_, nullptr);
}

/**
 * @tc.name: SelectFrameNodeAnimationTest001
 * @tc.desc: Test MoreAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create default menu and extension menu .
     * @tc.expected: The default menu and extended menu are created successfully.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->CreateExtensionToolBar();
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    /**
     * @tc.steps: step3. Execute MoreAnimation.
     * @tc.expected: The node state switches correctly.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->CreateNodePaintMethod();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->MoreOrBackAnimation(true);
    EXPECT_TRUE(selectOverlayNode->isExtensionMenu_);
    /**
     * @tc.steps: step4. Execute BackAnimation.
     * @tc.expected: The node state switches correctly.
     */
    selectOverlayNode->isDoingAnimation_ = false;
    selectOverlayNode->MoreOrBackAnimation(false);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}
} // namespace OHOS::Ace::NG