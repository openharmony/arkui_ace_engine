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
#include <vector>

#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"

#define protected public
#define private public

#include "test/mock/base/mock_task_executor.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/pipeline/base/constants.h"
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
const Color COLOR_ALPHA_MASK = Color::FromRGB(255, 100, 100);
constexpr MenuType TYPE = MenuType::MENU;
const OffsetF offset(10, 10);
int32_t callBackFlag = 0;
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
    bool isShow[2] = { false, true };
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
    bool handleReverse[2] = { false, true };
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
    auto selectOverlayLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(selectOverlayLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(selectOverlayLayoutAlgorithm));

    DirtySwapConfig config;
    config.skipMeasure = true;
    EXPECT_FALSE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));

    layoutWrapper->skipMeasureContent_ = false;
    config.skipMeasure = false;
    EXPECT_TRUE(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config));
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

    area = RectF(1, 1, 1, 1);
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
    auto firstHandlePaintRect = pattern->GetSelectOverlayInfo()->firstHandle.paintRect + offset;
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
    auto secondHandlePaintRect = pattern->GetSelectOverlayInfo()->secondHandle.paintRect + offset2;
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
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return ;
    };
    infoPtr->onTouchUp = [](const TouchEventInfo& info) {
        callBackFlag = 2;
        return ;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 1);
}

/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator004, TestSize.Level1)
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
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return ;
    };
    infoPtr->onTouchUp = [](const TouchEventInfo& info) {
        callBackFlag = 2;
        return ;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 2);
}

/**
 * @tc.name: HandleOperator003
 * @tc.desc: Test SelectOverlayPattern HandleOperator.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HandleOperator005, TestSize.Level1)
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
    infoPtr->onTouchDown = [](const TouchEventInfo& info) {
        callBackFlag = 1;
        return ;
    };
    infoPtr->onTouchMove = [](const TouchEventInfo& info) {
        callBackFlag = 3;
        return ;
    };
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    pattern->HandleTouchEvent(touchInfo);
    EXPECT_EQ(callBackFlag, 3);
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
    bool handleReverse[2] = { false, true };
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
    bool handleReverse[2] = { false, true };
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
    bool menuIsShow[2] = { false, true };
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
            ASSERT_NE(firstLayoutWrapper, nullptr);
            auto itemPattern = item->GetPattern<MenuPattern>();
            ASSERT_NE(itemPattern, nullptr);
            firstLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
            auto itemLayoutAlgorithm = itemPattern->CreateLayoutAlgorithm();
            ASSERT_NE(itemLayoutAlgorithm, nullptr);
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
 * @tc.name: SetHasShowAnimation001
 * @tc.desc: Test SetHasShowAnimation when argument is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetHasShowAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call SetHasShowAnimation and argument is true .
     * @tc.expected: The hasShowAnimation_ be changed success.
     */
    pattern->SetHasShowAnimation(true);
    EXPECT_TRUE(pattern->hasShowAnimation_);
}

/**
 * @tc.name: SetFrameNodeStatus001
 * @tc.desc: Test SetFrameNodeStatus different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeStatus001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call SetFrameNodeStatus and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::SELECTMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenuStatus_, FrameNodeStatus::VISIBLE);
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::EXTENSIONMENU, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenuStatus_, FrameNodeStatus::VISIBLE);
    selectOverlayNode->SetFrameNodeStatus(FrameNodeType::BACKBUTTON, FrameNodeStatus::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButtonStatus_, FrameNodeStatus::VISIBLE);
}

/**
 * @tc.name: SetFrameNodeVisibility001
 * @tc.desc: Test SetFrameNodeVisibility different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeVisibility001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
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
     * @tc.steps: step3. call SetFrameNodeVisibility and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::SELECTMENU, VisibleType::VISIBLE);
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::EXTENSIONMENU, VisibleType::VISIBLE);
    selectOverlayNode->SetFrameNodeVisibility(FrameNodeType::BACKBUTTON, VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->selectMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->extensionMenu_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
    EXPECT_EQ(selectOverlayNode->backButton_->GetLayoutProperty()->GetVisibility(), VisibleType::VISIBLE);
}

/**
 * @tc.name: SetFrameNodeOpacity001
 * @tc.desc: Test SetFrameNodeOpacity different argument.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetFrameNodeOpacity001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
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
     * @tc.steps: step3. call SetFrameNodeOpacity and pass different parameters .
     * @tc.expected: the corresponding value was successfully changed.
     */
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::SELECTMENU, 0.0);
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::EXTENSIONMENU, 0.0);
    selectOverlayNode->SetFrameNodeOpacity(FrameNodeType::BACKBUTTON, 0.0);

    EXPECT_EQ(selectOverlayNode->selectMenu_->GetRenderContext()->GetOpacity(), 0.0);
    EXPECT_EQ(selectOverlayNode->extensionMenu_->GetRenderContext()->GetOpacity(), 0.0);
    EXPECT_EQ(selectOverlayNode->backButton_->GetRenderContext()->GetOpacity(), 0.0);
}

