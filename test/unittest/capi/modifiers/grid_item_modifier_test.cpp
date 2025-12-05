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

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"

#include "core/components_ng/pattern/grid/grid_item_event_hub.h"
#include "core/components_ng/pattern/grid/grid_item_theme.h"

#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_STYLE_NAME = "style";
    const auto ATTRIBUTE_STYLE_DEFAULT_VALUE = "NONE";
    const auto ATTRIBUTE_ROW_START_NAME = "rowStart";
    const auto ATTRIBUTE_ROW_START_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_ROW_END_NAME = "rowEnd";
    const auto ATTRIBUTE_ROW_END_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_COLUMN_START_NAME = "columnStart";
    const auto ATTRIBUTE_COLUMN_START_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_COLUMN_END_NAME = "columnEnd";
    const auto ATTRIBUTE_COLUMN_END_DEFAULT_VALUE = "0";
    const auto ATTRIBUTE_FORCE_REBUILD_NAME = "forceRebuild";
    const auto ATTRIBUTE_FORCE_REBUILD_DEFAULT_VALUE = "false";
    const auto ATTRIBUTE_SELECTABLE_NAME = "selectable";
    const auto ATTRIBUTE_SELECTABLE_DEFAULT_VALUE = "true";
    const auto ATTRIBUTE_SELECTED_NAME = "selected";
    const auto ATTRIBUTE_SELECTED_DEFAULT_VALUE = "false";
} // namespace

class GridItemModifierTest : public ModifierTestBase<GENERATED_ArkUIGridItemModifier,
    &GENERATED_ArkUINodeModifiers::getGridItemModifier, GENERATED_ARKUI_GRID_ITEM> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<GridItemTheme>();
    }
};

