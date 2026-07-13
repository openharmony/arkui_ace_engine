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
#include "base/geometry/shape.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components/common/properties/border_image.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/pattern/menu/wrapper/menu_wrapper_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class ViewAbstractModelStaticTestNg : public testing::Test {};

namespace {
constexpr int32_t STATIC_TEST_NODE_ID = 10001;
constexpr float STATIC_TEST_FLOAT_ONE = 1.0f;
constexpr float STATIC_TEST_FLOAT_TWO = 2.0f;
constexpr float STATIC_TEST_FLOAT_THREE = 3.0f;
constexpr float STATIC_TEST_FLOAT_FOUR = 4.0f;
constexpr float STATIC_TEST_FLOAT_FIVE = 5.0f;
constexpr float STATIC_TEST_FLOAT_SIX = 6.0f;

RefPtr<FrameNode> CreateStaticFrameNode(int32_t nodeId = STATIC_TEST_NODE_ID)
{
    return AceType::MakeRefPtr<FrameNode>("staticTest", nodeId, AceType::MakeRefPtr<Pattern>());
}

RefPtr<PipelineContext> AttachPipelineContext(const RefPtr<FrameNode>& frameNode)
{
    auto pipeline = AceType::MakeRefPtr<NG::PipelineContext>();
    auto rootNode = AceType::MakeRefPtr<FrameNode>("root", -1, AceType::MakeRefPtr<Pattern>());
     pipeline->rootNode_ = rootNode;
    pipeline->overlayManager_ = AceType::MakeRefPtr<NG::OverlayManager>(rootNode);
    frameNode->context_ = AceType::RawPtr(pipeline);
    return pipeline;
}

void PutMenuNode(const RefPtr<OverlayManager>& overlayManager, int32_t targetId, const RefPtr<FrameNode>& menuNode)
{
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->menuMap_[targetId] = menuNode;
}

RefPtr<FrameNode> CreateMenuWrapperNode(int32_t targetId)
{
    auto wrapperPattern = AceType::MakeRefPtr<MenuWrapperPattern>(targetId);
    auto menuNode = AceType::MakeRefPtr<FrameNode>("menu", targetId, wrapperPattern);
    return menuNode;
}

BorderWidthProperty CreateBorderWidthProperty(float left, float top, float right, float bottom)
{
    BorderWidthProperty borderWidth;
    borderWidth.leftDimen = Dimension(left, DimensionUnit::VP);
    borderWidth.topDimen = Dimension(top, DimensionUnit::VP);
    borderWidth.rightDimen = Dimension(right, DimensionUnit::VP);
    borderWidth.bottomDimen = Dimension(bottom, DimensionUnit::VP);
    borderWidth.multiValued = true;
    return borderWidth;
}

BorderRadiusProperty CreateBorderRadiusProperty(float leftTop, float rightTop, float rightBottom, float leftBottom)
{
    BorderRadiusProperty borderRadius;
    borderRadius.radiusTopLeft = Dimension(leftTop, DimensionUnit::VP);
    borderRadius.radiusTopRight = Dimension(rightTop, DimensionUnit::VP);
    borderRadius.radiusBottomRight = Dimension(rightBottom, DimensionUnit::VP);
    borderRadius.radiusBottomLeft = Dimension(leftBottom, DimensionUnit::VP);
    borderRadius.multiValued = true;
    return borderRadius;
}

BorderColorProperty CreateBorderColorProperty()
{
    BorderColorProperty borderColor;
    borderColor.leftColor = Color::BLUE;
    borderColor.topColor = Color::RED;
    borderColor.rightColor = Color::GREEN;
    borderColor.bottomColor = Color::BLACK;
    borderColor.multiValued = true;
    return borderColor;
}

BorderStyleProperty CreateBorderStyleProperty()
{
    BorderStyleProperty borderStyle;
    borderStyle.styleLeft = BorderStyle::SOLID;
    borderStyle.styleTop = BorderStyle::DASHED;
    borderStyle.styleRight = BorderStyle::DOTTED;
    borderStyle.styleBottom = BorderStyle::NONE;
    borderStyle.multiValued = true;
    return borderStyle;
}
} // namespace

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
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->menuMap_[targetId] = menuNode;
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
    overlayManager->CheckMenuManager();
    auto menuManager = AceType::DynamicCast<MenuManager>(overlayManager->menuManager_);
    ASSERT_NE(menuManager, nullptr);
    menuManager->menuMap_[targetId] = frameNode;
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

/**
 * @tc.name: BindMenuGestureWithParams
 * @tc.desc: Test BindMenuGesture registers menu click and touch callbacks when option params are supplied.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenuGestureWithParams, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and attach pipeline context.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = AttachPipelineContext(frameNode);
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. call BindMenuGesture with option params.
     * @tc.expected: gesture callbacks are registered.
     */
    std::vector<NG::OptionParam> params;
    params.emplace_back(NG::OptionParam {});
    std::function<void()> buildFunc = nullptr;
    MenuParam menuParam;
    ViewAbstractModelStatic::BindMenuGesture(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc),
        menuParam);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(gestureHub->showMenu_, nullptr);
    EXPECT_NE(gestureHub->bindMenuTouch_, nullptr);
}

