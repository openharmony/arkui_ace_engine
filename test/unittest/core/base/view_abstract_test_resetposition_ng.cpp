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
} // namespace OHOS::Ace::NG