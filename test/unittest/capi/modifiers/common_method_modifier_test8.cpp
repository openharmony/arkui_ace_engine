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
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/interfaces/native/implementation/draw_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/transition_effect_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"


using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_NAME = "geometryTransition";
    const auto ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_RESTORE_ID_NAME = "restoreId";
    const auto ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MONOPOLIZE_EVENTS_NAME = "monopolizeEvents";
    const auto ATTRIBUTE_MONOPOLIZE_EVENTS_DEFAULT_VALUE = "false";
    const auto ACTUAL_TRUE = true;
    const auto ACTUAL_FALSE = false;
    const auto EXPECTED_TRUE = "true";
    const auto EXPECTED_FALSE = "false";
    const auto EXPECTED_CONTEXT_ID = 123;
    const auto EXPECTED_NODE_ID = 555;
    const auto INVALID_REASON_VALUE = -1;
    const auto EXPECTED_SHORTCUTS_SIZE = 3;

    std::vector<std::pair<Opt_ModalTransition, ModalTransition>> modalTransitionTestPlan = {
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_DEFAULT), ModalTransition::DEFAULT },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_NONE), ModalTransition::NONE },
        { Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_ALPHA), ModalTransition::ALPHA },
        { Converter::ArkValue<Opt_ModalTransition>(static_cast<Ark_ModalTransition>(-1)), ModalTransition::DEFAULT },
        { Converter::ArkValue<Opt_ModalTransition>(Ark_Empty()), ModalTransition::DEFAULT },
    };
    std::vector<std::pair<uint32_t, std::optional<BindSheetDismissReason>>> bindSheetDismissReasonTestPlan = {
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::BACK_PRESSED),
            std::make_optional(BindSheetDismissReason::BACK_PRESSED) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::TOUCH_OUTSIDE),
            std::make_optional(BindSheetDismissReason::TOUCH_OUTSIDE) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::CLOSE_BUTTON),
            std::make_optional(BindSheetDismissReason::CLOSE_BUTTON) },
        { std::underlying_type_t<BindSheetDismissReason>(BindSheetDismissReason::SLIDE_DOWN),
            std::make_optional(BindSheetDismissReason::SLIDE_DOWN) },
        { INVALID_REASON_VALUE, std::nullopt },
    };
    std::vector<std::pair<Opt_ResourceColor, std::string>> colorTestPlan = {
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(ARK_ARKUI_COMPONENT_ENUMS_COLOR_TRANSPARENT), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_arkui_component_enums_Color>(static_cast<Ark_arkui_component_enums_Color>(-1)), "#00000000" },
        { Converter::ArkUnion<Opt_ResourceColor, Ark_Empty>(nullptr), "#00000000" },
    };
    std::vector<std::pair<Opt_Union_F64_String, double>> arkUnionNumberTestPlan = {
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(100), 100 },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(0), 0 },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-100), -100 },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(12.34), 12.34 },
        { Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-56.73), -56.73 }
    };
    std::vector<std::pair<Opt_Float64, double>> arkNumberTestPlan = {
        { Converter::ArkValue<Opt_Float64>(100), 100 },
        { Converter::ArkValue<Opt_Float64>(0), 0 },
        { Converter::ArkValue<Opt_Float64>(-100), -100 },
        { Converter::ArkValue<Opt_Float64>(12.34), 12.34 },
        { Converter::ArkValue<Opt_Float64>(-56.73), -56.73 }
    };
    std::vector<std::pair<Opt_Union_String_FunctionKey, bool>> arkShortcutKeyTestPlan = {
        { Converter::ArkUnion<Opt_Union_String_FunctionKey, Ark_String>("A"), true },
        { Converter::ArkUnion<Opt_Union_String_FunctionKey, Ark_String>("B"), true },
        { Converter::ArkUnion<Opt_Union_String_FunctionKey, Ark_String>("C"), true },
    };
    struct CheckEvent {
        int32_t nodeId;
    };
    struct CheckBuilderEvent {
        int32_t resourceId;
        Ark_NativePointer parentNode;
    };
    static std::optional<CheckBuilderEvent> checkBuilderEvent = std::nullopt;
    struct CheckNestedEvent {
        int32_t resourceId;
        std::optional<BindSheetDismissReason> reason;
        bool fired;
    };
    static std::optional<CheckNestedEvent> checkNestedEvent = std::nullopt;
    static std::optional<RefPtr<UINode>> uiNode = nullptr;
}
namespace Converter {

} // namespace Converter

