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

#include "gtest/gtest.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "text_base.h"
#include "ui/base/geometry/dimension.h"

#include "core/components/common/layout/constants.h"
#include "core/components/text_overlay/text_overlay_theme.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_v2/inspector/inspector_constants.h"


namespace OHOS::Ace::NG {

namespace {
int32_t callBack1 = 0;
int32_t callBack2 = 0;
int32_t callBack3 = 0;
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
constexpr uint32_t DEFAULT_NODE_ID = 0;
constexpr uint32_t UKNOWN_VALUE = 0;
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_COLOR = 1;
constexpr uint32_t RENDERINGSTRATEGY_MULTIPLE_OPACITY = 2;
constexpr uint32_t MAX_LINES_VALUE0 = 3;
constexpr uint32_t MAX_LINES_VALUE1 = 4;
constexpr uint32_t MAX_LINES_VALUE2 = 7;
constexpr uint32_t MAX_LINES_VALUE3 = 10;
constexpr uint32_t MAX_LINES_VALUE4 = 5;
void ConstructGestureStyle(GestureStyle& gestureInfo)
{
    auto onClick = [](const BaseEventInfo* info) {};
    auto tmpClickFunc = [func = std::move(onClick)](GestureEvent& info) { func(&info); };
    gestureInfo.onClick = std::move(tmpClickFunc);

    auto onLongPress = [](const BaseEventInfo* info) {};
    auto tmpLongPressFunc = [func = std::move(onLongPress)](GestureEvent& info) { func(&info); };
    gestureInfo.onLongPress = std::move(tmpLongPressFunc);
}
} // namespace

class TextTestNgOne : public TextBases {
public:
};

/**
 * @tc.name: TextSelectOverlayTestGetSelectArea002
 * @tc.desc: Verify GetSelectArea
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextSelectOverlayTestGetSelectArea002, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    TextSelectOverlay textSelectOverlay(textBase);

    ASSERT_EQ(textSelectOverlay.GetSelectArea(), RectF());
}

/**
 * @tc.name: TextSelectOverlayTestGetSelectAreaFromHandle001
 * @tc.desc: Verify GetSelectAreaFromHandle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextSelectOverlayTestGetSelectAreaFromHandle001, TestSize.Level1)
{
    /**
     * @tc.steps: set theme, used in CheckAndAdjustHandle.
     */
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    pipeline->SetThemeManager(theme);
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextOverlayTheme>()));

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("Test", DEFAULT_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->geometryNode_ = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(frameNode->geometryNode_, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    RectF rect;
    textSelectOverlay->hasTransform_ = !textSelectOverlay->hasTransform_;
    textSelectOverlay->GetSelectAreaFromHandle(rect);
    textSelectOverlay->hasTransform_ = !textSelectOverlay->hasTransform_;
    ASSERT_EQ(rect.GetX(), 0.0);
    ASSERT_EQ(rect.GetY(), 0.0);
}

/**
 * @tc.name: TextSelectOverlayTestGetSelectAreaFromHandle002
 * @tc.desc: Verify GetSelectAreaFromHandle
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextSelectOverlayTestGetSelectAreaFromHandle002, TestSize.Level1)
{
    WeakPtr<TextBase> textBase = nullptr;
    TextSelectOverlay textSelectOverlay(textBase);

    RectF rect(RECT_X_VALUE, RECT_Y_VALUE, RECT_WIDTH_VALUE, RECT_HEIGHT_VALUE);

    textSelectOverlay.OnHandleMove(rect, false);
    textSelectOverlay.GetSelectAreaFromHandle(rect);
    ASSERT_EQ(rect.GetX(), RECT_X_VALUE);
    ASSERT_EQ(rect.GetY(), RECT_Y_VALUE);
}

/**
 * @tc.name: TextSelectOverlayTestOnUpdateMenuInfo001
 * @tc.desc: Verify OnUpdateMenuInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextSelectOverlayTestOnUpdateMenuInfo001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textSelectOverlay = pattern->selectOverlay_;
    ASSERT_NE(textSelectOverlay, nullptr);

    SelectMenuInfo menuInfo;

    textSelectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_COPY_ALL_ITEM);
    ASSERT_EQ(menuInfo.showCut, false);

    textSelectOverlay->OnUpdateMenuInfo(menuInfo, DIRTY_FIRST_HANDLE);
    ASSERT_EQ(menuInfo.showCut, false);
}

/**
 * @tc.name: TextStylesTestGetFontFamilyInJson001
 * @tc.desc: Verify GetFontFamilyInJson
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextStylesTestGetFontFamilyInJson001, TestSize.Level1)
{
    std::optional<std::vector<std::string>> value;

    value = std::vector<std::string>{ "Arial", "Calibri" };

    ASSERT_EQ(GetFontFamilyInJson(value), "Arial,Calibri");
}

/**
 * @tc.name: TextStylesTestGetSymbolRenderingStrategyInJson001
 * @tc.desc: Verify GetSymbolRenderingStrategyInJson
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextStylesTestGetSymbolRenderingStrategyInJson001, TestSize.Level1)
{
    std::optional<uint32_t> value = RENDERINGSTRATEGY_MULTIPLE_COLOR;
    ASSERT_EQ(GetSymbolRenderingStrategyInJson(value), "SymbolRenderingStrategy.MULTIPLE_COLOR");

    value = RENDERINGSTRATEGY_MULTIPLE_OPACITY;
    ASSERT_EQ(GetSymbolRenderingStrategyInJson(value), "SymbolRenderingStrategy.MULTIPLE_OPACITY");

    value = UKNOWN_VALUE;
    ASSERT_EQ(GetSymbolRenderingStrategyInJson(value), "SymbolRenderingStrategy.SINGLE");
}

/**
 * @tc.name: TextStylesTestGetSymbolEffectStrategyInJson001
 * @tc.desc: Verify GetSymbolEffectStrategyInJson
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextStylesTestGetSymbolEffectStrategyInJson001, TestSize.Level1)
{
    std::optional<uint32_t> value = static_cast<uint32_t>(SymbolEffectType::SCALE);
    ASSERT_EQ(GetSymbolEffectStrategyInJson(value), "SymbolEffectStrategy.SCALE");

    value = static_cast<uint32_t>(SymbolEffectType::HIERARCHICAL);
    ASSERT_EQ(GetSymbolEffectStrategyInJson(value), "SymbolEffectStrategy.HIERARCHICAL");

    value = UKNOWN_VALUE;
    ASSERT_EQ(GetSymbolEffectStrategyInJson(value), "SymbolEffectStrategy.NONE");
}

/**
 * @tc.name: UpdateSelectOverlayOrCreate001
 * @tc.desc: Test TextPattern UpdateSelectOverlayOrCreate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, UpdateSelectOverlayOrCreate001, TestSize.Level1)
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
    /**
     * @tc.steps: step2. Construct data and call UpdateSelectOverlayOrCreate
     */
    SelectOverlayInfo selectOverlayInfo;
    selectOverlayInfo.singleLineHeight = NODE_ID;
    textPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_EQ(selectOverlayInfo.hitTestMode, HitTestMode::HTMDEFAULT);

    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectOverlayInfo, nullptr, false);
    textPattern->selectOverlayProxy_ = proxy;
    textPattern->UpdateSelectOverlayOrCreate(selectOverlayInfo, true);
    EXPECT_TRUE(textPattern->selectOverlayProxy_ && !textPattern->selectOverlayProxy_->IsClosed());
}

