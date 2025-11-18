/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/unittest/core/base/view_abstract_test_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void ViewAbstractTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestThreeNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ViewAbstractTest028
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTest028, TestSize.Level1)
{
    /**
     * @tc.steps: step1.push FrameNode is not null, callback Pop function.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);
    ViewAbstract::Pop();

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->elementsStack_.empty());
    EXPECT_EQ(ViewStackProcessor::GetInstance()->elementsStack_.size(), INDEX);
}

/**
 * @tc.name: ViewAbstractTest029
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTest029, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    ViewAbstract::SetWidth(NG::CalcLength(WIDTH));
    ViewAbstract::SetHeight(NG::CalcLength(HEIGHT));
    ViewAbstract::SetMinWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMinHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetMaxWidth(NG::CalcLength(MIN_WIDTH));
    ViewAbstract::SetMaxHeight(NG::CalcLength(MIN_HEIGHT));
    ViewAbstract::SetAspectRatio(RATIO);
    ViewAbstract::SetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER), RATIO);
    ViewAbstract::SetBackgroundColor(BLUE);
    ViewAbstract::SetBackgroundColor(nullptr, BLUE);
    ViewAbstract::SetBackgroundImage(imageSourceInfo);
    ViewAbstract::SetBackgroundImage(nullptr, imageSourceInfo);
    ViewAbstract::SetBackgroundImageSize(BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE);
    ViewAbstract::SetBackgroundImageSize(nullptr, BACKGROUNDSIZE, true);
    ViewAbstract::SetBackgroundImagePosition(BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION);
    ViewAbstract::SetBackgroundImagePosition(nullptr, BACKGROUNDPOSITION, true);
    ViewAbstract::SetPixelRound(0);
    ChainInfo chainInfo;
    chainInfo.direction = LineDirection::HORIZONTAL;
    chainInfo.style = ChainStyle::SPREAD;
    ViewAbstract::SetChainStyle(chainInfo);
    ViewAbstract::SetChainStyle(AceType::RawPtr(FRAME_NODE_REGISTER), chainInfo);
    ViewAbstract::SetBias(biasPair);
    ViewAbstract::SetBias(nullptr, biasPair);
    ViewAbstract::SetOuterBorderRadius(ZERO);
    ViewAbstract::SetOuterBorderRadius(nullptr, ZERO);
    NG::BorderRadiusProperty borderRadius;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    ViewAbstract::SetOuterBorderRadius(nullptr, borderRadius);
    ViewAbstract::SetOuterBorderColor(BLUE);
    ViewAbstract::SetOuterBorderColor(nullptr, BLUE);
    NG::BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    ViewAbstract::SetOuterBorderColor(nullptr, borderColor);
    ViewAbstract::SetOuterBorderWidth(ZERO);
    ViewAbstract::SetOuterBorderWidth(nullptr, ZERO);
    NG::BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    ViewAbstract::SetOuterBorderWidth(nullptr, borderWidth);
    auto borderStyle = static_cast<BorderStyle>(INDEX);
    ViewAbstract::SetOuterBorderStyle(borderStyle);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyle);
    NG::BorderStyleProperty borderStyleProperty;
    ViewAbstract::SetOuterBorderStyle(borderStyleProperty);
    ViewAbstract::SetOuterBorderStyle(nullptr, borderStyleProperty);
    ViewAbstract::ResetAspectRatio();
    ViewAbstract::ResetAspectRatio(AceType::RawPtr(FRAME_NODE_REGISTER));

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractTest030
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    MotionPathOption motionPath;
    ViewAbstract::SetMotionPath(std::move(motionPath));
    auto repeat = static_cast<ImageRepeat>(INDEX);
    ViewAbstract::SetBackgroundImageRepeat(repeat);
    GestureJudgeFunc tapEventFunc;
    ViewAbstract::SetOnGestureJudgeBegin(std::move(tapEventFunc));

    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);

    auto direction = static_cast<TextDirection>(INDEX);
    ViewAbstract::SetLayoutDirection(direction);
    std::map<AlignDirection, AlignRule> alignRules;
    ViewAbstract::SetAlignRules(alignRules);
    auto alignSelf = static_cast<FlexAlign>(INDEX);
    ViewAbstract::SetAlignSelf(alignSelf);
    ViewAbstract::SetAlignSelf(AceType::RawPtr(FRAME_NODE_REGISTER), alignSelf);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OpenPopup
 * @tc.desc: Test OpenPopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, OpenPopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    RefPtr<PopupParam> param2 = nullptr;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    /**
     * @tc.steps: step2. Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param2, contentNode2), ERROR_CODE_INTERNAL_ERROR);
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    int32_t targetId = -1;
    param->SetTargetId(std::to_string(targetId));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = 10000;
    param->SetTargetId(std::to_string(targetId));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    param->SetTargetId(std::to_string(targetNode->GetId()));
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE);
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
}

/**
 * @tc.name: UpdatePopup
 * @tc.desc: Test UpdatePopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, UpdatePopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    param->SetShowInSubWindow(false);
    param->SetTargetId(std::to_string(targetNode->GetId()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = true;
    param->SetIsPartialUpdate(true);
    EXPECT_EQ(ViewAbstract::UpdatePopup(param, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: ClosePopup
 * @tc.desc: Test ClosePopup of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ClosePopup, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and params.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    auto param = AceType::MakeRefPtr<PopupParam>();
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    param->SetIsShow(true);
    param->SetUseCustomComponent(true);
    param->SetTargetId(std::to_string(targetNode->GetId()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = true;
    EXPECT_EQ(ViewAbstract::ClosePopup(contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::ClosePopup(contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: OpenMenu001
 * @tc.desc: Test OpenMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, OpenMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    menuParam.previewMode = MenuPreviewMode::IMAGE;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto contentNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    int32_t targetId = targetNode->GetId();
    /**
     * @tc.steps: step2. Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode2, targetId), ERROR_CODE_DIALOG_CONTENT_ERROR);
    targetId = -1;
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = 10000;
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_INFO_NOT_EXIST);
    targetId = targetNode->GetId();
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_TARGET_NOT_ON_COMPONENT_TREE);
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST);
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode3, targetId), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: UpdateMenu001
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, UpdateMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    overlayManager->menuMap_.clear();
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: UpdateMenu002
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, UpdateMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    auto selectTheme = AceType::MakeRefPtr<SelectTheme>();
    selectTheme->expandDisplay_ = true;
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(selectTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(selectTheme));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto contentNodePipelineContext = contentNode->GetContextWithCheck();
    contentNodePipelineContext->overlayManager_ = nullptr;
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_INTERNAL_ERROR);
    contentNodePipelineContext->overlayManager_ = overlayManager;
}

/**
 * @tc.name: UpdateMenu003
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, UpdateMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(contentNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menuWrapperNode->GetPattern());
    ASSERT_NE(wrapperPattern, nullptr);
    auto menu = wrapperPattern->GetMenu();
    ASSERT_NE(menu, nullptr);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    ASSERT_NE(menuPattern, nullptr);
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    menuItem->MountToParent(menu);

    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_TAG, MenuType::SUB_MENU));
    subMenu->MountToParent(menuWrapperNode);
    menuPattern->SetShowedSubMenu(subMenu);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::EMBEDDED;
    menuPattern->AddEmbeddedMenuItem(menuItem);

    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: UpdateMenu004
 * @tc.desc: Test UpdateMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, UpdateMenu004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto menuWrapperNode = overlayManager->GetMenuNodeWithExistContent(contentNode);
    ASSERT_NE(menuWrapperNode, nullptr);
    auto wrapperPattern = AceType::DynamicCast<MenuWrapperPattern>(menuWrapperNode->GetPattern());
    ASSERT_NE(wrapperPattern, nullptr);
    auto menu = wrapperPattern->GetMenu();
    ASSERT_NE(menu, nullptr);
    auto menuPattern = AceType::DynamicCast<MenuPattern>(menu->GetPattern());
    ASSERT_NE(menuPattern, nullptr);
    auto menuItem = FrameNode::GetOrCreateFrameNode(V2::MENU_ITEM_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<MenuItemPattern>(); });
    menuItem->MountToParent(menu);
    auto subMenu = FrameNode::CreateFrameNode(
        V2::MENU_ETS_TAG, 3, AceType::MakeRefPtr<MenuPattern>(1, V2::MENU_ETS_TAG, MenuType::SUB_MENU));
    subMenu->MountToParent(menuWrapperNode);
    menuPattern->SetShowedSubMenu(subMenu);
    auto menuItemPattern = menuItem->GetPattern<MenuItemPattern>();
    menuItemPattern->expandingMode_ = SubMenuExpandingMode::STACK;
    EXPECT_EQ(ViewAbstract::UpdateMenu(menuParam, contentNode), ERROR_CODE_NO_ERROR);
}

/**
 * @tc.name: CloseMenu001
 * @tc.desc: Test CloseMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, CloseMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_NO_ERROR);
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode2), ERROR_CODE_DIALOG_CONTENT_ERROR);
    overlayManager->menuMap_.clear();
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_DIALOG_CONTENT_NOT_FOUND);
}

/**
 * @tc.name: CloseMenu002
 * @tc.desc: Test CloseMenu of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, CloseMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create some FrameNode and menuParam.
     */
    auto pipelineContext = PipelineContext::GetCurrentContext();
    MenuParam menuParam;
    menuParam.isShowInSubWindow = false;
    auto contentNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    RefPtr<FrameNode> contentNode2 = nullptr;

    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    ViewStackProcessor::GetInstance()->Push(targetNode);
    targetNode->onMainTree_ = true;
    targetNode->AttachToMainTree(false, AceType::RawPtr(pipelineContext));
    auto stageNode = FrameNode::CreateFrameNode(
        V2::STAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StagePattern>());
    auto rootNode = FrameNode::CreateFrameNode(V2::ROOT_ETS_TAG, 1, AceType::MakeRefPtr<RootPattern>());
    stageNode->MountToParent(rootNode);
    targetNode->MountToParent(stageNode);
    rootNode->MarkDirtyNode();
    auto targetId = targetNode->GetId();
    auto targetNodePipelineContext = targetNode->GetContextWithCheck();
    ASSERT_NE(targetNodePipelineContext, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    targetNodePipelineContext->SetThemeManager(themeManager);
    targetNodePipelineContext->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));

    /**
     * @tc.expected: Return expected results.
     */
    EXPECT_EQ(ViewAbstract::OpenMenu(menuParam, contentNode, targetId), ERROR_CODE_NO_ERROR);
    auto overlayManager = ViewAbstract::GetCurOverlayManager(contentNode);
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->menuMap_[targetId];
    auto contentNodePipelineContext = contentNode->GetContextWithCheck();
    contentNodePipelineContext->overlayManager_ = nullptr;
    EXPECT_EQ(ViewAbstract::CloseMenu(contentNode), ERROR_CODE_INTERNAL_ERROR);
    contentNodePipelineContext->overlayManager_ = overlayManager;
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0037, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const std::string& id = "test_id";
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );
     /**
     * @tc.steps:  connect the FrameNode and id.
     */
    targetNode->UpdateInspectorId(id);

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeById(id, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0038, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const std::string& id = "test_id";
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );
     /**
     * @tc.steps:  connect the FrameNode and id.
     */
    targetNode->UpdateInspectorId(id);
    /**
     * @tc.steps:  set the FrameNode's  pipeline to null.
     */
    targetNode->context_ = nullptr;

    /**
     * @tc.expected: call the function to unfreeze the node.
     */
    bool isFreeze = false;
    ViewAbstract::FreezeUINodeById(id, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();
    EXPECT_EQ(isOpenInvisibleFreeze, true);

    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeById
 * @tc.desc: Test FreezeUINodeById of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0039, TestSize.Level1)
{
     /**
     * @tc.expected: use a non_existing node id.
     */
    const std::string& non_existing_id = "non_existing_id";
    /**
     * @tc.expected: call the function with the non_existing_id.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeById(non_existing_id, isFreeze);

    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(non_existing_id, true);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0040, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const int32_t& uniqueId = 1111;
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            uniqueId, []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeByUniqueId(uniqueId, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0041, TestSize.Level1)
{
    /**
     * @tc.steps:  Create some FrameNode.
     */
    const int32_t& uniqueId = 222;
    auto targetNode =
        FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            uniqueId, []() {
                return AceType::MakeRefPtr<ButtonPattern>();
            }
        );

    /**
     * @tc.steps:  set the FrameNode's  pipeline to null.
     */
    targetNode->context_ = nullptr;

    /**
     * @tc.expected: call the function to freeze the node.
     */
    bool isFreeze = false;
    ViewAbstract::FreezeUINodeByUniqueId(uniqueId, isFreeze);

    /**
     * @tc.expected: verify the pipeline's property is set.
     */
    auto pipeline = targetNode->GetContext();
    bool isOpenInvisibleFreeze = pipeline->IsOpenInvisibleFreeze();

    EXPECT_EQ(isOpenInvisibleFreeze, true);
    /**
     * @tc.expected: verify the node's freeze state.
     */
    bool res = targetNode->IsFreeze();
    EXPECT_EQ(res, isFreeze);
}

