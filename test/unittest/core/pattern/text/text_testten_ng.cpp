/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "text_base.h"

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "core/components_ng/pattern/text/span/tlv_util.h"

#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_select_overlay.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/pattern/text/text_select_overlay.h"

namespace OHOS::Ace::NG {

namespace {
const std::string IMAGE_ICON = "app.media.icon";

} // namespace

class TextFieldTenPatternNg : public TextBases {
public:
};

class MockTextBase : public TextBase {
public:
    MOCK_METHOD1(BetweenSelectedPosition, bool(const Offset& globalOffset));
};

/**
 * @tc.name: SpanItemUpdateParagraph007
 * @tc.desc: Test ImageSpanItem UpdateParagraph when baselineOffset is not zero.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SpanItemUpdateParagraph007, TestSize.Level1)
{
    RefPtr<ImageSpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(spanItem, nullptr);
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddPlaceholder).WillRepeatedly(Return(50));
    EXPECT_CALL(*paragraph, PopStyle).Times(AnyNumber());
    PlaceholderStyle placeholderStyle;
    placeholderStyle.width = 9.0;
    placeholderStyle.height = 10.0;
    placeholderStyle.verticalAlign = VerticalAlign::BASELINE;
    placeholderStyle.baselineOffset = 1.0;
    spanItem->UpdatePlaceholderRun(placeholderStyle);
    auto index = spanItem->UpdateParagraph(nullptr, paragraph, TextStyle());
    EXPECT_EQ(index, 50);
    MockParagraph::TearDown();
}

/**
 * @tc.name: SpanNodeUpdateTextStyle001
 * @tc.desc: Test SpanItem UpdateTextStyle when is dragging.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SpanNodeUpdateTextStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode and paragraph.
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetTextDetectEnable(true);
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->position = StringUtils::ToWstring(CREATE_VALUE).length();
    TextStyle textStyle;
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle).Times(AnyNumber());
    /**
     * @tc.steps: step2. call StartDrag
     * @tc.expected: IsDragging() return ture
     */
    spanNode->spanItem_->StartDrag(1, 2);
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    /**
     * @tc.steps: step3. call UpdateTextStyle
     * @tc.expected: cover branch content is empty.
     */
    std::u16string spanContent;
    EXPECT_TRUE(spanNode->spanItem_->IsDragging());
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step4. call UpdateTextStyle
     * @tc.expected: cover branch selStart > 0, selEnd < contentLength.
     */
    spanContent = CREATE_VALUE_W;
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 1, 2);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step5. call UpdateTextStyle
     * @tc.expected: cover branch selStart < 0, selEnd < 0.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, -1, -1);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    /**
     * @tc.steps: step6. call UpdateTextStyle
     * @tc.expected: cover branch selStart > contentLength, selEnd > contentLength.
     */
    spanNode->spanItem_->UpdateTextStyle(spanContent, paragraph, textStyle, 20, 20);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    MockParagraph::TearDown();
}

/**
 * @tc.name: UpdateTextStyleForAISpan002
 * @tc.desc: Test SpanItem UpdateTextStyleForAISpan when children is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, UpdateTextStyleForAISpan002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetTextDetectEnable(true);
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);

    Ace::AISpan aiSpan1;
    aiSpan1.start = AI_SPAN_END_II + 1;
    aiSpan1.end = AI_SPAN_START;
    aiSpan1.content = SPAN_PHONE;
    aiSpan1.type = TextDataDetectType::PHONE_NUMBER;
    Ace::AISpan aiSpan2;
    aiSpan2.start = 0;
    aiSpan2.end = -1;
    aiSpan2.content = SPAN_URL;
    aiSpan2.type = TextDataDetectType::URL;
    std::map<int32_t, Ace::AISpan> aiSpanMap;
    aiSpanMap[AI_SPAN_START] = aiSpan1;
    aiSpanMap[AI_SPAN_START_II] = aiSpan2;
    spanNode->spanItem_->aiSpanMap = aiSpanMap;
    spanNode->spanItem_->fontStyle = nullptr;

    std::u16string spanContent = U16TEXT_FOR_AI;
    spanNode->spanItem_->position = spanContent.length();
    TextStyle textStyle;
    auto aiSpanStyle = textStyle;
    pattern->ModifyAISpanStyle(aiSpanStyle);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle).Times(AnyNumber());

    spanNode->spanItem_->SetNeedRemoveNewLine(true);
    spanNode->spanItem_->UpdateTextStyleForAISpan(spanContent, paragraph, textStyle, aiSpanStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
    MockParagraph::TearDown();
}

/**
 * @tc.name: SpanNodeGetSpanResultObject001
 * @tc.desc: Test ImageSpanItem GetSpanResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SpanNodeGetSpanResultObject001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize spanNode.
     */
    RefPtr<ImageSpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->interval = {0, 10};
    auto obj = spanItem->GetSpanResultObject(1, 10);
    EXPECT_FALSE(obj.isInit);
    obj = spanItem->GetSpanResultObject(0, 9);
    EXPECT_FALSE(obj.isInit);
    /**
     * @tc.steps: step2. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image don't have value.
     */
    std::optional<std::string> image;
    std::optional<RefPtr<PixelMap>> pixelMap;
    ImageSpanOptions options1 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options1);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    /**
     * @tc.steps: step3. call GetSpanResultObject
     * @tc.expected: cover branch imagePixelMap and image have value.
     */
    image = make_optional(IMAGE_ICON);
    pixelMap = PixelMap::CreatePixelMap(nullptr);
    ImageSpanOptions options2 = { .image = image, .imagePixelMap = pixelMap };
    spanItem->SetImageSpanOptions(options2);
    obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    EXPECT_EQ(StringUtils::Str16ToStr8(obj.valueString), image);
    EXPECT_EQ(obj.valuePixelMap, pixelMap.value());
}

/**
 * @tc.name: SpanNodeGetSpanResultObject002
 * @tc.desc: Test SpanItem GetSpanResultObject.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SpanNodeGetSpanResultObject002, TestSize.Level1)
{
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->interval = {0, 10};
    auto obj = spanItem->GetSpanResultObject(0, 10);
    EXPECT_TRUE(obj.isInit);
    obj = spanItem->GetSpanResultObject(1, 11);
    EXPECT_TRUE(obj.isInit);
    obj = spanItem->GetSpanResultObject(-1, 9);
    EXPECT_TRUE(obj.isInit);
    obj = spanItem->GetSpanResultObject(1, 9);
    EXPECT_TRUE(obj.isInit);
    obj = spanItem->GetSpanResultObject(-1, -1);
    EXPECT_FALSE(obj.isInit);
}

/**
 * @tc.name: ToJsonValue007
 * @tc.desc: Test textPattern ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ToJsonValue007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"");
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = frameNode->GetPattern<TextPattern>();
    auto json = JsonUtil::Create(true);
    /**
     * @tc.steps: step2. expect default textDetectEnable_ false.
     */
    pattern->SetTextDetectEnable(true);
    pattern->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("enableDataDetector"), "true");
}