/**
 * @tc.name: BindMenuGestureWithBuilder
 * @tc.desc: Test BindMenuGesture registers menu click and touch callbacks when builder is supplied.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindMenuGestureWithBuilder, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and buildFunc.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pipeline = AttachPipelineContext(frameNode);
    ASSERT_NE(pipeline, nullptr);
    bool buildCalled = false;
    std::function<void()> buildFunc = [&buildCalled]() { buildCalled = true; };
    std::vector<NG::OptionParam> params;
    MenuParam menuParam;

    /**
     * @tc.steps: step2. call BindMenuGesture with builder.
     * @tc.expected: click and touch callbacks are registered, builder is not executed during registration.
     */
    ViewAbstractModelStatic::BindMenuGesture(AceType::RawPtr(frameNode), std::move(params), std::move(buildFunc),
        menuParam);

    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(gestureHub->showMenu_, nullptr);
    EXPECT_NE(gestureHub->bindMenuTouch_, nullptr);
    EXPECT_FALSE(buildCalled);
}

/**
 * @tc.name: CheckMenuIsShowWithTransition
 * @tc.desc: Test CheckMenuIsShow returns true and touches transition branch when menu node exists.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShowWithTransition, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node, pipeline and menu wrapper.
     */
    constexpr int32_t targetId = 10002;
    auto targetNode = CreateStaticFrameNode(targetId);
    ASSERT_NE(targetNode, nullptr);
    auto pipeline = AttachPipelineContext(targetNode);
    ASSERT_NE(pipeline, nullptr);
    auto menuNode = CreateMenuWrapperNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    PutMenuNode(pipeline->overlayManager_, targetId, menuNode);

    /**
     * @tc.steps: step2. call CheckMenuIsShow with transition flag.
     * @tc.expected: returns true because menu node and wrapper pattern can be found.
     */
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.hasTransitionEffect = true;
    EXPECT_TRUE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, false));
}

/**
 * @tc.name: CheckMenuIsShowHideShownMenu
 * @tc.desc: Test CheckMenuIsShow handles shown menu when caller closes it by show state.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, CheckMenuIsShowHideShownMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create shown menu wrapper in overlay manager.
     */
    constexpr int32_t targetId = 10003;
    auto targetNode = CreateStaticFrameNode(targetId);
    ASSERT_NE(targetNode, nullptr);
    auto pipeline = AttachPipelineContext(targetNode);
    ASSERT_NE(pipeline, nullptr);
    auto menuNode = CreateMenuWrapperNode(targetId);
    ASSERT_NE(menuNode, nullptr);
    auto wrapperPattern = menuNode->GetPattern<MenuWrapperPattern>();
    ASSERT_NE(wrapperPattern, nullptr);
    wrapperPattern->SetMenuStatus(MenuStatus::SHOW);
    wrapperPattern->SetIsOpenMenu(false);
    PutMenuNode(pipeline->overlayManager_, targetId, menuNode);

    /**
     * @tc.steps: step2. call CheckMenuIsShow with setShow false.
     * @tc.expected: returns true after hide branch is visited.
     */
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.setShow = true;
    menuParam.isShow = false;
    EXPECT_TRUE(ViewAbstractModelStatic::CheckMenuIsShow(menuParam, targetId, targetNode, false));
}

/**
 * @tc.name: BindContextMenuStaticWithOptionsEmpty
 * @tc.desc: Test BindContextMenuStaticWithOptions clears context menu event when params are empty.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindContextMenuStaticWithOptionsEmpty, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node with existing input and long press callbacks.
     */
    auto targetNode = CreateStaticFrameNode();
    ASSERT_NE(targetNode, nullptr);
    auto pipeline = AttachPipelineContext(targetNode);
    ASSERT_NE(pipeline, nullptr);
    auto inputHub = targetNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    inputHub->BindContextMenu([](MouseInfo&) {});
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetLongPressEvent(AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {}));

    /**
     * @tc.steps: step2. call BindContextMenuStaticWithOptions with empty params.
     * @tc.expected: input callback is replaced and long press event is cleared.
     */
    std::vector<NG::OptionParam> params;
    MenuParam menuParam;
    std::function<void()> previewBuildFunc = nullptr;
    ViewAbstractModelStatic::BindContextMenuStaticWithOptions(targetNode, ResponseType::RIGHT_CLICK, std::move(params),
        menuParam, std::move(previewBuildFunc));

    EXPECT_NE(inputHub->showMenu_, nullptr);
    EXPECT_EQ(gestureHub->GetLongPressEventActuator()->longPressEvent_, nullptr);
}

/**
 * @tc.name: BindContextMenuStaticWithOptionsRightClick
 * @tc.desc: Test BindContextMenuStaticWithOptions registers right-click and key event callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindContextMenuStaticWithOptionsRightClick, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and option params.
     */
    auto targetNode = CreateStaticFrameNode();
    ASSERT_NE(targetNode, nullptr);
    auto pipeline = AttachPipelineContext(targetNode);
    ASSERT_NE(pipeline, nullptr);
    std::vector<NG::OptionParam> params;
    params.emplace_back(NG::OptionParam {});
    MenuParam menuParam;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    menuParam.isShowHoverImage = true;
    std::function<void()> previewBuildFunc = nullptr;

    /**
     * @tc.steps: step2. bind context menu with RIGHT_CLICK.
     * @tc.expected: right-click callback and focus key callback are registered; menu param is normalized.
     */
    ViewAbstractModelStatic::BindContextMenuStaticWithOptions(targetNode, ResponseType::RIGHT_CLICK, std::move(params),
        menuParam, std::move(previewBuildFunc));

    auto inputHub = targetNode->GetOrCreateInputEventHub();
    auto focusHub = targetNode->GetOrCreateFocusHub();
    ASSERT_NE(inputHub, nullptr);
    ASSERT_NE(focusHub, nullptr);
    EXPECT_NE(inputHub->showMenu_, nullptr);
    EXPECT_FALSE(focusHub->onKeyEventsInternal_.empty());
    EXPECT_EQ(menuParam.previewMode, MenuPreviewMode::NONE);
    EXPECT_FALSE(menuParam.isShowHoverImage);
    EXPECT_EQ(menuParam.menuBindType, MenuBindingType::RIGHT_CLICK);
}

