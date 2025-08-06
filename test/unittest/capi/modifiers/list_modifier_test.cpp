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

#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/list/list_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/components_v2/list/list_properties.h"

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
inline void AssignArkValue(Ark_OnScrollFrameBeginHandlerResult& dst, const ScrollFrameResult& src,
    ConvContext *ctx)
{
    dst.offsetRemain = Converter::ArkValue<Ark_Number>(src.offset);
}
} // Converter

namespace {
const auto FRICTION_RES_NAME = "friction_res_name";
const auto FRICTION_RESOURCE = CreateResource(FRICTION_RES_NAME, Converter::ResourceType::FLOAT);
const auto FRICTION_VALUE = 1.2f;
const auto DIVIDER_COLOR_RES_NAME = "divider_color_res_name";
const auto DIVIDER_COLOR = "#08000000";
const auto DIVIDER_COLOR_RESOURCE = CreateResource(DIVIDER_COLOR_RES_NAME, Converter::ResourceType::COLOR);
const float TEST_OFFSET = 10.0f;
} // namespace

class ListModifierTest : public ModifierTestBase<GENERATED_ArkUIListModifier,
    &GENERATED_ArkUINodeModifiers::getListModifier, GENERATED_ARKUI_LIST> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<ScrollableTheme>();

        AddResource(FRICTION_RES_NAME, FRICTION_VALUE);
        AddResource(DIVIDER_COLOR_RES_NAME, Color::FromString(DIVIDER_COLOR));
    }

    void OnModifyDone()
    {
        auto frameNode = reinterpret_cast<FrameNode*>(node_);
        ASSERT_NE(frameNode, nullptr);
        auto pattern = frameNode->GetPattern();
        ASSERT_TRUE(pattern);
        pattern->OnModifyDone();
    }
};

