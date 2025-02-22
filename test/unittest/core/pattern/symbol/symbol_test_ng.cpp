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

#include <functional>
#include <optional>

#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_render_context.h"
#include "test/mock/core/rosen/mock_canvas.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/symbol/constants.h"
#include "core/components_ng/pattern/symbol/symbol_effect_options.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/symbol/symbol_source_info.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/components_ng/pattern/root/root_pattern.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

const std::uint32_t CREATE_VALUE = 983041;
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
std::uint32_t RENDER_STRATEGY = 1;
std::uint32_t EFFECT_STRATEGY = 1;
constexpr float MIN_FONT_SCALE = 0.5f;
constexpr float MAX_FONT_SCALE = 2.5f;
SymbolEffectOptions SYMBOL_EFFECT_OPTIONS =
    SymbolEffectOptions(OHOS::Ace::SymbolEffectType::BOUNCE, OHOS::Ace::ScopeType::WHOLE, OHOS::Ace::CommonSubType::UP);
std::vector<Color> SYMBOL_COLOR_LIST = { Color::FromRGB(255, 100, 100), Color::FromRGB(255, 255, 100) };
const char* SYMBOL_FONT_FAMILY = "Symbol_Test_CustomSymbol";
struct TestProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<SymbolSourceInfo> symbolSourceInfo = std::nullopt;
};

class SymbolTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;

protected:
    static void UpdateTextLayoutProperty(RefPtr<TextLayoutProperty> textLayoutProperty);
    RefPtr<FrameNode> symbolGlyphNode_;
};

void SymbolTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void SymbolTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void SymbolTestNg::SetUp()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    symbolGlyphNode_ = FrameNode::GetOrCreateFrameNode(
        V2::SYMBOL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TextPattern>(); });
    ASSERT_NE(symbolGlyphNode_, nullptr);
}

void SymbolTestNg::TearDown()
{
    MockParagraph::TearDown();
}

/**
 * @tc.name: SymbolFrameNodeCreator001
 * @tc.desc: test symbol create
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolFrameNodeCreator001, TestSize.Level1)
{
    ASSERT_NE(symbolGlyphNode_, nullptr);
    auto textPattern = symbolGlyphNode_->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    SymbolModelNG symbolModel;
    symbolModel.Create(CREATE_VALUE);
    EXPECT_EQ(static_cast<int32_t>(ViewStackProcessor::GetInstance()->elementsStack_.size()), 1);
    while (!ViewStackProcessor::GetInstance()->elementsStack_.empty()) {
        ViewStackProcessor::GetInstance()->elementsStack_.pop();
    }
}

/**
 * @tc.name: SymbolFrameNodeCreator002
 * @tc.desc: test symbol is atomicNode
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolFrameNodeCreator002, TestSize.Level1)
{
    ASSERT_NE(symbolGlyphNode_, nullptr);
    auto textPattern = symbolGlyphNode_->GetPattern<TextPattern>();
    ASSERT_NE(textPattern, nullptr);
    ASSERT_TRUE(textPattern->IsAtomicNode());
}

/**
 * @tc.name: SymbolFrameNodeCreator003
 * @tc.desc: test symbol unicode
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolFrameNodeCreator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    ASSERT_TRUE(frameNode->GetTag() == V2::SYMBOL_ETS_TAG);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get symbol unicode property
     */
    auto symbolInfo = textLayoutProperty->GetSymbolSourceInfo().value();
    EXPECT_EQ(symbolInfo.GetUnicode(), CREATE_VALUE);
}

