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
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/unittest/core/pattern/test_ng.h"
#include "test/unittest/core/pattern/text/text_base.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_layout_algorithm.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr double ICON_SIZE = 24;
constexpr double ICON_HOT_ZONE_SIZE = 40;
constexpr int32_t DEFAULT_NODE_ID = 1;
constexpr int32_t MIN_PLATFORM_VERSION = 10;
const std::string DEFAULT_TEXT = "abcdefghijklmnopqrstuvwxyz";
struct ExpectParagraphParams {
    float height = 50.f;
    float longestLine = 460.f;
    float maxWidth = 460.f;
    size_t lineCount = 1;
    bool firstCalc = true;
    bool secondCalc = true;
};
} // namespace

class TextFieldTestNgFive : public TestNG {
protected:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void TearDown() override;

    void FlushLayoutTask(const RefPtr<FrameNode>& frameNode);
    void CreateTextField(const std::string& text = "", const std::string& placeHolder = "",
        const std::function<void(TextFieldModelNG&)>& callback = nullptr);
    static void ExpectCallParagraphMethods(ExpectParagraphParams params);
    void GetFocus();

    RefPtr<FrameNode> frameNode_;
    RefPtr<TextFieldPattern> pattern_;
    RefPtr<TextFieldEventHub> eventHub_;
    RefPtr<TextFieldLayoutProperty> layoutProperty_;
    RefPtr<TextFieldAccessibilityProperty> accessibilityProperty_;
};

void TextFieldTestNgFive::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    ExpectCallParagraphMethods(ExpectParagraphParams());
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto textFieldTheme = AceType::MakeRefPtr<TextFieldTheme>();
    textFieldTheme->iconSize_ = Dimension(ICON_SIZE, DimensionUnit::VP);
    textFieldTheme->iconHotZoneSize_ = Dimension(ICON_HOT_ZONE_SIZE, DimensionUnit::VP);
    textFieldTheme->fontSize_ = Dimension(FONT_SIZE, DimensionUnit::FP);
    textFieldTheme->fontWeight_ = FontWeight::W400;
    textFieldTheme->textColor_ = Color::FromString("#ff182431");
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([textFieldTheme = textFieldTheme](ThemeType type, int id) -> RefPtr<Theme> {
            if (type == ScrollBarTheme::TypeId()) {
                return AceType::MakeRefPtr<ScrollBarTheme>();
            }
            return textFieldTheme;
        });
    MockPipelineContext::GetCurrent()->SetMinPlatformVersion(MIN_PLATFORM_VERSION);
    MockPipelineContext::GetCurrent()->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManagerNG>());
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void TextFieldTestNgFive::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
    MockParagraph::TearDown();
}

void TextFieldTestNgFive::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
}

void TextFieldTestNgFive::ExpectCallParagraphMethods(ExpectParagraphParams params)
{
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*paragraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, PopStyle()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Build()).Times(AnyNumber());
    EXPECT_CALL(*paragraph, Layout(_)).Times(AnyNumber());
    EXPECT_CALL(*paragraph, GetTextWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetAlphabeticBaseline()).WillRepeatedly(Return(0.f));
    EXPECT_CALL(*paragraph, GetHeight()).WillRepeatedly(Return(params.height));
    EXPECT_CALL(*paragraph, GetLongestLine()).WillRepeatedly(Return(params.longestLine));
    EXPECT_CALL(*paragraph, GetMaxWidth()).WillRepeatedly(Return(params.maxWidth));
    EXPECT_CALL(*paragraph, GetLineCount()).WillRepeatedly(Return(params.lineCount));
}

void TextFieldTestNgFive::FlushLayoutTask(const RefPtr<FrameNode>& frameNode)
{
    frameNode->SetActive();
    frameNode->isLayoutDirtyMarked_ = true;
    frameNode->CreateLayoutTask();
    auto paintProperty = frameNode->GetPaintProperty<PaintProperty>();
    auto wrapper = frameNode->CreatePaintWrapper();
    if (wrapper != nullptr) {
        wrapper->FlushRender();
    }
    paintProperty->CleanDirty();
    frameNode->SetActive(false);
}

