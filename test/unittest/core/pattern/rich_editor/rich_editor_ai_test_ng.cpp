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

}