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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
const std::string ADDRESS = "天安门";
const std::u16string ADDRESS_U16 = u"天安门";
const std::string SPAN_PHONE = "12345678900";
} // namespace

class RichEditorAITestOneNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorAITestOneNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode_->GetGeometryNode()->SetContentSize({});
}

void RichEditorAITestOneNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorAITestOneNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: IsShowAIWrite001
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    auto mockContainer = MockContainer::Current();
    mockContainer->SetIsSceneBoardWindow(true);
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite002
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    MockContainer::TearDown();
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite003
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite004
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite005
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    theme->aiWriteAbilityName_ = "abilityName";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("bundleName", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_EQ("abilityName", richEditorPattern->aiWriteAdapter_->GetAbilityName());
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsShowAIWrite006
 * @tc.desc: test IsShowAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, IsShowAIWrite006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->copyOption_ = CopyOptions::Local;
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));
    theme->aiWriteBundleName_ = "bundleName";
    theme->aiWriteAbilityName_ = "abilityName";
    theme->aiWriteIsSupport_ = "true";
    auto result = richEditorPattern->IsShowAIWrite();
    EXPECT_EQ("bundleName", richEditorPattern->aiWriteAdapter_->GetBundleName());
    EXPECT_EQ("abilityName", richEditorPattern->aiWriteAdapter_->GetAbilityName());
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, HandleAIWrite001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);

    richEditorPattern->textSelector_.Update(0, 5);
    AIWriteInfo info;
    richEditorPattern->GetAIWriteInfo(info);
    EXPECT_EQ(info.selectStart, 0);
    EXPECT_EQ(info.selectEnd, 5);
    EXPECT_EQ(info.selectLength, 5);
    EXPECT_EQ(info.firstHandle, richEditorPattern->textSelector_.firstHandle.ToString());
    EXPECT_EQ(info.secondHandle, richEditorPattern->textSelector_.secondHandle.ToString());
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(info.selectBuffer);
    ASSERT_NE(spanString, nullptr);
    auto textContent = spanString->GetString();
    EXPECT_EQ(textContent.empty(), false);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test HandleOnAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, HandleAIWrite002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->HandleOnAIWrite();
    auto start = richEditorPattern->operationRecords_.size();

    std::vector<uint8_t> buff;
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"dddd结果回填123456");
    spanStr->EncodeTlv(buff);
    richEditorPattern->HandleAIWriteResult(0, 5, buff);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 3);
}

/**
 * @tc.name: HandleAIWrite001
 * @tc.desc: test AddSpansAndReplacePlaceholder&SetSubSpansWithAIWrite
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, HandleAIWrite003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    /**
     * @tc.steps: step2. add span
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddSymbolSpan(options1);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddImageSpan(options3);
    EXPECT_EQ(static_cast<int32_t>(contentNode->GetChildren().size()), 5);

    /**
     * @tc.steps: step3. replace and recover placeholder for non-text.
     */
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"");
    ASSERT_NE(spanString, nullptr);
    richEditorPattern->SetSubSpansWithAIWrite(spanString, 0, 12);
    auto spanStr = AceType::MakeRefPtr<SpanString>(u"test![id1]占位符![id2]");
    richEditorPattern->textSelector_.Update(0, 10);
    auto start = richEditorPattern->operationRecords_.size();
    richEditorPattern->AddSpansAndReplacePlaceholder(spanStr);
    EXPECT_EQ(richEditorPattern->operationRecords_.size(), start + 4);
}

