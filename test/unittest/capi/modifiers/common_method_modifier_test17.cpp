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
#include "generated/type_helpers.h"
#include "test/unittest/capi/utils/custom_node_builder_test_helper.h"
#include "core/components_ng/pattern/bubble/bubble_event_hub.h"
#include "core/components_ng/pattern/bubble/bubble_pattern.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components/button/button_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components/theme/theme_attributes.h"
#include "base/geometry/ng/offset_t.h"
#include "test/mock/core/render/mock_render_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
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

    const auto BUBBLE_LAYOUT_PROP_ARROW_WIDTH = "arrowWidth";
    const auto BUBBLE_LAYOUT_PROP_ARROW_HEIGHT = "arrowHeight";
    const auto BUBBLE_LAYOUT_PROP_RADIUS = "radius";
    const auto BUBBLE_RENDER_PROP_BLUR_STYLE = "backgroundBlurStyle";
    const auto BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE = "value";
    const auto BUBBLE_CHILD_PROP_SIZE = "size";
    const auto BUBBLE_CHILD_PROP_SIZE_WIDTH = "width";

    const auto TEST_COLOR_BLUE_NUM = 0xFF0000FF;
    const auto TEST_COLOR_BLUE_STR = "#FF0000FF";
    const auto TEST_COLOR_BLUE = Color::BLUE;
    const auto THEME_COLOR_RED = Color::RED;
    const auto TEST_COLOR_RES_NAME = "test_color_res_name";
    const auto TEST_COLOR_RESOURCE = CreateResource(TEST_COLOR_RES_NAME, ResourceType::COLOR);
    const auto TEST_RESOURCE_ID_1 = 1001;
}

class CommonMethodModifierTest17 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
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

    RefPtr<MockRenderContext> GetMockRenderContext()
    {
        if (auto fnode = reinterpret_cast<FrameNode *>(node_); fnode) {
            return AceType::DynamicCast<MockRenderContext>(fnode->GetRenderContext());
        }
        return nullptr;
    }
};

