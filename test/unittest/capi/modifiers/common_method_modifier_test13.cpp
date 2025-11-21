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
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "generated/type_helpers.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components/button/button_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "core/components/theme/shadow_theme.h"
#include "base/geometry/ng/offset_t.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const auto ACCESSIBLE_PROP_TEXT_VALUE = "Hello, World!";
const auto BUBBLE_LAYOUT_PROP = "bubbleLayoutProperty";
const auto BUBBLE_LAYOUT_PROP_ARROW_WIDTH = "arrowWidth";
const auto BUBBLE_LAYOUT_PROP_ARROW_HEIGHT = "arrowHeight";
const auto BUBBLE_LAYOUT_PROP_RADIUS = "radius";
const auto BUBBLE_RENDER_PROP = "bubbleRenderProperty";
const auto BUBBLE_RENDER_PROP_BLUR_STYLE = "backgroundBlurStyle";
const auto BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE = "value";
const auto BUBBLE_RENDER_PROP_PRIMARY_BUTTON_SHOW = "primaryButtonShow";
const auto BUBBLE_RENDER_PROP_SECONDARY_BUTTON_SHOW = "secondaryButtonShow";
const auto TEXT_LAYOUT_PROP_CONTENT = "content";

const auto TEST_COLOR_BLUE_NUM = 0xFF0000FF;
const auto TEST_COLOR_BLUE_STR = "#FF0000FF";
const auto TEST_COLOR_BLUE = Color::BLUE;
const auto THEME_COLOR_RED = Color::RED;
const auto TEST_COLOR_RES_NAME = "test_color_res_name";
const auto TEST_COLOR_RESOURCE = CreateResource(TEST_COLOR_RES_NAME, ResourceType::COLOR);
const auto TEST_FLOAT_RES_NAME = "float_res_name";
const auto TEST_FLOAT_RESOURCE = CreateResource(TEST_FLOAT_RES_NAME, ResourceType::FLOAT);
const auto FLOAT_VALUE = 1.0f;
const auto PRIMARY_BUTTON_TEXT = "Primary Button";
const auto SECONDARY_BUTTON_TEXT = "Secondary Button";
constexpr int32_t TEST_RESOURCE_ID_1 = 1001;
constexpr int32_t TEST_RESOURCE_ID_2 = 1002;
} // namespace

class CommonMethodModifierTest13 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
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

        SetupThemeStyle(THEME_PATTERN_SHADOW);
        SetupTheme<ShadowTheme>();
        AddResource(TEST_COLOR_RES_NAME, TEST_COLOR_BLUE);
        AddResource(TEST_FLOAT_RES_NAME, FLOAT_VALUE);
    }

    RefPtr<MockRenderContext> GetMockRenderContext()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            return AceType::DynamicCast<MockRenderContext>(fnode->GetRenderContext());
        }
        return nullptr;
    }
};

