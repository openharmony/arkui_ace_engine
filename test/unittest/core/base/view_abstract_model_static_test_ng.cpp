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
 * @tc.name: ViewAbstractModelStaticTestNg001
 * @tc.desc: Test the SetAccessibilityVirtualNode
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: virtualNode is nullptr.
     */
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    EXPECT_NE(frameNode, nullptr);
    bool isClip = true;
    viewAbstractModelStatic.SetClipEdge(frameNode, isClip);

    int32_t nodeId = 100;
    auto buildFunc = [&nodeId]() -> RefPtr<NG::UINode> {
        nodeId = 123;
        return nullptr;
    };
    viewAbstractModelStatic.SetAccessibilityVirtualNode(frameNode, std::move(buildFunc));
    EXPECT_NE(nodeId, 100);

    /**
     * @tc.steps: virtualNode is not nullptr.
     */
    nodeId = 100;
    auto buildFuncs = [&nodeId]() -> RefPtr<NG::UINode> {
        nodeId = 123;
        auto pattern = AceType::MakeRefPtr<Pattern>();
        auto frameNodes = AceType::MakeRefPtr<FrameNode>("tag_name", nodeId, pattern);
        return frameNodes;
    };
    viewAbstractModelStatic.SetAccessibilityVirtualNode(frameNode, std::move(buildFuncs));
    EXPECT_NE(nodeId, 100);
}

/**
 * @tc.name: ViewAbstractModelStaticTestNg002
 * @tc.desc: Test the BindContextMenu
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg002, TestSize.Level1)
{
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->SetPreviewMode(MenuPreviewMode::NONE);
    auto type = ResponseType::LONG_PRESS;
    std::function<void()> buildMenuFunc = []() {};

    NG::MenuParam menuParam;
    menuParam.hasTransitionEffect = true;
    menuParam.hasPreviewTransitionEffect = true;
    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;
    menuParam.previewMode = MenuPreviewMode::IMAGE;

    std::function<void()> previewBuildFunc = []() {};
    viewAbstractModelStatic.BindContextMenu(targetNode, type, buildMenuFunc, menuParam, previewBuildFunc);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->GetPreviewMode(), MenuPreviewMode::IMAGE);
}

/**
 * @tc.name: ViewAbstractModelStaticTestNg003
 * @tc.desc: Test the BindDragWithContextMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg003, TestSize.Level1)
{
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    NG::MenuParam menuParam;

    /**
     * @tc.steps: gestureHub is nullptr.
     */
    auto targetNodes = AceType::RawPtr(FRAME_NODE_REGISTER);
    targetNodes->eventHub_ = nullptr;
    targetNodes->pattern_ = nullptr;
    viewAbstractModelStatic.BindDragWithContextMenuParams(targetNodes, menuParam);
    EXPECT_EQ(targetNodes->GetOrCreateGestureEventHub(), nullptr);

    /**
     * @tc.steps: contextMenuRegisterType is CUSTOM_TYPE.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    viewAbstractModelStatic.BindDragWithContextMenuParams(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: menuBindType is RIGHT_CLICK.
     */
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    viewAbstractModelStatic.BindDragWithContextMenuParams(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: contextMenuRegisterType is NORMAL_TYPE.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::NORMAL_TYPE;
    viewAbstractModelStatic.BindDragWithContextMenuParams(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: menuBindType is LONG_PRESS.
     */
    menuParam.menuBindType = MenuBindingType::LONG_PRESS;
    viewAbstractModelStatic.BindDragWithContextMenuParams(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);
}

/**
 * @tc.name: ViewAbstractModelStaticTestNg004
 * @tc.desc: Test the RegisterContextMenuKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg004, TestSize.Level1)
{
    const auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    std::function<void()> buildFunc = []() {};
    NG::MenuParam menuParam;
    menuParam.hasTransitionEffect = true;
    menuParam.hasPreviewTransitionEffect = true;
    menuParam.type = MenuType::MENU;
    menuParam.isShow = true;
    targetNode->GetOrCreateFocusHub()->onKeyEventsInternal_.clear();
    ViewAbstractModelStatic::RegisterContextMenuKeyEvent(targetNode, buildFunc, menuParam);
    EXPECT_FALSE(targetNode->GetOrCreateFocusHub()->onKeyEventsInternal_.empty());
}

/**
 * @tc.name: ViewAbstractModelStaticTestNg005
 * @tc.desc: Test the BindContextMenuStatic
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg005, TestSize.Level1)
{
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    gestureHub->SetPreviewMode(MenuPreviewMode::NONE);
    std::function<void()> buildMenuFunc = []() {};
    NG::MenuParam menuParam;

    /**
     * @tc.steps: type is RIGHT_CLICK.
     */
    auto type = ResponseType::RIGHT_CLICK;
    targetNode->destroyCallbacksMap_.clear();
    std::function<void()> previewBuildFunc = []() {};
    viewAbstractModelStatic.BindContextMenuStatic(
        targetNode, type, std::move(buildMenuFunc), menuParam, std::move(previewBuildFunc));
    EXPECT_FALSE(targetNode->destroyCallbacksMap_.empty());

    /**
     * @tc.steps: contextMenuRegisterType is CUSTOM_TYPE.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    targetNode->destroyCallbacksMap_.clear();
    viewAbstractModelStatic.BindContextMenuStatic(
        targetNode, type, std::move(buildMenuFunc), menuParam, std::move(previewBuildFunc));
    EXPECT_FALSE(targetNode->destroyCallbacksMap_.empty());

    /**
     * @tc.steps: subwindow is not null.
     */
    SubwindowManager::GetInstance()->RemoveSubwindow(Container::CurrentId(), SubwindowType::TYPE_DIALOG);
    auto subwindow = Subwindow::CreateSubwindow(Container::CurrentId());
    SubwindowManager::GetInstance()->AddSubwindow(Container::CurrentId(), subwindow);
    viewAbstractModelStatic.BindContextMenuStatic(
        targetNode, type, std::move(buildMenuFunc), menuParam, std::move(previewBuildFunc));
    ASSERT_NE(SubwindowManager::GetInstance()->GetSubwindow(Container::CurrentId()), nullptr);
}

