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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/implementation/scroller_peer_impl.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace {
struct EventsTracker {
    static inline GENERATED_ArkUIScrollEventsReceiver eventsReceiver {};

    static inline const GENERATED_ArkUIEventsAPI eventsApiImpl = {
        .getScrollEventsReceiver = [] () -> const GENERATED_ArkUIScrollEventsReceiver* {
            return &eventsReceiver;
        }
    };
};

struct ScrollStateValue {
    Ark_Int32 nodeId;
    bool state;
};

inline void AssignArkValue(Opt_Length& dst, const CalcDimension& src)
{
    if (src.Unit() == DimensionUnit::CALC) {
        return;
    }
    dst.tag = ARK_TAG_LENGTH;
    dst.value.value = src.ConvertToVp();
}

inline void AssignArkValue(Ark_OffsetOptions& dst, const OffsetT<CalcDimension>& src)
{
    AssignArkValue(dst.xOffset, src.GetX());
    AssignArkValue(dst.yOffset, src.GetY());
}

std::optional<std::string> getStringScrollable(std::unique_ptr<JsonValue>& json, std::string key)
{
    for (auto object = json->GetChild(); object->IsValid(); object = object->GetNext()) {
        if (object->IsString() && object->GetKey() == key) {
            return object->GetString();
        }
    }
    return std::nullopt;
}
Opt_Union_Dimension_Array_Dimension createSnapSet(Converter::ArkArrayHolder<Array_Dimension>& arrayHolder)
{
    Ark_Union_Dimension_Array_Dimension value;
    value.selector = 1;
    value.value1 = arrayHolder.ArkValue();

    Opt_Union_Dimension_Array_Dimension retVal;
    retVal.tag = ARK_TAG_OBJECT;
    retVal.value = value;
    return retVal;
}

} // namespace

class ScrollModifierTest : public ModifierTestBase<GENERATED_ArkUIScrollModifier,
                              &GENERATED_ArkUINodeModifiers::getScrollModifier, GENERATED_ARKUI_SCROLL> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<ScrollBarTheme>();
        fullAPI_->setArkUIEventsAPI(&EventsTracker::eventsApiImpl);
    }
};