/*
 * @tc.name: setGridItemOptionsTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setGridItemOptionsTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_STYLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setGridItemOptionsTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setGridItemOptionsTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_GridItemOptions options;
    Opt_GridItemOptions opt_options;

    // check PLAIN style
    options.style = Converter::ArkValue<Opt_GridItemStyle>(ARK_GRID_ITEM_STYLE_PLAIN);
    opt_options = Converter::ArkValue<Opt_GridItemOptions>(options);
    modifier_->setGridItemOptions(node_, &opt_options);
    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(strResult, "PLAIN");

    // check NONE style
    options.style = Converter::ArkValue<Opt_GridItemStyle>(ARK_GRID_ITEM_STYLE_NONE);
    opt_options = Converter::ArkValue<Opt_GridItemOptions>(options);
    modifier_->setGridItemOptions(node_, &opt_options);
    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(strResult, "NONE");
}

/*
 * @tc.name: setGridItemOptionsTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setGridItemOptionsTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    Opt_GridItemOptions inputValue = Converter::ArkValue<Opt_GridItemOptions>(Ark_Empty());

    // check that style is not changed
    modifier_->setGridItemOptions(node_, &inputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_STYLE_NAME);
    EXPECT_EQ(strResult, "NONE");
}

/*
 * @tc.name: setRowStartTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setRowStartTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_START_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROW_START_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowStartTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setRowStartTestValidValues, TestSize.Level1)
{
    std::string strResult;

    // check positive value
    auto optInputValue = Converter::ArkValue<Opt_Int32>(1);
    modifier_->setRowStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_START_NAME);
    EXPECT_EQ(strResult, "1");

    // check another positive value
    optInputValue = Converter::ArkValue<Opt_Int32>(5);
    modifier_->setRowStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_START_NAME);
    EXPECT_EQ(strResult, "5");

    // check negative value
    optInputValue = Converter::ArkValue<Opt_Int32>(-10);
    modifier_->setRowStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_START_NAME);
    EXPECT_EQ(strResult, "-10");
}

/*
 * @tc.name: setRowStartTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, DISABLED_setRowStartTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    modifier_->setRowStart(node_, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_START_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROW_START_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setRowEndTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_END_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROW_END_DEFAULT_VALUE);
}

/*
 * @tc.name: setRowEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setRowEndTestValidValues, TestSize.Level1)
{
    std::string strResult;

    // check positive value
    auto optInputValue = Converter::ArkValue<Opt_Int32>(1);
    modifier_->setRowEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_END_NAME);
    EXPECT_EQ(strResult, "1");

    // check another positive value
    optInputValue = Converter::ArkValue<Opt_Int32>(5);
    modifier_->setRowEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_END_NAME);
    EXPECT_EQ(strResult, "5");

    // check negative value
    optInputValue = Converter::ArkValue<Opt_Int32>(-10);
    modifier_->setRowEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_END_NAME);
    EXPECT_EQ(strResult, "-10");
}

/*
 * @tc.name: setRowEndTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, DISABLED_setRowEndTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    modifier_->setRowEnd(node_, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_ROW_END_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ROW_END_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnStartTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setColumnStartTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_START_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMN_START_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnStartTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setColumnStartTestValidValues, TestSize.Level1)
{
    std::string strResult;

    // check positive value
    auto optInputValue = Converter::ArkValue<Opt_Int32>(1);
    modifier_->setColumnStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_START_NAME);
    EXPECT_EQ(strResult, "1");

    // check another positive value
    optInputValue = Converter::ArkValue<Opt_Int32>(5);
    modifier_->setColumnStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_START_NAME);
    EXPECT_EQ(strResult, "5");

    // check negative value
    optInputValue = Converter::ArkValue<Opt_Int32>(-10);
    modifier_->setColumnStart(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_START_NAME);
    EXPECT_EQ(strResult, "-10");
}

/*
 * @tc.name: setColumnStartTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, DISABLED_setColumnStartTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    modifier_->setColumnStart(node_, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_START_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMN_START_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnEndTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setColumnEndTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_END_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMN_END_DEFAULT_VALUE);
}

/*
 * @tc.name: setColumnEndTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setColumnEndTestValidValues, TestSize.Level1)
{
    std::string strResult;

    // check positive value
    auto optInputValue = Converter::ArkValue<Opt_Int32>(1);
    modifier_->setColumnEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_END_NAME);
    EXPECT_EQ(strResult, "1");

    // check another positive value
    optInputValue = Converter::ArkValue<Opt_Int32>(5);
    modifier_->setColumnEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_END_NAME);
    EXPECT_EQ(strResult, "5");

    // check negative value
    optInputValue = Converter::ArkValue<Opt_Int32>(-10);
    modifier_->setColumnEnd(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_END_NAME);
    EXPECT_EQ(strResult, "-10");
}

/*
 * @tc.name: setColumnEndTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, DISABLED_setColumnEndTestInvalidValues, TestSize.Level1)
{
    std::string strResult;
    modifier_->setColumnEnd(node_, nullptr);
    strResult = GetStringAttribute(node_, ATTRIBUTE_COLUMN_END_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_COLUMN_END_DEFAULT_VALUE);
}

/*
 * @tc.name: setForceRebuildTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setForceRebuildTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_FORCE_REBUILD_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_FORCE_REBUILD_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setSelectableTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTABLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SELECTABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setSelectableTestValidValues, TestSize.Level1)
{
    std::string strResult;
    Ark_Boolean inputValue;

    // check false value
    inputValue = Converter::ArkValue<Ark_Boolean>(false);
    auto optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setSelectable(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTABLE_NAME);
    EXPECT_EQ(strResult, "false");

    // check true value
    inputValue = Converter::ArkValue<Ark_Boolean>(true);
    optInputValue = Converter::ArkValue<Opt_Boolean>(inputValue);
    modifier_->setSelectable(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTABLE_NAME);
    EXPECT_EQ(strResult, "true");
}

/*
 * @tc.name: setSelectedTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setSelectedTestDefaultValues, TestSize.Level1)
{
    std::string strResult;

    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_SELECTED_DEFAULT_VALUE);
}

/*
 * @tc.name: setSelectedTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setSelectedTestValidValues, TestSize.Level1)
{
    std::string strResult;

    // check true value
    auto optInputValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(true);
    modifier_->setSelected(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(strResult, "true");

    // check false value
    optInputValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable_Boolean, Ark_Boolean>(false);
    modifier_->setSelected(node_, &optInputValue);
    strResult = GetStringAttribute(node_, ATTRIBUTE_SELECTED_NAME);
    EXPECT_EQ(strResult, "false");
}

/*
 * @tc.name: setOnSelectTest
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setOnSelectTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();

    struct CheckEvent {
        int32_t nodeId;
        bool isSelected;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    Callback_Boolean_Void onSelect = {
        .resource = {.resourceId = frameNode->GetId()},
        .call = [](Ark_Int32 nodeId, const Ark_Boolean isSelected) {
            checkEvent = {
                .nodeId = nodeId,
                .isSelected = Converter::Convert<bool>(isSelected)
            };
        }
    };

    auto optOnSelect = Converter::ArkValue<Opt_Callback_Boolean_Void>(onSelect);
    modifier_->setOnSelect(node_, &optOnSelect);

    // check true value
    EXPECT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectChangeEvent(true);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isSelected, true);

    // check false value
    eventHub->FireSelectChangeEvent(false);
    EXPECT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, frameNode->GetId());
    EXPECT_EQ(checkEvent->isSelected, false);
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelectedImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(GridItemModifierTest, setOnChangeEventSelectedImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::OptConvert<bool>(parameter)
        };
    };

    Callback_Opt_Boolean_Void arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_selected(node_, &arkCallback);

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->FireSelectChangeEvent(true);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->FireSelectChangeEvent(false);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
