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
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_url_analyzer_mgr.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string URL_ADDRESS_1 = u"https://www.baidu.com";
const std::u16string URL_ADDRESS_2 = u"https://www.12345.com";
RichEditorChangeValue onWillChangeValue;
auto& onWillReplacedSpans = onWillChangeValue.replacedSpans_;
}

class RichEditorUrlStyleTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    RefPtr<SpanNode> GetSpanNodeAtIndex(int32_t index);
    RefPtr<SpanItem> GetSpanItemAtIndex(int32_t index);
    void ResetContentChangeCallbackState();
    void InitContentChangeCallback();
    void InitDataUrlAnalyzer(MockDataUrlAnalyzerMgr& mockDataUrlAnalyzerMgr);
    static void TearDownTestSuite();
};

void RichEditorUrlStyleTest::InitDataUrlAnalyzer(MockDataUrlAnalyzerMgr& mockDataUrlAnalyzerMgr)
{
    EXPECT_CALL(mockDataUrlAnalyzerMgr, AnalyzeUrls(_))
        .WillRepeatedly([](const std::string& text) -> std::vector<UrlEntity> {
            std::vector<UrlEntity> data;
            if (text.empty()) {
                return data;
            }
            UrlEntity urlEntity;
            urlEntity.text = text;
            urlEntity.charOffset = text.length();
            data.push_back(urlEntity);
            return data;
        });
}

void RichEditorUrlStyleTest::SetUp()
{
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

void RichEditorUrlStyleTest::TearDown()
{
    richEditorNode_ = nullptr;
}

void RichEditorUrlStyleTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

RefPtr<SpanNode> RichEditorUrlStyleTest::GetSpanNodeAtIndex(int32_t index)
{
    CHECK_NULL_RETURN(richEditorNode_, {});
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    return AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(index));
}

RefPtr<SpanItem> RichEditorUrlStyleTest::GetSpanItemAtIndex(int32_t index)
{
    auto spanNode = GetSpanNodeAtIndex(index);
    CHECK_NULL_RETURN(spanNode, {});
    return spanNode->GetSpanItem();
}

void RichEditorUrlStyleTest::ResetContentChangeCallbackState()
{
    onWillChangeValue.reset();
}

void RichEditorUrlStyleTest::InitContentChangeCallback()
{
    ResetContentChangeCallbackState();
    auto onWillChange = [](const RichEditorChangeValue& changeValue) {
        onWillChangeValue = changeValue;
        return true;
    };
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetOnWillChange(std::move(onWillChange));
}