/**
 * @tc.name: Scrollable_SetDirectionOnSlide
 * @tc.desc: Test ScrollableImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Scrollable_SetDirectionOnSlide, testing::ext::TestSize.Level1)
{
    auto direction = Ark_ScrollDirection::ARK_SCROLL_DIRECTION_FREE;
    modifier_->setScrollable(node_, direction);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    // json has 2 values with the key "scrollable" one is boolean and one is string (we need the later one)
    auto afterState = getStringScrollable(json, "scrollable");
    ASSERT_TRUE(afterState);
    ASSERT_EQ("ScrollDirection.Free", afterState.value());
}

/**
 * @tc.name: Scrollable_SetBadDirectionOnSlide
 * @tc.desc: Test ScrollableImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Scrollable_SetBadDirectionOnSlide, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollable";
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto beforeState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(beforeState);

    Ark_ScrollDirection direction = static_cast<Ark_ScrollDirection>(INT_MAX);
    modifier_->setScrollable(node_, direction);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto afterState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(afterState);
    EXPECT_EQ(beforeState.value(), afterState.value());

    direction = static_cast<Ark_ScrollDirection>(INT_MIN);
    modifier_->setScrollable(node_, direction);
    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    afterState = getStringScrollable(json, jsonKey);
    ASSERT_TRUE(afterState);
    EXPECT_EQ(beforeState.value(), afterState.value());
}

/**
 * @tc.name: OnScroll_SetCallback
 * @tc.desc: Test OnScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScroll_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Number_Number_Void func{};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollEvent());

    struct ScrollData
    {
        Ark_Number x;
        Ark_Number y;
        Ark_Int32  nodeId;
    };
    static std::optional<ScrollData> data;
    EventsTracker::eventsReceiver.onScroll = [] (Ark_Int32 nodeId, const Ark_Number x, const Ark_Number y)
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

/**
 * @tc.name: OnScrollStart_SetCallback
 * @tc.desc: Test OnScrollStartImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollStart_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    VoidCallback func{};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollStart());

    static std::optional<ScrollStateValue> state;
    EventsTracker::eventsReceiver.onScrollStart = [] (Ark_Int32 nodeId)
    {
        state = {nodeId, true};
    };

    modifier_->setOnScrollStart(node_, &func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnScrollStart());

    eventHub->GetOnScrollStart()();
    ASSERT_TRUE(state.has_value());
    ASSERT_TRUE(state->state);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
}

/**
 * @tc.name: SetOnScrollEnd_SetCallBack
 * @tc.desc: Test OnScrollEndImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, SetOnScrollEnd_SetCallBack, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Callback_Void func{};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetScrollEndEvent());

    static std::optional<ScrollStateValue> state;
    EventsTracker::eventsReceiver.onScrollEnd = [] (Ark_Int32 nodeId)
    {
        state = {nodeId, false};
    };

    modifier_->setOnScrollEnd(node_, &func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetScrollEndEvent());

    eventHub->GetScrollEndEvent()();
    ASSERT_TRUE(state.has_value());
    ASSERT_FALSE(state->state);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
}

/**
 * @tc.name: OnScrollStop_setCallback
 * @tc.desc: Test OnScrollStopImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollStop_setCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    VoidCallback func{};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnScrollStop());

    static std::optional<ScrollStateValue> state;
    EventsTracker::eventsReceiver.onScrollStop = [] (Ark_Int32 nodeId)
    {
        state = {nodeId, true};
    };

    modifier_->setOnScrollStop(node_, &func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnScrollStop());

    eventHub->GetOnScrollStop()();
    ASSERT_TRUE(state.has_value());
    ASSERT_TRUE(state->state);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
}

/**
 * @tc.name: OnScrollBar_SetDisplayMode
 * @tc.desc: Test OnScrollBarImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollBar_SetDisplayMode, testing::ext::TestSize.Level1)
{
    auto testState = Converter::ArkValue<Ark_BarState>(DisplayMode::OFF);
    modifier_->setScrollBar(node_, testState);
    auto afterState = GetStringAttribute(node_, "scrollBar");
    ASSERT_EQ("BarState.Off", afterState);
}

/**
 * @tc.name: OnScrollBar_SetBadDisplayMode
 * @tc.desc: Test OnScrollBarImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollBar_SetBadDisplayMode, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBar";
    auto beforeState = GetStringAttribute(node_, jsonKey);

    Ark_BarState testState = static_cast<Ark_BarState>(INT_MIN);
    modifier_->setScrollBar(node_, testState);
    auto afterState = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(beforeState, afterState);

    testState = static_cast<Ark_BarState>(INT_MAX);
    modifier_->setScrollBar(node_, testState);
    afterState = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(beforeState, afterState);
}

/**
 * @tc.name: ScrollBarColor_SetColorString
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarColor_SetColorString, testing::ext::TestSize.Level1)
{
    std::string testColor = "#11123456";
    Ark_String str = Converter::ArkValue<Ark_String>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(node_, &colorUnion);

    auto after = GetStringAttribute(node_, "scrollBarColor");
    ASSERT_EQ(testColor, after);
}

/**
 * @tc.name: ScrollBarColor_SetColorEnum
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarColor_SetColorEnum, testing::ext::TestSize.Level1)
{
    int32_t testColor = 0xff008000;
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(Ark_Color::ARK_COLOR_GREEN);
    modifier_->setScrollBarColor(node_, &colorUnion);

    auto after = GetStringAttribute(node_, "scrollBarColor");
    auto afterNumeric = Color::FromString(after).GetValue();
    ASSERT_EQ(testColor, afterNumeric);
}

/**
 * @tc.name: ScrollBarColor_SetColorFloat
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarColor_SetColorFloat, testing::ext::TestSize.Level1)
{
    float testColor = 286405718.0;
    auto testNumber = Converter::ArkValue<Ark_Number>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(testNumber);
    modifier_->setScrollBarColor(node_, &colorUnion);

    auto after = GetStringAttribute(node_, "scrollBarColor");
    auto afterNumeric = Color::FromString(after).GetValue();
    ASSERT_EQ(testColor, afterNumeric);
}

/**
 * @tc.name: ScrollBarColor_SetBadColorString
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarColor_SetBadColorString, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarColor";
    std::string before = "#FF000000";

    // empty color string
    std::string testColor = "";
    Ark_String str = Converter::ArkValue<Ark_String>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(node_, &colorUnion);
    auto after = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(before, after);
    // nullptr to data
    str = {.length = 12334, .chars = nullptr};
    colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(node_, &colorUnion);
    after = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(before, after);
    // nullptr value
    modifier_->setScrollBarColor(node_, nullptr);
    after = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(before, after);
}

/**
 * @tc.name: ScrollModifierTest012
 * @tc.desc: Test OnScrollBarWidthImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarWidth_SetWidth, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarWidth";
    Dimension testValue(33.56, DimensionUnit::VP);
    auto testNumber = Converter::ArkValue<Ark_Number>(testValue.ConvertToVp());
    auto arkVal = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testNumber);

    modifier_->setScrollBarWidth(node_, &arkVal);
    auto setVal = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(setVal, testValue.ToString());

    auto strVal = std::string("222.99px");
    auto testStr = Converter::ArkValue<Ark_String>(strVal.data());
    arkVal = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(testStr);

    modifier_->setScrollBarWidth(node_, &arkVal);
    setVal = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(setVal, strVal);
}

/**
 * @tc.name: ScrollModifierTest012
 * @tc.desc: Test OnScrollBarWidthImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarWidth_SetDefectiveWidth, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarWidth";
    auto defaultVal = GetStringAttribute(node_, jsonKey);
    Dimension defaultValDim = Dimension::FromString(defaultVal);

    modifier_->setScrollBarWidth(node_, nullptr);

    auto testVal = GetStringAttribute(node_, jsonKey);
    EXPECT_EQ(testVal, defaultVal);

    Ark_Number num = {.tag = ARK_TAG_UNDEFINED};
    auto defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(num);
    modifier_->setScrollBarWidth(node_, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    Dimension testValDim = Dimension::FromString(testVal);
    EXPECT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    Ark_String str = {.length = 0, .chars = 0};
    auto emptyString = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(str);
    modifier_->setScrollBarWidth(node_, &emptyString);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    EXPECT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    auto testNumber = Converter::ArkValue<Ark_Number>(-1.0f);
    defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testNumber);
    modifier_->setScrollBarWidth(node_, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    EXPECT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    auto testStr = Converter::ArkValue<Ark_String>("33%");
    defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(testStr);
    modifier_->setScrollBarWidth(node_, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    EXPECT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());
}

/**
 * @tc.name: Friction_SetNullValue
 * @tc.desc: Test FrictionImpl attempt to set a null value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Friction_SetNullValue, testing::ext::TestSize.Level1)
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
 * @tc.name: Friction_SetAValue
 * @tc.desc: Test FrictionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Friction_SetAValue, testing::ext::TestSize.Level1)
{
    float testValue = 0.13;
    auto testNumber = Converter::ArkValue<Ark_Number>(testValue);
    auto friction = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(testNumber);

    modifier_->setFriction(node_, &friction);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    ASSERT_NEAR(testValue, GetAttrValue<double>(json, "friction"), 0.0001);
}

/**
 * @tc.name: Friction_SetAValueFromResource
 * @tc.desc: Test FrictionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Friction_SetAValueFromResource, testing::ext::TestSize.Level1)
{
    double testVal = 0.317;
    std::string resName = "app.float.friction";
    AddResource(resName, testVal);
    auto RES_NAME = NamedResourceId{resName.c_str(), NodeModifier::ResourceType::FLOAT};
    auto friction = CreateResourceUnion<Ark_Union_Number_Resource>(RES_NAME);

    modifier_->setFriction(node_, &friction);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    std::string jsonName = "friction";
    ASSERT_NEAR(testVal, GetAttrValue<double>(json, jsonName), 0.0001);
}

/**
 * @tc.name: EnablePaging_SetValues
 * @tc.desc: Test EnablePagingImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, EnablePaging_SetValues, testing::ext::TestSize.Level1)
{
    // enablePaging is initially hidden in JSON
    auto root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    auto enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_FALSE(enablePaging.has_value());

    modifier_->setEnablePaging(node_, Converter::ArkValue<Ark_Boolean>(true));
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    EXPECT_TRUE(enablePaging.value());

    modifier_->setEnablePaging(node_, Converter::ArkValue<Ark_Boolean>(false));
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    EXPECT_FALSE(enablePaging.value());
}

/**
 * @tc.name: InitialOffset_SetNullValue
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, InitialOffset_SetNullValue, testing::ext::TestSize.Level1)
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
 * @tc.name: InitialOffset_SetAValue
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, InitialOffset_SetAValue, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    OffsetT<CalcDimension> value;
    float x = 22;
    float y = 7;
    value.SetX(x);
    value.SetY(y);
    Ark_OffsetOptions offset;
    AssignArkValue(offset, value);
    modifier_->setInitialOffset(node_, &offset);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");

    ASSERT_EQ(value.GetX().ToString(), xAfter);
    ASSERT_EQ(value.GetY().ToString(), yAfter);
}

/**
 * @tc.name: InitialOffset_SetBothCoordinatesDisabled
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, InitialOffset_SetBothCoordinatesDisabled, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xBefore = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yBefore = GetAttrValue<std::string>(initialOffset, "yOffset");

    Ark_OffsetOptions offset;
    offset.xOffset.tag = ARK_TAG_UNDEFINED;
    offset.yOffset.tag = ARK_TAG_UNDEFINED;
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
 * @tc.name: InitialOffset_SetOneCoordinateDisabled
 * @tc.desc: Test InitialOffsetImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, InitialOffset_SetOneCoordinateDisabled, testing::ext::TestSize.Level1)
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
    OffsetT<CalcDimension> value;
    float x = 22;
    value.SetX(x);
    Ark_OffsetOptions offset;
    AssignArkValue(offset, value);
    offset.yOffset.tag = ARK_TAG_UNDEFINED;
    modifier_->setInitialOffset(node_, &offset);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    auto xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    auto yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    ASSERT_EQ(value.GetX().ToString(), xAfter);
    ASSERT_EQ(yBefore, yAfter);
    // disabled x will be set to some defined by lower levels value (we expect that it will the same as after start)
    OffsetT<CalcDimension> value1;
    float y = 7;
    value1.SetY(y);
    AssignArkValue(offset, value1);
    offset.xOffset.tag = ARK_TAG_UNDEFINED;
    modifier_->setInitialOffset(node_, &offset);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    initialOffset = json->GetObject("initialOffset");
    ASSERT_TRUE(initialOffset);
    xAfter = GetAttrValue<std::string>(initialOffset, "xOffset");
    yAfter = GetAttrValue<std::string>(initialOffset, "yOffset");
    ASSERT_EQ(xBefore, xAfter);
    ASSERT_EQ(value1.GetY().ToString(), yAfter);
}

/**
 * @tc.name: EdgeEffect_SetValues
 * @tc.desc: Test EdgeEffectImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, EdgeEffect_SetValues, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto edgeEffectOptions = json->GetValue("edgeEffectOptions");

    bool testVal1 = edgeEffectOptions ? !GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled") : false;
    auto options = Converter::ArkValue<Opt_EdgeEffectOptions>(std::optional(testVal1));
    Ark_EdgeEffect effect = Converter::ArkValue<Ark_EdgeEffect>(EdgeEffect::FADE);

    modifier_->setEdgeEffect(node_, effect, &options);
    EXPECT_EQ("EdgeEffect.Fade", GetStringAttribute(node_, "edgeEffect"));

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_EQ(testVal1, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
}

/**
 * @tc.name: EdgeEffect_SetBadValues
 * @tc.desc: Test EdgeEffectImpl
 * @tc.type: FUNC
 */

