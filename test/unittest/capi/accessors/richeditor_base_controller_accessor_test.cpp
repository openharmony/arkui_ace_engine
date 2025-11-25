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
#include <gmock/gmock.h>

#include "richeditor_accessor_test.h"
#include "accessor_test_base.h"

#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/interfaces/native/implementation/rich_editor_base_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace {
bool operator==(const std::optional<OHOS::Ace::SelectionOptions>& lhs,
                const std::optional<OHOS::Ace::SelectionOptions>& rhs)
{
    if (!lhs.has_value() || !rhs.has_value()) {
        return false;
    }
    return lhs->menuPolicy == rhs->menuPolicy;
}
bool operator==(const std::optional<OHOS::Ace::UpdateSpanStyle>& lhs,
                const std::optional<OHOS::Ace::UpdateSpanStyle>& rhs)
{
    if (!lhs.has_value() || !rhs.has_value()) {
        return false;
    }
    bool textColorEq = lhs->updateTextColor && rhs->updateTextColor &&
        lhs->updateTextColor.value() == rhs->updateTextColor.value();
    bool fontSizeEq = lhs->updateFontSize && rhs->updateFontSize &&
        lhs->updateFontSize.value() == rhs->updateFontSize.value();
    bool italicFontStyleEq = lhs->updateItalicFontStyle && rhs->updateItalicFontStyle &&
        lhs->updateItalicFontStyle.value() == rhs->updateItalicFontStyle.value();
    bool fontWeightEq = lhs->updateFontWeight && rhs->updateFontWeight &&
        lhs->updateFontWeight.value() == rhs->updateFontWeight.value();
    return textColorEq && fontSizeEq && italicFontStyleEq && fontWeightEq;
}
} // OHOS::Ace

static constexpr int32_t TEST_IDX = 0;
static constexpr int32_t TEST_IDX_2 = 10;
static constexpr int32_t TEST_START = 1;
static constexpr int32_t TEST_END = 3;
static const std::vector<std::string> FONT_FAMILIES = { "serif" };
static constexpr double FONT_SIZE = 10.0;
static constexpr OHOS::Ace::FontWeight FONT_WEIGHT = OHOS::Ace::FontWeight::NORMAL;
static constexpr OHOS::Ace::FontStyle FONT_STYLE = OHOS::Ace::FontStyle::NORMAL;
static constexpr auto TEXT_DECOR = OHOS::Ace::TextDecoration::UNDERLINE;
static constexpr auto TEXT_DECOR_STYLE = OHOS::Ace::TextDecorationStyle::DOTTED;
static const auto FONT_COLOR = OHOS::Ace::Color::RED;
static constexpr int32_t TEST_SHADOW_COUNT = 2;
namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
template<>
void AssignCast(std::optional<RectF>& dst, const Ark_RectResult& src)
{
    dst = RectF(
        Converter::Convert<float>(src.x),
        Converter::Convert<float>(src.y),
        Converter::Convert<float>(src.width),
        Converter::Convert<float>(src.height)
    );
}
}

UpdateSpanStyle GetUpdateSpanStyle()
{
    UpdateSpanStyle ret;
    ret.updateTextColor = FONT_COLOR;
    ret.updateFontSize = FONT_SIZE;
    ret.updateItalicFontStyle = FONT_STYLE;
    ret.updateFontWeight = FONT_WEIGHT;
    ret.updateFontFamily= FONT_FAMILIES;
    ret.isInitDecoration = true;
    ret.updateTextDecoration = TEXT_DECOR;
    ret.updateTextDecorationColor = FONT_COLOR;
    ret.updateTextDecorationStyle = TEXT_DECOR_STYLE;
    std::vector<Shadow> shadowVec;
    shadowVec.push_back(Shadow());
    shadowVec.push_back(Shadow(FONT_SIZE, Offset(FONT_SIZE, FONT_SIZE), FONT_COLOR, ShadowStyle::OuterDefaultXS));
    ret.updateTextShadows = shadowVec;
    ret.updateLineHeight = CalcDimension(FONT_SIZE);
    ret.updateLetterSpacing = CalcDimension(FONT_SIZE);
    return ret;
}