/**
 * @tc.name: TextDragOverlayModifierTestNG001
 * @tc.desc: test text_drag_overlay_modifier.cpp onDraw(DrawingContext& context) function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextDragOverlayModifierTestNG001, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode(
        V2::RICH_EDITOR_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(V2::TEXTDRAG_ETS_TAG, nullptr);
    auto textPattern = textNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    textPattern->pManager_->AddParagraph(ParagraphManager::ParagraphInfo());
    auto dragNode = TextDragPattern::CreateDragNode(textNode);
    ASSERT_NE(dragNode, nullptr);
    auto test = dragNode->GetPattern<TextDragPattern>();
    ASSERT_NE(test, nullptr);

    WeakPtr<TextDragPattern> mockPattern = std::move(test);
    auto modifier = AceType::MakeRefPtr<TextDragOverlayModifier>(mockPattern);
    ASSERT_NE(modifier, nullptr);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, ClipPath(_, _, _)).Times(AtLeast(1));

    DrawingContext context { rsCanvas, 50.0f, 50.0f };
    modifier->isAnimating_ = false;
    modifier->type_ = DragAnimType::DEFAULT;
    modifier->onDraw(context);

    auto pattern = AccessibilityManager::DynamicCast<TextDragPattern>(modifier->pattern_.Upgrade());
    EXPECT_NE(pattern->backGroundPath_.get(), nullptr);
    EXPECT_NE(modifier->isAnimating_, true);
    pattern->backGroundPath_ = nullptr;
    modifier->onDraw(context);

    modifier->isAnimating_ = true;
    pattern->backGroundPath_ = nullptr;
    EXPECT_NE(modifier->isAnimating_, false);
    EXPECT_EQ(pattern->backGroundPath_.get(), nullptr);
    modifier->onDraw(context);
}

/**
 * @tc.name: TextDragOverlayModifierTestNG002
 * @tc.desc: test text_drag_overlay_modifier.cpp PaintBackground function
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextDragOverlayModifierTestNG002, TestSize.Level1)
{
    RefPtr<TextDragPattern> mockPattern = AceType::MakeRefPtr<TextDragPattern>();
    TextDragOverlayModifier modifier(mockPattern);
    DragAnimType type = DragAnimType::DEFAULT;
    modifier.type_ = type;

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachPen(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawPath(_)).WillRepeatedly(Return());

    ON_CALL(rsCanvas, AttachBrush(_))
        .WillByDefault(ReturnRef(rsCanvas));
    ON_CALL(rsCanvas, DrawPath(_))
        .WillByDefault(::testing::Return());

    RSPath path = RSPath();
    EXPECT_EQ(modifier.type_, type);
    modifier.PaintBackground(path, rsCanvas, mockPattern);
}

/**
 * @tc.name: TextFieldDeleteRange001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange001, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = 5;
    int32_t end = 2;
    const std::u16string str1 = u"abc";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_FALSE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: TextFieldDeleteRange002
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange002, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = 3;
    int32_t end = 5;
    const std::u16string str1 = u"ab";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_TRUE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: TextFieldDeleteRange003
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange003, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = 2;
    int32_t end = 5;
    const std::u16string str1 = u"abc";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_FALSE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: TextFieldDeleteRange004
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange004, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = 2;
    int32_t end = 2;
    const std::u16string str1 = u"abc";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_TRUE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: TextFieldDeleteRange005
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange005, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = -2;
    int32_t end = -1;
    const std::u16string str1 = u"abcdefgh";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_TRUE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: TextFieldDeleteRange006
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, TextFieldDeleteRange006, TestSize.Level1)
{
    TextFieldPattern textFieldPatternObject;
    int32_t start = 6;
    int32_t end = 5;
    const std::u16string str1 = u"abc";
    textFieldPatternObject.showCountBorderStyle_ = true;
    textFieldPatternObject.contentController_->SetTextValue(str1);
    textFieldPatternObject.DeleteRange(start, end);
    EXPECT_TRUE(textFieldPatternObject.showCountBorderStyle_);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: test text_pattern.cpp HandleClickEvent function,
    case dataDetectorAdapter_->hasClickedAISpan_,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleClickEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    pattern->HandleClickEvent(info);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->hasClickedAISpan_);
}

/**
 * @tc.name: HandleUrlClick001
 * @tc.desc: test text_pattern.cpp HandleUrlClick function,
    case iter == spans_.end(), span && span->urlOnRelease,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleUrlClick001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->clickedSpanPosition_ = 1;
    auto ret = pattern->HandleUrlClick();
    EXPECT_FALSE(ret);

    RefPtr<SpanItem> item = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> item1 = AceType::MakeRefPtr<SpanItem>();
    item1->urlOnRelease = []{};
    pattern->spans_.push_back(item);
    pattern->spans_.push_back(item1);
    ret = pattern->HandleUrlClick();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: HandleSingleClickEvent001
 * @tc.desc: test text_pattern.cpp HandleSingleClickEvent function,
    case IsUsingMouse() && isMousePressed_ && leftMousePressed_ && moveOverClickThreshold_,
        HandleUrlClick(), dataDetectorAdapter_->hasClickedAISpan_,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSingleClickEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    pattern->sourceType_ = SourceType::MOUSE;
    pattern->isMousePressed_ = true;
    pattern->leftMousePressed_ = true;
    pattern->moveOverClickThreshold_= true;
    pattern->HandleSingleClickEvent(info);
    EXPECT_FALSE(pattern->moveOverClickThreshold_);

    pattern->sourceType_ = SourceType::NONE;
    pattern->isMousePressed_ = false;
    pattern->leftMousePressed_ = false;
    pattern->moveOverClickThreshold_= false;
    pattern->clickedSpanPosition_ = 1;
    RefPtr<SpanItem> item = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> item1 = AceType::MakeRefPtr<SpanItem>();
    item1->urlOnRelease = []{};
    pattern->spans_.push_back(item);
    pattern->spans_.push_back(item1);
    pattern->HandleSingleClickEvent(info);
    EXPECT_FALSE(pattern->moveOverClickThreshold_);

    pattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    pattern->isMousePressed_ = true;
    pattern->clickedSpanPosition_ = -1;
    pattern->HandleSingleClickEvent(info);
    EXPECT_TRUE(pattern->selectOverlay_->originalMenuIsShow_);
}

/**
 * @tc.name: HandleClickOnTextAndSpan001
 * @tc.desc: test text_pattern.cpp HandleClickOnTextAndSpan function,
    case iter == spans_.end(), !(span && span->onClick),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleClickOnTextAndSpan001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    pattern->isMousePressed_ = true;
    pattern->clickedSpanPosition_ = 0;
    bool flag = false;
    pattern->onClick_ = [&flag] (GestureEvent& info) { flag = true;};
    pattern->HandleClickOnTextAndSpan(info);
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: CheckClickedOnSpanOrText001
 * @tc.desc: test text_pattern.cpp CheckClickedOnSpanOrText function,
    case onClick_,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CheckClickedOnSpanOrText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RectF textContentRect;
    Offset localLocation;
    pattern->onClick_ = [] (GestureEvent& info) {};
    auto ret = pattern->CheckClickedOnSpanOrText(textContentRect, localLocation);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: CalculateClickedSpanPosition001
 * @tc.desc: test text_pattern.cpp CalculateClickedSpanPosition function,
    case !item,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CalculateClickedSpanPosition001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    PointF textOffset;
    RefPtr<SpanItem> item = nullptr;
    pattern->spans_.push_back(item);
    auto ret = pattern->CalculateClickedSpanPosition(textOffset);
    EXPECT_EQ(pattern->clickedSpanPosition_, -1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: CheckAndClick001
 * @tc.desc: test text_pattern.cpp CheckAndClick function,
    case !(item->onClick || item->urlOnRelease),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CheckAndClick001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<SpanItem> item = AceType::MakeRefPtr<SpanItem>();
    item->onClick = nullptr;
    item->urlOnRelease = nullptr;
    auto ret = pattern->CheckAndClick(item);
    EXPECT_EQ(pattern->clickedSpanPosition_, -1);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ClickAISpan001
 * @tc.desc: test text_pattern.cpp ClickAISpan function,
    case !(item->onClick || item->urlOnRelease),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ClickAISpan001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    PointF textOffset;
    AISpan aiSpan;
    auto textLayoutProperty =  pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    ParagraphManager::ParagraphInfo info;
    ParagraphStyle paragraphStyle;
    info.paragraph = Paragraph::Create(paragraphStyle, FontCollection::Current());
    //info.paragraph->paragraph_
    pattern->pManager_->paragraphs_.push_back(info);
    auto ret = pattern->ClickAISpan(textOffset, aiSpan);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDragEnd001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnDragEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: Step1. Create text pattern and prepare basic environment
     */
    TextModelNG textModel;
    textModel.Create("Test");
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();

    /**
     * @tc.steps: Step2 Empty dragResultObjects_
     */
    pattern->dragResultObjects_.clear();
    pattern->status_ = Status::DRAGGING;
    pattern->OnDragEnd(nullptr);
    EXPECT_NE(pattern->status_, Status::DRAGGING);

    /**
     * @tc.steps: Step3 Non-empty dragResultObjects_
     */
    ResultObject resultObject;
    pattern->dragResultObjects_.emplace_back(resultObject);
    EXPECT_FALSE(pattern->dragResultObjects_.empty());
    auto event = AceType::MakeRefPtr<Ace::DragEvent>();
    event->SetResult(DragRet::DRAG_DEFAULT);

    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_NE(textPattern, nullptr);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    textPattern->status_ = Status::DRAGGING;
    textPattern->dragResultObjects_.emplace_back(resultObject);
    textPattern->copyOption_ = CopyOptions::Local;
    textPattern->lastDragTool_ = SourceTool::FINGER;
    EXPECT_EQ(textPattern->GetCurrentDragTool(), SourceTool::FINGER);
    textPattern->OnDragEnd(event);
    EXPECT_TRUE(textPattern->dragResultObjects_.empty());
}

