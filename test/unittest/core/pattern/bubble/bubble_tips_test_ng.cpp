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
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"

#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_engine.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string BUBBLE_MESSAGE = "Hello World";
const std::u16string TIPS_MSG_1 = u"tips 123";
const std::u16string TIPS_MSG_2 = u"tips 1\ntips 2\nend";
const std::u16string TIPS_MSG_3 = std::u16string(2500, u'A');
const std::u16string TIPS_MSG_4 = std::u16string(1500, u'A');
const SizeF MAX_SIZE = { 480.0f, 100.0f };
constexpr float DEVICE_WIDTH = 720.0f;
constexpr float DEVICE_HEIGHT = 1280.0f;
constexpr float TOP_INSET = 72.0f;
constexpr float BOTTOM_INSET = 72.0f;
constexpr float HALF = 0.5f;
constexpr float LINE_HEIGHT = 16.0f;
constexpr float TEXT_WIDTH = 14.0f;
constexpr float TEXT_PADDING = 12.0f;
constexpr int32_t DOUBLE = 2;
constexpr float WIDTH = 100.0f;
constexpr float HEIGHT = 100.0f;
constexpr Dimension TIPS_MARGIN_SPACE = 8.0_vp;
constexpr Dimension MOUSE_WIDTH = 16.0_vp;
constexpr Dimension MOUSE_HEIGHT = 24.0_vp;
constexpr Dimension KEYBOARD_SPACE = 8.0_vp;
constexpr Dimension RADIUS = 8.0_vp;
constexpr float ARROW_WIDTH_PX = 30.0f;
constexpr float ARROW_HEIGHT_PX = 30.0f;
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
constexpr float LP_SCREEN_WIDTH = 2160.0f;
constexpr float LP_SCREEN_HEIGHT = 3840.0f;
constexpr float BUBBLE_WIDTH = 200.0f;
constexpr float BUBBLE_HEIGHT = 50.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const SizeF WRAPPER_SIZE = { 1000.0f, 1000.0f };
const SafeAreaInsets::Inset KEYBOARD_INSET = { .start = 500.f, .end = 1000.f };
} // namespace
class BubbleTipsTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

protected:
    static RefPtr<FrameNode> CreateTargetNode();
    static RefPtr<FrameNode> CreateTipsNode(const RefPtr<PopupParam>& param, const std::u16string& spanString);
    static RefPtr<PopupParam> CreateTipsParamForCursor();
    static RefPtr<PopupParam> CreateTipsParamWithArrow();
    static RefPtr<FrameNode> CreateTipsNodeWithArrow(
        const RefPtr<PopupParam>& param, const std::u16string& spanString);
    static void UpdateLayoutPropWidthArrow(RefPtr<FrameNode> frameNode);
    static void UpdateConstraintFullScreen(RefPtr<LayoutWrapperNode> layoutWrapper);
    static void UpdateConstraintLPScreen(RefPtr<LayoutWrapperNode> layoutWrapper);
    static void AddTextNodeToTips(RefPtr<FrameNode> frameNode, RefPtr<LayoutWrapperNode> layoutWrapper);
    SizeF ConstructParagraphs(const std::u16string& text, int32_t lineCount);
    RefPtr<BubbleLayoutAlgorithm> MeasureTipsRegion(const std::u16string& text, const Offset& mouseOffset);
    static LayoutConstraintF childLayoutConstraint;
    static RefPtr<PopupTheme> popupTheme;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
};

LayoutConstraintF BubbleTipsTestNg::childLayoutConstraint;
RefPtr<PopupTheme> BubbleTipsTestNg::popupTheme;

void BubbleTipsTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;
    MockContainer::Current()->pipelineContext_->dipScale_ = 1.5f;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    BubbleTipsTestNg::popupTheme = AceType::MakeRefPtr<PopupTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == HyperlinkTheme::TypeId()) {
            return AceType::MakeRefPtr<HyperlinkTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else if (type == ShadowTheme::TypeId()) {
            return AceType::MakeRefPtr<ShadowTheme>();
        } else {
            return BubbleTipsTestNg::popupTheme;
        }
    });
    childLayoutConstraint.maxSize = MAX_SIZE;
}
void BubbleTipsTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void BubbleTipsTestNg::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
}

void BubbleTipsTestNg::TearDown()
{
    MockParagraph::TearDown();
}

RefPtr<FrameNode> BubbleTipsTestNg::CreateTargetNode()
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    return frameNode;
}