/**
 * @tc.name: SymbolPropertyTest001
 * @tc.desc: test symbol fontSize property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetFontSize(FONT_SIZE_VALUE);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get fontSize property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    EXPECT_EQ(symbolStyle->GetFontSize(), FONT_SIZE_VALUE);
}

/**
 * @tc.name: SymbolPropertyTest002
 * @tc.desc: test symbol fontWeight property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetFontWeight(FontWeight::W100);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get fontWeight property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    EXPECT_EQ(symbolStyle->GetFontWeight(), FontWeight::W100);
}

/**
 * @tc.name: SymbolPropertyTest003
 * @tc.desc: test symbol renderStrategy property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetSymbolRenderingStrategy(RENDER_STRATEGY);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get renderStrategy property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    EXPECT_EQ(textStyle.GetRenderStrategy(), RENDER_STRATEGY);
}

/**
 * @tc.name: SymbolPropertyTest004
 * @tc.desc: test symbol color property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetFontColor(SYMBOL_COLOR_LIST);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get color property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    EXPECT_EQ(textStyle.GetRenderColors(), SYMBOL_COLOR_LIST);
}

/**
 * @tc.name: SymbolPropertyTest005
 * @tc.desc: test symbol effectStrategy property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetSymbolEffect(EFFECT_STRATEGY);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get effectStrategy property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    EXPECT_EQ(textStyle.GetEffectStrategy(), EFFECT_STRATEGY);
}

/**
 * @tc.name: SymbolPropertyTest006
 * @tc.desc: test symbol symbolEffect property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetSymbolEffectOptions(SYMBOL_EFFECT_OPTIONS);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);

    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get symbolEffect property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);
    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    auto symbolOptions = textStyle.GetSymbolEffectOptions().value_or(SymbolEffectOptions());
    EXPECT_EQ(symbolOptions.GetEffectType(), OHOS::Ace::SymbolEffectType::BOUNCE);
    EXPECT_EQ(symbolOptions.GetScopeType(), OHOS::Ace::ScopeType::WHOLE);
    EXPECT_EQ(symbolOptions.GetCommonSubType(), OHOS::Ace::CommonSubType::UP);
}

/**
 * @tc.name: SymbolPropertyTest007
 * @tc.desc: test static method of symbol model
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest007, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    auto frameNode = SymbolModelNG::CreateFrameNode(CREATE_VALUE);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::RawPtr(frameNode);
    ASSERT_NE(node, nullptr);

    SymbolModelNG::SetFontColor(node, SYMBOL_COLOR_LIST);
    SymbolModelNG::SetFontSize(node, FONT_SIZE_VALUE);
    SymbolModelNG::SetFontWeight(node, FontWeight::W100);
    SymbolModelNG::SetRenderingStrategy(node, RENDER_STRATEGY);
    SymbolModelNG::SetSymbolEffect(node, EFFECT_STRATEGY);
    SymbolModelNG::SetSymbolEffectOptions(node, SYMBOL_EFFECT_OPTIONS);

    RefPtr<LayoutProperty> property = frameNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    RefPtr<TextLayoutProperty> textProperty = AceType::DynamicCast<TextLayoutProperty>(property);
    ASSERT_NE(textProperty, nullptr);
    const std::unique_ptr<FontStyle>& symbolStyle = textProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    auto effectOptions = textStyle.GetSymbolEffectOptions().value_or(SymbolEffectOptions());
    EXPECT_EQ(textStyle.GetRenderColors(), SYMBOL_COLOR_LIST);
    EXPECT_EQ(textStyle.GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(symbolStyle->GetFontWeight(), FontWeight::W100);
    EXPECT_EQ(textStyle.GetEffectStrategy(), EFFECT_STRATEGY);
    EXPECT_EQ(effectOptions.GetEffectType(), OHOS::Ace::SymbolEffectType::BOUNCE);
    EXPECT_EQ(effectOptions.GetScopeType(), OHOS::Ace::ScopeType::WHOLE);
    EXPECT_EQ(effectOptions.GetCommonSubType(), OHOS::Ace::CommonSubType::UP);
}

/**
 * @tc.name: SymbolPropertyTest008
 * @tc.desc: test symbol minFontScale property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetMinFontScale(MIN_FONT_SCALE);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get minFontScale property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    EXPECT_EQ(textStyle.GetMinFontScale(), MIN_FONT_SCALE);
}

/**
 * @tc.name: SymbolPropertyTest009
 * @tc.desc: test symbol maxFontScale property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetMaxFontScale(MAX_FONT_SCALE);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get minFontScale property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    EXPECT_EQ(textStyle.GetMaxFontScale(), MAX_FONT_SCALE);
}

/**
 * @tc.name: SymbolPropertyTest010
 * @tc.desc: test symbol fontFamilies property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    std::vector<std::string> testFontFamilies;
    testFontFamilies.push_back(SYMBOL_FONT_FAMILY);
    symbolModelNG.SetFontFamilies(testFontFamilies);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get fontFamily property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    auto fontFamilies = textStyle.GetFontFamilies();
    ASSERT_NE(fontFamilies.size(), 0);
    auto familyNameValue = fontFamilies.front();
    EXPECT_EQ(familyNameValue, SYMBOL_FONT_FAMILY);
}

/**
 * @tc.name: SymbolPropertyTest011
 * @tc.desc: test symbol set symbolType property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    SymbolModelNG symbolModelNG;
    symbolModelNG.Create(CREATE_VALUE);
    symbolModelNG.SetSymbolType(SymbolType::CUSTOM);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get symbolType property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    
    auto symbolType = textStyle.GetSymbolType();
    EXPECT_EQ(symbolType, SymbolType::CUSTOM);
}

/**
 * @tc.name: SymbolPropertyTest012
 * @tc.desc: test symbol SetCustomSymbolGlyphInitialize property of symbol
 * @tc.type: FUNC
 */
HWTEST_F(SymbolTestNg, SymbolPropertyTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create symbol node
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SYMBOL_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TextPattern>(); });
    SymbolModelNG::SetCustomSymbolGlyphInitialize(AceType::RawPtr(frameNode), CREATE_VALUE, SYMBOL_FONT_FAMILY);

    /**
     * @tc.steps: step2. get symbol node and layoutProperty
     */
    RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    RefPtr<TextLayoutProperty> textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutProperty);
    ASSERT_NE(textLayoutProperty, nullptr);

    /**
     * @tc.steps: step3. test get symbolType property
     */
    const std::unique_ptr<FontStyle>& symbolStyle = textLayoutProperty->GetFontStyle();
    ASSERT_NE(symbolStyle, nullptr);

    auto textStyle = CreateTextStyleUsingTheme(symbolStyle, nullptr, nullptr);
    
    auto fontFamilies = textStyle.GetFontFamilies();
    ASSERT_NE(fontFamilies.size(), 0);
    auto familyNameValue = fontFamilies.front();
    EXPECT_EQ(familyNameValue, SYMBOL_FONT_FAMILY);

    auto symbolType = textStyle.GetSymbolType();
    EXPECT_EQ(symbolType, SymbolType::CUSTOM);
}
} // namespace OHOS::Ace::NG