/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test hasShowAnimation_ value change situation.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    bool animate[2] = { true, false };
    /**
     * @tc.steps: step2. call ShowSelectOverlay  .
     * @tc.expected: the hasShowAnimation_ value was successfully changed.
     */
    for (int i = 0; i < 2; i++) {
        selectOverlayNode->ShowSelectOverlay(animate[i]);
        EXPECT_EQ(pattern->hasShowAnimation_, animate[i]);
    }
}

/**
 * @tc.name: HideSelectOverlay001
 * @tc.desc: Test select_overlay_node HideSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HideSelectOverlay001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern.
     */
    SelectOverlayInfo selectInfo;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    /**
     * @tc.steps: step2. call ShowSelectOverlay  .
     * @tc.expected: the circlesAndBackArrowOpacity_ value was successfully changed.
     */
    pattern->CreateNodePaintMethod();
    ASSERT_NE(pattern->selectOverlayModifier_, nullptr);
    selectOverlayNode->HideSelectOverlay([]() {});
    EXPECT_EQ(pattern->selectOverlayModifier_->circlesAndBackArrowOpacity_->Get(), 0.0);
}

/**
 * @tc.name: UpdateToolBar001
 * @tc.desc: Test select_overlay_node UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateToolBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern six situation.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
            case 3:
                selectInfo.menuInfo.menuDisable = true;
                break;
            case 1:
            case 4:
                selectInfo.menuInfo.menuDisable = false;
                selectInfo.menuInfo.menuIsShow = true;
                break;
            case 2:
            case 6:
                selectInfo.menuInfo.menuDisable = false;
                selectInfo.menuInfo.menuIsShow = false;
                break;
            default:
                break;
        }

        auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
        auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
        auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
        ASSERT_NE(selectOverlayNode, nullptr);
        selectOverlayNode->isExtensionMenu_ = true;
        selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
        selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        if (i < 3) {
            selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
            selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
            selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONETOVISIBLE;
        }
        EXPECT_NE(selectOverlayNode->backButton_, nullptr);
        EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
        EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
        auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
        ASSERT_NE(pattern, nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayNode->CreateToolBar();
        /**
         * @tc.steps: step3. call UpdateToolBar for call the other function .
         * @tc.expected: the isExtensionMenu_ value was successfully changed.
         */
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
        selectOverlayNode->UpdateToolBar(false);

        EXPECT_TRUE(selectOverlayNode->isExtensionMenu_);

        selectOverlayNode->UpdateToolBar(true);

        EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    }
}

