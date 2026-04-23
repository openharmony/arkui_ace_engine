/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "modifier_test_base.h"

#include "core/components_ng/pattern/shape/shape_paint_property.h"
#include "core/interfaces/native/node/common_shape_modifier.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class CommonShapeMethodModifierHdrPayloadTest
    : public ModifierTestBase<GENERATED_ArkUICommonShapeMethodModifier,
          &GENERATED_ArkUINodeModifiers::getCommonShapeMethodModifier,
          GENERATED_ARKUI_CIRCLE> {
public:
    void* CreateNodeImpl() override
    {
        return nodeModifiers_->getCircleModifier()->construct(GetId(), 0);
    }
};

/**
 * @tc.name: CommonShapeModifierPayloadFill001
 * @tc.desc: BT2020 payload should be accepted even if packed color value mismatches input value.
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierHdrPayloadTest, CommonShapeModifierPayloadFill001, TestSize.Level0)
{
    auto* commonShapeModifier = NodeModifier::GetCommonShapeModifier();
    ASSERT_NE(commonShapeModifier, nullptr);
    ASSERT_NE(commonShapeModifier->setFill, nullptr);

    Color payloadColor(0xFF123456);
    payloadColor.SetColorSpace(ColorSpace::BT2020);
    auto payload = AceType::MakeRefPtr<NodeModifier::ShapeColorModifierPayload>(payloadColor, nullptr);

    constexpr uint32_t inputColorValue = 0xFFABCDEF;
    commonShapeModifier->setFill(node_, inputColorValue, static_cast<void*>(AceType::RawPtr(payload)));

    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto shapePaintProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapePaintProperty, nullptr);
    ASSERT_TRUE(shapePaintProperty->HasFill());
    auto fillColor = shapePaintProperty->GetFillValue();
    EXPECT_EQ(fillColor.GetValue(), payloadColor.GetValue());
    EXPECT_EQ(fillColor.GetColorSpace(), ColorSpace::BT2020);
}

/**
 * @tc.name: CommonShapeModifierPayloadStroke001
 * @tc.desc: HDR payload should be accepted and preserve headroom metadata.
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierHdrPayloadTest, CommonShapeModifierPayloadStroke001, TestSize.Level0)
{
    auto* commonShapeModifier = NodeModifier::GetCommonShapeModifier();
    ASSERT_NE(commonShapeModifier, nullptr);
    ASSERT_NE(commonShapeModifier->setStroke, nullptr);

    Color payloadColor = Color::FromFloat(0.7f, 0.2f, 0.1f, 1.0f, 2.5f);
    auto payload = AceType::MakeRefPtr<NodeModifier::ShapeColorModifierPayload>(payloadColor, nullptr);

    constexpr uint32_t inputColorValue = 0xFF0A0B0C;
    commonShapeModifier->setStroke(node_, inputColorValue, static_cast<void*>(AceType::RawPtr(payload)));

    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto shapePaintProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapePaintProperty, nullptr);
    ASSERT_TRUE(shapePaintProperty->HasStroke());
    auto strokeColor = shapePaintProperty->GetStrokeValue();
    auto headRoom = strokeColor.GetHeadRoomColor();
    ASSERT_TRUE(headRoom.has_value());
    EXPECT_FLOAT_EQ(headRoom->headRoom, 2.5f);
}

/**
 * @tc.name: CommonShapeModifierPayloadFill002
 * @tc.desc: Non-HDR and non-BT2020 payload with mismatched value should be ignored.
 * @tc.type: FUNC
 */
HWTEST_F(CommonShapeMethodModifierHdrPayloadTest, CommonShapeModifierPayloadFill002, TestSize.Level0)
{
    auto* commonShapeModifier = NodeModifier::GetCommonShapeModifier();
    ASSERT_NE(commonShapeModifier, nullptr);
    ASSERT_NE(commonShapeModifier->setFill, nullptr);

    Color payloadColor = Color::RED;
    auto payload = AceType::MakeRefPtr<NodeModifier::ShapeColorModifierPayload>(payloadColor, nullptr);

    constexpr uint32_t inputColorValue = 0xFF00FF00;
    commonShapeModifier->setFill(node_, inputColorValue, static_cast<void*>(AceType::RawPtr(payload)));

    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto shapePaintProperty = frameNode->GetPaintProperty<ShapePaintProperty>();
    ASSERT_NE(shapePaintProperty, nullptr);
    ASSERT_TRUE(shapePaintProperty->HasFill());
    EXPECT_EQ(shapePaintProperty->GetFillValue().GetValue(), inputColorValue);
}
} // namespace OHOS::Ace::NG
