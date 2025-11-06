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

#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/interfaces/native/implementation/rich_editor_controller_peer_impl.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"

#include "accessor_test_base.h"
#include "accessor_test_fixtures.h"
#include "accessor_test_utils.h"

namespace OHOS::Ace {
bool operator==(const TextSpanOptions& lhs, const TextSpanOptions& rhs)
{
    return lhs.offset.value() == rhs.offset.value();
}
bool operator==(const ImageSpanOptions& lhs, const ImageSpanOptions& rhs)
{
    return lhs.offset.value() == rhs.offset.value();
}
bool operator==(const SymbolSpanOptions& lhs, const SymbolSpanOptions& rhs)
{
    return lhs.offset.value() == rhs.offset.value();
}
bool operator==(const SpanOptionBase& lhs, const SpanOptionBase& rhs)
{
    return lhs.offset.value() == rhs.offset.value();
}

bool operator==(const UpdateParagraphStyle& lhs, const UpdateParagraphStyle& rhs)
{
    return lhs.textAlign.value() == rhs.textAlign.value() &&
        lhs.wordBreak.value() == rhs.wordBreak.value() &&
        lhs.lineBreakStrategy.value() == rhs.lineBreakStrategy.value();
}

bool operator==(const RangeOptions& lhs, const RangeOptions& rhs)
{
    return lhs.start.value() == rhs.start.value() && lhs.end.value() == rhs.end.value();
}
} // OHOS::Ace

static constexpr int TEST_OFFSET = 5;
static constexpr int TEST_START = 1;
static constexpr int TEST_END = 3;
static const std::u16string TEST_VALUE = u"test value";
static const std::vector<std::string> FONT_FAMILIES = { "Arial" };
static constexpr double FONT_SIZE = 12.0;
static constexpr OHOS::Ace::FontWeight FONT_WEIGHT = OHOS::Ace::FontWeight::BOLD;
static constexpr OHOS::Ace::FontStyle FONT_STYLE = OHOS::Ace::FontStyle::ITALIC;
static const OHOS::Ace::Color FONT_COLOUR = OHOS::Ace::Color::RED;
static constexpr int TEST_NODE_ID = 333;

namespace OHOS::Ace::NG {

using namespace OHOS::Ace::NG::TypeHelper;
using namespace testing;
using namespace testing::ext;

namespace Converter {
void AssignArkValue(Ark_RichEditorTextSpanOptions& dst, const OHOS::Ace::TextSpanOptions& src)
{
    dst.offset = Converter::ArkValue<Opt_Int32>(src.offset);
}
void AssignArkValue(Ark_RichEditorLayoutStyle& dst, const OHOS::Ace::ImageSpanAttribute& src)
{
    dst.margin = Converter::ArkUnion<Opt_Union_Dimension_Margin, Ark_Padding>(src.marginProp);
}
void AssignArkValue(Ark_RichEditorImageSpanStyle& dst, const OHOS::Ace::ImageSpanAttribute& src)
{
    dst.layoutStyle = Converter::ArkValue<Opt_RichEditorLayoutStyle>(src);
}
void AssignArkValue(Ark_RichEditorImageSpanOptions& dst, const OHOS::Ace::ImageSpanOptions& src)
{
    dst.offset = Converter::ArkValue<Opt_Int32>(src.offset);
    dst.imageStyle = Converter::ArkValue<Opt_RichEditorImageSpanStyle>(src.imageAttribute);
}
void AssignArkValue(Ark_RichEditorSymbolSpanOptions& dst, const OHOS::Ace::SymbolSpanOptions& src)
{
    dst.offset = Converter::ArkValue<Opt_Int32>(src.offset);
}
void AssignArkValue(Ark_RichEditorBuilderSpanOptions& dst, const OHOS::Ace::SpanOptionBase& src)
{
    dst.offset = Converter::ArkValue<Opt_Int32>(src.offset);
}

void AssignArkValue(Ark_RichEditorUpdateTextSpanStyleOptions& dst, const TextSpanOptionsForUpdate& src,
    Converter::ConvContext *ctx)
{
    dst.start = Converter::ArkValue<Opt_Int32>(src.start);
    dst.end = Converter::ArkValue<Opt_Int32>(src.end);
    if (src.textStyle) {
        dst.textStyle = Converter::ArkValue<Ark_RichEditorTextStyle>(src.textStyle.value(), ctx);
    }
}
void AssignArkValue(
    Ark_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions& dst,
    const TextSpanOptionsForUpdate& src, Converter::ConvContext *ctx)
{
    dst = Converter::ArkUnion<
        Ark_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions,
        Ark_RichEditorUpdateTextSpanStyleOptions>(src, ctx);
}

void AssignArkValue(Ark_DecorationStyleInterface& dst, const Converter::TextDecorationStruct& src,
                    Converter::ConvContext *ctx)
{
    dst.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(src.color, ctx);
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.style);
    dst.type = Converter::ArkValue<Opt_TextDecorationType>(src.textDecoration);
}

void AssignArkValue(Ark_RichEditorTextStyle& dst, const OHOS::Ace::TextStyle& style,
    Converter::ConvContext *ctx)
{
    dst.fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(style.GetTextColor(), ctx);
    dst.fontSize = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_String>(style.GetFontSize(), ctx);
    dst.fontStyle = Converter::ArkValue<Opt_FontStyle>(style.GetFontStyle());
    dst.fontWeight = Converter::ArkUnion<
        Opt_Union_I32_FontWeight_String, Ark_FontWeight>(style.GetFontWeight());

    auto families = style.GetFontFamilies();
    if (!families.empty()) {
        dst.fontFamily = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(families[0], ctx);
    }

    Converter::TextDecorationStruct decoration;
    decoration.color = style.GetTextDecorationColor();
    decoration.style = style.GetTextDecorationStyle();
    auto types = style.GetTextDecoration();
    ASSERT_GE(std::size(types), 1);
    decoration.textDecoration = types[0];
    dst.decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(decoration, ctx);

    dst.textShadow = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Ark_Empty>(nullptr);

    dst.letterSpacing = Converter::ArkUnion<Opt_Union_F64_String, Ark_Empty>(nullptr);

    dst.lineHeight = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr);