void TextFieldTestNgFive::CreateTextField(
    const std::string& text, const std::string& placeHolder, const std::function<void(TextFieldModelNG&)>& callback)
{
    auto* stack = ViewStackProcessor::GetInstance();
    stack->StartGetAccessRecordingFor(DEFAULT_NODE_ID);
    TextFieldModelNG textFieldModelNG;
    textFieldModelNG.CreateTextInput(StringUtils::Str8ToStr16(placeHolder), StringUtils::Str8ToStr16(text));
    if (callback) {
        callback(textFieldModelNG);
    }
    stack->StopGetAccessRecording();
    frameNode_ = AceType::DynamicCast<FrameNode>(stack->Finish());
    pattern_ = frameNode_->GetPattern<TextFieldPattern>();
    eventHub_ = frameNode_->GetEventHub<TextFieldEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TextFieldLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<TextFieldAccessibilityProperty>();
    FlushLayoutTask(frameNode_);
}

void TextFieldTestNgFive::GetFocus()
{
    auto focushHub = pattern_->GetFocusHub();
    focushHub->currentFocus_ = true;
    pattern_->HandleFocusEvent();
    FlushLayoutTask(frameNode_);
}

/**
 * @tc.name: SetExtraConfig
 * @tc.desc: test pass extra config to ime.
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetExtraConfig, TestSize.Level1)
{
    /**
     * @tc.steps: step1 Create Text filed node
     */
    struct ExtraConfig {
        std::string key;
        std::string value;
    };
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) {
        IMEAttachCallback attach = [](IMEClient& client) {
            ExtraConfig* extraConfig = new ExtraConfig();
            extraConfig->key = "name";
            extraConfig->value = "test";
            client.extraInfo = AceType::MakeRefPtr<IMEExtraInfo>(extraConfig, [extraConfig]() { delete extraConfig; });
        };
        model.SetOnWillAttachIME(std::move(attach));
    });
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.step: step2. Call FireOnWillAttachIME
     */
    auto clientInfo = pattern_->GetIMEClientInfo();
    pattern_->FireOnWillAttachIME(clientInfo);
    ASSERT_NE(clientInfo.extraInfo, nullptr);
    ASSERT_NE(clientInfo.extraInfo->GetExtraInfo(), nullptr);
    auto parsedConfig = *reinterpret_cast<ExtraConfig*>(clientInfo.extraInfo->GetExtraInfo());
    EXPECT_EQ(parsedConfig.key, "name");
    EXPECT_EQ(parsedConfig.value, "test");
}

/**
 * @tc.name: SetBorderDashGap001
 * @tc.desc: Test TextField border dashGap with single value using ViewAbstract
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetBorderDashGap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get paint property
     * @tc.expected: Paint property should exist
     */
    auto paintProperty = frameNode_->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. Call ViewAbstract::SetDashGap with positive value
     * @tc.expected: dashGap should be set
     */
    constexpr float dashGapValue = 5.0f;
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode_), Dimension(dashGapValue, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Flush layout to apply border properties
     * @tc.expected: Border properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Verify render context has dashGap
     * @tc.expected: DashGap property should exist in render context
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto dashGap = renderContext->GetDashGap();
    EXPECT_TRUE(dashGap.has_value());
}