/**
 * @tc.name: SetTextSelectDetectEnable001
 * @tc.desc: Test SetTextSelectDetectEnable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, SetTextSelectDetectEnable001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textModelNG and frameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. call GetSelectDetectEnable.
     * @tc.expected: the default properties are default values(true).
     */
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(pattern);
    ASSERT_EQ(pattern->GetSelectDetectEnable(), true);

    /**
     * @tc.steps: step3. create selectDetectEnable and call SetSelectDetectEnable.
     * @tc.expected: the properties are successfully set to default values.
     */
    bool selectDetectEnable = false;
    textModelNG.SetSelectDetectEnable(selectDetectEnable);
    ASSERT_EQ(pattern->GetSelectDetectEnable(), false);
}

/**
 * @tc.name: HandleOnSelectAll001
 * @tc.desc: Test TextPattern HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, HandleOnSelectAll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Construct data and call HandleOnSelectAll
     */
    textPattern->sourceType_ = SourceType::MOUSE;
    textPattern->HandleOnSelectAll();
    EXPECT_TRUE(textPattern->IsUsingMouse());
}

/**
 * @tc.name: CreateImageSourceInfo001
 * @tc.desc: Test TextPattern HandleOnSelectAll
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, CreateImageSourceInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    /**
     * @tc.steps: step2. Construct data and call CreatImageSourceInfo
     */
    ImageSpanOptions textOptions;
    ParagraphUtil::CreateImageSourceInfo(textOptions);
    textOptions.image = "textImage";
    textOptions.bundleName = "textBundleName";
    textOptions.moduleName = "textModuleName";
    ParagraphUtil::CreateImageSourceInfo(textOptions);
    EXPECT_TRUE(textOptions.image.has_value());
    EXPECT_TRUE(textOptions.bundleName.has_value());
    EXPECT_TRUE(textOptions.moduleName.has_value());
}

