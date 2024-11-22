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

#include <gtest/gtest.h>
#include <climits>

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/pattern/grid/grid_event_hub.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"

#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/implementation/scroller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::Ace::NG::Converter;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME = "gridLayoutOptions";
    const auto ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SET_REGULAR_SIZE_NAME = "regularSize";
    const auto ATTRIBUTE_SET_REGULAR_SIZE_DEFAULT_VALUE = "[]";
    const auto ATTRIBUTE_SET_IRREGULAR_INDEXES_NAME = "irregularIndexes";
    const auto ATTRIBUTE_SET_IRREGULAR_INDEXES_DEFAULT_VALUE = "[]";
    const auto ATTRIBUTE_COLUMNS_TEMPLATE_NAME = "columnsTemplate";
    const auto ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_ROWS_TEMPLATE_NAME = "rowsTemplate";
    const auto ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_COLUMNS_GAP_NAME = "columnsGap";
    const auto ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_ROWS_GAP_NAME = "rowsGap";
    const auto ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_SCROLL_BAR_WIDTH_NAME = "scrollBarWidth";
    const auto ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE = "0.00vp";
    const auto ATTRIBUTE_SCROLL_BAR_COLOR_NAME = "scrollBarColor";
    const auto ATTRIBUTE_SCROLL_BAR_COLOR_DEFAULT_VALUE = "#00FF00FF";
    const auto ATTRIBUTE_SCROLL_BAR_NAME = "scrollBar";
    const auto ATTRIBUTE_SCROLL_BAR_DEFAULT_VALUE = "BarState.Auto";
    const auto ATTRIBUTE_CACHED_COUNT_NAME = "cachedCount";
    const auto ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE = 1;
    const auto ATTRIBUTE_EDIT_MODE_NAME = "editMode";
    const auto ATTRIBUTE_EDIT_MODE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_MULTI_SELECTABLE_NAME = "multiSelectable";
    const auto ATTRIBUTE_MULTI_SELECTABLE_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_MAX_COUNT_NAME = "maxCount";
    const auto ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE = Infinity<int32_t>();
    const auto ATTRIBUTE_MIN_COUNT_NAME = "minCount";
    const auto ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE = 1;
    const auto ATTRIBUTE_CELL_LENGTH_NAME = "cellLength";
    const auto ATTRIBUTE_CELL_LENGTH_DEFAULT_VALUE = 0;
    const auto ATTRIBUTE_LAYOUT_DIRECTION_NAME = "layoutDirection";
    const auto ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE = "GridDirection.Row";
    const auto ATTRIBUTE_SUPPORT_ANIMATION_NAME = "supportAnimation";
    const auto ATTRIBUTE_SUPPORT_ANIMATION_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_EDGE_EFFECT_NAME = "edgeEffect";
    const auto ATTRIBUTE_EDGE_EFFECT_DEFAULT_VALUE = "EdgeEffect.None";
    const auto ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME = "edgeEffectOptions";
    const auto ATTRIBUTE_ALWAYS_ENABLED_NAME = "alwaysEnabled";
    const auto ATTRIBUTE_ALWAYS_ENABLED_DEFAULT_VALUE = false;
    const auto ATTRIBUTE_NESTED_SCROLL_NAME = "nestedScroll";
    const auto ATTRIBUTE_SCROLL_FORWARD_NAME = "scrollForward";
    const auto ATTRIBUTE_SCROLL_FORWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
    const auto ATTRIBUTE_SCROLL_BACKWARD_NAME = "scrollBackward";
    const auto ATTRIBUTE_SCROLL_BACKWARD_DEFAULT_VALUE = "NestedScrollMode.SELF_ONLY";
    const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME = "enableScrollInteraction";
    const auto ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE = true;
    const auto ATTRIBUTE_FRICTION_NAME = "friction";
    const auto ATTRIBUTE_FRICTION_DEFAULT_VALUE = 0.75f;
    const auto ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME = "alignItems";
    const auto ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_DEFAULT_VALUE = "GridItemAlignment.Default";

    const Color THEME_SCROLLBAR_COLOR(0x00FF00FF);

    // resource names and id
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", NodeModifier::ResourceType::FLOAT};
    const auto RES_ID = IntResourceId{11111, NodeModifier::ResourceType::FLOAT};

    // resource values
    const auto RESOURCE_OPACITY_BY_STRING = 0.4f;
    const auto RESOURCE_OPACITY_BY_NUMBER = 0.5f;

    using OneNumResStep = std::pair<Ark_Union_Number_Resource, float>;
    static const std::vector<OneNumResStep> UNION_NUMBER_RES_TEST_PLAN = {
        { CreateResourceUnion<Ark_Union_Number_Resource>(RES_NAME), RESOURCE_OPACITY_BY_STRING },
        { CreateResourceUnion<Ark_Union_Number_Resource>(RES_ID), RESOURCE_OPACITY_BY_NUMBER },
    };

    const Ark_Int32 FAKE_RES_ID(1234);
    const Ark_Length RES_ARK_LENGTH = { .type = ARK_TAG_RESOURCE, .resource = FAKE_RES_ID };
} // namespace

