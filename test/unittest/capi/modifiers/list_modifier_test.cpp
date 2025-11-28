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
#include "core/components_ng/pattern/list/list_layout_property.h"
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
    dst.offsetRemain = Converter::ArkValue<Ark_Float64>(src.offset);
}
} // Converter

namespace {
const auto DIVIDER_COLOR_RES_NAME = "divider_color_res_name";
const auto DIVIDER_COLOR = "#08000000";
const auto DIVIDER_COLOR_RESOURCE = CreateResource(DIVIDER_COLOR_RES_NAME, ResourceType::COLOR);
const float TEST_OFFSET = 10.0f;
} // namespace

class ListModifierTest : public ModifierTestBase<GENERATED_ArkUIListModifier,
    &GENERATED_ArkUINodeModifiers::getListModifier, GENERATED_ARKUI_LIST> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();
        SetupTheme<ScrollableTheme>();
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
 * @tc.name: setCachedCount0Test
 * @tc.desc: Check the functionality of ListModifier.setCachedCount0
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, DISABLED_setCachedCount0Test, TestSize.Level1)
{
    auto checkValue = GetAttrValue<std::string>(node_, "cachedCount");
    EXPECT_EQ(checkValue, "0");

    auto arg = Converter::ArkValue<Ark_Int32>(10);
    auto optArg = Converter::ArkValue<Opt_Int32>(arg);
    modifier_->setCachedCount0(node_, &optArg);
    checkValue = GetAttrValue<std::string>(node_, "cachedCount");
    EXPECT_EQ(checkValue, "10");

    arg = Converter::ArkValue<Ark_Int32>(-10);
    optArg = Converter::ArkValue<Opt_Int32>(arg);
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

    auto intNum = Converter::ArkValue<Ark_Float64>(11);
    auto optIntNum = Converter::ArkValue<Opt_Float64>(intNum);
    modifier_->setContentStartOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_EQ(checkValue, "11.000000");

    auto floatNum = Converter::ArkValue<Ark_Float64>(22.2f);
    auto optFloatNum = Converter::ArkValue<Opt_Float64>(floatNum);
    modifier_->setContentStartOffset(node_, &optFloatNum);
    checkValue = GetAttrValue<std::string>(node_, "contentStartOffset");
    EXPECT_THAT(checkValue, StartsWith("22.2"));

    intNum = Converter::ArkValue<Ark_Float64>(-33);
    optIntNum = Converter::ArkValue<Opt_Float64>(intNum);
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

    auto intNum = Converter::ArkValue<Ark_Float64>(11);;
    auto optIntNum = Converter::ArkValue<Opt_Float64>(intNum);
    modifier_->setContentEndOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_EQ(checkValue, "11.000000");

    auto floatNum = Converter::ArkValue<Ark_Float64>(22.2f);
    auto optFloatNum = Converter::ArkValue<Opt_Float64>(floatNum);
    modifier_->setContentEndOffset(node_, &optFloatNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_THAT(checkValue, StartsWith("22.2"));

    intNum = Converter::ArkValue<Ark_Float64>(-55);
    optIntNum = Converter::ArkValue<Opt_Float64>(intNum);
    modifier_->setContentEndOffset(node_, &optIntNum);
    checkValue = GetAttrValue<std::string>(node_, "contentEndOffset");
    EXPECT_THAT(checkValue, StartsWith("-55"));
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
        .initialIndex = Converter::ArkValue<Opt_Int32>(1),
        .space = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(55.7f),
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
        .initialIndex = Converter::ArkValue<Opt_Int32>(Ark_Empty()),
        .space = Converter::ArkValue<Opt_Union_F64_String>(Ark_Empty()),
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
        .initialIndex = Converter::ArkValue<Opt_Int32>(3),
        .space = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>("88.9px"),
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
        .initialIndex = Converter::ArkValue<Opt_Int32>(-7),
        .space = Converter::ArkUnion<Opt_Union_F64_String, Ark_Float64>(-9),
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
    Ark_Union_Number_LengthConstrain value =  Converter::ArkUnion<Ark_Union_I32_LengthConstrain, Ark_Int32>(2);
    auto optValue = Converter::ArkValue<Opt_Union_I32_LengthConstrain>(value);
    auto gutterOpt = Converter::ArkValue<Opt_Dimension>(55.5f);
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
    EXPECT_EQ(gutterCheckValue, "0.00vp");

    // lanes as constraints
    Ark_LengthConstrain constraint = {
        .minLength = Converter::ArkValue<Ark_Length>("11fp"),
        .maxLength = Converter::ArkValue<Ark_Length>("77.7px"),
    };
    value = Converter::ArkUnion<Ark_Union_I32_LengthConstrain, Ark_LengthConstrain>(constraint);
    optValue = Converter::ArkValue<Opt_Union_I32_LengthConstrain>(value);
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
    Ark_Union_Number_LengthConstrain value = Converter::ArkUnion<Ark_Union_I32_LengthConstrain, Ark_I32>(-2);
    auto optValue = Converter::ArkValue<Opt_Union_I32_LengthConstrain>(value);
    auto gutterOpt = Converter::ArkValue<Opt_Dimension>("-88px");
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>("77px")),
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
        .strokeWidth = Converter::ArkValue<Ark_Length>("11px"),
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
        .strokeWidth = Converter::ArkValue<Ark_Length>(11.f),
        .startMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(55.5f)),
        .endMargin = Converter::ArkValue<Opt_Length>(Converter::ArkValue<Ark_Length>(77.f)),
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
 * @tc.name: setChainAnimationOptionsTest
 * @tc.desc: Check the functionality of ListModifier.setChainAnimationOptions
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, DISABLED_setChainAnimationOptionsTest, TestSize.Level1)
{
    FAIL() << "Test is not implemented yet";
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
 * @tc.name: setOnScrollIndexTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollIndexTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        int32_t start;
        int32_t end;
        int32_t center;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Number_Number_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Int32 start, const Ark_Int32 end, const Ark_Int32 center) {
            checkEvent = {
                .nodeId = nodeId,
                .start = Converter::Convert<int32_t>(start),
                .end = Converter::Convert<int32_t>(end),
                .center = Converter::Convert<int32_t>(center)
            };
        }
    };
    auto optCallback = Converter::ArkValue<Opt_Callback_I32_I32_I32_Void>(arkCallback);
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
 * @tc.name: setOnItemDragStartTest
 * @tc.desc: Check the functionality of ListModifier.setOnItemDragStart
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, DISABLED_setOnItemDragStartTest, TestSize.Level1)
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
        const Ark_ItemDragInfo event, const Ark_Int32 itemIndex,
        const Callback_Opt_CustomBuilder_Void continuation
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
        auto optBuilder = ArkValue<Opt_CustomNodeBuilder>(builder);

        // return result
        CallbackHelper(continuation).InvokeSync(optBuilder);
    };
    auto arkCallback =
        ArkValue<OnItemDragStartCallback>(nullptr, onItemDragStartSyncFunc, expectedResourceId);
    auto optCallback = Converter::ArkValue<Opt_OnItemDragStartCallback>(arkCallback);
    modifier_->setOnItemDragStart(node_, &optCallback);

    // imitate the test case
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
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
                const Ark_Int32 itemIndex, const Ark_Int32 insertIndex) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex),
                .insertIndex = Converter::Convert<int32_t>(insertIndex)
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_I32_I32_Void>(arkCallback);
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_Number_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex)
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_Int32_Void>(arkCallback);
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {
        int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
        bool isSuccess;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_I32_I32_Boolean_Void arkCallback = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_Int32 itemIndex,
                const Ark_Int32 insertIndex, const Ark_Boolean isSuccess) {
            checkEvent = {
                .nodeId = nodeId,
                .dragInfo = Converter::Convert<ItemDragInfo>(event),
                .itemIndex = Converter::Convert<int32_t>(itemIndex),
                .insertIndex = Converter::Convert<int32_t>(insertIndex),
                .isSuccess = Converter::Convert<bool>(isSuccess),
            };
        }
    };

    auto optCallback = Converter::ArkValue<Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void>(arkCallback);
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    ASSERT_NE(eventHub, nullptr);

    ASSERT_NE(modifier_->setOnScrollFrameBegin, nullptr);
    modifier_->setOnScrollFrameBegin(node_, nullptr);

    static const Ark_Int32 expectedResId = 123;
    auto onScrollFrameBegin = [](Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Float64 offset, Ark_ScrollState state,
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
    auto eventHub = frameNode->GetEventHub<ListEventHub>();
    auto dragInfo = ItemDragInfo();

    struct CheckEvent {int32_t nodeId;
        ItemDragInfo dragInfo;
        int32_t itemIndex;
        int32_t insertIndex;
        bool isSuccess;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_ItemDragInfo_I32_I32_Boolean_Void arkCallbackDrop = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_ItemDragInfo event, const Ark_I32 itemIndex,
                const Ark_I32 insertIndex, const Ark_Boolean isSuccess) {
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
            const Ark_Int32 from, const Ark_Int32 to, const Callback_Boolean_Void cbReturn
        ) {
        EXPECT_EQ(resourceId, expectedResourceId);
        auto result = Converter::Convert<int32_t>(from) > Converter::Convert<int32_t>(to);
        CallbackHelper(cbReturn).InvokeSync(Converter::ArkValue<Ark_Boolean>(result));
    };
    auto func2 = Converter::ArkValue<Callback_I32_I32_Boolean>(nullptr, onItemMoveFunc, expectedResourceId);

    auto optCallbackDrop = Converter::ArkValue<Opt_Callback_ItemDragInfo_I32_I32_Boolean_Void>(arkCallbackDrop);
    modifier_->setOnItemDrop(node_, &optCallbackDrop);
    auto optFunc2 = Converter::ArkValue<Opt_Callback_I32_I32_Boolean>(func2);
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
 * @tc.name: setOnScrollVisibleContentChangeTest
 * @tc.desc: Check the functionality of ListModifier.setOnScrollVisibleContentChange
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setOnScrollVisibleContentChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<ListEventHub>();

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

/*
 * @tc.name: setStackFromEndTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(ListModifierTest, setStackFromEndTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    auto property = frameNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(property, nullptr);

    std::optional<bool> result;
    auto value = Converter::ArkValue<Opt_Boolean>(Ark_Empty());

    modifier_->setStackFromEnd(node_, &value);
    result = property->GetStackFromEnd();
    ASSERT_FALSE(result);

    value = Converter::ArkValue<Opt_Boolean>(true);
    modifier_->setStackFromEnd(node_, &value);
    result = property->GetStackFromEnd();
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), true);

    value = Converter::ArkValue<Opt_Boolean>(false);
    modifier_->setStackFromEnd(node_, &value);
    result = property->GetStackFromEnd();
    ASSERT_TRUE(result);
    EXPECT_EQ(result.value(), false);
}
} // namespace OHOS::Ace::NG
