/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <functional>
#include <optional>

#include "gmock/gmock-actions.h"
#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_typography_properties.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_accessibility_property.h"
#include "core/components_ng/pattern/text/text_content_modifier.h"
#include "core/components_ng/pattern/text/text_event_hub.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_paint_method.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "frameworks/base/window/drag_window.h"
#include "frameworks/core/components_ng/pattern/root/root_pattern.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float RK356_LOW_WIDTH = 50.0f;
constexpr float RK356_LOW_HEIGHT = 20.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 75.0f;
constexpr float LARGE_WIDTH = 1000000.0f;
constexpr float DIMENSION = 10.0f;
constexpr float CONTEXT_WIDTH_VALUE = 10.0f;
constexpr float CONTEXT_LARGE_WIDTH_VALUE = 10000.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 10.0f;
constexpr float BASE_LINE_OFFSET_VALUE = 1.0;
constexpr float BASE_LINE_OFFSET = 20.f;
constexpr double RECT_X_VALUE = 1.0;
constexpr double RECT_SECOND_X_VALUE = 2.0;
constexpr double RECT_Y_VALUE = 1.0;
constexpr double RECT_WIDTH_VALUE = 5.0;
constexpr double RECT_HEIGHT_VALUE = 10.0;
constexpr double BLURRADIUS_VALUE = 0.0;
constexpr double SPREADRADIUS_VALUE = 0.0;
constexpr double ADAPT_OFFSETY_VALUE = 5.0;
constexpr double ADAPT_OFFSETX_VALUE = 5.0;
constexpr bool ADAPT_FILL_VALUE = true;
const std::string TEXT_CONTENT = "text";
constexpr int32_t TEXT_ERROR = -1;
constexpr int32_t TEXT_SIZE_INT = 10;
constexpr int32_t MAX_LINES = 500;
constexpr int32_t SELECTED_COLOR = 0;
constexpr Dimension BASELINE_OFFSET_VALUE = Dimension(20, DimensionUnit::PX);
constexpr Dimension ADAPT_MIN_FONT_SIZE_VALUE = Dimension(50, DimensionUnit::PX);
constexpr Dimension ADAPT_OVER_MIN_FONT_SIZE_VALUE = Dimension(100, DimensionUnit::PX);
constexpr Dimension ADAPT_ZERO_FONT_SIZE_VALUE = Dimension(0, DimensionUnit::PX);
constexpr Dimension ADAPT_MAX_FONT_SIZE_VALUE_S = Dimension(80, DimensionUnit::PX);
constexpr Dimension ADAPT_FONT_SIZE_STEP_VALUE = Dimension(10, DimensionUnit::PX);
const std::string CREATE_VALUE = "Hello World";
const std::u16string CREATE_VALUE_W = u"Hello World";
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF CONTAINER_LOW_SIZE(RK356_LOW_WIDTH, RK356_LOW_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const SizeF LARGE_CONTAINER_SIZE(LARGE_WIDTH, TEXT_HEIGHT);
constexpr Dimension ADAPT_LINE_HEIGHT_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension ADAPT_FONT_SIZE_VALUE = Dimension(30, DimensionUnit::PX);
constexpr Dimension ADAPT_BASE_LINE_OFFSET_VALUE = Dimension(10, DimensionUnit::PX);
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const SizeT<float> LARGE_SIZE = SizeT<float>(10000.0f, 1000.0f);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextAlign TEXT_ALIGN_VALUE = Ace::TextAlign::CENTER;
const Ace::TextOverflow TEXT_OVERFLOW_VALUE = Ace::TextOverflow::CLIP;
const uint32_t MAX_LINES_VALUE = 10;
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension ADAPT_MAX_FONT_SIZE_VALUE = Dimension(200, DimensionUnit::PX);
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension TEXT_INDENT = Dimension(5, DimensionUnit::PX);
const Dimension ADAPT_UPDATE_FONTSIZE_VALUE = Dimension(50, DimensionUnit::PX);
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;
const Color FOREGROUND_COLOR_VALUE = Color::FOREGROUND;
const RectF CONTENT_RECT(3.0, 3.0, TEXT_WIDTH, TEXT_HEIGHT);
constexpr int32_t ROOT_NODE_ID = 113;
const std::string EMPTY_TEXT = "";
const CopyOptions copyOption = CopyOptions::None;
constexpr int32_t UNKNOWN_REASON = 1;
constexpr float TEXT_RECT_SIZE_ZEOR = 0.0f;
constexpr float TEXT_RECT_WIDTH = 10.0f;
constexpr float TEXT_RECT_TOP_ONE = 10.0f;
constexpr float TEXT_RECT_TOP_TWO = 20.0f;
constexpr float TEXT_CONTENT_SIZE = 50.0f;
const std::string TEXT_DEFAULT_VALUE = "{\"style\":\"FontStyle.Normal\",\"size\":\"16.00fp\",\"weight\":"
                                       "\"FontWeight.Normal\",\"family\":\"HarmonyOS Sans\"}";
const std::string TEXT_EQUALS_VALUE =
    R"({"style":"FontStyle.Italic","size":"20.10px","weight":"FontWeight.Bold","family":"cursive"})";
const Ace::WordBreak TEXT_WORD_BREAK = Ace::WordBreak::BREAK_ALL;
const std::string TEXT_FOR_AI_SINGLE = "phone: 18888888888";
const std::string TEXT_FOR_AI = "phone: 12345678900,url: www.baidu.com";
const std::string SPAN_PHONE = "12345678900";
const std::string SPAN_URL = "www.baidu.com";
constexpr int32_t AI_SPAN_START = 7;
constexpr int32_t AI_SPAN_END = 18;
constexpr int32_t AI_SPAN_START_II = 24;
constexpr int32_t AI_SPAN_END_II = 37;
const struct TextDataDetectResult TEXT_DATA_DETECT_RESULT = {
    0,
    "{\"phoneNum\":[{\"charOffset\":7,\"number\":\"18888888888\",\"oriText\":\"18888888888\",\"type\":1}]}",
    "0",
    "{\"phoneNum\":[{\"option\":\"呼叫\"},{\"option\":\"发送信息\"},\
        {\"option\":\"新建联系人\"},{\"option\":\"复制\"},{\"option\":\"选择文本\"}],\
        \"url\":[{\"option\":\"打开\"},{\"option\":\"复制\"},{\"option\":\"选择文本\"}],\
        \"email\":[{\"option\":\"新建邮箱\"},{\"option\":\"发送信息\"},\
        {\"option\":\"新建联系人\"},{\"option\":\"复制\"},{\"option\":\"选择文本\"}],\
        \"location\":[{\"option\":\"导航至该位置\"},{\"option\":\"在地图中打开\"},\
        {\"option\":\"复制\"},{\"option\":\"选择文本\"}]}",
    "{\"bundlename\":\"com.XXXXXX.hmsapp.hiai\",\"abilityname\":\"EntityMenuUIExtensionAbility\"}"
};

using OnClickCallback = std::function<void(const BaseEventInfo* info)>;
using DragDropBaseCallback = std::function<DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;

void onClickFunc(const BaseEventInfo* info) {};

void onRemoteMessage() {};

DragDropBaseInfo OnDragStartFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)
{
    DragDropBaseInfo temp;
    return temp;
}

void OnDragDropFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};

void TestUpdateScenario(const RefPtr<TextPattern>& pattern)
{
    ASSERT_NE(pattern, nullptr);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(ADAPT_UPDATE_FONTSIZE_VALUE);
    pattern->BeforeCreateLayoutWrapper();
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    for (const auto& child : host->GetChildren()) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        ASSERT_NE(spanNode, nullptr);
        auto inheritPropertyInfo = spanNode->CalculateInheritPropertyInfo();
        auto iter = inheritPropertyInfo.find(PropertyInfo::FONTSIZE);
        if (iter != inheritPropertyInfo.end()) {
            EXPECT_EQ(spanNode->GetFontSize().value(), ADAPT_UPDATE_FONTSIZE_VALUE);
        }
    }
}
} // namespace

struct TestProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyleValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Ace::TextAlign> textAlignValue = std::nullopt;
    std::optional<Ace::TextOverflow> textOverflowValue = std::nullopt;
    std::optional<uint32_t> maxLinesValue = std::nullopt;
    std::optional<Dimension> lineHeightValue = std::nullopt;
    std::optional<Ace::TextDecoration> textDecorationValue = std::nullopt;
    std::optional<Color> textDecorationColorValue = std::nullopt;
    std::optional<Dimension> baselineOffsetValue = std::nullopt;
    std::optional<Ace::TextCase> textCaseValue = std::nullopt;
    std::optional<Dimension> adaptMinFontSize = std::nullopt;
    std::optional<Dimension> adaptMaxFontSize = std::nullopt;
    std::optional<Dimension> letterSpacing = std::nullopt;
    std::optional<Dimension> textIndent = std::nullopt;
    std::optional<Ace::WordBreak> wordBreak = std::nullopt;
};

struct ImageSpanNodeProperty {
    std::optional<std::string> imageSrc = std::nullopt;
    std::optional<RefPtr<PixelMap>> pixelMap = std::nullopt;
    std::optional<MarginPropertyF> margin = std::nullopt;
    std::optional<ImageFit> imageFit = std::nullopt;
    std::optional<VerticalAlign> verticalAlign = std::nullopt;
};

class TextTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<SpanNode> CreateSpanNodeWithSetDefaultProperty(const std::string& content);
    RefPtr<ImageSpanNode> CreateImageSpanNode(const ImageSpanNodeProperty& property);

protected:
    static RefPtr<FrameNode> CreateTextParagraph(const std::string& createValue, const TestProperty& testProperty);
    static void SetContentModifier(TextContentModifier& textContentModifier);
    static void SetPaintMethodModifier(TextPaintMethod& textPaintMethod);
    static void UpdateTextLayoutProperty(RefPtr<TextLayoutProperty> textLayoutProperty);
};

void TextTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void TextTestNg::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
}

void TextTestNg::TearDown()
{
    MockParagraph::TearDown();
}

RefPtr<SpanNode> TextTestNg::CreateSpanNodeWithSetDefaultProperty(const std::string& content)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(content);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontWeight(FONT_WEIGHT_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    spanModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    return AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
}

RefPtr<ImageSpanNode> TextTestNg::CreateImageSpanNode(const ImageSpanNodeProperty& property)
{
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageSpanNode->GetLayoutProperty());
    if (property.imageSrc.has_value()) {
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(property.imageSrc.value()));
    }
    if (property.pixelMap.has_value()) {
        imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(property.pixelMap.value()));
    }
    if (property.imageFit.has_value()) {
        imageLayoutProperty->UpdateImageFit(property.imageFit.value());
    }
    if (property.verticalAlign.has_value()) {
        imageLayoutProperty->UpdateVerticalAlign(property.verticalAlign.value());
    }
    if (property.margin.has_value()) {
        auto geometryNode = imageSpanNode->GetGeometryNode();
        geometryNode->UpdateMargin(property.margin.value());
    }
    return imageSpanNode;
}

RefPtr<FrameNode> TextTestNg::CreateTextParagraph(const std::string& createValue, const TestProperty& testProperty)
{
    TextModelNG textModel;
    textModel.Create(createValue);
    if (testProperty.fontSizeValue.has_value()) {
        textModel.SetFontSize(testProperty.fontSizeValue.value());
    }
    if (testProperty.textColorValue.has_value()) {
        textModel.SetTextColor(testProperty.textColorValue.value());
    }
    if (testProperty.italicFontStyleValue.has_value()) {
        textModel.SetItalicFontStyle(testProperty.italicFontStyleValue.value());
    }
    if (testProperty.fontWeightValue.has_value()) {
        textModel.SetFontWeight(testProperty.fontWeightValue.value());
    }
    if (testProperty.fontFamilyValue.has_value()) {
        textModel.SetFontFamily(testProperty.fontFamilyValue.value());
    }
    if (testProperty.textAlignValue.has_value()) {
        textModel.SetTextAlign(testProperty.textAlignValue.value());
    }
    if (testProperty.textOverflowValue.has_value()) {
        textModel.SetTextOverflow(testProperty.textOverflowValue.value());
    }
    if (testProperty.maxLinesValue.has_value()) {
        textModel.SetMaxLines(testProperty.maxLinesValue.value());
    }
    if (testProperty.lineHeightValue.has_value()) {
        textModel.SetLineHeight(testProperty.lineHeightValue.value());
    }
    if (testProperty.textDecorationValue.has_value()) {
        textModel.SetTextDecoration(testProperty.textDecorationValue.value());
    }
    if (testProperty.textDecorationColorValue.has_value()) {
        textModel.SetTextDecorationColor(testProperty.textDecorationColorValue.value());
    }
    if (testProperty.baselineOffsetValue.has_value()) {
        textModel.SetBaselineOffset(testProperty.baselineOffsetValue.value());
    }
    if (testProperty.textCaseValue.has_value()) {
        textModel.SetTextCase(testProperty.textCaseValue.value());
    }
    if (testProperty.adaptMinFontSize.has_value()) {
        textModel.SetAdaptMinFontSize(testProperty.adaptMinFontSize.value());
    }
    if (testProperty.adaptMaxFontSize.has_value()) {
        textModel.SetAdaptMaxFontSize(testProperty.adaptMaxFontSize.value());
    }
    if (testProperty.letterSpacing.has_value()) {
        textModel.SetLetterSpacing(testProperty.letterSpacing.value());
    }
    if (testProperty.textIndent.has_value()) {
        textModel.SetTextIndent(testProperty.textIndent.value());
    }
    if (testProperty.wordBreak.has_value()) {
        textModel.SetWordBreak(testProperty.wordBreak.value());
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish(); // TextView pop
    return AceType::DynamicCast<FrameNode>(element);
}

void TextTestNg::SetContentModifier(TextContentModifier& textContentModifier)
{
    textContentModifier.SetFontWeight(Ace::FontWeight::W200);
    textContentModifier.SetTextColor(TEXT_COLOR_VALUE);
    textContentModifier.SetTextDecorationColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textShadow.SetIsFilled(ADAPT_FILL_VALUE);
    textContentModifier.SetTextShadow({ textShadow });
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE);
    OffsetF paintOffset;
    textContentModifier.SetPrintOffset(paintOffset);
}

void TextTestNg::SetPaintMethodModifier(TextPaintMethod& textPaintMethod)
{
    textPaintMethod.textContentModifier_->fontSize_ = ADAPT_FONT_SIZE_VALUE;
    textPaintMethod.textContentModifier_->fontWeight_ = FontWeight::LIGHTER;
    textPaintMethod.textContentModifier_->textColor_ = TEXT_COLOR_VALUE;
    textPaintMethod.textContentModifier_->AddDefaultShadow();
    textPaintMethod.textContentModifier_->textDecorationColorAlpha_ =
        AceType::MakeRefPtr<AnimatablePropertyFloat>(1.0f);
    textPaintMethod.textContentModifier_->textDecoration_ = TextDecoration::NONE;
    textPaintMethod.textContentModifier_->baselineOffset_ = BASELINE_OFFSET_VALUE;
}

