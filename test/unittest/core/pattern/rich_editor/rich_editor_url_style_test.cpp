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
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

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
    static void TearDownTestSuite();
};

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
    return AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(index));
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
    EXPECT_EQ(spanItem->urlAddress, u"");
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
    EXPECT_EQ(spanItem1->urlAddress, u"");
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

}