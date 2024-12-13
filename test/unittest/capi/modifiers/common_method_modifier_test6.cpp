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

#include "common_method_modifier_test.h"

#include "modifier_test_base.h"
#include "modifiers_test_utils.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const auto ATTRIBUTE_TRANSFORM_NAME = "transform";
    const auto ATTRIBUTE_TRANSFORM_DEFAULT_VALUE = "{}";
    const auto ATTRIBUTE_CLICK_EFFECT_NAME = "clickEffect";
    const auto ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_ALLOW_DROP_NAME = "allowDrop";
    const auto ATTRIBUTE_ALLOW_DROP_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
    const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_DRAG_PREVIEW_NAME = "dragPreview";
    const auto ATTRIBUTE_DRAG_PREVIEW_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_MOTION_PATH_NAME = "motionPath";
    const auto ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE = "";
    const auto ATTRIBUTE_KEY_NAME = "id";
    const auto ATTRIBUTE_KEY_DEFAULT_VALUE = "";
}
struct ClickEffect {
    Ark_ClickEffectLevel level;
    float scale = 0.0f;
};
void AssignArkValue(Ark_ClickEffect& dst, const ClickEffect& value)
{
    dst.level = Converter::ArkValue<Ark_ClickEffectLevel>(value.level);
    dst.scale = Converter::ArkValue<Opt_Number>(value.scale);
}
struct MotionPathOptionTest {
    std::string path = "";
    std::optional<float> from = 0.0f;
    std::optional<float> to = 1.0f;
    std::optional<bool> rotatable = false;
};
namespace Converter {
    bool StrToArrayChar(char (&dst)[20], const char* src)
    {
        if (src == nullptr) {
            LOGE("Error: Source string is null.");
            return false;
        }
        size_t maxLen = sizeof(dst) - 1;
        size_t srcLen = std::strlen(src);
        if (srcLen > maxLen) {
            LOGE("Error: Source string is longer than destination buffer. String will be truncated.");
            return false;
        }
        for (size_t i = 0; i < srcLen && i < maxLen; ++i) {
            dst[i] = src[i];
        }
        dst[std::min(srcLen, maxLen)] = '\0';
        return true;
    }
    template<>
    Ark_CustomObject ArkValue(const double (&value)[4][4])
    {
        LOGE("This reverse converter is created for testing purposes only. Custom objects are not supported.");
        Ark_CustomObject dst;
        if (StrToArrayChar(dst.kind, "Matrix4")) {
            const int rowCount = sizeof(value) / sizeof(value[0]);
            for (int i = 0; i < rowCount; ++i) {
                dst.pointers[i] = (void*)value[i];
            }
        }
        return dst;
    }
    template<>
    Ark_MotionPathOptions ArkValue(const MotionPathOptionTest& src)
    {
        Ark_MotionPathOptions dst;
        dst.path = ArkValue<Ark_String>(src.path);
        dst.from = ArkValue<Opt_Number>(src.from);
        dst.to = ArkValue<Opt_Number>(src.to);
        dst.rotatable = ArkValue<Opt_Boolean>(src.rotatable);
        return dst;
    }
}
class CommonMethodModifierTest6 : public ModifierTestBase<GENERATED_ArkUICommonMethodModifier,
    &GENERATED_ArkUINodeModifiers::getCommonMethodModifier,
    GENERATED_ARKUI_BLANK // test common methods on frameNode for Blank component
    > {
public:
    RefPtr<RenderContext> render_;

    void *CreateNodeImpl() override
    {
        return nodeModifiers_->getBlankModifier()->construct(GetId(), 0);
    }
};