void TextTestNg::UpdateTextLayoutProperty(RefPtr<TextLayoutProperty> textLayoutProperty)
{
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration(TextDecoration::OVERLINE);
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);
    textLayoutProperty->UpdateWordBreak(TEXT_WORD_BREAK);
}

std::pair<RefPtr<FrameNode>, RefPtr<TextPattern>> Init()
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    pattern->AttachToFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, ROOT_NODE_ID, Referenced::MakeRefPtr<RootPattern>());

    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    pattern->clipboard_ = clipboard;
    return { frameNode, pattern };
}

void SuppressMockParagraph()
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(0.f));
    std::vector<RectF> rects;
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects)); // 2 means second paras
}

/**
 * @tc.name: TextFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    testProperty.textAlignValue = std::make_optional(TEXT_ALIGN_VALUE);
    testProperty.textOverflowValue = std::make_optional(TEXT_OVERFLOW_VALUE);
    testProperty.maxLinesValue = std::make_optional(MAX_LINES_VALUE);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.adaptMinFontSize = std::make_optional(ADAPT_MIN_FONT_SIZE_VALUE);
    testProperty.adaptMaxFontSize = std::make_optional(ADAPT_MAX_FONT_SIZE_VALUE);
    testProperty.textIndent = std::make_optional(TEXT_INDENT);
    testProperty.wordBreak = std::make_optional(TEXT_WORD_BREAK);

    RefPtr<FrameNode> frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLineStyle, nullptr);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(textStyle.GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetFontFamilies(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textStyle.GetTextAlign(), TEXT_ALIGN_VALUE);
    EXPECT_EQ(textStyle.GetTextOverflow(), TEXT_OVERFLOW_VALUE);
    EXPECT_EQ(textStyle.GetMaxLines(), MAX_LINES_VALUE);
    EXPECT_EQ(textStyle.GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(textStyle.GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(textStyle.GetBaselineOffset(), BASELINE_OFFSET_VALUE);
    EXPECT_EQ(textStyle.GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMinFontSize(), ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptMaxFontSize(), ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textStyle.GetAdaptTextSize(),
        testProperty.adaptMinFontSize.has_value() || testProperty.adaptMaxFontSize.has_value());
    EXPECT_EQ(textStyle.GetWordBreak(), TEXT_WORD_BREAK);

    /**
     * @tc.cases: case2. renderContext has foreground color and modifier will foreground color flag
     */
    frameNode->GetRenderContext()->UpdateForegroundColor(Color::RED);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetTextColor(), FOREGROUND_COLOR_VALUE);
}

/**
 * @tc.name: TextFrameNodeCreator002
 * @tc.desc: Test all the property of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator002, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    testProperty.baselineOffsetValue = std::make_optional(BASELINE_OFFSET_VALUE);
    auto frameNode = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLineStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);
    EXPECT_EQ(textStyle.GetLetterSpacing(), LETTER_SPACING);
}

/**
 * @tc.name: TextFrameNodeCreator003
 * @tc.desc: Test all the fontWeight and events of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator003, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE);
    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textModelNG.SetLineHeight(LINE_HEIGHT_VALUE);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
    const std::unique_ptr<TextLineStyle>& textLineStyle = textLayoutProperty->GetTextLineStyle();
    ASSERT_NE(textLayoutProperty, nullptr);
    TextStyle textStyle = CreateTextStyleUsingTheme(fontStyle, textLineStyle, nullptr);

    textModelNG.SetFontWeight(FontWeight::LIGHTER);
    textStyle.SetFontWeight(FontWeight::W100);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W100);
    textModelNG.SetFontWeight(FontWeight::REGULAR);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::NORMAL);
    textStyle.SetFontWeight(FontWeight::W400);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W400);
    textModelNG.SetFontWeight(FontWeight::MEDIUM);
    textStyle.SetFontWeight(FontWeight::W500);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W500);
    textModelNG.SetFontWeight(FontWeight::BOLD);
    textStyle.SetFontWeight(FontWeight::W700);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W700);
    textModelNG.SetFontWeight(FontWeight::BOLDER);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);
    textModelNG.SetFontWeight(FontWeight::W900);
    textStyle.SetFontWeight(FontWeight::W900);
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::W900);

    textModelNG.SetOnClick(onClickFunc);
    textModelNG.SetRemoteMessage(onRemoteMessage);
    textModelNG.SetCopyOption(copyOption);
    textModelNG.SetOnDragStart(OnDragStartFunction);
    textModelNG.SetOnDragEnter(OnDragDropFunction);
    textModelNG.SetOnDragMove(OnDragDropFunction);
    textModelNG.SetOnDragLeave(OnDragDropFunction);
    textModelNG.SetOnDrop(OnDragDropFunction);
}

/**
 * @tc.name: OnAttachToFrameNode001
 * @tc.desc: Test TextPattern OnAttachToFrameNode when GetHost is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnAttachToFrameNode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->OnAttachToFrameNode();
    EXPECT_EQ(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: Test TextPattern OnHandleMoveDone
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. call OnHandleMoveDone when SelectOverlayProxy is nullptr.
     * @tc.expected: the function exits normally
     */
    RectF handleRect = CONTENT_RECT;
    pattern->OnHandleMoveDone(handleRect, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);

    /**
     * @tc.steps: step3. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step4. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);

    /**
     * @tc.steps: step5. call OnHandleMoveDone when SelectOverlayProxy is not nullptr.
     * @tc.expected: the OnHandleMoveDone function exits normally
     */
    bool isFirstHandle[2] = { true, false };
    bool isShowCopyAll[2] = { true, false };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; ++j) {
            pattern->selectMenuInfo_.showCopyAll = isShowCopyAll[j];
            pattern->textForDisplay_ = "abcdefghij";
            pattern->OnHandleMoveDone(handleRect, isFirstHandle[i]);
            if (pattern->IsSelectAll() && pattern->selectMenuInfo_.showCopyAll) {
                EXPECT_FALSE(pattern->selectMenuInfo_.showCopyAll);
            }

            pattern->selectMenuInfo_.showCopyAll = isShowCopyAll[j];
            pattern->textForDisplay_ = TEXT_CONTENT;
            pattern->OnHandleMoveDone(handleRect, isFirstHandle[i]);
            if (!pattern->IsSelectAll() && !pattern->selectMenuInfo_.showCopyAll) {
                EXPECT_TRUE(pattern->selectMenuInfo_.showCopyAll);
            }
        }
        pattern->OnHandleMoveDone(handleRect, isFirstHandle[i]);
        EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
        EXPECT_EQ(pattern->textSelector_.GetTextEnd(), TEXT_SIZE_INT);
    }
}

/**
 * @tc.name: ShowSelectOverlay001
 * @tc.desc: Test TextPattern ShowSelectOverlay when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowSelectOverlay001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    pattern->selectOverlayProxy_ = AceType::MakeRefPtr<SelectOverlayProxy>(0);
    RectF firstHandle = CONTENT_RECT;
    RectF secondHandle = CONTENT_RECT;
    pattern->ShowSelectOverlay(firstHandle, secondHandle);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
    pattern->selectOverlayProxy_->Close();
    pattern->ShowSelectOverlay(firstHandle, secondHandle);
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test TextPattern OnModifyDone when frameNode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    pattern->OnModifyDone();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test TextPattern OnModifyDone longPressEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * copyOption: CopyOptions::InApp
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textLayoutProperty->UpdateContent(TEXT_CONTENT);

    /**
     * @tc.steps: step3. check the longPressEvent.
     * @tc.expected: longPressEvent is triggered
     */
    textPattern->OnModifyDone();
    EXPECT_NE(textPattern->longPressEvent_, nullptr);
    EXPECT_EQ(textPattern->textForDisplay_, TEXT_CONTENT);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is true.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;
    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    auto ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap003
 * @tc.desc: Test TextPattern OnDirtyLayoutWrapperSwap when skipMeasure is fasle and paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnDirtyLayoutWrapperSwap003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);

    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper002
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper003
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when paragraph is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper003, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        rowLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, AceType::MakeRefPtr<GeometryNode>(), nullptr);
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    ret = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_TRUE(ret);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: BeforeCreateLayoutWrapper004
 * @tc.desc: Test TextPattern BeforeCreateLayoutWrapper when frameNode child is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BeforeCreateLayoutWrapper004, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto patternChild = AceType::MakeRefPtr<TextPattern>();
    auto frameNodeChild = FrameNode::CreateFrameNode("Test", 1, patternChild);
    ASSERT_NE(frameNodeChild, nullptr);

    frameNode->AddChild(frameNodeChild);
    pattern->AttachToFrameNode(frameNode);
    pattern->selectOverlayProxy_ = nullptr;

    auto rowLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(rowLayoutAlgorithm));
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: Test TextPattern OnHandleMove when SelectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMove001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    /**
     * @tc.steps: step1. construct a SelectOverlayManager
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step2. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    EXPECT_NE(pattern->selectOverlayProxy_, nullptr);
}

/**
 * @tc.name: TextCreateParagraph002
 * @tc.desc: Correctly create Paragraph only Set content.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextCreateParagraph002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline).WillOnce(Return(0));
    EXPECT_CALL(*paragraph, PushStyle);
    EXPECT_CALL(*paragraph, Build);
    // investigate why it layouts twice
    EXPECT_CALL(*paragraph, Layout).Times(2);

    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set Content.
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    EXPECT_FALSE(textLayoutAlgorithm == nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: TextLayoutTest001
 * @tc.desc: Set content , width and height to Text and the check result.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(TEXT_WIDTH));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, Layout);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * content: CREATE_VALUE
     * width: 100.0f
     * height: 75.0f
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
}

/**
 * @tc.name: TextLayoutTest002
 * @tc.desc: set baselineOffset and maxsize of Text check height
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, Layout).Times(2);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), BASELINE_OFFSET_VALUE.Value() + 50.0);
}

/**
 * @tc.name: TextLayoutTest003
 * @tc.desc: set minFontSize and maxFontSize of Text check then check
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest003, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MIN_FONT_SIZE_VALUE, ADAPT_MAX_FONT_SIZE_VALUE_S);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContext();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest004
 * @tc.desc: set minFontSize and maxFontSize of Text check then check
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest004, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MIN_FONT_SIZE_VALUE, ADAPT_MAX_FONT_SIZE_VALUE_S);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContext();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest005
 * @tc.desc: set minFontSize and maxFontSize of Text check then check when maxFontSize >= minFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest005, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Build).Times(1);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * minFontSize: 50_px
     * macFontSize: 80_px
     */

    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextAlign(TextAlign::CENTER);
    textStyle.SetAdaptTextSize(ADAPT_MAX_FONT_SIZE_VALUE_S, ADAPT_MIN_FONT_SIZE_VALUE);
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    auto pipeline = textFrameNode->GetContext();

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto result = textLayoutAlgorithm->AdaptMinTextSize(
        textStyle, CREATE_VALUE, parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode));

    /**
     * @tc.steps: step4. check the fontSize.
     */

    EXPECT_TRUE(result);
}

/**
 * @tc.name: TextLayoutTest006
 * @tc.desc: set baselineOffset and maxsize of Text check height when paragraph_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));
    EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, AddText).Times(2);
    EXPECT_CALL(*paragraph, Layout).Times(3);
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), BASELINE_OFFSET_VALUE.Value() + 50.0);
}

/**
 * @tc.name: TextLayoutTest007
 * @tc.desc: set baselineOffset and maxsize of Text check height when AdaptTextSize is disable.
 *           contentConstraint.maxSize.IsPositive() is false.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize.SetHeight(-1.0);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    Dimension adaptMinFontSize(DIMENSION, DimensionUnit::PERCENT);
    textStyle.SetAdaptMinFontSize(adaptMinFontSize);
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(
        textStyle, "", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX, std::nullopt);
}

/**
 * @tc.name: TextLayoutTest008
 * @tc.desc: set baselineOffset and maxsize of Text check height when AdaptTextSize is disable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutTest008, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetWidth(-1.0);
    parentLayoutConstraint.maxSize.SetHeight(1.0);
    parentLayoutConstraint.maxSize.SetWidth(1.0);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    Dimension adaptMinFontSize(DIMENSION, DimensionUnit::PERCENT);
    textStyle.SetAdaptMinFontSize(adaptMinFontSize);
    auto ret = textLayoutAlgorithm->CreateParagraphAndLayout(
        textStyle, "", parentLayoutConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    auto sizeX =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_EQ(sizeX->Height(), 1.0);
}

/**
 * @tc.name: ToJsonValue001
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue002
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::IDEOGRAPHIC);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue003
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::TOP);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue004
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::BOTTOM);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue005
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::MIDDLE);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue006
 * @tc.desc: Test TextLayoutProperty ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run ToJsonValue().
     */
    Dimension dim(DIMENSION);
    textLayoutProperty->UpdateAdaptMinFontSize(dim);
    textLayoutProperty->UpdateAdaptMaxFontSize(dim);
    textLayoutProperty->UpdateLetterSpacing(dim);
    textLayoutProperty->UpdateTextBaseline(TextBaseline::HANGING);
    auto json = std::make_unique<JsonValue>();
    textLayoutProperty->ToJsonValue(json);
}

/**
 * @tc.name: ToJsonValue007
 * @tc.desc: Test textPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create("");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto json = JsonUtil::Create(true);
    /**
     * @tc.steps: step2. expect default textDetectEnable_ false.
     */
    pattern->SetTextDetectEnable(true);
    pattern->ToJsonValue(json);
    EXPECT_EQ(json->GetString("enableDataDetector"), "true");
}

/**
 * @tc.name: DidExceedMaxLines001
 * @tc.desc: Test TextLayoutAlgorithm DidExceedMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, DidExceedMaxLines001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, Layout);
    EXPECT_CALL(*paragraph, DidExceedMaxLines).WillOnce(Return(true));
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    SizeF maxSize;
    ret = textLayoutAlgorithm->DidExceedMaxLines(maxSize);

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_TRUE(ret);
}

/**
 * @tc.name: DidExceedMaxLines002
 * @tc.desc: Test TextLayoutAlgorithm DidExceedMaxLines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, DidExceedMaxLines002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, DidExceedMaxLines).WillOnce(Return(true));
    /**
     * @tc.steps: step1. create textFrameNode.
     */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     * baselineOffset: 20_px
     */

    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     */

    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    LayoutConstraintF contentConstraint;
    auto ret =
        textLayoutAlgorithm->CreateParagraphAndLayout(textStyle, "", contentConstraint, AceType::RawPtr(textFrameNode));
    EXPECT_TRUE(ret);
    SizeF maxSize;
    ret = textLayoutAlgorithm->DidExceedMaxLines(maxSize);

    /**
     * @tc.steps: step4. check the size.
     */

    EXPECT_TRUE(ret);
}

