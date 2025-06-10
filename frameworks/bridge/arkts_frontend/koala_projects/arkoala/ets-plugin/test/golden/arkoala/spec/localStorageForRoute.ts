import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, LocalStorage } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
let route = 'pages/Index';
/** @memo:stable */
class ArkLocalStorageComponentComponent extends ArkStructBase<ArkLocalStorageComponentComponent, LocalStorageComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageComponentOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageComponentOptions) {
        ArkColumn(__instance => {
            {
                __instance.height(500);
            }
            __builder?.(__instance);
        }, undefined);
    }
}
export {};
/** @memo */
export function LocalStorageComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageComponentOptions): void {
    const updatedInitializers: LocalStorageComponentOptions = {};
    ArkLocalStorageComponentComponent._instantiate(style, () => new ArkLocalStorageComponentComponent, content, updatedInitializers);
}
export interface LocalStorageComponentOptions {
}
registerArkuiEntry(LocalStorageComponent, "localStorageForRoute");
export const __Entry = LocalStorageComponent;
