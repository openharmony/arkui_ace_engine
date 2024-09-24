/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/rosen/mock_canvas.h"
#include "test/mock/core/rosen/testing_canvas.h"

#include "base/geometry/ng/rect_t.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/base/geometry_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/option/option_accessibility_property.h"
#include "core/components_ng/pattern/option/option_layout_algorithm.h"
#include "core/components_ng/pattern/option/option_pattern.h"
#include "core/components_ng/pattern/option/option_view.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/geometry_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/pattern/menu/menu_view.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string EMPTY_TEXT = "";
const std::string OPTION_TEST_TEXT = "option";
const Dimension WIDTH = 50.0_vp;
const Dimension HEIGHT = 50.0_vp;
const Dimension DIVIDER_STROKE_WIDTH = 1.0_vp;
const Dimension DIVIDER_START_MARGIN = 10.0_vp;
const Dimension DIVIDER_END_MARGIN = 15.0_vp;
} // namespace

class OptionTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    bool InitOptionTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<OptionPattern> optionPattern_;
    RefPtr<OptionAccessibilityProperty> optionAccessibilityProperty_;

protected:
    PaintWrapper* GetPaintWrapper(RefPtr<OptionPaintProperty> paintProperty);
};

void OptionTestNg::SetUp()
{
    ASSERT_TRUE(InitOptionTestNg());
}

void OptionTestNg::TearDown()
{
    frameNode_ = nullptr;
    optionPattern_ = nullptr;
    optionAccessibilityProperty_ = nullptr;
}
void OptionTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void OptionTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaintWrapper* OptionTestNg::GetPaintWrapper(RefPtr<OptionPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

bool OptionTestNg::InitOptionTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    CHECK_NULL_RETURN(frameNode_, false);

    optionPattern_ = frameNode_->GetPattern<OptionPattern>();
    CHECK_NULL_RETURN(optionPattern_, false);

    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    CHECK_NULL_RETURN(textNode, false);

    optionPattern_->SetTextNode(textNode);

    optionAccessibilityProperty_ = frameNode_->GetAccessibilityProperty<OptionAccessibilityProperty>();
    CHECK_NULL_RETURN(optionAccessibilityProperty_, false);
    return true;
}

