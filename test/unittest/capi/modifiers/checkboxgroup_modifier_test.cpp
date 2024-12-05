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

#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {

using namespace testing;
using namespace testing::ext;

static bool g_isCheckedTest = false;
static constexpr int SIZE1 = 111;
static constexpr int SIZE2 = 222;

static void onChangeCallback(Ark_Int32 nodeId, const Ark_CheckboxGroupResult event)
{
    g_isCheckedTest = !g_isCheckedTest;
};
static GENERATED_ArkUICheckboxGroupEventsReceiver recv {
    .onChange = onChangeCallback
};
static const GENERATED_ArkUICheckboxGroupEventsReceiver* getEventsReceiverTest()
{
    return &recv;
};

static const GENERATED_ArkUIEventsAPI* GetArkUiEventsAPITest()
{
    static const GENERATED_ArkUIEventsAPI eventsImpl = { .getCheckboxGroupEventsReceiver = getEventsReceiverTest };
    return &eventsImpl;
};

class CheckboxGroupModifierTest : public ModifierTestBase<GENERATED_ArkUICheckboxGroupModifier,
    &GENERATED_ArkUINodeModifiers::getCheckboxGroupModifier, GENERATED_ARKUI_CHECKBOX_GROUP> {
public:
    static void SetUpTestCase()
    {
        ModifierTestBase::SetUpTestCase();

        SetupTheme<CheckboxTheme>();

        fullAPI_->setArkUIEventsAPI(GetArkUiEventsAPITest());
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
 * @tc.name: CheckboxGroupModifierTest006
 * @tc.desc: onChange event test
 * @tc.type: FUNC
 */
HWTEST_F(CheckboxGroupModifierTest, CheckboxGroupModifierTest006, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    OnCheckboxGroupChangeCallback func{};
    modifier_->setOnChange(node_, &func);
    EXPECT_EQ(g_isCheckedTest, false);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();

    CheckboxGroupResult info({}, 0);
    eventHub->UpdateChangeEvent(&info);
    EXPECT_EQ(g_isCheckedTest, true);
    ASSERT_NE(eventHub, nullptr);
    eventHub->UpdateChangeEvent(&info);
    EXPECT_EQ(g_isCheckedTest, false);
}
} // namespace OHOS::Ace::NG
