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

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "test/mock/core/common/mock_udmf.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/style_manager.h"
#include "test/mock/base/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class RichEditorStyleManagerTest : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
};

void RichEditorStyleManagerTest::SetUp()
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

void RichEditorStyleManagerTest::TearDown()
{
    richEditorNode_ = nullptr;
    MockParagraph::TearDown();
}

void RichEditorStyleManagerTest::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToTextStyleTest001, TestSize.Level1)
{
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextColorResource(textStyle, nullptr);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToTextStyleTest002, TestSize.Level1)
{
    TextStyle textStyle;
    g_isConfigChangePerform = true;

    StyleManager::AddTextColorResource(textStyle, nullptr);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToTextStyleTest003, TestSize.Level1)
{
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    g_isConfigChangePerform = false;

    StyleManager::AddTextColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToTextStyleTest004, TestSize.Level1)
{
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    g_isConfigChangePerform = true;

    StyleManager::AddTextColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 1);

    StyleManager::AddTextColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 1);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToSpanNodeTest001, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = nullptr;
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextColorResource(spanNode, textStyle);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToSpanNodeTest002, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToSpanNodeTest003, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = nullptr;
    TextStyle textStyle;
    g_isConfigChangePerform = true;

    StyleManager::AddTextColorResource(spanNode, textStyle);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextColorResToSpanNodeTest004, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    textStyle.AddResource(StyleManager::TEXT_COLOR_KEY, colorResObj, StyleManager::TEXT_STYLE_TEXT_COLOR_UPDATER);
    g_isConfigChangePerform = true;

    StyleManager::AddTextColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 1);

    textStyle.AddResource(StyleManager::TEXT_DECORATION_COLOR_KEY, colorResObj,
        StyleManager::TEXT_STYLE_TEXT_DECORATION_COLOR_UPDATER);
    StyleManager::AddTextColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 1);
}


HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToTextStyleTest001, TestSize.Level1)
{
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextDecorationColorResource(textStyle, nullptr);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToTextStyleTest002, TestSize.Level1)
{
    TextStyle textStyle;
    g_isConfigChangePerform = true;

    StyleManager::AddTextDecorationColorResource(textStyle, nullptr);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToTextStyleTest003, TestSize.Level1)
{
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    g_isConfigChangePerform = false;

    StyleManager::AddTextDecorationColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToTextStyleTest004, TestSize.Level1)
{
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    g_isConfigChangePerform = true;

    StyleManager::AddTextDecorationColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 1);

    StyleManager::AddTextDecorationColorResource(textStyle, colorResObj);
    EXPECT_EQ(textStyle.resMap_.size(), 1);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToSpanNodeTest001, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = nullptr;
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextDecorationColorResource(spanNode, textStyle);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToSpanNodeTest002, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    TextStyle textStyle;
    g_isConfigChangePerform = false;

    StyleManager::AddTextDecorationColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 0);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToSpanNodeTest003, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = nullptr;
    TextStyle textStyle;
    g_isConfigChangePerform = true;

    StyleManager::AddTextDecorationColorResource(spanNode, textStyle);
}

HWTEST_F(RichEditorStyleManagerTest, AddTextDecorationColorResToSpanNodeTest004, TestSize.Level1)
{
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    textStyle.AddResource(StyleManager::TEXT_DECORATION_COLOR_KEY, colorResObj,
        StyleManager::TEXT_STYLE_TEXT_DECORATION_COLOR_UPDATER);
    g_isConfigChangePerform = true;

    StyleManager::AddTextDecorationColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 1);

    textStyle.AddResource(StyleManager::TEXT_COLOR_KEY, colorResObj, StyleManager::TEXT_STYLE_TEXT_COLOR_UPDATER);
    StyleManager::AddTextDecorationColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 1);
}

HWTEST_F(RichEditorStyleManagerTest, AddSymbolColorResToTextStyleTest001, TestSize.Level1) {
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
    resObjArr.push_back(std::make_pair(0, colorResObj));
    resObjArr.push_back(std::make_pair(1, colorResObj));
    resObjArr.push_back(std::make_pair(2, colorResObj));

    g_isConfigChangePerform = false;
    StyleManager::AddSymbolColorResource(textStyle, resObjArr);
    EXPECT_EQ(textStyle.resMap_.size(), 0);

    g_isConfigChangePerform = true;
    StyleManager::AddSymbolColorResource(textStyle, resObjArr);
    EXPECT_EQ(textStyle.resMap_.size(), 3);
}