RefPtr<FrameNode> BubbleTipsTestNg::CreateTipsNode(const RefPtr<PopupParam>& param, const std::u16string& spanString)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto tipsNode =
        BubbleView::CreateBubbleNode(targetTag, targetId, param, AceType::MakeRefPtr<SpanString>(spanString));
    auto bubblePattern = tipsNode->GetPattern<BubblePattern>();
    bubblePattern->mouseOffset_ = Offset();
    tipsNode->layoutAlgorithm_ = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(bubblePattern->CreateLayoutAlgorithm());
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->top_ = TOP_INSET;
    layoutAlgorithm->marginTop_ = TOP_INSET + TIPS_MARGIN_SPACE.ConvertToPx();
    layoutAlgorithm->bottom_ = BOTTOM_INSET;
    layoutAlgorithm->marginBottom_ = BOTTOM_INSET + TIPS_MARGIN_SPACE.ConvertToPx();
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->marginStart_ = TIPS_MARGIN_SPACE.ConvertToPx();
    layoutAlgorithm->marginEnd_ = TIPS_MARGIN_SPACE.ConvertToPx();
    layoutAlgorithm->targetSpace_ = TIPS_MARGIN_SPACE;
    auto property = tipsNode->GetLayoutProperty<BubbleLayoutProperty>();
    property->UpdateShowAtAnchor(TipsAnchorType::CURSOR);
    return tipsNode;
}

RefPtr<PopupParam> BubbleTipsTestNg::CreateTipsParamForCursor()
{
    auto tipsParam = AceType::MakeRefPtr<PopupParam>();
    tipsParam->SetAnchorType(TipsAnchorType::CURSOR);
    tipsParam->SetBlockEvent(false);
    tipsParam->SetTipsFlag(true);
    tipsParam->SetShowInSubWindow(true);
    tipsParam->SetKeyBoardAvoidMode(PopupKeyboardAvoidMode::DEFAULT);
    return tipsParam;
}

RefPtr<FrameNode> BubbleTipsTestNg::CreateTipsNodeWithArrow(
    const RefPtr<PopupParam>& param, const std::u16string& spanString)
{
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto frameNode =
        BubbleView::CreateBubbleNode(targetTag, targetId, param, AceType::MakeRefPtr<SpanString>(spanString));
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    CHECK_NULL_RETURN(bubblePattern, frameNode);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    CHECK_NULL_RETURN(bubbleLayoutAlgorithm, frameNode);
    bubbleLayoutAlgorithm->targetTag_ = targetTag;
    bubbleLayoutAlgorithm->targetNodeId_ = targetId;
    return frameNode;
}

RefPtr<PopupParam> BubbleTipsTestNg::CreateTipsParamWithArrow()
{
    auto tipsParam = AceType::MakeRefPtr<PopupParam>();
    CHECK_NULL_RETURN(tipsParam, nullptr);
    tipsParam->SetTipsFlag(true);
    tipsParam->SetIsShow(true);
    tipsParam->SetMessage(BUBBLE_MESSAGE);
    tipsParam->SetUseCustomComponent(false);
    Dimension arrowWidth = Dimension(ARROW_WIDTH_PX, DimensionUnit::LPX);
    Dimension arrowHeight = Dimension(ARROW_HEIGHT_PX, DimensionUnit::LPX);
    tipsParam->SetArrowWidth(arrowWidth);
    tipsParam->SetArrowHeight(arrowHeight);
    tipsParam->SetEnableArrow(true);
    tipsParam->SetShowInSubWindow(true);
    return tipsParam;
}

void BubbleTipsTestNg::UpdateLayoutPropWidthArrow(RefPtr<FrameNode> frameNode)
{
    CHECK_NULL_VOID(frameNode);
    Dimension arrowWidth = Dimension(ARROW_WIDTH_PX, DimensionUnit::LPX);
    Dimension arrowHeight = Dimension(ARROW_HEIGHT_PX, DimensionUnit::LPX);
    auto layoutProp = frameNode->GetLayoutProperty<BubbleLayoutProperty>();
    CHECK_NULL_VOID(layoutProp);
    layoutProp->UpdateShowInSubWindow(true);
    layoutProp->UpdateIsTips(true);
    layoutProp->UpdateEnableArrow(true);
    layoutProp->UpdateArrowWidth(arrowWidth);
    layoutProp->UpdateArrowHeight(arrowHeight);
    layoutProp->UpdateRadius(RADIUS);
}

void BubbleTipsTestNg::UpdateConstraintFullScreen(RefPtr<LayoutWrapperNode> layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FULL_SCREEN_WIDTH), CalcLength(FULL_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
}

void BubbleTipsTestNg::UpdateConstraintLPScreen(RefPtr<LayoutWrapperNode> layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    layoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(LP_SCREEN_WIDTH), CalcLength(LP_SCREEN_HEIGHT)));
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = FULL_SCREEN_SIZE;
    parentLayoutConstraint.percentReference = FULL_SCREEN_SIZE;
    parentLayoutConstraint.selfIdealSize.SetSize(SizeF(LP_SCREEN_WIDTH, LP_SCREEN_HEIGHT));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(parentLayoutConstraint);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
}

void BubbleTipsTestNg::AddTextNodeToTips(RefPtr<FrameNode> frameNode, RefPtr<LayoutWrapperNode> layoutWrapper)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(layoutWrapper);
    auto textFrameNode = BubbleView::CreateMessage(BUBBLE_MESSAGE, true);
    CHECK_NULL_VOID(layoutWrapper);
    RefPtr<GeometryNode> textGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    textGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, textGeometryNode, textFrameNode->GetLayoutProperty());
    textLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    textLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(BUBBLE_WIDTH), CalcLength(BUBBLE_HEIGHT)));
    auto boxLayoutAlgorithm = textFrameNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    CHECK_NULL_VOID(boxLayoutAlgorithm);
    textLayoutWrapper->SetLayoutAlgorithm(AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(boxLayoutAlgorithm));
    frameNode->AddChild(textFrameNode);
    layoutWrapper->AppendChild(textLayoutWrapper);
}

