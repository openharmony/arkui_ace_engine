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

#include <cstdint>
#include <iostream>
#include <optional>
#include <string>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/common/ace_application_info.h"
#include "core/components/common/layout/constants.h"
#include "core/components/select/select_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "core/components/theme/icon_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/pattern/menu/menu_layout_property.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_layout_property.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "base/geometry/dimension.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
namespace {
const std::string SELECT_TEXT = "select";
const std::string OPTION_TEXT = "aaa";
const std::string OPTION_TEXT_2 = "BBB";
const std::string OPTION_TEXT_3 = "CCC";
const std::string INTERNAL_SOURCE = "$r('app.media.icon')";
const std::string FILE_SOURCE = "/common/icon.png";
const std::string DEFAULT_STR("2.0");
const std::string TEXT_VALUE = "test";
const CalcLength MARGIN_LENGTH = CalcLength("8vp");
const CalcSize TEXT_IDEAL_SIZE = CalcSize(CalcLength("50vp"), std::nullopt);
constexpr float FULL_SCREEN_WIDTH = 720.0f;
constexpr float FULL_SCREEN_HEIGHT = 1136.0f;
const SizeF FULL_SCREEN_SIZE(FULL_SCREEN_WIDTH, FULL_SCREEN_HEIGHT);
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Color BG_COLOR_VALUE = Color::FromRGB(100, 255, 100);
const std::vector<SelectParam> CREATE_VALUE = { { OPTION_TEXT, FILE_SOURCE }, { OPTION_TEXT_2, INTERNAL_SOURCE },
    { OPTION_TEXT_3, INTERNAL_SOURCE } };
constexpr float TEST_SIZE_WIDTH = 10.0f;
constexpr float TEST_SIZE_HEIGHT = 10.0f;
const SizeF SELECT_TEXT_SIZE(TEST_SIZE_WIDTH, TEST_SIZE_HEIGHT);
} // namespace

struct TestProperty {
    std::optional<Dimension> FontSize = std::nullopt;
    std::optional<Ace::FontStyle> FontStyle = std::nullopt;
    std::optional<FontWeight> FontWeight = std::nullopt;
    std::optional<std::vector<std::string>> FontFamily = std::nullopt;
    std::optional<Color> FontColor = std::nullopt;
};

class SelectPatternOneTestControlSizeNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    RefPtr<FrameNode> frameNode_;
    RefPtr<SelectPattern> selectPattern_;

protected:
    static RefPtr<FrameNode> CreateSelect(const std::vector<SelectParam>& value, const TestProperty& test);
};

void SelectPatternOneTestControlSizeNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
}

void SelectPatternOneTestControlSizeNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SelectPatternOneTestControlSizeNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
    MockContainer::SetUp();
}

void SelectPatternOneTestControlSizeNg::TearDown()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> SelectPatternOneTestControlSizeNg::CreateSelect(const std::vector<SelectParam>& value,
    const TestProperty& test)
{
    SelectModelNG selectModelInstance;
    selectModelInstance.Create(value);
    if (test.FontSize.has_value()) {
        selectModelInstance.SetFontSize(test.FontSize.value());
    }
    if (test.FontColor.has_value()) {
        selectModelInstance.SetFontColor(test.FontColor.value());
    }
    if (test.FontStyle.has_value()) {
        selectModelInstance.SetItalicFontStyle(test.FontStyle.value());
    }
    if (test.FontWeight.has_value()) {
        selectModelInstance.SetFontWeight(test.FontWeight.value());
    }
    if (test.FontFamily.has_value()) {
        selectModelInstance.SetFontFamily(test.FontFamily.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: SelectPatternUpdateComponentColorTest001
 * @tc.desc: Test SelectPattern::UpdateComponentColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternOneTestControlSizeNg, SelectPatternUpdateComponentColorTest001, TestSize.Level1)
{
    int32_t backupApiVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));

    /**
     * @tc.steps: step1. Create select model, select frame node and select pattern.
     * @tc.expected: Objects are created successfully.
     */
    TestProperty testProperty;
    testProperty.FontSize = std::make_optional(FONT_SIZE_VALUE);
    testProperty.FontStyle = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.FontWeight = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.FontColor = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.FontFamily = std::make_optional(FONT_FAMILY_VALUE);
    auto frameNode = CreateSelect(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = host->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    pipelineContext->isSystemColorChange_ = true;

    Color testColor = Color::BLUE;
    /**
     * @tc.steps: step3. Test UpdateComponentColor with BACKGROUND_COLOR.
     * @tc.expected: Background color is updated correctly.
     */
    pattern->UpdateComponentColor(testColor, SelectColorType::BACKGROUND_COLOR);
    EXPECT_EQ(renderContext->GetBackgroundColor().value(), testColor);
    AceApplicationInfo::GetInstance().SetApiTargetVersion(backupApiVersion);
}

/**
 * @tc.name: ToJsonSelectedOptionFontAndColor001
 * @tc.desc: Test SelectPattern::ToJsonSelectedOptionFontAndColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternOneTestControlSizeNg, ToJsonSelectedOptionFontAndColor001, TestSize.Level1)
{
    const std::string fontKey = "selectedOptionFont";
    const std::string fontColorKey = "selectedOptionFontColor";

    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    ASSERT_NE(select, nullptr);
    EXPECT_TRUE(select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedOptionFontFamily(FONT_FAMILY_VALUE);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(select));
    pattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_EQ(pattern->textSelectOptionApply_, nullptr);
    EXPECT_TRUE(pattern->options_.empty());

    /**
     * @tc.steps: step1. Test pattern->textSelectOptionApply_ is nullptr.
     * @tc.expected: set value.
     */
    InspectorFilter filter;
    EXPECT_FALSE(filter.IsFastFilter());
    auto jsonValue = JsonUtil::Create(true);
    ASSERT_NE(jsonValue, nullptr);
    pattern->ToJsonSelectedOptionFontAndColor(jsonValue, filter);
    EXPECT_TRUE(jsonValue->Contains(fontKey));
    EXPECT_TRUE(jsonValue->Contains(fontColorKey));

    /**
     * @tc.steps: step2. Test filter is IsFastFilter.
     * @tc.expected: do not set value.
     */
    filter.filterExt.clear();
    filter.filterFixed = 1;
    EXPECT_TRUE(filter.IsFastFilter());
    jsonValue = JsonUtil::Create(true);
    ASSERT_NE(jsonValue, nullptr);
    pattern->ToJsonSelectedOptionFontAndColor(jsonValue, filter);
    EXPECT_FALSE(jsonValue->Contains(fontKey));
    EXPECT_FALSE(jsonValue->Contains(fontColorKey));
}