void CheckRichEditorTextStyle(Ark_RichEditorTextStyle &style)
{
    auto valOptFontSize = Converter::OptConvert<Dimension>(style.fontSize);
    ASSERT_EQ(valOptFontSize.value_or(Dimension()).Value(), FONT_SIZE);
    auto valOptColor = Converter::OptConvert<Color>(style.fontColor);
    ASSERT_EQ(valOptColor.value_or(Color::TRANSPARENT), FONT_COLOR);
    auto valOptFontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(style.fontStyle);
    ASSERT_EQ(valOptFontStyle.value_or(OHOS::Ace::FontStyle::NONE), FONT_STYLE);
    auto valOptFontWeight = Converter::OptConvert<OHOS::Ace::FontWeight>(style.fontWeight);
    ASSERT_EQ(valOptFontWeight.value_or(OHOS::Ace::FontWeight::W100), FONT_WEIGHT);
    auto valOptFontFamily = Converter::OptConvert<std::string>(style.fontFamily);
    ASSERT_EQ(valOptFontFamily.value_or(""), FONT_FAMILIES[0]);

    auto arkDecor = Converter::OptConvert<Ark_DecorationStyleInterface>(style.decoration);
    ASSERT_NE(arkDecor, std::nullopt);
    valOptColor = Converter::OptConvert<Color>(arkDecor->color);
    ASSERT_EQ(valOptColor.value_or(Color::TRANSPARENT), FONT_COLOR);

    auto valDecType = Converter::OptConvert<OHOS::Ace::TextDecoration>(arkDecor->type);
    ASSERT_EQ(valDecType, TEXT_DECOR);
    auto valOptDecStyle = Converter::OptConvert<OHOS::Ace::TextDecorationStyle>(arkDecor->style);
    ASSERT_EQ(valOptDecStyle.value_or(OHOS::Ace::TextDecorationStyle::SOLID), TEXT_DECOR_STYLE);
    auto shadowsOpt = Converter::OptConvert<std::vector<Shadow>>(style.textShadow);
    ASSERT_NE(shadowsOpt, std::nullopt);
    ASSERT_EQ(shadowsOpt->size(), TEST_SHADOW_COUNT);
    valOptFontSize = Converter::OptConvert<Dimension>(style.lineHeight);
    ASSERT_EQ(valOptFontSize.value_or(Dimension()).Value(), FONT_SIZE);
    valOptFontSize = Converter::OptConvert<Dimension>(style.letterSpacing);
    ASSERT_EQ(valOptFontSize.value_or(Dimension()).Value(), FONT_SIZE);
}

namespace {
class MockRichEditorBaseController : public RichEditorBaseController {
public:
    MockRichEditorBaseController() = default;
    ~MockRichEditorBaseController() override = default;
    MOCK_METHOD(RectF, GetCaretRect, ());
    MOCK_METHOD(int32_t, GetCaretOffset, ());
    MOCK_METHOD(bool, SetCaretOffset, (int32_t));
    MOCK_METHOD(void, CloseSelectionMenu, ());
    MOCK_METHOD(bool, IsEditing, ());
    MOCK_METHOD(void, StopEditing, ());
    MOCK_METHOD(void, SetSelection, (int32_t, int32_t, const std::optional<SelectionOptions>&, bool));
    MOCK_METHOD(void, SetTypingStyle, (std::optional<UpdateSpanStyle>, std::optional<TextStyle>));
    MOCK_METHOD(const PreviewTextInfo, GetPreviewTextInfo, (), (const));
    MOCK_METHOD(WeakPtr<LayoutInfoInterface>, GetLayoutInfoInterface, ());
};

class TestRichEditorBaseController2 : public RichEditorBaseController {
    public:
    void SetTypingStyle(std::optional<UpdateSpanStyle> style, std::optional<TextStyle> textStyle) override
    {
        style_ = style;
        textStyle_ = textStyle;
    }
    std::optional<UpdateSpanStyle> GetTypingStyle() override
    {
        return style_;
    }
    std::optional<UpdateSpanStyle> style_;
    std::optional<TextStyle> textStyle_;
};
} // namespace

class RichEditorBaseControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIRichEditorBaseControllerAccessor,
    &GENERATED_ArkUIAccessors::getRichEditorBaseControllerAccessor, RichEditorBaseControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();
        mockRichEditorController_ = new MockRichEditorBaseController();
        mockRichEditorControllerKeeper_ = AceType::Claim(mockRichEditorController_);
        ASSERT_NE(mockRichEditorControllerKeeper_, nullptr);
        peer_->AddTargetController(mockRichEditorControllerKeeper_);
    }

    void TearDown() override
    {
        mockRichEditorControllerKeeper_ = nullptr;
        mockRichEditorController_ = nullptr;
        controller2_ = nullptr;
        controllerKeeper2_ = nullptr;
    }

    void SetUp2()
    {
        controller2_ = new TestRichEditorBaseController2();
        controllerKeeper2_ = AceType::Claim(controller2_);
        ASSERT_NE(controllerKeeper2_, nullptr);
        peer_->AddTargetController(controllerKeeper2_);
    }

    MockRichEditorBaseController *mockRichEditorController_ = nullptr;
    RefPtr<MockRichEditorBaseController> mockRichEditorControllerKeeper_ = nullptr;
    TestRichEditorBaseController2 *controller2_ = nullptr;
    RefPtr<TestRichEditorBaseController2> controllerKeeper2_ = nullptr;
};

