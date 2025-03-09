import { ArkCommonMethodComponent, ArkList, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ForEach, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkParentViewComponent extends ArkStructBase<ArkParentViewComponent, ParentViewOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentViewOptions): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentViewOptions) {
        ArkList(__builder, () => {
            ForEach(this.arr, item => {
                ArkText(undefined, undefined, item);
            });
        });
    }
}
/** @memo:stable */
class ArkParentView1Component extends ArkStructBase<ArkParentView1Component, ParentView1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentView1Options): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentView1Options) {
        ArkList(__builder, () => {
            ForEach(this.arr, (item, index) => {
                ArkText(undefined, undefined, item);
            });
        });
    }
}
/** @memo:stable */
class ArkParentView2Component extends ArkStructBase<ArkParentView2Component, ParentView2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentView2Options): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentView2Options) {
        ArkList(__builder, () => {
            ForEach(this.arr, (item, index) => {
                ArkText(undefined, undefined, item);
            }, item => item.toString());
        });
    }
}
/** @memo:stable */
class ArkParentView3Component extends ArkStructBase<ArkParentView3Component, ParentView3Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentView3Options): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentView3Options) {
        ArkList(__builder, () => {
            ForEach(this.arr, (item, index) => {
                ArkText(undefined, undefined, item);
            }, (item, index) => item.toString());
        });
    }
}
/** @memo:stable */
class ArkParentView4Component extends ArkStructBase<ArkParentView4Component, ParentView4Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentView4Options): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentView4Options) {
        ArkList(__builder, () => {
            ForEach(this.arr, item => {
                ArkText(undefined, undefined, item);
            }, (item, index) => item.toString());
        });
    }
}
/** @memo:stable */
class ArkParentView5Component extends ArkStructBase<ArkParentView5Component, ParentView5Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentView5Options): void {
        this.__backing_arr = stateOf<string[]>(initializers?.arr ?? (['1', '2', '3']), this);
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
    content?: () => void, initializers?: ParentView5Options) {
        ArkList(__builder, () => {
            ForEach(this.arr, item => {
                ArkText(undefined, undefined, item);
            }, item => item.toString());
        });
    }
}
export {};
/** @memo */
export function ParentView(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentViewOptions): void {
    const updatedInitializers: ParentViewOptions = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentViewComponent._instantiate(style, () => new ArkParentViewComponent, content, updatedInitializers);
}
/** @memo */
export function ParentView1(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentView1Options): void {
    const updatedInitializers: ParentView1Options = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentView1Component._instantiate(style, () => new ArkParentView1Component, content, updatedInitializers);
}
/** @memo */
export function ParentView2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentView2Options): void {
    const updatedInitializers: ParentView2Options = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentView2Component._instantiate(style, () => new ArkParentView2Component, content, updatedInitializers);
}
/** @memo */
export function ParentView3(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentView3Options): void {
    const updatedInitializers: ParentView3Options = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentView3Component._instantiate(style, () => new ArkParentView3Component, content, updatedInitializers);
}
/** @memo */
export function ParentView4(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentView4Options): void {
    const updatedInitializers: ParentView4Options = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentView4Component._instantiate(style, () => new ArkParentView4Component, content, updatedInitializers);
}
/** @memo */
export function ParentView5(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentView5Options): void {
    const updatedInitializers: ParentView5Options = {
        __backing_arr: initializers?.__backing_arr
    };
    ArkParentView5Component._instantiate(style, () => new ArkParentView5Component, content, updatedInitializers);
}
export interface ParentViewOptions {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
registerArkuiEntry(ParentView, "foreach");
export const __Entry = ParentView;
export interface ParentView1Options {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
export interface ParentView2Options {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
export interface ParentView3Options {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
export interface ParentView4Options {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
export interface ParentView5Options {
    __backing_arr?: MutableState<string[]>;
    arr?: string[];
}
