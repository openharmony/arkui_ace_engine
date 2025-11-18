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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace  {
    const auto ATTRIBUTE_GUIDE_LINE_NAME = "guideLine";
    const auto ATTRIBUTE_BARRIER_NAME = "barrier";
    const auto ATTRIBUTE_ARRAY_DEFAULT_SIZE = 0;

    const auto ATTR_GUIDE_LINE_ID = "id";
    const auto ATTR_GUIDE_LINE_DIRECTION = "direction";
    const auto ATTR_GUIDE_LINE_POSITION = "position";
    const auto ATTR_GUIDE_LINE_START = "start";
    const auto ATTR_GUIDE_LINE_END = "end";

    const auto ATTR_BARRIER_ID = "id";
    const auto ATTR_BARRIER_DIRECTION = "direction";
    const auto ATTR_BARRIER_REF_ID = "referencedId";

inline Ark_GuideLineStyle GetGuideLineStyle(const std::string& idValue, const Ark_Axis directionValue,
    const float startValue, const float endValue)
{
    Ark_GuideLineStyle style;
    style.id = Converter::ArkValue<Ark_String>(idValue);
    style.position = {
        .start = Converter::ArkValue<Opt_Dimension>(startValue),
        .end = Converter::ArkValue<Opt_Dimension>(endValue),
    };
    style.direction = directionValue;
    return style;
}

inline Ark_BarrierStyle GetBarrierStyle(const std::string& idValue, const Ark_BarrierDirection directionValue,
    const Array_String& vecRefId)
{
    return {
        .id = Converter::ArkValue<Ark_String>(idValue),
        .direction = directionValue,
        .referencedId = vecRefId
    };
}

std::string ArkAxisToString(Ark_Axis value)
{
    if (value == Ark_Axis::ARK_AXIS_VERTICAL) {
        return "Axis.Vertical";
    }
    if (value == Ark_Axis::ARK_AXIS_HORIZONTAL) {
        return "Axis.Horizontal";
    }
    return "";
}

std::string ArkBarrierDirection(Ark_BarrierDirection value)
{
    switch (value) {
        case ARK_BARRIER_DIRECTION_LEFT: return "BarrierDirection.LEFT";
        case ARK_BARRIER_DIRECTION_RIGHT: return "BarrierDirection.RIGHT";
        case ARK_BARRIER_DIRECTION_TOP: return "BarrierDirection.TOP";
        case ARK_BARRIER_DIRECTION_BOTTOM: return "BarrierDirection.BOTTOM";
        default: return "";
    }
}

void checkGuideLineData(Ark_NodeHandle node, std::vector<string> vecId,
    std::vector<Ark_Axis> vecAxisDir,
    std::vector<string> vecStart, std::vector<string> vecEnd)
{
    auto jsonValue = GetJsonValue(node);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_GUIDE_LINE_NAME);
    ASSERT_NE(jsonArray, nullptr);
    EXPECT_EQ(jsonArray->GetArraySize(), vecId.size());
    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto itemJson = jsonArray->GetArrayItem(i);
        EXPECT_EQ(itemJson->GetString(ATTR_GUIDE_LINE_ID), vecId[i]);
        if (vecAxisDir[i] == ARK_AXIS_VERTICAL || vecAxisDir[i] == ARK_AXIS_HORIZONTAL) {
            EXPECT_EQ(itemJson->GetString(ATTR_GUIDE_LINE_DIRECTION), ArkAxisToString(vecAxisDir[i]));
        } else {
            EXPECT_EQ(itemJson->GetString(ATTR_GUIDE_LINE_DIRECTION), "Axis.Vertical");
        }
        auto posJson = GetAttrValue<std::unique_ptr<JsonValue>>(itemJson, ATTR_GUIDE_LINE_POSITION);
        EXPECT_EQ(posJson->GetString(ATTR_GUIDE_LINE_START), vecStart[i]);
        EXPECT_EQ(posJson->GetString(ATTR_GUIDE_LINE_END), vecEnd[i]);
    }
}

std::string ExpectedBarrierDirValue(Ark_BarrierDirection value)
{
    if (value == ARK_BARRIER_DIRECTION_LEFT || value == ARK_BARRIER_DIRECTION_RIGHT ||
        value == ARK_BARRIER_DIRECTION_TOP || value == ARK_BARRIER_DIRECTION_BOTTOM) {
        return ArkBarrierDirection(value);
    }
    return "BarrierDirection.LEFT";
}

