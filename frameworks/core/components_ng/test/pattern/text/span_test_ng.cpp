/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include <memory>
#include <optional>

#include "gtest/gtest.h"

#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#define private public
#define protected public
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#undef private
#undef protected
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "frameworks/core/components_ng/pattern/image/image_layout_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
void onClickFunc(const BaseEventInfo* info) {};
const std::string FONT_SIZE = "fontSize";
const std::string FONT_DEFAULT_VALUE = "{\"style\":\"FontStyle.Normal\",\"size\":\"16.00fp\",\"weight\":"
                                       "\"FontWeight.Normal\",\"family\":\"HarmonyOS Sans\"}";
const std::string FONT_EQUALS_VALUE =
    R"({"style":"FontStyle.Italic","size":"20.10px","weight":"FontWeight.Bold","family":"cursive"})";
} // namespace

class SpanTestNg : public testing::Test {};

class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

public:
    static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
    {
        auto spanNode = MakeRefPtr<TestNode>(nodeId);
        return spanNode;
    };

    bool IsAtomicNode() const override
    {
        return true;
    }

    explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
    ~TestNode() override = default;
};

/**
 * @tc.name: SpanFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanFrameNodeCreator001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    EXPECT_EQ(spanNode->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(spanNode->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(spanNode->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(spanNode->GetFontFamily(), FONT_FAMILY_VALUE);

    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    EXPECT_EQ(spanNode->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(spanNode->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(spanNode->GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(spanNode->GetLetterSpacing(), LETTER_SPACING);

    spanModelNG.SetFontWeight(FontWeight::LIGHTER);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::LIGHTER);
    spanModelNG.SetFontWeight(FontWeight::REGULAR);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::REGULAR);
    spanModelNG.SetFontWeight(FontWeight::NORMAL);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::NORMAL);
    spanModelNG.SetFontWeight(FontWeight::MEDIUM);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::MEDIUM);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::BOLD);
    spanModelNG.SetFontWeight(FontWeight::BOLDER);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::BOLDER);
    spanModelNG.SetFontWeight(FontWeight::W100);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::W100);
    spanModelNG.SetOnClick(onClickFunc);
}

/**
 * @tc.name: SpanItemToJsonValue001
 * @tc.desc: Test SpanItem ToJsonValue when fontStyle is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemToJsonValue001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->ToJsonValue(json);
    bool ret = json->Contains(FONT_SIZE);
    EXPECT_EQ(ret, false);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemToJsonValue002
 * @tc.desc: Test SpanItem ToJsonValue when fontStyle is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemToJsonValue002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = std::make_unique<FontStyle>();
    spanNode->spanItem_->ToJsonValue(json);
    bool ret = json->Contains(FONT_SIZE);
    EXPECT_EQ(ret, false);
    ASSERT_NE(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode001
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when span node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeGetOrCreateSpanNode001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = spanNode->GetOrCreateSpanNode(-1);
    ASSERT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode002
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when span node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeGetOrCreateSpanNode002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = spanNode->GetOrCreateSpanNode(1);
    ASSERT_NE(node, nullptr);
    node = spanNode->GetOrCreateSpanNode(1);
    ASSERT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode003
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when spannode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeGetOrCreateSpanNode003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    ElementRegister::GetInstance()->AddUINode(node);
    node = spanNode->GetOrCreateSpanNode(1);
    ASSERT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph001
 * @tc.desc: Test SpanNode MountToParagraph when parent is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeMountToParagraph001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    spanNode->SetParent(nullptr);
    spanNode->MountToParagraph();
    EXPECT_EQ(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph002
 * @tc.desc: Test SpanNode MountToParagraph when parent is valid.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeMountToParagraph002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph003
 * @tc.desc: Test SpanNode MountToParagraph when parent is FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeMountToParagraph003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph004
 * @tc.desc: Test SpanNode MountToParagraph when textPattern is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeMountToParagraph004, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph005
 * @tc.desc: Test SpanNode MountToParagraph when parent is CustomNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeMountToParagraph005, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = TestNode::CreateTestNode(1);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty001
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeRequestTextFlushDirty001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    spanNode->SetParent(nullptr);
    spanNode->RequestTextFlushDirty();
    EXPECT_EQ(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty002
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeRequestTextFlushDirty002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty003
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeRequestTextFlushDirty003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty004
 * @tc.desc: Test SpanNode RequestTextFlushDirty when TextPattern is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeRequestTextFlushDirty004, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty005
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is CustomNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanNodeRequestTextFlushDirty005, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = TestNode::CreateTestNode(1);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    ASSERT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph001
 * @tc.desc: Test SpanItem UpdateParagraph when fontStyle is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemUpdateParagraph001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = std::make_unique<FontStyle>();
    TextStyle textStyle;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    spanNode->spanItem_->UpdateParagraph(paragraph);
    ASSERT_NE(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph002
 * @tc.desc: Test SpanItem UpdateParagraph when fontStyle is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemUpdateParagraph002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = nullptr;
    TextStyle textStyle;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    spanNode->spanItem_->UpdateParagraph(paragraph);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph003
 * @tc.desc: Test SpanItem UpdateParagraph when Paragraph is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemUpdateParagraph003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->spanItem_->UpdateParagraph(nullptr);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph004
 * @tc.desc: Test SpanItem UpdateParagraph when children is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemUpdateParagraph004, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "";
    spanNode->spanItem_->fontStyle = nullptr;
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    spanNode->spanItem_->children.push_back(spanItem);
    TextStyle textStyle;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    spanNode->spanItem_->UpdateParagraph(paragraph);
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph005
 * @tc.desc: Test SpanItem UpdateParagraph when children is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemUpdateParagraph005, TestSize.Level1)
{
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<ImageSpanItem>();
    ASSERT_NE(spanItem, nullptr);
    TextStyle textStyle;
    ParagraphStyle paraStyle = { .direction = TextDirection::LTR,
        .align = textStyle.GetTextAlign(),
        .maxLines = textStyle.GetMaxLines(),
        .fontLocale = "zh-CN",
        .wordBreak = textStyle.GetWordBreak(),
        .textOverflow = textStyle.GetTextOverflow() };
    auto paragraph = Paragraph::Create(paraStyle, FontCollection::Current());
    ASSERT_NE(paragraph, nullptr);
    auto index = spanItem->UpdateParagraph(paragraph, 9.0, 10.0, VerticalAlign::TOP);
    index = spanItem->UpdateParagraph(paragraph, 9.0, 10.0, VerticalAlign::CENTER);
    index = spanItem->UpdateParagraph(paragraph, 9.0, 10.0, VerticalAlign::BOTTOM);
    index = spanItem->UpdateParagraph(paragraph, 9.0, 10.0, VerticalAlign::BASELINE);
    index = spanItem->UpdateParagraph(paragraph, 9.0, 10.0, VerticalAlign::NONE);
    EXPECT_EQ(index, -1);
}

/**
 * @tc.name: ImageSpanViewCreat001
 * @tc.desc: Test SpanItem UpdateParagraph when children is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, Create001, TestSize.Level1)
{
    ImageModelNG imageSpan;
    std::string bundleName;
    std::string moduleName;
    std::string src;
    RefPtr<PixelMap> pixMap = nullptr;
    imageSpan.Create(src, pixMap, bundleName, moduleName);
    ImageSpanView::SetObjectFit(ImageFit::FILL);
    ImageSpanView::SetVerticalAlign(VerticalAlign::TOP);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetImageFitValue(ImageFit::COVER), ImageFit::FILL);
    EXPECT_EQ(layoutProperty->GetVerticalAlignValue(VerticalAlign::BOTTOM), VerticalAlign::TOP);
}

/**
 * @tc.name: SpanModelSetFont001
 * @tc.desc: Test if SetFont is successful
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanModelSetFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize SpanModelNG
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);

    /**
     * @tc.steps: step2. Set Font, call SetFont
     */
    Font font;
    font.fontSize = FONT_SIZE_VALUE;
    font.fontWeight = FontWeight::BOLD;
    font.fontFamilies = FONT_FAMILY_VALUE;
    font.fontStyle = ITALIC_FONT_STYLE_VALUE;
    spanModelNG.SetFont(font);
    /**
     * @tc.steps: step3. Gets the relevant properties of the Font
     * @tc.expected: step3. Check the font value
     */
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    EXPECT_EQ(spanNode->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(spanNode->GetFontWeight().value(), FontWeight::BOLD);
    EXPECT_EQ(spanNode->GetFontFamily(), FONT_FAMILY_VALUE);
    EXPECT_EQ(spanNode->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
}

/**
 * @tc.name: SpanItemSetFont001GetFontSize
 * @tc.desc: Test if GetFont is successful
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanItemGetFont001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize SpanModelNG and SpanNode
     */
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(spanNode, nullptr);
    spanModelNG.SetFontWeight(FontWeight::NORMAL);

    /**
     * @tc.steps: step2. not set Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    EXPECT_EQ(spanNode->spanItem_->GetFont(), FONT_DEFAULT_VALUE);

    /**
     * @tc.steps: step2. set and Gets the relevant properties of the Font
     * @tc.expected: step2. Check the font value
     */
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(spanNode->spanItem_->GetFont(), FONT_EQUALS_VALUE);
}