/**
 * @tc.name: BindContextMenuStaticCustomType
 * @tc.desc: Test BindContextMenuStatic enters CUSTOM_TYPE path and marks overlay binding.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindContextMenuStaticCustomType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and menu param.
     */
    auto targetNode = CreateStaticFrameNode();
    ASSERT_NE(targetNode, nullptr);
    auto pipeline = AttachPipelineContext(targetNode);
    ASSERT_NE(pipeline, nullptr);
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::CUSTOM_TYPE;
    menuParam.isShow = false;
    std::function<void()> buildFunc = []() {};
    std::function<void()> previewBuildFunc = nullptr;

    /**
     * @tc.steps: step2. bind custom context menu.
     * @tc.expected: layout property records overlay binding and destroy callback is registered.
     */
    ViewAbstractModelStatic::BindContextMenuStatic(targetNode, ResponseType::RIGHT_CLICK, std::move(buildFunc),
        menuParam, std::move(previewBuildFunc));

    auto layoutProperty = targetNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetIsBindOverlay().value_or(false));
    EXPECT_FALSE(targetNode->destroyCallbacksMap_.empty());
}

/**
 * @tc.name: RegisterContextMenuKeyEventOptions
 * @tc.desc: Test RegisterContextMenuKeyEventOptions stores a context-menu key event callback.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, RegisterContextMenuKeyEventOptions, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and option params.
     */
    auto targetNode = CreateStaticFrameNode();
    ASSERT_NE(targetNode, nullptr);
    std::vector<NG::OptionParam> params;
    params.emplace_back(NG::OptionParam {});
    MenuParam menuParam;
    auto focusHub = targetNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->onKeyEventsInternal_.clear();

    /**
     * @tc.steps: step2. register key event.
     * @tc.expected: internal key event map is not empty.
     */
    ViewAbstractModelStatic::RegisterContextMenuKeyEventOptions(targetNode, std::move(params), menuParam);
    EXPECT_FALSE(focusHub->onKeyEventsInternal_.empty());
}

/**
 * @tc.name: BindDragWithContextMenuParamsStaticPreviewScale
 * @tc.desc: Test BindDragWithContextMenuParamsStatic stores preview mode, show status and preview scale.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindDragWithContextMenuParamsStaticPreviewScale, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create target node and menu param with custom scale.
     */
    auto targetNode = CreateStaticFrameNode();
    ASSERT_NE(targetNode, nullptr);
    MenuParam menuParam;
    menuParam.contextMenuRegisterType = ContextMenuRegisterType::NORMAL_TYPE;
    menuParam.menuBindType = MenuBindingType::LONG_PRESS;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    menuParam.isShow = true;
    menuParam.previewAnimationOptions.scaleTo = STATIC_TEST_FLOAT_TWO;

    /**
     * @tc.steps: step2. bind drag params.
     * @tc.expected: gesture hub keeps long press menu status and custom scale.
     */
    ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(targetNode, menuParam);

    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_EQ(gestureHub->GetPreviewMode(), MenuPreviewMode::IMAGE);
    EXPECT_TRUE(gestureHub->contextMenuShowStatus_);
    EXPECT_EQ(gestureHub->menuBindingType_, MenuBindingType::LONG_PRESS);
    EXPECT_EQ(gestureHub->GetMenuPreviewScale(), STATIC_TEST_FLOAT_TWO);

    /**
     * @tc.steps: step3. bind right-click params.
     * @tc.expected: right-click binding does not overwrite preview scale.
     */
    menuParam.menuBindType = MenuBindingType::RIGHT_CLICK;
    menuParam.previewAnimationOptions.scaleTo = STATIC_TEST_FLOAT_THREE;
    ViewAbstractModelStatic::BindDragWithContextMenuParamsStatic(targetNode, menuParam);
    EXPECT_EQ(gestureHub->GetMenuPreviewScale(), STATIC_TEST_FLOAT_TWO);
    EXPECT_EQ(gestureHub->menuBindingType_, MenuBindingType::RIGHT_CLICK);
}

/**
 * @tc.name: TextHintAndSamePageStatic
 * @tc.desc: Test text hint and same page setter paths.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, TextHintAndSamePageStatic, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set text hint and same page.
     * @tc.expected: property stores same page value and text hint is marked.
     */
    ViewAbstractModelStatic::SetAccessibilityTextHint(AceType::RawPtr(frameNode), "hint");
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(AceType::RawPtr(frameNode), "pageA");
    ASSERT_TRUE(accessibilityProperty->textTypeHint_.has_value());
    EXPECT_EQ(accessibilityProperty->textTypeHint_.value(), "hint");
    EXPECT_TRUE(accessibilityProperty->HasAccessibilitySamePage());
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), "pageA");

    /**
     * @tc.steps: step3. call with same page mode again.
     * @tc.expected: property value stays unchanged.
     */
    ViewAbstractModelStatic::SetAccessibilityUseSamePage(AceType::RawPtr(frameNode), "pageA");
    EXPECT_EQ(accessibilityProperty->GetAccessibilitySamePage(), "pageA");
}