/**
 * @tc.name: TextLayoutAlgorithmTest001
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to MIN_FONT_SIZE_FIRST
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    // set TextHeightAdaptivePolicy MAX_LINES_FIRST
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    // MockTxtParagraph::SetCanConstruct(false);
    textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    // set SetCanConstruct true
    // MockTxtParagraph::SetCanConstruct(true);
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->baselineOffset_ = BASE_LINE_OFFSET;
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest002
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textLayoutProperty);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration(TextDecoration::OVERLINE);
    textLayoutProperty->UpdateBaselineOffset(BASELINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent/SetPropertyToModifier function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContext();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(std::move(textStyle)));
    auto contentModifier = textPattern->GetContentModifier();
    textLayoutAlgorithm->SetPropertyToModifier(textLayoutProperty, contentModifier);
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest003
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to MIN_FONT_SIZE_FIRST, minFontSize and
 *           fontSize are equal
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest004
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight,
 *     the height of text is bigger than the height of container
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_LOW_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_OVER_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest005
 * @tc.desc: test text_layout_algorithm.cpp:Set textHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set lineHeight,
 *     the height of text is bigger than the height of container,set maxlines.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_LOW_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_OVER_MIN_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateMaxLines(MAX_LINES);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextPaintMethodTest001
 * @tc.desc: test text_paint_method.cpp :set textOverflow to MARQUEE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPaintMethodTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set theme.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));

    /**
     * @tc.steps: step3. create textPaintMethod and call UpdateContentModifier function.
     * @tc.expected: The return value of GetOverlayModifier is not null.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    AceType::DynamicCast<TextPattern>(pattern)->textSelector_.Update(0, -1);
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    UpdateTextLayoutProperty(textLayoutProperty);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    SetPaintMethodModifier(textPaintMethod);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    textPaintMethod.textContentModifier_->textDecoration_ = TextDecoration::UNDERLINE;
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper)), nullptr);
}

/**
 * @tc.name: TextContentModifier001
 * @tc.desc: test text_content_modifier.cpp onDraw function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextContentModifier001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call onDraw function.
     * @tc.expected: The member variable value of textContentModifier is the value set above
     */
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContext();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> contentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, contentModifier, textOverlayModifier);
    // set pipelineContext nullptr
    MockPipelineContext::TearDown();
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE);
    MockPipelineContext::SetUp();
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    textContentModifier.SetParagraph(paragraph);
    // call onDraw function(textRacing_ = true)
    textContentModifier.StartTextRace();
    context.width = CONTEXT_LARGE_WIDTH_VALUE;
    textContentModifier.onDraw(context);
    // call onDraw function(textRacing_ = false)
    textContentModifier.StopTextRace();
    textContentModifier.onDraw(context);
    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), ADAPT_FONT_SIZE_VALUE.Value());
    EXPECT_EQ(textContentModifier.baselineOffsetFloat_->Get(), BASELINE_OFFSET_VALUE.Value());
    EXPECT_EQ(textContentModifier.shadows_[0].isFilled->Get(), ADAPT_FILL_VALUE);
    EXPECT_EQ(textContentModifier.paragraph_, paragraph);
}

/**
 * @tc.name: TextContentModifier002
 * @tc.desc: test text_content_modifier.cpp ModifyTextStyle function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextContentModifier002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call ModifyTextStyle function.
     * @tc.expected: The member variable value of textContentModifier is the value set above
     */
    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContext();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    TextContentModifier textContentModifier(std::optional<TextStyle>(std::move(textStyle)));
    textStyle.SetTextDecorationColor(TEXT_COLOR_VALUE);
    SetContentModifier(textContentModifier);
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> contentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, contentModifier, textOverlayModifier);
    // set pipelineContext nullptr
    MockPipelineContext::TearDown();
    textContentModifier.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textContentModifier.SetBaselineOffset(BASELINE_OFFSET_VALUE);
    MockPipelineContext::SetUp();
    // set textDecorationAnimatable_ true
    textContentModifier.textDecorationAnimatable_ = true;
    textContentModifier.textDecoration_ = TextDecoration::UNDERLINE;
    textContentModifier.SetTextDecoration(TextDecoration::NONE);
    textContentModifier.ModifyTextStyle(textStyle);
    // set textDecorationColorAlpha_ value
    textContentModifier.textDecorationColorAlpha_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(1000.0f);
    textContentModifier.ModifyTextStyle(textStyle);
    // set textDecorationAnimatable_ false
    textContentModifier.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textContentModifier.ModifyTextStyle(textStyle);
    EXPECT_EQ(textContentModifier.fontSizeFloat_->Get(), ADAPT_FONT_SIZE_VALUE.Value());
    EXPECT_EQ(textContentModifier.baselineOffsetFloat_->Get(), BASELINE_OFFSET_VALUE.Value());
    EXPECT_EQ(textStyle.GetFontSize().Value(), textContentModifier.fontSizeFloat_->Get());
}

/**
 * @tc.name: TextLayoutAlgorithmTest006
 * @tc.desc: text_layout_algorithm.cpp:Set TextOverflow to MARQUEE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest006, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetMaxWidth).WillOnce(Return(100.0f));
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm and call MeasureContent function.
     * @tc.expected: The width of the return value of MeasureContent is equal to 100.0f
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), 100.0f);
}

/**
 * @tc.name: TextLayoutAlgorithmTest007
 * @tc.desc: text_layout_algorithm.cpp:set TextHeightAdaptivePolicy to LAYOUT_CONSTRAINT_FIRST and set minFontSize to
 *           zero. ADAPT_ZERO_FONT_SIZE_VALUE
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. set textLayoutProperty.
     */
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    textLayoutProperty->UpdateAdaptMinFontSize(ADAPT_ZERO_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateLineHeight(ADAPT_LINE_HEIGHT_VALUE);
    textLayoutProperty->UpdateMaxLines(MAX_LINES);

    /**
     * @tc.steps: step3. create textLayoutAlgorithm.
     * @tc.expected: The width of the return value of MeasureContent is equal to maxWidth of paragraph_
     */
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto contentSize =
        textLayoutAlgorithm->MeasureContent(parentLayoutConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Measure(AccessibilityManager::RawPtr(layoutWrapper));
    textLayoutAlgorithm->Layout(AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_EQ(contentSize.value().Width(), textLayoutAlgorithm->paragraph_->GetMaxWidth());
}

/**
 * @tc.name: TextLayoutAlgorithmTest008
 * @tc.desc: text_layout_algorithm.cpp:call AdaptMaxTextSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest008, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(2);
    EXPECT_CALL(*paragraph, AddText).Times(2);
    EXPECT_CALL(*paragraph, Layout).Times(2);
    EXPECT_CALL(*paragraph, Build).Times(2);
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(2));
    EXPECT_CALL(*paragraph, GetLongestLine).WillRepeatedly(Return(100));

    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    auto frameNode = layoutWrapper->GetHostNode();
    auto pipeline = frameNode->GetContext();
    TextStyle textStyle = CreateTextStyleUsingTheme(
        textLayoutProperty->GetFontStyle(), textLayoutProperty->GetTextLineStyle(), pipeline->GetTheme<TextTheme>());
    textStyle.SetAdaptFontSizeStep(ADAPT_FONT_SIZE_STEP_VALUE);

    /**
     * @tc.steps: step2. create textLayoutAlgorithm and call AdaptMaxTextSize.
     * @tc.expected: when maxFontSize < minFontSize,The return value of AdaptMaxTextSize is false.
     *               when create paragraph failed,The return value of AdaptMaxTextSize is false.
     *               when increase font size,The return value of AdaptMaxTextSize is true.
     *               when set NormalizeToPx false,The return value of AdaptMaxTextSize is false.
     */
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.selfIdealSize.SetSize(TEXT_SIZE);
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto textLayoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();

    // maxFontSize < minFontSize
    textStyle.SetAdaptMaxFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMaxTextSize(
                  textStyle, "abc", parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode)),
        true);

    // create paragraph failed
    MockParagraph::enabled_ = false;
    textStyle.SetAdaptMaxFontSize(ADAPT_MAX_FONT_SIZE_VALUE);
    textStyle.SetAdaptMinFontSize(ADAPT_MIN_FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMaxTextSize(
                  textStyle, "abc", parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode)),
        false);
    MockParagraph::enabled_ = true;

    // increase font size
    EXPECT_EQ(textLayoutAlgorithm->AdaptMaxTextSize(
                  textStyle, "abc", parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode)),
        true);

    // set NormalizeToPx false
    textStyle.adaptFontSizeStep_.SetUnit(DimensionUnit::CALC);
    EXPECT_EQ(textLayoutAlgorithm->AdaptMaxTextSize(
                  textStyle, "abc", parentLayoutConstraint, pipeline, AceType::RawPtr(textFrameNode)),
        false);
}

/**
 * @tc.name: TextOverlayModifierTest001
 * @tc.desc: test text_overlay_modifier.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextOverlayModifierTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textOverlayModifier and call text_overlay_modifier.cpp function.
     * @tc.expected: The member variable value of textOverlayModifier is the value set above
     */
    TextOverlayModifier textOverlayModifier;
    OffsetF paintOffset;
    textOverlayModifier.SetPrintOffset(paintOffset);
    textOverlayModifier.SetSelectedColor(SELECTED_COLOR);
    std::vector<RectF> rectList;
    rectList.push_back(RectF(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE));
    textOverlayModifier.SetSelectedRects(rectList);
    // change selectedRects_ and call IsSelectedRectsChanged function
    RectF secondRect(RECT_SECOND_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);
    textOverlayModifier.selectedRects_[0] = secondRect;
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, Save()).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, Restore()).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    RectF contentRect;
    textOverlayModifier.SetContentRect(contentRect);
    textOverlayModifier.onDraw(context);
    EXPECT_EQ(textOverlayModifier.paintOffset_->Get(), paintOffset);
    EXPECT_EQ(textOverlayModifier.selectedColor_->Get(), SELECTED_COLOR);
    EXPECT_EQ(textOverlayModifier.IsSelectedRectsChanged(rectList), true);
    EXPECT_EQ(textOverlayModifier.contentRect_, contentRect);
}

/**
 * @tc.name: TextPaintMethodTest002
 * @tc.desc: test text_paint_method.cpp without setting textOverflow
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPaintMethodTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textLayoutProperty.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. create textPaintMethod and update textLayoutProperty.
     */
    auto pattern = textFrameNode->GetPattern<Pattern>();
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textLayoutProperty->UpdateFontSize(ADAPT_FONT_SIZE_VALUE);
    textLayoutProperty->UpdateFontWeight(Ace::FontWeight::W200);
    textLayoutProperty->UpdateTextColor(TEXT_COLOR_VALUE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    textLayoutProperty->UpdateTextShadow({ textShadow });
    textLayoutProperty->UpdateTextDecorationColor(TEXT_COLOR_VALUE);
    textLayoutProperty->UpdateTextDecoration(TextDecoration::OVERLINE);
    textLayoutProperty->UpdateBaselineOffset(ADAPT_BASE_LINE_OFFSET_VALUE);

    /**
     * @tc.steps: step3. call UpdateContentModifier,UpdateOverlayModifier and GetOverlayModifier.
     * @tc.expected: The return value of GetOverlayModifier is not empty
     */
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = textPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    textPaintMethod.UpdateOverlayModifier(AceType::RawPtr(paintWrapper));
    auto OverlayModifier = textPaintMethod.GetOverlayModifier(AceType::RawPtr(paintWrapper));
    ASSERT_NE(OverlayModifier, nullptr);
}

/**
 * @tc.name: TextAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextAccessibilityPropertyGetText001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);

    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateContent(CREATE_VALUE);
    EXPECT_EQ(textAccessibilityProperty->GetText(), CREATE_VALUE);

    auto spanNode = SpanNode::GetOrCreateSpanNode(ElementRegister::GetInstance()->MakeUniqueId());
    frameNode->AddChild(spanNode);
    textPattern->textForDisplay_ = TEXT_CONTENT;
    EXPECT_EQ(textAccessibilityProperty->GetText(), TEXT_CONTENT);
}

/**
 * @tc.name: TextAccessibilityPropertyIsSelected001
 * @tc.desc: Test IsSelected of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextAccessibilityPropertyIsSelected001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_FALSE(textAccessibilityProperty->IsSelected());
    textAccessibilityProperty->SetSelected(true);
    EXPECT_TRUE(textAccessibilityProperty->IsSelected());
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionStart001
 * @tc.desc: Test GetTextSelectionStart of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextAccessibilityPropertyGetTextSelectionStart001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionStart(), TEXT_ERROR);
    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionStart(), 0);
}

/**
 * @tc.name: TextAccessibilityPropertyGetTextSelectionEnd001
 * @tc.desc: Test GetTextSelectionEnd of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextAccessibilityPropertyGetTextSelectionEnd001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionEnd(), TEXT_ERROR);
    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textAccessibilityProperty->GetTextSelectionEnd(), TEXT_SIZE_INT);
}

/**
 * @tc.name: TextAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    TextModelNG textModel;
    textModel.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textAccessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = textAccessibilityProperty->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_COPY);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SET_SELECTION);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: TextModelNgTest001
 * @tc.desc: test text_model_ng.cpp SetHeightAdaptivePolicy and SetTextShadow
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextModelNgTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetHeightAdaptivePolicy and SetTextShadow.
     * @tc.expected: The HeightAdaptivePolicyValue of textLayoutProperty is MAX_LINES_FIRST.
     *               The TextShadowValue of textLayoutProperty is textShadow.
     */
    TextModelNG text;
    text.Create("text");
    text.SetHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    Shadow textShadow;
    text.SetTextShadow({ textShadow });
    EXPECT_EQ(textLayoutProperty->GetHeightAdaptivePolicyValue(TextHeightAdaptivePolicy::MAX_LINES_FIRST),
        TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(*textLayoutProperty->GetTextShadowValue({ textShadow }).begin(), textShadow);
}

/**
 * @tc.name: TextPatternTest001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPatternTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateNodePaintMethod function.
     * @tc.expected: The return value of CreateNodePaintMethod is not empty.
     *               textPattern's textContentModifier_ is not empty.
     *               textPattern's textOverlayModifier_ is not empty.
     */
    auto nodePaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);
    ASSERT_NE(textPattern->contentMod_, nullptr);
    ASSERT_NE(textPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: TextPatternTest002
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPatternTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateLayoutProperty function.
     * @tc.expected: The return value of CreateLayoutProperty is not empty.
     */
    RefPtr<LayoutProperty> textLayoutProperty = textPattern->CreateLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
}