/**
 * @tc.name: OptionAccessibilityPropertyGetText001
 * @tc.desc: Test GetText of option.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionAccessibilityPropertyGetText001, TestSize.Level1)
{
    auto textLayoutProperty = optionPattern_->text_->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(OPTION_TEST_TEXT);
    EXPECT_EQ(optionAccessibilityProperty_->GetText(), OPTION_TEST_TEXT);
}

/**
 * @tc.name: OptionAccessibilityPropertyGetSupportAction001
 * @tc.desc: Test GetSupportAction of option.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionAccessibilityPropertyGetSupportAction001, TestSize.Level1)
{
    optionAccessibilityProperty_->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = optionAccessibilityProperty_->GetSupportAction();
    uint64_t actions = 0, expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, expectActions);
}

/**
 * @tc.name: OptionLayoutTest001
 * @tc.desc: Test OptionLayoutAlgorithm layout
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionLayoutTest001, TestSize.Level1)
{
    OHOS::Ace::NG::OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    OHOS::Ace::NG::LayoutWrapperNode* rosenLayoutWrapper = new LayoutWrapperNode(nullptr, rosenRefPtr, rosenMakeRefPtr);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, rosenRefPtr, rosenMakeRefPtr);
    rosenLayoutWrapper->AppendChild(childWrapper);
    rosenOptionLayoutAlgorithm.Layout(rosenLayoutWrapper);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Option Accessibility PerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create option frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG,
        ViewStackProcessor::GetInstance()->ClaimNodeId(), []() { return AceType::MakeRefPtr<OptionPattern>(0); });
    ASSERT_NE(frameNode, nullptr);
    auto optionPattern = frameNode->GetPattern<OptionPattern>();
    ASSERT_NE(optionPattern, nullptr);
    optionPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get option accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto optionAccessibilityProperty = frameNode->GetAccessibilityProperty<OptionAccessibilityProperty>();
    ASSERT_NE(optionAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. Call the callback function in optionAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(optionAccessibilityProperty->ActActionSelect());
}
/**
 * @tc.name: PerformActionTest002
 * @tc.desc:  Test OptionPattern OnHover, OnPress, OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, PerformActionTest002, TestSize.Level1)
{
    optionPattern_->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    /**
     * @tc.steps: step1. Call OnHover.
     * @tc.expected: the function runs normally
     */
    bool isHover[2] = { false, true };
    Color hoverColor[2] = { Color::TRANSPARENT, Color(0x0c000000) };
    for (int turn = 0; turn < 2; turn++) {
        optionPattern_->OnHover(isHover[turn]);
        EXPECT_EQ(optionPattern_->GetBgBlendColor(), hoverColor[turn]);
    }
    /**
     * @tc.steps: step2. construct keyEvent and call OnKeyEvent.
     * @tc.expected: the function runs normally
     */
    KeyEvent event;
    EXPECT_FALSE(optionPattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(optionPattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(optionPattern_->OnKeyEvent(event));
    /**
     * @tc.steps: step3. construct TouchEventInfo and call OnPress.
     * @tc.expected: the value of bgBlendColor is right
     */
    TouchEventInfo touchInfo("touchUP");
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::UP);
    touchInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    for (int turn = 0; turn < 2; turn++) {
        optionPattern_->SetIsHover(isHover[turn]);
        optionPattern_->OnPress(touchInfo);
        EXPECT_EQ(optionPattern_->GetBgBlendColor(), hoverColor[turn]);
    }

    TouchEventInfo touchInfo2("touchDown");
    TouchLocationInfo touchLocationInfo2(1);
    touchLocationInfo2.SetTouchType(TouchType::DOWN);
    touchInfo2.AddTouchLocationInfo(std::move(touchLocationInfo2));
    optionPattern_->OnPress(touchInfo2);
    EXPECT_EQ(optionPattern_->GetBgBlendColor(), optionPattern_->selectTheme_->GetClickedColor());
}
/**
 * @tc.name: OptionLayoutTest002
 * @tc.desc: Test OptionLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionLayoutTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct optionLayoutAlgorithm and layoutWrapper.
     */
    OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    LayoutWrapperNode* rosenLayoutWrapper = new LayoutWrapperNode(nullptr, rosenRefPtr, rosenMakeRefPtr);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, rosenRefPtr, rosenMakeRefPtr);
    rosenLayoutWrapper->AppendChild(childWrapper);
    rosenLayoutWrapper->hostNode_ = frameNode_;
    optionPattern_->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    /**
     * @tc.steps: step2. construct layoutConstraint and call Measure.
     * @tc.expected: the value of horInterval_ is updated
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    rosenLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    rosenLayoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    MeasureProperty calcLayoutConstraint;
    rosenLayoutWrapper->GetLayoutProperty()->UpdateCalcLayoutProperty(calcLayoutConstraint);
    rosenOptionLayoutAlgorithm.Measure(rosenLayoutWrapper);
    EXPECT_NE(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    EXPECT_EQ(rosenLayoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 0);
}

/**
 * @tc.name: OptionPaintPropertyTestNg001
 * @tc.desc: Verify Property Update.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintPropertyTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object OptionPaintProperty.
     * @tc.expected: property has not value.
     */
    OptionPaintProperty property;
    EXPECT_FALSE(property.GetHover().has_value());
    EXPECT_FALSE(property.GetPress().has_value());
    EXPECT_FALSE(property.GetNeedDivider().has_value());
    EXPECT_FALSE(property.GetHasIcon().has_value());
    /**
     * @tc.steps: step2. Update property value.
     * @tc.expected: property value are as expected.
     */
    property.UpdateHover(true);
    property.UpdatePress(true);
    property.UpdateNeedDivider(true);
    property.UpdateHasIcon(true);
    EXPECT_TRUE(property.GetHover().value());
    EXPECT_TRUE(property.GetPress().value());
    EXPECT_TRUE(property.GetNeedDivider().value());
    EXPECT_TRUE(property.GetHasIcon().value());
}

/**
 * @tc.name: OptionPaintPropertyTestNg002
 * @tc.desc: Verify Property Reset.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintPropertyTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object OptionPaintProperty, udpate property
     * @tc.expected: property value are as expected.
     */
    OptionPaintProperty property;
    property.UpdateHover(true);
    property.UpdatePress(true);
    property.UpdateNeedDivider(true);
    property.UpdateHasIcon(true);
    EXPECT_TRUE(property.GetHover().value());
    EXPECT_TRUE(property.GetPress().value());
    EXPECT_TRUE(property.GetNeedDivider().value());
    EXPECT_TRUE(property.GetHasIcon().value());
    /**
     * @tc.steps: step2. reset property
     * @tc.expected: property value are as expected.
     */
    property.Reset();
    EXPECT_FALSE(property.GetHover().has_value());
    EXPECT_FALSE(property.GetPress().has_value());
    EXPECT_FALSE(property.GetNeedDivider().has_value());
    EXPECT_FALSE(property.GetHasIcon().has_value());
}

