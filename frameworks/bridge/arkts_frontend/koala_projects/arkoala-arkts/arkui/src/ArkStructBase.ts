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

import { remember } from "@koalaui/runtime"
import { ArkCustomComponentImpl } from "./ArkCustomComponent"
import { ArkCommonMethodComponent } from "./generated"
import { ArkPageTransitionEnter, ArkPageTransitionExit } from "./handwritten/ArkPageTransition";
import { PageTransitionOptions } from "./generated/ArkPageTransitionInterfaces";
import { ArkComponentRoot } from "./ArkComponentRoot"

/** base class for user's structs */
export abstract class ArkStructBase<T, T_Options> extends ArkCustomComponentImpl {
    // Can be overridden as an effect of @Prop, @Watch etc
    /** @memo */
    protected __updateStruct(arg1?: T_Options): void { }

    /** @memo */
    static _instantiate<T extends ArkStructBase<T, T_Options>, T_Options>(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        factory: () => T,
        /** @memo */
        arg1?: () => void,
        arg2?: T_Options
    ): void {
        const receiver = remember(() => {
            const instance = factory();
            instance.__initializeStruct(arg1, arg2);
            return instance;
        });
        receiver._buildWrapper(attributes, arg1, arg2);
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        console.log("__initializeStruct()")
    }

    /** @memo */
    _buildWrapper(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        ArkComponentRoot(this, () => {
            this.__updateStruct(initializers)
            this.__build(attributes, content, initializers)
        })
    }

    /** @memo */
    abstract __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void

    /** @memo */
    pageTransition(): void {
        ArkPageTransitionEnter(undefined, undefined, { duration: 100 } as PageTransitionOptions )
        ArkPageTransitionExit(undefined, undefined, { duration: 100 } as PageTransitionOptions )
    }
}
