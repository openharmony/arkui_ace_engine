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
#include "test/unittest/core/base/view_abstract_test_ng.h"
#include "core/components/select/select_theme.h"
#include "test/mock/core/render/mock_render_context.h"
#include "core/components_ng/base/view_stack_processor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
const std::string NODE_TAG("node");
void ViewAbstractTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: SetChainWeight001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetChainWeight001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    NG::ChainWeightPair value = {3.14f, 2.71f };
    ViewAbstract::SetChainWeight(value);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetChainWeight(value);
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetSafeAreaPadding001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSafeAreaPadding001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    PaddingProperty value;
    ViewAbstract::SetSafeAreaPadding(value);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetSafeAreaPadding(value);
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetSafeAreaPadding002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetSafeAreaPadding002, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::SetSafeAreaPadding(NG::CalcLength(WIDTH));
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetSafeAreaPadding(NG::CalcLength(WIDTH));
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetSafeAreaPadding001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ResetSafeAreaPadding001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::ResetSafeAreaPadding();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::ResetSafeAreaPadding();
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetPositionEdges001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetPositionEdges001, TestSize.Level1)
{
    EdgesParam value;
    CalcDimension top(30, DimensionUnit::VP);
    CalcDimension left(20, DimensionUnit::VP);
    value.SetTop(top);
    value.SetLeft(left);
    ViewAbstract::SetPositionEdges(value);

    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::SetPositionEdges(value);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetOffset001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetOffset001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    OffsetT<Dimension> values = { WIDTH, HEIGHT };
    ViewAbstract::SetOffset(values);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetOffset(values);
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetPosition002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ResetPosition002, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::ResetPosition();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto pipe = MockPipelineContext::GetCurrent();
    const auto root = FrameNode::CreateFrameNode(TAG_CHILD, 0, AceType::MakeRefPtr<RootPattern>(), true);
    auto child = FrameNode::CreateFrameNode(TAG_CHILD, 3, AceType::MakeRefPtr<RootPattern>(), true);
    auto child2 = FrameNode::CreateFrameNode(TAG_CHILD, 4, AceType::MakeRefPtr<Pattern>(), true);
    root->context_ = AceType::RawPtr(pipe);
    child->context_ = AceType::RawPtr(pipe);
    child2->context_ = AceType::RawPtr(pipe);

    child->SetParent(child2, false);
    ViewStackProcessor::GetInstance()->Push(child);
    child->IncRefCount();
    ViewAbstract::ResetPosition();
    EXPECT_NE(child->GetRenderContext(), nullptr);
}