HWTEST_F(RichEditorStyleManagerTest, AddSymbolColorResToSpanNodeTest001, TestSize.Level1) {
    RefPtr<SpanNode> spanNode = nullptr;
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
    resObjArr.push_back(std::make_pair(0, colorResObj));
    resObjArr.push_back(std::make_pair(1, colorResObj));
    resObjArr.push_back(std::make_pair(2, colorResObj));
    std::vector<Color> symbolColorList;
    symbolColorList.push_back(Color());
    symbolColorList.push_back(Color());
    symbolColorList.push_back(Color());

    g_isConfigChangePerform = true;
    StyleManager::AddSymbolColorResource(textStyle, resObjArr);
    textStyle.SetSymbolColorList(symbolColorList);
    EXPECT_EQ(textStyle.resMap_.size(), 3);
    EXPECT_EQ(textStyle.GetSymbolColorList().size(), 3);

    g_isConfigChangePerform = false;
    StyleManager::AddSymbolColorResource(spanNode, textStyle);

    spanNode = AceType::MakeRefPtr<SpanNode>(1);

    g_isConfigChangePerform = false;
    StyleManager::AddSymbolColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 0);

    g_isConfigChangePerform = true;
    StyleManager::AddSymbolColorResource(spanNode, textStyle);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 3);
}

HWTEST_F(RichEditorStyleManagerTest, ResUpdaterTest001, TestSize.Level1) {
    TextStyle textStyle;
    FontStyle fontStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();

    StyleManager::TEXT_COLOR_UPDATER(colorResObj, fontStyle);
    StyleManager::TEXT_STYLE_TEXT_COLOR_UPDATER(colorResObj, textStyle);
    StyleManager::TEXT_DECORATION_COLOR_UPDATER(colorResObj, fontStyle);
    StyleManager::TEXT_STYLE_TEXT_DECORATION_COLOR_UPDATER(colorResObj, textStyle);
}

HWTEST_F(RichEditorStyleManagerTest, ShadowUpdateTest001, TestSize.Level1) {
    Shadow shadow;
    g_isConfigChangePerform = false;
    shadow.UpdateColorByResourceId();

    g_isConfigChangePerform = true;
    shadow.UpdateColorByResourceId();
}

HWTEST_F(RichEditorStyleManagerTest, TextStyleUpdateTest001, TestSize.Level1) {
    TextStyle textStyle;
    g_isConfigChangePerform = false;
    textStyle.UpdateColorByResourceId();

    g_isConfigChangePerform = true;
    textStyle.UpdateColorByResourceId();
}

HWTEST_F(RichEditorStyleManagerTest, TextStyleUpdateTest002, TestSize.Level1) {
    TextStyle textStyle;
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    const auto& key = StyleManager::TEXT_COLOR_KEY;
    const auto& updater = StyleManager::TEXT_STYLE_TEXT_COLOR_UPDATER;
    textStyle.AddResource(key, colorResObj, updater);
    EXPECT_EQ(textStyle.resMap_.size(), 1);
    EXPECT_NE(textStyle.GetResource(key), nullptr);

    TextStyle textStyle1;
    textStyle1.CopyResource(textStyle);
    EXPECT_EQ(textStyle1.resMap_.size(), 1);
    EXPECT_NE(textStyle1.GetResource(key), nullptr);

    TextStyle textStyle2;
    textStyle2.AppendResource(textStyle);
    EXPECT_EQ(textStyle2.resMap_.size(), 1);
    EXPECT_NE(textStyle2.GetResource(key), nullptr);
}

HWTEST_F(RichEditorStyleManagerTest, TextStyleUpdateTest003, TestSize.Level1) {
    TextStyle textStyle;
    EXPECT_EQ(textStyle.GetSymbolColorList().size(), 0);

    auto& symbolColorList = textStyle.GetSymbolColorListRef();
    symbolColorList.push_back(Color());
    EXPECT_EQ(textStyle.GetSymbolColorList().size(), 1);
}

