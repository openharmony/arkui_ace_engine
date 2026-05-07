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

/**
 * @addtogroup ArkUI_NativeModule
 * @{
 *
 * @brief Provides UI capabilities of ArkUI on the native side, such as UI component creation and destruction,
 * tree node operations, attribute setting, and event listening.
 *
 * @since 26.0.0
 */

/**
 * @file native_material.h
 *
 * @brief Declares the immersive material types and APIs for ArkUI on the native side.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 26.0.0
 */
#ifndef ARKUI_NATIVE_MATERIAL_H
#define ARKUI_NATIVE_MATERIAL_H

#include "native_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the immersive material styles.
 * Different styles correspond to different material parameters, which affect the thickness of the material.
 *
 * @since 26.0.0
 */
typedef enum {
    /** Ultra thin style. The material layer is ultra thin, with a very strong transparency effect. */
    ARKUI_IMMERSIVE_STYLE_ULTRA_THIN = 0,
    /** Thin style. The material layer is thin, with a strong transparency effect. */
    ARKUI_IMMERSIVE_STYLE_THIN,
    /** Regular style. The material layer has a standard thickness with balanced visual effect. */
    ARKUI_IMMERSIVE_STYLE_REGULAR,
    /** Thick style. The blur effect is strong. */
    ARKUI_IMMERSIVE_STYLE_THICK,
    /** Ultra thick style. */
    ARKUI_IMMERSIVE_STYLE_ULTRA_THICK,
} ArkUI_ImmersiveStyle;

/**
 * @brief Enumerates the material levels, which indicate the computing power level of the device.
 * Use {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel} to obtain the material level of the current device.
 *
 * @since 26.0.0
 */
typedef enum {
    /** Exquisite level. The effect is exquisite and is suitable for high-end computing device. */
    ARKUI_MATERIAL_LEVEL_EXQUISITE = 0,
    /** Gentle level. The effect is gentle and is suitable for mid-range computing device. */
    ARKUI_MATERIAL_LEVEL_GENTLE,
    /** Smooth level. The effect is smooth and is suitable for low-end computing device. */
    ARKUI_MATERIAL_LEVEL_SMOOTH,
} ArkUI_MaterialLevel;

/**
 * @brief Defines the immersive material object on the native side.
 * Immersive materials have different performance levels based on the computing power of the device.
 * The performance level is defined by {@link ArkUI_MaterialLevel}, which can be obtained
 * by {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}.
 * On high-end and mid-range computing power devices, they affect the filter effect of the
 * material layer and shadow effect. On low-end computing power devices, it affects the
 * background color, border color, border width, and shadow effect.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial ArkUI_ImmersiveMaterial;

/**
 * @brief Defines the pointer to the immersive material object.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_ImmersiveMaterial* ArkUI_ImmersiveMaterialHandle;

/**
 * @brief Defines the light effect options for immersive material.
 * The object is created with a default white color.
 *
 * @since 26.0.0
 */
typedef struct ArkUI_LightEffectOptions ArkUI_LightEffectOptions;

/**
 * @brief Defines the pointer to the light effect options.
 *
 * @since 26.0.0
 */
typedef ArkUI_LightEffectOptions* ArkUI_LightEffectOptionsHandle;

/**
 * @brief Check whether systemMaterial is supported on the current device.
 * If it is true, the {@link NODE_SYSTEM_MATERIAL} attribute can be used;
 * otherwise, setting the NODE_SYSTEM_MATERIAL attribute will be ineffective.
 * It is defined by the device and cannot be modified.
 *
 * @return Returns whether systemMaterial is enabled on the device.
 * @since 26.0.0
 */
bool OH_ArkUI_NativeModule_GetSystemMaterialSupported();

/**
 * @brief Obtain the global material level, which is related to the computing power of the device. It is defined by the
 * device and cannot be modified.
 *
 * @return Returns the material level of the device. The return type is {@link ArkUI_MaterialLevel}.
 * @since 26.0.0
 */
ArkUI_MaterialLevel OH_ArkUI_NativeModule_GetGlobalMaterialLevel();

/**
 * @brief Creates an immersive material object with the specified style. The level of the created material follows
 * the global material level and can be obtained through {@link OH_ArkUI_NativeModule_GetGlobalMaterialLevel}.
 *
 * @param style The material style. The parameter type is {@link ArkUI_ImmersiveStyle}.
 * @return Returns the pointer to the created immersive material object.
 *         If creation fails or the style is invalid, returns NULL.
 * @since 26.0.0
 */
ArkUI_ImmersiveMaterialHandle OH_ArkUI_NativeModule_ImmersiveMaterial_Create(ArkUI_ImmersiveStyle style);

