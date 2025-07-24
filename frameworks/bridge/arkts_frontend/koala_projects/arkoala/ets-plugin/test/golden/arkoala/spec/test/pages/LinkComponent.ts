import { ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
import DefaultComponent from "./DefaultComponent";
/** @memo:stable */
class ArkLinkComponent1Component extends ArkStructBase<ArkLinkComponent1Component, LinkComponent1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent1Options): void {
        this.__backing_LinkComponent1Link1 = initializers!.__backing_LinkComponent1Link1!;
        this.__backing_LinkComponent1Link2 = initializers!.__backing_LinkComponent1Link2!;
        this.__backing_LinkComponent1Link3 = initializers!.__backing_LinkComponent1Link3!;
        this.__backing_LinkComponent1Link4 = initializers!.__backing_LinkComponent1Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_LinkComponent1Link1?: MutableState<any>;
    private get LinkComponent1Link1(): any {
        return this.__backing_LinkComponent1Link1!.value;
    }
    private set LinkComponent1Link1(value: any) {
        this.__backing_LinkComponent1Link1!.value = observableProxy(value);
    }
    private __backing_LinkComponent1Link2?: MutableState<number>;
    private get LinkComponent1Link2(): number {
        return this.__backing_LinkComponent1Link2!.value;
    }
    private set LinkComponent1Link2(value: number) {
        this.__backing_LinkComponent1Link2!.value = observableProxy(value);
    }
    private __backing_LinkComponent1Link3?: MutableState<boolean>;
    private get LinkComponent1Link3(): boolean {
        return this.__backing_LinkComponent1Link3!.value;
    }
    private set LinkComponent1Link3(value: boolean) {
        this.__backing_LinkComponent1Link3!.value = observableProxy(value);
    }
    private __backing_LinkComponent1Link4?: MutableState<string>;
    private get LinkComponent1Link4(): string {
        return this.__backing_LinkComponent1Link4!.value;
    }
    private set LinkComponent1Link4(value: string) {
        this.__backing_LinkComponent1Link4!.value = observableProxy(value);
    }
    private __backing_indexState1?: MutableState<any>;
    private get indexState1(): any {
        return this.__backing_indexState1!.value;
    }
    private set indexState1(value: any) {
        this.__backing_indexState1!.value = observableProxy(value);
    }
    private __backing_indexState2?: MutableState<number>;
    private get indexState2(): number {
        return this.__backing_indexState2!.value;
    }
    private set indexState2(value: number) {
        this.__backing_indexState2!.value = observableProxy(value);
    }
    private __backing_indexState3?: MutableState<boolean>;
    private get indexState3(): boolean {
        return this.__backing_indexState3!.value;
    }
    private set indexState3(value: boolean) {
        this.__backing_indexState3!.value = observableProxy(value);
    }
    private __backing_indexState4?: MutableState<string>;
    private get indexState4(): string {
        return this.__backing_indexState4!.value;
    }
    private set indexState4(value: string) {
        this.__backing_indexState4!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent1Options) {
        ArkRow(__builder, () => {
            DefaultComponent({
                __backing_DefaultComponentLink1: this.__backing_indexState1,
                __backing_DefaultComponentLink2: this.__backing_indexState2,
                __backing_DefaultComponentLink3: this.__backing_indexState3,
                __backing_DefaultComponentLink4: this.__backing_indexState4,
                myVar: 100,
                myVar2: 100
            });
        });
    }
}
/** @memo:stable */
class ArkLinkComponent2Component extends ArkStructBase<ArkLinkComponent2Component, LinkComponent2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent2Options): void {
        this.__backing_LinkComponent2Link1 = initializers!.__backing_LinkComponent2Link1!;
        this.__backing_LinkComponent2Link2 = initializers!.__backing_LinkComponent2Link2!;
        this.__backing_LinkComponent2Link3 = initializers!.__backing_LinkComponent2Link3!;
        this.__backing_LinkComponent2Link4 = initializers!.__backing_LinkComponent2Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_LinkComponent2Link1?: MutableState<any>;
    private get LinkComponent2Link1(): any {
        return this.__backing_LinkComponent2Link1!.value;
    }
    private set LinkComponent2Link1(value: any) {
        this.__backing_LinkComponent2Link1!.value = observableProxy(value);
    }
    private __backing_LinkComponent2Link2?: MutableState<number>;
    private get LinkComponent2Link2(): number {
        return this.__backing_LinkComponent2Link2!.value;
    }
    private set LinkComponent2Link2(value: number) {
        this.__backing_LinkComponent2Link2!.value = observableProxy(value);
    }
    private __backing_LinkComponent2Link3?: MutableState<boolean>;
    private get LinkComponent2Link3(): boolean {
        return this.__backing_LinkComponent2Link3!.value;
    }
    private set LinkComponent2Link3(value: boolean) {
        this.__backing_LinkComponent2Link3!.value = observableProxy(value);
    }
    private __backing_LinkComponent2Link4?: MutableState<string>;
    private get LinkComponent2Link4(): string {
        return this.__backing_LinkComponent2Link4!.value;
    }
    private set LinkComponent2Link4(value: string) {
        this.__backing_LinkComponent2Link4!.value = observableProxy(value);
    }
    private __backing_indexState1?: MutableState<any>;
    private get indexState1(): any {
        return this.__backing_indexState1!.value;
    }
    private set indexState1(value: any) {
        this.__backing_indexState1!.value = observableProxy(value);
    }
    private __backing_indexState2?: MutableState<number>;
    private get indexState2(): number {
        return this.__backing_indexState2!.value;
    }
    private set indexState2(value: number) {
        this.__backing_indexState2!.value = observableProxy(value);
    }
    private __backing_indexState3?: MutableState<boolean>;
    private get indexState3(): boolean {
        return this.__backing_indexState3!.value;
    }
    private set indexState3(value: boolean) {
        this.__backing_indexState3!.value = observableProxy(value);
    }
    private __backing_indexState4?: MutableState<string>;
    private get indexState4(): string {
        return this.__backing_indexState4!.value;
    }
    private set indexState4(value: string) {
        this.__backing_indexState4!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent2Options) {
        ArkRow(__builder, () => {
            DefaultComponent({
                __backing_DefaultComponentLink1: this.__backing_indexState1,
                __backing_DefaultComponentLink2: this.__backing_indexState2,
                __backing_DefaultComponentLink3: this.__backing_indexState3,
                __backing_DefaultComponentLink4: this.__backing_indexState4,
                myVar: 100,
                myVar2: 100
            });
        });
    }
}
/** @memo:stable */
class ArkLinkComponent3Component extends ArkStructBase<ArkLinkComponent3Component, LinkComponent3Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent3Options): void {
        this.__backing_LinkComponent3Link1 = initializers!.__backing_LinkComponent3Link1!;
        this.__backing_LinkComponent3Link2 = initializers!.__backing_LinkComponent3Link2!;
        this.__backing_LinkComponent3Link3 = initializers!.__backing_LinkComponent3Link3!;
        this.__backing_LinkComponent3Link4 = initializers!.__backing_LinkComponent3Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_LinkComponent3Link1?: MutableState<any>;
    private get LinkComponent3Link1(): any {
        return this.__backing_LinkComponent3Link1!.value;
    }
    private set LinkComponent3Link1(value: any) {
        this.__backing_LinkComponent3Link1!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link2?: MutableState<number>;
    private get LinkComponent3Link2(): number {
        return this.__backing_LinkComponent3Link2!.value;
    }
    private set LinkComponent3Link2(value: number) {
        this.__backing_LinkComponent3Link2!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link3?: MutableState<boolean>;
    private get LinkComponent3Link3(): boolean {
        return this.__backing_LinkComponent3Link3!.value;
    }
    private set LinkComponent3Link3(value: boolean) {
        this.__backing_LinkComponent3Link3!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link4?: MutableState<string>;
    private get LinkComponent3Link4(): string {
        return this.__backing_LinkComponent3Link4!.value;
    }
    private set LinkComponent3Link4(value: string) {
        this.__backing_LinkComponent3Link4!.value = observableProxy(value);
    }
    private __backing_indexState1?: MutableState<any>;
    private get indexState1(): any {
        return this.__backing_indexState1!.value;
    }
    private set indexState1(value: any) {
        this.__backing_indexState1!.value = observableProxy(value);
    }
    private __backing_indexState2?: MutableState<number>;
    private get indexState2(): number {
        return this.__backing_indexState2!.value;
    }
    private set indexState2(value: number) {
        this.__backing_indexState2!.value = observableProxy(value);
    }
    private __backing_indexState3?: MutableState<boolean>;
    private get indexState3(): boolean {
        return this.__backing_indexState3!.value;
    }
    private set indexState3(value: boolean) {
        this.__backing_indexState3!.value = observableProxy(value);
    }
    private __backing_indexState4?: MutableState<string>;
    private get indexState4(): string {
        return this.__backing_indexState4!.value;
    }
    private set indexState4(value: string) {
        this.__backing_indexState4!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent3Options) {
        ArkRow(__builder, () => {
            DefaultComponent({
                __backing_DefaultComponentLink1: this.__backing_indexState1,
                __backing_DefaultComponentLink2: this.__backing_indexState2,
                __backing_DefaultComponentLink3: this.__backing_indexState3,
                __backing_DefaultComponentLink4: this.__backing_indexState4,
                myVar: 100,
                myVar2: 100
            });
        });
    }
}
/** @memo:stable */
class ArkLinkComponent4Component extends ArkStructBase<ArkLinkComponent4Component, LinkComponent4Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent4Options): void {
        this.__backing_LinkComponent3Link1 = initializers!.__backing_LinkComponent3Link1!;
        this.__backing_LinkComponent3Link2 = initializers!.__backing_LinkComponent3Link2!;
        this.__backing_LinkComponent3Link3 = initializers!.__backing_LinkComponent3Link3!;
        this.__backing_LinkComponent3Link4 = initializers!.__backing_LinkComponent3Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_LinkComponent3Link1?: MutableState<any>;
    private get LinkComponent3Link1(): any {
        return this.__backing_LinkComponent3Link1!.value;
    }
    private set LinkComponent3Link1(value: any) {
        this.__backing_LinkComponent3Link1!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link2?: MutableState<number>;
    private get LinkComponent3Link2(): number {
        return this.__backing_LinkComponent3Link2!.value;
    }
    private set LinkComponent3Link2(value: number) {
        this.__backing_LinkComponent3Link2!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link3?: MutableState<boolean>;
    private get LinkComponent3Link3(): boolean {
        return this.__backing_LinkComponent3Link3!.value;
    }
    private set LinkComponent3Link3(value: boolean) {
        this.__backing_LinkComponent3Link3!.value = observableProxy(value);
    }
    private __backing_LinkComponent3Link4?: MutableState<string>;
    private get LinkComponent3Link4(): string {
        return this.__backing_LinkComponent3Link4!.value;
    }
    private set LinkComponent3Link4(value: string) {
        this.__backing_LinkComponent3Link4!.value = observableProxy(value);
    }
    private __backing_indexState1?: MutableState<any>;
    private get indexState1(): any {
        return this.__backing_indexState1!.value;
    }
    private set indexState1(value: any) {
        this.__backing_indexState1!.value = observableProxy(value);
    }
    private __backing_indexState2?: MutableState<number>;
    private get indexState2(): number {
        return this.__backing_indexState2!.value;
    }
    private set indexState2(value: number) {
        this.__backing_indexState2!.value = observableProxy(value);
    }
    private __backing_indexState3?: MutableState<boolean>;
    private get indexState3(): boolean {
        return this.__backing_indexState3!.value;
    }
    private set indexState3(value: boolean) {
        this.__backing_indexState3!.value = observableProxy(value);
    }
    private __backing_indexState4?: MutableState<string>;
    private get indexState4(): string {
        return this.__backing_indexState4!.value;
    }
    private set indexState4(value: string) {
        this.__backing_indexState4!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkComponent4Options) {
        ArkRow(__builder, () => {
            DefaultComponent({
                __backing_DefaultComponentLink1: this.__backing_indexState1,
                __backing_DefaultComponentLink2: this.__backing_indexState2,
                __backing_DefaultComponentLink3: this.__backing_indexState3,
                __backing_DefaultComponentLink4: this.__backing_indexState4,
                myVar: 100,
                myVar2: 100
            });
        });
    }
}
export { LinkComponent1 as LinkComponent, LinkComponent2, LinkComponent3 };
export default LinkComponent4;
export {};
/** @memo */
export function LinkComponent1(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkComponent1Options): void {
    const updatedInitializers: LinkComponent1Options = {
        __backing_LinkComponent1Link1: initializers?.__backing_LinkComponent1Link1,
        __backing_LinkComponent1Link2: initializers?.__backing_LinkComponent1Link2,
        __backing_LinkComponent1Link3: initializers?.__backing_LinkComponent1Link3,
        __backing_LinkComponent1Link4: initializers?.__backing_LinkComponent1Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkLinkComponent1Component._instantiate(style, () => new ArkLinkComponent1Component, content, updatedInitializers);
}
/** @memo */
export function LinkComponent2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkComponent2Options): void {
    const updatedInitializers: LinkComponent2Options = {
        __backing_LinkComponent2Link1: initializers?.__backing_LinkComponent2Link1,
        __backing_LinkComponent2Link2: initializers?.__backing_LinkComponent2Link2,
        __backing_LinkComponent2Link3: initializers?.__backing_LinkComponent2Link3,
        __backing_LinkComponent2Link4: initializers?.__backing_LinkComponent2Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkLinkComponent2Component._instantiate(style, () => new ArkLinkComponent2Component, content, updatedInitializers);
}
/** @memo */
export function LinkComponent3(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkComponent3Options): void {
    const updatedInitializers: LinkComponent3Options = {
        __backing_LinkComponent3Link1: initializers?.__backing_LinkComponent3Link1,
        __backing_LinkComponent3Link2: initializers?.__backing_LinkComponent3Link2,
        __backing_LinkComponent3Link3: initializers?.__backing_LinkComponent3Link3,
        __backing_LinkComponent3Link4: initializers?.__backing_LinkComponent3Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkLinkComponent3Component._instantiate(style, () => new ArkLinkComponent3Component, content, updatedInitializers);
}
/** @memo */
export function LinkComponent4(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkComponent4Options): void {
    const updatedInitializers: LinkComponent4Options = {
        __backing_LinkComponent3Link1: initializers?.__backing_LinkComponent3Link1,
        __backing_LinkComponent3Link2: initializers?.__backing_LinkComponent3Link2,
        __backing_LinkComponent3Link3: initializers?.__backing_LinkComponent3Link3,
        __backing_LinkComponent3Link4: initializers?.__backing_LinkComponent3Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkLinkComponent4Component._instantiate(style, () => new ArkLinkComponent4Component, content, updatedInitializers);
}
export interface LinkComponent1Options {
    __backing_LinkComponent1Link1?: MutableState<any>;
    LinkComponent1Link1?: any;
    __backing_LinkComponent1Link2?: MutableState<number>;
    LinkComponent1Link2?: number;
    __backing_LinkComponent1Link3?: MutableState<boolean>;
    LinkComponent1Link3?: boolean;
    __backing_LinkComponent1Link4?: MutableState<string>;
    LinkComponent1Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface LinkComponent2Options {
    __backing_LinkComponent2Link1?: MutableState<any>;
    LinkComponent2Link1?: any;
    __backing_LinkComponent2Link2?: MutableState<number>;
    LinkComponent2Link2?: number;
    __backing_LinkComponent2Link3?: MutableState<boolean>;
    LinkComponent2Link3?: boolean;
    __backing_LinkComponent2Link4?: MutableState<string>;
    LinkComponent2Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface LinkComponent3Options {
    __backing_LinkComponent3Link1?: MutableState<any>;
    LinkComponent3Link1?: any;
    __backing_LinkComponent3Link2?: MutableState<number>;
    LinkComponent3Link2?: number;
    __backing_LinkComponent3Link3?: MutableState<boolean>;
    LinkComponent3Link3?: boolean;
    __backing_LinkComponent3Link4?: MutableState<string>;
    LinkComponent3Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface LinkComponent4Options {
    __backing_LinkComponent3Link1?: MutableState<any>;
    LinkComponent3Link1?: any;
    __backing_LinkComponent3Link2?: MutableState<number>;
    LinkComponent3Link2?: number;
    __backing_LinkComponent3Link3?: MutableState<boolean>;
    LinkComponent3Link3?: boolean;
    __backing_LinkComponent3Link4?: MutableState<string>;
    LinkComponent3Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
