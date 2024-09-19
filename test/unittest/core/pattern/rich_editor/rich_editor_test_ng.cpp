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
#include <optional>
#include <vector>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_data_detector_mgr.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "base/window/drag_window.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/overlay/keyboard_view.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_layout_algorithm.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_overlay_modifier.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/selection_info.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/select_overlay/select_overlay_property.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_selector.h"
#include "core/components_ng/render/paragraph.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/pipeline/base/constants.h"
#include "test/unittest/core/pattern/test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
int32_t testOnReadyEvent = 0;
int32_t testAboutToIMEInput = 0;
int32_t testOnIMEInputComplete = 0;
int32_t testAboutToDelete = 0;
int32_t testOnDeleteComplete = 0;
int32_t testOnSelect = 0;
SelectionRangeInfo testSelectionRange(0, 0);
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
const std::string INIT_VALUE_1 = "hello1";
const std::string INIT_VALUE_2 = "hello2";
const std::string INIT_VALUE_3 = "hello world! hello world! hello world!";
const std::string TEST_INSERT_VALUE = "s";
const std::string TEST_INSERT_LINE_SEP = "\n";
const std::string EXCEPT_VALUE = "h\n";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Dimension FONT_SIZE_VALUE_2 = Dimension(40, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Ace::FontWeight FONT_WEIGHT_BOLD = Ace::FontWeight::BOLD;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Shadow TEXT_SHADOW1 = Shadow(0, 0, Offset(), Color::RED);
const Shadow TEXT_SHADOW2 = Shadow(0, 0, Offset(), Color::WHITE);
const std::vector<Shadow> SHADOWS { TEXT_SHADOW1, TEXT_SHADOW2 };
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
const std::string PREVIEW_TEXT_VALUE1 = "nihao";
const std::string PREVIEW_TEXT_VALUE2 = "nihaodajia";
const std::string PREVIEW_TEXT_VALUE3 = "dajia";
const std::string ROOT_TAG = "root";
const CalcLength CALC_LENGTH_CALC { 10.0, DimensionUnit::CALC };
const CalcLength ERROR_CALC_LENGTH_CALC { -10.0, DimensionUnit::CALC };
const Dimension CALC_TEST { 10.0, DimensionUnit::CALC };
const Dimension ERROR_CALC_TEST { -10.0, DimensionUnit::CALC };
const Offset MOUSE_GLOBAL_LOCATION = { 100, 200 };
constexpr int32_t WORD_LIMIT_LEN = 6;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
constexpr int32_t THIRD_PARAM = 2;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float BUILDER_WIDTH = 150.0f;
const float BUILDER_HEIGHT = 75.0f;
const SizeF BUILDER_SIZE(BUILDER_WIDTH, BUILDER_HEIGHT);
const uint32_t SYMBOL_ID = 1;
std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE = {{ "subs", 1 }};
std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE_2 = {{ "subs", 0 }};
std::vector<Color> SYMBOL_COLOR_LIST_1 = { Color::FromRGB(255, 100, 100) };
std::vector<Color> SYMBOL_COLOR_LIST_2 = { Color::FromRGB(255, 100, 100), Color::FromRGB(255, 255, 100) };
const uint32_t RENDER_STRATEGY_SINGLE = 0;
const uint32_t RENDER_STRATEGY_MULTI_COLOR = 1;
const uint32_t EFFECT_STRATEGY_NONE = 0;
const uint32_t EFFECT_STRATEGY_SCALE = 1;
const SizeF CONTAINER_SIZE(720.0f, 1136.0f);
constexpr float DEFAILT_OPACITY = 0.2f;
constexpr Color SYSTEM_CARET_COLOR = Color(0xff007dff);
constexpr Color SYSTEM_SELECT_BACKGROUND_COLOR = Color(0x33007dff);
constexpr float CONTEXT_WIDTH_VALUE = 300.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 150.0f;
const Color DEFAULT_TEXT_COLOR_VALUE = Color::FromARGB(229, 0, 0, 0);
bool g_isOnWillChangeCalled = false;
bool g_isOnDidChangeCalled = false;
RichEditorChangeValue onWillChangeValue;
RichEditorChangeValue onDidChangeValue;
auto& onWillRangeBefore = onWillChangeValue.rangeBefore_;
auto& onWillReplacedSpans = onWillChangeValue.replacedSpans_;
auto& onWillReplacedImageSpans = onWillChangeValue.replacedImageSpans_;
auto& onWillReplacedSymbolSpans = onWillChangeValue.replacedSymbolSpans_;
auto& onDidRangeBefore = onDidChangeValue.rangeBefore_;
auto& onDidRangeAfter = onDidChangeValue.rangeAfter_;
const TextStyle TEXT_STYLE_1(10.0);
const TextStyle TEXT_STYLE_2(20.0);
const TextStyle TEXT_STYLE_3(30.0);
const TextSpanOptions TEXT_SPAN_OPTIONS_1 = { .value = INIT_VALUE_1, .style = TEXT_STYLE_1 };
const ImageSpanAttribute IMAGE_SPAN_ATTRIBUTE_1 = {
    .size = ImageSpanSize{ .width = 200.0_px, .height = 100.0_px },
    .verticalAlign = VerticalAlign::CENTER,
    .objectFit = ImageFit::COVER,
    .marginProp = std::nullopt,
    .borderRadius = std::nullopt,
    .paddingProp = std::nullopt
};
const ImageSpanOptions IMAGE_SPAN_OPTIONS_1 = {
    .offset = std::nullopt,
    .image = "app.media.icon",
    .bundleName = std::nullopt,
    .moduleName = std::nullopt,
    .imagePixelMap = std::nullopt,
    .imageAttribute = IMAGE_SPAN_ATTRIBUTE_1
};

struct TestCursorItem {
    int32_t index;
    CaretMetricsF caretMetricsFDown;
    CaretMetricsF caretMetricsFUp;
};

struct TestParagraphRect {
    int32_t start;
    int32_t end;
    std::vector<RectF> rects;
};

struct TestParagraphItem {
    int32_t start;
    int32_t end;
    int32_t height;
    ParagraphStyle paragraphStyle;
    std::map<int32_t, Offset> indexOffsetMap;
    std::vector<TestCursorItem> testCursorItems;
    std::vector<TestParagraphRect> testParagraphRects;
};
} // namespace

class RichEditorTestNg : public TestNG {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    void AddSpan(const std::string& content);
    void AddImageSpan();
    void AddParagraph(TestParagraphItem testParagraphItem);
    void ClearParagraph();
    void ClearSpan();
    void InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr);
    void RequestFocus();
    void GetFocus(const RefPtr<RichEditorPattern>& pattern);
    void OnDrawVerify(const SelectSpanType& type, const std::string& text, SymbolSpanOptions options, Offset offset,
        bool selected = false);
    void ResetContentChangeCallbackState();
    void InitContentChangeCallback(RichEditorModelNG& richEditorModel);

protected:
    static void MockKeyboardBuilder() {}
    RefPtr<FrameNode> richEditorNode_;
};

void RichEditorTestNg::ResetContentChangeCallbackState()
{
    g_isOnWillChangeCalled = false;
    g_isOnDidChangeCalled = false;
    onWillChangeValue.reset();
    onDidChangeValue.reset();
}

void RichEditorTestNg::InitContentChangeCallback(RichEditorModelNG& richEditorModel)
{
    ResetContentChangeCallbackState();
    auto onWillChange = [](const RichEditorChangeValue& changeValue) {
        g_isOnWillChangeCalled = true;
        onWillChangeValue = changeValue;
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));

    auto onDidChange = [](const RichEditorChangeValue& changeValue) {
        g_isOnDidChangeCalled = true;
        onDidChangeValue = changeValue;
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));
}

void RichEditorTestNg::SetUp()
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

void RichEditorTestNg::TearDown()
{
    richEditorNode_ = nullptr;
    testOnReadyEvent = 0;
    testAboutToIMEInput = 0;
    testOnIMEInputComplete = 0;
    testAboutToDelete = 0;
    testOnDeleteComplete = 0;
    MockParagraph::TearDown();
}

void RichEditorTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RichEditorTestNg::AddSpan(const std::string& content)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
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
    spanModelNG.SetTextShadow(SHADOWS);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    spanNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    richEditorPattern->spans_.emplace_back(spanNode->spanItem_);
    int32_t spanTextLength = 0;
    for (auto& span : richEditorPattern->spans_) {
        spanTextLength += StringUtils::ToWstring(span->content).length();
        span->position = spanTextLength;
    }
}

void RichEditorTestNg::AddImageSpan()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto imageNode = FrameNode::GetOrCreateFrameNode(
        V2::IMAGE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    ImageSourceInfo imageInfo(IMAGE_VALUE, BUNDLE_NAME, MODULE_NAME);
    imageLayoutProperty->UpdateImageSourceInfo(imageInfo);
    imageNode->MountToParent(richEditorNode_, richEditorNode_->children_.size());
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = " ";
    spanItem->placeholderIndex = 0;
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.emplace_back(spanItem);
    int32_t spanTextLength = 0;
    for (auto& span : richEditorPattern->spans_) {
        spanTextLength += StringUtils::ToWstring(span->content).length();
        span->position = spanTextLength;
    }
}

void RichEditorTestNg::AddParagraph(TestParagraphItem testParagraphItem)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.AddParagraph(
        { .paragraph = paragraph, .start = testParagraphItem.start, .end = testParagraphItem.end });
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(offset, _)).WillRepeatedly(Return(index));
    }
    for (auto& cursorItem : testParagraphItem.testCursorItems) {
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(cursorItem.index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(cursorItem.caretMetricsFUp), Return(true)));
        float cursorHeight = 0.0f;
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, true),
            cursorItem.caretMetricsFDown.offset);
        EXPECT_EQ(richEditorPattern->paragraphs_.ComputeCursorOffset(cursorItem.index, cursorHeight, false),
            cursorItem.caretMetricsFUp.offset);
    }
    for (auto& paragraphRect : testParagraphItem.testParagraphRects) {
        EXPECT_CALL(*paragraph, GetRectsForRange(paragraphRect.start, paragraphRect.end, _))
            .WillRepeatedly(SetArgReferee<THIRD_PARAM>(paragraphRect.rects));
    }
}

void RichEditorTestNg::ClearParagraph()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->paragraphs_.Reset();
}

void RichEditorTestNg::ClearSpan()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorNode_->children_.clear();
    richEditorPattern->spans_.clear();
    richEditorPattern->caretPosition_ = 0;
}

void RichEditorTestNg::InitAdjustObject(MockDataDetectorMgr& mockDataDetectorMgr)
{
    EXPECT_CALL(mockDataDetectorMgr, GetCursorPosition(_, _))
        .WillRepeatedly([](const std::string& text, int8_t offset) -> int8_t {
            if (text.empty()) {
                return DEFAULT_RETURN_VALUE;
            }
            if (text.length() <= WORD_LIMIT_LEN) {
                return WORD_LIMIT_RETURN;
            } else {
                return BEYOND_LIMIT_RETURN;
            }
        });

    EXPECT_CALL(mockDataDetectorMgr, GetWordSelection(_, _))
        .WillRepeatedly([](const std::string& text, int8_t offset) -> std::vector<int8_t> {
            if (text.empty()) {
                return std::vector<int8_t> { -1, -1 };
            }

            if (text.length() <= WORD_LIMIT_LEN) {
                return std::vector<int8_t> { 2, 3 };
            } else {
                return std::vector<int8_t> { 0, 2 };
            }
        });
}

void RichEditorTestNg::RequestFocus()
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
}

void RichEditorTestNg::GetFocus(const RefPtr<RichEditorPattern>& pattern)
{
    ASSERT_NE(pattern, nullptr);
    auto focushHub = pattern->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern->HandleFocusEvent();
    FlushLayoutTask(richEditorNode_);
}