/**
 * @tc.name: Create001
 * @tc.desc: Test create with spanstring.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, Create001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
     /**
     * @tc.steps: step1. Create spanBases
     */
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567891");
    /**
     * @tc.steps: step2. call spanBases
     */
    textModelNG.Create(spanStringWithSpans);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    EXPECT_NE(textPattern->GetSpanStringMode(), true);
}

/**
 * @tc.name: SetTextSelectableMode001
 * @tc.desc: Test SetTextSelectableMode by frameNode..
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, SetTextSelectableMode001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    auto retFont = textModelNG.GetFont(frameNode);
    textModelNG.SetFontSize(ADAPT_ZERO_FONT_SIZE_VALUE);
    EXPECT_EQ(textModelNG.GetFontSize(frameNode), ADAPT_ZERO_FONT_SIZE_VALUE);

    textModelNG.SetTextSelectableMode(frameNode, TextSelectableMode::SELECTABLE_UNFOCUSABLE);
    textModelNG.SetTextSelectableMode(TextSelectableMode::SELECTABLE_UNFOCUSABLE);
    ASSERT_EQ(textModelNG.GetTextSelectableMode(frameNode), TextSelectableMode::SELECTABLE_UNFOCUSABLE);

    textModelNG.SetEllipsisMode(frameNode, EllipsisMode::HEAD);
    textModelNG.SetEllipsisMode(EllipsisMode::HEAD);
    ASSERT_EQ(textModelNG.GetEllipsisMode(frameNode), EllipsisMode::HEAD);
}

/**
 * @tc.name: InitSpanStringController001
 * @tc.desc: Test InitSpanStringController.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, InitSpanStringController001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567893421");

    textModelNG.InitSpanStringController(frameNode, spanStringWithSpans);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    EXPECT_EQ(textPattern->GetSpanStringMode(), true);
}

/**
 * @tc.name: InitTextController001
 * @tc.desc: Test InitTextController.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, InitTextController001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    auto ret = textModelNG.InitTextController(frameNode);
    EXPECT_NE(ret, nullptr);
}

/**
 * @tc.name: SetTextDetectEnable001
 * @tc.desc: Test SetTextDetectEnable.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, SetTextDetectEnable001, TestSize.Level1)
{
    TextModelNG textModelNG;
    textModelNG.Create(CREATE_VALUE_W);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    EXPECT_EQ(textLayoutProperty->GetContentValue(), CREATE_VALUE_W);

    textModelNG.SetTextDetectEnable(frameNode, true);
    ASSERT_NE(textModelNG.GetTextDetectEnable(frameNode), false);

    auto ret = textModelNG.GetTextController();
    EXPECT_NE(ret, nullptr);

    textModelNG.SetClipEdge(true);
    EXPECT_NE(frameNode->renderContext_, nullptr);

    auto strContent = textModelNG.GetContent(frameNode);
    EXPECT_EQ(strContent, CREATE_VALUE_W);

    auto retLineHeight = textModelNG.GetLineHeight(frameNode);
    EXPECT_EQ(retLineHeight, 0.0f);

    auto retLineSpacing = textModelNG.GetLineSpacing(frameNode);
    EXPECT_EQ(retLineSpacing, 0.0f);

    auto retDecoration = textModelNG.GetDecoration(frameNode);
    EXPECT_EQ(retDecoration, TextDecoration::NONE);

    auto retTextDecorationColor = textModelNG.GetTextDecorationColor(frameNode);
    EXPECT_EQ(retTextDecorationColor, Color::BLACK);

    auto retTextDecorationStyle = textModelNG.GetTextDecorationStyle(frameNode);
    EXPECT_EQ(retTextDecorationStyle, TextDecorationStyle::SOLID);

    auto retTextCase = textModelNG.GetTextCase(frameNode);
    EXPECT_EQ(retTextCase, TextCase::NORMAL);

    auto retLetterSpacing = textModelNG.GetLetterSpacing(frameNode);
    EXPECT_EQ(retLetterSpacing, ADAPT_ZERO_FONT_SIZE_VALUE);

    auto retMaxLines = textModelNG.GetMaxLines(frameNode);
    EXPECT_NE(retMaxLines, 0.0f);

    auto retTextAlign = textModelNG.GetTextAlign(frameNode);
    EXPECT_EQ(retTextAlign, TextAlign::START);
}

/**
 * @tc.name: TextPattern001
 * @tc.desc: Test TextPattern GetGlyphPositionAtCoordinate
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern GetGlyphPositionAtCoordinate
     */
    auto [frameNode, pattern] = Init();
    auto positionWithAffinity = pattern->GetGlyphPositionAtCoordinate(1, 1);
    EXPECT_EQ(positionWithAffinity.position_, 0);
}