/**
 * @tc.name: TextPatternTest003
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPatternTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. call CreateLayoutAlgorithm function.
     * @tc.expected: The return value of CreateLayoutAlgorithm is not empty.
     */
    RefPtr<LayoutAlgorithm> textLayoutAlgorithm = textPattern->CreateLayoutAlgorithm();
    ASSERT_NE(textLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: TextPatternTest004
 * @tc.desc: Test the CopyOption value while in Marquee state.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPatternTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode("", 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set the TextOverflow value to Marquee.
     */
    auto textLayoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: step3. call OnModifyDone function.
     * @tc.expected: The copyOption_ value is equal to CopyOptions::None.
     */
    textPattern->OnModifyDone();
    EXPECT_EQ(textPattern->copyOption_, CopyOptions::None);
}

/**
 * @tc.name: CreateParagraph001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CreateParagraph001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle);
    EXPECT_CALL(*paragraph, AddText);
    EXPECT_CALL(*paragraph, Build);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: Layout001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, Layout001, TestSize.Level1)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    layoutWrapper->children_.push_back(layoutWrapper);
    auto imageSpanNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageSpanNode, nullptr);
}

/**
 * @tc.name: ApplyIndents001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ApplyIndents001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    rowLayoutAlgorithm->ApplyIndent(textStyle, RECT_WIDTH_VALUE);
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AddChildSpanItem001
 * @tc.desc: test text_pattern.h CreateNodePaintMethod function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, AddChildSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    DirtySwapConfig config;
    config.skipMeasure = false;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    TextStyle textStyle;
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    pattern->AddChildSpanItem(element);
    auto ret = rowLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ShowSelectOverlay003
 * @tc.desc: test text_pattern.h ShowSelectOverlay function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowSelectOverlay003, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    // copyOption = None
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);

    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    pattern->textForDisplay_ = "test";
    pattern->textSelector_.Update(0, 20);

    pattern->ShowSelectOverlay(pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle);
    EXPECT_NE(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_NE(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: ShowSelectOverlay004
 * @tc.desc: test text_pattern.h ShowSelectOverlay function when menuOptionItems_ is not nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowSelectOverlay004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    /**
     * @tc.steps: step2. construct menuOptionItems
     */
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    pattern->textForDisplay_ = "test";
    pattern->textSelector_.Update(0, 20);
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    pattern->menuOptionItems_ = menuOptionItems;

    /**
     * @tc.steps: step2. call ShowSelectOverlay function
     * @tc.expected: the property of selectInfo is assigned.
     */
    pattern->ShowSelectOverlay(pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
}

/**
 * @tc.name: IsDraggable001
 * @tc.desc: test text_pattern.h Draggable function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, IsDraggable001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    auto [host, pattern] = Init();
    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->paragraph_ = paragraph;
    host->draggable_ = true;
    host->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });

    /**
     * @tc.steps: step1. set selected rect to [0, 0] - [20, 20]
     * @tc.expected: return true if the location is in region
     */
    pattern->textSelector_.Update(0, 20);
    EXPECT_TRUE(pattern->IsDraggable(Offset(1, 1)));

    /**
     * @tc.expected: return false if the location is not in region
     */
    EXPECT_FALSE(pattern->IsDraggable(Offset(21, 21)));

    /**
     * @tc.steps: step2. text not selected
     * @tc.expected: return false
     */
    pattern->textSelector_.Update(-1);
    EXPECT_FALSE(pattern->IsDraggable(Offset(1, 1)));
}

/**
 * @tc.name: DragBase001
 * @tc.desc: test text_pattern.h DragBase function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, DragBase001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();

    // test ResetSelection should reset textSelector
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    pattern->CloseSelectOverlay();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    pattern->ResetSelection();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    // test GetTextBoxes and GetLineHeight
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->paragraph_ = paragraph;
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    pattern->textSelector_.Update(0, 20);
    auto boxes = pattern->GetTextBoxes();
    EXPECT_EQ(boxes.size(), 1);
    EXPECT_EQ(boxes[0].Left(), 0);
    EXPECT_EQ(boxes[0].Right(), 20);

    auto height = pattern->GetLineHeight();
    EXPECT_EQ(height, 20);
}

/**
 * @tc.name: TextDecorationStyleTest001
 * @tc.desc: test text_model_ng.cpp SetTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationStyleTest001, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE);
    text.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: TextDecorationStyleTest002
 * @tc.desc: Test TextDecorationStyle of Text will be inheritted by Span
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text FrameNode and set TextDecoration values
     * @tc.expected: Successfully created parent Node
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    textModelNG.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textModelNG.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. create spanNode without setting TextDecoration values
     * @tc.expected: Successfully created spanNode
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step3. SpanNode mount to parent
     */
    textFrameNode->AddChild(spanNode);

    /**
     * @tc.steps: step4. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: spanNode inherits parent property
     */
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(spanNode->GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(spanNode->GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: TextDecorationStyleTest003
 * @tc.desc: Test TextDecorationStyle of Text won't override that of Span
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text FrameNode and set TextDecoration values
     * @tc.expected: Successfully created parent Node
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    textModelNG.SetTextDecoration(TextDecoration::LINE_THROUGH);
    textModelNG.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto textFrameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step2. create spanNode1 and set TextDecoration values
     * @tc.expected: Successfully created spanNode1
     */
    SpanModelNG spanModelNG1;
    spanModelNG1.Create(CREATE_VALUE);
    spanModelNG1.SetTextDecoration(TextDecoration::OVERLINE);
    spanModelNG1.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    auto spanNode1 = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step3. create spanNode2 without setting TextDecoration values
     * @tc.expected: Successfully created spanNode2
     */
    SpanModelNG spanModelNG2;
    spanModelNG2.Create(TEXT_CONTENT);
    auto spanNode2 = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: step4. SpanNode mount to parent
     */
    textFrameNode->AddChild(spanNode1);
    textFrameNode->AddChild(spanNode2);

    /**
     * @tc.steps: step5. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: spanNode1 uses own property and spanNode2 inherits parent property
     */
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(spanNode1->GetTextDecoration(), TextDecoration::OVERLINE);
    EXPECT_EQ(spanNode1->GetTextDecorationStyle(), TextDecorationStyle::WAVY);
    EXPECT_EQ(spanNode2->GetTextDecoration(), TextDecoration::LINE_THROUGH);
    EXPECT_EQ(spanNode2->GetTextDecorationStyle(), TextDecorationStyle::DOUBLE);
}

/**
 * @tc.name: TextDecorationToJsonValue001
 * @tc.desc: Test Text Decoration ToJsonValue when values set.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationToJsonValue001, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE);
    text.SetTextDecoration(TextDecoration::LINE_THROUGH);
    text.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    text.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == TEXT_COLOR_VALUE.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: TextDecorationToJsonValue002
 * @tc.desc: Test Text Decoration ToJsonValue when default values.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationToJsonValue002, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(
        decorationJson->GetValue("type")->GetString() == V2::ConvertWrapTextDecorationToStirng(TextDecoration::NONE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(TextDecorationStyle::SOLID));
}

/**
 * @tc.name: TextDecorationToJsonValue003
 * @tc.desc: Test Text Decoration ToJsonValue when set multiple textShadows.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextDecorationToJsonValue003, TestSize.Level1)
{
    TextModelNG text;
    text.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    Shadow textShadow1 = Shadow();
    Shadow textShadow2 = Shadow();
    textShadow1.SetColor(Color::RED);
    textShadow2.SetColor(Color::WHITE);
    std::vector<Shadow> shadows { textShadow1, textShadow2 };
    textLayoutProperty->UpdateTextShadow(shadows);
    auto json = JsonUtil::Create(true);
    textLayoutProperty->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("textShadow"));
    auto textShadowJson = json->GetValue("textShadow");
    EXPECT_TRUE(textShadowJson->IsArray());
}

/**
 * @tc.name: UpdateChildProperty001
 * @tc.desc: test UpdateChildProperty function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UpdateChildProperty001, TestSize.Level1)
{
    TestProperty testProperty;
    testProperty.fontSizeValue = std::make_optional(FONT_SIZE_VALUE);
    testProperty.textColorValue = std::make_optional(TEXT_COLOR_VALUE);
    testProperty.italicFontStyleValue = std::make_optional(ITALIC_FONT_STYLE_VALUE);
    testProperty.fontWeightValue = std::make_optional(FONT_WEIGHT_VALUE);
    testProperty.textDecorationValue = std::make_optional(TEXT_DECORATION_VALUE);
    testProperty.textDecorationColorValue = std::make_optional(TEXT_DECORATION_COLOR_VALUE);
    testProperty.textCaseValue = std::make_optional(TEXT_CASE_VALUE);
    testProperty.letterSpacing = std::make_optional(LETTER_SPACING);
    testProperty.lineHeightValue = std::make_optional(LINE_HEIGHT_VALUE);
    testProperty.fontFamilyValue = std::make_optional(FONT_FAMILY_VALUE);
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update parent FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(host, nullptr);
    SpanModelNG spanModelNG;
    spanModelNG.Create("span1");
    auto firstChild = ViewStackProcessor::GetInstance()->Finish();
    spanModelNG.Create("span2");
    auto secondChild = ViewStackProcessor::GetInstance()->Finish();

    /**
     * @tc.steps: step2. SpanNode mount to parent
     */
    host->AddChild(firstChild);
    host->AddChild(secondChild);

    /**
     * @tc.steps: step3. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: child count is not empty, Child inherits parent property
     */
    auto pattern = host->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(host->GetChildren().size(), 2);
    for (const auto& child : host->GetChildren()) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        ASSERT_NE(spanNode, nullptr);
        EXPECT_EQ(spanNode->GetFontSize().value(), FONT_SIZE_VALUE);
        EXPECT_EQ(spanNode->GetTextColor().value(), TEXT_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetItalicFontStyle().value(), ITALIC_FONT_STYLE_VALUE);
        EXPECT_EQ(spanNode->GetFontWeight().value(), FONT_WEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetTextDecoration().value(), TEXT_DECORATION_VALUE);
        EXPECT_EQ(spanNode->GetTextDecorationColor().value(), TEXT_DECORATION_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetTextCase().value(), TEXT_CASE_VALUE);
        EXPECT_EQ(spanNode->GetLetterSpacing().value(), LETTER_SPACING);
        EXPECT_EQ(spanNode->GetLineHeight().value(), LINE_HEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetFontFamily().value(), FONT_FAMILY_VALUE);
    }

    /**
     * @tc.steps: step4. Update parent fontsize property, called BeforeCreateLayoutWrapper again
     * @tc.expected: Child update fontsize property
     */
    TestUpdateScenario(pattern);
}

/**
 * @tc.name: UpdateChildProperty002
 * @tc.desc: test UpdateChildProperty function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, UpdateChildProperty002, TestSize.Level1)
{
    TestProperty testProperty;
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update child FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(host, nullptr);
    auto firstChild = CreateSpanNodeWithSetDefaultProperty("SPANNODE");
    auto secondChild = CreateSpanNodeWithSetDefaultProperty("spanNode");

    /**
     * @tc.steps: step2. SpanNode mount to parent
     */
    host->AddChild(firstChild);
    host->AddChild(secondChild);

    /**
     * @tc.steps: step3. called BeforeCreateLayoutWrapper function to UpdateChildProperty
     * @tc.expected: child count is not empty, Child use owner property
     */
    auto pattern = host->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(host->GetChildren().size(), 2);
    for (const auto& child : host->GetChildren()) {
        auto spanNode = AceType::DynamicCast<SpanNode>(child);
        ASSERT_NE(spanNode, nullptr);
        EXPECT_EQ(spanNode->GetFontSize().value(), FONT_SIZE_VALUE);
        EXPECT_EQ(spanNode->GetTextColor().value(), TEXT_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetItalicFontStyle().value(), ITALIC_FONT_STYLE_VALUE);
        EXPECT_EQ(spanNode->GetFontWeight().value(), FONT_WEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetTextDecoration().value(), TEXT_DECORATION_VALUE);
        EXPECT_EQ(spanNode->GetTextDecorationColor().value(), TEXT_DECORATION_COLOR_VALUE);
        EXPECT_EQ(spanNode->GetTextCase().value(), TEXT_CASE_VALUE);
        EXPECT_EQ(spanNode->GetLetterSpacing().value(), LETTER_SPACING);
        EXPECT_EQ(spanNode->GetLineHeight().value(), LINE_HEIGHT_VALUE);
        EXPECT_EQ(spanNode->GetFontFamily().value(), FONT_FAMILY_VALUE);
    }

    /**
     * @tc.steps: step4. Update parent fontsize property, called BeforeCreateLayoutWrapper again
     * @tc.expected: Child use owner property
     */
    TestUpdateScenario(pattern);
}

/**
 * @tc.name: InitSurfaceChangedTest001
 * @tc.desc: test InitSurfaceChangedCallback function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, InitSurfaceChangedTest001, TestSize.Level1)
{
    TestProperty testProperty;
    /**
     * @tc.steps: step1. create text FrameNode and SpanNode, Update child FrameNode properties
     * @tc.expected: Successfully created parent Node and child Node
     */
    auto host = CreateTextParagraph(CREATE_VALUE, testProperty);
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. get text pattern called InitSurfaceChangedCallback function.
     * @tc.expected: HasSurfaceChangedCallback return true.
     */
    auto pattern = host->GetPattern<TextPattern>();
    pattern->InitSurfaceChangedCallback();
    EXPECT_TRUE(pattern->HasSurfaceChangedCallback());
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test test_pattern.h HandleClickEvent function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. create GestureEvent and call HandleClickEvent function
     * @tc.expected: selectOverlay is closed
     */
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandleClickEvent002
 * @tc.desc: test test_pattern.h HandleClickEvent function when spanItemChildren is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleClickEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step4. create GestureEvent and call HandleClickEvent function with invalid textSelector
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    pattern->HandleClickEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -2);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -2);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2.call OnVisibleChange function
     * @tc.expected: selectOverlay is closed
     */
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);
    pattern->OnVisibleChange(false);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);

    /**
     * @tc.steps: step3. create MouseEvent and call HandleMouseEvent function when copyOption is none
     * @tc.expected: selectOverlay is closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(1, 1);
    pattern->copyOption_ = copyOption;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = "test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: test test_pattern.h HandleMouseEvent function when copyOption is not none
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = "test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: selectOverlay is not closed
     */
    MouseInfo info;
    // none none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::NONE_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left none
    pattern->textSelector_.Update(0, 3);
    info.localLocation_ = Offset(2, 2);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // right none
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::NONE;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    // left press
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left move
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::MOVE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    // left RELEASE
    pattern->textSelector_.Update(0, 3);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 0);

    pattern->textSelector_.Update(0, 3);
    pattern->blockPress_ = false;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
}

