import { ArkButton, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
import { tExtend, tStyles, DivideTest, Base, DivideTestOptions } from './test/pages/ImportNestAll';
/** @memo:stable */
class ArkImportTestComponent extends ArkStructBase<ArkImportTestComponent, ImportTestOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ImportTestOptions): void {
        this.__backing_testText1 = stateOf<string>(initializers?.testText1 ?? ('Hello'), this);
        this.__backing_testText2 = stateOf<string>(initializers?.testText2 ?? ('World'), this);
        this.__backing_testText3 = stateOf<string>(initializers?.testText3 ?? ('Test'), this);
        this.__backing_testText4 = stateOf<string>(initializers?.testText4 ?? ('Component'), this);
        this.__backing_testState1 = stateOf<string>(initializers?.testState1 ?? ('Base'), this);
        this.__backing_testState2 = stateOf<number>(initializers?.testState2 ?? (0), this);
        this.__backing_testState3 = stateOf<object>(initializers?.testState3 ?? ({ name: 'Base' }), this);
        this.__backing_testState4 = stateOf<number>(initializers?.testState4 ?? (3), this);
        this.__backing_testState5 = stateOf<number>(initializers?.testState5 ?? (10), this);
    }
    private __backing_testText1?: MutableState<string>;
    private get testText1(): string {
        return this.__backing_testText1!.value;
    }
    private set testText1(value: string) {
        this.__backing_testText1!.value = observableProxy(value);
    }
    private __backing_testText2?: MutableState<string>;
    private get testText2(): string {
        return this.__backing_testText2!.value;
    }
    private set testText2(value: string) {
        this.__backing_testText2!.value = observableProxy(value);
    }
    private __backing_testText3?: MutableState<string>;
    private get testText3(): string {
        return this.__backing_testText3!.value;
    }
    private set testText3(value: string) {
        this.__backing_testText3!.value = observableProxy(value);
    }
    private __backing_testText4?: MutableState<string>;
    private get testText4(): string {
        return this.__backing_testText4!.value;
    }
    private set testText4(value: string) {
        this.__backing_testText4!.value = observableProxy(value);
    }
    private __backing_testState1?: MutableState<string>;
    private get testState1(): string {
        return this.__backing_testState1!.value;
    }
    private set testState1(value: string) {
        this.__backing_testState1!.value = observableProxy(value);
    }
    private __backing_testState2?: MutableState<number>;
    private get testState2(): number {
        return this.__backing_testState2!.value;
    }
    private set testState2(value: number) {
        this.__backing_testState2!.value = observableProxy(value);
    }
    private __backing_testState3?: MutableState<object>;
    private get testState3(): object {
        return this.__backing_testState3!.value;
    }
    private set testState3(value: object) {
        this.__backing_testState3!.value = observableProxy(value);
    }
    private __backing_testState4?: MutableState<number>;
    private get testState4(): number {
        return this.__backing_testState4!.value;
    }
    private set testState4(value: number) {
        this.__backing_testState4!.value = observableProxy(value);
    }
    private __backing_testState5?: MutableState<number>;
    private get testState5(): number {
        return this.__backing_testState5!.value;
    }
    private set testState5(value: number) {
        this.__backing_testState5!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ImportTestOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, this.testText1);
            tExtend(20);
            ArkText(undefined, undefined, this.testText2);
            tStyles();
            ArkButton(undefined, undefined, this.testText3);
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, this.testText4);
            Base({
                __backing_testStr: this.__backing_testState1,
                __backing_testNum: this.__backing_testState2,
                __backing_testObj: this.__backing_testState3
            });
            DivideTest(undefined, undefined, {
                __backing_testNum1: this.__backing_testState4,
                __backing_testNum2: this.__backing_testState5
            } as DivideTestOptions);
        });
    }
}
export {};
/** @memo */
export function ImportTest(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ImportTestOptions): void {
    const updatedInitializers: ImportTestOptions = {
        __backing_testText1: initializers?.__backing_testText1,
        __backing_testText2: initializers?.__backing_testText2,
        __backing_testText3: initializers?.__backing_testText3,
        __backing_testText4: initializers?.__backing_testText4,
        __backing_testState1: initializers?.__backing_testState1,
        __backing_testState2: initializers?.__backing_testState2,
        __backing_testState3: initializers?.__backing_testState3,
        __backing_testState4: initializers?.__backing_testState4,
        __backing_testState5: initializers?.__backing_testState5
    };
    ArkImportTestComponent._instantiate(style, () => new ArkImportTestComponent, content, updatedInitializers);
}
export interface ImportTestOptions {
    __backing_testText1?: MutableState<string>;
    testText1?: string;
    __backing_testText2?: MutableState<string>;
    testText2?: string;
    __backing_testText3?: MutableState<string>;
    testText3?: string;
    __backing_testText4?: MutableState<string>;
    testText4?: string;
    __backing_testState1?: MutableState<string>;
    testState1?: string;
    __backing_testState2?: MutableState<number>;
    testState2?: number;
    __backing_testState3?: MutableState<object>;
    testState3?: object;
    __backing_testState4?: MutableState<number>;
    testState4?: number;
    __backing_testState5?: MutableState<number>;
    testState5?: number;
}
