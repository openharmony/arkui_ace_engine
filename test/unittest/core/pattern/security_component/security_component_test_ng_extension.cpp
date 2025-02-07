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

#include <algorithm>
#include <cstddef>
#include <optional>
#include <utility>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_common.h"
#include "core/components_ng/pattern/security_component/location_button/location_button_model_ng.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_common.h"
#include "core/components_ng/pattern/security_component/paste_button/paste_button_model_ng.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_common.h"
#include "core/components_ng/pattern/security_component/save_button/save_button_model_ng.h"
#include "core/components_ng/pattern/security_component/security_component_handler.h"
#include "core/components_ng/pattern/security_component/security_component_pattern.h"
#include "core/components_ng/pattern/security_component/security_component_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"
#include "test/mock/base/mock_task_executor.h"
#include "security_component_test_ng.h"
#undef protected
#undef private

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
}

namespace {
    constexpr float MAX_ROTATE = 360.0f;
    constexpr float TEST_FONT_SIZE = 2.0;
class TestNode : public UINode {
    DECLARE_ACE_TYPE(TestNode, UINode);

    public:
        static RefPtr<TestNode> CreateTestNode(int32_t nodeId)
        {
            auto node = MakeRefPtr<TestNode>(nodeId);
            return node;
        }

        bool IsAtomicNode() const override
        {
            return true;
        }

        explicit TestNode(int32_t nodeId) : UINode("TestNode", nodeId) {}
        ~TestNode() override = default;
    };
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest004
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest004, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateForegroundColor(Color::TRANSPARENT);
    std::string message;
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetForegroundColor().value(), Color::TRANSPARENT);
    renderContext->UpdateForegroundColor(Color::GRAY);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest005
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest005, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    RefPtr<BasicShape> basicShape;
    renderContext->UpdateClipMask(basicShape);
    std::string message;
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest006
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest006, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateClipEdge(true);
    std::string message;
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));

    OffsetF invalidOffset(-100.0, -100.0);
    childFrameNode->geometryNode_->SetFrameOffset(invalidOffset);
    EXPECT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest007
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest007, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontColorBlend(Color::TRANSPARENT);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontColorBlend().value(), Color::TRANSPARENT);
    renderContext->UpdateFrontColorBlend(Color::GRAY);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest008
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest008, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontHueRotate(0);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontHueRotate().value(), 0.0f);
    renderContext->UpdateFrontHueRotate(MAX_ROTATE);
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontHueRotate().value(), MAX_ROTATE);
    renderContext->UpdateFrontHueRotate(1);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest009
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest009, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontSepia(0.0_vp);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontSepia().value().ConvertToVp(), 0.0f);
    renderContext->UpdateFrontSepia(1.0_vp);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest010
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest010, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    InvertVariant invert = 0.0f;
    renderContext->UpdateFrontInvert(invert);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontInvert().value(), InvertVariant(0.0f));
    invert = 1.0f; // 1.0 means have frontinvert
    renderContext->UpdateFrontInvert(invert);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest011
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest011, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontContrast(1.0_vp);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontContrast().value().ConvertToVp(), 1.0f);
    renderContext->UpdateFrontContrast(2.0_vp);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest012
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest012, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontSaturate(1.0_vp);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontSaturate().value().ConvertToVp(), 1.0f);
    renderContext->UpdateFrontSaturate(2.0_vp);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest013
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest013, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontGrayScale(0.0_vp);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontGrayScale().value().ConvertToVp(), 0.0f);
    renderContext->UpdateFrontGrayScale(1.0_vp);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest014
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest014, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontBlurRadius(0.0_px);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest015
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest015, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto property = parentFrameNode->GetLayoutProperty<SecurityComponentLayoutProperty>();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(property, nullptr);
    property->UpdateVisibility(VisibleType::VISIBLE);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(property->GetVisibility().value(), VisibleType::VISIBLE);
    property->UpdateVisibility(VisibleType::INVISIBLE);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest016
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest016, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateFrontBrightness(1.0_vp);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    ASSERT_EQ(renderContext->GetFrontBrightness().value().ConvertToVp(), 1.0f);
    renderContext->UpdateFrontBrightness(2.0_vp);
    ASSERT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest017
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest017, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    renderContext->UpdateOpacity(1);
    std::string message;
    EXPECT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    EXPECT_EQ(renderContext->GetOpacity().value(), 1.0f);
    renderContext->UpdateOpacity(2);
    EXPECT_TRUE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));

    parentFrameNode->tag_ = V2::MENU_WRAPPER_ETS_TAG;
    EXPECT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));

    // parent is not FrameNode
    RefPtr<TestNode> unFrameNode = AceType::MakeRefPtr<TestNode>(0);
    unFrameNode->AddChild(childFrameNode);
    EXPECT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
}