/**
 * @tc.name: TextPattern002
 * @tc.desc: Test TextPattern ConvertLocalOffsetToParagraphOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern ConvertLocalOffsetToParagraphOffset
     */
    auto [frameNode, pattern] = Init();
    Offset offset = Offset(1, 1);
    auto paragraphOffset = pattern->ConvertLocalOffsetToParagraphOffset(offset);
    EXPECT_EQ(paragraphOffset.GetX(), 1);
}

/**
 * @tc.name: TextPattern003
 * @tc.desc: Test TextPattern GetLineMetrics
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern GetLineMetrics
     */
    auto [frameNode, pattern] = Init();
    auto textLineMetrics = pattern->GetLineMetrics(1);
    EXPECT_EQ(textLineMetrics.lineNumber, 0);
}

/**
 * @tc.name: TextPattern004
 * @tc.desc: Test TextPattern DidExceedMaxLines
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern DidExceedMaxLines
     */
    auto [frameNode, pattern] = Init();
    auto didExceedMaxLines = pattern->DidExceedMaxLines();
    EXPECT_EQ(didExceedMaxLines, false);
}

/**
 * @tc.name: TextPattern005
 * @tc.desc: Test TextPattern GetTextContentRect
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern GetTextContentRect
     */
    auto [frameNode, pattern] = Init();
    auto textRect = pattern->GetTextContentRect(true);
    EXPECT_EQ(textRect.GetY(), 0);
}

/**
 * @tc.name: TextPattern006
 * @tc.desc: Test TextPattern SetExternalSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern SetExternalSpanItem
     */
    auto [frameNode, pattern] = Init();
    std::list<RefPtr<SpanItem>> spanItems;
    pattern->SetExternalSpanItem(spanItems);
    EXPECT_EQ(pattern->isSpanStringMode_, false);
}

/**
 * @tc.name: TextPattern007
 * @tc.desc: Test TextPattern ConvertGlobalToLocalOffset
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern ConvertGlobalToLocalOffset
     */
    auto [frameNode, pattern] = Init();
    Offset globalOffset = Offset(1, 1);
    auto localPoint = pattern->ConvertGlobalToLocalOffset(globalOffset);
    EXPECT_EQ(localPoint.GetY(), 1);
}

/**
 * @tc.name: TextPattern008
 * @tc.desc: Test TextPattern OnSensitiveStyleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern OnSensitiveStyleChange
     */
    auto [frameNode, pattern] = Init();
    pattern->OnSensitiveStyleChange(true);
    EXPECT_EQ(pattern->isSensitive_, 1);
}

/**
 * @tc.name: TextPattern009
 * @tc.desc: Test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern ProcessSpanString
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    pattern->ProcessSpanString();
    EXPECT_EQ(pattern->textForDisplay_.length(), 0);
}

/**
 * @tc.name: TextPattern010
 * @tc.desc: Test TextPattern CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern CreateImageSourceInfo
     */
    auto [frameNode, pattern] = Init();
    ImageSpanAttribute imageStyle;
    ImageSpanOptions options;
    options.imageAttribute = imageStyle;
    options.image = IMAGE_VALUE;
    options.bundleName = BUNDLE_NAME;
    options.moduleName = MODULE_NAME;
    options.offset = 1;
    auto imageSourceInfo = ParagraphUtil::CreateImageSourceInfo(options);
    EXPECT_EQ(imageSourceInfo.isFromReset_, 0);
}

/**
 * @tc.name: TextPattern011
 * @tc.desc: Test TextPattern CreateImageSourceInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern CreateImageSourceInfo
     */
    auto [frameNode, pattern] = Init();

    /**
     * @tc.steps: step2. Create spanBases and gestureInfo
     */
    std::vector<RefPtr<SpanBase>> spanBases;
    GestureStyle gestureInfo;
    ConstructGestureStyle(gestureInfo);
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 0, 3));
    spanBases.emplace_back(AceType::MakeRefPtr<GestureSpan>(gestureInfo, 8, 11));
    auto spanStringWithSpans = AceType::MakeRefPtr<SpanString>(u"01234567891");
    spanStringWithSpans->BindWithSpans(spanBases);
    auto spans = spanStringWithSpans->GetSpanItems();
    pattern->SetSpanItemChildren(spans);

    /**
     * @tc.steps: step3. test pattern MountImageNode
     */
    auto spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    spanItem->content = u" ";
    spanItem->placeholderIndex = 0;
    pattern->MountImageNode(spanItem);
    EXPECT_EQ(pattern->childNodes_.size(), 1);
}

