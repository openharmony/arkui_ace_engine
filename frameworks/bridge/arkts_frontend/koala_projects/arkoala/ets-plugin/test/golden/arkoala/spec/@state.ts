import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkStatePageComponent extends ArkStructBase<ArkStatePageComponent, StatePageOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StatePageOptions): void {
        this.__backing_counter = stateOf<number>(initializers?.counter ?? (0), this);
    }
    private __backing_counter?: MutableState<number>;
    private get counter(): number {
        return this.__backing_counter!.value;
    }
    private set counter(value: number) {
        this.__backing_counter!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StatePageOptions) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, "counter:" + this.counter);
        });
    }
}
export {};
/** @memo */
export function StatePage(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StatePageOptions): void {
    const updatedInitializers: StatePageOptions = {
        __backing_counter: initializers?.__backing_counter
    };
    ArkStatePageComponent._instantiate(style, () => new ArkStatePageComponent, content, updatedInitializers);
}
export interface StatePageOptions {
    __backing_counter?: MutableState<number>;
    counter?: number;
}
registerArkuiEntry(StatePage, "@state");
export const __Entry = StatePage;