/**
 * @tc.name: SecurityComponentCheckParentNodesEffectTest018
 * @tc.desc: Test security component CheckParentNodesEffect
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentCheckParentNodesEffectTest018, TestSize.Level1)
{
    RefPtr<FrameNode> parentFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(parentFrameNode, nullptr);
    RefPtr<FrameNode> childFrameNode = CreateSecurityComponent(0, 0,
        static_cast<int32_t>(ButtonType::CAPSULE), V2::PASTE_BUTTON_ETS_TAG);
    ASSERT_NE(childFrameNode, nullptr);
    parentFrameNode->AddChild(childFrameNode);

    auto renderContext = parentFrameNode->GetRenderContext();
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    ASSERT_NE(renderContext, nullptr);
    BlurStyleOption blur;
    blur.blurStyle = BlurStyle::NO_MATERIAL;
    renderContext->UpdateFrontBlurStyle(blur);
    std::string message;
    ASSERT_FALSE(SecurityComponentHandler::CheckParentNodesEffect(childFrameNode, buttonInfo, message));
    auto blurStyleOption = renderContext->GetFrontBlurStyle();
    ASSERT_EQ(blurStyleOption->blurStyle, BlurStyle::NO_MATERIAL);
}

/**
 * @tc.name: SecurityComponentIsOutOfParentWithRound001
 * @tc.desc: Test security component IsOutOfParentWithRound
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentIsOutOfParentWithRound001, TestSize.Level1)
{
    RectF smallRect(1.0, 1.0, 10.0, 10.0);
    RectF largerRect(1.0, 1.0, 12.0, 12.0);
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    EXPECT_EQ(SecurityComponentHandler::IsOutOfParentWithRound(smallRect, largerRect, buttonInfo), true);
    EXPECT_EQ(SecurityComponentHandler::IsOutOfParentWithRound(largerRect, smallRect, buttonInfo), false);
}

/**
 * @tc.name: SecurityComponentInitChildInfo001
 * @tc.desc: Test security component InitChildInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentInitChildInfo001, TestSize.Level1)
{
    RefPtr<SecurityComponentPattern> pattern =
        AceType::MakeRefPtr<SecurityComponentPattern>();
    RefPtr<FrameNode> node = AceType::MakeRefPtr<FrameNode>(V2::LOCATION_BUTTON_ETS_TAG, 1, pattern, false);
    OHOS::Security::SecurityComponent::SecCompBase buttonInfo;
    EXPECT_FALSE(SecurityComponentHandler::InitChildInfo(buttonInfo, node));
}

/**
 * @tc.name: SecurityComponentInitButtonInfo001
 * @tc.desc: Test security component InitButtonInfo
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentInitButtonInfo001, TestSize.Level1)
{
    RefPtr<SecurityComponentPattern> pattern =
        AceType::MakeRefPtr<SecurityComponentPattern>();
    RefPtr<FrameNode> node = AceType::MakeRefPtr<FrameNode>(V2::MENU_WRAPPER_ETS_TAG, 1, pattern, false);
    std::string compInfo;
    Security::SecurityComponent::SecCompType type;
    std::string message;
    EXPECT_FALSE(SecurityComponentHandler::InitButtonInfo(compInfo, node, type, message));
}

/**
 * @tc.name: PasteButtonModelNGCreateNode001
 * @tc.desc: Test paste button create Node
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, PasteButtonModelNGCreateNode001, TestSize.Level1)
{
    auto frameNode = PasteButtonModelNG::GetInstance()->CreateNode(0, 0, 0, false);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: PasteButtonModelNGCreateNode002
 * @tc.desc: Test paste button create symbol Node
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, PasteButtonModelNGCreateNode002, TestSize.Level1)
{
    auto frameNode = PasteButtonModelNG::GetInstance()->CreateNode(0, 0, 0, false, 0);
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: PasteButtonModelNGGetTextResource001
 * @tc.desc: Test paste button get text resource failed
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, PasteButtonModelNGGetTextResource001, TestSize.Level1)
{
    auto scTheme = MockPipelineContext::GetCurrent()->GetThemeManager();
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    std::string text;
    EXPECT_FALSE(PasteButtonModelNG::GetInstance()->GetTextResource(0, text));
    MockPipelineContext::GetCurrent()->SetThemeManager(scTheme);
}

/**
 * @tc.name: LocationButtonModelNGGetTextResource001
 * @tc.desc: Test location button get text resource failed
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, LocationButtonModelNGGetTextResource001, TestSize.Level1)
{
    auto scTheme = MockPipelineContext::GetCurrent()->GetThemeManager();
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    std::string text;
    EXPECT_FALSE(LocationButtonModelNG::GetInstance()->GetTextResource(0, text));
    MockPipelineContext::GetCurrent()->SetThemeManager(scTheme);
}

/**
 * @tc.name: SaveButtonModelNGGetTextResource001
 * @tc.desc: Test save button get text resource failed
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SaveButtonModelNGGetTextResource001, TestSize.Level1)
{
    auto scTheme = MockPipelineContext::GetCurrent()->GetThemeManager();
    MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
    std::string text;
    EXPECT_FALSE(SaveButtonModelNG::GetInstance()->GetTextResource(0, text));
    MockPipelineContext::GetCurrent()->SetThemeManager(scTheme);
}

/**
 * @tc.name: SecurityComponentProbeInitProbeTask001
 * @tc.desc: Test security component probe init task
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentProbeInitProbeTask001, TestSize.Level1)
{
    SecurityComponentProbe probe;
    std::string compInfo;
    // not init
    ASSERT_EQ(probe.GetComponentInfo(0, compInfo), -1);

    // init twice
    probe.InitProbeTask();
    probe.InitProbeTask();
    ASSERT_TRUE(probe.taskExec_.has_value());
    auto pipeline = PipelineBase::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    ASSERT_EQ(probe.GetComponentInfo(1001, compInfo), 0);
}

/**
 * @tc.name: SecurityComponentLayoutElementIconElement001
 * @tc.desc: Test security component icon element
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutElementIconElement001, TestSize.Level1)
{
    IconLayoutElement icon;
    icon.isExist_ = false;
    icon.DoMeasure();
    ASSERT_EQ(icon.ShrinkWidth(0.0), 0.0);
    ASSERT_EQ(icon.ShrinkHeight(0.0), 0.0);

    icon.isExist_ = true;
    icon.isSetSize_ = true;
    ASSERT_EQ(icon.ShrinkWidth(0.0), 0.0);
    ASSERT_EQ(icon.ShrinkHeight(0.0), 0.0);

    icon.isSetSize_ = false;
    icon.minIconSize_ = 0.0;
    icon.width_ = 2.0;
    icon.height_ = 2.0;
    ASSERT_EQ(icon.ShrinkWidth(1.0), 0.0);
    ASSERT_EQ(icon.ShrinkHeight(1.0), 0.0);
}

/**
 * @tc.name: SecurityComponentLayoutElementTextElement001
 * @tc.desc: Test security component text element
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutElementTextElement001, TestSize.Level1)
{
    TextLayoutElement text;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<SecurityComponentLayoutProperty> property =
        AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    RefPtr<TextLayoutProperty> textProp = AceType::MakeRefPtr<TextLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> wrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geoNode, textProp);
    property->UpdateSecurityComponentDescription(-1);
    text.Init(property, wrapper);
    ASSERT_FALSE(text.isExist_);
    property->UpdateSecurityComponentDescription(0);
    property->UpdateFontSize(Dimension(2.0));
    text.Init(property, wrapper);
    ASSERT_TRUE(text.isExist_);
    ASSERT_TRUE(text.isSetSize_);

    RefPtr<TextLayoutProperty> textProperty =
        AceType::MakeRefPtr<TextLayoutProperty>();
    text.minTextSize_ = SizeF(1.0, 1.0);
    text.ChooseExactFontSize(textProperty, true);
    text.isExist_ = false;
    ASSERT_EQ(text.ShrinkWidth(0.0), 0.0);
    ASSERT_EQ(text.ShrinkHeight(0.0), 0.0);
    text.isExist_ = true;
    text.isSetSize_ = true;
    ASSERT_EQ(text.ShrinkWidth(0.0), 0.0);
    ASSERT_EQ(text.ShrinkHeight(0.0), 0.0);
}

/**
 * @tc.name: SecurityComponentLayoutElementTextElement002
 * @tc.desc: Test security component text element
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutElementTextElement002, TestSize.Level1)
{
    TextLayoutElement text;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<SecurityComponentLayoutProperty> property =
        AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    RefPtr<TextLayoutProperty> textProp = AceType::MakeRefPtr<TextLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapper> wrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geoNode, textProp);
    property->UpdateSecurityComponentDescription(-1);
    text.Init(property, wrapper);
    ASSERT_FALSE(text.isExist_);
    std::optional<SizeF> currentTextSize;
    ASSERT_FALSE(text.DidExceedMaxLines(currentTextSize));
    property->UpdateSecurityComponentDescription(0);
    property->UpdateFontSize(Dimension(15.0));
    property->UpdateAdaptMaxFontSize(Dimension(20.0));
    property->UpdateAdaptMinFontSize(Dimension(10.0));
    text.Init(property, wrapper);
    ASSERT_TRUE(text.isExist_);
    ASSERT_TRUE(text.isSetSize_);

    text.UpdateFontSize();
    ASSERT_EQ(property->GetFontSize()->ConvertToFp(), 15.0);
    property->UpdateBackgroundTopPadding(Dimension(0.0));
    property->UpdateBackgroundBottomPadding(Dimension(0.0));
    ASSERT_EQ(text.GetHeightConstraint(property, 30.0), 30.0);
    property->UpdateTextIconLayoutDirection(SecurityComponentLayoutDirection::VERTICAL);
    property->UpdateIconSize(Dimension(5.0));
    property->UpdateTextIconSpace(Dimension(5.0));
    ASSERT_EQ(text.GetHeightConstraint(property, 30.0), 20.0);
    ASSERT_FALSE(text.DidExceedMaxLines(currentTextSize));
}

/**
 * @tc.name: SecurityComponentPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: Test security component OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    RefPtr<SecurityComponentLayoutProperty> prop = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    RefPtr<GeometryNode> geoNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> wrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geoNode, prop);
    DirtySwapConfig config;
    config.skipMeasure = true;
    ASSERT_FALSE(pattern.OnDirtyLayoutWrapperSwap(wrapper, config));
    config.skipMeasure = false;
    wrapper->skipMeasureContent_ = true;
    ASSERT_FALSE(pattern.OnDirtyLayoutWrapperSwap(wrapper, config));

    RefPtr<LayoutAlgorithmWrapper> layoutWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>());
    wrapper->SetLayoutAlgorithm(layoutWrapper);
    config.skipMeasure = false;
    wrapper->skipMeasureContent_ = false;
    ASSERT_TRUE(pattern.OnDirtyLayoutWrapperSwap(wrapper, config));
}

/**
 * @tc.name: SecurityComponentPatternOnKeyEvent001
 * @tc.desc: Test security component OnKeyEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternOnKeyEvent001, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    KeyEvent event;
    event.action = KeyAction::UP;
    ASSERT_FALSE(pattern.OnKeyEvent(event));

    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_CALL;
    ASSERT_FALSE(pattern.OnKeyEvent(event));

    // frameNode is null
    event.code = KeyCode::KEY_SPACE;
    ASSERT_FALSE(pattern.OnKeyEvent(event));

    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    pattern.frameNode_ = frameNode;
    ASSERT_TRUE(pattern.OnKeyEvent(event));
}

/**
 * @tc.name: SecurityComponentPatternInitOnKeyEvent001
 * @tc.desc: Test security component InitOnKeyEvent
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternInitOnKeyEvent001, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    pattern.InitOnKeyEvent(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
    KeyEvent event;
    focusHub->ProcessOnKeyEventInternal(event);
    ASSERT_TRUE(pattern.isSetOnKeyEvent);
}

/**
 * @tc.name: SecurityComponentPatternIsParentMenu001
 * @tc.desc: Test security component IsParentMenu
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternIsParentMenu001, TestSize.Level1)
{
    RefPtr<SecurityComponentPattern> pattern = AceType::MakeRefPtr<SecurityComponentPattern>();
    auto menuNode = AceType::MakeRefPtr<FrameNode>(V2::MENU_WRAPPER_ETS_TAG, 1, pattern);
    auto locationButton = AceType::MakeRefPtr<FrameNode>(V2::LOCATION_BUTTON_ETS_TAG, 1, pattern);
    auto text = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, 1, pattern);

    locationButton->SetParent(text);
    ASSERT_FALSE(pattern->IsParentMenu(locationButton));

    text->SetParent(menuNode);
    ASSERT_TRUE(pattern->IsParentMenu(locationButton));
}

/**
 * @tc.name: SecurityComponentPatternOnTouch001
 * @tc.desc: Test security component OnTouch
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternOnTouch001, TestSize.Level1)
{
    // DOWN
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset offset(1.0, 1.0);
    locationInfo.SetLocalLocation(offset);
    TouchEventInfo info("");
    info.AddTouchLocationInfo(std::move(locationInfo));
    SecurityComponentPattern pattern;
    pattern.OnTouch(info);
    ASSERT_NE(pattern.lastTouchOffset_, nullptr);

    // UP
    TouchLocationInfo locationInfo1(0);
    locationInfo1.SetTouchType(TouchType::UP);
    Offset offset1(1.0, 1.0);
    locationInfo1.SetLocalLocation(offset1);
    TouchEventInfo info1("");
    info1.AddTouchLocationInfo(std::move(locationInfo1));
    pattern.OnTouch(info1);
    ASSERT_EQ(pattern.lastTouchOffset_, nullptr);

    // OTHERS
    TouchLocationInfo locationInfo2(0);
    locationInfo2.SetTouchType(TouchType::PULL_DOWN);
    Offset offset2(1.0, 1.0);
    locationInfo2.SetLocalLocation(offset2);
    TouchEventInfo info2("");
    info2.AddTouchLocationInfo(std::move(locationInfo2));
    pattern.OnTouch(info2);
    ASSERT_EQ(pattern.lastTouchOffset_, nullptr);
}

/**
 * @tc.name: SecurityComponentPatternOnTouch002
 * @tc.desc: Test security component OnTouch
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternOnTouch002, TestSize.Level1)
{
    // DOWN
    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset offset(1.0, 1.0);
    locationInfo.SetLocalLocation(offset);
    TouchEventInfo info("");
    info.AddTouchLocationInfo(std::move(locationInfo));
    SecurityComponentPattern pattern;
    pattern.OnTouch(info);
    ASSERT_NE(pattern.lastTouchOffset_, nullptr);

    // UP other location
    TouchLocationInfo locationInfo1(0);
    locationInfo1.SetTouchType(TouchType::UP);
    Offset offset1(100.0, 100.0);
    locationInfo1.SetLocalLocation(offset1);
    TouchEventInfo info1("");
    info1.AddTouchLocationInfo(std::move(locationInfo1));
    pattern.OnTouch(info1);
    ASSERT_EQ(pattern.lastTouchOffset_, nullptr);
}

/**
 * @tc.name: SecurityComponentPatternInitOnTouchEvent001
 * @tc.desc: Test security component InitOnTouch
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternInitOnTouchEvent001, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    pattern.InitOnTouch(frameNode);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();

    TouchLocationInfo locationInfo(0);
    locationInfo.SetTouchType(TouchType::DOWN);
    Offset offset(1.0, 1.0);
    locationInfo.SetLocalLocation(offset);
    TouchEventInfo info("");
    info.AddTouchLocationInfo(std::move(locationInfo));

    ASSERT_TRUE(gestureHub->touchEventActuator_ != nullptr);
    ASSERT_TRUE(gestureHub->touchEventActuator_->touchEvents_.size() > 0);
    auto impl = gestureHub->touchEventActuator_->touchEvents_.front()->callback_;
    impl(info);
    ASSERT_NE(pattern.onTouchListener_, nullptr);
}

/**
 * @tc.name: SecurityComponentPatternToJsonValue001
 * @tc.desc: Test security component without bg ToJsonValue
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternToJsonValue001, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        BUTTON_TYPE_NULL, V2::LOCATION_BUTTON_ETS_TAG);
    pattern.frameNode_ = frameNode;
    auto jsonNode = JsonUtil::Create(true);
    pattern.ToJsonValue(jsonNode, filter);
    ASSERT_EQ(jsonNode->GetString("type", ""), V2::LOCATION_BUTTON_ETS_TAG);
}

/**
 * @tc.name: SecurityComponentPatternToJsonValue002
 * @tc.desc: Test security component without text ToJsonValue
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternToJsonValue002, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode =
        CreateSecurityComponent(static_cast<int32_t>(SecurityComponentDescription::TEXT_NULL),
        0, 0, V2::LOCATION_BUTTON_ETS_TAG);
    pattern.frameNode_ = frameNode;
    auto jsonNode = JsonUtil::Create(true);
    pattern.ToJsonValue(jsonNode, filter);
    ASSERT_EQ(jsonNode->GetString("type", ""), V2::LOCATION_BUTTON_ETS_TAG);
}

/**
 * @tc.name: SecurityComponentPatternToJsonValue003
 * @tc.desc: Test security component without icon ToJsonValue
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentPatternToJsonValue003, TestSize.Level1)
{
    SecurityComponentPattern pattern;
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0,
        static_cast<int32_t>(SecurityComponentIconStyle::ICON_NULL),
        0, V2::LOCATION_BUTTON_ETS_TAG);
    pattern.frameNode_ = frameNode;
    auto jsonNode = JsonUtil::Create(true);
    pattern.ToJsonValue(jsonNode, filter);
    ASSERT_EQ(jsonNode->GetString("type", ""), V2::LOCATION_BUTTON_ETS_TAG);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmGetChildWrapper001
 * @tc.desc: Test security component GetChildWrapper no exist child
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmGetChildWrapper001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        0, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto buttonWrapper = CreateLayoutWrapper(frameNode);
    buttonWrapper->currentChildCount_ = 1;
    buttonWrapper->layoutWrapperBuilder_ = nullptr;
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    ASSERT_EQ(buttonAlgorithm->GetChildWrapper(&*buttonWrapper, ""), nullptr);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmUpdateChildPosition001
 * @tc.desc: Test security component UpdateChildPosition
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmUpdateChildPosition001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        0, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = CreateLayoutWrapper(frameNode);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textGeometryNode = textNode->geometryNode_;
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto textWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(textNode)), textGeometryNode, textLayoutProperty);
    layoutWrapper->childrenMap_[0] = textWrapper;
    layoutWrapper->currentChildCount_ = 1;

    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    OffsetF offset(1.0, 0.0);
    buttonAlgorithm->UpdateChildPosition(&*layoutWrapper, V2::TEXT_ETS_TAG, offset);

    ASSERT_EQ(textGeometryNode->GetMarginFrameOffset().GetX(), 1.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkWidth001
 * @tc.desc: Test security component ShrinkWidth, shrink left and right padding
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkWidth001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->left_ = PaddingLayoutElement();
    buttonAlgorithm->left_.Init(false, false, 4.0, 0.0); // left padding 4.0, minsize 0.0
    buttonAlgorithm->right_ = PaddingLayoutElement();
    buttonAlgorithm->right_.Init(false, false, 4.0, 0.0); // right_ padding 4.0, minsize 0.0
    // shrink 2.0px, left to 3.0, right to 3.0, total 6.0
    ASSERT_EQ(buttonAlgorithm->ShrinkWidth(2.0), 6.0);
    ASSERT_EQ(buttonAlgorithm->left_.width_, 3.0);
    ASSERT_EQ(buttonAlgorithm->right_.width_, 3.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkWidth002
 * @tc.desc: Test security component ShrinkWidth, shrink middle padding
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkWidth002, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->left_ = PaddingLayoutElement();
    buttonAlgorithm->left_.Init(false, false, 4.0, 4.0); // left padding 4.0, minsize 4.0
    buttonAlgorithm->right_ = PaddingLayoutElement();
    buttonAlgorithm->right_.Init(false, false, 4.0, 4.0); // right_ padding 4.0, minsize 4.0
    buttonAlgorithm->middle_ = PaddingLayoutElement();
    buttonAlgorithm->middle_.Init(false, false, 4.0, 0.0); // middle_ padding 4.0, minsize 0.0
    // shrink 2.0px, left to 3.0, right to 3.0, total 6.0
    ASSERT_EQ(buttonAlgorithm->ShrinkWidth(2.0), 10.0);
    ASSERT_EQ(buttonAlgorithm->middle_.width_, 2.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkWidth003
 * @tc.desc: Test security component ShrinkWidth, shrink text when isVertical_
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkWidth003, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textGeometryNode = textNode->geometryNode_;
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    auto textWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(textNode)), textGeometryNode, textLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateSecurityComponentDescription(1);

    buttonAlgorithm->text_ = TextLayoutElement();
    RefPtr<LayoutWrapper> textWrapper = textWrapperNode;
    buttonAlgorithm->text_.Init(secCompProperty, textWrapper);
    buttonAlgorithm->text_.width_ = 4.0; // set width 4.0
    buttonAlgorithm->isVertical_ = true;

    // shrink 2.0px, icon not exist, total 2.0
    ASSERT_EQ(buttonAlgorithm->ShrinkWidth(2.0), 2.0);
    ASSERT_EQ(buttonAlgorithm->text_.width_, 2.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkWidth004
 * @tc.desc: Test security component ShrinkWidth, shrink icon when isVertical_
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkWidth004, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageGeometryNode = imageIcon->geometryNode_;
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    auto imageWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(imageIcon)), imageGeometryNode, imageLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateIconStyle(1);

    buttonAlgorithm->icon_ = IconLayoutElement();
    RefPtr<LayoutWrapper> iconWrapper = imageWrapperNode;
    buttonAlgorithm->icon_.Init(secCompProperty, iconWrapper);
    buttonAlgorithm->icon_.width_ = 16.0; // set width 4.0
    buttonAlgorithm->isVertical_ = true;

    EXPECT_EQ(buttonAlgorithm->ShrinkWidth(2.0), 14.0);
    EXPECT_EQ(buttonAlgorithm->icon_.width_, 14.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkWidth005
 * @tc.desc: Test security component ShrinkWidth, shrink icon when not isVertical_
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkWidth005, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageGeometryNode = imageIcon->geometryNode_;
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    auto imageWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(imageIcon)), imageGeometryNode, imageLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateIconStyle(1);

    buttonAlgorithm->icon_ = IconLayoutElement();
    RefPtr<LayoutWrapper> iconWrapper = imageWrapperNode;
    buttonAlgorithm->icon_.Init(secCompProperty, iconWrapper);
    buttonAlgorithm->icon_.width_ = 16.0; // set width 4.0
    buttonAlgorithm->isVertical_ = false;
    buttonAlgorithm->text_.isSetSize_ = true;
    buttonAlgorithm->text_.width_ = 16.0; // set text 16.0
    // shrink 2.0px, icon will shrink only
    EXPECT_EQ(buttonAlgorithm->ShrinkWidth(2.0), 30);
    EXPECT_EQ(buttonAlgorithm->icon_.width_, 14.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmEnlargeWidth001
 * @tc.desc: Test security component EnlargeWidth
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmEnlargeWidth001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->middle_.isVertical_ = false;

    buttonAlgorithm->left_ = PaddingLayoutElement();
    buttonAlgorithm->left_.Init(false, true, 4.0, 0.0);
    buttonAlgorithm->right_ = PaddingLayoutElement();
    buttonAlgorithm->right_.Init(false, true, 4.0, 0.0);
    buttonAlgorithm->isVertical_ = true;
    EXPECT_EQ(buttonAlgorithm->EnlargeWidth(2.0), 8.0);

    buttonAlgorithm->left_.isSetSize_ = false;
    buttonAlgorithm->isVertical_ = false;
    EXPECT_EQ(buttonAlgorithm->EnlargeWidth(2.0), 10.0);
    EXPECT_EQ(buttonAlgorithm->middle_.width_, 0.0);

    buttonAlgorithm->left_.isSetSize_ = false;
    buttonAlgorithm->isVertical_ = true;
    EXPECT_EQ(buttonAlgorithm->EnlargeWidth(2.0), 12.0);
    EXPECT_EQ(buttonAlgorithm->middle_.width_, 0.0);

    buttonAlgorithm->left_.isSetSize_ = true;
    buttonAlgorithm->isVertical_ = false;
    EXPECT_EQ(buttonAlgorithm->EnlargeWidth(2.0), 14.0);
    EXPECT_EQ(buttonAlgorithm->middle_.width_, 2.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkHeight001
 * @tc.desc: Test security component ShrinkHeight, shrink top and bottom padding
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkHeight001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->top_ = PaddingLayoutElement();
    buttonAlgorithm->top_.Init(true, false, 4.0, 0.0); // top padding 4.0, minsize 0.0
    buttonAlgorithm->bottom_ = PaddingLayoutElement();
    buttonAlgorithm->bottom_.Init(true, false, 4.0, 0.0); // bottom padding 4.0, minsize 0.0
    // shrink 2.0px, left to 3.0, right to 3.0, total 6.0
    ASSERT_EQ(buttonAlgorithm->ShrinkHeight(2.0), 6.0);
    ASSERT_EQ(buttonAlgorithm->top_.height_, 3.0);
    ASSERT_EQ(buttonAlgorithm->bottom_.height_, 3.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkHeight002
 * @tc.desc: Test security component ShrinkWidth, shrink middle padding
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkHeight002, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->isVertical_ = true;
    buttonAlgorithm->top_ = PaddingLayoutElement();
    buttonAlgorithm->top_.Init(true, false, 4.0, 4.0); // left padding 4.0, minsize 4.0
    buttonAlgorithm->bottom_ = PaddingLayoutElement();
    buttonAlgorithm->bottom_.Init(true, false, 4.0, 4.0); // right_ padding 4.0, minsize 4.0
    buttonAlgorithm->middle_ = PaddingLayoutElement();
    buttonAlgorithm->middle_.Init(true, false, 4.0, 0.0); // middle_ padding 4.0, minsize 0.0
    // shrink 2.0px, left to 3.0, right to 3.0, total 6.0
    ASSERT_EQ(buttonAlgorithm->ShrinkHeight(2.0), 10.0);
    ASSERT_EQ(buttonAlgorithm->middle_.height_, 2.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkHeight003
 * @tc.desc: Test security component ShrinkWidth, shrink icon when isVertical_
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkHeight003, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageGeometryNode = imageIcon->geometryNode_;
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    auto imageWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(imageIcon)), imageGeometryNode, imageLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateIconStyle(1);

    buttonAlgorithm->icon_ = IconLayoutElement();
    RefPtr<LayoutWrapper> iconWrapper = imageWrapperNode;
    buttonAlgorithm->icon_.Init(secCompProperty, iconWrapper);
    buttonAlgorithm->icon_.height_ = 15.0; // set width 4.0
    buttonAlgorithm->text_.isSetSize_ = true;
    buttonAlgorithm->text_.height_ = 20.0; // set width 20.0
    buttonAlgorithm->isVertical_ = false;

    EXPECT_EQ(buttonAlgorithm->ShrinkHeight(4.0), 20.0); // text can not shrink
    EXPECT_EQ(buttonAlgorithm->icon_.height_, 15.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmShrinkHeight004
 * @tc.desc: Test security component ShrinkWidth, shrink icon when not isVertical_
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmShrinkHeight004, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    auto imageIcon = FrameNode::CreateFrameNode(
        V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ImagePattern>());
    auto imageGeometryNode = imageIcon->geometryNode_;
    auto imageLayoutProperty = imageIcon->GetLayoutProperty<ImageLayoutProperty>();
    auto imageWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(imageIcon)), imageGeometryNode, imageLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateIconStyle(1);

    buttonAlgorithm->isVertical_ = true;
    buttonAlgorithm->icon_ = IconLayoutElement();
    RefPtr<LayoutWrapper> iconWrapper = imageWrapperNode;
    buttonAlgorithm->icon_.Init(secCompProperty, iconWrapper);
    buttonAlgorithm->icon_.height_ = 16.0; // set width 4.0
    buttonAlgorithm->isVertical_ = true;
    buttonAlgorithm->text_.isSetSize_ = true;
    buttonAlgorithm->text_.height_ = 16.0; // set text 16.0
    // shrink 2.0px, icon will shrink only
    EXPECT_EQ(buttonAlgorithm->ShrinkHeight(2.0), 30.0);
    EXPECT_EQ(buttonAlgorithm->icon_.height_, 14.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmEnlargeHeight001
 * @tc.desc: Test security component EnlargeHeight
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmEnlargeHeight001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    buttonAlgorithm->middle_.isVertical_ = true;

    buttonAlgorithm->top_ = PaddingLayoutElement();
    buttonAlgorithm->top_.Init(true, true, 4.0, 0.0);
    buttonAlgorithm->bottom_ = PaddingLayoutElement();
    buttonAlgorithm->bottom_.Init(true, true, 4.0, 0.0);
    buttonAlgorithm->isVertical_ = false;
    EXPECT_EQ(buttonAlgorithm->EnlargeHeight(2.0), 8.0);

    buttonAlgorithm->top_.isSetSize_ = false;
    buttonAlgorithm->isVertical_ = true;
    EXPECT_EQ(buttonAlgorithm->EnlargeHeight(2.0), 10.0);
    EXPECT_EQ(buttonAlgorithm->middle_.height_, 0.0);

    buttonAlgorithm->top_.isSetSize_ = false;
    buttonAlgorithm->isVertical_ = false;
    EXPECT_EQ(buttonAlgorithm->EnlargeHeight(2.0), 12.0);
    EXPECT_EQ(buttonAlgorithm->middle_.height_, 0.0);

    buttonAlgorithm->top_.isSetSize_ = true;
    buttonAlgorithm->isVertical_ = true;
    EXPECT_EQ(buttonAlgorithm->EnlargeHeight(2.0), 14.0);
    EXPECT_EQ(buttonAlgorithm->middle_.height_, 2.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmAdapterWidth001
 * @tc.desc: Test security component AdaptWidth
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmAdapterWidth001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);

    buttonAlgorithm->idealWidth_ = 0.0;
    buttonAlgorithm->top_ = PaddingLayoutElement();
    buttonAlgorithm->top_.Init(true, false, 4.0, 0.0);
    buttonAlgorithm->left_ = PaddingLayoutElement();
    buttonAlgorithm->left_.Init(false, false, 4.0, 0.0);
    buttonAlgorithm->componentWidth_ = 4.0;
    buttonAlgorithm->maxWidth_ = 2.0;
    buttonAlgorithm->AdaptWidth();
    EXPECT_EQ(buttonAlgorithm->componentWidth_, 2.0);

    buttonAlgorithm->maxWidth_ = 20.0;
    buttonAlgorithm->minWidth_ = 10.0;
    buttonAlgorithm->AdaptWidth();
    EXPECT_EQ(buttonAlgorithm->componentWidth_, 10.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmAdaptHeight001
 * @tc.desc: Test security component AdaptHeight
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmAdaptHeight001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);

    buttonAlgorithm->idealWidth_ = 0.0;
    buttonAlgorithm->top_ = PaddingLayoutElement();
    buttonAlgorithm->top_.Init(true, false, 4.0, 0.0);
    buttonAlgorithm->left_ = PaddingLayoutElement();
    buttonAlgorithm->left_.Init(false, false, 4.0, 0.0);
    buttonAlgorithm->componentHeight_ = 4.0;
    buttonAlgorithm->maxHeight_ = 2.0;
    buttonAlgorithm->AdaptHeight();
    EXPECT_EQ(buttonAlgorithm->componentHeight_, 2.0);

    buttonAlgorithm->maxHeight_ = 20.0;
    buttonAlgorithm->minHeight_ = 10.0;
    buttonAlgorithm->AdaptHeight();
    EXPECT_EQ(buttonAlgorithm->componentHeight_, 10.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmUpdateVerticalOffset001
 * @tc.desc: Test security component UpdateVerticalOffset
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmUpdateVerticalOffset001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);

    OffsetF offsetIcon(0.0, 0.0);
    OffsetF offsetText(0.0, 0.0);
    SizeF childSize(0.0, 0.0);
    buttonAlgorithm->icon_.height_ = 2.0;
    buttonAlgorithm->middle_.height_ = 2.0;
    buttonAlgorithm->icon_.width_ = 2.0;
    buttonAlgorithm->text_.width_ = 1.0;
    buttonAlgorithm->UpdateVerticalOffset(offsetIcon, offsetText, childSize);
    EXPECT_EQ(offsetText.GetX(), 0.5); // (icon_.width_ - text_.width_) / 2
    EXPECT_EQ(offsetText.GetY(), 4.0); // icon_.height_ + middle_.height_

    OffsetF offsetIcon1(0.0, 0.0);
    OffsetF offsetText1(0.0, 0.0);
    buttonAlgorithm->text_.width_ = 3.0;
    buttonAlgorithm->UpdateVerticalOffset(offsetIcon1, offsetText1, childSize);
    EXPECT_EQ(offsetText1.GetX(), 0);
    EXPECT_EQ(offsetText1.GetY(), 4.0); // icon_.height_ + middle_.height_
    EXPECT_EQ(offsetIcon1.GetX(), 0.5); // (text_.width_ - icon_.width_) / 2
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmUpdateHorizontalOffset001
 * @tc.desc: Test security component UpdateHorizontalOffset
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmUpdateHorizontalOffset001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        0, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapperNode = CreateLayoutWrapper(frameNode);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));

    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);

    OffsetF offsetIcon(0.0, 0.0);
    OffsetF offsetText(0.0, 0.0);
    SizeF childSize(0.0, 0.0);
    buttonAlgorithm->icon_.width_ = 2.0;
    buttonAlgorithm->middle_.width_ = 2.0;
    buttonAlgorithm->icon_.height_ = 2.0;
    buttonAlgorithm->text_.height_ = 1.0;
    buttonAlgorithm->UpdateHorizontalOffset(layoutWrapper, offsetIcon, offsetText, childSize);
    EXPECT_EQ(offsetText.GetX(), 4.0); // icon_.width_ + middle_.width_
    EXPECT_EQ(offsetText.GetY(), 0.5); // (icon_.height_ - text_.height_) / 2

    OffsetF offsetIcon1(0.0, 0.0);
    OffsetF offsetText1(0.0, 0.0);
    buttonAlgorithm->text_.height_ = 3.0;
    buttonAlgorithm->UpdateHorizontalOffset(layoutWrapper, offsetIcon1, offsetText1, childSize);
    EXPECT_EQ(offsetText1.GetX(), 4.0); // icon_.height_ + middle_.height_
    EXPECT_EQ(offsetText1.GetY(), 0);
    EXPECT_EQ(offsetIcon1.GetY(), 0.5); // (text_.width_ - icon_.width_) / 2
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmGetTextDirection001
 * @tc.desc: Test security component GetTextDirectio
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmGetTextDirection001, TestSize.Level1)
{
    RefPtr<FrameNode> frameNode = CreateSecurityComponent(0, 0,
        0, V2::LOCATION_BUTTON_ETS_TAG);
    ASSERT_NE(frameNode, nullptr);
    auto textNode = GetSecCompChildNode(frameNode, V2::TEXT_ETS_TAG);
    ASSERT_NE(textNode, nullptr);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    auto layoutWrapperNode = CreateLayoutWrapper(frameNode);
    auto layoutWrapper = reinterpret_cast<LayoutWrapper*>(Referenced::RawPtr(layoutWrapperNode));

    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    
    textLayoutProperty->UpdateContent(u"test");
    EXPECT_EQ(buttonAlgorithm->GetTextDirection(layoutWrapper), TextDirection::LTR);

    textLayoutProperty->UpdateContent(u"تۇرۇشلۇق ئورۇن"); // this text is read from RTL
    EXPECT_EQ(buttonAlgorithm->GetTextDirection(layoutWrapper), TextDirection::RTL);

    textLayoutProperty->UpdateContent(u""); // this text empty, should ret default LTR
    EXPECT_EQ(buttonAlgorithm->GetTextDirection(layoutWrapper), TextDirection::LTR);
}

/**
 * @tc.name: LayoutAlgorithmUpdateCircleButtonConstraint001
 * @tc.desc: Test security component UpdateCircleButtonConstraint
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, LayoutAlgorithmUpdateCircleButtonConstraint001, TestSize.Level1)
{
    SecurityComponentLayoutAlgorithm buttonAlgorithm;
    buttonAlgorithm.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm.idealWidth_, 0.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm1;
    buttonAlgorithm1.idealWidth_ = 1.0;
    buttonAlgorithm1.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm1.idealWidth_, 1.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm2;
    buttonAlgorithm2.idealHeight_ = 2.0;
    buttonAlgorithm2.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm2.idealWidth_, 2.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm3;
    buttonAlgorithm3.componentWidth_ = 1.0;
    buttonAlgorithm3.minWidth_ = 2.0;
    buttonAlgorithm3.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm3.idealWidth_, 2.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm4;
    buttonAlgorithm4.componentHeight_ = 2.0;
    buttonAlgorithm4.minHeight_ = 3.0;
    buttonAlgorithm4.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm4.idealWidth_, 3.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm5;
    buttonAlgorithm5.componentWidth_ = 10.0;
    buttonAlgorithm5.maxWidth_ = 4.0;
    buttonAlgorithm5.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm5.idealWidth_, 4.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm6;
    buttonAlgorithm6.componentHeight_ = 10.0;
    buttonAlgorithm6.maxHeight_ = 4.0;
    buttonAlgorithm6.UpdateCircleButtonConstraint();
    EXPECT_EQ(buttonAlgorithm6.idealWidth_, 4.0);
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmFillBlank001
 * @tc.desc: Test security component FillBlank
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmFillBlank001, TestSize.Level1)
{
    SecurityComponentLayoutAlgorithm buttonAlgorithm;
    buttonAlgorithm.isNobg_ = true;
    buttonAlgorithm.FillBlank();
    EXPECT_EQ(buttonAlgorithm.componentWidth_, 0.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm1;
    buttonAlgorithm1.idealWidth_ = 2.0;
    buttonAlgorithm1.componentWidth_ = 0.0;
    buttonAlgorithm1.idealHeight_ = 2.0;
    buttonAlgorithm1.componentHeight_ = 0.0;
    buttonAlgorithm1.FillBlank();
    EXPECT_EQ(buttonAlgorithm1.left_.width_, 1.0);
    EXPECT_EQ(buttonAlgorithm1.right_.width_, 1.0);
    EXPECT_EQ(buttonAlgorithm1.top_.height_, 1.0);
    EXPECT_EQ(buttonAlgorithm1.bottom_.height_, 1.0);

    SecurityComponentLayoutAlgorithm buttonAlgorithm2;
    buttonAlgorithm2.minWidth_ = 2.0;
    buttonAlgorithm2.componentWidth_ = 0.0;
    buttonAlgorithm2.minHeight_ = 2.0;
    buttonAlgorithm2.componentHeight_ = 0.0;
    buttonAlgorithm2.FillBlank();
    EXPECT_EQ(buttonAlgorithm2.left_.width_, 1.0);
    EXPECT_EQ(buttonAlgorithm2.right_.width_, 1.0);
    EXPECT_EQ(buttonAlgorithm2.top_.height_, 1.0);
    EXPECT_EQ(buttonAlgorithm2.bottom_.height_, 1.0);
}

void SecurityComponentModelTestNg::InitLayoutAlgorithm(RefPtr<SecurityComponentLayoutAlgorithm>& buttonAlgorithm)
{
    auto textNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    auto textGeometryNode = textNode->geometryNode_;
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    textLayoutProperty->UpdateContent(u"Security component");
    textLayoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE));
    auto textWrapperNode = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(textNode)), textGeometryNode, textLayoutProperty);
    auto secCompProperty = AceType::MakeRefPtr<SecurityComponentLayoutProperty>();
    secCompProperty->UpdateSecurityComponentDescription(1);

    buttonAlgorithm->text_ = TextLayoutElement();
    RefPtr<LayoutWrapper> textWrapper = textWrapperNode;
    buttonAlgorithm->text_.Init(secCompProperty, textWrapper);
    buttonAlgorithm->text_.width_ = 4.0; // set width 4.0
    buttonAlgorithm->isVertical_ = true;
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCircle001
 * @tc.desc: Test security component IsTextOutOfRangeInCircle
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCircle001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    InitLayoutAlgorithm(buttonAlgorithm);

    buttonAlgorithm->componentWidth_ = 10.0;
    buttonAlgorithm->componentHeight_ = 10.0;
    buttonAlgorithm->currentFontSize_ = Dimension(2.0);
    buttonAlgorithm->textLeftTopPoint_ = SizeF(4, 4);
    buttonAlgorithm->textRightTopPoint_ = SizeF(6, 4);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(4, 6);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(6, 6);
    EXPECT_FALSE(buttonAlgorithm->IsTextOutOfRangeInCircle());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCircle());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCircle());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(8, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(10, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(8, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(10, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCircle());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(8, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(10, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(8, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(10, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCircle());
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCapsule001
 * @tc.desc: Test security component IsTextOutOfRangeInCapsule
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCapsule001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    InitLayoutAlgorithm(buttonAlgorithm);

    buttonAlgorithm->componentWidth_ = 15.0;
    buttonAlgorithm->componentHeight_ = 10.0;
    buttonAlgorithm->currentFontSize_ = Dimension(2.0);
    buttonAlgorithm->textLeftTopPoint_ = SizeF(4, 4);
    buttonAlgorithm->textRightTopPoint_ = SizeF(6, 4);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(4, 6);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(6, 6);
    EXPECT_FALSE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(13, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(15, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(13, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(15, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(13, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(15, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(13, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(15, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCapsule002
 * @tc.desc: Test security component IsTextOutOfRangeInCapsule
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmIsTextOutOfRangeInCapsule002, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    InitLayoutAlgorithm(buttonAlgorithm);

    buttonAlgorithm->componentWidth_ = 10.0;
    buttonAlgorithm->componentHeight_ = 15.0;
    buttonAlgorithm->currentFontSize_ = Dimension(2.0);
    buttonAlgorithm->textLeftTopPoint_ = SizeF(4, 4);
    buttonAlgorithm->textRightTopPoint_ = SizeF(6, 4);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(4, 6);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(6, 6);
    EXPECT_FALSE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 13);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 13);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 15);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 15);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(8, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(10, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(8, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(10, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(8, 13);
    buttonAlgorithm->textRightTopPoint_ = SizeF(10, 13);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(8, 15);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(10, 15);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInCapsule());
}

/**
 * @tc.name: SecurityComponentLayoutAlgorithmIsTextOutOfRangeInNormal001
 * @tc.desc: Test security component IsTextOutOfRangeInNormal
 * @tc.type: FUNC
 * @tc.author:
 */
