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
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#undef private
#undef protected

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
void onclickFunc(const BaseEventInfo* info) {};
const std::string FONT_SIZE = "fontSize";
} // namespace

class SpanPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SpanPatternTestNg::SetUpTestCase() {}
void SpanPatternTestNg::TearDownTestCase() {}
void SpanPatternTestNg::SetUp() {}
void SpanPatternTestNg::TearDown() {}

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
HWTEST_F(SpanPatternTestNg, SpanFrameNodeCreator001, TestSize.Level1)
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
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W100);
    spanModelNG.SetFontWeight(FontWeight::REGULAR);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W400);
    spanModelNG.SetFontWeight(FontWeight::NORMAL);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W400);
    spanModelNG.SetFontWeight(FontWeight::MEDIUM);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W500);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W700);
    spanModelNG.SetFontWeight(FontWeight::BOLDER);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W900);
    spanModelNG.SetFontWeight(FontWeight::W100);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W100);
    spanModelNG.SetOnClick(onclickFunc);
}

/**
 * @tc.name: SpanItemToJsonValue001
 * @tc.desc: Test SpanItem ToJsonValue when fontStyle is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanItemToJsonValue001, TestSize.Level1)
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
HWTEST_F(SpanPatternTestNg, SpanItemToJsonValue002, TestSize.Level1)
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
    EXPECT_NE(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode001
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when span node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeGetOrCreateSpanNode001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = spanNode->GetOrCreateSpanNode(-1);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode002
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when span node is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeGetOrCreateSpanNode002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = spanNode->GetOrCreateSpanNode(1);
    EXPECT_NE(node, nullptr);
    node = spanNode->GetOrCreateSpanNode(1);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeGetOrCreateSpanNode003
 * @tc.desc: Test SpanNode GetOrCreateSpanNode when spannode is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeGetOrCreateSpanNode003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    ElementRegister::GetInstance()->AddUINode(node);
    node = spanNode->GetOrCreateSpanNode(1);
    EXPECT_NE(node, nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph001
 * @tc.desc: Test SpanNode MountToParagraph when parent is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeMountToParagraph001, TestSize.Level1)
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
HWTEST_F(SpanPatternTestNg, SpanNodeMountToParagraph002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph003
 * @tc.desc: Test SpanNode MountToParagraph when parent is FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeMountToParagraph003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph004
 * @tc.desc: Test SpanNode MountToParagraph when textPattern is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeMountToParagraph004, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeMountToParagraph005
 * @tc.desc: Test SpanNode MountToParagraph when parent is CustomNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeMountToParagraph005, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = TestNode::CreateTestNode(1);
    spanNode->SetParent(node);
    spanNode->MountToParagraph();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty001
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeRequestTextFlushDirty001, TestSize.Level1)
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
HWTEST_F(SpanPatternTestNg, SpanNodeRequestTextFlushDirty002, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = AceType::MakeRefPtr<SpanNode>(1);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty003
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeRequestTextFlushDirty003, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty004
 * @tc.desc: Test SpanNode RequestTextFlushDirty when TextPattern is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeRequestTextFlushDirty004, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto node = FrameNode::CreateFrameNode("Test", 1, pattern);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanNodeRequestTextFlushDirty005
 * @tc.desc: Test SpanNode RequestTextFlushDirty when parent is CustomNode.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeRequestTextFlushDirty005, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto node = TestNode::CreateTestNode(1);
    spanNode->SetParent(node);
    spanNode->RequestTextFlushDirty();
    EXPECT_NE(spanNode->GetParent(), nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph001
 * @tc.desc: Test SpanItem UpdateParagraph when fontStyle is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanItemUpdateParagraph001, TestSize.Level1)
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
    EXPECT_NE(spanNode->spanItem_->fontStyle, nullptr);
}

/**
 * @tc.name: SpanItemUpdateParagraph002
 * @tc.desc: Test SpanItem UpdateParagraph when fontStyle is nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanItemUpdateParagraph002, TestSize.Level1)
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
HWTEST_F(SpanPatternTestNg, SpanItemUpdateParagraph003, TestSize.Level1)
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
HWTEST_F(SpanPatternTestNg, SpanItemUpdateParagraph004, TestSize.Level1)
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
 * @tc.name: SpanNodeUpdateParagraph001
 * @tc.desc: Test SpanNode UpdateContent when content is not empty.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanNodeUpdateParagraph001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto json = std::make_unique<JsonValue>();
    spanNode->spanItem_->content = "test";
    spanNode->spanItem_->fontStyle = nullptr;
    spanNode->UpdateContent("test");
    EXPECT_EQ(spanNode->spanItem_->fontStyle, nullptr);
}
} // namespace OHOS::Ace::NG