/**
 * @tc.name: SpanDecorationStyleTest001
 * @tc.desc: test span_model_ng.cpp SetTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanDecorationStyleTest001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    spanModelNG.SetTextDecorationStyle(Ace::TextDecorationStyle::WAVY);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_EQ(spanNode->GetTextDecorationStyle(), Ace::TextDecorationStyle::WAVY);
}

/**
 * @tc.name: SpanDecorationToJsonValue001
 * @tc.desc: Test Span Decoration ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanDecorationToJsonValue001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    spanModelNG.SetTextDecoration(TextDecoration::LINE_THROUGH);
    spanModelNG.SetTextDecorationStyle(Ace::TextDecorationStyle::DOUBLE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    spanNode->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(Ace::TextDecoration::LINE_THROUGH));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == TEXT_DECORATION_COLOR_VALUE.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(Ace::TextDecorationStyle::DOUBLE));
}

/**
 * @tc.name: SpanDecorationToJsonValue002
 * @tc.desc: Test Span Decoration ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanDecorationToJsonValue002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    spanNode->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_TRUE(json->Contains("fontSize"));
    EXPECT_TRUE(json->GetValue("fontSize")->GetString() == FONT_SIZE_VALUE.ToString());
    EXPECT_TRUE(json->Contains("decoration"));
    std::string decorationStr = json->GetValue("decoration")->GetString();
    auto decorationJson = JsonUtil::ParseJsonString(decorationStr);
    ASSERT_NE(decorationJson, nullptr);
    EXPECT_TRUE(decorationJson->Contains("type"));
    EXPECT_TRUE(decorationJson->GetValue("type")->GetString() ==
                V2::ConvertWrapTextDecorationToStirng(Ace::TextDecoration::NONE));
    EXPECT_TRUE(decorationJson->Contains("color"));
    EXPECT_TRUE(decorationJson->GetValue("color")->GetString() == Color::BLACK.ColorToString());
    EXPECT_TRUE(decorationJson->Contains("style"));
    EXPECT_TRUE(decorationJson->GetValue("style")->GetString() ==
                V2::ConvertWrapTextDecorationStyleToString(Ace::TextDecorationStyle::SOLID));
}

/**
 * @tc.name: SpanDecorationToJsonValue003
 * @tc.desc: Test Span Decoration ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(SpanTestNg, SpanDecorationToJsonValue003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(spanNode, nullptr);
    auto json = JsonUtil::Create(true);
    spanNode->ToJsonValue(json);
    EXPECT_TRUE(json->Contains("content"));
    EXPECT_TRUE(json->GetValue("content")->GetString() == CREATE_VALUE);
    EXPECT_FALSE(json->Contains("decoration"));
}
} // namespace OHOS::Ace::NG