/**
 * @tc.name: setEditModeTest
 * @tc.desc: Check the functionality of ListModifier.setEditMode
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setEditModeTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<bool>(node_, "editMode");
    EXPECT_FALSE(checkValue);
    auto optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setEditMode(node_, &optValue);
    checkValue = GetAttrValue<bool>(node_, "editMode");
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: setMultiSelectableTest
 * @tc.desc: Check the functionality of ListModifier.setMultiSelectable
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setMultiSelectableTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<bool>(node_, "multiSelectable");
    EXPECT_FALSE(checkValue);
    auto optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setMultiSelectable(node_, &optValue);
    checkValue = GetAttrValue<bool>(node_, "multiSelectable");
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: setChainAnimationTest
 * @tc.desc: Check the functionality of ListModifier.setChainAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setChainAnimationTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<bool>(node_, "chainAnimation");
    EXPECT_FALSE(checkValue);
    auto optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setChainAnimation(node_, &optValue);
    checkValue = GetAttrValue<bool>(node_, "chainAnimation");
    EXPECT_TRUE(checkValue);
}

/**
 * @tc.name: setEnableScrollInteractionTest
 * @tc.desc: Check the functionality of ListModifier.setEnableScrollInteraction
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setEnableScrollInteractionTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<bool>(node_, "enableScrollInteraction");
    EXPECT_TRUE(checkValue);
    auto optValue = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setEnableScrollInteraction(node_, &optValue);
    checkValue = GetAttrValue<bool>(node_, "enableScrollInteraction");
    EXPECT_FALSE(checkValue);
}

/**
 * @tc.name: setCachedCount0Test
 * @tc.desc: Check the functionality of ListModifier.setCachedCount0
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setCachedCount0Test, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "cachedCount");
    EXPECT_EQ(checkValue, "0");

    auto arg = Converter::ArkValue<Ark_Number>(10);
    auto optArg = Converter::ArkValue<Opt_Number>(arg);
    modifier_->setCachedCount0(node_, &optArg);
    checkValue = GetAttrValue<std::string>(node_, "cachedCount");
    EXPECT_EQ(checkValue, "10");

    arg = Converter::ArkValue<Ark_Number>(-10);
    optArg = Converter::ArkValue<Opt_Number>(arg);
    modifier_->setCachedCount0(node_, &optArg);
    checkValue = GetAttrValue<std::string>(node_, "cachedCount");
    EXPECT_EQ(checkValue, "0");
}

/**
 * @tc.name: setStickyTest
 * @tc.desc: Check the functionality of ListModifier.setSticky
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setStickyTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "StickyStyle.None");
    auto value = Converter::ArkValue<Ark_StickyStyle>(V2::StickyStyle::HEADER);
    auto optValue = Converter::ArkValue<Opt_StickyStyle>(value);
    modifier_->setSticky(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "StickyStyle.Header");

    value = Converter::ArkValue<Ark_StickyStyle>(V2::StickyStyle::NONE);
    optValue = Converter::ArkValue<Opt_StickyStyle>(value);
    modifier_->setSticky(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "StickyStyle.None");

    value = Converter::ArkValue<Ark_StickyStyle>(V2::StickyStyle::FOOTER);
    optValue = Converter::ArkValue<Opt_StickyStyle>(value);
    modifier_->setSticky(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "StickyStyle.Footer");

    value = Converter::ArkValue<Ark_StickyStyle>(static_cast<V2::StickyStyle>(-10));
    optValue = Converter::ArkValue<Opt_StickyStyle>(value);
    modifier_->setSticky(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "sticky");
    EXPECT_EQ(checkValue, "StickyStyle.None");
}

/**
 * @tc.name: setAlignListItemTest
 * @tc.desc: Check the functionality of ListModifier.setAlignListItem
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setAlignListItemTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "alignListItem");
    EXPECT_EQ(checkValue, "ListItemAlign.Start");

    auto value = Converter::ArkValue<Ark_ListItemAlign>(V2::ListItemAlign::CENTER);
    auto optValue = Converter::ArkValue<Opt_ListItemAlign>(value);
    modifier_->setAlignListItem(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "alignListItem");
    EXPECT_EQ(checkValue, "ListItemAlign.Center");

    value = Converter::ArkValue<Ark_ListItemAlign>(V2::ListItemAlign::END);
    optValue = Converter::ArkValue<Opt_ListItemAlign>(value);
    modifier_->setAlignListItem(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "alignListItem");
    EXPECT_EQ(checkValue, "ListItemAlign.End");

    value = Converter::ArkValue<Ark_ListItemAlign>(V2::ListItemAlign::START);
    optValue = Converter::ArkValue<Opt_ListItemAlign>(value);
    modifier_->setAlignListItem(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "alignListItem");
    EXPECT_EQ(checkValue, "ListItemAlign.Start");

    value = Converter::ArkValue<Ark_ListItemAlign>(static_cast<V2::ListItemAlign>(-10));
    optValue = Converter::ArkValue<Opt_ListItemAlign>(value);
    modifier_->setAlignListItem(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "alignListItem");
    EXPECT_EQ(checkValue, "ListItemAlign.Start");
}

/**
 * @tc.name: setScrollSnapAlignTest
 * @tc.desc: Check the functionality of ListModifier.setScrollSnapAlign
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setScrollSnapAlignTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.NONE");

    auto value = Converter::ArkValue<Ark_ScrollSnapAlign>(V2::ScrollSnapAlign::START);
    auto optValue = Converter::ArkValue<Opt_ScrollSnapAlign>(value);
    modifier_->setScrollSnapAlign(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.START");

    value = Converter::ArkValue<Ark_ScrollSnapAlign>(V2::ScrollSnapAlign::NONE);
    optValue = Converter::ArkValue<Opt_ScrollSnapAlign>(value);
    modifier_->setScrollSnapAlign(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.NONE");

    value = Converter::ArkValue<Ark_ScrollSnapAlign>(V2::ScrollSnapAlign::CENTER);
    optValue = Converter::ArkValue<Opt_ScrollSnapAlign>(value);
    modifier_->setScrollSnapAlign(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.CENTER");

    value = Converter::ArkValue<Ark_ScrollSnapAlign>(V2::ScrollSnapAlign::END);
    optValue = Converter::ArkValue<Opt_ScrollSnapAlign>(value);
    modifier_->setScrollSnapAlign(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.END");

    value = Converter::ArkValue<Ark_ScrollSnapAlign>(static_cast<V2::ScrollSnapAlign>(-10));
    optValue = Converter::ArkValue<Opt_ScrollSnapAlign>(value);
    modifier_->setScrollSnapAlign(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollSnapAlign");
    EXPECT_EQ(checkValue, "ScrollSnapAlign.NONE");
}

/**
 * @tc.name: setContentStartOffsetTest
 * @tc.desc: Check the functionality of ListModifier.setContentStartOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setContentStartOffsetTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_EQ(checkValue, "0.000000");

    auto intNum = Converter::ArkValue<Ark_Number>(11);
    auto optIntNum = Converter::ArkValue<Opt_Number>(intNum);
    modifier_->setContentStartOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_EQ(checkValue, "11.000000");

    auto floatNum = Converter::ArkValue<Ark_Number>(22.2f);
    auto optFloatNum = Converter::ArkValue<Opt_Number>(floatNum);
    modifier_->setContentStartOffset(node_, &optFloatNum);
    checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_THAT(checkValue, StartsWith("22.2"));

    intNum = Converter::ArkValue<Ark_Number>(-33);
    optIntNum = Converter::ArkValue<Opt_Number>(intNum);
    modifier_->setContentStartOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_THAT(checkValue, StartsWith("-33.000000"));
}

/**
 * @tc.name: setContentEndOffsetTest
 * @tc.desc: Check the functionality of ListModifier.setContentEndOffset
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setContentEndOffsetTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_EQ(checkValue, "0.000000");

    auto intNum = Converter::ArkValue<Ark_Number>(11);;
    auto optIntNum = Converter::ArkValue<Opt_Number>(intNum);
    modifier_->setContentEndOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_EQ(checkValue, "11.000000");

    auto floatNum = Converter::ArkValue<Ark_Number>(22.2f);
    auto optFloatNum = Converter::ArkValue<Opt_Number>(floatNum);
    modifier_->setContentEndOffset(node_, &optFloatNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_THAT(checkValue, StartsWith("22.2"));

    intNum = Converter::ArkValue<Ark_Number>(-55);
    optIntNum = Converter::ArkValue<Opt_Number>(intNum);
    modifier_->setContentEndOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_THAT(checkValue, StartsWith("-55"));
}

/**
 * @tc.name: setScrollBarTest
 * @tc.desc: Check the functionality of ListModifier.setScrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setScrollBarTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "scrollBar");
    EXPECT_EQ(checkValue, "BarState.Auto");

    auto value = Converter::ArkValue<Ark_BarState>(DisplayMode::ON);
    auto optValue = Converter::ArkValue<Opt_BarState>(value);
    modifier_->setScrollBar(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollBar");
    EXPECT_EQ(checkValue, "BarState.On");

    value = Converter::ArkValue<Ark_BarState>(DisplayMode::OFF);
    optValue = Converter::ArkValue<Opt_BarState>(value);
    modifier_->setScrollBar(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollBar");
    EXPECT_EQ(checkValue, "BarState.Off");

    value = Converter::ArkValue<Ark_BarState>(DisplayMode::AUTO);
    optValue = Converter::ArkValue<Opt_BarState>(value);
    modifier_->setScrollBar(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollBar");
    EXPECT_EQ(checkValue, "BarState.Auto");

    value = Converter::ArkValue<Ark_BarState>(static_cast<DisplayMode>(-10));
    optValue = Converter::ArkValue<Opt_BarState>(value);
    modifier_->setScrollBar(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "scrollBar");
    EXPECT_EQ(checkValue, "BarState.Auto");
}

/**
 * @tc.name: setListDirectionTest
 * @tc.desc: Check the functionality of ListModifier.setListDirection
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setListDirectionTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "listDirection");
    EXPECT_EQ(checkValue, "Axis.Vertical");

    auto value = Converter::ArkValue<Ark_Axis>(Converter::ArkValue<Ark_Axis>(Axis::HORIZONTAL));
    auto optValue = Converter::ArkValue<Opt_Axis>(value);
    modifier_->setListDirection(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "listDirection");
    EXPECT_EQ(checkValue, "Axis.Horizontal");

    value = Converter::ArkValue<Ark_Axis>(Converter::ArkValue<Ark_Axis>(Axis::VERTICAL));
    optValue = Converter::ArkValue<Opt_Axis>(value);
    modifier_->setListDirection(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "listDirection");
    EXPECT_EQ(checkValue, "Axis.Vertical");

    value = Converter::ArkValue<Ark_Axis>(Converter::ArkValue<Ark_Axis>(static_cast<Axis>(-10)));
    optValue = Converter::ArkValue<Opt_Axis>(value);
    modifier_->setListDirection(node_, &optValue);
    checkValue = GetAttrValue<std::string>(node_, "listDirection");
    EXPECT_EQ(checkValue, "Axis.Vertical");
}

/**
 * @tc.name: setListOptionsTest
 * @tc.desc: Check the functionality of ListModifier.setListOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setListOptionsTest, TestSize.Level1)
{
    auto indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "0");
    auto spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "0.00vp");

    Ark_ListOptions listOptions = {
        .initialIndex = Converter::ArkValue<Opt_Number>(1),
        .space = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(55.7f),
        .scroller = Converter::ArkValue<Opt_Scroller>(Ark_Scroller{nullptr}),
    };

    Opt_ListOptions options = Converter::ArkValue<Opt_ListOptions>(listOptions);
    modifier_->setListOptions(node_, &options);
    indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "1");
    spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "55.70vp");

    // options are undefined
    options = Converter::ArkValue<Opt_ListOptions>(Ark_Empty());
    modifier_->setListOptions(node_, &options);
    indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "1");
    spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "55.70vp");

    // index, space are undefined
    listOptions = {
        .initialIndex = Converter::ArkValue<Opt_Number>(Ark_Empty()),
        .space = Converter::ArkValue<Opt_Union_Number_String>(Ark_Empty()),
        .scroller = Converter::ArkValue<Opt_Scroller>(Ark_Scroller{nullptr}),
    };
    options = Converter::ArkValue<Opt_ListOptions>(listOptions);
    modifier_->setListOptions(node_, &options);
    indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "0");
    spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "0.00vp");

    // space as string
    listOptions = {
        .initialIndex = Converter::ArkValue<Opt_Number>(3),
        .space = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>("88.9px"),
        .scroller = Converter::ArkValue<Opt_Scroller>(Ark_Scroller{nullptr}),
    };
    options = Converter::ArkValue<Opt_ListOptions>(listOptions);
    modifier_->setListOptions(node_, &options);
    indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "3");
    spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "88.90px");
}

/**
 * @tc.name: setListOptionsNegativeTest
 * @tc.desc: Check the functionality of ListModifier.setListOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setListOptionsNegativeTest, TestSize.Level1)
{
// space and index are negative
    Ark_ListOptions listOptions = {
        .initialIndex = Converter::ArkValue<Opt_Number>(-7),
        .space = Converter::ArkUnion<Opt_Union_Number_String, Ark_Number>(-9),
        .scroller = Converter::ArkValue<Opt_Scroller>(Ark_Scroller{nullptr}),
    };
    Opt_ListOptions options = Converter::ArkValue<Opt_ListOptions>(listOptions);
    modifier_->setListOptions(node_, &options);
    auto indexCheckValue = GetAttrValue<std::string>(node_, "initialIndex");
    EXPECT_EQ(indexCheckValue, "-7");
    auto spaceCheckValue = GetAttrValue<std::string>(node_, "space");
    EXPECT_EQ(spaceCheckValue, "-9.00vp");
}

/**
 * @tc.name: setLanesTest
 * @tc.desc: Check the functionality of ListModifier.setLanes
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setLanesTest, TestSize.Level1)
{
    // default values
    auto lanesCheckValue = GetAttrValue<std::string>(node_, "lanes");
    EXPECT_EQ(lanesCheckValue, "0");
    auto laneMinLengthCheckValue = GetAttrValue<std::string>(node_, "laneMinLength");
    EXPECT_EQ(laneMinLengthCheckValue, "0.00vp");
    auto laneMaxLengthCheckValue = GetAttrValue<std::string>(node_, "laneMaxLength");
    EXPECT_EQ(laneMaxLengthCheckValue, "0.00vp");
    auto gutterCheckValue = GetAttrValue<std::string>(node_, "laneGutter");
    EXPECT_EQ(gutterCheckValue, "0.00vp");

    // lanes, gutter are valid
    Ark_Union_Number_LengthConstrain value =  Converter::ArkUnion<Ark_Union_Number_LengthConstrain, Ark_Number>(2);
    auto optValue = Converter::ArkValue<Opt_Union_Number_LengthConstrain>(value);
    Opt_Dimension gutterOpt = Converter::ArkValue<Opt_Dimension>(Converter::ArkValue<Ark_Length>(55.5f));
    modifier_->setLanes(node_, &optValue, &gutterOpt);
    lanesCheckValue = GetAttrValue<std::string>(node_, "lanes");
    EXPECT_EQ(lanesCheckValue, "2");
    laneMinLengthCheckValue = GetAttrValue<std::string>(node_, "laneMinLength");
    EXPECT_EQ(laneMinLengthCheckValue, "0.00vp");
    laneMaxLengthCheckValue = GetAttrValue<std::string>(node_, "laneMaxLength");
    EXPECT_EQ(laneMaxLengthCheckValue, "0.00vp");
    gutterCheckValue = GetAttrValue<std::string>(node_, "laneGutter");
    EXPECT_EQ(gutterCheckValue, "55.50vp");

    // gutter as optional
    gutterOpt = Converter::ArkValue<Opt_Dimension>(Ark_Empty());
    modifier_->setLanes(node_, &optValue, &gutterOpt);
    gutterCheckValue = GetAttrValue<std::string>(node_, "laneGutter");
    EXPECT_EQ(gutterCheckValue, "55.50vp");

    // lanes as constraints
    Ark_LengthConstrain constraint = {
        .minLength = {.value = Converter::ArkValue<Ark_Int32>(11), .unit = Converter::ArkValue<Ark_Int32>(2)},
        .maxLength = {.value = Converter::ArkValue<Ark_Float32>(77.7f)}};
    value = Converter::ArkUnion<Ark_Union_Number_LengthConstrain, Ark_LengthConstrain>(constraint);
    optValue = Converter::ArkValue<Opt_Union_Number_LengthConstrain>(value);
    modifier_->setLanes(node_, &optValue, &gutterOpt);
    lanesCheckValue = GetAttrValue<std::string>(node_, "lanes");
    EXPECT_EQ(lanesCheckValue, "1");
    laneMinLengthCheckValue = GetAttrValue<std::string>(node_, "laneMinLength");
    EXPECT_EQ(laneMinLengthCheckValue, "11.00fp");
    laneMaxLengthCheckValue = GetAttrValue<std::string>(node_, "laneMaxLength");
    EXPECT_EQ(laneMaxLengthCheckValue, "77.70px");
}

/**
 * @tc.name: setLanesNegativeTest
 * @tc.desc: Check the functionality of ListModifier.setLanes
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setLanesNegativeTest, TestSize.Level1)
{
    // lanes, gutter are negative
    Ark_Union_Number_LengthConstrain value = Converter::ArkUnion<Ark_Union_Number_LengthConstrain, Ark_Number>(-2);
    auto optValue = Converter::ArkValue<Opt_Union_Number_LengthConstrain>(value);
    Opt_Dimension gutterOpt = Converter::ArkValue<Opt_Dimension>(Converter::ArkValue<Ark_Length>(-88._px));
    modifier_->setLanes(node_, &optValue, &gutterOpt);
    auto lanesCheckValue = GetAttrValue<std::string>(node_, "lanes");
    EXPECT_EQ(lanesCheckValue, "-2");
    auto laneMinLengthCheckValue = GetAttrValue<std::string>(node_, "laneMinLength");
    EXPECT_EQ(laneMinLengthCheckValue, "0.00vp");
    auto laneMaxLengthCheckValue = GetAttrValue<std::string>(node_, "laneMaxLength");
    EXPECT_EQ(laneMaxLengthCheckValue, "0.00vp");
    auto gutterCheckValue = GetAttrValue<std::string>(node_, "laneGutter");
    EXPECT_EQ(gutterCheckValue, "-88.00px");
}

/**
 * @tc.name: setEdgeEffectTest
 * @tc.desc: Check the functionality of ListModifier.setEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setEdgeEffectTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto edgeEffectCheckValue = GetAttrValue<std::string>(node_, "edgeEffect");
    EXPECT_EQ(edgeEffectCheckValue, "EdgeEffect.Spring");

    auto edgeEffectOptionsObject =  GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "edgeEffectOptions");
    auto edgeEffectOptionsCheckValue = GetAttrValue<bool>(edgeEffectOptionsObject, "alwaysEnabled");
    EXPECT_EQ(edgeEffectOptionsCheckValue, false);

    // set edgeEffect and options
    Opt_EdgeEffectOptions options =
    Converter::ArkValue<Opt_EdgeEffectOptions>(Converter::ArkValue<Ark_Boolean>(true));
    auto value = Converter::ArkValue<Ark_EdgeEffect>(Converter::ArkValue<Ark_EdgeEffect>(EdgeEffect::FADE));
    auto optValue = Converter::ArkValue<Opt_EdgeEffect>(value);
    modifier_->setEdgeEffect(node_, &optValue, &options);
    fullJson = GetJsonValue(node_);
    edgeEffectCheckValue = GetAttrValue<std::string>(node_, "edgeEffect");
    EXPECT_EQ(edgeEffectCheckValue, "EdgeEffect.Fade");
    edgeEffectOptionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "edgeEffectOptions");
    edgeEffectOptionsCheckValue = GetAttrValue<bool>(edgeEffectOptionsObject, "alwaysEnabled");
    EXPECT_EQ(edgeEffectOptionsCheckValue, true);

    // alwaysEnabled is undefined
    options = Converter::ArkValue<Opt_EdgeEffectOptions>(Ark_Empty());
    value = Converter::ArkValue<Ark_EdgeEffect>(Converter::ArkValue<Ark_EdgeEffect>(EdgeEffect::NONE));
    optValue = Converter::ArkValue<Opt_EdgeEffect>(value);
    modifier_->setEdgeEffect(node_, &optValue, &options);
    fullJson = GetJsonValue(node_);
    edgeEffectCheckValue = GetAttrValue<std::string>(node_, "edgeEffect");
    EXPECT_EQ(edgeEffectCheckValue, "EdgeEffect.None");
    edgeEffectOptionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "edgeEffectOptions");
    edgeEffectOptionsCheckValue = GetAttrValue<bool>(edgeEffectOptionsObject, "alwaysEnabled");
    EXPECT_EQ(edgeEffectOptionsCheckValue, false);

    // set invalid edgeEffect
    options = Converter::ArkValue<Opt_EdgeEffectOptions>(Converter::ArkValue<Ark_Boolean>(true));
    value = Converter::ArkValue<Ark_EdgeEffect>(Converter::ArkValue<Ark_EdgeEffect>(static_cast<EdgeEffect>(-10)));
    optValue = Converter::ArkValue<Opt_EdgeEffect>(value);
    modifier_->setEdgeEffect(node_, &optValue, &options);
    fullJson = GetJsonValue(node_);
    edgeEffectCheckValue = GetAttrValue<std::string>(node_, "edgeEffect");
    EXPECT_EQ(edgeEffectCheckValue, "EdgeEffect.Spring");
    edgeEffectOptionsObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "edgeEffectOptions");
    edgeEffectOptionsCheckValue = GetAttrValue<bool>(edgeEffectOptionsObject, "alwaysEnabled");
    EXPECT_EQ(edgeEffectOptionsCheckValue, true);
}

/**
 * @tc.name: setNestedScrollTest
 * @tc.desc: Check the functionality of ListModifier.setNestedScroll
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setNestedScrollTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto nestedScrollObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "nestedScroll");
    auto scrollForwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollForward");
    EXPECT_EQ(scrollForwardCheckValue, "NestedScrollMode.SELF_ONLY");
    auto scrollBackwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollBackward");
    EXPECT_EQ(scrollBackwardCheckValue, "NestedScrollMode.SELF_ONLY");

    // set valid values
    Ark_NestedScrollOptions options = {
        .scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(NestedScrollMode::PARENT_FIRST),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(NestedScrollMode::PARALLEL)};
    auto optOptions = Converter::ArkValue<Opt_NestedScrollOptions>(options);
    modifier_->setNestedScroll(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    nestedScrollObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "nestedScroll");
    scrollForwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollForward");
    EXPECT_EQ(scrollForwardCheckValue, "NestedScrollMode.PARENT_FIRST");
    scrollBackwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollBackward");
    EXPECT_EQ(scrollBackwardCheckValue, "NestedScrollMode.PARALLEL");

    options = {.scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(NestedScrollMode::SELF_ONLY),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(NestedScrollMode::SELF_FIRST)};
    optOptions = Converter::ArkValue<Opt_NestedScrollOptions>(options);
    modifier_->setNestedScroll(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    nestedScrollObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "nestedScroll");
    scrollForwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollForward");
    EXPECT_EQ(scrollForwardCheckValue, "NestedScrollMode.SELF_ONLY");
    scrollBackwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollBackward");
    EXPECT_EQ(scrollBackwardCheckValue, "NestedScrollMode.SELF_FIRST");

    // set negative values
    options = {.scrollForward = Converter::ArkValue<Ark_NestedScrollMode>(static_cast<NestedScrollMode>(-88)),
        .scrollBackward = Converter::ArkValue<Ark_NestedScrollMode>(static_cast<NestedScrollMode>(-99))};
    optOptions = Converter::ArkValue<Opt_NestedScrollOptions>(options);
    modifier_->setNestedScroll(node_, &optOptions);
    fullJson = GetJsonValue(node_);
    nestedScrollObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "nestedScroll");
    scrollForwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollForward");
    EXPECT_EQ(scrollForwardCheckValue, "NestedScrollMode.SELF_ONLY");
    scrollBackwardCheckValue = GetAttrValue<std::string>(nestedScrollObject, "scrollBackward");
    EXPECT_EQ(scrollBackwardCheckValue, "NestedScrollMode.SELF_ONLY");
}

/**
 * @tc.name: setDividerTest
 * @tc.desc: Check the functionality of ListModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setDividerTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "{}");

    // set valid values, color as Ark_Color aka int
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11._px),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77._px)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Color>(ARK_COLOR_WHITE),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "55.50vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "77.00px");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FFFFFFFF");

    // set color as Ark_Number
    dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11._px),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77._px)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_Number>(0x123456),
    };
    divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#FF123456");
}

/**
 * @tc.name: setDividerColorResourceTest
 * @tc.desc: Check the functionality of ListModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setDividerColorResourceTest, TestSize.Level1)
{
    // default values
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto dividerCheckValue = dividerObject->ToString();
    EXPECT_EQ(dividerCheckValue, "{}");

    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11._px),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77._px)),
        .color = Converter::ArkValue<Opt_ResourceColor>(
            Converter::ArkUnion<Ark_ResourceColor, Ark_Resource>(DIVIDER_COLOR_RESOURCE))
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, DIVIDER_COLOR);
}

/**
 * @tc.name: setDividerUndefinedTest
 * @tc.desc: Check the functionality of ListModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setDividerUndefinedTest, TestSize.Level1)
{
    // set undefined values
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11._px),
        .startMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .endMargin = Converter::ArkValue<Opt_Length>(Ark_Empty()),
        .color = Converter::ArkValue<Opt_ResourceColor>(),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "11.00px");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#00000000");
}

/**
 * @tc.name: setDividerColorStringTest
 * @tc.desc: Check the functionality of ListModifier.setDivider
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setDividerColorStringTest, TestSize.Level1)
{
    // set color as Ark_String
    Ark_ListDividerOptions dividerOptions = {
        .strokeWidth = Converter::ArkValue<Ark_Length>(11),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77)),
        .color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>("#11223344"),
    };
    auto divider = Converter::ArkValue<Opt_ListDividerOptions>(dividerOptions);
    modifier_->setDivider(node_, &divider);
    auto fullJson = GetJsonValue(node_);
    auto dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#11223344");

    divider = Converter::ArkValue<Opt_ListDividerOptions>();
    modifier_->setDivider(node_, &divider);
    fullJson = GetJsonValue(node_);
    dividerObject = GetAttrValue<std::unique_ptr<JsonValue>>(fullJson, "divider");
    auto strokeWidthCheckValue = GetAttrValue<std::string>(dividerObject, "strokeWidth");
    EXPECT_EQ(strokeWidthCheckValue, "0.00vp");
    auto startMarginCheckValue = GetAttrValue<std::string>(dividerObject, "startMargin");
    EXPECT_EQ(startMarginCheckValue, "0.00vp");
    auto endMarginCheckValue = GetAttrValue<std::string>(dividerObject, "endMargin");
    EXPECT_EQ(endMarginCheckValue, "0.00vp");
    colorCheckValue = GetAttrValue<std::string>(dividerObject, "color");
    EXPECT_EQ(colorCheckValue, "#00000000");
}
/**
 * @tc.name: setFrictionTest
 * @tc.desc: Check the functionality of ListModifier.setFriction
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setFrictionTest, TestSize.Level1)
{
    // default values
    OnModifyDone();
    auto frictionCheckValue = GetAttrValue<double>(node_, "friction");
    EXPECT_EQ(frictionCheckValue, 0.75);

    // set float friction
    Ark_Union_Number_Resource friction =
        Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(55.5f);
    auto optFriction = Converter::ArkValue<Opt_Union_Number_Resource>(friction);
    modifier_->setFriction(node_, &optFriction);
    frictionCheckValue = GetAttrValue<double>(node_, "friction");
    EXPECT_EQ(frictionCheckValue, 55.50);

    // set negative friction
    friction = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(-55.5f);
    optFriction = Converter::ArkValue<Opt_Union_Number_Resource>(friction);
    modifier_->setFriction(node_, &optFriction);
    frictionCheckValue = GetAttrValue<double>(node_, "friction");
    EXPECT_NEAR(frictionCheckValue, 0.6, 0.01);

    // set int friction
    friction = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(77);
    optFriction = Converter::ArkValue<Opt_Union_Number_Resource>(friction);
    modifier_->setFriction(node_, &optFriction);
    frictionCheckValue = GetAttrValue<double>(node_, "friction");
    EXPECT_EQ(frictionCheckValue, 77.00);

    // set friction from resource
    friction = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Resource>(FRICTION_RESOURCE);
    optFriction = Converter::ArkValue<Opt_Union_Number_Resource>(friction);
    modifier_->setFriction(node_, &optFriction);
    frictionCheckValue = GetAttrValue<double>(node_, "friction");
    EXPECT_EQ(frictionCheckValue, FRICTION_VALUE);
}

/**
 * @tc.name: setChainAnimationOptionsTest
 * @tc.desc: Check the functionality of ListModifier.setChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, DISABLED_setChainAnimationOptionsTest, TestSize.Level1)
{
}

/**
 * @tc.name: setMaintainVisibleContentPosition
 * @tc.desc: Check the functionality of ListModifier.SetMaintainVisibleContentPosition
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setListMaintainVisibleContentPositionTest, TestSize.Level1)
{
    auto checkValue = GetAttrValue<bool>(node_, "maintainVisibleContentPosition");
    EXPECT_FALSE(checkValue);
    auto optValue = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setMaintainVisibleContentPosition(node_, &optValue);
    checkValue = GetAttrValue<bool>(node_, "maintainVisibleContentPosition");
    EXPECT_TRUE(checkValue);
}

/*
 * @tc.name: setOnScrollTest
 * @tc.desc: Check the functionality of ListModifier.setOnScroll
 * @tc.type: FUNC
 */

