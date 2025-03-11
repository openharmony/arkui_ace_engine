/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_TEXT_AREA_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_TEXT_AREA_BASE_H

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/text_input/mock/mock_text_field_select_overlay.h"

#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr float OFFSET = 3;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
const std::u16string DEFAULT_TEXT_U16 = u"abcdefghijklmnopqrstuvwxyz";
const std::string DEFAULT_TEXT_THREE_LINE = "abcdef\nghijkl\nmnopqr\n";
const std::string HELLO_TEXT = "hello";
const std::string DEFAULT_PLACE_HOLDER = "please input text here";
const std::string LOWERCASE_FILTER = "[a-z]";
const std::string NUMBER_FILTER = "^[0-9]*$";
const std::string DEFAULT_INPUT_FILTER = "[a-z]";
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_1 = ParseFontFeatureSettings("\"ss01\" 1");
const std::list<std::pair<std::string, int32_t>> FONT_FEATURE_VALUE_0 = ParseFontFeatureSettings("\"ss01\" 0");
template<typename CheckItem, typename Expected>
struct TestItem {
    CheckItem item;
    Expected expected;
    std::string error;
    TestItem(CheckItem checkItem, Expected expectedValue, std::string message = "")
        : item(checkItem), expected(expectedValue), error(std::move(message))
    {}
    TestItem() = default;
};
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};

class TextAreaBase : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
    void GetFocus();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_TEXT_AREA_BASE_H
