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

#include "core/components_ng/pattern/text/span_model_ng.h"

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
    TouchLocationInfo locationInfo(0);
    pattern->OnTextGenstureSelectionEnd(locationInfo);
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
    TouchLocationInfo locationInfo(0);
    pattern->OnTextGenstureSelectionEnd(locationInfo);
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

/**
 * @tc.name: OnHover001
 * @tc.desc: test OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnHover001, TestSize.Level1)
{
    bool isHover = true;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnHover(isHover);
    EXPECT_TRUE(pipeline->eventManager_->GetMouseStyleManager()->mouseStyleNodeId_.has_value());
}

/**
 * @tc.name: OnHover002
 * @tc.desc: test OnHover.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnHover002, TestSize.Level1)
{
    bool isHover = false;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pattern->OnHover(isHover);
    EXPECT_FALSE(pipeline->eventManager_->GetMouseStyleManager()->mouseStyleNodeId_.has_value());
}

/**
 * @tc.name: HandleUrlMouseEvent001
 * @tc.desc: test HandleUrlMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleUrlMouseEvent001, TestSize.Level1)
{
    MouseInfo info;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto oldLocalLocation = info.GetLocalLocation();
    pattern->selectOverlay_->hasTransform_ = true;
    auto hasTransform = pattern->selectOverlay_->hasTransform_;
    pattern->isMousePressed_ = true;
    pattern->HandleUrlMouseEvent(info);
    auto newLocalLocation = info.GetLocalLocation();
    EXPECT_EQ(newLocalLocation, oldLocalLocation);
    EXPECT_EQ(hasTransform, pattern->selectOverlay_->hasTransform_);
}

/**
 * @tc.name: HandleUrlMouseEvent002
 * @tc.desc: test HandleUrlMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleUrlMouseEvent002, TestSize.Level1)
{
    MouseInfo info;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto oldLocalLocation = info.GetLocalLocation();
    pattern->selectOverlay_->hasTransform_ = true;
    auto hasTransform = pattern->selectOverlay_->hasTransform_;
    pattern->isMousePressed_ = false;
    pattern->HandleUrlMouseEvent(info);
    auto newLocalLocation = info.GetLocalLocation();
    EXPECT_EQ(newLocalLocation, oldLocalLocation);
    EXPECT_NE(hasTransform, pattern->selectOverlay_->hasTransform_);
}

/**
 * @tc.name: SetTextStyleDumpInfo001
 * @tc.desc: test SetTextStyleDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, SetTextStyleDumpInfo001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));
    TextStyle existingStyle;
    pattern->textStyle_ = std::move(existingStyle);
    pattern->SetTextStyleDumpInfo(json);
    EXPECT_NE(json->ToString(), "{}");
}

/**
 * @tc.name: SetTextStyleDumpInfo002
 * @tc.desc: test SetTextStyleDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, SetTextStyleDumpInfo002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    pattern->SetTextStyleDumpInfo(json);
    EXPECT_EQ(json->ToString(), "{}");
}

/**
 * @tc.name: SpanNodeDumpInfo001
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, SpanNodeDumpInfo001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    spanNode->spanItem_->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));
    TextStyle existingStyle;
    spanNode->spanItem_->textStyle_ = std::move(existingStyle);
    spanNode->tag_ = V2::SYMBOL_SPAN_ETS_TAG;
    spanNode->DumpInfo(json);
    EXPECT_TRUE(json->Contains("FontSize"));
    EXPECT_TRUE(json->Contains("SpanTextColor"));
    EXPECT_TRUE(json->Contains("SymbolColor"));
}

/**
 * @tc.name: SpanNodeDumpInfo002
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, SpanNodeDumpInfo002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    spanNode->DumpInfo(json);
    EXPECT_FALSE(json->Contains("FontSize"));
}

/**
 * @tc.name: SpanNodeDumpInfo003
 * @tc.desc: test DumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, SpanNodeDumpInfo003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE_W);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    ASSERT_NE(json, nullptr);
    spanNode->spanItem_->textStyle_->SetAdaptTextSize(Dimension(100), Dimension(10), Dimension(10));
    spanNode->spanItem_->fontStyle.reset();
    TextStyle existingStyle;
    spanNode->spanItem_->textStyle_ = std::move(existingStyle);
    spanNode->DumpInfo(json);
    EXPECT_FALSE(json->Contains("SpanTextColor"));
    EXPECT_FALSE(json->Contains("SymbolColor"));
}

/**
 * @tc.name: GetSuitableSizeLD001
 * @tc.desc: test GetSuitableSizeLD.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetSuitableSizeLD001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    std::u16string content;
    LayoutConstraintF contentConstraint;
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    double stepSize = 0.0;
    auto result = rowLayoutAlgorithm->GetSuitableSizeLD(
        textStyle, content, contentConstraint, layoutWrapper.GetRawPtr(), stepSize);
    EXPECT_FALSE(result.first);
}

/**
 * @tc.name: GetSuitableSizeLD002
 * @tc.desc: test GetSuitableSizeLD.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, GetSuitableSizeLD002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto rowLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(rowLayoutAlgorithm, nullptr);
    TextStyle textStyle;
    textStyle.adaptMaxFontSize_ = Dimension(-1);
    textStyle.adaptMinFontSize_ = Dimension(5);
    std::u16string content;
    LayoutConstraintF contentConstraint;
    RefPtr<LayoutWrapper> layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    double stepSize = 1.0;
    auto result = rowLayoutAlgorithm->GetSuitableSizeLD(
        textStyle, content, contentConstraint, layoutWrapper.GetRawPtr(), stepSize);
    EXPECT_FALSE(result.first);
}

/**
 * @tc.name: DumpParagraphsInfo001
 * @tc.desc: test DumpParagraphsInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpParagraphsInfo001, TestSize.Level1)
{
    auto& dumpLog = OHOS::Ace::DumpLog::GetInstance();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphManager::ParagraphInfo info;
    info.paragraph = nullptr;
    pattern->pManager_->AddParagraph(std::move(info));
    ASSERT_NE(pattern->pManager_, nullptr);
    pattern->DumpParagraphsInfo();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "paragraphs is empty!\n");
    EXPECT_EQ(it, dumpLog.description_.end());
    it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "paragraph: ");
    EXPECT_EQ(it, dumpLog.description_.end());
    EXPECT_NE(pattern->pManager_->paragraphs_.size(), 0);
}

/**
 * @tc.name: DumpParagraphsInfo002
 * @tc.desc: test DumpParagraphsInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, DumpParagraphsInfo002, TestSize.Level1)
{
    auto& dumpLog = OHOS::Ace::DumpLog::GetInstance();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pattern->pManager_, nullptr);
    pattern->DumpParagraphsInfo();
    auto it = std::find(dumpLog.description_.begin(), dumpLog.description_.end(), "paragraphs is empty!\n");
    EXPECT_NE(it, dumpLog.description_.end());
}

/**
 * @tc.name: AddSubComponentInfosByDataDetectorForSpan001
 * @tc.desc: test AddSubComponentInfosByDataDetectorForSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, AddSubComponentInfosByDataDetectorForSpan001, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItemChild, nullptr);
    spanItemChild->position = 100;
    spanItemChild->content = u"content";
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    AISpan span1 = {10, 20, "example content1", TextDataDetectType::EMAIL};
    AISpan span2 = {101, 20, "example content2", TextDataDetectType::EMAIL};
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(1, span1));
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(2, span2));
    pattern->AddSubComponentInfosByDataDetectorForSpan(subComponentInfos, spanItemChild);
    EXPECT_TRUE(pattern->subComponentInfos_.empty());
    EXPECT_TRUE(subComponentInfos.empty());
}

/**
 * @tc.name: AddSubComponentInfosByDataDetectorForSpan002
 * @tc.desc: test AddSubComponentInfosByDataDetectorForSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, AddSubComponentInfosByDataDetectorForSpan002, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItemChild, nullptr);
    spanItemChild->position = 50;
    spanItemChild->content = u"content";
    spanItemChild->needRemoveNewLine = true;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    AISpan span1 = {10, 50, "example content1", TextDataDetectType::EMAIL};
    AISpan span2 = {10, 20, "example content2", TextDataDetectType::EMAIL};
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(1, span1));
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(2, span2));
    pattern->AddSubComponentInfosByDataDetectorForSpan(subComponentInfos, spanItemChild);
    EXPECT_EQ(subComponentInfos.back().spanText, "example content1");
}

/**
 * @tc.name: AddSubComponentInfosByDataDetectorForSpan003
 * @tc.desc: test AddSubComponentInfosByDataDetectorForSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, AddSubComponentInfosByDataDetectorForSpan003, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItemChild, nullptr);
    spanItemChild->position = 55;
    spanItemChild->content = u"content";
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    AISpan span1 = {10, 50, "example content1", TextDataDetectType::EMAIL};
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(1, span1));
    pattern->AddSubComponentInfosByDataDetectorForSpan(subComponentInfos, spanItemChild);
    EXPECT_EQ(subComponentInfos.back().spanText, "example content1");
}

/**
 * @tc.name: AddSubComponentInfosByDataDetectorForSpan004
 * @tc.desc: test AddSubComponentInfosByDataDetectorForSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, AddSubComponentInfosByDataDetectorForSpan004, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItemChild, nullptr);
    spanItemChild->position = 55;
    spanItemChild->content = u"content";
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    AISpan span1 = {40, 60, "example content1", TextDataDetectType::EMAIL};
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(1, span1));
    CHECK_NULL_VOID(pattern->dataDetectorAdapter_);
    pattern->AddSubComponentInfosByDataDetectorForSpan(subComponentInfos, spanItemChild);
    EXPECT_EQ(subComponentInfos.back().spanText, "example content1");
}

/**
 * @tc.name: AddSubComponentInfosByDataDetectorForSpan005
 * @tc.desc: test AddSubComponentInfosByDataDetectorForSpan.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, AddSubComponentInfosByDataDetectorForSpan005, TestSize.Level1)
{
    std::vector<SubComponentInfo> subComponentInfos;
    auto spanItemChild = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItemChild, nullptr);
    spanItemChild->position = 55;
    spanItemChild->content = u"a";
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    AISpan span1 = {50, 54, "example content", TextDataDetectType::EMAIL};
    pattern->dataDetectorAdapter_->aiSpanMap_.insert(std::make_pair(1, span1));
    CHECK_NULL_VOID(pattern->dataDetectorAdapter_);
    pattern->AddSubComponentInfosByDataDetectorForSpan(subComponentInfos, spanItemChild);
    EXPECT_TRUE(pattern->subComponentInfos_.empty());
    EXPECT_TRUE(subComponentInfos.empty());
}

/**
 * @tc.name: OnDetachFromFrameNode001
 * @tc.desc: test OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnDetachFromFrameNode001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->surfaceChangedCallbackMap_.emplace(-1, [](int32_t, int32_t, int32_t, int32_t, WindowSizeChangeReason) {});
    pattern->surfaceChangedCallbackId_ = -1;
    auto beforeSize = pipeline->surfaceChangedCallbackMap_.size();
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    auto atferSize = pipeline->surfaceChangedCallbackMap_.size();
    EXPECT_NE(beforeSize, atferSize);
}

/**
 * @tc.name: OnDetachFromFrameNode002
 * @tc.desc: test OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, OnDetachFromFrameNode002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto pipeline = frameNode->GetContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->surfacePositionChangedCallbackMap_.emplace(-1, [](int32_t, int32_t) {});
    pattern->surfacePositionChangedCallbackId_ = -1;
    auto beforeSize = pipeline->surfacePositionChangedCallbackMap_.size();
    pattern->OnDetachFromFrameNode(AceType::RawPtr(frameNode));
    auto afterSize = pipeline->surfacePositionChangedCallbackMap_.size();
    EXPECT_NE(beforeSize, afterSize);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: test HandleLongPress.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, HandleLongPress001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    GestureEvent info;
    pattern->isMousePressed_ = false;
    pattern->selectOverlay_->isHandleDragging_ = true;
    pattern->HandleLongPress(info);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    auto hub = host->GetEventHub<EventHub>();
    auto gestureHub = hub->GetGestureEventHub();
    EXPECT_EQ(gestureHub, nullptr);
}

/**
 * @tc.name: ShowShadow001
 * @tc.desc: test ShowShadow.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, ShowShadow001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1 = nullptr;
    pattern->spans_.emplace_back(spanItem1);
    RefPtr<TextOverlayModifier> modifier = AceType::MakeRefPtr<TextOverlayModifier>();
    pattern->overlayMod_ = modifier;
    pattern->hasUrlSpan_ = true;
    pattern->pManager_ = AceType::MakeRefPtr<ParagraphManager>();
    ASSERT_NE(pattern->pManager_, nullptr);
    PointF point;
    Color color;
    auto res = pattern->ShowShadow(point, color);
    EXPECT_FALSE(res);
}

/**
 * @tc.name: LocalOffsetInSelectedArea001
 * @tc.desc: test LocalOffsetInSelectedArea.
 * @tc.type: FUNC
 */
HWTEST_F(TextTestEightNg, LocalOffsetInSelectedArea001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto textLayoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::UNSELECTABLE);
    pattern->copyOption_ = CopyOptions::None;
    auto res = pattern->LocalOffsetInSelectedArea(Offset(0, 0));
    EXPECT_FALSE(res);
}
} // namespace OHOS::Ace::NG
