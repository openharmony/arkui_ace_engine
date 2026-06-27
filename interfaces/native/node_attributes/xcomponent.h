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
 * @brief Defines xcomponent attribute enum value.
 *
 * @since 12
 */

/**
 * @file xcomponent.h
 *
 * @brief Defines xcomponent attribute enum value.
 *
 * @library libace_ndk.z.so
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @kit ArkUI
 * @since 12
 */
#ifndef ARKUI_XCOMPONENT_H
#define ARKUI_XCOMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Enumerates the types of the **XComponent** component.
 *
 * @since 12
 */
typedef enum {
    /**
     * The custom content of EGL/OpenGL ES and media data is displayed individually on the screen.
     * @since 12
     */
    ARKUI_XCOMPONENT_TYPE_SURFACE = 0,
    /**
     * The custom content of EGL/OpenGL ES and media data is grouped and displayed together with content of the
     * component.
     * @since 12
     */
    ARKUI_XCOMPONENT_TYPE_TEXTURE = 2,
} ArkUI_XComponentType;

#ifdef __cplusplus
}
#endif

#endif // ARKUI_XCOMPONENT_H
/** @} */