/**
 * @tc.name: OptionPaintPropertyTestNg003
 * @tc.desc: Verify Property Clone.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintPropertyTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object OptionPaintProperty, update property
     */
    OptionPaintProperty property;
    property.UpdateHover(true);
    property.UpdatePress(true);
    property.UpdateNeedDivider(true);
    property.UpdateHasIcon(true);
    /**
     * @tc.steps: step2. clone property
     * @tc.expected: property value are as expected.
     */
    auto cloneProperty = AceType::DynamicCast<OptionPaintProperty>(property.Clone());
    ASSERT_NE(cloneProperty, nullptr);
    EXPECT_TRUE(property.GetHover());
    EXPECT_TRUE(property.GetPress());
    EXPECT_TRUE(property.GetNeedDivider());
    EXPECT_TRUE(property.GetHasIcon());
}

/**
 * @tc.name: OptionPaintPropertyTestNg004
 * @tc.desc: Verify ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintPropertyTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object OptionPaintProperty, update property
     */
    OptionPaintProperty property;
    property.UpdateHover(true);
    property.UpdateNeedDivider(true);
    property.UpdateHasIcon(true);
    /**
     * @tc.steps: step2. clone property
     * @tc.expected: property value are as expected.
     */
    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("hover"), "true");
    EXPECT_EQ(json->GetString("needDivider"), "true");
    EXPECT_EQ(json->GetString("hasIcon"), "true");
}

/**
 * @tc.name: OptionPaintPropertyTestNg005
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintPropertyTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Build a object OptionPaintProperty, udpate property
     */
    OptionPaintProperty property;
    /**
     * @tc.steps: step2. clone property
     * @tc.expected: property value are as expected.
     */
    auto json = JsonUtil::Create(true);
    property.ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("hover"), "false");
    EXPECT_EQ(json->GetString("needDivider"), "true");
    EXPECT_EQ(json->GetString("hasIcon"), "false");
}

/**
 * @tc.name: OptionPaintMethodTestNg001
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paint method object.
     */
    RefPtr<OptionPaintProperty> paintProp = AceType::MakeRefPtr<OptionPaintProperty>();
    RefPtr<OptionPaintMethod> paintMethod = AceType::MakeRefPtr<OptionPaintMethod>();
    PaintWrapper* paintWrapper = GetPaintWrapper(paintProp);
    /**
     * @tc.steps: step2. execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg002
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<OptionPattern>(0));
    ASSERT_NE(optionNode, nullptr);
    auto renderContext = optionNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProp = optionNode->GetPaintProperty<OptionPaintProperty>();
    ASSERT_NE(paintProp, nullptr);
    RefPtr<OptionPaintMethod> paintMethod = AceType::MakeRefPtr<OptionPaintMethod>();
    paintProp->UpdatePress(false);
    paintProp->UpdateHover(false);
    paintProp->UpdateNeedDivider(true);
    paintProp->UpdateHasIcon(true);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. Execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
    /**
     * @tc.steps: step3. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg003
 * @tc.desc: Verify select option attributes default value and their get and set function.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintMethodTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Verify the default value of flags.
     * @tc.expected: The value of isWidthModifiedBySelect_ and isSelectOption_ should be false.
     */
    EXPECT_FALSE(optionPattern_->IsWidthModifiedBySelect());
    EXPECT_FALSE(optionPattern_->IsSelectOption());
    /**
     * @tc.steps: step2. Update flags value and check them.
     * @tc.expected: Flags value are as expected, which are true.
     */
    optionPattern_->SetIsWidthModifiedBySelect(true);
    optionPattern_->SetIsSelectOption(true);
    EXPECT_TRUE(optionPattern_->IsWidthModifiedBySelect());
    EXPECT_TRUE(optionPattern_->IsSelectOption());
}