/**
 * @tc.name: HandleMouseEvent004
 * @tc.desc: test test_pattern.h HandleMouseEvent function when isDoubleClick_ is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = "test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. create MouseInfo and call HandleMouseEvent function
     * @tc.expected: isDoubleClick_ is false
     */
    MouseInfo info;
    // left RELEASE
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->blockPress_ = true;
    pattern->isDoubleClick_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_FALSE(pattern->isDoubleClick_);
}

/**
 * @tc.name: HandleMouseEvent005
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitMouseEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create("1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();

    AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    pattern->aiSpanMap_ = aiSpanMap;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->paragraph_ = paragraph;
    pattern->CreateHandles();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is in GetRectsForRange region, expect MouseRightButton release event
     *     captured by AISpan.
     */
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(5.f, 5.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(pattern->hasClickedAISpan_);

    /**
     * @tc.steps: step3. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: MouseInfo localLocation is not in GetRectsForRange region.
     */
    pattern->hasClickedAISpan_ = false;
    info.SetLocalLocation(Offset(60.f, 60.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    (*mouseEvent)(info);
    EXPECT_TRUE(!pattern->hasClickedAISpan_);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::TEXT);
}

/**
 * @tc.name: HandleMouseEvent006
 * @tc.desc: test test_pattern.h HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleMouseEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, add child imageSpanNode.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto pattern = host->GetPattern<TextPattern>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 40, 40) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    ImageSpanNodeProperty firstProperty {
        .imageSrc = std::make_optional("image")
    };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    ImageSpanNodeProperty secondProperty {
        .pixelMap = std::make_optional(PixelMap::CreatePixelMap(nullptr)),
        .imageFit = std::make_optional(ImageFit::FILL)
    };
    imageSpanNode = CreateImageSpanNode(secondProperty);
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    pattern->CreateHandles();

    /**
     * @tc.steps: step2. test text_pattern.h HandleMouseRightButton function.
     * @tc.expect: expect selectedType_ IMAGE when mouse release offset not in textContentRect region.
     */
    pattern->paragraph_ = paragraph;
    auto inputHub = host->GetEventHub<EventHub>()->GetOrCreateInputEventHub();
    auto mouseEvent = inputHub->mouseEventActuator_->inputEvents_.back();
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    (*mouseEvent)(info);
    info.SetLocalLocation(Offset(40.f, 40.f));
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->contentRect_ = { 30, 30, 20, 20 };
    (*mouseEvent)(info);
    EXPECT_EQ(pattern->textResponseType_, TextResponseType::RIGHT_CLICK);
    EXPECT_EQ(pattern->selectedType_, TextSpanType::IMAGE);
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleOnCopy001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function when textSelector is valid and textStart is equal to textEnd
     * @tc.steps: step3. call HandleOnCopy function when textSelector is not valid and textStart < 0
     * @tc.expected: selectOverlay is closed
     */
    std::vector<std::vector<int32_t>> params = { { 2, 2 }, { -1, 20 } };
    for (int turn = 0; turn < params.size(); turn++) {
        pattern->textSelector_.Update(params[turn][0], params[turn][1]);
        pattern->HandleOnCopy();
        EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
        EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    }
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test test_pattern.h HandleOnCopy function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. call HandleOnCopy function with valid textSelector and copyOption
     * @tc.expected: selectOverlay is closed
     */
    pattern->textSelector_.Update(0, 6);
    pattern->textForDisplay_ = "TestHandleOnCopy";
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->HandleOnCopy();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: HandlePanStart001
 * @tc.desc: test text_pattern.h HandlePanStart function when IsDraggable is false
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandlePanStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->copyOption_ = copyOption;
    pattern->textSelector_.Update(0, 20);
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    /**
     * @tc.steps: step2. call HandlePanStart function
     * @tc.expected: The function exits normally
     */
    pattern->HandlePanStart(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
}

/**
 * @tc.name: HandlePanStart002
 * @tc.desc: test text_pattern.h HandlePanStart function when IsDraggable is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandlePanStart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    frameNode->draggable_ = true;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_CONTENT;
    pattern->selectOverlayProxy_ = nullptr;
    GestureEvent info;
    info.localLocation_ = Offset(1.0, 1.0);

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. call HandlePanStart function
     * @tc.expected: The function exits normally
     */
    pattern->HandlePanStart(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is false
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleLongPress001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    frameNode->draggable_ = false;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    EXPECT_FALSE(pattern->IsDraggable(info.GetLocalLocation()));

    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 1);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: test text_pattern.h HandleLongPress function when IsDraggable is true
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleLongPress002, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream).WillRepeatedly(Return(true));
    EXPECT_CALL(*paragraph, GetWordBoundary).WillRepeatedly(Return(false));
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).Times(2).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    frameNode->draggable_ = true;
    frameNode->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    pattern->paragraph_ = paragraph;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 3);
    pattern->textForDisplay_ = TEXT_CONTENT;
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    /**
     * @tc.steps: step2. call HandleLongPress function
     * @tc.expected: The function exits normally
     */
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 3);
}

/**
 * @tc.name: HandlePanUpdateAndEnd001
 * @tc.desc: test text_pattern.h HandlePanUpdate function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandlePanUpdateAndEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->textSelector_.Update(0, 20);
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);

    /**
     * @tc.steps: step2. construct dragWindow_
     */
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto rect = pipelineContext->GetCurrentWindowRect();
    auto contentRect_ = CONTENT_RECT;
    pattern->HandlePanUpdate(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    pattern->HandlePanEnd(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
    // create textdrag window
    auto dragWindow = DragWindow::CreateTextDragWindow("APP_DRAG_WINDOW",
        static_cast<int32_t>(host->GetPaintRectOffset().GetX() + rect.Left()),
        static_cast<int32_t>(host->GetPaintRectOffset().GetY() + rect.Top()),
        static_cast<int32_t>(contentRect_.Width() + contentRect_.GetX()), contentRect_.Height() + contentRect_.GetY());
    pattern->dragWindow_ = dragWindow;
    pattern->HandlePanEnd(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);

    dragWindow = DragWindow::CreateTextDragWindow("APP_DRAG_WINDOW",
        static_cast<int32_t>(host->GetPaintRectOffset().GetX() + rect.Left()),
        static_cast<int32_t>(host->GetPaintRectOffset().GetY() + rect.Top()),
        static_cast<int32_t>(contentRect_.Width() + contentRect_.GetX()), contentRect_.Height() + contentRect_.GetY());
    pattern->dragWindow_ = dragWindow;

    /**
     * @tc.steps: step3. call HandlePanUpdate function
     * @tc.expected: The function exits normally
     */
    pattern->HandlePanUpdate(info);
    EXPECT_NE(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_NE(pattern->textSelector_.GetTextEnd(), -1);

    /**
     * @tc.steps: step4. construct dragProxy_
     */
    // draw select text on drag window
    pattern->dragWindow_->DrawTextNG(pattern->paragraph_, pattern);
    // add select data to clipboard
    auto manager = pipelineContext->GetDragDropManager();
    ASSERT_NE(manager, nullptr);
    auto dragDropProxy = manager->CreateTextDragDropProxy();
    ASSERT_NE(dragDropProxy, nullptr);
    pattern->dragDropProxy_ = dragDropProxy;

    /**
     * @tc.steps: step5. call HandlePanEnd function
     * @tc.expected: The function exits normally
     */
    pattern->HandlePanEnd(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 20);
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = "TestHandleOnSelectAll";
    pattern->selectOverlayProxy_ = nullptr;

    /**
     * @tc.steps: step2. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step3. call HandleOnSelectAll
     * @tc.expected:The function exits normally
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), pattern->textForDisplay_.length());
}

/**
 * @tc.name: HandleOnSelectAll002
 * @tc.desc: Test TextPattern HandleOnSelectAll when selectOverlayProxy is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleOnSelectAll002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    /**
     * @tc.steps: step2. construct a SelectOverlayManager and rootNode
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);

    /**
     * @tc.steps: step3. call CreateAndShowSelectOverlay
     * @tc.expected: return the proxy which has the right SelectOverlayId
     */
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    pattern->selectOverlayProxy_ = proxy;
    pattern->textForDisplay_ = "TestHandleOnSelectAll";

    /**
     * @tc.steps: step4. call HandleOnSelectAll
     * @tc.expected:textSelector updates successfully
     */
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 21);

    /**
     * @tc.steps: step5. call CloseSelectOverlay
     * @tc.expected: Related function is called
     */
    pattern->CloseSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlayProxy_->IsClosed());
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Text Accessibility PerformAction test Select ClearSelection and Copy.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create text, get text frameNode and pattern, set callback function.
     * @tc.expected: FrameNode and pattern is not null, related function is called.
     */
    MockPipelineContext::GetCurrent()->rootNode_ =
        FrameNode::CreateFrameNodeWithTree(V2::ROOT_ETS_TAG, 0, AceType::MakeRefPtr<RootPattern>());
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::None);
    textPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get text accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto textAccessibilityProperty = frameNode->GetAccessibilityProperty<TextAccessibilityProperty>();
    ASSERT_NE(textAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. When text CopyOptions is None, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());

    /**
     * @tc.steps: step4. When text CopyOptions is InApp, call the callback function in textAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(-1, -1));
    EXPECT_TRUE(textAccessibilityProperty->ActActionSetSelection(1, TEXT_SIZE_INT));
    EXPECT_TRUE(textAccessibilityProperty->ActActionClearSelection());
    EXPECT_TRUE(textAccessibilityProperty->ActActionCopy());
}

/**
 * @tc.name: TextSelectorTest001
 * @tc.desc: test Update function in TextSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextSelectorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Text.
     */
    TextModelNG textModel;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. set callback function.
     */
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    textPattern->OnModifyDone();

    /**
     * @tc.steps: step3. call callback function.
     * @tc.expected: textSelector_ update successfully.
     */
    textPattern->textSelector_.Update(0);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);

    textPattern->textSelector_.Update(0, TEXT_SIZE_INT);
    EXPECT_EQ(textPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(textPattern->textSelector_.destinationOffset, TEXT_SIZE_INT);
}

/**
 * @tc.name: TextPaintMethodTest003
 * @tc.desc: test text_paint_method.cpp UpdateContentModifier function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextPaintMethodTest003, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create textFrameNode and geometryNode.
     */
    auto [host, pattern] = Init();
    pattern->paragraph_ = paragraph;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto renderContext = host->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProperty = pattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step2. set textForDisplay_ to EMPTY_TEXT.
     */
    pattern->textForDisplay_ = EMPTY_TEXT;

    /**
     * @tc.steps: step3. create textPaintMethod and call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is empty.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    RefPtr<TextOverlayModifier> textOverlayModifier = AceType::MakeRefPtr<TextOverlayModifier>();
    TextPaintMethod textPaintMethod(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    textPaintMethod.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_EQ(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step4. set textForDisplay_ to CREATE_VALUE.
     */
    pattern->textForDisplay_ = CREATE_VALUE;

    /**
     * @tc.steps: step5. call UpdateContentModifier function.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is not empty.
     */
    renderContext = host->GetRenderContext();
    paintProperty = pattern->CreatePaintProperty();
    paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    TextPaintMethod textPaintMethod1(pattern, BASE_LINE_OFFSET_VALUE, textContentModifier, textOverlayModifier);
    textPaintMethod1.UpdateContentModifier(AceType::RawPtr(paintWrapper));
    EXPECT_NE(textContentModifier->drawObscuredRects_, std::vector<RectF>());

    /**
     * @tc.steps: step6. push UNKNOWN_REASON and PLACEHOLDER to reasons.
     *                   set obscured of renderContext to reasons.
     */
    std::vector<ObscuredReasons> reasons;
    reasons.push_back((ObscuredReasons)UNKNOWN_REASON);
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    renderContext->UpdateObscured(reasons);

    /**
     * @tc.steps: step7. call OnModifyDone function.
     * @tc.expected: The obscured of renderContext is reasons.
     */
    pattern->OnModifyDone();
    EXPECT_EQ(renderContext->GetObscured(), reasons);
}

/**
 * @tc.name: TextContentModifier003
 * @tc.desc: test text_content_modifier.cpp onDraw function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextContentModifier003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and geometryNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. set context.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step3. call onDraw function of textContentModifier.
     * @tc.expected: The obscuredReasons_ of textContentModifier is empty.
     *               The ifHaveSpanItemChildren_ of textContentModifier is false.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->obscuredReasons_, std::vector<ObscuredReasons>());
    EXPECT_EQ(textContentModifier->ifHaveSpanItemChildren_, false);

    /**
     * @tc.steps: step4. set ifHaveSpanItemChildren_ to true.
     */
    textContentModifier->SetIfHaveSpanItemChildren(true);

    /**
     * @tc.steps: step5. call onDraw function of textContentModifier.
     * @tc.expected: The obscuredReasons_ of textContentModifier is empty.
     *               The ifHaveSpanItemChildren_ of textContentModifier is true.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->obscuredReasons_, std::vector<ObscuredReasons>());
    EXPECT_EQ(textContentModifier->ifHaveSpanItemChildren_, true);

    /**
     * @tc.steps: step6. push UNKNOWN_REASON and PLACEHOLDER to reasons.
     *                   set obscuredReasons_ to reasons.
     */
    std::vector<ObscuredReasons> reasons;
    reasons.push_back((ObscuredReasons)UNKNOWN_REASON);
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    textContentModifier->SetObscured(reasons);

    /**
     * @tc.steps: step7. call onDraw function of textContentModifier.
     * @tc.expected: The obscuredReasons_ of textContentModifier is reasons.
     *               The ifHaveSpanItemChildren_ of textContentModifier is true.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->obscuredReasons_, reasons);
    EXPECT_EQ(textContentModifier->ifHaveSpanItemChildren_, true);

    /**
     * @tc.steps: step8. set ifHaveSpanItemChildren_ to false.
     */
    textContentModifier->SetIfHaveSpanItemChildren(false);

    /**
     * @tc.steps: step9. call onDraw function of textContentModifier.
     * @tc.expected: The obscuredReasons_ of textContentModifier is reasons.
     *               The ifHaveSpanItemChildren_ of textContentModifier is false.
     */
    textContentModifier->onDraw(context);
    EXPECT_EQ(textContentModifier->obscuredReasons_, reasons);
    EXPECT_EQ(textContentModifier->ifHaveSpanItemChildren_, false);
}