/**
 * @tc.name: OnWindowHide001
 * @tc.desc: test TextPattern OnWindowHide
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnWindowHide001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    host->tag_ = V2::SYMBOL_ETS_TAG;

    (void)pattern->GetOrCreateMagnifier();
    (void)pattern->CreateNodePaintMethod();
    pattern->magnifierController_ = nullptr;
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->isLoopAnimation_ = true;
    EXPECT_TRUE(layoutProperty->GetIsLoopAnimation());
    auto symbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());

    /**
     * @tc.expected: Cover the branch when magnifierController_ is nullptr,
     * and expecting GetIsTxtActive in the function PauseSymbolAnimation() to return true.
     */
    symbolEffectOptions.SetIsTxtActive(true);
    pattern->OnWindowHide();
    EXPECT_TRUE(symbolEffectOptions.GetIsTxtActive());

    /**
     * @tc.expected: Cover the branch when magnifierController_ is nullptr,
     * and expecting GetIsTxtActive in the function PauseSymbolAnimation() to return false.
     */
    symbolEffectOptions.SetIsTxtActive(false);
    pattern->OnWindowHide();
    EXPECT_FALSE(symbolEffectOptions.GetIsTxtActive());
}

/**
 * @tc.name: SetOnClickMenu001
 * @tc.desc: test text_pattern.cpp SetOnClickMenu function,
    case action == COPY, action == SELECT_TEXT, calculateHandleFunc == nullptr,
        showSelectOverlayFunc == nullptr, calculateHandleFunc != nullptr, showSelectOverlayFunc != nullptr,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetOnClickMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    AISpan aiSpan;
    CalculateHandleFunc calculateHandleFunc;
    ShowSelectOverlayFunc showSelectOverlayFunc;
    pattern->SetOnClickMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
    std::string action("copy");
    pattern->textSelector_.baseOffset = 1;
    pattern->textSelector_.destinationOffset = 3;
    pattern->shiftFlag_ = false;
    pattern->dataDetectorAdapter_->onClickMenu_(action);
    EXPECT_EQ(pattern->textSelector_.baseOffset, -1);
    EXPECT_EQ(pattern->textSelector_.destinationOffset, -1);

    bool flag = false;
    int32_t value = 0;
    action = "selectText";
    pattern->dataDetectorAdapter_->onClickMenu_(action);
    EXPECT_FALSE(flag);
    EXPECT_EQ(value, 0);

    calculateHandleFunc = [&value]() { value = 123;};
    showSelectOverlayFunc = [&flag](const RectF&, const RectF&) { flag = true; };
    pattern->SetOnClickMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
    pattern->dataDetectorAdapter_->onClickMenu_(action);
    EXPECT_TRUE(flag);
    EXPECT_EQ(value, 123);
}

/**
 * @tc.name: ShowAIEntityMenu001
 * @tc.desc: test text_pattern.cpp ShowAIEntityMenu function,
    case mode == TextSelectableMode::UNSELECTABLE, !NearEqual(safeAreaManager->GetKeyboardInset().Length(), 0)
        && mode == TextSelectableMode::SELECTABLE_FOCUSABLE,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ShowAIEntityMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    AISpan aiSpan;
    CalculateHandleFunc calculateHandleFunc;
    ShowSelectOverlayFunc showSelectOverlayFunc;
    auto host = pattern->GetHost();
    auto context = host->GetContext();
    auto safeAreaManager = context->GetSafeAreaManager();
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    safeAreaManager->keyboardAvoidMode_ = KeyBoardAvoidMode::OFFSET;
    safeAreaManager->keyboardInset_.start = 0;
    safeAreaManager->keyboardInset_.end = 2;
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::UNSELECTABLE);
    pattern->copyOption_ = CopyOptions::InApp;
    auto ret = pattern->ShowAIEntityMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
    EXPECT_TRUE(ret);

    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    ret = pattern->ShowAIEntityMenu(aiSpan, calculateHandleFunc, showSelectOverlayFunc);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: InitMouseEvent001
 * @tc.desc: test text_pattern.cpp InitMouseEvent function,
    case pattern,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, InitMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto eventHub = host->GetOrCreateEventHub<EventHub>();
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    pattern->currentMouseStyle_ = MouseFormat::WEST;
    pattern->InitMouseEvent();

    bool isHover = true;
    inputHub->hoverEventActuator_->inputEvents_.front()->GetOnHoverEventFunc()(isHover);
    EXPECT_EQ(pattern->currentMouseStyle_, MouseFormat::DEFAULT);
}

/**
 * @tc.name: AddIsFocusActiveUpdateEvent001
 * @tc.desc: test text_pattern.cpp AddIsFocusActiveUpdateEvent function,
    case !isFocusActiveUpdateEvent_,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddIsFocusActiveUpdateEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->isFocusActiveUpdateEvent_ = nullptr;
    pattern->AddIsFocusActiveUpdateEvent();
    EXPECT_NE(pattern->isFocusActiveUpdateEvent_, nullptr);
}

/**
 * @tc.name: RecoverCopyOption001
 * @tc.desc: test text_pattern.cpp RecoverCopyOption function,
    case textDetectEnable_ && enabledCache != enabled_,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, RecoverCopyOption001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->enabled_ = false;
    pattern->textDetectEnable_ = true;
    pattern->RecoverCopyOption();
    EXPECT_TRUE(pattern->enabled_);
}

/**
 * @tc.name: InitCopyOption001
 * @tc.desc: test text_pattern.cpp InitCopyOption function,
    case longPressEvent_ && !hasSpanStringLongPressEvent_, !clipboard_ && context,
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, InitCopyOption001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    RefPtr<GestureEventHub> gestureEventHub =
        AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto longPressCallback = [](GestureEvent& info) {};
    pattern->longPressEvent_ = AIWriteAdapter::MakeRefPtr<LongPressEvent>(std::move(longPressCallback));
    pattern->hasSpanStringLongPressEvent_ = false;
    pattern->onClick_ = [](GestureEvent& info) {};
    pattern->textDetectEnable_ = true;
    pattern->enabled_ = true;
    RefPtr<SpanItem> item = nullptr;
    pattern->spans_.push_back(item);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::CLIP);
    pattern->clipboard_ = nullptr;
    pattern->InitCopyOption(gestureEventHub, eventHub);
    EXPECT_EQ(pattern->longPressEvent_, nullptr);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: test text_pattern.cpp HandleMouseEvent function,
    case isAutoScrollByMouse_ && GetHost(),
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    MouseInfo info;
    info.globalLocation_ = Offset(4, 5);
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    pattern->leftMousePressedOffset_ = Offset(0, 0);
    pattern->isAutoScrollByMouse_ = true;
    pattern->HandleMouseEvent(info);
    EXPECT_EQ(pattern->leftMousePressedOffset_, Offset(4, 5));
}

/**
 * @tc.name: OnDragEndNoChild001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnDragEndNoChild001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"TestChild");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step2. Test OnDragEndNoChild expected result is DRAG_DEFAULT and
     * event is true when isSelectableAndCopy is true.
     * @tc.expect: expect OnDragEndNoChild will set status None
     */
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    event->SetResult(DragRet::DRAG_DEFAULT);
    pattern->status_ = Status::DRAGGING;
    pattern->OnDragEndNoChild(event);
    EXPECT_EQ(pattern->status_, Status::NONE);

    /**
     * @tc.steps: step3.test OnDragEndNoChild even result DRAG_SUCCESS
     * @tc.expect: expect OnDragEndNoChild will set status None
     */
    event->SetResult(DragRet::DRAG_SUCCESS);
    pattern->status_ = Status::DRAGGING;
    pattern->OnDragEndNoChild(event);
    EXPECT_EQ(pattern->status_, Status::NONE);

    /**
     * @tc.steps: step4. test OnDragEndNoChild with drag tool FINGER.
     * @tc.expect: expect OnDragEndNoChild will set status None, showSelect_ is true.
     */
    event->SetResult(DragRet::DRAG_DEFAULT);
    pattern->status_ = Status::DRAGGING;
    pattern->SetCurrentDragTool(SourceTool::FINGER);
    pattern->OnDragEndNoChild(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
    EXPECT_EQ(pattern->showSelect_, true);

    /**
     * @tc.steps: step5. call OnDragEndNoChild function with status NONE.
     * @tc.expect: expect OnDragEndNoChild will not change status.
     */
    pattern->status_ = Status::NONE;
    pattern->showSelect_ = false;
    pattern->OnDragEndNoChild(event);
    EXPECT_EQ(pattern->status_, Status::NONE);
}

