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

#include "gtest/gtest.h"

#define private public
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#undef private

#define protected public
#include "core/components_ng/pattern/select_overlay/select_overlay_pattern.h"
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {} // namespace

class SelectOverlayPatternTestNg : public testing::Test {
public:
};

void ResetCallback()
{
    std::cout << "onResetSelection" << std::endl;
}

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
} // namespace OHOS::Ace::NG