/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_font_manager.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "text_base.h"

#include "core/common/font_manager.h"
#include "core/components_ng/pattern/text/span/span_string.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t NODE_ID_START = 2000;
const std::string TEXT_DETECT_TYPES_MT = "phoneNum,url";
} // namespace

class TextPatternMultiThreadTestNg : public TextBases {
public:
    static void SetUpTestSuite()
    {
        TextBases::SetUpTestSuite();
        MockPipelineContext::GetCurrent()->SetUseFlushUITasks(false);
    }

protected:
    RefPtr<TextTheme> PrepareTextTheme()
    {
        auto pipeline = MockPipelineContext::GetCurrent();
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        pipeline->SetThemeManager(themeManager);
        auto textTheme = AceType::MakeRefPtr<TextTheme>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(textTheme));
        EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(textTheme));
        return textTheme;
    }

    std::pair<RefPtr<FrameNode>, RefPtr<TextPattern>> CreateTextPatternNode(bool attachContext, bool isFreeNode)
    {
        auto pattern = AceType::MakeRefPtr<TextPattern>();
        auto frameNode = AceType::MakeRefPtr<FrameNode>(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId() + NODE_ID_START, pattern);
        CHECK_NULL_RETURN(frameNode, std::make_pair(RefPtr<FrameNode>(), RefPtr<TextPattern>()));
        frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
        if (attachContext) {
            auto pipeline = MockPipelineContext::GetCurrent();
            frameNode->AttachContext(AceType::RawPtr(pipeline), true);
        }
        pattern->AttachToFrameNode(frameNode);
        frameNode->SetIsFree(isFreeNode);
        return { frameNode, pattern };
    }

    void ExecutePendingMainTreeTasks(const RefPtr<FrameNode>& frameNode)
    {
        ASSERT_NE(frameNode, nullptr);
        frameNode->MarkNodeNotFree();
    }
};

