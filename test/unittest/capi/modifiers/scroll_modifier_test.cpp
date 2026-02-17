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

#include "gmock/gmock.h"
#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
inline void AssignArkValue(Ark_OnScrollFrameBeginHandlerResult& dst, const ScrollFrameResult& src,
    ConvContext *ctx)
{
    dst.offsetRemain = Converter::ArkValue<Ark_Float64>(src.offset);
}
} // Converter

namespace {
const float TEST_OFFSET = 10.0;

struct ScrollStateValue {
    Ark_Int32 nodeId;
    bool state;
};

std::optional<std::string> getStringScrollable(std::unique_ptr<JsonValue>& json, std::string key)
{
    for (auto object = json->GetChild(); object->IsValid(); object = object->GetNext()) {
        if (object->IsString() && object->GetKey() == key) {
            return object->GetString();
        }
    }
    return std::nullopt;
}

Opt_Union_Dimension_Array_Dimension createSnapSet(const Array_Dimension& arrayHolder)
{
    return Converter::ArkUnion<Opt_Union_Dimension_Array_Dimension, Array_Dimension>(arrayHolder);
}

Opt_Union_Dimension_Array_Dimension createEmptySnapSet()
{
    return Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(Ark_Empty());
}

} // namespace

class ScrollModifierTest : public ModifierTestBase<GENERATED_ArkUIScrollModifier,
                              &GENERATED_ArkUINodeModifiers::getScrollModifier, GENERATED_ARKUI_SCROLL> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<ScrollBarTheme>();
    }
};

/**
 * @tc.name: setScrollableTestSetBadDirectionOnSlide
 * @tc.desc: Test ScrollableImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollableTestSetBadDirectionOnSlide, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollable";
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto beforeState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(beforeState);

    auto direction = Converter::ArkValue<Opt_ScrollDirection>(static_cast<Ark_ScrollDirection>(INT_MAX));
    modifier_->setScrollable(node_, &direction);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto afterState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(afterState);
    EXPECT_EQ(beforeState.value(), afterState.value());

    direction = Converter::ArkValue<Opt_ScrollDirection>(
        static_cast<Ark_ScrollDirection>(INT_MIN));
    modifier_->setScrollable(node_, &direction);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    afterState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(afterState);
    EXPECT_EQ(beforeState.value(), afterState.value());
}

/**
 * @tc.name: setOnScrollTestSetCallback
 * @tc.desc: Test OnScrollImpl
 * @tc.type: FUNC
 */
#ifdef DEPRECATED
HWTEST_F(ScrollModifierTest, setOnScrollTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_F64_F64_Void func{};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollEvent());

    struct ScrollData
    {
        Ark_Float64 x;
        Ark_Float64 y;
        Ark_Int32  nodeId;
    };
    static std::optional<ScrollData> data;
    EventsTracker::eventsReceiver.onScroll = [] (Ark_Int32 nodeId, const Ark_Float64 x, const Ark_Float64 y)
    {
        data = {x, y, nodeId};
    };

    modifier_->setOnScroll(node_, &func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnScrollEvent());

    Dimension x(33.0, DimensionUnit::VP);
    Dimension y(133.0, DimensionUnit::VP);
    eventHub->GetOnScrollEvent()(x, y);
    ASSERT_TRUE(data);
    ASSERT_EQ(x.Value(), data->x.f32);
    ASSERT_EQ(y.Value(), data->y.f32);
    ASSERT_EQ(frameNode->GetId(), data->nodeId);
}
#endif