/**
 * @tc.name: ContentModifierOnDraw001
 * @tc.desc: Test select_ovelay_content_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ContentModifierOnDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto contentModifier = pattern->selectOverlayContentModifier_;
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(contentModifier, nullptr);
    EXPECT_NE(overlayModifier, nullptr);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AtLeast(1));
    DrawingContext context { canvas, 100, 100 };
    /**
     * @tc.steps: step2. get the contentModifier and initialize properies and call onDraw function.
     * @tc.expected: the innerHandleRadius_ value is correct.
     */
    contentModifier->SetIsSingleHandle(true);
    contentModifier->SetFirstHandleIsShow(true);
    contentModifier->SetInShowArea(true);
    EXPECT_EQ(contentModifier->inShowArea_->Get(), true);
    contentModifier->SetHandleReverse(false);
    EXPECT_EQ(contentModifier->handleReverse_->Get(), false);
    contentModifier->SetViewPort(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->viewPort_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetFirstHandle(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->firstHandle_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetSecondHandle(SECOND_HANDLE_REGION);
    EXPECT_EQ(contentModifier->secondHandle_->Get(), SECOND_HANDLE_REGION);
    contentModifier->SetHandleColor(Color::RED);
    EXPECT_EQ(contentModifier->handleColor_->Get(), Color::RED);
    contentModifier->SetInnerHandleColor(Color::RED);
    EXPECT_EQ(contentModifier->innerHandleColor_->Get(), Color::RED);
    contentModifier->SetHandleRadius(2.0f);
    EXPECT_EQ(contentModifier->handleRadius_->Get(), 2.0f);
    contentModifier->SetInnerHandleRadius(2.0f);
    EXPECT_EQ(contentModifier->innerHandleRadius_->Get(), 2.0f);
    contentModifier->SetHandleOpacity(2.0f);
    EXPECT_EQ(contentModifier->handleOpacity_->Get(), 2.0f);
    for (int i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                contentModifier->SetFirstHandleIsShow(true);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), true);
                break;
            case 1:
                contentModifier->SetIsSingleHandle(true);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), true);
                contentModifier->SetFirstHandleIsShow(false);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), false);
                contentModifier->SetSecondHandleIsShow(true);
                EXPECT_EQ(contentModifier->secondHandleIsShow_->Get(), true);
                break;
            case 2:
                contentModifier->SetIsSingleHandle(false);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), false);
                contentModifier->SetFirstHandleIsShow(true);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), true);
                break;
            case 3:
                contentModifier->SetIsSingleHandle(true);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), true);
                contentModifier->SetFirstHandleIsShow(false);
                EXPECT_EQ(contentModifier->firstHandleIsShow_->Get(), false);
                contentModifier->SetSecondHandleIsShow(false);
                EXPECT_EQ(contentModifier->secondHandleIsShow_->Get(), false);
                break;
            case 4:
                contentModifier->SetIsSingleHandle(false);
                EXPECT_EQ(contentModifier->isSingleHandle_->Get(), false);
                break;
            case 5:
                contentModifier->SetInShowArea(false);
                EXPECT_EQ(contentModifier->inShowArea_->Get(), false);
                break;
            default:
                break;
        }

        contentModifier->onDraw(context);
    }
    EXPECT_EQ(contentModifier->innerHandleRadius_->Get(), 2.0f);
}

/**
 * @tc.name: OverlayModifierOnDraw001
 * @tc.desc: Test select_ovelay_modifier onDraw.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OverlayModifierOnDraw001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern,canvs
     * and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    EXPECT_NE(pattern, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    auto overlayModifier = pattern->selectOverlayModifier_;
    EXPECT_NE(overlayModifier, nullptr);
    Testing::MockCanvas canvas;
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(canvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    for (int32_t i = 0; i < 4; i++) {
        overlayModifier->circleOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
        EXPECT_NE(overlayModifier->circleOffset_[i], nullptr);
        if (i < 4 - 1) {
            overlayModifier->lineEndOffset_[i] = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
            EXPECT_NE(overlayModifier->lineEndOffset_[i], nullptr);
        }
    }
    overlayModifier->rotationAngle_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetMenuOptionOffset(offset);
    overlayModifier->pointRadius_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(Dimension(1.75_vp).ConvertToPx());
    overlayModifier->SetHeadPointRadius(Dimension(1.0));
    /**
     * @tc.steps: step2. call onDraw.
     * @tc.expected: the menuOptionOffset_ value is correct.
     */
    overlayModifier->onDraw(context);
    EXPECT_EQ(overlayModifier->hasExtensionMenu_, false);
}

/**
 * @tc.name: UpdateContentModifier001
 * @tc.desc: Test select_ovelay_modifier UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode, pattern and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the isCreated_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
}

/**
 * @tc.name: UpdateContentModifier002
 * @tc.desc: Test select_ovelay_modifier UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    selectOverlayPaintMethod->isCreated_ = false;
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
    /**
     * @tc.steps: step2. call UpdateContentModifier.
     * @tc.expected: the isCreated_ value is correct.
     */
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
}

/**
 * @tc.name: UpdateContentModifier003
 * @tc.desc: Test select_ovelay_modifier UpdateContentModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateContentModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto framenode = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    framenode->viewPort_ = RectF(1, 1, 1, 1);
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.callerFrameNode = AceType::WeakClaim(AceType::RawPtr(framenode));
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the hasShowAnimation_ value is correct.
     */
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                selectOverlayPaintMethod->isCreated_ = true;
                EXPECT_EQ(selectOverlayPaintMethod->isCreated_, true);
                selectOverlayPaintMethod->selectOverlayModifier_->SetHasExtensionMenu(true);
                EXPECT_EQ(selectOverlayPaintMethod->selectOverlayModifier_->hasExtensionMenu_, true);
                selectOverlayPaintMethod->hasExtensionMenu_ = true;
                EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, true);
                break;
            case 1:
                selectOverlayPaintMethod->hasExtensionMenu_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, false);
                break;
            case 2:
                selectOverlayPaintMethod->isCreated_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->isCreated_, false);
                selectOverlayPaintMethod->handleIsShown_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
                selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, false);
                selectOverlayPaintMethod->hasExtensionMenu_ = true;
                EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, true);
                selectOverlayPaintMethod->hasShowAnimation_ = true;
                EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, true);
                break;
            case 3:
                selectOverlayPaintMethod->handleIsShown_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->handleIsShown_, false);
                selectOverlayPaintMethod->hasShowAnimation_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, false);
                break;
            case 4:
                selectOverlayPaintMethod->hasExtensionMenu_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, false);
                break;
            default:
                break;
        }
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayPaintMethod->GetOverlayModifier(paintWrapper);
        selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    }
    EXPECT_EQ(selectOverlayPaintMethod->hasShowAnimation_, false);
}