HWTEST_F(ScrollModifierTest, EdgeEffect_SetBadValues, testing::ext::TestSize.Level1)
{
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    auto defaultAlways = GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled");
    auto defaultEffect = GetStringAttribute(node_, "edgeEffect");

    auto options = Converter::ArkValue<Opt_EdgeEffectOptions>(std::optional(defaultAlways));
    Ark_EdgeEffect effect = static_cast<Ark_EdgeEffect>(INT_MAX);
    modifier_->setEdgeEffect(node_, effect, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    EXPECT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));

    effect = static_cast<Ark_EdgeEffect>(INT_MIN);
    modifier_->setEdgeEffect(node_, effect, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    EXPECT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));

    modifier_->setEdgeEffect(node_, effect, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    EXPECT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    EXPECT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));
}


} // namespace OHOS::Ace::NG
 * @tc.name: SetScrollOptions
 * @tc.desc: Test SetScrollOptions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, SetScrollOptions, testing::ext::TestSize.Level1)
{
    Ark_NativePointer scrollerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ScrollerPeerImpl*>(scrollerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);

    Ark_Scroller arkScroller;
    arkScroller.ptr = scrollerPtr;
    Opt_Scroller scroller = Converter::ArkValue<Opt_Scroller>(std::optional<Ark_Scroller>(arkScroller));
    modifier_->setScrollOptions(node_, &scroller);

    RefPtr<ScrollControllerBase> positionController = pattern->GetOrCreatePositionController();
    EXPECT_NE(positionController, nullptr);
    RefPtr<ScrollProxy> scrollBarProxy = pattern->GetScrollBarProxy();
    EXPECT_NE(scrollBarProxy, nullptr);

    EXPECT_EQ(peerImplPtr->GetController(), positionController);
    EXPECT_EQ(peerImplPtr->GetScrollBarProxy(), scrollBarProxy);

    Ark_NativePointer finalizerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(reinterpret_cast<ScrollerPeer *>(scrollerPtr));
}

