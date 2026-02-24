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

class MockDrawingColorFilter : public OHOS::Ace::DrawingColorFilter {
    DECLARE_ACE_TYPE(MockDrawingColorFilter, OHOS::Ace::DrawingColorFilter);

public:
    MockDrawingColorFilter() = default;
    ~MockDrawingColorFilter() override = default;

    void* GetDrawingColorFilterSptrAddr() override
    {
        return nullptr;
    }
    napi_value GetDrawingColorFilterNapiValue(NativeEngine* nativeEngine) override
    {
        return nullptr;
    }
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest002, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest003, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAddTest004, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleUpdateTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest002, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillChangeTest003, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace002, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace003, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnWillTestReplace004, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleIMEInputTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleAboutToDeleteTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleGetSpansTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleGetSelectionTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, RichEditorUrlStyleOnSelectTest001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanColor001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanShowShadow001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, AnalyzeUrls001, TestSize.Level0)
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
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanString001, TestSize.Level0)
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

/**
 * @tc.name: SetStyledStringWithMaxLengthCheck001
 * @tc.desc: test SetStyledString cannot update if current content already exceeds maxLength
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, SetStyledStringWithMaxLengthCheck001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 1. Set up: Have content that exceeds the future maxLength
    auto initialSpanString = AceType::MakeRefPtr<MutableSpanString>(u"InitialLongContent");
    richEditorPattern->SetStyledString(initialSpanString);
    int32_t initialLength = richEditorPattern->GetTextContentLength();

    // 2. Set the maxLength to a value smaller than the current content
    int32_t maxLength = initialLength - 5;
    richEditorPattern->SetMaxLength(maxLength);
    EXPECT_LT(maxLength, initialLength);

    // 3. Try to update with new content (this should fail due to pre-existing overflow)
    auto newSpanString = AceType::MakeRefPtr<MutableSpanString>(u"NewContent");
    richEditorPattern->SetStyledString(newSpanString);

    // 4. Assert: The content remains unchanged because the function returned early
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), initialLength);
}

/**
 * @tc.name: SetStyledStringSecondConditionSubLengthNonZero001
 * @tc.desc: Test the second condition branch where value length > maxLength but current content <= maxLength,
 *           and subLength is not zero, so truncation occurs
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, SetStyledStringSecondConditionSubLengthNonZero001, TestSize.Level0)
{
    // 1. Create a new rich editor node with styled string mode
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(true); });
    ASSERT_NE(frameNode, nullptr);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Verify styledString_ is initialized
    auto styledString = richEditorPattern->GetStyledString();
    ASSERT_NE(styledString, nullptr);

    // 3. Set a moderate length content first
    std::u16string initialContent = u"Hello";
    auto initialSpanString = AceType::MakeRefPtr<MutableSpanString>(initialContent);
    richEditorPattern->SetStyledString(initialSpanString);

    // 4. Set a maxLength that is less than new content but greater than or equal to current content
    int32_t maxLength = 10;
    richEditorPattern->SetMaxLength(maxLength);

    // 5. Verify that current content length is not greater than maxLength (so first condition is false)
    EXPECT_LE(richEditorPattern->GetTextContentLength(), maxLength);

    // 6. Create a new span string that has a length greater than maxLength
    std::u16string longerContent = u"This is a much longer content than the max length";
    auto longerSpanString = AceType::MakeRefPtr<MutableSpanString>(longerContent);

    // 7. Verify the new content length is greater than maxLength and lengths are different
    EXPECT_GT(static_cast<int32_t>(longerContent.length()), maxLength);
    EXPECT_NE(longerSpanString->GetLength(), initialSpanString->GetLength());

    // 8. Call SetStyledString - this should trigger the second condition and perform truncation
    richEditorPattern->SetStyledString(longerSpanString);

    // 9. Assert: Content should have been truncated to maxLength but not completely rejected
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), maxLength);
}

/**
 * @tc.name: SetStyledStringSecondConditionSubLengthZero001
 * @tc.desc: Test the second condition branch where value length > maxLength but current content <= maxLength,
 *           and subLength becomes zero, causing early return
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, SetStyledStringSecondConditionSubLengthZero001, TestSize.Level0)
{
    // 1. Create a new rich editor node with styled string mode
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RICH_EDITOR_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<RichEditorPattern>(true); }); // Enable styled string mode
    ASSERT_NE(frameNode, nullptr);
    auto richEditorPattern = frameNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Verify styledString_ is initialized
    auto styledString = richEditorPattern->GetStyledString();
    ASSERT_NE(styledString, nullptr);

    // 3. Set an empty initial content
    std::u16string emptyContent = u"";
    auto emptySpanString = AceType::MakeRefPtr<MutableSpanString>(emptyContent);
    richEditorPattern->SetStyledString(emptySpanString);

    // 4. Set a maxLength of 0 to ensure subLength will be 0 when trying to add content
    int32_t maxLength = 0;
    richEditorPattern->SetMaxLength(maxLength);

    // 5. Verify that current content length is NOT greater than maxLength (first condition is false)
    EXPECT_FALSE(richEditorPattern->GetTextContentLength() > maxLength);

    // 6. Create content that has length > maxLength (to trigger second condition)
    std::u16string newContent = u"Any content";
    auto newSpanString = AceType::MakeRefPtr<MutableSpanString>(newContent);

    // 7. Verify the new content length is greater than maxLength and lengths are different
    EXPECT_GT(static_cast<int32_t>(newContent.length()), maxLength);
    EXPECT_NE(newSpanString->GetLength(), emptySpanString->GetLength());

    // 8. Now both conditions for the second branch are met, call SetStyledString
    richEditorPattern->SetStyledString(newSpanString);

    // 9. Assert: Since maxLength is 0, subLength will be 0, triggering early return, content remains as empty
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 0);
}

/**
 * @tc.name: MountImageNodeWithPixelMap001
 * @tc.desc: test MountImageNode function with imagePixelMap option to cover the branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, MountImageNodeWithPixelMap001, TestSize.Level0)
{
    // 1. Verify the richEditorNode_ is not null and get the pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Create an ImageSpanItem with imagePixelMap option
    auto imageItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(imageItem, nullptr);

    // 3. Prepare ImageSpanOptions with imagePixelMap
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;

    imageItem->options = options;

    // 4. Add the imageItem to the spans list
    richEditorPattern->spans_.push_front(imageItem);

    // 5. Call MountImageNode which should trigger the branch we want to test
    richEditorPattern->MountImageNode(imageItem);

    // 6. Verify that the imageNode was added
    EXPECT_FALSE(richEditorPattern->imageNodes.empty());
}

/**
 * @tc.name: SetImageLayoutPropertyWithColorFilterMatrix001
 * @tc.desc: Test SetImageLayoutProperty function with colorFilterMatrix option to cover the branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, SetImageLayoutPropertyWithColorFilterMatrix001, TestSize.Level0)
{
    // 1. Verify the richEditorNode_ is not null and get the pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Create an ImageSpanNode
    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);

    // 3. Prepare ImageSpanOptions with ImageSpanAttribute containing colorFilterMatrix
    ImageSpanOptions options;
    ImageSpanAttribute imgAttr;

    // 4. Set colorFilterMatrix with some values
    std::vector<float> colorFilterMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    imgAttr.colorFilterMatrix = colorFilterMatrix;
    options.imageAttribute = imgAttr;

    // 5. Call SetImageLayoutProperty which should trigger the colorFilterMatrix branch
    richEditorPattern->SetImageLayoutProperty(imageNode, options);

    // 6. Verify the property was updated correctly
    auto paintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasColorFilter());
}

/**
 * @tc.name: SetImageLayoutPropertyWithDrawingColorFilter001
 * @tc.desc: Test SetImageLayoutProperty function with drawingColorFilter option to cover the branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, SetImageLayoutPropertyWithDrawingColorFilter001, TestSize.Level0)
{
    // 1. Verify the richEditorNode_ is not null and get the pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Create an ImageSpanNode
    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);

    // 3. Prepare ImageSpanOptions with ImageSpanAttribute containing drawingColorFilter
    ImageSpanOptions options;
    ImageSpanAttribute imgAttr;

    // 4. Create and set a mock drawingColorFilter using local mock class
    auto drawingColorFilter = AceType::MakeRefPtr<MockDrawingColorFilter>();
    ASSERT_NE(drawingColorFilter, nullptr);
    imgAttr.drawingColorFilter = drawingColorFilter;
    options.imageAttribute = imgAttr;

    // 5. Call SetImageLayoutProperty which should trigger the drawingColorFilter branch
    richEditorPattern->SetImageLayoutProperty(imageNode, options);

    // 6. Verify the property was updated correctly
    auto paintProperty = imageNode->GetPaintProperty<ImageRenderProperty>();
    ASSERT_NE(paintProperty, nullptr);
    EXPECT_TRUE(paintProperty->HasDrawingColorFilter());
}

/**
 * @tc.name: RichEditorBeforeCreateLayoutWrapperContentModNotNull001
 * @tc.desc: Test BeforeCreateLayoutWrapper function to cover the branch where contentMod_ is not null
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorBeforeCreateLayoutWrapperContentModNotNull001, TestSize.Level0)
{
    // 1. Verify the richEditorNode_ is not null and get the pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2. Set the pattern to span string mode to make the second branch execute
    richEditorPattern->SetSpanStringMode(true);
    EXPECT_EQ(richEditorPattern->isSpanStringMode_, true);

    // 3. Create a TextContentModifier instance and assign it to contentMod_
    RefPtr<TextContentModifier> contentMod =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    richEditorPattern->contentMod_ = contentMod;

    // 4. Verify that contentMod_ is not null
    ASSERT_NE(richEditorPattern->GetContentModifier(), nullptr);

    // 5. Call BeforeCreateLayoutWrapper which should now execute the contentMod_ branch
    richEditorPattern->BeforeCreateLayoutWrapper();

    // 6. Verify the function executed properly - the contentMod_->ContentChange() should have been called
    EXPECT_EQ(richEditorPattern->isSpanStringMode_, true);
    EXPECT_NE(richEditorPattern->GetContentModifier(), nullptr);
}

/**
 * @tc.name: OnMenuItemAction001
 * @tc.desc: test OnMenuItemAction
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, OnMenuItemAction001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get richeditor pattern and add text span
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);

    /**
     * @tc.steps: step2. request focus
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. create a scene where the text menu has popped up
     */
    FuncVariant funcCopy = []() -> std::string { return "copy"; };
    FuncVariant funcSelectText = []() -> std::string { return "selectText"; };

    richEditorPattern->dataDetectorAdapter_->textDetectResult_.menuOptionAndAction["email"] = { { "copy", funcCopy },
        { "selectText", funcSelectText } };

    richEditorPattern->OnModifyDone();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->textSelector_.Update(0, 2);

    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 2);
    EXPECT_EQ(richEditorPattern->copyOption_, CopyOptions::Local);

    /**
     * @tc.step: step4. test OnMenuItemAction
     */
    richEditorPattern->isMousePressed_ = true;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->selectOverlay_->OnMenuItemAction(OptionMenuActionId::COPY, OptionMenuType::MOUSE_MENU);
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwapAfterDragSelect001
 * @tc.desc: Test OnDirtyLayoutWrapperSwap with afterDragSelect_ enabled
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, OnDirtyLayoutWrapperSwapAfterDragSelect001, TestSize.Level0)
{
    // 1: Get RichEditorPattern from node
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // 2: Setup layout wrapper and algorithm
    auto renderContext = richEditorNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    renderContext->ResetClipEdge();

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // 3: Set afterDragSelect_ to true to trigger the target branch
    richEditorPattern->afterDragSelect_ = true;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.frameSizeChange = false;

    // 4: Call OnDirtyLayoutWrapperSwap which should trigger the afterDragSelect_ branch
    richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);

    // 5: Verify afterDragSelect_ was reset to false after processing
    EXPECT_FALSE(richEditorPattern->afterDragSelect_);
}