void checkBarrierData(Ark_NodeHandle node, std::vector<string> vecId,
    std::vector<Ark_BarrierDirection> vecBarrierDir,
    std::vector<string> vecRedId)
{
    auto jsonValue = GetJsonValue(node);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BARRIER_NAME);
    ASSERT_NE(jsonArray, nullptr);
    EXPECT_EQ(jsonArray->GetArraySize(), vecId.size());
    for (int i = 0; i < jsonArray->GetArraySize(); i++) {
        auto itemJson = jsonArray->GetArrayItem(i);
        EXPECT_EQ(itemJson->GetString(ATTR_BARRIER_ID), vecId[i]);
        auto expectedDir =  ExpectedBarrierDirValue(vecBarrierDir[i]);
        EXPECT_EQ(itemJson->GetString(ATTR_BARRIER_DIRECTION), expectedDir);
        auto refIdJson = GetAttrValue<std::unique_ptr<JsonValue>>(itemJson, ATTR_BARRIER_REF_ID);
        for (int j = 0; j < refIdJson->GetArraySize(); j++) {
            auto refIdItem = refIdJson->GetArrayItem(j);
            EXPECT_EQ(refIdItem->GetString(), vecRedId[j]);
        }
    }
}
} // namespace

class RelativeContainerModifierTest : public ModifierTestBase<
    GENERATED_ArkUIRelativeContainerModifier,
    &GENERATED_ArkUINodeModifiers::getRelativeContainerModifier,
    GENERATED_ARKUI_RELATIVE_CONTAINER> {
};

