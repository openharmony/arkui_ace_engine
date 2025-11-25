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
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"

#include "core/interfaces/native/implementation/scroller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"

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
    const auto RES_NAME = NamedResourceId{"aa.bb.cc", ResourceType::FLOAT};
    const auto RES_ID = IntResourceId{11111, ResourceType::FLOAT};

    // resource values
    const auto RESOURCE_OPACITY_BY_STRING = 0.4f;
    const auto RESOURCE_OPACITY_BY_NUMBER = 0.5f;

    using OneNumResStep = std::pair<Opt_Union_I32_Resource, float>;
    const std::vector<OneNumResStep> UNION_NUMBER_RES_TEST_PLAN = {
        { CreateResourceUnion<Opt_Union_I32_Resource>(RES_NAME), RESOURCE_OPACITY_BY_STRING },
        { CreateResourceUnion<Opt_Union_I32_Resource>(RES_ID), RESOURCE_OPACITY_BY_NUMBER },
    };

    const int64_t FAKE_RES_ID(1234);
    const Ark_Length RES_ARK_LENGTH = Converter::ArkValue<Ark_Length>(FAKE_RES_ID);
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
        SetupTheme<ScrollableTheme>();

        // set test values to Theme Pattern as data for the Theme building
        AddResource(RES_NAME, RESOURCE_OPACITY_BY_STRING);
        AddResource(RES_ID, RESOURCE_OPACITY_BY_NUMBER);
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

    layoutOptions.regularSize.value0 = Converter::ArkValue<Ark_Int32>(1);
    layoutOptions.regularSize.value1 = Converter::ArkValue<Ark_Int32>(1);
    std::vector<int32_t> indexes{1, 2, 3, 4, 5};
    Converter::ArkArrayHolder<Array_I32> indexesHolder(indexes);
    Array_I32 indexesArrayResult = indexesHolder.ArkValue();
    layoutOptions.irregularIndexes = Converter::ArkValue<Opt_Array_I32>(indexesArrayResult);
    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_GRID_OPTIONS_LAYOUT_OPTIONS_NAME);
    EXPECT_EQ(strResult, "true");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_REGULAR_SIZE_NAME);
    EXPECT_EQ(strResult, "[1,1]");
    strResult = GetStringAttribute(node_, ATTRIBUTE_SET_IRREGULAR_INDEXES_NAME);
    EXPECT_EQ(strResult, "[1,2,3,4,5]");

    layoutOptions.regularSize.value0 = Converter::ArkValue<Ark_Int32>(2);
    layoutOptions.regularSize.value1 = Converter::ArkValue<Ark_Int32>(2);
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
    auto peer = fullAPI_->getAccessors()->getScrollerAccessor()->construct();
    auto peerImplPtr = static_cast<ScrollerPeer *>(peer);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern, nullptr);

    Opt_Scroller inputValue0 = Converter::ArkValue<Opt_Scroller>(peerImplPtr);
    Opt_GridLayoutOptions inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(Ark_Empty());
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);

    RefPtr<ScrollControllerBase> positionController = pattern->GetOrCreatePositionController();
    EXPECT_NE(positionController, nullptr);
    RefPtr<ScrollProxy> scrollBarProxy = pattern->GetScrollBarProxy();
    EXPECT_NE(scrollBarProxy, nullptr);

    EXPECT_EQ(peerImplPtr->GetController(), positionController);
    EXPECT_EQ(peerImplPtr->GetScrollBarProxy(), scrollBarProxy);

    Ark_NativePointer finalizerPtr =
        fullAPI_->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(peerImplPtr);
}