HWTEST_F(ListModifierTest, setOnScrollTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        Dimension scrollOffset;
        int32_t scrollState;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Number_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Number offset, const Ark_Number state) {
            checkEvent = {
                .nodeId = nodeId,
                .scrollOffset = Converter::Convert<Dimension>(offset),
                .scrollState = Converter::Convert<int32_t>(state),
            };
        }
    };

    auto onScroll = eventHub->GetOnScroll();
    EXPECT_EQ(onScroll, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_Number_Number_Void>(arkCallback);
    modifier_->setOnScroll(node_, &optCallback);
    onScroll = eventHub->GetOnScroll();
    EXPECT_NE(onScroll, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScroll(CalcDimension(55), ScrollState::FLING);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->scrollOffset.Value(), 55);
    EXPECT_EQ(checkEvent->scrollOffset.Unit(), DimensionUnit::VP);
    EXPECT_EQ(checkEvent->scrollState, static_cast<int>(ScrollState::FLING));
}

/*
 * @tc.name: setOnScrollIndexTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollIndexTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t start;
        int32_t end;
        int32_t center;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Number_Number_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Number start, const Ark_Number end, const Ark_Number center) {
            checkEvent = {
                .nodeId = nodeId,
                .start = Converter::Convert<int32_t>(start),
                .end = Converter::Convert<int32_t>(end),
                .center = Converter::Convert<int32_t>(center)
            };
        }
    };
    auto optCallback = Converter::ArkValue<Opt_Callback_Number_Number_Number_Void>(arkCallback);
    modifier_->setOnScrollIndex(node_, &optCallback);

    auto onScrollIndex = eventHub->GetOnScrollIndex();
    EXPECT_NE(onScrollIndex, nullptr);
    EXPECT_EQ(checkEvent.has_value(), false);

    // start: 0, end: 10, center: 5
    onScrollIndex(0, 10, 5);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->start, 0);
    EXPECT_EQ(checkEvent->end, 10);
    EXPECT_EQ(checkEvent->center, 5);

    // start: 5, end: 25, center: 15
    onScrollIndex(5, 25, 15);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->start, 5);
    EXPECT_EQ(checkEvent->end, 25);
    EXPECT_EQ(checkEvent->center, 15);
}

/*
 * @tc.name: setOnReachStartTest
 * @tc.desc: Check the functionality of ListModifier.setOnReachStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnReachStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            checkEvent = {
            .nodeId = nodeId,
            .result = true,
            };
        }
    };

    auto onReachStart = eventHub->GetOnReachStart();
    EXPECT_EQ(onReachStart, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnReachStart(node_, &optCallback);
    onReachStart = eventHub->GetOnReachStart();
    EXPECT_NE(onReachStart, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onReachStart();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnReachEndTest
 * @tc.desc: Check the functionality of ListModifier.setOnReachEnd
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnReachEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            checkEvent = {
            .nodeId = nodeId,
            .result = true,
            };
        }
    };

    auto onReachEnd = eventHub->GetOnReachEnd();
    EXPECT_EQ(onReachEnd, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnReachEnd(node_, &optCallback);
    onReachEnd = eventHub->GetOnReachEnd();
    EXPECT_NE(onReachEnd, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onReachEnd();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnScrollStartTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollStartTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            checkEvent = {
            .nodeId = nodeId,
            .result = true,
            };
        }
    };

    auto onScrollStart = eventHub->GetOnScrollStart();
    EXPECT_EQ(onScrollStart, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnScrollStart(node_, &optCallback);
    onScrollStart = eventHub->GetOnScrollStart();
    EXPECT_NE(onScrollStart, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScrollStart();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnScrollStopTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollStop
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollStopTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId) {
            checkEvent = {
            .nodeId = nodeId,
            .result = true,
            };
        }
    };

    auto onScrollStop = eventHub->GetOnScrollStop();
    EXPECT_EQ(onScrollStop, nullptr);
    auto optCallback = Converter::ArkValue<Opt_Callback_Void>(arkCallback);
    modifier_->setOnScrollStop(node_, &optCallback);
    onScrollStop = eventHub->GetOnScrollStop();
    EXPECT_NE(onScrollStop, nullptr);

    EXPECT_FALSE(checkEvent.has_value());
    onScrollStop();
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_TRUE(checkEvent->result);
}

/*
 * @tc.name: setOnItemDragStartTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemDragStartTest, TestSize.Level1)
{
    using namespace Converter;
    static const int32_t expectedX = 357;
    static const int32_t expectedY = 468;
    static const int32_t expectedIdx = 7;
    static const int32_t expectedResourceId = 123;

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    static const auto expectedParentNode = frameNode;
    static auto expectedCustomNode = CreateNode();
    ASSERT_NE(expectedCustomNode, nullptr);

    // set callback to model
    auto onItemDragStartSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_ItemDragInfo event, const Ark_Number itemIndex,
        const Callback_CustomBuilder_Void continuation
    ) {
        // check input values
        EXPECT_EQ(resourceId, expectedResourceId);
        auto dragInfo = Convert<ItemDragInfo>(event);
        EXPECT_EQ(dragInfo.GetX(), expectedX);
        EXPECT_EQ(dragInfo.GetY(), expectedY);
        auto index = Convert<int32_t>(itemIndex);
        EXPECT_EQ(index, expectedIdx);

        // construct the result CustomBuilder
        auto builderSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
            const Ark_NativePointer parentNode, const Callback_Pointer_Void continuation) {
            EXPECT_EQ(reinterpret_cast<FrameNode*>(parentNode), expectedParentNode);
            CallbackHelper(continuation).InvokeSync(expectedCustomNode);
        };
        auto builder = ArkValue<CustomNodeBuilder>(nullptr, builderSyncFunc);

        // return result
        CallbackHelper(continuation).InvokeSync(builder);
    };
    auto arkCallback =
        ArkValue<ListAttribute_onItemDragStart_event_type>(nullptr, onItemDragStartSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_ListAttribute_onItemDragStart_event_type>(arkCallback);
    modifier_->setOnItemDragStart(node_, &optCallback);

    // imitate the test case
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    ASSERT_NE(eventHub, nullptr);
    ItemDragInfo dragInfo;
    dragInfo.SetX(expectedX);
    dragInfo.SetY(expectedY);
    auto resultNode = eventHub->FireOnItemDragStart(dragInfo, expectedIdx);

    // check result
    EXPECT_EQ(resultNode, reinterpret_cast<UINode *>(expectedCustomNode));

    DisposeNode(expectedCustomNode);
}

/*
 * @tc.name: setOnItemDragEnterTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDragEnter
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemDragEnterTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_Void>(arkCallback);
    modifier_->setOnItemDragEnter(node_, &optCallback);

    dragInfo.SetX(234);
    dragInfo.SetY(567);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragEnter(dragInfo);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 234);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 567);
}

/*
 * @tc.name: setOnItemDragMoveTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDragMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemDragMoveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Number_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event,
                const Ark_Number itemIndex, const Ark_Number insertIndex) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex),
                .insertIndex = Converter::Convert<int32_t>(insertIndex)
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_Number_Number_Void>(arkCallback);
    modifier_->setOnItemDragMove(node_, &optCallback);

    dragInfo.SetX(987);
    dragInfo.SetY(654);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragMove(dragInfo, 4, 35);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 987);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 654);
    EXPECT_EQ(checkEvent->itemIndex, 4);
    EXPECT_EQ(checkEvent->insertIndex, 35);
}

/*
 * @tc.name: setOnItemDragLeaveTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDragLeave
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemDragLeaveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_Number itemIndex) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex)
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_Number_Void>(arkCallback);
    modifier_->setOnItemDragLeave(node_, &optCallback);

    dragInfo.SetX(135);
    dragInfo.SetY(246);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDragLeave(dragInfo, 6);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 135);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 246);
    EXPECT_EQ(checkEvent->itemIndex, 6);
}

/*
 * @tc.name: setOnItemDropTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDrop
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemDropTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
        bool isSuccess;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Number_Number_Boolean_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_Number itemIndex,
                const Ark_Number insertIndex, const Ark_Boolean isSuccess) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex),
                .insertIndex = Converter::Convert<int32_t>(insertIndex),
                .isSuccess = Converter::Convert<bool>(isSuccess),
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void>(arkCallback);
    modifier_->setOnItemDrop(node_, &optCallback);

    dragInfo.SetX(975);
    dragInfo.SetY(864);

    EXPECT_FALSE(checkEvent.has_value());
    eventHub->FireOnItemDrop(dragInfo, 81, 99, true);
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->dragInfo.GetX(), 975);
    EXPECT_EQ(checkEvent->dragInfo.GetY(), 864);
    EXPECT_EQ(checkEvent->itemIndex, 81);
    EXPECT_EQ(checkEvent->insertIndex, 99);
    EXPECT_TRUE(checkEvent->isSuccess);
}

/*
 * @tc.name: setOnScrollFrameBeginTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollFrameBegin
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollFrameBeginTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_NE(modifier_->setOnScrollFrameBegin, nullptr);
    modifier_->setOnScrollFrameBegin(node_, nullptr);

    static const Ark_Int32 expectedResId = 123;
    auto onScrollFrameBegin = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Number offset, Ark_ScrollState state,
        const Callback_OnScrollFrameBeginHandlerResult_Void cbReturn) {
        EXPECT_EQ(resourceId, expectedResId);
        EXPECT_EQ(Converter::Convert<float>(offset), TEST_OFFSET);
        ScrollFrameResult result;
        result.offset = Converter::Convert<Dimension>(offset);
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_OnScrollFrameBeginHandlerResult>(result));
    };
    auto arkFunc = Converter::ArkValue<OnScrollFrameBeginCallback>(
        nullptr, onScrollFrameBegin, expectedResId);
    auto arkFuncOpt = Converter::ArkValue<Opt_OnScrollFrameBeginCallback>(arkFunc);
    modifier_->setOnScrollFrameBegin(node_, &arkFuncOpt);

    Dimension dimension(TEST_OFFSET);
    ScrollState state = ScrollState::SCROLL;
    ScrollFrameResult result = eventHub->GetOnScrollFrameBegin()(dimension, state);
    EXPECT_EQ(result.offset.ConvertToPx(), dimension.ConvertToPx());
}

/*
 * @tc.name: setOnItemMoveTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemMove
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnItemMoveTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
        bool isSuccess;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Number_Number_Boolean_Void arkCallbackDrop = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_Number itemIndex,
                const Ark_Number insertIndex, const Ark_Boolean isSuccess) {
            checkEvent = {.nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex),
                .insertIndex = Converter::Convert<int32_t>(insertIndex),
                .isSuccess = Converter::Convert<bool>(isSuccess),
            };
        }
    };

    static const int32_t expectedResourceId = 123;
    auto onItemMoveFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
            const Ark_Number from, const Ark_Number to, const Callback_Boolean_Void cbReturn
        ) {
        EXPECT_EQ(resourceId, expectedResourceId);
        auto result = Converter::Convert<int32_t>(from) > Converter::Convert<int32_t>(to);
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto func2 = Converter::ArkValue<Callback_Number_Number_Boolean>(nullptr, onItemMoveFunc, expectedResourceId);

    auto optCallbackDrop = Converter::ArkValue<Opt_Callback_ItemDragInfo_Number_Number_Boolean_Void>(arkCallbackDrop);
    modifier_->setOnItemDrop(node_, &optCallbackDrop);
    auto optFunc2 = Converter::ArkValue<Opt_Callback_Number_Number_Boolean>(func2);
    modifier_->setOnItemMove(node_, &optFunc2);
    dragInfo.SetX(975);
    dragInfo.SetY(864);

    checkEvent.reset();
    eventHub->FireOnItemDrop(dragInfo, 81, 99, false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_FALSE(checkEvent->isSuccess);

    checkEvent.reset();
    eventHub->FireOnItemDrop(dragInfo, 30, 20, false);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_TRUE(checkEvent->isSuccess);
}

/*
 * @tc.name: DISABLED_setOnItemDeleteTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDelete
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, DISABLED_setOnItemDeleteTest, TestSize.Level1)
{
    Callback_Number_Boolean func{};
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    static const int32_t expectedResourceId = 123;
    static const int32_t fakeTotalCount = 10;
    auto callbackSyncFunc = [](Ark_VMContext context, const Ark_Int32 resourceId,
            const Ark_Number index, const Callback_Boolean_Void cbReturn
        ) {
        EXPECT_EQ(resourceId, expectedResourceId);
        auto result = Converter::Convert<int32_t>(index) < fakeTotalCount;
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    func = Converter::ArkValue<Callback_Number_Boolean>(nullptr, callbackSyncFunc, expectedResourceId);

    auto optFunc = Converter::ArkValue<Opt_Callback_Number_Boolean>(func);
    modifier_->setOnItemDelete(node_, &optFunc);
    // check is not enable due to the ListEventHub does no support the onItemDelete event
}

/*
 * @tc.name: setOnScrollVisibleContentChangeTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollVisibleContentChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetOrCreateEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        ListItemIndex start;
        ListItemIndex end;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    OnScrollVisibleContentChangeCallback arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_VisibleListContentInfo start, const Ark_VisibleListContentInfo end) {
            checkEvent = {
                .nodeId = nodeId,
                .start = Converter::Convert<ListItemIndex>(start),
                .end = Converter::Convert<ListItemIndex>(end)
            };
        }
    };

    auto onScrollVisibleContentChange = eventHub->GetOnScrollVisibleContentChange();
    EXPECT_EQ(onScrollVisibleContentChange, nullptr);
    auto optCallback = Converter::ArkValue<Opt_OnScrollVisibleContentChangeCallback>(arkCallback);
    modifier_->setOnScrollVisibleContentChange(node_, &optCallback);
    onScrollVisibleContentChange = eventHub->GetOnScrollVisibleContentChange();
    EXPECT_NE(onScrollVisibleContentChange, nullptr);
    EXPECT_FALSE(checkEvent.has_value());
    onScrollVisibleContentChange(
        ListItemIndex {.index=11, .area=ARK_LIST_ITEM_GROUP_AREA_IN_HEADER_AREA, .indexInGroup=33},
        ListItemIndex {.index=77, .area=ARK_LIST_ITEM_GROUP_AREA_IN_FOOTER_AREA, .indexInGroup=99});
    EXPECT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->start.index, 11);
    EXPECT_EQ(checkEvent->start.area, ListItemGroupArea::IN_HEADER_AREA);
    EXPECT_EQ(checkEvent->start.indexInGroup, 33);
    EXPECT_EQ(checkEvent->end.index, 77);
    EXPECT_EQ(checkEvent->end.area, ListItemGroupArea::IN_FOOTER_AREA);
    EXPECT_EQ(checkEvent->end.indexInGroup, 99);
}
} // namespace OHOS::Ace::NG