/**
 * @tc.name: TextContentModifier004
 * @tc.desc: test text_content_modifier.cpp DrawObscuration function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextContentModifier004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto textPaintMethod = textPattern->CreateNodePaintMethod();
    ASSERT_NE(textPaintMethod, nullptr);
    auto textContentModifier = textPattern->GetContentModifier();
    ASSERT_NE(textContentModifier, nullptr);

    /**
     * @tc.steps: step2. set context and paragraph.
     *                   set defaultFontSize defaultTextColor and contentSize of textContentModifier.
     *                   push one rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, ClipRect(_, _)).WillRepeatedly(Return());
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    DrawingContext context { canvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    textContentModifier->SetParagraph(paragraph);
    TextStyle textStyle;
    textStyle.SetFontSize(ADAPT_FONT_SIZE_VALUE);
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textContentModifier->SetDefaultAnimatablePropertyValue(textStyle);
    SizeF contentSize(TEXT_CONTENT_SIZE, TEXT_CONTENT_SIZE);
    textContentModifier->SetContentSize(contentSize);
    std::vector<RectF> drawObscuredRects;
    RectF textRect;
    textRect.SetHeight(TEXT_RECT_WIDTH);
    textRect.SetWidth(TEXT_RECT_WIDTH);
    textRect.SetTop(TEXT_RECT_TOP_ONE);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step3. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step4. push two rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    drawObscuredRects.push_back(textRect);
    textRect.SetTop(TEXT_RECT_TOP_TWO);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step5. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step6. push three rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetHeight(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step7. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);

    /**
     * @tc.steps: step8. push four rect to drawObscuredRects and set drawObscuredRects_ to drawObscuredRects.
     */
    textRect.SetWidth(TEXT_RECT_SIZE_ZEOR);
    drawObscuredRects.push_back(textRect);
    textContentModifier->SetDrawObscuredRects(drawObscuredRects);

    /**
     * @tc.steps: step9. call DrawObscuration function of textContentModifier.
     * @tc.expected: The drawObscuredRects_ of textContentModifier is drawObscuredRects.
     */
    textContentModifier->DrawObscuration(context);
    EXPECT_EQ(textContentModifier->drawObscuredRects_, drawObscuredRects);
}

/*
 * @tc.name: TextModelSetFont001
 * @tc.desc: Test if SetFont is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextModelSetFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. call SetFont and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    textModelNG.SetFont(font);
    EXPECT_EQ(textLayoutProperty->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(textLayoutProperty->GetFontWeight().value(), FontWeight::BOLD);
    EXPECT_EQ(textLayoutProperty->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(textLayoutProperty->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
}

/**
 * @tc.name: TextModelGetFont001
 * @tc.desc: Test if GetFont is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextModelGetFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. not set and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    EXPECT_EQ(textLayoutProperty->GetFont(), TEXT_DEFAULT_VALUE);

    /**
     * @tc.steps: step2. call SetFont and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    textModelNG.SetFont(font);
    EXPECT_EQ(textLayoutProperty->GetFont(), TEXT_EQUALS_VALUE);
}

/**
 * @tc.name: BetweenSelectedPosition001
 * @tc.desc: test text_pattern.cpp BetweenSelectedPosition function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BetweenSelectedPosition001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    host->draggable_ = true;
    host->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });

    /**
     * @tc.steps: step2. set selected rect to [0, 0] - [20, 20]
     */
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running the BetweenSelectedPosition function and check the result with expected results.
     */
    std::vector<Offset> cases = { Offset(1, 1), Offset(21, 21) };
    std::vector<bool> exceptResults = { true, false };
    for (uint32_t turn = 0; turn < cases.size(); ++turn) {
        EXPECT_EQ(pattern->BetweenSelectedPosition(cases[turn]), exceptResults[turn]);
    }
}

/**
 * @tc.name: OnHandleMove002
 * @tc.desc: test text_pattern.cpp OnHandleMove function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnHandleMove002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr);
    pattern->selectOverlayProxy_ = proxy;
    pipeline->rootNode_->GetGeometryNode()->SetFrameOffset({ 3.0, 5.0 });

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running the OnHandleMove function and check the result with expected results.
     */
    std::vector<RectF> handleRects = { { 1.0, 2.0, 3.0, 4.0 }, { 5.0, 6.0, 7.0, 8.0 }, { -9.0, -10.0, 11.0, 12.0 } };
    std::vector<vector<TextSelector>> expectResults = { { TextSelector(0, -1), TextSelector(0, 0) },
        { TextSelector(0, 0), TextSelector(0, 0) }, { TextSelector(0, 0), TextSelector(0, 0) } };
    for (uint32_t turn = 0; turn < handleRects.size(); ++turn) {
        pattern->OnHandleMove(handleRects[turn], true);
        EXPECT_EQ(pattern->textSelector_, expectResults[turn][0]);
        pattern->OnHandleMove(handleRects[turn], false);
        EXPECT_EQ(pattern->textSelector_, expectResults[turn][1]);
    }
}

/**
 * @tc.name: GetGlobalOffset001
 * @tc.desc: test text_pattern.cpp GetGlobalOffset function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetGlobalOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto pipeline = PipelineContext::GetCurrentContext();

    /**
     * @tc.steps: step3. construct 3 groups cases and corresponding expected results.
     * @tc.expected: Running GetGlobalOffset function and check the result with expected results.
     */
    std::vector<OffsetF> offsetCases = { { 3.0, 5.0 }, { 4.0, 5.0 }, { 6.0, 7.0 } };
    std::vector<Offset> expectResults = { { -3.0, -5.0 }, { -4.0, -5.0 }, { -6.0, -7.0 } };
    for (uint32_t turn = 0; turn < offsetCases.size(); ++turn) {
        pipeline->rootNode_->GetGeometryNode()->SetFrameOffset(offsetCases[turn]);
        Offset tmp;
        pattern->GetGlobalOffset(tmp);
        EXPECT_EQ(tmp, expectResults[turn]);
    }
}

/**
 * @tc.name: CreateImageSpanAndLayout001
 * @tc.desc: test text_layout_algorithm.cpp CreateImageSpanAndLayout function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CreateImageSpanAndLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContext();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    /**
     * @tc.steps: step2. Add Text and Image Span.
     */
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        frameNode, AceType::MakeRefPtr<GeometryNode>(), frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    layoutWrapper->children_.push_back(layoutWrapper);

    auto textSpanNode = CreateSpanNodeWithSetDefaultProperty("this is a test.");
    ASSERT_NE(textSpanNode, nullptr);
    pattern->AddChildSpanItem(textSpanNode);
    frameNode->AddChild(textSpanNode);
    nodeId = stack->ClaimNodeId();
    auto imageSpanNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageSpanNode, nullptr);
    pattern->AddChildSpanItem(imageSpanNode);
    frameNode->AddChild(imageSpanNode);

    /**
     * @tc.steps: step3. Init TextLayoutAlgorithm and Paragraph, then run the CreateImageSpanAndLayout Func.
     * @tc.expected: Construct result is True.
     */
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    rowLayoutAlgorithm->CreateParagraph(textStyle, "", AceType::RawPtr(frameNode));
    auto ret = rowLayoutAlgorithm->CreateImageSpanAndLayout(
        textStyle, "", contentConstraint, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ApplyIndents002
 * @tc.desc: test text_layout_algorithm.cpp ApplyIndents function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ApplyIndents002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. construct textStyle with TextIndent 5.
     */
    TextStyle textStyle;
    textStyle.SetTextIndent(Dimension(5));
    rowLayoutAlgorithm->CreateParagraph(textStyle, "This is a test.", AceType::RawPtr(host));

    /**
     * @tc.steps: step3. run the ApplyIndents Func.
     * @tc.expected: paragraph_.rawPtr_ is nullptr.
     */
    rowLayoutAlgorithm->ApplyIndent(textStyle, 10.0);
    EXPECT_NE(rowLayoutAlgorithm->paragraph_.rawPtr_, nullptr);
}

/**
 * @tc.name: ApplyIndents003
 * @tc.desc: test text_layout_algorithm.cpp ApplyIndents function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ApplyIndents003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. construct textStyle with TextIndent 5 and type is DimensionUnit::PERCENT.
     */
    TextStyle textStyle;
    textStyle.SetTextIndent(Dimension(5, DimensionUnit::PERCENT));
    rowLayoutAlgorithm->CreateParagraph(textStyle, "This is a test.", AceType::RawPtr(host));

    /**
     * @tc.steps: step3. run the ApplyIndents Func.
     * @tc.expected: paragraph_.rawPtr_ is nullptr.
     */
    rowLayoutAlgorithm->ApplyIndent(textStyle, 10.0);
    EXPECT_NE(rowLayoutAlgorithm->paragraph_.rawPtr_, nullptr);
}

/**
 * @tc.name: SetDraggable001
 * @tc.desc: test text_model_ng.cpp SetDraggable function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetDraggable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());

    /**
     * @tc.steps: step3. construct 2 groups cases and corresponding expected results.
     * @tc.expected: Running SetDraggable function and check the result with expected results.
     */
    std::vector<bool> cases = { true, false };
    std::vector<bool> expectResult = { true, false };
    for (uint32_t turn = 0; turn < cases.size(); ++turn) {
        textModelNG.SetDraggable(cases[turn]);
        EXPECT_EQ(frameNode->IsDraggable(), expectResult[turn]);
    }
}

/**
 * @tc.name: SetMenuOptionItems001
 * @tc.desc: test text_model_ng.cpp SetMenuOptionItems function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetMenuOptionItems001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());

    /**
     * @tc.steps: step2. construct menuOptionItems.
     * @tc.expected: Running SetMenuOptionItems function and check the result.
     */
    std::vector<MenuOptionsParam> menuOptionItems;
    MenuOptionsParam menuOptionItem1;
    menuOptionItem1.content = "test1";
    menuOptionItem1.action = [](const std::string&) {};
    menuOptionItems.emplace_back(menuOptionItem1);
    pattern->menuOptionItems_ = menuOptionItems;
    textModelNG.SetMenuOptionItems(std::move(menuOptionItems));
    EXPECT_EQ(pattern->menuOptionItems_.size(), 1);
    EXPECT_EQ(pattern->menuOptionItems_[0].ToString(), menuOptionItem1.ToString());
}

/**
 * @tc.name: ClearOnClick001
 * @tc.desc: test text_model_ng.cpp ClearOnClick function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ClearOnClick001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());

    /**
     * @tc.steps: step2. Running ClearOnClick function.
     * @tc.expected: the onClick_ will be nullptr.
     */
    textModelNG.ClearOnClick();
    EXPECT_EQ(pattern->onClick_, nullptr);
}

/**
 * @tc.name: SetFontSize001
 * @tc.desc: test text_model_ng.cpp SetFontSize function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [host, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());

    /**
     * @tc.steps: step2. Run SetFontSize with isvalid data.
     * @tc.expected: the fontsize will be Dimension(0).
     */
    textModelNG.SetFontSize(Dimension(-1));
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    const std::unique_ptr<FontStyle>& fontStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(fontStyle, nullptr);
    EXPECT_EQ(fontStyle->GetFontSize().value(), Dimension(0));
}

/**
 * @tc.name: GetLineCount001
 * @tc.desc: test text_layout_algorithm.cpp GetLineCount function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetLineCount001, TestSize.Level1)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, AddText);
    EXPECT_CALL(*paragraph, GetLineCount).WillOnce(Return(1));
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContext();

    /**
     * @tc.steps: step2. Create Paragraph
     */
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    TextStyle textStyle;
    LayoutConstraintF contentConstraint;
    rowLayoutAlgorithm->CreateParagraph(textStyle, "This is a test.", AceType::RawPtr(frameNode));

    /**
     * @tc.steps: step3. GetLineCount.
     * @tc.expected: linecount will be 1.
     */
    EXPECT_EQ(rowLayoutAlgorithm->GetLineCount(), 1);
}

/**
 * @tc.name: GetDragUpperLeftCoordinates001
 * @tc.desc: test text_layout_algorithm.cpp GetDragUpperLeftCoordinates function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetDragUpperLeftCoordinates001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern and some environment for running process.
     */
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContext();

    /**
     * @tc.steps: step3. run GetDragUpperLeftCoordinates func.
     */
    auto ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));

    pattern->dragBoxes_.push_back({});
    ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));

    pattern->dragBoxes_.push_back({ 1, 2, 3, 4 });
    ret = pattern->GetDragUpperLeftCoordinates();
    EXPECT_EQ(ret, OffsetF(0, 0));
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test on color configuration update
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    auto context = textFrameNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    context->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    auto theme = context->GetTheme<TextTheme>();
    ASSERT_NE(theme, nullptr);
    theme->textStyle_.textColor_ = Color::BLACK;
    textPattern->OnColorConfigurationUpdate();
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetTextColor(), Color::BLACK);
}

/**
 * @tc.name: GetCopyOptionString001
 * @tc.desc: Test if GetCopyOptionString is successful
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetCopyOptionString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize textModelNG and FrameNode
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto [frameNode, pattern] = Init();
    auto pipeline = frameNode->GetContext();
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step2. run GetCopyOptionString Func.
     */
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.InApp");
    textLayoutProperty->UpdateCopyOption(CopyOptions::Local);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.Local");
    textLayoutProperty->UpdateCopyOption(CopyOptions::None);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.None");
    textLayoutProperty->UpdateCopyOption(CopyOptions::Distributed);
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.Distributed");
    textLayoutProperty->UpdateCopyOption(CopyOptions(10));
    EXPECT_EQ(textLayoutProperty->GetCopyOptionString(), "CopyOptions.None");
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: test test_pattern.h HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step4. create GestureEvent and call HandleTouchEvent.
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(0, 0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));

    pattern->HandleTouchEvent(touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -2);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -2);
}

/**
 * @tc.name: HandleDoubleClickEvent001
 * @tc.desc: test test_pattern.h HandleDoubleClickEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleDoubleClickEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    std::list<RefPtr<SpanItem>> spanItemChildren;
    auto spanItemChild1 = AceType::MakeRefPtr<SpanItem>();
    spanItemChildren.emplace_back(spanItemChild1);
    pattern->spans_ = spanItemChildren;

    /**
     * @tc.steps: step3. create paragraph
     */
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    pattern->paragraph_ = paragraph;

    /**
     * @tc.steps: step4. create GestureEvent and call HandleClickEvent function quickly to trigger doubleClick.
     * @tc.expected: function run rightly
     */
    pattern->textSelector_.Update(-2, -2);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);

    // test CopyOptions is None
    pattern->copyOption_ = CopyOptions::None;
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->hasClicked_);
    pattern->HandleClickEvent(info);
    EXPECT_FALSE(pattern->hasClicked_);

    // test mouse doubleClick
    pattern->isMousePressed_ = true;
    pattern->copyOption_ = CopyOptions::Local;
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->hasClicked_);
    pattern->HandleClickEvent(info);
    EXPECT_FALSE(pattern->hasClicked_);

    // test gesture doubleClick
    pattern->isMousePressed_ = false;
    pattern->copyOption_ = CopyOptions::Local;
    pattern->HandleClickEvent(info);
    EXPECT_TRUE(pattern->hasClicked_);
    pattern->HandleClickEvent(info);
    EXPECT_FALSE(pattern->hasClicked_);
}