/**
 * @tc.name: setOnScrollStartTestSetCallback
 * @tc.desc: Test OnScrollStartImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnScrollStartTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollStart());

    static std::optional<ScrollStateValue> state;
    VoidCallback callback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            state = {
                .nodeId = nodeId,
                .state = true
            };
        }
    };
    auto arkCallback = Converter::ArkValue<Opt_VoidCallback>(callback);

    modifier_->setOnScrollStart(node_, &arkCallback);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnScrollStart());

    eventHub->GetOnScrollStart()();
    ASSERT_TRUE(state.has_value());
    ASSERT_TRUE(state->state);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
}

/**
 * @tc.name: setOnScrollStopTestSetCallback
 * @tc.desc: Test OnScrollStopImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnScrollStopTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollStop());

    static std::optional<ScrollStateValue> state;
    VoidCallback callback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            state = {
                .nodeId = nodeId,
                .state = true
            };
        }
    };
    auto arkCallback = Converter::ArkValue<Opt_VoidCallback>(callback);

    modifier_->setOnScrollStop(node_, &arkCallback);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnScrollStop());

    eventHub->GetOnScrollStop()();
    ASSERT_TRUE(state.has_value());
    ASSERT_TRUE(state->state);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
}

/**
 * @tc.name: setScrollBarTestSetDisplayMode
 * @tc.desc: Test OnScrollBarImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollBarTestSetDisplayMode, testing::ext::TestSize.Level1)
{
    auto testState = Converter::ArkValue<Opt_BarState>(DisplayMode::OFF);
    modifier_->setScrollBar(node_, &testState);
    auto afterState = GetAttrValue<std::string>(node_, "scrollBar");
    ASSERT_EQ("BarState.Off", afterState);
}

/**
 * @tc.name: setScrollBarTestSetBadDisplayMode
 * @tc.desc: Test OnScrollBarImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollBarTestSetBadDisplayMode, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBar";
    auto beforeState = GetAttrValue<std::string>(node_, jsonKey);

    auto testState = Converter::ArkValue<Opt_BarState>(static_cast<Ark_BarState>(INT_MIN));
    modifier_->setScrollBar(node_, &testState);
    auto afterState = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(beforeState, Eq(afterState));

    testState = Converter::ArkValue<Opt_BarState>(static_cast<Ark_BarState>(INT_MAX));
    modifier_->setScrollBar(node_, &testState);
    afterState = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(beforeState, Eq(afterState));
}

/**
 * @tc.name: setScrollBarColorTestSetColorString
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollBarColorTestSetColorString, testing::ext::TestSize.Level1)
{
    std::string testColor = "#11123456";
    auto colorUnion = Converter::ArkUnion<Opt_Union_Color_I32_String_Resource, Ark_String>(testColor);
    modifier_->setScrollBarColor(node_, &colorUnion);

    auto after = GetAttrValue<std::string>(node_, "scrollBarColor");
    ASSERT_EQ(testColor, after);
}

/**
 * @tc.name: setScrollBarColorTestSetColorEnum
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollBarColorTestSetColorEnum, testing::ext::TestSize.Level1)
{
    auto colorUnion = Converter::ArkUnion<Opt_Union_Color_I32_String_Resource, Ark_Color>(ARK_COLOR_GREEN);
    modifier_->setScrollBarColor(node_, &colorUnion);

    auto after = GetAttrValue<std::string>(node_, "scrollBarColor");
    EXPECT_THAT(after, Eq("#FF008000"));
}

/**
 * @tc.name: setScrollBarColorTestSetBadColorString
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, DISABLED_setScrollBarColorTestSetBadColorString, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarColor";
    std::string before = "#FF000000";

    // empty color string
    std::string testColor = "";
    auto colorUnion = Converter::ArkUnion<Opt_Union_Color_I32_String_Resource, Ark_String>(testColor);
    modifier_->setScrollBarColor(node_, &colorUnion);
    auto after = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_EQ(before, after);
    // nullptr value
    modifier_->setScrollBarColor(node_, nullptr);
    after = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_EQ(before, after);
}

/**
 * @tc.name: setScrollBarWidthTestSetWidth
 * @tc.desc: Test OnScrollBarWidthImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollBarWidthTestSetWidth, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarWidth";
    Dimension testValue(33.56, DimensionUnit::VP);
    auto testNumber = Converter::ArkValue<Ark_Float64>(testValue.ConvertToVp());
    auto arkVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(testNumber);

    modifier_->setScrollBarWidth(node_, &arkVal);
    auto setVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(setVal, Eq(testValue.ToString()));

    auto strVal = std::string("222.99px");
    arkVal = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(strVal);

    modifier_->setScrollBarWidth(node_, &arkVal);
    setVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(setVal, Eq(strVal));
}

/**
 * @tc.name: setScrollBarWidthTestSetDefectiveWidth
 * @tc.desc: Test OnScrollBarWidthImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, DISABLED_setScrollBarWidthTestSetDefectiveWidth, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarWidth";
    auto defaultVal = GetAttrValue<std::string>(node_, jsonKey);

    modifier_->setScrollBarWidth(node_, nullptr);

    auto testVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(testVal, Eq(defaultVal));

    Ark_String str = Converter::ArkValue<Ark_String>("");
    auto emptyString = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(str);
    modifier_->setScrollBarWidth(node_, &emptyString);

    testVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(testVal, Eq(defaultVal));

    auto testNumber = Converter::ArkValue<Ark_Float64>(-1.0);
    auto defectiveNumber = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(testNumber);
    modifier_->setScrollBarWidth(node_, &defectiveNumber);

    testVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(testVal, Eq(defaultVal));

    auto testStr = Converter::ArkValue<Ark_String>("33%");
    defectiveNumber = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(testStr);
    modifier_->setScrollBarWidth(node_, &defectiveNumber);

    testVal = GetAttrValue<std::string>(node_, jsonKey);
    EXPECT_THAT(testVal, Eq(defaultVal));
}

/**
 * @tc.name: setFrictionTestSetNullValue
 * @tc.desc: Test FrictionImpl attempt to set a null value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, DISABLED_setFrictionTestSetNullValue, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto defaultFriction = GetAttrValue<double>(json, "friction");
    modifier_->setFriction(node_, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_EQ(defaultFriction, GetAttrValue<double>(json, "friction"));
}

/**
 * @tc.name: setFrictionTestSetAValue
 * @tc.desc: Test FrictionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setFrictionTestSetAValue, testing::ext::TestSize.Level1)
{
    float testValue = 0.13;
    auto testNumber = Converter::ArkValue<Ark_Float64>(testValue);
    auto friction = Converter::ArkUnion<Opt_Union_F64_Resource, Ark_Float64>(testNumber);

    modifier_->setFriction(node_, &friction);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto frictionValue = GetAttrValue<double>(json, "friction");
    EXPECT_THAT(frictionValue, Optional(DoubleEq(testValue)));
}

/**
 * @tc.name: setFrictionTestSetAValueFromResource
 * @tc.desc: Test FrictionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setFrictionTestSetAValueFromResource, testing::ext::TestSize.Level1)
{
    double testVal = 0.317f;
    std::string resName = "app.float.friction";
    AddResource(resName, testVal);
    auto RES_NAME = NamedResourceId{resName.c_str(), ResourceType::FLOAT};
    auto friction = CreateResourceUnion<Opt_Union_F64_Resource>(RES_NAME);

    modifier_->setFriction(node_, &friction);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    std::string jsonName = "friction";
    auto frictionValue = GetAttrValue<double>(json, jsonName);
    EXPECT_THAT(frictionValue, Optional(DoubleEq(testVal)));
}

/**
 * @tc.name: setEnablePagingTestSetValues
 * @tc.desc: Test EnablePagingImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setEnablePagingTestSetValues, testing::ext::TestSize.Level1)
{
    // enablePaging is initially hidden in JSON
    auto root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    auto enablePaging = GetAttrValue<bool>(root, "enablePaging");
    ASSERT_FALSE(enablePaging.has_value());

    auto value = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnablePaging(node_, &value);
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<bool>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    EXPECT_TRUE(enablePaging.value());

    value = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnablePaging(node_, &value);
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<bool>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    EXPECT_FALSE(enablePaging.value());
}

/**
 * @tc.name: setInitialOffsetTestSetNullValue
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, DISABLED_setInitialOffsetTestSetNullValue, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xBefore = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yBefore = GetAttrValue<std::string>(initialOffset, "yOffset");

    modifier_->setInitialOffset(node_, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    ASSERT_EQ(xBefore, xAfter);
    ASSERT_EQ(yBefore, yAfter);
}

/**
 * @tc.name: setInitialOffsetTestSetAValue
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setInitialOffsetTestSetAValue, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto offset = Converter::ArkValue<Opt_OffsetOptions>(Ark_OffsetOptions {
        .xOffset = Converter::ArkValue<Opt_Dimension>(22.0f),
        .yOffset = Converter::ArkValue<Opt_Dimension>(7.0f)});
    modifier_->setInitialOffset(node_, &offset);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");

    EXPECT_THAT(xAfter, Eq("22.00vp"));
    EXPECT_THAT(yAfter, Eq("7.00vp"));
}

/**
 * @tc.name: setInitialOffsetTestSetBothCoordinatesDisabled
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setInitialOffsetTestSetBothCoordinatesDisabled, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xBefore = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yBefore = GetAttrValue<std::string>(initialOffset, "yOffset");

    auto offset = Converter::ArkValue<Opt_OffsetOptions>(Ark_OffsetOptions {
        .xOffset = Converter::ArkValue<Opt_Dimension>(),
        .yOffset = Converter::ArkValue<Opt_Dimension>()});
    modifier_->setInitialOffset(node_, &offset);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    ASSERT_EQ(xBefore, xAfter);
    ASSERT_EQ(yBefore, yAfter);
}

/**
 * @tc.name: setInitialOffsetTestSetOneCoordinateDisabled
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setInitialOffsetTestSetOneCoordinateDisabled, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xBefore = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yBefore = GetAttrValue<std::string>(initialOffset, "yOffset");
    // disabled y will be set to some defined by lower levels value (we expect that it will the same as after start)
    auto offset = Converter::ArkValue<Opt_OffsetOptions>(Ark_OffsetOptions {
        .xOffset = Converter::ArkValue<Opt_Dimension>(22.f),
        .yOffset = Converter::ArkValue<Opt_Dimension>()});
    modifier_->setInitialOffset(node_, &offset);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    EXPECT_THAT(xAfter, Eq("22.00vp"));
    EXPECT_THAT(yBefore, Eq(yAfter));
    // disabled x will be set to some defined by lower levels value (we expect that it will the same as after start)
    offset = Converter::ArkValue<Opt_OffsetOptions>(Ark_OffsetOptions {
        .xOffset = Converter::ArkValue<Opt_Dimension>(),
        .yOffset = Converter::ArkValue<Opt_Dimension>(7.f)});
    modifier_->setInitialOffset(node_, &offset);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    EXPECT_THAT(xBefore, Eq(xAfter));
    EXPECT_THAT(yAfter, Eq("7.00vp"));
}

/**
 * @tc.name: setEdgeEffectTestSetValues
 * @tc.desc: Test EdgeEffectImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setEdgeEffectTestSetValues, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto edgeEffectOptions = json->GetValue("edgeEffectOptions");

    bool testVal1 = edgeEffectOptions ? !GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled") : false;
    auto options = Converter::ArkValue<Opt_EdgeEffectOptions>(testVal1);
    auto effect = Converter::ArkValue<Opt_EdgeEffect>(EdgeEffect::FADE);

    modifier_->setEdgeEffect(node_, &effect, &options);
    EXPECT_EQ("EdgeEffect.Fade", GetAttrValue<std::string>(node_, "edgeEffect"));

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_EQ(testVal1, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
}

/**
 * @tc.name: setEdgeEffectTestSetBadValues
 * @tc.desc: Test EdgeEffectImpl
 * @tc.type: FUNC
 */