/**
 * @tc.name: RichEditorUrlStyleAddTest001
 * @tc.desc: test add single span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = TEXT_STYLE_1;
    richEditorController->AddTextSpan(options);
    ASSERT_EQ(spans.size(), 1);
    auto spanItem = GetSpanItemAtIndex(0);
    EXPECT_EQ(spanItem->urlAddress, std::nullopt);
    EXPECT_EQ(spanItem->urlOnRelease, nullptr);
}

/**
 * @tc.name: RichEditorUrlStyleAddTest002
 * @tc.desc: test add single span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = TEXT_STYLE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorController->AddTextSpan(options);

    ASSERT_EQ(spans.size(), 1);
    auto spanItem = GetSpanItemAtIndex(0);
    ASSERT_NE(spanItem, nullptr);
    EXPECT_EQ(spanItem->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem->urlOnRelease, nullptr);

    options.urlAddress = URL_ADDRESS_2;
    richEditorController->AddTextSpan(options);

    ASSERT_EQ(spans.size(), 2);
    auto spanItem1 = GetSpanItemAtIndex(1);
    ASSERT_NE(spanItem1, nullptr);
    EXPECT_EQ(spanItem1->urlAddress, URL_ADDRESS_2);
    EXPECT_NE(spanItem1->urlOnRelease, nullptr);
}

/**
 * @tc.name: RichEditorUrlStyleAddTest003
 * @tc.desc: test add single span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    
    TextSpanOptions options;
    options.value = INIT_VALUE_1 + u"\n" + INIT_VALUE_2 + u"\n" + INIT_VALUE_3;
    options.style = TEXT_STYLE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorController->AddTextSpan(options);
    ASSERT_EQ(spans.size(), 3);
    auto spanItem1 = GetSpanItemAtIndex(0);
    ASSERT_NE(spanItem1, nullptr);
    EXPECT_EQ(spanItem1->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem1->urlOnRelease, nullptr);

    auto spanItem2 = GetSpanItemAtIndex(1);
    ASSERT_NE(spanItem2, nullptr);
    EXPECT_EQ(spanItem2->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem2->urlOnRelease, nullptr);

    auto spanItem3 = GetSpanItemAtIndex(2);
    ASSERT_NE(spanItem3, nullptr);
    EXPECT_EQ(spanItem3->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem3->urlOnRelease, nullptr);
}

/**
 * @tc.name: RichEditorUrlStyleAddTest004
 * @tc.desc: test add single span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = TEXT_STYLE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorController->AddTextSpan(options);
    ASSERT_EQ(spans.size(), 1);

    options.offset = 1;
    options.urlAddress = URL_ADDRESS_2;
    richEditorController->AddTextSpan(options);
    ASSERT_EQ(spans.size(), 3);
    auto spanItem1 = GetSpanItemAtIndex(0);
    ASSERT_NE(spanItem1, nullptr);
    EXPECT_EQ(spanItem1->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem1->urlOnRelease, nullptr);

    auto spanItem2 = GetSpanItemAtIndex(1);
    ASSERT_NE(spanItem2, nullptr);
    EXPECT_EQ(spanItem2->urlAddress, URL_ADDRESS_2);
    EXPECT_NE(spanItem2->urlOnRelease, nullptr);

    auto spanItem3 = GetSpanItemAtIndex(2);
    ASSERT_NE(spanItem3, nullptr);
    EXPECT_EQ(spanItem3->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem3->urlOnRelease, nullptr);
}

/**
 * @tc.name: RichEditorUrlStyleUpdateTest001
 * @tc.desc: test add single span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleUpdateTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = TEXT_STYLE_1;
    richEditorController->AddTextSpan(options);
    ASSERT_EQ(spans.size(), 1);
    auto spanItem1 = GetSpanItemAtIndex(0);
    EXPECT_EQ(spanItem1->urlAddress, std::nullopt);
    EXPECT_EQ(spanItem1->urlOnRelease, nullptr);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    updateSpanStyle.updateUrlAddress = URL_ADDRESS_1;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(0, static_cast<int32_t>(INIT_VALUE_1.length()), textStyle, imageStyle);
    EXPECT_EQ(spanItem1->urlAddress, URL_ADDRESS_1);
    EXPECT_NE(spanItem1->urlOnRelease, nullptr);

    updateSpanStyle.updateUrlAddress = u"";
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(0, static_cast<int32_t>(INIT_VALUE_1.length()), textStyle, imageStyle);
    EXPECT_EQ(spanItem1->urlAddress, u"");
    EXPECT_EQ(spanItem1->urlOnRelease, nullptr);
}


/**
 * @tc.name: RichEditorUrlStyleOnWillChangeTest001
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback();
    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = TEXT_STYLE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    auto& spanResult = onWillReplacedSpans[0];
    EXPECT_EQ(spanResult.GetValue(), INIT_VALUE_1);
    EXPECT_EQ(spanResult.GetUrlAddress(), URL_ADDRESS_1);

    richEditorPattern->InsertValue(INIT_VALUE_1);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    auto allString = INIT_VALUE_1 + INIT_VALUE_1;
    EXPECT_EQ(spanResult.GetValue(), allString);
    EXPECT_EQ(spanResult.GetUrlAddress(), URL_ADDRESS_1);
}

/**
 * @tc.name: RichEditorUrlStyleOnWillChangeTest002
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback();
    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1 + u"\n" + INIT_VALUE_2 + u"\n" + INIT_VALUE_3;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);

    ASSERT_EQ(onWillReplacedSpans.size(), 3);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), URL_ADDRESS_1);
    EXPECT_EQ(onWillReplacedSpans[1].GetUrlAddress(), URL_ADDRESS_1);
    EXPECT_EQ(onWillReplacedSpans[2].GetUrlAddress(), URL_ADDRESS_1);
}

/**
 * @tc.name: RichEditorUrlStyleOnWillChangeTest003
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    auto strWithNewline = INIT_VALUE_1 + u"\n" + INIT_VALUE_2 + u"\n" + INIT_VALUE_3;

    InitContentChangeCallback();
    richEditorPattern->isEditing_ = true;
    richEditorPattern->InsertValue(strWithNewline, true);

    ASSERT_EQ(onWillReplacedSpans.size(), 3);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), URL_ADDRESS_1);
    EXPECT_EQ(onWillReplacedSpans[1].GetUrlAddress(), URL_ADDRESS_1);
    EXPECT_EQ(onWillReplacedSpans[2].GetUrlAddress(), URL_ADDRESS_1);
}

/**
 * @tc.name: RichEditorUrlStyleOnWillTestReplace001
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->textSelector_.Update(0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));

    InitContentChangeCallback();
    richEditorPattern->InsertValue(INIT_VALUE_1);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), u"");
}

/**
 * @tc.name: RichEditorUrlStyleOnWillTestReplace002
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1, .urlAddress = URL_ADDRESS_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    int32_t start = static_cast<int32_t>(INIT_VALUE_1.length());
    int32_t end = start + static_cast<int32_t>(INIT_VALUE_1.length());
    richEditorPattern->textSelector_.Update(start, end);

    InitContentChangeCallback();
    richEditorPattern->InsertValue(INIT_VALUE_1);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), u"");
}

/**
 * @tc.name: RichEditorUrlStyleOnWillTestReplace003
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1, .urlAddress = URL_ADDRESS_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    int32_t start = static_cast<int32_t>(INIT_VALUE_1.length());
    int32_t end = start + static_cast<int32_t>(INIT_VALUE_1.length());
    richEditorPattern->textSelector_.Update(start - 1, end - 1);

    InitContentChangeCallback();
    richEditorPattern->InsertValue(INIT_VALUE_1);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), u"");
}

/**
 * @tc.name: RichEditorUrlStyleOnWillTestReplace004
 * @tc.desc: test for callback onWillchange
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1, .urlAddress = URL_ADDRESS_1 });
    richEditorPattern->AddTextSpan({ .value = INIT_VALUE_1 });
    int32_t start = static_cast<int32_t>(INIT_VALUE_1.length());
    int32_t end = start + static_cast<int32_t>(INIT_VALUE_1.length());
    richEditorPattern->textSelector_.Update(start + 1, end + 1);

    InitContentChangeCallback();
    richEditorPattern->InsertValue(INIT_VALUE_1);
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    EXPECT_EQ(onWillReplacedSpans[0].GetUrlAddress(), URL_ADDRESS_1);
}

/**
 * @tc.name: RichEditorUrlStyleIMEInputTest001
 * @tc.desc: test for callback IMEInput
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleIMEInputTest001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::u16string urlAddress = u"unCalled";
    auto func = [&urlAddress](const RichEditorAbstractSpanResult& info) { urlAddress = info.GetUrlAddress(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    richEditorPattern->isEditing_ = true;

    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    EXPECT_EQ(urlAddress, u"");

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    EXPECT_EQ(urlAddress, URL_ADDRESS_1);

    eventHub->SetOnIMEInputComplete(nullptr);
}

/**
 * @tc.name: RichEditorUrlStyleAboutToDeleteTest001
 * @tc.desc: test for callback AboutToDelete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAboutToDeleteTest001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::vector<RichEditorAbstractSpanResult> spanResults;
    auto func = [&spanResults](const RichEditorDeleteValue& deleteValue) {
        auto& spanResultList = deleteValue.GetRichEditorDeleteSpans();
        spanResults = std::vector<RichEditorAbstractSpanResult>(spanResultList.begin(), spanResultList.end());
        return true;
    };
    eventHub->SetAboutToDelete(std::move(func));

    richEditorPattern->InsertValue(INIT_VALUE_1);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(spanResults.size(), 1);
    EXPECT_EQ(spanResults[0].GetUrlAddress(), u"");

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(spanResults.size(), 1);
    EXPECT_EQ(spanResults[0].GetUrlAddress(), URL_ADDRESS_1);
}

/**
 * @tc.name: RichEditorUrlStyleGetSpansTest001
 * @tc.desc: test for GetSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleGetSpansTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_2;
    richEditorPattern->AddTextSpan(options);

    SelectionInfo info = richEditorController->GetSpansInfo(-1, -1);
    std::list<ResultObject>& rets = info.selection_.resultObjects;
    std::vector<ResultObject> retVec(rets.begin(), rets.end());

    ASSERT_EQ(retVec.size(), 3);
    EXPECT_EQ(retVec[0].urlAddress, u"");
    EXPECT_EQ(retVec[1].urlAddress, URL_ADDRESS_1);
    EXPECT_EQ(retVec[2].urlAddress, URL_ADDRESS_2);
}

/**
 * @tc.name: RichEditorUrlStyleGetSelectionTest001
 * @tc.desc: test for GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleGetSelectionTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_2;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->UpdateSelector(0, static_cast<int32_t>(richEditorPattern->GetTextContentLength()));

    SelectionInfo info = richEditorController->GetSelectionSpansInfo();
    std::list<ResultObject>& rets = info.selection_.resultObjects;
    std::vector<ResultObject> retVec(rets.begin(), rets.end());

    ASSERT_EQ(retVec.size(), 3);
    EXPECT_EQ(retVec[0].urlAddress, u"");
    EXPECT_EQ(retVec[1].urlAddress, URL_ADDRESS_1);
    EXPECT_EQ(retVec[2].urlAddress, URL_ADDRESS_2);
}

/**
 * @tc.name: RichEditorUrlStyleOnSelectTest001
 * @tc.desc: test for OnSelect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnSelectTest001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    RichEditorCommonTestNg::ClearSpan();
    std::vector<ResultObject> spanResults;

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto func = [&spanResults](const BaseEventInfo* info) {
        const SelectionInfo* eventInfo = TypeInfoHelper::DynamicCast<SelectionInfo>(info);
        ASSERT_NE(eventInfo, nullptr);
        auto& spanResultList = eventInfo->selection_.resultObjects;
        spanResults = std::vector<ResultObject>(spanResultList.begin(), spanResultList.end());
    };
    eventHub->SetOnSelect(std::move(func));

    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_1;
    richEditorPattern->AddTextSpan(options);
    options.urlAddress = URL_ADDRESS_2;
    richEditorPattern->AddTextSpan(options);
    richEditorPattern->HandleOnSelectAll();

    ASSERT_EQ(spanResults.size(), 3);
    EXPECT_EQ(spanResults[0].urlAddress, u"");
    EXPECT_EQ(spanResults[1].urlAddress, URL_ADDRESS_1);
    EXPECT_EQ(spanResults[2].urlAddress, URL_ADDRESS_2);
}

/**
 * @tc.name: GetUrlSpanColor001
 * @tc.desc: Test get color in urlSpan theme.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanColor001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 1: Get richEditorTheme
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<RichEditorTheme>()));

    // 2: Backup old richEditorTheme and set new richEditorTheme
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;

    // 3: Test whether richEditor pattern->GetUrlHoverColor() and theme-GetUrlHoverColor() are the same color
    RichEditorTheme richEditorTheme;
    EXPECT_EQ(richEditorPattern->GetUrlHoverColor(), richEditorTheme.GetUrlHoverColor());

    // 4: Test whether richEditor pattern->GetUrlPressColor() and theme-GetUrlPressColor() are the same color
    EXPECT_EQ(richEditorPattern->GetUrlPressColor(), richEditorTheme.GetUrlPressColor());

    // 5: Restore old richEditorTheme
    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: GetUrlSpanShowShadow001
 * @tc.desc: Test set urlSpan showShadow
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanShowShadow001, TestSize.Level1)
{
    // 0: Get richEditor Node and richEditor Pattern
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 1: Mock location
    Offset localLocation = Offset(54.0, 20.0);
    Offset globalLocation = Offset(54.0, 20.0);

    // 2: Mock contentRect position and width and height
    richEditorPattern->contentRect_.x_ = 25.0f;
    richEditorPattern->contentRect_.y_ = 13.0f;
    richEditorPattern->contentRect_.width_ = 526.0f;
    richEditorPattern->contentRect_.height_ = 56.0f;

    // 3: Create urlSpan with hyperlink address
    std::string address = "https://www.example.com";
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>(address);

    // 4: Create spanItem and set to spans list
    auto spanItem = AceType::MakeRefPtr<NG::SpanItem>();
    urlSpan->ApplyToSpanItem(spanItem, SpanOperation::ADD);
    spanItem->position = 2;
    std::list<RefPtr<NG::SpanItem>> spans;
    spans.push_back(spanItem);

    // 5: Create ParagraphManager and set to richEditorPattern
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pManager, nullptr);
    richEditorPattern->pManager_ = pManager;

    // 6: Create MutableSpanString and set to richEditorPattern
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"click here");
    spanString->AddSpan(AceType::MakeRefPtr<UrlSpan>(address, 0, 10));
    richEditorPattern->SetStyledString(spanString);

    // 7: Create TextOverlayModifier and set to richEditorPattern
    richEditorPattern->overlayMod_ = AceType::MakeRefPtr<TextOverlayModifier>();

    // 8: Create Paragraph and set to richEditorPattern
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });

    // 9: spans list set to richEditorPattern
    richEditorPattern->spans_ = spans;

    // 10: call HandleUrlSpanShowShadow method
    bool show = richEditorPattern->HandleUrlSpanShowShadow(localLocation, globalLocation, Color(Color::BLUE));

    EXPECT_FALSE(show);
}

/*
 * @tc.name: AnalyzeUrls001
 * @tc.desc: test url Analyzer
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, AnalyzeUrls001, TestSize.Level1)
{
    MockDataUrlAnalyzerMgr mockDataUrlAnalyzerMgr;
    InitDataUrlAnalyzer(mockDataUrlAnalyzerMgr);

    std::string text = "";
    std::vector<UrlEntity> data = mockDataUrlAnalyzerMgr.AnalyzeUrls(text);
    EXPECT_TRUE(data.empty());

    text = "test1";
    data = mockDataUrlAnalyzerMgr.AnalyzeUrls(text);
    EXPECT_FALSE(data.empty());
}

/**
 * @tc.name: GetUrlSpanString001
 * @tc.desc: Test basic function of UrlSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanString001, TestSize.Level1)
{
    // 0: Create MutableSpanString
    auto spanString = AceType::MakeRefPtr<MutableSpanString>(u"0123456789");

    // 1: Create UrlSpan and add to spanString
    std::string address = "https://www.example.com";
    spanString->AddSpan(AceType::MakeRefPtr<UrlSpan>(address, 8, 10));

    // 2: Test subSpanString and spanString is equal
    auto subSpanString  = spanString->GetSubSpanString(0, 10);
    EXPECT_TRUE(subSpanString->IsEqualToSpanString(spanString));

    // 3: Test get urlspan first position size
    auto firstSpans = spanString->GetSpans(8, 1);
    EXPECT_EQ(firstSpans.size(), 1);

    // 4: Test get urlSpan start and end position, and url address
    auto urlSpan = AceType::DynamicCast<UrlSpan>(firstSpans[0]);
    ASSERT_NE(urlSpan, nullptr);
    EXPECT_EQ(urlSpan->GetStartIndex(), 8);
    EXPECT_EQ(urlSpan->GetEndIndex(), 9);
    EXPECT_EQ(urlSpan->GetUrlSpanAddress(), address);
}

}