/**
 * @tc.name: GetAIWriteInfo001
 * @tc.desc: test GetAIWriteInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, GetAIWriteInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, 5);
    richEditorPattern->textForDisplay_ = u"testtesttest";
    AIWriteInfo info;
    richEditorPattern->GetAIWriteInfo(info);
    EXPECT_EQ(info.selectStart, 0);
    EXPECT_EQ(info.selectEnd, 5);
    EXPECT_EQ(info.selectLength, 5);
    EXPECT_EQ(info.firstHandle, richEditorPattern->textSelector_.firstHandle.ToString());
    EXPECT_EQ(info.secondHandle, richEditorPattern->textSelector_.secondHandle.ToString());
    RefPtr<SpanString> spanString = SpanString::DecodeTlv(info.selectBuffer);
    ASSERT_NE(spanString, nullptr);
    auto textContent = spanString->GetString();
    EXPECT_EQ(textContent.empty(), false);
}

/**
 * @tc.name: CanStartAITask001
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, CanStartAITask001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CanStartAITask002
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, CanStartAITask002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    bool ret = true;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CanStartAITask003
 * @tc.desc: test CanStartAITask
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, CanStartAITask003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isShowPlaceholder_ = true;
    bool ret = true;
    ret = richEditorPattern->CanStartAITask();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedShowAIDetect001
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, NeedShowAIDetect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    bool ret = false;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: NeedShowAIDetect002
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, NeedShowAIDetect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isEditing_ = true;
    bool ret = true;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: NeedShowAIDetect003
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, NeedShowAIDetect003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0;
    aiSpanMap[0] = aiSpan0;
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->isShowPlaceholder_ = true;
    bool ret = true;
    ret = richEditorPattern->NeedShowAIDetect();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: InitAiselection001
 * @tc.desc: test NeedShowAIDetect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, InitAiselection, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0 = { .content = ADDRESS, .start = 0, .end = 3 };
    aiSpanMap[0] = aiSpan0;
    TextSpanOptions options = { .value = ADDRESS_U16 };
    richEditorPattern->AddTextSpan(options);
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(mockParagraph, nullptr);
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    PositionWithAffinity positionWithAffinity(1, TextAffinity::UPSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));

    auto pipeline = PipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    ParagraphManager::ParagraphInfo paragraphInfo = { .paragraph = mockParagraph, .start = 0, .end = 10 };
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    Offset offset = { 10, 10 };
    richEditorPattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    richEditorPattern->dataDetectorAdapter_->enablePreviewMenu_ = true;
    richEditorPattern->textDetectEnable_ = true;
    richEditorPattern->InitAiSelection(offset);
    auto textSelector1 = richEditorPattern->GetTextSelector();
    EXPECT_TRUE(textSelector1.aiStart.has_value());
    EXPECT_TRUE(textSelector1.aiEnd.has_value());
    EXPECT_TRUE(textSelector1.aiEnd.value() > textSelector1.aiStart.value());
    richEditorPattern->dataDetectorAdapter_->enablePreviewMenu_ = false;
    richEditorPattern->InitAiSelection(offset);
    auto textSelector2 = richEditorPattern->GetTextSelector();
    EXPECT_FALSE(textSelector2.aiStart.has_value());
    EXPECT_FALSE(textSelector2.aiEnd.has_value());
}

/**
 * @tc.name: InitAiSelection002
 * @tc.desc: test InitAiSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, InitAiSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan0 = { .content = ADDRESS, .start = 0, .end = 3 };
    aiSpanMap[0] = aiSpan0;
    TextSpanOptions options = { .value = ADDRESS_U16 };
    pattern->AddTextSpan(options);
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    PositionWithAffinity positionWithAffinity(1, TextAffinity::DOWNSTREAM);
    EXPECT_CALL(*mockParagraph, GetGlyphPositionAtCoordinate(_)).WillRepeatedly(Return(positionWithAffinity));
    ParagraphManager::ParagraphInfo paragraphInfo = { .paragraph = mockParagraph, .start = 0, .end = 10 };
    pattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    Offset offset = { 10, 10 };
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    pattern->dataDetectorAdapter_->enablePreviewMenu_ = true;
    pattern->textDetectEnable_ = true;

    auto pipeline = PipelineContext::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(themeManager);
    auto theme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(theme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(theme));

    pattern->showSelect_ = false;
    pattern->InitAiSelection(offset, false);
    EXPECT_TRUE(pattern->GetTextSelector().aiStart.has_value());
    EXPECT_TRUE(pattern->GetTextSelector().aiEnd.has_value());

    pattern->showSelect_ = false;
    pattern->InitAiSelection(offset, true);
    EXPECT_TRUE(pattern->GetTextSelector().aiStart.has_value());
    EXPECT_TRUE(pattern->GetTextSelector().aiEnd.has_value());

    pattern->showSelect_ = true;
    pattern->InitAiSelection(offset, false);
    EXPECT_TRUE(pattern->GetTextSelector().aiStart.has_value());
    EXPECT_TRUE(pattern->GetTextSelector().aiEnd.has_value());

    pattern->showSelect_ = true;
    pattern->InitAiSelection(offset, true);
    EXPECT_FALSE(pattern->GetTextSelector().aiStart.has_value());
    EXPECT_FALSE(pattern->GetTextSelector().aiEnd.has_value());
}

/**
 * @tc.name: UpdateAIStyle
 * @tc.desc: test UpdateAIStyle.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, UpdateAIStyle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto& spans = richEditorPattern->spans_;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->aiSpanResultCount = 0;
    spans.push_back(spanItem);

    TextDetectConfig textDetectConfig;

    textDetectConfig.entityColor = TEXT_COLOR_VALUE;
    textDetectConfig.entityDecorationType = TextDecoration::OVERLINE;
    textDetectConfig.entityDecorationColor = Color::BLACK;
    textDetectConfig.entityDecorationStyle = TextDecorationStyle ::DOUBLE;
    richEditorPattern->SetTextDetectConfig(textDetectConfig);
    EXPECT_FALSE(spanItem->needReLayout);

    spanItem->aiSpanResultCount = 1;
    textDetectConfig.entityDecorationColor = Color::BLUE;
    richEditorPattern->SetTextDetectConfig(textDetectConfig);
    EXPECT_TRUE(spanItem->needReLayout);
}

/**
 * @tc.name: CreateAIEntityMenuTest
 * @tc.desc: Test CreateAIEntityMenu set preview menu nodes correctly
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, CreateAIEntityMenuTest, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step1. set invalid value
     */
    auto menuNode = pattern->CreateAIEntityMenu();
    EXPECT_EQ(menuNode, nullptr);

    pattern->textSelector_.aiStart = 0;
    pattern->textSelector_.aiEnd = 5;
    menuNode = pattern->CreateAIEntityMenu();
    EXPECT_EQ(menuNode, nullptr);

    /**
     * @tc.steps: step2. set aiSpanMap
     */
    std::map<int32_t, AISpan> aiSpanMap;
    AISpan aiSpan1;
    aiSpan1.start = 0;
    aiSpan1.end = 5;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    aiSpanMap[0] = aiSpan1;
    pattern->dataDetectorAdapter_->aiSpanMap_ = aiSpanMap;
    menuNode = pattern->CreateAIEntityMenu();
    EXPECT_EQ(menuNode, 0);
}

/**
 * @tc.name: NeedAiAnalysis001
 * @tc.desc: test NeedAiAnalysis
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorAITestOneNg, NeedAiAnalysis001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init and call function.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_EQ(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
    /**
     * @tc.steps: step2. change parameter and call function.
     */
    std::string content = "";
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"");
    CaretUpdateType targeType1 = CaretUpdateType::PRESSED;
    int32_t pos = 0;
    int32_t spanStart = 10;
    auto ret = richEditorPattern->NeedAiAnalysis(targeType1, pos, spanStart, content);
    EXPECT_FALSE(ret);
    /**
     * @tc.steps: step3. change parameter and call function.
     */
    CaretUpdateType targeType2 = CaretUpdateType::DOUBLE_CLICK;
    ret = richEditorPattern->NeedAiAnalysis(targeType2, pos, spanStart, content);
    EXPECT_FALSE(ret);
}

}