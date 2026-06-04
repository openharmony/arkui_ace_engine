/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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
#include "test/unittest/core/base/view_abstract_test_ng.h"
#include "core/common/event_manager.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void ViewAbstractTestFiveNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->pipelineContext_ = PipelineBase::GetCurrentContext();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineBase::GetCurrentContext()->SetThemeManager(themeManager);
    PipelineBase::GetCurrentContext()->SetEventManager(AceType::MakeRefPtr<EventManager>());
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<PopupTheme>()));
}

void ViewAbstractTestFiveNg::TearDownTestSuite()
{
    MockContainer::Current()->pipelineContext_ = nullptr;
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: CreateWithDimensionResourceObj001
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create dimension resource object and configure popup parameters.
     * @tc.expected: step2. Dimension resource object and popup parameters are initialized correctly.
     */
    std::vector<ResourceObjectParams> params = { { "", ResourceObjectParamType::NONE } };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(0, 10007, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetWidthResourceObject(resObj);
    param->SetArrowWidthResourceObject(resObj);
    param->SetArrowHeightResourceObject(resObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for width dimension resource.
     * @tc.expected: step3. Width dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_WIDTH;
    auto widthResourceObject = param->GetWidthResourceObject();
    ASSERT_NE(widthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, widthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto widthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(widthStr, "width");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for arrow width dimension resource.
     * @tc.expected: step4. Arrow width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWWIDTH;
    auto arrowWidthResourceObject = param->GetArrowWidthResourceObject();
    ASSERT_NE(arrowWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, arrowWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowWidthStr, "arrowWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for arrow height dimension resource.
     * @tc.expected: step5. Arrow height dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWHEIGHT;
    auto arrowHeighResourceObject = param->GetArrowHeightResourceObject();
    ASSERT_NE(arrowHeighResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, arrowHeighResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowHeighStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowHeighStr, "arrowHeight");
}

/**
 * @tc.name: CreateWithDimensionResourceObj002
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create dimension resource object and configure popup parameters.
     * @tc.expected: step2. Dimension resource object and popup parameters are initialized correctly.
     */
    std::vector<ResourceObjectParams> params = { { "", ResourceObjectParamType::NONE } };
    RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>(0, 10007, params, "", "", 0);
    ASSERT_NE(resObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetRadiusResourceObject(resObj);
    param->SetOutlineWidthObject(resObj);
    param->SetBorderWidthObject(resObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for radius dimension resource.
     * @tc.expected: step3. Radius dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_RADIUS;
    auto radiusResourceObject = param->GetRadiusResourceObject();
    ASSERT_NE(radiusResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, radiusResourceObject, type);
    pattern->OnColorModeChange(1);
    auto radiusStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(radiusStr, "radius");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for outline width dimension resource.
     * @tc.expected: step4. Outline width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_OUTLINEWIDTH;
    auto outlineWidthResourceObject = param->GetOutlineWidthResourceObject();
    ASSERT_NE(outlineWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, outlineWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto outlineWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(outlineWidthStr, "outlineWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for border width dimension resource.
     * @tc.expected: step5. Border width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_BORDERWIDTH;
    auto borderWidthResourceObject = param->GetBorderWidthResourceObject();
    ASSERT_NE(borderWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, borderWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto borderWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(borderWidthStr, "borderWidth");
}

/**
 * @tc.name: CreateWithDimensionResourceObj003
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create default resource object and configure popup parameters.
     * @tc.expected: step2. Default resource object and popup parameters are initialized correctly.
     */
    RefPtr<ResourceObject> defaultResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ASSERT_NE(defaultResObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetWidthResourceObject(defaultResObj);
    param->SetArrowWidthResourceObject(defaultResObj);
    param->SetArrowHeightResourceObject(defaultResObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for width dimension with default resource.
     * @tc.expected: step3. Width dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_WIDTH;
    auto defaultWidthResourceObject = param->GetWidthResourceObject();
    ASSERT_NE(defaultWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto widthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(widthStr, "width");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for arrow width dimension with default resource.
     * @tc.expected: step4. Arrow width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWWIDTH;
    auto defaultArrowWidthResourceObject = param->GetArrowWidthResourceObject();
    ASSERT_NE(defaultArrowWidthResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultArrowWidthResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowWidthStr, "arrowWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for arrow height dimension with default resource.
     * @tc.expected: step5. Arrow height dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_ARROWHEIGHT;
    auto defaultArrowHeightResourceObject = param->GetArrowHeightResourceObject();
    ASSERT_NE(defaultArrowHeightResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultArrowHeightResourceObject, type);
    pattern->OnColorModeChange(1);
    auto arrowHeighStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(arrowHeighStr, "arrowHeight");
}

/**
 * @tc.name: CreateWithDimensionResourceObj004
 * @tc.desc: Test CreateWithDimensionResourceObj of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, CreateWithDimensionResourceObj004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create frame node and initialize components.
     * @tc.expected: step1. Frame node and related components are created successfully.
     */
    const RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("main", 1, AceType::MakeRefPtr<BubblePattern>());
    ASSERT_NE(frameNode, nullptr);
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto pattern = frameNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2. Create default resource object and configure popup parameters.
     * @tc.expected: step2. Default resource object and popup parameters are initialized correctly.
     */
    RefPtr<ResourceObject> defaultResObj = AceType::MakeRefPtr<ResourceObject>("", "", 0);
    ASSERT_NE(defaultResObj, nullptr);

    RefPtr<PopupParam> param = AceType::MakeRefPtr<PopupParam>();
    ASSERT_NE(param, nullptr);

    param->SetRadiusResourceObject(defaultResObj);
    param->SetOutlineWidthObject(defaultResObj);
    param->SetBorderWidthObject(defaultResObj);

    /**
     * @tc.steps: step3. Test CreateWithResourceObj for radius dimension with default resource.
     * @tc.expected: step3. Radius dimension resource is applied and type string is correct.
     */
    PopupOptionsType type = POPUP_OPTIONTYPE_RADIUS;
    auto defaultRadiusResourceObject = param->GetRadiusResourceObject();
    ASSERT_NE(defaultRadiusResourceObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultRadiusResourceObject, type);
    pattern->OnColorModeChange(1);
    auto radiusStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(radiusStr, "radius");

    /**
     * @tc.steps: step4. Test CreateWithResourceObj for outline width dimension with default resource.
     * @tc.expected: step4. Outline width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_OUTLINEWIDTH;
    auto defaultOutlineWidthObject = param->GetOutlineWidthResourceObject();
    ASSERT_NE(defaultOutlineWidthObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultOutlineWidthObject, type);
    pattern->OnColorModeChange(1);
    auto outlineWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(outlineWidthStr, "outlineWidth");

    /**
     * @tc.steps: step5. Test CreateWithResourceObj for border width dimension with default resource.
     * @tc.expected: step5. Border width dimension resource is applied and type string is correct.
     */
    type = POPUP_OPTIONTYPE_BORDERWIDTH;
    auto defaultBorderWidthObject = param->GetBorderWidthResourceObject();
    ASSERT_NE(defaultBorderWidthObject, nullptr);
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultBorderWidthObject, type);
    pattern->OnColorModeChange(1);
    auto borderWidthStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(borderWidthStr, "borderWidth");

    /**
     * @tc.steps: step6. Test CreateWithResourceObj with invalid type using default resource.
     * @tc.expected: step6. Type string for invalid type is empty.
     */
    type = POPUP_OPTIONTYPE_OFFSETDX;
    viewAbstractModelNG.CreateWithResourceObj(frameNode, defaultResObj, type);
    pattern->OnColorModeChange(1);
    auto defaultStr = viewAbstractModelNG.PopupOptionTypeStr(type);
    EXPECT_EQ(defaultStr, "");
}

/**
 * @tc.name: ViewAbstractModelNg_SetClipEdge
 * @tc.desc: Test SetClipEdge of View_Abstract_Model_NG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, ViewAbstractModelNg_SetClipEdge, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstractModelNG::SetClipEdge(frameNode, true);
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ViewAbstractModelNg_SetClipShape
 * @tc.desc: Test SetClipShape of View_Abstract_Model_NG
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, ViewAbstractNGSetClipShape001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    g_isConfigChangePerform = true;
    ViewAbstractModelNG::SetClipEdge(frameNode, true);
    auto basicShape = AceType::MakeRefPtr<Circle>();
    basicShape->SetBasicShapeType(BasicShapeType::CIRCLE);
    EXPECT_EQ(basicShape->GetBasicShapeType(), BasicShapeType::CIRCLE);
    ViewAbstractModelNG::SetClipShape(frameNode, basicShape);
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
    std::string shapeStr = pattern->GetResCacheMapByKey("clipShape");
    EXPECT_EQ(shapeStr, "");
}

/**
 * @tc.name: SweepGradientHDRColorTest001
 * @tc.desc: Test SetSweepGradient with basic HDR color configuration
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Enable config change perform mode
     * @tc.expected: Config change perform mode should be enabled
     */
    g_isConfigChangePerform = true;
    
    /**
     * @tc.steps: step3. Create sweep gradient with HDR colors
     * @tc.expected: Gradient should be created successfully with HDR colors
     */
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    // Add first HDR color stop with headRoom=2.0
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    // Add second HDR color stop with headRoom=2.0
    NG::GradientColor gradientColor2(Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f));
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    // Set sweep gradient center position
    gradient.GetSweepGradient()->centerX = CalcDimension(0.5, DimensionUnit::PERCENT);
    gradient.GetSweepGradient()->centerY = CalcDimension(0.5, DimensionUnit::PERCENT);
    
    /**
     * @tc.steps: step4. Apply sweep gradient to frame node
     * @tc.expected: Sweep gradient should be applied successfully
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    /**
     * @tc.steps: step5. Verify sweep gradient is applied correctly
     * @tc.expected: Render context should have sweep gradient with HDR colors
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify HDR color headroom values
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[0].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    
    /**
     * @tc.steps: step6. Test color mode change callback
     * @tc.expected: OnColorModeChange should be called without error
     */
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest002
 * @tc.desc: Test SetSweepGradient with multiple HDR colors and full parameters
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Enable config change perform mode and create gradient
     * @tc.expected: Gradient should be created with 3 HDR color stops
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f));
    gradientColor2.SetDimension(50.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    NG::GradientColor gradientColor3(Color::FromFloat(0.0f, 0.0f, 1.0f, 1.0f, 2.0f));
    gradientColor3.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor3);
    
    /**
     * @tc.steps: step3. Set all sweep gradient parameters
     * @tc.expected: All parameters should be set correctly
     */
    gradient.GetSweepGradient()->centerX = CalcDimension(0.5, DimensionUnit::PERCENT);
    gradient.GetSweepGradient()->centerY = CalcDimension(0.5, DimensionUnit::PERCENT);
    gradient.GetSweepGradient()->startAngle = CalcDimension(0.0, DimensionUnit::PX);
    gradient.GetSweepGradient()->endAngle = CalcDimension(360.0, DimensionUnit::PX);
    gradient.GetSweepGradient()->rotation = CalcDimension(0.0, DimensionUnit::PX);
    
    /**
     * @tc.steps: step4. Apply sweep gradient and verify
     * @tc.expected: All HDR colors and parameters should be correct
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify all HDR colors
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[0].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[2].GetColor().GetHeadRoomColor().has_value());
    
    // Verify all sweep gradient parameters
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->centerX,
        CalcDimension(0.5, DimensionUnit::PERCENT));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->centerY,
        CalcDimension(0.5, DimensionUnit::PERCENT));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->startAngle,
        CalcDimension(0.0, DimensionUnit::PX));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->endAngle,
        CalcDimension(360.0, DimensionUnit::PX));
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest003
 * @tc.desc: Test SetSweepGradient without FrameNode parameter with HDR colors
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Enable config change perform mode and create gradient
     * @tc.expected: Gradient should be created with HDR colors
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    NG::GradientColor gradientColor1(Color::FromFloat(0.8f, 0.2f, 0.3f, 1.0f, 1.5f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.3f, 0.7f, 0.9f, 1.0f, 1.8f));
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    gradient.GetSweepGradient()->endAngle = CalcDimension(270.0, DimensionUnit::PX);
    
    /**
     * @tc.steps: step3. Test SetSweepGradient without FrameNode parameter
     * @tc.expected: Sweep gradient should be applied successfully
     */
    ViewAbstract::SetSweepGradient(gradient);
    
    /**
     * @tc.steps: step4. Verify sweep gradient is applied correctly
     * @tc.expected: Render context should have sweep gradient with HDR colors
     */
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->endAngle,
        CalcDimension(270.0, DimensionUnit::PX));
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest004
 * @tc.desc: Test SetSweepGradient with HDR color and repeat flag enabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create sweep gradient with repeat flag enabled
     * @tc.expected: Repeat flag should be set to true
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    gradient.SetRepeat(true);
    
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.5f, 0.0f, 1.0f, 2.2f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.5f, 0.0f, 1.0f, 0.8f, 2.5f));
    gradientColor2.SetDimension(50.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    gradient.GetSweepGradient()->centerX = CalcDimension(0.3, DimensionUnit::PERCENT);
    gradient.GetSweepGradient()->centerY = CalcDimension(0.7, DimensionUnit::PERCENT);
    
    /**
     * @tc.steps: step3. Apply sweep gradient and verify repeat flag
     * @tc.expected: Repeat flag should be true and HDR colors should be applied
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    EXPECT_EQ(renderContext->GetSweepGradient()->GetRepeat(), true);
    
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->centerX,
        CalcDimension(0.3, DimensionUnit::PERCENT));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->centerY,
        CalcDimension(0.7, DimensionUnit::PERCENT));
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest005
 * @tc.desc: Test SetSweepGradient with mixed HDR and normal colors
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create gradient with mixed HDR and normal colors
     * @tc.expected: Gradient should contain both HDR and non-HDR colors
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    // First color: HDR color with headRoom
    NG::GradientColor gradientColor1(Color::FromFloat(1.2f, 0.6f, 0.4f, 1.0f, 1.8f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    // Second color: Normal color without headRoom
    NG::GradientColor gradientColor2(Color::FromARGB(255, 0, 255, 0));
    gradientColor2.SetDimension(50.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    // Third color: HDR color with different headRoom
    NG::GradientColor gradientColor3(Color::FromFloat(0.4f, 0.8f, 1.0f, 1.0f, 2.0f));
    gradientColor3.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor3);
    
    /**
     * @tc.steps: step3. Apply gradient and verify mixed color types
     * @tc.expected: Should have both HDR and non-HDR colors
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify HDR and non-HDR color mix
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[0].GetColor().GetHeadRoomColor().has_value());
    EXPECT_FALSE(colors[1].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[2].GetColor().GetHeadRoomColor().has_value());
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest006
 * @tc.desc: Test SetSweepGradient with HDR color in BT2020 color space
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create HDR colors with BT2020 color space
     * @tc.expected: Colors should have BT2020 color space set
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    Color hdrColor1 = Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f);
    hdrColor1.SetColorSpace(ColorSpace::BT2020);
    NG::GradientColor gradientColor1(hdrColor1);
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    Color hdrColor2 = Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f);
    hdrColor2.SetColorSpace(ColorSpace::BT2020);
    NG::GradientColor gradientColor2(hdrColor2);
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    gradient.GetSweepGradient()->centerX = CalcDimension(0.5, DimensionUnit::PERCENT);
    gradient.GetSweepGradient()->centerY = CalcDimension(0.5, DimensionUnit::PERCENT);
    
    /**
     * @tc.steps: step3. Apply gradient and verify color space
     * @tc.expected: Both colors should have BT2020 color space
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify color space
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_EQ(colors[0].GetColor().GetColorSpace(), ColorSpace::BT2020);
    EXPECT_EQ(colors[1].GetColor().GetColorSpace(), ColorSpace::BT2020);
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest007
 * @tc.desc: Test SetSweepGradient with config change perform disabled
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Disable config change perform mode
     * @tc.expected: Config change perform mode should be disabled
     */
    g_isConfigChangePerform = false;
    
    /**
     * @tc.steps: step3. Create sweep gradient with HDR colors
     * @tc.expected: Gradient should be created successfully
     */
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f));
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    /**
     * @tc.steps: step4. Apply sweep gradient with config change disabled
     * @tc.expected: Sweep gradient should still be applied successfully
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
}

/**
 * @tc.name: SweepGradientHDRColorTest008
 * @tc.desc: Test SetSweepGradient with different angle configurations
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create sweep gradient with custom angles
     * @tc.expected: Custom angles should be set correctly
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.5f, 0.0f, 1.0f, 1.5f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.0f, 0.5f, 1.0f, 1.0f, 1.5f));
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    // Test different angle configurations
    gradient.GetSweepGradient()->startAngle = CalcDimension(45.0, DimensionUnit::PX);
    gradient.GetSweepGradient()->endAngle = CalcDimension(315.0, DimensionUnit::PX);
    gradient.GetSweepGradient()->rotation = CalcDimension(90.0, DimensionUnit::PX);
    
    /**
     * @tc.steps: step3. Apply gradient and verify angles
     * @tc.expected: All angles should be applied correctly
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->startAngle,
        CalcDimension(45.0, DimensionUnit::PX));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->endAngle,
        CalcDimension(315.0, DimensionUnit::PX));
    EXPECT_EQ(renderContext->GetSweepGradient()->GetSweepGradient()->rotation,
        CalcDimension(90.0, DimensionUnit::PX));
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest009
 * @tc.desc: Test SetSweepGradient with different opacity values in HDR colors
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create sweep gradient with different opacity values
     * @tc.expected: Different opacity values should be set correctly
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    // Test with different opacity values
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.0f, 0.0f, 0.5f, 2.0f)); // opacity=0.5
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.0f, 1.0f, 0.0f, 0.8f, 2.0f)); // opacity=0.8
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    /**
     * @tc.steps: step3. Apply gradient and verify opacity
     * @tc.expected: Different opacity values should be preserved
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest010
 * @tc.desc: Test SetSweepGradient with DISPLAY_P3 color space
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create HDR color with DISPLAY_P3 color space
     * @tc.expected: Colors should have DISPLAY_P3 color space set
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    Color hdrColor1 = Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f);
    hdrColor1.SetColorSpace(ColorSpace::DISPLAY_P3);
    NG::GradientColor gradientColor1(hdrColor1);
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    Color hdrColor2 = Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f);
    hdrColor2.SetColorSpace(ColorSpace::DISPLAY_P3);
    NG::GradientColor gradientColor2(hdrColor2);
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    /**
     * @tc.steps: step3. Apply gradient and verify color space
     * @tc.expected: Both colors should have DISPLAY_P3 color space
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify DISPLAY_P3 color space
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_EQ(colors[0].GetColor().GetColorSpace(), ColorSpace::DISPLAY_P3);
    EXPECT_EQ(colors[1].GetColor().GetColorSpace(), ColorSpace::DISPLAY_P3);
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest011
 * @tc.desc: Test SetSweepGradient with maximum HDR headRoom value
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create gradient with maximum headRoom value
     * @tc.expected: Maximum headRoom value should be set
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    // Test with maximum headRoom value
    NG::GradientColor gradientColor1(Color::FromFloat(1.5f, 0.8f, 0.6f, 1.0f, 10.0f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(0.6f, 1.2f, 1.0f, 1.0f, 10.0f));
    gradientColor2.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    /**
     * @tc.steps: step3. Apply gradient and verify headRoom
     * @tc.expected: Maximum headRoom value should be preserved
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: SweepGradientHDRColorTest012
 * @tc.desc: Test SetSweepGradient with 4 or more color stops
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestFiveNg, SweepGradientHDRColorTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get frame node and pattern for testing
     * @tc.expected: Frame node and pattern should be available
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<Pattern>();
    ASSERT_NE(pattern, nullptr);
    
    /**
     * @tc.steps: step2. Create gradient with 4 color stops
     * @tc.expected: 4 color stops should be added successfully
     */
    g_isConfigChangePerform = true;
    
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::SWEEP);
    
    NG::GradientColor gradientColor1(Color::FromFloat(1.0f, 0.0f, 0.0f, 1.0f, 2.0f));
    gradientColor1.SetDimension(0.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor1);
    
    NG::GradientColor gradientColor2(Color::FromFloat(1.0f, 1.0f, 0.0f, 1.0f, 2.0f));
    gradientColor2.SetDimension(33.3, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor2);
    
    NG::GradientColor gradientColor3(Color::FromFloat(0.0f, 1.0f, 0.0f, 1.0f, 2.0f));
    gradientColor3.SetDimension(66.6, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor3);
    
    NG::GradientColor gradientColor4(Color::FromFloat(0.0f, 0.0f, 1.0f, 1.0f, 2.0f));
    gradientColor4.SetDimension(100.0, DimensionUnit::PERCENT);
    gradient.AddColor(gradientColor4);
    
    /**
     * @tc.steps: step3. Apply gradient and verify all colors
     * @tc.expected: All 4 HDR colors should be present
     */
    ViewAbstract::SetSweepGradient(frameNode, gradient);
    
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_EQ(renderContext->GetSweepGradient().has_value(), true);
    
    // Verify all HDR colors
    auto colors = renderContext->GetSweepGradient()->GetColors();
    EXPECT_TRUE(colors[0].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[1].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[2].GetColor().GetHeadRoomColor().has_value());
    EXPECT_TRUE(colors[3].GetColor().GetHeadRoomColor().has_value());
    
    pattern->OnColorModeChange((uint32_t)ColorMode::DARK);
    g_isConfigChangePerform = false;
}

