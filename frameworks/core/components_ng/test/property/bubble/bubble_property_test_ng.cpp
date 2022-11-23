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

#include <optional>
#include <string>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/bubble/bubble_layout_property.h"
#include "core/components_ng/pattern/bubble/bubble_render_property.h"
#include "core/components_ng/pattern/bubble/bubble_view.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const bool BUBBLE_PROPERTY_SHOW = true;
const std::string BUBBLE_MESSAGE = "HelloWorld";
constexpr Dimension BUBBLE_PAINT_PROPERTY_ARROW_OFFSET = 20.0_px;
const bool BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW = true;
const bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW = false;
const bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM = false;
const std::vector<Placement> BUBBLE_LAYOUT_PROPERTY_PLACEMENT = {
    Placement::LEFT,
    Placement::RIGHT,
    Placement::TOP,
    Placement::BOTTOM,
    Placement::TOP_LEFT,
    Placement::TOP_RIGHT,
    Placement::BOTTOM_LEFT,
    Placement::BOTTOM_RIGHT,
    Placement::LEFT_BOTTOM,
    Placement::LEFT_TOP,
    Placement::RIGHT_BOTTOM,
    Placement::RIGHT_TOP,
};
const Color BUBBLE_PAINT_PROPERTY_MASK_COLOR = Color::BLUE;
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color::RED;
} // namespace
class BubblePropertyTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: BubblePropertyTest001
 * @tc.desc: Set show value into BubblePropertyTest001 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest001, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto isShow = popupParam->IsShow();
    EXPECT_EQ(isShow, BUBBLE_PROPERTY_SHOW);
}

/**
 * @tc.name: BubblePropertyTest002
 * @tc.desc: set message value into BubblePropertyTest002 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest002, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto message = popupParam->GetMessage();
    EXPECT_EQ(message, BUBBLE_MESSAGE);
}

/**
 * @tc.name: BubblePropertyTest003
 * @tc.desc: set placementOnTop value into BubblePropertyTest003 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest003, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetPlacement(Placement::TOP);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto targetId = frameNode->GetId();
    auto targetTag = frameNode->GetTag();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubbleLayoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    EXPECT_EQ(bubbleLayoutProperty->GetPlacement().value_or(Placement::BOTTOM), Placement::TOP);
}

/**
 * @tc.name: BubblePropertyTest004
 * @tc.desc: set arrowOffset value into BubblePropertyTest004 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest004, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto targetId = frameNode->GetId();
    auto targetTag = frameNode->GetTag();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubblePaintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_FALSE(bubblePaintProperty == nullptr);
    EXPECT_EQ(bubblePaintProperty->GetArrowOffset().value_or(0.0_px), BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
}

/**
 * @tc.name: BubblePropertyTest005
 * @tc.desc: set showInSubWindow value into BubblePropertyTest005 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest005, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto targetId = frameNode->GetId();
    auto targetTag = frameNode->GetTag();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubbleLayoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    EXPECT_EQ(bubbleLayoutProperty->GetShowInSubWindow().value_or(false), BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
}

/**
 * @tc.name: BubblePropertyTest006
 * @tc.desc: set enableArrow value into BubblePropertyTest006 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest006, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubbleLayoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    EXPECT_EQ(bubbleLayoutProperty->GetEnableArrow().value_or(true), BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW);
}

/**
 * @tc.name: BubblePropertyTest007
 * @tc.desc: set primaryButton value into BubblePropertyTest007 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest007, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ButtonProperties properties;
    properties.showButton = true;
    properties.value = BUBBLE_MESSAGE;
    popupParam->SetPrimaryButtonProperties(properties);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto primaryButton = popupParam->GetPrimaryButtonProperties();
    EXPECT_EQ(primaryButton.showButton, true);
    EXPECT_EQ(primaryButton.value, BUBBLE_MESSAGE);
}

/**
 * @tc.name: BubblePropertyTest008
 * @tc.desc: set secondaryButton value into BubblePropertyTest008 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest008, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    ButtonProperties properties;
    properties.showButton = true;
    properties.value = BUBBLE_MESSAGE;
    popupParam->SetSecondaryButtonProperties(properties);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto secondaryButton = popupParam->GetSecondaryButtonProperties();
    EXPECT_EQ(secondaryButton.showButton, true);
    EXPECT_EQ(secondaryButton.value, BUBBLE_MESSAGE);
}

/**
 * @tc.name: BubblePropertyTest009
 * @tc.desc: set UseCustom value into BubblePropertyTest009 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest009, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubbleLayoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
    EXPECT_FALSE(bubbleLayoutProperty == nullptr);
    EXPECT_EQ(bubbleLayoutProperty->GetUseCustom().value_or(true), BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM);
}

/**
 * @tc.name: BubblePropertyTest0010
 * @tc.desc: set a lot of placement value into BubblePropertyTest0010 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest0010, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    for (const auto& placement : BUBBLE_LAYOUT_PROPERTY_PLACEMENT) {
        popupParam->SetPlacement(placement);
        auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
        EXPECT_FALSE(frameNode == nullptr);
        ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
        auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
        EXPECT_FALSE(popupNode == nullptr);
        auto bubbleLayoutProperty = popupNode->GetLayoutProperty<BubbleLayoutProperty>();
        EXPECT_FALSE(bubbleLayoutProperty == nullptr);
        EXPECT_EQ(bubbleLayoutProperty->GetPlacement().value_or(Placement::BOTTOM), placement);
    }
}

/**
 * @tc.name: BubblePropertyTest0011
 * @tc.desc: set autoCancel value into BubblePropertyTest0011 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest0011, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetHasAction(false);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubblePaintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_FALSE(bubblePaintProperty == nullptr);
    EXPECT_EQ(bubblePaintProperty->GetAutoCancel().value_or(true), !popupParam->HasAction());
}

/**
 * @tc.name: BubblePropertyTest0012
 * @tc.desc: set maskColor value into BubblePropertyTest0012 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest0012, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubblePaintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_FALSE(bubblePaintProperty == nullptr);
    EXPECT_EQ(bubblePaintProperty->GetMaskColor().value_or(Color::WHITE), BUBBLE_PAINT_PROPERTY_MASK_COLOR);
}

/**
 * @tc.name: BubblePropertyTest0013
 * @tc.desc: set BackgroundColor value into BubblePropertyTest0013 and get it.
 * @tc.type: FUNC
 */
HWTEST_F(BubblePropertyTestNg, BubblePropertyTest0013, TestSize.Level1)
{
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(frameNode == nullptr);
    ViewAbstract::BindPopup(popupParam, frameNode, nullptr);
    auto popupNode = BubbleView::CreateBubbleNode(frameNode->GetTag(), frameNode->GetId(), popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto bubblePaintProperty = popupNode->GetPaintProperty<BubbleRenderProperty>();
    EXPECT_FALSE(bubblePaintProperty == nullptr);
    EXPECT_EQ(
        bubblePaintProperty->GetBackgroundColor().value_or(Color::WHITE), BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);
}

} // namespace OHOS::Ace::NG