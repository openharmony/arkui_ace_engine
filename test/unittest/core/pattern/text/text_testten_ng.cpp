/*
 * Copyright (c) 2024-2024 Huawei Device Co., Ltd.
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

#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

namespace OHOS::Ace::NG {

namespace {
const std::string IMAGE_ICON = "app.media.icon";

} // namespace

class TextFieldTenPatternNg : public TextBases {
public:
};


/**
 * @tc.name: SpanItemUpdateParagraph007
 * @tc.desc: Test ImageSpanItem UpdateParagraph when baselineOffset is not zero.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTenPatternNg, SpanItemUpdateParagraph007, TestSize.Level1)
{
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
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
    auto index = spanItem->UpdateParagraph(nullptr, paragraph, false, placeholderStyle);
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
} // namespace OHOS::Ace::NG