/**
 * @tc.name: OptionLayoutTest003
 * @tc.desc: Test OptionLayoutAlgorithm Measure when option belongs to a select, mainly test GetSelectOptionWidth.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionLayoutTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct option layout algorithm and layout wrapper and set the horizontal interval.
     * @tc.expected: The horizontal interval is setted successfully.
     */
    OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    /**
     * @tc.steps: step2. Construct the reference pointer of layout property and geometry node, set the margin of
     * geometry node to be null.
     * @tc.expected: the value of horInterval_ is updated
     */
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    /**
     * @tc.steps: step3. Construct a layout wrapper node with the previous reference pointers and set another
     * layout wrapper node to be its child node.
     * @tc.expected: Objects are constructed successfully.
     */
    LayoutWrapperNode* rosenLayoutWrapper = new LayoutWrapperNode(nullptr, rosenRefPtr, rosenMakeRefPtr);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(nullptr, rosenRefPtr, rosenMakeRefPtr);
    rosenLayoutWrapper->AppendChild(childWrapper);
    rosenLayoutWrapper->hostNode_ = frameNode_;
    optionPattern_->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    /**
     * @tc.steps: step4. Construct and update layout and content constraint,set the flag to claim that this is
     * a select option and call Measure.
     * @tc.expected: Objects are constructed successfully.
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    rosenLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    rosenLayoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    MeasureProperty calcLayoutConstraint;
    rosenLayoutWrapper->GetLayoutProperty()->UpdateCalcLayoutProperty(calcLayoutConstraint);
    optionPattern_->SetIsSelectOption(true);
    rosenOptionLayoutAlgorithm.Measure(rosenLayoutWrapper);
    /**
     * @tc.steps: step5. After the measure of option layout algorithm, compare the horizontal interval of option
     * layout algorithm with the previous setted value. Compare frame width in the geometry node of option layout
     * algorithm with the default width value.
     * @tc.expected: The value of horInterval_ is updated and is no longer equal to the previous setted value.
     * Frame width in the geometry node of option layout algorithm is equal to the default value of the frame size,
     * which is 0.
     */
    EXPECT_NE(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    EXPECT_EQ(rosenLayoutWrapper->GetGeometryNode()->GetFrameSize().Width(), 0);
}

/**
 * @tc.name: OptionLayoutTest004
 * @tc.desc: Test OptionLayoutAlgorithm Measure when the flag indicates that the option belongs to a select, mainly
 * test GetSelectOptionWidth.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionLayoutTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Get the width of select option without setting it, this case is meant to test the correctness
     * of its default value.
     * @tc.expected: Default width of select option should be 0.0.
     */
    ASSERT_NE(optionPattern_, nullptr);
    auto OptionWidth = optionPattern_->GetSelectOptionWidth();
    ASSERT_NE(OptionWidth, 0.0);
}

/**
* @tc.name: CreatePasteButton001
* @tc.desc: Test OptionView whether the created node tag is a pastebutton
* @tc.type: FUNC
*/
HWTEST_F(OptionTestNg, CreatePasteButton001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create option node.
     * @tc.expected: Option node created success.
     */
    auto Id = ElementRegister::GetInstance()->MakeUniqueId();
    auto option = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, Id, AceType::MakeRefPtr<OptionPattern>(0));

    /**
     * @tc.steps: step2. Create row node.
     * @tc.expected: Row node created success.
     */
    auto row = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<LinearLayoutPattern>(false));

    /**
     * @tc.steps: step3. Create pasteButton node.
     * @tc.expected: The child node pastebutton can be obtained through the parent node option.
     */
    OptionView::CreatePasteButton(false, option, row, []() {});
    auto PasteButtonNode = option->GetChildAtIndex(0)->GetChildren();
    EXPECT_FALSE(PasteButtonNode.empty());
}

