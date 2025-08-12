import { ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, FlexAlign, FlexDirection, ItemAlign, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkTapGestureExampleComponent extends ArkStructBase<ArkTapGestureExampleComponent, TapGestureExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TapGestureExampleOptions): void {
        this.__backing_value = stateOf<string>(initializers?.value ?? (''), this);
    }
    private __backing_value?: MutableState<string>;
    private get value(): string {
        return this.__backing_value!.value;
    }
    private set value(value: string) {
        this.__backing_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TapGestureExampleOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(200).width(300).padding(60).border({ width: 1 }).margin(30)
                    .gesture(TapGesture({ count: 2 })
                    .onAction(() => {
                    this.value = 'TapGesture onAction';
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText(undefined, undefined, 'Click twice');
            ArkText(undefined, undefined, this.value);
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function TapGestureExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TapGestureExampleOptions): void {
    const updatedInitializers: TapGestureExampleOptions = {
        __backing_value: initializers?.__backing_value
    };
    ArkTapGestureExampleComponent._instantiate(style, () => new ArkTapGestureExampleComponent, content, updatedInitializers);
}
export interface TapGestureExampleOptions {
    __backing_value?: MutableState<string>;
    value?: string;
}
registerArkuiEntry(TapGestureExample, "tapGesture");
export const __Entry = TapGestureExample;