/**
 * @tc.name: SetBorderDashGap002
 * @tc.desc: Test TextField border dashGap with BorderWidthProperty
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetBorderDashGap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get paint property
     * @tc.expected: Paint property should exist
     */
    auto paintProperty = frameNode_->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. Create BorderWidthProperty with different dashGap values
     * @tc.expected: Each side has independent dashGap value
     */
    BorderWidthProperty dashGap;
    dashGap.leftDimen = Dimension(3.0f, DimensionUnit::VP);
    dashGap.topDimen = Dimension(5.0f, DimensionUnit::VP);
    dashGap.rightDimen = Dimension(7.0f, DimensionUnit::VP);
    dashGap.bottomDimen = Dimension(9.0f, DimensionUnit::VP);

    /**
     * @tc.steps: step4. Call ViewAbstract::SetDashGap with BorderWidthProperty
     * @tc.expected: dashGap should be set for all sides
     */
    ViewAbstractModelStatic::SetDashGap(AceType::RawPtr(frameNode_), dashGap);

    /**
     * @tc.steps: step5. Flush layout to apply border properties
     * @tc.expected: Border properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step6. Verify render context has dashGap
     * @tc.expected: DashGap property should exist in render context
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto dashGapResult = renderContext->GetDashGap();
    EXPECT_TRUE(dashGapResult.has_value());
}

/**
 * @tc.name: SetBorderDashGap003
 * @tc.desc: Test TextField border dashGap reset to default value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetBorderDashGap003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Get paint property
     * @tc.expected: Paint property should exist
     */
    auto paintProperty = frameNode_->GetPaintProperty<PaintProperty>();
    ASSERT_NE(paintProperty, nullptr);

    /**
     * @tc.steps: step3. Set dashGap with positive value first
     * @tc.expected: Initial dashGap is set
     */
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode_), Dimension(5.0f, DimensionUnit::VP));
    FlushLayoutTask(frameNode_);

    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode_), Dimension(-1));

    /**
     * @tc.steps: step5. Flush layout to apply changes
     * @tc.expected: Border properties should be updated
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step6. Verify render context
     * @tc.expected: Render context should still be valid
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto dashGap = renderContext->GetDashGap();
    EXPECT_TRUE(dashGap.has_value());
}

/**
 * @tc.name: ResetDashGap001
 * @tc.desc: Test ResetDashGap function resets dash gap to default value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, ResetDashGap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set initial dash gap value
     * @tc.expected: Initial dash gap is set
     */
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode_), Dimension(5.0f, DimensionUnit::VP));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Call ResetDashGap through style_modifier interface
     * @tc.expected: Dash gap should be reset to default (-1)
     */
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode_), Dimension(-1));
    FlushLayoutTask(frameNode_);

    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    /**
     * @tc.steps: step5. Verify render context state after reset
     * @tc.expected: Render context remains valid
     */
    auto dashGapAfterReset = renderContext->GetDashGap();
    EXPECT_TRUE(dashGapAfterReset.has_value());
}

/**
 * @tc.name: SetDashWidth001
 * @tc.desc: Test SetDashWidth with four values for border dash width
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetDashWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create BorderWidthProperty with dash width values
     * @tc.expected: Each side has independent dash width value
     */
    BorderWidthProperty dashWidth;
    dashWidth.leftDimen = Dimension(2.0f, DimensionUnit::VP);
    dashWidth.topDimen = Dimension(3.0f, DimensionUnit::VP);
    dashWidth.rightDimen = Dimension(4.0f, DimensionUnit::VP);
    dashWidth.bottomDimen = Dimension(5.0f, DimensionUnit::VP);

    /**
     * @tc.steps: step3. Call ViewAbstract::SetDashWidth with BorderWidthProperty
     * @tc.expected: Dash width should be set for all sides
     */
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode_), Dimension(3.0f, DimensionUnit::VP));

    /**
     * @tc.steps: step4. Flush layout to apply border properties
     * @tc.expected: Border properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Verify render context has dash width
     * @tc.expected: Dash width property should be configured
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    EXPECT_TRUE(renderContext->GetDashWidth().has_value());
}

/**
 * @tc.name: SetDashWidth002
 * @tc.desc: Test SetDashWidth with single value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetDashWidth002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Call ViewAbstract::SetDashWidth with single Dimension value
     * @tc.expected: Dash width should be set uniformly
     */
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode_), Dimension(3.0f, DimensionUnit::VP));

    /**
     * @tc.steps: step3. Flush layout to apply border properties
     * @tc.expected: Border properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step4. Verify render context
     * @tc.expected: Render context should be valid
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto dashWidth = renderContext->GetDashWidth();
    EXPECT_TRUE(dashWidth.has_value());
}

/**
 * @tc.name: ResetDashWidth001
 * @tc.desc: Test ResetDashWidth function resets dash width to default value
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, ResetDashWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set initial dash width
     * @tc.expected: Initial dash width is set
     */
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode_), Dimension(3.0f, DimensionUnit::VP));
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Reset dash width to default (-1)
     * @tc.expected: Dash width should be reset
     */
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode_), Dimension(-1));

    /**
     * @tc.steps: step5. Verify render context
     * @tc.expected: Render context should still be valid
     */
    auto renderContext = frameNode_->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto dashWidth = renderContext->GetDashWidth();
    EXPECT_TRUE(dashWidth.has_value());
}