/**
 * @tc.name: HandleOnSelect001
 * @tc.desc: test HandleOnSelect.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleOnSelect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    EXPECT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize text and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"12345");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3. test verify switch-case KeyCode.
     * @tc.expect: expect call HandleSelection/HandleSelectionDown/HandleSelectionUp function.
     */
    KeyCode code = KeyCode::KEY_DPAD_LEFT;
    textPattern->HandleOnSelect(code);
    EXPECT_NE(textPattern->textSelector_.GetEnd(), 5);

    code = KeyCode::KEY_DPAD_RIGHT;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);

    code = KeyCode::KEY_DPAD_UP;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);

    code = KeyCode::KEY_DPAD_DOWN;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);

    code = KeyCode::KEY_DPAD_CENTER;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);

    /**
     * @tc.steps: step4. test KEY_DPAD_UP with shiftFlag_ true.
     * @tc.expect: expect ResetOriginCaretPosition is not called.
     */
    textPattern->shiftFlag_ =true;
    code = KeyCode::KEY_DPAD_UP;
    textPattern->HandleOnSelect(code);
    
    code = KeyCode::KEY_DPAD_DOWN;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);

    /**
     * @tc.steps: step5. test KEY_DPAD_UP with shiftFlag_ false.
     * @tc.expect: expect HandleOnSelect is called.
     */
    textPattern->shiftFlag_ = false;
    code = KeyCode::KEY_DPAD_UP;
    textPattern->HandleOnSelect(code);

    code = KeyCode::KEY_DPAD_DOWN;
    textPattern->HandleOnSelect(code);
    EXPECT_EQ(textPattern->textSelector_.GetEnd(), 6);
}

/**
 * @tc.name: HandleMouseLeftReleaseAction001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftReleaseAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. Set blockPress_ to false and isDoubleClick_ to true.
     * @tc.expect: blockPress_ value will not be changed.
     */
    MouseInfo info;
    Offset offset = Offset(1, 1);
    pattern->blockPress_ = false;
    pattern->isDoubleClick_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->blockPress_);

    /**
     * @tc.steps: step3. Set mouseStatus_  and hasClickedAISpan_ is true.
     * @tc.expect: blockPress_ value will be changed.
     */
    pattern->blockPress_ = true;
    pattern->status_ = Status::FLOATING;
    pattern->mouseStatus_ = MouseStatus::PRESSED;
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->blockPress_);
}

/**
 * @tc.name: HiddenMenu001
 * @tc.desc: test TextPattern HiddenMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HiddenMenu001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->sourceType_ = SourceType::MOUSE;
    pattern->HiddenMenu();
    EXPECT_TRUE(pattern->IsUsingMouse());
}

/**
 * @tc.name: CreateHandles001
 * @tc.desc: test CreateHandles
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CreateHandles001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->status_ = Status::DRAGGING;
    pattern->CreateHandles();
    EXPECT_TRUE(pattern->IsDragging());
}

/**
 * @tc.name: AddSubComponentInfoForSpan001
 * @tc.desc: test AddSubComponentInfoForSpan
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddSubComponentInfoForSpan001, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    std::string content = "test";
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    GestureEventFunc onClick = [](GestureEvent& info) {
        return;
    };
    RefPtr<SpanItem> span = AceType::MakeRefPtr<SpanItem>();
    span->onClick = onClick;
    span->accessibilityProperty = nullptr;
    pattern->AddSubComponentInfoForSpan(subComponentInfos, content, span);
    EXPECT_NE(subComponentInfos.size(), 0);
}

/**
 * @tc.name: ToTreeJson001
 * @tc.desc: test ToTreeJson
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ToTreeJson001, TestSize.Level1)
{
    std::string testJson = "\"Ace Unittest\"";
    std::unique_ptr<JsonValue> stringValue = JsonUtil::ParseJsonString(testJson);
    InspectorConfig config;
    std::string defaultVal = "";
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->textForDisplay_.clear();
    pattern->ToTreeJson(stringValue, config);
    stringValue->GetString(TreeKey::CONTENT, defaultVal);
    EXPECT_TRUE(defaultVal.empty());

    pattern->textForDisplay_ = u"Some text";
    pattern->ToTreeJson(stringValue, config);
    stringValue->GetString(TreeKey::CONTENT, defaultVal);
    EXPECT_FALSE(pattern->textForDisplay_.empty());
}

/**
 * @tc.name: HandleMouseLeftReleaseAction002
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftReleaseAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. Set blockPress_ to false and isDoubleClick_ to true.
     * @tc.expect: blockPress_ value will not be changed.
     */
    MouseInfo info;
    Offset offset = Offset(1, 1);
    pattern->blockPress_ = false;
    pattern->isDoubleClick_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->isDoubleClick_);

    /**
     * @tc.steps: step3. Set mouseStatus_  and hasClickedAISpan_ is true.
     * @tc.expect: blockPress_ value will be changed.
     */
    pattern->blockPress_ = true;
    pattern->status_ = Status::FLOATING;
    pattern->mouseStatus_ = MouseStatus::PRESSED;
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->blockPress_);

    pattern->mouseStatus_ = MouseStatus::MOVE;
    pattern->HandleMouseLeftReleaseAction(info, offset);

    pattern->shiftFlag_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->blockPress_);
}

/**
 * @tc.name: OnDragMove001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnDragMove001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"TestChild");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    auto host = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto event = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();

    /**
     * @tc.steps: step2. Set status_ is DRAGGING
     * @tc.expect: The initial value of showSelect_ is true `OnDragMove` will set showSelect_ to false.
     */
    pattern->status_ = Status::DRAGGING;
    pattern->OnDragMove(event);
    EXPECT_EQ(pattern->showSelect_, false);

    /**
     * @tc.steps: step3. Set status_ not DRAGGING
     * @tc.expect: pattern->showSelect_ has not been changed.
     */
    pattern->status_ = Status::NONE;
    pattern->showSelect_ = true;
    pattern->OnDragMove(event);
    EXPECT_EQ(pattern->showSelect_, true);
}