/**
 * @tc.name: SetTextSelection001
 * @tc.desc: test test_pattern.h SetTextSelection function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextSelection001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);

    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::None
     * @tc.expected: not selected
     */
    textModelNG.SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);

    /**
     * @tc.steps: step3. Get LayoutProperty and update CopyOption
     * @tc.expected: textSelector_ updated successfully
     */
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    textLayoutProperty->UpdateCopyOption(CopyOptions::InApp);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::NONE);
    pattern->SetTextSelection(0, 4);

    /**
     * @tc.steps: step4. enabled is false or obscured is true
     * @tc.expected: not selected
     */
    auto eventHub = pattern->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = false;
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    std::vector<ObscuredReasons> reasons;
    reasons.push_back(ObscuredReasons::PLACEHOLDER);
    renderContext->UpdateObscured(reasons);
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
    eventHub->enabled_ = true;
    pattern->SetTextSelection(0, 4);
    EXPECT_EQ(pattern->textSelector_.GetStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), -1);
}

/**
 * @tc.name: TextFrameNodeCreator004
 * @tc.desc: Test onCopy event of text.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextFrameNodeCreator004, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<TextEventHub>();
    EXPECT_TRUE(eventHub);
    std::string EventValue;
    auto Event = [&EventValue](const std::string& param) { EventValue = param; };

    textModelNG.SetOnCopy(Event);
    eventHub->SetOnCopy(std::move(Event));
    EXPECT_TRUE(eventHub->onCopy_);
}

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: Test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, BindSelectionMenu001, TestSize.Level1)
{
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TOAST_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    int32_t callBack1 = 0;
    int32_t callBack2 = 0;
    int32_t callBack3 = 0;
    std::function<void()> buildFunc = [&callBack1]() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [&callBack2](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = [&callBack3]() {
        callBack3 = 3;
        return;
    };

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    pattern->selectionMenuMap_[key] = params1;

    std::function<void()> nullFunc = nullptr;

    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK, nullFunc, onAppear, onDisappear);
    EXPECT_TRUE(pattern->selectionMenuMap_.empty());

    pattern->selectionMenuMap_[key] = params1;
    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(pattern->selectionMenuMap_.empty());

    pattern->BindSelectionMenu(TextSpanType::IMAGE, TextResponseType::RIGHT_CLICK, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(pattern->selectionMenuMap_.empty());
}

/**
 * @tc.name: CloseSelectionMenu001
 * @tc.desc: Test CloseSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, CloseSelectionMenu001, TestSize.Level1)
{
    auto textFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::TOAST_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, CREATE_VALUE);
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    pattern->SetTextController(AceType::MakeRefPtr<TextController>());
    pattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    auto textController = pattern->GetTextController();
    textController->CloseSelectionMenu();
    int32_t callBack1 = 0;
    int32_t callBack2 = 0;
    int32_t callBack3 = 0;
    std::function<void()> buildFunc = [&callBack1]() {
        callBack1 = 1;
        return;
    };

    std::function<void(int32_t, int32_t)> onAppear = [&callBack2](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = [&callBack3]() {
        callBack3 = 3;
        return;
    };
    pattern->BindSelectionMenu(TextSpanType::MIXED, TextResponseType::LONG_PRESS, buildFunc, onAppear, onDisappear);
    GestureEvent info;
    info.localLocation_ = Offset(1, 1);
    // copyOption = None
    pattern->HandleLongPress(info);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    pattern->copyOption_ = CopyOptions::Distributed;
    pattern->paragraph_ = MockParagraph::GetOrCreateMockParagraph();
    pattern->textForDisplay_ = CREATE_VALUE;
    pattern->textSelector_.Update(0, 20);

    pattern->ShowSelectOverlay(pattern->textSelector_.firstHandle, pattern->textSelector_.secondHandle);

    auto isClosed = pattern->selectOverlayProxy_->IsClosed();
    EXPECT_FALSE(isClosed);
    textController = pattern->GetTextController();
    textController->CloseSelectionMenu();
    isClosed = pattern->selectOverlayProxy_->IsClosed();
    EXPECT_TRUE(isClosed);
}

/**
 * @tc.name: OnTextSelectionChange001
 * @tc.desc: Test onTextSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnTextSelectionChange001, TestSize.Level1)
{
    auto textFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::TOAST_ETS_TAG, 2, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ACE_UPDATE_LAYOUT_PROPERTY(TextLayoutProperty, Content, CREATE_VALUE);
    auto pattern = textFrameNode->GetPattern<TextPattern>();
    pattern->SetTextController(AceType::MakeRefPtr<TextController>());
    pattern->GetTextController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(pattern)));
    pattern->textForDisplay_ = CREATE_VALUE;
    pattern->selectOverlayProxy_ = nullptr;
    ParagraphStyle paragraphStyle;
    RefPtr<Paragraph> paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    pattern->paragraph_ = paragraph;
    pattern->HandleOnSelectAll();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), pattern->textForDisplay_.length());

    pattern->ResetSelection();
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
}

/**
 * @tc.name: OnTextSelectionChange002
 * @tc.desc: Test onTextSelectionChange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, OnTextSelectionChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    /**
     * @tc.steps: step2. call SetTextSelection with CopyOptions::InApp
     * @tc.expected: longPress/gesture/input will be regist when CopyOptions not none.
     */
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    bool isSelectChanged = false;
    auto onSelectionChanged = [&isSelectChanged](int32_t, int32_t) {
        isSelectChanged = true;
    };
    textModelNG.SetOnTextSelectionChange(onSelectionChanged);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->draggable_ = true;
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    EXPECT_NE(gestureEventHub->longPressEventActuator_->longPressEvent_, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    EXPECT_TRUE(!inputHub->mouseEventActuator_->inputEvents_.empty());
    EXPECT_TRUE(!gestureEventHub->touchEventActuator_->touchEvents_.empty());

    /**
     * @tc.steps: step3. create paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->paragraph_ = paragraph;
    EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_)).WillRepeatedly(Return(0));
    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(2), Return(false)));
    GestureEvent info;
    info.localLocation_ = Offset(1, 2);
    pattern->HandleLongPress(info);
    EXPECT_EQ(isSelectChanged, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 1);

    EXPECT_CALL(*paragraph, GetWordBoundary(_, _, _))
        .WillRepeatedly(DoAll(SetArgReferee<1>(0), SetArgReferee<2>(2), Return(true)));
    pattern->HandleLongPress(info);
    EXPECT_EQ(isSelectChanged, true);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
}

/**
 * @tc.name: TextLayoutAlgorithmTest009
 * @tc.desc: test text_layout_algorithm.cpp: new method UpdateParagraphForAISpan001
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, TextLayoutAlgorithmTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    TextStyle textStyle;
    textStyle.SetMaxLines(MAX_LINES);
    textStyle.SetTextCase(TextCase::NORMAL);
    LayoutConstraintF contentConstraint;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph= MockParagraph::GetOrCreateMockParagraph();

    AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    textPattern->aiSpanMap_ = aiSpanMap;
    textPattern->textForAI_ = TEXT_FOR_AI;

    /**
     * @tc.steps: step2. Create textLayoutAlgorithm and call UpdateParagraphForAISpan function.
     * @tc.expected: textLayoutAlgorithm->paragraph_.rawPtr_ is nullptr.
     */
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->SetParagraph(paragraph);
    textLayoutAlgorithm->UpdateParagraphForAISpan(textStyle, AccessibilityManager::RawPtr(layoutWrapper));
    EXPECT_NE(textLayoutAlgorithm->paragraph_.rawPtr_, nullptr);
}

/**
 * @tc.name: ParseAIJson001
 * @tc.desc: Test TextPattern: new method ParseAIJson for TextDataDetectResult
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ParseAIJson001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Parse to JsonObject.
     * @tc.expected: parseSuccess phoneNum is not Empty.
     */

    auto detectResultJson = JsonUtil::ParseJsonString(TEXT_DATA_DETECT_RESULT.entity);
    ASSERT_NE(detectResultJson, nullptr);
    EXPECT_TRUE(detectResultJson->Contains("phoneNum"));
    auto phoneNum = detectResultJson->GetValue("phoneNum");
    EXPECT_TRUE(phoneNum->IsArray());

    /**
     * @tc.steps: step3. call ParseAIJson
     * @tc.expected:aiSpanMap_ not empty
     */
    textPattern->textForAI_ = TEXT_FOR_AI_SINGLE;
    textPattern->aiSpanMap_.clear();
    textPattern->ParseAIJson(phoneNum, TextDataDetectType::PHONE_NUMBER, 0, false);
    EXPECT_FALSE(textPattern->aiSpanMap_.empty());
}

    /**
 * @tc.name: ParseAIJson002
 * @tc.desc: Test TextPattern: new method ParseAIJson for methodOption
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ParseAIJson002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. call ParseAIResult function.
     * @tc.expected: parseSuccess any element is not Empty.
     */

    auto menuOptionJson = JsonUtil::ParseJsonString(TEXT_DATA_DETECT_RESULT.menuOption);
    ASSERT_NE(menuOptionJson, nullptr);

    EXPECT_TRUE(menuOptionJson->Contains("phoneNum"));
    auto phoneNumOpt = menuOptionJson->GetValue("phoneNum");
    EXPECT_TRUE(phoneNumOpt->IsArray());
    auto item = phoneNumOpt->GetArrayItem(0);
    EXPECT_TRUE(item->Contains("option"));
    std::string optValue = item->GetString("option");
    EXPECT_EQ(optValue, "呼叫");

    /**
     * @tc.steps: step3. call ParseAIJson to generate aiMenuOptionsMap_
     * @tc.expected:aiMenuOptionsMap_ not empty
     */
    textPattern->aiMenuOptionsMap_.clear();
    textPattern->ParseAIJson(phoneNumOpt, TextDataDetectType::PHONE_NUMBER, 0, true);
    EXPECT_FALSE(textPattern->aiMenuOptionsMap_.empty());
}

/**
 * @tc.name: ParseAIResult001
 * @tc.desc: Test TextPattern: new method ParseAIResult when methodoption is empty
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ParseAIResult001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. call ParseAIResult function.
     * @tc.expected: parseSuccess aiSpanMap_ is not Empty.
     */
    auto detectResultJson = JsonUtil::ParseJsonString(TEXT_DATA_DETECT_RESULT.entity);
    ASSERT_NE(detectResultJson, nullptr);
    EXPECT_TRUE(detectResultJson->Contains("phoneNum"));
    auto phoneNum = detectResultJson->GetValue("phoneNum");
    EXPECT_TRUE(phoneNum->IsArray());

    textPattern->textForAI_ = TEXT_FOR_AI_SINGLE;
    textPattern->aiMenuOptionsMap_.clear();
    textPattern->aiSpanMap_.clear();
    textPattern->ParseAIResult(TEXT_DATA_DETECT_RESULT, 0);
    EXPECT_FALSE(textPattern->aiSpanMap_.empty());
}