/**
 * @tc.name: UpdateOverlayModifier001
 * @tc.desc: Test select_ovelay_modifier UpdateOverlayModifier.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateOverlayModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectinfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectinfo.menuOptionItems = menuOptionItems;
    selectinfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectinfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    ASSERT_NE(paintWrapper, nullptr);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);
    /**
     * @tc.steps: step2. call UpdateContentModifier by five situations.
     * @tc.expected: the hasExtensionMenu_ value is correct.
     */
    for (int i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                selectOverlayPaintMethod->isCreated_ = true;
                selectOverlayPaintMethod->selectOverlayModifier_->SetHasExtensionMenu(false);
                selectOverlayPaintMethod->hasExtensionMenu_ = true;
                break;
            case 1:
                selectOverlayPaintMethod->selectOverlayModifier_->SetHasExtensionMenu(true);
                selectOverlayPaintMethod->hasExtensionMenu_ = false;
                break;
            case 2:
                selectOverlayPaintMethod->isCreated_ = false;
                selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, false);
                selectOverlayPaintMethod->hasExtensionMenu_ = true;
                selectOverlayPaintMethod->hasShowAnimation_ = true;
                break;
            case 3:
                selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
                EXPECT_EQ(selectOverlayPaintMethod->circlesAndBackArrowIsShown_, false);
                selectOverlayPaintMethod->hasShowAnimation_ = false;
                break;
            case 4:
                selectOverlayPaintMethod->hasExtensionMenu_ = true;
                break;
            default:
                break;
        }
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
        selectOverlayPaintMethod->GetContentModifier(paintWrapper);
        selectOverlayPaintMethod->UpdateOverlayModifier(paintWrapper);
    }
    EXPECT_EQ(selectOverlayPaintMethod->hasExtensionMenu_, true);
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
        EXPECT_FALSE(layoutWrapper->isActive_);
    }
}