void RichEditorTestNg::OnDrawVerify(
    const SelectSpanType& type, const std::string& text, SymbolSpanOptions options, Offset offset, bool selected)
{
    /**
     * @tc.steps: step1. Initialize text input and get focus
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    if (SelectSpanType::TYPESPAN == type) {
        AddSpan(text);
    } else if (SelectSpanType::TYPEIMAGE == type) {
        AddImageSpan();
    } else if (SelectSpanType::TYPESYMBOLSPAN == type) {
        auto richEditorController = richEditorPattern->GetRichEditorController();
        ASSERT_NE(richEditorController, nullptr);
        richEditorController->AddSymbolSpan(options);
    }

    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    GetFocus(richEditorPattern);

    if (!selected) {
        GestureEvent info;
        info.localLocation_ = offset;
        richEditorPattern->HandleClickEvent(info);
    } else {
        richEditorPattern->HandleOnSelectAll();
    }

    /**
     * @tc.steps: step2. Move handle
     */
    auto controller = richEditorPattern->GetMagnifierController();
    ASSERT_NE(controller, nullptr);
    controller->SetLocalOffset(OffsetF(1.0f, 1.0f));
    RectF handleRect;
    richEditorPattern->selectOverlay_->OnHandleMove(handleRect, false);

    /**
     * @tc.steps: step3. Test magnifier open or close
     * @tc.expected: magnifier is open
     */
    auto ret = controller->GetShowMagnifier();
    EXPECT_TRUE(ret);

    /**
     * @tc.steps: step4. Craete RichEditorOverlayModifier
     */
    EdgeEffect edgeEffect;
    auto scrollEdgeEffect = AceType::MakeRefPtr<ScrollEdgeEffect>(edgeEffect);
    auto scrollBarModifier = AceType::MakeRefPtr<ScrollBarOverlayModifier>();
    auto richFieldOverlayModifier = AceType::MakeRefPtr<RichEditorOverlayModifier>(
        richEditorPattern, AceType::WeakClaim(AceType::RawPtr(scrollBarModifier)), scrollEdgeEffect);
    ASSERT_NE(richFieldOverlayModifier, nullptr);

    /**
     * @tc.steps: step5. Create DrawingContext
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };

    /**
     * @tc.steps: step6. Do onDraw(context)
     */
    richFieldOverlayModifier->onDraw(context);

    /**
     * @tc.steps: step7. When handle move done
     */
    richEditorPattern->selectOverlay_->ProcessOverlay();
    richEditorPattern->selectOverlay_->OnHandleMoveDone(handleRect, true);

    /**
     * @tc.steps: step8. Test magnifier open or close
     * @tc.expected: magnifier is close
     */
    ret = controller->GetShowMagnifier();
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: RichEditorModel001
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    EXPECT_EQ(static_cast<int32_t>(ViewStackProcessor::GetInstance()->elementsStack_.size()), 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel002
 * @tc.desc: test create
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel002, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetDraggable(true);
    EXPECT_TRUE(ViewStackProcessor::GetInstance()->GetMainFrameNode()->draggable_);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel003
 * @tc.desc: test set on ready
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel003, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnReadyEvent = 1; };
    richEditorModel.SetOnReady(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnReady();
    EXPECT_EQ(testOnReadyEvent, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel004
 * @tc.desc: test set about to IME input
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel004, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorInsertValue&) {
        testAboutToIMEInput = 1;
        return true;
    };
    richEditorModel.SetAboutToIMEInput(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorInsertValue info;
    eventHub->FireAboutToIMEInput(info);
    EXPECT_EQ(testAboutToIMEInput, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel005
 * @tc.desc: test set on IME input complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel005, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorAbstractSpanResult&) { testOnIMEInputComplete = 1; };
    richEditorModel.SetOnIMEInputComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorAbstractSpanResult info;
    eventHub->FireOnIMEInputComplete(info);
    EXPECT_EQ(testOnIMEInputComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel006
 * @tc.desc: test set about to delete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel006, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const RichEditorDeleteValue&) {
        testAboutToDelete = 1;
        return true;
    };
    richEditorModel.SetAboutToDelete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    RichEditorDeleteValue info;
    eventHub->FireAboutToDelete(info);
    EXPECT_EQ(testAboutToDelete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel007
 * @tc.desc: test set on delete complete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel007, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = []() { testOnDeleteComplete = 1; };
    richEditorModel.SetOnDeleteComplete(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->FireOnDeleteComplete();
    EXPECT_EQ(testOnDeleteComplete, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel008
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel008, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel009
 * @tc.desc: test set on text selection change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel009, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) {
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        testSelectionRange = *selectionRange;
    };
    richEditorModel.SetOnSelectionChange(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    // insert value 1
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(testSelectionRange.start_, 6);
    EXPECT_EQ(testSelectionRange.end_, 6);

    // insert value 2
    richEditorPattern->InsertValue(INIT_VALUE_1);
    EXPECT_EQ(testSelectionRange.start_, 12);
    EXPECT_EQ(testSelectionRange.end_, 12);

    // set caret position
    richEditorPattern->SetCaretPosition(3);
    EXPECT_EQ(testSelectionRange.start_, 3);
    EXPECT_EQ(testSelectionRange.end_, 3);

    // update selector
    richEditorPattern->textSelector_.Update(0, 10);
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 10);

    // update selector, reverse handle
    richEditorPattern->textSelector_.Update(10, 8);
    EXPECT_EQ(testSelectionRange.start_, 8);
    EXPECT_EQ(testSelectionRange.end_, 10);

    // select all
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 12);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel010
 * @tc.desc: test set on text/image/symbol selection change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel010, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) {
        const auto* selectionRange = TypeInfoHelper::DynamicCast<SelectionRangeInfo>(info);
        ASSERT_NE(selectionRange, nullptr);
        testSelectionRange = *selectionRange;
    };
    richEditorModel.SetOnSelectionChange(std::move(func));
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ClearSpan();
    auto focusHub = richEditorPattern->GetFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    // insert value
    richEditorPattern->InsertValue(INIT_VALUE_1);

    // add image
    ImageSpanOptions imageSpanOptions;
    richEditorPattern->AddImageSpan(imageSpanOptions);
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 7);

    // add symbol
    SymbolSpanOptions symbolSpanOptions;
    symbolSpanOptions.symbolId = SYMBOL_ID;
    auto richEditorController =  richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorController->AddSymbolSpan(symbolSpanOptions);
    richEditorPattern->HandleOnSelectAll();
    EXPECT_EQ(testSelectionRange.start_, 0);
    EXPECT_EQ(testSelectionRange.end_, 9);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel011
 * @tc.desc: test placeholder appear and disappear
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel011, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    richEditorModel.SetPlaceholder(options);

    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode, AceType::MakeRefPtr<GeometryNode>(), richEditorNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // test placeholder appear when there is nothing in richEditor
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    // test add Text then placeholder disappear
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_2;
    richEditorController->AddTextSpan(textOptions);
    layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 1);
    EXPECT_EQ(spanItemChildren.back()->GetSpanContent(), INIT_VALUE_2);

    // test when richEitor empty again,placeholder Appear again
    RangeOptions rangeoptions;
    richEditorController->DeleteSpans(rangeoptions);
    richEditorPattern->BeforeCreateLayoutWrapper();
    layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel012
 * @tc.desc: test placeholder styel value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel012, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    options.fontColor = TEXT_COLOR_VALUE;
    options.fontSize = FONT_SIZE_VALUE;
    options.fontStyle = ITALIC_FONT_STYLE_VALUE;
    options.fontWeight = FONT_WEIGHT_VALUE;
    options.fontFamilies = FONT_FAMILY_VALUE;
    richEditorModel.SetPlaceholder(options);

    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode, AceType::MakeRefPtr<GeometryNode>(), richEditorNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // test placeholder value and style is correct
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel013
 * @tc.desc: test placeholder styel value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel013, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    PlaceholderOptions options;
    options.value = INIT_VALUE_1;
    richEditorModel.SetPlaceholder(options);

    auto richEditorNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    LayoutConstraintF parentLayoutConstraint;
    parentLayoutConstraint.maxSize = CONTAINER_SIZE;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode, AceType::MakeRefPtr<GeometryNode>(), richEditorNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));

    // test placeholder value and style is correct
    layoutAlgorithm->MeasureContent(parentLayoutConstraint, AceType::RawPtr(layoutWrapper));
    auto spanItemChildren = layoutAlgorithm->GetSpans();
    EXPECT_EQ(spanItemChildren.size(), 0);

    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorModel014
 * @tc.desc: test paragraph style wordBreak attribute
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel014, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    // test paragraph  style wordBreak default value
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_WORD);

    // test paragraph style wordBreak value of WordBreak.NORMAL
    struct UpdateParagraphStyle style;
    style.wordBreak = WordBreak::NORMAL;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::NORMAL);

    // test paragraph style wordBreak value of WordBreak.BREAK_ALL
    style.wordBreak = WordBreak::BREAK_ALL;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_ALL);
    
    // test paragraph style wordBreak value of WordBreak.BREAK_WORD
    style.wordBreak = WordBreak::BREAK_WORD;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<WordBreak>(info[0].wordBreak), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: RichEditorModel015
 * @tc.desc: test textstyle Color
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel015, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto richEditorTheme = AceType::MakeRefPtr<RichEditorTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(richEditorTheme));
    richEditorTheme->textStyle_.SetTextColor(DEFAULT_TEXT_COLOR_VALUE);
    richEditorTheme->textStyle_.SetTextDecorationColor(DEFAULT_TEXT_COLOR_VALUE);

    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorController->AddTextSpan(textOptions);
    auto info1 = richEditorController->GetSpansInfo(1, 3);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle1.fontSize, 16);
    EXPECT_EQ(Color::FromString(textStyle1.fontColor), DEFAULT_TEXT_COLOR_VALUE);
    EXPECT_EQ(Color::FromString(textStyle1.decorationColor), DEFAULT_TEXT_COLOR_VALUE);

    ClearSpan();
    richEditorPattern->InsertValue(INIT_VALUE_2);
    auto info2 = richEditorController->GetSpansInfo(1, 2);
    ASSERT_NE(info2.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info2.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(Color::FromString(textStyle2.fontColor), DEFAULT_TEXT_COLOR_VALUE);
    EXPECT_EQ(Color::FromString(textStyle2.decorationColor), DEFAULT_TEXT_COLOR_VALUE);
}

/**
 * @tc.name: RichEditorModel016
 * @tc.desc: test paragraph style linebreakstrategy attribute
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorModel016, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    // test paragraph  style linebreakstrategy default value
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), LineBreakStrategy::GREEDY);

    // test paragraph style linebreakstrategy value of LineBreakStrategy.GREEDY
    struct UpdateParagraphStyle style;
    style.lineBreakStrategy = LineBreakStrategy::GREEDY;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), LineBreakStrategy::GREEDY);

    // test paragraph style linebreakstrategy value of LineBreakStrategy.HIGH_QUALITY
    style.lineBreakStrategy = LineBreakStrategy::HIGH_QUALITY;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), LineBreakStrategy::HIGH_QUALITY);

    // test paragraph style linebreakstrategy value of LineBreakStrategy.BALANCED
    style.lineBreakStrategy = LineBreakStrategy::BALANCED;
    richEditorController->UpdateParagraphStyle(1, sizeof(INIT_VALUE_1), style);
    info = richEditorController->GetParagraphsInfo(1, sizeof(INIT_VALUE_1));
    EXPECT_EQ(static_cast<LineBreakStrategy>(info[0].lineBreakStrategy), LineBreakStrategy::BALANCED);
}

/**
 * @tc.name: RichEditorInsertValue001
 * @tc.desc: test calc insert value object
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    TextInsertValueInfo info;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 0);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.GetSpanIndex(), 1);
    EXPECT_EQ(info.GetOffsetInSpan(), 0);
}

/**
 * @tc.name: RichEditorInsertValue002
 * @tc.desc: test insert value last
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it3 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result3 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result3, it3->spanItem_->content);
    ClearSpan();
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it4 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result4 = TEST_INSERT_VALUE;
    EXPECT_EQ(result4, it4->spanItem_->content);
    ClearSpan();
    richEditorPattern->InsertValue(" ");
    auto it5 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    EXPECT_TRUE(it5);
}

/**
 * @tc.name: RichEditorInsertValue003
 * @tc.desc: test insert value between text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    AddSpan(INIT_VALUE_2);
    richEditorPattern->caretPosition_ = INIT_VALUE_1.size();
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = INIT_VALUE_1 + TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue004
 * @tc.desc: test insert value first
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result1 = TEST_INSERT_VALUE;
    EXPECT_EQ(result1, it1->spanItem_->content);
}

/**
 * @tc.name: RichEditorInsertValue005
 * @tc.desc: test insert value if the insert char is line separator
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorInsertValue005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    const std::string result1 = INIT_VALUE_1;
    EXPECT_EQ(result1, it1->spanItem_->content);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->moveLength_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_LINE_SEP);
    auto it2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetFirstChild());
    const std::string result2 = EXCEPT_VALUE;
    EXPECT_EQ(result2, it2->spanItem_->content);
}

/**
 * @tc.name: RichEditorDelete001
 * @tc.desc: test delete forward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDelete001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteForward(1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 0);
}

/**
 * @tc.name: RichEditorDelete002
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDelete002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->DeleteBackward(6);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDelete003
 * @tc.desc: test delete backforward
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDelete003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddImageSpan();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->DeleteBackward(1);
    EXPECT_NE(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 0);
    richEditorPattern->textSelector_ = TextSelector(0, 1);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
    while (!richEditorPattern->spans_.empty()) {
        richEditorPattern->spans_.pop_back();
    }
    richEditorPattern->DeleteBackward(1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);
}

/**
 * @tc.name: RichEditorDeleteForwardEmoji
 * @tc.desc: test DeleteForward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDeleteForwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteForward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorDeleteBackwardEmoji
 * @tc.desc: test DeleteBackward Emoji And Emoji Selected
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDeleteBackwardEmoji, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("😄3😄😄");
    richEditorPattern->caretPosition_ = 2;
    richEditorPattern->textSelector_ = TextSelector(2, 5);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorPattern->DeleteBackward(1);
    ASSERT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: RichEditorController001
 * @tc.desc: test add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    ImageSpanAttribute imageStyle;
    AddSpan("test");
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto index1 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index1, 1);
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 2;
    auto index2 = richEditorController->AddImageSpan(options);
    EXPECT_EQ(index2, 2);

    options.offset = std::nullopt;
    auto index3 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index3, 4);

    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index4 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index4, 5);

    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index5 = richEditorPattern->AddImageSpan(options, false, 0);
    EXPECT_EQ(index5, 6);

    marginProp = { ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC, ERROR_CALC_LENGTH_CALC };
    borderRadius = { ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST, ERROR_CALC_TEST };
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;
    auto index6 = richEditorPattern->AddImageSpan(options, false, -1);
    EXPECT_EQ(index6, 7);
}

/**
 * @tc.name: RichEditorController002
 * @tc.desc: test add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetFontFamilies(FONT_FAMILY_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextSpanOptions options;
    options.offset = 1;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index1 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index2, 1);
    options.value = "hello\n";
    auto index3 = richEditorController->AddTextSpan(options);
    EXPECT_EQ(index3, 1);
}

/**
 * @tc.name: OnCaretTwinkling001
 * @tc.desc: test on caret twinkling
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnCaretTwinkling001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->OnCaretTwinkling();
    EXPECT_FALSE(richEditorPattern->caretVisible_);
}

/**
 * @tc.name: RichEditorController003
 * @tc.desc: test get caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 1;
    auto offset1 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset1, 1);
    richEditorPattern->caretPosition_ = 2;
    auto offset2 = richEditorController->GetCaretOffset();
    EXPECT_EQ(offset2, 2);
}

/**
 * @tc.name: RichEditorController004
 * @tc.desc: test set caret offset
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorController->SetCaretOffset(2);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
    richEditorController->SetCaretOffset(-1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 2);
}

/**
 * @tc.name: RichEditorController005
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController005, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetTextColor(TEXT_COLOR_VALUE);
    textStyle.SetTextShadows(SHADOWS);
    textStyle.SetFontSize(FONT_SIZE_VALUE);
    textStyle.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    textStyle.SetFontWeight(FONT_WEIGHT_VALUE);
    textStyle.SetFontFamilies(FONT_FAMILY_VALUE);
    textStyle.SetTextDecoration(TEXT_DECORATION_VALUE);
    textStyle.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateTextColor = TEXT_COLOR_VALUE;
    updateSpanStyle.updateTextShadows = SHADOWS;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE;
    updateSpanStyle.updateItalicFontStyle = ITALIC_FONT_STYLE_VALUE;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_VALUE;
    updateSpanStyle.updateFontFamily = FONT_FAMILY_VALUE;
    updateSpanStyle.updateTextDecoration = TEXT_DECORATION_VALUE;
    updateSpanStyle.updateTextDecorationColor = TEXT_DECORATION_COLOR_VALUE;
    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    richEditorController->UpdateSpanStyle(5, 10, textStyle, imageStyle);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 5);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan1->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan1->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan1->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan1->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(3));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(newSpan2->GetTextShadow(), SHADOWS);
    EXPECT_EQ(newSpan2->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(newSpan2->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
}

/**
 * @tc.name: RichEditorController006
 * @tc.desc: test get span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController006, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    auto info1 = richEditorController->GetSpansInfo(1, 10);
    EXPECT_EQ(info1.selection_.selection[0], 1);
    EXPECT_EQ(info1.selection_.selection[1], 10);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 3);
    auto info2 = richEditorController->GetSpansInfo(10, 1);
    EXPECT_EQ(info2.selection_.selection[0], 1);
    EXPECT_EQ(info2.selection_.selection[1], 10);
    auto info3 = richEditorController->GetSpansInfo(-1, 10);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 10);
    auto info4 = richEditorController->GetSpansInfo(1, -10);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 1);
}

/**
 * @tc.name: RichEditorController007
 * @tc.desc: test delete span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController007, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option1;
    option1.start = 5;
    option1.end = 10;
    richEditorController->DeleteSpans(option1);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option2;
    option2.start = 10;
    option2.end = 5;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option3;
    option3.start = -5;
    option3.end = 10;
    richEditorController->DeleteSpans(option3);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option4;
    option4.start = 5;
    option4.end = -10;
    richEditorController->DeleteSpans(option4);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    RangeOptions option5;
    richEditorController->DeleteSpans(option5);
    EXPECT_TRUE(richEditorNode_->GetChildren().empty());
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 100;
    option5.end = 10;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);
    ClearSpan();
    AddSpan(INIT_VALUE_1);
    AddImageSpan();
    AddSpan(INIT_VALUE_2);
    option5.start = 3;
    option5.end = 3;
    richEditorController->DeleteSpans(option5);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);
    ClearSpan();
    richEditorController->DeleteSpans(option5);
}

/**
 * @tc.name: OnDirtyLayoutWrapper001
 * @tc.desc: test on dirty layout wrapper
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnDirtyLayoutWrapper001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        richEditorNode_, AceType::MakeRefPtr<GeometryNode>(), richEditorNode_->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm));
    DirtySwapConfig config;
    config.skipMeasure = true;
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    auto ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
    richEditorPattern->isRichEditorInit_ = true;

    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);

    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = -1;
    ret = richEditorPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CreateImageSourceInfo001
 * @tc.desc: test CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CreateImageSourceInfo001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    ImageSpanOptions info;
    auto ret = richEditorPattern->CreateImageSourceInfo(info);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test handle click event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    ParagraphStyle paragraphStyle;
    auto paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    richEditorPattern->pManager_->AddParagraph({ .paragraph = paragraph, .paragraphStyle = paragraphStyle });
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;

    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;

    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);

    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->hasClicked_ = false;
    richEditorPattern->HandleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: PreventDefault001
 * @tc.desc: test PreventDefault001 in ImageSpan and TextSpan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, PreventDefault001, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto richEditorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(richEditorNode, nullptr);
    auto richEditorPattern = richEditorNode->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    // add imageSpan
    ClearSpan();
    ImageSpanOptions imageSpanOptions;
    GestureEventFunc callback2 = [](GestureEvent& info) {
        info.SetPreventDefault(true);
    };
    imageSpanOptions.userGestureOption.onClick = callback2;
    richEditorController->AddImageSpan(imageSpanOptions);

    /**
     * @tc.steps: step1. Click on imagespan
     */
    GestureEvent info2;
    info2.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info2);
    EXPECT_FALSE(richEditorPattern->HasFocus());
}

