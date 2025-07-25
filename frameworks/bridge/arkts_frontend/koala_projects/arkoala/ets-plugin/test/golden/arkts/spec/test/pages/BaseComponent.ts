import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo */
function textExtend(fontsize: number) {
    ArkText((__instance: ArkTextComponent) => {
        __instance.fontSize(fontsize);
    }, undefined, 'Builder');
}
/** @memo:stable */
class ArkBaseComponentComponent extends ArkStructBase<ArkBaseComponentComponent, BaseComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BaseComponentOptions): void {
        this.__backing_testStr = initializers!.__backing_testStr!;
        this.__backing_testNum = initializers!.__backing_testNum!;
        this.__backing_testObj = initializers!.__backing_testObj!;
    }
    private __backing_testStr?: MutableState<string>;
    private get testStr(): string {
        return this.__backing_testStr!.value;
    }
    private set testStr(value: string) {
        this.__backing_testStr!.value = observableProxy(value);
    }
    private __backing_testNum?: MutableState<number>;
    private get testNum(): number {
        return this.__backing_testNum!.value;
    }
    private set testNum(value: number) {
        this.__backing_testNum!.value = observableProxy(value);
    }
    private __backing_testObj?: MutableState<object>;
    private get testObj(): object {
        return this.__backing_testObj!.value;
    }
    private set testObj(value: object) {
        this.__backing_testObj!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BaseComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'BaseComponent');
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'testStr: ' + JSON.stringify(this.testStr));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'testNum: ' + JSON.stringify(this.testNum));
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'testObj: ' + JSON.stringify(this.testObj));
        });
    }
}
export { textExtend, BaseComponent };
export {};
/** @memo */
export function BaseComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BaseComponentOptions): void {
    const updatedInitializers: BaseComponentOptions = {
        __backing_testStr: initializers?.__backing_testStr,
        __backing_testNum: initializers?.__backing_testNum,
        __backing_testObj: initializers?.__backing_testObj
    };
    ArkBaseComponentComponent._instantiate(style, () => new ArkBaseComponentComponent, content, updatedInitializers);
}
export interface BaseComponentOptions {
    __backing_testStr?: MutableState<string>;
    testStr?: string;
    __backing_testNum?: MutableState<number>;
    testNum?: number;
    __backing_testObj?: MutableState<object>;
    testObj?: object;
}
