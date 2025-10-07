/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components/button/button_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "base/geometry/ng/offset_t.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto PROP_NAME_SHADOW = "shadow";
    const auto PROP_NAME_RADIUS = "radius";
    const auto PROP_NAME_OFFSET_X = "offsetX";
    const auto PROP_NAME_OFFSET_Y = "offsetY";
    const auto PROP_NAME_COLOR = "color";
    const auto PROP_NAME_TYPE = "type";
    const auto PROP_NAME_FILL = "fill";

    const auto TEST_COLOR_BLACK_STR = "#FF000000";
    const auto TEST_COLOR_BLUE_STR = "#FF0000FF";
    const auto TEST_COLOR_BLUE = Color::BLUE;
    const auto THEME_COLOR_RED = Color::RED;
    const auto TEST_COLOR_RES_NAME = "test_color_res_name";
    const auto TEST_COLOR_RESOURCE = CreateResource(TEST_COLOR_RES_NAME, ResourceType::COLOR);
    const auto TEST_FLOAT_RES_NAME = "float_res_name";
    const auto TEST_FLOAT_RESOURCE = CreateResource(TEST_FLOAT_RES_NAME, ResourceType::FLOAT);
    const auto FLOAT_VALUE = 1.0f;
    const auto DOUBLE_0_STR = "0.000000";
    const auto DOUBLE_1_STR = "1.000000";
    const auto DOUBLE_1_NEGATIVE_STR = "-1.000000";
}

class CommonMethodModifierTest18 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
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
 * @tc.name: bindPopupCustomPopupOptionsShadowDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowDefaultTest, TestSize.Level1)
{
    // default value
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkValue<Opt_Union_ShadowOptions_ShadowStyle>(Ark_Empty()),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_RADIUS);
    EXPECT_EQ(checkValue, DOUBLE_0_STR);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLACK_STR);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_X);
    EXPECT_EQ(checkValue, DOUBLE_0_STR);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_Y);
    EXPECT_EQ(checkValue, DOUBLE_0_STR);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_TYPE);
    EXPECT_EQ(checkValue, "0");
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_FILL);
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowStyleTest, TestSize.Level1)
{
    // valid value
    auto arkShadowStyle = ARK_SHADOW_STYLE_OUTER_FLOATING_MD;
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowStyle>(arkShadowStyle),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto checkValue = GetAttrValue<std::string>(fullJson, PROP_NAME_SHADOW);
    EXPECT_EQ(checkValue, "ShadowStyle.OuterFloatingMD");

    // invalid value
    arkShadowStyle = Converter::INVALID_ENUM_VAL<Ark_ShadowStyle>;
    arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowStyle>(arkShadowStyle),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    checkValue = GetAttrValue<std::string>(fullJson, PROP_NAME_SHADOW);
    EXPECT_EQ(checkValue, "ShadowStyle.OuterFloatingMD");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsRadiusNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsRadiusNumberTest, TestSize.Level1)
{
    // valid value
    Ark_ShadowOptions arkShadowOptions = {
        .radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(1.0),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_RADIUS);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);

    // negative value
    arkShadowOptions = {
        .radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Float64>(-1.0),
    };
    arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_RADIUS);
    EXPECT_EQ(checkValue, DOUBLE_0_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsRadiusResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsRadiusResourceTest,
    TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .radius = Converter::ArkUnion<Ark_Union_F64_Resource, Ark_Resource>(TEST_FLOAT_RESOURCE),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_RADIUS);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetXNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetXNumberTest,
    TestSize.Level1)
{
    // valid value
    Ark_ShadowOptions arkShadowOptions = {
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_X);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetXNumberTest2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetXNumberTest2,
    TestSize.Level1)
{
    // negative value
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;

    Ark_ShadowOptions arkShadowOptions = {
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-1.0),
    };

    auto arkOptions = Ark_CustomPopupOptions  {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    UINode* blankNode = reinterpret_cast<UINode *>(node_);
    RefPtr<UINode> blankRef = AceType::Claim(blankNode);
    auto context = blankNode->GetContext();
    auto overlayManager = context->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    auto popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    auto childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_X);
    EXPECT_EQ(checkValue, DOUBLE_1_NEGATIVE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetXResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetXResourceTest,
    TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .offsetX = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(TEST_FLOAT_RESOURCE),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_X);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetYNumberValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetYNumberValidTest,
    TestSize.Level1)
{
    // valid value
    Ark_ShadowOptions arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(1.0),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_Y);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetYNumberInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetYNumberInvalidTest,
    TestSize.Level1)
{
    // valid value
    Ark_ShadowOptions arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(-1.0),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_Y);
    EXPECT_EQ(checkValue, DOUBLE_1_NEGATIVE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsOffsetYResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsOffsetYResourceTest,
    TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .offsetY = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Resource>(TEST_FLOAT_RESOURCE),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_OFFSET_Y);
    EXPECT_EQ(checkValue, DOUBLE_1_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsFillTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsFillTest, TestSize.Level1)
{
    // true value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .fill = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_FILL);
    EXPECT_EQ(checkValue, "1");

    // false value
    arkShadowOptions = { .fill = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)) };
    arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_FILL);
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsTypeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsTypeTest, TestSize.Level1)
{
    // valid value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = { .type = Converter::ArkValue<Opt_ShadowType>(
        Converter::ArkValue<Ark_ShadowType>(Ark_ShadowType::ARK_SHADOW_TYPE_BLUR))
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_TYPE);
    EXPECT_EQ(checkValue, "1");

    // invalid value
    arkShadowOptions = { .type = Converter::ArkValue<Opt_ShadowType>(
        Converter::ArkValue<Ark_ShadowType>(static_cast<Ark_ShadowType>(-1)))
    };
    arkOptions = { .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };

    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);
    childNode = popupInfo.popupNode->GetFirstChild();
    ASSERT_NE(childNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_TYPE);
    EXPECT_EQ(checkValue, "0");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsColorColorTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsColorColorTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Color>(ARK_COLOR_BLUE),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsColorStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsColorStringTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_String>(
            TEST_COLOR_BLUE_STR),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsColorResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsColorResourceTest,
    TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_Resource>(
            TEST_COLOR_RESOURCE),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsColorStrategyValidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsColorStrategyValidTest,
    TestSize.Level1)
{
    // valid value
    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(
            ARK_COLORING_STRATEGY_PRIMARY),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, "ColoringStrategy.PRIMARY");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShadowOptionsColorStrategyInvalidTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest18, DISABLED_bindPopupCustomPopupOptionsShadowOptionsColorStrategyInvalidTest,
    TestSize.Level1)
{
    // invalid value
    Ark_ShadowOptions arkShadowOptions = {
        .color = Converter::ArkUnion<Opt_Union_Color_String_Resource_ColoringStrategy, Ark_ColoringStrategy>(
            Converter::INVALID_ENUM_VAL<Ark_ColoringStrategy>),
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest18> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .shadow = Converter::ArkUnion<Opt_Union_ShadowOptions_ShadowStyle, Ark_ShadowOptions>(arkShadowOptions),
    };
    auto arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, PROP_NAME_SHADOW);
    auto checkValue = GetAttrValue<std::string>(childObject, PROP_NAME_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLACK_STR);
}
}