/**
 * @tc.name: MoveCaretAfterTextChange001
 * @tc.desc: test move caret after text change
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, MoveCaretAfterTextChange001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->moveDirection_ = MoveDirection::BACKWARD;
    richEditorPattern->caretPosition_ = 5;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 4);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection::FORWARD;
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
    richEditorPattern->isTextChange_ = true;
    richEditorPattern->moveDirection_ = MoveDirection(-1);
    richEditorPattern->moveLength_ = 1;
    richEditorPattern->MoveCaretAfterTextChange();
    EXPECT_EQ(richEditorPattern->caretPosition_, 5);
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnKeyEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    KeyEvent keyE;

    keyE.action = KeyAction::DOWN;
    keyE.code = KeyCode::KEY_TAB;
    EXPECT_FALSE(richEditorPattern->OnKeyEvent(keyE));

    // 2012 2015
    keyE.action = KeyAction::DOWN;
    std::vector<KeyCode> eventCodes = {
        KeyCode::KEY_DPAD_LEFT,
        KeyCode::KEY_DPAD_UP,
        KeyCode::KEY_DPAD_RIGHT,
        KeyCode::KEY_DPAD_DOWN,
    };
    std::vector<KeyCode> presscodes = {};
    keyE.pressedCodes = presscodes;
    for (auto eventCode : eventCodes) {
        keyE.pressedCodes.clear();
        keyE.pressedCodes.emplace_back(eventCode);
        keyE.code = eventCode;
        auto ret = richEditorPattern->OnKeyEvent(keyE);
        EXPECT_TRUE(ret) << "KeyCode: " + std::to_string(static_cast<int>(eventCode));
    }
}

/**
 * @tc.name: GetLeftTextOfCursor001
 * @tc.desc: test GetLeftTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetLeftTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "e");

    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(2));
    EXPECT_EQ(ret, "e");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "t");

    richEditorPattern->textSelector_.baseOffset = 3;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(1));
    EXPECT_EQ(ret, "e");
}

/**
 * @tc.name: GetLeftTextOfCursor002
 * @tc.desc: test get left text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetLeftTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetLeftTextOfCursor(3));
    EXPECT_EQ(ret, "");
}

/**
 * @tc.name: GetRightTextOfCursor001
 * @tc.desc: test GetRightTextOfCursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetRightTextOfCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    richEditorPattern->textForDisplay_ = "tesol";
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 1;
    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "ol");

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 2;
    ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(2));
    EXPECT_EQ(ret, "es");
}

/**
 * @tc.name: GetRightTextOfCursor002
 * @tc.desc: test get right text of cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetRightTextOfCursor002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    auto ret = StringUtils::Str16ToStr8(richEditorPattern->GetRightTextOfCursor(3));
    EXPECT_EQ(ret, "hel");
}

/**
 * @tc.name: GetTextIndexAtCursor001
 * @tc.desc: test get text index at cursor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetTextIndexAtCursor001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->caretPosition_ = 3;
    EXPECT_EQ(richEditorPattern->GetTextIndexAtCursor(), 3);
}

/**
 * @tc.name: InitSelection001
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, InitSelection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->textForDisplay_ = "test";
    richEditorPattern->InitSelection(Offset(0, 0));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: InitSelection002
 * @tc.desc: test InitSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, InitSelection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->textForDisplay_ = "test";
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.front()->position = 3;
    richEditorPattern->InitSelection(Offset(0, 1));
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/**
 * @tc.name: CalcInsertValueObj001
 * @tc.desc: test CalcInsertValueObj
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CalcInsertValueObj001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("test1");
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto it = richEditorPattern->spans_.front();
    TextInsertValueInfo info;

    it->content = "test";
    it->position = 4;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->moveLength_ = 2;

    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 0);

    richEditorPattern->moveLength_ = -1;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 2);

    richEditorPattern->moveLength_ = 5;
    richEditorPattern->CalcInsertValueObj(info);
    EXPECT_EQ(info.spanIndex_, 2);
}

/**
 * @tc.name: MouseRightFocus001
 * @tc.desc: test MouseRightFocus
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, MouseRightFocus001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan("test1");
    AddImageSpan();
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    richEditorPattern->caretPosition_ = richEditorPattern->GetTextContentLength();
    richEditorPattern->moveLength_ = 0;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    MouseInfo info;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 0;
    richEditorPattern->MouseRightFocus(info);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: test handle mouse event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleMouseEvent002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo info;
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::MOVE;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::PRESS;
    richEditorPattern->HandleMouseEvent(info);
    info.action_ = MouseAction::RELEASE;
    EXPECT_TRUE(richEditorPattern->isMousePressed_);
    richEditorPattern->HandleMouseEvent(info);
    EXPECT_FALSE(richEditorPattern->blockPress_);
    EXPECT_FALSE(richEditorPattern->leftMousePress_);
    EXPECT_FALSE(richEditorPattern->isMouseSelect_);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
    EXPECT_TRUE(richEditorPattern->isFirstMouseSelect_);
}

/**
 * @tc.name: OnHover001
 * @tc.desc: test on hover
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnHover001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto host = richEditorPattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto id = host->GetId();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    richEditorPattern->OnHover(true);
    EXPECT_EQ(pipeline->mouseStyleNodeId_.value(), id);
    richEditorPattern->OnHover(false);
    EXPECT_FALSE(pipeline->mouseStyleNodeId_.has_value());
}

/**
 * @tc.name: OnHandleMove001
 * @tc.desc: test on handle move
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnHandleMove001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(richEditorPattern->caretPosition_, -1);

    richEditorPattern->caretPosition_ = -1;
    richEditorPattern->selectOverlay_->OnHandleMove(RectF(0.0f, 0.0f, 10.0f, 10.0f), false);
    EXPECT_EQ(richEditorPattern->caretPosition_, -1);
}

/**
 * @tc.name: OnAreaChangedInner001
 * @tc.desc: test OnAreaChangedInner
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnAreaChangedInner001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->OnAreaChangedInner();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    richEditorPattern->parentGlobalOffset_ = OffsetF(0, 1);

    richEditorPattern->OnAreaChangedInner();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/**
 * @tc.name: OnHandleMoveDone001
 * @tc.desc: test on handle move done
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnHandleMoveDone001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    auto eventHub = richEditorNode_->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->onSelect_ = std::move(func);
    richEditorPattern->OnHandleMoveDone(RectF(0.0f, 0.0f, 10.0f, 10.0f), true);
    EXPECT_EQ(testOnSelect, 1);
}

/**
 * @tc.name: GetSelectedSpanText002
 * @tc.desc: test get select span text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetSelectedSpanText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    auto ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), -1, 1);
    ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), -1, 10);
    ret = richEditorPattern->GetSelectedSpanText(StringUtils::ToWstring(INIT_VALUE_1), 0, 1);
    EXPECT_EQ(ret, "h");
}

/**
 * @tc.name: GetChildByIndex002
 * @tc.desc: test get child by index
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetChildByIndex002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->GetChildByIndex(-1);
    AddSpan(INIT_VALUE_1);
    auto ret = richEditorPattern->GetChildByIndex(0);
    EXPECT_EQ(*(richEditorNode_->GetChildren().begin()), ret);
}

/**
 * @tc.name: HandleMouseLeftButton001
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleMouseLeftButton001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::MOVE;
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->leftMousePress_ = false;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::NONE);

    auto paragraph = AceType::MakeRefPtr<MockParagraph>();
    EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(0));
    richEditorPattern->paragraphs_.paragraphs_.push_front({ paragraph });
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->blockPress_ = false;
    richEditorPattern->leftMousePress_ = true;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->isFirstMouseSelect_ = true;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);

    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->isFirstMouseSelect_ = false;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::MOVE);

    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(2, 5));
    richEditorPattern->textSelector_.baseOffset = 3;
    richEditorPattern->textSelector_.destinationOffset = 4;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::PRESSED);

    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    mouseInfo.SetGlobalLocation(Offset(2, 5));
    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 8;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::PRESSED);

    mouseInfo.action_ = MouseAction::RELEASE;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::RELEASED);

    mouseInfo.action_ = MouseAction::NONE;
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::NONE);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleMouseEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    MouseInfo mouseInfo;

    mouseInfo.action_ = MouseAction::PRESS;
    mouseInfo.button_ = MouseButton::LEFT_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.button_ = MouseButton::RIGHT_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.button_ = MouseButton::BACK_BUTTON;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
}

/**
 * @tc.name: GetChildByIndex001
 * @tc.desc: test GetChildByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetChildByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    AddSpan(INIT_VALUE_1);
    auto ret1 = richEditorPattern->GetChildByIndex(1);
    EXPECT_EQ(ret1, nullptr);
    auto ret2 = richEditorPattern->GetChildByIndex(-1);
    EXPECT_EQ(ret2, nullptr);
    auto ret3 = richEditorPattern->GetChildByIndex(0);
    EXPECT_NE(ret3, nullptr);
}

/**
 * @tc.name: GetSelectedSpanText001
 * @tc.desc: test GetSelectedSpanText
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetSelectedSpanText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::string ori = "12345";
    std::wstring value = StringUtils::ToWstring(ori);

    std::vector<int> start = { -1, 0, 15 };
    std::vector<int> end = { 10, -3 };

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            auto ret = richEditorPattern->GetSelectedSpanText(value, start[i], end[j]);
            EXPECT_EQ(ret, "");
        }
    }

    auto ret = richEditorPattern->GetSelectedSpanText(value, 0, 1);
    EXPECT_EQ(ret, "1");
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleSurfaceChanged001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    std::vector<std::vector<int>> cases = { { 1, 1, 2, 2 }, { 1, 2, 2, 2 }, { 1, 1, 1, 2 }, { 1, 2, 1, 2 } };
    for (uint32_t i = 0; i < cases.size(); ++i) {
        richEditorPattern->HandleSurfaceChanged(cases[i][0], cases[i][1], cases[i][2], cases[i][3]);
        EXPECT_NE(richEditorPattern, nullptr);
    }
}

/**
 * @tc.name: CopySelectionMenuParams001
 * @tc.desc: test CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CopySelectionMenuParams001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectOverlayInfo selectInfo;
    richEditorPattern->selectedType_ = TextSpanType::TEXT;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::IMAGE;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    richEditorPattern->selectedType_ = TextSpanType(-1);
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::LONG_PRESS);
    EXPECT_EQ(selectInfo.menuCallback.onDisappear, nullptr);

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;
    selectInfo.isUsingMouse = true;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);

    key = std::make_pair(TextSpanType::MIXED, TextResponseType::LONG_PRESS);
    std::shared_ptr<SelectionMenuParams> params2 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, nullptr, nullptr, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params2;
    selectInfo.isUsingMouse = false;
    richEditorPattern->selectedType_ = TextSpanType::MIXED;
    richEditorPattern->CopySelectionMenuParams(selectInfo, TextResponseType::RIGHT_CLICK);
    EXPECT_NE(selectInfo.menuCallback.onDisappear, nullptr);
}

/**
 * @tc.name: UpdateSelectionType001
 * @tc.desc: test UpdateSelectionType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, UpdateSelectionType001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    SelectionInfo selection;

    ResultObject obj1;
    obj1.type = SelectSpanType::TYPESPAN;
    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::TEXT);

    selection.selection_.resultObjects.pop_front();
    ResultObject obj2;
    obj2.type = SelectSpanType::TYPEIMAGE;
    selection.selection_.resultObjects.push_front(obj2);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::IMAGE);

    selection.selection_.resultObjects.push_front(obj1);
    richEditorPattern->UpdateSelectionType(selection);
    EXPECT_EQ(richEditorPattern->selectedType_.value(), TextSpanType::MIXED);
}

/**
 * @tc.name: CreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CreateNodePaintMethod001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: CreateNodePaintMethod002
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CreateNodePaintMethod002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->contentMod_ = AceType::MakeRefPtr<RichEditorContentModifier>(
        richEditorPattern->textStyle_, &richEditorPattern->paragraphs_, richEditorPattern);
    richEditorPattern->isCustomFont_ = true;
    richEditorPattern->CreateNodePaintMethod();
    EXPECT_NE(richEditorPattern->contentMod_, nullptr);
    EXPECT_NE(richEditorPattern->overlayMod_, nullptr);
}

/**
 * @tc.name: BindSelectionMenu001
 * @tc.desc: test BindSelectionMenu
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, BindSelectionMenu001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    callBack1 = 0;
    callBack2 = 0;
    callBack3 = 0;
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };

    auto key = std::make_pair(TextSpanType::MIXED, TextResponseType::RIGHT_CLICK);
    std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
        TextSpanType::MIXED, buildFunc, onAppear, onDisappear, TextResponseType::RIGHT_CLICK);
    richEditorPattern->selectionMenuMap_[key] = params1;

    std::function<void()> nullFunc = nullptr;

    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, nullFunc, onAppear, onDisappear);
    EXPECT_TRUE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->selectionMenuMap_[key] = params1;
    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::MIXED, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());

    richEditorPattern->BindSelectionMenu(
        TextResponseType::RIGHT_CLICK, TextSpanType::IMAGE, buildFunc, onAppear, onDisappear);
    EXPECT_FALSE(richEditorPattern->selectionMenuMap_.empty());
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test HandleMouseRightButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleMouseRightButton001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ClipboardProxy::GetInstance()->SetDelegate(nullptr);

    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::PRESS;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_TRUE(richEditorPattern->isMousePressed_);

    mouseInfo.action_ = MouseAction::HOVER;
    richEditorPattern->isMousePressed_ = false;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    mouseInfo.action_ = MouseAction::RELEASE;
    richEditorPattern->isMousePressed_ = true;
    mouseInfo.SetGlobalLocation({ 1, 5 });
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    richEditorPattern->textSelector_.baseOffset = 2;
    richEditorPattern->textSelector_.destinationOffset = 3;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);

    richEditorPattern->textSelector_.baseOffset = 1;
    richEditorPattern->textSelector_.destinationOffset = 9;
    richEditorPattern->HandleMouseRightButton(mouseInfo);
    EXPECT_FALSE(richEditorPattern->isMousePressed_);
}

/**
 * @tc.name: HandleOnCopy001
 * @tc.desc: test HandleOnCopy
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnCopy001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    AddSpan("test1");
    richEditorPattern->HandleOnCopy();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    richEditorPattern->HandleOnCopy();
    ClearSpan();
    AddImageSpan();
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
}

/**
 * @tc.name: HasSameTypingStyle001
 * @tc.desc: test HasSameTypingStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HasSameTypingStyle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->InsertValue(TEST_INSERT_VALUE);
    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = std::nullopt;
    auto ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = std::nullopt;
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = std::nullopt;
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);

    spanItem->textStyle_ = TextStyle();
    richEditorPattern->typingTextStyle_ = TextStyle();
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_TRUE(ret);

    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    ret = richEditorPattern->HasSameTypingStyle(it);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: GetSpanItemByIndex001
 * @tc.desc: test GetSpanItemByIndex
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetSpanItemByIndex001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->spans_.push_front(AceType::MakeRefPtr<SpanItem>());
    auto ret = richEditorPattern->GetSpanItemByIndex(-1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(1);
    EXPECT_EQ(ret, nullptr);
    ret = richEditorPattern->GetSpanItemByIndex(0);
    EXPECT_EQ(ret, richEditorPattern->spans_.front());
}

/**
 * @tc.name: GetParagraphNodes001
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetParagraphNodes001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto nodes = richEditorPattern->GetParagraphNodes(1, 5);
    EXPECT_EQ(nodes.size(), 0);
    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 0);

    // add multiple paragraphs
    AddSpan(INIT_VALUE_1 + "\n"); // length 7
    AddImageSpan();               // length 1
    AddSpan(INIT_VALUE_2 + "\n"); // length 7
    AddSpan(INIT_VALUE_1);        // length 6
    AddSpan(INIT_VALUE_2 + "\n");
    AddSpan(INIT_VALUE_2);
    AddSpan(INIT_VALUE_2 + "\n");
    AddSpan(INIT_VALUE_2);
    EXPECT_EQ(richEditorNode_->children_.size(), 8);

    nodes = richEditorPattern->GetParagraphNodes(3, 5);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(0)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(0, INT_MAX);
    EXPECT_EQ(nodes.size(), 7);

    nodes = richEditorPattern->GetParagraphNodes(10, 15);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(2)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(6, 7);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(0)->GetId());

    // selecting only the placeholder region
    nodes = richEditorPattern->GetParagraphNodes(7, 8);
    EXPECT_EQ(nodes.size(), 1);
    EXPECT_EQ(nodes[0]->GetId(), richEditorNode_->GetChildAtIndex(1)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(2, 20);
    EXPECT_EQ(nodes.size(), 4);
    EXPECT_EQ(nodes[3]->GetId(), richEditorNode_->GetChildAtIndex(4)->GetId());

    nodes = richEditorPattern->GetParagraphNodes(400, 404);
    EXPECT_EQ(nodes.size(), 0);
}

/**
 * @tc.name: GetParagraphNodes002
 * @tc.desc: test get paragraph nodes with multiple placeholders
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetParagraphNodes002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    // add multiple paragraphs
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1
    AddImageSpan(); // length 1

    EXPECT_EQ(richEditorNode_->children_.size(), 3);

    auto nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_TRUE(nodes.empty());

    AddSpan(INIT_VALUE_2);

    // selecting only placeholder, should return span in the same paragraph
    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 1);

    nodes = richEditorPattern->GetParagraphNodes(4, 6);
    EXPECT_EQ(nodes.size(), 1);
}

/**
 * @tc.name: GetParagraphNodes003
 * @tc.desc: test get paragraph nodes
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetParagraphNodes003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    AddSpan("0123");
    AddImageSpan();
    AddSpan("45789\n");
    AddSpan("aaaaaaaaaa");

    EXPECT_EQ(richEditorNode_->children_.size(), 4);

    auto nodes = richEditorPattern->GetParagraphNodes(50, 52);
    EXPECT_EQ(nodes.size(), 0);

    nodes = richEditorPattern->GetParagraphNodes(1, 2);
    EXPECT_EQ(nodes.size(), 2);
}

/**
 * @tc.name: GetParagraphLength001
 * @tc.desc: test get paragraph length
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetParagraphLength001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    // Add multiple paragraphs
    auto host = richEditorPattern->GetHost();
    AddImageSpan(); // length 1
    auto length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 1);
    AddImageSpan();
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 3);
    AddSpan(INIT_VALUE_1 + "\n"); // length 7
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 10);
    AddImageSpan();
    length = richEditorPattern->GetParagraphLength(host->GetChildren());
    EXPECT_EQ(length, 11);
}

/**
 * @tc.name: GetCaretRect001
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetCaretRect001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    EXPECT_EQ(richEditorOverlay->GetCaretOffset(), OffsetF(80.0f, 100.0f));
    EXPECT_EQ(richEditorOverlay->GetCaretHeight(), 60.0f);
    EXPECT_EQ(caretRect.GetOffset(), richEditorOverlay->GetCaretOffset());
    EXPECT_EQ(caretRect.Height(), richEditorOverlay->GetCaretHeight());
}

/**
 * @tc.name: GetCaretRect002
 * @tc.desc: test get caret rect
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetCaretRect002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    auto overlayMod = richEditorNode_->GetOverlayNode();
    auto richEditorOverlay = AceType::DynamicCast<RichEditorOverlayModifier>(richEditorPattern->overlayMod_);
    richEditorOverlay->SetCaretOffsetAndHeight(OffsetF(80.0f, 100.0f), 60.0f);
    auto caretRect = richEditorPattern->GetCaretRect();

    manager->SetClickPosition({ caretRect.GetOffset().GetX(), caretRect.GetOffset().GetY() });
    manager->SetHeight(caretRect.Height());
    manager->ScrollTextFieldToSafeArea();
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetX(), 0.0f), true);
    EXPECT_EQ(GreatNotEqual(manager->GetClickPosition().GetY(), 0.0f), true);

    EXPECT_EQ(GreatNotEqual(manager->GetHeight(), 0.0f), true);
    EXPECT_EQ(LessNotEqual(manager->GetHeight(), 800.0f), true);
}

/**
 * @tc.name: HandleMouseLeftButton002
 * @tc.desc: test HandleMouseLeftButton
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleMouseLeftButton002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    MouseInfo mouseInfo;
    mouseInfo.action_ = MouseAction::RELEASE;
    mouseInfo.SetGlobalLocation(MOUSE_GLOBAL_LOCATION);
    richEditorPattern->mouseStatus_ = MouseStatus::NONE;
    richEditorPattern->HandleMouseLeftButton(mouseInfo);
    EXPECT_EQ(richEditorPattern->mouseStatus_, MouseStatus::RELEASED);
    richEditorPattern->textSelector_ = TextSelector(0, 2);
    std::vector<TextSpanType> selectType = { TextSpanType::TEXT, TextSpanType::IMAGE, TextSpanType::MIXED };
    SelectOverlayInfo selectInfo;
    selectInfo.isUsingMouse = true;
    for (int32_t i = 0; i < static_cast<int32_t>(selectType.size()); i++) {
        richEditorPattern->selectedType_ = selectType[i];
        richEditorPattern->HandleMouseLeftButton(mouseInfo);
        EXPECT_NE(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetX()));
        EXPECT_NE(richEditorPattern->selectionMenuOffsetByMouse_.GetY(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetY()));
    }
    std::function<void()> buildFunc = []() {
        callBack1 = 1;
        return;
    };
    std::function<void(int32_t, int32_t)> onAppear = [](int32_t a, int32_t b) {
        callBack2 = 2;
        return;
    };
    std::function<void()> onDisappear = []() {
        callBack3 = 3;
        return;
    };
    richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
    for (int32_t i = 0; i < static_cast<int32_t>(selectType.size()); i++) {
        richEditorPattern->selectedType_ = selectType[i];
        auto key = std::make_pair(selectType[i], TextResponseType::SELECTED_BY_MOUSE);
        std::shared_ptr<SelectionMenuParams> params1 = std::make_shared<SelectionMenuParams>(
            selectType[i], buildFunc, onAppear, onDisappear, TextResponseType::SELECTED_BY_MOUSE);
        richEditorPattern->selectionMenuMap_[key] = params1;
        richEditorPattern->mouseStatus_ = MouseStatus::MOVE;
        richEditorPattern->HandleMouseLeftButton(mouseInfo);
        EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetX(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetX()));
        EXPECT_EQ(richEditorPattern->selectionMenuOffsetByMouse_.GetY(),
            static_cast<float>(mouseInfo.GetGlobalLocation().GetY()));
    }
}

/**
 * @tc.name: Selection001
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->SetSelection(0, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    auto richEditorSelection = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection.selection[0], 0);
    EXPECT_EQ(richEditorSelection.selection[1], 0);

    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetSelection(0, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);
    auto richEditorSelection2 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection2.selection[0], 0);
    EXPECT_EQ(richEditorSelection2.selection[1], 1);

    richEditorPattern->SetSelection(3, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 1);
    auto richEditorSelection3 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection3.selection[0], 1);
    EXPECT_EQ(richEditorSelection3.selection[1], 1);

    richEditorPattern->SetSelection(-1, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection4 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection4.selection[0], 0);
    EXPECT_EQ(richEditorSelection4.selection[1], 6);

    richEditorPattern->SetSelection(0, 10);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection5 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection5.selection[0], 0);
    EXPECT_EQ(richEditorSelection5.selection[1], 6);

    richEditorPattern->SetSelection(-2, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 3);
    EXPECT_EQ(richEditorPattern->caretPosition_, 3);
    auto richEditorSelection6 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection6.selection[0], 0);
    EXPECT_EQ(richEditorSelection6.selection[1], 3);

    richEditorPattern->SetSelection(-2, 8);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 6);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection7 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection7.selection[0], 0);
    EXPECT_EQ(richEditorSelection7.selection[1], 6);

    richEditorPattern->SetSelection(-2, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
    auto richEditorSelection8 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection8.selection[0], 6);
    EXPECT_EQ(richEditorSelection8.selection[1], 6);

    richEditorPattern->SetSelection(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 3);
    EXPECT_EQ(richEditorPattern->caretPosition_, 3);
    auto richEditorSelection9 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection9.selection[0], 1);
    EXPECT_EQ(richEditorSelection9.selection[1], 3);
}

/**
 * @tc.name: SetSelection002
 * @tc.desc: test SetSelection and GetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->RequestFocusImmediately();
    richEditorPattern->SetSelection(0, 1);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.step: step1. Empty text calls the setSelection interface.
     * @tc.expected: The interface exits normally, but it does not take effect
     */
    ClearSpan();
    richEditorPattern->SetSelection(1, 3);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
    auto richEditorSelection = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection.selection[0], 0);
    EXPECT_EQ(richEditorSelection.selection[1], 0);
    /**
     * @tc.step: step2. Extra-long text scenes.
     * @tc.expected: A portion of the selected text is not displayed, but the selection range can be updated
     * successfully
     */
    AddSpan(INIT_VALUE_3);
    SizeF sizeF(10.0f, 10.0f);
    richEditorNode_->GetGeometryNode()->SetContentSize(sizeF);
    richEditorPattern->SetSelection(15, 30);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 15);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 30);
    EXPECT_EQ(richEditorPattern->caretPosition_, 30);
    auto richEditorSelection2 = richEditorController->GetSelectionSpansInfo().GetSelection();
    EXPECT_EQ(richEditorSelection2.selection[0], 15);
    EXPECT_EQ(richEditorSelection2.selection[1], 30);
    ASSERT_NE(richEditorSelection2.resultObjects.size(), 0);
    auto resultObject = richEditorSelection2.resultObjects.front();
    EXPECT_EQ(resultObject.valueString, INIT_VALUE_3);
    EXPECT_EQ(resultObject.offsetInSpan[0], 15);
    EXPECT_EQ(resultObject.offsetInSpan[1], 30);
}