HWTEST_F(RichEditorStyleManagerTest, SpanNodeUpdateTest001, TestSize.Level1) {
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    g_isConfigChangePerform = false;
    spanNode->UpdateColorByResourceId();

    g_isConfigChangePerform = true;
    spanNode->UpdateColorByResourceId();
}

HWTEST_F(RichEditorStyleManagerTest, SpanNodeUpdateTest002, TestSize.Level1) {
    RefPtr<SpanNode> spanNode = AceType::MakeRefPtr<SpanNode>(1);
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    const auto& key = StyleManager::TEXT_COLOR_KEY;
    const auto& updater = StyleManager::TEXT_COLOR_UPDATER;
    spanNode->AddResource(key, colorResObj, updater);
    EXPECT_EQ(spanNode->spanItem_->fontStyle->resMap_.size(), 1);

    RefPtr<SpanNode> spanNode1 = AceType::MakeRefPtr<SpanNode>(1);
    spanNode1->CopyResource(spanNode);
    EXPECT_EQ(spanNode1->spanItem_->fontStyle->resMap_.size(), 1);

    spanNode->ReloadResources();
}

HWTEST_F(RichEditorStyleManagerTest, SpanItemUpdateTest001, TestSize.Level1) {
    RefPtr<SpanItem> spanItem = AceType::MakeRefPtr<SpanItem>();
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    const auto& key = StyleManager::TEXT_COLOR_KEY;
    const auto& updater = StyleManager::TEXT_COLOR_UPDATER;
    spanItem->AddResource(key, colorResObj, updater);
    EXPECT_EQ(spanItem->fontStyle->resMap_.size(), 1);

    RefPtr<SpanItem> spanItem1 = AceType::MakeRefPtr<SpanItem>();
    spanItem1->CopyResource(spanItem);
    EXPECT_EQ(spanItem1->fontStyle->resMap_.size(), 1);

    spanItem->ReloadResources();
}

HWTEST_F(RichEditorStyleManagerTest, FontStyleUpdateTest001, TestSize.Level1) {
    FontStyle fontStyle;
    g_isConfigChangePerform = false;
    fontStyle.UpdateColorByResourceId();

    g_isConfigChangePerform = true;
    fontStyle.UpdateColorByResourceId();
}

HWTEST_F(RichEditorStyleManagerTest, FontStyleUpdateTest002, TestSize.Level1) {
    std::unique_ptr<FontStyle> fontStyle = std::make_unique<FontStyle>();
    RefPtr<ResourceObject> colorResObj = AceType::MakeRefPtr<ResourceObject>();
    const auto& key = StyleManager::TEXT_COLOR_KEY;
    const auto& updater = StyleManager::TEXT_COLOR_UPDATER;
    fontStyle->AddResource(key, colorResObj, updater);
    EXPECT_EQ(fontStyle->resMap_.size(), 1);

    FontStyle fontStyle1;
    fontStyle1.CopyResource(fontStyle);
    EXPECT_EQ(fontStyle1.resMap_.size(), 1);

    fontStyle->ReloadResources();
    fontStyle->propTextShadow = std::vector<Shadow>();
    fontStyle->ReloadResources();
}

HWTEST_F(RichEditorStyleManagerTest, UpdatePropertyTest001, TestSize.Level1) {
    ASSERT_NE(richEditorNode_, nullptr);
    auto richEditorPattern = richEditorNode_->GetPattern<RichEditorPattern>();
    ASSERT_NE(richEditorPattern, nullptr);
    Color color = Color::BLACK;
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    value->SetValueType(ValueType::COLOR);
    value->SetValue(color);

    richEditorPattern->UpdatePropertyImpl(StyleManager::CARET_COLOR_KEY, value);
    richEditorPattern->UpdatePropertyImpl(StyleManager::SCROLL_BAR_COLOR_KEY, value);
    richEditorPattern->UpdatePropertyImpl(StyleManager::PLACEHOLDER_FONT_COLOR_KEY, value);
    richEditorPattern->UpdatePropertyImpl(StyleManager::SELECTED_BACKGROUND_COLOR_KEY, value);

    richEditorPattern->OnColorModeChange(0);
    richEditorPattern->UpdatePlaceholderFontColor(color);
}

}