/**
 * @tc.name: GetThumbnailCallback001
 * @tc.desc: test GetThumbnailCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetThumbnailCallback001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create textFrameNode and textPattern
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    EXPECT_NE(textPattern, nullptr);

    auto func = textPattern->GetThumbnailCallback();
    EXPECT_NE(func, nullptr);
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    std::vector<RectF> rects { RectF(0, 0, 20, 20) };
    EXPECT_CALL(*paragraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));

    textFrameNode->draggable_ = true;
    textFrameNode->GetOrCreateEventHub<EventHub>()->SetOnDragStart(
        [](const RefPtr<Ace::DragEvent>&, const std::string&) -> DragDropInfo { return {}; });
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(0, 3);
    textPattern->textForDisplay_ = TEXT_U16CONTENT;

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);

    auto childFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(childFrameNode, nullptr);
    textPattern->childNodes_.emplace_back(childFrameNode);
    func = textPattern->GetThumbnailCallback();
    
    auto imageNode = FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, 1,
            AceType::MakeRefPtr<ImagePattern>());
    textFrameNode->AddChild(imageNode);
    func = textPattern->GetThumbnailCallback();
    auto children = textPattern->GetChildNodes();
    EXPECT_EQ(children.size(), 1);

    textPattern->dragNode_ = nullptr;
    func(Offset(0, 1));
    EXPECT_NE(textPattern->dragNode_, nullptr);
}

/**
 * @tc.name: GetSubComponentInfos001
 * @tc.desc: test GetSubComponentInfos
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetSubComponentInfos001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    auto spanItem2 = AceType::MakeRefPtr<PlaceholderSpanItem>();
    spanItem1->spanItemType = SpanItemType::CustomSpan;
    spanItem2->placeholderSpanNodeId = 0;
    pattern->spans_.push_back(spanItem1);
    pattern->spans_.push_back(spanItem2);
    pattern->spans_.push_back(nullptr);

    std::vector<SubComponentInfo> subComponentInfos;
    size_t result = pattern->GetSubComponentInfos(subComponentInfos);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: InitSpanItem001
 * @tc.desc: test InitSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, InitSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    std::stack<SpanNodeInfo> nodes;
    pattern->InitSpanItem(nodes);
    EXPECT_EQ(pattern->textForDisplay_, u"");
}

/**
 * @tc.name: GetSubComponentInfosForSpans001
 * @tc.desc: test GetSubComponentInfosForSpans
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetSubComponentInfosForSpans001, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    RefPtr<SpanItem> span = nullptr;
    RefPtr<SpanItem> span1 = AceType::MakeRefPtr<SpanItem>();
    span1->nodeId_ = 1;
    span1->unicode = 1;
    RefPtr<SpanItem> span2 = AceType::MakeRefPtr<SpanItem>();
    span2->nodeId_ = -1;
    span2->unicode = 1;
    RefPtr<SpanItem> span3 = AceType::MakeRefPtr<SpanItem>();
    span3->nodeId_ = 1;
    span3->unicode = 0;
    RefPtr<SpanItem> span4 = AceType::MakeRefPtr<SpanItem>();
    span4->nodeId_ = -1;
    span4->unicode = 0;
    span4->spanItemType = SpanItemType::CustomSpan;
    RefPtr<SpanItem> span5 = AceType::MakeRefPtr<SpanItem>();
    span5->nodeId_ = -1;
    span5->unicode = 0;
    GestureEventFunc onClick = [](GestureEvent& info) {
        return;
    };
    span5->content = u"test";
    span5->onClick = onClick;
    span5->spanItemType = SpanItemType::NORMAL;
    pattern->spans_.push_back(span);
    pattern->spans_.push_back(span1);
    pattern->spans_.push_back(span2);
    pattern->spans_.push_back(span3);
    pattern->spans_.push_back(span4);
    pattern->spans_.push_back(span5);
    pattern->GetSubComponentInfosForSpans(subComponentInfos);
    EXPECT_NE(subComponentInfos.size(), 0);
}

/**
 * @tc.name: GetSymbolSpanResultObject001
 * @tc.desc: test GetSymbolSpanResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetSymbolSpanResultObject001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    int32_t index = 1;
    int32_t start = 1;
    int32_t end = 1;
    EXPECT_FALSE(pattern->GetSymbolSpanResultObject(nullptr, index, start, end).isDraggable);
}

/**
 * @tc.name: UpdateSelectOverlayOrCreate001
 * @tc.desc: test UpdateSelectOverlayOrCreate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, UpdateSelectOverlayOrCreate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    RefPtr<SelectOverlayProxy> selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    SelectOverlayInfo selectInfo;
    selectInfo.isNewAvoid = true;
    selectInfo.isUsingMouse = false;
    selectOverlayProxy->selectOverlayId_ = 1;
    pattern->selectOverlayProxy_ = selectOverlayProxy;
    bool animation = false;
    auto pipeline = PipelineContext::GetCurrentContext();
    auto manager = pipeline->GetSelectOverlayManager();
    auto node3 = AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> selectOverlayItem = AceType::WeakClaim(AceType::RawPtr(node3));
    manager->selectOverlayItem_ = selectOverlayItem;
    pattern->UpdateSelectOverlayOrCreate(selectInfo, animation);
    EXPECT_FALSE(pattern->selectOverlayProxy_->IsClosed());

    pattern->selectOverlayProxy_.Reset();
    pattern->UpdateSelectOverlayOrCreate(selectInfo, animation);
    EXPECT_FALSE(pattern->selectOverlayProxy_);
}

/**
 * @tc.name: OnVisibleChange001
 * @tc.desc: test OnVisibleChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnVisibleChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    bool isVisible = false;
    pattern->textDetectEnable_ = true;
    pattern->OnVisibleChange(isVisible);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->aiDetectDelayTask_);
}

/**
 * @tc.name: GetTextResultObject001
 * @tc.desc: test TextPattern GetTextResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetTextResultObject001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<UINode> uinode = nullptr;
    int32_t index = 10;
    int32_t start = 1;
    int32_t end = 100;

    pattern->GetTextResultObject(uinode, index, start, end);
    auto node = AceType::DynamicCast<SpanNode>(uinode);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: GetImageResultObject001
 * @tc.desc: test TextPattern GetImageResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetImageResultObject001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    RefPtr<UINode> uinode = nullptr;
    int32_t index = -10;
    int32_t start = 1;
    int32_t end = 100;

    pattern->GetImageResultObject(uinode, index, start, end);
    auto ret = pattern->GetSpanItemByIndex(index);
    EXPECT_EQ(ret, nullptr);

    index = 10;
    pattern->GetImageResultObject(uinode, index, start, end);
    auto node = AceType::DynamicCast<FrameNode>(uinode);
    EXPECT_EQ(node, nullptr);
}

/**
 * @tc.name: MountImageNode001
 * @tc.desc: test TextPattern MountImageNode
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, MountImageNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);

    auto imageItem = AceType::MakeRefPtr<NG::ImageSpanItem>();
    imageItem->options.imageAttribute = ImageSpanAttribute();
    imageItem->options.imageAttribute->colorFilterMatrix = std::vector<float>{0.5f, 1.0f, 0.2f, 1.0f};

    pattern->MountImageNode(imageItem);

    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        imageItem->nodeId_, []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(imageLayoutProperty, nullptr);
    EXPECT_EQ(imageLayoutProperty->HasImageFit(), false);
}

/**
 * @tc.name: ProcessSpanString001
 * @tc.desc: test TextPattern ProcessSpanString
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessSpanString001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->textDetectEnable_ = true;
    EXPECT_TRUE(pattern->CanStartAITask());
    EXPECT_FALSE(pattern->dataDetectorAdapter_->aiDetectInitialized_);

    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    pattern->ProcessSpanString();
    EXPECT_NE(layoutProperty, nullptr);
}

/**
 * @tc.name: SetExternalSpanItem001
 * @tc.desc: test TextPattern SetExternalSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetExternalSpanItem001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    std::list<RefPtr<SpanItem>> spans;
    spans.emplace_back(spanItem);
    
    pattern->SetExternalSpanItem(spans);
    EXPECT_NE(pattern->styledString_, nullptr);
}

/**
 * @tc.name: PauseSymbolAnimation001
 * @tc.desc: test PauseSymbolAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, PauseSymbolAnimation001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->SetIsLoopAnimation(true);
    pattern->PauseSymbolAnimation();
    auto testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_FALSE(testSymbolEffectOptions.GetIsTxtActive());

    SymbolEffectOptions symbolEffectOptions;
    symbolEffectOptions.SetIsTxtActive(true);
    layoutProperty->UpdateSymbolEffectOptions(symbolEffectOptions);
    testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_TRUE(testSymbolEffectOptions.GetIsTxtActive());
    pattern->PauseSymbolAnimation();
    testSymbolEffectOptions = layoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_FALSE(testSymbolEffectOptions.GetIsTxtActive());
}

/**
 * @tc.name: HandleSurfaceChanged001
 * @tc.desc: test HandleSurfaceChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSurfaceChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);

    pattern->HandleSurfaceChanged(10, 10, 20, 20, WindowSizeChangeReason::UNDEFINED);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_TRUE(layoutProperty->propNeedReCreateParagraph_);
}

/**
 * @tc.name: AddImageToSpanItem001
 * @tc.desc: test AddImageToSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddImageToSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::RICH_EDITOR_ETS_TAG, 0, pattern);

    auto imageSpanNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    pattern->AddImageToSpanItem(imageSpanNode);
    EXPECT_EQ(pattern->spans_.size(), 1);
}

/**
 * @tc.name: DumpSpanItem001
 * @tc.desc: test DumpSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpSpanItem001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(spanItem);
    pattern->spans_.push_back(nullptr);
    pattern->isSpanStringMode_ = true;

    auto& dumpLog = DumpLog::GetInstance();
    pattern->DumpSpanItem();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "-----SpanDumpInfo-----\n");
    EXPECT_NE(it, dumpLog.description_.end());
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpInfo001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 0, pattern);
    pattern->textStyle_ = TextStyle();
    pattern->contentMod_ = AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->pManager_ = nullptr;

    pattern->DumpInfo();
    auto& dumpLog = DumpLog::GetInstance();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "PaintInfo: NA\n");
    EXPECT_EQ(it, dumpLog.description_.end());
}

/**
 * @tc.name: HasContent001
 * @tc.desc: test TextPattern HasContent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HasContent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto span1 = AceType::MakeRefPtr<SpanItem>();
    span1->spanItemType = SpanItemType::NORMAL;
    pattern->spans_.push_back(span1);
    auto ret = pattern->HasContent();
    EXPECT_FALSE(ret);

    auto span2 = AceType::MakeRefPtr<SpanItem>();
    span2->spanItemType = SpanItemType::CustomSpan;
    pattern->spans_.push_back(span2);
    ret = pattern->HasContent();
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ChangeHandleHeight001
 * @tc.desc: test TextPattern ChangeHandleHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ChangeHandleHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent event;
    bool isFirst = false;
    bool isOverlayMode = false;

    pattern->ChangeHandleHeight(event, isFirst, isOverlayMode);
    bool isChangeFirstHandle = isFirst ?
        (!pattern->textSelector_.StartGreaterDest()) : pattern->textSelector_.StartGreaterDest();
    EXPECT_FALSE(isChangeFirstHandle);
}

/**
 * @tc.name: ChangeFirstHandleHeight001
 * @tc.desc: test TextPattern ChangeFirstHandleHeight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ChangeFirstHandleHeight001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    Offset touchOffset = Offset(10.0f, 5.0f);
    RectF handleRect = RectF(10.0f, 10.0f, 10.0f, 10.0f);
    pattern->ChangeFirstHandleHeight(touchOffset, handleRect);
    bool isTouchHandleCircle = LessNotEqual(touchOffset.GetY(), handleRect.Top());
    EXPECT_TRUE(isTouchHandleCircle);
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: test TextPattern DumpInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, DumpInfoTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo info1;
    pattern->pManager_->paragraphs_.push_back(info1);

    SystemProperties::debugEnabled_ = true;
    pattern->DumpInfo(json);
    EXPECT_NE(pattern->pManager_, nullptr);
    EXPECT_FALSE(pattern->pManager_->GetParagraphs().empty());
    EXPECT_TRUE(SystemProperties::GetDebugEnabled());
    EXPECT_FALSE(json->Contains("Content"));
    EXPECT_FALSE(json->Contains("PaintInfo"));
    EXPECT_FALSE(json->Contains("contentRect"));
}

/**
 * @tc.name: LogForFormRender001
 * @tc.desc: test LogForFormRender
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, LogForFormRender001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    auto host = pattern->GetHost();
    auto pipeline = host->GetContext();
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();

    std::string logTag = "logTag";
    pipeline->SetIsFormRender(true);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSetObscured());

    pipeline->SetIsFormRender(true);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = true;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSetObscured());

    pipeline->SetIsFormRender(false);
    pattern->spans_.clear();
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSensitiveEnable());

    pipeline->SetIsFormRender(false);
    pattern->spans_.clear();
    pattern->spans_.push_back(spanItem);
    pattern->isSensitive_ = false;
    pattern->LogForFormRender(logTag);
    EXPECT_FALSE(pattern->IsSensitiveEnable());
}

/**
 * @tc.name: HandleMouseLeftMoveAction001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftMoveAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::None;

    /**
     * @tc.steps: step2. Set IsSelectableAndCopy is true.
     * @tc.expect: isMousePressed_ value will  be change.
     */
    MouseInfo info;
    Offset offset(1, 1);
    pattern->HandleMouseLeftMoveAction(info, offset);
    EXPECT_EQ(pattern->isMousePressed_, false);
}