/**
 * @tc.name: Selection003
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection003, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);

    /**
     * @tc.step: step4. Call SetSelection with forward selection
     * @tc.expected: Cursor at start position
     */
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), start);

    /**
     * @tc.step: step5. Call SetSelection with backward selection
     * @tc.expected: Cursor at end position
     */
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), end);

    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: Selection004
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection004, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up
     * @tc.expected: Text is selected and the menu still pop up
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::DEFAULT;
    richEditorPattern->SetSelection(start, end, options);

    /**
     * @tc.step: step5. Call SetSelection with forward selection
     * @tc.expected: Cursor at start position
     */
    richEditorPattern->SetSelection(start, end, options, true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);

    /**
     * @tc.step: step6. Call SetSelection with backward selection
     * @tc.expected: Cursor at end position
     */
    richEditorPattern->SetSelection(start, end, options, false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), INIT_VALUE_1.length());

    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/**
 * @tc.name: Selection005
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection005, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu doesn't pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: Selection006
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection006, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up.
     * @tc.expected: Text is selected and menu doesn't pop up.
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::HIDE;
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/**
 * @tc.name: Selection007
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection007, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Call SetSelection with no menu
     * @tc.expected: Text is selected and the menu pop up
     */
    int32_t start = 0;
    int32_t end = 1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->OnModifyDone();
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, start);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, end);
}

/**
 * @tc.name: Selection008
 * @tc.desc: test SetSelection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, Selection008, TestSize.Level1)
{
    /**
     * @tc.step: step1. Add text span and get richeditor pattern.
     */
    AddSpan(INIT_VALUE_1);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.step: step2. Request focus.
     */
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    focusHub->RequestFocusImmediately();

    /**
     * @tc.step: step3. Create a scene where the text menu has popped up.
     */
    richEditorPattern->OnModifyDone();
    richEditorPattern->textSelector_.Update(0, 1);
    richEditorPattern->CalculateHandleOffsetAndShowOverlay();
    richEditorPattern->ShowSelectOverlay(
        richEditorPattern->textSelector_.firstHandle, richEditorPattern->textSelector_.secondHandle, false);
    EXPECT_TRUE(richEditorPattern->SelectOverlayIsOn());

    /**
     * @tc.step: step4. Call SetSelection with menu pop up.
     * @tc.expected: Text is selected and menu pop up.
     */
    int32_t start = -1;
    int32_t end = -1;
    SelectionOptions options;
    options.menuPolicy = MenuPolicy::SHOW;
    richEditorPattern->SetSelection(start, end, options);
    ClearSpan();
    EXPECT_FALSE(richEditorPattern->SelectOverlayIsOn());
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, INIT_VALUE_1.length());
}

