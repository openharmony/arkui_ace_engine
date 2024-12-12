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

#include "text_base.h"

#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class TextTestEightNg : public TextBases {
public:
};

/**
 * @tc.name: DumpInfo001
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pattern->pManager_, nullptr);
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("Content"));
    EXPECT_FALSE(json->Contains("PaintInfo"));
    EXPECT_FALSE(json->Contains("contentRect"));
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpInfo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->pManager_ = nullptr;
    pattern->DumpInfo(json);
    EXPECT_TRUE(json->Contains("Content"));
    EXPECT_FALSE(json->Contains("PaintInfo"));
    EXPECT_FALSE(json->Contains("contentRect"));
}

/**
 * @tc.name: DumpAdvanceInfo001
 * @tc.desc: test DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpAdvanceInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->pManager_ = nullptr;
    pattern->DumpAdvanceInfo(json);
    EXPECT_FALSE(json->Contains("from TextEngine paragraphs_ info"));
    EXPECT_FALSE(json->Contains("ForegroundColor"));
    EXPECT_FALSE(json->Contains("ForegroundColorStrategy"));
}

/**
 * @tc.name: DumpAdvanceInfo002
 * @tc.desc: test DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpAdvanceInfo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pattern->pManager_, nullptr);
    SystemProperties::debugEnabled_ = true;
    pattern->DumpAdvanceInfo(json);
    EXPECT_TRUE(json->Contains("from TextEngine paragraphs_ info"));
    EXPECT_FALSE(json->Contains("ForegroundColor"));
    EXPECT_FALSE(json->Contains("ForegroundColorStrategy"));
}

/**
 * @tc.name: DumpAdvanceInfo003
 * @tc.desc: test DumpAdvanceInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpAdvanceInfo003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->pManager_ = nullptr;
    SystemProperties::debugEnabled_ = true;
    pattern->DumpAdvanceInfo(json);
    EXPECT_FALSE(json->Contains("from TextEngine paragraphs_ info"));
    EXPECT_FALSE(json->Contains("ForegroundColor"));
    EXPECT_FALSE(json->Contains("ForegroundColorStrategy"));
}

/**
 * @tc.name: OnTextGestureSelectionUpdate001
 * @tc.desc: test OnTextGestureSelectionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGestureSelectionUpdate001, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 2;
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = u"";
    pattern->OnTextGestureSelectionUpdate(start, end, touchEventInfo);
    EXPECT_TRUE(pattern->GetTextForDisplay().empty());
    EXPECT_NE(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_NE(pattern->textSelector_.GetTextEnd(), 2);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate002
 * @tc.desc: test OnTextGestureSelectionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGestureSelectionUpdate002, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 2;
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(0, 0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    pattern->magnifierController_->magnifierNodeExist_ = false;
    pattern->OnTextGestureSelectionUpdate(start, end, touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    EXPECT_TRUE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate003
 * @tc.desc: test OnTextGestureSelectionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGestureSelectionUpdate003, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 2;
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(0, 0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->magnifierController_ = nullptr;
    pattern->OnTextGestureSelectionUpdate(start, end, touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    EXPECT_TRUE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate004
 * @tc.desc: test OnTextGestureSelectionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGestureSelectionUpdate004, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 2;
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(0, 0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    pattern->textSelector_.baseOffset = 2;
    pattern->OnTextGestureSelectionUpdate(start, end, touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    EXPECT_TRUE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: OnTextGestureSelectionUpdate005
 * @tc.desc: test OnTextGestureSelectionUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGestureSelectionUpdate005, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 2;
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(1, 1));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->magnifierController_ = AceType::MakeRefPtr<MagnifierController>(pattern);
    pattern->magnifierController_->magnifierNodeExist_ = false;
    pattern->textSelector_.baseOffset = 0;
    pattern->OnTextGestureSelectionUpdate(start, end, touchEventInfo);
    EXPECT_EQ(pattern->textSelector_.GetTextStart(), 0);
    EXPECT_EQ(pattern->textSelector_.GetTextEnd(), 2);
    EXPECT_TRUE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: OnTextGenstureSelectionEnd001
 * @tc.desc: test OnTextGenstureSelectionEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGenstureSelectionEnd001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = CREATE_VALUE_W;
    pattern->SetupMagnifier();
    pattern->magnifierController_->magnifierNodeExist_ = true;
    auto secondHandle_ = pattern->textSelector_.secondHandle;
    pattern->OnTextGenstureSelectionEnd();
    EXPECT_NE(secondHandle_, pattern->textSelector_.secondHandle);
    EXPECT_FALSE(pattern->magnifierController_->magnifierNodeExist_);
}

/**
 * @tc.name: OnTextGenstureSelectionEnd002
 * @tc.desc: test OnTextGenstureSelectionEnd.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnTextGenstureSelectionEnd002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textForDisplay_ = u"";
    auto secondHandle_ = pattern->textSelector_.secondHandle;
    pattern->OnTextGenstureSelectionEnd();
    EXPECT_EQ(secondHandle_, pattern->textSelector_.secondHandle);
}

/**
 * @tc.name: GetTouchIndex001
 * @tc.desc: test GetTouchIndex.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetTouchIndex001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->UnRegisterAfterLayoutCallback();
    auto result = pattern->GetTouchIndex(secondOffset);
    EXPECT_EQ(result, 0);
}

/**
 * @tc.name: GetRectsForRange001
 * @tc.desc: test GetRectsForRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetRectsForRange001, TestSize.Level1)
{
    int32_t start = -1;
    int32_t end = 1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    auto result = pattern->GetRectsForRange(start, end, RectHeightStyle::MAX, RectWidthStyle::MAX);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange002
 * @tc.desc: test GetRectsForRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetRectsForRange002, TestSize.Level1)
{
    int32_t start = 1;
    int32_t end = -1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    auto result = pattern->GetRectsForRange(start, end, RectHeightStyle::MAX, RectWidthStyle::MAX);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange003
 * @tc.desc: test GetRectsForRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetRectsForRange003, TestSize.Level1)
{
    int32_t start = 2;
    int32_t end = 1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    auto result = pattern->GetRectsForRange(start, end, RectHeightStyle::MAX, RectWidthStyle::MAX);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetRectsForRange004
 * @tc.desc: test GetRectsForRange.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetRectsForRange004, TestSize.Level1)
{
    int32_t start = 0;
    int32_t end = 1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    auto result =
        pattern->GetRectsForRange(start, end, RectHeightStyle::INCLUDE_LINE_SPACE_MIDDLE, RectWidthStyle::TIGHT);
    EXPECT_TRUE(result.empty());
}


/**
 * @tc.name: HandleSelection001
 * @tc.desc: test HandleSelection.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleSelection001, TestSize.Level1)
{
    bool isEmojiStart = true;
    int32_t end = 0;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textSelector_.baseOffset = 0;
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->textSelector_.selectionBaseOffset = secondOffset;
    auto old = pattern->textSelector_.selectionBaseOffset;
    pattern->HandleSelection(isEmojiStart, end);
    EXPECT_NE(old, pattern->textSelector_.selectionBaseOffset);
}

/**
 * @tc.name: HandleSelection002
 * @tc.desc: test HandleSelection.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleSelection002, TestSize.Level1)
{
    bool isEmojiStart = true;
    int32_t end = 0;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textSelector_.baseOffset = -1;
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->textSelector_.selectionBaseOffset = secondOffset;
    auto old = pattern->textSelector_.selectionBaseOffset;
    pattern->HandleSelection(isEmojiStart, end);
    EXPECT_EQ(old, pattern->textSelector_.selectionBaseOffset);
}

/**
 * @tc.name: HandleSelection003
 * @tc.desc: test HandleSelection.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleSelection003, TestSize.Level1)
{
    bool isEmojiStart = true;
    int32_t end = 0;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textSelector_.baseOffset = 2;
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->textSelector_.selectionBaseOffset = secondOffset;
    auto old = pattern->textSelector_.selectionBaseOffset;
    pattern->HandleSelection(isEmojiStart, end);
    EXPECT_EQ(old, pattern->textSelector_.selectionBaseOffset);
}

/**
 * @tc.name: HandleSelection004
 * @tc.desc: test HandleSelection.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleSelection004, TestSize.Level1)
{
    bool isEmojiStart = true;
    int32_t end = -1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textSelector_.baseOffset = 0;
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->textSelector_.selectionBaseOffset = secondOffset;
    auto old = pattern->textSelector_.selectionBaseOffset;
    pattern->HandleSelection(isEmojiStart, end);
    EXPECT_EQ(old, pattern->textSelector_.selectionBaseOffset);
}

/**
 * @tc.name: HandleSelection005
 * @tc.desc: test HandleSelection.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleSelection005, TestSize.Level1)
{
    bool isEmojiStart = true;
    int32_t end = 1;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->textSelector_.baseOffset = 0;
    OffsetF secondOffset(ADAPT_OFFSETY_VALUE, ADAPT_OFFSETX_VALUE);
    pattern->textSelector_.selectionBaseOffset = secondOffset;
    auto old = pattern->textSelector_.selectionBaseOffset;
    pattern->HandleSelection(isEmojiStart, end);
    EXPECT_EQ(old, pattern->textSelector_.selectionBaseOffset);
}
} // namespace OHOS::Ace::NG
