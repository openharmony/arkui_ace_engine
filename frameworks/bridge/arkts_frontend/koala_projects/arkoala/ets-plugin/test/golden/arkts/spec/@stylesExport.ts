import { ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkCommonMethodInterface, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, Color, ColumnOptions, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo */
function globalFancy<T extends ArkCommonMethodInterface<T>>(CommonInstance: T): T {
    return CommonInstance.backgroundColor(Color.Red);
}
/** @memo:stable */
export class ArkFancyUseExpComponent extends ArkStructBase<ArkFancyUseExpComponent, FancyUseExpOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: FancyUseExpOptions): void {
        this.__backing_enable = stateOf<boolean>(initializers?.enable ?? (true), this);
    }
    private __backing_enable?: MutableState<boolean>;
    private get enable(): boolean {
        return this.__backing_enable!.value;
    }
    private set enable(value: boolean) {
        this.__backing_enable!.value = observableProxy(value);
    }
    /** @memo */
    componentFancy<T extends ArkCommonMethodInterface<T>>(CommonInstance: T): T {
        return CommonInstance.backgroundColor(Color.Blue);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: FancyUseExpOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.__applyStyle(globalFancy)
                    .width(100)
                    .height(100);
            }, undefined, "Fancy");
            ArkText((__instance: ArkTextComponent) => {
                __instance.__applyStyle(this.componentFancy.bind(this))
                    .width(100)
                    .height(100);
            }, undefined, "Fancy");
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.enabled(this.enable)
                    .onClick(() => {
                    this.enable = false;
                })
                    .stateStyles({
                    normal: {
                        ButtonInstance: ButtonInstance.backgroundColor(Color.Green)
                    },
                    disabled: this.componentFancy,
                    pressed: globalFancy
                });
            }, () => {
                ArkText(undefined, undefined, "Fancy");
            });
        }, { space: 10 } as ColumnOptions);
    }
}
export {};
/** @memo */
export function FancyUseExp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: FancyUseExpOptions): void {
    const updatedInitializers: FancyUseExpOptions = {
        __backing_enable: initializers?.__backing_enable
    };
    ArkFancyUseExpComponent._instantiate(style, () => new ArkFancyUseExpComponent, content, updatedInitializers);
}
export interface FancyUseExpOptions {
    __backing_enable?: MutableState<boolean>;
    enable?: boolean;
}