class CommonMethodModifierTest8 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
    CustomNodeBuilder CreateCustomNodeBuilder(RefPtr<FrameNode>& node)
    {
        checkBuilderEvent.reset();
        static std::optional<RefPtr<UINode>> uiNode = node;
        auto checkCallback = [](
            Ark_VMContext context,
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkBuilderEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).InvokeSync(AceType::RawPtr(uiNode.value()));
            }
        };
        auto checkCallbackAsync = [](
            const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode,
            const Callback_Pointer_Void continuation) {
            checkBuilderEvent = {
                .resourceId = resourceId,
                .parentNode = parentNode
            };
            if (uiNode) {
                CallbackHelper(continuation).Invoke(AceType::RawPtr(uiNode.value()));
            }
        };
        CustomNodeBuilder customBuilder =
            Converter::ArkValue<CustomNodeBuilder>(checkCallbackAsync, checkCallback, EXPECTED_CONTEXT_ID);
        return customBuilder;
    }
    Opt_Callback_DismissContentCoverAction_Void CreateDismissCallback(FrameNode* frameNode)
    {
        checkNestedEvent.reset();
        auto dismissCallback = [](const Ark_Int32 resourceId, const Ark_DismissContentCoverAction parameter) {
            checkNestedEvent = {
                .resourceId = resourceId,
                .reason = Converter::OptConvert<BindSheetDismissReason>(parameter.reason)
            };
            auto helper = CallbackHelper(parameter.dismiss);
            checkNestedEvent->fired = true;
            helper.Invoke();
        };
        auto arkDismissCallback =
            Converter::ArkValue<Callback_DismissContentCoverAction_Void>(dismissCallback, frameNode->GetId());
        return Converter::ArkValue<Opt_Callback_DismissContentCoverAction_Void>(arkDismissCallback);
    }
};

