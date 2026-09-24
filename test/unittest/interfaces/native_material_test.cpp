/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "interfaces/native/native_material.h"
#include "interfaces/native/node/node_model.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

class NativeMaterialTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        ASSERT_TRUE(NodeModel::InitialFullImpl());
    }

    static void TearDownTestSuite() {}

    void SetUp() {}
    void TearDown() {}
};

/**
 * @tc.name: ImmersiveMaterial_CreateValidStyles
 * @tc.desc: Test creating immersive material with each valid style
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_CreateValidStyles, TestSize.Level1)
{
    OH_ArkUI_NativeModule_GetSystemMaterialSupported();
    OH_ArkUI_NativeModule_GetGlobalMaterialLevel();

    static constexpr ArkUI_ImmersiveStyle kStyles[] = {
        ARKUI_IMMERSIVE_STYLE_ULTRA_THIN,
        ARKUI_IMMERSIVE_STYLE_THIN,
        ARKUI_IMMERSIVE_STYLE_REGULAR,
        ARKUI_IMMERSIVE_STYLE_THICK,
        ARKUI_IMMERSIVE_STYLE_ULTRA_THICK,
    };
    constexpr int32_t kStyleCount = sizeof(kStyles) / sizeof(kStyles[0]);

    for (int32_t i = 0; i < kStyleCount; ++i) {
        auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(kStyles[i]);
        ASSERT_NE(handle, nullptr) << "style index: " << i;
        ArkUI_ImmersiveStyle outStyle;
        EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(handle, &outStyle), ARKUI_ERROR_CODE_NO_ERROR);
        EXPECT_EQ(outStyle, kStyles[i]);
        OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
    }
}

/**
 * @tc.name: ImmersiveMaterial_CreateInvalidStyle
 * @tc.desc: Test creating immersive material with invalid style returns nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_CreateInvalidStyle, TestSize.Level1)
{
    constexpr int32_t kInvalidBelow = static_cast<int32_t>(ARKUI_IMMERSIVE_STYLE_ULTRA_THIN) - 1;
    constexpr int32_t kInvalidAbove = static_cast<int32_t>(ARKUI_IMMERSIVE_STYLE_ULTRA_THICK) + 1;

    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(static_cast<ArkUI_ImmersiveStyle>(kInvalidBelow));
    EXPECT_EQ(handle, nullptr);

    handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(static_cast<ArkUI_ImmersiveStyle>(kInvalidAbove));
    EXPECT_EQ(handle, nullptr);
}

/**
 * @tc.name: ImmersiveMaterial_DestroyNull
 * @tc.desc: Test destroying nullptr handle does not crash
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_DestroyNull, TestSize.Level1)
{
    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(nullptr);
}

/**
 * @tc.name: ImmersiveMaterial_SetStyleValid
 * @tc.desc: Test setting each valid style and getting it back
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetStyleValid, TestSize.Level1)
{
    static constexpr ArkUI_ImmersiveStyle kStyles[] = {
        ARKUI_IMMERSIVE_STYLE_ULTRA_THIN,
        ARKUI_IMMERSIVE_STYLE_THIN,
        ARKUI_IMMERSIVE_STYLE_REGULAR,
        ARKUI_IMMERSIVE_STYLE_THICK,
        ARKUI_IMMERSIVE_STYLE_ULTRA_THICK,
    };

    for (auto style : kStyles) {
        auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
        ASSERT_NE(handle, nullptr);
        EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(handle, style), ARKUI_ERROR_CODE_NO_ERROR);
        ArkUI_ImmersiveStyle outStyle;
        EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(handle, &outStyle), ARKUI_ERROR_CODE_NO_ERROR);
        EXPECT_EQ(outStyle, style);
        OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
    }
}

/**
 * @tc.name: ImmersiveMaterial_SetStyleInvalid
 * @tc.desc: Test setting invalid style returns error
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetStyleInvalid, TestSize.Level1)
{
    constexpr int32_t kInvalidBelow = static_cast<int32_t>(ARKUI_IMMERSIVE_STYLE_ULTRA_THIN) - 1;
    constexpr int32_t kInvalidAbove = static_cast<int32_t>(ARKUI_IMMERSIVE_STYLE_ULTRA_THICK) + 1;

    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);

    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(handle, static_cast<ArkUI_ImmersiveStyle>(kInvalidBelow)),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(handle, static_cast<ArkUI_ImmersiveStyle>(kInvalidAbove)),
        ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}

/**
 * @tc.name: ImmersiveMaterial_SetStyleNullHandle
 * @tc.desc: Test setting style with nullptr handle returns error
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetStyleNullHandle, TestSize.Level1)
{
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(nullptr, ARKUI_IMMERSIVE_STYLE_REGULAR),
        ARKUI_ERROR_CODE_PARAM_INVALID);
}

/**
 * @tc.name: ImmersiveMaterial_GetStyleNullParams
 * @tc.desc: Test getting style with nullptr parameters returns error
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_GetStyleNullParams, TestSize.Level1)
{
    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(nullptr, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(handle, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);

    ArkUI_ImmersiveStyle outStyle = ARKUI_IMMERSIVE_STYLE_REGULAR;
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(nullptr, &outStyle), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}

/**
 * @tc.name: ImmersiveMaterial_SetGetMaterialColor
 * @tc.desc: Test setting and getting material color
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetGetMaterialColor, TestSize.Level1)
{
    static constexpr uint32_t kTestColor = 0xFF123456;
    static constexpr uint32_t kOtherColor = 0xAAFFBBCC;

    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);

    uint32_t outColor = 0;
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(handle, &outColor),
        ARKUI_ERROR_CODE_PARAM_ERROR);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(handle, kTestColor), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(handle, &outColor), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(outColor, kTestColor);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(handle, kOtherColor), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(handle, &outColor), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(outColor, kOtherColor);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(nullptr, 0), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(nullptr, &outColor), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(handle, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}

/**
 * @tc.name: ImmersiveMaterial_SetGetApplyShadow
 * @tc.desc: Test setting and getting apply shadow with default value verification
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetGetApplyShadow, TestSize.Level1)
{
    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);

    bool outValue = false;
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(handle, &outValue), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(outValue);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(handle, false), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(handle, &outValue), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(outValue);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(handle, true), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(handle, &outValue), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(outValue);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(nullptr, true), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(nullptr, &outValue), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(handle, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}

/**
 * @tc.name: ImmersiveMaterial_SetGetInteractive
 * @tc.desc: Test setting and getting interactive attribute
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetGetInteractive, TestSize.Level1)
{
    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);

    bool outValue = false;
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(handle, &outValue), ARKUI_ERROR_CODE_PARAM_ERROR);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(handle, true), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(handle, &outValue), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_TRUE(outValue);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(handle, false), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(handle, &outValue), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_FALSE(outValue);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(nullptr, true), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(nullptr, &outValue), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(handle, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}

/**
 * @tc.name: LightEffectOptions_CreateAndDestroy
 * @tc.desc: Test creating and destroying light effect options
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, LightEffectOptions_CreateAndDestroy, TestSize.Level1)
{
    auto options = OH_ArkUI_NativeModule_LightEffectOptions_Create();
    ASSERT_NE(options, nullptr);
    OH_ArkUI_NativeModule_LightEffectOptions_Destroy(options);

    OH_ArkUI_NativeModule_LightEffectOptions_Destroy(nullptr);
}

/**
 * @tc.name: LightEffectOptions_SetColor
 * @tc.desc: Test setting light effect color
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, LightEffectOptions_SetColor, TestSize.Level1)
{
    static constexpr uint32_t kTestColor = 0xAAFFCCDD;

    auto options = OH_ArkUI_NativeModule_LightEffectOptions_Create();
    ASSERT_NE(options, nullptr);

    EXPECT_EQ(OH_ArkUI_NativeModule_LightEffectOptions_SetColor(options, kTestColor), ARKUI_ERROR_CODE_NO_ERROR);

    EXPECT_EQ(OH_ArkUI_NativeModule_LightEffectOptions_SetColor(nullptr, 0), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_LightEffectOptions_Destroy(options);
}

/**
 * @tc.name: ImmersiveMaterial_SetGetLightEffect
 * @tc.desc: Test setting and getting light effect on immersive material
 * @tc.type: FUNC
 */
