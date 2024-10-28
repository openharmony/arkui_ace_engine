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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    Ark_ScrollDirection direction = static_cast<Ark_ScrollDirection>(Axis::FREE);
    modifier_->setScrollable(frameNode, direction);

    auto json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    // json has 2 values with the key "scrollable" one is boolean and one is string (we need the later one)
    std::string afterState;
    for (auto object = json->GetChild(); object->IsValid(); object = object->GetNext()) {
        if (object->IsString() && object->GetKey() == "scrollable") {
            afterState = object->GetString();
        }
    }
    ASSERT_EQ("ScrollDirection.Free", afterState);
}

/**
 * @tc.name: Scrollable_SetBadDirectionOnSlide
 * @tc.desc: Test ScrollableImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Scrollable_SetBadDirectionOnSlide, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollable";
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto beforeState = GetStringAttribute(node_, jsonKey);

    Ark_ScrollDirection direction = static_cast<Ark_ScrollDirection>(static_cast<int>(Axis::VERTICAL) - 1);
    modifier_->setScrollable(frameNode, direction);
    auto afterState = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(beforeState, afterState);

    direction = static_cast<Ark_ScrollDirection>(static_cast<int>(Axis::NONE) + 1);
    modifier_->setScrollable(frameNode, direction);
    afterState = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(beforeState, afterState);
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
 * @tc.name: OnDidScroll_SetCallback
 * @tc.desc: Test OnDidScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnDidScroll_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetOnDidScrollEvent());
    
    struct ScrollData
    {
        Ark_Number x;
        Ark_Number y;
        Ark_ScrollState state;
        Ark_Int32  nodeId;
    };
    static std::optional<ScrollData> data;
    EventsTracker::eventsReceiver.onDidScroll = [] (Ark_Int32 nodeId, Ark_Number x, Ark_Number y, Ark_ScrollState state)
    {
        data = {x, y, state, nodeId};
    };

    modifier_->setOnDidScroll(node_, func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetOnDidScrollEvent());

    
    Dimension x(5.0, DimensionUnit::VP);
    Dimension y(918.0, DimensionUnit::VP);
    eventHub->GetOnDidScrollEvent()(x, y, ScrollState::IDLE);
    ASSERT_TRUE(data);
    ASSERT_EQ(x.Value(), data->x.f32);
    ASSERT_EQ(y.Value(), data->y.f32);
    ASSERT_EQ(Ark_ScrollState::ARK_SCROLL_STATE_IDLE, data->state);
}

/**
 * @tc.name: OnScrollEdge_SetCallback
 * @tc.desc: Test OnScrollEdgeImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollEdge_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ASSERT_FALSE(eventHub->GetScrollEdgeEvent());

    struct ScrollEdgeState {
        Ark_Int32 nodeId;
        Ark_Edge edge;
    };
    static std::optional<ScrollEdgeState> state;
    EventsTracker::eventsReceiver.onScrollEdge = [] (Ark_Int32 nodeId, Ark_Edge edge)
    {
        state = {nodeId, edge};
    };

    modifier_->setOnScrollEdge(node_, func);
    ASSERT_NE(eventHub, nullptr);
    ASSERT_TRUE(eventHub->GetScrollEdgeEvent());

    auto value = OHOS::Ace::NG::ScrollEdge::LEFT;
    eventHub->GetScrollEdgeEvent()(value);
    ASSERT_TRUE(state.has_value());
    ASSERT_EQ(Ark_Edge::ARK_EDGE_TOP, state->edge);
    ASSERT_EQ(frameNode->GetId(), state->nodeId);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto testState = Converter::ArkValue<Ark_BarState>(DisplayMode::OFF);
    modifier_->setScrollBar(frameNode, testState);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto beforeState = GetStringAttribute(node_, jsonKey);

    Ark_BarState testState = static_cast<Ark_BarState>(INT_MIN);
    modifier_->setScrollBar(frameNode, testState);
    auto afterState = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(beforeState, afterState);

    testState = static_cast<Ark_BarState>(INT_MAX);
    modifier_->setScrollBar(frameNode, testState);
    afterState = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(beforeState, afterState);
}

/**
 * @tc.name: ScrollBarColor_SetColorString
 * @tc.desc: Test OnScrollBarColorImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarColor_SetColorString, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    std::string testColor = "#11123456";
    Ark_String str = Converter::ArkValue<Ark_String>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(frameNode, &colorUnion);

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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    int32_t testColor = 0xff008000;
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(Ark_Color::ARK_COLOR_GREEN);
    modifier_->setScrollBarColor(frameNode, &colorUnion);

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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    float testColor = 286405718.0;
    auto testNumber = Converter::ArkValue<Ark_Number>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(testNumber);
    modifier_->setScrollBarColor(frameNode, &colorUnion);

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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    std::string before = "#FF000000";

    // empty color string
    std::string testColor = "";
    Ark_String str = Converter::ArkValue<Ark_String>(testColor);
    auto colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(frameNode, &colorUnion);
    auto after = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(before, after);
    // nullptr to data
    str = {.length = 12334, .chars = nullptr};
    colorUnion = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>(str);
    modifier_->setScrollBarColor(frameNode, &colorUnion);
    after = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(before, after);
    // nullptr value
    modifier_->setScrollBarColor(frameNode, nullptr);
    after = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(before, after);
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

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    modifier_->setScrollBarWidth(frameNode, &arkVal);

    auto setVal = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(setVal, testValue.ToString());

    auto strVal = std::string("222.99px");
    auto testStr = Converter::ArkValue<Ark_String>(strVal.data());
    arkVal = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(testStr);
    modifier_->setScrollBarWidth(frameNode, &arkVal);

    setVal = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(setVal, strVal);
}

/**
 * @tc.name: ScrollModifierTest012
 * @tc.desc: Test OnScrollBarWidthImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, ScrollBarWidth_SetDefectiveWidth, testing::ext::TestSize.Level1)
{
    std::string jsonKey = "scrollBarWidth";
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    auto defaultVal = GetStringAttribute(node_, jsonKey);
    Dimension defaultValDim = Dimension::FromString(defaultVal);

    modifier_->setScrollBarWidth(frameNode, nullptr);

    auto testVal = GetStringAttribute(node_, jsonKey);
    ASSERT_EQ(testVal, defaultVal);

    Ark_Number num = {.tag = ARK_TAG_UNDEFINED};
    auto defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(num);
    modifier_->setScrollBarWidth(frameNode, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    Dimension testValDim = Dimension::FromString(testVal);
    ASSERT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    Ark_String str = {.length = 0, .chars = 0};
    auto emptyString = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(str);
    modifier_->setScrollBarWidth(frameNode, &emptyString);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    ASSERT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    auto testNumber = Converter::ArkValue<Ark_Number>(-1.0f);
    defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(testNumber);
    modifier_->setScrollBarWidth(frameNode, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    ASSERT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());

    auto testStr = Converter::ArkValue<Ark_String>("33%");
    defectiveNumber = Converter::ArkUnion<Ark_Union_Number_String, Ark_String>(testStr);
    modifier_->setScrollBarWidth(frameNode, &defectiveNumber);

    testVal = GetStringAttribute(node_, jsonKey);
    testValDim = Dimension::FromString(testVal);
    ASSERT_EQ(testValDim.ConvertToVp(), defaultValDim.ConvertToVp());
}

/**
 * @tc.name: Friction_SetNullValue
 * @tc.desc: Test FrictionImpl attempt to set a null value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, Friction_SetNullValue, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

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
HWTEST_F(ScrollModifierTest, DISABLED_EnablePaging_SetValues, testing::ext::TestSize.Level1)
{
    // enablePaging is initially hidden in JSON
    auto root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    auto enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_FALSE(enablePaging.has_value());

    modifier_->setEnablePaging(node_, 1);
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    ASSERT_TRUE(enablePaging.value());

    modifier_->setEnablePaging(node_, 0);
    root = GetJsonValue(node_);
    ASSERT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    ASSERT_TRUE(enablePaging.has_value());
    ASSERT_FALSE(enablePaging.value());
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

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    modifier_->setEdgeEffect(node_, effect, &options);

    ASSERT_EQ("EdgeEffect.Fade", GetStringAttribute(node_, "edgeEffect"));

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    ASSERT_EQ(testVal1, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
}

/**
 * @tc.name: EdgeEffect_SetBadValues
 * @tc.desc: Test EdgeEffectImpl
 * @tc.type: FUNC
 */

HWTEST_F(ScrollModifierTest, EdgeEffect_SetBadValues, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
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
    ASSERT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    ASSERT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));

    effect = static_cast<Ark_EdgeEffect>(INT_MIN);
    modifier_->setEdgeEffect(node_, effect, &options);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    ASSERT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    ASSERT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));

    modifier_->setEdgeEffect(node_, effect, nullptr);

    json = GetJsonValue(node_);
    ASSERT_TRUE(json);
    edgeEffectOptions = json->GetValue("edgeEffectOptions");
    ASSERT_TRUE(edgeEffectOptions);
    ASSERT_EQ(defaultAlways, GetAttrValue<bool>(edgeEffectOptions, "alwaysEnabled"));
    ASSERT_EQ(defaultEffect, GetStringAttribute(node_, "edgeEffect"));
}


} // namespace OHOS::Ace::NG