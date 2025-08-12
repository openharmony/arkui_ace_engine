import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, Color, LocalStorage, MutableState, observableProxy } from "@koalaui/arkoala-arkui";
/** @memo */
function textStyles() {
    ArkText((__instance: ArkTextComponent) => {
        __instance.backgroundColor(Color.Red);
    }, undefined, 'Builder');
}
/** @memo:stable */
class ArkDivideComponentComponent extends ArkStructBase<ArkDivideComponentComponent, DivideComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: DivideComponentOptions): void {
        this.__backing_testNum1 = initializers!.__backing_testNum1!;
        this.__backing_testNum2 = initializers!.__backing_testNum2!;
    }
    private __backing_testNum1?: MutableState<number>;
    private get testNum1(): number {
        return this.__backing_testNum1!.value;
    }
    private set testNum1(value: number) {
        this.__backing_testNum1!.value = observableProxy(value);
    }
    private __backing_testNum2?: MutableState<number>;
    private get testNum2(): number {
        return this.__backing_testNum2!.value;
    }
    private set testNum2(value: number) {
        this.__backing_testNum2!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: DivideComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DivideComponent');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'DivideResult: ' + JSON.stringify(this.testNum1 / this.testNum2));
        });
    }
}
export { textStyles, DivideComponent };
export {};
/** @memo */
export function DivideComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: DivideComponentOptions): void {
    const updatedInitializers: DivideComponentOptions = {
        __backing_testNum1: initializers?.__backing_testNum1,
        __backing_testNum2: initializers?.__backing_testNum2
    };
    ArkDivideComponentComponent._instantiate(style, () => new ArkDivideComponentComponent, content, updatedInitializers);
}
export interface DivideComponentOptions {
    __backing_testNum1?: MutableState<number>;
    testNum1?: number;
    __backing_testNum2?: MutableState<number>;
    testNum2?: number;
}