/**
 * @tc.name: ViewAbstractLpxWidthHeight001
 * @tc.desc: Test SetWidth/SetHeight with LPX unit registers LPX attribute, non-LPX unregisters.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxWidthHeight001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetWidth(NG::CalcLength(lpxDim));
    ViewAbstract::SetHeight(NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    ViewAbstract::SetWidth(NG::CalcLength(vpDim));
    ViewAbstract::SetHeight(NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxMinMax001
 * @tc.desc: Test SetMinWidth/Height, SetMaxWidth/Height with LPX unit.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxMinMax001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetMinWidth(NG::CalcLength(lpxDim));
    ViewAbstract::SetMinHeight(NG::CalcLength(lpxDim));
    ViewAbstract::SetMaxWidth(NG::CalcLength(lpxDim));
    ViewAbstract::SetMaxHeight(NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 4);

    ViewAbstract::SetMinWidth(NG::CalcLength(vpDim));
    ViewAbstract::SetMinHeight(NG::CalcLength(vpDim));
    ViewAbstract::SetMaxWidth(NG::CalcLength(vpDim));
    ViewAbstract::SetMaxHeight(NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxPadding001
 * @tc.desc: Test SetPadding with LPX unit registers LPX_PADDING attribute.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxPadding001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetPadding(NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 1);

    ViewAbstract::SetPadding(NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxSafeAreaPadding001
 * @tc.desc: Test SetSafeAreaPadding with LPX unit registers LPX_SAFE_AREA_PADDING attribute.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxSafeAreaPadding001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetSafeAreaPadding(NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 1);

    ViewAbstract::SetSafeAreaPadding(NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxMargin001
 * @tc.desc: Test SetMargin with LPX unit registers LPX_MARGIN attribute.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxMargin001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetMargin(NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 1);

    ViewAbstract::SetMargin(NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxBorderRadius001
 * @tc.desc: Test SetBorderRadius with LPX unit registers LPX_BORDER_RADIUS attribute.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxBorderRadius001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetBorderRadius(lpxDim);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 1);

    ViewAbstract::SetBorderRadius(vpDim);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxBorderWidth001
 * @tc.desc: Test SetBorderWidth with LPX unit registers LPX_BORDER_WIDTH attribute.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxBorderWidth001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetBorderWidth(lpxDim);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 1);

    ViewAbstract::SetBorderWidth(vpDim);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxPosition001
 * @tc.desc: Test SetPosition with LPX unit registers LPX_POSITION_X/Y attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxPosition001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetPosition(OffsetT<Dimension>(lpxDim, lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    ViewAbstract::SetPosition(OffsetT<Dimension>(vpDim, vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxOffset001
 * @tc.desc: Test SetOffset with LPX unit registers LPX_OFFSET_X/Y attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxOffset001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetOffset(OffsetT<Dimension>(lpxDim, lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    ViewAbstract::SetOffset(OffsetT<Dimension>(vpDim, vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxMarkAnchor001
 * @tc.desc: Test MarkAnchor with LPX unit registers LPX_MARK_ANCHOR_X/Y attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxMarkAnchor001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::MarkAnchor(OffsetT<Dimension>(lpxDim, lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    ViewAbstract::MarkAnchor(OffsetT<Dimension>(vpDim, vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxPositionEdges001
 * @tc.desc: Test SetPositionEdges with LPX unit registers LPX_POSITION_EDGES attributes.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxPositionEdges001, TestSize.Level1)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    EdgesParam edges;
    edges.left = lpxDim;
    edges.top = lpxDim;
    ViewAbstract::SetPositionEdges(edges);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    EdgesParam vpEdges;
    vpEdges.left = vpDim;
    vpEdges.top = vpDim;
    ViewAbstract::SetPositionEdges(vpEdges);
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}

/**
 * @tc.name: ViewAbstractLpxFrameNodeWidthHeight001
 * @tc.desc: Test FrameNode-based SetWidth/SetHeight with LPX unit.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractLpxFrameNodeWidthHeight001, TestSize.Level1)
{
    auto frameNode = AceType::RawPtr(FRAME_NODE_REGISTER);
    ASSERT_NE(frameNode, nullptr);
    frameNode->AttachToMainTree();
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    context->lpxDirtyNodes_.clear();

    Dimension lpxDim(10.0, DimensionUnit::LPX);
    Dimension vpDim(10.0, DimensionUnit::VP);

    ViewAbstract::SetWidth(frameNode, NG::CalcLength(lpxDim));
    ViewAbstract::SetHeight(frameNode, NG::CalcLength(lpxDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 2);

    ViewAbstract::SetWidth(frameNode, NG::CalcLength(vpDim));
    ViewAbstract::SetHeight(frameNode, NG::CalcLength(vpDim));
    EXPECT_EQ(frameNode->lpxAttributes_.size(), 0);
}
} // namespace OHOS::Ace::NG