SizeF BubbleTipsTestNg::ConstructParagraphs(const std::u16string& text, int32_t lineCount)
{
    pManager->SetParagraphs({});
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth())
        .WillRepeatedly(Return(std::min(text.length() * TEXT_WIDTH + TEXT_PADDING + TEXT_PADDING, MAX_SIZE.Width())));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(lineCount));
    EXPECT_CALL(*paragraph, GetHeight())
        .WillRepeatedly(Return(std::min(lineCount * LINE_HEIGHT + TEXT_PADDING + TEXT_PADDING,
            DEVICE_HEIGHT - TOP_INSET - BOTTOM_INSET - static_cast<float>(TIPS_MARGIN_SPACE.ConvertToPx()) * DOUBLE)));
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    pManager->AddParagraph({ .paragraph = paragraph, .start = 0, .end = text.length() });
    return { paragraph->GetMaxWidth(), paragraph->GetHeight() };
}

RefPtr<BubbleLayoutAlgorithm> BubbleTipsTestNg::MeasureTipsRegion(const std::u16string& text, const Offset& mouseOffset)
{
    auto singleTextCount =
        (int32_t)((MAX_SIZE.Width() - TEXT_PADDING - TEXT_PADDING) / TEXT_WIDTH);
    if (NearEqual(singleTextCount, 0)) {
        return nullptr;
    }
    int32_t lineCount = text.length() / singleTextCount + ((text.length() % singleTextCount) ? 1 : 0);
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), text);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    EXPECT_NE(layoutAlgorithm, nullptr);
    layoutAlgorithm->measureChildSizeAfter_ = ConstructParagraphs(text, lineCount);
    auto tipsLayoutWrapper = tipsNode->CreateLayoutWrapper();
    auto childWrapper = tipsLayoutWrapper->GetAllChildrenWithBuild().front();
    layoutAlgorithm->targetOffset_ = OffsetF(mouseOffset.GetX(), mouseOffset.GetY());
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->MeasureTipsRegion(childWrapper, childLayoutConstraint);
    return layoutAlgorithm;
}

/**
 * @tc.name: MesureTipsRegion001
 * @tc.desc: Test BubbleLayoutAlgorithm::MesureTipsRegion.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, MesureTipsRegion001, TestSize.Level1)
{
    /*
     * @tc.desc: 1.Set mouse position to calculate target position.
                 2.Get mouse position.
     */
    Offset offset(TIPS_MARGIN_SPACE.ConvertToPx(), TOP_INSET + TIPS_MARGIN_SPACE.ConvertToPx());
    auto layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::BOTTOM_LEFT);

    offset = Offset(DEVICE_WIDTH - TIPS_MARGIN_SPACE.ConvertToPx(), TOP_INSET + TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::BOTTOM);

    offset = Offset(DEVICE_WIDTH - TIPS_MSG_1.length() * TEXT_WIDTH + TEXT_PADDING + TEXT_PADDING,
        TOP_INSET + TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::BOTTOM_RIGHT);

    offset = Offset(TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT - BOTTOM_INSET - TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::TOP_LEFT);

    offset = Offset(
        DEVICE_WIDTH - TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT - BOTTOM_INSET - TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::TOP);

    offset = Offset(DEVICE_WIDTH - TIPS_MSG_1.length() * TEXT_WIDTH + TEXT_PADDING + TEXT_PADDING,
        DEVICE_HEIGHT - BOTTOM_INSET - TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_1, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::TOP_RIGHT);

    offset = Offset(TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT * HALF);
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_4, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::RIGHT_TOP);

    offset = Offset(DEVICE_WIDTH, DEVICE_HEIGHT * HALF);
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_4, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::LEFT_TOP);

    offset = Offset(DEVICE_WIDTH * HALF, DEVICE_HEIGHT - BOTTOM_INSET - TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_4, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::TOP);

    offset = Offset(DEVICE_WIDTH * HALF, TOP_INSET + TIPS_MARGIN_SPACE.ConvertToPx());
    layoutAlgorithm = MeasureTipsRegion(TIPS_MSG_4, offset);
    EXPECT_EQ(layoutAlgorithm->tipsPlacement_, Placement::BOTTOM);
}