/**
 * @tc.name: VirtualNodeNullAndValidStatic
 * @tc.desc: Test virtual node setter clears and stores builder output.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, VirtualNodeNullAndValidStatic, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create parent and virtual frame node.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    /**
     * @tc.steps: step2. set nullptr builder.
     * @tc.expected: virtual node flag is cleared.
     */
    std::function<RefPtr<NG::UINode>()> nullBuilder = nullptr;
    ViewAbstractModelStatic::SetAccessibilityVirtualNode(AceType::RawPtr(frameNode), std::move(nullBuilder));
    EXPECT_FALSE(frameNode->hasAccessibilityVirtualNode_);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityVirtualNode(), nullptr);

    /**
     * @tc.steps: step3. set valid virtual frame node builder.
     * @tc.expected: virtual node is saved.
     */
    auto virtualNode = CreateStaticFrameNode(10004);
    std::function<RefPtr<NG::UINode>()> buildFunc = [virtualNode]() { return virtualNode; };
    ViewAbstractModelStatic::SetAccessibilityVirtualNode(AceType::RawPtr(frameNode), std::move(buildFunc));
    EXPECT_TRUE(frameNode->hasAccessibilityVirtualNode_);
    EXPECT_EQ(accessibilityProperty->GetAccessibilityVirtualNode(), virtualNode);
}

/**
 * @tc.name: HoverSetAndDisableStatic
 * @tc.desc: Test hover callback setters update input hub state.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, HoverSetAndDisableStatic, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and hover callback.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto inputHub = frameNode->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    OnAccessibilityHoverFunc hoverFunc = [](bool, AccessibilityHoverInfo&) {};

    /**
     * @tc.steps: step2. set and disable hover callback.
     * @tc.expected: user callback is set and then cleared.
     */
    ViewAbstractModelStatic::SetOnAccessibilityHover(AceType::RawPtr(frameNode), std::move(hoverFunc));
    EXPECT_TRUE(inputHub->HasAccessibilityHoverEvent());

    ViewAbstractModelStatic::DisableOnAccessibilityHover(AceType::RawPtr(frameNode));
    EXPECT_FALSE(inputHub->HasAccessibilityHoverEvent());
}

/**
 * @tc.name: BindBackgroundAndResetBackground
 * @tc.desc: Test BindBackground stores alignment and ResetBackground restores background flags.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BindBackgroundAndResetBackground, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node with background builder.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    std::function<RefPtr<UINode>()> buildFunc = []() -> RefPtr<UINode> {
        return AceType::MakeRefPtr<FrameNode>("background", 10005, AceType::MakeRefPtr<Pattern>());
    };

    /**
     * @tc.steps: step2. bind background with alignment.
     * @tc.expected: render context stores background alignment.
     */
    ViewAbstractModelStatic::BindBackground(AceType::RawPtr(frameNode), std::move(buildFunc), Alignment::BOTTOM_RIGHT);
    ASSERT_TRUE(renderContext->GetBackgroundAlign().has_value());
    EXPECT_EQ(renderContext->GetBackgroundAlign().value(), Alignment::BOTTOM_RIGHT);

    /**
     * @tc.steps: step3. bind background without alignment, then reset background.
     * @tc.expected: alignment is reset and reset values are written.
     */
    std::function<RefPtr<UINode>()> emptyBuildFunc = nullptr;
    ViewAbstractModelStatic::BindBackground(AceType::RawPtr(frameNode), std::move(emptyBuildFunc), std::nullopt);
    EXPECT_FALSE(renderContext->GetBackgroundAlign().has_value());

    ViewAbstractModelStatic::ResetBackground(AceType::RawPtr(frameNode));
    EXPECT_TRUE(renderContext->GetIsTransitionBackground().value_or(false));
    EXPECT_FALSE(renderContext->GetBuilderBackgroundFlag().value_or(true));
    EXPECT_EQ(renderContext->GetBackgroundAlign().value_or(Alignment::TOP_LEFT), Alignment::CENTER);
    EXPECT_EQ(renderContext->GetCustomBackgroundColor().value_or(Color::BLACK), Color::TRANSPARENT);
}

/**
 * @tc.name: FlexSizingStaticSetters
 * @tc.desc: Test flex grow, shrink and basis setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, FlexSizingStaticSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and layout property.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. set flex grow, shrink and percent basis.
     * @tc.expected: layout flex item property is updated; percent basis is converted to auto.
     */
    ViewAbstractModelStatic::SetFlexGrow(AceType::RawPtr(frameNode), STATIC_TEST_FLOAT_TWO);
    ViewAbstractModelStatic::SetFlexShrink(AceType::RawPtr(frameNode), STATIC_TEST_FLOAT_THREE);
    ViewAbstractModelStatic::SetFlexBasis(AceType::RawPtr(frameNode), Dimension(50.0, DimensionUnit::PERCENT));

    const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    ASSERT_NE(flexItemProperty, nullptr);
    EXPECT_EQ(flexItemProperty->GetFlexGrow().value_or(0.0f), STATIC_TEST_FLOAT_TWO);
    EXPECT_EQ(flexItemProperty->GetFlexShrink().value_or(0.0f), STATIC_TEST_FLOAT_THREE);
    ASSERT_TRUE(flexItemProperty->GetFlexBasis().has_value());
    EXPECT_EQ(flexItemProperty->GetFlexBasis()->Unit(), DimensionUnit::AUTO);

    /**
     * @tc.steps: step3. reset shrink and set empty basis.
     * @tc.expected: shrink is reset and basis becomes zero.
     */
    ViewAbstractModelStatic::ResetFlexShrink(AceType::RawPtr(frameNode));
    EXPECT_FALSE(flexItemProperty->GetFlexShrink().has_value());

    ViewAbstractModelStatic::SetFlexBasis(AceType::RawPtr(frameNode), std::nullopt);
    ASSERT_TRUE(flexItemProperty->GetFlexBasis().has_value());
    EXPECT_EQ(flexItemProperty->GetFlexBasis()->Value(), 0.0);
}

