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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "test/unittest/core/pattern/text/text_base.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/pattern/image/image_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const CaretStyle DEFAULT_CARET_STYLE = { Dimension(3, DimensionUnit::VP) };
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextFieldTestNgFive : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void GetFocus();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};

void TextFieldTestNgFive::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ExpectCallParagraphMethods(ExpectParagraphParams());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    textFieldTheme->iconSize_ = Dimension(ICON_SIZE, DimensionUnit::VP);
    textFieldTheme->iconHotZoneSize_ = Dimension(ICON_HOT_ZONE_SIZE, DimensionUnit::VP);
    textFieldTheme->fontSize_ = Dimension(FONT_SIZE, DimensionUnit::FP);
    textFieldTheme->fontWeight_ = FontWeight::W400;
    textFieldTheme->textColor_ = Color::FromString("#ff182431");
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type, int id) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(MIN_PLATFORM_VERSION);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextFieldTestNgFive::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextFieldTestNgFive::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextFieldTestNgFive::ExpectCallParagraphMethods(ExpectParagraphParams params)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(params.height));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(params.longestLine));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(params.lineCount));
}

void TextFieldTestNgFive::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
}

void TextFieldTestNgFive::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
    if (callback) {
        callback(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    eventHub_ = frameNode_->GetEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextFieldTestNgFive::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: testFieldModelStatic011
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic011, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLineBreakStrategy(frameNode, std::make_optional(LineBreakStrategy::BALANCED));
    EXPECT_EQ(layoutProperty->GetLineBreakStrategy().value(), LineBreakStrategy::BALANCED);

    TextFieldModelStatic::SetLineBreakStrategy(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineBreakStrategy().has_value());
}

/**
 * @tc.name: testFieldModelStatic012
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic012, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    TextFieldModelStatic::SetInputStyle(frameNode, std::make_optional(InputStyle::DEFAULT));
    frameNode->MarkModifyDone();
    EXPECT_EQ(textPaintProperty->GetInputStyle().value(), InputStyle::DEFAULT);

    TextFieldModelStatic::SetInputStyle(frameNode, std::nullopt);
    EXPECT_FALSE(textPaintProperty->GetInputStyle().has_value());
}

/**
 * @tc.name: testFieldModelStatic013
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic013, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetBarState(frameNode, std::make_optional(DisplayMode::ON));
    frameNode->MarkModifyDone();
    EXPECT_EQ(layoutProperty->GetDisplayMode().value(), DisplayMode::ON);

    TextFieldModelStatic::SetBarState(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetDisplayMode().has_value());
}

/**
 * @tc.name: testFieldModelStatic014
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic014, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextFieldPlaceHolder(frameNode, std::make_optional(u"placeholder"));
    EXPECT_EQ(layoutProperty->GetPlaceholder().value(), u"placeholder");

    TextFieldModelStatic::SetTextFieldPlaceHolder(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholder().has_value());
}

/**
 * @tc.name: testFieldModelStatic015
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic015, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetMaxViewLines(frameNode, std::make_optional(5));
    EXPECT_EQ(layoutProperty->GetMaxViewLines().value(), 5);
}

/**
 * @tc.name: testFieldModelStatic016
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic016, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetNormalMaxViewLines(frameNode, std::make_optional(10));
    EXPECT_EQ(layoutProperty->GetNormalMaxViewLines().value(), 10);
}

/**
 * @tc.name: testFieldModelStatic017
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic017, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTextInputType(TextInputType::UNSPECIFIED);
    TextFieldModelStatic::SetType(frameNode, std::make_optional(TextInputType::UNSPECIFIED));
    EXPECT_EQ(layoutProperty->GetTextInputType().value(), TextInputType::UNSPECIFIED);

    TextFieldModelStatic::SetType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextInputType().has_value());
}

/**
 * @tc.name: testFieldModelStatic018
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic018, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetContentType(frameNode, std::make_optional(TextContentType::USER_NAME));
    EXPECT_EQ(layoutProperty->GetTextContentType().value(), TextContentType::USER_NAME);

    TextFieldModelStatic::SetContentType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextContentType().has_value());
}

/**
 * @tc.name: testFieldModelStatic019
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic019, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    Font font;
    font.fontSize = Dimension(2);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, std::make_optional(font));
    EXPECT_EQ(layoutProperty->GetPlaceholderFontSizeValue(Dimension(0)), Dimension(2));

    TextFieldModelStatic::SetPlaceholderFont(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholderFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic020
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic020, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetShowPassword(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetShowPasswordText().value(), false);

    TextFieldModelStatic::SetShowPassword(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetShowPasswordText().has_value());
}

/**
 * @tc.name: testFieldModelStatic021
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic021, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextAlign(frameNode, std::make_optional(TextAlign::RIGHT));
    EXPECT_EQ(layoutProperty->GetTextAlign().value(), TextAlign::RIGHT);

    TextFieldModelStatic::SetTextAlign(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextAlign().has_value());
}

/**
 * @tc.name: testFieldModelStatic022
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic022, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextColor(frameNode, std::make_optional(Color::BLACK));
    EXPECT_EQ(layoutProperty->GetTextColor().value(), Color::BLACK);

    TextFieldModelStatic::SetTextColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextColor().has_value());
}

/**
 * @tc.name: testFieldModelStatic023
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic023, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontStyle(frameNode, std::make_optional(Ace::FontStyle::NORMAL));
    EXPECT_EQ(layoutProperty->GetItalicFontStyle().value(), Ace::FontStyle::NORMAL);

    TextFieldModelStatic::SetFontStyle(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: testFieldModelStatic024
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic024, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontSize(frameNode, std::make_optional(Dimension(20)));
    EXPECT_EQ(layoutProperty->GetFontSize().value(), Dimension(20));

    TextFieldModelStatic::SetFontSize(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());
}

/**
 * @tc.name: testFieldModelStatic025
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic025, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    TextFieldModelStatic::SetCaretStyle(frameNode, std::make_optional(DEFAULT_CARET_STYLE));
    EXPECT_EQ(textPaintProperty->GetCursorWidth().value(), DEFAULT_CARET_STYLE.caretWidth.value());

    TextFieldModelStatic::SetCaretStyle(frameNode, std::nullopt);
    EXPECT_FALSE(textPaintProperty->GetCursorWidth().has_value());
}

/**
 * @tc.name: testFieldModelStatic026
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic026, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, std::make_optional(Color::GRAY));
    EXPECT_EQ(layoutProperty->GetPlaceholderTextColor().value(), Color::GRAY);

    TextFieldModelStatic::SetPlaceholderColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPlaceholderTextColor().has_value());
}

/**
 * @tc.name: testFieldModelStatic027
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic027, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetFontWeight(frameNode, std::make_optional(FontWeight::W500));
    EXPECT_EQ(layoutProperty->GetFontWeight().value(), FontWeight::W500);

    TextFieldModelStatic::SetFontWeight(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetFontWeight().has_value());
}

/**
 * @tc.name: testFieldModelStatic028
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic028, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetPasswordRules(frameNode, std::make_optional("passwordRules"));
    EXPECT_EQ(layoutProperty->GetPasswordRules().value(), "passwordRules");

    TextFieldModelStatic::SetPasswordRules(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetPasswordRules().has_value());

    auto textFieldPattern = frameNode->GetPattern<TextFieldPattern>();

    NG::OnCreateMenuCallback onCreate = [](const std::vector<NG::MenuItemParam>&) -> std::vector<MenuOptionsParam> {
        std::vector<NG::MenuOptionsParam> menuParams;
        return menuParams;
    };
    NG::OnMenuItemClickCallback onMenuItemClick = [](const NG::MenuItemParam&) -> bool { return false; };
    TextFieldModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreate), std::move(onMenuItemClick));
    EXPECT_NE(textFieldPattern->selectOverlay_->onCreateMenuCallback_, nullptr);
    EXPECT_NE(textFieldPattern->selectOverlay_->onMenuItemClick_, nullptr);
}

/**
 * @tc.name: testFieldModelStatic029
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic029, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetShowError(frameNode, std::make_optional(u"error"), true);
    EXPECT_EQ(layoutProperty->GetShowErrorText().value(), true);

    TextFieldModelStatic::SetShowError(frameNode, std::nullopt, false);
    EXPECT_FALSE(layoutProperty->GetShowErrorText().has_value());

    std::function<RefPtr<UINode>()> nullfunc;
    auto builder = []() -> RefPtr<UINode> {
        RefPtr<UINode> uiNode;
        return uiNode;
    };
    TextFieldModelStatic::SetShowUnit(frameNode, std::move(nullfunc));
    TextFieldModelStatic::SetShowUnit(frameNode, std::move(builder));

    RefPtr<TextFieldPattern> pattern = frameNode->GetPattern<TextFieldPattern>();
    TextFieldModelStatic::GetController(frameNode, std::make_optional(u"placeholder"), std::make_optional(u"value"));
    EXPECT_TRUE(layoutProperty->GetPlaceholder().has_value());
    EXPECT_EQ(pattern->isTextChangedAtCreation_, true);
}

/**
 * @tc.name: testFieldModelStatic030
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic030, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCounterType(frameNode, std::make_optional(10));
    EXPECT_EQ(layoutProperty->GetSetCounter().value(), 10);

    TextFieldModelStatic::SetCounterType(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetSetCounter().has_value());

    TextFieldModelStatic::SetShowCounterBorder(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetShowHighlightBorder().value(), true);
    TextFieldModelStatic::SetShowCounterBorder(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowHighlightBorder().value(), true);
}

/**
 * @tc.name: testFieldModelStatic031
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic031, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCancelIconSize(frameNode, std::make_optional(Dimension(24, DimensionUnit::PX)));
    EXPECT_EQ(layoutProperty->GetIconSize().value(), Dimension(24));

    TextFieldModelStatic::SetCancelIconSize(frameNode, std::nullopt);
    EXPECT_TRUE(layoutProperty->GetIconSize().has_value());

    TextFieldModelStatic::SetSelectAllValue(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetSelectAllValue().value(), true);
    TextFieldModelStatic::SetSelectAllValue(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetSelectAllValue().value(), false);
}

/**
 * @tc.name: testFieldModelStatic032
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic032, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    std::string bundleName = "com.example.test";
    std::string moduleName = "entry";
    TextFieldModelStatic::SetCanacelIconSrc(frameNode, "src", bundleName, moduleName);
    EXPECT_EQ(layoutProperty->GetIconSrc().value(), "src");

    TextFieldModelStatic::SetShowUnderline(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetShowUnderline().value(), true);
    TextFieldModelStatic::SetShowUnderline(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowUnderline().value(), false);
}

/**
 * @tc.name: testFieldModelStatic033
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic033, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetCancelIconColor(frameNode, std::make_optional(Color::GRAY));
    EXPECT_EQ(layoutProperty->GetIconColor().value(), Color::GRAY);

    TextFieldModelStatic::SetCancelIconColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetIconColor().has_value());

    std::optional<float> minFontScale = 1.f;
    TextFieldModelStatic::SetMinFontScale(frameNode, minFontScale);
    EXPECT_EQ(layoutProperty->GetMinFontScale().value(), minFontScale);
    TextFieldModelStatic::SetMinFontScale(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMinFontScale().has_value());

    std::optional<float> maxFontScale = 50.f;
    TextFieldModelStatic::SetMaxFontScale(frameNode, maxFontScale);
    EXPECT_EQ(layoutProperty->GetMaxFontScale().value(), maxFontScale);
    TextFieldModelStatic::SetMaxFontScale(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetMaxFontScale().has_value());
}

/**
 * @tc.name: testFieldModelStatic034
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic034, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecoration(frameNode, std::make_optional(TextDecoration::UNDERLINE));
    EXPECT_EQ(layoutProperty->GetTextDecorationFirst(), TextDecoration::UNDERLINE);

    TextFieldModelStatic::SetTextDecoration(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecoration().has_value());

    TextFieldModelStatic::SetEllipsisMode(frameNode, std::make_optional(EllipsisMode::MIDDLE));
    EXPECT_EQ(layoutProperty->GetEllipsisMode().value(), EllipsisMode::MIDDLE);
    TextFieldModelStatic::SetEllipsisMode(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetEllipsisMode().has_value());

    TextFieldModelStatic::SetHalfLeading(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetHalfLeading().value(), false);
    TextFieldModelStatic::SetHalfLeading(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetHalfLeading().has_value());
}

/**
 * @tc.name: testFieldModelStatic035
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic035, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecorationColor(frameNode, std::make_optional(Color::BLUE));
    EXPECT_EQ(layoutProperty->GetTextDecorationColor().value(), Color::BLUE);

    TextFieldModelStatic::SetTextDecorationColor(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationColor().has_value());

    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->GetEnableHapticFeedback(), false);
    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->GetEnableHapticFeedback(), true);

    TextFieldModelStatic::SetEnableAutoFill(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetEnableAutoFill(), false);
    TextFieldModelStatic::SetEnableAutoFill(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetEnableAutoFill(), true);
}

/**
 * @tc.name: testFieldModelStatic036
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic036, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetTextDecorationStyle(frameNode, std::make_optional(TextDecorationStyle::DOTTED));
    EXPECT_EQ(layoutProperty->GetTextDecorationStyle().value(), TextDecorationStyle::DOTTED);

    TextFieldModelStatic::SetTextDecorationStyle(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetTextDecorationStyle().has_value());

    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, std::make_optional(true));
    EXPECT_EQ(layoutProperty->GetSelectionMenuHidden(), true);
    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetSelectionMenuHidden(), false);

    TextFieldModelStatic::SetEnablePreviewText(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->GetSupportPreviewText(), false);
    TextFieldModelStatic::SetEnablePreviewText(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->GetSupportPreviewText(), true);
}

/**
 * @tc.name: testFieldModelStatic037
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic037, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextFieldLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    TextFieldModelStatic::SetLineHeight(frameNode, std::make_optional(Dimension(10)));
    EXPECT_EQ(layoutProperty->GetLineHeight().value(), Dimension(10));

    TextFieldModelStatic::SetLineHeight(frameNode, std::nullopt);
    EXPECT_FALSE(layoutProperty->GetLineHeight().has_value());
    TextFieldModelStatic::SetStopBackPress(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetStopBackPress().value(), false);

    TextFieldModelStatic::SetStopBackPress(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetStopBackPress().value(), true);

    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, std::make_optional(false));
    RefPtr<TextFieldPattern> textFieldPattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_EQ(textFieldPattern->NeedToRequestKeyboardOnFocus(), false);
    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, std::nullopt);
    EXPECT_EQ(textFieldPattern->NeedToRequestKeyboardOnFocus(), true);

    TextFieldModelStatic::SetShowPasswordIcon(frameNode, std::make_optional(false));
    EXPECT_EQ(layoutProperty->GetShowPasswordIcon().value(), false);
    TextFieldModelStatic::SetShowPasswordIcon(frameNode, std::nullopt);
    EXPECT_EQ(layoutProperty->GetShowPasswordIcon().value(), true);
}

/**
 * @tc.name: testFieldModelStatic038
 * @tc.desc: test testInput ModelStatic
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, testFieldModelStatic038, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto textPaintProperty = frameNode->GetPaintProperty<TextFieldPaintProperty>();
    EXPECT_NE(textPaintProperty, nullptr);
    TextFieldModelStatic::SetSelectedBackgroundColor(frameNode, std::make_optional(Color::GRAY));
    EXPECT_NE(textPaintProperty->GetSelectedBackgroundColor().value(), Color::GRAY);

    TextFieldModelStatic::SetSelectedBackgroundColor(frameNode, std::nullopt);
    EXPECT_FALSE(textPaintProperty->GetSelectedBackgroundColor().has_value());
}

/**
 * @tc.name: SetCapitalizationMode001
 * @tc.desc: test search set CapitalizationMode default value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetCapitalizationMode001, TestSize.Level1)
{
    TextFieldModelNG textFieldModelNG;
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextFieldPattern>();
    EXPECT_NE(pattern, nullptr);

    textFieldModelNG.SetCapitalizationMode(AutoCapitalizationMode::NONE);
    EXPECT_EQ(AutoCapitalizationMode::NONE, pattern->GetAutoCapitalizationMode());

    textFieldModelNG.SetAutoCapitalizationMode(frameNode, AutoCapitalizationMode::WORDS);
    EXPECT_EQ(AutoCapitalizationMode::WORDS, pattern->GetAutoCapitalizationMode());
}

/**
 * @tc.name: SetExtraConfig
 * @tc.desc: test pass extra config to ime.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetExtraConfig, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create Text filed node
     */
    struct ExtraConfig {
        std::string key;
        std::string value;
    };
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        IMEAttachCallback attach = [](IMEClient& client) {
            ExtraConfig* extraConfig = new ExtraConfig();
            extraConfig->key = "name";
            extraConfig->value = "test";
            client.extraInfo = AceType::MakeRefPtr<IMEExtraInfo>(extraConfig, [extraConfig]() {
                delete extraConfig;
            });
        };
        model.SetOnWillAttachIME(std::move(attach));
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.step: step2. Call FireOnWillAttachIME
     */
    auto clientInfo = pattern_->GetIMEClientInfo();
    pattern_->FireOnWillAttachIME(clientInfo);
    ASSERT_NE(clientInfo.extraInfo, nullptr);
    ASSERT_NE(clientInfo.extraInfo->GetExtraInfo(), nullptr);
    auto parsedConfig = *reinterpret_cast<ExtraConfig*>(clientInfo.extraInfo->GetExtraInfo());
    EXPECT_EQ(parsedConfig.key, "name");
    EXPECT_EQ(parsedConfig.value, "test");
}

} // namespace OHOS::Ace::NG