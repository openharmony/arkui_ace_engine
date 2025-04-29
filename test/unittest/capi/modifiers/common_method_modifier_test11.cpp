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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"

#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components/button/button_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "base/geometry/ng/offset_t.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ACCESSABLE_PROP_TEXT = "propText";
    const auto ACCESSABLE_PROP_TEXT_VALUE = "Hello, World!";
    const auto BUBBLE_LAYOUT_PROP = "bubbleLayoutProperty";
    const auto BUBBLE_LAYOUT_PROP_PLACEMENT = "placement";
    const auto BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM = "Placement::BOTTOM";
    const auto BUBBLE_LAYOUT_PROP_PLACEMENT_TOP = "Placement::TOP";
    const auto BUBBLE_LAYOUT_PROP_TARGET_SPACE = "targetSpace";
    const auto BUBBLE_LAYOUT_PROP_ENABLE_ARROW = "enableArrow";
    const auto BUBBLE_LAYOUT_PROP_ENABLE_HOVER_MODE = "enableHoverMode";
    const auto BUBBLE_LAYOUT_PROP_FOLLOW_TRANSFORM = "followTransformOfTarget";
    const auto BUBBLE_LAYOUT_PROP_BLOCK_EVENT = "blockEvent";
    const auto BUBBLE_LAYOUT_PROP_POSITION_OFFSET = "positionOffset";
    const auto BUBBLE_LAYOUT_PROP_SHOW_IN_SUBWINDOW = "showInSubWindow";
    const auto BUBBLE_RENDER_PROP = "bubbleRenderProperty";
    const auto BUBBLE_RENDER_PROP_ARROW_OFFSET = "arrowOffset";
    const auto BUBBLE_RENDER_PROP_AUTO_CANCEL = "autoCancel";
    const auto BUBBLE_RENDER_PROP_MASK_COLOR = "maskColor";
    const auto BUBBLE_RENDER_PROP_POPUP_COLOR = "popupColor";

    const auto TEST_COLOR_BLUE_NUM = 0xFF0000FF;
    const auto TEST_COLOR_BLUE_STR = "#FF0000FF";
    const auto TEST_COLOR_BLUE = Color::BLUE;
    const auto THEME_COLOR_RED = Color::RED;
    const auto TEST_COLOR_RES_NAME = "test_color_res_name";
    const auto TEST_COLOR_RESOURCE = CreateResource(TEST_COLOR_RES_NAME, Converter::ResourceType::COLOR);
}

class CommonMethodModifierTest11 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        auto theme = SetupThemeStyle(THEME_PATTERN_POPUP);
        theme->SetAttr("popup_mask_color",
            { .value = THEME_COLOR_RED });
        theme->SetAttr(PATTERN_BG_COLOR,
            { .value = THEME_COLOR_RED });
        SetupTheme<PopupTheme>();
        SetupTheme<ButtonTheme>();
        AddResource(TEST_COLOR_RES_NAME, TEST_COLOR_BLUE);
    }
};

