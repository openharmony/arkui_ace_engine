/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class SpanNodeNotifyColorModeTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
};

void SpanNodeNotifyColorModeTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void SpanNodeNotifyColorModeTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange001
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange with undefined local color mode
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange001, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(100);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(true);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_EQ(containerSpanNode->GetLocalColorMode(), ColorMode::COLOR_MODE_UNDEFINED);
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange002
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange with rerenderable and force dark allowed
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange002, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(101);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(true);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_EQ(ResourceParseUtils::NeedReload(), originalNeedReload);
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange003
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange with force dark not allowed
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange003, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(102);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(false);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    ResourceParseUtils::SetNeedReload(true);
    
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_TRUE(ResourceParseUtils::NeedReload());
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange004
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange with resource manager
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange004, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(103);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(true);
    
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto updateFunc = [](const RefPtr<ResourceObject>&) {};
    containerSpanNode->AddResObj("testKey", resObj, std::move(updateFunc));
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    auto resourceMgr = containerSpanNode->GetResourceManager();
    ASSERT_NE(resourceMgr, nullptr);
    
    containerSpanNode->RemoveResObj("testKey");
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange005
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange without resource manager
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange005, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(104);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(true);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    auto resourceMgr = containerSpanNode->GetResourceManager();
    EXPECT_EQ(resourceMgr, nullptr);
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange006
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange without rerenderable
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange006, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(105);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(false);
    containerSpanNode->AllowForceDark(true);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_FALSE(containerSpanNode->CheckIsDarkMode());
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: ContainerSpanNodeNotifyColorModeChange007
 * @tc.desc: Test ContainerSpanNode NotifyColorModeChange basic flow
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, ContainerSpanNodeNotifyColorModeChange007, TestSize.Level1)
{
    auto containerSpanNode = AceType::MakeRefPtr<ContainerSpanNode>(106);
    ASSERT_NE(containerSpanNode, nullptr);
    
    containerSpanNode->SetThemeScopeId(-1);
    containerSpanNode->SetRerenderable(true);
    containerSpanNode->AllowForceDark(true);
    
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    ResourceParseUtils::SetNeedReload(false);
    
    containerSpanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::LIGHT));
    
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeUpdateSpanResource001
 * @tc.desc: Test SpanNode UpdateSpanResource without pattern
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode and set rerenderable
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(200);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step2. Create ResourceObject and call UpdateSpanResource
     * @tc.expected: No crash when pattern is nullptr
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<Color>("fontColor", resObj);
    
    EXPECT_NE(spanNode->GetSpanItem(), nullptr);
}