/**
 * @tc.name: PaddingMarginAspectLayoutSetters
 * @tc.desc: Test padding, margin, aspect ratio, layout weight and direction setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, PaddingMarginAspectLayoutSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and properties.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    PaddingProperty padding;
    padding.SetEdges(CalcLength(STATIC_TEST_FLOAT_FOUR));
    PaddingProperty margin;
    margin.SetEdges(CalcLength(STATIC_TEST_FLOAT_FIVE));

    /**
     * @tc.steps: step2. set layout related values.
     * @tc.expected: layout property keeps the values.
     */
    ViewAbstractModelStatic::SetPadding(AceType::RawPtr(frameNode), padding);
    ViewAbstractModelStatic::SetMargin(AceType::RawPtr(frameNode), margin);
    ViewAbstractModelStatic::SetAspectRatio(AceType::RawPtr(frameNode), STATIC_TEST_FLOAT_TWO);
    ViewAbstractModelStatic::SetLayoutWeight(AceType::RawPtr(frameNode), STATIC_TEST_FLOAT_THREE);
    ViewAbstractModelStatic::SetAlignSelf(AceType::RawPtr(frameNode), FlexAlign::CENTER);
    ViewAbstractModelStatic::SetLayoutGravity(AceType::RawPtr(frameNode), Alignment::BOTTOM_CENTER);
    ViewAbstractModelStatic::SetLayoutDirection(AceType::RawPtr(frameNode), TextDirection::RTL);

    ASSERT_NE(layoutProperty->GetPaddingProperty(), nullptr);
    ASSERT_NE(layoutProperty->GetMarginProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetPaddingProperty()->left.value(), CalcLength(STATIC_TEST_FLOAT_FOUR));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(STATIC_TEST_FLOAT_FIVE));
    EXPECT_TRUE(layoutProperty->HasAspectRatio());
    EXPECT_EQ(layoutProperty->GetAspectRatio(), STATIC_TEST_FLOAT_TWO);
    EXPECT_EQ(layoutProperty->GetLayoutDirection(), TextDirection::RTL);
    const auto& flexItemProperty = layoutProperty->GetFlexItemProperty();
    ASSERT_NE(flexItemProperty, nullptr);
    EXPECT_EQ(flexItemProperty->GetAlignSelf().value_or(FlexAlign::AUTO), FlexAlign::CENTER);

    /**
     * @tc.steps: step3. reset padding, margin and aspect ratio.
     * @tc.expected: padding and margin are reset to zero; aspect ratio flag is cleared.
     */
    ViewAbstractModelStatic::SetPadding(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::SetMargin(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::ResetAspectRatio(AceType::RawPtr(frameNode));
    EXPECT_EQ(layoutProperty->GetPaddingProperty()->left.value(), CalcLength(0.0));
    EXPECT_EQ(layoutProperty->GetMarginProperty()->left.value(), CalcLength(0.0));
    EXPECT_FALSE(layoutProperty->HasAspectRatio());
}

/**
 * @tc.name: BorderRenderSetters
 * @tc.desc: Test border style, width, color, radius and render strategy setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BorderRenderSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and render context.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderStyle = CreateBorderStyleProperty();
    auto borderWidth = CreateBorderWidthProperty(STATIC_TEST_FLOAT_ONE, STATIC_TEST_FLOAT_TWO,
        STATIC_TEST_FLOAT_THREE, STATIC_TEST_FLOAT_FOUR);
    auto borderColor = CreateBorderColorProperty();
    auto borderRadius = CreateBorderRadiusProperty(STATIC_TEST_FLOAT_ONE, STATIC_TEST_FLOAT_TWO,
        STATIC_TEST_FLOAT_THREE, STATIC_TEST_FLOAT_FOUR);

    /**
     * @tc.steps: step2. set border render properties.
     * @tc.expected: render context keeps corresponding border properties.
     */
    ViewAbstractModelStatic::SetBorderStyle(AceType::RawPtr(frameNode), borderStyle);
    ViewAbstractModelStatic::SetBorderWidth(AceType::RawPtr(frameNode), borderWidth);
    ViewAbstractModelStatic::SetBorderColor(AceType::RawPtr(frameNode), borderColor);
    ViewAbstractModelStatic::SetBorderRadius(AceType::RawPtr(frameNode), borderRadius);
    ViewAbstractModelStatic::SetRenderStrategy(AceType::RawPtr(frameNode), RenderStrategy::OFFSCREEN);

    ASSERT_TRUE(renderContext->GetBorderStyle().has_value());
    ASSERT_TRUE(renderContext->GetBorderWidth().has_value());
    ASSERT_TRUE(renderContext->GetBorderColor().has_value());
    ASSERT_TRUE(renderContext->GetBorderRadius().has_value());
    EXPECT_EQ(renderContext->GetBorderStyle().value(), borderStyle);
    EXPECT_EQ(renderContext->GetBorderWidth().value(), borderWidth);
    EXPECT_EQ(renderContext->GetBorderColor().value(), borderColor);
    EXPECT_EQ(renderContext->GetBorderRadius().value(), borderRadius);
    EXPECT_EQ(renderContext->GetRenderStrategy().value_or(RenderStrategy::FAST), RenderStrategy::OFFSCREEN);
}

