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
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
const bool BUBBLE_PROPERTY_SHOW = true;
const std::string BUBBLE_MESSAGE = "HelloWorld";
const std::string BUBBLE_NEW_MESSAGE = "Good";
constexpr Dimension BUBBLE_PAINT_PROPERTY_ARROW_OFFSET = 20.0_px;
const bool BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW = true;
const bool BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW = false;
const bool BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM = true;
const Color BUBBLE_PAINT_PROPERTY_MASK_COLOR = Color::BLUE;
const Color BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR = Color::RED;
} // namespace

class BubbleLayoutTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: BubbleLayoutTest001
 * @tc.desc: Test layout of bubble.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest001, TestSize.Level1)
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
 * @tc.name: BubbleLayoutTest002
 * @tc.desc: Test CreateCustomBubbleNode of bubble and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest002, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(BUBBLE_LAYOUT_PROPERTY_USE_CUSTOM);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);

    // create customBubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(targetNode == nullptr);
    auto rowFrameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG, 0, AceType::MakeRefPtr<LinearLayoutPattern>(false));
    EXPECT_FALSE(rowFrameNode == nullptr);
    auto blankFrameNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(blankFrameNode == nullptr);
    rowFrameNode->AddChild(blankFrameNode);
    auto popupNode =
        BubbleView::CreateCustomBubbleNode(targetNode->GetTag(), targetNode->GetId(), rowFrameNode, popupParam);
    EXPECT_FALSE(popupNode == nullptr);

    // update customBubbleNode
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
}

/**
 * @tc.name: BubbleLayoutTest003
 * @tc.desc: Test CreateBubbleNode with message and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest003, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetArrowOffset(BUBBLE_PAINT_PROPERTY_ARROW_OFFSET);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(false);
    popupParam->SetMaskColor(BUBBLE_PAINT_PROPERTY_MASK_COLOR);
    popupParam->SetHasAction(false);
    popupParam->SetBackgroundColor(BUBBLE_PAINT_PROPERTY_BACK_GROUND_COLOR);

    // create bubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(targetNode == nullptr);
    auto targetTag = targetNode->GetTag();
    auto targetId = targetNode->GetId();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto firstTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(firstTextNode == nullptr);

    // update BubbleNode
    auto popupId = popupNode->GetId();
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetUseCustomComponent(!popupParam->IsUseCustom());
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    auto secondTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(secondTextNode == nullptr);
}

/**
 * @tc.name: BubbleLayoutTest004
 * @tc.desc: Test CreateBubbleNode with CreateCombinedChild and Update.
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest004, TestSize.Level1)
{
    // set value to popupParam
    auto popupParam = AceType::MakeRefPtr<PopupParam>();
    popupParam->SetIsShow(BUBBLE_PROPERTY_SHOW);
    popupParam->SetMessage(BUBBLE_MESSAGE);
    popupParam->SetShowInSubWindow(BUBBLE_LAYOUT_PROPERTY_SHOW_IN_SUBWINDOW);
    popupParam->SetEnableArrow(BUBBLE_LAYOUT_PROPERTY_ENABLE_ARROW);
    popupParam->SetPlacement(Placement::BOTTOM_RIGHT);
    popupParam->SetUseCustomComponent(false);
    popupParam->SetHasAction(false);
    ButtonProperties primaryProperties;
    primaryProperties.showButton = false;
    primaryProperties.value = BUBBLE_MESSAGE;
    popupParam->SetPrimaryButtonProperties(primaryProperties);
    ButtonProperties secondProperties;
    secondProperties.showButton = false;
    secondProperties.value = BUBBLE_NEW_MESSAGE;
    popupParam->SetSecondaryButtonProperties(secondProperties);

    // create bubbleNode
    auto targetNode = FrameNode::GetOrCreateFrameNode(V2::BUTTON_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    EXPECT_FALSE(targetNode == nullptr);
    auto targetTag = targetNode->GetTag();
    auto targetId = targetNode->GetId();
    auto popupNode = BubbleView::CreateBubbleNode(targetTag, targetId, popupParam);
    EXPECT_FALSE(popupNode == nullptr);
    auto popupId = popupNode->GetId();
    auto textNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(textNode == nullptr);

    // update BubbleNode
    popupParam->SetPlacement(Placement::LEFT);
    popupParam->SetMessage(BUBBLE_NEW_MESSAGE);
    popupParam->SetUseCustomComponent(!popupParam->IsUseCustom());
    popupParam->SetHasAction(true);
    BubbleView::UpdatePopupParam(popupId, popupParam, targetNode);
    auto secondTextNode = BubbleView::CreateMessage(popupParam->GetMessage(), popupParam->IsUseCustom());
    EXPECT_FALSE(secondTextNode == nullptr);
}

/**
 * @tc.name: BubbleLayoutTest005
 * @tc.desc: Test BubbleNode layout
 * @tc.type: FUNC
 */
HWTEST_F(BubbleLayoutTestNg, BubbleLayoutTest005, TestSize.Level1) {}

} // namespace OHOS::Ace::NG