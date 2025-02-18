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

static constexpr int SIZE1 = 111;
static constexpr int SIZE2 = 222;

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
    modifier_->setSelectedColor(node_, &color);
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
    modifier_->setUnselectedColor(node_, &color);
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
    modifier_->setSelectAll(node_, true);
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
    Ark_Length len1 = { .value = SIZE1 };
    Ark_Length len2 = { .value = SIZE2 };
    Opt_Length opt1 = { .tag = ARK_TAG_INT32, .value = len1 };
    Opt_Length opt2 = { .tag = ARK_TAG_INT32, .value = len2 };
    style.strokeColor.value = color;
    style.size = opt1;
    style.strokeWidth = opt2;
    modifier_->setMark(node_, &style);

    auto* frameNode = reinterpret_cast<FrameNode*>(node_);
    const InspectorFilter inspector;
    auto jsonVal = JsonUtil::Create(true);
    frameNode->ToJsonValue(jsonVal, inspector);
    auto mark = jsonVal->GetValue("mark");

    auto checkVal1 = mark->GetString("strokeColor");
    EXPECT_EQ(checkVal1, "#FF123456");

    auto checkVal2 = mark->GetString("size");
    EXPECT_EQ(checkVal2, "111.00px");

    auto checkVal3 = mark->GetString("strokeWidth");
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

    modifier_->setCheckboxShape(node_, ARK_CHECK_BOX_SHAPE_ROUNDED_SQUARE);
    auto checkVal2 = GetStringAttribute(node_, "checkboxShape");
    EXPECT_EQ(checkVal2, "ROUNDED_SQUARE");

    modifier_->setCheckboxShape(node_, ARK_CHECK_BOX_SHAPE_CIRCLE);
    auto checkVal3 = GetStringAttribute(node_, "checkboxShape");
    EXPECT_EQ(checkVal3, "CIRCLE");
}

/**
 * @tc.name: SetOnChangeTest
 * @tc.desc: onChange event test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, SetOnChangeTest, TestSize.Level1)
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
    modifier_->setOnChange(node_, &arkCallback);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    ASSERT_NE(eventHub, nullptr);
    CheckboxGroupResult info({"test1", "test2"}, 2);
    eventHub->UpdateChangeEvent(&info);
    ASSERT_TRUE(checkEvent.has_value());
    EXPECT_EQ(checkEvent->resourceId, frameNode->GetId());
    EXPECT_EQ(checkEvent->result.GetNameList(), info.GetNameList());
    EXPECT_EQ(checkEvent->result.GetStatus(), info.GetStatus());
}

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
        bool value;
    };
    static std::optional<CheckEvent> checkEvent = std::nullopt;
    static constexpr int32_t contextId = 123;

    auto checkCallback = [](const Ark_Int32 resourceId, const Ark_Boolean parameter) {
        checkEvent = {
            .nodeId = resourceId,
            .value = Converter::Convert<bool>(parameter)
        };
    };

    Callback_Boolean_Void arkCallback = Converter::ArkValue<Callback_Boolean_Void>(checkCallback, contextId);

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
} // namespace OHOS::Ace::NG