/**
 * @tc.name: BorderImageAndDashSetters
 * @tc.desc: Test border image source flags and dash setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BorderImageAndDashSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and border image.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto borderImage = AceType::MakeRefPtr<BorderImage>("resource://border.png");
    ASSERT_NE(borderImage, nullptr);
    borderImage->SetBundleName("bundle");
    borderImage->SetModuleName("module");
    auto dashGap = CreateBorderWidthProperty(STATIC_TEST_FLOAT_ONE, STATIC_TEST_FLOAT_ONE,
        STATIC_TEST_FLOAT_ONE, STATIC_TEST_FLOAT_ONE);
    auto dashWidth = CreateBorderWidthProperty(STATIC_TEST_FLOAT_TWO, STATIC_TEST_FLOAT_TWO,
        STATIC_TEST_FLOAT_TWO, STATIC_TEST_FLOAT_TWO);

    /**
     * @tc.steps: step2. set border image and dash values.
     * @tc.expected: render context stores source flags and dash values.
     */
    ViewAbstractModelStatic::SetBorderImage(AceType::RawPtr(frameNode), borderImage,
        BorderImage::SOURCE_BIT | BorderImage::OUTSET_BIT | BorderImage::SLICE_BIT |
        BorderImage::REPEAT_BIT | BorderImage::WIDTH_BIT);
    ViewAbstractModelStatic::SetDashGap(AceType::RawPtr(frameNode), dashGap);
    ViewAbstractModelStatic::SetDashWidth(AceType::RawPtr(frameNode), dashWidth);

    ASSERT_TRUE(renderContext->GetBorderImageSource().has_value());
    EXPECT_EQ(renderContext->GetBorderImageSource()->GetSrc(), "resource://border.png");
    EXPECT_TRUE(renderContext->GetBorderSourceFromImage().value_or(false));
    EXPECT_TRUE(renderContext->GetHasBorderImageOutset().value_or(false));
    EXPECT_TRUE(renderContext->GetHasBorderImageSlice().value_or(false));
    EXPECT_TRUE(renderContext->GetHasBorderImageRepeat().value_or(false));
    EXPECT_TRUE(renderContext->GetHasBorderImageWidth().value_or(false));
    EXPECT_EQ(renderContext->GetDashGap().value(), dashGap);
    EXPECT_EQ(renderContext->GetDashWidth().value(), dashWidth);
}

/**
 * @tc.name: PositionAndAnchorSetters
 * @tc.desc: Test align, position, offset, localized edge and anchor setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, PositionAndAnchorSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and position values.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(renderContext, nullptr);
    ASSERT_NE(layoutProperty, nullptr);
    OffsetT<Dimension> position { Dimension(STATIC_TEST_FLOAT_ONE), Dimension(STATIC_TEST_FLOAT_TWO) };
    OffsetT<Dimension> offset { Dimension(STATIC_TEST_FLOAT_THREE), Dimension(STATIC_TEST_FLOAT_FOUR) };
    EdgesParam edges;
    edges.top = Dimension(STATIC_TEST_FLOAT_FIVE);
    edges.left = Dimension(STATIC_TEST_FLOAT_FIVE);
    edges.bottom = Dimension(STATIC_TEST_FLOAT_FIVE);
    edges.right = Dimension(STATIC_TEST_FLOAT_FIVE);

    /**
     * @tc.steps: step2. set align, position, offset and anchor.
     * @tc.expected: render context and layout property are updated.
     */
    ViewAbstractModelStatic::SetAlign(AceType::RawPtr(frameNode), Alignment::CENTER_RIGHT);
    ViewAbstractModelStatic::SetAlign(AceType::RawPtr(frameNode), std::string("start"));
    ViewAbstractModelStatic::SetPosition(AceType::RawPtr(frameNode), position);
    ViewAbstractModelStatic::SetPositionEdges(AceType::RawPtr(frameNode), edges);
    ViewAbstractModelStatic::SetPositionLocalizedEdges(AceType::RawPtr(frameNode), true);
    ViewAbstractModelStatic::SetOffset(AceType::RawPtr(frameNode), offset);
    ViewAbstractModelStatic::SetOffsetEdges(AceType::RawPtr(frameNode), edges);
    ViewAbstractModelStatic::SetOffsetLocalizedEdges(AceType::RawPtr(frameNode), true);
    ViewAbstractModelStatic::SetMarkAnchorStart(AceType::RawPtr(frameNode), Dimension(STATIC_TEST_FLOAT_SIX));
    ViewAbstractModelStatic::MarkAnchor(AceType::RawPtr(frameNode), position);

    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    ASSERT_FALSE(renderContext->GetPosition().has_value());
    EXPECT_TRUE(renderContext->HasPositionEdges());
    ASSERT_FALSE(renderContext->GetOffset().has_value());
    EXPECT_TRUE(renderContext->HasOffsetEdges());
    ASSERT_TRUE(renderContext->GetAnchor().has_value());
    EXPECT_EQ(renderContext->GetAnchor().value(), position);
    EXPECT_TRUE(layoutProperty->IsPositionLocalizedEdges());
    EXPECT_TRUE(layoutProperty->IsOffsetLocalizedEdges());
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetLocalizedAlignment().value_or(""), "start");

    /**
     * @tc.steps: step3. reset mark anchor start and anchor.
     * @tc.expected: anchor is reset.
     */
    ViewAbstractModelStatic::ResetMarkAnchorStart(AceType::RawPtr(frameNode));
    ViewAbstractModelStatic::MarkAnchor(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_FALSE(renderContext->GetAnchor().has_value());
}