/**
 * @tc.name: OptionLayoutTest005
 * @tc.desc: Test OptionLayoutAlgorithm Measure
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionLayoutTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. construct optionLayoutAlgorithm and layoutWrapper.
     */
    OptionLayoutAlgorithm rosenOptionLayoutAlgorithm;
    rosenOptionLayoutAlgorithm.horInterval_ = 2.0;
    EXPECT_FLOAT_EQ(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    auto rosenMakeRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::LayoutProperty>();
    auto rosenRefPtr = AceType::MakeRefPtr<OHOS::Ace::NG::GeometryNode>();
    rosenRefPtr->margin_ = nullptr;
    SelectParam param = { "optiontest", " " };
    RefPtr<FrameNode> optionNode = OptionView::CreateSelectOption(param, 2);
    LayoutWrapperNode* rosenLayoutWrapper = new LayoutWrapperNode(optionNode, rosenRefPtr, rosenMakeRefPtr);
    auto childWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(optionNode, rosenRefPtr, rosenMakeRefPtr);
    rosenLayoutWrapper->AppendChild(childWrapper);
    rosenLayoutWrapper->hostNode_ = frameNode_;
    optionPattern_->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    /**
     * @tc.steps: step2. construct layoutConstraint and call Measure.
     * @tc.expected: the value of horInterval_ is updated
     */
    LayoutConstraintF layoutConstraintSize;
    layoutConstraintSize.selfIdealSize.SetSize(SizeF(WIDTH.ConvertToPx(), HEIGHT.ConvertToPx()));
    rosenLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(layoutConstraintSize);
    rosenLayoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    MeasureProperty calcLayoutConstraint;
    calcLayoutConstraint.UpdateMinSizeWithCheck(CalcSize(CalcLength(10.0), CalcLength(10.0)));
    rosenLayoutWrapper->GetLayoutProperty()->UpdateCalcLayoutProperty(calcLayoutConstraint);
    auto tmpOptionNode = rosenLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(tmpOptionNode);
    auto optionPattern = tmpOptionNode->GetPattern<OptionPattern>();
    CHECK_NULL_VOID(optionPattern);
    optionPattern->SetIsSelectOption(true);
    optionPattern->SetHasOptionWidth(true);
    rosenOptionLayoutAlgorithm.Measure(rosenLayoutWrapper);
    EXPECT_NE(rosenOptionLayoutAlgorithm.horInterval_, 2.0);
    EXPECT_TRUE(optionPattern->IsSelectOption());
    EXPECT_TRUE(optionPattern->GetHasOptionWidth());
}
/**
 * @tc.name: PerformActionTest003
 * @tc.desc:  Test OptionPattern OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, PerformActionTest003, TestSize.Level1)
{
    optionPattern_->selectTheme_ = AceType::MakeRefPtr<SelectTheme>();
    std::vector<SelectParam> params;
    auto wrapperNode = MenuView::Create(params, 3, "");
    ASSERT_NE(wrapperNode, nullptr);
    auto menuNode = AceType::DynamicCast<FrameNode>(wrapperNode->GetChildAtIndex(0));
    ASSERT_NE(menuNode, nullptr);
    ASSERT_EQ(menuNode->GetChildren().size(), 1);

    params.push_back({ "content1", "icon1" });
    params.push_back({ "content2", "" });
    params.push_back({ "", "icon3" });
    params.push_back({ "", "" });
    auto menuPattern = menuNode->GetPattern<MenuPattern>();
    ASSERT_NE(menuPattern, nullptr);
    menuPattern->UpdateSelectParam(params);
    optionPattern_->SetMenu(menuNode);
    /**
     * @tc.steps: step1. Call OnHover.
     * @tc.expected: the function runs normally
     */
    bool isHover[2] = { false, true };
    Color hoverColor[2] = { Color::TRANSPARENT, Color(0x0c000000) };
    for (int turn = 0; turn < 2; turn++) {
        optionPattern_->OnHover(isHover[turn]);
        EXPECT_EQ(optionPattern_->GetBgBlendColor(), hoverColor[turn]);
    }
    /**
     * @tc.steps: step2. construct keyEvent and call OnKeyEvent.
     * @tc.expected: the function runs normally
     */
    KeyEvent event;
    EXPECT_FALSE(optionPattern_->OnKeyEvent(event));
    event.action = KeyAction::DOWN;
    EXPECT_FALSE(optionPattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(optionPattern_->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_HOME;
    optionPattern_->isSelectOption_ = true;
    EXPECT_TRUE(optionPattern_->OnKeyEvent(event));
}
/**
 * @tc.name: OptionPaintMethodTestNg004
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintMethodTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<OptionPattern>(0));
    ASSERT_NE(optionNode, nullptr);
    auto renderContext = optionNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProp = optionNode->GetPaintProperty<OptionPaintProperty>();
    ASSERT_NE(paintProp, nullptr);
    RefPtr<OptionPaintMethod> paintMethod = AceType::MakeRefPtr<OptionPaintMethod>();
    paintProp->UpdatePress(false);
    paintProp->UpdateHover(false);
    paintProp->UpdateNeedDivider(true);
    paintProp->UpdateHasIcon(false);
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. Execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg005
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionTestNg, OptionPaintMethodTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<OptionPattern>(0));
    ASSERT_NE(optionNode, nullptr);
    auto renderContext = optionNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    auto paintProp = optionNode->GetPaintProperty<OptionPaintProperty>();
    ASSERT_NE(paintProp, nullptr);
    RefPtr<OptionPaintMethod> paintMethod = AceType::MakeRefPtr<OptionPaintMethod>();
    paintProp->UpdatePress(false);
    paintProp->UpdateHover(false);
    paintProp->UpdateNeedDivider(true);
    paintProp->UpdateHasIcon(true);
    SelectDivider divider;
    divider.color = Color::RED;
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    divider.startMargin = DIVIDER_START_MARGIN;
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(1));
    /**
     * @tc.steps: step2. Execute GetOverlayDrawFunction.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
    /**
     * @tc.steps: step3. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
    /**
     * @tc.steps: step3. update press to true.
     * @tc.expected:  return value are as expected.
     */
    paintProp->UpdatePress(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}
} // namespace OHOS::Ace::NG
