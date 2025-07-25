import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, ArkTextComponent, ForEach, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo */
function ComB(param: string[]) {
    ForEach(param, item => {
        ComA((__instance: ArkCommonMethodComponent) => {
            __instance.backgroundColor('red');
        }, undefined);
    });
}
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3', '4', '5']), this);
    }
    private __backing_arr?: MutableState<string[]>;
    private get arr(): string[] {
        return this.__backing_arr!.value;
    }
    private set arr(value: string[]) {
        this.__backing_arr!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkColumn(__builder, () => {
            ComB(this.arr);
        });
    }
}
/** @memo:stable */
class ArkComAComponent extends ArkStructBase<ArkComAComponent, ComAOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ComAOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ComAOptions) {
        ArkRow(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(30);
            }, undefined, '自定义组件');
        });
    }
}
export {};
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const updatedInitializers: IndexOptions = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
/** @memo */
export function ComA(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ComAOptions): void {
    const updatedInitializers: ComAOptions = {};
    ArkComAComponent._instantiate(style, () => new ArkComAComponent, content, updatedInitializers);
}
export interface IndexOptions {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
export interface ComAOptions {
}