HWTEST_F(ScrollModifierTest, DISABLED_setEdgeEffectTestSetBadValues, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    auto defaultAlways = GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled");
    auto defaultEffect = GetAttrValue<std::string>(node_, "edgeEffect");

    auto options = Converter::ArkValue<Opt_EdgeEffectOptions>(defaultAlways);
    auto effect = Converter::ArkValue<Opt_EdgeEffect>(static_cast<Ark_EdgeEffect>(INT_MAX));
    modifier_->setEdgeEffect(node_, &effect, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_THAT(defaultAlways, Eq(GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled")));
    EXPECT_THAT(defaultEffect, Eq(GetAttrValue<std::string>(node_, "edgeEffect")));

    effect = Converter::ArkValue<Opt_EdgeEffect>(static_cast<Ark_EdgeEffect>(INT_MIN));
    modifier_->setEdgeEffect(node_, &effect, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_THAT(defaultAlways, Eq(GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled")));
    EXPECT_THAT(defaultEffect, Eq(GetAttrValue<std::string>(node_, "edgeEffect")));

    modifier_->setEdgeEffect(node_, &effect, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_THAT(defaultAlways, Eq(GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled")));
    EXPECT_THAT(defaultEffect, Eq(GetAttrValue<std::string>(node_, "edgeEffect")));
}

/*
 * @tc.name: setScrollOptionsTest
 * @tc.desc: Test SetScrollOptions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollOptionsTest, testing::ext::TestSize.Level1)
{
    auto peer = fullAPI_->getAccessors()->getScrollerAccessor()->construct();
    auto peerImplPtr = static_cast<ScrollerPeer *>(peer);
    ASSERT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);

    Opt_Scroller scroller = Converter::ArkValue<Opt_Scroller>(peerImplPtr);
    modifier_->setScrollOptions(node_, &scroller);

    RefPtr<ScrollControllerBase> positionController = pattern->GetOrCreatePositionController();
    ASSERT_NE(positionController, nullptr);
    RefPtr<ScrollProxy> scrollBarProxy = pattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);

    ASSERT_EQ(peerImplPtr->GetController(), positionController);
    ASSERT_EQ(peerImplPtr->GetScrollBarProxy(), scrollBarProxy);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(peerImplPtr);
}

/**
 * @tc.name: setScrollOptionsTestEmptyScroller
 * @tc.desc: Test SetScrollOptions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollOptionsTestEmptyScroller, testing::ext::TestSize.Level1)
{
    auto peer = fullAPI_->getAccessors()->getScrollerAccessor()->construct();
    auto peerImplPtr = static_cast<ScrollerPeer *>(peer);
    ASSERT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    ASSERT_NE(pattern, nullptr);

    Opt_Scroller scroller = Converter::ArkValue<Opt_Scroller>(Ark_Empty());
    modifier_->setScrollOptions(node_, &scroller);

    RefPtr<ScrollControllerBase> positionController = pattern->GetOrCreatePositionController();
    ASSERT_NE(positionController, nullptr);
    RefPtr<ScrollProxy> scrollBarProxy = pattern->GetScrollBarProxy();
    ASSERT_NE(scrollBarProxy, nullptr);

    ASSERT_NE(peerImplPtr->GetController(), positionController);
    ASSERT_NE(peerImplPtr->GetScrollBarProxy(), scrollBarProxy);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(peerImplPtr);
}

/**
 * @tc.name: setNestedScrollTestOption
 * @tc.desc: Test NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setNestedScrollTestOption, testing::ext::TestSize.Level1)
{
    auto  options = Converter::ArkValue<Opt_NestedScrollOptions>(Ark_NestedScrollOptions {
        .scrollForward = Ark_NestedScrollMode::ARK_NESTED_SCROLL_MODE_SELF_FIRST,
        .scrollBackward = Ark_NestedScrollMode::ARK_NESTED_SCROLL_MODE_PARALLEL
    });

    modifier_->setNestedScroll(node_, &options);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    auto forward = GetAttrValue<std::string>(nestedScroll, "scrollForward");
    auto backward = GetAttrValue<std::string>(nestedScroll, "scrollBackward");
    EXPECT_EQ(std::string("NestedScrollMode.SELF_FIRST"), forward);
    EXPECT_EQ(std::string("NestedScrollMode.PARALLEL"), backward);
}

/**
 * @tc.name: setNestedScrollTestSetDefectiveNestedScrollOptions
 * @tc.desc: Test NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setNestedScrollTestSetDefectiveNestedScrollOptions, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    auto forwardBefore = GetAttrValue<std::string>(nestedScroll, "scrollForward");
    auto backwardBefore = GetAttrValue<std::string>(nestedScroll, "scrollBackward");

    NestedScrollMode testVal1 = static_cast<NestedScrollMode>(INT_MAX);
    NestedScrollMode testVal2 = static_cast<NestedScrollMode>(INT_MIN);
    auto options = Converter::ArkValue<Opt_NestedScrollOptions>(Ark_NestedScrollOptions {
        .scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(testVal1),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(testVal2)
    });
    modifier_->setNestedScroll(node_, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    ASSERT_EQ(forwardBefore, GetAttrValue<std::string>(nestedScroll, "scrollForward"));
    ASSERT_EQ(backwardBefore, GetAttrValue<std::string>(nestedScroll, "scrollBackward"));

    modifier_->setNestedScroll(node_, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    EXPECT_THAT(forwardBefore, Eq(GetAttrValue<std::string>(nestedScroll, "scrollForward")));
    EXPECT_THAT(backwardBefore, Eq(GetAttrValue<std::string>(nestedScroll, "scrollBackward")));
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptions, testing::ext::TestSize.Level1)
{
    std::vector<float> testSet{1, 2, 3, 4};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .enableSnapToStart = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .enableSnapToEnd = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = createSnapSet(arrayHolder.ArkValue())
    });
    modifier_->setScrollSnap(node_, &newOpt);

    auto state = GetJsonValue(node_);
    ASSERT_TRUE(state);
    auto scrollSnap = state->GetObject("scrollSnap");
    ASSERT_TRUE(scrollSnap);
    auto enableSnapToEnd = GetAttrValue<bool>(scrollSnap, "enableSnapToEnd");
    ASSERT_TRUE(enableSnapToEnd);
    ASSERT_FALSE(enableSnapToEnd.value());
    auto enableSnapToStart = GetAttrValue<bool>(scrollSnap, "enableSnapToStart");
    ASSERT_TRUE(enableSnapToStart);
    ASSERT_FALSE(enableSnapToStart.value());
    auto snapPagination = scrollSnap->GetValue("snapPagination");
    ASSERT_TRUE(snapPagination);
    ASSERT_TRUE(snapPagination->IsArray());
    ASSERT_EQ(testSet.size(), snapPagination->GetArraySize());
    for (int i = 0; i < snapPagination->GetArraySize(); ++i) {
        auto arrayItem = snapPagination->GetArrayItem(i);
        auto dimVal = Converter::OptConvert<Dimension>(arrayHolder.ArkValue().array[i]);
        ASSERT_TRUE(arrayItem);
        EXPECT_EQ(dimVal.value().ToString(), arrayItem->GetString());
    }
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetSnapAlignOption
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetSnapAlignOption, testing::ext::TestSize.Level1)
{
    auto snapAlign = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign.NONE"), snapAlign);

    auto intervalLen = Converter::ArkValue<Ark_Dimension>(1234.f);
    auto interval = Converter::ArkUnion<Ark_Union_Dimension_Array_Dimension, Ark_Dimension>(intervalLen);
    auto options = Ark_ScrollSnapOptions {
        .enableSnapToStart = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .enableSnapToEnd = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .snapPagination = Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(interval)
    };
    options.snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_END;
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(options);
    modifier_->setScrollSnap(node_, &newOpt);

    snapAlign = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign::END"), snapAlign);

    options.snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_START;
    newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(options);
    modifier_->setScrollSnap(node_, &newOpt);

    snapAlign = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign.START"), snapAlign);
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetBadSnapAlignOption
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetBadSnapAlignOption, testing::ext::TestSize.Level1)
{
    auto snapAlignBefore = GetAttrValue<std::string>(node_, "scrollSnapAlign");

    Ark_ScrollSnapOptions options;
    options.snapAlign = static_cast<Ark_ScrollSnapAlign>(INT_MAX);
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(options);
    modifier_->setScrollSnap(node_, &newOpt);

    auto snapAlignAfter = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    ASSERT_EQ(snapAlignBefore, snapAlignAfter);
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsDefaultSnapPagination
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsDefaultSnapPagination, testing::ext::TestSize.Level1)
{
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .enableSnapToStart = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .enableSnapToEnd = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false)),
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER
    });
    modifier_->setScrollSnap(node_, &newOpt);

    auto state = GetJsonValue(node_);
    ASSERT_TRUE(state);
    auto scrollSnap = GetAttrObject(state, "scrollSnap");
    ASSERT_TRUE(scrollSnap);
    ASSERT_EQ(GetAttrValue<std::string>(scrollSnap, "snapPagination"), "0.00vp");
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetIntervalSize
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetIntervalSize, testing::ext::TestSize.Level1)
{
    auto intervalLen = Converter::ArkValue<Ark_Dimension>(1234.f);
    auto interval = Converter::ArkUnion<Ark_Union_Dimension_Array_Dimension, Ark_Dimension>(intervalLen);
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(interval)
    });
    modifier_->setScrollSnap(node_, &newOpt);

    auto dim = Converter::OptConvert<Dimension>(intervalLen);
    ASSERT_TRUE(dim);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    ASSERT_EQ(dim.value().ToString(), GetAttrValue<std::string>(scrollSnap, "snapPagination"));
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetNegativeIntervalSize
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetNegativeIntervalSize, testing::ext::TestSize.Level1)
{
    auto intervalLen = Converter::ArkValue<Ark_Dimension>("-1234px");
    auto interval = Converter::ArkUnion<Ark_Union_Dimension_Array_Dimension, Ark_Dimension>(intervalLen);
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(interval)
    });
    modifier_->setScrollSnap(node_, &newOpt);

    Dimension dim;
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    ASSERT_EQ(dim.ToString(), GetAttrValue<std::string>(scrollSnap, "snapPagination"));
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetArrayOfPositions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetArrayOfPositions, testing::ext::TestSize.Level1)
{
    std::vector<float> testSet{10, 45, 6, 9};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = createSnapSet(arrayHolder.ArkValue())
    });
    modifier_->setScrollSnap(node_, &newOpt);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto snapPagination = scrollSnap->GetValue("snapPagination");
    ASSERT_TRUE(snapPagination->IsArray());
    ASSERT_EQ(testSet.size(), snapPagination->GetArraySize());
    for (int32_t i = 0; i < snapPagination->GetArraySize(); ++i) {
        auto arrayItem = snapPagination->GetArrayItem(i);
        ASSERT_TRUE(arrayItem);
        auto dimVal = Converter::OptConvert<Dimension>(arrayHolder.ArkValue().array[i]);
        EXPECT_EQ(dimVal.value().ToString(), arrayItem->GetString());
    }
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsNegativeValuesInSnapPagination
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsNegativeValuesInSnapPagination,
    testing::ext::TestSize.Level1)
{
    std::vector<float> testSet{10., 45., -6., 9.};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = createSnapSet(arrayHolder.ArkValue())
    });
    modifier_->setScrollSnap(node_, &newOpt);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto snapPagination = scrollSnap->GetValue("snapPagination");
    ASSERT_FALSE(snapPagination->IsArray());
    Dimension dim;
    ASSERT_EQ(dim.ToString(), GetAttrValue<std::string>(scrollSnap, "snapPagination"));
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetEmptyArrayOfPositions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetEmptyArrayOfPositions, testing::ext::TestSize.Level1)
{
    // set up some initial, non default state
    std::vector<float> testSet{10, 45, 6, 9};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);
    auto opt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = createSnapSet(arrayHolder.ArkValue()),
        .enableSnapToStart = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(false))
    });
    modifier_->setScrollSnap(node_, &opt);
    auto jsonBefore = GetJsonValue(node_);
    ASSERT_TRUE(jsonBefore);

    std::vector<float> emptySet;
    Converter::ArkArrayHolder<Array_Dimension> emptyArrayHolder(emptySet);
    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(Ark_ScrollSnapOptions {
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_END,
        .snapPagination = createSnapSet(emptyArrayHolder.ArkValue()),
        .enableSnapToStart = Converter::ArkValue<Opt_Boolean>(Converter::ArkValue<Ark_Boolean>(true)),
    });
    modifier_->setScrollSnap(node_, &newOpt);
    auto jsonAfter = GetJsonValue(node_);
    ASSERT_TRUE(jsonAfter);

    auto snapAlignAfter = GetAttrValue<std::string>(jsonAfter, "scrollSnapAlign");
    ASSERT_NE(snapAlignAfter, GetAttrValue<std::string>(jsonBefore, "scrollSnapAlign"));

    auto scrollSnapBefore = jsonBefore->GetObject("scrollSnap");
    ASSERT_TRUE(scrollSnapBefore);
    auto scrollSnapAfter = jsonAfter->GetObject("scrollSnap");
    ASSERT_NE(
        GetAttrValue<bool>(scrollSnapBefore, "enableSnapToStart"),
        GetAttrValue<bool>(scrollSnapAfter, "enableSnapToStart")
    );

    auto snapPaginationBefore = scrollSnapBefore->GetValue("snapPagination");
    ASSERT_TRUE(snapPaginationBefore->IsArray());
    auto snapPaginationAfter = scrollSnapAfter->GetValue("snapPagination");
    ASSERT_NE(snapPaginationBefore->IsArray(), snapPaginationAfter->IsArray());
    Dimension dim;
    ASSERT_EQ(dim.ToString(), snapPaginationAfter->GetString());
}

/**
 * @tc.name: setScrollSnapTestSetSnapOptionsSetNullSnapSet
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetSnapOptionsSetNullSnapSet, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto scrollSnapBefore = GetAttrValue<std::string>(scrollSnap, "snapPagination");

    auto newOpt = Converter::ArkValue<Opt_ScrollSnapOptions>(
        Ark_ScrollSnapOptions {.snapPagination = createEmptySnapSet()});
    modifier_->setScrollSnap(node_, &newOpt);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    scrollSnap = json->GetObject("scrollSnap");
    auto scrollSnapAfter = GetAttrValue<std::string>(scrollSnap, "snapPagination");
    ASSERT_EQ(scrollSnapBefore, scrollSnapAfter);
}

/**
 * @tc.name: setScrollSnapTestSetVoidSnapOptions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setScrollSnapTestSetVoidSnapOptions, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto enableSnapToStartBefore = GetAttrValue<bool>(scrollSnap, "enableSnapToStart");
    auto enableSnapToEndBefore = GetAttrValue<bool>(scrollSnap, "enableSnapToEnd");
    auto scrollSnapBefore = GetAttrValue<std::string>(scrollSnap, "snapPagination");
    auto scrollSnapAlignBefore = GetAttrValue<std::string>(json, "scrollSnapAlign");

    modifier_->setScrollSnap(node_, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    scrollSnap = json->GetObject("scrollSnap");
    auto enableSnapToStartAfter = GetAttrValue<bool>(scrollSnap, "enableSnapToStart");
    auto enableSnapToEndAfter = GetAttrValue<bool>(scrollSnap, "enableSnapToEnd");
    auto scrollSnapAfter = GetAttrValue<std::string>(scrollSnap, "snapPagination");
    auto scrollSnapAlignAfter = GetAttrValue<std::string>(json, "scrollSnapAlign");
    EXPECT_THAT(enableSnapToStartBefore, Eq(enableSnapToStartAfter));
    EXPECT_THAT(enableSnapToEndBefore, Eq(enableSnapToEndAfter));
    EXPECT_THAT(scrollSnapBefore, Eq(scrollSnapAfter));
    EXPECT_THAT(scrollSnapAlignBefore, Eq(scrollSnapAlignAfter));
}

/**
 * @tc.name: setEnableScrollInteractionTestSetValue
 * @tc.desc: Test EnableScrollInteractionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setEnableScrollInteractionTestSetValue, testing::ext::TestSize.Level1)
{
    auto value = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEnableScrollInteraction(node_, &value);
    auto root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    auto enable = GetAttrValue<bool>(root, "enableScrollInteraction");
    ASSERT_TRUE(enable.has_value());
    EXPECT_TRUE(enable.value());

    value = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableScrollInteraction(node_, &value);
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enable = GetAttrValue<bool>(root, "enableScrollInteraction");
    ASSERT_TRUE(enable.has_value());
    ASSERT_FALSE(enable.value());
}

/**
 * @tc.name: setOnScrollEdgeTestSetCallback
 * @tc.desc: Test OnScrollEdgeImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnScrollEdgeTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct resultData {
        Ark_Int32 resourceId;
        Ark_Edge side;
    };
    static std::optional<resultData> result;

    auto callback = [](
        const Ark_Int32 resourceId, Ark_Edge side) {
            result = {resourceId, side};
    };

    auto id = Converter::ArkValue<Ark_Int32>(123);

    auto apiCall = Converter::ArkValue<Opt_OnScrollEdgeCallback>(
        Converter::ArkValue<OnScrollEdgeCallback>(callback, id));
    ASSERT_FALSE(eventHub->GetScrollEdgeEvent());

    ASSERT_NE(modifier_->setOnScrollEdge, nullptr);
    modifier_->setOnScrollEdge(node_, &apiCall);

    ASSERT_TRUE(eventHub->GetScrollEdgeEvent());
    eventHub->GetScrollEdgeEvent()(ScrollEdge::BOTTOM);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(Ark_Edge::ARK_EDGE_BOTTOM, result.value().side);
    EXPECT_EQ(id, result.value().resourceId);
}

/**
 * @tc.name: setOnScrollEdgeTestSetNullCallback
 * @tc.desc: Test OnScrollEdgeImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnScrollEdgeTestSetNullCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_NE(modifier_->setOnScrollEdge, nullptr);
    modifier_->setOnScrollEdge(node_, nullptr);
    ASSERT_FALSE(eventHub->GetScrollEdgeEvent());
}

/**
 * @tc.name: setOnScrollFrameBeginTest
 * @tc.desc: Test for setOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnScrollFrameBeginTest, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_NE(modifier_->setOnScrollFrameBegin, nullptr);
    modifier_->setOnScrollFrameBegin(node_, nullptr);

    static const Ark_Int32 expectedResId = 123;
    auto onScrollFrameBegin = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Float64 offset, Ark_ScrollState state,
        const Callback_OnScrollFrameBeginHandlerResult_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_DOUBLE_EQ(Converter::Convert<double>(offset), TEST_OFFSET);
        ScrollFrameResult result;
        result.offset = Converter::Convert<Dimension>(offset);
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_OnScrollFrameBeginHandlerResult>(result));
    };
    auto arkFunc = Converter::ArkValue<Opt_OnScrollFrameBeginCallback>(Converter::ArkValue<OnScrollFrameBeginCallback>(
        nullptr, onScrollFrameBegin, expectedResId));
    modifier_->setOnScrollFrameBegin(node_, &arkFunc);

    Dimension dimension(TEST_OFFSET);
    ScrollState state = ScrollState::SCROLL;
    ScrollFrameResult result = eventHub->GetOnScrollFrameBegin()(dimension, state);
    EXPECT_EQ(result.offset.ConvertToPx(), dimension.ConvertToPx());
}

/**
 * @tc.name: setOnWillScrollTestSetCallback
 * @tc.desc: Test OnWillScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnWillScrollTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct ScrollData
    {
        Ark_ScrollState state;
        Ark_ScrollSource source;
        Ark_Int32 nodeId;
    };
    static std::optional<ScrollData> otherState;

    auto callback = [](
        Ark_VMContext context,
        const Ark_Int32 resourceId,
        const Ark_Float64 xOffset,
        const Ark_Float64 yOffset,
        Ark_ScrollState scrollState,
        Ark_ScrollSource scrollSource,
        const Callback_Opt_OffsetResult_Void continuation) {
        otherState = {scrollState, scrollSource, resourceId};
        Ark_OffsetResult retVal;
        retVal.xOffset = xOffset;
        retVal.yOffset = yOffset;
        CallbackHelper(continuation).InvokeSync(Converter::ArkValue<Opt_OffsetResult>(retVal));
    };

    auto id = Converter::ArkValue<Ark_Int32>(123);

    auto apiCall = Converter::ArkValue<Opt_ScrollOnWillScrollCallback>(
        Converter::ArkValue<ScrollOnWillScrollCallback>(nullptr, callback, id));
    ASSERT_FALSE(eventHub->GetScrollEdgeEvent());

    ASSERT_NE(modifier_->setOnWillScroll, nullptr);
    modifier_->setOnWillScroll(node_, &apiCall);

    ASSERT_TRUE(eventHub->GetOnWillScrollEvent());
    Dimension x(212, DimensionUnit::VP);
    Dimension y(984, DimensionUnit::VP);
    auto returnValue = eventHub->GetOnWillScrollEvent()(x, y, ScrollState::FLING, ScrollSource::SCROLL_BAR);
    EXPECT_EQ(returnValue.xOffset.ToString(), "212.00vp");
    EXPECT_EQ(returnValue.yOffset.ToString(), "984.00vp");
    ASSERT_TRUE(otherState.has_value());
    EXPECT_EQ(Ark_ScrollState::ARK_SCROLL_STATE_FLING, otherState->state);
    EXPECT_EQ(Ark_ScrollSource::ARK_SCROLL_SOURCE_SCROLL_BAR, otherState->source);
    EXPECT_EQ(id, otherState->nodeId);
}

/**
 * @tc.name: setOnWillScrollTestSetNullptrCallback
 * @tc.desc: Test OnWillScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnWillScrollTestSetNullptrCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_FALSE(eventHub->GetOnWillScrollEvent());
    ASSERT_NE(modifier_->setOnWillScroll, nullptr);
    modifier_->setOnWillScroll(node_, nullptr);
    ASSERT_FALSE(eventHub->GetOnWillScrollEvent());
}

/*
 * @tc.name: setOnDidScrollTestSetCallback
 * @tc.desc: Test OnDidScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnDidScrollTestSetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct resultData {
        Ark_Int32 resourceId;
        Ark_Float64 x;
        Ark_Float64 y;
        Ark_ScrollState state;
    };
    static std::optional<resultData> result;

    auto callback = [](
        const Ark_Int32 resourceId, const Ark_Float64 xOffset, const Ark_Float64 yOffset, Ark_ScrollState scrollState) {
            result = {resourceId, xOffset, yOffset, scrollState};
    };

    auto id = Converter::ArkValue<Ark_Int32>(123);

    auto apiCall = Converter::ArkValue<Opt_ScrollOnScrollCallback>(
        Converter::ArkValue<ScrollOnScrollCallback>(callback, id));
    ASSERT_FALSE(eventHub->GetOnDidScrollEvent());

    ASSERT_NE(modifier_->setOnDidScroll, nullptr);
    modifier_->setOnDidScroll(node_, &apiCall);

    ASSERT_TRUE(eventHub->GetOnDidScrollEvent());
    int testValX = 12;
    int testValY = 333;
    Dimension x(testValX);
    Dimension y(testValY);
    eventHub->GetOnDidScrollEvent()(x, y, ScrollState::SCROLL);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(Ark_ScrollState::ARK_SCROLL_STATE_SCROLL, result.value().state);
    auto resultValX = Converter::OptConvert<int>(result.value().x);
    auto resultValY = Converter::OptConvert<int>(result.value().y);
    ASSERT_TRUE(resultValX.has_value());
    EXPECT_EQ(testValX, resultValX.value());
    ASSERT_TRUE(resultValY.has_value());
    EXPECT_EQ(testValY, resultValY.value());
    EXPECT_EQ(id, result.value().resourceId);
}

/**
 * @tc.name: setOnDidScrollTestSetNullCallback
 * @tc.desc: Test OnScrollEdgeImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, setOnDidScrollTestSetNullCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_NE(modifier_->setOnDidScroll, nullptr);
    modifier_->setOnDidScroll(node_, nullptr);
    ASSERT_FALSE(eventHub->GetOnDidScrollEvent());
}
} // namespace OHOS::Ace::NG