    dst.halfLeading = Converter::ArkValue<Opt_Boolean>();

    dst.fontFeature = Converter::ArkValue<Opt_String>();

    dst.textBackgroundStyle = Converter::ArkValue<Opt_TextBackgroundStyle>();
}

void AssignArkValue(Ark_RichEditorParagraphStyle& dst, const UpdateParagraphStyle& style)
{
    dst.textAlign = Converter::ArkValue<Opt_TextAlign>(style.textAlign);
    dst.wordBreak = Converter::ArkValue<Opt_WordBreak>(style.wordBreak);
    dst.lineBreakStrategy = Converter::ArkValue<Opt_LineBreakStrategy>(style.lineBreakStrategy);
}

void AssignArkValue(Ark_RichEditorParagraphStyleOptions& dst, const Converter::UpdateParagraphStyleForUpdate& style)
{
    dst.start = Converter::ArkValue<Opt_Int32>(style.start);
    dst.end = Converter::ArkValue<Opt_Int32>(style.end);
    dst.style = Converter::ArkValue<Ark_RichEditorParagraphStyle>(style.style.value());
}

void AssignArkValue(Ark_RichEditorRange& dst, const RangeOptions& src)
{
    dst.start = Converter::ArkValue<Opt_Int32>(src.start);
    dst.end = Converter::ArkValue<Opt_Int32>(src.end);
}
} // Converter

namespace {
class MockRichEditorController : public RichEditorController {
public:
    MockRichEditorController() = default;
    ~MockRichEditorController() override = default;
    MOCK_METHOD(int32_t, AddImageSpan, (const ImageSpanOptions&));
    MOCK_METHOD(int32_t, AddSymbolSpan, (const SymbolSpanOptions&));
    MOCK_METHOD(int32_t, AddPlaceholderSpan, (const RefPtr<UINode>&, const SpanOptionBase&));
    MOCK_METHOD(void, UpdateSpanStyle, (int32_t, int32_t, TextStyle, ImageSpanAttribute));
    MOCK_METHOD(void, UpdateParagraphStyle, (int32_t, int32_t, const struct UpdateParagraphStyle&));
    MOCK_METHOD(void, DeleteSpans, (const RangeOptions&));
    MOCK_METHOD(std::vector<ParagraphInfo>, GetParagraphsInfo, (int32_t start, int32_t end));
    MOCK_METHOD(RefPtr<SpanStringBase>, ToStyledString, (int32_t, int32_t));

