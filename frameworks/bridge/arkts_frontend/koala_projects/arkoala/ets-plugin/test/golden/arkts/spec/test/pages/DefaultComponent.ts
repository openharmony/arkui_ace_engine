import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkDefaultComponentComponent extends ArkStructBase<ArkDefaultComponentComponent, DefaultComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: DefaultComponentOptions): void {
        this.__backing_DefaultComponentLink1 = initializers!.__backing_DefaultComponentLink1!;
        this.__backing_DefaultComponentLink2 = initializers!.__backing_DefaultComponentLink2!;
        this.__backing_DefaultComponentLink3 = initializers!.__backing_DefaultComponentLink3!;
        this.__backing_DefaultComponentLink4 = initializers!.__backing_DefaultComponentLink4!;
        this.__backing_myVar = initializers?.myVar ?? (0);
        if (initializers?.myVar2) {
            this.__backing_myVar2 = initializers?.myVar2;
        }
    }
    private __backing_DefaultComponentLink1?: MutableState<any>;
    private get DefaultComponentLink1(): any {
        return this.__backing_DefaultComponentLink1!.value;
    }
    private set DefaultComponentLink1(value: any) {
        this.__backing_DefaultComponentLink1!.value = observableProxy(value);
    }
    private __backing_DefaultComponentLink2?: MutableState<number>;
    private get DefaultComponentLink2(): number {
        return this.__backing_DefaultComponentLink2!.value;
    }
    private set DefaultComponentLink2(value: number) {
        this.__backing_DefaultComponentLink2!.value = observableProxy(value);
    }
    private __backing_DefaultComponentLink3?: MutableState<boolean>;
    private get DefaultComponentLink3(): boolean {
        return this.__backing_DefaultComponentLink3!.value;
    }
    private set DefaultComponentLink3(value: boolean) {
        this.__backing_DefaultComponentLink3!.value = observableProxy(value);
    }
    private __backing_DefaultComponentLink4?: MutableState<string>;
    private get DefaultComponentLink4(): string {
        return this.__backing_DefaultComponentLink4!.value;
    }
    private set DefaultComponentLink4(value: string) {
        this.__backing_DefaultComponentLink4!.value = observableProxy(value);
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
    content?: () => void, initializers?: DefaultComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DefaultComponent');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DefaultComponentLink1: ' + JSON.stringify(this.DefaultComponentLink1));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DefaultComponentLink2: ' + JSON.stringify(this.DefaultComponentLink2));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DefaultComponentLink3: ' + JSON.stringify(this.DefaultComponentLink3));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DefaultComponentLink4: ' + JSON.stringify(this.DefaultComponentLink4));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar: ' + JSON.stringify(this.myVar));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar2: ' + JSON.stringify(this.myVar2));
        });
    }
}
export default DefaultComponent;
export {};
/** @memo */
export function DefaultComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: DefaultComponentOptions): void {
    const updatedInitializers: DefaultComponentOptions = {
        __backing_DefaultComponentLink1: initializers?.__backing_DefaultComponentLink1,
        __backing_DefaultComponentLink2: initializers?.__backing_DefaultComponentLink2,
        __backing_DefaultComponentLink3: initializers?.__backing_DefaultComponentLink3,
        __backing_DefaultComponentLink4: initializers?.__backing_DefaultComponentLink4,
        myVar: initializers?.myVar,
        myVar2: initializers?.myVar2
    };
    ArkDefaultComponentComponent._instantiate(style, () => new ArkDefaultComponentComponent, content, updatedInitializers);
}
export interface DefaultComponentOptions {
    __backing_DefaultComponentLink1?: MutableState<any>;
    DefaultComponentLink1?: any;
    __backing_DefaultComponentLink2?: MutableState<number>;
    DefaultComponentLink2?: number;
    __backing_DefaultComponentLink3?: MutableState<boolean>;
    DefaultComponentLink3?: boolean;
    __backing_DefaultComponentLink4?: MutableState<string>;
    DefaultComponentLink4?: string;
    myVar?: number;
    myVar2?: number;
}
