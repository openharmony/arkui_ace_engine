import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkLinkComponentComponent extends ArkStructBase<ArkLinkComponentComponent, LinkComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkComponentOptions): void {
        this.__backing_counter = initializers!.__backing_counter!;
    }
    private __backing_counter?: MutableState<string>;
    private get counter(): string {
        return this.__backing_counter!.value;
    }
    private set counter(value: string) {
        this.__backing_counter!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkComponentOptions) {
        ArkText(__builder, undefined, this.counter);
    }
}
/** @memo:stable */
class ArkParentComponentComponent extends ArkStructBase<ArkParentComponentComponent, ParentComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentComponentOptions): void {
        this.__backing_value = stateOf<string>(initializers?.value ?? ('first init content'), this);
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
    content?: () => void, initializers?: ParentComponentOptions) {
        ArkColumn(__builder, () => {
            LinkComponent(undefined, undefined, { __backing_counter: this.__backing_value } as LinkComponentOptions);
        });
    }
}
export {};
/** @memo */
export function LinkComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkComponentOptions): void {
    const updatedInitializers: LinkComponentOptions = {
        __backing_counter: initializers?.__backing_counter
    };
    ArkLinkComponentComponent._instantiate(style, () => new ArkLinkComponentComponent, content, updatedInitializers);
}
/** @memo */
export function ParentComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentComponentOptions): void {
    const updatedInitializers: ParentComponentOptions = {
        __backing_value: initializers?.__backing_value
    };
    ArkParentComponentComponent._instantiate(style, () => new ArkParentComponentComponent, content, updatedInitializers);
}
export interface LinkComponentOptions {
    __backing_counter?: MutableState<string>;
    counter?: string;
}
export interface ParentComponentOptions {
    __backing_value?: MutableState<string>;
    value?: string;
}
registerArkuiEntry(ParentComponent, "@link");
export const __Entry = ParentComponent;