/**
 * @tc.name: AlignRulesAndBiasSetters
 * @tc.desc: Test align rules and two bias setter overloads.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, AlignRulesAndBiasSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and align rules.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    AlignRule leftRule;
    leftRule.anchor = "anchor";
    leftRule.horizontal = HorizontalAlign::START;
    std::map<AlignDirection, AlignRule> alignRules;
    alignRules[AlignDirection::LEFT] = leftRule;

    /**
     * @tc.steps: step2. set align rules and explicit bias pair.
     * @tc.expected: flex item property stores align rules and bias pair.
     */
    ViewAbstractModelStatic::SetAlignRules(AceType::RawPtr(frameNode), alignRules);
    ViewAbstractModelStatic::SetBias(AceType::RawPtr(frameNode), BiasPair(STATIC_TEST_FLOAT_ONE,
        STATIC_TEST_FLOAT_TWO));
    const auto& flexItemProperty = frameNode->GetLayoutProperty()->GetFlexItemProperty();
    ASSERT_NE(flexItemProperty, nullptr);
    ASSERT_TRUE(flexItemProperty->GetAlignRules().has_value());
    ASSERT_TRUE(flexItemProperty->GetBias().has_value());
    EXPECT_EQ(flexItemProperty->GetAlignRules()->at(AlignDirection::LEFT).anchor, "anchor");
    EXPECT_EQ(flexItemProperty->GetBias()->first, STATIC_TEST_FLOAT_ONE);
    EXPECT_EQ(flexItemProperty->GetBias()->second, STATIC_TEST_FLOAT_TWO);

    /**
     * @tc.steps: step3. reset align rules and use optional float bias overload.
     * @tc.expected: align rules reset and missing side defaults to 0.5.
     */
    ViewAbstractModelStatic::SetAlignRules(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::SetBias(AceType::RawPtr(frameNode), std::nullopt, STATIC_TEST_FLOAT_THREE);
    EXPECT_FALSE(flexItemProperty->GetAlignRules().has_value());
    ASSERT_TRUE(flexItemProperty->GetBias().has_value());
    EXPECT_EQ(flexItemProperty->GetBias()->first, 0.5f);
    EXPECT_EQ(flexItemProperty->GetBias()->second, STATIC_TEST_FLOAT_THREE);
}

/**
 * @tc.name: PixelRoundDisplayBackgroundPivotRotate
 * @tc.desc: Test pixel round, display index, background color, pivot and rotate setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, PixelRoundDisplayBackgroundPivotRotate, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(layoutProperty, nullptr);
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. set pixel round, display index, background color, pivot and rotate.
     * @tc.expected: properties are updated.
     */
    ViewAbstractModelStatic::SetPixelRound(AceType::RawPtr(frameNode), 3);
    ViewAbstractModelStatic::SetDisplayIndex(AceType::RawPtr(frameNode), 9);
    ViewAbstractModelStatic::SetBackgroundColor(AceType::RawPtr(frameNode), Color::RED);
    DimensionOffset pivot { Dimension(STATIC_TEST_FLOAT_ONE), Dimension(STATIC_TEST_FLOAT_TWO) };
    ViewAbstractModelStatic::SetPivot(AceType::RawPtr(frameNode), pivot);
    std::vector<std::optional<float>> rotate = {
        STATIC_TEST_FLOAT_ONE, STATIC_TEST_FLOAT_TWO, STATIC_TEST_FLOAT_THREE, STATIC_TEST_FLOAT_FOUR,
        STATIC_TEST_FLOAT_FIVE
    };
    std::vector<std::optional<float>> rotateAngle = {
        std::nullopt, std::nullopt, std::nullopt, STATIC_TEST_FLOAT_SIX
    };
    ViewAbstractModelStatic::SetRotate(AceType::RawPtr(frameNode), rotate);
    ViewAbstractModelStatic::SetRotateAngle(AceType::RawPtr(frameNode), rotateAngle);

    EXPECT_EQ(layoutProperty->GetPixelRound(), 3);
    ASSERT_TRUE(layoutProperty->GetFlexItemProperty()->GetDisplayIndex().has_value());
    EXPECT_EQ(layoutProperty->GetFlexItemProperty()->GetDisplayIndex().value(), 9);
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::TRANSPARENT), Color::RED);
    EXPECT_EQ(renderContext->GetTransformCenter().value(), pivot);
    ASSERT_TRUE(renderContext->GetTransformRotate().has_value());
    EXPECT_EQ(renderContext->GetTransformRotate()->x, STATIC_TEST_FLOAT_ONE);
    EXPECT_EQ(renderContext->GetTransformRotate()->v, STATIC_TEST_FLOAT_FIVE);
    ASSERT_TRUE(renderContext->GetTransformRotateAngle().has_value());
    EXPECT_EQ(renderContext->GetTransformRotateAngle()->z, STATIC_TEST_FLOAT_ONE);
    EXPECT_EQ(renderContext->GetTransformRotateAngle()->w, STATIC_TEST_FLOAT_SIX);

    /**
     * @tc.steps: step3. reset background color and pivot.
     * @tc.expected: background becomes transparent and pivot is reset.
     */
    ViewAbstractModelStatic::SetBackgroundColor(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::SetPivot(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::BLACK), Color::TRANSPARENT);
    EXPECT_FALSE(renderContext->GetTransformCenter().has_value());
}