/**
 * @tc.name: ToJsonSelectedOptionFontAndColor002
 * @tc.desc: Test SelectPattern::ToJsonSelectedOptionFontAndColor.
 * @tc.type: FUNC
 */
HWTEST_F(SelectPatternOneTestControlSizeNg, ToJsonSelectedOptionFontAndColor002, TestSize.Level1)
{
    const std::string fontKey = "selectedOptionFont";
    const std::string fontColorKey = "selectedOptionFontColor";

    auto select = AceType::MakeRefPtr<FrameNode>(V2::SELECT_ETS_TAG, 1, AceType::MakeRefPtr<SelectPattern>());
    ASSERT_NE(select, nullptr);
    EXPECT_TRUE(select->GetTag() == V2::SELECT_ETS_TAG);
    auto pattern = select->GetPattern<SelectPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetSelectedOptionFontFamily(FONT_FAMILY_VALUE);
    pattern->frameNode_ = AceType::WeakClaim(AceType::RawPtr(select));
    pattern->text_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_EQ(pattern->textSelectOptionApply_, nullptr);
    EXPECT_TRUE(pattern->options_.empty());

    /**
     * @tc.steps: step1. Test pattern->options_ is empty.
     * @tc.expected: set value.
     */
    InspectorFilter filter;
    pattern->textSelectOptionApply_ = [](WeakPtr<FrameNode> weakNode) {};
    auto jsonValue = JsonUtil::Create(true);
    ASSERT_NE(jsonValue, nullptr);
    pattern->ToJsonSelectedOptionFontAndColor(jsonValue, filter);
    EXPECT_TRUE(jsonValue->Contains(fontKey));
    EXPECT_TRUE(jsonValue->Contains(fontColorKey));

    /**
     * @tc.steps: step2. Test pattern->options_ is not empty.
     * @tc.expected: set value.
     */
    auto option = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    ASSERT_NE(option, nullptr);
    pattern->options_.push_back(option);
    pattern->menuWrapper_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    jsonValue = JsonUtil::Create(true);
    ASSERT_NE(jsonValue, nullptr);
    pattern->selected_ = pattern->options_.size() + 1; // large then pattern->options_.size
    pattern->ToJsonSelectedOptionFontAndColor(jsonValue, filter);
    EXPECT_TRUE(jsonValue->Contains(fontKey));
    EXPECT_TRUE(jsonValue->Contains(fontColorKey));

    /**
     * @tc.steps: step3. Test pattern->options_ is not empty.
     * @tc.expected: set value.
     */
    jsonValue = JsonUtil::Create(true);
    ASSERT_NE(jsonValue, nullptr);
    pattern->selected_ = 0;
    pattern->ToJsonSelectedOptionFontAndColor(jsonValue, filter);
    EXPECT_TRUE(jsonValue->Contains(fontKey));
    EXPECT_TRUE(jsonValue->Contains(fontColorKey));
}
} // namespace OHOS::Ace::NG
