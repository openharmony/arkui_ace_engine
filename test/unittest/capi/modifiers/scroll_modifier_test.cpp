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
static Ark_Number g_xOffset;
static Ark_Number g_yOffset;
static Ark_Int32  g_scrollState;
static bool g_isBoolEventSet = false;
static Ark_Int32 g_scrollEdge = 0;
static Ark_Number g_setNumberTestValue;
static auto onScrollEvent(Ark_Int32 nodeId, const Ark_Number x, const Ark_Number y)
{
    g_xOffset = x;
    g_yOffset = y;
}
static auto onScrollFrameBegin(Ark_Int32 nodeId, const Ark_Number value1, const enum Ark_ScrollState state)
{
    g_setNumberTestValue = value1;
    g_scrollState = state;
}
static auto onScrollEdge(Ark_Int32 nodeId, const enum Ark_Edge edge)
{
    g_scrollEdge = edge;
}
static auto scrollOnBooleanEvent(Ark_Int32 nodeId)
{

    g_isBoolEventSet = !g_isBoolEventSet;
}
static auto onDidScrollEvent(Ark_Int32 nodeId, const Ark_Number x, const Ark_Number y, const enum Ark_ScrollState state)
{
    g_xOffset = x;
    g_yOffset = y;
    g_scrollState = state;
}

static GENERATED_ArkUIScrollEventsReceiver recv {
    .onScrollStart = scrollOnBooleanEvent,
    .onScrollStop = scrollOnBooleanEvent,
    .onScrollEnd = scrollOnBooleanEvent,
    .onScrollEdge = onScrollEdge,
    .onScrollFrameBegin = onScrollFrameBegin,
    .onDidScroll = onDidScrollEvent,
    .onScroll = onScrollEvent,
};
static const GENERATED_ArkUIScrollEventsReceiver* getScrollEventsReceiverTest()
{
    return &recv;
};
static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getScrollEventsReceiver = getScrollEventsReceiverTest };
    return &eventsImpl;
};

inline void AssignArkValue(Opt_Length& dst, const CalcDimension& src)
{
    if (src.Unit() == DimensionUnit::CALC)
        return;
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
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
            auto constants = RefPtr<ThemeConstants>();
            auto theme = ScrollBarTheme::Builder().Build(constants);
            return theme;
        });
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        MockContainer::SetUp();
        NG::GeneratedModifier::GetFullAPI()->setArkUIEventsAPI(GetArkUiEventsAPITest());
    }

    static void TearDownTestCase()
    {
        MockPipelineContext::GetCurrent()->SetThemeManager(nullptr);
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: OnScroll_SetCallback
 * @tc.desc: Test OnScrollImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScroll_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->GetOnScrollEvent());

    modifier_->setOnScroll(node_, func);
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetOnScrollEvent());

    Dimension x(33.0, DimensionUnit::VP);
    Dimension y(133.0, DimensionUnit::VP);
    eventHub->GetOnScrollEvent()(x, y);
    EXPECT_EQ(33.0, g_xOffset.f32);
    EXPECT_EQ(133.0, g_yOffset.f32);
}

/**
 * @tc.name: OnScrollStart_SetCallback
 * @tc.desc: Test OnScrollStartImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollStart_SetCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->GetOnScrollStart());

    modifier_->setOnScrollStart(node_, func);
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetOnScrollStart());

    g_isBoolEventSet = false;
    eventHub->GetOnScrollStart()();
    EXPECT_TRUE(g_isBoolEventSet);
}

/**
 * @tc.name: SetOnScrollEnd_SetCallBack
 * @tc.desc: Test OnScrollEndImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, SetOnScrollEnd_SetCallBack, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->GetScrollEndEvent());

    modifier_->setOnScrollEnd(node_, func);
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetScrollEndEvent());

    g_isBoolEventSet = false;
    eventHub->GetScrollEndEvent()();
    EXPECT_TRUE(g_isBoolEventSet);
}

/**
 * @tc.name: OnScrollStop_setCallback
 * @tc.desc: Test OnScrollStopImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, OnScrollStop_setCallback, testing::ext::TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    Ark_Function func = {};

    auto eventHub = frameNode->GetEventHub<NG::ScrollEventHub>();
    ASSERT_NE(eventHub, nullptr);
    EXPECT_FALSE(eventHub->GetOnScrollStop());

    modifier_->setOnScrollStop(node_, func);
    ASSERT_NE(eventHub, nullptr);
    EXPECT_TRUE(eventHub->GetOnScrollStop());

    g_isBoolEventSet = false;
    eventHub->GetOnScrollStop()();
    EXPECT_TRUE(g_isBoolEventSet);
}

/**
 * @tc.name: EnablePaging_SetValues
 * @tc.desc: Test EnablePagingImpl
 * @tc.type: FUNC
 */
HWTEST_F(ScrollModifierTest, EnablePaging_SetValues, testing::ext::TestSize.Level1)
{
    // enablePaging is initialy hidden in JSON
    auto root = GetJsonValue(node_);
    EXPECT_TRUE(root);
    auto enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    EXPECT_FALSE(enablePaging.has_value());

    modifier_->setEnablePaging(node_, 1);
    root = GetJsonValue(node_);
    EXPECT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    EXPECT_TRUE(enablePaging.has_value());
    EXPECT_TRUE(enablePaging.value());

    modifier_->setEnablePaging(node_, 0);
    root = GetJsonValue(node_);
    EXPECT_TRUE(root);
    enablePaging = GetAttrValue<std::optional<bool>>(root, "enablePaging");
    EXPECT_TRUE(enablePaging.has_value());
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
    EXPECT_EQ(xBefore, xAfter);
    EXPECT_EQ(yBefore, yAfter);
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

    EXPECT_EQ(value.GetX().ToString(), xAfter);
    EXPECT_EQ(value.GetY().ToString(), yAfter);
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
    EXPECT_EQ(xBefore, xAfter);
    EXPECT_EQ(yBefore, yAfter);
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
    EXPECT_EQ(value.GetX().ToString(), xAfter);
    EXPECT_EQ(yBefore, yAfter);
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
    EXPECT_EQ(xBefore, xAfter);
    EXPECT_EQ(value1.GetY().ToString(), yAfter);
}

} // namespace OHOS::Ace::NG
