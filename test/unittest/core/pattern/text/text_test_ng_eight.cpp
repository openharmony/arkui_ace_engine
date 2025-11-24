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

class TextTestNgEight : public TextBases {
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
HWTEST_F(TextTestNgEight, SpanItemUpdateParagraph007, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, SpanNodeUpdateTextStyle001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, UpdateTextStyleForAISpan002, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, SpanNodeGetSpanResultObject001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, SpanNodeGetSpanResultObject002, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, ToJsonValue007, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextDragOverlayModifierTestNG001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextDragOverlayModifierTestNG002, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange002, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange003, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange004, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange005, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, TextFieldDeleteRange006, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleClickEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    GestureEvent info;
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
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
HWTEST_F(TextTestNgEight, HandleUrlClick001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleSingleClickEvent001, TestSize.Level1)
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

    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
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
HWTEST_F(TextTestNgEight, HandleClickOnTextAndSpan001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, CheckClickedOnSpanOrText001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, CalculateClickedSpanPosition001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, CheckAndClick001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, ClickAISpan001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, OnDragEnd001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, OnWindowHide001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, SetOnClickMenu001, TestSize.Level1)
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
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
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
HWTEST_F(TextTestNgEight, ShowAIEntityMenu001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, InitMouseEvent001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);

    auto host = pattern->GetHost();
    auto eventHub = host->GetEventHub<EventHub>();
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
HWTEST_F(TextTestNgEight, AddIsFocusActiveUpdateEvent001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, RecoverCopyOption001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, InitCopyOption001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleMouseEvent001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, OnDragEndNoChild001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleOnSelect001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleMouseLeftReleaseAction001, TestSize.Level1)
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
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
    pattern->dataDetectorAdapter_->hasClickedAISpan_ = true;
    pattern->HandleMouseLeftReleaseAction(info, offset);
    EXPECT_FALSE(pattern->blockPress_);
}

/**
 * @tc.name: HiddenMenu001
 * @tc.desc: test TextPattern HiddenMenu
 * @tc.type: FUNC
 */
HWTEST_F(TextTestNgEight, HiddenMenu001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, CreateHandles001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, AddSubComponentInfoForSpan001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, ToTreeJson001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, HandleMouseLeftReleaseAction002, TestSize.Level1)
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
    ASSERT_NE(pattern->GetDataDetectorAdapter(), nullptr);
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
HWTEST_F(TextTestNgEight, OnDragMove001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, GetThumbnailCallback001, TestSize.Level1)
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
    textFrameNode->GetEventHub<EventHub>()->SetOnDragStart(
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
HWTEST_F(TextTestNgEight, GetSubComponentInfos001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, InitSpanItem001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, GetSubComponentInfosForSpans001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, GetSymbolSpanResultObject001, TestSize.Level1)
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
HWTEST_F(TextTestNgEight, UpdateSelectOverlayOrCreate001, TestSize.Level1)
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
} // namespace OHOS::Ace::NG