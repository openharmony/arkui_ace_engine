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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "text_base.h"

#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/typed_text.h"
#define private public
#define protected public
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#undef protected
#undef private


namespace OHOS::Ace::NG {

namespace {} // namespace

class TypedTextTestNg : public TextBases {
public:
};

class TextFieldPatternNg : public TextBases {
public:
};

class TextPatternNg : public TextBases {
public:
};

/**
 * @tc.name: GetUTF8OneCharacterSize
 * @tc.desc: Test GetUTF8OneCharacterSize.
 * @tc.type: FUNC
 */
HWTEST_F(TypedTextTestNg, GetUTF8OneCharacterSize, TestSize.Level1)
{
    /**
     * @tc.steps: step1. The CharacterSize is 0
     */
    uint8_t size = TypedText::GetUTF8OneCharacterSize(nullptr);
    EXPECT_EQ(0, size);

    /**
     * @tc.steps: step2. The CharacterSize is 1
     */
    size = TypedText::GetUTF8OneCharacterSize("A");
    EXPECT_EQ(1, size);

    /**
     * @tc.steps: step3. The CharacterSize is 2
     */
    size = TypedText::GetUTF8OneCharacterSize("Č");
    EXPECT_EQ(2, size);

    /**
     * @tc.steps: step4. The CharacterSize is 3
     */
    size = TypedText::GetUTF8OneCharacterSize("宝");
    EXPECT_EQ(3, size);

    /**
     * @tc.steps: step5. The CharacterSize is 4
     */
    size = TypedText::GetUTF8OneCharacterSize("😀");
    EXPECT_EQ(4, size);
}

/**
 * @tc.name: IsEmoji
 * @tc.desc: Test IsEmoji.
 * @tc.type: FUNC
 */
HWTEST_F(TypedTextTestNg, IsEmoji, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Miscellaneous symbols and symbol fonts
     */
    bool isEmoji = false;
    isEmoji = TypedText::IsEmoji(8235);
    EXPECT_TRUE(isEmoji);
    isEmoji = TypedText::IsEmoji(8287);
    EXPECT_TRUE(isEmoji);

    /**
     * @tc.steps: step2. Area occupied by punctuation, Alphabetic symbol
     */
    isEmoji = TypedText::IsEmoji(9728);
    EXPECT_TRUE(isEmoji);
    isEmoji = TypedText::IsEmoji(10175);
    EXPECT_TRUE(isEmoji);

    /**
     * @tc.steps: step3. Arrow B,Chinese symbols
     */
    isEmoji = TypedText::IsEmoji(12349);
    EXPECT_TRUE(isEmoji);
    isEmoji = TypedText::IsEmoji(15600);
    EXPECT_FALSE(isEmoji);
    isEmoji = TypedText::IsEmoji(26515);
    EXPECT_FALSE(isEmoji);
    isEmoji = TypedText::IsEmoji(20000);
    EXPECT_FALSE(isEmoji);
    isEmoji = TypedText::IsEmoji(35487);
    EXPECT_FALSE(isEmoji);

    /**
     * @tc.steps: step4. High and low substitution reserved area, Private reserved area
     */
    isEmoji = TypedText::IsEmoji(68452);
    EXPECT_TRUE(isEmoji);
    isEmoji = TypedText::IsEmoji(96457);
    EXPECT_TRUE(isEmoji);
}

/**
 * @tc.name: GetUTF8Next
 * @tc.desc: Test GetUTF8Next.
 * @tc.type: FUNC
 */
HWTEST_F(TypedTextTestNg, GetUTF8Next, TestSize.Level1)
{
    const char* text = nullptr;
    uint32_t i = 0;
    uint32_t j = 0;

    /**
     * @tc.steps: step1. The CharacterSize is 0
     */
    TypedText::GetUTF8Next(text, i, j);
    EXPECT_EQ(j, 0);

    /**
     * @tc.steps: step2. The CharacterSize is 1
     */
    text = "A";
    TypedText::GetUTF8Next(text, i, j);
    EXPECT_EQ(j, 1);

    /**
     * @tc.steps: step3. The CharacterSize is 2
     */
    text = "Č";
    TypedText::GetUTF8Next(text, i, j);
    EXPECT_EQ(j, 2);

    /**
     * @tc.steps: step4. The CharacterSize is 3
     */
    text = "宝";
    TypedText::GetUTF8Next(text, i, j);
    EXPECT_EQ(j, 3);

    /**
     * @tc.steps: step5. The CharacterSize is 4
     */
    text = "😀";
    TypedText::GetUTF8Next(text, i, j);
    EXPECT_EQ(j, 4);
}

/**
 * @tc.name: TextFieldDeleteRange001
 * @tc.desc: test DeleteRange
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange001, TestSize.Level1)
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
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange002, TestSize.Level1)
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
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange003, TestSize.Level1)
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
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange004, TestSize.Level1)
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
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange005, TestSize.Level1)
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
HWTEST_F(TextFieldPatternNg, TextFieldDeleteRange006, TestSize.Level1)
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
 * @tc.name: TextPatternHandleAISpanHoverEvent001
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent001, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    textPattern.isHover_ = true;
    textPattern.textDetectEnable_ = true;
    AISpan span;
    span.start = 10;
    span.end = 20;
    span.content = "content";
    span.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = span;
    RefPtr<MockParagraph> mockParagraph = AIWriteAdapter::MakeRefPtr<MockParagraph>();
    auto paragraphManager = AceType::MakeRefPtr<ParagraphManager>();
    textPattern.pManager_ = paragraphManager;
    std::list<ParagraphManager::ParagraphInfo> paragraphs;
    ParagraphManager::ParagraphInfo paragraphInfo;
    paragraphInfo.start = 5;
    paragraphInfo.end = 15;
    paragraphInfo.paragraph = mockParagraph;
    paragraphs.push_back(paragraphInfo);
    paragraphManager->SetParagraphs(paragraphs);
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    textPattern.dataDetectorAdapter_->aiSpanRects_.clear();
    const std::string tag = "xyz";
    int32_t nodeId = 4;
    RefPtr<Pattern> pattern = AIWriteAdapter::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;
    RefPtr<FrameNode> frameNodeRef = AIWriteAdapter::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    textPattern.frameNode_ = frameNodeRef;
    std::vector<RectF> rects { RectF(5, 5, 10, 10) };
    EXPECT_CALL(*mockParagraph, GetRectsForRange(_, _, _)).WillRepeatedly(SetArgReferee<2>(rects));
    EXPECT_CALL(*mockParagraph, GetHeight()).WillRepeatedly(Return(0));
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_FALSE(textPattern.dataDetectorAdapter_->aiSpanRects_.empty());
    EXPECT_EQ(MouseFormat::DEFAULT, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent002
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent002, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.textDetectEnable_ = true;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    AISpan span;
    span.start = 10;
    span.end = 20;
    span.content = "content";
    span.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = span;
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::EAST, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent003
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent003, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.isHover_ = true;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::EAST, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent004
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent004, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::EAST, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent005
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent005, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    textPattern.isHover_ = true;
    textPattern.textDetectEnable_ = true;
    AISpan spanOne;
    spanOne.start = 10;
    spanOne.end = 20;
    spanOne.content = "content";
    spanOne.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = spanOne;
    AISpan spanTwo;
    spanTwo.start = 20;
    spanTwo.end = 30;
    spanTwo.content = "text";
    spanTwo.type = TextDataDetectType::DATE_TIME;
    textPattern.dataDetectorAdapter_->aiSpanMap_[1] = spanTwo;
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    RectF rectF = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    textPattern.dataDetectorAdapter_->aiSpanRects_.emplace_back(rectF);
    const std::string tag = "xyz";
    int32_t nodeId = 4;
    RefPtr<Pattern> pattern = AIWriteAdapter::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;
    RefPtr<FrameNode> frameNodeRef = AIWriteAdapter::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    textPattern.frameNode_ = frameNodeRef;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_FALSE(textPattern.dataDetectorAdapter_->aiSpanRects_.empty());
    EXPECT_EQ(MouseFormat::DEFAULT, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent006
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent006, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.currentMouseStyle_ = MouseFormat::EAST;
    textPattern.isHover_ = true;
    textPattern.textDetectEnable_ = true;
    AISpan spanOne;
    spanOne.start = 10;
    spanOne.end = 20;
    spanOne.content = "content";
    spanOne.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = spanOne;
    AISpan spanTwo;
    spanTwo.start = 20;
    spanTwo.end = 30;
    spanTwo.content = "text";
    spanTwo.type = TextDataDetectType::DATE_TIME;
    textPattern.dataDetectorAdapter_->aiSpanMap_[1] = spanTwo;
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    RectF rectF = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    textPattern.dataDetectorAdapter_->aiSpanRects_.emplace_back(rectF);
    textPattern.contentRect_ = rectF;
    Offset offset = Offset(100.0, 100.0);
    info.localLocation_ = offset;
    const std::string tag = "xyz";
    int32_t nodeId = 4;
    RefPtr<Pattern> pattern = AIWriteAdapter::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;
    RefPtr<FrameNode> frameNodeRef = AIWriteAdapter::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    textPattern.frameNode_ = frameNodeRef;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::HAND_POINTING, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent007
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent007, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.currentMouseStyle_ = MouseFormat::HAND_POINTING;
    textPattern.isHover_ = true;
    textPattern.textDetectEnable_ = true;
    AISpan spanOne;
    spanOne.start = 10;
    spanOne.end = 20;
    spanOne.content = "content";
    spanOne.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = spanOne;
    AISpan spanTwo;
    spanTwo.start = 20;
    spanTwo.end = 30;
    spanTwo.content = "text";
    spanTwo.type = TextDataDetectType::DATE_TIME;
    textPattern.dataDetectorAdapter_->aiSpanMap_[1] = spanTwo;
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    RectF rectF = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    textPattern.dataDetectorAdapter_->aiSpanRects_.emplace_back(rectF);
    textPattern.contentRect_ = rectF;
    Offset offset = Offset(100.0, 100.0);
    info.localLocation_ = offset;
    const std::string tag = "xyz";
    int32_t nodeId = 4;
    RefPtr<Pattern> pattern = AIWriteAdapter::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;
    RefPtr<FrameNode> frameNodeRef = AIWriteAdapter::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    textPattern.frameNode_ = frameNodeRef;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::HAND_POINTING, textPattern.currentMouseStyle_);
}

/**
 * @tc.name: TextPatternHandleAISpanHoverEvent008
 * @tc.desc: test HandleAISpanHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TextPatternNg, TextPatternHandleAISpanHoverEvent008, TestSize.Level1)
{
    TextPattern textPattern;
    MouseInfo info;
    info.action_ = MouseAction::MOVE;
    textPattern.currentMouseStyle_ = MouseFormat::DEFAULT;
    textPattern.isHover_ = true;
    textPattern.textDetectEnable_ = true;
    AISpan spanOne;
    spanOne.start = 10;
    spanOne.end = 20;
    spanOne.content = "content";
    spanOne.type = TextDataDetectType::PHONE_NUMBER;
    textPattern.dataDetectorAdapter_->aiSpanMap_[0] = spanOne;
    AISpan spanTwo;
    spanTwo.start = 20;
    spanTwo.end = 30;
    spanTwo.content = "text";
    spanTwo.type = TextDataDetectType::DATE_TIME;
    textPattern.dataDetectorAdapter_->aiSpanMap_[1] = spanTwo;
    RefPtr<SpanItem> spanItem = AIWriteAdapter::MakeRefPtr<SpanItem>();
    spanItem->content = u"example content";
    spanItem->spanItemType = SpanItemType::IMAGE;
    textPattern.spans_.push_back(spanItem);
    RectF rectF = RectF(20.0f, 30.0f, 120.0f, 180.0f);
    textPattern.dataDetectorAdapter_->aiSpanRects_.emplace_back(rectF);
    const std::string tag = "xyz";
    int32_t nodeId = 4;
    RefPtr<Pattern> pattern = AIWriteAdapter::MakeRefPtr<Pattern>();
    bool isRoot = false;
    bool isLayoutNode = false;
    RefPtr<FrameNode> frameNodeRef = AIWriteAdapter::MakeRefPtr<FrameNode>(tag, nodeId, pattern, isRoot, isLayoutNode);
    textPattern.frameNode_ = frameNodeRef;
    textPattern.HandleAISpanHoverEvent(info);
    EXPECT_EQ(MouseFormat::DEFAULT, textPattern.currentMouseStyle_);
}
} // namespace OHOS::Ace::NG