/**
 * @tc.name: TextPattern015
 * @tc.desc: Test TextPattern CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. test pattern OnHandleAreaChanged
     */
    RectF handleRect = CONTENT_RECT;
    pattern->selectOverlay_->OnHandleMoveDone(handleRect, true);
    pattern->OnHandleAreaChanged();
    EXPECT_EQ(pattern->selectOverlay_->SelectOverlayIsOn(), false);
}

/**
 * @tc.name: TextPattern016
 * @tc.desc: Test TextPattern CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. test pattern HandleSurfaceChanged
     */
    int32_t newWidth = 1;
    int32_t newHeight = 1;
    int32_t prevWidth = 0;
    int32_t prevHeight = 0;
    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, WindowSizeChangeReason::DRAG);
    EXPECT_EQ(pattern->selectOverlay_->IsShowMouseMenu(), false);

    /**
     * @tc.steps: step3. set Width Height equal before adn after, test pattern HandleSurfaceChanged
     */
    newWidth = 1;
    newHeight = 1;
    prevWidth = 1;
    prevHeight = 1;
    pattern->HandleSurfaceChanged(newWidth, newHeight, prevWidth, prevHeight, WindowSizeChangeReason::DRAG);
    EXPECT_EQ(pattern->selectOverlay_->IsShowMouseMenu(), false);
}

/**
 * @tc.name: TextPattern017
 * @tc.desc: Test TextPattern CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. create SelectOverlayInfo
     */
    SelectOverlayInfo selectInfo;
    selectInfo.singleLineHeight = NODE_ID;
    auto root = AceType::MakeRefPtr<FrameNode>(ROOT_TAG, -1, AceType::MakeRefPtr<Pattern>(), true);
    auto selectOverlayManager = AceType::MakeRefPtr<SelectOverlayManager>(root);
    auto proxy = selectOverlayManager->CreateAndShowSelectOverlay(selectInfo, nullptr, false);
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

    /**
     * @tc.steps: step3. test pattern UpdateSelectOverlayOrCreate
     */
    pattern->UpdateSelectOverlayOrCreate(selectInfo, true);
    EXPECT_EQ(pattern->selectOverlay_->IsShowMouseMenu(), false);

    pattern->UpdateSelectOverlayOrCreate(selectInfo, false);
    EXPECT_EQ(pattern->selectOverlay_->IsShowMouseMenu(), false);
}

/**
 * @tc.name: TextPattern018
 * @tc.desc: Test TextPattern CopySelectionMenuParams
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    auto IsShowHandle = pattern->IsShowHandle();
    EXPECT_EQ(IsShowHandle, false);
}

/**
 * @tc.name: TextPattern019
 * @tc.desc: Test TextPattern OnFrameNodeChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern IsShowHandle
     */
    auto [frameNode, pattern] = Init();
    pattern->textSelector_.Update(0, TEXT_SIZE_INT);

    /**
     * @tc.steps: step2. show selectoverlay.
     */
    pattern->ShowSelectOverlay();
    EXPECT_TRUE(pattern->selectOverlay_->SelectOverlayIsOn());

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    frameNode->AddFrameNodeChangeInfoFlag(FRAME_NODE_CHANGE_START_SCROLL);
    frameNode->ProcessFrameNodeChangeFlag();
    EXPECT_EQ(pattern->selectOverlay_->handleLevelMode_, HandleLevelMode::EMBED);
}

/**
 * @tc.name: TextPattern020
 * @tc.desc: Test TextPattern AddImageToSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextPattern020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textNode and ImageSpanNode.
     */
    auto [frameNode, pattern] = Init();
    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });

    /**
     * @tc.steps: step2. AddImageToSpanItem.
     */
    pattern->AddImageToSpanItem(imageSpanNode);
    EXPECT_EQ(pattern->spans_.size(), 1);
    auto span1 = AceType::DynamicCast<ImageSpanItem>(pattern->spans_.back());
    ASSERT_NE(span1, nullptr);

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    EXPECT_EQ(pattern->spans_.back(), imageSpanNode->GetSpanItem());
}

/**
 * @tc.name: SetFontSize001
 * @tc.desc: Test TextContentModifier SetFontSize
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, SetFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextContentModifier.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetFontScale(TEXT_FONT_SCALE);

    /**
     * @tc.steps: step2. SetFontSize.
     */
    textContentModifier->SetFontSize(Dimension(DIMENSION, DimensionUnit::FP), TextStyle(), false);

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    EXPECT_EQ(textContentModifier->fontSize_.value(), Dimension(FONT_SIZE, DimensionUnit::PX));

    pipeline->SetFontScale(1.0f);
}

