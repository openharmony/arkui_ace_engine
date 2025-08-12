import { ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText } from "@koalaui/arkts-arkui";
import { LocalStorage } from "@koalaui/arkui-common";
/** @memo */
function myBuilder() {
    child(undefined, undefined);
}
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
    }
    /** @memo */
    Builder1() {
        child(undefined, undefined);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkRow(__builder, () => {
            myBuilder();
            this.Builder1();
            child(undefined, undefined);
        });
    }
}
/** @memo:stable */
class ArkchildComponent extends ArkStructBase<ArkchildComponent, childOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: childOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: childOptions) {
        ArkText(__builder, undefined, 'Hello');
    }
}
export {};
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const updatedInitializers: IndexOptions = {};
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
/** @memo */
export function child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: childOptions): void {
    const updatedInitializers: childOptions = {};
    ArkchildComponent._instantiate(style, () => new ArkchildComponent, content, updatedInitializers);
}
export interface IndexOptions {
}
export interface childOptions {
}