HWTEST_F(NativeMaterialTest, ImmersiveMaterial_SetGetLightEffect, TestSize.Level1)
{
    static constexpr uint32_t kCustomColor = 0xFFAABBCC;

    auto handle = OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ARKUI_IMMERSIVE_STYLE_REGULAR);
    ASSERT_NE(handle, nullptr);
    auto options = OH_ArkUI_NativeModule_LightEffectOptions_Create();
    ASSERT_NE(options, nullptr);

    uint32_t outColor = 0;
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(handle, &outColor), ARKUI_ERROR_CODE_PARAM_ERROR);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(handle, options), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(handle, &outColor), ARKUI_ERROR_CODE_PARAM_ERROR);
    EXPECT_EQ(outColor, 0);

    OH_ArkUI_NativeModule_LightEffectOptions_SetColor(options, kCustomColor);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(handle, options), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(handle, &outColor), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(outColor, kCustomColor);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(handle, nullptr), ARKUI_ERROR_CODE_NO_ERROR);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(handle, &outColor), ARKUI_ERROR_CODE_PARAM_ERROR);

    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(nullptr, options), ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(nullptr, &outColor),
        ARKUI_ERROR_CODE_PARAM_INVALID);
    EXPECT_EQ(
        OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(handle, nullptr), ARKUI_ERROR_CODE_PARAM_INVALID);

    OH_ArkUI_NativeModule_LightEffectOptions_Destroy(options);
    OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(handle);
}
} // namespace OHOS::Ace::NG