/**
 * @tc.name: ResetTipsMaxLines001
 * @tc.desc: Test ResetTipsMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, ResetTipsMaxLines001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    tipsNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    tipsNode->RemoveChildAtIndex(0);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->MountToParent(columnNode);
    columnNode->MountToParent(tipsNode);

    auto bubbleProp = AceType::DynamicCast<BubbleLayoutProperty>(tipsNode->GetLayoutProperty());
    bubbleProp->layoutConstraint_ = LayoutConstraintF();
    bubbleProp->contentConstraint_ = LayoutConstraintF();

    const auto& children = tipsNode->GetAllChildrenWithBuild();
    auto childWrapper = children.front();
    auto node = childWrapper->GetAllChildrenWithBuild().front();
    auto layoutProps = AceType::DynamicCast<TextLayoutProperty>(node->GetLayoutProperty());
    EXPECT_EQ(layoutProps, nullptr);

    /**
     * @tc.steps: step2. test ResetTipsMaxLines.
     */
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->Measure(AceType::RawPtr(tipsNode));
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->targetOffset_ = OffsetF(DEVICE_WIDTH * HALF, DEVICE_HEIGHT * HALF);
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->followTransformOfTarget_ = false;
    layoutAlgorithm->InitTargetSizeAndPosition(false, nullptr);
    EXPECT_EQ(layoutAlgorithm->targetOffset_, OffsetF(DEVICE_WIDTH * HALF, DEVICE_HEIGHT * HALF));
}

/**
 * @tc.name: ResetTipsMaxLines002
 * @tc.desc: Test ResetTipsMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, ResetTipsMaxLines002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto bubbleProp = AceType::DynamicCast<BubbleLayoutProperty>(tipsNode->GetLayoutProperty());
    bubbleProp->layoutConstraint_ = LayoutConstraintF();
    bubbleProp->contentConstraint_ = LayoutConstraintF();

    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    const auto& children = tipsNode->GetAllChildrenWithBuild();
    auto childWrapper = children.front();
    auto text = childWrapper->GetAllChildrenWithBuild().front();
    auto layoutProps = AceType::DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    /**
     * @tc.steps: step2. test ResetTipsMaxLines.
     */
    layoutProps->UpdateMaxLines(DOUBLE);
    layoutAlgorithm->Measure(AceType::RawPtr(tipsNode));
    EXPECT_NE(layoutProps->GetMaxLinesValue(0), DOUBLE);
}

/**
 * @tc.name: ResetTipsMaxLines003
 * @tc.desc: Test ResetTipsMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, ResetTipsMaxLines003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto param = CreateTipsParamForCursor();
    param->SetAnchorType(TipsAnchorType::TARGET);
    auto tipsNode = CreateTipsNode(param, TIPS_MSG_1);
    ASSERT_NE(tipsNode, nullptr);
    auto bubbleProp = AceType::DynamicCast<BubbleLayoutProperty>(tipsNode->GetLayoutProperty());
    bubbleProp->layoutConstraint_ = LayoutConstraintF();
    bubbleProp->contentConstraint_ = LayoutConstraintF();
    bubbleProp->UpdateShowAtAnchor(TipsAnchorType::TARGET);

    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    const auto& children = tipsNode->GetAllChildrenWithBuild();
    auto childWrapper = children.front();
    ASSERT_NE(childWrapper, nullptr);
    auto text = childWrapper->GetAllChildrenWithBuild().front();
    ASSERT_NE(text, nullptr);
    auto layoutProps = AceType::DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    /**
     * @tc.steps: step2. test ResetTipsMaxLines.
     */
    layoutProps->UpdateMaxLines(DOUBLE);
    layoutAlgorithm->Measure(AceType::RawPtr(tipsNode));
    EXPECT_NE(layoutProps->GetMaxLinesValue(0), DOUBLE);
}

/**
 * @tc.name: TipsFitAvailableRect001
 * @tc.desc: Test FitAvailableRect for tips.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, TipsFitAvailableRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto pipelineContext = frameNode->GetContextRefPtr();
    ASSERT_NE(pipelineContext, nullptr);
    /**
     * @tc.steps: step2. test FitAvailableRect.
     */
    pipelineContext->UpdateDisplayAvailableRect(Rect(0.0f, 0.0f, 0.0f, 0.0f));
    layoutAlgorithm->isTips_ = true;
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->expandDisplay_ = true;
    layoutAlgorithm->FitAvailableRect(AceType::RawPtr(layoutWrapper), true);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: TipsHandleKeyboardTest
 * @tc.desc: Test HandleKeyboard function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, TipsHandleKeyboardTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto targetId = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(targetId, targetTag));
    ASSERT_NE(frameNode, nullptr);

    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    bubblePattern->SetAvoidKeyboard(true);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());

    /**
     * @tc.steps: step2. test HandleKeyboard.
     */
    auto pipeline = MockPipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    manager->keyboardInset_ = KEYBOARD_INSET;
    layoutAlgorithm->wrapperSize_ = WRAPPER_SIZE;
    layoutAlgorithm->marginBottom_ = .0f;
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), false);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(),
        WRAPPER_SIZE.Height() - KEYBOARD_INSET.Length() + KEYBOARD_SPACE.ConvertToPx());
    layoutAlgorithm->GetChildPositionNew(SizeF(), frameNode->GetLayoutProperty<BubbleLayoutProperty>(), nullptr);

    layoutAlgorithm->wrapperSize_ = WRAPPER_SIZE;
    layoutAlgorithm->marginBottom_ = .0f;
    layoutAlgorithm->followCursor_ = false;
    layoutAlgorithm->HandleKeyboard(AceType::RawPtr(layoutWrapper), false);
    EXPECT_EQ(layoutAlgorithm->wrapperSize_.Height(), WRAPPER_SIZE.Height() - KEYBOARD_INSET.Length());
}

