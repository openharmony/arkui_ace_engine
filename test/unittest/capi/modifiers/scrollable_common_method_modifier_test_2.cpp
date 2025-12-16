/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/unittest/capi/modifiers/generated/test_fixtures.h"
#include "test/unittest/capi/modifiers/generated/type_helpers.h"

#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/interfaces/native/implementation/rect_shape_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;
using namespace Converter;
using namespace TypeHelper;
namespace {
const auto ATTRIBUTE_CLIP_CONTENT_NAME = "clipContent";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_NAME = "clipContentRect";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_WIDTH_NAME = "width";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_HEIGHT_NAME = "height";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_TOP_LEFT_RADIUS_NAME = "topLeftRadius";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_TOP_RIGHT_RADIUS_NAME = "topRightRadius";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_BOTTOM_RIGHT_RADIUS_NAME = "bottomRightRadius";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_BOTTOM_LEFT_RADIUS_NAME = "bottomLeftRadius";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_OFFSET_NAME = "offset";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_POSITION_NAME = "position";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_COLOR_NAME = "color";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_STROKE_COLOR_NAME = "strokeColor";
const auto ATTRIBUTE_CLIP_CONTENT_RECT_STROKE_WIDTH_NAME = "strokeWidth";
const auto ATTRIBUTE_DIMENSION_OFFSET_X = "x";
const auto ATTRIBUTE_DIMENSION_OFFSET_Y = "y";
const auto ATTRIBUTE_DIMENSION_OFFSET_Z = "z";
const auto ATTRIBUTE_CLIP_CONTENT_DEFAULT_BOUNDARY_VALUE = "ContentClipMode.BOUNDARY";
const auto ATTRIBUTE_CLIP_CONTENT_DEFAULT_ONLY_VALUE = "ContentClipMode.CONTENT_ONLY";
const auto ATTRIBUTE_CLIP_CONTENT_CUSTOM_VALUE = "RectShape";
const auto GRID_MODIFIER_INDEX = 0;
const auto SCROLL_MODIFIER_INDEX = 2;
} // namespace

class ScrollableCommonMethodModifierTest2
    : public ModifierTestBase<GENERATED_ArkUIScrollableCommonMethodModifier,
          &GENERATED_ArkUINodeModifiers::getScrollableCommonMethodModifier, GENERATED_ARKUI_SCROLLABLE_COMMON_METHOD>,
      public testing::WithParamInterface<int> {
public:
    void* CreateNodeImpl() override
    {
        typedef void* (*ConstructFunc)(Ark_Int32, Ark_Int32);
        const ConstructFunc constructors[] = {
            nodeModifiers_->getGridModifier()->construct,
            nodeModifiers_->getListModifier()->construct,
            nodeModifiers_->getScrollModifier()->construct,
            nodeModifiers_->getWaterFlowModifier()->construct,
        };
        if (GetParam() < std::size(constructors)) {
            return constructors[GetParam()](GetId(), 0);
        }
        return nullptr;
    }

    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ScrollBarTheme>();
        SetupTheme<ScrollableTheme>();

        for (auto& [id, strid, res] : Fixtures::resourceInitTable) {
            AddResource(id, res);
            AddResource(strid, res);
        }
    }

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone();
    }

    std::string GetDefaultClipContentValue()
    {
        if (GetParam() == GRID_MODIFIER_INDEX || GetParam() == SCROLL_MODIFIER_INDEX) {
            return ATTRIBUTE_CLIP_CONTENT_DEFAULT_BOUNDARY_VALUE;
        } else {
            return ATTRIBUTE_CLIP_CONTENT_DEFAULT_ONLY_VALUE;
        }
    }

    void initRectShape(RefPtr<ShapeRect> shape)
    {
        shape->SetWidth(20.0_px);
        shape->SetHeight(30.0_px);
        shape->SetTopLeftRadius(Radius(11.0f));
        shape->SetTopRightRadius(Radius(12.0f));
        shape->SetBottomRightRadius(Radius(13.0f));
        shape->SetBottomLeftRadius(Radius(14.0f));
        auto offset = DimensionOffset(10.0_px, 20.0_px);
        offset.SetZ(30.0_px);
        shape->SetOffset(offset);
        auto position = DimensionOffset(40.0_px, 50.0_px);
        position.SetZ(60.0_px);
        shape->SetPosition(position);
        shape->SetColor(Color(0xFF123456));
        shape->SetStrokeColor(0x12345678);
        shape->SetStrokeWidth(15.0f);
    }

    void CompareDimensionOffset(std::unique_ptr<JsonValue> value, const DimensionOffset& expected)
    {
        EXPECT_EQ(expected.GetX().ToString(), GetAttrValue<std::string>(value, ATTRIBUTE_DIMENSION_OFFSET_X));
        EXPECT_EQ(expected.GetY().ToString(), GetAttrValue<std::string>(value, ATTRIBUTE_DIMENSION_OFFSET_Y));
        auto optZ = expected.GetZ();
        if (optZ) {
            EXPECT_EQ(optZ->ToString(), GetAttrValue<std::string>(value, ATTRIBUTE_DIMENSION_OFFSET_Z));
        } else {
            EXPECT_EQ("", GetAttrValue<std::string>(value, ATTRIBUTE_DIMENSION_OFFSET_Z));
        }
    }
};