/*
 * @tc.name: bindPopupPopupOptionsArrowWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsArrowWidthTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowWidth = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

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
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "16.00vp");

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowWidth = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowWidth = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "1.00px");
}

/*
 * @tc.name: bindPopupPopupOptionsArrowHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsArrowHeightTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowHeight = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

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
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "8.00vp");

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowHeight = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .arrowHeight = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "1.00px");
}

/*
 * @tc.name: bindPopupPopupOptionsRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsRadiusTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .radius = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

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
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "20.00vp");

    // valid value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .radius = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .radius = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "1.00px");
}

/*
 * @tc.name: bindPopupPopupOptionsBlurStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsBlurStyleTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    // default value
    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP_BLUR_STYLE);
    auto checkValue = GetAttrValue<std::string>(childObject, BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE);
    EXPECT_EQ(checkValue, "BlurStyle.COMPONENT_ULTRA_THICK");

    // valid value
    arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(
            Converter::ArkValue<Ark_BlurStyle>(Ark_BlurStyle::ARK_BLUR_STYLE_REGULAR)),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP_BLUR_STYLE);
    checkValue = GetAttrValue<std::string>(childObject, BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE);
    EXPECT_EQ(checkValue, "BlurStyle.Regular");

    // invalid value
    arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(
            Converter::ArkValue<Ark_BlurStyle>(static_cast<Ark_BlurStyle>(-1))),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP_BLUR_STYLE);
    checkValue = GetAttrValue<std::string>(childObject, BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE);
    EXPECT_EQ(checkValue, "BlurStyle.COMPONENT_ULTRA_THICK");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    // default value
    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "radius");
    EXPECT_EQ(checkValue, "0.000000");
    checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, "#FF000000");
    checkValue = GetAttrValue<std::string>(childObject, "offsetX");
    EXPECT_EQ(checkValue, "0.000000");
    checkValue = GetAttrValue<std::string>(childObject, "offsetY");
    EXPECT_EQ(checkValue, "0.000000");
    checkValue = GetAttrValue<std::string>(childObject, "type");
    EXPECT_EQ(checkValue, "0");
    checkValue = GetAttrValue<std::string>(childObject, "fill");
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowStyleTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkShadowStyle = Converter::ArkValue<Ark_ShadowStyle>(Ark_ShadowStyle::ARK_SHADOW_STYLE_OUTER_FLOATING_MD);
    Ark_Union_ShadowOptions_ShadowStyle arkUnionShadow;
    TypeHelper::WriteToUnion<Ark_ShadowStyle>(arkUnionShadow) = arkShadowStyle;

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "shadow");
    EXPECT_EQ(checkValue, "ShadowStyle.OuterFloatingMD");

    // invalid value
    arkShadowStyle = Converter::ArkValue<Ark_ShadowStyle>(static_cast<Ark_ShadowStyle>(-1));
    TypeHelper::WriteToUnion<Ark_ShadowStyle>(arkUnionShadow) = arkShadowStyle;

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    checkValue = GetAttrValue<std::string>(fullJson, "shadow");
    EXPECT_EQ(checkValue, "ShadowStyle.OuterFloatingMD");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsRaiusNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsRaiusNumberTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    // valid value
    auto arkRadius = Converter::ArkValue<Ark_Float64>(1.0f);
    Ark_Union_F64_Resource arkUnionRadius;
    TypeHelper::WriteToUnion<Ark_Float64>(arkUnionRadius) = arkRadius;

    Ark_ShadowOptions arkShadowOptions = { .radius = arkUnionRadius };

    Ark_Union_ShadowOptions_ShadowStyle arkUnionShadow;
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "radius");
    EXPECT_EQ(checkValue, "1.000000");

    // negative value
    arkRadius = Converter::ArkValue<Ark_Float64>(-1.0f);
    TypeHelper::WriteToUnion<Ark_Float64>(arkUnionRadius) = arkRadius;

    arkShadowOptions = { .radius = arkUnionRadius };
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "radius");
    EXPECT_EQ(checkValue, "0.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsRaiusResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsRaiusResourceTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_Union_F64_Resource arkUnionRadius;
    TypeHelper::WriteToUnion<Ark_Resource>(arkUnionRadius) = TEST_FLOAT_RESOURCE;

    Ark_ShadowOptions arkShadowOptions = {
        .radius = arkUnionRadius
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "radius");
    EXPECT_EQ(checkValue, "1.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsOffsetXNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsOffsetXNumberTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkOffsetX = Converter::ArkValue<Ark_Float64>(1.0f);
    Ark_Union_F64_Resource arkUnionOffsetX;
    TypeHelper::WriteToUnion<Ark_Float64>(arkUnionOffsetX) = arkOffsetX;

    Ark_ShadowOptions arkShadowOptions = {
        .offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(arkUnionOffsetX)
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "offsetX");
    EXPECT_EQ(checkValue, "1.000000");

    // negative value
    arkOffsetX = Converter::ArkValue<Ark_Float64>(-1.0f);
    TypeHelper::WriteToUnion<Ark_Float64>(arkUnionOffsetX) = arkOffsetX;

    arkShadowOptions = {
        .offsetX = Converter::ArkValue<Opt_Union_F64_Resource>(arkUnionOffsetX)
    };
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "offsetX");
    EXPECT_EQ(checkValue, "-1.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsOffsetXResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsOffsetXResourceTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_ShadowOptions arkShadowOptions = {
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(TEST_FLOAT_RESOURCE),
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "offsetX");
    EXPECT_EQ(checkValue, "1.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsOffsetYNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsOffsetYNumberTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_ShadowOptions arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0),
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "offsetY");
    EXPECT_EQ(checkValue, "1.000000");

    // negative value
    arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-1.0),
    };
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "offsetY");
    EXPECT_EQ(checkValue, "-1.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsOffsetYResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsOffsetYResourceTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_ShadowOptions arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(TEST_FLOAT_RESOURCE),
    };

    Ark_Union_ShadowOptions_ShadowStyle arkUnionShadow;
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "offsetY");
    EXPECT_EQ(checkValue, "1.000000");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsFillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsFillTest, TestSize.Level1)
{
    // true value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .fill = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "fill");
    EXPECT_EQ(checkValue, "1");

    // false value
    arkShadowOptions = {
        .fill = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false))
    };
    TypeHelper::WriteToUnion<Ark_ShadowOptions>(arkUnionShadow) = arkShadowOptions;

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "fill");
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsTypeTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .type = Converter::ArkValue<Opt_ShadowType>(
            Converter::ArkValue<Ark_ShadowType>(Ark_ShadowType::ARK_SHADOW_TYPE_BLUR))
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "type");
    EXPECT_EQ(checkValue, "1");

    // invalid value
    arkShadowOptions = {
        .type = Converter::ArkValue<Opt_ShadowType>(
            Converter::ArkValue<Ark_ShadowType>(static_cast<Ark_ShadowType>(-1)))
    };
    arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "type");
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsColorColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsColorColorTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkColor = Converter::ArkValue<Ark_Color>(Ark_Color::ARK_COLOR_BLUE);
    auto arkUnionColor = Converter::ArkUnion<Ark_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(
        colorArkColor);

    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>(arkUnionColor)
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsColorStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsColorStringTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkStr = Converter::ArkValue<Ark_String>(TEST_COLOR_BLUE_STR);
    auto arkUnionColor = Converter::ArkUnion<Ark_Union_Color_String_Resource_ColoringStrategy, Ark_String>(colorArkStr);

    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>(arkUnionColor)
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsColorResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsColorResourceTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkUnionColor = Converter::ArkUnion<Ark_Union_Color_String_Resource_ColoringStrategy, Ark_Resource>(
        TEST_COLOR_RESOURCE);

    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>(arkUnionColor)
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsShadowOptionsColorColorStrategyTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsShadowOptionsColorColorStrategyTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkStrategy = Converter::ArkValue<Ark_ColoringStrategy>(
        Ark_ColoringStrategy::ARK_COLORING_STRATEGY_PRIMARY);
    auto arkUnionColor = Converter::ArkUnion<Ark_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(
        colorArkStrategy);

    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>(arkUnionColor)
    };

    auto arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    auto checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, "ColoringStrategy.PRIMARY");

    // invalid value
    colorArkStrategy = Converter::ArkValue<Ark_ColoringStrategy>(static_cast<Ark_ColoringStrategy>(-1));
    arkUnionColor = Converter::ArkUnion<Ark_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(
        colorArkStrategy);

    arkShadowOptions = {
        .color = Converter::ArkValue<Opt_Union_Color_String_Resource_ColoringStrategy>(arkUnionColor)
    };

    arkUnionShadow = Converter::ArkUnion<Ark_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions);

    arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(arkUnionShadow)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "shadow");
    checkValue = GetAttrValue<std::string>(childObject, "color");
    EXPECT_EQ(checkValue, "#FF000000");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(Ark_Empty())
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontSize");
    EXPECT_EQ(checkValue, "14.00fp");
    checkValue = GetAttrValue<std::string>(fullJson, "fontColor");
    EXPECT_EQ(checkValue, "#FFFFFFFF");
    checkValue = GetAttrValue<std::string>(fullJson, "fontStyle");
    EXPECT_EQ(checkValue, "FontStyle.Normal");
    checkValue = GetAttrValue<std::string>(fullJson, "fontWeight");
    EXPECT_EQ(checkValue, "FontWeight.Normal");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsTextColorColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsTextColorColorTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto color = Converter::ArkValue<Ark_Color>(Ark_Color::ARK_COLOR_BLUE);
    auto arkUnionColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Color>(color);

    Ark_PopupMessageOptions arkMessageOptions = {
        .textColor = Converter::ArkValue<Opt_ResourceColor>(arkUnionColor)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontColor");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsTextColorNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsTextColorNumberTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto color = Converter::ArkValue<Ark_Int32>(TEST_COLOR_BLUE_NUM);
    auto arkUnionColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(color);

    Ark_PopupMessageOptions arkMessageOptions = {
        .textColor = Converter::ArkValue<Opt_ResourceColor>(arkUnionColor)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontColor");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsTextColorStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsTextColorStringTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto color = Converter::ArkValue<Ark_String>(TEST_COLOR_BLUE_STR);
    auto arkUnionColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(color);

    Ark_PopupMessageOptions arkMessageOptions = {
        .textColor = Converter::ArkValue<Opt_ResourceColor>(arkUnionColor)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontColor");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsTextColorResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsTextColorResourceTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkUnionColor = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(TEST_COLOR_RESOURCE);

    Ark_PopupMessageOptions arkMessageOptions = {
        .textColor = Converter::ArkValue<Opt_ResourceColor>(arkUnionColor)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontColor");
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontSizeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontSizeTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_Font arkFont = {
        .size = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(11._px))
    };

    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontSize");
    EXPECT_EQ(checkValue, "11.00px");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontWeightWeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontWeightWeightTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_Font arkFont = {
        .weight = Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_FontWeight>(ARK_FONT_WEIGHT_BOLDER),
    };

    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontWeight");
    EXPECT_EQ(checkValue, "FontWeight.Bolder");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontWeightNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontWeightNumberTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_Font arkFont = {
        .weight = Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_Int32>(400),
    };

    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontWeight");
    EXPECT_EQ(checkValue, "400");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontWeightStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontWeightStringTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    Ark_Font arkFont = {
        .weight = Converter::ArkUnion<Opt_Union_FontWeight_I32_String, Ark_String>("medium"),
    };

    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontWeight");
    EXPECT_EQ(checkValue, "FontWeight.Medium");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontStyleTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkFontStyle = Converter::ArkValue<Ark_FontStyle>(Ark_FontStyle::ARK_FONT_STYLE_ITALIC);
    Ark_Font arkFont = {
        .style = Converter::ArkValue<Opt_FontStyle>(arkFontStyle)
    };
    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontStyle");
    EXPECT_EQ(checkValue, "FontStyle.Italic");
}

/*
 * @tc.name: bindPopupPopupOptionsMessageOptionsFontStyleInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsMessageOptionsFontStyleInvalidTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto arkFontStyle = Converter::ArkValue<Ark_FontStyle>(static_cast<Ark_FontStyle>(-1));
    Ark_Font arkFont = {
        .style = Converter::ArkValue<Opt_FontStyle>(arkFontStyle)
    };
    Ark_PopupMessageOptions arkMessageOptions = {
        .font = Converter::ArkValue<Opt_Font>(arkFont)
    };
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .messageOptions = Converter::ArkValue<Opt_PopupMessageOptions>(arkMessageOptions)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);

    auto scrollNode = columnNode->GetFirstChild();
    ASSERT_NE(scrollNode, nullptr);

    auto textNode = scrollNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValue = GetAttrValue<std::string>(fullJson, "fontStyle");
    EXPECT_EQ(checkValue, "FontStyle.Normal");
}

/*
 * @tc.name: bindPopupPopupOptionsOnWillDismissDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsOnWillDismissDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(Ark_Empty())
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->GetInteractiveDismiss());
    EXPECT_FALSE(pattern->HasOnWillDismiss());
}

/*
 * @tc.name: bindPopupPopupOptionsOnWillDismissBoolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsOnWillDismissBoolTest, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(false));
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto dismissUnion = Converter::ArkUnion<Ark_Union_Boolean_Callback_DismissPopupAction_Void, Ark_Boolean>(
        Converter::ArkValue<Ark_Boolean>(false));

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(dismissUnion)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->GetInteractiveDismiss());
}

/*
 * @tc.name: bindPopupPopupOptionsOnWillDismissCallbackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsOnWillDismissCallbackTest, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(false));
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    struct CheckEvent { int32_t resourceId; std::optional<DismissReason> reason; };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    void (*checkCallback)(const Ark_Int32, const Ark_DismissPopupAction) =
        [](const Ark_Int32 resourceId, const Ark_DismissPopupAction action) {
            auto accessors = fullAPI_->getAccessors();
            auto accessor = accessors->getDismissPopupActionAccessor();
            checkEvent = {
                .resourceId = resourceId,
                .reason = static_cast<DismissReason>(accessor->getReason(action)),
            };
        };

    auto dismissCb = Converter::ArkValue<Callback_DismissPopupAction_Void>(checkCallback, TEST_RESOURCE_ID_1);

    auto dismissUnion = Converter::ArkUnion<Ark_Union_Boolean_Callback_DismissPopupAction_Void,
        Callback_DismissPopupAction_Void>(dismissCb);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(dismissUnion)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    ASSERT_TRUE(pattern->HasOnWillDismiss());
    pattern->CallOnWillDismiss(static_cast<int32_t>(DismissReason::TOUCH_OUTSIDE));

    ASSERT_TRUE(checkEvent.has_value());
    ASSERT_TRUE(checkEvent.value().reason.has_value());
    EXPECT_EQ(checkEvent.value().resourceId, TEST_RESOURCE_ID_1);
    EXPECT_EQ(checkEvent.value().reason.value(), DismissReason::TOUCH_OUTSIDE);
}

/*
 * @tc.name: bindPopupPopupOptionsOnStateChangeCallbackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsOnStateChangeCallbackTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    struct CheckEvent { int32_t resourceId; std::optional<bool> isVisible; };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    void (*checkCallback)(const Ark_Int32, const Ark_PopupStateChangeParam) =
        [](const Ark_Int32 resourceId, const Ark_PopupStateChangeParam event) {
            checkEvent = {
                .resourceId = resourceId,
                .isVisible = Converter::OptConvert<bool>(event.isVisible)
            };
        };

    auto stateChangeCb =
        Converter::ArkValue<PopupStateChangeCallback>(checkCallback, TEST_RESOURCE_ID_1);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .onStateChange = Converter::ArkValue<Opt_PopupStateChangeCallback>(stateChangeCb)
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto eventHub = popupInfo.popupNode->GetEventHub<BubbleEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(true);
    ASSERT_TRUE(checkEvent.has_value());
    ASSERT_TRUE(checkEvent.value().isVisible.has_value());
    EXPECT_TRUE(checkEvent.value().isVisible.value());
}

/*
 * @tc.name: bindPopupPopupOptionsPrimaryButtonDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsPrimaryButtonDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

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
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_PRIMARY_BUTTON_SHOW);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupPopupOptionsPrimaryButtonTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsPrimaryButtonTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    struct CheckEvent { int32_t resourceId; };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](const Ark_Int32 resourceId) { checkEvent = { .resourceId = resourceId }; };

    Ark_PopupButton buttonAction = {
        .value = Converter::ArkValue<Ark_String>(PRIMARY_BUTTON_TEXT),
        .action = Converter::ArkValue<VoidCallback>(checkCallback, TEST_RESOURCE_ID_1)
    };

    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(buttonAction),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    RefPtr<UINode> blankRef = AceType::Claim(reinterpret_cast<UINode *>(node_));
    auto context = blankRef->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_PRIMARY_BUTTON_SHOW);
    EXPECT_TRUE(checkValue);

    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChildNode = columnNode->GetFirstChild();
    ASSERT_NE(combinedChildNode, nullptr);
    auto rowNode = combinedChildNode->GetLastChild();
    ASSERT_NE(rowNode, nullptr);
    auto firstButtonNode = rowNode->GetFirstChild();
    ASSERT_NE(firstButtonNode, nullptr);
    auto textNode = firstButtonNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValueString = GetAttrValue<std::string>(fullJson, TEXT_LAYOUT_PROP_CONTENT);
    EXPECT_EQ(checkValueString, PRIMARY_BUTTON_TEXT);

    auto frameNode = AceType::DynamicCast<FrameNode>(firstButtonNode);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    ASSERT_NE(gestureEventHub->GetClickEvent(), nullptr);
    gestureEventHub->ActClick();
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().resourceId, TEST_RESOURCE_ID_1);
}

/*
 * @tc.name: bindPopupPopupOptionsSecondaryButtonTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsSecondaryButtonTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    struct CheckEvent { int32_t resourceId; };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto checkCallback = [](const Ark_Int32 resourceId) { checkEvent = { .resourceId = resourceId }; };

    Ark_PopupButton buttonAction = {
        .value = Converter::ArkValue<Ark_String>(SECONDARY_BUTTON_TEXT),
        .action = Converter::ArkValue<VoidCallback>(checkCallback, TEST_RESOURCE_ID_2)
    };

    Ark_PopupOptions arkOptions = { .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .primaryButton = Converter::ArkValue<Opt_PopupButton>(Ark_Empty()),
        .secondaryButton = Converter::ArkValue<Opt_PopupButton>(buttonAction),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    RefPtr<UINode> blankRef = AceType::Claim(reinterpret_cast<UINode *>(node_));
    auto context = blankRef->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_SECONDARY_BUTTON_SHOW);
    EXPECT_TRUE(checkValue);

    auto columnNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(columnNode, nullptr);
    auto combinedChildNode = columnNode->GetFirstChild();
    ASSERT_NE(combinedChildNode, nullptr);
    auto rowNode = combinedChildNode->GetLastChild();
    ASSERT_NE(rowNode, nullptr);
    auto secondButtonNode = rowNode->GetLastChild();
    ASSERT_NE(secondButtonNode, nullptr);
    auto textNode = secondButtonNode->GetFirstChild();
    ASSERT_NE(textNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(textNode)));
    auto checkValueString = GetAttrValue<std::string>(fullJson, TEXT_LAYOUT_PROP_CONTENT);
    EXPECT_EQ(checkValueString, SECONDARY_BUTTON_TEXT);

    auto frameNode = AceType::DynamicCast<FrameNode>(secondButtonNode);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureEventHub = eventHub->GetGestureEventHub();
    ASSERT_NE(gestureEventHub, nullptr);
    ASSERT_NE(gestureEventHub->GetClickEvent(), nullptr);
    gestureEventHub->ActClick();
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent.value().resourceId, TEST_RESOURCE_ID_2);
}

/*
 * @tc.name: bindPopupPopupOptionsTransitionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest13, DISABLED_bindPopupPopupOptionsTransitionTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ChainedTransitionEffect> transitionHandler =
        AceType::Claim(new ChainedOpacityEffect(1.0f));
    peer->handler = transitionHandler;
    auto arkEffect = Converter::ArkValue<Opt_TransitionEffect>(peer);

    Ark_PopupOptions arkOptions = {
        .message = Converter::ArkValue<Ark_String>(ACCESSIBLE_PROP_TEXT_VALUE),
        .transition = arkEffect
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_PopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    ASSERT_NE(context, nullptr);
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    auto popupMockRenderContext = AceType::DynamicCast<MockRenderContext>(popupInfo.popupNode->GetRenderContext());
    ASSERT_NE(popupMockRenderContext, nullptr);
    auto checkPtr = popupMockRenderContext->GetChainedTransitionEffect();
    EXPECT_EQ(checkPtr, transitionHandler);
}
}
