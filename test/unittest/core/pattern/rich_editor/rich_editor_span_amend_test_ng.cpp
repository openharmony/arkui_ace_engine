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
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/components_ng/render/mock_canvas_image.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/page_translate/page_translate_node.h"
#include "core/components_ng/pattern/text/span/span_string.h"

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

class RichEditorSpanAmendTestNg : public RichEditorCommonTestNg {
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

void RichEditorSpanAmendTestNg::SetUp()
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

void RichEditorSpanAmendTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorSpanAmendTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

template<typename... Args>
void RichEditorSpanAmendTestNg::InitSpans(Args... args)
{
    RichEditorCommonTestNg::ClearSpan();
    auto pattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ConstructSpans(pattern, args...);
}

template<typename T, typename... Args>
void RichEditorSpanAmendTestNg::ConstructSpans(RefPtr<RichEditorPattern> pattern, T value, Args... args)
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
 * @tc.name: AddTextSpan001
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, AddTextSpan001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextSpanOptions options;
    richEditorPattern->previewTextRecord_.previewContent = u"123";
    richEditorPattern->previewTextRecord_.previewTextHasStarted = true;
    richEditorPattern->previewTextRecord_.startOffset = 0;
    richEditorPattern->previewTextRecord_.endOffset = 0;
    EXPECT_EQ(richEditorPattern->previewTextRecord_.IsValid(), true);
    int32_t res = richEditorPattern->AddTextSpan(options, TextChangeReason::UNKNOWN, true, 0);
    EXPECT_EQ(res, 0);
}

/**
 * @tc.name: AddTextSpan001
 * @tc.desc: test AddTextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PlaceholderSpanNodeTest001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto placeholderSpanNode = PlaceholderSpanNode::GetOrCreateSpanNode(V2::PLACEHOLDER_SPAN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<PlaceholderSpanPattern>(); });
    ASSERT_NE(placeholderSpanNode, nullptr);
    auto placeholderSpanItem = placeholderSpanNode->GetSpanItem();
    ASSERT_NE(placeholderSpanItem, nullptr);
    auto placeholderSpanPattern = placeholderSpanNode->GetPattern<PlaceholderSpanPattern>();
    ASSERT_NE(placeholderSpanPattern, nullptr);

    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    DirtySwapConfig config = { .frameSizeChange = true };

    placeholderSpanItem->needReLayout = false;
    placeholderSpanPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(placeholderSpanItem->needReLayout, true);
}

/**
 * @tc.name: SpanAddAndClear001
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, SpanAddAndClear001, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option1;
    option1.start = 5;
    option1.end = 10;
    richEditorController->DeleteSpans(option1);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option2;
    option2.start = 10;
    option2.end = 5;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(contentNode->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option3;
    option3.start = -5;
    option3.end = 10;
    richEditorController->DeleteSpans(option3);
    EXPECT_EQ(contentNode->GetChildren().size(), 1);
}

/**
 * @tc.name: SpanAddAndClear002
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, SpanAddAndClear002, TestSize.Level0)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    ASSERT_NE(contentNode, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option4;
    option4.start = 5;
    option4.end = -10;
    richEditorController->DeleteSpans(option4);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option5;
    richEditorController->DeleteSpans(option5);
    EXPECT_TRUE(contentNode->GetChildren().empty());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 100;
    option5.end = 10;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 3;
    option5.end = 3;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(contentNode->GetChildren().size(), 3);
    ClearSpan();
    richEditorController->DeleteSpans(option5);
}

/**
 * @tc.name: SymbolTest001
 * @tc.desc: test update symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, SymbolTest001, TestSize.Level0)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    /**
     * @tc.steps: step2. initalize symbol span properties
     */
    TextStyle style;
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_1);
    style.SetRenderStrategy(RENDER_STRATEGY_SINGLE);
    style.SetEffectStrategy(EFFECT_STRATEGY_NONE);
    SymbolSpanOptions options;
    options.symbolId = SYMBOL_ID;
    options.style = style;

    /**
     * @tc.steps: step3. add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);

    /**
     * @tc.steps: step4. update symbol span style
     */
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateSymbolFontSize = FONT_SIZE_VALUE_2;
    updateSpanStyle.updateSymbolFontWeight = FONT_WEIGHT_BOLD;
    updateSpanStyle.updateSymbolColor = SYMBOL_COLOR_LIST_2;
    updateSpanStyle.updateSymbolRenderingStrategy = RENDER_STRATEGY_MULTI_COLOR;
    updateSpanStyle.updateSymbolEffectStrategy = EFFECT_STRATEGY_SCALE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);

    ImageSpanAttribute imageStyle;
    style.SetFontSize(FONT_SIZE_VALUE_2);
    style.SetFontWeight(FONT_WEIGHT_BOLD);
    style.SetSymbolColorList(SYMBOL_COLOR_LIST_2);
    style.SetRenderStrategy(RENDER_STRATEGY_MULTI_COLOR);
    style.SetEffectStrategy(EFFECT_STRATEGY_SCALE);

    // update the first symbol span
    richEditorController->UpdateSpanStyle(0, 2, style, imageStyle);

    /**
     * @tc.steps: step5. test symbol span style
     */
    auto contentNode = richEditorNode_->GetChildAtIndex(0);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_BOLD);
    EXPECT_EQ(newSpan1->GetSymbolColorList(), SYMBOL_COLOR_LIST_2);
    EXPECT_EQ(newSpan1->GetSymbolRenderingStrategy(), RENDER_STRATEGY_MULTI_COLOR);
    EXPECT_EQ(newSpan1->GetSymbolEffectStrategy(), EFFECT_STRATEGY_SCALE);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(contentNode->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetSymbolColorList(), SYMBOL_COLOR_LIST_1);
    EXPECT_EQ(newSpan2->GetSymbolRenderingStrategy(), RENDER_STRATEGY_SINGLE);
    EXPECT_EQ(newSpan2->GetSymbolEffectStrategy(), EFFECT_STRATEGY_NONE);

    ClearSpan();
}