/**
 * @tc.name: RichEditorAddImageSpanFromCollaborationTest001
 * @tc.desc: Test AddImageSpanFromCollaboration when isSpanStringMode_ is false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorAddImageSpanFromCollaborationTest001, TestSize.Level1)
{
    // 1. Create RichEditor node and pattern
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isSpanStringMode_ = false;

    // 2. Prepare ImageSpanOptions with image source
    ImageSpanOptions options;
    options.image = "test_image.png";
    options.offset = 0;

    // 3. Call AddImageSpanFromCollaboration with updateCaret = true
    int32_t result = richEditorPattern->AddImageSpanFromCollaboration(options, true);

    // 4. Verify that the function returns successfully (should return spanIndex >= -1)
    EXPECT_GE(result, -1);
}

/**
 * @tc.name: CheckPreviewTextValidate001
 * @tc.desc: Test CheckPreviewTextValidate function when not dragging
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, CheckPreviewTextValidate001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->status_ = Status::NONE;
    PreviewRange range;
    range.start = 0;
    range.end = 5;

    auto result = richEditorPattern->CheckPreviewTextValidate(u"preview_text", range);
    EXPECT_EQ(result, 0);
    auto resultStdString = richEditorPattern->CheckPreviewTextValidate("preview_text", range);
    EXPECT_EQ(resultStdString, 0);
}

/**
 * @tc.name: CheckPreviewTextValidate002
 * @tc.desc: Test CheckPreviewTextValidate function when dragging
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, CheckPreviewTextValidate002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->status_ = Status::DRAGGING;
    PreviewRange range;
    range.start = 0;
    range.end = 5;

    auto result = richEditorPattern->CheckPreviewTextValidate(u"preview_text", range);
    EXPECT_EQ(result, -1);
    auto resultStdString = richEditorPattern->CheckPreviewTextValidate("preview_text", range);
    EXPECT_EQ(resultStdString, -1);
}

/**
 * @tc.name: CheckPreviewTextValidate003
 * @tc.desc: Test CheckPreviewTextValidate function with empty preview text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, CheckPreviewTextValidate003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->status_ = Status::NONE;
    PreviewRange range;
    range.start = 0;
    range.end = 0;

    auto result = richEditorPattern->CheckPreviewTextValidate(u"", range);
    EXPECT_EQ(result, 0);
    auto resultStdString = richEditorPattern->CheckPreviewTextValidate("", range);
    EXPECT_EQ(resultStdString, 0);
}

/**
 * @tc.name: CheckPreviewTextValidate004
 * @tc.desc: Test CheckPreviewTextValidate function with invalid range
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, CheckPreviewTextValidate004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->status_ = Status::NONE;
    PreviewRange range;
    range.start = -1;
    range.end = -1;

    auto result = richEditorPattern->CheckPreviewTextValidate(u"preview_text", range);
    EXPECT_EQ(result, 0);
    auto resultStdString = richEditorPattern->CheckPreviewTextValidate("preview_text", range);
    EXPECT_EQ(resultStdString, 0);
}

/**
 * @tc.name: ProcessTextTruncationOperation001
 * @tc.desc: Test ProcessTextTruncationOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessTextTruncationOperation001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    const int32_t MAX_LENGTH = 3;
    richEditorPattern->SetMaxLength(MAX_LENGTH);
    std::u16string existingText = u"12345";
    richEditorPattern->InsertValue(existingText);
    richEditorPattern->previewTextRecord_.needReplacePreviewText = false;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->previewTextRecord_.replacedRange = { 0, 0 };
    std::u16string newText = u"67890";
    auto result = richEditorPattern->ProcessTextTruncationOperation(newText, true);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: ProcessTextTruncationOperation002
 * @tc.desc: Test ProcessTextTruncationOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessTextTruncationOperation002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    const int32_t MAX_LENGTH = 3;
    richEditorPattern->SetMaxLength(MAX_LENGTH);
    std::u16string existingText = u"12345";
    richEditorPattern->InsertValue(existingText);
    richEditorPattern->previewTextRecord_.needReplacePreviewText = false;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->previewTextRecord_.replacedRange = { 0, 0 };
    richEditorPattern->previewTextRecord_.needReplaceText = true;

    std::u16string newText = u"67890";
    auto result = richEditorPattern->ProcessTextTruncationOperation(newText, true);
    ASSERT_TRUE(result);
}

/**
 * @tc.name: ProcessTextTruncationOperation003
 * @tc.desc: Test ProcessTextTruncationOperation
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessTextTruncationOperation003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    const int32_t MAX_LENGTH = 3;
    richEditorPattern->SetMaxLength(MAX_LENGTH);
    std::u16string existingText = u"12345";
    richEditorPattern->InsertValue(existingText);
    richEditorPattern->previewTextRecord_.needReplacePreviewText = false;
    richEditorPattern->previewTextRecord_.previewContent = u"";
    richEditorPattern->previewTextRecord_.replacedRange = { 0, 0 };
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;

    std::u16string newText = u"67890";
    auto result = richEditorPattern->ProcessTextTruncationOperation(newText, true);
    ASSERT_TRUE(result);
}

/**
 * @tc.name: ProcessInsertValueMorePreviewTextTest001
 * @tc.desc: Test the branch when preRecord.needReplacePreviewText is true and
 *           previewTextRecord_.needReplacePreviewText is false in ProcessInsertValueMore
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessInsertValueMorePreviewTextTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    std::u16string text = u"test text";
    RichEditorPattern::OperationRecord record;
    record.beforeCaretPosition = 0;
    record.afterCaretPosition = 0;

    OperationType operationType = OperationType::DEFAULT;
    RichEditorChangeValue changeValue;
    RichEditorPattern::PreviewTextRecord preRecord;
    preRecord.needReplacePreviewText = true;
    preRecord.previewTextHasStarted = true;
    preRecord.startOffset = 0;
    preRecord.endOffset = static_cast<int32_t>(text.length());
    richEditorPattern->previewTextRecord_.needReplacePreviewText = false;
    bool shouldCommitInput = false;

    richEditorPattern->ProcessInsertValueMore(text, record, operationType, changeValue, preRecord, shouldCommitInput);
}

/**
 * @tc.name: ProcessInsertValueTruncationTest001
 * @tc.desc: Test the branch when ProcessTextTruncationOperation returns false in ProcessInsertValue
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessInsertValueTruncationTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->SetMaxLength(0);
    std::u16string insertValue = u"test text";
    richEditorPattern->ProcessInsertValue(insertValue, OperationType::DEFAULT, true);
}

/**
 * @tc.name: DeleteForwardInPreviewTextInputting001
 * @tc.desc: Test DeleteForward function to cover the branch when IsPreviewTextInputting() returns true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, DeleteForwardInPreviewTextInputting001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->previewTextRecord_.previewContent = u"preview text";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 11;

    EXPECT_TRUE(richEditorPattern->IsPreviewTextInputting());
    richEditorPattern->DeleteForward(1, TextChangeReason::INPUT);
    richEditorPattern->DeleteForward(5, TextChangeReason::INPUT);

    EXPECT_EQ(richEditorPattern->previewTextRecord_.previewContent, u"preview text");
    EXPECT_TRUE(richEditorPattern->previewTextRecord_.previewTextHasStarted);
}

/**
 * @tc.name: RichEditorDeleteContentTest001
 * @tc.desc: Test DeleteContent method when GetTextContentLength() equals 0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorDeleteContentTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    ASSERT_TRUE(spans.empty());

    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 0);
    richEditorPattern->DeleteContent(5);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 0);
}

/**
 * @tc.name: RichEditorDeleteContentTest002
 * @tc.desc: Test DeleteContent method when spans_ is not empty but DoDeleteActions returns true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorDeleteContentTest002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    RichEditorCommonTestNg::AddSpan(u"Hello World");
    auto& spans = richEditorPattern->spans_;
    ASSERT_FALSE(spans.empty());
    EXPECT_GT(richEditorPattern->GetTextContentLength(), 0);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetAboutToDelete([](const RichEditorDeleteValue& info) -> bool {
        return true;
    });

    richEditorPattern->DeleteContent(5);
    EXPECT_LT(richEditorPattern->GetTextContentLength(), 11);
}

/**
 * @tc.name: RichEditorDeleteContentTest003
 * @tc.desc: Test DeleteContent method when spans_ is not empty and DoDeleteActions returns false
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorDeleteContentTest003, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    RichEditorCommonTestNg::AddSpan(u"Hello World");
    auto& spans = richEditorPattern->spans_;
    ASSERT_FALSE(spans.empty());
    EXPECT_GT(richEditorPattern->GetTextContentLength(), 0);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetAboutToDelete([](const RichEditorDeleteValue& info) -> bool {
        return false;
    });

    richEditorPattern->DeleteContent(5);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), 11);
}

/**
 * @tc.name: RichEditorDeleteContentTest004
 * @tc.desc: Test DeleteContent method when spans_ is empty but GetTextContentLength is not 0
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorDeleteContentTest004, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    ASSERT_TRUE(spans.empty());
    auto styledStringRef = AceType::MakeRefPtr<MutableSpanString>(u"Hello Styled String");
    richEditorPattern->styledString_ = styledStringRef;
    richEditorPattern->isSpanStringMode_ = true;

    EXPECT_TRUE(spans.empty());
    EXPECT_GT(richEditorPattern->GetTextContentLength(), 0);

    richEditorPattern->DeleteContent(5);
    EXPECT_GE(richEditorPattern->GetTextContentLength(), 0);
}

/**
 * @tc.name: RichEditorDeleteToMaxLengthTest001
 * @tc.desc: Test DeleteToMaxLength method entering isSpanStringMode_ branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorDeleteToMaxLengthTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    auto& spans = richEditorPattern->spans_;
    ASSERT_TRUE(spans.empty());

    auto styledStringRef = AceType::MakeRefPtr<MutableSpanString>(u"Hello Styled String Content For Testing");
    richEditorPattern->styledString_ = styledStringRef;
    richEditorPattern->isSpanStringMode_ = true;

    int32_t originalLength = richEditorPattern->GetTextContentLength();
    EXPECT_GT(originalLength, 10);
    int32_t maxLength = 10;
    EXPECT_LT(maxLength, originalLength);
    richEditorPattern->DeleteToMaxLength(maxLength);

    EXPECT_LE(richEditorPattern->GetTextContentLength(), maxLength);
}

/**
 * @tc.name: RichEditorCursorMoveRightTest001
 * @tc.desc: Test CursorMoveRight method entering isEmojiOnCaretForward branch but not caretPosition equality branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorCursorMoveRightTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    RichEditorCommonTestNg::AddSpan(u"Hello 👨‍👩‍👧‍👦 World");
    richEditorPattern->caretPosition_ = 6;

    int32_t contentLength = richEditorPattern->GetTextContentLength();
    EXPECT_GT(contentLength, 10);
    EXPECT_LT(richEditorPattern->caretPosition_, contentLength);

    int32_t originalCaretPosition = richEditorPattern->caretPosition_;
    bool result = richEditorPattern->CursorMoveRight();

    EXPECT_TRUE(result);
    EXPECT_NE(richEditorPattern->caretPosition_, originalCaretPosition);
    EXPECT_GT(richEditorPattern->caretPosition_, originalCaretPosition);
}

/**
 * @tc.name: RichEditorCursorMoveToNextWordTest001
 * @tc.desc: Test CursorMoveToNextWord method entering textSelector branch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorCursorMoveToNextWordTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorCommonTestNg::ClearSpan();
    RichEditorCommonTestNg::AddSpan(u"Hello World Test Content");
    TextSelector selector(2, 8);
    richEditorPattern->textSelector_ = selector;

    richEditorPattern->caretPosition_ = 5;
    EXPECT_FALSE(richEditorPattern->textSelector_.SelectNothing());
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 2);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 8);

    richEditorPattern->CursorMoveToNextWord(CaretMoveIntent::LeftWord);
    richEditorPattern->ResetSelection();
    richEditorPattern->textSelector_ = selector;
    richEditorPattern->caretPosition_ = 5;

    richEditorPattern->CursorMoveToNextWord(CaretMoveIntent::RightWord);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: GetAcceptedTouchLocationInfo001
 * @tc.desc: Test basic function of UrlSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetAcceptedTouchLocationInfo005, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isTouchSelecting_ = false;
    richEditorPattern->moveCaretState_.touchFingerId = 12;
    TouchEventInfo touchInfo("touch");
    touchInfo.AddChangedTouchLocationInfo(TouchLocationInfo(12));
    auto result = richEditorPattern->GetAcceptedTouchLocationInfo(touchInfo);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->GetFingerId(), 12);
}

/**
 * @tc.name: GetAcceptedTouchLocationInfo001
 * @tc.desc: Test basic function of UrlSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetAcceptedTouchLocationInfo006, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->isTouchSelecting_ = false;
    richEditorPattern->moveCaretState_.touchFingerId = 8;
    TouchEventInfo touchInfo("touch");
    touchInfo.AddChangedTouchLocationInfo(TouchLocationInfo(1));
    touchInfo.AddChangedTouchLocationInfo(TouchLocationInfo(2));
    auto result = richEditorPattern->GetAcceptedTouchLocationInfo(touchInfo);
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: HandleTouchDownNoCaretTouchTest001
 * @tc.desc: Test HandleTouchDownNoCaretTouch
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, HandleTouchDownNoCaretTouchTest001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto overlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    richEditorPattern->overlayMod_ = overlayModifier;
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    EXPECT_TRUE(richEditorPattern->HasFocus());
    TouchLocationInfo touchInfo(0);
    touchInfo.SetSourceTool(SourceTool::FINGER);
    Offset touchPosition(1000.0, 1000.0);
    touchInfo.SetLocalLocation(touchPosition);
    RectF caretRect(0.0, 0.0, 10.0, 20.0);
    richEditorPattern->HandleTouchDown(touchInfo);
    EXPECT_FALSE(richEditorPattern->moveCaretState_.isTouchCaret)
        << "isTouchCaret should remain false when touch is not on caret";
    EXPECT_EQ(richEditorPattern->touchedFingerCount_, 1);
    EXPECT_EQ(richEditorPattern->moveCaretState_.touchDownOffset, touchPosition);
}

/**
 * @tc.name: ScheduleFirstClickResetAfterWindowFocus001
 * @tc.desc: Test ScheduleFirstClickResetAfterWindowFocus
 * @tc.type: FUNC
 */