///////// GeometryTransition
/*
 * @tc.name: setGeometryTransitionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setGeometryTransitionTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_GEOMETRY_TRANSITION_DEFAULT_VALUE);
}

/*
 * @tc.name: setGeometryTransitionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setGeometryTransitionTestValidValues, TestSize.Level1)
{
#ifdef WRONG_GEN_SIG
    ASSERT_NE(modifier_->setGeometryTransition0, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("id1"), "id1"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setGeometryTransition0(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_GEOMETRY_TRANSITION_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
#endif // WRONG_GEN_SIG
}

///////// RestoreId
/*
 * @tc.name: setRestoreIdTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setRestoreIdTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_RESTORE_ID_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_RESTORE_ID_DEFAULT_VALUE);
}

/*
 * @tc.name: setRestoreIdTestValidValues
 * @tc.desc:
 * @tc.type: FUNC /data/home/mlobakh/BZ_OHOS/OHOS/interface/sdk-js/api/@internal/component/ets/common.d.ts
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setRestoreIdTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setRestoreId, nullptr);
    using OneTestStep = std::tuple<Opt_Int32, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Int32>(1), "1"},
        {Converter::ArkValue<Opt_Int32>(2), "2"},
        {Converter::ArkValue<Opt_Int32>(3), "3"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setRestoreId(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_RESTORE_ID_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setMonopolizeEventsTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setMonopolizeEventsTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMonopolizeEvents, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, ATTRIBUTE_MONOPOLIZE_EVENTS_DEFAULT_VALUE);

    auto arkTrueValue = Converter::ArkValue<Opt_Boolean>(ACTUAL_TRUE);
    modifier_->setMonopolizeEvents(node_, &arkTrueValue);
    fullJson = GetJsonValue(node_);
    resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, EXPECTED_TRUE);

    auto arkFalseValue = Converter::ArkValue<Opt_Boolean>(ACTUAL_FALSE);
    modifier_->setMonopolizeEvents(node_, &arkFalseValue);
    fullJson = GetJsonValue(node_);
    resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MONOPOLIZE_EVENTS_NAME);
    EXPECT_EQ(resultValue, EXPECTED_FALSE);
}

/*
 * @tc.name: setBindContentCover0IsShowTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setBindContentCover0IsShowTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover0, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto optModal = Converter::ArkValue<Opt_ModalTransition>(ARK_MODAL_TRANSITION_ALPHA);

    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover0(node_, &arkShow, &customBuilder, &optModal);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);

    arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_FALSE);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover0(node_, &arkShow, &customBuilder, &optModal);
    EXPECT_FALSE(checkBuilderEvent.has_value());
}

/*
 * @tc.name: setBindContentCover0ModalTransitionTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover0ModalTransitionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover0, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);

    for (auto& [actual, expected] : modalTransitionTestPlan) {
        modifier_->setBindContentCover0(node_, &arkShow, &customBuilder, &actual);
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        EXPECT_NE(modal, nullptr);
        auto pattern = modal->GetPattern<ModalPresentationPattern>();
        EXPECT_NE(pattern, nullptr);
        EXPECT_TRUE(checkBuilderEvent.has_value());
        EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
        EXPECT_EQ(pattern->GetType(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1IsShowTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(Ark_Empty());

    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);

    arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_FALSE);
    checkBuilderEvent.reset();
    EXPECT_FALSE(checkBuilderEvent.has_value());
    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
    EXPECT_FALSE(checkBuilderEvent.has_value());
}

/*
 * @tc.name: setBindContentCover1OnAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1OnAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    static std::optional<CheckEvent> checkEventAppear = std::nullopt;
    auto onAppearCallback = [](Ark_Int32 nodeId) {
        checkEventAppear = {
            .nodeId = nodeId,
        };
    };
    auto arkOnAppearCallback = Converter::ArkValue<Callback_Void>(onAppearCallback, frameNode->GetId());
    auto optOnAppearCallback = Converter::ArkValue<Opt_Callback_Void>(arkOnAppearCallback);

    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onAppear = optOnAppearCallback,
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());

    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEventAppear.has_value());

    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);

    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    EXPECT_NE(parentNode, nullptr);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
    EXPECT_TRUE(checkEventAppear.has_value());
    EXPECT_EQ(checkEventAppear->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setBindContentCover1OnDisAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1OnDisAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    static std::optional<CheckEvent> checkEventDisAppear = std::nullopt;
    auto onDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEventDisAppear = {
            .nodeId = nodeId,
        };
    };
    auto arkOnDisAppearCallback = Converter::ArkValue<Callback_Void>(onDisAppearCallback, frameNode->GetId());
    auto optOnDisAppearCallback = Converter::ArkValue<Opt_Callback_Void>(arkOnDisAppearCallback);

    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onDisappear = optOnDisAppearCallback,
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEventDisAppear.has_value());

    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);

    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_NE(modal, nullptr);
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnDisappear();

    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    EXPECT_NE(parentNode, nullptr);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
    EXPECT_TRUE(checkEventDisAppear.has_value());
    EXPECT_EQ(checkEventDisAppear->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setBindContentCover1OnWillAppearTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1OnWillAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    static std::optional<CheckEvent> checkEventWillAppear = std::nullopt;
    auto onWillAppearCallback = [](Ark_Int32 nodeId) {
        checkEventWillAppear = {
            .nodeId = nodeId,
        };
    };
    auto arkOnWillAppearCallback = Converter::ArkValue<Callback_Void>(onWillAppearCallback, frameNode->GetId());
    auto optOnWillAppearCallback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillAppearCallback);

    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onWillAppear = optOnWillAppearCallback,
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEventWillAppear.has_value());

    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    EXPECT_NE(parentNode, nullptr);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
    EXPECT_TRUE(checkEventWillAppear.has_value());
    EXPECT_EQ(checkEventWillAppear->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1OnWillDisAppearTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    static std::optional<CheckEvent> checkEventWillDisAppear = std::nullopt;
    auto onWillDisAppearCallback = [](Ark_Int32 nodeId) {
        checkEventWillDisAppear = {
            .nodeId = nodeId,
        };
    };
    auto arkOnWillDisAppearCallback = Converter::ArkValue<Callback_Void>(onWillDisAppearCallback, frameNode->GetId());
    auto optOnWillDisAppearCallback = Converter::ArkValue<Opt_Callback_Void>(arkOnWillDisAppearCallback);
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onWillDisappear = optOnWillDisAppearCallback,
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());

    EXPECT_FALSE(checkBuilderEvent.has_value());
    EXPECT_FALSE(checkEventWillDisAppear.has_value());
    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);

    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_NE(modal, nullptr);
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(pattern, nullptr);
    pattern->OnWillDisappear();

    auto parentNode = reinterpret_cast<FrameNode*>(checkBuilderEvent->parentNode);
    EXPECT_NE(parentNode, nullptr);
    EXPECT_TRUE(checkBuilderEvent.has_value());
    EXPECT_EQ(checkBuilderEvent->resourceId, EXPECTED_CONTEXT_ID);
    EXPECT_EQ(parentNode->GetId(), frameNode->GetId());
    EXPECT_TRUE(checkEventWillDisAppear.has_value());
    EXPECT_EQ(checkEventWillDisAppear->nodeId, frameNode->GetId());
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1DismissCallbackTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto onDismissCallback = CreateDismissCallback(frameNode);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);
    auto arkOptions = Ark_ContentCoverOptions {
        .onWillDismiss = onDismissCallback
    };
    auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
    auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_EQ(modal, nullptr);

    modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);

    modal = AceType::DynamicCast<FrameNode>(node->GetParent());
    EXPECT_NE(modal, nullptr);
    auto pattern = modal->GetPattern<ModalPresentationPattern>();
    EXPECT_NE(pattern, nullptr);
    for (auto& [actual, expected] : bindSheetDismissReasonTestPlan) {
        checkNestedEvent.reset();
        EXPECT_FALSE(checkNestedEvent.has_value());
        pattern->CallOnWillDismiss(actual);

        EXPECT_TRUE(checkNestedEvent.has_value());
        EXPECT_EQ(checkNestedEvent->resourceId, frameNode->GetId());
        EXPECT_EQ(checkNestedEvent->reason, expected);
        EXPECT_TRUE(checkNestedEvent->fired);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1BackgroundColorTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);

    for (auto& [actual, expected] : colorTestPlan) {
        auto arkOptions = Ark_ContentCoverOptions {
            .backgroundColor = actual,
        };
        auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
        modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        EXPECT_NE(modal, nullptr);
        auto context = modal->GetRenderContext();
        EXPECT_NE(context, nullptr);
        auto backgroundColor = context->GetBackgroundColor();
        EXPECT_TRUE(backgroundColor.has_value());
        EXPECT_EQ(backgroundColor->ToString(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1ModalTransitionTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);

    for (auto& [actual, expected] : modalTransitionTestPlan) {
        auto arkOptions = Ark_ContentCoverOptions {
            .modalTransition = actual,
        };
        auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
        modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
        auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
        EXPECT_NE(modal, nullptr);
        auto pattern = modal->GetPattern<ModalPresentationPattern>();
        EXPECT_NE(pattern, nullptr);
        EXPECT_EQ(pattern->GetType(), expected);
    }
}

/*
 * @tc.name: setBindContentCover1Test
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, DISABLED_setBindContentCover1TransitionEffectTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setBindContentCover1, nullptr);
    FrameNode* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto node = BlankModelNG::CreateFrameNode(EXPECTED_NODE_ID);
    EXPECT_NE(node, nullptr);
    auto customBuilder = Converter::ArkValue<Opt_CustomNodeBuilder>(CreateCustomNodeBuilder(node));
    auto arkShow = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(ACTUAL_TRUE);

    for (auto& [actualC, expectedC] : arkUnionNumberTestPlan) {
        for (auto& [actualS, expectedS] : arkNumberTestPlan) {
            auto arkScale = Ark_ScaleOptions {
                .centerX = actualC,
                .centerY = actualC,
                .x = actualS,
                .y = actualS,
                .z = actualS,
            };
            const auto accessor = fullAPI_->getAccessors()->getTransitionEffectAccessor();
            auto peer = accessor->scale(&arkScale);
            auto arkOptions = Ark_ContentCoverOptions {
                .transition = Converter::ArkValue<Opt_TransitionEffect>(peer)
            };
            auto optOptions = Converter::ArkValue<Opt_ContentCoverOptions>(arkOptions);
            auto modal = AceType::DynamicCast<FrameNode>(node->GetParent());
            auto pattern = modal ? modal->GetPattern<ModalPresentationPattern>() : nullptr;
            if (pattern) {
                pattern->SetHasTransitionEffect(ACTUAL_FALSE);
            }
            EXPECT_FALSE(pattern ? pattern->HasTransitionEffect() : ACTUAL_FALSE);
            modifier_->setBindContentCover1(node_, &arkShow, &customBuilder, &optOptions);
            modal = AceType::DynamicCast<FrameNode>(node->GetParent());
            EXPECT_NE(modal, nullptr);
            pattern = modal->GetPattern<ModalPresentationPattern>();
            EXPECT_NE(pattern, nullptr);
            EXPECT_TRUE(pattern->HasTransitionEffect());
        }
    }
}

/**
 * @tc.name: setKeyboardShortcutTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest8, setKeyboardShortcutTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKeyboardShortcut, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto callback = [](Ark_VMContext context, const Ark_Int32 resourceId) {
        checkEvent = {
            .nodeId = resourceId,
        };
    };
    const int32_t contextId = 123;
    auto arkCallback = Converter::ArkValue<Callback_Void>(callback, contextId);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);

    std::vector<Ark_ModifierKey> modifiers = {
        Ark_ModifierKey::ARK_MODIFIER_KEY_ALT,
        Ark_ModifierKey::ARK_MODIFIER_KEY_SHIFT,
    };
    Converter::ArkArrayHolder<Array_ModifierKey> keyHolder(modifiers);
    Array_ModifierKey keysHolder = keyHolder.ArkValue();
    auto keys = Converter::ArkValue<Opt_Array_ModifierKey>(keysHolder);
    auto previous = eventHub->GetKeyboardShortcut();

    for (auto& [actual, expected] : arkShortcutKeyTestPlan) {
        modifier_->setKeyboardShortcut(node_, &actual, &keys, &optCallback);
        auto shortcuts = eventHub->GetKeyboardShortcut();
        EXPECT_FALSE(checkEvent.has_value());
        EXPECT_EQ(previous.size() != shortcuts.size(), expected);
        previous = shortcuts;
    }
    auto shortcuts = eventHub->GetKeyboardShortcut();
    EXPECT_EQ(shortcuts.size(), EXPECTED_SHORTCUTS_SIZE);

    for (auto& shortcut : shortcuts) {
        checkEvent.reset();
        auto action = shortcut.onKeyboardShortcutAction;
        EXPECT_FALSE(checkEvent.has_value());
        EXPECT_NE(action, nullptr);
        action();
        EXPECT_TRUE(checkEvent.has_value());
        EXPECT_EQ(checkEvent->nodeId, contextId);
    }
}
}