/**
 * @tc.name: SetChainWeight001
 * @tc.desc: Test SetChainWeight with horizontal and vertical weights
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetChainWeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create ChainWeightPair with custom weights
     * @tc.expected: Horizontal and vertical weights are set
     */
    NG::ChainWeightPair chainWeight;
    chainWeight.first = 1.0f;
    chainWeight.second = 2.0f;

    /**
     * @tc.steps: step3. Call ViewAbstract::SetChainWeight
     * @tc.expected: Chain weight should be set
     */
    ViewAbstract::SetChainWeight(AceType::RawPtr(frameNode_), chainWeight);

    /**
     * @tc.steps: step4. Flush layout to apply changes
     * @tc.expected: Layout properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Verify frame node is still valid
     * @tc.expected: Frame node should remain valid after chain weight set
     */
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: SetChainWeight002
 * @tc.desc: Test SetChainWeight with only horizontal weight
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, SetChainWeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Create ChainWeightPair with horizontal weight only
     * @tc.expected: Horizontal weight is set, vertical defaults to 0
     */
    NG::ChainWeightPair chainWeight;
    chainWeight.first = 1.5f;
    chainWeight.second = std::nullopt;

    /**
     * @tc.steps: step3. Call ViewAbstract::SetChainWeight
     * @tc.expected: Chain weight should be set
     */
    ViewAbstract::SetChainWeight(AceType::RawPtr(frameNode_), chainWeight);

    /**
     * @tc.steps: step4. Flush layout to apply changes
     * @tc.expected: Layout properties should be processed
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Verify frame node state
     * @tc.expected: Frame node should be valid
     */
    EXPECT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: ResetChainWeight001
 * @tc.desc: Test ResetChainWeight function resets chain weight to default values
 * @tc.type: FUNC
 */
HWTEST_F(TextFieldTestNgFive, ResetChainWeight001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TextField
     * @tc.expected: TextField is created successfully
     */
    CreateTextField(DEFAULT_TEXT, "", [](TextFieldModelNG model) { model.SetType(TextInputType::TEXT); });

    ASSERT_NE(frameNode_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Set initial chain weight
     * @tc.expected: Initial chain weight is set
     */
    NG::ChainWeightPair initialWeight;
    initialWeight.first = 2.0f;
    initialWeight.second = 3.0f;
    ViewAbstract::SetChainWeight(AceType::RawPtr(frameNode_), initialWeight);
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step3. Reset chain weight to default (0, 0)
     * @tc.expected: Chain weight should be reset to zero
     */
    NG::ChainWeightPair defaultWeight;
    defaultWeight.first = 0.0f;
    defaultWeight.second = 0.0f;
    ViewAbstract::SetChainWeight(AceType::RawPtr(frameNode_), defaultWeight);

    /**
     * @tc.steps: step4. Flush layout to apply changes
     * @tc.expected: Layout properties should be updated
     */
    FlushLayoutTask(frameNode_);

    /**
     * @tc.steps: step5. Verify frame node is still valid
     * @tc.expected: Frame node should remain valid after reset
     */
    EXPECT_NE(frameNode_, nullptr);
}

} // namespace OHOS::Ace::NG