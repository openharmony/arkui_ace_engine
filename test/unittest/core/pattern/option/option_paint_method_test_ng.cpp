/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/menu/menu_item/menu_item_pattern.h"
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
const Dimension DIVIDER_STROKE_WIDTH = 1.0_vp;
const Dimension DIVIDER_START_MARGIN = 10.0_vp;
const Dimension DIVIDER_END_MARGIN = 15.0_vp;
} // namespace

class OptionPaintMethodTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    bool InitOptionTestNg();
    RefPtr<FrameNode> frameNode_;
    RefPtr<MenuItemPattern> optionPattern_;
    RefPtr<OptionAccessibilityProperty> optionAccessibilityProperty_;

protected:
    PaintWrapper* GetPaintWrapper(RefPtr<OptionPaintProperty> paintProperty);
};

void OptionPaintMethodTestNg::SetUp()
{
    ASSERT_TRUE(InitOptionTestNg());
}

void OptionPaintMethodTestNg::TearDown()
{
    frameNode_ = nullptr;
    optionPattern_ = nullptr;
    optionAccessibilityProperty_ = nullptr;
}
void OptionPaintMethodTestNg::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SelectTheme>()));
}

void OptionPaintMethodTestNg::TearDownTestCase()
{
    MockPipelineContext::TearDown();
}

PaintWrapper* OptionPaintMethodTestNg::GetPaintWrapper(RefPtr<OptionPaintProperty> paintProperty)
{
    WeakPtr<RenderContext> renderContext;
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProperty);
    return paintWrapper;
}

bool OptionPaintMethodTestNg::InitOptionTestNg()
{
    frameNode_ = FrameNode::GetOrCreateFrameNode(V2::OPTION_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
        []() { return AceType::MakeRefPtr<MenuItemPattern>(true, 0); });
    CHECK_NULL_RETURN(frameNode_, false);

    optionPattern_ = frameNode_->GetPattern<MenuItemPattern>();
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
 * @tc.name: OptionPaintMethodTestNg001
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg002
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
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
}

/**
 * @tc.name: OptionPaintMethodTestNg003
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
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
}

/**
 * @tc.name: OptionPaintMethodTestNg004
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg005
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg006
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
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
}

/**
 * @tc.name: OptionPaintMethodTestNg007
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg008
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    divider.startMargin = DIVIDER_START_MARGIN;
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
}

/**
 * @tc.name: OptionPaintMethodTestNg009
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
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
}

/**
 * @tc.name: OptionPaintMethodTestNg010
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg011
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg012
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg013
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg014
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
}

/**
 * @tc.name: OptionPaintMethodTestNg015
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg016
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg017
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg018
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg019
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg020
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg021
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg022
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    divider.startMargin = DIVIDER_START_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg023
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg024
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg025
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg026
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg027
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.startMargin = DIVIDER_START_MARGIN;
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}

/**
 * @tc.name: OptionPaintMethodTestNg028
 * @tc.desc: Verify ToJsonValue default value.
 * @tc.type: FUNC
 */
HWTEST_F(OptionPaintMethodTestNg, OptionPaintMethodTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. prepare paintMethod, paintProp, canvas.
     */
    auto optionNode = FrameNode::CreateFrameNode(V2::OPTION_ETS_TAG, 0, AceType::MakeRefPtr<MenuItemPattern>(true, 0));
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
    divider.strokeWidth = DIVIDER_STROKE_WIDTH;
    divider.startMargin = DIVIDER_START_MARGIN;
    divider.endMargin = DIVIDER_END_MARGIN;
    paintProp->UpdateDivider(divider);
    EXPECT_TRUE(paintProp->HasDivider());
    Testing::MockCanvas canvas;
    EXPECT_CALL(canvas, AttachBrush(_)).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DetachBrush()).WillRepeatedly(ReturnRef(canvas));
    EXPECT_CALL(canvas, DrawPath(_)).Times(AtLeast(0));
    /**
     * @tc.steps: step2. update hover to true.
     * @tc.expected:  return value are as expected.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    PaintWrapper* paintWrapper = new PaintWrapper(renderContext, geometryNode, paintProp);
    paintProp->UpdateHover(true);
    paintWrapper = GetPaintWrapper(paintProp);
    paintMethod->PaintDivider(canvas, paintWrapper);
    auto result = paintMethod->GetOverlayDrawFunction(paintWrapper);
    EXPECT_NE(result, nullptr);
    delete paintWrapper;
    paintWrapper = nullptr;
}
} // namespace OHOS::Ace::NG
