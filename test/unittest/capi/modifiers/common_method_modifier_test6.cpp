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

namespace {
    const auto ATTRIBUTE_TRANSFORM_NAME = "transform";
    const auto ATTRIBUTE_TRANSFORM_DEFAULT_VALUE = "{}";
    const auto ATTRIBUTE_CLICK_EFFECT_NAME = "clickEffect";
    const auto ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE = std::nullopt;
    const auto ATTRIBUTE_DRAGGABLE_NAME = "draggable";
    const auto ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE = std::nullopt;
    const auto ATTRIBUTE_MOTION_PATH_NAME = "motionPath";
    const auto ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE = std::nullopt;
    const auto ATTRIBUTE_KEY_NAME = "id";
    const auto ATTRIBUTE_KEY_DEFAULT_VALUE = "";

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
} // namespace

void AssignArkValue(Ark_CustomObject& dst, const double (&value)[4][4])
{
    LOGE("This reverse converter is created for testing purposes only. Custom objects are not supported.");
    if (StrToArrayChar(dst.kind, "Matrix4")) {
        const int rowCount = sizeof(value) / sizeof(value[0]);
        for (int i = 0; i < rowCount; ++i) {
            dst.pointers[i] = (void*)value[i];
        }
    }
}

namespace OHOS::Ace::NG {
struct ClickEffect {
    Ark_ClickEffectLevel level;
    float scale;
};
void AssignArkValue(Ark_ClickEffect& dst, const ClickEffect& value)
{
    dst.level = value.level;
    dst.scale = Converter::ArkValue<Opt_Float64>(value.scale);
}
struct MotionPathOptionTest {
    std::string path = "";
    std::optional<float> from = 0.0f;
    std::optional<float> to = 1.0f;
    std::optional<bool> rotatable = false;
};
void AssignArkValue(Ark_MotionPathOptions& dst, const MotionPathOptionTest& src)
{
    dst.path = Converter::ArkValue<Ark_String>(src.path);
    dst.from = Converter::ArkValue<Opt_Float64>(src.from);
    dst.to = Converter::ArkValue<Opt_Float64>(src.to);
    dst.rotatable = Converter::ArkValue<Opt_Boolean>(src.rotatable);
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
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_TRANSFORM_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_TRANSFORM_DEFAULT_VALUE));
}

/*
 * @tc.name: setTransformTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTransform, nullptr);
    FAIL() << "Test is not implemented yet";
}

/*
 * @tc.name: setTransformTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setTransformTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setTransform, nullptr);
    FAIL() << "Test is not implemented yet";
}

//////////// ClickEffect
/*
 * @tc.name: setClickEffectTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setClickEffectTestDefaultValues, TestSize.Level1)
{
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_CLICK_EFFECT_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_CLICK_EFFECT_DEFAULT_VALUE));
}

/*
 * @tc.name: setClickEffectTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setClickEffectTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    const std::vector<OneTestStep> testPlan = {
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
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
    }
}

/*
 * @tc.name: setClickEffectTestInvalidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setClickEffectTestInvalidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setClickEffect, nullptr);
    using OneTestStep = std::tuple<Opt_ClickEffect, std::string>;
    const std::vector<OneTestStep> testPlan = {
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
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
    }
    modifier_->setClickEffect(node_, nullptr);
    auto fullJson = GetJsonValue(node_);
    auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_CLICK_EFFECT_NAME);
    auto expectedValue = "";
    EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
}

//////////// AllowDrop
/*
 * @tc.name: setAllowDropTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setAllowDropTestDefaultValues, TestSize.Level1)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node_);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_TRUE((frameNode->GetAllowDrop()).empty()) << "Passed value -- empty set is true";
}

//////////// Draggable
/*
 * @tc.name: setDraggableTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setDraggableTestDefaultValues, TestSize.Level1)
{
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_DRAGGABLE_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_DRAGGABLE_DEFAULT_VALUE));
}

/*
 * @tc.name: setDraggableTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setDraggableTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setDraggable, nullptr);
    using OneTestStep = std::tuple<Opt_Boolean, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_Boolean>(true), "true"},
        {Converter::ArkValue<Opt_Boolean>(false), "false"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setDraggable(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_DRAGGABLE_NAME);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
    }
}

//////////// MotionPath
/*
 * @tc.name: setMotionPathTestDefaultValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, setMotionPathTestDefaultValues, TestSize.Level1)
{
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_MOTION_PATH_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_MOTION_PATH_DEFAULT_VALUE));
}

/*
 * @tc.name: setMotionPathTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setMotionPathTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setMotionPath, nullptr);
    using OneTestStep = std::tuple<Opt_MotionPathOptions, std::string>;
    MotionPathOptionTest defaultValue;
    MotionPathOptionTest validValue = {.path = "path", .from = 1.0f, .to = 2.0f, .rotatable = true};
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_MotionPathOptions>(defaultValue), ""},
        {Converter::ArkValue<Opt_MotionPathOptions>(validValue), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
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
    using OneTestStep = std::tuple<Opt_MotionPathOptions, std::string>;
    MotionPathOptionTest invalidValue1 = {.path = "path", .from = 2.0f, .to = 1.0f, .rotatable = true};
    MotionPathOptionTest invalidValue2 = {.path = "path", .from = -2.0f, .to = -1.0f, .rotatable = true};
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_MotionPathOptions>(invalidValue1), ""},
        {Converter::ArkValue<Opt_MotionPathOptions>(invalidValue2), ""},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setMotionPath(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_MOTION_PATH_NAME);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
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
    auto strResult = GetAttrValue<std::string>(node_, ATTRIBUTE_KEY_NAME);
    EXPECT_THAT(strResult, Eq(ATTRIBUTE_KEY_DEFAULT_VALUE));
}

/*
 * @tc.name: setKeyTestValidValues
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(CommonMethodModifierTest6, DISABLED_setKeyTestValidValues, TestSize.Level1)
{
    ASSERT_NE(modifier_->setKey, nullptr);
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>("1"), "1"},
        {Converter::ArkValue<Opt_String>("2"), "2"},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
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
    using OneTestStep = std::tuple<Opt_String, std::string>;
    const std::vector<OneTestStep> testPlan = {
        {Converter::ArkValue<Opt_String>(""), ATTRIBUTE_KEY_DEFAULT_VALUE},
    };
    for (auto [inputValue, expectedValue]: testPlan) {
        modifier_->setKey(node_, &inputValue);
        auto fullJson = GetJsonValue(node_);
        ASSERT_NE(fullJson, nullptr);
        auto resultValue = GetAttrValue<std::string>(fullJson, ATTRIBUTE_KEY_NAME);
        EXPECT_THAT(resultValue, Eq(expectedValue)) << "Passed value is: " << expectedValue;
    }
}
// GENERATED_ArkUICommonMethodModifier
}