/**
 * @tc.name: HandleMouseLeftMoveAction002
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseLeftMoveAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern
     */
    auto [frameNode, pattern] = Init();
    pattern->textForDisplay_ = u"test";
    pattern->textSelector_.Update(0, 3);
    pattern->copyOption_ = CopyOptions::InApp;

    /**
     * @tc.steps: step2. Set IsSelectableAndCopy is false.
     * @tc.expect: mouseStatus_ value result  MOVE.
     */
    MouseInfo info;
    Offset offset(1, 1);
    pattern->isMousePressed_ = true;
    pattern->leftMousePressed_ = true;
    pattern->HandleMouseLeftMoveAction(info, offset);
    EXPECT_EQ(pattern->mouseStatus_, MouseStatus::MOVE);
}

/**
 * @tc.name: HandleMouseRightButton001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleMouseRightButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern, InitMouseEvent.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"1234567890");
    textModelNG.SetTextDetectEnable(true);
    auto host = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto pattern = host->GetPattern<TextPattern>();
    auto inputHub = host->GetOrCreateEventHub<EventHub>()->GetOrCreateInputEventHub();
    inputHub->mouseEventActuator_->inputEvents_.clear();
    pattern->mouseEventInitialized_ = false;
    pattern->InitMouseEvent();

    /**
     * @tc.steps: step2. test HandleMouseRightButton function and MouseButton LEFT_BUTTON.
     * @tc.expect:hasClickedAISpan_ is false.
     */
    MouseInfo info;
    info.button_ = MouseButton::LEFT_BUTTON;
    info.action_ = MouseAction::PRESS;
    Offset offset(5.f, 5.f);
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->copyOption_ = CopyOptions::None;
    pattern->HandleMouseRightButton(info, offset);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    /**
     * @tc.steps: step3. test HandleMouseRightButton function and MouseButton RIGHT_BUTTON..
     * @tc.expect: hasClickedAISpan_ is false.
     */
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = false;
    info.button_ = MouseButton::RIGHT_BUTTON;
    info.action_ = MouseAction::RELEASE;
    pattern->copyOption_ = CopyOptions::InApp;
    pattern->HandleMouseRightButton(info, offset);
    EXPECT_FALSE(pattern->dataDetectorAdapter_->hasClickedAISpan_);

    info.SetAction(MouseAction::PRESS);
    pattern->HandleMouseRightButton(info, offset);
    EXPECT_NE(pattern->dataDetectorAdapter_->hasClickedAISpan_, true);
}

/**
 * @tc.name: UpdateShiftFlag001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, UpdateShiftFlag001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create pattern and KeyEvent.
     * @tc.expected: Ensure that the pattern is not empty.
     */
    
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    KeyEvent keyEvent;

    /**
     * @tc.steps: step2. pressing the left Shift KeyAction:: DOWN
     * @tc.expected: called UpdateShiftFlag shiftFlag_ should be set to true.
     */
    keyEvent.action = KeyAction::DOWN;
    keyEvent.code = KeyCode::KEY_SHIFT_LEFT;
    keyEvent.pressedCodes.push_back(KeyCode::KEY_SHIFT_LEFT);
    pattern->UpdateShiftFlag(keyEvent);
    EXPECT_EQ(pattern->shiftFlag_, true);

    /**
     * @tc.steps: step2. pressing the left Shift KeyAction:: UP
     * @tc.expected: called UpdateShiftFlag shiftFlag_ should be set to false.
     */
    keyEvent.action = KeyAction::UP;
    pattern->shiftFlag_ = true;
    keyEvent.pressedCodes.clear();
    pattern->UpdateShiftFlag(keyEvent);
    EXPECT_EQ(pattern->shiftFlag_, false);
}