/**
 * @tc.name: ViewAbstractModelStaticTestNg006
 * @tc.desc: Test the BindDragWithContextMenuParamsStatic
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ViewAbstractModelStaticTestNg006, TestSize.Level1)
{
    ViewAbstractModelStatic viewAbstractModelStatic;
    auto targetNode = FrameNode::CreateFrameNode(TAG_CHILD, 2, MOCK_PATTERN_ROOT, false);
    NG::MenuParam menuParam;

    /**
     * @tc.steps: gestureHub is nullptr.
     */
    auto targetNodes = AceType::RawPtr(FRAME_NODE_REGISTER);
    targetNodes->eventHub_ = nullptr;
    targetNodes->pattern_ = nullptr;
    viewAbstractModelStatic.BindDragWithContextMenuParamsStatic(targetNodes, menuParam);
    EXPECT_EQ(targetNodes->GetOrCreateGestureEventHub(), nullptr);

    /**
     * @tc.steps: contextMenuRegisterType is CUSTOM_TYPE.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    viewAbstractModelStatic.BindDragWithContextMenuParamsStatic(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: menuBindType is RIGHT_CLICK.
     */
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    viewAbstractModelStatic.BindDragWithContextMenuParamsStatic(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: contextMenuRegisterType is NORMAL_TYPE.
     */
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::NORMAL_TYPE;
    viewAbstractModelStatic.BindDragWithContextMenuParamsStatic(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);

    /**
     * @tc.steps: menuBindType is LONG_PRESS.
     */
    menuParam.menuBindType = MenuBindingType::LONG_PRESS;
    viewAbstractModelStatic.BindDragWithContextMenuParamsStatic(AceType::RawPtr(targetNode), menuParam);
    EXPECT_EQ(targetNode->GetOrCreateGestureEventHub()->bindMenuStatus_.isBindCustomMenu, true);
}
} // namespace OHOS::Ace::NG