/**
 * @tc.name: FreezeUINodeByUniqueId
 * @tc.desc: Test FreezeUINodeByUniqueId of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0042, TestSize.Level1)
{
     /**
     * @tc.expected: use a non_existing node uniqueId.
     */
    const int32_t& non_existing_unique_id = 333;
    /**
     * @tc.expected: call the function with the non_existing_unique_id.
     */
    bool isFreeze = true;
    ViewAbstract::FreezeUINodeByUniqueId(non_existing_unique_id, isFreeze);

    auto node = ElementRegister::GetInstance()->GetNodeById(non_existing_unique_id);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: SetPositionLocalizedEdges
 * @tc.desc: Test SetPositionLocalizedEdges of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0043, TestSize.Level1)
{
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
     /**
     * @tc.expected: call the function to Update the layout property.
     */
    bool needLocalized = true;
    ViewAbstract::SetPositionLocalizedEdges(needLocalized);

    auto layoutProperty = targetNode->GetLayoutProperty();

     /**
     * @tc.expected: verify layout property is updated.
     */
    auto positionLocalizedEdges = layoutProperty->IsPositionLocalizedEdges();
    EXPECT_EQ(positionLocalizedEdges, needLocalized);
}

/**
 * @tc.name: SetPositionLocalizedEdges
 * @tc.desc: Test SetPositionLocalizedEdges of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0044, TestSize.Level1)
{
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
     /**
     * @tc.expected: call the function to Update the layout property.
     */
    bool needLocalized = false;
    ViewAbstract::SetPositionLocalizedEdges(needLocalized);

    auto layoutProperty = targetNode->GetLayoutProperty();

     /**
     * @tc.expected: verify layout property is updated.
     */
    auto positionLocalizedEdges = layoutProperty->IsPositionLocalizedEdges();
    EXPECT_EQ(positionLocalizedEdges, needLocalized);
}