INSTANTIATE_TEST_SUITE_P(Tests, ScrollableCommonMethodModifierTest2, testing::Range(0, 4));

/*
 * @tc.name: setClipContentTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest2, setClipContentTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    std::string resultStr;

    resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLIP_CONTENT_NAME);
    EXPECT_EQ(resultStr, GetDefaultClipContentValue()) << "Default value for attribute 'clipContent'";
}

/*
 * @tc.name: setClipContentTestClipContentValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest2, setClipContentTestClipContentValidValues, TestSize.Level1)
{
    Opt_Union_ContentClipMode_RectShape initValueClipContent;

    // Initial setup
    WriteTo(initValueClipContent) = ArkUnion<Ark_Union_ContentClipMode_RectShape, Ark_ContentClipMode>(
        std::get<1>(Fixtures::testFixtureEnumContentClipModeValidValues[0]));

    auto checkValue = [this, &initValueClipContent](const std::string& input, const std::string& expectedStr,
                          const Ark_Union_ContentClipMode_RectShape& value) {
        Opt_Union_ContentClipMode_RectShape inputValueClipContent = initValueClipContent;

        WriteTo(inputValueClipContent) = value;
        modifier_->setClipContent(node_, &inputValueClipContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLIP_CONTENT_NAME);
        EXPECT_EQ(resultStr, expectedStr) <<
            "Input value is: " << input << ", method: setClipContent, attribute: clipContent";
    };

    for (auto& [input, value, expected] : Fixtures::testFixtureEnumContentClipModeValidValues) {
        checkValue(input, expected, ArkUnion<Ark_Union_ContentClipMode_RectShape, Ark_ContentClipMode>(value));
    }
}

/*
 * @tc.name: setClipContentTestClipContentInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest2, setClipContentTestClipContentInvalidValues, TestSize.Level1)
{
    Opt_Union_ContentClipMode_RectShape initValueClipContent;

    // Initial setup
    WriteTo(initValueClipContent) = ArkUnion<Ark_Union_ContentClipMode_RectShape, Ark_ContentClipMode>(
        std::get<1>(Fixtures::testFixtureEnumContentClipModeValidValues[0]));

    auto checkValue = [this, &initValueClipContent](
                          const std::string& input, const Ark_Union_ContentClipMode_RectShape& value) {
        Opt_Union_ContentClipMode_RectShape inputValueClipContent = initValueClipContent;

        modifier_->setClipContent(node_, &inputValueClipContent);
        WriteTo(inputValueClipContent) = value;
        modifier_->setClipContent(node_, &inputValueClipContent);
        auto jsonValue = GetJsonValue(node_);
        auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLIP_CONTENT_NAME);
        EXPECT_EQ(resultStr, GetDefaultClipContentValue()) <<
            "Input value is: " << input << ", method: setClipContent, attribute: clipContent";
    };

    for (auto& [input, value] : Fixtures::testFixtureEnumContentClipModeInvalidValues) {
        checkValue(input, ArkUnion<Ark_Union_ContentClipMode_RectShape, Ark_ContentClipMode>(value));
    }
    // Check invalid union
    checkValue("invalid union", ArkUnion<Ark_Union_ContentClipMode_RectShape, Ark_Empty>(nullptr));
}

/*
 * @tc.name: setClipContentTestRectShape
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest2, setClipContentTestRectShape, TestSize.Level1)
{
    Ark_RectShape peer = PeerUtils::CreatePeer<RectShapePeer>();
    RefPtr<ShapeRect> shape = Referenced::MakeRefPtr<ShapeRect>();
    initRectShape(shape);
    peer->rectShape = shape;
    auto clipContentUnion = ArkUnion<Opt_Union_ContentClipMode_RectShape, Ark_RectShape>(peer);
    modifier_->setClipContent(node_, &clipContentUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLIP_CONTENT_NAME);
    EXPECT_EQ(resultStr, ATTRIBUTE_CLIP_CONTENT_CUSTOM_VALUE);
    auto clipRectJSON = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_CLIP_CONTENT_RECT_NAME);
    EXPECT_EQ(
        shape->GetWidth().ToString(), GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_WIDTH_NAME));
    EXPECT_EQ(shape->GetHeight().ToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_HEIGHT_NAME));
    EXPECT_EQ(shape->GetTopLeftRadius().ToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_TOP_LEFT_RADIUS_NAME));
    EXPECT_EQ(shape->GetTopRightRadius().ToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_TOP_RIGHT_RADIUS_NAME));
    EXPECT_EQ(shape->GetBottomRightRadius().ToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_BOTTOM_RIGHT_RADIUS_NAME));
    EXPECT_EQ(shape->GetBottomLeftRadius().ToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_BOTTOM_LEFT_RADIUS_NAME));
    auto offsetJSON = GetAttrValue<std::unique_ptr<JsonValue>>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_OFFSET_NAME);
    CompareDimensionOffset(std::move(offsetJSON), shape->GetOffset());
    auto positionJSON =
        GetAttrValue<std::unique_ptr<JsonValue>>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_POSITION_NAME);
    CompareDimensionOffset(std::move(positionJSON), shape->GetPosition());
    EXPECT_EQ(shape->GetColor().ColorToString(),
        GetAttrValue<std::string>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_COLOR_NAME));
    EXPECT_EQ(static_cast<int32_t>(shape->GetStrokeColor()),
        GetAttrValue<int32_t>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_STROKE_COLOR_NAME));
    EXPECT_EQ(
        shape->GetStrokeWidth(), GetAttrValue<double>(clipRectJSON, ATTRIBUTE_CLIP_CONTENT_RECT_STROKE_WIDTH_NAME));
    PeerUtils::DestroyPeer(peer);
}

/*
 * @tc.name: setClipContentTestRectShapeNullptr
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_P(ScrollableCommonMethodModifierTest2, setClipContentTestRectShapeNullptr, TestSize.Level1)
{
    Ark_RectShape peer = PeerUtils::CreatePeer<RectShapePeer>();
    auto clipContentUnion = ArkUnion<Opt_Union_ContentClipMode_RectShape, Ark_RectShape>(peer);

    modifier_->setClipContent(node_, &clipContentUnion);
    auto jsonValue = GetJsonValue(node_);
    auto resultStr = GetAttrValue<std::string>(jsonValue, ATTRIBUTE_CLIP_CONTENT_NAME);
    EXPECT_EQ(resultStr, GetDefaultClipContentValue());
    PeerUtils::DestroyPeer(peer);
}
} // namespace OHOS::Ace::NG
