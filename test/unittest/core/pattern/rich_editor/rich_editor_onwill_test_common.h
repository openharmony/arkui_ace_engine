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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_ONWILL_TEST_COMMON_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_ONWILL_TEST_COMMON_H

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "test/unittest/core/pattern/rich_editor/rich_editor_recursive_macro.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"

#define GENERATE_CASES(num, OP) EXPAND_##num(OP, num)

#define CREATE_INSERT_CASE(testSuite, cases, number)                                                         \
HWTEST_F(testSuite, testSuite##number, TestSize.Level1)                                                      \
{                                                                                                            \
    ASSERT_NE(richEditorNode_, nullptr);                                                                     \
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();                                         \
    ASSERT_NE(pattern, nullptr);                                                                             \
    const auto& testCase = (cases)[std::atoi(#number)];                                                      \
    const auto& input = testCase.first;                                                                      \
    const auto& expectOutput = testCase.second;                                                              \
    ASSERT_TRUE(pattern->caretPosition_ != -1 || (input.selector.start != -1 && input.selector.end != -1));  \
    InitSpans(input.spans);                                                                                  \
    if (input.caret != -1) {                                                                                 \
        pattern->caretPosition_ = input.caret;                                                               \
    } else {                                                                                                 \
        pattern->UpdateSelector(input.selector.start, input.selector.end);                                   \
        pattern->caretPosition_ = input.selector.start;                                                      \
    }                                                                                                        \
    InitContentChangeCallback();                                                                             \
    pattern->InsertValue(INSERT_VALUE);                                                                      \
    EXPECT_EQ(isOnWillChangeCalled, true);                                                                   \
    ASSERT_EQ(onWillReplacedSpans.size(), 1);                                                                \
    auto& replacedSpan = onWillReplacedSpans.front();                                                        \
    EXPECT_EQ(onWillRangeBefore, expectOutput.rangeBefore);                                                  \
    EXPECT_EQ(replacedSpan.GetSpanIndex(), expectOutput.spanIndex);                                          \
    EXPECT_EQ(replacedSpan.OffsetInSpan(), expectOutput.rangeInSpan.start);                                  \
    EXPECT_EQ(replacedSpan.GetEraseLength(), expectOutput.rangeInSpan.end - expectOutput.rangeInSpan.start); \
    EXPECT_EQ(replacedSpan.GetSpanRangeStart(), expectOutput.spanRange.start);                               \
    EXPECT_EQ(replacedSpan.GetSpanRangeEnd(), expectOutput.spanRange.end);                                   \
    EXPECT_EQ(replacedSpan.GetValue(), expectOutput.value);                                                  \
}

namespace OHOS::Ace::NG {
enum class SpanType {
    TEXT,
    SYMBOL,
    IMAGE,
    BUILDER
};
struct ReplacedSpanInfo {
    TextRange rangeBefore;
    int32_t spanIndex;
    TextRange rangeInSpan;
    TextRange spanRange;
    std::u16string value;
};
struct InputInfo {
    std::string spans;
    int32_t caret = -1;
    TextRange selector;
};
namespace {
bool isOnWillChangeCalled = false;
bool isOnDidChangeCalled = false;
RichEditorChangeValue onWillChangeValue;
RichEditorChangeValue onDidChangeValue;
auto& onWillRangeBefore = onWillChangeValue.rangeBefore_;
auto& onWillReplacedSpans = onWillChangeValue.replacedSpans_;

std::u16string INSERT_VALUE = u"A";
const auto BUILDER_NODE_1 = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(),
    []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
const TextSpanOptions TEXT_SPAN_OPTIONS = { .value = u"abc", .style = TEXT_STYLE_1 };
const std::unordered_map<SpanType, std::function<void(RefPtr<RichEditorPattern>)>> SPAN_CONSTRUCTOR_MAP = {
    { SpanType::TEXT, [](RefPtr<RichEditorPattern> pattern) { pattern->AddTextSpan(TEXT_SPAN_OPTIONS);} },
    { SpanType::IMAGE, [](RefPtr<RichEditorPattern> pattern) { pattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);} },
    { SpanType::SYMBOL, [](RefPtr<RichEditorPattern> pattern) { pattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);} },
    { SpanType::BUILDER, [](RefPtr<RichEditorPattern> pattern) { pattern->AddPlaceholderSpan(BUILDER_NODE_1, {});} }
};

const std::vector<std::string> SPAN_KEY_WORDS = {"[IMAGE]", "[BUILDER]", "[SYMBOL]"};
const std::unordered_map<std::string, std::function<void(RefPtr<RichEditorPattern>)>> SPAN_ADDER_MAP = {
    { SPAN_KEY_WORDS[0], [](RefPtr<RichEditorPattern> pattern) { pattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);} },
    { SPAN_KEY_WORDS[1], [](RefPtr<RichEditorPattern> pattern) { pattern->AddPlaceholderSpan(BUILDER_NODE_1, {});} },
    { SPAN_KEY_WORDS[2], [](RefPtr<RichEditorPattern> pattern) { pattern->AddSymbolSpan(SYMBOL_SPAN_OPTIONS_1);} },
};

class SpanStringSpliter {
public:
static std::vector<std::string> SplitSpanString(const std::string& str)
{
    auto parts = SplitByPipe(str);
    return SplitString(parts);
}
private:
static std::vector<std::string> SplitByPipe(const std::string& str) 
{
    std::vector<std::string> parts;
    std::regex pattern(R"([^|]+)");
    std::sregex_iterator it(str.begin(), str.end(), pattern);
    std::sregex_iterator end;
    for (; it != end; ++it) {
        parts.push_back(it->str());
    }
    return parts;
}

static std::vector<std::string> SplitString(const std::string& str) {
    std::vector<std::string> result;
    std::string current_str;
    int i = 0;
    int n = str.size();
    while (i < n) {
        if (str[i] == '\n') {
            current_str += '\n';
            result.push_back(current_str);
            current_str.clear();
            i++;
            continue;
        }
        bool found = false;
        for (const auto& kw : SPAN_KEY_WORDS) {
            int kw_len = kw.size();
            CHECK_NULL_CONTINUE(i + kw_len <= n && str.substr(i, kw_len) == kw);
            if (!current_str.empty()) {
                result.push_back(current_str);
                current_str.clear();
            }
            result.push_back(kw);
            i += kw_len;
            found = true;
            break;
        }
        CHECK_NULL_CONTINUE(!found);
        current_str += str[i];
        i++;
    }
    if (!current_str.empty()) {
        result.push_back(current_str);
    }
    return result;
}

static std::vector<std::string> SplitString(std::vector<std::string>& parts)
{
    std::vector<std::string> result;
    for (auto& part : parts) {
        auto partResult = SplitString(part);
        result.insert(result.end(), partResult.begin(), partResult.end());
    }
    return result;
}
};

} // namespace

class RichEditorOnWillTestCommon : public RichEditorCommonTestNg {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
        MockContainer::SetUp();
        MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
        auto* stack = ViewStackProcessor::GetInstance();
        auto nodeId = stack->ClaimNodeId();
        richEditorNode_ = FrameNode::GetOrCreateFrameNode(
            V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
        ASSERT_NE(richEditorNode_, nullptr);
        auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
        pattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
        pattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    }

    void TearDown() override
    {
        richEditorNode_ = nullptr;
        MockParagraph::TearDown();
    }

    static void TearDownTestSuite()
    {
        TestNG::TearDownTestSuite();
    }
protected:
    void ResetContentChangeCallbackState()
    {
        isOnWillChangeCalled = false;
        isOnDidChangeCalled = false;
        onWillChangeValue.reset();
        onDidChangeValue.reset();
    }

    void InitContentChangeCallback()
    {
        ResetContentChangeCallbackState();
        auto onWillChange = [](const RichEditorChangeValue& changeValue) {
            isOnWillChangeCalled = true;
            onWillChangeValue = changeValue;
            return true;
        };
        RichEditorModelNG::SetOnWillChange(AceType::RawPtr(richEditorNode_), std::move(onWillChange));

        auto onDidChange = [](const RichEditorChangeValue& changeValue) {
            isOnDidChangeCalled = true;
            onDidChangeValue = changeValue;
        };
        RichEditorModelNG::SetOnDidChange(AceType::RawPtr(richEditorNode_), std::move(onDidChange));
    }

    void InitSpans(const std::vector<SpanType>& spanTypes)
    {
        RichEditorCommonTestNg::ClearSpan();
        auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
        for (const auto& spanType : spanTypes) {
            auto it = SPAN_CONSTRUCTOR_MAP.find(spanType);
            (it->second)(pattern);
        }
    }

    void InitSpans(const std::string& spanString)
    {
        RichEditorCommonTestNg::ClearSpan();
        std::vector<std::string> spans = SpanStringSpliter::SplitSpanString(spanString);
        auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
        for (const auto& span : spans) {
            auto it = SPAN_ADDER_MAP.find(span);
            if (it != SPAN_ADDER_MAP.end()) {
                (it->second)(pattern);
                continue;
            }
            TextSpanOptions options = { .value = StringUtils::Str8ToStr16(span), .style = TEXT_STYLE_1 };
            pattern->AddTextSpan(options);
        }
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_ONWILL_TEST_COMMON_H