/**
 * @tc.name: CreateTextDragInfo001
 * @tc.desc: test CreateTextDragInfo
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CreateTextDragInfo001, TestSize.Level1)
{
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXTINPUT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    RefPtr<TextPattern> pattern = textNode->GetPattern<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;
    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    auto manager = AceType::MakeRefPtr<SelectContentOverlayManager>(textNode);
    pattern->selectOverlay_->OnBind(manager);
    pattern->selectOverlay_->ToggleMenu();
    pattern->AttachToFrameNode(frameNode);

    RectF paintRect1(2.0, 0.0, 0.0, 0.0);
    RectF paintRect2(1.0, 1.0, 1.0, 1.0);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    pipeline->themeManager_ = theme;
    auto ret = pattern->CreateTextDragInfo();
    EXPECT_NE(ret.firstHandle, paintRect1);
    EXPECT_NE(ret.secondHandle, paintRect2);

    auto manager1 = pattern->selectOverlay_->GetManager<SelectContentOverlayManager>();
    std::shared_ptr<SelectOverlayInfo> shareOverlayInfo = std::make_shared<SelectOverlayInfo>();
    SelectHandleInfo firstHandle;
    firstHandle.paintRect = paintRect1;

    SelectHandleInfo secondHandle;
    secondHandle.paintRect = paintRect2;
    shareOverlayInfo->firstHandle = firstHandle;
    shareOverlayInfo->secondHandle = secondHandle;
    manager1->shareOverlayInfo_ = shareOverlayInfo;
    manager1->shareOverlayInfo_->firstHandle.isShow = true;
    manager1->shareOverlayInfo_->secondHandle.isShow = true;
    ret = pattern->CreateTextDragInfo();
    EXPECT_EQ(ret.firstHandle, paintRect1);
    EXPECT_EQ(ret.secondHandle, paintRect2);

    manager1->shareOverlayInfo_ = shareOverlayInfo;
    manager1->shareOverlayInfo_->firstHandle.isShow = false;
    manager1->shareOverlayInfo_->secondHandle.isShow = false;
    ret = pattern->CreateTextDragInfo();
    EXPECT_NE(ret.firstHandle, paintRect1);
    EXPECT_NE(ret.secondHandle, paintRect2);
}

/**
 * @tc.name: GetUrlSpanColor001
 * @tc.desc: test GetUrlSpanColor
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetUrlSpanColor001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    pattern->AttachToFrameNode(frameNode);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto theme = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*theme, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<MockTextBase> mockBase = AIWriteAdapter::MakeRefPtr<MockTextBase>();
    WeakPtr<MockTextBase> textBase = mockBase;

    pattern->selectOverlay_ = AceType::MakeRefPtr<TextSelectOverlay>(textBase);
    pattern->selectOverlay_->ProcessOverlay({ .animation = false });
    pipeline->themeManager_ = theme;
    auto eventHub = pattern->GetHost()->GetOrCreateEventHub<EventHub>();
    eventHub->enabled_ = true;
    Color ret = pattern->GetUrlSpanColor();
    EXPECT_EQ(ret, pipeline->GetTheme<TextTheme>()->GetUrlDefaultColor());

    eventHub->enabled_ = false;
    ret = pattern->GetUrlSpanColor();
    EXPECT_EQ(ret, pipeline->GetTheme<TextTheme>()->GetUrlDisabledColor());
}

/**
 * @tc.name: ResumeSymbolAnimation001
 * @tc.desc: test ResumeSymbolAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ResumeSymbolAnimation001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SYMBOL_ETS_TAG, 1, pattern);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->SetIsLoopAnimation(true);
    pattern->ResumeSymbolAnimation();
    EXPECT_TRUE(pattern->GetLayoutProperty<TextLayoutProperty>()->
        GetSymbolEffectOptionsValue(SymbolEffectOptions()).GetIsTxtActive());
}

/**
 * @tc.name: OnThemeScopeUpdate001
 * @tc.desc: test OnThemeScopeUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnThemeScopeUpdate001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    int32_t themeScopeId = 0;
    bool result = pattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_FALSE(result);

    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextColor(Color::RED);
    result = pattern->OnThemeScopeUpdate(themeScopeId);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetOriginCaretPosition001
 * @tc.desc: test GetOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetOriginCaretPosition001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    OffsetF offset(0, 0);
    pattern->ResetOriginCaretPosition();
    bool result = pattern->GetOriginCaretPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ProcessBoundRectByTextMarquee001
 * @tc.desc: test ProcessBoundRectByTextMarquee
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessBoundRectByTextMarquee001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    RectF rect = RectF(10, 0, 0, 0);
    pattern->ProcessBoundRectByTextMarquee(rect);
    EXPECT_EQ(rect.Width(), -10);

    RectF testRect = RectF(10, 0, 0, 0);
    frameNode->GetGeometryNode()->SetContentSize({ 10, 10 });
    pattern->ProcessBoundRectByTextMarquee(testRect);
    EXPECT_EQ(testRect.Width(), 0);
}

/**
 * @tc.name: CreateModifier001
 * @tc.desc: test CreateModifier
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, CreateModifier001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetIsCustomFont(true);
    pattern->CreateModifier();
    EXPECT_TRUE(pattern->contentMod_->GetIsCustomFont());
}

/**
 * @tc.name: OnHandleAreaChanged001
 * @tc.desc: test OnHandleAreaChanged
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnHandleAreaChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. parentGlobalOffset_ is default vaule { 0, 0 } and call OnHandleAreaChanged.
     * @tc.expect: pattern->GetParentGlobalOffset() is equal to pattern->parentGlobalOffset_.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    pattern->ShowSelectOverlay();
    pattern->OnHandleAreaChanged();
    EXPECT_EQ(pattern->GetParentGlobalOffset(), pattern->parentGlobalOffset_);

    /**
     * @tc.steps: step2. parentGlobalOffset_ is { 1, 1 } and call OnHandleAreaChanged.
     * @tc.expect: pattern->GetParentGlobalOffset() is equal to pattern->parentGlobalOffset_.
     */
    pattern->parentGlobalOffset_ = { 1, 1 };
    pattern->OnHandleAreaChanged();
    EXPECT_EQ(pattern->GetParentGlobalOffset(), pattern->parentGlobalOffset_);
}

/**
 * @tc.name: SetTextDetectEnable001
 * @tc.desc: test SetTextDetectEnable
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetTextDetectEnable001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    bool enable = false;
    pattern->SetTextDetectEnable(enable);
    EXPECT_FALSE(pattern->textDetectEnable_);

    pattern->textDetectEnable_ = true;
    pattern->SetTextDetectEnable(enable);
    EXPECT_FALSE(pattern->textDetectEnable_);
}

/**
 * @tc.name: FireOnMarqueeStateChange001
 * @tc.desc: test FireOnMarqueeStateChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, FireOnMarqueeStateChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    TextMarqueeState state = TextMarqueeState::FINISH;
    pattern->isMarqueeRunning_ = true;
    pattern->FireOnMarqueeStateChange(state);
    EXPECT_FALSE(pattern->isMarqueeRunning_);
}

/**
 * @tc.name: HandleSelectionChange001
 * @tc.desc: test HandleSelectionChange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionChange001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->unicode = 1;
    pattern->spans_.push_back(spanItem);

    int32_t start = 1;
    int32_t end = 1;
    pattern->HandleSelectionChange(start, end);
    EXPECT_EQ(pattern->textSelector_.GetStart(), start);
    EXPECT_EQ(pattern->textSelector_.GetEnd(), end);
}

/**
 * @tc.name: GetBuilderResultObject001
 * @tc.desc: test GetBuilderResultObject
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetBuilderResultObject001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    int32_t index = -1;
    int32_t start = 0;
    int32_t end = 0;
    ResultObject resultObject;
    ResultObject result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(spanItem);
    pattern->spans_.push_back(spanItem);
    index = 1;
    start = -100;
    end = -100;
    result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);

    start = 100;
    result = pattern->GetBuilderResultObject(frameNode, index, start, end);
    EXPECT_EQ(result.spanPosition.spanIndex, resultObject.spanPosition.spanIndex);
}

/**
 * @tc.name: ProcessMarqueeVisibleAreaCallback001
 * @tc.desc: test TextPattern ProcessMarqueeVisibleAreaCallback
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, ProcessMarqueeVisibleAreaCallback001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);

    /**
     * @tc.steps: visible is 0, ratio is 0, raceAnimation_ is null.
     * @tc.expected: marqueeState_ is default value MarqueeState::IDLE.
     */
    RefPtr<TextContentModifier> contentMod =
        AceType::MakeRefPtr<TextContentModifier>(std::optional<TextStyle>(TextStyle()));
    pattern->contentMod_ = contentMod;
    EXPECT_NE(pattern->contentMod_, nullptr);
    pattern->ProcessMarqueeVisibleAreaCallback();
    EXPECT_EQ(pattern->contentMod_->marqueeState_, MarqueeState::IDLE);
}

