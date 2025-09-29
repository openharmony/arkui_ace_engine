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
#include "test/unittest/core/pattern/text_input/mock/mock_text_field_select_overlay.h"

#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr double FONT_SIZE = 16;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
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
} // namespace

class TextAreaMenuTestNg : public TestNG {
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

void TextAreaMenuTestNg::SetUpTestSuite()
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

void TextAreaMenuTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextAreaMenuTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextAreaMenuTestNg::ExpectCallParagraphMethods(ExpectParagraphParams params)
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

void TextAreaMenuTestNg::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
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

void TextAreaMenuTestNg::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextArea(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
    if (callback) {
        callback(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    eventHub_ = frameNode_->GetOrCreateEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextAreaMenuTestNg::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: SelectTextShowMenu001
 * @tc.desc: Test default menu policy without setting any policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Test menu open or close
     * @tc.expected: text menu is close
     */
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Select text
     */
    SelectionOptions options;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step4. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu002
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::DEFAULT menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu003
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::HIDE menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu004
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: Text is selected and the menu pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step3. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: Text is selected and the menu pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SelectTextShowMenu005
 * @tc.desc: Test show menu after SetTextSelection() in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Set menuPolicy to be MenuPolicy::SHOW
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step4. Test menu open or close
     * @tc.expected: text menu is open
     */
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step5. Press esc
     */
    KeyEvent event;
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step6. Set menuPolicy to be MenuPolicy::HIDE
     */
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step7. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step8. Press esc
     */
    event.code = KeyCode::KEY_ESCAPE;
    pattern_->OnKeyEvent(event);

    /**
     * @tc.steps: step9. Set menuPolicy to be MenuPolicy::DEFAULT
     */
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step10. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu006
 * @tc.desc: Test default menu policy without setting any policy in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Test menu open or close
     * @tc.expected: text menu is close
     */
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step4. Select text
     */
    SelectionOptions options;
    pattern_->SetSelectionFlag(0, DEFAULT_TEXT.length(), options);

    /**
     * @tc.steps: step5. Test menu open or close
     * @tc.expected: text menu is close
     */
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu007
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::DEFAULT menu policy in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Set start = end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step4. Set start != end and menuPolicy as MenuPolicy::DEFAULT
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu008
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::HIDE menu policy in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Set start = end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);

    /**
     * @tc.steps: step4. Set start != end and menuPolicy as MenuPolicy::HIDE
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SelectTextShowMenu009
 * @tc.desc: Test SetSelectionFlag with setting MenuPolicy::SHOW menu policy in inline mode
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SelectTextShowMenu009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.steps: step3. Set start = end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: Text is selected and the menu pop up
     */
    auto start = 5;
    auto end = 5;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetCaretIndex(), 5);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Set start != end and menuPolicy as MenuPolicy::SHOW
     * @tc.expected: Text is selected and the menu pop up
     */
    GetFocus();
    end = 10;
    pattern_->SetSelectionFlag(start, end, options);
    EXPECT_EQ(pattern_->selectController_->GetFirstHandleInfo().index, 5);
    EXPECT_EQ(pattern_->selectController_->GetSecondHandleInfo().index, 5);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection001
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::DEFAULT menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection002
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: The menu still pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection003
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::HIDE menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection004
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::HIDE menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: The menu doesn't pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection005
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call SetTextSelection with no menu
     * @tc.expected: The menu pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection006
 * @tc.desc: Test SetTextSelection with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.step: step2. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step3. Call SetTextSelection with menu pop up
     * @tc.expected: Text is selected and the menu pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection007
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::DEFAULT menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection008
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.step: step3. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step4. Call SetTextSelection with menu pop up
     * @tc.expected: Text is selected and the menu still pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection009
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::HIDE menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection010
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::HIDE menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.step: step3. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step4. Call SetTextSelection with menu pop up
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: SetTextSelection011
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.step: step3. Call SetTextSelection with no menu
     * @tc.expected: Text is selected and the menu pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(start, end, options);
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: SetTextSelection012
 * @tc.desc: Test SetTextSelection in inline mode with setting MenuPolicy::SHOW menu policy
 * @tc.type: FUNC
 */
HWTEST_F(TextAreaMenuTestNg, SetTextSelection012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    CreateTextField(DEFAULT_TEXT);
    GetFocus();
    auto mockSelectOverlay = AceType::MakeRefPtr<MockTextFieldSelectOverlay>(pattern_);
    EXPECT_CALL(*mockSelectOverlay, GetSelectArea()).WillRepeatedly(Return(RectF(0, 0, 5, 5)));
    pattern_->selectOverlay_ = mockSelectOverlay;

    /**
     * @tc.steps: step2. Set InputStyle::INLINE mode
     */
    auto paintProperty = frameNode_->GetPaintProperty<TextFieldPaintProperty>();
    paintProperty->UpdateInputStyle(InputStyle::INLINE);
    frameNode_->MarkModifyDone();
    pattern_->OnModifyDone();

    /**
     * @tc.step: step3. Call HandleOnShowMenu
     * @tc.expected: The menu pop up
     */
    pattern_->HandleOnShowMenu();
    auto ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);

    /**
     * @tc.step: step4. Call SetTextSelection with menu pop up
     * @tc.expected: Text is selected and the menu pop up
     */
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    pattern_->textFieldController_->SetTextSelection(0, DEFAULT_TEXT.length(), options);
    ret = pattern_->selectOverlay_->IsCurrentMenuVisibile();
    EXPECT_TRUE(ret);
}
} // namespace OHOS::Ace::NG