/**
 * @brief Destroys an immersive material object.
 *
 * @param material Pointer to material object.
 *     The type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_ImmersiveMaterial_Destroy(ArkUI_ImmersiveMaterialHandle material);

/**
 * @brief Sets the style. Only effective for exquisite and gentle materials.
 *
 * @param material Pointer to material object. The type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @param style The material style. The type is {@link ArkUI_ImmersiveStyle}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle style);

/**
 * @brief Gets the style of an immersive material object.
 *
 * @param material Pointer to material object. The type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @param style Pointer to style. The type is {@link ArkUI_ImmersiveStyle}.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetStyle(
    ArkUI_ImmersiveMaterialHandle material, ArkUI_ImmersiveStyle* style);

/**
 * @brief Sets the material color of an immersive material object. This parameter is only
 *        effective for exquisite and gentle materials. If not set, the default value
 *        is 0 which means transparent color.
 *
 * @param material The pointer to the immersive material object. The parameter
 *        type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @param color The material color in 0xARGB format. Pass 0 for
 *        transparent (default value).
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t color);

/**
 * @brief Gets the material color of an immersive material object.
 *
 * @param material Pointer to material object. The type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @param color Pointer to color in 0xARGB format.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetMaterialColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

/**
 * @brief Sets the apply shadow attribute of an immersive material object. This parameter is effective for all levels
 * of materials. When this parameter is true, the shadow effect in the material takes effect, taking precedence over
 * the shadow general property. When this parameter is false, the shadow general property takes effect, and the
 * material has no shadow effect. If not set, the default value is true.
 *
 * @param material Pointer to material object. The type is {@link ArkUI_ImmersiveMaterialHandle}.
 * @param applyShadow Whether to add shadows of the material effect. Default value is true.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool applyShadow);

/**
 * @brief Gets the apply shadow attribute of an immersive material object.
 *
 * @param material The pointer to the immersive material object. The parameter type is
 *        {@link ArkUI_ImmersiveMaterialHandle}.
 * @param applyShadow Pointer to the variable that receives whether to apply shadow. Default value is true.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetApplyShadow(
    ArkUI_ImmersiveMaterialHandle material, bool* applyShadow);

/**
 * @brief Sets the interactive attribute of an immersive material object. This parameter is effective for all levels
 * of materials. When this parameter is true, the material is interactive. When this parameter is false,
 * the material is not interactive. If not set, it follows the behavior of the component.
 *
 * @param material The pointer to the immersive material object. The parameter type is
 *        {@link ArkUI_ImmersiveMaterialHandle}.
 * @param interactive Whether the material is interactive.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool interactive);

/**
 * @brief Gets the interactive attribute of an immersive material object.
 * If the value is never set, the function will return {@link ARKUI_ERROR_CODE_PARAM_ERROR}.
 *
 * @param material The pointer to the immersive material object. The parameter type is
 *        {@link ArkUI_ImmersiveMaterialHandle}.
 * @param interactive Pointer to the variable that receives whether the material is interactive.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if the value is never set.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetInteractive(
    ArkUI_ImmersiveMaterialHandle material, bool* interactive);

/**
 * @brief Creates a light effect options object with default white color.
 *
 * @return Returns the pointer to the created object.
 * @since 26.0.0
 */
ArkUI_LightEffectOptionsHandle OH_ArkUI_NativeModule_LightEffectOptions_Create();

/**
 * @brief Destroys a light effect options object.
 *
 * @param options The pointer to the options object.
 * @since 26.0.0
 */
void OH_ArkUI_NativeModule_LightEffectOptions_Destroy(ArkUI_LightEffectOptionsHandle options);

/**
 * @brief Sets the color of the light effect.
 * If not set, the default white color is white(0xffffffff).
 *
 * @param options The pointer to the options object. The parameter type is {@link ArkUI_LightEffectOptionsHandle}.
 * @param color The light effect color in 0xARGB format.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_LightEffectOptions_SetColor(
    ArkUI_LightEffectOptionsHandle options, uint32_t color);

/**
 * @brief Sets the light effect of an immersive material object.
 * Passing NULL disables the light effect. Passing non-NULL enables it with the options.
 * If not set, it follows the behavior of the component.
 *
 * @param material The pointer to the immersive material object. The parameter type is
 *        {@link ArkUI_ImmersiveMaterialHandle}.
 * @param options The light effect options. Pass NULL to disable.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect(
    ArkUI_ImmersiveMaterialHandle material, const ArkUI_LightEffectOptionsHandle options);

/**
 * @brief Gets the color of the light effect of an immersive material object.
 * Only succeeds if {@link OH_ArkUI_NativeModule_ImmersiveMaterial_SetLightEffect} was called with non-NULL options.
 * If never set or disabled (NULL passed), returns {@link ARKUI_ERROR_CODE_PARAM_ERROR}.
 *
 * @param material The pointer to the immersive material object. The parameter type is
 *        {@link ArkUI_ImmersiveMaterialHandle}.
 * @param color Pointer to the variable that receives the light effect color.
 * @return Returns the result code.
 *         Returns {@link ARKUI_ERROR_CODE_NO_ERROR} if the operation is successful.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_INVALID} if a parameter exception occurs.
 *         Returns {@link ARKUI_ERROR_CODE_PARAM_ERROR} if lightEffect is never set or disabled.
 * @since 26.0.0
 */
ArkUI_ErrorCode OH_ArkUI_NativeModule_ImmersiveMaterial_GetLightEffectColor(
    ArkUI_ImmersiveMaterialHandle material, uint32_t* color);

#ifdef __cplusplus
};
#endif

#endif // ARKUI_NATIVE_MATERIAL_H
/** @} */