/*
 * @tc.name: setGridOptionsTestInvalidScrollerValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsTestInvalidScrollerValues, TestSize.Level1)
{
    auto peer = fullAPI_->getAccessors()->getScrollerAccessor()->construct();
    auto peerImplPtr = static_cast<ScrollerPeer *>(peer);
    EXPECT_NE(peerImplPtr, nullptr);

    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    EXPECT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<GridPattern>();
    EXPECT_NE(pattern, nullptr);

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
        fullAPI_->getAccessors()->getScrollerAccessor()->getFinalizer();
    auto finalyzer = reinterpret_cast<void (*)(ScrollerPeer *)>(finalizerPtr);
    finalyzer(peerImplPtr);
}

/**
 * @tc.name: setGridOptionsGetSizeByIndex
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsGetSizeByIndex, TestSize.Level1)
{
    static const int32_t expectedResId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        int32_t info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Int32 parameter,
        const Callback_Tuple_I32_I32_Void continuation) {
        int32_t info = Converter::Convert<int32_t>(parameter);

        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        Ark_Tuple_I32_I32 arkRes;
        arkRes.value0 = ArkValue<Ark_Int32>(1);
        arkRes.value1 = ArkValue<Ark_Int32>(1);
        CallbackHelper(continuation).InvokeSync(arkRes);
    };
    auto func = Converter::ArkValue<Callback_I32_Tuple_I32_I32>(nullptr, inputCallback, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_Callback_I32_Tuple_I32_I32>(func);

    Opt_Scroller inputValue0;
    Ark_GridLayoutOptions layoutOptions;
    Opt_GridLayoutOptions inputValue1;
    layoutOptions.onGetIrregularSizeByIndex = optFunc;
    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);

    auto property = frameNode->GetLayoutProperty<GridLayoutProperty>();
    auto options = property->GetLayoutOptions();
    auto getSizeByIndex = options->getSizeByIndex;
    getSizeByIndex(123);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
}

/**
 * @tc.name: setGridOptionsGetRectByIndex
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setGridOptionsGetRectByIndex, TestSize.Level1)
{
    static const int32_t expectedResId = 123;
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);

    struct CheckEvent {
        int32_t resourceId;
        int32_t info;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto inputCallback = [] (Ark_VMContext context, const Ark_Int32 resourceId,
        const Ark_Int32 parameter,
        const Callback_Tuple_I32_I32_I32_I32_Void continuation) {
        int32_t info = Converter::Convert<int32_t>(parameter);

        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .info = info,
        };
        Ark_Tuple_I32_I32_I32_I32 arkRes;
        arkRes.value0 = ArkValue<Ark_Int32>(-1);
        arkRes.value1 = ArkValue<Ark_Int32>(1);
        arkRes.value0 = ArkValue<Ark_Int32>(-1);
        arkRes.value1 = ArkValue<Ark_Int32>(1);
        CallbackHelper(continuation).InvokeSync(arkRes);
    };
    auto func = Converter::ArkValue<Callback_I32_Tuple_I32_I32_I32_I32>
                                                    (nullptr, inputCallback, expectedResId);
    auto optFunc = Converter::ArkValue<Opt_Callback_I32_Tuple_I32_I32_I32_I32>(func);
    Opt_Scroller inputValue0;
    Ark_GridLayoutOptions layoutOptions;
    Opt_GridLayoutOptions inputValue1;
    layoutOptions.onGetRectByIndex = optFunc;

    inputValue1 = Converter::ArkValue<Opt_GridLayoutOptions>(layoutOptions);
    modifier_->setGridOptions(node_, &inputValue0, &inputValue1);

    auto property = frameNode->GetLayoutProperty<GridLayoutProperty>();
    auto options = property->GetLayoutOptions();
    auto getRectByIndex = options->getRectByIndex;
    getRectByIndex(123);
    ASSERT_TRUE(checkEvent);
    EXPECT_EQ(checkEvent->resourceId, expectedResId);
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
    auto optInputValue = Converter::ArkValue<Opt_String>(inputValue);
    modifier_->setColumnsTemplate(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr 1fr 1fr");

    // check '2fr' template
    inputValue = Converter::ArkValue<Ark_String>("2fr");
    optInputValue = Converter::ArkValue<Opt_String>(inputValue);
    modifier_->setColumnsTemplate(node_, &optInputValue);
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
    Opt_String inputValue;
    auto initValue = Converter::ArkValue<Opt_String>("1fr");

    // check empty template
    inputValue = Converter::ArkValue<Opt_String>("");
    modifier_->setColumnsTemplate(node_, &initValue);
    modifier_->setColumnsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE);

    inputValue = Converter::ArkValue<Opt_String>();
    modifier_->setColumnsTemplate(node_, &initValue);
    modifier_->setColumnsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMNS_TEMPLATE_DEFAULT_VALUE);
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
    auto optInputValue = Converter::ArkValue<Opt_String>(inputValue);
    modifier_->setRowsTemplate(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, "1fr 1fr 1fr");

    // check '2fr' template
    inputValue = Converter::ArkValue<Ark_String>("2fr");
    optInputValue = Converter::ArkValue<Opt_String>(inputValue);
    modifier_->setRowsTemplate(node_, &optInputValue);
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
    Opt_String inputValue;
    auto initValue = Converter::ArkValue<Opt_String>("1fr");

    // check empty template
    inputValue = Converter::ArkValue<Opt_String>("");
    modifier_->setRowsTemplate(node_, &initValue);
    modifier_->setRowsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE);

    inputValue = Converter::ArkValue<Opt_String>();
    modifier_->setRowsTemplate(node_, &initValue);
    modifier_->setRowsTemplate(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_TEMPLATE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROWS_TEMPLATE_DEFAULT_VALUE);
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

    // set 2vp
    inputValue = Converter::ArkValue<Ark_Length>(2.f);
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setColumnsGap(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "2.00vp");

    // set 50.35vp
    inputValue = Converter::ArkValue<Ark_Length>(50.35f);
    optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setColumnsGap(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "50.35vp");

    // set 0vp
    inputValue = Converter::ArkValue<Ark_Length>(0.f);
    optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setColumnsGap(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setColumnsGap(node_, &optInputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMNS_GAP_NAME);
    EXPECT_EQ(strResult, "10.00px");
}

/*
 * @tc.name: setColumnsGapTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setColumnsGapTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set -1vp
    inputValue = Converter::ArkValue<Ark_Length>(-1.f);
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setColumnsGap(node_, &optInputValue);
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

    // set 2vp
    inputValue = Converter::ArkValue<Ark_Length>(2.f);
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setRowsGap(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "2.00vp");

    // set 50.35vp
    inputValue = Converter::ArkValue<Ark_Length>(50.35f);
    optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setRowsGap(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "50.35vp");

    // set 0vp
    inputValue = Converter::ArkValue<Ark_Length>(0.f);
    optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setRowsGap(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setRowsGap(node_, &optInputValue);
    auto strResult = GetStringAttribute(node_, ATTRIBUTE_ROWS_GAP_NAME);
    EXPECT_EQ(strResult, "10.00px");
}

/*
 * @tc.name: setRowsGapTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setRowsGapTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Length inputValue;

    // set -1vp
    inputValue = Converter::ArkValue<Ark_Length>(-1.f);
    auto optInputValue = Converter::ArkValue<Opt_Length>(inputValue);
    modifier_->setRowsGap(node_, &optInputValue);
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
 * @tc.name: setCachedCount0TestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCachedCount0TestDefaultValues, TestSize.Level1)
{
    int intResult;

    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);
}

/*
 * @tc.name: setCachedCount0TestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setCachedCount0TestValidValues, TestSize.Level1)
{
    int intResult;
    Ark_Int32 inputValue;

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Int32>(0);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, 0);

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Int32>(5);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MAX);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setCachedCount0TestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setCachedCount0TestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Int32 inputValue;

    modifier_->setCachedCount0(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MIN);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Int32>(-1);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CACHED_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_CACHED_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Int32>(2.2f);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setCachedCount0(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setEditMode(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_EDIT_MODE_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setEditMode(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setMultiSelectable(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_MULTI_SELECTABLE_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setMultiSelectable(node_, &optInputValue);
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
    Ark_Int32 inputValue;

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Int32>(5);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MAX);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setMaxCountTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setMaxCountTestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Int32 inputValue;

    modifier_->setMaxCount(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Int32>(0);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MIN);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Int32>(-2);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MAX_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MAX_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Int32>(5.3f);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMaxCount(node_, &optInputValue);
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
    Ark_Int32 inputValue;

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Int32>(5);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MAX);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, INT_MAX);
}

/*
 * @tc.name: setMinCountTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setMinCountTestInvalidValues, TestSize.Level1)
{
    int intResult;
    Ark_Int32 inputValue;

    modifier_->setMinCount(node_, nullptr);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check 0 value
    inputValue = Converter::ArkValue<Ark_Int32>(0);
    auto optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Int32>(INT_MIN);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check negative value
    inputValue = Converter::ArkValue<Ark_Int32>(-4);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_MIN_COUNT_NAME);
    EXPECT_EQ(intResult, ATTRIBUTE_MIN_COUNT_DEFAULT_VALUE);

    // check float value
    inputValue = Converter::ArkValue<Ark_Int32>(6.4f);
    optInputValue = Converter::ArkValue<Opt_Int32>(inputValue);
    modifier_->setMinCount(node_, &optInputValue);
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
    Ark_Float64 inputValue;

    // check 1 value
    inputValue = Converter::ArkValue<Ark_Float64>(1);
    auto optInputValue = Converter::ArkValue<Opt_Float64>(inputValue);
    modifier_->setCellLength(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, 1);

    // check 5 value
    inputValue = Converter::ArkValue<Ark_Float64>(5);
    optInputValue = Converter::ArkValue<Opt_Float64>(inputValue);
    modifier_->setCellLength(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, 5);

    // check maximum value
    inputValue = Converter::ArkValue<Ark_Float64>(INT_MAX);
    optInputValue = Converter::ArkValue<Opt_Float64>(inputValue);
    modifier_->setCellLength(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, INT_MAX);

    // check minimum value
    inputValue = Converter::ArkValue<Ark_Float64>(INT_MIN);
    optInputValue = Converter::ArkValue<Opt_Float64>(inputValue);
    modifier_->setCellLength(node_, &optInputValue);
    intResult = GetAttrValue<int>(node_, ATTRIBUTE_CELL_LENGTH_NAME);
    EXPECT_EQ(intResult, INT_MIN);
}

/*
 * @tc.name: setCellLengthTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, DISABLED_setCellLengthTestInvalidValues, TestSize.Level1)
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
    auto optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Column");

    // check Row direction
    inputValue = ARK_GRID_DIRECTION_ROW;
    optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Row");

    // check Column Reverse direction
    inputValue = ARK_GRID_DIRECTION_COLUMN_REVERSE;
    optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.ColumnReverse");

    // check Row Reverse direction
    inputValue = ARK_GRID_DIRECTION_ROW_REVERSE;
    optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_LAYOUT_DIRECTION_NAME);
    EXPECT_EQ(strResult, "GridDirection.Row");

    // check value more then possible range
    inputValue = static_cast<Ark_GridDirection>(4);
    optInputValue = Converter::ArkValue<Opt_GridDirection>(inputValue);
    modifier_->setLayoutDirection(node_, &optInputValue);
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
    auto optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setSupportAnimation(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SUPPORT_ANIMATION_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setSupportAnimation(node_, &optInputValue);
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
 * @tc.name: setFrictionTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridModifierTest, setFrictionTestDefaultValues, TestSize.Level1)
{
    double doubleResult;

    auto columnsStr = ArkValue<Ark_String>("1fr 1fr 2fr");
    auto optColumnsStr = Converter::ArkValue<Opt_String>(columnsStr);
    modifier_->setColumnsTemplate(node_, &optColumnsStr);
    OnModifyDone();

    doubleResult = GetAttrValue<double>(node_, ATTRIBUTE_FRICTION_NAME);
    EXPECT_DOUBLE_EQ(doubleResult, ATTRIBUTE_FRICTION_DEFAULT_VALUE);
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
HWTEST_F(GridModifierTest, setAlignItemsTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Opt_GridItemAlignment inputValue;

    // check Stretch
    inputValue = Converter::ArkValue<Opt_GridItemAlignment>(ARK_GRID_ITEM_ALIGNMENT_STRETCH);
    modifier_->setAlignItems(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ALIGN_ITEMS_ALIGNMENT_NAME);
    EXPECT_EQ(strResult, "GridItemAlignment.Stretch");

    // check Default
    inputValue = Converter::ArkValue<Opt_GridItemAlignment>(ARK_GRID_ITEM_ALIGNMENT_DEFAULT);
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
} // namespace OHOS::Ace::NG