/**
 * @tc.name: ParseAIResult002
 * @tc.desc: Test TextPattern: new method ParseAIResult when methodoption is not empty
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ParseAIResult002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. call ParseAIResult function.
     * @tc.expected: parseSuccess aiSpanMap_ is not Empty.
     */
    std::unordered_map<std::string, std::vector<std::string>> menuOptionsMap;
    std::vector<std::string> menuOptionsPhone = { "呼叫", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsEmail = { "新建邮箱", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsUrl = { "打开", "复制", "选择文本" };
    std::vector<std::string> menuOptionsLocation = { "导航至该位置", "在地图中打开", "复制", "选择文本" };

    menuOptionsMap["phoneNum"] = menuOptionsPhone;
    menuOptionsMap["url"] = menuOptionsUrl;
    menuOptionsMap["email"] = menuOptionsEmail;
    menuOptionsMap["location"] = menuOptionsLocation;

    textPattern->textForAI_ = TEXT_FOR_AI_SINGLE;
    textPattern->aiMenuOptionsMap_ = menuOptionsMap;
    textPattern->aiSpanMap_.clear();
    textPattern->ParseAIResult(TEXT_DATA_DETECT_RESULT, 0);
    EXPECT_FALSE(textPattern->aiSpanMap_.empty());
}

    /**
 * @tc.name: HandleSpanSingleClickEvent
 * @tc.desc: test test_pattern.h HandleSpanSingleClickEvent function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleSpanSingleClickEvent, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);

    /**
     * @tc.steps: step2. construct spanItemChildren
     */
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    spanItemChild->content = TEXT_FOR_AI;
    spanItemChild->position = StringUtils::ToWstring(spanItemChild->content).length();
    pattern->spans_.emplace_back(spanItemChild);

    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    pattern->paragraph_ = paragraph;

    pattern->SetTextDetectEnable(true);
    RectF textContentRect = CONTENT_RECT;
    pattern->copyOption_ = CopyOptions::Distributed;

    Ace::AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_START;
    aiSpan1.end = AI_SPAN_END;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    Ace::AISpan aiSpan2;
    aiSpan2.start = AI_SPAN_START_II;
    aiSpan2.end = AI_SPAN_END_II;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    pattern->aiSpanMap_ = aiSpanMap;

    std::unordered_map<std::string, std::vector<std::string>> menuOptionsMap;
    std::vector<std::string> menuOptionsPhone = { "呼叫", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsEmail = { "新建邮箱", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsUrl = { "打开", "复制", "选择文本" };
    std::vector<std::string> menuOptionsLocation = { "导航至该位置", "在地图中打开", "复制", "选择文本" };
    menuOptionsMap["phoneNum"] = menuOptionsPhone;
    menuOptionsMap["url"] = menuOptionsUrl;
    menuOptionsMap["email"] = menuOptionsEmail;
    menuOptionsMap["location"] = menuOptionsLocation;
    pattern->aiMenuOptionsMap_ = menuOptionsMap;

    /**
     * @tc.steps: step3. create GestureEvent and call HandleSpanSingleClickEvent function.
     * @tc.expected: isClickOnAISpan is been setted true.
     */
    GestureEvent info;
    info.localLocation_ = Offset(3.0f, 3.0f);

    PointF textOffset = { info.GetLocalLocation().GetX() - textContentRect.GetX(),
    info.GetLocalLocation().GetY() - textContentRect.GetY() };

    bool isClickOnSpan = false;
    bool isClickOnAISpan = false;
    pattern->HandleSpanSingleClickEvent(info, textContentRect, textOffset, isClickOnSpan, isClickOnAISpan);
    EXPECT_TRUE(isClickOnAISpan);
}

/**
 * @tc.name: ShowUIExtensionMenu
 * @tc.desc: test test_pattern.h ShowUIExtensionMenu function with valid textSelector
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, ShowUIExtensionMenu, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, 20);
    auto textSpanNode = CreateSpanNodeWithSetDefaultProperty(TEXT_FOR_AI);
    ASSERT_NE(textSpanNode, nullptr);
    pattern->AddChildSpanItem(textSpanNode);
    pattern->SetTextDetectEnable(true);

    Ace::AISpan aiSpan;
    aiSpan.start = AI_SPAN_START;
    aiSpan.end = AI_SPAN_END;
    aiSpan.content = SPAN_PHONE;
    aiSpan.type = TextDataDetectType::PHONE_NUMBER;

    // /**
    //  * @tc.steps: step2. set pattern->aiMenuOptionsMap_ and call ShowUIExtensionMenu function
    //  * @tc.expected: ShowUIExtensionMenu result is true.
    //  */
    std::unordered_map<std::string, std::vector<std::string>> menuOptionsMap;
    std::vector<std::string> menuOptionsPhone = { "呼叫", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsEmail = { "新建邮箱", "发送信息", "新建联系人", "复制", "选择文本" };
    std::vector<std::string> menuOptionsUrl = { "打开", "复制", "选择文本" };
    std::vector<std::string> menuOptionsLocation = { "导航至该位置", "在地图中打开", "复制", "选择文本" };

    menuOptionsMap["phoneNum"] = menuOptionsPhone;
    menuOptionsMap["url"] = menuOptionsUrl;
    menuOptionsMap["email"] = menuOptionsEmail;
    menuOptionsMap["location"] = menuOptionsLocation;
    pattern->aiMenuOptionsMap_ = menuOptionsMap;

    EXPECT_TRUE(pattern->ShowUIExtensionMenu(aiSpan, nullptr, nullptr));
}

/**
 * @tc.name: InitSpanItem001
 * @tc.desc: test test_pattern.h InitSpanItem function.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, InitSpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE);
    textModelNG.SetCopyOption(CopyOptions::InApp);
    textModelNG.SetTextDetectEnable(true);
    /**
     * @tc.steps: step2. construct different child SpanNode.
     */
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto childFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, 2, []() { return AceType::MakeRefPtr<TextPattern>(); });
    host->AddChild(childFrameNode);
    childFrameNode->SetParent(host);

    auto spanNode = CreateSpanNodeWithSetDefaultProperty("spannode");
    auto spanOnClickFunc = [](GestureEvent& info) {};
    spanNode->UpdateOnClickEvent(std::move(spanOnClickFunc));
    host->AddChild(spanNode);
    spanNode->SetParent(host);

    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    auto symbolSpanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, nodeId);
    host->AddChild(symbolSpanNode);
    symbolSpanNode->SetParent(host);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);

    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    host->AddChild(placeholderSpanNode);
    placeholderSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    /**
     * @tc.steps: step3. textFrameNode Measure will call InitSpanItem/CollectSpanNodes.
     * @tc.expect: expect childSpanNode MountToParagraph, add into TextPattern spans_.
     */
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    EXPECT_EQ(textPattern->spans_.size(), 5);
    auto gesture = childFrameNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(gesture->GetHitTestMode(), HitTestMode::HTMNONE);
}

/**
 * @tc.name: HandleDragEvent001
 * @tc.desc: test test_pattern.h InitDragEvent without any childSpan, then eventHub call
 *     OnDragStartNoChild/OnDragMove/OnDragEndNoChild.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleDragEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern without childSpanNode, ViewStackProcessor Finish call
     *     InitDragEvent to set onDragStart/OnDragMove/OnDragEnd callback function.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("1234567890");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step2. test text OnDragStart.
     * @tc.expect: expect OnDragStart result return GetSelectedText range [2, 6], status: Status::DRAGGING
     */
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetOnDragStart();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "3456");
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    EXPECT_EQ(pattern->status_, Status::DRAGGING);

    /**
     * @tc.steps: step3. test OnDragMove.
     */
    eventHub->FireOnDragMove(event, "");
    EXPECT_EQ(pattern->showSelect_, false);
    /**
     * @tc.steps: step4. test text OnDragMoveEnd.
     * @tc.expect: expect onDragEnd will set status None, showSelect_ is true.
     */
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    EXPECT_EQ(pattern->showSelect_, true);
}

/**
 * @tc.name: HandleDragEvent002
 * @tc.desc: test test_pattern.h InitDragEvent with child spanNode, then eventHub call
 *     OnDragStart/OnDragMove/OnDragEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, HandleDragEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child span node.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("1234567890abcdefghijklmnopqrstuvwxyz");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto childFrameNode =
        FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, 2, []() { return AceType::MakeRefPtr<TextPattern>(); });
    // need set, otherwise will crash.
    childFrameNode->SetLayoutProperty(AceType::MakeRefPtr<ImageLayoutProperty>());
    host->AddChild(childFrameNode);
    childFrameNode->SetParent(host);
    auto spanNode = CreateSpanNodeWithSetDefaultProperty("spannode");
    auto spanOnClickFunc = [](GestureEvent& info) {};
    spanNode->UpdateOnClickEvent(std::move(spanOnClickFunc));
    host->AddChild(spanNode);
    spanNode->SetParent(host);
    auto symbolSpanNode =
        SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId());
    host->AddChild(symbolSpanNode);
    symbolSpanNode->SetParent(host);
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    host->AddChild(imageSpanNode);
    imageSpanNode->SetParent(host);
    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    host->AddChild(placeholderSpanNode);
    placeholderSpanNode->SetParent(host);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    pattern->textSelector_.Update(6, 15);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. test textPattern OnDragStart.
     * @tc.expect: expect childSpanNode selected add into dragResultObjects.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());

    /**
     * @tc.steps: step3. test get text onDragMove.
     */
    eventHub->FireOnDragMove(dragEvent, "");
    EXPECT_EQ(pattern->showSelect_, true);

    /**
     * @tc.steps: step4. test textPattern onDragMove.
     * @expect: expect dragResultObjects_ empty OnDragEnd.
     */
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(dragEvent);
    EXPECT_TRUE(pattern->dragResultObjects_.empty());
}

/**
 * @tc.name: GetTextResultObject001
 * @tc.desc: test test_pattern.h GetTextResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetTextResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with two spanNodes,
     *     firstChild is SPAN_URL, secondChild is SPAN_PHONE
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    auto spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_URL);
    host->AddChild(spanNode);
    spanNode = CreateSpanNodeWithSetDefaultProperty(SPAN_PHONE);
    host->AddChild(spanNode);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);
    EXPECT_TRUE(gesture->GetTextDraggable());
    /**
     * @tc.steps: step2. textSpanNode dragResultObject range as expected.
     * @tc.expect: expect spanNode will be selected by drag, textSelector [0, 15] exceed the first spannode len,
     *    SPAN_URL dragResult range [0, 13], the SPAN_PHONE dragResult range [0, 2]
     */
    pattern->textSelector_.Update(0, 15);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(pattern->dragResultObjects_.back().valueString, SPAN_PHONE);
    EXPECT_EQ(pattern->dragResultObjects_.back().offsetInSpan[RichEditorSpanRange::RANGEEND], 2);

    /**
     * @tc.steps: step2. update text selector and call OnDragStart.
     * @tc.expect: expect spanNode will be selected, textSelector [0, 5] not exceed the first spannode len,
     *     thus dragResultObject is [0, 5] and dragResult is SPAN_URL.
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(0, 5);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(pattern->dragResultObjects_.front().valueString, SPAN_URL);
    EXPECT_EQ(pattern->dragResultObjects_.front().offsetInSpan[RichEditorSpanRange::RANGEEND], 5);

    /**
     * @tc.steps: step3. update text selector and call OnDragStart.
     * @tc.expect: expect dragResultObject [SPAN_URL, SPAN_PHONE], SPAN_URL ranged [0, 13], .
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(8, 16);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(pattern->dragResultObjects_.back().valueString, SPAN_PHONE);
    EXPECT_EQ(pattern->dragResultObjects_.front().offsetInSpan[RichEditorSpanRange::RANGEEND], SPAN_URL.size());
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPESPAN);
    }
}

/**
 * @tc.name: GetSymbolSpanResultObject001
 * @tc.desc: test test_pattern.h GetSymbolSpanResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetSymbolSpanResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child symbolSpanNodes.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto stack = ViewStackProcessor::GetInstance();
    auto host = stack->GetMainFrameNode();
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    std::vector<uint32_t> unicodes = { 0x4F60, 0x597D, 0xFF0C, 0x4E16, 0x754C, 0xFF01 };
    for (auto code : unicodes) {
        auto symbolSpanNode = SpanNode::GetOrCreateSpanNode(V2::SYMBOL_SPAN_ETS_TAG, stack->ClaimNodeId());
        symbolSpanNode->UpdateContent(code);
        host->AddChild(symbolSpanNode);
        symbolSpanNode->SetParent(host);
    }
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    // measure will call pattern InitDragEvent.
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. symbol spanNode drag select range as expected.
     * @tc.expect: symbol spanNode len is 2, thus last dragResultObject is partial selected, range [0, 1]
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetOnDragStart();
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(0, 5);
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());
    EXPECT_EQ(pattern->dragResultObjects_.front().valueString, "20320"); // "20320" means: unicode string
    EXPECT_EQ(pattern->dragResultObjects_.back().offsetInSpan[RichEditorSpanRange::RANGEEND], 1);
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPESYMBOLSPAN);
    }

    /**
     * @tc.steps: step3. text selectstr OnDragStart as expected.
     * @tc.expect: expect dragResultObjects_ not empty.
     */
    pattern->dragResultObjects_.clear();
    pattern->textSelector_.Update(8, 12);
    dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_TRUE(!pattern->dragResultObjects_.empty());
}

/**
 * @tc.name: GetImageResultObject001
 * @tc.desc: test test_pattern.h GetImageResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, GetImageResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with three child ImageSpanNodes.
     */
    SuppressMockParagraph();
    TextModelNG textModelNG;
    textModelNG.Create("");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    host->draggable_ = true;
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));

    MarginPropertyF margin { .left = 40.f, .right = 40.f, .top = 80.f, .bottom = 80.f };
    ImageSpanNodeProperty firstProperty {
        .imageSrc = std::make_optional("image"),
        .margin = std::make_optional(margin),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER)
    };
    auto imageSpanNode = CreateImageSpanNode(firstProperty);
    host->AddChild(imageSpanNode);

    ImageSpanNodeProperty secondProperty {
        .pixelMap = std::make_optional(PixelMap::CreatePixelMap(nullptr)),
        .margin = std::make_optional(margin),
        .imageFit = std::make_optional(ImageFit::FILL),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER)
    };
    imageSpanNode = CreateImageSpanNode(secondProperty);
    host->AddChild(imageSpanNode);

    ImageSpanNodeProperty thirdProperty {
        .margin = std::make_optional(margin),
        .imageFit = std::make_optional(ImageFit::FILL),
        .verticalAlign = std::make_optional(VerticalAlign::CENTER)
    };
    imageSpanNode = CreateImageSpanNode(thirdProperty);
    host->AddChild(imageSpanNode);

    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    LayoutConstraintF layoutConstraintF;
    frameNode->Measure(layoutConstraintF);
    auto gesture = frameNode->GetOrCreateGestureEventHub();
    gesture->SetIsTextDraggable(true);

    /**
     * @tc.steps: step2. text selectstr OnDragStart as expected.
     * @tc.expect expect non-null imagesrc & pixelMap in dragResultObjects, properties as expected,
     *     dragResultObjects_ size is 2.
     */
    pattern->textSelector_.Update(0, 20);
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = frameNode->GetEventHub<EventHub>();
    auto onDragStart = eventHub->GetOnDragStart();
    auto dragDropInfo = onDragStart(dragEvent, "");
    EXPECT_EQ(pattern->dragResultObjects_.size(), 2); // 2 means result list size.
    EXPECT_EQ(
        pattern->dragResultObjects_.front().imageStyle.verticalAlign, static_cast<int32_t>(ImageFit::FILL));
    EXPECT_EQ(pattern->dragResultObjects_.front().imageStyle.objectFit, static_cast<int32_t>(VerticalAlign::CENTER));
    for (auto obj : pattern->dragResultObjects_) {
        EXPECT_EQ(obj.type, SelectSpanType::TYPEIMAGE);
    }
}

/**
 * @tc.name: SetTextDetectTypes001
 * @tc.desc: test test_pattern.h SetTextDetectTypes.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, SetTextDetectTypes001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern with child span node.
     */
    TextModelNG textModelNG;
    textModelNG.Create("");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto onResult = [](const std::string&) {};
    textModelNG.SetTextDetectConfig("apple, orange, banana", std::move(onResult));
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    EXPECT_EQ(pattern->aiDetectTypesChanged_, true);
    pattern->InitTextDetect(0, "orange");
}

/**
 * @tc.name: InitPanEvent001
 * @tc.desc: test test_pattern.h InitPanEvent, dragWindow will be create/destroy as expected.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNg, InitPanEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitPanEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create("012345678900000000000");
    textModelNG.SetCopyOption(CopyOptions::Local);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    frameNode->eventHub_->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    auto pattern = frameNode->GetPattern<TextPattern>();
    pattern->textSelector_.Update(0, 15);

    auto gestureEventHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    pattern->InitPanEvent(gestureEventHub);
    EXPECT_EQ(pattern->dragWindow_, nullptr);

    GestureEvent info;
    info.SetLocalLocation(Offset(0, 10));
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    pattern->paragraph_ = paragraph;
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    /**
     * @tc.steps: step2. test HandlePanStart.
     * @tc.expect: expect dragWindow created.
     */
    auto panEvent = gestureEventHub->panEventActuator_->panEvents_.back();
    auto onPanStart = panEvent->GetActionStartEventFunc();
    onPanStart(info);
    EXPECT_NE(pattern->dragWindow_, nullptr);

    /**
     * @tc.steps: step3. test HandlePanUpdate.
     */
    auto onPanUpdate = panEvent->GetActionUpdateEventFunc();
    onPanUpdate(info);

    /**
     * @tc.steps: step4. test HandlePanEnd.
     * @tc.expect: expect dragWindow Destroyed.
     */
    auto onPanEnd = panEvent->GetActionEndEventFunc();
    onPanEnd(info);
    EXPECT_EQ(pattern->dragWindow_, nullptr);
}
} // namespace OHOS::Ace::NG
