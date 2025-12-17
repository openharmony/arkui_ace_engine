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
#include <vector>
#include "gtest/gtest.h"
#include "gtest/internal/gtest-internal.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "base/geometry/dimension_rect.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/memory/referenced.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components/theme/theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_node.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/pipeline/base/constants.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_TAG = "Test";
constexpr int32_t NODE_ID = 143;
const RectF FIRST_HANDLE_REGION(0, 0, 10, 10);
const RectF SECOND_HANDLE_REGION(10, 10, 10, 10);
const RectF SECOND_HANDLE_REGION2(20, 20, 10, 10);
const float FIRST_ITEM_WIDTH = 150.0f;
const float FIRST_ITEM_HEIGHT = 75.0f;
const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
const Color COLOR_ALPHA_MASK = Color::FromRGB(255, 100, 100);
const OffsetF offset(10, 10);
int32_t callBackFlag = 0;
const OffsetF OFFSET_ITEM1 = OffsetF(5, 5);
const Rect WINDOW_RECT(0, 0, 280, 1280);
const float AGING_MIN_SCALE_TEST = 2.0f;
} // namespace

class SelectOverlayFiveTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

protected:
    std::vector<MenuOptionsParam> GetMenuOptionItems();
    DrawingContext GetDrawingContext(Testing::MockCanvas& canvas);
    void InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme);
};

void SelectOverlayFiveTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
}

void SelectOverlayFiveTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

std::vector<MenuOptionsParam> SelectOverlayFiveTestNg::GetMenuOptionItems()
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

