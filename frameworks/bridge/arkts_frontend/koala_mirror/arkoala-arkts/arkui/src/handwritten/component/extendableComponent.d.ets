/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
 * @file
 * @kit ArkUI
 */
import { memo } from "@koalaui/runtime/annotations"

export class UIContext {}

/**
 * Defining interface of LifeCycle for custom component and custom dialog
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 20
 */
export interface LifeCycle {
    /**
     * aboutToAppear Method.
     *
     * The aboutToAppear function is executed after a new instance of the custom component is created,
     * before its build() function is executed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    aboutToAppear(): void

    /**
     * aboutToDisappear Method.
     *
     * The aboutToDisappear function executes before a custom component is destroyed.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    aboutToDisappear(): void

    /**
     * The callback method after the custom component is built.
     *
     * Triggered when the custom component has been built.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    onDidBuild(): void

    /**
     * Customize the build process of the custom component.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    @memo
    build(): void
}

/**
 * Definition of extendable component, which is base class of custom component and custom dialog.
 *
 * @implements LifeCycle
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 20
 */
export abstract class ExtendableComponent implements LifeCycle {
    /**
     * Get current UIContext.
     *
     * @returns { UIContext } The UIContext that the custom component belongs to.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    abstract getUIContext(): UIContext

    /**
     * Get uniqueId of the custom component.
     *
     * @returns { int } - The uniqueId of the custom component.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @atomicservice
     * @since 20
     */
    abstract getUniqueId(): int
}