/**
 * @tc.name: UpdateTextNodeMaxLinesTest001
 * @tc.desc: Test UpdateTextNodeMaxLines function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, UpdateTextNodeMaxLinesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    pManager->SetParagraphs({});
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(LINE_HEIGHT));
    pManager->AddParagraph({ .paragraph = paragraph, .start = 0, .end = TIPS_MSG_1.length() });

    /**
     * @tc.steps: step2. test UpdateTextNodeMaxLines.
     */
    LayoutConstraintF constraint;
    constraint.maxSize = WRAPPER_SIZE;
    layoutAlgorithm->UpdateTextNodeMaxLines(tipsNode->GetChildByIndex(0), constraint);
    auto text = tipsNode->GetChildByIndex(0)->GetChildByIndex(0);
    auto layoutProps = AceType::DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    EXPECT_EQ(layoutProps->GetMaxLines(), std::floor(WRAPPER_SIZE.Height() / LINE_HEIGHT) - 1);

    tipsNode->RemoveChildAtIndex(0);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto buttonNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    buttonNode->MountToParent(columnNode);
    columnNode->MountToParent(tipsNode);

    /**
     * @tc.steps: step3. test UpdateTextNodeMaxLines return.
     */
    layoutAlgorithm->UpdateTextNodeMaxLines(columnNode, LayoutConstraintF());
}

/**
 * @tc.name: CalculateTipsDirectionsTest001
 * @tc.desc: Test CalculateTipsDirections function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, CalculateTipsDirectionsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());

    /**
     * @tc.steps: step2. test CalculateTipsDirections.
     */
    SizeF newSize;
    layoutAlgorithm->targetOffset_ = { TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT - BOTTOM_INSET };
    auto placement = layoutAlgorithm->CalculateTipsDirections(newSize);
    EXPECT_EQ(placement, Placement::TOP_LEFT);

    layoutAlgorithm->targetOffset_ = { TOP_INSET, TIPS_MARGIN_SPACE.ConvertToPx() };
    placement = layoutAlgorithm->CalculateTipsDirections(newSize);
    EXPECT_EQ(placement, Placement::BOTTOM_LEFT);

    layoutAlgorithm->targetOffset_ = { DEVICE_WIDTH - TIPS_MARGIN_SPACE.ConvertToPx() - MOUSE_WIDTH.ConvertToPx(),
        DEVICE_HEIGHT - BOTTOM_INSET * DOUBLE };
    layoutAlgorithm->isHalfFoldHover_ = true;
    placement = layoutAlgorithm->CalculateTipsDirections(newSize);
    EXPECT_EQ(placement, Placement::LEFT_TOP);
}

/**
 * @tc.name: GetPositionWithPlacementLeftTopTest001
 * @tc.desc: Test GetPositionWithPlacementLeftTop function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, GetPositionWithPlacementLeftTopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->targetOffset_ = { DEVICE_WIDTH, DEVICE_HEIGHT * HALF };
    layoutAlgorithm->targetSpace_ = Dimension();
    layoutAlgorithm->resetTipsSize_ = true;
    /**
     * @tc.steps: step2. test GetPositionWithPlacementLeftTop.
     */
    OffsetF topPosition;
    OffsetF bottomPosition;
    OffsetF arrowPosition;
    auto position =
        layoutAlgorithm->GetPositionWithPlacementLeftTop(MAX_SIZE, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), DEVICE_WIDTH - MAX_SIZE.Width());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT * HALF);

    layoutAlgorithm->isHalfFoldHover_ = true;
    position = layoutAlgorithm->GetPositionWithPlacementLeftTop(MAX_SIZE, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), DEVICE_WIDTH - MAX_SIZE.Width());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT * HALF);
}

/**
 * @tc.name: GetPositionWithPlacementLeftTopTest002
 * @tc.desc: Test GetPositionWithPlacementLeftTop function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, GetPositionWithPlacementLeftTopTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->targetOffset_ = { DEVICE_WIDTH, DEVICE_HEIGHT * HALF };
    layoutAlgorithm->targetSpace_ = Dimension();
    layoutAlgorithm->resetTipsSize_ = true;
    /**
     * @tc.steps: step2. test GetPositionWithPlacementLeftTop.
     */
    OffsetF topPosition;
    OffsetF bottomPosition;
    OffsetF arrowPosition;
    const SizeF childSize { 480.0, DEVICE_HEIGHT * HALF };
    auto position =
        layoutAlgorithm->GetPositionWithPlacementLeftTop(childSize, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), DEVICE_WIDTH - childSize.Width());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT - layoutAlgorithm->marginBottom_ - childSize.Height());

    layoutAlgorithm->isHalfFoldHover_ = true;
    position = layoutAlgorithm->GetPositionWithPlacementLeftTop(childSize, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), DEVICE_WIDTH - childSize.Width());
    EXPECT_EQ(position.GetY(), layoutAlgorithm->wrapperRect_.Bottom() - childSize.Height());
}

