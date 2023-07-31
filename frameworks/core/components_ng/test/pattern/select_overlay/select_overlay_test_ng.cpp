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
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "Test";
constexpr int32_t NODE_ID = 143;
constexpr int32_t NODE_ID2 = 153;
constexpr int32_t NODE_ID3 = 10;
const RectF FIRST_HANDLE_REGION(0, 0, 10, 10);
const RectF SECOND_HANDLE_REGION(10, 10, 10, 10);
const RectF SECOND_HANDLE_REGION2(20, 20, 10, 10);
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
constexpr MenuType TYPE = MenuType::MENU;
} // namespace

class SelectOverlayTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
};

void SelectOverlayTestNg::SetUpTestCase()
{
    MockPipelineBase::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayTestNg::TearDownTestCase()
{
    MockPipelineBase::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlayTestNg::GetMenuOptionItems()
{
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    MenuOptionsParam menuOptionItem2;
    menuOptionItem2.content = "test2";
    menuOptionItem2.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    menuOptionItems.emplace_back(menuOptionItem2);
    return menuOptionItems;
}
/**
 * @tc.name: SelectFrameNodeCreator001
 * @tc.desc: Test CreateSelectOverlayNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode with using mouse.
     * @tc.expected: the selectOverlayNode is created successfully.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.isUsingMouse = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto selectOverlayNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    EXPECT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create selectOverlayNode with extension.
     * @tc.expected: the selectOverlayNode including selectMenu is created successfully.
     */
    SelectOverlayInfo selectInfo2;
    selectInfo2.menuInfo.menuIsShow = true;
    selectInfo2.menuInfo.showCopy = false;
    selectInfo2.menuInfo.showCopyAll = false;
    selectInfo2.menuOptionItems = GetMenuOptionItems();
    auto infoPtr2 = std::make_shared<SelectOverlayInfo>(selectInfo2);
    auto frameNode2 = SelectOverlayNode::CreateSelectOverlayNode(infoPtr2);
    auto selectOverlayNode2 = AceType::DynamicCast<SelectOverlayNode>(frameNode2);
    EXPECT_NE(selectOverlayNode2->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode2->selectMenuInner_, nullptr);
}

/**
 * @tc.name: SelectFrameNodeAnimationTest001
 * @tc.desc: Test MoreAnimation and BackAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
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
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
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
/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test SelectOverlayPattern OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.isSingleHandle = true;
    bool isShow[2] = { false, true};
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.firstHandle.isShow = isShow[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call OnAttachToFrameNode function.
         * @tc.expected: the function exits normally.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        pattern->OnAttachToFrameNode();
        EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);
    }
}
/**
 * @tc.name: UpdateSelectHandleInfo001
 * @tc.desc: Test SelectOverlayPattern UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectHandleInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. call UpdateHandleInfo functions without changing HandleInfo.
     * @tc.expected: The branch of function runs correctly
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    pattern->UpdateFirstSelectHandleInfo(selectInfo.firstHandle);
    pattern->UpdateSecondSelectHandleInfo(selectInfo.secondHandle);
    pattern->UpdateFirstAndSecondHandleInfo(selectInfo.firstHandle, selectInfo.secondHandle);
    EXPECT_EQ(pattern->info_->firstHandle, selectInfo.firstHandle);
    EXPECT_EQ(pattern->info_->secondHandle, selectInfo.secondHandle);
}
/**
 * @tc.name: UpdateSelectHandleInfo002
 * @tc.desc: Test SelectOverlayPattern UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectHandleInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    bool handleReverse[2] = { false, true};
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call UpdateHandleInfo functions with changing HandleInfo.
         * @tc.expected: The branch of function runs correctly
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        SelectOverlayInfo selectInfo2;
        selectInfo2.singleLineHeight = NODE_ID2;
        selectInfo2.firstHandle.isShow = false;
        selectInfo2.secondHandle.isShow = false;
        SelectOverlayInfo selectInfo3;
        selectInfo3.singleLineHeight = NODE_ID3;
        pattern->UpdateFirstSelectHandleInfo(selectInfo2.firstHandle);
        pattern->UpdateSecondSelectHandleInfo(selectInfo2.secondHandle);
        pattern->UpdateFirstAndSecondHandleInfo(selectInfo3.firstHandle, selectInfo3.secondHandle);
    }
}
/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test SelectOverlayPattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and geometryNode.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    /**
     * @tc.steps: step2. Call OnDirtyLayoutWrapperSwap function.
     * @tc.expected: return false
     */
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    DirtySwapConfig config;
    config.skipMeasure = true;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
}
/**
 * @tc.name: UpdateShowArea001
 * @tc.desc: Test SelectOverlayPattern UpdateShowArea.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateShowArea001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Call UpdateShowArea
     * @tc.expected: the function exits normally
     */
    RectF area;
    pattern->UpdateShowArea(area);
    EXPECT_NE(pattern->GetSelectOverlayInfo(), nullptr);
}
/**
 * @tc.name: HandleOperator001
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step4. Construct GestureEvent and Call UpdateShowArea
     * @tc.expected: the function exits normally
     */
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleOnClick(info);
    EXPECT_FALSE(pattern->GetSelectOverlayInfo()->isSingleHandle);
    pattern->HandlePanEnd(info);
    EXPECT_FALSE(pattern->GetSelectOverlayInfo()->isSingleHandle);
}
/**
 * @tc.name: HandleOperator002
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.isSingleHandle = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct GestureEvent and Call HandleOperator functions in firstHandleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleOnClick(info);
    EXPECT_TRUE(pattern->GetSelectOverlayInfo()->menuInfo.menuIsShow);
    pattern->HandlePanStart(info);
    EXPECT_TRUE(pattern->firstHandleDrag_);
    const auto& offset = OffsetF(info.GetDelta().GetX(), info.GetDelta().GetY());
    auto firstHandlePaintRect = pattern->GetSelectOverlayInfo()->firstHandle.paintRect+offset;
    pattern->HandlePanMove(info);
    auto firstHandlePaintRect2 = pattern->GetSelectOverlayInfo()->secondHandle.paintRect;
    EXPECT_EQ(firstHandlePaintRect.GetX(), firstHandlePaintRect2.GetX());
    pattern->HandlePanEnd(info);
    EXPECT_FALSE(pattern->firstHandleDrag_);
    /**
     * @tc.steps: step4. Construct GestureEvent and Call HandleOperator functions in secondHandleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info2;
    info2.localLocation_ = Offset(11, 11);
    pattern->HandlePanStart(info2);
    EXPECT_TRUE(pattern->secondHandleDrag_);
    const auto& offset2 = OffsetF(info2.GetDelta().GetX(), info2.GetDelta().GetY());
    auto secondHandlePaintRect = pattern->GetSelectOverlayInfo()->secondHandle.paintRect+offset2;
    pattern->HandlePanMove(info2);
    auto secondHandlePaintRect2 = pattern->GetSelectOverlayInfo()->secondHandle.paintRect;
    EXPECT_EQ(secondHandlePaintRect.GetX(), secondHandlePaintRect2.GetX());
    pattern->HandlePanEnd(info2);
    EXPECT_FALSE(pattern->secondHandleDrag_);
    /**
     * @tc.steps: step5. Construct GestureEvent and Call HandleOperator functions which is not in handleRegion.
     * @tc.expected: the function runs rightly
     */
    GestureEvent info3;
    info3.localLocation_ = Offset(21, 21);
    pattern->HandlePanStart(info3);
    pattern->HandlePanMove(info3);
    EXPECT_FALSE(pattern->firstHandleDrag_);
    EXPECT_FALSE(pattern->secondHandleDrag_);
}
/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. Construct TouchEventInfo and Call HandleTouchEvent function.
     * @tc.expected: check whether the function is executed.
     */
    TouchEventInfo touchInfo("touchDown");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
}
/**
 * @tc.name: CheckHandleReverse001
 * @tc.desc: Test SelectOverlayPattern CheckHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckHandleReverse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectHandleInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID3;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = FIRST_HANDLE_REGION;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = SECOND_HANDLE_REGION2;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    bool handleReverse[2] = { false, true};
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call CheckHandleReverse function.
         * @tc.expected: check whether the value of handleReverse is correct.
         */
        pattern->CheckHandleReverse();
        auto res = pattern->GetSelectOverlayInfo()->handleReverse;
        EXPECT_FALSE(res);
    }
}
/**
 * @tc.name: CheckHandleReverse002
 * @tc.desc: Test SelectOverlayPattern CheckHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, CheckHandleReverse002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectHandleInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID3;
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = SECOND_HANDLE_REGION2;
    SelectHandleInfo secondHandle;
    secondHandle.paintRect = FIRST_HANDLE_REGION;
    selectInfo.firstHandle = firstHandle;
    selectInfo.secondHandle = secondHandle;
    bool handleReverse[2] = { false, true};
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.handleReverse = handleReverse[turn];
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        /**
         * @tc.steps: step3. call CheckHandleReverse function.
         * @tc.expected: check whether the value of handleReverse is correct.
         */
        pattern->CheckHandleReverse();
        auto res = pattern->GetSelectOverlayInfo()->handleReverse;
        EXPECT_TRUE(res);
    }
}
/**
 * @tc.name: SelectOverlayLayout001
 * @tc.desc: Test selectOverlay layout.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    bool menuIsShow[2] = { false, true};
    for (int turn = 0; turn < 2; turn++) {
        selectInfo.menuInfo.menuIsShow = menuIsShow[turn];
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern and geometryNode.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        /**
         * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
         * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
         */
        auto layoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
        auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
        ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
        layoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

        auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
        // create menu and extensionMenu
        for (int i = 0; i < 2; i++) {
            auto item = FrameNode::GetOrCreateFrameNode(
                V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
            // add item to selectOverlayNode
            selectOverlayNode->AddChild(item);
            RefPtr<GeometryNode> firstGeometryNode = AceType::MakeRefPtr<GeometryNode>();
            firstGeometryNode->Reset();
            RefPtr<LayoutWrapperNode> firstLayoutWrapper =
                AceType::MakeRefPtr<LayoutWrapperNode>(item, firstGeometryNode, item->GetLayoutProperty());
            EXPECT_FALSE(firstLayoutWrapper == nullptr);
            auto itemPattern = item->GetPattern<MenuPattern>();
            EXPECT_FALSE(itemPattern == nullptr);
            firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
            auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
            EXPECT_FALSE(itemLayoutAlgorithm == nullptr);
            firstLayoutWrapper->SetLayoutAlgorithm(
                AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
            firstLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
            layoutWrapper->AppendChild(firstLayoutWrapper);
        }
        /**
         * @tc.steps: step4. use layoutAlgorithm to measure and layout.
         * @tc.expected: the function runs rightly.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    }
}
/**
 * @tc.name: SelectOverlayNodeTest001
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea with menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step4. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return true
     */
    const NG::PointF point2 { 12.0f, 12.0f };
    auto result2 = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point2);
    EXPECT_TRUE(result2);
}

