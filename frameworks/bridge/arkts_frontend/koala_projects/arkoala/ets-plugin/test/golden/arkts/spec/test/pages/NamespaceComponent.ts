import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkNamespaceComponent1Component extends ArkStructBase<ArkNamespaceComponent1Component, NamespaceComponent1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent1Options): void {
        this.__backing_NamespaceComponent1Link1 = initializers!.__backing_NamespaceComponent1Link1!;
        this.__backing_NamespaceComponent1Link2 = initializers!.__backing_NamespaceComponent1Link2!;
        this.__backing_NamespaceComponent1Link3 = initializers!.__backing_NamespaceComponent1Link3!;
        this.__backing_NamespaceComponent1Link4 = initializers!.__backing_NamespaceComponent1Link4!;
        this.__backing_myVar = initializers?.myVar ?? (0);
        if (initializers?.myVar2) {
            this.__backing_myVar2 = initializers?.myVar2;
        }
    }
    private __backing_NamespaceComponent1Link1?: MutableState<any>;
    private get NamespaceComponent1Link1(): any {
        return this.__backing_NamespaceComponent1Link1!.value;
    }
    private set NamespaceComponent1Link1(value: any) {
        this.__backing_NamespaceComponent1Link1!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent1Link2?: MutableState<number>;
    private get NamespaceComponent1Link2(): number {
        return this.__backing_NamespaceComponent1Link2!.value;
    }
    private set NamespaceComponent1Link2(value: number) {
        this.__backing_NamespaceComponent1Link2!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent1Link3?: MutableState<boolean>;
    private get NamespaceComponent1Link3(): boolean {
        return this.__backing_NamespaceComponent1Link3!.value;
    }
    private set NamespaceComponent1Link3(value: boolean) {
        this.__backing_NamespaceComponent1Link3!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent1Link4?: MutableState<string>;
    private get NamespaceComponent1Link4(): string {
        return this.__backing_NamespaceComponent1Link4!.value;
    }
    private set NamespaceComponent1Link4(value: string) {
        this.__backing_NamespaceComponent1Link4!.value = observableProxy(value);
    }
    private __backing_myVar?: number;
    private get myVar(): number {
        return this.__backing_myVar as number;
    }
    private set myVar(value: number) {
        this.__backing_myVar = value;
    }
    private __backing_myVar2?: number;
    private get myVar2(): number {
        return this.__backing_myVar2 as number;
    }
    private set myVar2(value: number) {
        this.__backing_myVar2 = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent1Options) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent1');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent1Link1: ' + JSON.stringify(this.NamespaceComponent1Link1));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent1Link2: ' + JSON.stringify(this.NamespaceComponent1Link2));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent1Link3: ' + JSON.stringify(this.NamespaceComponent1Link3));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent1Link4: ' + JSON.stringify(this.NamespaceComponent1Link4));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar: ' + JSON.stringify(this.myVar));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar2: ' + JSON.stringify(this.myVar2));
        });
    }
}
/** @memo:stable */
class ArkNamespaceComponent2Component extends ArkStructBase<ArkNamespaceComponent2Component, NamespaceComponent2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent2Options): void {
        this.__backing_NamespaceComponent2Link1 = initializers!.__backing_NamespaceComponent2Link1!;
        this.__backing_NamespaceComponent2Link2 = initializers!.__backing_NamespaceComponent2Link2!;
        this.__backing_NamespaceComponent2Link3 = initializers!.__backing_NamespaceComponent2Link3!;
        this.__backing_NamespaceComponent2Link4 = initializers!.__backing_NamespaceComponent2Link4!;
        this.__backing_myVar = initializers?.myVar ?? (0);
        if (initializers?.myVar2) {
            this.__backing_myVar2 = initializers?.myVar2;
        }
    }
    private __backing_NamespaceComponent2Link1?: MutableState<any>;
    private get NamespaceComponent2Link1(): any {
        return this.__backing_NamespaceComponent2Link1!.value;
    }
    private set NamespaceComponent2Link1(value: any) {
        this.__backing_NamespaceComponent2Link1!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent2Link2?: MutableState<number>;
    private get NamespaceComponent2Link2(): number {
        return this.__backing_NamespaceComponent2Link2!.value;
    }
    private set NamespaceComponent2Link2(value: number) {
        this.__backing_NamespaceComponent2Link2!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent2Link3?: MutableState<boolean>;
    private get NamespaceComponent2Link3(): boolean {
        return this.__backing_NamespaceComponent2Link3!.value;
    }
    private set NamespaceComponent2Link3(value: boolean) {
        this.__backing_NamespaceComponent2Link3!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent2Link4?: MutableState<string>;
    private get NamespaceComponent2Link4(): string {
        return this.__backing_NamespaceComponent2Link4!.value;
    }
    private set NamespaceComponent2Link4(value: string) {
        this.__backing_NamespaceComponent2Link4!.value = observableProxy(value);
    }
    private __backing_myVar?: number;
    private get myVar(): number {
        return this.__backing_myVar as number;
    }
    private set myVar(value: number) {
        this.__backing_myVar = value;
    }
    private __backing_myVar2?: number;
    private get myVar2(): number {
        return this.__backing_myVar2 as number;
    }
    private set myVar2(value: number) {
        this.__backing_myVar2 = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent2Options) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent2');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent2Link1: ' + JSON.stringify(this.NamespaceComponent2Link1));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent2Link2: ' + JSON.stringify(this.NamespaceComponent2Link2));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent2Link3: ' + JSON.stringify(this.NamespaceComponent2Link3));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent2Link4: ' + JSON.stringify(this.NamespaceComponent2Link4));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar: ' + JSON.stringify(this.myVar));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar2: ' + JSON.stringify(this.myVar2));
        });
    }
}
/** @memo:stable */
class ArkNamespaceComponent3Component extends ArkStructBase<ArkNamespaceComponent3Component, NamespaceComponent3Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent3Options): void {
        this.__backing_NamespaceComponent3Link1 = initializers!.__backing_NamespaceComponent3Link1!;
        this.__backing_NamespaceComponent3Link2 = initializers!.__backing_NamespaceComponent3Link2!;
        this.__backing_NamespaceComponent3Link3 = initializers!.__backing_NamespaceComponent3Link3!;
        this.__backing_NamespaceComponent3Link4 = initializers!.__backing_NamespaceComponent3Link4!;
        this.__backing_myVar = initializers?.myVar ?? (0);
        if (initializers?.myVar2) {
            this.__backing_myVar2 = initializers?.myVar2;
        }
    }
    private __backing_NamespaceComponent3Link1?: MutableState<any>;
    private get NamespaceComponent3Link1(): any {
        return this.__backing_NamespaceComponent3Link1!.value;
    }
    private set NamespaceComponent3Link1(value: any) {
        this.__backing_NamespaceComponent3Link1!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent3Link2?: MutableState<number>;
    private get NamespaceComponent3Link2(): number {
        return this.__backing_NamespaceComponent3Link2!.value;
    }
    private set NamespaceComponent3Link2(value: number) {
        this.__backing_NamespaceComponent3Link2!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent3Link3?: MutableState<boolean>;
    private get NamespaceComponent3Link3(): boolean {
        return this.__backing_NamespaceComponent3Link3!.value;
    }
    private set NamespaceComponent3Link3(value: boolean) {
        this.__backing_NamespaceComponent3Link3!.value = observableProxy(value);
    }
    private __backing_NamespaceComponent3Link4?: MutableState<string>;
    private get NamespaceComponent3Link4(): string {
        return this.__backing_NamespaceComponent3Link4!.value;
    }
    private set NamespaceComponent3Link4(value: string) {
        this.__backing_NamespaceComponent3Link4!.value = observableProxy(value);
    }
    private __backing_myVar?: number;
    private get myVar(): number {
        return this.__backing_myVar as number;
    }
    private set myVar(value: number) {
        this.__backing_myVar = value;
    }
    private __backing_myVar2?: number;
    private get myVar2(): number {
        return this.__backing_myVar2 as number;
    }
    private set myVar2(value: number) {
        this.__backing_myVar2 = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: NamespaceComponent3Options) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent3');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent3Link1: ' + JSON.stringify(this.NamespaceComponent3Link1));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent3Link2: ' + JSON.stringify(this.NamespaceComponent3Link2));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent3Link3: ' + JSON.stringify(this.NamespaceComponent3Link3));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'NamespaceComponent3Link4: ' + JSON.stringify(this.NamespaceComponent3Link4));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar: ' + JSON.stringify(this.myVar));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar2: ' + JSON.stringify(this.myVar2));
        });
    }
}
export { NamespaceComponent1, NamespaceComponent2 };
export default NamespaceComponent3;
export {};
/** @memo */
export function NamespaceComponent1(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: NamespaceComponent1Options): void {
    const updatedInitializers: NamespaceComponent1Options = {
        __backing_NamespaceComponent1Link1: initializers?.__backing_NamespaceComponent1Link1,
        __backing_NamespaceComponent1Link2: initializers?.__backing_NamespaceComponent1Link2,
        __backing_NamespaceComponent1Link3: initializers?.__backing_NamespaceComponent1Link3,
        __backing_NamespaceComponent1Link4: initializers?.__backing_NamespaceComponent1Link4,
        myVar: initializers?.myVar,
        myVar2: initializers?.myVar2
    };
    ArkNamespaceComponent1Component._instantiate(style, () => new ArkNamespaceComponent1Component, content, updatedInitializers);
}
/** @memo */
export function NamespaceComponent2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: NamespaceComponent2Options): void {
    const updatedInitializers: NamespaceComponent2Options = {
        __backing_NamespaceComponent2Link1: initializers?.__backing_NamespaceComponent2Link1,
        __backing_NamespaceComponent2Link2: initializers?.__backing_NamespaceComponent2Link2,
        __backing_NamespaceComponent2Link3: initializers?.__backing_NamespaceComponent2Link3,
        __backing_NamespaceComponent2Link4: initializers?.__backing_NamespaceComponent2Link4,
        myVar: initializers?.myVar,
        myVar2: initializers?.myVar2
    };
    ArkNamespaceComponent2Component._instantiate(style, () => new ArkNamespaceComponent2Component, content, updatedInitializers);
}
/** @memo */
export function NamespaceComponent3(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: NamespaceComponent3Options): void {
    const updatedInitializers: NamespaceComponent3Options = {
        __backing_NamespaceComponent3Link1: initializers?.__backing_NamespaceComponent3Link1,
        __backing_NamespaceComponent3Link2: initializers?.__backing_NamespaceComponent3Link2,
        __backing_NamespaceComponent3Link3: initializers?.__backing_NamespaceComponent3Link3,
        __backing_NamespaceComponent3Link4: initializers?.__backing_NamespaceComponent3Link4,
        myVar: initializers?.myVar,
        myVar2: initializers?.myVar2
    };
    ArkNamespaceComponent3Component._instantiate(style, () => new ArkNamespaceComponent3Component, content, updatedInitializers);
}
export interface NamespaceComponent1Options {
    __backing_NamespaceComponent1Link1?: MutableState<any>;
    NamespaceComponent1Link1?: any;
    __backing_NamespaceComponent1Link2?: MutableState<number>;
    NamespaceComponent1Link2?: number;
    __backing_NamespaceComponent1Link3?: MutableState<boolean>;
    NamespaceComponent1Link3?: boolean;
    __backing_NamespaceComponent1Link4?: MutableState<string>;
    NamespaceComponent1Link4?: string;
    myVar?: number;
    myVar2?: number;
}
export interface NamespaceComponent2Options {
    __backing_NamespaceComponent2Link1?: MutableState<any>;
    NamespaceComponent2Link1?: any;
    __backing_NamespaceComponent2Link2?: MutableState<number>;
    NamespaceComponent2Link2?: number;
    __backing_NamespaceComponent2Link3?: MutableState<boolean>;
    NamespaceComponent2Link3?: boolean;
    __backing_NamespaceComponent2Link4?: MutableState<string>;
    NamespaceComponent2Link4?: string;
    myVar?: number;
    myVar2?: number;
}
export interface NamespaceComponent3Options {
    __backing_NamespaceComponent3Link1?: MutableState<any>;
    NamespaceComponent3Link1?: any;
    __backing_NamespaceComponent3Link2?: MutableState<number>;
    NamespaceComponent3Link2?: number;
    __backing_NamespaceComponent3Link3?: MutableState<boolean>;
    NamespaceComponent3Link3?: boolean;
    __backing_NamespaceComponent3Link4?: MutableState<string>;
    NamespaceComponent3Link4?: string;
    myVar?: number;
    myVar2?: number;
}