/**
 * @tc.name: OnScrollCallback
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnScrollCallback, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();

    int32_t SCROLL_FROM_START = 10;
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(0, SCROLL_FROM_START));

    int32_t SCROLL_FROM_UPDATE = 1;
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Reach Top Boundary";

    richEditorPattern->richTextRect_ = RectF(0, -40, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_FALSE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Reach Bottom Boundary";

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);
    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE)) << "Scroll Up 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -10);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -10);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(-50, SCROLL_FROM_UPDATE)) << "Scroll Up 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -40);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -40);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(10, SCROLL_FROM_UPDATE)) << "Scroll Down 10";
    EXPECT_EQ(richEditorPattern->scrollOffset_, -30);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), -30);

    EXPECT_TRUE(richEditorPattern->OnScrollCallback(50, SCROLL_FROM_UPDATE)) << "Scroll Down 50";
    EXPECT_EQ(richEditorPattern->scrollOffset_, 0);
    EXPECT_EQ(richEditorPattern->richTextRect_.GetY(), 0);
}

/**
 * @tc.name: MoveHandle
 * @tc.desc: test whether the handle is moved when scrolling.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, MoveHandle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->textResponseType_ = TextResponseType::LONG_PRESS;
    richEditorPattern->selectOverlay_->ProcessOverlay({.animation = true});

    richEditorPattern->textSelector_.selectionBaseOffset = OffsetF(20, 20);
    richEditorPattern->textSelector_.firstHandle = RectF(20, 20, 20, 20);
    richEditorPattern->textSelector_.selectionDestinationOffset = OffsetF(60, 40);
    richEditorPattern->textSelector_.secondHandle = RectF(60, 40, 20, 20);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->OnScrollCallback(-10, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 10);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 30);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 30);

    richEditorPattern->OnScrollCallback(5, SCROLL_FROM_UPDATE);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionBaseOffset.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.firstHandle.GetY(), 15);
    EXPECT_EQ(richEditorPattern->textSelector_.selectionDestinationOffset.GetY(), 35);
    EXPECT_EQ(richEditorPattern->textSelector_.secondHandle.GetY(), 35);
}

/**
 * @tc.name: AutoScrollByEdgeDetection001
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, AutoScrollByEdgeDetection001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect = RectF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1, 20, 20);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "handle reach top edge";
    richEditorPattern->StopAutoScroll();

    auto handleHeight = 20;
    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1 - handleHeight, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "handle move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    param.handleRect =
        RectF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - handleHeight + 1, 20, handleHeight);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "handle reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection002
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, AutoScrollByEdgeDetection002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::MOUSE };
    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.GetY() + edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "mouse reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "mouse move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->contentRect_.Bottom() - edgeDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "mouse reach bottom edge";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection003
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, AutoScrollByEdgeDetection003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, -10, 100, 540);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 500);
    richEditorPattern->frameRect_ = RectF(0, 0, 100, 500);

    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::DRAG };
    Dimension AUTO_SCROLL_DRAG_EDGE_DISTANCE = 58.0_vp;
    auto dragDistance = AUTO_SCROLL_DRAG_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance + 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move up but not reach top edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, OffsetF(50, dragDistance - 10), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachTop()) << "drag reach top edge";
    auto speed = richEditorPattern->CalcDragSpeed(dragDistance, 0, dragDistance - 10);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, speed) << "darg speed move up";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->AutoScrollByEdgeDetection(param,
        OffsetF(50, richEditorPattern->frameRect_.Bottom() - dragDistance - 1), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "drag move down but not reach bottom edge";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    auto pointY = richEditorPattern->frameRect_.Bottom() - dragDistance + 10;
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, pointY), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_TRUE(richEditorPattern->IsReachBottom()) << "drag reach bottom edge";
    speed = richEditorPattern->CalcDragSpeed(
        richEditorPattern->frameRect_.Bottom() - dragDistance, richEditorPattern->frameRect_.Bottom(), pointY);
    EXPECT_EQ(richEditorPattern->currentScrollParam_.offset, -speed) << "darg speed move down";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: AutoScrollByEdgeDetection004
 * @tc.desc: Verify that the OnScrollCallback interface calls normally and exits without exception.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, AutoScrollByEdgeDetection004, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    Dimension AUTO_SCROLL_EDGE_DISTANCE = 15.0_vp;
    auto edgeDistance = AUTO_SCROLL_EDGE_DISTANCE.ConvertToPx();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(50, 50);
    AutoScrollParam param = { .autoScrollEvent = AutoScrollEvent::HANDLE, .handleRect = RectF(50, 50, 20, 20) };
    richEditorPattern->AutoScrollByEdgeDetection(param, OffsetF(50, 50), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "the touch point is the same as the last time";
    richEditorPattern->StopAutoScroll();

    richEditorPattern->prevAutoScrollOffset_ = OffsetF(0, 0);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, edgeDistance - 1);
    richEditorPattern->AutoScrollByEdgeDetection(
        param, param.handleRect.GetOffset(), EdgeDetectionStrategy::OUT_BOUNDARY);
    EXPECT_FALSE(richEditorPattern->autoScrollTask_) << "content height is too small.";
    richEditorPattern->StopAutoScroll();

    pipeline->taskExecutor_.Reset();
}

/**
 * @tc.name: CheckScrollable
 * @tc.desc: test CheckScrollable.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CheckScrollable, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 140);
    richEditorPattern->contentRect_ = RectF(0, 0, 100, 100);

    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    AddSpan(TEST_INSERT_VALUE);
    richEditorPattern->CheckScrollable();
    EXPECT_TRUE(richEditorPattern->scrollable_);

    richEditorPattern->richTextRect_ = RectF(0, 0, 100, 80);
    richEditorPattern->CheckScrollable();
    EXPECT_FALSE(richEditorPattern->scrollable_);

    ClearSpan();
}

/**
 * @tc.name: NeedSoftKeyboard001
 * @tc.desc: test NeedSoftKeyboard
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, NeedSoftKeyboard001, TestSize.Level1)
{
    /**
     * @tc.step: step1. Get frameNode and pattern.
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /**
     * @tc.steps: step2. Test whether rich editor need soft keyboard.
     */
    EXPECT_TRUE(richEditorPattern->NeedSoftKeyboard());
}

/*
 * @tc.name: DoubleHandleClickEvent001
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, DoubleHandleClickEvent001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    AddSpan(INIT_VALUE_1);
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->caretVisible_);

    AddSpan(INIT_VALUE_3);
    info.localLocation_ = Offset(50, 50);
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_NE(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_NE(richEditorPattern->textSelector_.destinationOffset, -1);
    EXPECT_NE(richEditorPattern->caretPosition_, -1);

    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = true;
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->HandleDoubleClickEvent(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 0);
}

/*
 * @tc.name: DoubleHandleClickEvent002
 * @tc.desc: test Mouse Double Click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, DoubleHandleClickEvent002, TestSize.Level1)
{
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    AddSpan(TEST_INSERT_VALUE);

    TestParagraphRect paragraphRect = { .start = 0, .end = 1, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 1,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } },
        .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);

    GestureEvent info;
    richEditorPattern->isMousePressed_ = true;
    info.SetSourceDevice(SourceType::MOUSE);
    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::DOUBLE_CLICK;
    richEditorPattern->caretPosition_ = 0;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->isMouseSelect_ = false;
    richEditorPattern->caretVisible_ = true;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, 0);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, 1);

    richEditorPattern->textSelector_.baseOffset = -1;
    richEditorPattern->textSelector_.destinationOffset = -1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::LONG_PRESSED;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_EQ(richEditorPattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(richEditorPattern->textSelector_.destinationOffset, -1);
}

/*
 * @tc.name: DoubleHandleClickEvent001
 * @tc.desc: test double click
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, AdjustWordCursorAndSelect01, TestSize.Level1)
{
    using namespace std::chrono;
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    AddSpan(INIT_VALUE_1);
    int32_t pos = 3;

    MockDataDetectorMgr mockDataDetectorMgr;
    InitAdjustObject(mockDataDetectorMgr);

    richEditorPattern->lastAiPosTimeStamp_ = high_resolution_clock::now();
    richEditorPattern->lastClickTimeStamp_ = richEditorPattern->lastAiPosTimeStamp_ + seconds(2);
    int32_t spanStart = -1;
    std::string content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 2);

    int32_t start = 1;
    int32_t end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 2);
    EXPECT_EQ(end, 3);

    AddSpan(INIT_VALUE_2);
    pos = 1;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, 4);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, 0);
    EXPECT_EQ(end, 2);

    ClearSpan();
    pos = 2;
    content = richEditorPattern->GetPositionSpansText(pos, spanStart);
    mockDataDetectorMgr.AdjustCursorPosition(
        pos, content, richEditorPattern->lastAiPosTimeStamp_, richEditorPattern->lastClickTimeStamp_);
    EXPECT_EQ(pos, -1);

    start = 1;
    end = 3;
    mockDataDetectorMgr.AdjustWordSelection(pos, content, start, end);
    EXPECT_EQ(start, -1);
    EXPECT_EQ(end, -1);
}

/**
 * @tc.name: RichEditorController008
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController008, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    auto builderSpanChildren = richEditorNode_->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpanChild = builderSpanChildren.begin();
    EXPECT_EQ((*builderSpanChild)->GetTag(), "Span");
    ClearSpan();
}

/**
 * @tc.name: RichEditorController009
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController009, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    RefPtr<GeometryNode> containerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(containerGeometryNode == nullptr);
    containerGeometryNode->SetFrameSize(SizeF(CONTAINER_WIDTH, CONTAINER_HEIGHT));
    ASSERT_NE(richEditorNode_->GetLayoutProperty(), nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(richEditorNode_, containerGeometryNode, richEditorNode_->GetLayoutProperty());

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));

    auto builderId1 = ElementRegister::GetInstance()->MakeUniqueId();
    auto builderNode1 = FrameNode::GetOrCreateFrameNode(
        V2::ROW_ETS_TAG, builderId1, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    auto builderSpanChildren = richEditorNode_->GetChildren();
    ASSERT_NE(static_cast<int32_t>(builderSpanChildren.size()), 0);
    auto builderSpan = builderSpanChildren.begin();
    auto builderSpanChild = AceType::DynamicCast<FrameNode>(*builderSpan);
    ASSERT_NE(builderSpanChild, nullptr);
    EXPECT_EQ(builderSpanChild->GetTag(), V2::PLACEHOLDER_SPAN_ETS_TAG);

    auto richEditorLayoutAlgorithm = richEditorPattern->CreateLayoutAlgorithm();
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(richEditorLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(BUILDER_SIZE);

    RefPtr<GeometryNode> builderGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    builderGeometryNode->Reset();
    RefPtr<LayoutWrapperNode> builderLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        builderSpanChild, builderGeometryNode, builderSpanChild->GetLayoutProperty());
    EXPECT_FALSE(builderLayoutWrapper == nullptr);
    auto builderPattern = builderSpanChild->GetPattern();
    builderLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    auto firstItemLayoutAlgorithm = builderPattern->CreateLayoutAlgorithm();
    EXPECT_FALSE(firstItemLayoutAlgorithm == nullptr);
}

/**
 * @tc.name: RichEditorController010
 * @tc.desc: test add builder span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController010, TestSize.Level1)
{
    auto nodeId = ViewStackProcessor::GetInstance()->ClaimNodeId();
    richEditorNode_ = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<RichEditorPattern>(); });
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->SetRichEditorController(AceType::MakeRefPtr<RichEditorController>());
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->GetRichEditorController()->SetPattern(AceType::WeakClaim(AceType::RawPtr(richEditorPattern)));
    AddSpan("test");
    RefPtr<FrameNode> builderNode1 = nullptr;
    auto index1 = richEditorController->AddPlaceholderSpan(builderNode1, {});
    EXPECT_EQ(index1, 0);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 1);
    ClearSpan();
}

/**
 * @tc.name: RichEditorController011
 * @tc.desc: test add symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController011, TestSize.Level1)
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
     * @tc.steps: step3. test add symbol span
     */
    auto index1 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index1, 0);
    auto index2 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index2, 1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 2);
    ClearSpan();
}

/**
 * @tc.name: RichEditorController012
 * @tc.desc: test update symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController012, TestSize.Level1)
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
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;
    updateSpanStyle.updateFontWeight = FONT_WEIGHT_BOLD;
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
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetFontSize(), FONT_SIZE_VALUE_2);
    EXPECT_EQ(newSpan1->GetFontWeight(), FONT_WEIGHT_BOLD);
    EXPECT_EQ(newSpan1->GetSymbolColorList(), SYMBOL_COLOR_LIST_2);
    EXPECT_EQ(newSpan1->GetSymbolRenderingStrategy(), RENDER_STRATEGY_MULTI_COLOR);
    EXPECT_EQ(newSpan1->GetSymbolEffectStrategy(), EFFECT_STRATEGY_SCALE);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(newSpan2->GetFontWeight(), FONT_WEIGHT_VALUE);
    EXPECT_EQ(newSpan2->GetSymbolColorList(), SYMBOL_COLOR_LIST_1);
    EXPECT_EQ(newSpan2->GetSymbolRenderingStrategy(), RENDER_STRATEGY_SINGLE);
    EXPECT_EQ(newSpan2->GetSymbolEffectStrategy(), EFFECT_STRATEGY_NONE);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController013
 * @tc.desc: test get symbol span info
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController013, TestSize.Level1)
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
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);

    /**
     * @tc.steps: step4. get symbol span info
     */
    auto info1 = richEditorController->GetSpansInfo(2, 5);
    EXPECT_EQ(info1.selection_.selection[0], 2);
    EXPECT_EQ(info1.selection_.selection[1], 5);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 2);

    auto info2 = richEditorController->GetSpansInfo(5, 2);
    EXPECT_EQ(info2.selection_.selection[0], 2);
    EXPECT_EQ(info2.selection_.selection[1], 5);
    EXPECT_EQ(info2.selection_.resultObjects.size(), 2);

    auto info3 = richEditorController->GetSpansInfo(-2, 5);
    EXPECT_EQ(info3.selection_.selection[0], 0);
    EXPECT_EQ(info3.selection_.selection[1], 5);
    EXPECT_EQ(info3.selection_.resultObjects.size(), 3);

    auto info4 = richEditorController->GetSpansInfo(2, -5);
    EXPECT_EQ(info4.selection_.selection[0], 0);
    EXPECT_EQ(info4.selection_.selection[1], 2);
    EXPECT_EQ(info4.selection_.resultObjects.size(), 1);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController014
 * @tc.desc: test delete symbol span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController014, TestSize.Level1)
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
    auto index3 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index3, 2);
    auto index4 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index4, 3);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 4);

    /**
     * @tc.steps: step4. delete single symbol span
     */
    RangeOptions option2;
    option2.start = 0;
    option2.end = 2;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);

    option2.start = 2;
    option2.end = 0;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);

    option2.start = -1;
    option2.end = 2;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);

    option2.start = 2;
    option2.end = -1;
    richEditorController->DeleteSpans(option2);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);

    /**
     * @tc.steps: step5. add symbol span
     */
    auto index5 = richEditorController->AddSymbolSpan(options);
    EXPECT_EQ(index5, 0);

    /**
     * @tc.steps: step6. delete symbol span
     */
    option2.start = 0;
    option2.end = 1;
    richEditorController->DeleteSpans(option2); // delete half symbol span, will fail
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 0);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController015
 * @tc.desc: test use span & imagespan & symbolspan together
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController015, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddSymbolSpan(options1);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddImageSpan(options3);
    richEditorController->AddTextSpan(options2);
    richEditorController->AddSymbolSpan(options1);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 5);

    /**
     * @tc.steps: step4. test get span
     */
    auto info1 = richEditorController->GetSpansInfo(0, 3);
    EXPECT_EQ(info1.selection_.resultObjects.size(), 2);
    auto info2 = richEditorController->GetSpansInfo(8, 9);
    EXPECT_EQ(info2.selection_.resultObjects.size(), 1);

    /**
     * @tc.steps: step5. test update span
     */
    TextStyle textStyle;
    textStyle.SetFontSize(FONT_SIZE_VALUE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontSize = FONT_SIZE_VALUE_2;

    richEditorController->SetUpdateSpanStyle(updateSpanStyle);
    ImageSpanAttribute imageStyle;
    richEditorController->UpdateSpanStyle(2, 8, textStyle, imageStyle);

    auto newSpan2 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(1));
    ASSERT_NE(newSpan2, nullptr);
    EXPECT_EQ(newSpan2->GetFontSize(), FONT_SIZE_VALUE_2);

    /**
     * @tc.steps: step6. test delete span
     */
    RangeOptions option;
    option.start = 8;
    option.end = 15;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 3);

    option.start = 0;
    option.end = 2;
    richEditorController->DeleteSpans(option);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);

    ClearSpan();
}

