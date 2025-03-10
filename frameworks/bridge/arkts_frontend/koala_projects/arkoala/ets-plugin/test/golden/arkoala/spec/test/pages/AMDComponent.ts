import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage, MutableState, observableProxy } from "@koalaui/arkoala-arkui";
/** @memo:stable */
class ArkAMDComponentComponent extends ArkStructBase<ArkAMDComponentComponent, AMDComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: AMDComponentOptions): void {
        this.__backing_AMDComponentLink1 = initializers!.__backing_AMDComponentLink1!;
        this.__backing_AMDComponentLink2 = initializers!.__backing_AMDComponentLink2!;
        this.__backing_AMDComponentLink3 = initializers!.__backing_AMDComponentLink3!;
        this.__backing_AMDComponentLink4 = initializers!.__backing_AMDComponentLink4!;
        this.__backing_myVar = initializers?.myVar ?? (0);
        if (initializers?.myVar2) {
            this.__backing_myVar2 = initializers?.myVar2;
        }
    }
    private __backing_AMDComponentLink1?: MutableState<any>;
    private get AMDComponentLink1(): any {
        return this.__backing_AMDComponentLink1!.value;
    }
    private set AMDComponentLink1(value: any) {
        this.__backing_AMDComponentLink1!.value = observableProxy(value);
    }
    private __backing_AMDComponentLink2?: MutableState<number>;
    private get AMDComponentLink2(): number {
        return this.__backing_AMDComponentLink2!.value;
    }
    private set AMDComponentLink2(value: number) {
        this.__backing_AMDComponentLink2!.value = observableProxy(value);
    }
    private __backing_AMDComponentLink3?: MutableState<boolean>;
    private get AMDComponentLink3(): boolean {
        return this.__backing_AMDComponentLink3!.value;
    }
    private set AMDComponentLink3(value: boolean) {
        this.__backing_AMDComponentLink3!.value = observableProxy(value);
    }
    private __backing_AMDComponentLink4?: MutableState<string>;
    private get AMDComponentLink4(): string {
        return this.__backing_AMDComponentLink4!.value;
    }
    private set AMDComponentLink4(value: string) {
        this.__backing_AMDComponentLink4!.value = observableProxy(value);
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
    content?: () => void, initializers?: AMDComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'AMDComponent');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'AMDComponentLink1: ' + JSON.stringify(this.AMDComponentLink1));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'AMDComponentLink2: ' + JSON.stringify(this.AMDComponentLink2));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'AMDComponentLink3: ' + JSON.stringify(this.AMDComponentLink3));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'AMDComponentLink4: ' + JSON.stringify(this.AMDComponentLink4));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar: ' + JSON.stringify(this.myVar));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'myVar2: ' + JSON.stringify(this.myVar2));
        });
    }
}
export = AMDComponent;
export {};
/** @memo */
export function AMDComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: AMDComponentOptions): void {
    const updatedInitializers: AMDComponentOptions = {
        __backing_AMDComponentLink1: initializers?.__backing_AMDComponentLink1,
        __backing_AMDComponentLink2: initializers?.__backing_AMDComponentLink2,
        __backing_AMDComponentLink3: initializers?.__backing_AMDComponentLink3,
        __backing_AMDComponentLink4: initializers?.__backing_AMDComponentLink4,
        myVar: initializers?.myVar,
        myVar2: initializers?.myVar2
    };
    ArkAMDComponentComponent._instantiate(style, () => new ArkAMDComponentComponent, content, updatedInitializers);
}
export interface AMDComponentOptions {
    __backing_AMDComponentLink1?: MutableState<any>;
    AMDComponentLink1?: any;
    __backing_AMDComponentLink2?: MutableState<number>;
    AMDComponentLink2?: number;
    __backing_AMDComponentLink3?: MutableState<boolean>;
    AMDComponentLink3?: boolean;
    __backing_AMDComponentLink4?: MutableState<string>;
    AMDComponentLink4?: string;
    myVar?: number;
    myVar2?: number;
}