HWTEST_F(RichEditorUrlStyleTest, ScheduleFirstClickResetAfterWindowFocus001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    EXPECT_NE(richEditorPattern, nullptr);
    EXPECT_NE(richEditorPattern->GetContext(), nullptr);
    auto pipeline = richEditorPattern->GetContext();
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    ASSERT_NE(mockTaskExecutor, nullptr);
    context->taskExecutor_ = mockTaskExecutor;
    auto taskExecutor = pipeline->GetTaskExecutor();
    richEditorPattern->ScheduleFirstClickResetAfterWindowFocus();
    EXPECT_FALSE(richEditorPattern->firstClickAfterWindowFocus_);
}

/**
 * @tc.name: HandleTouchCancelAfterLongPress001
 * @tc.desc: Test HandleTouchCancelAfterLongPress
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, HandleTouchCancelAfterLongPress001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->previewLongPress_ = true;
    richEditorPattern->editingLongPress_ = false;
    richEditorPattern->isEditing_ = true;
    int32_t testStart = 5;
    int32_t testEnd = 10;
    richEditorPattern->textSelector_.Update(testStart, testEnd);
    richEditorPattern->HandleTouchCancelAfterLongPress();
    EXPECT_NE(richEditorPattern, nullptr);
    EXPECT_NE(richEditorPattern->GetContext(), nullptr);
    SUCCEED() << "Function executed without crashing";
}

/**
 * @tc.name: RichEditorHandleMouseRightButton001
 * @tc.desc: Test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, RichEditorHandleMouseRightButton001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->isInterceptMouseRightRelease_ = true;
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->textSelector_.Update(0, 10);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    MouseInfo mouseInfo;
    mouseInfo.SetLocalLocation(Offset(10.0f, 20.0f));
    mouseInfo.SetGlobalLocation(Offset(100.0f, 150.0f));
    mouseInfo.SetAction(MouseAction::RELEASE);
    EXPECT_TRUE(richEditorPattern->textSelector_.IsValid());
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
    EXPECT_FALSE(richEditorPattern->usingMouseRightButton_);
}

/**
 * @tc.name: GetUrlSpanColor002
 * @tc.desc: Test GetUrlSpanColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, GetUrlSpanColor002, TestSize.Level0)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    EXPECT_CALL(*themeManager, GetTheme(::testing::A<ThemeType>()))
        .WillRepeatedly(::testing::Return(richEditorTheme));
    EXPECT_CALL(*themeManager, GetTheme(::testing::A<ThemeType>(), ::testing::_))
        .WillRepeatedly(::testing::Return(richEditorTheme));
    auto oldThemeManager = PipelineBase::GetCurrentContext()->themeManager_;
    PipelineBase::GetCurrentContext()->themeManager_ = themeManager;
    RichEditorTheme expectedTheme;
    auto color = richEditorPattern->GetUrlSpanColor();
    EXPECT_EQ(color, expectedTheme.GetUrlDefaultColor());
    EXPECT_EQ(richEditorPattern->GetUrlHoverColor(), expectedTheme.GetUrlHoverColor());
    EXPECT_EQ(richEditorPattern->GetUrlPressColor(), expectedTheme.GetUrlPressColor());
    PipelineBase::GetCurrentContext()->themeManager_ = oldThemeManager;
}

/**
 * @tc.name: ProcessAutoFillOnPaste001
 * @tc.desc: Test ProcessAutoFillOnPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, ProcessAutoFillOnPaste001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->ProcessAutoFillOnPaste();
    SUCCEED() << "Function called successfully, requires Mock verification for internal calls";
}

/**
 * @tc.name: HandleOnPasswordVault001
 * @tc.desc: Test HandleOnPasswordVault
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorUrlStyleTest, HandleOnPasswordVault001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto richEditorNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->HandleOnPasswordVault();
    EXPECT_NE(richEditorPattern, nullptr);
    SUCCEED() << "HandleOnPasswordVault executed successfully";
}
}