/**
 * @tc.name: CreateWithForegroundColorResourceObj
 * @tc.desc: Test CreateWithForegroundColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0045, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {};
    updateFunc(resObj);
    pattern->AddResObj("foregroundColor", resObj, std::move(updateFunc));
    std::string foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, "");
}

/**
 * @tc.name: SetBackgroundColor
 * @tc.desc: Test SetBackgroundColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0046, TestSize.Level1)
{
    Color p3Red;
    p3Red.SetValue(0xffff0000);
    p3Red.SetColorSpace(ColorSpace::DISPLAY_P3);
    ViewAbstract::SetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER), p3Red);
    Color result = ViewAbstract::GetBackgroundColor(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(result.GetColorSpace(), p3Red.GetColorSpace());
}

/**
 * @tc.name: SetSweepGradient
 * @tc.desc: Test SetSweepGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0047, TestSize.Level1)
{
    Color p3Red;
    p3Red.SetValue(0xffff0000);
    p3Red.SetColorSpace(ColorSpace::DISPLAY_P3);
    Color p3Green;
    p3Green.SetValue(0xff00ff00);
    p3Green.SetColorSpace(ColorSpace::DISPLAY_P3);
    Color p3Blue;
    p3Blue.SetValue(0xff0000ff);
    p3Blue.SetColorSpace(ColorSpace::DISPLAY_P3);
    GradientColor gradientColor;
    Gradient gradient;
    gradientColor.SetColor(p3Red);
    gradient.AddColor(gradientColor);
    gradientColor.SetColor(p3Green);
    gradient.AddColor(gradientColor);
    gradientColor.SetColor(p3Blue);
    gradient.AddColor(gradientColor);
    ViewAbstract::SetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER), gradient);
    Gradient result = ViewAbstract::GetSweepGradient(AceType::RawPtr(FRAME_NODE_REGISTER));
    EXPECT_EQ(result.GetColors().front().GetColor().GetColorSpace(), p3Red.GetColorSpace());
    EXPECT_EQ(result.GetColors().back().GetColor().GetColorSpace(), p3Blue.GetColorSpace());
}

/**
 * @tc.name: SetLinearGradient
 * @tc.desc: Test SetLinearGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0048, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    ViewAbstract::SetLinearGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("LinearGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: CreateWithForegroundColorResourceObj
 * @tc.desc: Test CreateWithForegroundColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0049, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithForegroundColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    foregroundColor = pattern->GetResCacheMapByKey("foregroundColor");
    EXPECT_EQ(foregroundColor, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderColorResourceObj
 * @tc.desc: Test CreateWithOuterBorderColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0050, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("outerBorderColorRes");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("outerBorderColorRes");
    EXPECT_EQ(colorStr, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderRadiusResourceObj
 * @tc.desc: Test CreateWithOuterBorderRadiusResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0051, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string radiusStr = pattern->GetResCacheMapByKey("outerBorderRadiusRes");
    EXPECT_EQ(radiusStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderRadiusResourceObj(resObj);
    CalcDimension result;
    ResourceParseUtils::ParseResDimensionVp(resObj, result);
    radiusStr = pattern->GetResCacheMapByKey("outerBorderRadiusRes");
    EXPECT_EQ(radiusStr, result.ToString());
}

/**
 * @tc.name: CreateWithLightColorResourceObj
 * @tc.desc: Test CreateWithLightColorResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0052, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithLightColorResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("LightColorRes");
    EXPECT_EQ(colorStr, result.ColorToString());
}

/**
 * @tc.name: CreateWithOuterBorderWidthResourceObj
 * @tc.desc: Test CreateWithOuterBorderWidthResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0053, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string widthStr = pattern->GetResCacheMapByKey("outerBorderWidthRes");
    EXPECT_EQ(widthStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithOuterBorderWidthResourceObj(resObj);
    CalcDimension result;
    ResourceParseUtils::ParseResDimensionVp(resObj, result);
    widthStr = pattern->GetResCacheMapByKey("outerBorderWidthRes");
    EXPECT_EQ(widthStr, result.ToString());
}

/**
 * @tc.name: CreateWithColorBlendResourceObj
 * @tc.desc: Test CreateWithColorBlendResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0054, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, "");
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);
    ViewAbstract::CreateWithColorBlendResourceObj(resObj);
    Color result;
    ResourceParseUtils::ParseResColor(resObj, result);
    colorStr = pattern->GetResCacheMapByKey("viewAbstract.colorBlend");
    EXPECT_EQ(colorStr, result.ToString());
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
}

/**
 * @tc.name: CreateWithOpacityResourceObj
 * @tc.desc: Test CreateWithOpacityResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0055, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    std::string opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, "");
    std::string bundleName = "app.float.test";
    std::string moduleName = "entry";
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(bundleName, moduleName, 0);

    g_isConfigChangePerform = true;
    ViewAbstract::CreateWithOpacityResourceObj(resObj);
    double result;
    ResourceParseUtils::ParseResDouble(resObj, result);
    opacityStr = pattern->GetResCacheMapByKey("viewAbstract.opacity");
    EXPECT_EQ(opacityStr, std::to_string(result));
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SetSweepGradient
 * @tc.desc: Test SetSweepGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0056, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    ViewAbstract::SetSweepGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("SweepGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: SetRadialGradient
 * @tc.desc: Test SetRadialGradient of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0057, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);

    g_isConfigChangePerform = true;
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);
    ViewAbstract::SetRadialGradient(gradient);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string gradientStr = pattern->GetResCacheMapByKey("RadialGradient.gradient");
    EXPECT_EQ(gradientStr, "");
}

/**
 * @tc.name: SetClipShape
 * @tc.desc: Test SetClipShape of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0058, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    g_isConfigChangePerform = true;
    ViewAbstract::SetClipEdge(frameNode, true);
    auto basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    ViewAbstract::SetClipShape(basicShape);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
}

/**
 * @tc.name: SetBackgroundBlurStyle
 * @tc.desc: Test SetBackgroundBlurStyle of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0059, TestSize.Level1)
{
    BlurStyleOption blurStyleOption;
    blurStyleOption.blurStyle = BlurStyle::NO_MATERIAL;
    blurStyleOption.colorMode = ThemeColorMode::SYSTEM;
    blurStyleOption.adaptiveColor = AdaptiveColor::DEFAULT;
    blurStyleOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBackgroundBlurStyle(blurStyleOption);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;

    std::string blurStyleStr = pattern->GetResCacheMapByKey("backgroundBlurStyle.backgroundBlurStyleOptions");
    EXPECT_EQ(blurStyleStr, "");
}

/**
 * @tc.name: SetBackgroundEffect
 * @tc.desc: Test SetBackgroundEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0060, TestSize.Level1)
{
    EffectOption option;
    Color color = Color::TRANSPARENT;
    option.color = color;
    option.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    g_isConfigChangePerform = true;
    ViewAbstract::SetBackgroundEffect(option);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string effectStr = pattern->GetResCacheMapByKey("backgroundEffect");
    EXPECT_EQ(effectStr, "");
}

/**
 * @tc.name: SetPixelStretchEffect
 * @tc.desc: Test SetPixelStretchEffect of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0061, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    PixStretchEffectOption option;
    option.ResetValue();
    ViewAbstract::SetPixelStretchEffect(option);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string effectStr = pattern->GetResCacheMapByKey("pixelStretchEffect");
    EXPECT_EQ(effectStr, "");
}

/**
 * @tc.name: SetOuterBorderRadius
 * @tc.desc: Test SetOuterBorderRadius of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0062, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    NG::BorderRadiusProperty borderRadius;
    borderRadius.multiValued = true;
    ViewAbstract::SetOuterBorderRadius(borderRadius);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderRadiusStr = pattern->GetResCacheMapByKey("outerBorderRadius");
    EXPECT_EQ(borderRadiusStr, "");
}

/**
 * @tc.name: SetOuterBorderColor
 * @tc.desc: Test SetOuterBorderColor of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0063, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderColorProperty borderColor;
    ViewAbstract::SetOuterBorderColor(borderColor);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderColorStr = pattern->GetResCacheMapByKey("outerBorderColor");
    EXPECT_EQ(borderColorStr, "");
}

/**
 * @tc.name: SetOuterBorderWidth
 * @tc.desc: Test SetOuterBorderWidth of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0064, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    BorderWidthProperty borderWidth;
    ViewAbstract::SetOuterBorderWidth(borderWidth);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string borderWidthStr = pattern->GetResCacheMapByKey("outerBorderWidth");
    EXPECT_EQ(borderWidthStr, "");
}

/**
 * @tc.name: SetProgressMask
 * @tc.desc: Test SetProgressMask of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0065, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>(BasicShapeType::CIRCLE);
    RefPtr<NG::ProgressMaskProperty> progressMaskProperty = AceType::MakeRefPtr<NG::ProgressMaskProperty>();
    progressMaskProperty->SetMaxValue(200.0f);
    progressMaskProperty->SetColor(Color(0xffff0000));
    progressMaskProperty->SetValue(1.0f);
    auto target = frameNode->GetRenderContext();
    ASSERT_NE(target, nullptr);
    target->UpdateClipMask(basicShape);
    ViewAbstract::SetProgressMask(progressMaskProperty);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string maskShape = pattern->GetResCacheMapByKey("ProgressMask");
    EXPECT_EQ(maskShape, "");
}

/**
 * @tc.name: SetLightPosition
 * @tc.desc: Test SetLightPosition of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0066, TestSize.Level1)
{
    NG::TranslateOptions option;
    CalcDimension dimPositionX(30, DimensionUnit::VP);
    CalcDimension dimPositionY(20, DimensionUnit::VP);
    CalcDimension dimPositionZ(10, DimensionUnit::VP);
    option.x = dimPositionX;
    option.y = dimPositionY;
    option.z = dimPositionZ;
    g_isConfigChangePerform = true;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<Pattern>();
    CHECK_NULL_VOID(pattern);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetLightPosition(option);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);

    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    std::string lightSource = pattern->GetResCacheMapByKey("pointLight.LightSource");
    EXPECT_EQ(lightSource, "");

    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::SetLightPosition(option);
    g_isConfigChangePerform = false;
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetBackShadow
 * @tc.desc: Test SetBackShadow of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestThreeNg, ViewAbstractTestNg0067, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    Shadow shadow;
    ViewAbstract::SetBackShadow(shadow);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string shadowStr = pattern->GetResCacheMapByKey("shadow");
    EXPECT_EQ(shadowStr, "");
}
} // namespace OHOS::Ace::NG