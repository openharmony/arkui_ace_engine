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

import { NodeAttach, remember } from "@koalaui/runtime"
import { ArkCustomComponentImpl } from "./ArkCustomComponent"
import { ArkCommonMethodComponent } from "./generated"
import { ArkPageTransitionEnter, ArkPageTransitionExit } from "./handwritten/ArkPageTransition";
import { PageTransitionOptions } from "./component/pageTransition";
import { ArkComponentRoot } from "./ArkComponentRoot"
import { ArkColumnPeer } from "./generated/peers/ArkColumnPeer";

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
        arg2?: T_Options,
        reuseKey?: string
    ): void {
        if (reuseKey) {
            ArkStructBase._instantiateReusable(reuseKey!, attributes, factory, arg1, arg2);
            return
        }
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
        ArkPageTransitionEnter(undefined, undefined, { duration: 100 } as PageTransitionOptions)
        ArkPageTransitionExit(undefined, undefined, { duration: 100 } as PageTransitionOptions)
    }

    /** @memo */
    static _instantiateReusable<T extends ArkStructBase<T, T_Options>, T_Options>(
        reuseId: string,
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        factory: () => T,
        /** @memo */
        arg1?: () => void,
        arg2?: T_Options,
    ): void {
        /* need to wrap both states and build() of @Component */
        NodeAttach(() => ArkColumnPeer.create(), (node: ArkColumnPeer) => { // replace with Frontend Node later
            const component = remember(() => {
                const instance = factory()
                instance.__initializeStruct(arg1, arg2);
                node.setOnRecycle(() =>
                    instance.aboutToRecycle()
                )
                return instance
            });
            node.setOnReuse(
                () => {
                    if (arg2) component.aboutToReuse(component.__toRecord(arg2!! as Object))
                }
            )
            component._buildWrapper(attributes, arg1, arg2);
        }, reuseId)
    }

    abstract __toRecord(param: Object): Record<string, Object> // overridden by CustomDelegate
}
