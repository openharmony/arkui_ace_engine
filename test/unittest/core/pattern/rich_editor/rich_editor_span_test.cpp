/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <utility>
#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
enum class SpanType {
    TEXT,
    SYMBOL,
    IMAGE,
    BUILDER
};
namespace {
const std::vector<std::u16string> INSERT_VALUE_LIST = {
    u"哈哈哈haha123",
    u"\n哈哈哈haha123",
    u"哈哈哈\nhaha123",
    u"哈哈哈haha123\n",
    u"\n哈哈哈\nhaha123",
    u"\n哈哈哈haha123\n",
    u"哈哈哈\nhaha123\n",
    u"\n哈哈哈\nhaha123\n",
};
const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
    []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
const std::unordered_map<SpanType, std::function<void(RefPtr<RichEditorPattern>)>> SPAN_CONSTRUCTOR_MAP = {
    { SpanType::TEXT, [](RefPtr<RichEditorPattern> pattern) { pattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);} },
    { SpanType::IMAGE, [](RefPtr<RichEditorPattern> pattern) { pattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);} },
    { SpanType::SYMBOL, [](RefPtr<RichEditorPattern> pattern) { pattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);} },
    { SpanType::BUILDER, [](RefPtr<RichEditorPattern> pattern) { pattern->AddPlaceholderSpan(BUILDER_NODE_1, {});} }
};
} // namespace

class RichEditorSpanTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    template<typename... Args>
    void InitSpans(Args... args);
    template<typename T, typename... Args>
    void ConstructSpans(RefPtr<RichEditorPattern> pattern, T value, Args... args);
    void ConstructSpans(RefPtr<RichEditorPattern> pattern) {}
    static void TearDownTestSuite();
};

void RichEditorSpanTest::SetUp()
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

void RichEditorSpanTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorSpanTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

template<typename... Args>
void RichEditorSpanTest::InitSpans(Args... args)
{
    RichEditorCommonTestNg::ClearSpan();
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ConstructSpans(pattern, args...);
}

template<typename T, typename... Args>
void RichEditorSpanTest::ConstructSpans(RefPtr<RichEditorPattern> pattern, T value, Args... args)
{
    if constexpr (std::is_same_v<T, std::string>) {
        pattern->AddTextSpan({ .value = value });
    } else if constexpr (std::is_same_v<T, SpanType>) {
        auto it = SPAN_CONSTRUCTOR_MAP.find(value);
        (it->second)(pattern);
    }
    ConstructSpans(pattern, args...);
}

/**
 * @tc.name: RichEditorSpanTestTextText001
 * @tc.desc: test span num [text-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::TEXT); // [hello1][hello1]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextImage001
 * @tc.desc: test span num [text-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::IMAGE); // hello1[image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextBuilder001
 * @tc.desc: test span num [text-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    
    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::BUILDER); // hello1[builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestTextSymbol001
 * @tc.desc: test span num [text-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestTextSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 6;
        InitSpans(SpanType::TEXT, SpanType::SYMBOL); // hello1[symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);
}

/**
 * @tc.name: RichEditorSpanTestImageText001
 * @tc.desc: test span num [image-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::TEXT); // [image]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageImage001
 * @tc.desc: test span num [image-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::IMAGE); // [image][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageBuilder001
 * @tc.desc: test span num [image-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::BUILDER); // [image][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestImageSymbol001
 * @tc.desc: test span num [image-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestImageSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::IMAGE, SpanType::SYMBOL); // [image][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderText001
 * @tc.desc: test span num [builder-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::TEXT); // [builder]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderImage001
 * @tc.desc: test span num [builder-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::IMAGE); // [builder][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderBuilder001
 * @tc.desc: test span num [builder-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::BUILDER); // [builder][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestBuilderSymbol001
 * @tc.desc: test span num [builder-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestBuilderSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 1;
        InitSpans(SpanType::BUILDER, SpanType::SYMBOL); // [builder][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolText001
 * @tc.desc: test span num [symbol-text]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::TEXT); // [symbol]hello1
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3); // fail
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolImage001
 * @tc.desc: test span num [symbol-image]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolImage001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::IMAGE); // [symbol][image]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolBuilder001
 * @tc.desc: test span num [symbol-builder]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolBuilder001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::BUILDER); // [symbol][builder]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

/**
 * @tc.name: RichEditorSpanTestSymbolSymbol001
 * @tc.desc: test span num [symbol-symbol]
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanTest, RichEditorSpanTestSymbolSymbol001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);

    auto insertFunc = [this, richEditorPattern](const std::u16string& insertValue) {
        const int32_t insertIndex = 2;
        InitSpans(SpanType::SYMBOL, SpanType::SYMBOL); // [symbol][symbol]
        ASSERT_EQ(richEditorPattern->spans_.back()->rangeStart, insertIndex);
        richEditorPattern->SetCaretOffset(insertIndex);
        ASSERT_EQ(richEditorPattern->caretPosition_, insertIndex);
        richEditorPattern->InsertValue(insertValue);
    };

    // 0: 哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[0]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 1: \n哈哈哈haha123
    insertFunc(INSERT_VALUE_LIST[1]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 2: 哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[2]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 3: 哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[3]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);

    // 4: \n哈哈哈\nhaha123
    insertFunc(INSERT_VALUE_LIST[4]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);

    // 5: \n哈哈哈haha123\n
    insertFunc(INSERT_VALUE_LIST[5]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 6: 哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[6]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 4);
    EXPECT_EQ(contentNode->GetChildren().size(), 4);

    // 7: \n哈哈哈\nhaha123\n
    insertFunc(INSERT_VALUE_LIST[7]);
    EXPECT_EQ(richEditorPattern->spans_.size(), 5);
    EXPECT_EQ(contentNode->GetChildren().size(), 5);
}

} // namespace OHOS::Ace::NG