/*
 * @tc.name: bindPopupPopupOptionsInitialPopupInfoTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsInitialPopupInfoTest, TestSize.Level1)
{
    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    EXPECT_FALSE(overlayManager->HasPopupInfo(blankRef->GetId()));
}

/*
 * @tc.name: bindPopupPopupOptionsMessageTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsMessageTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto checkValue = GetAttrValue<std::string>(
        reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)),
        ACCESSABLE_PROP_TEXT);
    EXPECT_EQ(checkValue, ACCESSABLE_PROP_TEXT_VALUE);
}

/*
 * @tc.name: bindPopupPopupOptionsPlacementDeafultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPlacementDefaultValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

/*
 * @tc.name: bindPopupPopupOptionsPlacementValidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPlacementValidValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(
            Converter::ArkValue<Ark_Placement>(Ark_Placement::ARK_PLACEMENT_TOP))
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_TOP);
}

/*
 * @tc.name: bindPopupPopupOptionsPlacementInvalidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPlacementInvalidValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(
            Converter::ArkValue<Ark_Placement>(static_cast<Ark_Placement>(-1)))
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

// deprecated
/*
 * @tc.name: bindPopupPopupOptionsPlacementOnTopDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPlacementOnTopDefaultValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Empty()),
        .placementOnTop = Converter::ArkValue<Opt_Boolean>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

// deprecated
/*
 * @tc.name: bindPopupPopupOptionsPlacementOnTopTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPlacementOnTopTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Empty()),
        .placementOnTop = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_TOP);

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Empty()),
        .placementOnTop = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false))
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

/*
 * @tc.name: bindPopupPopupOptionsArrowOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsArrowOffsetTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "0.00px");

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .arrowOffset = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(1._px)),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "1.00px");

    // dont check negative value since it is clamped-ed during a layout process
}

/*
 * @tc.name: bindPopupPopupOptionsArrowOffsetPointPositionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsArrowOffsetPointPositionTest, TestSize.Level1)
{
    // default value
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "0.00px");

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(
            Converter::ArkValue<Ark_ArrowPointPosition>(Ark_ArrowPointPosition::ARK_ARROW_POINT_POSITION_CENTER))
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "50.00%");

    // dont check negative value since it is clamped-ed during a layout process
}

/*
 * @tc.name: bindPopupPopupOptionsTargetSpaceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsTargetSpaceTest, TestSize.Level1)
{
    // default value
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .targetSpace = Converter::ArkValue<Opt_Length>(Ark_Empty()),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "8.00vp"); // default from PopupTheme

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .targetSpace = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(1._px)),
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .targetSpace = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(-1._px)),
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "-1.00px");
}

/*
 * @tc.name: bindPopupPopupOptionsEnableArrowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsEnableArrowTest, TestSize.Level1)
{
    // default value
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .enableArrow = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_ARROW);
    EXPECT_TRUE(checkValue); // default from PopupParam

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .enableArrow = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_ARROW);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsEnableHoverModeDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsEnableHoverModeDefaultValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .enableHoverMode = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_HOVER_MODE);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsEnableHoverModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsEnableHoverModeTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .enableHoverMode = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_HOVER_MODE);
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsFollowTransformOfTargetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsFollowTransformOfTargetTest, TestSize.Level1)
{
    // default value
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .followTransformOfTarget = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_FOLLOW_TRANSFORM);
    EXPECT_FALSE(checkValue); // default from PopupParam

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .followTransformOfTarget = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true)),
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_FOLLOW_TRANSFORM);
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsAutoCancelDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsAutoCancelDefaultValueTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .autoCancel = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_AUTO_CANCEL);
    EXPECT_TRUE(checkValue); // default from PopupParam, autoCancel = !hasAction
}

/*
 * @tc.name: bindPopupPopupOptionsAutoCancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsAutoCancelTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .autoCancel = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true)),
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_AUTO_CANCEL);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsMaskBlockEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsMaskBlockEventTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_BLOCK_EVENT);
    EXPECT_TRUE(checkValue);

    Ark_Union_Boolean_Literal_ResourceColor_color arkUnionMask;
    TypeHelper::WriteToUnion<Ark_Boolean>(arkUnionMask) = Converter::ArkValue<Ark_Boolean>(false);
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(arkUnionMask)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_BLOCK_EVENT);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsMaskColorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsMaskColorDefaultTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, THEME_COLOR_RED.ToString()); // set & get from PopupTheme
}

/*
 * @tc.name: bindPopupPopupOptionsMaskColorColorNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsMaskColorColorNumberTest, TestSize.Level1)
{
    // color as ark_color
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    auto colorArkColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(Ark_Color::ARK_COLOR_BLUE);
    Ark_Literal_ResourceColor_color literalColor = { .color = colorArkColor };
    Ark_Union_Boolean_Literal_ResourceColor_color arkUnionMask;
    TypeHelper::WriteToUnion<Ark_Literal_ResourceColor_color>(arkUnionMask) = literalColor;
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(arkUnionMask)
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as number
    auto colorArkNumber = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(TEST_COLOR_BLUE_NUM);
    literalColor = { .color = colorArkNumber };
    TypeHelper::WriteToUnion<Ark_Literal_ResourceColor_color>(arkUnionMask) = literalColor;
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(arkUnionMask)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsMaskColorStringResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsMaskColorStringResourceTest, TestSize.Level1)
{
    // color as string
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    auto colorArkStr = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(TEST_COLOR_BLUE_STR);
    Ark_Literal_ResourceColor_color literalColor = { .color = colorArkStr };
    Ark_Union_Boolean_Literal_ResourceColor_color arkUnionMask;
    TypeHelper::WriteToUnion<Ark_Literal_ResourceColor_color>(arkUnionMask) = literalColor;
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(arkUnionMask)
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as resource
    auto colorArkRes = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(TEST_COLOR_RESOURCE);
    literalColor = { .color = colorArkRes };
    TypeHelper::WriteToUnion<Ark_Literal_ResourceColor_color>(arkUnionMask) = literalColor;
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .mask = Converter::ArkValue<Opt_Union_Boolean_Literal_ResourceColor_color>(arkUnionMask)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsOffsetTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .offset = Converter::ArkValue<Opt_Position>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_POSITION_OFFSET);
    EXPECT_EQ(checkValue, "Offset (0.00, 0.00)");

    const auto xLength = 1.1f;
    const auto yLength = 2.2f;
    Ark_Position arkPosition = {
        .x = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(xLength)),
        .y = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(yLength))
    };
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .offset = Converter::ArkValue<Opt_Position>(arkPosition)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_POSITION_OFFSET);
    EXPECT_EQ(checkValue, OffsetF(xLength, yLength).ToString());
}

/*
 * @tc.name: bindPopupPopupOptionsPopupColorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPopupColorDefaultTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .popupColor = Converter::ArkValue<Opt_Union_Color_String_Resource_Number>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, THEME_COLOR_RED.ToString()); // set & get from PopupTheme
}

/*
 * @tc.name: bindPopupPopupOptionsPopupColorColorStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPopupColorColorStringTest, TestSize.Level1)
{
    // color as arkcolor
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    auto colorArkColor = Converter::ArkValue<Ark_Color>(Ark_Color::ARK_COLOR_BLUE);
    Ark_Union_Color_String_Resource_Number arkUnionPopupColor;
    TypeHelper::WriteToUnion<Ark_Color>(arkUnionPopupColor) = colorArkColor;

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .popupColor = Converter::ArkValue<Opt_Union_Color_String_Resource_Number>(arkUnionPopupColor)
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as string
    auto colorArkStr = Converter::ArkValue<Ark_String>(TEST_COLOR_BLUE_STR);
    TypeHelper::WriteToUnion<Ark_String>(arkUnionPopupColor) = colorArkStr;
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .popupColor = Converter::ArkValue<Opt_Union_Color_String_Resource_Number>(arkUnionPopupColor)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsPopupColorNumberResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsPopupColorNumberResourceTest, TestSize.Level1)
{
    // color as number
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    auto colorArkNumber = Converter::ArkValue<Ark_Number>(TEST_COLOR_BLUE_NUM);
    Ark_Union_Color_String_Resource_Number arkUnionPopupColor;
    TypeHelper::WriteToUnion<Ark_Number>(arkUnionPopupColor) = colorArkNumber;

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .popupColor = Converter::ArkValue<Opt_Union_Color_String_Resource_Number>(arkUnionPopupColor)
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as resource
    TypeHelper::WriteToUnion<Ark_Resource>(arkUnionPopupColor) = TEST_COLOR_RESOURCE;
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .popupColor = Converter::ArkValue<Opt_Union_Color_String_Resource_Number>(arkUnionPopupColor)
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsShowInSubWindowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest11, bindPopupPopupOptionsShowInSubWindowTest, TestSize.Level1)
{
    Ark_Boolean arkShow = Converter::ArkValue<Ark_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .showInSubWindow = Converter::ArkValue<Opt_Boolean>(Ark_Empty())
    };
    Ark_Union_PopupOptions_CustomPopupOptions arkUnion;
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_SHOW_IN_SUBWINDOW);
    EXPECT_FALSE(checkValue);

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSABLE_PROP_TEXT_VALUE),
        .showInSubWindow = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };
    TypeHelper::WriteToUnion<Ark_PopupOptions>(arkUnion) = arkOptions;
    modifier_->setBindPopup(node_, arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_SHOW_IN_SUBWINDOW);
    EXPECT_TRUE(checkValue);
}
}