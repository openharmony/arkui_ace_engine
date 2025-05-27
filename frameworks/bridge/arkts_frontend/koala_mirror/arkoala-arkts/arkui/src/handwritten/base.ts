/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { AnimateParam } from "../generated";

export interface AttributeModifier<T> {
    isUpdater: boolean;
    /**@memo*/
    applyNormalAttribute(instance: T): void;
    /**@memo*/
    applyPressedAttribute(instance: T): void;
    /**@memo*/
    applyFocusedAttribute(instance: T): void;
    /**@memo*/
    applyDisabledAttribute(instance: T): void;
    /**@memo*/
    applySelectedAttribute(instance: T): void;
}

export interface UICommonBase {
    /** @memo */
    __applyStyle<T, A>(
        /** @memo */
        style: (instance: T, args: A) => T,
        arg: A
    ): T

    /** @memo */
    __applyAnimatableExtend<T, A>(
        /** @memo */
        func: (instance: T, arg: A) => T,
        arg: A
    ): T

    animationStart(param: AnimateParam): this
    animationEnd(): this
}

// TODO: implement this
export interface SubscribaleAbstract {}
export interface CommonTransition {}
export { AbstractProperty } from "@koalaui/arkui-common"
export interface CustomComponent {}
export interface IPropertySubscriber {}
export interface ISinglePropertyChangeSubscriber {}