HWTEST_F(SecurityComponentModelTestNg, SecurityComponentLayoutAlgorithmIsTextOutOfRangeInNormal001, TestSize.Level1)
{
    auto buttonAlgorithm = AceType::MakeRefPtr<SecurityComponentLayoutAlgorithm>();
    ASSERT_NE(buttonAlgorithm, nullptr);
    InitLayoutAlgorithm(buttonAlgorithm);
    auto buttonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<ButtonPattern>());
    buttonNode->SetInternal();
    buttonAlgorithm->buttonLayoutProperty_ = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonAlgorithm->buttonLayoutProperty_);
    buttonAlgorithm->buttonLayoutProperty_->UpdateBorderRadius(BorderRadiusProperty(Dimension(5.0)));

    buttonAlgorithm->componentWidth_ = 15.0;
    buttonAlgorithm->componentHeight_ = 10.0;
    buttonAlgorithm->currentFontSize_ = Dimension(2.0);
    buttonAlgorithm->textLeftTopPoint_ = SizeF(4, 4);
    buttonAlgorithm->textRightTopPoint_ = SizeF(6, 4);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(4, 6);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(6, 6);
    EXPECT_FALSE(buttonAlgorithm->IsTextOutOfRangeInNormal());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInNormal());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(0, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(2, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(0, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(2, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInNormal());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(13, 0);
    buttonAlgorithm->textRightTopPoint_ = SizeF(15, 0);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(13, 2);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(15, 2);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInNormal());
    buttonAlgorithm->textLeftTopPoint_ = SizeF(13, 8);
    buttonAlgorithm->textRightTopPoint_ = SizeF(15, 8);
    buttonAlgorithm->textLeftBottomPoint_ = SizeF(13, 10);
    buttonAlgorithm->textRightBottomPoint_ = SizeF(15, 10);
    EXPECT_TRUE(buttonAlgorithm->IsTextOutOfRangeInNormal());
}
} // namespace OHOS::Ace::NG