    int32_t AddTextSpan(const TextSpanOptions& options) override
    {
        textSpanOptions_ = options;
        return 0;
    }

    TextSpanOptions textSpanOptions_;
};

Ark_RichEditorTextStyle GetEmptyTextStyle()
{
    Ark_RichEditorTextStyle style = {
        .fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr),
        .fontSize = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_Empty>(nullptr),
        .fontStyle = Converter::ArkValue<Opt_FontStyle>(),
        .fontWeight = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_Empty>(nullptr),
        .fontFamily = Converter::ArkUnion<Opt_ResourceStr, Ark_Empty>(nullptr),
        .decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(),
        .textShadow = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Ark_Empty>(nullptr),
        .letterSpacing = Converter::ArkUnion<Opt_Union_F64_String, Ark_Empty>(nullptr),
        .lineHeight = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Empty>(nullptr),
        .halfLeading = Converter::ArkValue<Opt_Boolean>(),
        .fontFeature = Converter::ArkValue<Opt_String>(),
        .textBackgroundStyle = Converter::ArkValue<Opt_TextBackgroundStyle>()
    };
    return style;
}
} // namespace

class RichEditorControllerAccessorTest : public AccessorTestBase<GENERATED_ArkUIRichEditorControllerAccessor,
    &GENERATED_ArkUIAccessors::getRichEditorControllerAccessor, RichEditorControllerPeer> {
public:
    void SetUp(void) override
    {
        AccessorTestBase::SetUp();

        mockRichEditorController_ = new MockRichEditorController();
        mockRichEditorControllerKeeper_ = AceType::Claim(mockRichEditorController_);
        ASSERT_NE(mockRichEditorControllerKeeper_, nullptr);

        auto peerImpl = reinterpret_cast<GeneratedModifier::RichEditorControllerPeerImpl *>(peer_);
        ASSERT_NE(peerImpl, nullptr);
        peerImpl->AddTargetController(mockRichEditorControllerKeeper_);

        ASSERT_NE(mockRichEditorController_, nullptr);

        SetupTheme<RichEditorTheme>();
    }

    void TearDown() override
    {
        mockRichEditorControllerKeeper_ = nullptr;
        mockRichEditorController_ = nullptr;
        richEditorPattern_ = nullptr;
        richEditorNode_ = nullptr;
    }

    RefPtr<RichEditorPattern> GetRichEditorPattern()
    {
        richEditorNode_ = FrameNode::GetOrCreateFrameNode(
            V2::RICH_EDITOR_ETS_TAG, TEST_NODE_ID, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
        CHECK_NULL_RETURN(richEditorNode_, nullptr);
        richEditorPattern_ = richEditorNode_->GetPattern<RichEditorPattern>();
        CHECK_NULL_RETURN(richEditorPattern_, nullptr);
        richEditorPattern_->SetRichEditorController(AceType::Claim(mockRichEditorController_));
        mockRichEditorController_->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern_)));
        return richEditorPattern_;
    }

    MockRichEditorController *mockRichEditorController_ = nullptr;
    RefPtr<MockRichEditorController> mockRichEditorControllerKeeper_ = nullptr;
    RefPtr<FrameNode> richEditorNode_ = nullptr;;
    RefPtr<RichEditorPattern> richEditorPattern_ = nullptr;
    Ark_VMContext vmContext_ = nullptr;
};