/**
 * @tc.name: SpanNodeUpdateSpanResource002
 * @tc.desc: Test SpanNode UpdateSpanResource with pattern but without textPattern
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode and set pattern without TextPattern
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(201);
    ASSERT_NE(spanNode, nullptr);
    auto pattern = AceType::MakeRefPtr<Pattern>();
    spanNode->GetSpanItem()->SetTextPattern(pattern);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step2. Call UpdateSpanResource with Color type
     * @tc.expected: No crash when textPattern is nullptr
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<Color>("fontColor", resObj);
    
    EXPECT_NE(spanNode->GetSpanItem(), nullptr);
}

/**
 * @tc.name: SpanNodeUpdateSpanResource003
 * @tc.desc: Test SpanNode UpdateSpanResource with rerenderable true
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and TextFrameNode
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 203, AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Create SpanNode and set textPattern
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(202);
    ASSERT_NE(spanNode, nullptr);
    spanNode->GetSpanItem()->SetTextPattern(textPattern);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step3. Call UpdateSpanResource with Color type
     * @tc.expected: Execute successfully when rerenderable is true
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<Color>("fontColor", resObj);
    
    EXPECT_TRUE(spanNode->GetRerenderable());
}

/**
 * @tc.name: SpanNodeUpdateSpanResource004
 * @tc.desc: Test SpanNode UpdateSpanResource with rerenderable false
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and TextFrameNode
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 205, AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Create SpanNode and set rerenderable false
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(204);
    ASSERT_NE(spanNode, nullptr);
    spanNode->GetSpanItem()->SetTextPattern(textPattern);
    spanNode->SetRerenderable(false);
    
    /**
     * @tc.steps: step3. Call UpdateSpanResource with Color type
     * @tc.expected: Execute successfully when rerenderable is false
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<Color>("fontColor", resObj);
    
    EXPECT_FALSE(spanNode->GetRerenderable());
}

/**
 * @tc.name: SpanNodeUpdateSpanResource005
 * @tc.desc: Test SpanNode UpdateSpanResource with CalcDimension type
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and TextFrameNode
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 207, AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Create SpanNode and set rerenderable true
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(206);
    ASSERT_NE(spanNode, nullptr);
    spanNode->GetSpanItem()->SetTextPattern(textPattern);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step3. Call UpdateSpanResource with CalcDimension type
     * @tc.expected: Execute successfully with fontSize key
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<CalcDimension>("fontSize", resObj);
    
    EXPECT_TRUE(spanNode->GetRerenderable());
}

/**
 * @tc.name: SpanNodeUpdateSpanResource006
 * @tc.desc: Test SpanNode UpdateSpanResource with FontWeight type
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and TextFrameNode
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 209, AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Create SpanNode and set rerenderable true
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(208);
    ASSERT_NE(spanNode, nullptr);
    spanNode->GetSpanItem()->SetTextPattern(textPattern);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step3. Call UpdateSpanResource with FontWeight type
     * @tc.expected: Execute successfully with fontWeight key
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<FontWeight>("fontWeight", resObj);
    
    EXPECT_TRUE(spanNode->GetRerenderable());
}

/**
 * @tc.name: SpanNodeUpdateSpanResource007
 * @tc.desc: Test SpanNode UpdateSpanResource with vector<string> type
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeUpdateSpanResource007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and TextFrameNode
     */
    auto textFrameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 211, AceType::MakeRefPtr<TextPattern>());
    auto textPattern = textFrameNode->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    
    /**
     * @tc.steps: step2. Create SpanNode and set rerenderable true
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(210);
    ASSERT_NE(spanNode, nullptr);
    spanNode->GetSpanItem()->SetTextPattern(textPattern);
    spanNode->SetRerenderable(true);
    
    /**
     * @tc.steps: step3. Call UpdateSpanResource with vector<string> type
     * @tc.expected: Execute successfully with fontFamily key
     */
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    spanNode->UpdateSpanResource<std::vector<std::string>>("fontFamily", resObj);
    
    EXPECT_TRUE(spanNode->GetRerenderable());
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange001
 * @tc.desc: Test SpanNode NotifyColorModeChange with undefined local color mode
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode and set theme scope id
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(300);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(true);
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange with DARK mode
     * @tc.expected: Local color mode is COLOR_MODE_UNDEFINED
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_EQ(spanNode->GetLocalColorMode(), ColorMode::COLOR_MODE_UNDEFINED);
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange002
 * @tc.desc: Test SpanNode NotifyColorModeChange with rerenderable and force dark allowed
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode with rerenderable and force dark allowed
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(301);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(true);
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange and verify NeedReload
     * @tc.expected: NeedReload value restored to original
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_EQ(ResourceParseUtils::NeedReload(), originalNeedReload);
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange003
 * @tc.desc: Test SpanNode NotifyColorModeChange with force dark not allowed
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode with force dark not allowed
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(302);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(false);
    
    /**
     * @tc.steps: step2. Set NeedReload to true and call NotifyColorModeChange
     * @tc.expected: NeedReload restored to original value
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    ResourceParseUtils::SetNeedReload(true);
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_TRUE(ResourceParseUtils::NeedReload());
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange004
 * @tc.desc: Test SpanNode NotifyColorModeChange with resource manager
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode and add resource object
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(303);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(true);
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("bundle", "module", 0);
    auto updateFunc = [](const RefPtr<ResourceObject>&) {};
    spanNode->AddResObj("testKey", resObj, std::move(updateFunc));
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange
     * @tc.expected: ResourceManager exists and resources reloaded
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    auto resourceMgr = spanNode->GetResourceManager();
    ASSERT_NE(resourceMgr, nullptr);
    spanNode->RemoveResObj("testKey");
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange005
 * @tc.desc: Test SpanNode NotifyColorModeChange without resource manager
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode without resource object
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(304);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(true);
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange
     * @tc.expected: ResourceManager is nullptr
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    auto resourceMgr = spanNode->GetResourceManager();
    EXPECT_EQ(resourceMgr, nullptr);
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange006
 * @tc.desc: Test SpanNode NotifyColorModeChange without rerenderable
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode with rerenderable false
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(305);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(false);
    spanNode->AllowForceDark(true);
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange
     * @tc.expected: DarkMode not set
     */
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::DARK));
    
    EXPECT_FALSE(spanNode->CheckIsDarkMode());
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanNodeNotifyColorModeChange007
 * @tc.desc: Test SpanNode NotifyColorModeChange with light mode
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanNodeNotifyColorModeChange007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanNode and set NeedReload false
     */
    auto spanNode = AceType::MakeRefPtr<SpanNode>(306);
    ASSERT_NE(spanNode, nullptr);
    spanNode->SetThemeScopeId(-1);
    spanNode->SetRerenderable(true);
    spanNode->AllowForceDark(true);
    bool originalNeedReload = ResourceParseUtils::NeedReload();
    ResourceParseUtils::SetNeedReload(false);
    
    /**
     * @tc.steps: step2. Call NotifyColorModeChange with LIGHT mode
     * @tc.expected: Execute successfully with LIGHT color mode
     */
    spanNode->NotifyColorModeChange(static_cast<uint32_t>(ColorMode::LIGHT));
    ResourceParseUtils::SetNeedReload(originalNeedReload);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph001
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with nullptr builder
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    
    /**
     * @tc.steps: step2. Call UpdateSymbolSpanParagraph with nullptr builder
     * @tc.expected: textStyle_ not set when builder is nullptr
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, nullptr, false);
    
    EXPECT_FALSE(spanItem->textStyle_.has_value());
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph002
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph without fontStyle/textLineStyle/symbolStyle
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem without styles
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = nullptr;
    spanItem->textLineStyle = nullptr;
    spanItem->symbolStyle = nullptr;
    
    /**
     * @tc.steps: step2. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount]() { callPushStyleCount++; });
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanParagraph
     * @tc.expected: PushStyle not called when styles are nullptr
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, paragraph, false);
    
    EXPECT_EQ(callPushStyleCount, 0);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph003
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with fontStyle and fontWeight
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem with fontStyle and fontWeight
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = std::make_unique<FontStyle>();
    spanItem->fontStyle->UpdateFontWeight(FontWeight::BOLD);
    spanItem->fontStyle->UpdateEnableVariableFontWeight(true);
    
    /**
     * @tc.steps: step2. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    int32_t callPopStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount]() { callPushStyleCount++; });
    EXPECT_CALL(*paragraph, PopStyle()).WillRepeatedly([&callPopStyleCount]() { callPopStyleCount++; });
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanParagraph
     * @tc.expected: PushStyle and PopStyle called once
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, paragraph, false);
    
    EXPECT_EQ(callPushStyleCount, 1);
    EXPECT_EQ(callPopStyleCount, 1);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph004
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with symbolUnicode and isDragging
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem with symbol type and unicode
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->spanItemType = SpanItemType::SYMBOL;
    spanItem->unicode = 1;
    spanItem->symbolEffectSwitch_ = true;
    spanItem->fontStyle = nullptr;
    spanItem->textLineStyle = nullptr;
    spanItem->symbolStyle = nullptr;
    
    /**
     * @tc.steps: step2. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callAddSymbolCount = 0;
    EXPECT_CALL(*paragraph, AddSymbol(_)).WillRepeatedly([&callAddSymbolCount]() { callAddSymbolCount++; });
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanParagraph with isDragging true
     * @tc.expected: AddSymbol called once and textStyle_ set
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, paragraph, true);
    
    EXPECT_EQ(callAddSymbolCount, 1);
    EXPECT_TRUE(spanItem->textStyle_.has_value());
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph005
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and FrameNode
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 400, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    /**
     * @tc.steps: step2. Create SpanItem with fontStyle and unicode
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = std::make_unique<FontStyle>();
    spanItem->unicode = 1;
    
    /**
     * @tc.steps: step3. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    int32_t callPopStyleCount = 0;
    int32_t callAddSymbolCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount]() { callPushStyleCount++; });
    EXPECT_CALL(*paragraph, PopStyle()).WillRepeatedly([&callPopStyleCount]() { callPopStyleCount++; });
    EXPECT_CALL(*paragraph, AddSymbol(_)).WillRepeatedly([&callAddSymbolCount]() { callAddSymbolCount++; });
    
    /**
     * @tc.steps: step4. Call UpdateSymbolSpanParagraph
     * @tc.expected: All paragraph methods called correctly
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(frameNode, textStyle, paragraph, false);
    
    EXPECT_EQ(callPushStyleCount, 1);
    EXPECT_EQ(callPopStyleCount, 1);
    EXPECT_EQ(callAddSymbolCount, 1);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph006
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with custom symbol font family
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem with custom symbol type
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = std::make_unique<FontStyle>();
    spanItem->symbolStyle = std::make_unique<SymbolStyle>();
    spanItem->symbolStyle->UpdateSymbolType(SymbolType::CUSTOM);
    
    /**
     * @tc.steps: step2. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount]() { callPushStyleCount++; });
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanParagraph
     * @tc.expected: PushStyle not called for CUSTOM type without font family
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, paragraph, false);
    
    EXPECT_EQ(callPushStyleCount, 0);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanParagraph007
 * @tc.desc: Test SpanItem UpdateSymbolSpanParagraph with system symbol type
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanParagraph007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem with system symbol type
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->fontStyle = std::make_unique<FontStyle>();
    spanItem->symbolStyle = std::make_unique<SymbolStyle>();
    spanItem->symbolStyle->UpdateSymbolType(SymbolType::SYSTEM);
    spanItem->unicode = 1;
    
    /**
     * @tc.steps: step2. Create mock paragraph
     */
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    ASSERT_NE(paragraph, nullptr);
    int32_t callPushStyleCount = 0;
    int32_t callPopStyleCount = 0;
    int32_t callAddSymbolCount = 0;
    EXPECT_CALL(*paragraph, PushStyle(_)).WillRepeatedly([&callPushStyleCount]() { callPushStyleCount++; });
    EXPECT_CALL(*paragraph, PopStyle()).WillRepeatedly([&callPopStyleCount]() { callPopStyleCount++; });
    EXPECT_CALL(*paragraph, AddSymbol(_)).WillRepeatedly([&callAddSymbolCount]() { callAddSymbolCount++; });
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanParagraph
     * @tc.expected: All paragraph methods called for SYSTEM type
     */
    TextStyle textStyle;
    spanItem->UpdateSymbolSpanParagraph(nullptr, textStyle, paragraph, false);
    
    EXPECT_EQ(callPushStyleCount, 1);
    EXPECT_EQ(callAddSymbolCount, 1);
    EXPECT_EQ(callPopStyleCount, 1);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanColor001
 * @tc.desc: Test SpanItem UpdateSymbolSpanColor with nullptr frameNode
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create SpanItem
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    
    /**
     * @tc.steps: step2. Create TextStyle with empty color list
     */
    TextStyle symbolSpanStyle;
    symbolSpanStyle.SetSymbolColorList(std::vector<Color>());
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanColor with nullptr frameNode
     * @tc.expected: isSymbolGlyph set to true
     */
    spanItem->UpdateSymbolSpanColor(nullptr, symbolSpanStyle);
    
    EXPECT_TRUE(symbolSpanStyle.isSymbolGlyph_);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanColor002
 * @tc.desc: Test SpanItem UpdateSymbolSpanColor with isParentText false
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanColor002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and FrameNode
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 401, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    /**
     * @tc.steps: step2. Create SpanItem with isParentText false
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->SetIsParentText(false);
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanColor
     * @tc.expected: isSymbolGlyph set to true, color list not updated
     */
    TextStyle symbolSpanStyle;
    symbolSpanStyle.SetSymbolColorList(std::vector<Color>());
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    
    EXPECT_TRUE(symbolSpanStyle.isSymbolGlyph_);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanColor003
 * @tc.desc: Test SpanItem UpdateSymbolSpanColor with non-empty color list
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanColor003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and FrameNode
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 402, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    /**
     * @tc.steps: step2. Create SpanItem with isParentText true and non-empty color list
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->SetIsParentText(true);
    TextStyle symbolSpanStyle;
    std::vector<Color> colors = { Color::RED };
    symbolSpanStyle.SetSymbolColorList(colors);
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanColor
     * @tc.expected: Color list size remains 1
     */
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanColor004
 * @tc.desc: Test SpanItem UpdateSymbolSpanColor with textColor set
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanColor004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and FrameNode with textColor
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 403, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);
    textLayoutProperty->UpdateTextColor(Color::BLUE);
    
    /**
     * @tc.steps: step2. Create SpanItem with isParentText true and empty color list
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->SetIsParentText(true);
    TextStyle symbolSpanStyle;
    symbolSpanStyle.SetSymbolColorList(std::vector<Color>());
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanColor
     * @tc.expected: Color list updated with textColor
     */
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    
    EXPECT_EQ(symbolSpanStyle.GetSymbolColorList().size(), 1);
}

/**
 * @tc.name: SpanItemUpdateSymbolSpanColor005
 * @tc.desc: Test SpanItem UpdateSymbolSpanColor without textColor
 * @tc.type: FUNC
 */
HWTEST_F(SpanNodeNotifyColorModeTestNg, SpanItemUpdateSymbolSpanColor005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextPattern and FrameNode without textColor
     */
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 404, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    /**
     * @tc.steps: step2. Create SpanItem with isParentText true
     */
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    spanItem->SetIsParentText(true);
    TextStyle symbolSpanStyle;
    symbolSpanStyle.SetSymbolColorList(std::vector<Color>());
    
    /**
     * @tc.steps: step3. Call UpdateSymbolSpanColor
     * @tc.expected: isSymbolGlyph set to true
     */
    spanItem->UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
    
    EXPECT_TRUE(symbolSpanStyle.isSymbolGlyph_);
}
} // namespace OHOS::Ace::NG
