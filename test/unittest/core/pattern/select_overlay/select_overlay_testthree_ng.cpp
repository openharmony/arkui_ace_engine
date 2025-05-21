/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <memory>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/common/manager_interface.h"

#define private public
#define protected public
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#undef protected
#undef private

#define protected public
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#undef protected
#include "core/components_ng/pattern/select_overlay/magnifier_controller.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class SelectOverlayPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SelectOverlayPatternTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    // set SelectTheme to themeManager before using themeManager to get SelectTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SelectOverlayPatternTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

void ResetCallback()
{
    std::cout << "onResetSelection" << std::endl;
}

class MockUINode : public UINode {
public:
    MockUINode(const std::string& tag, int32_t nodeId, bool isRoot = false) : UINode(tag, nodeId) {}
    ~MockUINode() {};

    MOCK_CONST_METHOD0(IsAtomicNode, bool());
};
/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse001
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse001, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(40.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_TRUE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse002
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse002, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(40.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.info_->handleReverse = true;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_TRUE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse003
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse003, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.info_->handleReverse = true;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_FALSE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternCheckHandleReverse004
 * @tc.desc: test CheckHandleReverse
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternCheckHandleReverse004, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    SelectHandleInfo first;
    SelectHandleInfo second;
    first.paintRect = rectF1;
    second.paintRect = rectF2;
    selectOverlayPattern.info_->firstHandle = first;
    selectOverlayPattern.info_->secondHandle = second;
    selectOverlayPattern.CheckHandleReverse();
    EXPECT_FALSE(selectOverlayPattern.info_->handleReverse);
}

/**
 * @tc.name: SelectOverlayPatternUpdateAncestorViewPort001
 * @tc.desc: test UpdateAncestorViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternUpdateAncestorViewPort001, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF1 = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    RectF rectF2 = RectF(40.0f, 30.0f, 120.0f, 180.0f);
    std::optional<RectF> ancestorViewPort = rectF1;
    selectOverlayPattern.info_->ancestorViewPort = rectF2;
    selectOverlayPattern.UpdateAncestorViewPort(ancestorViewPort);
    EXPECT_EQ(selectOverlayPattern.info_->ancestorViewPort, ancestorViewPort);
}

/**
 * @tc.name: SelectOverlayPatternUpdateAncestorViewPort002
 * @tc.desc: test UpdateAncestorViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternUpdateAncestorViewPort002, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    std::optional<RectF> ancestorViewPort = rectF;
    selectOverlayPattern.info_->ancestorViewPort = rectF;
    selectOverlayPattern.UpdateAncestorViewPort(ancestorViewPort);
    EXPECT_EQ(selectOverlayPattern.info_->ancestorViewPort, ancestorViewPort);
}

/**
 * @tc.name: SelectOverlayPatternGetHandlePaintRect001
 * @tc.desc: test GetHandlePaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternGetHandlePaintRect001, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = rectF;
    handleInfo.isPaintHandleWithPoints = false;
    SelectHandlePaintInfo handlePaintInfo;
    handleInfo.paintInfo = handlePaintInfo;
    RectF result = selectOverlayPattern.GetHandlePaintRect(handleInfo);
    EXPECT_EQ(result.GetX(), 20);
    EXPECT_EQ(result.GetY(), 60);
}

/**
 * @tc.name: SelectOverlayPatternGetHandlePaintRect002
 * @tc.desc: test GetHandlePaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternGetHandlePaintRect002, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = rectF;
    handleInfo.isPaintHandleWithPoints = true;
    SelectHandlePaintInfo handlePaintInfo;
    handleInfo.paintInfo = handlePaintInfo;
    RectF result = selectOverlayPattern.GetHandlePaintRect(handleInfo);
    EXPECT_EQ(result.GetX(), 20);
    EXPECT_EQ(result.GetY(), 60);
}

/**
 * @tc.name: SelectOverlayPatternGetHandlePaintRect003
 * @tc.desc: test GetHandlePaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayPatternGetHandlePaintRect003, TestSize.Level1)
{
    std::shared_ptr<SelectOverlayInfo> info = std::make_shared<SelectOverlayInfo>();
    SelectOverlayMode mode = SelectOverlayMode::ALL;
    SelectOverlayPattern selectOverlayPattern = SelectOverlayPattern(info, mode);
    RectF rectF = RectF(20.0f, 60.0f, 240.0f, 360.0f);
    selectOverlayPattern.info_->handleLevelMode = HandleLevelMode::EMBED;
    SelectHandleInfo handleInfo;
    handleInfo.paintRect = rectF;
    handleInfo.isPaintHandleWithPoints = false;
    SelectHandlePaintInfo handlePaintInfo;
    handleInfo.paintInfo = handlePaintInfo;
    RectF result = selectOverlayPattern.GetHandlePaintRect(handleInfo);
    EXPECT_EQ(result.GetX(), 20);
    EXPECT_EQ(result.GetY(), 60);
}

/**
 * @tc.name: SelectOverlayManagerResetSelection001
 * @tc.desc: test ResetSelection
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayManagerResetSelection001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto rootNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(rootNode);
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    bool isMousePressAtSelectedNode = false;
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    SelectedByMouseInfo selectedByMouseInfo;
    auto node = FrameNode::CreateFrameNode("qwe", 4, pattern, false);
    selectedByMouseInfo.selectedNode = node;
    selectedByMouseInfo.onResetSelection = ResetCallback;
    selectOverlayManager.selectedByMouseInfo_ = selectedByMouseInfo;
    selectOverlayManager.ResetSelection(touchPoint, isMousePressAtSelectedNode);
    EXPECT_EQ(selectOverlayManager.selectedByMouseInfo_.selectedNode.Upgrade(), nullptr);
    EXPECT_EQ(selectOverlayManager.selectedByMouseInfo_.onResetSelection, nullptr);
}

/**
 * @tc.name: SelectOverlayManagerResetSelection002
 * @tc.desc: test ResetSelection
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayManagerResetSelection002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto rootNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(rootNode);
    TouchEvent touchPoint;
    touchPoint.type = TouchType::DOWN;
    bool isMousePressAtSelectedNode = false;
    auto selectOverlayItem = FrameNode::CreateFrameNode("xyz", 3, pattern, false);
    selectOverlayItem.Reset();
    selectOverlayManager.selectOverlayItem_ = selectOverlayItem;
    SelectedByMouseInfo selectedByMouseInfo;
    auto node = FrameNode::CreateFrameNode("qwe", 4, pattern, false);
    selectedByMouseInfo.selectedNode = node;
    selectOverlayManager.selectedByMouseInfo_ = selectedByMouseInfo;
    selectOverlayManager.ResetSelection(touchPoint, isMousePressAtSelectedNode);
    EXPECT_EQ(selectOverlayManager.selectedByMouseInfo_.selectedNode.Upgrade(), nullptr);
    EXPECT_EQ(selectOverlayManager.selectedByMouseInfo_.onResetSelection, nullptr);
}

/**
 * @tc.name: SelectOverlayManagerIsTouchInCallerArea001
 * @tc.desc: test IsTouchInCallerArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayManagerIsTouchInCallerArea001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto rootNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(rootNode);
    SelectOverlayInfo selectOverlayInfo;
    std::optional<NG::PointF> point;
    PointF pointOne = PointT(20.0f, 30.0f);
    point.emplace(pointOne);
    selectOverlayManager.selectOverlayInfo_ = selectOverlayInfo;
    selectOverlayManager.selectOverlayInfo_.checkIsTouchInHostArea = [](const OHOS::Ace::NG::PointF& point) -> bool {
        return true;
    };
    std::vector<std::string> touchTestResults;
    touchTestResults.emplace_back("0");
    touchTestResults.clear();
    selectOverlayManager.touchTestResults_ = touchTestResults;
    bool result = selectOverlayManager.IsTouchInCallerArea(point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SelectOverlayManagerIsTouchInCallerArea002
 * @tc.desc: test IsTouchInCallerArea
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayManagerIsTouchInCallerArea002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto rootNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(rootNode);
    SelectOverlayInfo selectOverlayInfo;
    std::optional<NG::PointF> point;
    PointF pointOne = PointT(20.0f, 30.0f);
    point.emplace(pointOne);
    selectOverlayManager.selectOverlayInfo_ = selectOverlayInfo;
    selectOverlayManager.selectOverlayInfo_.checkIsTouchInHostArea = [](const OHOS::Ace::NG::PointF& point) -> bool {
        return false;
    };
    std::vector<std::string> touchTestResults;
    touchTestResults.emplace_back("0");
    touchTestResults.clear();
    selectOverlayManager.touchTestResults_ = touchTestResults;
    bool result = selectOverlayManager.IsTouchInCallerArea(point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SelectOverlayManagerNotifyOnScrollCallback001
 * @tc.desc: test NotifyOnScrollCallback
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayManagerNotifyOnScrollCallback001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto rootNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    SelectOverlayManager selectOverlayManager = SelectOverlayManager(rootNode);
    std::map<int32_t, std::map<int32_t, ScrollableParentCallback>> parentScrollCallbacks;
    parentScrollCallbacks[1] = {};
    selectOverlayManager.parentScrollCallbacks_ = parentScrollCallbacks;
    selectOverlayManager.NotifyOnScrollCallback(1, Axis::HORIZONTAL, 20.0f, 2);
    EXPECT_EQ(selectOverlayManager.parentScrollCallbacks_.count(1), 0);
}

/**
 * @tc.name: SelectOverlayInfoGetCallerNodeAncestorViewPort001
 * @tc.desc: test GetCallerNodeAncestorViewPort
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, SelectOverlayInfoGetCallerNodeAncestorViewPort001, TestSize.Level1)
{
    SelectOverlayInfo info;
    RectF viewPort(20.0f, 20.0f, 180.0f, 190.0f);
    RectF rect(40.0f, 60.0f, 180.0f, 190.0f);
    info.ancestorViewPort.emplace(rect);
    info.GetCallerNodeAncestorViewPort(viewPort);
    EXPECT_EQ(viewPort.GetX(), 40);
}

/**
 * @tc.name: MagnifierController_FindWindowScene001
 * @tc.desc: test FindWindowScene
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, MagnifierController_FindWindowScene001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> weakPattern(pattern);
    MagnifierController controller(weakPattern);
    auto targetNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    RefPtr<UINode> mockUINode = AceType::MakeRefPtr<MockUINode>("tag", 2, false);
    auto node = AceType::MakeRefPtr<MockUINode>("six", 3, false);
    targetNode->parent_ = node;
    auto result = controller.FindWindowScene(targetNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: MagnifierController_FindWindowScene002
 * @tc.desc: test FindWindowScene
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, MagnifierController_FindWindowScene002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> weakPattern(pattern);
    MagnifierController controller(weakPattern);
    auto targetNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    WeakPtr<UINode> node = targetNode;
    targetNode->parent_ = node;
    targetNode->parent_.Upgrade()->tag_ = V2::WINDOW_SCENE_ETS_TAG;
    auto result = controller.FindWindowScene(targetNode);
    EXPECT_NE(result, nullptr);
}

/**
 * @tc.name: MagnifierController_FindWindowScene003
 * @tc.desc: test FindWindowScene
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, MagnifierController_FindWindowScene003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> weakPattern(pattern);
    MagnifierController controller(weakPattern);
    auto targetNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    auto result = controller.FindWindowScene(targetNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: MagnifierController_FindWindowScene004
 * @tc.desc: test FindWindowScene
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, MagnifierController_FindWindowScene004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<Pattern>();
    WeakPtr<Pattern> weakPattern(pattern);
    MagnifierController controller(weakPattern);
    auto targetNode = FrameNode::CreateFrameNode("tag", 2, pattern, false);
    targetNode->tag_ = V2::WINDOW_SCENE_ETS_TAG;
    auto result = controller.FindWindowScene(targetNode);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: TextMenuController.disableSystemServiceMenuItems
 * @tc.desc: test disableSystemServiceMenuItems
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, DisableSystemServiceMenuItems, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    SelectOverlayInfo overlayInfo;
    SelectMenuInfo menuInfo;
    menuInfo.showCopy = false;
    menuInfo.showPaste = false;
    menuInfo.showCopyAll = false;
    menuInfo.showCut = false;
    menuInfo.showAIWrite = true;
    menuInfo.showTranslate = true;
    menuInfo.showSearch = true;
    menuInfo.showCameraInput = true;
    menuInfo.showShare = true;
    overlayInfo.menuInfo = menuInfo;
    std::shared_ptr<SelectOverlayInfo> shareInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 5);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 0);

    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(~NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetChildren().size(), 5);
}

/**
 * @tc.name: TextMenuController.DisableMenuItems
 * @tc.desc: test DisableMenuItems
 * @tc.type: FUNC
 */
HWTEST_F(SelectOverlayPatternTestNg, DisableMenuItems, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));
    SelectOverlayInfo overlayInfo;
    SelectMenuInfo menuInfo;
    menuInfo.showCopy = false;
    menuInfo.showPaste = false;
    menuInfo.showCopyAll = false;
    menuInfo.showCut = false;
    menuInfo.showAIWrite = true;
    menuInfo.showTranslate = true;
    menuInfo.showSearch = true;
    menuInfo.showCameraInput = true;
    menuInfo.showShare = true;
    menuInfo.aiMenuOptionType = TextDataDetectType::ADDRESS;
    overlayInfo.menuInfo = menuInfo;
    std::shared_ptr<SelectOverlayInfo> shareInfo = std::make_shared<SelectOverlayInfo>(overlayInfo);
    auto selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 6);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(NG::DISABLE_AI_WRITER_FLAG|NG::DISABLE_TRANSLATE_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 4);

    AceApplicationInfo::GetInstance().AddTextMenuDisableFlag(
        DISABLE_TRANSLATE_FLAG | DISABLE_SEARCH_FLAG | DISABLE_SHARE_FLAG | DISABLE_CAMERA_INPUT_FLAG |
        DISABLE_AI_WRITER_FLAG | DISABLE_COLLABORATION_SERVICE_FLAG | DISABLE_AI_MENU_ADDRESS_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
            SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 0);

    AceApplicationInfo::GetInstance().SetTextMenuDisableFlags(NG::DISABLE_ALL_FLAG);
    selectOverlayNode = AceType::DynamicCast<SelectOverlayNode>(
        SelectOverlayNode::CreateSelectOverlayNode(shareInfo, SelectOverlayMode::MENU_ONLY));
    ASSERT_NE(selectOverlayNode, nullptr);
    EXPECT_EQ(selectOverlayNode->selectMenuInner_->GetTotalChildCount(), 6);
}
} // namespace OHOS::Ace::NG