/**
 * @tc.name: RichEditorController016
 * @tc.desc: test add many spans
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorController016, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    SymbolSpanOptions options1;
    options1.symbolId = SYMBOL_ID;
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;
    ImageSpanOptions options3;
    options3.image = IMAGE_VALUE;

    /**
     * @tc.steps: step3. test add span
     */
    for (int i = 0; i < 100; i++) {
        richEditorController->AddSymbolSpan(options1);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddImageSpan(options3);
        richEditorController->AddTextSpan(options2);
        richEditorController->AddSymbolSpan(options1);
    }
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 500);

    ClearSpan();
}

/**
 * @tc.name: RichEditorDragTest001
 * @tc.desc: test the drag of RichEditor without developer's onDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDragTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    ImageSpanOptions imageOptions;
    imageOptions.image = IMAGE_VALUE;
    controller->AddImageSpan(imageOptions);
    pattern->textSelector_.Update(0, 6);
    auto onDragStart = eventHub->GetDefaultOnDragStart();
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, "");
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), -1);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), -1);
    EXPECT_EQ(pattern->status_, Status::DRAGGING);
    eventHub->FireOnDragMove(event, "");
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest002
 * @tc.desc: test the drag of RichEditor with developer's onDragStart function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDragTest002, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    auto dragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event, const std::string& extraParams) -> NG::DragDropInfo {
        NG::DragDropInfo info;
        info.extraInfo = INIT_VALUE_1;
        return info;
    };
    eventHub->SetOnDragStart(std::move(dragStart));
    EXPECT_TRUE(eventHub->HasOnDragStart());
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    controller->AddTextSpan(options);
    ImageSpanOptions imageOptions;
    imageOptions.image = IMAGE_VALUE;
    controller->AddImageSpan(imageOptions);
    pattern->textSelector_.Update(0, 6);
    auto onDragStart = eventHub->GetOnDragStart();
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    auto dragDropInfo = onDragStart(event, "");
    EXPECT_EQ(dragDropInfo.extraInfo, INIT_VALUE_1);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 6);
    EXPECT_EQ(pattern->status_, Status::NONE);
    eventHub->FireOnDragMove(event, "");
    auto onDragEnd = eventHub->GetOnDragEnd();
    onDragEnd(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest003
 * @tc.desc: test the drag of RichEditor with developer's onDragDrop function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDragTest003, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasDefaultOnDragStart());
    EXPECT_TRUE(eventHub->HasOnDrop());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_3;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    pattern->textSelector_.Update(0, 6);
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireOnDrop(event, "");
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: RichEditorDragTest004
 * @tc.desc: test the drag of RichEditor with developer's HandleOnDragDropTextOperation function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorDragTest004, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    host->draggable_ = true;
    auto eventHub = host->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(pattern, nullptr);
    auto gesture = host->GetOrCreateGestureEventHub();
    ASSERT_NE(gesture, nullptr);
    EXPECT_TRUE(gesture->GetTextDraggable());
    gesture->SetIsTextDraggable(true);
    pattern->InitDragDropEvent();
    EXPECT_TRUE(eventHub->HasOnDrop());
    auto controller = pattern->GetRichEditorController();
    ASSERT_NE(controller, nullptr);
    TextStyle style;
    TextSpanOptions options;
    options.value = INIT_VALUE_1 + INIT_VALUE_1;
    options.style = style;
    auto index = controller->AddTextSpan(options);
    EXPECT_EQ(index, 0);
    pattern->dragRange_.first = 0;
    pattern->caretPosition_ = options.value.length();
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    pattern->dragRange_.first = options.value.length();
    pattern->caretPosition_ = 0;
    pattern->HandleOnDragDropTextOperation(INIT_VALUE_1, true);
    EXPECT_EQ(pattern->status_, Status::NONE);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: GetTextSpansInfo
 * @tc.desc: test get paragraphStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetTextSpansInfo, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options;
    options.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options);

    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);

    auto info = richEditorController->GetSpansInfo(0, 6);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto valueString = info.selection_.resultObjects.begin()->valueString;
    auto textStyle = info.selection_.resultObjects.begin()->textStyle;

    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_EQ(textStyle.leadingMarginSize[0], "5.00px");
    EXPECT_EQ(textStyle.leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: GetImageSpansInfo
 * @tc.desc: test image span layoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, GetImageSpansInfo, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddImageSpan(options);
    auto info = richEditorController->GetSpansInfo(0, 1);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);
    auto imageStyleout = info.selection_.resultObjects.begin()->imageStyle;
    EXPECT_EQ(imageStyleout.borderRadius,
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");
    EXPECT_EQ(imageStyleout.margin, "left: [10.00px]right: [10.00px]top: [10.00px]bottom: [10.00px]");
    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetTextSpan
 * @tc.desc: test add delete text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, DeleteValueSetTextSpan, TestSize.Level1)
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
     * @tc.steps: step2. test add span
     */
    AddSpan(INIT_VALUE_1);
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    auto info = richEditorController->GetSpansInfo(0, 6);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);

    auto it = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    auto spanItem = it->GetSpanItem();
    spanItem->position = 0;
    spanItem->textStyle_ = TextStyle();
    spanItem->textStyle_.value().fontFamilies_.push_back("test1");
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    richEditorPattern->DeleteValueSetTextSpan(spanItem, 0, 1, spanResult);

    EXPECT_EQ(spanResult.GetTextStyle().textAlign, int(TextAlign::END));
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[0], "5.00px");
    EXPECT_EQ(spanResult.GetTextStyle().leadingMarginSize[1], "10.00px");

    ClearSpan();
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, onIMEInputComplete, TestSize.Level1)
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
     * @tc.steps: step2. add text span
     */
    AddSpan(INIT_VALUE_1);
    struct UpdateParagraphStyle style1;
    style1.textAlign = TextAlign::END;
    style1.leadingMargin = std::make_optional<NG::LeadingMargin>();
    style1.leadingMargin->size = LeadingMarginSize(Dimension(5.0), Dimension(10.0));
    richEditorPattern->UpdateParagraphStyle(0, 6, style1);
    auto info = richEditorController->GetSpansInfo(0, 6);
    EXPECT_EQ(info.selection_.resultObjects.size(), 1);

    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    EXPECT_EQ(textStyle.textAlign, int(TextAlign::END));
    EXPECT_EQ(textStyle.leadingMarginSize[0], "5.00px");
    EXPECT_EQ(textStyle.leadingMarginSize[1], "10.00px");
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }

    ClearSpan();
}

/**
 * @tc.name: DeleteValueSetImageSpan
 * @tc.desc: test delete imagespan
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, DeleteValueSetImageSpan, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    ImageSpanOptions options;
    options.image = IMAGE_VALUE;
    std::optional<Ace::NG::MarginProperty> marginProp = std::nullopt;
    std::optional<Ace::NG::BorderRadiusProperty> borderRadius = std::nullopt;
    marginProp = { CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC, CALC_LENGTH_CALC };
    borderRadius = { CALC_TEST, CALC_TEST, CALC_TEST, CALC_TEST };
    ImageSpanAttribute imageStyle;
    imageStyle.marginProp = marginProp;
    imageStyle.borderRadius = borderRadius;
    options.imageAttribute = imageStyle;

    /**
     * @tc.steps: step3. test delete image span
     */
    richEditorController->AddImageSpan(options);
    RichEditorAbstractSpanResult spanResult;
    spanResult.SetSpanIndex(0);
    auto spanItem = richEditorPattern->spans_.front();
    richEditorPattern->DeleteValueSetImageSpan(spanItem, spanResult);
    EXPECT_EQ(spanResult.GetMargin(), "left: [10.00px]right: [10.00px]top: [10.00px]bottom: [10.00px]");
    EXPECT_EQ(spanResult.GetBorderRadius(),
        "{\"topLeft\":\"10.00px\",\"topRight\":\"10.00px\",\"bottomLeft\":\"10.00px\",\"bottomRight\":\"10.00px\"}");

    ClearSpan();
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, onIMEInputComplete002, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    /**
     * @tc.steps: step3. add text span
     */
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    EXPECT_EQ(textStyle.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: onIMEInputComplete
 * @tc.desc: test onIMEInputComplete
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, onIMEInputComplete003, TestSize.Level1)
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
     * @tc.steps: step2. initalize span properties
     */
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    /**
     * @tc.steps: step3. add text span
     */
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    TextStyleResult textStyle;
    auto func = [&textStyle](const RichEditorAbstractSpanResult& info) { textStyle = info.GetTextStyle(); };
    eventHub->SetOnIMEInputComplete(std::move(func));
    auto it1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetLastChild());
    richEditorPattern->AfterIMEInsertValue(it1, 1, false);
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, UpdateTextStyle, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE);
    textStyle.SetLineHeight(LINE_HEIGHT_VALUE);
    textStyle.SetLetterSpacing(LETTER_SPACING);

    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateLineHeight = LINE_HEIGHT_VALUE;
    updateSpanStyle.updateLetterSpacing = LETTER_SPACING;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;

    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    EXPECT_EQ(newSpan1->GetLineHeight(), LINE_HEIGHT_VALUE);
    EXPECT_EQ(newSpan1->GetLetterSpacing(), LETTER_SPACING);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: UpdateTextStyle
 * @tc.desc: test update span style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, UpdateTextStyle2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    AddSpan(INIT_VALUE_1);
    auto newSpan1 = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    TextStyle textStyle;
    ImageSpanAttribute imageStyle;
    textStyle.SetFontFeatures(TEXT_FONTFEATURE_2);
    struct UpdateSpanStyle updateSpanStyle;
    updateSpanStyle.updateFontFeature = TEXT_FONTFEATURE;
    richEditorPattern->UpdateTextStyle(newSpan1, updateSpanStyle, textStyle);
    ASSERT_NE(newSpan1, nullptr);
    for (const auto& pair : *newSpan1->GetFontFeature()) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}