/*
 * @tc.name: bindPopupCustomPopupOptionsInitialPopupInfoTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, bindPopupCustomPopupOptionsInitialPopupInfoTest, TestSize.Level1)
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
 * @tc.name: bindPopupCustomPopupOptionsPlacementDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPlacementDefaultValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsPlacementValidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPlacementValidValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .placement = Converter::ArkValue<Opt_Placement>(Ark_Placement::ARK_PLACEMENT_TOP)
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_TOP);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsPlacementInvalidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPlacementInvalidValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .placement = Converter::ArkValue<Opt_Placement>(
            Converter::ArkValue<Ark_Placement>(static_cast<Ark_Placement>(-1)))
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_PLACEMENT);
    EXPECT_EQ(checkValue, BUBBLE_LAYOUT_PROP_PLACEMENT_BOTTOM);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsArrowOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsArrowOffsetTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "0.00px");

    // valid value
    arkOptions = {
        .builder = *arkBuilder,
        .arrowOffset = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(1._px)),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "1.00px");

    // dont check negative value since it is clamped-ed during a layout process
}

/*
 * @tc.name: bindPopupCustomPopupOptionsArrowOffsetPointPositionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsArrowOffsetPointPositionTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "0.00px");

    // valid value
    arkOptions = {
        .builder = *arkBuilder,
        .arrowOffset = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .arrowPointPosition = Converter::ArkValue<Opt_ArrowPointPosition>(
            Converter::ArkValue<Ark_ArrowPointPosition>(Ark_ArrowPointPosition::ARK_ARROW_POINT_POSITION_CENTER))
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_ARROW_OFFSET);
    EXPECT_EQ(checkValue, "50.00%");

    // dont check negative value since it is clamped-ed during a layout process
}

/*
 * @tc.name: bindPopupCustomPopupOptionsTargetSpaceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsTargetSpaceTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .targetSpace = Converter::ArkValue<Opt_Length>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "8.00vp"); // default from PopupTheme

    // valid value
    arkOptions = { .builder = *arkBuilder,
        .targetSpace = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(1._px)),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = { .builder = *arkBuilder,
        .targetSpace = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(-1._px)),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_TARGET_SPACE);
    EXPECT_EQ(checkValue, "-1.00px");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsEnableArrowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsEnableArrowTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .enableArrow = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_ARROW);
    EXPECT_TRUE(checkValue); // default from PopupParam

    // valid value
    arkOptions = {
        .builder = *arkBuilder,
        .enableArrow = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_ARROW);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsEnableHoverModeDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsEnableHoverModeDefaultValueTest,
    TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .enableHoverMode = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_HOVER_MODE);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsEnableHoverModeTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsEnableHoverModeTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .enableHoverMode = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_ENABLE_HOVER_MODE);
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsFollowTransformOfTargetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsFollowTransformOfTargetTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .followTransformOfTarget = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_FOLLOW_TRANSFORM);
    EXPECT_FALSE(checkValue); // default from PopupParam

    // valid value
    arkOptions = {
        .builder = *arkBuilder,
        .followTransformOfTarget = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true)),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_FOLLOW_TRANSFORM);
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsAutoCancelDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsAutoCancelDefaultValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .autoCancel = Converter::ArkValue<Opt_Boolean>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_AUTO_CANCEL);
    EXPECT_TRUE(checkValue); // default from PopupParam, autoCancel = !hasAction
}

/*
 * @tc.name: bindPopupCustomPopupOptionsAutoCancelTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsAutoCancelTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .autoCancel = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true)),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_RENDER_PROP_AUTO_CANCEL);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsMaskBlockEventTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsMaskBlockEventTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_BLOCK_EVENT);
    EXPECT_TRUE(checkValue);

    Ark_Union_Boolean_PopupMaskType arkUnionMask;
    TypeHelper::WriteToUnion<Ark_Boolean>(arkUnionMask) = Converter::ArkValue<Ark_Boolean>(false);
    arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(arkUnionMask)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_BLOCK_EVENT);
    EXPECT_FALSE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsMaskColorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsMaskColorDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, THEME_COLOR_RED.ToString()); // set & get from PopupTheme
}

/*
 * @tc.name: bindPopupCustomPopupOptionsMaskColorColorNumberTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsMaskColorColorNumberTest, TestSize.Level1)
{
    // color as Ark_arkui_component_enums_Color
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkColor = Converter::ArkUnion<Ark_ResourceColor, Ark_arkui_component_enums_Color>(
        ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    Ark_PopupMaskType literalColor = { .color = colorArkColor };
    Ark_Union_Boolean_PopupMaskType arkUnionMask;
    TypeHelper::WriteToUnion<Ark_PopupMaskType>(arkUnionMask) = literalColor;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(arkUnionMask)
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as number
    auto colorArkNumber = Converter::ArkUnion<Ark_ResourceColor, Ark_Int32>(TEST_COLOR_BLUE_NUM);
    literalColor = { .color = colorArkNumber };
    TypeHelper::WriteToUnion<Ark_PopupMaskType>(arkUnionMask) = literalColor;
    arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(arkUnionMask)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsMaskColorStringResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsMaskColorStringResourceTest, TestSize.Level1)
{
    // color as string
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkStr = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(TEST_COLOR_BLUE_STR);
    Ark_PopupMaskType literalColor = { .color = colorArkStr };
    Ark_Union_Boolean_PopupMaskType arkUnionMask;
    TypeHelper::WriteToUnion<Ark_PopupMaskType>(arkUnionMask) = literalColor;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(arkUnionMask)
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as resource
    auto colorArkRes = Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(TEST_COLOR_RESOURCE);
    literalColor = { .color = colorArkRes };
    TypeHelper::WriteToUnion<Ark_PopupMaskType>(arkUnionMask) = literalColor;
    arkOptions = {
        .builder = *arkBuilder,
        .mask = Converter::ArkValue<Opt_Union_Boolean_PopupMaskType>(arkUnionMask)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_MASK_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOffsetTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOffsetTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .offset = Converter::ArkValue<Opt_Position>(Ark_Empty())
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
        .builder = *arkBuilder,
        .offset = Converter::ArkValue<Opt_Position>(arkPosition)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_POSITION_OFFSET);
    EXPECT_EQ(checkValue, OffsetF(xLength, yLength).ToString());
}

/*
 * @tc.name: bindPopupCustomPopupOptionsPopupColorDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPopupColorDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .popupColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_I64>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, THEME_COLOR_RED.ToString()); // set & get from PopupTheme
}

/*
 * @tc.name: bindPopupCustomPopupOptionsPopupColorColorStringTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPopupColorColorStringTest, TestSize.Level1)
{
    // color as arkcolor
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkColor = Converter::ArkValue<Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE);
    Ark_Union_arkui_component_enums_Color_String_Resource_I64 arkUnionPopupColor;
    TypeHelper::WriteToUnion<Ark_arkui_component_enums_Color>(arkUnionPopupColor) = colorArkColor;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .popupColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_I64>(arkUnionPopupColor)
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as string
    auto colorArkStr = Converter::ArkValue<Ark_String>(TEST_COLOR_BLUE_STR);
    TypeHelper::WriteToUnion<Ark_String>(arkUnionPopupColor) = colorArkStr;
    arkOptions = {
        .builder = *arkBuilder,
        .popupColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_I64>(arkUnionPopupColor)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsPopupColorNumberResourceTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsPopupColorNumberResourceTest, TestSize.Level1)
{
    // color as number
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto colorArkNumber = Converter::ArkValue<Ark_Int64>(TEST_COLOR_BLUE_NUM);
    Ark_Union_arkui_component_enums_Color_String_Resource_I64 arkUnionPopupColor;
    TypeHelper::WriteToUnion<Ark_Int64>(arkUnionPopupColor) = colorArkNumber;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .popupColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_I64>(arkUnionPopupColor)
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);

    // color as resource
    TypeHelper::WriteToUnion<Ark_Resource>(arkUnionPopupColor) = TEST_COLOR_RESOURCE;
    arkOptions = {
        .builder = *arkBuilder,
        .popupColor = Converter::ArkValue<Opt_Union_arkui_component_enums_Color_String_Resource_I64>(arkUnionPopupColor)
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_RENDER_PROP_POPUP_COLOR);
    EXPECT_EQ(checkValue, TEST_COLOR_BLUE_STR);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsShowInSubWindowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsShowInSubWindowTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .showInSubWindow = Converter::ArkValue<Opt_Boolean>(Ark_Empty())
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_SHOW_IN_SUBWINDOW);
    EXPECT_FALSE(checkValue);

    arkOptions = {
        .builder = *arkBuilder,
        .showInSubWindow = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true))
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<bool>(bubbleObject, BUBBLE_LAYOUT_PROP_SHOW_IN_SUBWINDOW);
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsArrowWidthTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsArrowWidthTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .arrowWidth = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "16.00vp");

    // valid value
    arkOptions = { .builder = *arkBuilder,
        .arrowWidth = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = { .builder = *arkBuilder,
        .arrowWidth = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_WIDTH);
    EXPECT_EQ(checkValue, "16.00vp");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsArrowHeightTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsArrowHeightTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .arrowHeight = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "8.00vp");

    // valid value
    arkOptions = { .builder = *arkBuilder,
        .arrowHeight = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = { .builder = *arkBuilder,
        .arrowHeight = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_ARROW_HEIGHT);
    EXPECT_EQ(checkValue, "8.00vp");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsRadiusTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsRadiusTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = { .builder = *arkBuilder,
        .radius = Converter::ArkValue<Opt_Dimension>(Ark_Empty()),
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

    auto fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    auto bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    auto checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "20.00vp");

    // valid value
    arkOptions = { .builder = *arkBuilder,
        .radius = Converter::ArkValue<Opt_Dimension>("1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "1.00px");

    // negative value
    arkOptions = { .builder = *arkBuilder,
        .radius = Converter::ArkValue<Opt_Dimension>("-1px"),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
    modifier_->setBindPopup(node_, &arkShow, &arkUnion);

    popupInfo = overlayManager->GetPopupInfo(blankRef->GetId());
    ASSERT_NE(popupInfo.popupNode, nullptr);

    fullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(popupInfo.popupNode)));
    bubbleObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_LAYOUT_PROP);
    checkValue = GetAttrValue<std::string>(bubbleObject, BUBBLE_LAYOUT_PROP_RADIUS);
    EXPECT_EQ(checkValue, "20.00vp");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsBlurStyleDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsBlurStyleDefaultTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(Ark_Empty()),
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP_BLUR_STYLE);
    auto checkValue = GetAttrValue<std::string>(childObject, BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE);
    EXPECT_EQ(checkValue, "BlurStyle.COMPONENT_ULTRA_THICK");
}


/*
 * @tc.name: bindPopupCustomPopupOptionsBlurStyleTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsBlurStyleTest, TestSize.Level1)
{
    // default value
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(
            Converter::ArkValue<Ark_BlurStyle>(Ark_BlurStyle::ARK_BLUR_STYLE_REGULAR)),
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
    auto childObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, BUBBLE_RENDER_PROP_BLUR_STYLE);
    auto checkValue = GetAttrValue<std::string>(childObject, BUBBLE_RENDER_PROP_BLUR_STYLE_VALUE);
    EXPECT_EQ(checkValue, "BlurStyle.Regular");

    // invalid value
    arkOptions = {
        .builder = *arkBuilder,
        .backgroundBlurStyle = Converter::ArkValue<Opt_BlurStyle>(
            Converter::ArkValue<Ark_BlurStyle>(static_cast<Ark_BlurStyle>(-1))),
    };
    arkUnion = Converter::ArkUnion<Opt_Union_PopupOptions_CustomPopupOptions, Ark_CustomPopupOptions>(arkOptions);
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
 * @tc.name: bindPopupCustomPopupOptionsTransitionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsTransitionTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    TransitionEffectPeer* peer = PeerUtils::CreatePeer<TransitionEffectPeer>();
    OHOS::Ace::RefPtr<OHOS::Ace::NG::ChainedTransitionEffect> transitionHandler =
        AceType::Claim(new ChainedOpacityEffect(1.0f));
    peer->handler = transitionHandler;
    auto arkEffect = Converter::ArkValue<Opt_TransitionEffect>(peer);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .transition = arkEffect
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

    auto popupMockRenderContext = AceType::DynamicCast<MockRenderContext>(popupInfo.popupNode->GetRenderContext());
    ASSERT_NE(popupMockRenderContext, nullptr);
    auto checkPtr = popupMockRenderContext->GetChainedTransitionEffect();
    EXPECT_EQ(checkPtr, transitionHandler);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsWidthDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsWidthDefaultValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .width = Converter::ArkValue<Opt_Dimension>(Ark_Empty())
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

    auto childFullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childSizeValue = GetAttrValue<std::unique_ptr<JsonValue>>(childFullJson, BUBBLE_CHILD_PROP_SIZE);
    auto checkValue = GetAttrValue<std::string>(childSizeValue, BUBBLE_CHILD_PROP_SIZE_WIDTH);
    EXPECT_EQ(checkValue, "0.00vp");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsWidthValidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsWidthValidValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .width = Converter::ArkValue<Opt_Dimension>(999.0f)
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

    auto childFullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childSizeValue = GetAttrValue<std::unique_ptr<JsonValue>>(childFullJson, BUBBLE_CHILD_PROP_SIZE);
    auto checkValue = GetAttrValue<std::string>(childSizeValue, BUBBLE_CHILD_PROP_SIZE_WIDTH);
    EXPECT_EQ(checkValue, "999.00vp");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsWidthInvalidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsWidthInvalidValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .width = Converter::ArkValue<Opt_Dimension>(-1.f)
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

    auto childFullJson = GetJsonValue(reinterpret_cast<Ark_NodeHandle>(Referenced::RawPtr(childNode)));
    auto childSizeValue = GetAttrValue<std::unique_ptr<JsonValue>>(childFullJson, BUBBLE_CHILD_PROP_SIZE);
    auto checkValue = GetAttrValue<std::string>(childSizeValue, BUBBLE_CHILD_PROP_SIZE_WIDTH);
    EXPECT_EQ(checkValue, "0.00px");
}

/*
 * @tc.name: bindPopupCustomPopupOptionsFocusableDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsFocusableDefaultValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .focusable = Converter::ArkValue<Opt_Boolean>(Ark_Empty())
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
    EXPECT_FALSE(popupInfo.focusable);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsFocusableValidValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsFocusableValidValueTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .focusable = Converter::ArkValue<Opt_Boolean>(true)
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
    EXPECT_TRUE(popupInfo.focusable);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsKeyboardAvoidModeDefaultValueTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsKeyboardAvoidModeDefaultValueTest,
    TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .keyboardAvoidMode = Converter::ArkValue<Opt_arkui_component_common_KeyboardAvoidMode>(Ark_Empty())
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
    EXPECT_FALSE(popupInfo.isAvoidKeyboard);
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOnStateChangeCallbackDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOnStateChangeCallbackDefaultTest,
    TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    struct CheckEvent { int32_t resourceId; std::optional<bool> isVisible; };
    static std::optional<CheckEvent> checkEvent = std::nullopt;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    auto arkOptions = Ark_CustomPopupOptions {
        .builder = *arkBuilder,
        .onStateChange = Converter::ArkValue<Opt_PopupStateChangeCallback>({})
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

    auto eventHub = popupInfo.popupNode->GetEventHub<BubbleEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(true);
    ASSERT_FALSE(checkEvent.has_value());
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOnStateChangeCallbackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOnStateChangeCallbackTest, TestSize.Level1)
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
        Converter::ArkValue<PopupStateChangeCallback>(checkCallback, nullptr, TEST_RESOURCE_ID_1);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    auto arkOptions = Ark_CustomPopupOptions {
        .builder = *arkBuilder,
        .onStateChange = Converter::ArkValue<Opt_PopupStateChangeCallback>(stateChangeCb)
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

    auto eventHub = popupInfo.popupNode->GetEventHub<BubbleEventHub>();
    ASSERT_NE(eventHub, nullptr);

    eventHub->FireChangeEvent(true);
    ASSERT_TRUE(checkEvent.has_value());
    ASSERT_TRUE(checkEvent.value().isVisible.has_value());
    EXPECT_TRUE(checkEvent.value().isVisible.value());
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOnWillDismissDefaultTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOnWillDismissDefaultTest, TestSize.Level1)
{
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(Ark_Empty())
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

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_TRUE(pattern->GetInteractiveDismiss());
    EXPECT_FALSE(pattern->HasOnWillDismiss());
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOnWillDismissBoolTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOnWillDismissBoolTest, TestSize.Level1)
{
    MockPipelineContext::GetCurrent()->SetTaskExecutor(AceType::MakeRefPtr<MockTaskExecutor>(false));
    auto arkShow = Converter::ArkValue<Opt_Boolean>(true);
    Ark_Union_Boolean_Callback_DismissPopupAction_Void dismissUnion;
    TypeHelper::WriteToUnion<Ark_Boolean>(dismissUnion) = Converter::ArkValue<Ark_Boolean>(false);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(dismissUnion)
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

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    EXPECT_FALSE(pattern->GetInteractiveDismiss());
}

/*
 * @tc.name: bindPopupCustomPopupOptionsOnWillDismissCallbackTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest17, DISABLED_bindPopupCustomPopupOptionsOnWillDismissCallbackTest, TestSize.Level1)
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

    Ark_Union_Boolean_Callback_DismissPopupAction_Void dismissUnion;
    TypeHelper::WriteToUnion<Callback_DismissPopupAction_Void>(dismissUnion) = dismissCb;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    const CustomNodeBuilderTestHelper<CommonMethodModifierTest17> builderHelper(this, frameNode);
    const CustomNodeBuilder builder = builderHelper.GetBuilder();
    static auto* arkBuilder = &builder;
    Ark_CustomPopupOptions arkOptions = {
        .builder = *arkBuilder,
        .onWillDismiss = Converter::ArkValue<Opt_Union_Boolean_Callback_DismissPopupAction_Void>(dismissUnion)
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

    auto pattern = popupInfo.popupNode->GetPattern<BubblePattern>();
    ASSERT_NE(pattern, nullptr);

    ASSERT_TRUE(pattern->HasOnWillDismiss());
    pattern->CallOnWillDismiss(static_cast<int32_t>(DismissReason::TOUCH_OUTSIDE));

    ASSERT_TRUE(checkEvent.has_value());
    ASSERT_TRUE(checkEvent.value().reason.has_value());
    EXPECT_EQ(checkEvent.value().resourceId, TEST_RESOURCE_ID_1);
    EXPECT_NE(checkEvent.value().reason.value(), DismissReason::TOUCH_OUTSIDE);
}

}