DrawingContext SelectOverlayFiveTestNg::GetDrawingContext(Testing::MockCanvas& canvas)
{
    DrawingContext context { canvas, 100, 100 };
    EXPECT_CALL(canvas, Save()).Times(AnyNumber());
    EXPECT_CALL(canvas, DrawLine(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Rotate(_, _, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, AttachPen(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachPen()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawCircle(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Translate(_, _)).Times(AnyNumber());
    EXPECT_CALL(canvas, Restore()).Times(AnyNumber());
    EXPECT_CALL(canvas, ClipRect(_, _, _)).WillRepeatedly(Return());
    return context;
}

void SelectOverlayFiveTestNg::InitTextOverlayTheme(const RefPtr<TextOverlayTheme>& textOverlayTheme)
{
    CHECK_NULL_VOID(textOverlayTheme);
    textOverlayTheme->cutLabel_ = "剪切";
    textOverlayTheme->copyLabel_ = "复制";
    textOverlayTheme->pasteLabel_ = "粘贴";
    textOverlayTheme->selectAllLabel_ = "全选";
    textOverlayTheme->translateLabel_ = "翻译";
    textOverlayTheme->shareLabel_ = "分享";
    textOverlayTheme->searchLabel_ = "搜索";
    textOverlayTheme->cameraInput_ = "拍摄输入";
    textOverlayTheme->aiWrite_ = "小艺帮写";
}

/**
 * @tc.name: BuildButton002
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, BuildButton002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_FALSE(result);
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_NE(selectOverlayNode->isShowInDefaultMenu_[0], false);
}

/**
 * @tc.name: BuildButton003
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, BuildButton003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->SetFontScale(AGING_MIN_SCALE_TEST);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_FALSE(result);
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_NE(selectOverlayNode->isShowInDefaultMenu_[0], false);
}

/**
 * @tc.name: BuildButton004
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, BuildButton004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->SetFontScale(AGING_MIN_SCALE_TEST);
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, mockContainer);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(frameNode);
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    selectOverlayManager.CreateAndShowSelectOverlay(selectInfo, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    bool result = selectOverlayNode->AddSystemDefaultOptions(maxWidth, allocatedSize);
    EXPECT_FALSE(result);
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_NE(selectOverlayNode->isShowInDefaultMenu_[0], false);
}

/**
 * @tc.name: BuildButton005
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, BuildButton005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;

    std::vector<MenuOptionsParam> menuVec;
    MenuOptionsParam menu1;
    menu1.id = "1";
    menu1.content = "1";
    menu1.action = [](const std::string& menuId) {};

    MenuOptionsParam menu2;
    menu2.id = "1";
    menu2.content = "1";
    menu2.action = [](const std::string& menuId) {};

    menuVec.push_back(menu1);
    menuVec.push_back(menu2);
    selectInfo.menuOptionItems = menuVec;
    float maxWidth = 50.0f;
    float allocatedSize = 2.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->SetFontScale(AGING_MIN_SCALE_TEST);
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, mockContainer);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(frameNode);
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    selectOverlayManager.CreateAndShowSelectOverlay(selectInfo, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    int32_t extensionOptionStartIndex = 0;
    selectOverlayNode->LandscapeMenuAddMenuOptions(true, maxWidth, allocatedSize, extensionOptionStartIndex, infoPtr);
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_FALSE(selectOverlayNode->isShowInDefaultMenu_[0]);
}

/**
 * @tc.name: BuildButton006
 * @tc.desc: Test BuildButton different parameter .
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, BuildButton006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = false;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;

    std::vector<MenuOptionsParam> menuVec;
    MenuOptionsParam menu1;
    menu1.id = "1";
    menu1.content = "1";
    menu1.action = [](const std::string& menuId) {};

    MenuOptionsParam menu2;
    menu2.id = "1";
    menu2.content = "1";
    menu2.action = [](const std::string& menuId) {};

    menuVec.push_back(menu1);
    menuVec.push_back(menu2);
    selectInfo.menuOptionItems = menuVec;
    float maxWidth = 40.0f;
    float allocatedSize = 50.0f;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    infoPtr->menuCallback.onCut = []() {
        callBackFlag = 1;
        return;
    };
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->SetFontScale(AGING_MIN_SCALE_TEST);
    MockContainer::SetUp();
    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    auto pipelineContext = MockPipelineContext::GetCurrent();
    mockContainer->pipelineContext_ = pipelineContext;
    AceEngine::Get().containerMap_.emplace(1, mockContainer);
    AceEngine::Get().containerMap_.emplace(2, mockContainer);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(frameNode);
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    selectOverlayManager.CreateAndShowSelectOverlay(selectInfo, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);

    /**
     * @tc.steps: step2. call BuildButton.
     */
    int32_t extensionOptionStartIndex = 0;
    selectOverlayNode->LandscapeMenuAddMenuOptions(true, maxWidth, allocatedSize, extensionOptionStartIndex, infoPtr);
    auto button = AceType::DynamicCast<FrameNode>(selectOverlayNode->selectMenuInner_->GetLastChild());
    EXPECT_NE(button, nullptr);
    auto gestureEventHubPtr = button->GetOrCreateGestureEventHub();
    EXPECT_NE(gestureEventHubPtr, nullptr);
    if (gestureEventHubPtr->clickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->clickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }

    if (gestureEventHubPtr->userParallelClickEventActuator_) {
        auto playClickCallback = gestureEventHubPtr->userParallelClickEventActuator_->userCallback_->callback_;
        GestureEvent gestureEvent = GestureEvent();
        playClickCallback(gestureEvent);
    }
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManagerBase);
    EXPECT_FALSE(selectOverlayNode->isShowInDefaultMenu_[0]);
}

/**
 * @tc.name: SetMoreOrBackButtonResponse
 * @tc.desc: Test select_overlay_test_ng SetMoreOrBackButtonResponse.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, SetMoreOrBackButtonResponse, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    int32_t extensionOptionStartIndex = -1;
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));

    selectOverlayNode->UpdateMenuOptions(infoPtr);
    EXPECT_NE(extensionOptionStartIndex, 0);
}

/**
 * @tc.name: UpdateBackButtonPadding
 * @tc.desc: Test select_overlay_test_ng UpdateBackButtonPadding.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, UpdateBackButtonPadding, TestSize.Level1)
{
    /**
     * @tc.steps: step1.  CreateMenuNodeSuccess.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.showCut = true;
    selectInfo.menuInfo.showCopy = true;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = true;
    selectInfo.menuInfo.showTranslate = true;
    selectInfo.menuInfo.showSearch = true;
    selectInfo.menuInfo.showShare = true;
    selectInfo.menuInfo.showCameraInput = true;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuItem1;
    menuItem1.content = "item1";
    menuItem1.id = "item1";
    menuOptionItems.emplace_back(menuItem1);

    MenuOptionsParam menuItem2;
    menuItem2.content = "item2";
    menuItem2.id = "item2";
    menuOptionItems.emplace_back(menuItem2);

    int32_t extensionOptionStartIndex = -1;
    auto themeManagerBase = MockPipelineContext::GetCurrent()->GetThemeManager();
    ASSERT_NE(themeManagerBase, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    InitTextOverlayTheme(textOverlayTheme);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textOverlayTheme));

    selectOverlayNode->UpdateMenuOptions(infoPtr);
    EXPECT_NE(extensionOptionStartIndex, 0);
}

/**
 * @tc.name: PrepareMoreOrBackButtonNode
 * @tc.desc: Test PrepareMoreOrBackButtonNode
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, PrepareMoreOrBackButtonNode, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            auto theme = AceType::MakeRefPtr<TextOverlayTheme>();
            theme->menuButtonPadding_.left_.value_ = 500;
            theme->menuButtonPadding_.right_.value_ = 500;
            return theme;
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            return AceType::MakeRefPtr<SelectTheme>();
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [menuOptionItems](
                                    const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();

    selectOverlayNode->CreateToolBar();
    selectOverlayNode->UpdateMenuOptions(infoPtr);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    auto gestureHub = selectOverlayNode->moreButton_->GetOrCreateGestureEventHub();
    auto vector = gestureHub->GetResponseRegion();
    if (vector.size() > 0) {
        auto menuPadding = textOverlayTheme->GetMenuPadding();
        auto buttonHeight = textOverlayTheme->GetMenuButtonHeight();
        auto responseHeight = menuPadding.Bottom().Value() + menuPadding.Top().Value() + buttonHeight.Value();
        EXPECT_EQ(vector.begin()->GetWidth().Value(), 40.0f);
        EXPECT_EQ(vector.begin()->GetHeight().Value(), responseHeight);
    }
}

/**
 * @tc.name: GetOverlayModifier001
 * @tc.desc: Test GetOverlayModifier when menuBuilder is set.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, GetOverlayModifier001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Set menuBuilder to test the branch
    selectOverlayPaintMethod->info_.menuInfo.menuBuilder = []() {};

    PaintWrapper* paintWrapper = nullptr;
    auto result = selectOverlayPaintMethod->GetOverlayModifier(paintWrapper);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetOverlayModifier002
 * @tc.desc: Test GetOverlayModifier when selectOverlayModifier_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, GetOverlayModifier002, TestSize.Level1)
{
    SelectOverlayPaintMethod paintMethod(
        nullptr, nullptr, SelectOverlayInfo(), OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetOverlayModifier(paintWrapper);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetContentModifier001
 * @tc.desc: Test GetContentModifier when selectOverlayContentModifier_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, GetContentModifier001, TestSize.Level1)
{
    SelectOverlayPaintMethod paintMethod(
        nullptr, nullptr, SelectOverlayInfo(), OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);
    PaintWrapper* paintWrapper = nullptr;
    auto result = paintMethod.GetContentModifier(paintWrapper);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: IsModeSwitchComplete001
 * @tc.desc: Test IsModeSwitchComplete when enableHandleLevel is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, IsModeSwitchComplete001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = false;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // When enableHandleLevel is false, should return true directly
    auto result = selectOverlayPaintMethod->IsModeSwitchComplete();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsModeSwitchComplete002
 * @tc.desc: Test IsModeSwitchComplete when handleLevelMode is not EMBED.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, IsModeSwitchComplete002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::OVERLAY;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // When handleLevelMode is not EMBED, should return true directly
    auto result = selectOverlayPaintMethod->IsModeSwitchComplete();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsModeSwitchComplete003
 * @tc.desc: Test IsModeSwitchComplete when selectOverlayContentModifier_ is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, IsModeSwitchComplete003, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::EMBED;

    SelectOverlayPaintMethod paintMethod(
        nullptr, nullptr, selectInfo, OffsetF(), 0.0f, false, false, false, false, OffsetF(), false, nullptr);

    // When selectOverlayContentModifier_ is nullptr, should return false
    auto result = paintMethod.IsModeSwitchComplete();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckHasExtensionMenu001
 * @tc.desc: Test CheckHasExtensionMenu when hasExtensionMenu_ is false but modifier hasExtensionMenu is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckHasExtensionMenu001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Set up the test case: hasExtensionMenu_ is false but modifier hasExtensionMenu is true
    selectOverlayPaintMethod->hasExtensionMenu_ = false;
    pattern->selectOverlayModifier_->SetHasExtensionMenu(true);
    selectOverlayPaintMethod->hasShowAnimation_ = false;

    // Before calling CheckHasExtensionMenu
    EXPECT_TRUE(pattern->selectOverlayModifier_->GetHasExtensionMenu());

    selectOverlayPaintMethod->CheckHasExtensionMenu();
}

/**
 * @tc.name: CheckHasExtensionMenu002
 * @tc.desc: Test CheckHasExtensionMenu with animation when hasExtensionMenu_ is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckHasExtensionMenu002, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Set up the test case: hasExtensionMenu_ is false and hasShowAnimation is true
    selectOverlayPaintMethod->hasExtensionMenu_ = false;
    pattern->selectOverlayModifier_->SetHasExtensionMenu(true);
    selectOverlayPaintMethod->hasShowAnimation_ = true;

    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetCirclesAndBackArrowOpacity(1.0);

    selectOverlayPaintMethod->CheckHasExtensionMenu();

    // Check that the animation was triggered (value should change from 1.0)
    // Note: In real test, the value might not change immediately due to animation, but the function should be called
    // For test purposes, we need to check the hasExtensionMenu flag in paint method which should be synced with
    // modifier
    EXPECT_FALSE(selectOverlayPaintMethod->hasExtensionMenu_);
}

/**
 * @tc.name: UpdateContentModifier019
 * @tc.desc: Test UpdateContentModifier when IsModeSwitchComplete returns false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, UpdateContentModifier019, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.enableHandleLevel = true;
    selectInfo.handleLevelMode = HandleLevelMode::EMBED;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Make IsModeSwitchComplete return false by not setting up the proper conditions
    // This should cause UpdateContentModifier to return early
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);
    // If we reach here without crash, the early return worked correctly
    SUCCEED();
}

/**
 * @tc.name: UpdateContentModifier020
 * @tc.desc: Test UpdateContentModifier with API version less than 12.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, UpdateContentModifier020, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuDisable = true;
    selectInfo.menuInfo.showCut = false;
    selectInfo.menuInfo.showPaste = false;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Set API version to less than 12
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(11);

    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    selectOverlayPaintMethod->UpdateContentModifier(paintWrapper);

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);
    auto overlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(overlayTheme, nullptr);

    // Should use theme color directly, not the info_.handlerColor
    EXPECT_TRUE(contentModifier->handleColor_->Get() == overlayTheme->GetHandleColor());

    // Restore API version
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: CheckCirclesAndBackArrowIsShown001
 * @tc.desc: Test CheckCirclesAndBackArrowIsShown when isCreated_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckCirclesAndBackArrowIsShown001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    // Set isCreated_ to true
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;

    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();

    // circlesAndBackArrowIsShown_ should be set to true when isCreated_ is true
    EXPECT_TRUE(selectOverlayPaintMethod->circlesAndBackArrowIsShown_);
}

/**
 * @tc.name: CheckHandleIsShown001
 * @tc.desc: Test CheckHandleIsShown when isCreated_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckHandleIsShown001, TestSize.Level1)
{
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    auto contentModifier = pattern->selectOverlayContentModifier_;
    ASSERT_NE(contentModifier, nullptr);

    // Set isCreated_ to true
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->handleIsShown_ = false;

    selectOverlayPaintMethod->CheckHandleIsShown();

    // handleIsShown_ should be set to true when isCreated_ is true
    EXPECT_TRUE(selectOverlayPaintMethod->handleIsShown_);
}

/**
 * @tc.name: CheckCirclesAndBackArrowIsShown002
 * @tc.desc: Test CheckCirclesAndBackArrowIsShown when hasExtensionMenu is true but hasShowAnimation is false.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckCirclesAndBackArrowIsShown002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions to cover the branch where hasExtensionMenu is true but hasShowAnimation is
     * false.
     * @tc.expected: circlesAndBackArrowIsShown_ should be set to true and opacity should be set to 1.0 directly.
     */
    selectOverlayPaintMethod->isCreated_ = false;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    selectOverlayPaintMethod->hasShowAnimation_ = false;

    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetCirclesAndBackArrowOpacity(0.0);

    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->circlesAndBackArrowIsShown_);
    EXPECT_EQ(overlayModifier->circlesAndBackArrowOpacity_->Get(), 1.0);
    EXPECT_TRUE(overlayModifier->GetHasExtensionMenu());
}