/**
 * @tc.name: SetOnSelect
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetOnSelect, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test set on select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetOnSelect2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    SelectionInfo selection;
    eventHub->FireOnSelect(&selection);
    EXPECT_EQ(testOnSelect, 1);
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetTypingStyle, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    AddSpan(INIT_VALUE_1);
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    EXPECT_EQ(textStyle2.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle2.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetTypingStyle
 * @tc.desc: test Typing Style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetTypingStyle2, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    UpdateSpanStyle typingStyle;
    richEditorPattern->SetTypingStyle(typingStyle, style);
    TextSpanOptions options1;
    options1.style = richEditorPattern->typingTextStyle_;
    auto info1 = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle2 = info1.selection_.resultObjects.front().textStyle;
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test Set On Select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetOnSelect003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto spanNode = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    EXPECT_EQ(textStyle1.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(textStyle1.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetOnSelect
 * @tc.desc: test Set On Select
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetOnSelect004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    auto info = richEditorController->GetSpansInfo(1, 5);
    ASSERT_NE(info.selection_.resultObjects.size(), 0);
    TextStyleResult textStyle1 = info.selection_.resultObjects.front().textStyle;
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto spanNode = AceType::DynamicCast<SpanNode>(richEditorNode_->GetChildAtIndex(0));
    auto func = [](const BaseEventInfo* info) { testOnSelect = 1; };
    richEditorModel.SetOnSelect(std::move(func));
    for (const auto& pair : textStyle1.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: SetSelection
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetSelection, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetLineHeight(LINE_HEIGHT_VALUE);
    style.SetLetterSpacing(LETTER_SPACING);
    style.SetFontFeatures(TEXT_FONTFEATURE);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->SetSelection(1, 3);
    auto info1 = richEditorController->GetSpansInfo(1, 2);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.lineHeight, LINE_HEIGHT_VALUE.ConvertToVp());
    EXPECT_EQ(info1.selection_.resultObjects.front().textStyle.letterSpacing, LETTER_SPACING.ConvertToVp());
    for (const auto& pair : info1.selection_.resultObjects.front().textStyle.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 1);
    }
    ClearSpan();
}

/**
 * @tc.name: SetSelection
 * @tc.desc: test Set Selection
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetSelection2, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    TextStyle style;
    style.SetFontFeatures(TEXT_FONTFEATURE_2);
    TextSpanOptions options;
    options.value = INIT_VALUE_1;
    options.style = style;
    richEditorController->AddTextSpan(options);
    AddSpan(INIT_VALUE_1);
    richEditorPattern->SetSelection(1, 3);
    auto info1 = richEditorController->GetSpansInfo(1, 2);
    ASSERT_NE(info1.selection_.resultObjects.size(), 0);
    for (const auto& pair : info1.selection_.resultObjects.front().textStyle.fontFeature) {
        EXPECT_EQ(pair.first, "subs");
        EXPECT_EQ(pair.second, 0);
    }
    ClearSpan();
}

/**
 * @tc.name: CaretColorTest001
 * @tc.desc: test set and get caretColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, CaretColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    Color patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, SYSTEM_CARET_COLOR);
    model.SetCaretColor(Color::BLUE);
    patternCaretColor = richEditorPattern->GetCaretColor();
    EXPECT_EQ(patternCaretColor, Color::BLUE);
}

/**
 * @tc.name: SelectedBackgroundColorTest001
 * @tc.desc: test set and get selectedBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SelectedBackgroundColorTest001, TestSize.Level1)
{
    RichEditorModelNG model;
    model.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    Color patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    EXPECT_EQ(patternSelectedBackgroundColor, SYSTEM_SELECT_BACKGROUND_COLOR);
    model.SetSelectedBackgroundColor(Color::RED);
    patternSelectedBackgroundColor = richEditorPattern->GetSelectedBackgroundColor();
    auto selectedBackgroundColorResult = Color::RED.ChangeOpacity(DEFAILT_OPACITY);
    EXPECT_EQ(patternSelectedBackgroundColor, selectedBackgroundColorResult);
}

/**
 * @tc.name: HandleOnEditChanged001
 * @tc.desc: test Get focus edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnEditChanged001, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Get the focus to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    richEditorPattern->HandleFocusEvent();
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged002
 * @tc.desc: test Lose focus edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnEditChanged002, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Lose the focus to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    richEditorPattern->HandleBlurEvent();
    EXPECT_FALSE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged003
 * @tc.desc: test Long press edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnEditChanged003, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorController->IsEditing());

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Long press to trigger the callback function and modify the editing status
     */

    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged004
 * @tc.desc: test Click on edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnEditChanged004, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. Click on to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    GestureEvent info;
    info.SetSourceDevice(SourceType::MOUSE);
    richEditorPattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: HandleOnEditChanged005
 * @tc.desc: test mouse release while dragging edit status is true
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnEditChanged005, TestSize.Level1)
{
    /* *
     * @tc.steps: step1. get richEditor richEditorPattern
     */
    ASSERT_NE(richEditorNode_, nullptr);

    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    /* *
     * @tc.steps: step2. Setting Callback Function
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetOnEditingChange([](bool value) {});

    /* *
     * @tc.steps: step3. mouse release while dragging to trigger the callback function and modify the editing status
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);

    MouseInfo info;
    auto focusHub = richEditorPattern->GetHost()->GetOrCreateFocusHub();
    focusHub->currentFocus_ = true;
    richEditorPattern->HandleMouseLeftButtonRelease(info);
    EXPECT_TRUE(richEditorController->IsEditing());
}

/**
 * @tc.name: StopEditingTest
 * @tc.desc: test StopEditing
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, StopEditingTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto focusHub = richEditorNode_->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);
    focusHub->RequestFocusImmediately();
    EXPECT_TRUE(focusHub->IsCurrentFocus());
    richEditorPattern->caretTwinkling_ = true;
    richEditorController->StopEditing();

    EXPECT_FALSE(richEditorPattern->caretTwinkling_);

    ClearSpan();
}

/**
 * @tc.name: OnSubmitTest
 * @tc.desc: test OnSubmitTest
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, OnSubmitTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    /**
     * @tc.steps: step2. initalize span properties
     */
    TextSpanOptions options2;
    options2.value = INIT_VALUE_1;

    /**
     * @tc.steps: step3. test add span
     */
    richEditorController->AddTextSpan(options2);

    int count = 0;
    TextFieldCommonEvent event2;
    auto callback = [&count, &event2](int32_t key, NG::TextFieldCommonEvent& event) {
        event2 = event;
        if (count > 0) {
            event.SetKeepEditable(true);
        }
        count = count + 1;
    };
    eventHub->SetOnSubmit(std::move(callback));

    TextInputAction action2 = TextInputAction::NEW_LINE;
    bool forceCloseKeyboard = false;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 0);

    action2 = TextInputAction::DONE;
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 1);
    richEditorPattern->PerformAction(action2, forceCloseKeyboard);
    EXPECT_EQ(count, 2);
    ClearSpan();
}

/**
 * @tc.name: SetEnterKeyType
 * @tc.desc: test SetEnterKeyType
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetEnterKeyType, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor controller
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    richEditorModel.SetEnterKeyType(TextInputAction::NEW_LINE);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    richEditorModel.SetEnterKeyType(TextInputAction::UNSPECIFIED);
    richEditorNode_->MarkModifyDone();
    EXPECT_EQ(richEditorPattern->GetTextInputActionValue(richEditorPattern->GetDefaultTextInputAction()),
        TextInputAction::NEW_LINE);
    ClearSpan();
}

/**
 * @tc.name: SupportAvoidanceTest
 * @tc.desc: test whether the custom keyboard supports the collision avoidance function
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SupportAvoidanceTest, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto overlayManager = pipeline->GetOverlayManager();
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto supportAvoidance = true;
    richEditorPattern->SetCustomKeyboardOption(supportAvoidance);
    auto support = richEditorPattern->keyboardAvoidance_;
    overlayManager->SetCustomKeyboardOption(support);
    EXPECT_TRUE(richEditorPattern->keyboardAvoidance_);
    supportAvoidance = false;
    richEditorPattern->SetCustomKeyboardOption(supportAvoidance);
    overlayManager->SetCustomKeyboardOption(support);
    EXPECT_FALSE(richEditorPattern->keyboardAvoidance_);
}

/**
 * @tc.name: HandleOnCut002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnCut002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCut003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnCut003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCutWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCut(std::move(onCutWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCut();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCopy002
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnCopy002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) { isEventCalled = true; };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::NONE);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: HandleOnCopy003
 * @tc.desc: test InsertValueByPaste
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, HandleOnCopy003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto pipeline = MockPipelineContext::GetCurrent();
    auto clipboard = ClipboardProxy::GetInstance()->GetClipboard(pipeline->GetTaskExecutor());
    richEditorPattern->clipboard_ = clipboard;
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isEventCalled = false;
    auto onCopyWithEvent = [&isEventCalled](NG::TextCommonEvent& event) {
        isEventCalled = true;
        event.SetPreventDefault(true);
    };
    richEditorModel.SetOnCopy(std::move(onCopyWithEvent));

    /**
     * @tc.steps: step2. call the callback function
     * @tc.expected: when PreventDefault is true, UpdateType_ and isEventCalled is valid
     */
    richEditorPattern->copyOption_ = CopyOptions::InApp;
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 1;
    richEditorPattern->caretUpdateType_ = CaretUpdateType::PRESSED;
    richEditorPattern->HandleOnCopy();
    EXPECT_EQ(richEditorPattern->caretUpdateType_, CaretUpdateType::PRESSED);
    EXPECT_EQ(isEventCalled, true);
}

/**
 * @tc.name: ChangeTextCallbackTest001
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return false;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with InsertValue When callback return false
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, false);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest002
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with AddTextSpan of TextStyle
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    TextStyle style;
    textOptions.offset = 1;
    textOptions.value = INIT_VALUE_2;
    textOptions.style = style;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest003
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with DeleteSpans
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    RangeOptions delOptions;
    delOptions.start = 0;
    delOptions.end = 2;
    richEditorPattern->DeleteSpans(delOptions);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 1);
    EXPECT_EQ(replacedCount, 0);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest004
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with InsertValue
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);

    /**
     * @tc.steps: step3. change text with multiLine
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->InsertValue("test\nvalue", true);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 2);
    EXPECT_EQ(afterCount, 2);
}

/**
 * @tc.name: ChangeTextCallbackTest005
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with ResetAfterPaste
     * @tc.expected: return value is valid
     */
    richEditorPattern->pasteStr_ = INIT_VALUE_1;
    richEditorPattern->ResetAfterPaste();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest006
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with HandleOnDragDropTextOperation
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->caretPosition_ = 4;
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 2;
    richEditorPattern->dragRange_.first = 0;
    richEditorPattern->dragRange_.second = 2;
    richEditorPattern->isDragSponsor_ = true;
    richEditorPattern->HandleOnDragDropTextOperation("he", true);
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 1);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest007
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with HandleOnUndoAction
     * @tc.expected: return value is valid
     */
    richEditorPattern->InsertValue(INIT_VALUE_1, true);
    isWillCalled = false;
    isDidCalled = false;
    richEditorPattern->HandleOnUndoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);

    /**
     * @tc.steps: step3. change text with HandleOnRedoAction
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 0);
    EXPECT_EQ(replacedCount, 1);
    EXPECT_EQ(afterCount, 1);
}

/**
 * @tc.name: ChangeTextCallbackTest008
 * @tc.desc: test for callback onWillchange/onWillDid
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init callback
     */
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool isWillCalled = false;
    int32_t originalCount = 0;
    int32_t replacedCount = 0;
    auto onWillChange = [&isWillCalled, &originalCount, &replacedCount](const RichEditorChangeValue& beforeResult) {
        isWillCalled = true;
        originalCount = beforeResult.GetRichEditorOriginalSpans().size();
        replacedCount = beforeResult.GetRichEditorReplacedSpans().size();
        return true;
    };
    richEditorModel.SetOnWillChange(std::move(onWillChange));
    bool isDidCalled = false;
    int32_t afterCount = 0;
    auto onDidChange = [&isDidCalled, &afterCount](const RichEditorChangeValue& afterResult) {
        isDidCalled = true;
        afterCount = afterResult.GetRichEditorReplacedSpans().size();
    };
    richEditorModel.SetOnDidChange(std::move(onDidChange));

    /**
     * @tc.steps: step2. change text with AddTextSpan & DeleteSpans & HandleOnUndoAction
     * @tc.expected: return value is valid
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_1;
    richEditorPattern->AddTextSpan(textOptions);
    RangeOptions delOptions;
    delOptions.start = 0;
    delOptions.end = 2;
    richEditorPattern->DeleteSpans(delOptions);
    richEditorPattern->HandleOnUndoAction();

    /**
     * @tc.steps: step4. change text with HandleOnRedoAction
     * @tc.expected: return value is valid
     */
    isWillCalled = false;
    isDidCalled = false;
    originalCount = 0;
    replacedCount = 0;
    afterCount = 0;
    richEditorPattern->HandleOnRedoAction();
    EXPECT_EQ(isWillCalled, true);
    EXPECT_EQ(isDidCalled, true);
    EXPECT_EQ(originalCount, 1);
    EXPECT_EQ(replacedCount, 0);
    EXPECT_EQ(afterCount, 0);
}

/**
 * @tc.name: ChangeTextCallbackTest009
 * @tc.desc: test for callback onWillchange/onDidChange, add text span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest009, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    EXPECT_EQ(g_isOnWillChangeCalled, true);
    EXPECT_EQ(g_isOnDidChangeCalled, true);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 0);
    EXPECT_EQ(onDidRangeAfter.end, 6); // length of INIT_VALUE_1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest010
 * @tc.desc: test for callback onWillchange/onDidChange, add text span then insert value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest010, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1); // content = hello1
    richEditorPattern->textSelector_.Update(1, 5); // select h[ello]1
    richEditorPattern->InsertValue(INIT_VALUE_1, true);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 1);
    EXPECT_EQ(onWillRangeBefore.end, 5);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.value_, "hhello11");
    EXPECT_EQ(spanResult.fontSize_, TEXT_STYLE_1.fontSize_.ConvertToPx());
    EXPECT_EQ(spanResult.offsetInSpan_, 1);
    EXPECT_EQ(spanResult.eraseLength_, 6);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 1);
    EXPECT_EQ(onDidRangeAfter.end, 7); // h[ello]1 -> h[hello1]1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest011
 * @tc.desc: test for callback onWillchange/onDidChange, add multi text span then insert value
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest011, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    richEditorPattern->AddTextSpan(TEXT_SPAN_OPTIONS_1);
    // content = hello1hello1hello1

    richEditorPattern->textSelector_.Update(1, 17); // select h[ello1hello1hello]1
    richEditorPattern->InsertValue(INIT_VALUE_1, true);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 1);
    EXPECT_EQ(onWillRangeBefore.end, 17);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 1);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 0);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.value_, "hhello1");
    EXPECT_EQ(spanResult.fontSize_, TEXT_STYLE_1.fontSize_.ConvertToPx());
    EXPECT_EQ(spanResult.offsetInSpan_, 1);
    EXPECT_EQ(spanResult.eraseLength_, 6);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 1);
    EXPECT_EQ(onDidRangeAfter.end, 7); // h[ello1hello1hello]1 -> h[hello1]1
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: ChangeTextCallbackTest012
 * @tc.desc: test for callback onWillchange/onDidChange, add image span
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, ChangeTextCallbackTest012, TestSize.Level1)
{
    RichEditorModelNG richEditorModel;
    richEditorModel.Create();
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(host, nullptr);
    auto richEditorPattern = host->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    InitContentChangeCallback(richEditorModel);

    richEditorPattern->AddImageSpan(IMAGE_SPAN_OPTIONS_1);

    // check onWill rangeBefore
    EXPECT_EQ(onWillRangeBefore.start, 0);
    EXPECT_EQ(onWillRangeBefore.end, 0);

    // check onWill span info
    ASSERT_EQ(onWillReplacedSpans.size(), 0);
    ASSERT_EQ(onWillReplacedImageSpans.size(), 1);
    ASSERT_EQ(onWillReplacedSymbolSpans.size(), 0);

    auto& spanResult = onWillReplacedImageSpans[0];
    EXPECT_EQ(spanResult.spanIndex_, 0);
    EXPECT_EQ(spanResult.offsetInSpan_, 0);
    EXPECT_EQ(spanResult.eraseLength_, 1);
    EXPECT_EQ(spanResult.width_, 200);
    EXPECT_EQ(spanResult.height_, 100);
    EXPECT_EQ(spanResult.verticalAlign_, VerticalAlign::CENTER);
    EXPECT_EQ(spanResult.objectFit_, ImageFit::COVER);

    // check onDid rangeBefore
    EXPECT_EQ(onDidRangeBefore, onWillRangeBefore);

    // check onDid rangeAfter
    EXPECT_EQ(onDidRangeAfter.start, 0);
    EXPECT_EQ(onDidRangeAfter.end, 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: SingleHandle001
 * @tc.desc: test show single handle with empty text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SingleHandle001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    richEditorPattern->caretPosition_ = -1;
    /**
     * @tc.steps: step1. first click does not show single handle
     */
    GestureEvent info;
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step2. repeat click caret position show single handle
     */
    info.localLocation_ = Offset(0, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 50);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. double click or long press show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
}

/**
 * @tc.name: SingleHandle002
 * @tc.desc: test show single handle with text
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SingleHandle002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. first click does not show single handle
     */
    richEditorPattern->caretPosition_ = -1;
    GestureEvent info;
    info.localLocation_ = Offset(0, 5);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step3. repeat click caret position show single handle
     */
    richEditorPattern->HandleClickEvent(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step4. repeat click away from caret position does not show single handle
     */
    richEditorPattern->selectOverlay_->SetIsSingleHandle(false);
    info.localLocation_ = Offset(50, 0);
    richEditorPattern->HandleClickEvent(info);
    EXPECT_FALSE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step5. double click or long press the end of text show single handle
     */
    richEditorPattern->HandleDoubleClickOrLongPress(info);
    EXPECT_TRUE(richEditorPattern->selectOverlay_->IsSingleHandle());
    /**
     * @tc.steps: step6. move single handle
     */
    auto handleOffset = OffsetF(0, 5);
    richEditorPattern->selectOverlay_->UpdateSelectorOnHandleMove(handleOffset, false);
    EXPECT_EQ(richEditorPattern->caretPosition_, 0);
}