/**
 * @tc.name: OnAttachToFrameNodeMultiThread001
 * @tc.desc: Test TextPattern::OnAttachToFrameNodeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnAttachToFrameNodeMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToFrameNodeMultiThread();
    SUCCEED();
}

/**
 * @tc.name: OnDetachFromFrameNodeMultiThread001
 * @tc.desc: Test TextPattern::OnDetachFromFrameNodeMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnDetachFromFrameNodeMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromFrameNodeMultiThread(nullptr);
    SUCCEED();
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread001
 * @tc.desc: Test TextPattern::OnAttachToMainTreeMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnAttachToMainTreeMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnAttachToMainTreeMultiThread();
    EXPECT_EQ(pattern->pipeline_.Upgrade(), nullptr);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread002
 * @tc.desc: Test TextPattern::OnAttachToMainTreeMultiThread with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnAttachToMainTreeMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(false, false);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto pipelineBeforeAttach = pattern->pipeline_.Upgrade();
    pattern->OnAttachToMainTreeMultiThread();
    EXPECT_EQ(pattern->pipeline_.Upgrade(), pipelineBeforeAttach);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread003
 * @tc.desc: Test TextPattern::OnAttachToMainTreeMultiThread positive branches.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnAttachToMainTreeMultiThread003, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto textTheme = PrepareTextTheme();
    ASSERT_NE(textTheme, nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, false);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    auto oldApiVersion = MockContainer::Current()->GetApiTargetVersion();
    auto oldMinVersion = pipeline->GetMinPlatformVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    pipeline->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));

    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto hasTextAlignBeforeAttach = layoutProperty->HasTextAlign();
    auto textAlignBeforeAttach = layoutProperty->GetTextAlignValue(TextAlign::START);
    pattern->OnAttachToMainTreeMultiThread();

    EXPECT_EQ(pattern->pipeline_.Upgrade(), pipeline);
    EXPECT_TRUE(layoutProperty->HasTextAlign());
    EXPECT_EQ(layoutProperty->GetTextAlignValue(TextAlign::START),
        hasTextAlignBeforeAttach ? textAlignBeforeAttach : textTheme->GetTextStyle().GetTextAlign());
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignmentValue(), Alignment::CENTER_LEFT);
    EXPECT_FALSE(pattern->isDetachFromMainTree_);
    ASSERT_NE(pipeline->GetFontManager(), nullptr);
    EXPECT_FALSE(pipeline->GetFontManager()->fontNodesNG_.empty());

    MockContainer::Current()->SetApiTargetVersion(oldApiVersion);
    pipeline->SetMinPlatformVersion(oldMinVersion);
}

/**
 * @tc.name: OnAttachToMainTreeMultiThread004
 * @tc.desc: Test TextPattern::OnAttachToMainTreeMultiThread keeps existing property values.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnAttachToMainTreeMultiThread004, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, false);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextAlign(TextAlign::END);
    layoutProperty->UpdateAlignment(Alignment::CENTER);

    pattern->OnAttachToMainTreeMultiThread();

    EXPECT_EQ(layoutProperty->GetTextAlignValue(TextAlign::START), TextAlign::END);
    ASSERT_NE(layoutProperty->GetPositionProperty(), nullptr);
    EXPECT_EQ(layoutProperty->GetPositionProperty()->GetAlignmentValue(), Alignment::CENTER);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread001
 * @tc.desc: Test TextPattern::OnDetachFromMainTreeMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnDetachFromMainTreeMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnDetachFromMainTreeMultiThread();
    EXPECT_FALSE(pattern->isDetachFromMainTree_);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread002
 * @tc.desc: Test TextPattern::OnDetachFromMainTreeMultiThread with null pipeline.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnDetachFromMainTreeMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, false);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->GetDataDetectorAdapter()->aiDetectDelayTask_.Reset([]() {});

    pattern->OnDetachFromMainTreeMultiThread();

    EXPECT_FALSE(static_cast<bool>(pattern->GetDataDetectorAdapter()->aiDetectDelayTask_));
    EXPECT_TRUE(pattern->isDetachFromMainTree_);
}

/**
 * @tc.name: OnDetachFromMainTreeMultiThread003
 * @tc.desc: Test TextPattern::OnDetachFromMainTreeMultiThread positive branches.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, OnDetachFromMainTreeMultiThread003, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, false);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->fontManager_ = AceType::MakeRefPtr<MockFontManager>();
    ASSERT_NE(pipeline->GetFontManager(), nullptr);
    pipeline->GetFontManager()->AddFontNodeNG(frameNode);
    pipeline->GetFontManager()->AddVariationNodeNG(frameNode);
    pattern->pipeline_ = WeakPtr<PipelineContext>(pipeline);
    pattern->GetDataDetectorAdapter()->aiDetectDelayTask_.Reset([]() {});
    pattern->surfaceChangedCallbackId_ = 1;
    pattern->surfacePositionChangedCallbackId_ = 2;

    pattern->OnDetachFromMainTreeMultiThread();

    EXPECT_FALSE(static_cast<bool>(pattern->GetDataDetectorAdapter()->aiDetectDelayTask_));
    EXPECT_TRUE(pattern->isDetachFromMainTree_);
    EXPECT_FALSE(pipeline->GetFontManager()->fontNodesNG_.empty());
    EXPECT_TRUE(pipeline->GetFontManager()->variationNodesNG_.empty());
}

/**
 * @tc.name: SetTextDetectEnableMultiThread001
 * @tc.desc: Test TextPattern::SetTextDetectEnableMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectEnableMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetTextDetectEnableMultiThread(true);
    EXPECT_FALSE(pattern->GetTextDetectEnable());
}

/**
 * @tc.name: SetTextDetectEnableMultiThread002
 * @tc.desc: Test TextPattern::SetTextDetectEnableMultiThread when value is unchanged.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectEnableMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->SetTextDetectEnableMultiThread(false);
    EXPECT_TRUE(frameNode->afterAttachMainTreeTasks_.empty());
    EXPECT_FALSE(pattern->GetTextDetectEnable());
}

/**
 * @tc.name: SetTextDetectEnableMultiThread003
 * @tc.desc: Test TextPattern::SetTextDetectEnableMultiThread enable branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectEnableMultiThread003, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);

    pattern->SetTextDetectEnableMultiThread(true);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(pattern->GetTextDetectEnable());
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->frameNode_.Upgrade(), frameNode);
    EXPECT_EQ(pipeline->configChangedCallback_.count(frameNode->GetId()), 1);
}

/**
 * @tc.name: SetTextDetectEnableMultiThread004
 * @tc.desc: Test TextPattern::SetTextDetectEnableMultiThread disable branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectEnableMultiThread004, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    pattern->textDetectEnable_ = true;
    pattern->GetDataDetectorAdapter()->aiDetectDelayTask_.Reset([]() {});

    pattern->SetTextDetectEnableMultiThread(false);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_FALSE(pattern->GetTextDetectEnable());
    EXPECT_FALSE(static_cast<bool>(pattern->GetDataDetectorAdapter()->aiDetectDelayTask_));
}

/**
 * @tc.name: SetTextDetectConfigMultiThread001
 * @tc.desc: Test TextPattern::SetTextDetectConfigMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectConfigMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = TEXT_DETECT_TYPES_MT;
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetTextDetectConfigMultiThread(textDetectConfig);
    EXPECT_EQ(pattern->dataDetectorAdapter_, nullptr);
}

/**
 * @tc.name: SetTextDetectConfigMultiThread002
 * @tc.desc: Test TextPattern::SetTextDetectConfigMultiThread positive branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextDetectConfigMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    TextDetectConfig textDetectConfig;
    textDetectConfig.types = TEXT_DETECT_TYPES_MT;
    textDetectConfig.entityColor = Color::BLACK;
    textDetectConfig.entityDecorationType = TextDecoration::UNDERLINE;
    textDetectConfig.entityDecorationColor = Color::BLUE;
    textDetectConfig.entityDecorationStyle = TextDecorationStyle::DOUBLE;
    textDetectConfig.enablePreviewMenu = true;
    textDetectConfig.onResult = [](const std::string&) {};

    pattern->SetTextDetectConfigMultiThread(textDetectConfig);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->textDetectTypes_, TEXT_DETECT_TYPES_MT);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->entityColor_, Color::BLACK);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->entityDecorationType_, TextDecoration::UNDERLINE);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->entityDecorationColor_, Color::BLUE);
    EXPECT_EQ(pattern->GetDataDetectorAdapter()->entityDecorationStyle_, TextDecorationStyle::DOUBLE);
    EXPECT_TRUE(pattern->GetDataDetectorAdapter()->enablePreviewMenu_);
    EXPECT_NE(pattern->GetDataDetectorAdapter()->onResult_, nullptr);
}

/**
 * @tc.name: SetStyledStringMultiThread001
 * @tc.desc: Test TextPattern::SetStyledStringMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetStyledStringMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetStyledStringMultiThread(AceType::MakeRefPtr<SpanString>(u"Hello"), false);
    EXPECT_EQ(pattern->styledString_, nullptr);
}

/**
 * @tc.name: SetStyledStringMultiThread002
 * @tc.desc: Test TextPattern::SetStyledStringMultiThread with null value branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetStyledStringMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);

    pattern->SetStyledStringMultiThread(nullptr, false);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(pattern->isSpanStringMode_);
    ASSERT_NE(pattern->styledString_, nullptr);
    EXPECT_TRUE(pattern->spans_.empty());
}

/**
 * @tc.name: SetStyledStringMultiThread003
 * @tc.desc: Test TextPattern::SetStyledStringMultiThread positive branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetStyledStringMultiThread003, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello");
    ASSERT_NE(spanString, nullptr);

    pattern->SetStyledStringMultiThread(spanString, false);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(pattern->isSpanStringMode_);
    ASSERT_NE(pattern->styledString_, nullptr);
    EXPECT_EQ(pattern->textForDisplay_, u"Hello");
    EXPECT_FALSE(pattern->spans_.empty());
}

/**
 * @tc.name: SetExternalSpanItemMultiThread002
 * @tc.desc: Test TextPattern::SetExternalSpanItemMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetExternalSpanItemMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    std::list<RefPtr<SpanItem>> spans;
    pattern->SetExternalSpanItemMultiThread(spans);
    EXPECT_TRUE(pattern->spans_.empty());
}

/**
 * @tc.name: SetExternalSpanItemMultiThread001
 * @tc.desc: Test TextPattern::SetExternalSpanItemMultiThread with empty spans.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetExternalSpanItemMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    std::list<RefPtr<SpanItem>> spans;

    pattern->SetExternalSpanItemMultiThread(spans);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_FALSE(pattern->isSpanStringMode_);
    EXPECT_TRUE(pattern->spans_.empty());
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetContentValue(u""), u"");
}

/**
 * @tc.name: SetExternalSpanItemMultiThread003
 * @tc.desc: Test TextPattern::SetExternalSpanItemMultiThread positive branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetExternalSpanItemMultiThread003, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    std::list<RefPtr<SpanItem>> spans;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->content = u"World";
    spans.emplace_back(spanItem);

    pattern->SetExternalSpanItemMultiThread(spans);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(pattern->isSpanStringMode_);
    ASSERT_NE(pattern->styledString_, nullptr);
    EXPECT_EQ(pattern->textForDisplay_, u"World");
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetContentValue(u""), u"World");
}

/**
 * @tc.name: CloseSelectOverlayMultiThread001
 * @tc.desc: Test TextPattern::CloseSelectOverlayMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, CloseSelectOverlayMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->CloseSelectOverlayMultiThread(true);
    SUCCEED();
}

/**
 * @tc.name: CloseSelectOverlayMultiThread002
 * @tc.desc: Test TextPattern::CloseSelectOverlayMultiThread.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, CloseSelectOverlayMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);

    pattern->CloseSelectOverlayMultiThread(true);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(frameNode->afterAttachMainTreeTasks_.empty());
}

/**
 * @tc.name: SetTextSelectionMultiThread001
 * @tc.desc: Test TextPattern::SetTextSelectionMultiThread with null host.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextSelectionMultiThread001, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetTextSelectionMultiThread(1, 2);
    EXPECT_FALSE(pattern->textSelector_.IsValid());
}

/**
 * @tc.name: SetTextSelectionMultiThread002
 * @tc.desc: Test TextPattern::SetTextSelectionMultiThread positive branch.
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternMultiThreadTestNg, SetTextSelectionMultiThread002, TestSize.Level1)
{
    int32_t breakPoint = __LINE__;
    EXPECT_GT(breakPoint, 0);
    ASSERT_NE(PrepareTextTheme(), nullptr);
    auto [frameNode, pattern] = CreateTextPatternNode(true, true);
    ASSERT_NE(frameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCopyOption(CopyOptions::Local);
    layoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
    frameNode->GetGeometryNode()->SetFrameSize(SizeF(100.0f, 50.0f));
    pattern->textForDisplay_ = u"Hello";

    pattern->SetTextSelectionMultiThread(2, 1);
    ASSERT_EQ(frameNode->afterAttachMainTreeTasks_.size(), 1);
    ExecutePendingMainTreeTasks(frameNode);

    EXPECT_TRUE(frameNode->afterAttachMainTreeTasks_.empty());
    EXPECT_FALSE(pattern->textSelector_.IsValid());
}
} // namespace OHOS::Ace::NG