/**
 * @tc.name: TextContentModifierSetFontSize001
 * @tc.desc: Test TextContentModifier construct
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextContentModifierSetFontSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextContentModifier.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    pipeline->SetFontScale(TEXT_FONT_SCALE);

    /**
     * @tc.steps: step2. SetFontSize.
     */
    textContentModifier->SetFontSize(Dimension(DIMENSION, DimensionUnit::FP), TextStyle(), false);

    /**
     * @tc.steps: step3. mark framnode changed.
     */
    EXPECT_EQ(textContentModifier->fontSize_.value(), Dimension(25.0, DimensionUnit::PX));

    pipeline->SetFontScale(1.0f);
}

/**
 * @tc.name: ProcessSpanString001
 * @tc.desc: Test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, ProcessSpanString001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageSpanItem.
     * Set the image to be loaded synchronously
     */
    
    ImageSpanOptions options;
    options.image = "image";
    options.bundleName = "bundleName";
    options.moduleName = "moduleName";
    ImageSpanAttribute imageStyle;
    imageStyle.syncLoad = true;
    options.imageAttribute = imageStyle;
    auto spanString = AceType::MakeRefPtr<SpanString>(options);

    /**
     * @tc.steps: step2. create textNode and call setStyledString.
     */
    
    auto [frameNode, pattern] = Init();
    pattern->SetStyledString(spanString);
    EXPECT_EQ(pattern->spans_.size(), 1);

    /**
     * @tc.steps: step3. Check that the image is mounted to the text.
     */
    
    auto children = frameNode->GetChildren();
    auto node = children.front();
    auto imageNode = AceType::DynamicCast<FrameNode>(node);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. Check that the image is set to synchronous loading.
     */
    
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_TRUE(imagePattern->GetSyncLoad());
}

/**
 * @tc.name: ProcessSpanString002
 * @tc.desc: Test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, ProcessSpanString002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create imageSpanItem.
     */
    
    ImageSpanOptions options;
    options.image = "image";
    options.bundleName = "bundleName";
    options.moduleName = "moduleName";
    ImageSpanAttribute imageStyle;
    options.imageAttribute = imageStyle;
    auto spanString = AceType::MakeRefPtr<SpanString>(options);

    /**
     * @tc.steps: step2. create textNode and call setStyledString.
     */
    
    auto [frameNode, pattern] = Init();
    pattern->SetStyledString(spanString);
    EXPECT_EQ(pattern->spans_.size(), 1);

    /**
     * @tc.steps: step3. Check that the image is mounted to the text.
     */
    
    auto children = frameNode->GetChildren();
    auto node = children.front();
    auto imageNode = AceType::DynamicCast<FrameNode>(node);
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);

    /**
     * @tc.steps: step4. Check the default loading method of image.
     */
    
    auto imagePattern = imageNode->GetPattern<ImagePattern>();
    ASSERT_NE(imagePattern, nullptr);
    EXPECT_FALSE(imagePattern->GetSyncLoad());

    /**
     * @tc.steps: step4. Check that the image is not of the pixmap type.
     */
    
    auto info = imageLayoutProperty->GetImageSourceInfo();
    ASSERT_NE(info.has_value(), false);
    EXPECT_EQ(info->pixmap_, nullptr);

    EXPECT_EQ(info->bundleName_, "bundleName");
    EXPECT_EQ(info->moduleName_, "moduleName");
}

/**
 * @tc.name: ProcessSpanString003
 * @tc.desc: Test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, ProcessSpanString003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and test pattern ProcessSpanString
     */
    auto [frameNode, pattern] = Init();
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->aiDetectInitialized_ = false;
    pattern->dataDetectorAdapter_->textForAI_ = pattern->textForDisplay_;
    pattern->ProcessSpanString();
    EXPECT_EQ(pattern->textForDisplay_.length(), 0);
}

/**
 * @tc.name: UpdateParagraphBySpan002
 * @tc.desc: Test the maxlines of UpdateParagraphBySpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, UpdateParagraphBySpan002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text.
     */
    
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Use span to construct two paragraphs
     */
    
    std::vector<std::list<RefPtr<SpanItem>>> spans;
    std::list<RefPtr<SpanItem>> spanList1;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    span1->textLineStyle->propMaxLines = MAX_LINES_VALUE0;
    spanList1.emplace_back(span1);
    spans.emplace_back(spanList1);

    std::list<RefPtr<SpanItem>> spanList2;
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"span2";
    span2->textLineStyle->propMaxLines = MAX_LINES_VALUE0;
    spanList2.emplace_back(span2);
    spans.emplace_back(spanList2);

    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->spans_ = spans;
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 2);

    /**
     * @tc.steps: step3. Call UpdateParagraphBySpan.
     * Set the total maximum number of lines to be 4.
     */
    
    ParagraphStyle paraStyle;
    paraStyle.maxLines = MAX_LINES_VALUE1;
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(3));
    textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle);
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();


    /**
     * @tc.expected: There are two paragraphs to expect.
     */
    EXPECT_EQ(paragraphs.size(), 2);

    /**
     * @tc.expected: The maximum number of lines in the first segment is expected to be 3,
     * and the maximum function in the second segment is 1.
     */
    auto paragraphInfo = paragraphs.begin();
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE0);
    ++paragraphInfo;
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, 1);
}

