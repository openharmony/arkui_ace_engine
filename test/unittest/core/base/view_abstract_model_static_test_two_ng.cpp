/*
 * Copyright (c) 2025 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public
#include "base/subwindow/subwindow_manager.h"
#include "test/mock/base/mock_system_properties.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewAbstractModelStaticTestNg : public testing::Test {};

/**
 * @tc.name: SetBackgroundImagePosition
 * @tc.desc: Test SetBackgroundImagePosition
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, SetBackgroundImagePosition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and renderContext
     */
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. set background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is set correctly
     */
    BackgroundImagePosition bgImgPosition;
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, false);
    EXPECT_TRUE(renderContext->GetBackgroundImagePosition().has_value());
    EXPECT_EQ(renderContext->GetBackgroundImagePosition().value(), bgImgPosition);

    /**
     * @tc.steps: step3. reset background image position and check renderContext's background image position
     * @tc.expected: renderContext's background image position is reset correctly
     */
    ViewAbstractModelStatic::SetBackgroundImagePosition(frameNode, bgImgPosition, true);
    EXPECT_FALSE(renderContext->GetBackgroundImagePosition().has_value());
}

/**
 * @tc.name: CheckMenuIsShow001
 * @tc.desc: Test CheckMenuIsShow returns false when targetNode is nullptr and isShowInSubWindow is false.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShow001, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    int32_t targetId = 1;
    RefPtr<FrameNode> targetNode = nullptr;
    bool isBuildFuncNull = false;
    EXPECT_FALSE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull));
}

/**
 * @tc.name: CheckMenuIsShow002
 * @tc.desc: Test CheckMenuIsShow returns false when subwindow is nullptr and isShowInSubWindow is true.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShow002, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.isShowInSubWindow = true;
    int32_t targetId = 1;
    RefPtr<FrameNode> targetNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    bool isBuildFuncNull = false;
    SubwindowManager::GetInstance()->RemoveSubwindow(Container::CurrentId(), SubwindowType::TYPE_MENU);
    EXPECT_FALSE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull));
}

/**
 * @tc.name: CheckMenuIsShow003
 * @tc.desc: Test CheckMenuIsShow returns false when overlayManager is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShow003, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    int32_t targetId = 1;
    RefPtr<FrameNode> targetNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    bool isBuildFuncNull = false;
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    targetNode->context_ = AceType::RawPtr(pipeline);
    pipeline->overlayManager_ = nullptr;
    EXPECT_FALSE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull));
}

/**
 * @tc.name: CheckMenuIsShow004
 * @tc.desc: Test CheckMenuIsShow returns false when menuNode is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShow004, TestSize.Level1)
{
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    int32_t targetId = 1;
    RefPtr<FrameNode> targetNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    bool isBuildFuncNull = false;
    auto rootNode = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<NG::OverlayManager>(rootNode);
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    pipeline->overlayManager_ = overlayManager;
    targetNode->context_ = AceType::RawPtr(pipeline);
    // overlayManager->GetMenuNode return nullptr
    EXPECT_FALSE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull));
}

/**
 * @tc.name: CheckMenuIsShow005
 * @tc.desc: Test CheckMenuIsShow returns true when all objects are valid.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShow005, TestSize.Level1)
{
    // Arrange
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = false;
    int32_t targetId = 1;
    bool isBuildFuncNull = false;
    auto targetNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    auto rootNode = AceType::MakeRefPtr<FrameNode>("root", -1, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<NG::OverlayManager>(rootNode);
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    pipeline->overlayManager_ = overlayManager;
    targetNode->context_ = AceType::RawPtr(pipeline);
    auto menuNode = AceType::MakeRefPtr<FrameNode>("menu", targetId, AceType::MakeRefPtr<Pattern>());
    auto wrapperPattern = AceType::MakeRefPtr<MenuWrapperPattern>(targetId);
    menuNode->pattern_ = wrapperPattern;
    overlayManager->menuMap_[targetId] = menuNode;
    EXPECT_TRUE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, isBuildFuncNull));
}

/**
 * @tc.name: BindMenu_CheckMenuIsShowTrue_BuildFuncNull
 * @tc.desc: Test BindMenu when CheckMenuIsShow returns true and buildFunc/params are empty.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenu_CheckMenuIsShowTrue_BuildFuncNull, TestSize.Level1)
{
    int32_t targetId = 1;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    auto rootNode = AceType::MakeRefPtr<FrameNode>("root", 0, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<NG::OverlayManager>(rootNode);
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    pipeline->overlayManager_ = overlayManager;
    frameNode->context_ = AceType::RawPtr(pipeline);

    std::vector<NG::OptionParam> params;
    std::function<void()> buildFunc = nullptr;
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = false;

    ViewAbstractModelStatic::BindMenu(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc), menuParam);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    EXPECT_FALSE(gestureHub->bindMenuStatus_.isBindCustomMenu);
}

/**
 * @tc.name: BindMenu_CheckMenuIsShowFalse_MenuIsShowTrue
 * @tc.desc: Test BindMenu when CheckMenuIsShow returns false
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenu_CheckMenuIsShowFalse_MenuIsShowTrue, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("tag", 1, AceType::MakeRefPtr<Pattern>());
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipeline);

    std::vector<NG::OptionParam> params;
    params.emplace_back(NG::OptionParam{});
    std::function<void()> buildFunc = nullptr;
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.isShow = true;
    menuParam.hasTransitionEffect = false;

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ViewAbstractModelStatic::BindMenu(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc), menuParam);
    EXPECT_TRUE(!gestureHub->bindMenuStatus_.isBindCustomMenu);
}

/**
 * @tc.name: BindMenu_isBuildFuncNullTrue
 * @tc.desc: Test BindMenu when isBuildFuncNull is true, gestureHub should be called.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenu_isBuildFuncNullTrue, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("tag", 1, AceType::MakeRefPtr<Pattern>());
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipeline);

    std::vector<NG::OptionParam> params;
    std::function<void()> buildFunc = nullptr;
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ViewAbstractModelStatic::BindMenu(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc), menuParam);
    EXPECT_TRUE(!gestureHub->bindMenuStatus_.isBindCustomMenu);
}

/**
 * @tc.name: BindMenu_BindMenuGestureBranch
 * @tc.desc: Test BindMenu when buildFunc is null
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenu_BindMenuGestureBranch, TestSize.Level1)
{
    int32_t targetId = 1;
    auto frameNode = AceType::MakeRefPtr<FrameNode>("tag", targetId, AceType::MakeRefPtr<Pattern>());
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    frameNode->context_ = AceType::RawPtr(pipeline);
    auto rootNode = AceType::MakeRefPtr<FrameNode>("root", -1, AceType::MakeRefPtr<Pattern>());
    auto overlayManager = AceType::MakeRefPtr<NG::OverlayManager>(rootNode);
    pipeline->overlayManager_ = overlayManager;
    overlayManager->menuMap_[targetId] = frameNode;
    auto wrapperPattern = AceType::MakeRefPtr<MenuWrapperPattern>(targetId);
    frameNode->pattern_ = wrapperPattern;

    std::vector<NG::OptionParam> params;
    params.emplace_back(NG::OptionParam{});
    std::function<void()> buildFunc = nullptr;
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.setShow = true;
    menuParam.isShow = false;

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ViewAbstractModelStatic::BindMenu(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc), menuParam);
    EXPECT_EQ(gestureHub->showMenu_, nullptr);
}

/**
 * @tc.name: BindContextMenuStatic001
 * @tc.desc: Test the BindContextMenuStatic
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindContextMenuStatic001, TestSize.Level1)
{
    /**
     * @tc.steps 1: create node and gestureHub.
     */
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->SetPreviewMode(MenuPreviewMode::NONE);
    std::function<void()> buildMenuFunc = nullptr;
    NG::MenuParam menuParam;

    /**
     * @tc.steps 2: buildMenuFunc is null, clear longPressEvent.
     */
    auto type = ResponseType::RIGHT_CLICK;
    targetNode->destroyCallbacksMap_.clear();
    std::function<void()> previewBuildFunc = []() {};
    viewAbstractModelStatic.BindContextMenuStatic(
        targetNode, type, std::move(buildMenuFunc), menuParam, std::move(previewBuildFunc));
    EXPECT_EQ(gestureHub->GetLongPressEventActuator()->longPressEvent_, nullptr);
}
} // namespace OHOS::Ace::NG