/**
 * @tc.name: SetPlaceHolderStyledString
 * @tc.desc: test SetPlaceHolderStyledString
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, SetPlaceHolderStyledString, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto spanString = AceType::MakeRefPtr<SpanString>(INIT_VALUE_1);
    ASSERT_NE(spanString, nullptr);
    // Setup content host so MarkDirtyNode can be triggered
    richEditorPattern->OnAttachToFrameNode();
    auto host = richEditorPattern->GetContentHost();
    ASSERT_NE(host, nullptr);
    auto hostLayoutProperty = host->GetLayoutProperty();
    ASSERT_NE(hostLayoutProperty, nullptr);
    hostLayoutProperty->CleanDirty();
    richEditorController->SetPlaceholderStyledString(spanString);
    EXPECT_NE(richEditorPattern->styledPlaceholder_, nullptr);
    // Branch: host != nullptr, verify content host marked dirty with PROPERTY_UPDATE_MEASURE
    EXPECT_EQ(hostLayoutProperty->GetPropertyChangeFlag() & PROPERTY_UPDATE_MEASURE,
        PROPERTY_UPDATE_MEASURE);
    richEditorPattern->isShowPlaceholder_ = true;
    richEditorPattern->richTextRect_ = RectF(50, 50, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    std::vector<std::list<RefPtr<SpanItem>>> spans;
    richEditorPattern->SetPlaceholder(spans);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetOffset(), OffsetF(50.0f, 50.0f));
    // Branch: contentRect offset == (0,0) -> UpdateRichTextRectOffsetWithPadding
    richEditorPattern->isShowPlaceholder_ = false;
    PaddingProperty padding;
    padding.left = CalcLength(Dimension(20.0f, DimensionUnit::PX));
    padding.top = CalcLength(Dimension(30.0f, DimensionUnit::PX));
    richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>()->UpdatePadding(padding);
    richEditorPattern->SetPlaceholder(spans);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetOffset(), OffsetF(20.0f, 30.0f));
    // Branch: contentRect offset != (0,0) -> richTextRect_.SetOffset(contentRect_.GetOffset())
    richEditorPattern->isShowPlaceholder_ = false;
    richEditorPattern->contentRect_ = RectF(10.0f, 20.0f, 100, 100);
    richEditorPattern->SetPlaceholder(spans);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetOffset(), OffsetF(10.0f, 20.0f));
}

/**
 * @tc.name: PlaceholderImageNode
 * @tc.desc: test PlaceholderImageNode
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PlaceholderImageNode, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ImageSpanOptions options;
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    ASSERT_NE(pixelMap, nullptr);
    options.imagePixelMap = pixelMap;
    auto spanString = AceType::MakeRefPtr<SpanString>(options);
    ASSERT_NE(spanString, nullptr);

    // Set placeholder with image.
    richEditorPattern->SetPlaceholderStyledString(spanString);
    auto& placeholderSpanNodes = richEditorPattern->placeholderImageNodes_;
    std::vector<std::list<RefPtr<SpanItem>>> spans;
    richEditorPattern->SetPlaceholder(spans);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(placeholderSpanNodes.size(), 1);

    // Remove placeholder image nodes when a text span is added.
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_TRUE(placeholderSpanNodes.empty());
    richEditorPattern->spans_.clear();
    richEditorPattern->SetPlaceholder(spans);
    EXPECT_EQ(spans.size(), 1);
    EXPECT_EQ(placeholderSpanNodes.size(), 1);

    // Remove placeholder image nodes since real content exists.
    richEditorPattern->BeforeCreateLayoutWrapper();
    EXPECT_EQ(placeholderSpanNodes.size(), 1);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    ASSERT_FALSE(richEditorPattern->spans_.empty());
    richEditorPattern->BeforeCreateLayoutWrapper();
    EXPECT_TRUE(placeholderSpanNodes.empty());
}

/**
 * @tc.name: PageTranslate_ApplyAndReset
 * @tc.desc: Test RichEditorPattern ApplyPageTranslateResult and ResetPageTranslate
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PageTranslate_ApplyAndReset, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // ApplyPageTranslateResult with negative version returns true but does not set translated placeholder
    EXPECT_TRUE(richEditorPattern->ApplyPageTranslateResult("result", -1));
    EXPECT_FALSE(richEditorPattern->pageTranslatedContent_.has_value());

    // ApplyPageTranslateResult with valid result sets translated placeholder and version
    EXPECT_TRUE(richEditorPattern->ApplyPageTranslateResult("translated", 1));
    ASSERT_TRUE(richEditorPattern->pageTranslatedContent_.has_value());
    EXPECT_EQ(richEditorPattern->pageTranslatedContent_.value(), u"translated");

    // ResetPageTranslate clears translated placeholder and version
    richEditorPattern->ResetPageTranslate();
    EXPECT_FALSE(richEditorPattern->pageTranslatedContent_.has_value());

    // ResetPageTranslate again when already clean is a no-op
    richEditorPattern->ResetPageTranslate();
    EXPECT_FALSE(richEditorPattern->pageTranslatedContent_.has_value());
}

/**
 * @tc.name: PageTranslate_GetCurrentPlaceholderText
 * @tc.desc: Test RichEditorPattern GetCurrentPlaceholderText for plain and styled placeholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PageTranslate_GetCurrentPlaceholderText, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    // plain placeholder: returns layoutProperty placeholder value
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdatePlaceholder(u"plain placeholder");
    EXPECT_EQ(richEditorPattern->GetCurrentPlaceholderText(), u"plain placeholder");

    // styled placeholder: returns styledPlaceholder_->GetU16string()
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = spanString;
    EXPECT_EQ(richEditorPattern->GetCurrentPlaceholderText(), u"Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = nullptr;
}

/**
 * @tc.name: PageTranslate_GetPageTranslateTextForReport
 * @tc.desc: Test RichEditorPattern GetPageTranslateTextForReport for plain and styled placeholder
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PageTranslate_GetPageTranslateTextForReport, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // isShowPlaceholder_ is false returns empty string
    richEditorPattern->isShowPlaceholder_ = false;
    EXPECT_TRUE(richEditorPattern->GetPageTranslateTextForReport().empty());

    // isShowPlaceholder_ is true, lastDrawn mismatch returns empty string (plain placeholder)
    richEditorPattern->isShowPlaceholder_ = true;
    layoutProperty->UpdatePlaceholder(u"plain placeholder");
    richEditorPattern->lastDrawnPageTranslateContent_ = u"mismatch";
    EXPECT_TRUE(richEditorPattern->GetPageTranslateTextForReport().empty());

    // isShowPlaceholder_ is true, lastDrawn match returns the text (plain placeholder)
    richEditorPattern->lastDrawnPageTranslateContent_ = u"plain placeholder";
    EXPECT_EQ(richEditorPattern->GetPageTranslateTextForReport(), "plain placeholder");

    // styled placeholder: lastDrawn match returns the styled text
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = spanString;
    richEditorPattern->lastDrawnPageTranslateContent_ = u"Styled Placeholder";
    EXPECT_EQ(richEditorPattern->GetPageTranslateTextForReport(), "Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = nullptr;
}

/**
 * @tc.name: PageTranslate_ReportAndOnSourceChanged
 * @tc.desc: Test RichEditorPattern ReportPageTranslatePlaceholderDrawn and OnPlaceholderSourceTextChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PageTranslate_ReportAndOnSourceChanged, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutProperty = richEditorNode_->GetLayoutProperty<RichEditorLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    // ReportPageTranslatePlaceholderDrawn sets lastDrawn to current placeholder (plain)
    richEditorPattern->isShowPlaceholder_ = true;
    layoutProperty->UpdatePlaceholder(u"plain placeholder");
    richEditorPattern->ReportPageTranslatePlaceholderDrawn();
    EXPECT_EQ(richEditorPattern->lastDrawnPageTranslateContent_, u"plain placeholder");

    // ReportPageTranslatePlaceholderDrawn with styled placeholder
    RefPtr<SpanString> spanString = AceType::MakeRefPtr<SpanString>(u"Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = spanString;
    richEditorPattern->lastDrawnPageTranslateContent_.clear();
    richEditorPattern->ReportPageTranslatePlaceholderDrawn();
    EXPECT_EQ(richEditorPattern->lastDrawnPageTranslateContent_, u"Styled Placeholder");
    richEditorPattern->styledPlaceholder_ = nullptr;

    // OnPlaceholderSourceTextChanged clears lastDrawn and resets translate
    richEditorPattern->ApplyPageTranslateResult("translated", 1);
    ASSERT_TRUE(richEditorPattern->pageTranslatedContent_.has_value());
    richEditorPattern->OnPlaceholderSourceTextChanged();
    EXPECT_FALSE(richEditorPattern->pageTranslatedContent_.has_value());
    EXPECT_TRUE(richEditorPattern->lastDrawnPageTranslateContent_.empty());

    // OnPlaceholderSourceTextChanged when no translate state is a no-op
    richEditorPattern->OnPlaceholderSourceTextChanged();
    EXPECT_FALSE(richEditorPattern->pageTranslatedContent_.has_value());
}

/**
 * @tc.name: PageTranslate_GetPageTranslateNodeId
 * @tc.desc: Test RichEditorPattern GetPageTranslateNodeId returns host id
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorSpanAmendTestNg, PageTranslate_GetPageTranslateNodeId, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    EXPECT_EQ(richEditorPattern->GetPageTranslateNodeId(), richEditorNode_->GetId());
}
} // namespace OHOS::Ace::NG