/**
 * @tc.name: SelectOverlayNodeTest002
 * @tc.desc: Test IsInSelectedOrSelectOverlayArea without menuOptions.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and initialize HandleRegion
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->firstHandleRegion_ = FIRST_HANDLE_REGION;
    pattern->secondHandleRegion_ = SECOND_HANDLE_REGION;
    /**
     * @tc.steps: step3. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return false
     */
    const NG::PointF point { 9.0f, 12.0f };
    auto result = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point);
    EXPECT_FALSE(result);
    /**
     * @tc.steps: step4. Construct Point and Call IsInSelectedOrSelectOverlayArea.
     * @tc.expected: return true
     */
    const NG::PointF point2 { 12.0f, 12.0f };
    auto result2 = selectOverlayNode->IsInSelectedOrSelectOverlayArea(point2);
    EXPECT_TRUE(result2);
}
/**
 * @tc.name: SelectFrameNodeAnimationTest002
 * @tc.desc: Test MoreAnimation and BackAnimation when isShowInDefaultMenu is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectFrameNodeAnimationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
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
    for (int i = 0; i < 7; i++) {
        selectOverlayNode->isShowInDefaultMenu_[i] = false;
    }
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
}
/**
 * @tc.name: SelectOverlayLayout002
 * @tc.desc: Test selectOverlay layout when checkIsInShowArea is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SelectOverlayLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize selectOverlayInfo properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.menuInfo.menuIsShow = true;
    selectInfo.useFullScreen = false;
    bool isSingleHandle[2] = { false, true };
    for (int i = 0; i < 2; i++) {
        selectInfo.isSingleHandle = isSingleHandle[i];
        selectInfo.firstHandle.paintRect = FIRST_HANDLE_REGION;
        selectInfo.secondHandle.paintRect = SECOND_HANDLE_REGION;
        selectInfo.showArea = FIRST_HANDLE_REGION;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        /**
         * @tc.steps: step2. Create pattern and geometryNode.
         */
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
        /**
         * @tc.steps: step3. Get layoutWrapper and layoutAlgorithm.
         * @tc.expected: layoutWrapper and layoutAlgorithm are created successfully
         */
        LayoutWrapperNode* layoutWrapper =
            new LayoutWrapperNode(frameNode, geometryNode, frameNode->GetLayoutProperty());
        auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
        ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
        layoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

        auto childLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
        // create menu
        auto item = FrameNode::GetOrCreateFrameNode(
            V2::MENU_ETS_TAG, -1, []() { return AceType::MakeRefPtr<MenuPattern>(1, "Test", TYPE); });
        // add item to selectOverlayNode
        selectOverlayNode->AddChild(item);
        RefPtr<GeometryNode> itemGeometryNode = AceType::MakeRefPtr<GeometryNode>();
        itemGeometryNode->Reset();
        RefPtr<LayoutWrapperNode> itemLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(item, itemGeometryNode, item->GetLayoutProperty());
        EXPECT_FALSE(itemLayoutWrapper == nullptr);
        auto itemPattern = item->GetPattern<MenuPattern>();
        EXPECT_FALSE(itemPattern == nullptr);
        itemLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
        EXPECT_FALSE(itemLayoutAlgorithm == nullptr);
        itemLayoutWrapper->SetLayoutAlgorithm(
            AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(itemLayoutAlgorithm));
        itemLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper->AppendChild(itemLayoutWrapper);
        /**
         * @tc.steps: step4. use layoutAlgorithm to measure and layout.
         * @tc.expected: RemoveChildInRenderTree is executed successfully when checkIsInShowArea is false.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayLayoutAlgorithm->Layout(layoutWrapper);
        EXPECT_TRUE(layoutWrapper->isActive_);
    }
}
/**
 * @tc.name: SetHasShowAnimation001
 * @tc.desc: Test SelectOverlayPattern SetHasShowAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetHasShowAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step3. call SetHasShowAnimation functions with true.
     * @tc.expected: The branch of function runs correctly
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    pattern->SetHasShowAnimation(true);
    EXPECT_EQ(pattern->hasShowAnimation_, true);
}
} // namespace OHOS::Ace::NG