/**
 * @tc.name: GetPositionWithPlacementRightTopTest001
 * @tc.desc: Test GetPositionWithPlacementRightTop function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, GetPositionWithPlacementRightTopTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->targetOffset_ = { TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT * HALF };
    layoutAlgorithm->targetSpace_ = Dimension();
    layoutAlgorithm->resetTipsSize_ = true;
    /**
     * @tc.steps: step2. test GetPositionWithPlacementRightTop.
     */
    OffsetF topPosition;
    OffsetF bottomPosition;
    OffsetF arrowPosition;
    auto position =
        layoutAlgorithm->GetPositionWithPlacementRightTop(MAX_SIZE, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), TIPS_MARGIN_SPACE.ConvertToPx() + MOUSE_WIDTH.ConvertToPx());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT * HALF);

    layoutAlgorithm->isHalfFoldHover_ = true;
    position = layoutAlgorithm->GetPositionWithPlacementRightTop(MAX_SIZE, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), TIPS_MARGIN_SPACE.ConvertToPx() + MOUSE_WIDTH.ConvertToPx());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT * HALF);
}
/**
 * @tc.name: GetPositionWithPlacementRightTopTest002
 * @tc.desc: Test GetPositionWithPlacementRightTop function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, GetPositionWithPlacementRightTopTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto tipsNode = CreateTipsNode(CreateTipsParamForCursor(), TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->targetSize_ = SizeF(MOUSE_WIDTH.ConvertToPx(), MOUSE_HEIGHT.ConvertToPx());
    layoutAlgorithm->targetOffset_ = { TIPS_MARGIN_SPACE.ConvertToPx(), DEVICE_HEIGHT * HALF };
    layoutAlgorithm->targetSpace_ = Dimension();
    layoutAlgorithm->resetTipsSize_ = true;
    /**
     * @tc.steps: step2. test GetPositionWithPlacementRightTop.
     */
    OffsetF topPosition;
    OffsetF bottomPosition;
    OffsetF arrowPosition;
    const SizeF childSize { 480.0, DEVICE_HEIGHT * HALF };
    auto position =
        layoutAlgorithm->GetPositionWithPlacementRightTop(childSize, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), TIPS_MARGIN_SPACE.ConvertToPx() + MOUSE_WIDTH.ConvertToPx());
    EXPECT_EQ(position.GetY(), DEVICE_HEIGHT - layoutAlgorithm->marginBottom_ - childSize.Height());

    layoutAlgorithm->isHalfFoldHover_ = true;
    position = layoutAlgorithm->GetPositionWithPlacementRightTop(childSize, topPosition, bottomPosition, arrowPosition);
    EXPECT_EQ(position.GetX(), TIPS_MARGIN_SPACE.ConvertToPx() + MOUSE_WIDTH.ConvertToPx());
    EXPECT_EQ(position.GetY(), layoutAlgorithm->wrapperRect_.Bottom() - childSize.Height());
}

/**
 * @tc.name: IsPaintDoubleBorderTest001
 * @tc.desc: Test IsPaintDoubleBorder function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, IsPaintDoubleBorderTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    const int32_t version = 20;
    auto param = CreateTipsParamForCursor();
    auto tipsNode = CreateTipsNode(param, TIPS_MSG_1);
    BubbleView::UpdateCommonParam(tipsNode->GetId(), param);
    auto pipeline = tipsNode->GetContext();
    pipeline->minPlatformVersion_ = version;
    auto pattern = tipsNode->GetPattern<BubblePattern>();
    auto paintMethod = AceType::DynamicCast<BubblePaintMethod>(pattern->CreateNodePaintMethod());
    tipsNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        tipsNode->GetRenderContext(), tipsNode->geometryNode_, tipsNode->paintProperty_);
    /**
     * @tc.steps: step2. test IsPaintDoubleBorder.
     */
    EXPECT_EQ(paintMethod->IsPaintDoubleBorder(AceType::RawPtr(paintWrapper)), false);
    popupTheme->tipsDoubleBorderEnable_ = true;
    EXPECT_EQ(paintMethod->IsPaintDoubleBorder(AceType::RawPtr(paintWrapper)), true);
}

/**
 * @tc.name: IsPaintDoubleBorderTest002
 * @tc.desc: Test IsPaintDoubleBorder function.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, IsPaintDoubleBorderTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    const int32_t version = 20;
    auto param = CreateTipsParamForCursor();
    param->SetAnchorType(TipsAnchorType::TARGET);
    auto tipsNode = CreateTipsNode(param, TIPS_MSG_1);
    BubbleView::UpdateCommonParam(tipsNode->GetId(), param);
    auto pipeline = tipsNode->GetContext();
    pipeline->minPlatformVersion_ = version;
    auto pattern = tipsNode->GetPattern<BubblePattern>();
    auto paintMethod = AceType::DynamicCast<BubblePaintMethod>(pattern->CreateNodePaintMethod());
    tipsNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(
        tipsNode->GetRenderContext(), tipsNode->geometryNode_, tipsNode->paintProperty_);
    /**
     * @tc.steps: step2. test IsPaintDoubleBorder.
     */
    popupTheme->tipsDoubleBorderEnable_ = false;
    EXPECT_EQ(paintMethod->IsPaintDoubleBorder(AceType::RawPtr(paintWrapper)), false);
    popupTheme->tipsDoubleBorderEnable_ = true;
    EXPECT_EQ(paintMethod->IsPaintDoubleBorder(AceType::RawPtr(paintWrapper)), true);
}