/**
 * @tc.name: SingleHandle003
 * @tc.desc: test move caret by touch event
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SingleHandle003, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    AddSpan(INIT_VALUE_1);
    TestParagraphItem paragraphItem = { .start = 0, .end = 6,
        .indexOffsetMap = { { 0, Offset(0, 0) }, { 6, Offset(50, 0) } } };
    AddParagraph(paragraphItem);
    /**
     * @tc.steps: step2. request foucus and show caret
     */
    RequestFocus();
    richEditorPattern->caretPosition_ = 0;
    richEditorPattern->StartTwinkling();
    /**
     * @tc.steps: step3. touch down caret position
     */
    auto touchOffset = Offset(0, 0);
    richEditorPattern->HandleTouchDown(touchOffset);
    EXPECT_TRUE(richEditorPattern->isTouchCaret_);
    /**
     * @tc.steps: step4. move caret position by touch move
     */
    touchOffset = Offset(50, 0);
    richEditorPattern->HandleTouchMove(touchOffset);
    EXPECT_EQ(richEditorPattern->caretPosition_, 6);
}

/**
 * @tc.name: IsSelectAreaVisible001
 * @tc.desc: test selectArea inVisible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, IsSelectAreaVisible001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { 0.0, 0.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { 0.0, 0.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_FALSE(res);
}

/**
 * @tc.name: IsSelectAreaVisible002
 * @tc.desc: test selectArea Visible
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, IsSelectAreaVisible002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. add text and paragraph
     */
    TestParagraphRect paragraphRect = { .start = 0, .end = 6, .rects = { { -400.0, -400.0, 200.0, 200.0 } } };
    TestParagraphItem paragraphItem = { .start = 0, .end = 6, .testParagraphRects = { paragraphRect } };
    AddParagraph(paragraphItem);
    richEditorPattern->textSelector_.baseOffset = 0;
    richEditorPattern->textSelector_.destinationOffset = 6;
    richEditorPattern->contentRect_ = { -500.0, -500.0, 500.0, 500.0 };
    /**
     * @tc.steps: step2. test IsSelectAreaVisible
     */
    auto res = richEditorPattern->IsSelectAreaVisible();
    EXPECT_TRUE(res);
}

/**
 * @tc.name: SetPreviewText001
 * @tc.desc: test setPreviewText and decoration available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetPreviewText001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2. test previewText content
     */
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, PREVIEW_TEXT_VALUE1);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE1).length());
    EXPECT_EQ(previewTextRecord.endOffset, previewTextRecord.startOffset + length);
    /**
     * @tc.steps: step3. set previewTextDecoration
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    EXPECT_FALSE(geometryNode == nullptr);
    RefPtr<RenderContext> renderContext = RenderContext::Create();
    auto paintProperty = richEditorPattern->CreatePaintProperty();
    auto paintWrapper = AceType::MakeRefPtr<PaintWrapper>(renderContext, geometryNode, paintProperty);
    auto paintMethod = AceType::DynamicCast<RichEditorPaintMethod>(richEditorPattern->CreateNodePaintMethod());
    paintMethod->SetPreviewTextDecoration(AceType::RawPtr(paintWrapper));
    auto overlayMod =
        AceType::DynamicCast<RichEditorOverlayModifier>(paintMethod->GetOverlayModifier(AceType::RawPtr(paintWrapper)));
    ASSERT_NE(overlayMod, nullptr);
    /**
     * @tc.steps: step4. test previewTextDecoration
     */
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    DrawingContext context { rsCanvas, CONTEXT_WIDTH_VALUE, CONTEXT_HEIGHT_VALUE };
    overlayMod->PaintPreviewTextDecoration(context);
    EXPECT_EQ(overlayMod->showPreviewTextDecoration_->Get(), true);
}

/**
 * @tc.name: SetPreviewText002
 * @tc.desc: test setPreviewText init, update, and delete available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, SetPreviewText002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2. update previewText
     */
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE2, previewRange);
    /**
     * @tc.steps: step3. test previewText content
     */
    auto& previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, PREVIEW_TEXT_VALUE2);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    auto length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE2).length());
    EXPECT_EQ(previewTextRecord.endOffset, previewTextRecord.startOffset + length);
    /**
     * @tc.steps: step4. delete content  previewText
     */
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE3, previewRange);
    auto previewContent2 = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent2, PREVIEW_TEXT_VALUE3);
    EXPECT_EQ(previewTextRecord.startOffset, 0);
    length = static_cast<int32_t>(StringUtils::ToWstring(PREVIEW_TEXT_VALUE3).length());
    EXPECT_EQ(richEditorPattern->previewTextRecord_.endOffset, previewTextRecord.startOffset + length);
}

/**
 * @tc.name: FinishTextPreview001
 * @tc.desc: test FinishTextPreview available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, FinishTextPreview001, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2.  FinishTextPreview
     */
    richEditorPattern->FinishTextPreview();
    /**
     * @tc.steps: step3. test previewText content
     */
    auto previewTextRecord = richEditorPattern->previewTextRecord_;
    auto previewContent = previewTextRecord.previewContent;
    EXPECT_EQ(previewContent, "");
    EXPECT_EQ(previewTextRecord.startOffset, -1);
    EXPECT_EQ(previewTextRecord.endOffset, -1);
}

/**
 * @tc.name: FinishTextPreview002
 * @tc.desc: test FinishTextPreview by insertValue available
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, FinishTextPreview002, TestSize.Level1)
{
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step1. set previewText
     */
    PreviewRange previewRange;
    previewRange.start = -1;
    previewRange.end = -1;
    richEditorPattern->SetPreviewText(PREVIEW_TEXT_VALUE1, previewRange);
    /**
     * @tc.steps: step2.  test insertValue when previewTextInputting
     */
    richEditorPattern->InsertValue(PREVIEW_TEXT_VALUE1, true);
    EXPECT_EQ(richEditorPattern->spans_.size(), 1);
    auto it = richEditorPattern->spans_.begin();
    EXPECT_EQ((*it)->content, PREVIEW_TEXT_VALUE1);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts001 about cursor move
 * @tc.desc: test the cursor move line start
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::Left);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 19);
    richEditorPattern->CursorMove(CaretMoveIntent::LeftWord);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 13);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::RightWord);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 24);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::Home);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::End);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->CursorMove(CaretMoveIntent::LineBegin);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts002 about cursor move
 * @tc.desc: test the cursor move line end and down
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);

    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    AddSpan(INIT_VALUE_1);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    TestParagraphItem testParagraphItem = {
        .start = 0, .end = 6, .indexOffsetMap = { { 0, Offset(0, 5) }, { 6, Offset(50, 0) } }
    };
    richEditorPattern->paragraphs_.AddParagraph({ .paragraph = paragraph, .start = 0, .end = 6 });
    CaretMetricsF metricsDown;
    CaretMetricsF metricsUp;
    for (const auto& [index, offset] : testParagraphItem.indexOffsetMap) {
        metricsDown.offset.SetX(offset.GetX());
        metricsDown.offset.SetY(offset.GetY());
        metricsUp.offset.SetX(offset.GetX());
        metricsUp.offset.SetY(offset.GetY());
        EXPECT_CALL(*paragraph, GetGlyphIndexByCoordinate(_, _)).WillRepeatedly(Return(6));
        EXPECT_CALL(*paragraph, GetMaxWidth).WillRepeatedly(Return(150));
        EXPECT_CALL(*paragraph, GetHeight).WillRepeatedly(Return(50));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretDownstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsDown), Return(true)));
        EXPECT_CALL(*paragraph, ComputeOffsetForCaretUpstream(index, _, _))
            .WillRepeatedly(DoAll(SetArgReferee<1>(metricsUp), Return(true)));
    }
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->CursorMove(CaretMoveIntent::LineEnd);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->HandleSelect(CaretMoveIntent::LineEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
    richEditorPattern->SetCaretPosition(0);
    richEditorPattern->HandleSelect(CaretMoveIntent::Down);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 6);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts101 about Handle select
 * @tc.desc: test the select move position
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts101, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    richEditorPattern->paragraphs_.minParagraphFontSize = 19.0;
    EXPECT_EQ(richEditorPattern->paragraphs_.minParagraphFontSize.value(), 19.0);
    /**
     * @tc.steps: step2. add text span
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::Left);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 19);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::Right);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 21);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::LeftWord);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 19);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::RightWord);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 21);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::ParagraghEnd);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), textOptions.value.length());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleSelect(CaretMoveIntent::LineBegin);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts101 about Handle select
 * @tc.desc: test the select move position, up
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts102, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    auto layoutAlgorithm = AceType::DynamicCast<RichEditorLayoutAlgorithm>(richEditorPattern->CreateLayoutAlgorithm());
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    style.SetTextColor(TEXT_COLOR_VALUE);
    style.SetFontSize(FONT_SIZE_VALUE);
    style.SetFontStyle(ITALIC_FONT_STYLE_VALUE);
    style.SetFontWeight(FONT_WEIGHT_VALUE);
    style.SetFontFamilies(FONT_FAMILY_VALUE);
    style.SetTextDecoration(TEXT_DECORATION_VALUE);
    style.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    EXPECT_EQ(richEditorPattern->caretPosition_, 20);
    richEditorPattern->paragraphs_.minParagraphFontSize = style.GetFontSize().ConvertToPx();
    richEditorPattern->HandleSelect(CaretMoveIntent::Up);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 0);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts201 about Handle delete comb
 * @tc.desc: test the delete comb
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts201, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->HandleOnDeleteComb(true);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 20);
    richEditorPattern->HandleOnDeleteComb(false);
    EXPECT_EQ(richEditorPattern->GetCaretPosition(), 20);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts202 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts202, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextStart(), 4);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_B);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateFontWeight, Ace::FontWeight::BOLD);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts203 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts203, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    EXPECT_EQ(richEditorPattern->textSelector_.GetTextEnd(), 20);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_I);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateItalicFontStyle, OHOS::Ace::FontStyle::ITALIC);
}

/**
 * @tc.name: RichEditorKeyBoardShortCuts204 about Handle Select FontStyle
 * @tc.desc: test the text font style
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, RichEditorKeyBoardShortCuts204, TestSize.Level1)
{
    /**
     * @tc.steps: step1. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step2. get richEditor controller
     */
    auto richEditorController = richEditorPattern->GetRichEditorController();
    ASSERT_NE(richEditorController, nullptr);
    /**
     * @tc.steps: step2. add text span
     */
    TextStyle style;
    TextSpanOptions textOptions;
    textOptions.value = INIT_VALUE_3;
    textOptions.style = style;
    richEditorController->AddTextSpan(textOptions);
    EXPECT_EQ(textOptions.value.length(), richEditorPattern->GetTextContentLength());
    richEditorPattern->SetCaretPosition(20);
    richEditorPattern->textSelector_.Update(4, 20);
    richEditorPattern->HandleSelectFontStyle(KeyCode::KEY_U);
    EXPECT_EQ(richEditorPattern->GetUpdateSpanStyle().updateTextDecoration, TextDecoration::UNDERLINE);
}

/**
 * @tc.name: onDraw001
 * @tc.desc: Verify the onDraw Magnifier.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, onDraw001, TestSize.Level1)
{
    Offset localOffset(0, 0);
    SymbolSpanOptions symbolSpanOptions;
    symbolSpanOptions.symbolId = SYMBOL_ID;

    //Verify the selected single line text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify the selected multi line text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_3, symbolSpanOptions, localOffset, true);

    //Verify the selected image magnifying glass
    OnDrawVerify(SelectSpanType::TYPEIMAGE, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify the selected symbol magnifying glass
    OnDrawVerify(SelectSpanType::TYPESYMBOLSPAN, INIT_VALUE_1, symbolSpanOptions, localOffset, true);

    //Verify insertion status with a regular text magnifying glass
    OnDrawVerify(SelectSpanType::TYPESPAN, INIT_VALUE_1, symbolSpanOptions, localOffset);

    //Verify the insertion status of the image magnifying glass
    OnDrawVerify(SelectSpanType::TYPEIMAGE, INIT_VALUE_1, symbolSpanOptions, localOffset);

    //Verify the insertion state symbol magnifying glass
    OnDrawVerify(SelectSpanType::TYPESYMBOLSPAN, INIT_VALUE_1, symbolSpanOptions, localOffset);
}

/**
 * @tc.name: StyledString001
 * @tc.desc: Test the styledString with image.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, StyledString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with image
     */
    ImageSpanSize size { .width = 50.0_vp, .height = 50.0_vp };
    BorderRadiusProperty borderRadius;
    borderRadius.SetRadius(2.0_vp);
    MarginProperty margins;
    margins.SetEdges(CalcLength(10.0));
    PaddingProperty paddings;
    paddings.SetEdges(CalcLength(5.0));
    ImageSpanAttribute attr { .size = size,
        .paddingProp = paddings,
        .marginProp = margins,
        .borderRadius = borderRadius,
        .objectFit = ImageFit::COVER,
        .verticalAlign = VerticalAlign::BOTTOM };
    ImageSpanOptions imageOption { .image = "src/icon-1.png", .imageAttribute = attr };
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    /**
     * @tc.steps: step2. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step3. set styledString
     */
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(static_cast<int32_t>(richEditorNode_->GetChildren().size()), 1);
    auto child = richEditorPattern->GetChildByIndex(0);
    auto imageNode = AceType::DynamicCast<ImageSpanNode>(child);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->calcLayoutConstraint_->selfIdealSize, size.GetSize());
    EXPECT_EQ(imageLayoutProperty->GetVerticalAlignValue(), VerticalAlign::BOTTOM);
    EXPECT_EQ(imageLayoutProperty->GetImageFitValue(), ImageFit::COVER);
    auto&& padding = imageLayoutProperty->GetPaddingProperty();
    ASSERT_NE(padding, nullptr);
    EXPECT_EQ(padding->ToString(), paddings.ToString());
    auto imageRenderCtx = imageNode->GetRenderContext();
    ASSERT_NE(imageRenderCtx, nullptr);
    EXPECT_EQ(imageRenderCtx->GetBorderRadius(), borderRadius);
}

/**
 * @tc.name: StyledString002
 * @tc.desc: Test the styledString with image and text.
 * @tc.type: FUNC
 */
HWTEST_F(RichEditorTestNg, StyledString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create styledString with image and text
     */
    ImageSpanOptions imageOption;
    auto mutableStr = AceType::MakeRefPtr<MutableSpanString>(imageOption);
    mutableStr->InsertString(0, "text");
    /**
     * @tc.steps: step2. get richEditor pattern
     */
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    /**
     * @tc.steps: step3. set styledString
     */
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 1);
    EXPECT_EQ(richEditorPattern->spans_.size(), 2);
    /**
     * @tc.steps: step5. insert other image
     */
    auto imageSpan = AceType::MakeRefPtr<SpanString>(imageOption);
    mutableStr->AppendSpanString(imageSpan);
    richEditorPattern->SetStyledString(mutableStr);
    EXPECT_EQ(richEditorNode_->GetChildren().size(), 2);
    EXPECT_EQ(richEditorPattern->spans_.size(), 3);
}
} // namespace OHOS::Ace::NG