//////////// Transform
/*
 * @tc.name: setTransformTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setTransformTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_TRANSFORM_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE);
}

/*
 * @tc.name: setTransformTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestValidValues, TestSize.Level1)
{
    LOGE("Custom objects are not supported.");
    ASSERT_NE(modifier_->setTransform, nullptr);
    using OneTestStep = std::tuple<Ark_CustomObject, std::string>;
    double matrix1[4][4] = {{11, 12, 13, 14}, {21, 22, 23, 24}, {31, 32, 33, 34}, {41, 42, 43, 44}};
    double matrix2[4][4] = {{22, 24, 26, 28}, {42, 44, 46, 48}, {62, 64, 66, 68}, {82, 84, 86, 88}};
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_CustomObject>(matrix1),
            "{\"type\":\"matrix\",\"matrix\":\""
            "11.000000,21.000000,31.000000,41.000000,"
            "12.000000,22.000000,32.000000,42.000000,"
            "13.000000,23.000000,33.000000,43.000000,"
            "14.000000,24.000000,34.000000,44.000000,\"}"},
        {Converter::ArkValue<Ark_CustomObject>(matrix2),
            "{\"type\":\"matrix\",\"matrix\":\""
            "22.000000,42.000000,62.000000,82.000000,"
            "24.000000,44.000000,64.000000,84.000000,"
            "26.000000,46.000000,66.000000,86.000000,"
            "28.000000,48.000000,68.000000,88.000000,\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTransform(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TRANSFORM_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setTransformTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTransform, nullptr);
    using OneTestStep = std::tuple<Ark_CustomObject, std::string>;
    Ark_CustomObject invalidValue1 = {};
    Ark_CustomObject invalidValue2 = {};
    Ark_CustomObject invalidValue3 = {};

    if (!Converter::StrToArrayChar(invalidValue2.kind, "invalidType")) {
        LOGE("Error copying string to invalidValue2.kind");
        return;
    }
    if (!Converter::StrToArrayChar(invalidValue3.kind, "Matrix4")) {
        LOGE("Error copying string to invalidValue3.kind");
        return;
    }
    static const std::vector<OneTestStep> testPlan = {
        {invalidValue1, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
        {invalidValue2, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
        {invalidValue3, ATTRIBUTE_TRANSFORM_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setTransform(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_TRANSFORM_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
//////////// ClickEffect
/*
 * @tc.name: setClickEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_CLICK_EFFECT_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE);
}

/*
 * @tc.name: setClickEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_LIGHT, .scale = 0.5f})),
            "{\"level\":\"0\",\"scale\":\"0.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_MIDDLE, .scale = 1.5f})),
            "{\"level\":\"1\",\"scale\":\"1.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_HEAVY, .scale = 2.5f})),
            "{\"level\":\"2\",\"scale\":\"2.500000\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setClickEffect(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setClickEffectTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_ClickEffect>(), ""},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = static_cast<Ark_ClickEffectLevel>(-1),
            .scale = 1.5f})),
            "{\"level\":\"0\",\"scale\":\"1.500000\"}"},
        {Converter::ArkValue<Opt_ClickEffect>(ClickEffect({.level = ARK_CLICK_EFFECT_LEVEL_HEAVY, .scale = -2.5f})),
            "{\"level\":\"2\",\"scale\":\"-2.500000\"}"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setClickEffect(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
    modifier_->setClickEffect(node_, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
    auto expectedValue = "";
    EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
}

//////////// AllowDrop
/*
 * @tc.name: setAllowDropTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setAllowDropTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_ALLOW_DROP_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_ALLOW_DROP_DEFAULT_VALUE);
}

/*
 * @tc.name: setAllowDropTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setAllowDropTestValidValues, TestSize.Level1)
{
    LOGE("ARKOALA: CommonMethod::setAllowDrop: Ark_Union_Array_UniformDataType_Undefined"
        ".CustomObject is not supported.\n");
}

/*
 * @tc.name: setAllowDropTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setAllowDropTestInvalidValues, TestSize.Level1)
{
    LOGE("ARKOALA: CommonMethod::setAllowDrop: Ark_Union_Array_UniformDataType_Undefined"
        ".CustomObject is not supported.\n");
}

//////////// Draggable
/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setDraggableTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE);
}

/*
 * @tc.name: setDraggableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setDraggableTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDraggable, nullptr);
    using OneTestStep = std::tuple<Ark_Boolean, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_Boolean>(true), "true"},
        {Converter::ArkValue<Ark_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setDraggable(node_, inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////////// DragPreview
/*
 * @tc.name: setDragPreviewTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setDragPreviewTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_DRAG_PREVIEW_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_DRAG_PREVIEW_DEFAULT_VALUE);
}

/*
 * @tc.name: setDragPreviewTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setDragPreviewTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDragPreview, nullptr);
    LOGE("ARKOALA: CommonMethod::setsetDragPreview: "
        "Ark_Union_CustomBuilder_DragItemInfo_String.DragDropInfo.pixelMap is not supported.\n");
}

//////////// MotionPath
/*
 * @tc.name: setMotionPathTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setMotionPathTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_MOTION_PATH_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE);
}

/*
 * @tc.name: setMotionPathTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setMotionPathTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Ark_MotionPathOptions, std::string>;
    MotionPathOptionTest defaultValue;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_MotionPathOptions>(defaultValue), ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE},
        {Converter::ArkValue<Ark_MotionPathOptions>(MotionPathOptionTest(
            {.path = "path", .from = 1.0f, .to = 2.0f, .rotatable = true})), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setMotionPathTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setMotionPathTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Ark_MotionPathOptions, std::string>;
    MotionPathOptionTest defaultValue;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_MotionPathOptions>(MotionPathOptionTest(
            {.path = "path", .from = 2.0f, .to = 1.0f, .rotatable = true})), ""},
        {Converter::ArkValue<Ark_MotionPathOptions>(MotionPathOptionTest(
            {.path = "path", .from = -2.0f, .to = -1.0f, .rotatable = true})), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

//////////// Key
/*
 * @tc.name: setKeyTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestDefaultValues, TestSize.Level1)
{
    std::string strResult = GetStringAttribute(node_, ATTRIBUTE_KEY_NAME);
    EXPECT_EQ(strResult, ATTRIBUTE_KEY_DEFAULT_VALUE);
}

/*
 * @tc.name: setKeyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>("1"), "1"},
        {Converter::ArkValue<Ark_String>("2"), "2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setKeyTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setKeyTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Ark_String, std::string>;
    static const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Ark_String>(""), ATTRIBUTE_KEY_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_EQ(resultValue, expectedValue) << "Passed value is: " << expectedValue;
    }
}
// GENERATED_ArkUICommonMethodModifier
}