/**
 * @tc.name: IsMenuShow001
 * @tc.desc: Test IsMenuShow function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsMenuShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call IsMenuShow function.
     * @tc.expected: The isMenuShow returns false
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->IsMenuShow());
}

/**
 * @tc.name: IsHandleShow001
 * @tc.desc: Test IsHandleShow function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, IsHandleShow001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    /**
     * @tc.steps: step2. Create pattern and call IsHandleShow function.
     * @tc.expected: The IsHandleShow returns true.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->IsHandleShow());
}

/**
 * @tc.name: StartHiddenHandleTask001
 * @tc.desc: Test StartHiddenHandleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, StartHiddenHandleTask001, TestSize.Level1)
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
    auto taskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    ASSERT_NE(taskExecutor, nullptr);
    auto pipeline = PipelineBase::GetCurrentContext();
    pipeline->taskExecutor_ = taskExecutor;
    /**
     * @tc.steps: step2. Create pattern and call StartHiddenHandleTask function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StartHiddenHandleTask();
}

/**
 * @tc.name: HiddenHandle001
 * @tc.desc: Test HiddenHandle function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, HiddenHandle001, TestSize.Level1)
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
     * @tc.steps: step2. Create pattern and call HiddenHandle function.
     * @tc.expected: The selectInfo->isHiddenHandle_ value is true
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->isHiddenHandle_ = false;
    pattern->HiddenHandle();
    EXPECT_TRUE(pattern->isHiddenHandle_);
}

/**
 * @tc.name: StopHiddenHandleTask001
 * @tc.desc: Test StopHiddenHandleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, StopHiddenHandleTask001, TestSize.Level1)
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
     * @tc.steps: step2. Create pattern and call StopHiddenHandleTask function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->StopHiddenHandleTask();
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: Test OnDetachFromFrameNodee function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    auto testCallback = [](bool closedByGlobalTouchEvent_) {
        callBackFlag = static_cast<int32_t>(closedByGlobalTouchEvent_);
        return ;
    };
    selectInfo.onClose = testCallback;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call OnDetachFromFrameNode function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNode(
        FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton", ElementRegister::GetInstance()->MakeUniqueId(), []() {
            return AceType::MakeRefPtr<ButtonPattern>();
        }).rawPtr_);
    EXPECT_FALSE(pattern->closedByGlobalTouchEvent_);
    EXPECT_EQ(callBackFlag, 0);
}

/**
 * @tc.name: SetHandleReverse001
 * @tc.desc: Test SetHandleReverse function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetHandleReverse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    selectInfo.isSingleHandle = false;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.steps: step2. Create pattern and call SetHandleReverse function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    pattern->info_->handleReverse = true;
    pattern->SetHandleReverse(true);
    EXPECT_TRUE(pattern->info_->handleReverse);
    pattern->SetHandleReverse(false);
    EXPECT_FALSE(pattern->info_->handleReverse);
}

/**
 * @tc.name: UpdateSelectMenuInfo001
 * @tc.desc: Test UpdateSelectMenuInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateSelectMenuInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call UpdateSelectMenuInfo function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    SelectMenuInfo infoMenu;
    OffsetF testCase(4, 5);
    infoMenu.menuOffset = testCase;
    pattern->UpdateSelectMenuInfo(infoMenu);
    EXPECT_EQ(pattern->info_->menuInfo.menuOffset, testCase);
}

/**
 * @tc.name: ShowOrHiddenMenu001
 * @tc.desc: Test ShowOrHiddenMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, ShowOrHiddenMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call ShowOrHiddenMenu function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->info_->menuInfo.menuIsShow = true;
    pattern->ShowOrHiddenMenu(true);
    EXPECT_FALSE(pattern->info_->menuInfo.menuIsShow);

    pattern->info_->menuInfo.menuIsShow = false;
    pattern->ShowOrHiddenMenu(false);
    pattern->info_->firstHandle.isShow = true;
    EXPECT_TRUE(pattern->info_->menuInfo.menuIsShow);
}

/**
 * @tc.name: DisableMenu001
 * @tc.desc: Test DisableMenu function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, DisableMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuOptionItems = GetMenuOptionItems();
    selectInfo.singleLineHeight = NODE_ID;
    selectInfo.menuInfo.menuDisable = false;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    /**
     * @tc.steps: step2. Create pattern and call DisableMenu function.
     */
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    std::vector<bool> testCases = { true, false };
    for (uint32_t turn = 0; turn < testCases.size(); ++turn) {
        pattern->DisableMenu(testCases[turn]);
        EXPECT_EQ(pattern->info_->menuInfo.menuDisable, testCases[turn]);
    }
}

/**
 * @tc.name: SetClosedByGlobalEvent001
 * @tc.desc: Test SetClosedByGlobalEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, SetClosedByGlobalEvent001, TestSize.Level1)
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
     * @tc.steps: step2. Create pattern and call SetClosedByGlobalEvent function.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->SetClosedByGlobalEvent(true);
    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_TRUE(pattern->closedByGlobalTouchEvent_);
}

/**
 * @tc.name: UpdateToolBar002
 * @tc.desc: Test select_overlay_node UpdateToolBar.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayTestNg, UpdateToolBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create and initialize selectOverlayNode and pattern six situation.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    selectOverlayNode->isExtensionMenu_ = true;
    selectOverlayNode->AddExtensionMenuOptions(menuOptionItems, 0);
    
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    selectOverlayNode->selectMenuStatus_ = FrameNodeStatus::VISIBLETOGONE;
    selectOverlayNode->extensionMenuStatus_ = FrameNodeStatus::GONETOVISIBLE;
    selectOverlayNode->backButtonStatus_ = FrameNodeStatus::GONETOVISIBLE;
    ASSERT_NE(selectOverlayNode->backButton_, nullptr);
    ASSERT_NE(selectOverlayNode->selectMenu_, nullptr);
    ASSERT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return ;
    };
    infoPtr->menuCallback.onPaste = []() {
        callBackFlag = 2;
        return ;
    };

    /**
    * @tc.steps: step3. call UpdateToolBar for call the other function.
    * @tc.expected: the isExtensionMenu_ value was successfully changed.
    */
    selectOverlayNode->UpdateToolBar(false);
    EXPECT_TRUE(selectOverlayNode->isExtensionMenu_);
    selectOverlayNode->UpdateToolBar(true);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
}
} // namespace OHOS::Ace::NG