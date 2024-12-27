/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "gtest/hwext/gtest-ext.h"
#include "gtest/hwext/gtest-tag.h"
#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_ng/pattern/pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RichEditorPatternTestSevenNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<FrameNode> richEditorNode;
};

void RichEditorPatternTestSevenNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    richEditorNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    richEditorPattern->InitScrollablePattern();
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    richEditorPattern->CreateNodePaintMethod();
    richEditorNode->GetGeometryNode()->SetContentSize({});
}

void RichEditorPatternTestSevenNg::TearDown()
{
    richEditorNode = nullptr;
    MockParagraph::TearDown();
}

void RichEditorPatternTestSevenNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

/**
 * @tc.name: GetTextBoxes003
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, GetTextBoxes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfo;
    RefPtr<MockParagraph> mockParagraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    const OHOS::Ace::NG::ParagraphStyle expectedStyle;
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraph, GetParagraphStyle()).WillRepeatedly(ReturnRef(expectedStyle));
    paragraphInfo.paragraph = mockParagraph;
    paragraphInfo.paragraphStyle = expectedStyle;
    paragraphInfo.start = 0;
    paragraphInfo.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfo);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfo));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

/**
 * @tc.name: GetTextBoxes004
 * @tc.desc: test GetTextBoxes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, GetTextBoxes004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = u"testShowHandles";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;

    ParagraphStyle paragraphStyle = {};
    paragraphStyle.leadingMargin = LeadingMargin();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 10;
    ParagraphManager::ParagraphInfo paragraphInfoOne;
    RefPtr<MockParagraph> mockParagraphOne = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*mockParagraphOne, GetRectsForRange(_, _, _))
        .WillRepeatedly(Invoke([&](int32_t start, int32_t end, std::vector<RectF>& selectedRects) {
            selectedRects.emplace_back(RectF(0, 0, 100, 20));
        }));
    LeadingMargin leadingMarginOne;
    EXPECT_CALL(*mockParagraphOne, GetParagraphStyle()).WillRepeatedly(ReturnRef(paragraphStyle));
    paragraphInfoOne.paragraph = mockParagraphOne;
    paragraphInfoOne.paragraphStyle = paragraphStyle;
    paragraphInfoOne.start = 0;
    paragraphInfoOne.end = 10;
    richEditorPattern->paragraphs_.paragraphs_.emplace_back(paragraphInfoOne);
    richEditorPattern->paragraphs_.AddParagraph(std::move(paragraphInfoOne));
    auto textBoxes = richEditorPattern->GetTextBoxes();
    EXPECT_NE(textBoxes.size(), 0);
}

/**
 * @tc.name: HandleOnDragDropStyledString001
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    auto host = richEditorPattern->GetHost();
    EXPECT_TRUE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString002
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString003
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<MockUnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();

    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString004
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "some", "string", "content" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = false;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDropStyledString005
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "some", "string", "content" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->HandleOnDragDropStyledString(event);
    auto host = richEditorPattern->GetHost();
    EXPECT_TRUE(host->isRestoreInfoUsed_);
}

/**
 * @tc.name: HandleOnDragDsropStyledString006
 * @tc.desc: test HandleOnDragDropStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorPatternTestSevenNg, HandleOnDragDropStyledString006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RefPtr<OHOS::Ace::DragEvent> event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    ASSERT_NE(event, nullptr);
    RefPtr<UnifiedData> unifiedData = AceType::MakeRefPtr<MockUnifiedData>();
    ASSERT_NE(unifiedData, nullptr);
    std::vector<uint8_t> expectedReturnUnint8_t = { 1, 2, 3 };
    std::vector<std::string> expectedReturnString = { "" };

    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_CONTENT);
    TLVUtil::WriteString(expectedReturnUnint8_t, "Some string content");
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_SPAN_STRING_SPANS);
    TLVUtil::WriteUint8(expectedReturnUnint8_t, TLV_END);

    UdmfClient* client = UdmfClient::GetInstance();
    MockUdmfClient* mockClient = static_cast<MockUdmfClient*>(client);
    EXPECT_CALL(*mockClient, GetSpanStringRecord(_)).WillRepeatedly(Return(expectedReturnUnint8_t));
    EXPECT_CALL(*mockClient, GetPlainTextRecords(_)).WillRepeatedly(Return(expectedReturnString));

    std::string selectedStr = "test123";
    OHOS::Ace::UdmfClient::GetInstance()->AddPlainTextRecord(unifiedData, selectedStr);
    event->SetData(unifiedData);
    richEditorPattern->isSpanStringMode_ = true;
    richEditorPattern->HandleOnDragDropStyledString(event);
    EXPECT_NE(event->GetData(), nullptr);
    auto host = richEditorPattern->GetHost();
    EXPECT_FALSE(host->isRestoreInfoUsed_);
}
} // namespace OHOS::Ace::NG