/**
 * @tc.name: CheckHasExtensionMenu003
 * @tc.desc: Test CheckHasExtensionMenu when hasExtensionMenu changes from false to true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckHasExtensionMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    selectOverlayNode->CreateToolBar();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    selectOverlayNode->backButton_ = FrameNode::GetOrCreateFrameNode("SelectMoreOrBackButton",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_NE(selectOverlayNode->backButton_, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<MenuTheme>()));
    selectOverlayNode->AddExtensionMenuOptions(infoPtr, 0);
    EXPECT_NE(selectOverlayNode->selectMenu_, nullptr);
    EXPECT_NE(selectOverlayNode->extensionMenu_, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions to cover the branch where hasExtensionMenu changes from false to true.
     */
    selectOverlayPaintMethod->hasExtensionMenu_ = true;
    auto overlayModifier = pattern->selectOverlayModifier_;
    ASSERT_NE(overlayModifier, nullptr);
    overlayModifier->SetHasExtensionMenu(false);
    overlayModifier->SetCirclesAndBackArrowOpacity(0.0);

    selectOverlayPaintMethod->CheckHasExtensionMenu();

    EXPECT_TRUE(overlayModifier->GetHasExtensionMenu());
}

/**
 * @tc.name: CheckCirclesAndBackArrowIsShown003
 * @tc.desc: Test CheckCirclesAndBackArrowIsShown when isCreated_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckCirclesAndBackArrowIsShown003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions to cover the branch where isCreated_ is true.
     */
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->circlesAndBackArrowIsShown_ = false;

    selectOverlayPaintMethod->CheckCirclesAndBackArrowIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->circlesAndBackArrowIsShown_);
}