/**
 * @tc.name: UpdateParagraphBySpan003
 * @tc.desc: Test the maxlines of UpdateParagraphBySpan
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, UpdateParagraphBySpan003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create text.
     */
    
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Use span to construct two paragraphs
     */
    
    std::vector<std::list<RefPtr<SpanItem>>> spans;
    std::list<RefPtr<SpanItem>> spanList1;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    span1->textLineStyle->propMaxLines = MAX_LINES_VALUE0;
    spanList1.emplace_back(span1);
    spans.emplace_back(spanList1);

    std::list<RefPtr<SpanItem>> spanList2;
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"span2";
    span2->textLineStyle->propMaxLines = MAX_LINES_VALUE0;
    spanList2.emplace_back(span2);
    spans.emplace_back(spanList2);

    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->spans_ = spans;
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 2);

    /**
     * @tc.steps: step3. Call UpdateParagraphBySpan.
     * Set the total maximum number of lines to be 7.
     */
    
    ParagraphStyle paraStyle;
    paraStyle.maxLines = MAX_LINES_VALUE2;
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(3));
    textLayoutAlgorithm->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle);
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();


    /**
     * @tc.expected: There are two paragraphs to expect.
     */
    EXPECT_EQ(paragraphs.size(), 2);

    /**
     * @tc.expected: The maximum number of lines in the first segment is expected to be 3,
     * and the maximum function in the second segment is 3.
     */
    auto paragraphInfo = paragraphs.begin();
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE0);
    ++paragraphInfo;
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE0);
}

/**
 * @tc.name: UpdateParagraphBySpan004
 * @tc.desc: Test the maxlines of UpdateParagraphBySpan with different maxLines settings for each span.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, UpdateParagraphBySpan004, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create text.
    */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
    * @tc.steps: step2. Use span to construct two paragraphs with different maxLines settings.
    */

    std::vector<std::list<RefPtr<SpanItem>>> spans;
    std::list<RefPtr<SpanItem>> spanList1;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    span1->textLineStyle->propMaxLines = MAX_LINES_VALUE4; // Set maxLines to 5 for the first span
    spanList1.emplace_back(span1);
    spans.emplace_back(spanList1);

    std::list<RefPtr<SpanItem>> spanList2;
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"span2";
    span2->textLineStyle->propMaxLines = MAX_LINES_VALUE2; // Set maxLines to 7 for the second span
    spanList2.emplace_back(span2);
    spans.emplace_back(spanList2);

    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->spans_ = spans;
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 2);

    /**
    * @tc.steps: step3. Call UpdateParagraphBySpan.
    * Set the total maximum number of lines to be 10.
    */

    ParagraphStyle paraStyle;
    paraStyle.maxLines = MAX_LINES_VALUE3; // Set total maxLines to 10
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(MAX_LINES_VALUE4)); // Mock line count to 5
    textLayoutAlgorithm->UpdateParagraphBySpan(AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle);
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();

    /**
    * @tc.expected: There are two paragraphs to expect.
    */
    EXPECT_EQ(paragraphs.size(), 2);

    /**
    * @tc.expected: The maximum number of lines in the first segment is expected to be 5,
    * and the maximum number of lines in the second segment is expected to be 5.
    */
    auto paragraphInfo = paragraphs.begin();
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE4);
    ++paragraphInfo;
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE4);
}

/**
* @tc.name: UpdateParagraphBySpan006
* @tc.desc: Test the maxlines of UpdateParagraphBySpan with different maxLines settings for each span.
* @tc.type: FUNC
*/
HWTEST_F(TextTestNgOne, UpdateParagraphBySpan006, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create text.
    */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
    * @tc.steps: step2. Use span to construct two paragraphs with different maxLines settings.
    */

    std::vector<std::list<RefPtr<SpanItem>>> spans;
    std::list<RefPtr<SpanItem>> spanList1;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    span1->textLineStyle->propMaxLines = MAX_LINES_VALUE4; // Set maxLines to 5 for the first span
    spanList1.emplace_back(span1);
    spans.emplace_back(spanList1);

    std::list<RefPtr<SpanItem>> spanList2;
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"span2";
    span2->textLineStyle->propMaxLines = MAX_LINES_VALUE0; // Set maxLines to 3 for the second span
    spanList2.emplace_back(span2);
    spans.emplace_back(spanList2);

    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->spans_ = spans;
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 2);

    /**
    * @tc.steps: step3. Call UpdateParagraphBySpan.
    * Set the total maximum number of lines to be 10.
    */

    ParagraphStyle paraStyle;
    paraStyle.maxLines = UINT32_MAX; // Set total maxLines to UINT32_MAX
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(MAX_LINES_VALUE4)); // Mock line count to 5
    textLayoutAlgorithm->UpdateParagraphBySpan(AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle);
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();

    /**
    * @tc.expected: There are two paragraphs to expect.
    */
    EXPECT_EQ(paragraphs.size(), 2);

    /**
    * @tc.expected: The maximum number of lines in the first segment is expected to be 5,
    * and the maximum number of lines in the second segment is expected to be 3.
    */
    auto paragraphInfo = paragraphs.begin();
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE4);
    ++paragraphInfo;
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE0);
}

