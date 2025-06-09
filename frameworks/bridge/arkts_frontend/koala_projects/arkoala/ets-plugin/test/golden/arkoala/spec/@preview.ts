import { ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkHomePreviewComponentComponent extends ArkStructBase<ArkHomePreviewComponentComponent, HomePreviewComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomePreviewComponentOptions): void {
        this.__backing_value = initializers?.value ?? ("hello world");
    }
    private __backing_value?: string;
    private get value(): string {
        return this.__backing_value as string;
    }
    private set value(value: string) {
        this.__backing_value = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomePreviewComponentOptions) {
        ArkText(__instance => {
            {
                __instance.fontSize(50);
            }
            __builder?.(__instance);
        }, undefined, this.value);
    }
}
/** @memo:stable */
class ArkHomePreviewComponent_PreviewComponent extends ArkStructBase<ArkHomePreviewComponent_PreviewComponent, HomePreviewComponent_PreviewOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomePreviewComponent_PreviewOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomePreviewComponent_PreviewOptions) {
        ArkColumn(__builder, () => {
            HomePreviewComponent(undefined, undefined);
        });
    }
}
export {};
/** @memo */
export function HomePreviewComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: HomePreviewComponentOptions): void {
    const updatedInitializers: HomePreviewComponentOptions = {
        value: initializers?.value
    };
    ArkHomePreviewComponentComponent._instantiate(style, () => new ArkHomePreviewComponentComponent, content, updatedInitializers);
}
/** @memo */
export function HomePreviewComponent_Preview(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: HomePreviewComponent_PreviewOptions): void {
    const updatedInitializers: HomePreviewComponent_PreviewOptions = {};
    ArkHomePreviewComponent_PreviewComponent._instantiate(style, () => new ArkHomePreviewComponent_PreviewComponent, content, updatedInitializers);
}
export interface HomePreviewComponentOptions {
    value?: string;
}
registerArkuiEntry(HomePreviewComponent, "@preview");
export const __Entry = HomePreviewComponent;
export interface HomePreviewComponent_PreviewOptions {
}