/**
 * @tc.name: FitMouseOffset001
 * @tc.desc: Test FitMouseOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, FitMouseOffset001, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    MockPipelineContext::GetCurrent()->displayWindowRectInfo_ = Rect(0.0, 0.0, WIDTH, HEIGHT);
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->expandDisplay_ = false;
    const double offset = 10.0;
    const double size = 20.0;
    const int32_t parentId = 1;
    const Rect subWindow(offset, offset, size, size);
    const OffsetF targetPosition(75.0, 75.0);
    RefPtr<PipelineContext> pipelineContext = targetNode->GetContextRefPtr();
    auto containerId = pipelineContext->GetInstanceId();
    AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(containerId))->isSubContainer_ = true;
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    SubwindowManager::GetInstance()->parentContainerMap_[MockContainer::CurrentId()] = parentId;
    AceEngine::Get().AddContainer(parentId, AceType::MakeRefPtr<MockContainer>());
    auto parentContainer = AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(parentId));
    parentContainer->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    EXPECT_CALL(*parentContainer, GetGlobalScaledRect()).WillOnce(Return(subWindow));
    layoutAlgorithm->targetOffset_ = OffsetF((offset + size) * HALF, (offset + size) * HALF);
    layoutAlgorithm->FitMouseOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutAlgorithm->targetOffset_, targetPosition);
    AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(containerId))->isSubContainer_ = false;
}

/**
 * @tc.name: FitMouseOffset002
 * @tc.desc: Test FitMouseOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, FitMouseOffset002, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    MockPipelineContext::GetCurrent()->displayWindowRectInfo_ = Rect(0.0, 0.0, WIDTH, HEIGHT);
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->expandDisplay_ = false;
    const double offset = 10.0;
    const double size = 20.0;
    const Rect subWindow(offset, offset, size, size);
    const OffsetF targetPosition((offset + size) * HALF, (offset + size) * HALF);
    MockContainer::UpdateCurrent(1);
    layoutAlgorithm->targetOffset_ = targetPosition;
    layoutAlgorithm->FitMouseOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutAlgorithm->targetOffset_, targetPosition);
}

/**
 * @tc.name: FitMouseOffset003
 * @tc.desc: Test FitMouseOffset.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, FitMouseOffset003, TestSize.Level1)
{
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    MockPipelineContext::GetCurrent()->displayWindowRectInfo_ = Rect(0.0, 0.0, WIDTH, HEIGHT);
    layoutAlgorithm->followCursor_ = true;
    layoutAlgorithm->expandDisplay_ = false;
    const Rect subWindow(0.0, 0.0, 0.0, 0.0);
    const OffsetF targetPosition(0.0, 0.0);
    const int32_t parentId = 1;
    RefPtr<PipelineContext> pipelineContext = targetNode->GetContextRefPtr();
    auto containerId = pipelineContext->GetInstanceId();
    AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(containerId))->isSubContainer_ = true;
    auto parentContainer = AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(parentId));
    parentContainer->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    EXPECT_CALL(*parentContainer, GetGlobalScaledRect()).WillOnce(Return(subWindow));
    layoutAlgorithm->targetOffset_ = targetPosition;
    layoutAlgorithm->FitMouseOffset(AceType::RawPtr(layoutWrapper));
    EXPECT_EQ(layoutAlgorithm->targetOffset_, targetPosition);
    AceType::DynamicCast<MockContainer>(AceEngine::Get().GetContainer(containerId))->isSubContainer_ = false;
}

/**
 * @tc.name: MeasureTipsFollowTarget001
 * @tc.desc: Test MeasureTipsFollowTarget.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, MeasureTipsFollowTarget001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto param = CreateTipsParamForCursor();
    param->SetAnchorType(TipsAnchorType::TARGET);
    auto tipsNode = CreateTipsNode(param, TIPS_MSG_1);
    auto layoutAlgorithm =
        AceType::DynamicCast<BubbleLayoutAlgorithm>(tipsNode->layoutAlgorithm_->GetLayoutAlgorithm());
    layoutAlgorithm->wrapperRect_ = { 0, 0, DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->wrapperSize_ = { DEVICE_WIDTH, DEVICE_HEIGHT };
    layoutAlgorithm->measureChildSizeAfter_ = ConstructParagraphs(TIPS_MSG_1, 1);

    auto tipsLayoutWrapper = tipsNode->CreateLayoutWrapper();
    auto childWrapper = tipsLayoutWrapper->GetAllChildrenWithBuild().front();
    auto children = childWrapper->GetAllChildrenWithBuild();
    auto text = children.front();
    auto layoutProps = AceType::DynamicCast<TextLayoutProperty>(text->GetLayoutProperty());
    ASSERT_NE(layoutProps, nullptr);
    layoutProps->ResetMaxLines();
    
    /**
     * @tc.steps: step2. expect text node set maxlines.
     */
    LayoutConstraintF childConstraint;
    layoutAlgorithm->MeasureTipsFollowTarget(childWrapper, childConstraint);
    EXPECT_TRUE(layoutProps->HasMaxLines());
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tipsNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = tipsNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto eventHub = targetNode->GetEventHub<EventHub>();

    /**
     * @tc.steps: step2. expect onAreaChangedFunc add.
     */
    EXPECT_TRUE(eventHub->onAreaChangedInnerCallbacks_.count(tipsNode->nodeId_));
    eventHub->onAreaChangedInnerCallbacks_[tipsNode->nodeId_]({}, {}, {}, {});
}