/**
 * @tc.name: SetScrollOptions
 * @tc.desc: Test SetScrollOptions
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, SetScrollOptions_EmptyScroller, testing::ext::TestSize.Level1)
{
    Ark_NativePointer scrollerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ScrollerPeerImpl*>(scrollerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<ScrollPattern>();
    EXPECT_NE(pattern, nullptr);

    Ark_Scroller arkScroller;
    arkScroller.ptr = scrollerPtr;
    Opt_Scroller scroller = Converter::ArkValue<Opt_Scroller>(Ark_Empty());
    modifier_->setScrollOptions(node_, &scroller);

    RefPtr<ScrollControllerBase> positionController = pattern->GetOrCreatePositionController();
    EXPECT_NE(positionController, nullptr);
    RefPtr<ScrollProxy> scrollBarProxy = pattern->GetScrollBarProxy();
    EXPECT_NE(scrollBarProxy, nullptr);

    EXPECT_NE(peerImplPtr->GetController(), positionController);
    EXPECT_NE(peerImplPtr->GetScrollBarProxy(), scrollBarProxy);

    Ark_NativePointer finalizerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(reinterpret_cast<ScrollerPeer *>(scrollerPtr));
}

/**
 * @tc.name: NestedScroll_SetNestedScrollOption
 * @tc.desc: Test NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, NestedScroll_SetNestedScrollOption, testing::ext::TestSize.Level1)
{
    auto testVal1 = NestedScrollMode::SELF_FIRST;
    auto testVal2 = NestedScrollMode::PARALLEL;
    Ark_NestedScrollOptions options = {
        .scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(testVal1),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(testVal2)
    };

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    modifier_->setNestedScroll(node_, &options);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    auto forward = GetAttrValue<std::string>(nestedScroll, "scrollForward");
    auto backward = GetAttrValue<std::string>(nestedScroll, "scrollBackward");
    ASSERT_EQ(std::string("NestedScrollMode.SELF_FIRST"), forward);
    ASSERT_EQ(std::string("NestedScrollMode.PARALLEL"), backward);
}

/**
 * @tc.name: NestedScroll_SetDefectiveNestedScrollOptions
 * @tc.desc: Test NestedScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, NestedScroll_SetDefectiveNestedScrollOptions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto nestedScroll = json->GetObject("nestedScroll");
    ASSERT_TRUE(nestedScroll);
    auto forwardBefore = GetAttrValue<std::string>(nestedScroll, "scrollForward");
    auto backwardBefore = GetAttrValue<std::string>(nestedScroll, "scrollBackward");

    NestedScrollMode testVal1 = static_cast<NestedScrollMode>(
        static_cast<int>(NestedScrollMode::SELF_ONLY) - 1
    );
    NestedScrollMode testVal2 = static_cast<NestedScrollMode>(
        static_cast<int>(NestedScrollMode::PARALLEL) + 2
    );
    Ark_NestedScrollOptions options = {
        .scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(testVal1),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(testVal2)
    };
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
    ASSERT_EQ(forwardBefore, GetAttrValue<std::string>(nestedScroll, "scrollForward"));
    ASSERT_EQ(backwardBefore, GetAttrValue<std::string>(nestedScroll, "scrollBackward"));
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::vector<int> testSet{1,2,3,4};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    Ark_ScrollSnapOptions newOpt = {
        .enableSnapToStart = {.tag = ARK_TAG_INT32, .value = Converter::ArkValue<Ark_Boolean>(false)},
        .enableSnapToEnd = {.tag = ARK_TAG_FLOAT32, .value = Converter::ArkValue<Ark_Boolean>(true)},
        .snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_CENTER,
        .snapPagination = createSnapSet(arrayHolder)
    };
    modifier_->setScrollSnap(node_, &newOpt);

    auto state = GetJsonValue(node_);
    ASSERT_TRUE(state);
    auto scrollSnap = state->GetObject("scrollSnap");
    ASSERT_TRUE(scrollSnap);
    auto enableSnapToEnd = GetAttrValue<std::optional<bool>>(scrollSnap, "enableSnapToEnd");
    ASSERT_TRUE(enableSnapToEnd);
    ASSERT_TRUE(enableSnapToEnd.value());
    auto enableSnapToStart = GetAttrValue<std::optional<bool>>(scrollSnap, "enableSnapToStart");
    ASSERT_TRUE(enableSnapToStart);
    ASSERT_FALSE(enableSnapToStart.value());
    auto snapPagination = scrollSnap->GetValue("snapPagination");
    ASSERT_TRUE(snapPagination);
    ASSERT_TRUE(snapPagination->IsArray());
    ASSERT_EQ(4, snapPagination->GetArraySize());
    for(int i = 0; i < snapPagination->GetArraySize(); ++i)
    {
        auto arrayItem = snapPagination->GetArrayItem(i);
        auto dimVal = Converter::OptConvert<Dimension>(arrayHolder.ArkValue().array[i]);
        ASSERT_TRUE(arrayItem);
        ASSERT_EQ(dimVal.value().ToString(), arrayItem->GetString());
    }
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions_setSnapAlignOption
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setSnapAlignOption, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto snapAlign = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign.NONE"), snapAlign);

    auto intervalLen = Converter::ArkValue<Ark_Length>(1234);
    auto interval = Converter::ArkUnion<Ark_Union_Dimension_Array_Dimension, Ark_Length>(intervalLen);
    Ark_ScrollSnapOptions newOpt = {
        .enableSnapToStart = {.tag = ARK_TAG_INT32, .value = Converter::ArkValue<Ark_Boolean>(false)},
        .enableSnapToEnd = {.tag = ARK_TAG_FLOAT32, .value = Converter::ArkValue<Ark_Boolean>(true)},
        .snapPagination = Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(interval)
    };
    newOpt.snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_END;
    modifier_->setScrollSnap(node_, &newOpt);

    snapAlign = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign::END"), snapAlign); // looks like a bug in components

    newOpt.snapAlign = Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_START;
    modifier_->setScrollSnap(node_, &newOpt);

    snapAlign = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(std::string("ScrollSnapAlign.START"), snapAlign);
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions_setBadSnapAlignOption
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setBadSnapAlignOption, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto snapAlignBefore = GetStringAttribute(node_, "scrollSnapAlign");

    Ark_ScrollSnapOptions newOpt;
    newOpt.snapAlign = static_cast<Ark_ScrollSnapAlign>(
        static_cast<int>(Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_NONE) - 1
    );
    modifier_->setScrollSnap(node_, &newOpt);

    auto snapAlignAfter = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(snapAlignBefore, snapAlignAfter);

    newOpt.snapAlign = static_cast<Ark_ScrollSnapAlign>(
        static_cast<int>(Ark_ScrollSnapAlign::ARK_SCROLL_SNAP_ALIGN_END) + 1
    );
    modifier_->setScrollSnap(node_, &newOpt);

    snapAlignAfter = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(snapAlignBefore, snapAlignAfter);
}


/**
 * @tc.name: ScrollSnap_SetSnapOptions_setIntervalSize
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setIntervalSize, testing::ext::TestSize.Level1)
{

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto intervalLen = Converter::ArkValue<Ark_Length>(1234);
    auto interval = Converter::ArkUnion<Ark_Union_Dimension_Array_Dimension, Ark_Length>(intervalLen);
    Ark_ScrollSnapOptions newOpt = {
        .snapPagination = Converter::ArkValue<Opt_Union_Dimension_Array_Dimension>(interval)
    };
    modifier_->setScrollSnap(node_, &newOpt);

    auto dim = Converter::OptConvert<Dimension>(intervalLen);
    ASSERT_TRUE(dim);
    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    ASSERT_EQ(dim.value().ToString(), GetAttrValue<std::string>(scrollSnap, "snapPagination"));
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions_setArrayOfPositions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setArrayOfPositions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::vector<int> testSet{10, 45, 6, 9};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    Ark_ScrollSnapOptions newOpt = {
        .snapPagination = createSnapSet(arrayHolder)
    };
    modifier_->setScrollSnap(node_, &newOpt);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto snapPagination = scrollSnap->GetValue("snapPagination");
    ASSERT_TRUE(snapPagination->IsArray());
    for (int32_t i = 0; i < snapPagination->GetArraySize(); ++i)
    {
        auto arrayItem = snapPagination->GetArrayItem(i);
        auto dimVal = Converter::OptConvert<Dimension>(arrayHolder.ArkValue().array[i]);
        ASSERT_TRUE(arrayItem);
        ASSERT_EQ(dimVal.value().ToString(), arrayItem->GetString());
    }
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions_setEmptyArrayOfPositions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setEmptyArrayOfPositions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    // set up some initial, non default state
    std::vector<int> testSet{10, 45, 6, 9};
    Converter::ArkArrayHolder<Array_Dimension> arrayHolder(testSet);

    Ark_ScrollSnapOptions opt = {
        .snapPagination = createSnapSet(arrayHolder),
        .enableSnapToStart = {.tag = ARK_TAG_INT32, .value = Converter::ArkValue<Ark_Boolean>(false)}
    };
    modifier_->setScrollSnap(node_, &opt);

    auto jsonBefore = GetJsonValue(node_);
    ASSERT_TRUE(jsonBefore);

    std::vector<int> emptySet;
    Converter::ArkArrayHolder<Array_Dimension> emptyArrayHolder(emptySet);
    Ark_ScrollSnapOptions newOpt = {
        .snapPagination = createSnapSet(emptyArrayHolder),
        .enableSnapToStart = {.tag = ARK_TAG_INT32, .value = Converter::ArkValue<Ark_Boolean>(true)}
    };
    modifier_->setScrollSnap(node_, &newOpt);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(jsonBefore);
    auto snapAlignAfter = GetStringAttribute(node_, "scrollSnapAlign");
    ASSERT_EQ(snapAlignAfter, GetAttrValue<std::string>(jsonBefore, "scrollSnapAlign"));

    auto scrollSnapBefore = jsonBefore->GetObject("scrollSnap");
    ASSERT_TRUE(scrollSnapBefore);
    auto scrollSnapAfter = jsonBefore->GetObject("scrollSnap");
    ASSERT_EQ(GetAttrValue<bool>(scrollSnapBefore, "enableSnapToStart"), GetAttrValue<bool>(scrollSnapAfter, "enableSnapToStart"));

    auto snapPaginationBefore = scrollSnapBefore->GetValue("snapPagination");
    ASSERT_TRUE(snapPaginationBefore->IsArray());
    auto snapPaginationAfter = scrollSnapAfter->GetValue("snapPagination");
    ASSERT_TRUE(snapPaginationAfter->IsArray());
    ASSERT_EQ(snapPaginationBefore->GetArraySize(), snapPaginationAfter->GetArraySize());
    for (int32_t i = 0; i < snapPaginationBefore->GetArraySize(); ++i)
    {
        ASSERT_EQ(snapPaginationBefore->GetArrayItem(i)->GetString(), snapPaginationAfter->GetArrayItem(i)->GetString());
    }
}

/**
 * @tc.name: ScrollSnap_SetSnapOptions_setNullSnapSet
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetSnapOptions_setNullSnapSet, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    auto scrollSnap = json->GetObject("scrollSnap");
    auto scrollSnapBefore = GetAttrValue<std::string>(scrollSnap, "snapPagination");

    Ark_ScrollSnapOptions newOpt;
    newOpt.snapPagination = createEmptySnapSet();
    modifier_->setScrollSnap(node_, &newOpt);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    scrollSnap = json->GetObject("scrollSnap");
    auto scrollSnapAfter = GetAttrValue<std::string>(scrollSnap, "snapPagination");
    ASSERT_EQ(scrollSnapBefore, scrollSnapAfter);
}

/**
 * @tc.name: ScrollSnap_SetVoidSnapOptions
 * @tc.desc: Test ScrollSnapImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollSnap_SetVoidSnapOptions, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

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
    ASSERT_EQ(enableSnapToStartBefore, enableSnapToStartAfter);
    ASSERT_EQ(enableSnapToEndBefore, enableSnapToEndAfter);
    ASSERT_EQ(scrollSnapBefore, scrollSnapAfter);
    ASSERT_EQ(scrollSnapAlignBefore, scrollSnapAlignAfter);
}

/**
 * @tc.name: EnableScrollInteraction_setValue
 * @tc.desc: Test EnableScrollInteractionImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, EnableScrollInteraction_setValue, testing::ext::TestSize.Level1)
{
    modifier_->setEnableScrollInteraction(node_, Converter::ArkValue<Ark_Boolean>(true));
    auto root = GetJsonValue(node_);
    EXPECT_TRUE(root);
    auto enable = GetAttrValue<std::optional<bool>>(root, "enableScrollInteraction");
    EXPECT_TRUE(enable.has_value());
    EXPECT_TRUE(enable.value());

    modifier_->setEnableScrollInteraction(node_, Converter::ArkValue<Ark_Boolean>(false));
    root = GetJsonValue(node_);
    EXPECT_TRUE(root);
    enable = GetAttrValue<std::optional<bool>>(root, "enableScrollInteraction");
    EXPECT_TRUE(enable.has_value());
    EXPECT_FALSE(enable.value());
}

} // namespace OHOS::Ace::NG