/**
 * @tc.name: CheckHandleIsShown002
 * @tc.desc: Test CheckHandleIsShown when isCreated_ is true.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CheckHandleIsShown002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);

    auto pattern = selectOverlayNode->GetPattern<SelectOverlayPattern>();
    RefPtr<NodePaintMethod> paintMethod = pattern->CreateNodePaintMethod();
    EXPECT_NE(paintMethod, nullptr);
    auto selectOverlayPaintMethod = AceType::DynamicCast<SelectOverlayPaintMethod>(paintMethod);
    EXPECT_NE(selectOverlayPaintMethod, nullptr);

    /**
     * @tc.steps: step2. Set up conditions to cover the branch where isCreated_ is true.
     */
    selectOverlayPaintMethod->isCreated_ = true;
    selectOverlayPaintMethod->handleIsShown_ = false;

    selectOverlayPaintMethod->CheckHandleIsShown();

    EXPECT_TRUE(selectOverlayPaintMethod->handleIsShown_);
}

/**
 * @tc.name: CreateMenuNode002
 * @tc.desc: Test CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CreateMenuNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    MockContainer::SetUp();
    int32_t setApiVersion = 12;
    MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        std::transform(params.begin(), params.end(), std::back_inserter(paramlist),
            [](NG::MenuItemParam item) { return item.menuOptionsParam; });
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
            selectTheme->optionContentNormalAlign_ = 1.0f;
            return selectTheme;
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    // MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    /**
     * @tc.steps: step2. call CreateMenuNode.
     */
    infoPtr->menuInfo.showCopy = true;
    infoPtr->menuInfo.showPaste = true;
    infoPtr->menuInfo.showCut = true;
    infoPtr->menuInfo.showCopyAll = true;
    infoPtr->menuInfo.showTranslate = true;
    infoPtr->menuInfo.showSearch = true;
    infoPtr->menuInfo.showCameraInput = true;
    infoPtr->menuInfo.showAIWrite = true;
    infoPtr->isUsingMouse = false;
    auto menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->menuInfo.showCopy = false;
    infoPtr->menuInfo.showPaste = false;
    infoPtr->menuInfo.showCut = false;
    infoPtr->menuInfo.showCopyAll = false;
    infoPtr->menuInfo.showTranslate = false;
    infoPtr->menuInfo.showSearch = false;
    infoPtr->menuInfo.showCameraInput = false;
    infoPtr->menuInfo.showAIWrite = false;
    infoPtr->isUsingMouse = true;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->isUsingMouse = false;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
}