/**
* @tc.name: UpdateParagraphBySpan004
* @tc.desc: Test the maxlines of UpdateParagraphBySpan with different maxLines settings for each span.
* @tc.type: FUNC
*/
HWTEST_F(TextTestNgOne, UpdateParagraphBySpan005, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create text.
    */

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textFrameNode, geometryNode, textFrameNode->GetLayoutProperty());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
    * @tc.steps: step2. Use span to construct two paragraphs with different maxLines settings.
    */

    std::vector<std::list<RefPtr<SpanItem>>> spans;
    std::list<RefPtr<SpanItem>> spanList1;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"span1";
    spanList1.emplace_back(span1);
    spans.emplace_back(spanList1);

    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(textPattern->CreateLayoutAlgorithm());
    textLayoutAlgorithm->spans_ = spans;
    EXPECT_EQ(textLayoutAlgorithm->spans_.size(), 1);

    /**
    * @tc.steps: step3. Call UpdateParagraphBySpan.
    * Set the total maximum number of lines to be 10.
    */

    ParagraphStyle paraStyle;
    paraStyle.maxLines = MAX_LINES_VALUE2; // Set total maxLines to UINT32_MAX
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, GetLineCount).WillRepeatedly(Return(MAX_LINES_VALUE4)); // Mock line count to 5
    textLayoutAlgorithm->UpdateParagraphBySpan(AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle);
    auto paragraphs = textLayoutAlgorithm->paragraphManager_->GetParagraphs();

    /**
    * @tc.expected: There are two paragraphs to expect.
    */
    EXPECT_EQ(paragraphs.size(), 1);

    /**
    * @tc.expected: The maximum number of lines in the first segment is expected to be 5,
    * and the maximum number of lines in the second segment is expected to be 3.
    */
    auto paragraphInfo = paragraphs.begin();
    EXPECT_EQ((*paragraphInfo).paragraphStyle.maxLines, MAX_LINES_VALUE2);
}

/**
 * @tc.name: TextContentModifierSetSymbolColor001
 * @tc.desc: Test SetSymbolColor with existing symbolColors (size=2) and input value size=1
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextContentModifierSetSymbolColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TextContentModifier and initialize symbolColors_ with size=2.
     */
    RefPtr<TextContentModifier> textContentModifier =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    ASSERT_NE(textContentModifier, nullptr);
    std::vector<Color> initialColors = { Color::BLUE };
    TextStyle style;
    style.SetSymbolColorList(initialColors);
    textContentModifier->SetDefaultSymbolColor(style);

    // Initialize symbolColors_ with 2 colors
    std::vector<Color> newColors1 = { Color::RED, Color::BLUE };
    textContentModifier->SetSymbolColor(newColors1, false);
    auto resultColors = textContentModifier->symbolColors_; // Assume there's a getter method
    ASSERT_NE(resultColors, std::nullopt);
    EXPECT_EQ(resultColors->size(), 2);

    /**
     * @tc.steps: step2. Call SetSymbolColor with value size=1 (smaller than current symbolColors_)
     */
    std::vector<Color> newColors2 = { Color::GREEN };
    textContentModifier->SetSymbolColor(newColors2, false);

    /**
     * @tc.steps: step3. Verify symbolColors_ is correctly updated and truncated
     * @tc.expected: symbolColors_ should have size=1 with the new color
     */
    resultColors = textContentModifier->symbolColors_; // Assume there's a getter method
    ASSERT_NE(resultColors, std::nullopt);
    EXPECT_EQ(resultColors->size(), 1);
    EXPECT_EQ((*resultColors)[0], LinearColor(Color::GREEN));
}

/**
 * @tc.name: TextLayoutProperty01
 * @tc.desc: test text_pattern.h CreateLayoutProperty function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgOne, TextLayoutProperty01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    RefPtr<LayoutProperty> textLayoutProperty = textPattern->CreateLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
}
} // namespace OHOS::Ace::NG
