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

#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

namespace Converter {
    template<>
    void AssignCast(std::optional<int32_t>& dst, const Ark_SelectStatus& src)
    {
        switch (src) {
            case ARK_SELECT_STATUS_ALL: dst = static_cast<int32_t>(ARK_SELECT_STATUS_ALL); break;
            case ARK_SELECT_STATUS_PART: dst = static_cast<int32_t>(ARK_SELECT_STATUS_PART); break;
            case ARK_SELECT_STATUS_NONE: dst = static_cast<int32_t>(ARK_SELECT_STATUS_NONE); break;
            default:
                LOGE("Unexpected enum value in SelectStatus: %{public}d", src);
        }
    }
    template<>
    CheckboxGroupResult Convert(const Ark_CheckboxGroupResult& src)
    {
        CheckboxGroupResult result(Converter::Convert<std::vector<std::string>>(src.name),
            Converter::OptConvert<int32_t>(src.status).value_or(static_cast<int32_t>(ARK_SELECT_STATUS_NONE)));
        return result;
    }
}

class CheckboxGroupModifierTest : public ModifierTestBase<GENERATED_ArkUICheckboxGroupModifier,
    &GENERATED_ArkUINodeModifiers::getCheckboxGroupModifier, GENERATED_ARKUI_CHECKBOX_GROUP> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<CheckboxTheme>();
    }
};