/**
 * @tc.name: ResetPosition003
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ResetPosition003, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto pipe = MockPipelineContext::GetCurrent();
    auto parent = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    parent->tag_ = V2::COLUMN_ETS_TAG;
    
    auto child = FrameNode::CreateFrameNode(TAG_CHILD, 3, AceType::MakeRefPtr<RootPattern>(), true);
    child->SetParent(parent);
    parent->context_ = AceType::RawPtr(pipe);
    child->context_ = AceType::RawPtr(pipe);
    ViewStackProcessor::GetInstance()->Push(child);
    ViewAbstract::ResetPosition();
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->visualState_.has_value());
}
/**
 * @tc.name: ResetPosition004
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ResetPosition004, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto pipe = MockPipelineContext::GetCurrent();
    auto parent = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    parent->tag_ = V2::ROW_ETS_TAG;
    
    auto child = FrameNode::CreateFrameNode(TAG_CHILD, 3, AceType::MakeRefPtr<RootPattern>(), true);
    child->SetParent(parent);
    parent->context_ = AceType::RawPtr(pipe);
    child->context_ = AceType::RawPtr(pipe);
    ViewStackProcessor::GetInstance()->Push(child);
    ViewAbstract::ResetPosition();
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->visualState_.has_value());
}

/**
 * @tc.name: ResetPosition005
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ResetPosition005, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto pipe = MockPipelineContext::GetCurrent();
    auto parent = FrameNode::CreateFrameNode("parent", 2, AceType::MakeRefPtr<Pattern>());
    parent->tag_ = V2::FLEX_ETS_TAG;
    
    auto child = FrameNode::CreateFrameNode(TAG_CHILD, 3, AceType::MakeRefPtr<RootPattern>(), true);
    child->SetParent(parent);
    parent->context_ = AceType::RawPtr(pipe);
    child->context_ = AceType::RawPtr(pipe);
    ViewStackProcessor::GetInstance()->Push(child);
    ViewAbstract::ResetPosition();
    EXPECT_FALSE(ViewStackProcessor::GetInstance()->visualState_.has_value());
}

/**
 * @tc.name: GetCurOverlayManager001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, GetCurOverlayManager001, TestSize.Level1)
{
    RefPtr<UINode> node = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto result = ViewAbstract::GetCurOverlayManager(node);
    EXPECT_EQ(result, 1);
}

/**
 * @tc.name: UpdatePopup001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup001, TestSize.Level1)
{
    RefPtr<PopupParam> param = nullptr;
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto result = ViewAbstract::UpdatePopup(param, customNode);
    EXPECT_EQ(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: UpdatePopup002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup002, TestSize.Level1)
{
    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    RefPtr<UINode> customNode = nullptr;
    auto result = ViewAbstract::UpdatePopup(param, customNode);
    EXPECT_EQ(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: UpdatePopup003
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup003, TestSize.Level1)
{
    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    param->SetTargetId("-1");
    auto result = ViewAbstract::UpdatePopup(param, customNode);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: UpdatePopup004
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup004, TestSize.Level1)
{
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto param = AceType::MakeRefPtr<PopupParam>();
    param->SetTargetId("");
    auto result = ViewAbstract::UpdatePopup(param, customNode);
    EXPECT_EQ(result, ERROR_CODE_INTERNAL_ERROR);

    param->SetTargetId("50");
    result = ViewAbstract::UpdatePopup(param, customNode);
    EXPECT_EQ(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: UpdatePopup005
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup005, TestSize.Level1)
{
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
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = true;
    overlayManager->popupMap_.clear();
    param->SetIsPartialUpdate(true);
    int32_t result = ViewAbstract::UpdatePopup(param, contentNode);
    EXPECT_EQ(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: UpdatePopup006
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdatePopup006, TestSize.Level1)
{
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
    EXPECT_EQ(ViewAbstract::OpenPopup(param, contentNode), ERROR_CODE_NO_ERROR);
    auto context = contentNode->GetContextWithCheck();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->popupMap_[targetNode->GetId()].isCurrentOnShow = false;
    param->SetIsPartialUpdate(true);
    int32_t result = ViewAbstract::UpdatePopup(param, contentNode);
    EXPECT_EQ(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: ClosePopup001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ClosePopup001, TestSize.Level1)
{
    auto result = ViewAbstract::ClosePopup(nullptr);
    EXPECT_EQ(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<PopupParam> param = nullptr;
    result = ViewAbstract::ClosePopup(customNode);
    EXPECT_NE(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: ClosePopup002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ClosePopup002, TestSize.Level1)
{
    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    param->SetTargetId("-1");
    auto result = ViewAbstract::ClosePopup(customNode);
    
    param->SetTargetId("");
    result = ViewAbstract::ClosePopup(customNode);

    param->SetTargetId("50");
    result = ViewAbstract::ClosePopup(customNode);
    EXPECT_NE(result, ERROR_CODE_INTERNAL_ERROR);
}

/**
 * @tc.name: DismissDialog001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, DismissDialog001, TestSize.Level1)
{
    auto context = PipelineContext::GetCurrentContext();
    auto overlayManager = context->GetOverlayManager();
    auto rootNode = overlayManager->GetRootNode().Upgrade();
    DialogProperties dialogProperties;

    auto overlay = AceType::DynamicCast<FrameNode>(rootNode->GetLastChild());
    ASSERT_NE(overlay, nullptr);
    auto dialog = overlayManager->ShowDialog(dialogProperties, nullptr, false);
    auto dialogMapSize = overlayManager->dialogMap_.size();
    ViewAbstract::DismissDialog();
    EXPECT_NE(overlayManager->dialogMap_.size(), dialogMapSize - 1);
}

/**
 * @tc.name: OpenMenu001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, OpenMenu001, TestSize.Level1)
{
    MenuParam menuParam;
    int32_t targetId = 0;
    int32_t result = ViewAbstract::OpenMenu(menuParam, nullptr, targetId);
    EXPECT_EQ(result, ERROR_CODE_DIALOG_CONTENT_ERROR);

    RefPtr<NG::UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    targetId = 999;
    result = ViewAbstract::OpenMenu(menuParam, customNode, targetId);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: OpenMenu002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, OpenMenu002, TestSize.Level1)
{
    MenuParam menuParam;
    RefPtr<NG::UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto frameNode = FrameNode::CreateFrameNode("frameNode", 1, AceType::MakeRefPtr<Pattern>(), true);
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });

    auto element = ElementRegister::GetInstance()->AddReferenced(1, frameNode);
    EXPECT_FALSE(element);
    auto result = ViewAbstract::OpenMenu(menuParam, customNode, 1);

    frameNode->onMainTree_ = false;
    result = ViewAbstract::OpenMenu(menuParam, customNode, 1);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
    frameNode->onMainTree_ = true;
    result = ViewAbstract::OpenMenu(menuParam, customNode, 1);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: UpdateMenu001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, UpdateMenu001, TestSize.Level1)
{
    MenuParam menuParam;
    int32_t result = ViewAbstract::UpdateMenu(menuParam, nullptr);
    EXPECT_EQ(result, ERROR_CODE_DIALOG_CONTENT_ERROR);

    RefPtr<NG::UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    result = ViewAbstract::UpdateMenu(menuParam, customNode);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: CloseMenu001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CloseMenu001, TestSize.Level1)
{
    int32_t result = ViewAbstract::CloseMenu(nullptr);
    EXPECT_EQ(result, ERROR_CODE_DIALOG_CONTENT_ERROR);

    RefPtr<NG::UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    result = ViewAbstract::CloseMenu(customNode);
    EXPECT_NE(result, ERROR_CODE_DIALOG_CONTENT_ERROR);
}

/**
 * @tc.name: SetInspectorId001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetInspectorId001, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->ClearStack();
    std::string inspectorId = "test";
    ViewAbstract::SetInspectorId(inspectorId);
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);

    auto node = FrameNode::CreateFrameNode("TestNode", 1, AceType::MakeRefPtr<Pattern>());
    ViewStackProcessor::GetInstance()->Push(node);
    ViewAbstract::SetInspectorId("test1");
}

/**
 * @tc.name: CleanTransition001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CleanTransition001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::CleanTransition();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::CleanTransition();
    result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CleanTransition002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CleanTransition002, TestSize.Level1)
{
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    ViewAbstract::CleanTransition();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetNodeBackdropBlur001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetNodeBackdropBlur001, TestSize.Level1)
{
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(itemNode, nullptr);
    FrameNode *frameNode = Referenced::RawPtr(itemNode);
    CHECK_NULL_VOID(frameNode);
    Dimension radius;
    BlurOption blurOption;
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewAbstract::SetNodeBackdropBlur(frameNode, radius, blurOption);
    EXPECT_NE(itemNode, nullptr);
}

/**
 * @tc.name: SetBackdropBlur001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetBackdropBlur001, TestSize.Level1)
{
    auto itemNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode *frameNode = Referenced::RawPtr(itemNode);
    CHECK_NULL_VOID(frameNode);
    Dimension radius;
    BlurOption blurOption;
    SysOptions sysOptions;
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewAbstract::SetBackdropBlur(frameNode, radius, blurOption, sysOptions);
    EXPECT_NE(itemNode, nullptr);
}

/**
 * @tc.name: SetOverlayComponentContent001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetOverlayComponentContent001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
    RefPtr<NG::FrameNode> contentNode = AceType::MakeRefPtr<FrameNode>("content", 1, AceType::MakeRefPtr<Pattern>());
    std::optional<Alignment> align;
    std::optional<Dimension> offsetX;
    std::optional<Dimension> offsetY;
    ViewAbstract::SetOverlayComponentContent(contentNode, align, offsetX, offsetY);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetOverlayComponentContent(contentNode, align, offsetX, offsetY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AddOverlayToFrameNode001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, AddOverlayToFrameNode001, TestSize.Level1)
{
    RefPtr<NG::FrameNode> contentNode = AceType::MakeRefPtr<FrameNode>("content", 1, AceType::MakeRefPtr<Pattern>());
    std::optional<Alignment> align;
    std::optional<Dimension> offsetX;
    std::optional<Dimension> offsetY;
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::AddOverlayToFrameNode(contentNode, align, offsetX, offsetY);
    ASSERT_NE(contentNode, nullptr);
}

/**
 * @tc.name: AddOverlayToFrameNode002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, AddOverlayToFrameNode002, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    ViewAbstract::CleanTransition();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    RefPtr<NG::FrameNode> contentNode = AceType::MakeRefPtr<FrameNode>("content", 1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(contentNode, nullptr);
    std::optional<Alignment> align;
    std::optional<Dimension> offsetX;
    std::optional<Dimension> offsetY;
    ViewAbstract::AddOverlayToFrameNode(contentNode, align, offsetX, offsetY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetOverlayBuilder001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetOverlayBuilder001, TestSize.Level1)
{
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    std::optional<Alignment> align;
    std::optional<Dimension> offsetX;
    std::optional<Dimension> offsetY;
    ViewAbstract::SetOverlayBuilder(nullptr, align, offsetX, offsetY);
    EXPECT_FALSE(result);

    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetOverlayBuilder(nullptr, align, offsetX, offsetY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetClipEdge001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetClipEdge001, TestSize.Level1)
{
    bool isClip = true;
    ViewAbstract::SetClipEdge(nullptr, isClip);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    isClip = false;
    ViewAbstract::SetClipEdge(AceType::RawPtr(node), isClip);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SetClipShape001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetClipShape001, TestSize.Level1)
{
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>();
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    
    ViewAbstract::SetClipShape(basicShape);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetClipShape(basicShape);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetClipShape002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetClipShape002, TestSize.Level1)
{
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>();
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    auto result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    auto frameNode = FrameNode::CreateFrameNode("test", 1, AceType::MakeRefPtr<Pattern>(), true);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewStackProcessor::GetInstance()->Push(frameNode);
    ViewAbstract::SetClipShape(basicShape);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: SetAttractionEffect001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetAttractionEffect001, TestSize.Level1)
{
    AttractionEffect effect;
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    
    ViewAbstract::SetAttractionEffect(effect);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetAttractionEffect(effect);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetLightIlluminated001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetLightIlluminated001, TestSize.Level1)
{
    uint32_t value = 100;
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    
    ViewAbstract::SetLightIlluminated(value);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetLightIlluminated(value);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetPrivacySensitive001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetPrivacySensitive001, TestSize.Level1)
{
    bool flag = true;
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    
    ViewAbstract::SetPrivacySensitive(flag);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetPrivacySensitive(flag);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetMask001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetMask001, TestSize.Level1)
{
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    RefPtr<BasicShape> basicShape = AceType::MakeRefPtr<BasicShape>();
    ViewAbstract::SetMask(frameNode, basicShape);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: SetProgressMask001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetProgressMask001, TestSize.Level1)
{
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    RefPtr<ProgressMaskProperty> progress;
    ViewAbstract::SetProgressMask(frameNode, progress);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: SetForegroundEffect001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetForegroundEffect001, TestSize.Level1)
{
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    float radius = 10.0f;
    SysOptions sysOptions;
    ViewAbstract::SetForegroundEffect(frameNode, radius, sysOptions);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: CleanTransit001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, CleanTransit001, TestSize.Level1)
{
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    ViewAbstract::CleanTransition(frameNode);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}

/**
 * @tc.name: SetOverlayBuilder002
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetOverlayBuilder002, TestSize.Level1)
{
    std::function<void()> buildFunc = []() {};
    std::optional<Alignment> align;
    std::optional<Dimension> offsetX;
    std::optional<Dimension> offsetY;
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    
    ViewAbstract::SetOverlayBuilder(std::move(buildFunc), align, offsetX, offsetY);
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetOverlayBuilder(std::move(buildFunc), align, offsetX, offsetY);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetDraggable001
 * @tc.desc: Test SetNeedFocus of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDraggable001, TestSize.Level1)
{
    auto progressNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    FrameNode* frameNode = Referenced::RawPtr(progressNode);
    frameNode->renderContext_ = AceType::MakeRefPtr<MockRenderContext>();
    bool draggable = true;
    
    ViewAbstract::SetDraggable(frameNode, draggable);
    draggable = false;
    ViewAbstract::SetDraggable(frameNode, draggable);
    EXPECT_NE(frameNode->renderContext_, nullptr);
}
} // namespace OHOS::Ace::NG