/*
 * @tc.name: setTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setTestDefaultValues, TestSize.Level1)
{
    std::unique_ptr<JsonValue> jsonValue = GetJsonValue(node_);
    auto jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_GUIDE_LINE_NAME);
    ASSERT_NE(jsonArray, nullptr);
    EXPECT_EQ(jsonArray->GetArraySize(), ATTRIBUTE_ARRAY_DEFAULT_SIZE);
    jsonArray = GetAttrValue<std::unique_ptr<JsonValue>>(jsonValue, ATTRIBUTE_BARRIER_NAME);
    EXPECT_EQ(jsonArray->GetArraySize(), ATTRIBUTE_ARRAY_DEFAULT_SIZE);
}

/*
 * @tc.name: setGuideLineTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setGuideLineTestValidValues, TestSize.Level1)
{
    std::vector<Ark_GuideLineStyle> inputVec;
    std::vector<string> vecId = {"abc1", "abc2", "abc3", "abc4", "abc5"};
    std::vector<float> vecStart = {0.f, 1.f, 2.f, 3.f, 100.f};
    std::vector<float> vecEnd = {10.f, 20.f, 30.f, 40.f, 1000.f};
    std::vector<Ark_Axis>  vecDir = {ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL,
        ARK_AXIS_HORIZONTAL, ARK_AXIS_HORIZONTAL};
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetGuideLineStyle(vecId[i], vecDir[i], vecStart[i], vecEnd[i]));
    }
    Converter::ArkArrayHolder<Array_GuideLineStyle> inputHolder(inputVec);
    Array_GuideLineStyle inputValueGuideLine = inputHolder.ArkValue();
    auto optInputValueGuideLine = Converter::ArkValue<Opt_Array_GuideLineStyle>(inputValueGuideLine);
    modifier_->setGuideLine(node_, &optInputValueGuideLine);

    std::vector<std::string> vecStartStr = {"0.00vp", "1.00vp", "2.00vp", "3.00vp", "100.00vp"};
    std::vector<std::string> vecEndStr = {"10.00vp", "20.00vp", "30.00vp", "40.00vp", "1000.00vp"};
    checkGuideLineData(node_, vecId, vecDir, vecStartStr, vecEndStr);
}

/*
 * @tc.name: setGuideLineTestValidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setGuideLineTestValidValues2, TestSize.Level1)
{
    std::vector<Ark_GuideLineStyle> inputVec;
    std::vector<std::string> vecId = {"8", "4", "5", "9", "100"};
    std::vector<Ark_Axis>  vecDir = {ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL,
        ARK_AXIS_HORIZONTAL, ARK_AXIS_HORIZONTAL};
    std::vector<float> vecStart = {1000.123f, 1000.123f, 1000.123f, 1000.123f, 1000.123f};
    std::vector<float> vecEnd = {1000.123456456f, 1000.123456456f, 1000.123456456f, 1000.123456456f, 1000.123456456f};
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetGuideLineStyle(vecId[i], vecDir[i], vecStart[i], vecEnd[i]));
    }
    Converter::ArkArrayHolder<Array_GuideLineStyle> inputHolder(inputVec);
    Array_GuideLineStyle inputValueGuideLine = inputHolder.ArkValue();
    auto optInputValueGuideLine = Converter::ArkValue<Opt_Array_GuideLineStyle>(inputValueGuideLine);
    modifier_->setGuideLine(node_, &optInputValueGuideLine);
    std::vector<std::string> vecStartStr = {"1000.12vp", "1000.12vp", "1000.12vp", "1000.12vp", "1000.12vp"};
    std::vector<std::string> vecEndStr = {"1000.12vp", "1000.12vp", "1000.12vp", "1000.12vp", "1000.12vp"};
    checkGuideLineData(node_, vecId, vecDir, vecStartStr, vecEndStr);
}

/*
 * @tc.name: setGuideLineTestValidValues3
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setGuideLineTestValidValues3, TestSize.Level1)
{
    std::vector<Ark_GuideLineStyle> inputVec;
    std::vector<std::string>  vecId = {"8", "4", "5", "9", "100"};
    std::vector<Ark_Axis>  vecDir = {ARK_AXIS_VERTICAL, ARK_AXIS_HORIZONTAL, ARK_AXIS_VERTICAL,
     ARK_AXIS_HORIZONTAL, ARK_AXIS_VERTICAL};
    std::vector<float> vecStart = {0.f, 1.f, 2.f, 3.f, 100.f};
    std::vector<float> vecEnd = {10.f, 20.f, 30.f, 40.f, 1000.f};
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetGuideLineStyle(vecId[i], vecDir[i], vecStart[i], vecEnd[i]));
    }
    Converter::ArkArrayHolder<Array_GuideLineStyle> inputHolder(inputVec);
    Array_GuideLineStyle inputValueGuideLine = inputHolder.ArkValue();
    auto optInputValueGuideLine = Converter::ArkValue<Opt_Array_GuideLineStyle>(inputValueGuideLine);
    modifier_->setGuideLine(node_, &optInputValueGuideLine);

    std::vector<std::string> vecStartStr = {"0.00vp", "1.00vp", "2.00vp", "3.00vp", "100.00vp"};
    std::vector<std::string> vecEndStr = {"10.00vp", "20.00vp", "30.00vp", "40.00vp", "1000.00vp"};
    checkGuideLineData(node_, vecId, vecDir, vecStartStr, vecEndStr);
}

/*
 * @tc.name: GuideLineImplTestInvalidValues
 * @tc.desc: vector of directions is less then vecId, so GetGuideLineStyle is called with
 * empty axis. The default value is AXIS_VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setGuideLineTestInvalidValues, TestSize.Level1)
{
    std::vector<Ark_GuideLineStyle> inputVec;
    std::vector<std::string>  vecId = {"-8", "-4", "-5-", "+9", "%100", "-10", "*&^", "abc", "40%", "-"};
    std::vector<Ark_Axis>  vecDir = {ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL,
        ARK_AXIS_HORIZONTAL, ARK_AXIS_VERTICAL, static_cast<Ark_Axis>(-1), static_cast<Ark_Axis>(-2),
        static_cast<Ark_Axis>(3), static_cast<Ark_Axis>(10), static_cast<Ark_Axis>(-1)};
    std::vector<float> vecStart = {0.f, -4.f, 5, 9, 100, 0.f, -4.f, 5, 9, 100};
    std::vector<float> vecEnd = {-10.f, -4.f, 5, 9, -100, 0.f, -4.f, 5, 9, 100};
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetGuideLineStyle(vecId[i], vecDir[i], vecStart[i], vecEnd[i]));
    }
    Converter::ArkArrayHolder<Array_GuideLineStyle> inputHolder(inputVec);
    Array_GuideLineStyle inputValueGuideLine = inputHolder.ArkValue();
    auto optInputValueGuideLine = Converter::ArkValue<Opt_Array_GuideLineStyle>(inputValueGuideLine);
    modifier_->setGuideLine(node_, &optInputValueGuideLine);
    std::vector<std::string> vecStartStr = {"0.00vp", "-4.00vp", "5.00vp", "9.00vp", "100.00vp",
        "0.00vp", "-4.00vp", "5.00vp", "9.00vp", "100.00vp"};
    std::vector<std::string> vecEndStr = {"-10.00vp", "-4.00vp", "5.00vp", "9.00vp", "-100.00vp",
        "0.00vp", "-4.00vp", "5.00vp", "9.00vp", "100.00vp"};
    checkGuideLineData(node_, vecId, vecDir, vecStartStr, vecEndStr);
}

/*
 * @tc.name: GuideLineImplTestInvalidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setGuideLineTestInvalidValues2, TestSize.Level1)
{
    std::vector<Ark_GuideLineStyle> inputVec;
    std::vector<std::string> vecId = {"", "", "", "", ""};
    std::vector<Ark_Axis>  vecDir = {ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL, ARK_AXIS_VERTICAL,
        ARK_AXIS_HORIZONTAL, ARK_AXIS_VERTICAL};
    std::vector<float> vecStart = {0.f, -4.f, 5, 9, 100};
    std::vector<float> vecEnd = {-10.f, -4.f, 5, 9, -100};
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetGuideLineStyle(vecId[i], vecDir[i], vecStart[i], vecEnd[i]));
    }
    Converter::ArkArrayHolder<Array_GuideLineStyle> inputHolder(inputVec);
    Array_GuideLineStyle inputValueGuideLine = inputHolder.ArkValue();
    auto optInputValueGuideLine = Converter::ArkValue<Opt_Array_GuideLineStyle>(inputValueGuideLine);
    modifier_->setGuideLine(node_, &optInputValueGuideLine);
    std::vector<std::string> vecStartStr = {"0.00vp", "-4.00vp", "5.00vp", "9.00vp", "100.00vp"};
    std::vector<std::string> vecEndStr = {"-10.00vp", "-4.00vp", "5.00vp", "9.00vp", "-100.00vp"};
    checkGuideLineData(node_, vecId, vecDir, vecStartStr, vecEndStr);
}

/*
 * @tc.name: setBarrierTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setBarrierTestValidValues, TestSize.Level1)
{
    std::vector<std::string> vecId = {"10.f", "4.f", "5", "9", "100"};
    std::vector<Ark_BarrierDirection> vecBarrierDir = {ARK_BARRIER_DIRECTION_BOTTOM, ARK_BARRIER_DIRECTION_RIGHT,
     ARK_BARRIER_DIRECTION_TOP, ARK_BARRIER_DIRECTION_BOTTOM, ARK_BARRIER_DIRECTION_BOTTOM};
    std::vector<Ark_BarrierStyle> inputVec;
    std::vector<string> vecDataRefIds = {"10.f", "4.f", "5", "9", "100"};
    Converter::ArkArrayHolder<Array_String> vecHolder(vecDataRefIds);
    Array_String vecRefIds = vecHolder.ArkValue();
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetBarrierStyle(vecId[i], vecBarrierDir[i], vecRefIds));
    }
    Converter::ArkArrayHolder<Array_BarrierStyle> inputHolder(inputVec);
    Array_BarrierStyle inputValueBarrier = inputHolder.ArkValue();
    auto optInputValueBarrier =
        Converter::ArkUnion<Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle, Array_BarrierStyle>(
            inputValueBarrier);
    modifier_->setBarrier(node_, &optInputValueBarrier);
    checkBarrierData(node_, vecId, vecBarrierDir, vecDataRefIds);
}

/*
 * @tc.name: setBarrier0TestValidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setBarrierTestValidValues2, TestSize.Level1)
{
    std::vector<std::string> vecId = {"abc1", "abc2", "abc3", "abc4", "abc5"};
    std::vector<Ark_BarrierDirection> vecBarrierDir = {ARK_BARRIER_DIRECTION_LEFT, ARK_BARRIER_DIRECTION_RIGHT,
        ARK_BARRIER_DIRECTION_TOP, ARK_BARRIER_DIRECTION_BOTTOM, ARK_BARRIER_DIRECTION_BOTTOM};
    std::vector<string> vecDataRefIds = {"bbb1", "bbb2", "bbb3", "bbb4", "bbb5"};
    Converter::ArkArrayHolder<Array_String> vecHolder(vecDataRefIds);
    Array_String vecRefIds = vecHolder.ArkValue();
    std::vector<Ark_BarrierStyle> inputVec;
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetBarrierStyle(vecId[i], vecBarrierDir[i], vecRefIds));
    }
    Converter::ArkArrayHolder<Array_BarrierStyle> inputHolder(inputVec);
    Array_BarrierStyle inputValueBarrier = inputHolder.ArkValue();
    auto optInputValueBarrier =
        Converter::ArkUnion<Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle, Array_BarrierStyle>(
            inputValueBarrier);
    modifier_->setBarrier(node_, &optInputValueBarrier);
    checkBarrierData(node_, vecId, vecBarrierDir, vecDataRefIds);
}

/*
 * @tc.name: setBarrierTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setBarrierTestInvalidValues, TestSize.Level1)
{
    std::vector<std::string> vecId = {"-10.f", "", "", "", "-100"};
    std::vector<Ark_BarrierDirection> vecBarrierDir = {ARK_BARRIER_DIRECTION_LEFT, ARK_BARRIER_DIRECTION_RIGHT,
        ARK_BARRIER_DIRECTION_TOP, ARK_BARRIER_DIRECTION_BOTTOM, ARK_BARRIER_DIRECTION_BOTTOM};

    std::vector<Ark_BarrierStyle> inputVec;
    std::vector<string> vecDataRefIds = {"-10.f", "-4.f", "-5", "-9", "-100"};
    Converter::ArkArrayHolder<Array_String> vecHolder(vecDataRefIds);
    Array_String vecRefIds = vecHolder.ArkValue();
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetBarrierStyle(vecId[i], vecBarrierDir[i], vecRefIds));
    }
    Converter::ArkArrayHolder<Array_BarrierStyle> inputHolder(inputVec);
    Array_BarrierStyle inputValueBarrier = inputHolder.ArkValue();
    auto optInputValueBarrier =
        Converter::ArkUnion<Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle, Array_BarrierStyle>(
            inputValueBarrier);
    modifier_->setBarrier(node_, &optInputValueBarrier);
    checkBarrierData(node_, vecId, vecBarrierDir, vecDataRefIds);
}

/*
 * @tc.name: setBarrierTestInvalidValues2
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(RelativeContainerModifierTest, DISABLED_setBarrierTestInvalidValues2, TestSize.Level1)
{
    std::vector<std::string> vecId = {"-10", "", "abc", "40%", "-"};
    std::vector<Ark_BarrierDirection> vecBarrierDir = {ARK_BARRIER_DIRECTION_LEFT, ARK_BARRIER_DIRECTION_RIGHT,
        ARK_BARRIER_DIRECTION_TOP, static_cast<Ark_BarrierDirection>(-1),
        static_cast<Ark_BarrierDirection>(100)};
    std::vector<string> vecDataRefIds = {"-10", "", "abc", "40%", "-"};
    Converter::ArkArrayHolder<Array_String> vecHolder(vecDataRefIds);
    Array_String vecRefIds = vecHolder.ArkValue();
    std::vector<Ark_BarrierStyle> inputVec;
    for (int i = 0; i < vecId.size(); i++) {
        inputVec.push_back(GetBarrierStyle(vecId[i], vecBarrierDir[i], vecRefIds));
    }
    Converter::ArkArrayHolder<Array_BarrierStyle> inputHolder(inputVec);
    Array_BarrierStyle inputValueBarrier = inputHolder.ArkValue();
    auto optInputValueBarrier =
        Converter::ArkUnion<Opt_Union_Array_BarrierStyle_Array_LocalizedBarrierStyle, Array_BarrierStyle>(
            inputValueBarrier);
    modifier_->setBarrier(node_, &optInputValueBarrier);
    checkBarrierData(node_, vecId, vecBarrierDir, vecDataRefIds);
}
} // namespace OHOS::Ace::NG
