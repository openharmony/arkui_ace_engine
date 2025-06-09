import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, LocalStorage, MutableState, SyncedProperty, observableProxy, propState, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
interface optionsType {
    message: string;
}
let options: optionsType = { message: 'Hi' };
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_message1 = stateOf<string>(initializers?.message1 ?? ('hello'), this);
        this.__backing_message2 = initializers?.message2 ?? ('Hi');
    }
    private __backing_message1?: MutableState<string>;
    private get message1(): string {
        return this.__backing_message1!.value;
    }
    private set message1(value: string) {
        this.__backing_message1!.value = observableProxy(value);
    }
    private __backing_message2?: string;
    private get message2(): string {
        return this.__backing_message2 as string;
    }
    private set message2(value: string) {
        this.__backing_message2 = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkRow(__builder, () => {
            Child(undefined, undefined, { options, message1: this.message1, message2: this.message2 } as ChildOptions);
            Child2(undefined, undefined, options as Child2Options);
        });
    }
}
/** @memo:stable */
class ArkChildComponent extends ArkStructBase<ArkChildComponent, ChildOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions): void {
        if (initializers?.options) {
            this.__backing_options = initializers?.options;
        }
        this.__backing_message1 = initializers!.__backing_message1!;
        this.__backing_message2 = propState<string>();
    }
    private __backing_options?: optionsType;
    private get options(): optionsType {
        return this.__backing_options as optionsType;
    }
    private set options(value: optionsType) {
        this.__backing_options = value;
    }
    private __backing_message1?: MutableState<string>;
    private get message1(): string {
        return this.__backing_message1!.value;
    }
    private set message1(value: string) {
        this.__backing_message1!.value = observableProxy(value);
    }
    private __backing_message2?: SyncedProperty<string>;
    private get message2(): string {
        return this.__backing_message2!.value;
    }
    private set message2(value: string) {
        this.__backing_message2!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ChildOptions | undefined): void {
        this.__backing_message2?.update(initializers?.message2);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, this.message1);
        });
    }
}
/** @memo:stable */
class ArkChild2Component extends ArkStructBase<ArkChild2Component, Child2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: Child2Options): void {
        if (initializers?.message) {
            this.__backing_message = initializers?.message;
        }
    }
    private __backing_message?: string;
    private get message(): string {
        return this.__backing_message as string;
    }
    private set message(value: string) {
        this.__backing_message = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: Child2Options) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, this.message);
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
        __backing_message1: initializers?.__backing_message1,
        message2: initializers?.message2
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
/** @memo */
export function Child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ChildOptions): void {
    const updatedInitializers: ChildOptions = {
        options: initializers?.options,
        __backing_message1: initializers?.__backing_message1,
        message2: initializers?.message2,
        __backing_message2: initializers?.__backing_message2
    };
    ArkChildComponent._instantiate(style, () => new ArkChildComponent, content, updatedInitializers);
}
/** @memo */
export function Child2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: Child2Options): void {
    const updatedInitializers: Child2Options = {
        message: initializers?.message
    };
    ArkChild2Component._instantiate(style, () => new ArkChild2Component, content, updatedInitializers);
}
export interface IndexOptions {
    __backing_message1?: MutableState<string>;
    message1?: string;
    message2?: string;
}
registerArkuiEntry(Index, "component_object");
export const __Entry = Index;
export interface ChildOptions {
    options?: optionsType;
    __backing_message1?: MutableState<string>;
    message1?: string;
    __backing_message2?: SyncedProperty<string>;
    message2?: string;
}
export interface Child2Options {
    message?: string;
}
