import { ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkDivider, ArkDividerComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, ColumnOptions, ForEach, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkMyComponentComponent extends ArkStructBase<ArkMyComponentComponent, MyComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions): void {
        this.__backing_arr = stateOf<number[]>(initializers?.arr ?? ([10, 20, 30]), this);
    }
    private __backing_arr?: MutableState<number[]>;
    private get arr(): number[] {
        return this.__backing_arr!.value;
    }
    private set arr(value: number[]) {
        this.__backing_arr!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions) {
        ArkColumn(__instance => {
            {
                __instance.width("100%").height("100%");
            }
            __builder?.(__instance);
        }, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.arr.reverse();
                });
            }, undefined, 'Reverse Array');
            ForEach(this.arr, ((item: number) => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.fontSize(18);
                }, undefined, 'item');
                ArkDivider((__instance: ArkDividerComponent) => {
                    __instance.strokeWidth(2);
                }, undefined);
            }), (item: number) => item.toString());
        }, { space: 5 } as ColumnOptions);
    }
}
export {};
/** @memo */
export function MyComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: MyComponentOptions): void {
    const updatedInitializers: MyComponentOptions = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkMyComponentComponent._instantiate(style, () => new ArkMyComponentComponent, content, updatedInitializers);
}
export interface MyComponentOptions {
    __backing_arr?: MutableState<number[]>;
    arr?: number[];
}