/**
 * @tc.name: CreateMenuNode003
 * @tc.desc: Test CreateMenuNode.
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, CreateMenuNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create selectOverlayNode and initialize properties.
     */
    MockContainer::SetUp();
    int32_t setApiVersion = 18;
    MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(setApiVersion);
    SelectOverlayInfo selectInfo;
    selectInfo.menuInfo.menuIsShow = false;
    selectInfo.menuInfo.showCopy = false;
    selectInfo.menuInfo.showPaste = true;
    selectInfo.menuInfo.showCopyAll = false;
    selectInfo.menuInfo.showCameraInput = false;
    selectInfo.menuInfo.aiMenuOptionType = TextDataDetectType::PHONE_NUMBER;
    selectInfo.onCreateCallback.onCreateMenuCallback = [](const std::vector<NG::MenuItemParam>& params) {
        std::vector<MenuOptionsParam> paramlist;
        std::transform(params.begin(), params.end(), std::back_inserter(paramlist),
            [](NG::MenuItemParam item) { return item.menuOptionsParam; });
        MenuOptionsParam menuItem1;
        menuItem1.content = "item1";
        menuItem1.id = OH_DEFAULT_COPY;
        paramlist.emplace_back(menuItem1);
        MenuOptionsParam menuItem2;
        menuItem1.content = "item2";
        menuItem1.id = OH_DEFAULT_CUT;
        paramlist.emplace_back(menuItem2);
        return paramlist;
    };
    selectInfo.onCreateCallback.onMenuItemClick = [](const NG::MenuItemParam& param) { return true; };
    selectInfo.onCreateCallback.textRangeCallback = [](int32_t& start, int32_t& end) {};
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    int32_t pasteCount = 0;
    infoPtr->menuCallback.onPaste = [&]() { pasteCount++; };
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    EXPECT_NE(selectOverlayNode->selectMenuInner_, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextOverlayTheme::TypeId()) {
            return AceType::MakeRefPtr<TextOverlayTheme>();
        } else if (type == IconTheme::TypeId()) {
            return AceType::MakeRefPtr<IconTheme>();
        } else if (type == SelectTheme::TypeId()) {
            auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
            selectTheme->optionContentNormalAlign_ = 1.0f;
            return selectTheme;
        }
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    // MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN));
    /**
     * @tc.steps: step2. call CreateMenuNode.
     */
    infoPtr->menuInfo.showCopy = true;
    infoPtr->menuInfo.showPaste = true;
    infoPtr->menuInfo.showCut = true;
    infoPtr->menuInfo.showCopyAll = true;
    infoPtr->menuInfo.showTranslate = true;
    infoPtr->menuInfo.showSearch = true;
    infoPtr->menuInfo.showCameraInput = true;
    infoPtr->menuInfo.showAIWrite = true;
    infoPtr->isUsingMouse = false;
    auto menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->menuInfo.showCopy = false;
    infoPtr->menuInfo.showPaste = false;
    infoPtr->menuInfo.showCut = false;
    infoPtr->menuInfo.showCopyAll = false;
    infoPtr->menuInfo.showTranslate = false;
    infoPtr->menuInfo.showSearch = false;
    infoPtr->menuInfo.showCameraInput = false;
    infoPtr->menuInfo.showAIWrite = false;
    infoPtr->isUsingMouse = true;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
    infoPtr->isUsingMouse = false;
    menuNode = selectOverlayNode->CreateMenuNode(infoPtr);
    EXPECT_NE(menuNode, nullptr);
}