/**
 * @tc.name: getCaretOffsetTest
 * @tc.desc: Check the functionality of getCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, getCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);

    EXPECT_CALL(*mockRichEditorController_, GetCaretOffset()).Times(1);
    auto offsetResult = accessor_->getCaretOffset(peer_);
    auto idxOpt = Converter::OptConvert<int32_t>(offsetResult);
    ASSERT_TRUE(idxOpt.has_value());
    auto idx = idxOpt.value();
    ASSERT_EQ(idx, TEST_IDX);
}

/**
 * @tc.name: setCaretOffsetTest
 * @tc.desc: Check the functionality of setCaretOffset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setCaretOffsetTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretOffset, nullptr);

    EXPECT_CALL(*mockRichEditorController_, SetCaretOffset(TEST_IDX_2)).Times(1);
    auto offset = Converter::ArkValue<Ark_Int32>(TEST_IDX_2);
    auto setResult = accessor_->setCaretOffset(peer_, &offset);
    auto resultOpt = Converter::OptConvert<bool>(setResult);
    ASSERT_TRUE(resultOpt.has_value());
    bool result = resultOpt.value();
    ASSERT_FALSE(result);
}

/**
 * @tc.name: closeSelectionMenuTest
 * @tc.desc: Check the functionality of closeSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, closeSelectionMenuTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->closeSelectionMenu, nullptr);

    EXPECT_CALL(*mockRichEditorController_, CloseSelectionMenu()).Times(1);
    accessor_->closeSelectionMenu(peer_);
}

/**
 * @tc.name: isEditingTest
 * @tc.desc: Check the functionality of isEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, isEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->isEditing, nullptr);

    EXPECT_CALL(*mockRichEditorController_, IsEditing()).Times(1);
    auto isEditingResult = accessor_->isEditing(peer_);
    auto resultOpt = Converter::OptConvert<bool>(isEditingResult);
    ASSERT_TRUE(resultOpt.has_value());
    bool result = resultOpt.value();
    ASSERT_FALSE(result);
}

/**
 * @tc.name: stopEditingTest
 * @tc.desc: Check the functionality of stopEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, stopEditingTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->stopEditing, nullptr);

    EXPECT_CALL(*mockRichEditorController_, StopEditing()).Times(1);
    accessor_->stopEditing(peer_);
}

/**
 * @tc.name: setSelectionTest
 * @tc.desc: Check the functionality of setSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setSelection, nullptr);

    SelectionOptions opts;
    opts.menuPolicy = MenuPolicy::SHOW;
    std::optional<SelectionOptions> checkOpts = opts;
    EXPECT_CALL(*mockRichEditorController_, SetSelection(TEST_START, TEST_END, checkOpts, true)).Times(1);
    auto start = Converter::ArkValue<Ark_Int32>(TEST_START);
    auto end = Converter::ArkValue<Ark_Int32>(TEST_END);
    Opt_SelectionOptions optsOpt;
    optsOpt.value.menuPolicy.value = Ark_MenuPolicy::ARK_MENU_POLICY_SHOW;
    accessor_->setSelection(peer_, &start, &end, &optsOpt);
}

/**
 * @tc.name: setTypingStyleTest
 * @tc.desc: Check the functionality of setTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, setTypingStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->setTypingStyle, nullptr);
    std::optional<UpdateSpanStyle> spanStyle = UpdateSpanStyle();
    spanStyle->updateTextColor = FONT_COLOR;
    spanStyle->updateFontSize = CalcDimension(FONT_SIZE);
    spanStyle->updateItalicFontStyle = FONT_STYLE;
    spanStyle->updateFontWeight = FONT_WEIGHT;
    std::optional<TextStyle> textStyle = TextStyle(FONT_FAMILIES, FONT_SIZE, FONT_WEIGHT, FONT_STYLE, FONT_COLOR);
    EXPECT_CALL(*mockRichEditorController_, SetTypingStyle(spanStyle, textStyle)).Times(1);
    Converter::ConvContext ctx;
    auto value = Converter::ArkValue<Ark_RichEditorTextStyle>(*textStyle, &ctx);
    accessor_->setTypingStyle(peer_, &value);
}

/**
 * @tc.name: getTypingStyleTest
 * @tc.desc: Check the functionality of setTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, getTypingStyleTest, TestSize.Level1)
{
    SetUp2();
    ASSERT_NE(accessor_->getTypingStyle, nullptr);
    accessor_->getTypingStyle(peer_);
    controller2_->style_ = GetUpdateSpanStyle();
    auto result = accessor_->getTypingStyle(peer_);
#ifdef WRONG_GEN
    auto resultOpt = Converter::GetOpt(styleResult);
    ASSERT_TRUE(resultOpt.has_value());
    auto result = resultOpt.value();
#endif
    CheckRichEditorTextStyle(result);
}

/**
 * @tc.name: GetPreviewTextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, GetPreviewTextTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getPreviewText, nullptr);
    PreviewTextInfo previewText = {.offset = 1, .value = u"info"};
    EXPECT_CALL(*mockRichEditorController_, GetPreviewTextInfo()).Times(1).WillOnce(Return(previewText));
    accessor_->getPreviewText(peer_); // fix after updating a return value
    // check a return value
}

/**
 * @tc.name: GetLayoutManagerTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, GetLayoutManagerTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getLayoutManager, nullptr);
    auto layoutInfo = OHOS::Ace::NG::LayoutInfoInterface();
    EXPECT_CALL(*mockRichEditorController_,
        GetLayoutInfoInterface()).Times(1).WillOnce(Return(layoutInfo.GetLayoutInfoInterface()));
    auto manager = accessor_->getLayoutManager(peer_);
#ifdef WRONG_GEN
    auto managerOpt = Converter::GetOpt(layoutManager);
    ASSERT_TRUE(managerOpt.has_value());
    Ark_LayoutManager manager = managerOpt.value();
#endif
    ASSERT_NE(manager, nullptr);
}

/**
 * @tc.name: GetCaretRectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorBaseControllerAccessorTest, GetCaretRectTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getCaretRect, nullptr);
    auto rectF = OHOS::Ace::NG::RectF(0.45f, 1.37f, 53.3f, 657.6f);
    EXPECT_CALL(*mockRichEditorController_,
        GetCaretRect()).Times(1).WillOnce(Return(rectF));
    auto rectResult = accessor_->getCaretRect(peer_);
    auto rectOpt = Converter::OptConvert<RectF>(rectResult);
    ASSERT_TRUE(rectOpt.has_value());
    EXPECT_NEAR(rectOpt->GetOffset().GetX(), 0.45f, FLT_EPSILON);
    EXPECT_NEAR(rectOpt->GetOffset().GetY(), 1.37f, FLT_EPSILON);
    EXPECT_NEAR(rectOpt->Width(), 53.3f, FLT_EPSILON);
    EXPECT_NEAR(rectOpt->Height(), 657.6f, FLT_EPSILON);

    // invalid
    rectResult = accessor_->getCaretRect(nullptr);
    rectOpt = Converter::OptConvert<RectF>(rectResult);
    EXPECT_FALSE(rectOpt.has_value());

    // invalid
    rectF = OHOS::Ace::NG::RectF(0.45f, 1.37f, -53.3f, 657.6f);
    EXPECT_CALL(*mockRichEditorController_,
        GetCaretRect()).Times(1).WillOnce(Return(rectF));
    rectResult = accessor_->getCaretRect(peer_);
    rectOpt = Converter::OptConvert<RectF>(rectResult);
    EXPECT_FALSE(rectOpt.has_value());
}

} // namespace OHOS::Ace::NG
