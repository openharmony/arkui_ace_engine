import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
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
class ArkExportComponent1Component extends ArkStructBase<ArkExportComponent1Component, ExportComponent1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ExportComponent1Options): void {
        this.__backing_ExportComponent1Link1 = initializers!.__backing_ExportComponent1Link1!;
        this.__backing_ExportComponent1Link2 = initializers!.__backing_ExportComponent1Link2!;
        this.__backing_ExportComponent1Link3 = initializers!.__backing_ExportComponent1Link3!;
        this.__backing_ExportComponent1Link4 = initializers!.__backing_ExportComponent1Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_ExportComponent1Link1?: MutableState<any>;
    private get ExportComponent1Link1(): any {
        return this.__backing_ExportComponent1Link1!.value;
    }
    private set ExportComponent1Link1(value: any) {
        this.__backing_ExportComponent1Link1!.value = observableProxy(value);
    }
    private __backing_ExportComponent1Link2?: MutableState<number>;
    private get ExportComponent1Link2(): number {
        return this.__backing_ExportComponent1Link2!.value;
    }
    private set ExportComponent1Link2(value: number) {
        this.__backing_ExportComponent1Link2!.value = observableProxy(value);
    }
    private __backing_ExportComponent1Link3?: MutableState<boolean>;
    private get ExportComponent1Link3(): boolean {
        return this.__backing_ExportComponent1Link3!.value;
    }
    private set ExportComponent1Link3(value: boolean) {
        this.__backing_ExportComponent1Link3!.value = observableProxy(value);
    }
    private __backing_ExportComponent1Link4?: MutableState<string>;
    private get ExportComponent1Link4(): string {
        return this.__backing_ExportComponent1Link4!.value;
    }
    private set ExportComponent1Link4(value: string) {
        this.__backing_ExportComponent1Link4!.value = observableProxy(value);
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
    content?: () => void, initializers?: ExportComponent1Options) {
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
class ArkExportComponent2Component extends ArkStructBase<ArkExportComponent2Component, ExportComponent2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ExportComponent2Options): void {
        this.__backing_ExportComponent2Link1 = initializers!.__backing_ExportComponent2Link1!;
        this.__backing_ExportComponent2Link2 = initializers!.__backing_ExportComponent2Link2!;
        this.__backing_ExportComponent2Link3 = initializers!.__backing_ExportComponent2Link3!;
        this.__backing_ExportComponent2Link4 = initializers!.__backing_ExportComponent2Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_ExportComponent2Link1?: MutableState<any>;
    private get ExportComponent2Link1(): any {
        return this.__backing_ExportComponent2Link1!.value;
    }
    private set ExportComponent2Link1(value: any) {
        this.__backing_ExportComponent2Link1!.value = observableProxy(value);
    }
    private __backing_ExportComponent2Link2?: MutableState<number>;
    private get ExportComponent2Link2(): number {
        return this.__backing_ExportComponent2Link2!.value;
    }
    private set ExportComponent2Link2(value: number) {
        this.__backing_ExportComponent2Link2!.value = observableProxy(value);
    }
    private __backing_ExportComponent2Link3?: MutableState<boolean>;
    private get ExportComponent2Link3(): boolean {
        return this.__backing_ExportComponent2Link3!.value;
    }
    private set ExportComponent2Link3(value: boolean) {
        this.__backing_ExportComponent2Link3!.value = observableProxy(value);
    }
    private __backing_ExportComponent2Link4?: MutableState<string>;
    private get ExportComponent2Link4(): string {
        return this.__backing_ExportComponent2Link4!.value;
    }
    private set ExportComponent2Link4(value: string) {
        this.__backing_ExportComponent2Link4!.value = observableProxy(value);
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
    content?: () => void, initializers?: ExportComponent2Options) {
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
class ArkExportComponent3Component extends ArkStructBase<ArkExportComponent3Component, ExportComponent3Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ExportComponent3Options): void {
        this.__backing_ExportComponent3Link1 = initializers!.__backing_ExportComponent3Link1!;
        this.__backing_ExportComponent3Link2 = initializers!.__backing_ExportComponent3Link2!;
        this.__backing_ExportComponent3Link3 = initializers!.__backing_ExportComponent3Link3!;
        this.__backing_ExportComponent3Link4 = initializers!.__backing_ExportComponent3Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_ExportComponent3Link1?: MutableState<any>;
    private get ExportComponent3Link1(): any {
        return this.__backing_ExportComponent3Link1!.value;
    }
    private set ExportComponent3Link1(value: any) {
        this.__backing_ExportComponent3Link1!.value = observableProxy(value);
    }
    private __backing_ExportComponent3Link2?: MutableState<number>;
    private get ExportComponent3Link2(): number {
        return this.__backing_ExportComponent3Link2!.value;
    }
    private set ExportComponent3Link2(value: number) {
        this.__backing_ExportComponent3Link2!.value = observableProxy(value);
    }
    private __backing_ExportComponent3Link3?: MutableState<boolean>;
    private get ExportComponent3Link3(): boolean {
        return this.__backing_ExportComponent3Link3!.value;
    }
    private set ExportComponent3Link3(value: boolean) {
        this.__backing_ExportComponent3Link3!.value = observableProxy(value);
    }
    private __backing_ExportComponent3Link4?: MutableState<string>;
    private get ExportComponent3Link4(): string {
        return this.__backing_ExportComponent3Link4!.value;
    }
    private set ExportComponent3Link4(value: string) {
        this.__backing_ExportComponent3Link4!.value = observableProxy(value);
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
    content?: () => void, initializers?: ExportComponent3Options) {
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
export default class ArkExportComponent4Component extends ArkStructBase<ArkExportComponent4Component, ExportComponent4Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ExportComponent4Options): void {
        this.__backing_ExportComponent4Link1 = initializers!.__backing_ExportComponent4Link1!;
        this.__backing_ExportComponent4Link2 = initializers!.__backing_ExportComponent4Link2!;
        this.__backing_ExportComponent4Link3 = initializers!.__backing_ExportComponent4Link3!;
        this.__backing_ExportComponent4Link4 = initializers!.__backing_ExportComponent4Link4!;
        this.__backing_indexState1 = stateOf<any>(initializers?.indexState1 ?? ({ count: 0 }), this);
        this.__backing_indexState2 = stateOf<number>(initializers?.indexState2 ?? (0), this);
        this.__backing_indexState3 = stateOf<boolean>(initializers?.indexState3 ?? (false), this);
        this.__backing_indexState4 = stateOf<string>(initializers?.indexState4 ?? ('Home'), this);
    }
    private __backing_ExportComponent4Link1?: MutableState<any>;
    private get ExportComponent4Link1(): any {
        return this.__backing_ExportComponent4Link1!.value;
    }
    private set ExportComponent4Link1(value: any) {
        this.__backing_ExportComponent4Link1!.value = observableProxy(value);
    }
    private __backing_ExportComponent4Link2?: MutableState<number>;
    private get ExportComponent4Link2(): number {
        return this.__backing_ExportComponent4Link2!.value;
    }
    private set ExportComponent4Link2(value: number) {
        this.__backing_ExportComponent4Link2!.value = observableProxy(value);
    }
    private __backing_ExportComponent4Link3?: MutableState<boolean>;
    private get ExportComponent4Link3(): boolean {
        return this.__backing_ExportComponent4Link3!.value;
    }
    private set ExportComponent4Link3(value: boolean) {
        this.__backing_ExportComponent4Link3!.value = observableProxy(value);
    }
    private __backing_ExportComponent4Link4?: MutableState<string>;
    private get ExportComponent4Link4(): string {
        return this.__backing_ExportComponent4Link4!.value;
    }
    private set ExportComponent4Link4(value: string) {
        this.__backing_ExportComponent4Link4!.value = observableProxy(value);
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
    content?: () => void, initializers?: ExportComponent4Options) {
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
export { ExportComponent1 as ExportComponent, ExportComponent2, ExportComponent3 };
export {};
/** @memo */
export function ExportComponent1(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ExportComponent1Options): void {
    const updatedInitializers: ExportComponent1Options = {
        __backing_ExportComponent1Link1: initializers?.__backing_ExportComponent1Link1,
        __backing_ExportComponent1Link2: initializers?.__backing_ExportComponent1Link2,
        __backing_ExportComponent1Link3: initializers?.__backing_ExportComponent1Link3,
        __backing_ExportComponent1Link4: initializers?.__backing_ExportComponent1Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkExportComponent1Component._instantiate(style, () => new ArkExportComponent1Component, content, updatedInitializers);
}
/** @memo */
export function ExportComponent2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ExportComponent2Options): void {
    const updatedInitializers: ExportComponent2Options = {
        __backing_ExportComponent2Link1: initializers?.__backing_ExportComponent2Link1,
        __backing_ExportComponent2Link2: initializers?.__backing_ExportComponent2Link2,
        __backing_ExportComponent2Link3: initializers?.__backing_ExportComponent2Link3,
        __backing_ExportComponent2Link4: initializers?.__backing_ExportComponent2Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkExportComponent2Component._instantiate(style, () => new ArkExportComponent2Component, content, updatedInitializers);
}
/** @memo */
export function ExportComponent3(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ExportComponent3Options): void {
    const updatedInitializers: ExportComponent3Options = {
        __backing_ExportComponent3Link1: initializers?.__backing_ExportComponent3Link1,
        __backing_ExportComponent3Link2: initializers?.__backing_ExportComponent3Link2,
        __backing_ExportComponent3Link3: initializers?.__backing_ExportComponent3Link3,
        __backing_ExportComponent3Link4: initializers?.__backing_ExportComponent3Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkExportComponent3Component._instantiate(style, () => new ArkExportComponent3Component, content, updatedInitializers);
}
/** @memo */
export function ExportComponent4(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ExportComponent4Options): void {
    const updatedInitializers: ExportComponent4Options = {
        __backing_ExportComponent4Link1: initializers?.__backing_ExportComponent4Link1,
        __backing_ExportComponent4Link2: initializers?.__backing_ExportComponent4Link2,
        __backing_ExportComponent4Link3: initializers?.__backing_ExportComponent4Link3,
        __backing_ExportComponent4Link4: initializers?.__backing_ExportComponent4Link4,
        __backing_indexState1: initializers?.__backing_indexState1,
        __backing_indexState2: initializers?.__backing_indexState2,
        __backing_indexState3: initializers?.__backing_indexState3,
        __backing_indexState4: initializers?.__backing_indexState4
    };
    ArkExportComponent4Component._instantiate(style, () => new ArkExportComponent4Component, content, updatedInitializers);
}
export interface ExportComponent1Options {
    __backing_ExportComponent1Link1?: MutableState<any>;
    ExportComponent1Link1?: any;
    __backing_ExportComponent1Link2?: MutableState<number>;
    ExportComponent1Link2?: number;
    __backing_ExportComponent1Link3?: MutableState<boolean>;
    ExportComponent1Link3?: boolean;
    __backing_ExportComponent1Link4?: MutableState<string>;
    ExportComponent1Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface ExportComponent2Options {
    __backing_ExportComponent2Link1?: MutableState<any>;
    ExportComponent2Link1?: any;
    __backing_ExportComponent2Link2?: MutableState<number>;
    ExportComponent2Link2?: number;
    __backing_ExportComponent2Link3?: MutableState<boolean>;
    ExportComponent2Link3?: boolean;
    __backing_ExportComponent2Link4?: MutableState<string>;
    ExportComponent2Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface ExportComponent3Options {
    __backing_ExportComponent3Link1?: MutableState<any>;
    ExportComponent3Link1?: any;
    __backing_ExportComponent3Link2?: MutableState<number>;
    ExportComponent3Link2?: number;
    __backing_ExportComponent3Link3?: MutableState<boolean>;
    ExportComponent3Link3?: boolean;
    __backing_ExportComponent3Link4?: MutableState<string>;
    ExportComponent3Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
export interface ExportComponent4Options {
    __backing_ExportComponent4Link1?: MutableState<any>;
    ExportComponent4Link1?: any;
    __backing_ExportComponent4Link2?: MutableState<number>;
    ExportComponent4Link2?: number;
    __backing_ExportComponent4Link3?: MutableState<boolean>;
    ExportComponent4Link3?: boolean;
    __backing_ExportComponent4Link4?: MutableState<string>;
    ExportComponent4Link4?: string;
    __backing_indexState1?: MutableState<any>;
    indexState1?: any;
    __backing_indexState2?: MutableState<number>;
    indexState2?: number;
    __backing_indexState3?: MutableState<boolean>;
    indexState3?: boolean;
    __backing_indexState4?: MutableState<string>;
    indexState4?: string;
}