/**
 * @tc.name: BackdropClipTransformAndRenderFit
 * @tc.desc: Test backdrop blur, clip edge, transform matrix and render fit optional setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, BackdropClipTransformAndRenderFit, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and render context.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    renderContext->UpdateClipShape(basicShape);

    /**
     * @tc.steps: step2. set backdrop blur, clip edge, transform matrix and render fit.
     * @tc.expected: clip shape is reset by clip edge; optional render values are stored.
     */
    BlurOption blurOption;
    ViewAbstractModelStatic::SetBackdropBlur(AceType::RawPtr(frameNode), Dimension(STATIC_TEST_FLOAT_FOUR),
        blurOption);
    ViewAbstractModelStatic::SetClipEdge(AceType::RawPtr(frameNode), true);
    Matrix4 matrix = Matrix4::CreateIdentity();
    ViewAbstractModelStatic::SetTransformMatrix(AceType::RawPtr(frameNode), matrix);
    ViewAbstractModelStatic::SetRenderFit(AceType::RawPtr(frameNode), RenderFit::CENTER);

    EXPECT_TRUE(renderContext->GetBackBlurRadius().has_value());
    EXPECT_TRUE(renderContext->GetClipEdge().value_or(false));
    EXPECT_FALSE(renderContext->GetClipShape().has_value());
    EXPECT_TRUE(renderContext->GetTransformMatrix().has_value());
    EXPECT_EQ(renderContext->GetRenderFit().value_or(RenderFit::TOP_LEFT), RenderFit::CENTER);

    /**
     * @tc.steps: step3. reset optional render values.
     * @tc.expected: transform matrix and render fit are reset.
     */
    ViewAbstractModelStatic::SetTransformMatrix(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::SetRenderFit(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_FALSE(renderContext->GetTransformMatrix().has_value());
    EXPECT_FALSE(renderContext->GetRenderFit().has_value());
}

/**
 * @tc.name: ForegroundColorAndEffectSetters
 * @tc.desc: Test foreground color, strategy, effect and blend mode setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, ForegroundColorAndEffectSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and render context.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step2. set strategy then foreground color.
     * @tc.expected: color clears strategy and foreground flag is true.
     */
    ViewAbstractModelStatic::SetForegroundColorStrategy(AceType::RawPtr(frameNode),
        ForegroundColorStrategy::INVERT);
    ASSERT_TRUE(renderContext->GetForegroundColorStrategy().has_value());
    ViewAbstractModelStatic::SetForegroundColor(AceType::RawPtr(frameNode), Color::BLUE);
    EXPECT_FALSE(renderContext->GetForegroundColorStrategy().has_value());
    EXPECT_EQ(renderContext->GetForegroundColor().value_or(Color::TRANSPARENT), Color::BLUE);
    EXPECT_TRUE(renderContext->GetForegroundColorFlag().value_or(false));

    /**
     * @tc.steps: step3. set foreground effect and blend mode, then reset foreground color.
     * @tc.expected: foreground effect is stored; foreground color flag is reset.
     */
    ViewAbstractModelStatic::SetForegroundEffect(AceType::RawPtr(frameNode), STATIC_TEST_FLOAT_FOUR);
    ViewAbstractModelStatic::SetBlendMode(AceType::RawPtr(frameNode), BlendMode::SRC_OVER);
    ASSERT_TRUE(renderContext->GetForegroundEffect().has_value());
    EXPECT_EQ(renderContext->GetForegroundEffect().value(), STATIC_TEST_FLOAT_FOUR);
    EXPECT_EQ(renderContext->GetBackBlendMode().value_or(BlendMode::NONE), BlendMode::SRC_OVER);

    ViewAbstractModelStatic::SetForegroundColor(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_FALSE(renderContext->GetForegroundColor().has_value());
    EXPECT_FALSE(renderContext->GetForegroundColorFlag().value_or(true));
}

/**
 * @tc.name: FocusBoxAndScopeSetters
 * @tc.desc: Test focus box style and focus scope setters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractModelStaticTestNg, FocusBoxAndScopeSetters, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frame node and focus hub.
     */
    auto frameNode = CreateStaticFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    FocusBoxStyle style;
    style.strokeColor = Color::BLUE;
    style.strokeWidth = Dimension(STATIC_TEST_FLOAT_TWO, DimensionUnit::PERCENT);
    style.margin = Dimension(STATIC_TEST_FLOAT_THREE, DimensionUnit::PERCENT);

    /**
     * @tc.steps: step2. set focus box and scope.
     * @tc.expected: focus hub stores normalized style and scope values.
     */
    ViewAbstractModelStatic::SetFocusBoxStyle(AceType::RawPtr(frameNode), style);
    ViewAbstractModelStatic::SetFocusScopeId(AceType::RawPtr(frameNode), std::string("scope"), true, false);
    ViewAbstractModelStatic::SetFocusScopePriority(AceType::RawPtr(frameNode), std::string("scope"),
        static_cast<uint32_t>(FocusPriority::PRIOR));

    auto storedStyle = focusHub->GetFocusBox().GetStyle();
    ASSERT_TRUE(storedStyle.has_value());
    EXPECT_EQ(storedStyle->strokeColor.value_or(Color::TRANSPARENT), Color::BLUE);
    EXPECT_EQ(storedStyle->strokeWidth->Unit(), DimensionUnit::FP);
    EXPECT_EQ(storedStyle->margin->Unit(), DimensionUnit::FP);
    EXPECT_EQ(focusHub->GetFocusScopeId(), "scope");
    EXPECT_EQ(focusHub->focusPriority_, FocusPriority::PRIOR);

    /**
     * @tc.steps: step3. reset focus box style and scope priority.
     * @tc.expected: style is reset to default and priority becomes AUTO.
     */
    ViewAbstractModelStatic::SetFocusBoxStyle(AceType::RawPtr(frameNode), std::nullopt);
    ViewAbstractModelStatic::SetFocusScopePriority(AceType::RawPtr(frameNode), std::nullopt, std::nullopt);
    EXPECT_FALSE(focusHub->GetFocusBox().GetStyle().has_value());
    EXPECT_EQ(focusHub->focusPriority_, FocusPriority::AUTO);
}
} // namespace OHOS::Ace::NG