/**
 * @tc.name: AddChildSpanItem001
 * @tc.desc: test AddChildSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, AddChildSpanItem001, TestSize.Level1)
{
    /**
     * @tc.steps: set isOverlayNode_ to true and call AddChildSpanItem.
     * @tc.expected: spans_ is null.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->SetIsOverlayNode(true);
    pattern->AddChildSpanItem(frameNode);
    EXPECT_EQ(pattern->spans_.size(), 0);
}

/**
 * @tc.name: OnColorConfigurationUpdate001
 * @tc.desc: test OnColorConfigurationUpdate
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, OnColorConfigurationUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: colorModeChange_ is default value false and call OnColorConfigurationUpdate.
     * @tc.expected: colorModeChange_ is true.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    pattern->OnColorConfigurationUpdate();
    EXPECT_TRUE(pattern->magnifierController_->colorModeChange_);
}

/**
 * @tc.name: RecordOriginCaretPosition001
 * @tc.desc: test RecordOriginCaretPosition
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, RecordOriginCaretPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: offset is negative value and call RecordOriginCaretPosition.
     * @tc.expected: result is false.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    OffsetF offset(-1, -1);
    bool result = pattern->RecordOriginCaretPosition(offset);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: SetResponseRegion001
 * @tc.desc: test SetResponseRegion
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetResponseRegion001, TestSize.Level1)
{
    /**
     * @tc.steps: set isUserSetResponseRegion_ to true and call SetResponseRegion.
     * @tc.expected: isUserSetResponseRegion_ is true and SetResponseRegion function return.
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("test", 0, pattern);
    SizeF frameSize(0, 0);
    SizeF boundsSize(0, 0);
    pattern->SetIsUserSetResponseRegion(true);
    pattern->SetResponseRegion(frameSize, boundsSize);
    EXPECT_TRUE(pattern->isUserSetResponseRegion_);
}

/**
 * @tc.name: GetStartAndEnd001
 * @tc.desc: test TextPattern GetStartAndEnd
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetStartAndEnd001, TestSize.Level1)
{
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    int32_t StartIndex = 0;
    int32_t EndIndex = 3;
    auto urlSpan = AceType::MakeRefPtr<UrlSpan>("test", StartIndex, EndIndex);
    urlSpan->AddUrlStyle(spanItem1);
    auto [frameNode, pattern] = Init();
    pattern->styledString_ = AceType::MakeRefPtr<MutableSpanString>(u"test");
    pattern->styledString_->text_ = u"testText";
    pattern->styledString_->AddSpan(urlSpan);

    int32_t start = 0;
    auto ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, StartIndex);
    EXPECT_EQ(ret.second, EndIndex);

    start = -1;
    ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, 0);
    EXPECT_EQ(ret.second, 0);

    start = 10;
    ret = pattern->GetStartAndEnd(start, spanItem1);
    EXPECT_EQ(ret.first, 0);
    EXPECT_EQ(ret.second, 0);
}

/**
 * @tc.name: EncodeTlvSpanItems002
 * @tc.desc: test TextPattern EncodeTlvSpanItems
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, EncodeTlvSpanItems002, TestSize.Level1)
{
    int32_t cursor = 1;
    auto [frameNode, pattern] = Init();
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->spanItemType = NG::SpanItemType::SYMBOL;
    int32_t textSelectorLength = pattern->textSelector_.GetTextEnd() - pattern->textSelector_.GetTextStart();
    
    std::string pasteData;
    std::vector<uint8_t> buff;

    spanItem->position = pattern->textSelector_.GetTextEnd() + 1;
    spanItem->length = textSelectorLength + 2;
    pattern->spans_.push_back(spanItem);
    pattern->EncodeTlvSpanItems(pasteData, buff);
    int32_t size = TLVUtil::ReadInt32(buff, cursor);
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: BeforeSyncGeometryProperties002
 * @tc.desc: test TextPattern BeforeSyncGeometryProperties
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, BeforeSyncGeometryProperties002, TestSize.Level1)
{
    DirtySwapConfig config;
    int32_t test = 1;
    auto [frameNode, pattern] = Init();
    std::function<void()> callback = [&]() {
        test++;
        return;
    };
    pattern->afterLayoutCallback_ = callback;
    pattern->BeforeSyncGeometryProperties(config);
    EXPECT_EQ(test, 2);
}

/**
 * @tc.name: HandleKeyEvent001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3. test the enter key is or not legal.
     * @tc.expect: the key is legal result is true.
     */
    KeyEvent event;
    event.pressedCodes.push_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.push_back(KeyCode::KEY_A);
    event.code = KeyCode::KEY_A;
    event.action = KeyAction::DOWN;
    EXPECT_TRUE(textPattern->HandleKeyEvent(event));
}

/**
 * @tc.name: HandleSelectionUp001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionUp001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3.set the line count is 1.
     * @tc.expect: the key is legal result is true.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    textPattern->HandleSelectionUp();
    EXPECT_EQ(textPattern->pManager_->GetLineCount(), 1);
}

/**
 * @tc.name: HandleSelectionDown001
 * @tc.desc:  test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSelectionDown001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2. Initialize textModelNG and textSelector_.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textPattern->copyOption_ = CopyOptions::InApp;
    textPattern->textSelector_.Update(2, 6);

    /**
     * @tc.steps: step3.set the line count is 1.
     * @tc.expect: the key is legal result is true.
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph, .start = 0, .end = 100 });
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(1));
    textPattern->HandleSelectionDown();
    EXPECT_EQ(textPattern->pManager_->GetLineCount(), 1);
}

/**
 * @tc.name: SetTextSelectableMode001
 * @tc.desc: test DeleteRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SetTextSelectableMode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and pattern.
     */
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);

    /**
     * @tc.steps: step2.Set the selectable mode to SELECTABLE_FOCUSABLE.
     * @tc.expected: The focusable value of focusHub is true.
     */
    TextModelNG textModelNG;
    textModelNG.Create(u"123456789");
    textModelNG.SetCopyOption(CopyOptions::InApp);
    TextSelectableMode value = TextSelectableMode::SELECTABLE_FOCUSABLE;
    textPattern->SetTextSelectableMode(value);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    EXPECT_TRUE(focusHub->focusable_);
}

/**
 * @tc.name: GetTextHeight001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, GetTextHeight001, TestSize.Level1)
{
   /**
     * @tc.steps: step1. Create a textFrameNode and  textPattern.
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(textFrameNode, nullptr);
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    ASSERT_NE(textPattern->pManager_, nullptr);

    auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    /**
     * @tc.steps: step2. Set GetLineCount return value of 1.
     */
    auto paragraph1 = MockParagraph::GetOrCreateMockParagraph();
    auto paragraph2 = MockParagraph::GetOrCreateMockParagraph();
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph1, .start = 0, .end = 2 });
    textPattern->pManager_->AddParagraph({ .paragraph = paragraph2, .start = 2, .end = 4 });
    EXPECT_CALL(*paragraph1, GetLineCount()).WillRepeatedly(Return(1));
    EXPECT_CALL(*paragraph2, GetLineCount()).WillRepeatedly(Return(1));
    
    /**
     * @tc.steps: step3. UpdateMaxLines of lines in the layout property to 3
     * @tc.expected: The result of GetTextHeight is 0.0.
     */
    layoutProperty->UpdateMaxLines(3);
    double result = textPattern->GetTextHeight(1, true);
    EXPECT_EQ(result, 0.0);
    result = textPattern->GetTextHeight(3, true);
    EXPECT_EQ(result, 0.0);
}

/**
 * @tc.name: HandleSpanLongPressEvent001
 * @tc.desc: test TextPattern HandleSpanLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, HandleSpanLongPressEvent001, TestSize.Level1)
{
    auto [frameNode, pattern] = Init();
    GestureEvent info;
    info.localLocation_ = Offset(15.0f, 15.0f);
    pattern->contentRect_ = RectF { 0, 0, 30, 30 };
    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    RefPtr<SpanItem> spanItem2 = AceType::MakeRefPtr<SpanItem>();
    pattern->spans_.push_back(nullptr);
    pattern->spans_.push_back(spanItem1);
    pattern->spans_.push_back(spanItem2);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();

    /**
     * @tc.steps: Cover the branch when isInRegion is true, spans_.empty() is false and pManager_has value.
     * @tc.expected: spans_ has value, isInRegion is true.
     */
    pattern->HandleSpanLongPressEvent(info);
    auto localLocation = info.GetLocalLocation();
    bool isInRegion = pattern->contentRect_.IsInRegion(
        PointF(static_cast<float>(localLocation.GetX()), static_cast<float>(localLocation.GetY())));
    bool isSpansEmpty = pattern->spans_.empty();
    EXPECT_TRUE(isInRegion);
    EXPECT_FALSE(isSpansEmpty);
}
} // namespace OHOS::Ace::NG