/**
 * @tc.name: PopBubble001
 * @tc.desc: Test PopBubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, PopBubble001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tipsNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = tipsNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    PopupInfo popupInfo;
    popupInfo.isCurrentOnShow = false;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->PopBubble();

    popupInfo.isCurrentOnShow = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    auto layoutProp = tipsNode->GetLayoutProperty<BubbleLayoutProperty>();
    layoutProp->UpdateShowInSubWindow(true);
    layoutProp->UpdateIsTips(true);
    bubblePattern->PopBubble();
    
    layoutProp->UpdateIsTips(false);
    bubblePattern->PopBubble();

    layoutProp->UpdateShowInSubWindow(false);
    layoutProp->UpdateIsTips(true);
    bubblePattern->PopBubble();
    
    layoutProp->UpdateIsTips(false);
    bubblePattern->PopBubble();
    EXPECT_EQ(overlayManager->GetPopupInfo(id).markNeedUpdate, false);
}

/**
 * @tc.name: PopBubble002
 * @tc.desc: Test PopBubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, PopBubble002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create bubble and get frameNode.
     */
    auto targetNode = CreateTargetNode();
    auto id = targetNode->GetId();
    auto targetTag = targetNode->GetTag();
    auto popupId = ElementRegister::GetInstance()->MakeUniqueId();
    auto tipsNode =
        FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, popupId, AceType::MakeRefPtr<BubblePattern>(id, targetTag));
    auto bubblePattern = tipsNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto overlayManager = MockPipelineContext::GetCurrent()->GetOverlayManager();
    PopupInfo popupInfo;
    popupInfo.isCurrentOnShow = true;
    popupInfo.isTips = false;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->PopBubble(true);

    popupInfo.isTips = true;
    overlayManager->UpdatePopupMap(id, popupInfo);
    bubblePattern->PopBubble(true);
    EXPECT_EQ(overlayManager->GetPopupInfo(id).markNeedUpdate, false);
}

/**
 * @tc.name: PopBubble003
 * @tc.desc: Test Bubble Algorithm
 * @tc.type: FUNC
 */
HWTEST_F(BubbleTipsTestNg, PopBubble003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create targetNode and get frameNode.
     */
    auto parm = CreateTipsParamWithArrow();
    ASSERT_NE(parm, nullptr);
    auto frameNode = CreateTipsNodeWithArrow(parm, TIPS_MSG_1);
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: step2. get layout property, layoutAlgorithm and create layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    auto bubblePattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(bubblePattern, nullptr);
    auto bubbleLayoutAlgorithm = AceType::DynamicCast<BubbleLayoutAlgorithm>(bubblePattern->CreateLayoutAlgorithm());
    ASSERT_NE(bubbleLayoutAlgorithm, nullptr);
    bubbleLayoutAlgorithm->childSize_ = SizeF(BUBBLE_WIDTH, BUBBLE_HEIGHT);
    /**
     * @tc.steps: step3. update layoutWrapper and layoutProperty. create bubble child and child's layoutWrapper.
     */
    UpdateLayoutPropWidthArrow(frameNode);
    UpdateConstraintFullScreen(layoutWrapper);
    AddTextNodeToTips(frameNode, layoutWrapper);
    /**
     * @tc.steps: step4. use layoutAlgorithm to measure and layout.
     * @tc.expected: step4. check whether arrow is show.
     */

    auto pipeline = PipelineContext::GetCurrentContext();
    auto designWidthScale = pipeline->designWidthScale_;
    pipeline->designWidthScale_ = 2.0f;
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    OffsetF offset(0.0f, 0.0f);
    bubbleLayoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_FLOAT_EQ(offset.GetY(), 0.0f);
    //  TipsWidth - Radius *2 > ArrowWidth : 200 - 24 * 2 > 60
    EXPECT_EQ(bubbleLayoutAlgorithm->showArrow_, true);

    UpdateConstraintLPScreen(layoutWrapper);
    pipeline->designWidthScale_ = 8.0f;
    bubbleLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    bubbleLayoutAlgorithm->UpdateChildPosition(offset);
    EXPECT_FLOAT_EQ(offset.GetY(), -240.0f);
    //  TipsWidth - Radius *2 < ArrowWidth : 200 - 24 * 2 < 240
    EXPECT_EQ(bubbleLayoutAlgorithm->showArrow_, false);
    pipeline->designWidthScale_ = designWidthScale;
}
} // namespace OHOS::Ace::NG