class GridModifierTest : public ModifierTestBase<GENERATED_ArkUIGridModifier,
    &GENERATED_ArkUINodeModifiers::getGridModifier, GENERATED_ARKUI_GRID> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        // set test values to Theme Pattern as data for the Theme building
        auto themeStyle = SetupThemeStyle(THEME_PATTERN_SCROLL_BAR);
        themeStyle->SetAttr(PATTERN_FG_COLOR, { .value = THEME_SCROLLBAR_COLOR });

        SetupTheme<ScrollBarTheme>();

        // set test values to Theme Pattern as data for the Theme building
        AddResource(RES_NAME, RESOURCE_OPACITY_BY_STRING);
        AddResource(RES_ID, RESOURCE_OPACITY_BY_NUMBER);
    }
};

/*
 * @tc.name: setGridOptionsTestDefaultLayoutOptionaValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestDefaultLayoutOptionaValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_REGULAR_SIZE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SET_REGULAR_SIZE_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_IRREGULAR_INDEXES_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SET_IRREGULAR_INDEXES_DEFAULT_VALUE);
}

/*
 * @tc.name: setGridOptionsTestValidLayoutOptionsValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestValidLayoutOptionsValues, TestSize.Level1)
{
    std::string strResult;
    Opt_Scroller inputValue0;
    Ark_GridLayoutOptions layoutOptions;
    Opt_GridLayoutOptions inputValue1;

    layoutOptions.regularSize.value0 = Converter::ArkValue<Ark_Number>(1);
    layoutOptions.regularSize.value1 = Converter::ArkValue<Ark_Number>(1);
    std::vector<int32_t> indexes{1, 2, 3, 4, 5};
    Converter::ArkArrayHolder<Array_Number> indexesHolder(indexes);
    Array_Number indexesArrayResult = indexesHolder.ArkValue();
    layoutOptions.irregularIndexes = Converter::ArkValue<Opt_Array_Number>(indexesArrayResult);
    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME);
    EXPECT_EQ(strResult, "true");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_REGULAR_SIZE_NAME);
    EXPECT_EQ(strResult, "[1,1]");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_IRREGULAR_INDEXES_NAME);
    EXPECT_EQ(strResult, "[1,2,3,4,5]");

    layoutOptions.regularSize.value0 = Converter::ArkValue<Ark_Number>(2);
    layoutOptions.regularSize.value1 = Converter::ArkValue<Ark_Number>(2);
    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME);
    EXPECT_EQ(strResult, "true");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_REGULAR_SIZE_NAME);
    EXPECT_EQ(strResult, "[1,1]");
}

/*
 * @tc.name: setGridOptionsTestInvalidLayoutOptionsValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestInvalidLayoutOptionsValues, TestSize.Level1)
{
    std::string strResult;
    Opt_Scroller inputValue0;
    Ark_GridLayoutOptions layoutOptions;
    Opt_GridLayoutOptions inputValue1;

    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME);
    EXPECT_EQ(strResult, "true");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_REGULAR_SIZE_NAME);
    EXPECT_EQ(strResult, "[1,1]");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_IRREGULAR_INDEXES_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SET_IRREGULAR_INDEXES_DEFAULT_VALUE);
}

/*
 * @tc.name: setGridOptionsTestValidScrollerValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestValidScrollerValues, TestSize.Level1)
{
    Ark_NativePointer scrollerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ScrollerPeerImpl*>(scrollerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern, nullptr);

    Ark_Scroller arkScroller;
    arkScroller.ptr = scrollerPtr;
    Opt_Scroller inputValue0 = Converter::ArkValue<Opt_Scroller>(std::optional<Ark_Scroller>(arkScroller));
    Opt_GridLayoutOptions inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(Ark_Empty());
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);

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

/*
 * @tc.name: setGridOptionsTestInvalidScrollerValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestInvalidScrollerValues, TestSize.Level1)
{
    Ark_NativePointer scrollerPtr =
        GeneratedModifier::GetFullAPI()->getAccessors()->getScrollerAccessor()->ctor();
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ScrollerPeerImpl*>(scrollerPtr);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern, nullptr);

    Ark_Scroller arkScroller;
    arkScroller.ptr = scrollerPtr;
    Opt_Scroller inputValue0 = Converter::ArkValue<Opt_Scroller>(Ark_Empty());
    Opt_GridLayoutOptions inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(Ark_Empty());
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);

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

/*
 * @tc.name: setColumnsTemplateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsTemplateTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnsTemplateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsTemplateTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_String inputValue;

    // check '1fr 1fr 1fr' template
    inputValue = Converter::ArkValue<Ark_String>("1fr 1fr 1fr");
    modifier_->setColumnsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr 1fr 1fr");

    // check '2fr' template
    inputValue = Converter::ArkValue<Ark_String>("2fr");
    modifier_->setColumnsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "2fr");
}

/*
 * @tc.name: setColumnsTemplateTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsTemplateTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_String inputValue;

    // check empty template
    inputValue = Converter::ArkValue<Ark_String>("");
    modifier_->setColumnsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr");
}

/*
 * @tc.name: setRowsTemplateTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsTemplateTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowsTemplateTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsTemplateTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_String inputValue;

    // check '1fr 1fr 1fr' template
    inputValue = Converter::ArkValue<Ark_String>("1fr 1fr 1fr");
    modifier_->setRowsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr 1fr 1fr");

    // check '2fr' template
    inputValue = Converter::ArkValue<Ark_String>("2fr");
    modifier_->setRowsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "2fr");
}

/*
 * @tc.name: setRowsTemplateTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsTemplateTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_String inputValue;

    // check empty template
    inputValue = Converter::ArkValue<Ark_String>("");
    modifier_->setRowsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr");
}

/*
 * @tc.name: setColumnsGapTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsGapTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnsGapTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsGapTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set 5px
    inputValue = Converter::ArkValue<Ark_Length>(5);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "5.00px");

    // set 20px
    inputValue = Converter::ArkValue<Ark_Length>(20);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "20.00px");

    // set 0px
    inputValue = Converter::ArkValue<Ark_Length>(0);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "0.00px");

    // set 2147483648px
    inputValue = Converter::ArkValue<Ark_Length>(INT_MAX);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "2147483648.00px");

    // set 2vp
    inputValue = Converter::ArkValue<Ark_Length>(2.f);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "2.00vp");

    // set 50.35vp
    inputValue = Converter::ArkValue<Ark_Length>(50.35f);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "50.35vp");

    // set 0vp
    inputValue = Converter::ArkValue<Ark_Length>(0.f);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "0.00vp");
}

/*
 * @tc.name: setColumnsGapTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsGapTestValidResourceValues, TestSize.Level1)
{
    Ark_Length inputValue = RES_ARK_LENGTH;
    modifier_->setColumnsGap(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "10.00px");
}

/*
 * @tc.name: setColumnsGapTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setColumnsGapTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set -1px
    inputValue = Converter::ArkValue<Ark_Length>(-1);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_NE(strResult, "-1.00px");
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE);

    // set -1vp
    inputValue = Converter::ArkValue<Ark_Length>(-1.f);
    modifier_->setColumnsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_NE(strResult, "-1.00vp");
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_GAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowsGapTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsGapTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowsGapTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsGapTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set 5px
    inputValue = Converter::ArkValue<Ark_Length>(5);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "5.00px");

    // set 20px
    inputValue = Converter::ArkValue<Ark_Length>(20);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "20.00px");

    // set 0px
    inputValue = Converter::ArkValue<Ark_Length>(0);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "0.00px");

    // set 2147483648px
    inputValue = Converter::ArkValue<Ark_Length>(INT_MAX);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "2147483648.00px");

    // set 2vp
    inputValue = Converter::ArkValue<Ark_Length>(2.f);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "2.00vp");

    // set 50.35vp
    inputValue = Converter::ArkValue<Ark_Length>(50.35f);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "50.35vp");

    // set 0vp
    inputValue = Converter::ArkValue<Ark_Length>(0.f);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "0.00vp");
}

/*
 * @tc.name: setRowsGapTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsGapTestValidResourceValues, TestSize.Level1)
{
    Ark_Length inputValue = RES_ARK_LENGTH;
    modifier_->setRowsGap(node_, &inputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "10.00px");
}

/*
 * @tc.name: setRowsGapTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setRowsGapTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set -1px
    inputValue = Converter::ArkValue<Ark_Length>(-1);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_NE(strResult, "-1.00px");
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE);

    // set -1vp
    inputValue = Converter::ArkValue<Ark_Length>(-1.f);
    modifier_->setRowsGap(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_NE(strResult, "-1.00vp");
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_GAP_DEFAULT_VALUE);
}

/*
 * @tc.name: setScrollBarWidthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarWidthTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setScrollBarWidthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarWidthTestValidValues, TestSize.Level1)
{
    std::string strResult;

    typedef std::pair<Ark_Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(1), "1.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(0), "0.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(2.45f), "2.45vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("5px"), "5.00px" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("22.35px"), "22.35px" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("7vp"), "7.00vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("1.65vp"), "1.65vp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("65fp"), "65.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("4.3fp"), "4.30fp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("11lpx"), "11.00lpx" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("0.5lpx"), "0.50lpx" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("3"), "3.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("10.65"), "10.65fp" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setScrollBarWidth(node_, &arkResColor);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setScrollBarWidthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarWidthTestInvalidValues, TestSize.Level1)
{
    std::string strResult;

    typedef std::pair<Ark_Union_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-1), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_Number>(-3.56f), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("invalid value"), "0.00fp" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-8px"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-15.6px"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("23%"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-21vp"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-8.6vp"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-32fp"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-9.99fp"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-22lpx"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-1.23lpx"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-6"), "" },
        { Converter::ArkUnion<Ark_Union_Number_String, Ark_String>("-16.2"), "" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setScrollBarWidth(node_, &arkResColor);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_WIDTH_NAME);
        EXPECT_EQ(strResult, expected.length() > 0 ? expected : ATTRIBUTE_SCROLL_BAR_WIDTH_DEFAULT_VALUE);
    }
}

/*
 * @tc.name: setScrollBarColorTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarColorTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SCROLL_BAR_COLOR_DEFAULT_VALUE);
}

/*
 * @tc.name: setScrollBarColorTestValidColorValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarColorTestValidColorValues, TestSize.Level1)
{
    // test is disabled because Ark_Color can`t be converted to Color
    std::string strResult;

    typedef std::pair<Ark_Union_Color_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_WHITE), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_BLACK), "#FF000000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_BLUE), "#FF0000FF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_BROWN), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_GRAY), "#FF808080" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_GREEN), "#FF008000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_GREY), "#FF808080" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_ORANGE), "#FFFFA500" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_PINK), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_RED), "#FFFF0000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_YELLOW), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Color>(ARK_COLOR_TRANSPARENT), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setScrollBarColor(node_, &arkResColor);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setScrollBarColorTestValidNumberValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarColorTestValidNumberValues, TestSize.Level1)
{
    std::string strResult;

    typedef std::pair<Ark_Union_Color_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffffffff), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xff000000), "#FF000000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xff0000ff), "#FF0000FF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffa52a2a), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xff808080), "#FF808080" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xff008000), "#FF008000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffffa500), "#FFFFA500" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffffc0cb), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffff0000), "#FFFF0000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffffff00), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0x00000000), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setScrollBarColor(node_, &arkResColor);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: setScrollBarColorTestValidStringValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarColorTestValidStringValues, TestSize.Level1)
{
    std::string strResult;

    typedef std::pair<Ark_Union_Color_Number_String, std::string> OneTestStep;
    static const std::vector<OneTestStep> testPlan = {
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#FFFFFFFF"), "#FFFFFFFF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ff000000"), "#FF000000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ff0000ff"), "#FF0000FF" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ffa52a2a"), "#FFA52A2A" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ff808080"), "#FF808080" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ff008000"), "#FF008000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ffffa500"), "#FFFFA500" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ffffc0cb"), "#FFFFC0CB" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ffff0000"), "#FFFF0000" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#ffffff00"), "#FFFFFF00" },
        { Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_String>("#00000000"), "#00000000" },
    };

    for (const auto &[arkResColor, expected]: testPlan) {
        modifier_->setScrollBarColor(node_, &arkResColor);
        strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
        EXPECT_EQ(strResult, expected);
    }
}

/*
 * @tc.name: DISABLED_setScrollBarColorTestInvalidColorValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setScrollBarColorTestInvalidColorValues, TestSize.Level1)
{
    // test is disabled because Ark_Color can`t be converted to Color
}


/*
 * @tc.name: setScrollBarColorTestInvalidNumberValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarColorTestInvalidNumberValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Union_Color_Number_String inputValue;

    inputValue = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0xffffffff + 1);
    modifier_->setScrollBarColor(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
    EXPECT_EQ(strResult, "#00000000");

    inputValue = Converter::ArkUnion<Ark_Union_Color_Number_String, Ark_Number>(0x00000000 - 1);
    modifier_->setScrollBarColor(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_COLOR_NAME);
    EXPECT_EQ(strResult, "#FFFFFFFF");
}

/*
 * @tc.name: setScrollBarTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SCROLL_BAR_DEFAULT_VALUE);
}

/*
 * @tc.name: setScrollBarTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_BarState inputValue;

    // check Auto mode (default is Off mode)
    inputValue = ARK_BAR_STATE_AUTO;
    modifier_->setScrollBar(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, "BarState.Auto");

    // check On mode
    inputValue = ARK_BAR_STATE_ON;
    modifier_->setScrollBar(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, "BarState.On");

    // check Off mode
    inputValue = ARK_BAR_STATE_OFF;
    modifier_->setScrollBar(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, "BarState.Off");
}

/*
 * @tc.name: setScrollBarTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setScrollBarTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_BarState inputValue;

    // test invalid value which less then normal range
    inputValue = static_cast<Ark_BarState>(-1);
    modifier_->setScrollBar(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, "BarState.Auto");

    // test invalid value which more then normal range
    inputValue = static_cast<Ark_BarState>(3);
    modifier_->setScrollBar(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SCROLL_BAR_NAME);
    EXPECT_EQ(strResult, "BarState.Auto");
}

/*
 * @tc.name: setCachedCountTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCachedCountTestDefaultValues, TestSize.Level1)
{
    int intResult;

    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);
}

/*
 * @tc.name: setCachedCountTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCachedCountTestValidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Number>(0);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, 0);

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Number>(5);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MAX);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setCachedCountTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCachedCountTestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    modifier_->setCachedCount(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MIN);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Number>(-1);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Number>(2.2f);
    modifier_->setCachedCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, 2);
}

/*
 * @tc.name: setEditModeTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEditModeTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_EDIT_MODE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_EDIT_MODE_DEFAULT_VALUE);
}

/*
 * @tc.name: setEditModeTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEditModeTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    // check true value
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEditMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDIT_MODE_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEditMode(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDIT_MODE_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setMultiSelectableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMultiSelectableTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_MULTI_SELECTABLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MULTI_SELECTABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setMultiSelectableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMultiSelectableTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    // check true value
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setMultiSelectable(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MULTI_SELECTABLE_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setMultiSelectable(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MULTI_SELECTABLE_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setMaxCountTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMaxCountTestDefaultValues, TestSize.Level1)
{
    int intResult;

    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);
}

/*
 * @tc.name: setMaxCountTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMaxCountTestValidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Number>(5);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MAX);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setMaxCountTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMaxCountTestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    modifier_->setMaxCount(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Number>(0);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MIN);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Number>(-2);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Number>(5.3f);
    modifier_->setMaxCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, 5);
}

/*
 * @tc.name: setMinCountTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMinCountTestDefaultValues, TestSize.Level1)
{
    int intResult;

    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);
}

/*
 * @tc.name: setMinCountTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMinCountTestValidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Number>(5);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MAX);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setMinCountTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setMinCountTestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    modifier_->setMinCount(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Number>(0);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MIN);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Number>(-4);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Number>(6.4f);
    modifier_->setMinCount(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, 6);
}

/*
 * @tc.name: setCellLengthTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCellLengthTestDefaultValues, TestSize.Level1)
{
    int intResult;

    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CELL_LENGTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setCellLengthTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCellLengthTestValidValues, TestSize.Level1)
{
    int intResult;
    Ark_Number inputValue;

    // check 1 value
    inputValue = Converter::ArkValue<Ark_Number>(1);
    modifier_->setCellLength(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, 1);

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Number>(5);
    modifier_->setCellLength(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MAX);
    modifier_->setCellLength(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, INT_MAX);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Number>(INT_MIN);
    modifier_->setCellLength(node_, &inputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, INT_MIN);
}

/*
 * @tc.name: setCellLengthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCellLengthTestInvalidValues, TestSize.Level1)
{
    int intResult;
    modifier_->setCellLength(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CELL_LENGTH_DEFAULT_VALUE);
}

/*
 * @tc.name: setLayoutDirectionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setLayoutDirectionTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_LAYOUT_DIRECTION_DEFAULT_VALUE);
}

/*
 * @tc.name: setLayoutDirectionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setLayoutDirectionTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_GridDirection inputValue;

    // check Column direction
    inputValue = ARK_GRID_DIRECTION_COLUMN;
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Column");

    // check Row direction
    inputValue = ARK_GRID_DIRECTION_ROW;
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Row");

    // check Column Reverse direction
    inputValue = ARK_GRID_DIRECTION_COLUMN_REVERSE;
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.ColumnReverse");

    // check Row Reverse direction
    inputValue = ARK_GRID_DIRECTION_ROW_REVERSE;
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.RowReverse");
}

/*
 * @tc.name: setLayoutDirectionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setLayoutDirectionTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_GridDirection inputValue;

    // check value less then possible range
    inputValue = static_cast<Ark_GridDirection>(-1);
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Row");

    // check value more then possible range
    inputValue = static_cast<Ark_GridDirection>(4);
    modifier_->setLayoutDirection(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Row");
}

/*
 * @tc.name: setSupportAnimationTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setSupportAnimationTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SUPPORT_ANIMATION_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SUPPORT_ANIMATION_DEFAULT_VALUE);
}

/*
 * @tc.name: setSupportAnimationTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setSupportAnimationTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    // check true value
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setSupportAnimation(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUPPORT_ANIMATION_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setSupportAnimation(node_, inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUPPORT_ANIMATION_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setEdgeEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEdgeEffectTestDefaultValues, TestSize.Level1)
{
    std::string strResult;
    bool boolResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_EDGE_EFFECT_DEFAULT_VALUE);

    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_ALWAYS_ENABLED_DEFAULT_VALUE);
}

/*
 * @tc.name: setEdgeEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEdgeEffectTestValidValues, TestSize.Level1)
{
    std::string strResult;
    bool boolResult;
    Ark_EdgeEffect inputValue0;
    Opt_EdgeEffectOptions inputValue1;

    // EdgeEffect - Fade, alwaysEnabled - true
    inputValue0 = ARK_EDGE_EFFECT_FADE;
    inputValue1 = Converter::ArkValue<Opt_EdgeEffectOptions>(std::optional(true));
    modifier_->setEdgeEffect(node_, inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, "EdgeEffect.Fade");
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_TRUE(boolResult);

    // EdgeEffect - None, alwaysEnabled - undefined
    inputValue0 = ARK_EDGE_EFFECT_NONE;
    inputValue1 = Converter::ArkValue<Opt_EdgeEffectOptions>(Ark_Empty());
    modifier_->setEdgeEffect(node_, inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, "EdgeEffect.None");
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_FALSE(boolResult);

    // EdgeEffect - Spring, alwaysEnabled - false
    inputValue0 = ARK_EDGE_EFFECT_SPRING;
    inputValue1 = Converter::ArkValue<Opt_EdgeEffectOptions>(std::optional(false));
    modifier_->setEdgeEffect(node_, inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, "EdgeEffect.Spring");
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_FALSE(boolResult);
}

/*
 * @tc.name: setEdgeEffectTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEdgeEffectTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    bool boolResult;
    Ark_EdgeEffect inputValue0;
    Opt_EdgeEffectOptions inputValue1;

    // EdgeEffect - less then possible range, alwaysEnabled - undefined
    inputValue0 = static_cast<Ark_EdgeEffect>(-1);
    inputValue1 = Converter::ArkValue<Opt_EdgeEffectOptions>(Ark_Empty());
    modifier_->setEdgeEffect(node_, inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, "EdgeEffect.None");
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_FALSE(boolResult);

    // EdgeEffect - more then possible range, alwaysEnabled - undefined
    inputValue0 = static_cast<Ark_EdgeEffect>(3);
    inputValue1 = Converter::ArkValue<Opt_EdgeEffectOptions>(Ark_Empty());
    modifier_->setEdgeEffect(node_, inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_NAME);
    EXPECT_EQ(strResult, "EdgeEffect.None");
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDGE_EFFECT_OPTIONS_NAME);
    boolResult = GetAttrValue<bool>(strResult, ATTRIBUTE_ALWAYS_ENABLED_NAME);
    EXPECT_FALSE(boolResult);
}

/*
 * @tc.name: setNestedScrollTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setNestedScrollTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string strScrollForward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_FORWARD_NAME);
    std::string strScrollBackward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(strScrollForward, ATTRIBUTE_SCROLL_FORWARD_DEFAULT_VALUE);
    EXPECT_EQ(strScrollBackward, ATTRIBUTE_SCROLL_BACKWARD_DEFAULT_VALUE);
}

/*
 * @tc.name: setNestedScrollTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setNestedScrollTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_NestedScrollOptions inputValue;
    NestedScrollOptions nestedScrollOptions;

    nestedScrollOptions = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::PARALLEL,
    };
    inputValue = Converter::ArkValue<Ark_NestedScrollOptions>(nestedScrollOptions);
    modifier_->setNestedScroll(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NESTED_SCROLL_NAME);
    std::string strScrollForward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_FORWARD_NAME);
    std::string strScrollBackward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(strScrollForward, "NestedScrollMode.SELF_FIRST");
    EXPECT_EQ(strScrollBackward, "NestedScrollMode.PARALLEL");

    nestedScrollOptions = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    inputValue = Converter::ArkValue<Ark_NestedScrollOptions>(nestedScrollOptions);
    modifier_->setNestedScroll(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NESTED_SCROLL_NAME);
    strScrollForward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_FORWARD_NAME);
    strScrollBackward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(strScrollForward, "NestedScrollMode.PARENT_FIRST");
    EXPECT_EQ(strScrollBackward, "NestedScrollMode.SELF_ONLY");

    nestedScrollOptions = {
        .forward = NestedScrollMode::PARALLEL,
        .backward = NestedScrollMode::PARENT_FIRST,
    };
    inputValue = Converter::ArkValue<Ark_NestedScrollOptions>(nestedScrollOptions);
    modifier_->setNestedScroll(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NESTED_SCROLL_NAME);
    strScrollForward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_FORWARD_NAME);
    strScrollBackward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(strScrollForward, "NestedScrollMode.PARALLEL");
    EXPECT_EQ(strScrollBackward, "NestedScrollMode.PARENT_FIRST");

    nestedScrollOptions = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    inputValue = Converter::ArkValue<Ark_NestedScrollOptions>(nestedScrollOptions);
    modifier_->setNestedScroll(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_NESTED_SCROLL_NAME);
    strScrollForward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_FORWARD_NAME);
    strScrollBackward = GetAttrValue<std::string>(strResult, ATTRIBUTE_SCROLL_BACKWARD_NAME);
    EXPECT_EQ(strScrollForward, "NestedScrollMode.SELF_ONLY");
    EXPECT_EQ(strScrollBackward, "NestedScrollMode.SELF_FIRST");
}

/*
 * @tc.name: setEnableScrollInteractionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEnableScrollInteractionTestDefaultValues, TestSize.Level1)
{
    bool boolResult;

    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
    EXPECT_EQ(boolResult, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_DEFAULT_VALUE);
}

/*
 * @tc.name: setEnableScrollInteractionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setEnableScrollInteractionTestValidValues, TestSize.Level1)
{
    bool boolResult;
    Ark_Boolean inputValue;

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    modifier_->setEnableScrollInteraction(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
    EXPECT_FALSE(boolResult);

    // check true value
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    modifier_->setEnableScrollInteraction(node_, inputValue);
    boolResult = GetAttrValue<bool>(node_, ATTRIBUTE_ENABLE_SCROLL_INTERACTION_NAME);
    EXPECT_TRUE(boolResult);
}

/*
 * @tc.name: setFrictionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setFrictionTestDefaultValues, TestSize.Level1)
{
    double doubleResult;

    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, ATTRIBUTE_FRICTION_DEFAULT_VALUE, FLT_EPSILON);
}

/*
 * @tc.name: setFrictionTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setFrictionTestValidValues, TestSize.Level1)
{
    double doubleResult;
    Ark_Union_Number_Resource inputValue;

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(0.1f);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 0.1f, FLT_EPSILON);

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(0.9f);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 0.9f, FLT_EPSILON);

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(1.1f);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 1.1f, FLT_EPSILON);

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(123456);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 123456.f, FLT_EPSILON);
}

/*
 * @tc.name: setFrictionTestValidResourceValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setFrictionTestValidResourceValues, TestSize.Level1)
{
    double doubleResult;
    for (const auto &[value, expectVal]: UNION_NUMBER_RES_TEST_PLAN) {
        modifier_->setFriction(node_, &value);
        doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
        EXPECT_NEAR(doubleResult, expectVal, FLT_EPSILON);
    }
}

/*
 * @tc.name: setFrictionTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setFrictionTestInvalidValues, TestSize.Level1)
{
    double doubleResult;
    Ark_Union_Number_Resource inputValue;

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(0);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 0.6f, FLT_EPSILON);

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(-1);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 0.6f, FLT_EPSILON);

    inputValue = Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(-0.1f);
    modifier_->setFriction(node_, &inputValue);
    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_NEAR(doubleResult, 0.6f, FLT_EPSILON);
}

/*
 * @tc.name: setAlignItemsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setAlignItemsTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_DEFAULT_VALUE);
}

/*
 * @tc.name: setAlignItemsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
#ifdef WRONG_OPT
HWTEST_F(GridModifierTest, setAlignItemsTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Opt_GridItemAlignment inputValue;

    // check Stretch
    inputValue = Converter::ArkValue<Opt_GridItemAlignment>(std::optional(ARK_GRID_ITEM_ALIGNMENT_STRETCH));
    modifier_->setAlignItems(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME);
    EXPECT_EQ(strResult, "GridItemAlignment.Stretch");

    // check Default
    inputValue = Converter::ArkValue<Opt_GridItemAlignment>(std::optional(ARK_GRID_ITEM_ALIGNMENT_DEFAULT));
    modifier_->setAlignItems(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME);
    EXPECT_EQ(strResult, "GridItemAlignment.Default");
}

/*
 * @tc.name: setAlignItemsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setAlignItemsTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Opt_GridItemAlignment inputValue;

    // check undefined
    inputValue = Converter::ArkValue<Opt_GridItemAlignment>(Ark_Empty());
    modifier_->setAlignItems(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME);
    EXPECT_EQ(strResult, "GridItemAlignment.Default");
}
#endif // WRONG_OPT
} // namespace OHOS::Ace::NG