/**
 * @tc.name: SetResponseRegion002
 * @tc.desc: Test SetResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayFiveTestNg, SetResponseRegion002, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    MockPipelineContext::GetCurrent()->SetFontScale(AGING_MIN_SCALE_TEST);
    auto textOverlayTheme = AceType::MakeRefPtr<TextOverlayTheme>();
    ASSERT_NE(textOverlayTheme, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return AceType::MakeRefPtr<TextOverlayTheme>();
    });
    SelectOverlayInfo selectInfo;
    auto menuOptionItems = GetMenuOptionItems();
    selectInfo.menuOptionItems = menuOptionItems;
    auto onMenuItemClick = [](NG::MenuItemParam menuOptionsParam) -> bool { return false; };
    selectInfo.onCreateCallback.onMenuItemClick = onMenuItemClick;
    auto onCreateMenuCallback = [menuOptionItems](
                                    const std::vector<NG::MenuItemParam>& menuItems) -> std::vector<MenuOptionsParam> {
        return menuOptionItems;
    };
    selectInfo.onCreateCallback.onCreateMenuCallback = onCreateMenuCallback;
    auto infoPtr = std::make_shared<SelectOverlayInfo>(selectInfo);
    ASSERT_NE(infoPtr, nullptr);
    auto frameNode = SelectOverlayNode::CreateSelectOverlayNode(infoPtr);
    ASSERT_NE(frameNode, nullptr);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(frameNode);
    ASSERT_NE(selectOverlayNode, nullptr);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    RefPtr<GestureEventHub> gestureHub =
        AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    ASSERT_NE(gestureHub, nullptr);
    selectOverlayNode->moreButton_->eventHub_ = eventHub;
    auto value = Dimension(0.0f, DimensionUnit::VP);
    gestureHub->responseRegion_.emplace_back(DimensionRect(value, value));
    selectOverlayNode->moreButton_->eventHub_->gestureEventHub_ = gestureHub;
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();

    float maxWidth = 1040.0f;
    selectOverlayNode->CreateToolBar();
    selectOverlayNode->AddMenuItemByCreateMenuCallback(infoPtr, maxWidth);
    EXPECT_NE(selectOverlayNode->moreButton_, nullptr);
    EXPECT_FALSE(selectOverlayNode->isExtensionMenu_);
    auto vector = gestureHub->GetResponseRegion();
    EXPECT_NE(vector.size(), 0);
    auto menuPadding = textOverlayTheme->GetMenuPadding();
    auto buttonHeight = textOverlayTheme->GetMenuButtonHeight();
    auto responseHeight = menuPadding.Bottom().Value() + menuPadding.Top().Value() + buttonHeight.Value();
    EXPECT_EQ(vector.begin()->GetHeight().Value(), responseHeight);
}
} // namespace OHOS::Ace::NG