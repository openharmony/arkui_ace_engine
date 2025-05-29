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
#include "base/utils/system_properties.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_layout_algorithm.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
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
constexpr Dimension TIPS_MARGIN_SPACE = 8.0_vp;
constexpr Dimension MOUSE_WIDTH = 16.0_vp;
constexpr Dimension MOUSE_HEIGHT = 24.0_vp;
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
    SizeF ConstructParagraphs(const std::u16string& text, int32_t lineCount);
    RefPtr<BubbleLayoutAlgorithm> MeasureTipsRegion(const std::u16string& text, const Offset& mouseOffset);
    static LayoutConstraintF childLayoutConstraint;
    RefPtr<ParagraphManager> pManager = AceType::MakeRefPtr<ParagraphManager>();
};

LayoutConstraintF BubbleTipsTestNg::childLayoutConstraint;

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
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == TextTheme::TypeId()) {
            return AceType::MakeRefPtr<TextTheme>();
        } else if (type == HyperlinkTheme::TypeId()) {
            return AceType::MakeRefPtr<HyperlinkTheme>();
        } else if (type == ButtonTheme::TypeId()) {
            return AceType::MakeRefPtr<ButtonTheme>();
        } else {
            return AceType::MakeRefPtr<PopupTheme>();
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

SizeF BubbleTipsTestNg::ConstructParagraphs(const std::u16string& text, int32_t lineCount)
{
    pManager->SetParagraphs({});
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth())
        .WillRepeatedly(Return(std::min(text.length() * TEXT_WIDTH + TEXT_PADDING + TEXT_PADDING, MAX_SIZE.Width())));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(lineCount));
    EXPECT_CALL(*paragraph, GetHeight())
        .WillRepeatedly(Return(std::min(lineCount * LINE_HEIGHT + TEXT_PADDING + TEXT_PADDING,
            DEVICE_HEIGHT - TOP_INSET - BOTTOM_INSET - static_cast<float>(TIPS_MARGIN_SPACE.ConvertToPx()) * 2)));
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly(Return());
    EXPECT_CALL(*paragraph, AddText(_)).WillRepeatedly(Return());
    pManager->AddParagraph({ .paragraph = paragraph, .start = 0, .end = text.length() });
    return { paragraph->GetMaxWidth(), paragraph->GetHeight() };
}

RefPtr<BubbleLayoutAlgorithm> BubbleTipsTestNg::MeasureTipsRegion(const std::u16string& text, const Offset& mouseOffset)
{
    auto singleTextCount =
        (int32_t)((MAX_SIZE.Width() - TEXT_PADDING - TEXT_PADDING) / TEXT_WIDTH);
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
} // namespace OHOS::Ace::NG