/**
 * @tc.name: CheckboxGroupModifierTest001
 * @tc.desc: setSelectedColor test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, CheckboxGroupModifierTest001, TestSize.Level1)
{
    auto checkVal1 = GetStringAttribute(node_, "selectedColor");
    EXPECT_EQ(checkVal1, "#FF007DFF");
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF123456);
    auto optColor = Converter::ArkValue<Opt_ResourceColor>(color);
    modifier_->setSelectedColor(node_, &optColor);
    auto checkVal2 = GetStringAttribute(node_, "selectedColor");
    EXPECT_EQ(checkVal2, "#FF123456");
}

/**
 * @tc.name: CheckboxGroupModifierTest002
 * @tc.desc: setUnselectedColor test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, CheckboxGroupModifierTest002, TestSize.Level1)
{
    auto checkVal1 = GetStringAttribute(node_, "unselectedColor");
    EXPECT_EQ(checkVal1, "#FF000000");
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF123456);
    auto optColor = Converter::ArkValue<Opt_ResourceColor>(color);
    modifier_->setUnselectedColor(node_, &optColor);
    auto checkVal2 = GetStringAttribute(node_, "unselectedColor");
    EXPECT_EQ(checkVal2, "#FF123456");
}

/**
 * @tc.name: CheckboxGroupModifierTest003
 * @tc.desc: setSelectAll test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, CheckboxGroupModifierTest003, TestSize.Level1)
{
    auto checkVal1 = GetStringAttribute(node_, "selectAll");
    EXPECT_EQ(checkVal1, "false");
    auto optValue = Converter::ArkUnion<Opt_Union_Boolean_Bindable, Ark_Boolean>(true);
    modifier_->setSelectAll(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, "selectAll");
    EXPECT_EQ(checkVal2, "true");
}

/**
 * @tc.name: CheckboxGroupModifierTest004
 * @tc.desc: setMark test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, CheckboxGroupModifierTest004, TestSize.Level1)
{
    Ark_MarkStyle style;
    Ark_ResourceColor color = Converter::ArkUnion<Ark_ResourceColor, Ark_Number>(0xFF123456);
    style.strokeColor.value = color;
    style.size = Converter::ArkValue<Opt_Length>("111.00px");
    style.strokeWidth = Converter::ArkValue<Opt_Length>("222.00px");
    auto optStyle = Converter::ArkValue<Opt_MarkStyle>(style);
    modifier_->setMark(node_, &optStyle);

    auto jsonValue = GetJsonValue(node_);
    auto mark = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, "mark");

    auto checkVal1 = GetAttrValue<std::string>(mark, "strokeColor");
    EXPECT_EQ(checkVal1, "#FF123456");

    auto checkVal2 = GetAttrValue<std::string>(mark, "size");
    EXPECT_EQ(checkVal2, "111.00px");

    auto checkVal3 = GetAttrValue<std::string>(mark, "strokeWidth");
    EXPECT_EQ(checkVal3, "222.00px");
}

/**
 * @tc.name: CheckboxGroupModifierTest005
 * @tc.desc: setCheckboxShape test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, DISABLED_CheckboxGroupModifierTest005, TestSize.Level1)
{
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        return;
    }
    auto checkVal1 = GetStringAttribute(node_, "checkboxShape");
    EXPECT_EQ(checkVal1, "CIRCLE");
    auto optValue = Converter::ArkValue<Opt_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE);
    modifier_->setCheckboxShape(node_, &optValue);
    auto checkVal2 = GetStringAttribute(node_, "checkboxShape");
    EXPECT_EQ(checkVal2, "ROUNDED_SQUARE");
    optValue = Converter::ArkValue<Opt_CheckBoxShape>(ARK_CHECK_BOX_SHAPE_CIRCLE);
    modifier_->setCheckboxShape(node_, &optValue);
    auto checkVal3 = GetStringAttribute(node_, "checkboxShape");
    EXPECT_EQ(checkVal3, "CIRCLE");
}

/**
 * @tc.name: SetOnChangeTest
 * @tc.desc: onChange event test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, DISABLED_SetOnChangeTest, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    struct CheckEvent {
        int32_t resourceId;
        CheckboxGroupResult result;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    auto testCallback = [](const Ark_Int32 resourceId, const Ark_CheckboxGroupResult result) {
        checkEvent = {
            .resourceId = Converter::Convert<int32_t>(resourceId),
            .result = Converter::Convert<CheckboxGroupResult>(result),
        };
    };
    auto arkCallback = Converter::ArkValue<OnCheckboxGroupChangeCallback>(testCallback, frameNode->GetId());
    auto optCallback = Converter::ArkValue<Opt_OnCheckboxGroupChangeCallback>(arkCallback);
    modifier_->setOnChange(node_, &optCallback);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    CheckboxGroupResult info({"test1", "test2"}, 2);
    eventHub->UpdateChangeEvent(&info);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->result.GetNameList(), info.GetNameList());
    EXPECT_EQ(checkEvent->result.GetStatus(), info.GetStatus());
}

#ifdef WRONG_OLD_GEN
/*
 * @tc.name: setOnChangeEventSelectAllImpl
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, setOnChangeEventSelectAllImpl, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);

    struct CheckEvent {
        int32_t nodeId;
        std::optional<bool> value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;
    auto checkCallback = [](const Ark_Int32 resourceId, const Opt_Boolean parameter) {
        auto param = Converter::OptConvert<bool>(parameter);
        checkEvent = {
            .nodeId = resourceId,
            .value = param
        };
    };

    auto arkCallback = Converter::ArkValue<Callback_Opt_Boolean_Void>(checkCallback, contextId);
    modifier_->set_onChangeEvent_selectAll(node_, &arkCallback);

    std::vector<std::string> vec;
    CheckboxGroupResult groupResultAll(vec, int(CheckBoxGroupPaintProperty::SelectStatus::ALL));
    CheckboxGroupResult groupResultPart(vec, int(CheckBoxGroupPaintProperty::SelectStatus::PART));
    CheckboxGroupResult groupResultNone(vec, int(CheckBoxGroupPaintProperty::SelectStatus::NONE));

    ASSERT_EQ(checkEvent.has_value(), false);
    eventHub->UpdateChangeEvent(&groupResultAll);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, true);
    eventHub->UpdateChangeEvent(&groupResultPart);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
    eventHub->UpdateChangeEvent(&groupResultNone);
    ASSERT_EQ(checkEvent.has_value(), true);
    EXPECT_EQ(checkEvent->nodeId, contextId);
    EXPECT_EQ(checkEvent->value, false);
}
#endif
} // namespace OHOS::Ace::NG