/**
 * @tc.name: addTextSpanTest
 * @tc.desc: Check the functionality of addTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addTextSpan, nullptr);

    TextSpanOptions textSpanOptions;
    textSpanOptions.offset = TEST_OFFSET;
    textSpanOptions.value = TEST_VALUE;
    Converter::ConvContext ctx;
    auto value = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(TEST_VALUE, &ctx);
    auto options = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    Opt_Int32 addResult = accessor_->addTextSpan(peer_, &value, &options);
    auto resultOpt = Converter::OptConvert<Ark_Int32>(addResult);
    ASSERT_TRUE(resultOpt.has_value());
    Ark_Int32 code = resultOpt.value();
    EXPECT_NE(code, 1);
    const TextSpanOptions& result = mockRichEditorController_->textSpanOptions_;
    ASSERT_TRUE(result.offset);
    EXPECT_EQ(result.offset.value(), TEST_OFFSET);

    EXPECT_EQ(result.value, TEST_VALUE);
}

/**
 * @tc.name: addSymbolSpanTest
 * @tc.desc: Check the functionality of addSymbolSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addSymbolSpanTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addSymbolSpan, nullptr);

    SymbolSpanOptions symbolSpanOptions;
    symbolSpanOptions.offset = TEST_OFFSET;

    std::string text = "S";
    std::string resName = "app.string.symbol";
    Ark_Resource value = CreateResource(resName.c_str(), ResourceType::INTEGER);
    AddResource(resName, text);

    auto options = Converter::ArkValue<Opt_RichEditorSymbolSpanOptions>(symbolSpanOptions);

    EXPECT_CALL(*mockRichEditorController_, AddSymbolSpan(symbolSpanOptions)).Times(1);
    accessor_->addSymbolSpan(peer_, &value, &options);
}

/**
 * @tc.name: addBuilderSpanTest
 * @tc.desc: Check the functionality of addBuilderSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, AddBuilderSpanTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->addBuilderSpan, nullptr);

    SpanOptionBase spanOptions = {.offset = TEST_OFFSET};
    auto options = Converter::ArkValue<Opt_RichEditorBuilderSpanOptions>(spanOptions);
    auto nodeId = 123;
    // Creating custom node
    auto customSpanNode = SpanNode::GetOrCreateSpanNode(nodeId);
    auto customUI_Node = static_cast<RefPtr<UINode>>(customSpanNode);
    auto customNodeHandle = reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(customSpanNode));
    // Creating custom node builder with helper and customNodeHandle
    int callsCount = 0;
    CustomNodeBuilderTestHelper<RichEditorControllerAccessorTest> builderHelper(this, nullptr, customNodeHandle);
    const auto builder = builderHelper.GetBuilder();
    // Testing custom node builder
    EXPECT_CALL(*mockRichEditorController_, AddPlaceholderSpan(customUI_Node, spanOptions)).Times(1);
    accessor_->addBuilderSpan(peer_, &builder, &options);
    EXPECT_EQ(builderHelper.GetCallsCount(), ++callsCount);
}

/**
 * @tc.name: updateSpanStyleTest
 * @tc.desc: Check the functionality of updateSpanStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, updateSpanStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->updateSpanStyle, nullptr);
    Converter::TextSpanOptionsForUpdate updateOptions;
    updateOptions.start = TEST_START;
    updateOptions.end = TEST_END;
    updateOptions.textStyle = TextStyle(FONT_FAMILIES, FONT_SIZE, FONT_WEIGHT, FONT_STYLE, FONT_COLOUR);
    Converter::ConvContext ctx;
    auto value = Converter::ArkValue<
        Ark_Union_RichEditorUpdateTextSpanStyleOptions_RichEditorUpdateImageSpanStyleOptions_RichEditorUpdateSymbolSpanStyleOptions
        >(updateOptions, &ctx);

    EXPECT_CALL(*mockRichEditorController_, UpdateSpanStyle(
        updateOptions.start, updateOptions.end, updateOptions.textStyle.value(), updateOptions.imageSpanAttribute
    )).Times(1);
    accessor_->updateSpanStyle(peer_, &value);
}

/**
 * @tc.name: updateParagraphStyleTest
 * @tc.desc: Check the functionality of updateParagraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, updateParagraphStyleTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->updateParagraphStyle, nullptr);
    Converter::UpdateParagraphStyleForUpdate updateOptions;
    updateOptions.start = TEST_START;
    updateOptions.end = TEST_END;
    updateOptions.style = UpdateParagraphStyle();
    updateOptions.style->textAlign = TextAlign::END;
    updateOptions.style->wordBreak = WordBreak::BREAK_ALL;
    updateOptions.style->lineBreakStrategy = LineBreakStrategy::HIGH_QUALITY;
    auto value = Converter::ArkValue<Ark_RichEditorParagraphStyleOptions>(updateOptions);

    EXPECT_CALL(*mockRichEditorController_, UpdateParagraphStyle(
        updateOptions.start, updateOptions.end, updateOptions.style.value()
    )).Times(1);
    accessor_->updateParagraphStyle(peer_, &value);
}

/**
 * @tc.name: deleteSpansTest
 * @tc.desc: Check the functionality of deleteSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, deleteSpansTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->deleteSpans, nullptr);
    RangeOptions options;
    options.start = TEST_START;
    options.end = TEST_END;

    auto value = Converter::ArkValue<Opt_RichEditorRange>(options);
    EXPECT_CALL(*mockRichEditorController_, DeleteSpans(options)).Times(1);
    accessor_->deleteSpans(peer_, &value);
}

/**
 * @tc.name: getSpansTest
 * @tc.desc: Check the functionality of getSpans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, getSpansTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSpans, nullptr);
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    TextStyle style;
    style.SetFontFamilies(FONT_FAMILIES);
    style.SetFontSize(Dimension(FONT_SIZE));
    style.SetFontWeight(FONT_WEIGHT);
    style.SetFontStyle(FONT_STYLE);
    style.SetTextColor(FONT_COLOUR);

    TextSpanOptions textSpanOptions;
    textSpanOptions.value = TEST_VALUE;
    textSpanOptions.style = style;

    richEditorPattern->InsertValueByPaste(TEST_VALUE);
    richEditorPattern->AddTextSpan(textSpanOptions);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), TEST_VALUE.length() * 2);

    RangeOptions options;
    options.start = TEST_VALUE.length();
    options.end = TEST_VALUE.length() * 2;

    auto value = Converter::ArkValue<Opt_RichEditorRange>(options);
    Opt_Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult spansResult = accessor_->getSpans(peer_, &value);
    auto resultOpt = Converter::GetOpt(spansResult);
    ASSERT_TRUE(resultOpt.has_value());
    Array_Union_RichEditorImageSpanResult_RichEditorTextSpanResult spans = resultOpt.value();

    ASSERT_TRUE(spans.length == 1);
    auto spansVec =
        Converter::Convert<std::vector<Ark_Union_RichEditorImageSpanResult_RichEditorTextSpanResult>>(spans);
    auto result = spansVec.front();
    auto textStyle = result.value1.textStyle;
    auto fzize = Converter::Convert<double>(textStyle.fontSize);
    EXPECT_EQ(fzize, FONT_SIZE);
    auto fontFamily = Converter::Convert<std::string>(textStyle.fontFamily);
    EXPECT_EQ(fontFamily, FONT_FAMILIES[0]);
    auto fontWeight = Converter::Convert<int32_t>(textStyle.fontWeight);
    EXPECT_EQ(static_cast<OHOS::Ace::FontWeight>(fontWeight), FONT_WEIGHT);
    auto fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(textStyle.fontStyle);
    ASSERT_TRUE(fontStyle.has_value());
    EXPECT_EQ(fontStyle.value(), FONT_STYLE);
    auto fontColor = Converter::OptConvert<Color>(textStyle.fontColor);
    ASSERT_TRUE(fontColor.has_value());
    EXPECT_EQ(fontColor.value(), FONT_COLOUR);
}

/**
 * @tc.name: getParagraphsTest
 * @tc.desc: Check the functionality of getParagraphs
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, getParagraphsTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getParagraphs, nullptr);
    RangeOptions options;
    options.start = TEST_START;
    options.end = TEST_END;

    auto value = Converter::ArkValue<Opt_RichEditorRange>(options);
    EXPECT_CALL(*mockRichEditorController_, GetParagraphsInfo(TEST_START, TEST_END)).Times(1);
    accessor_->getParagraphs(peer_, &value);
}

/**
 * @tc.name: getSelectionTest
 * @tc.desc: Check the functionality of getSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, getSelectionTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->getSelection, nullptr);
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    TextStyle style;
    style.SetFontFamilies(FONT_FAMILIES);
    style.SetFontSize(Dimension(FONT_SIZE));
    style.SetFontWeight(FONT_WEIGHT);
    style.SetFontStyle(FONT_STYLE);
    style.SetTextColor(FONT_COLOUR);

    TextSpanOptions textSpanOptions;
    textSpanOptions.value = TEST_VALUE;
    textSpanOptions.style = style;

    richEditorPattern->InsertValueByPaste(TEST_VALUE);
    richEditorPattern->AddTextSpan(textSpanOptions);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), TEST_VALUE.length() * 2);

    Opt_RichEditorSelection selectionResult = accessor_->getSelection(peer_);
    auto resultOpt = Converter::GetOpt(selectionResult);
    ASSERT_TRUE(resultOpt.has_value());
    Ark_RichEditorSelection selection = resultOpt.value();
    EXPECT_EQ(Converter::Convert<int32_t>(selection.selection.value0), TEST_VALUE.length() * 2);
    EXPECT_EQ(Converter::Convert<int32_t>(selection.selection.value1), TEST_VALUE.length() * 2);

    auto spans = selection.spans;
    ASSERT_TRUE(spans.length == 1);
    auto spansVec =
        Converter::Convert<std::vector<Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult>>(spans);
    auto result = spansVec.front();
    auto textStyle = result.value0.textStyle;
    auto fzize = Converter::Convert<double>(textStyle.fontSize);
    EXPECT_EQ(fzize, FONT_SIZE);
    auto fontFamily = Converter::Convert<std::string>(textStyle.fontFamily);
    EXPECT_EQ(fontFamily, FONT_FAMILIES[0]);
    auto fontWeight = Converter::Convert<int32_t>(textStyle.fontWeight);
    EXPECT_EQ(static_cast<OHOS::Ace::FontWeight>(fontWeight), FONT_WEIGHT);
    auto fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(textStyle.fontStyle);
    ASSERT_TRUE(fontStyle.has_value());
    EXPECT_EQ(fontStyle.value(), FONT_STYLE);
    auto fontColor = Converter::OptConvert<Color>(textStyle.fontColor);
    ASSERT_TRUE(fontColor.has_value());
    EXPECT_EQ(fontColor.value(), FONT_COLOUR);
}

/**
 * @tc.name: fromStyledStringTest
 * @tc.desc: Check the functionality of fromStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, DISABLED_fromStyledStringTest, TestSize.Level1)
{
#ifdef WRONG_NEW_ACE
    ASSERT_NE(accessor_->fromStyledString, nullptr);
    auto richEditorPattern = GetRichEditorPattern();
    ASSERT_NE(richEditorPattern, nullptr);

    TextStyle style;
    style.SetFontSize(Dimension(FONT_SIZE));
    style.SetFontWeight(FONT_WEIGHT);
    style.SetFontStyle(FONT_STYLE);
    style.SetTextColor(FONT_COLOUR);

    UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE;
    updateSpanStyle.updateTextColor = FONT_COLOUR;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT;
    updateSpanStyle.updateItalicFontStyle = FONT_STYLE;

    auto spanString = richEditorPattern->CreateStyledStringByTextStyle(TEST_VALUE, updateSpanStyle, style);
    richEditorPattern->InsertSpanByBackData(spanString);
    EXPECT_EQ(richEditorPattern->GetTextContentLength(), TEST_VALUE.length());

    Ark_StyledString inValue = StyledStringPeer::Create(spanString);
    auto spans = accessor_->fromStyledString(peer_, inValue);
    ASSERT_TRUE(spans.length == 1);
    auto spansVec =
        Converter::Convert<std::vector<Ark_RichEditorSpan>>(spans);
    auto result = spansVec.front();
    auto textStyle = result.value1.textStyle;
    auto fzize = Converter::Convert<double>(textStyle.fontSize);
    EXPECT_EQ(fzize, FONT_SIZE);
    auto fontWeight = Converter::Convert<int32_t>(textStyle.fontWeight);
    EXPECT_EQ(static_cast<OHOS::Ace::FontWeight>(fontWeight), FONT_WEIGHT);
    auto fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(textStyle.fontStyle);
    ASSERT_TRUE(fontStyle.has_value());
    EXPECT_EQ(fontStyle.value(), FONT_STYLE);
    auto fontColor = Converter::OptConvert<Color>(textStyle.fontColor);
    ASSERT_TRUE(fontColor.has_value());
    EXPECT_EQ(fontColor.value(), FONT_COLOUR);

    StyledStringPeer::Destroy(inValue);
#endif
}

/**
 * @tc.name: toStyledStringTest
 * @tc.desc: Check the functionality of toStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, toStyledStringTest, TestSize.Level1)
{
    ASSERT_NE(accessor_->toStyledString, nullptr);
    RangeOptions options;
    options.start = TEST_START;
    options.end = TEST_END;
    auto value = Converter::ArkValue<Ark_RichEditorRange>(options);
    EXPECT_CALL(*mockRichEditorController_, ToStyledString(TEST_START, TEST_END)).Times(1);
    accessor_->toStyledString(peer_, &value);
}

/**
 * @tc.name: addTextSpanTestTextShadow
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestTextShadow, TestSize.Level1)
{
    auto inputValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto inputValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    Ark_ShadowOptions shadow = {
        .radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(1.5f),
        .type = Converter::ArkValue<Opt_ShadowType>(ARK_SHADOW_TYPE_COLOR),
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>("#FF81AABB"),
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(2.5f),
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(3.5f),
        .fill = Converter::ArkValue<Opt_Boolean>(true)
    };

    Opt_Union_ShadowOptions_Array_ShadowOptions textShadow;
    WriteToUnion<Ark_ShadowOptions>(WriteTo(textShadow)) = shadow;

    WriteTo(WriteTo(inputValueOptions).style).textShadow = textShadow;
    accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
    const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
    ASSERT_TRUE(options.style);
    auto resultVec = options.style->GetTextShadows();
    ASSERT_EQ(resultVec.size(), 1);
    Shadow resultShadow = resultVec.front();
    EXPECT_FLOAT_EQ(resultShadow.GetBlurRadius(), 1.5f);
    EXPECT_EQ(resultShadow.GetShadowType(), ShadowType::COLOR);
    EXPECT_EQ(resultShadow.GetColor().ToString(), "#FF81AABB");
    EXPECT_FLOAT_EQ(resultShadow.GetOffset().GetX(), 2.5f);
    EXPECT_FLOAT_EQ(resultShadow.GetOffset().GetY(), 3.5f);
    EXPECT_EQ(resultShadow.GetIsFilled(), true);
}

/**
 * @tc.name: addTextSpanTestLetterSpacing
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestLetterSpacing, TestSize.Level1)
{
    auto initValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto initValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    auto checkValue = [this, &initValueValue, &initValueOptions](
        const std::string& input, const std::string& expected, const Opt_Union_F64_String& value) {
        auto inputValueValue = initValueValue;
        Opt_RichEditorTextSpanOptions inputValueOptions = initValueOptions;

        WriteTo(WriteTo(inputValueOptions).style).letterSpacing = value;
        accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
        const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
        ASSERT_TRUE(options.style);
        EXPECT_EQ(options.style->GetLetterSpacing().ToString(), expected) << "Input value is: " << input <<
            ", method: addTextSpan, attribute: options.style.letterSpacing";
    };

    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDimensionsNumAnyValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDimensionsStrNonPercValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(value));
    }
}

/**
 * @tc.name: addTextSpanTestLineHeight
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestLineHeight, TestSize.Level1)
{
    auto initValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto initValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    auto checkValue = [this, &initValueValue, &initValueOptions](
        const std::string& input, const std::string& expected, const Opt_Union_F64_String_Resource& value) {
        auto inputValueValue = initValueValue;
        Opt_RichEditorTextSpanOptions inputValueOptions = initValueOptions;

        WriteTo(WriteTo(inputValueOptions).style).lineHeight = value;
        accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
        const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
        ASSERT_TRUE(options.style);
        EXPECT_EQ(options.style->GetLineHeight().ToString(), expected) << "Input value is: " << input <<
            ", method: addTextSpan, attribute: options.style.lineHeight";
    };

    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDimensionsNumNonNegValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_Float64>(value));
    }
    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureDimensionsStrNonNegNonPctValidValues) {
        checkValue(input, expected, Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(value));
    }
}

/**
 * @tc.name: addTextSpanTestHalfLeading
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestHalfLeading, TestSize.Level1)
{
    auto initValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto initValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    auto checkValue = [this, &initValueValue, &initValueOptions](
        const std::string& input, bool expected, const Opt_Boolean& value) {
        auto inputValueValue = initValueValue;
        Opt_RichEditorTextSpanOptions inputValueOptions = initValueOptions;

        WriteTo(WriteTo(inputValueOptions).style).halfLeading = value;
        accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
        const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
        ASSERT_TRUE(options.style);
        EXPECT_EQ(options.style->GetHalfLeading(), expected) <<
            "Input value is: " << input << ", method: addTextSpan, attribute: options.style.halfLeading";
    };

    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureBooleanValues) {
        checkValue(input, expected, Converter::ArkValue<Opt_Boolean>(value));
    }
}

/**
 * @tc.name: addTextSpanTestFontFeature
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestFontFeature, TestSize.Level1)
{
    auto initValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto initValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    auto checkValue = [this, &initValueValue, &initValueOptions](
        const std::string& input, const std::string& expected, const Opt_String& value) {
        auto inputValueValue = initValueValue;
        Opt_RichEditorTextSpanOptions inputValueOptions = initValueOptions;

        WriteTo(WriteTo(inputValueOptions).style).fontFeature = value;
        accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
        const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
        ASSERT_TRUE(options.style);
        EXPECT_EQ(UnParseFontFeatureSetting(options.style->GetFontFeatures()), expected) <<
            "Input value is: " << input << ", method: addTextSpan, attribute: options.style.fontFeature";
    };

    for (auto& [input, value, expected] : AccessorTestFixtures::testFixtureFontFeatureValidValues) {
        checkValue(input, expected, Converter::ArkValue<Opt_String>(value));
    }
}

/**
 * @tc.name: addTextSpanTestTextBackgroundStyle
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorControllerAccessorTest, addTextSpanTestTextBackgroundStyle, TestSize.Level1)
{
    auto inputValueValue = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(
        std::get<1>(AccessorTestFixtures::testFixtureStringValidValues.front()));

    Ark_RichEditorTextSpanOptions textSpanOptions = {
        .offset = Converter::ArkValue<Opt_Int32>(),
        .style = Converter::ArkValue<Opt_RichEditorTextStyle>(GetEmptyTextStyle()),
        .paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(),
        .gesture = Converter::ArkValue<Opt_RichEditorGesture>()
    };
    auto inputValueOptions = Converter::ArkValue<Opt_RichEditorTextSpanOptions>(textSpanOptions);

    Opt_TextBackgroundStyle textBackgroundStyle;
    WriteTo(WriteTo(textBackgroundStyle).color) =
        Converter::ArkUnion<Ark_ResourceColor, Ark_String>("#FF101520");
    WriteTo(WriteTo(textBackgroundStyle).radius) =
        Converter::ArkUnion<Ark_Union_Dimension_BorderRadiuses, Ark_Dimension>("12.5vp");

    WriteTo(WriteTo(inputValueOptions).style).textBackgroundStyle = textBackgroundStyle;
    accessor_->addTextSpan(peer_, &inputValueValue, &inputValueOptions);
    const TextSpanOptions& options = mockRichEditorController_->textSpanOptions_;
    ASSERT_TRUE(options.style);
    auto result = options.style->GetTextBackgroundStyle();
    ASSERT_TRUE(result);

    ASSERT_TRUE(result->backgroundColor);
    EXPECT_EQ(result->backgroundColor->ColorToString(), "#FF101520") <<
        "Method: addTextSpan, attribute: options.style.textBackgroundStyle.color";

    auto radius = result->backgroundRadius;
    ASSERT_TRUE(radius);
    ASSERT_TRUE(radius->radiusTopLeft);
    ASSERT_TRUE(radius->radiusTopRight);
    ASSERT_TRUE(radius->radiusBottomRight);
    ASSERT_TRUE(radius->radiusBottomLeft);
    EXPECT_EQ(radius->radiusTopLeft->ToString(), "12.50vp");
    EXPECT_EQ(radius->radiusTopRight->ToString(), "12.50vp");
    EXPECT_EQ(radius->radiusBottomRight->ToString(), "12.50vp");
    EXPECT_EQ(radius->radiusBottomLeft->ToString(), "12.50vp");
}
} // namespace OHOS::Ace::NG
