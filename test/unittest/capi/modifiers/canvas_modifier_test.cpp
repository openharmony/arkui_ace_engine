/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test/mock/core/pattern/mock_canvas_pattern.h"
#include "gmock/gmock.h"
#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"

#include "core/interfaces/native/implementation/canvas_rendering_context2d_peer_impl.h"
#include "core/interfaces/native/implementation/drawing_rendering_context_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/canvas/canvas_event_hub.h"
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/components_ng/pattern/canvas/canvas_rendering_context_2d_model_ng.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
// Attribute names
const auto ATTRIBUTE_CANVAS_NAME = "canvas";
const auto ATTRIBUTE_ENABLE_ANALYZER_NAME = "enableAnalyzer";

// Default values
const auto ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE = false;

// Test plans
typedef std::pair<Ark_Boolean, bool> BoolTest;
const std::vector<BoolTest> BOOL_TEST_PLAN = {
    { false, false },
    { true, true },
    { 0, false },
    { -25, true },
    { 25, true },
};
class MockCanvasRenderingContext2DModel : public NG::CanvasRenderingContext2DModelNG {
public:
    MockCanvasRenderingContext2DModel() = default;
    ~MockCanvasRenderingContext2DModel() override = default;

    MOCK_METHOD(void, SetShadowColor, (const Ace::Color&), (override));
    MOCK_METHOD(void, SetPattern, (RefPtr<AceType>), (override));
};
class StubCanvasRenderingContext2DPeerImpl : public CanvasRenderingContext2DPeer {
public:
    StubCanvasRenderingContext2DPeerImpl() = default;
    ~StubCanvasRenderingContext2DPeerImpl() override = default;

    int32_t GetInstanceId()
    {
        return instanceId_;
    }
};
class StubDrawingRenderingContextPeerImpl : public GeneratedModifier::DrawingRenderingContextPeerImpl {
public:
    StubDrawingRenderingContextPeerImpl() = default;
    ~StubDrawingRenderingContextPeerImpl() override = default;

    int32_t GetInstanceId()
    {
        return instanceId_;
    }
    RefPtr<AceType> GetCanvasPattern()
    {
        return canvasPattern_;
    }
};
} // namespace
class CanvasModifierTest : public ModifierTestBase<GENERATED_ArkUICanvasModifier,
    &GENERATED_ArkUINodeModifiers::getCanvasModifier, GENERATED_ARKUI_CANVAS> {
    public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
    }
};

/*
 * @tc.name: setOnReadyTest
 * @tc.desc: Check the functionality of CanvasModifier.OnReadyImpl
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setOnReadyTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setOnReady, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<CanvasEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    const int32_t contextId = 123;
    void (*checkCallback)(const Ark_Int32) = [](const Ark_Int32 resourceId) {
            checkEvent = {
                .nodeId = resourceId,
            };
        };
    auto func = Converter::ArkValue<VoidCallback>(checkCallback, contextId);

    EXPECT_FALSE(checkEvent.has_value());
    modifier_->setOnReady(node_, &func);
    eventHub->FireReadyEvent();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, contextId);
}

/*
 * @tc.name: setEnableAnalyzerTestValidValues
 * @tc.desc: Check the functionality of CanvasModifier.EnableAnalyzerImpl
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setEnableAnalyzerTestValidValues, TestSize.Level1)
{
    auto fullJson = GetJsonValue(node_);
    auto canvasObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CANVAS_NAME);
    auto initialValue = GetAttrValue<bool>(canvasObject, ATTRIBUTE_ENABLE_ANALYZER_NAME);

    EXPECT_EQ(initialValue, ATTRIBUTE_ENABLE_ANALYZER_DEFAULT_VALUE);

    for (auto testValue : BOOL_TEST_PLAN) {
        Ark_Boolean inputValue = Converter::ArkValue<Ark_Boolean>(testValue.first);
        modifier_->setEnableAnalyzer(node_, inputValue);

        auto fullJson = GetJsonValue(node_);
        auto canvasObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, ATTRIBUTE_CANVAS_NAME);
        auto checkValue = GetAttrValue<bool>(canvasObject, ATTRIBUTE_ENABLE_ANALYZER_NAME);
        EXPECT_EQ(checkValue, testValue.second);
    }
}

/*
 * @tc.name: setCanvasOptions0RenderingContext2DTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setCanvasOptions0RenderingContext2DTest, TestSize.Level1)
{
    ASSERT_NE(modifier_->setCanvasOptions0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto renderingModel_ = AceType::MakeRefPtr<NiceMock<MockCanvasRenderingContext2DModel>>();
    auto peerImpl = Referenced::MakeRefPtr<StubCanvasRenderingContext2DPeerImpl>();
    peerImpl->SetRenderingContext2DModel(renderingModel_);
    Ark_CanvasRenderingContext2D arkContext2D =
        reinterpret_cast<CanvasRenderingContext2DPeer*>(Referenced::RawPtr(peerImpl));
    auto options =
        Converter::ArkUnion<Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext, Ark_CanvasRenderingContext2D>(
            arkContext2D);
    auto expectedId = Container::CurrentId();
    auto expectedPattern = CanvasModelNG::GetCanvasPattern(frameNode);
    EXPECT_CALL(*renderingModel_, SetPattern(_)).WillOnce([expectedPattern](RefPtr<AceType> pattern) {
        EXPECT_EQ(Referenced::RawPtr(pattern), Referenced::RawPtr(expectedPattern));
    });
    EXPECT_CALL(*renderingModel_, SetShadowColor(Color::TRANSPARENT)).Times(1);
    modifier_->setCanvasOptions0(node_, &options);

    EXPECT_EQ(peerImpl->GetInstanceId(), expectedId);
}

/*
 * @tc.name: setCanvasOptions0DrawingRenderingContextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setCanvasOptions0DrawingRenderingContextTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    ASSERT_NE(modifier_->setCanvasOptions0, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto peerImpl = Referenced::MakeRefPtr<StubDrawingRenderingContextPeerImpl>();
    Ark_DrawingRenderingContext arkDrawingContext =
        reinterpret_cast<DrawingRenderingContextPeer*>(Referenced::RawPtr(peerImpl));
    auto options =
        Converter::ArkUnion<Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext, Ark_DrawingRenderingContext>(
            arkDrawingContext);
    auto expectedId = Container::CurrentId();
    auto expectedPattern = CanvasModelNG::GetCanvasPattern(frameNode);
    modifier_->setCanvasOptions0(node_, &options);

    RefPtr<AceType> pattern = peerImpl->GetCanvasPattern();
    EXPECT_EQ(Referenced::RawPtr(pattern), Referenced::RawPtr(expectedPattern));
    EXPECT_EQ(peerImpl->GetInstanceId(), expectedId);
}

/*
 * @tc.name: setCanvasOptions0EmptyContextTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CanvasModifierTest, setCanvasOptions0EmptyContextTest, TestSize.Level1)
{
    auto holder = TestHolder::GetInstance();
    holder->SetUp();
    auto options = Converter::ArkValue<Opt_Union_CanvasRenderingContext2D_DrawingRenderingContext>(Ark_Empty());
    modifier_->setCanvasOptions0(node_, &options);
    EXPECT_TRUE(holder->isCalled);
    holder->SetUp();
    modifier_->setCanvasOptions0(node_, nullptr);
    EXPECT_TRUE(holder->isCalled);
}
} // namespace OHOS::Ace::NG
