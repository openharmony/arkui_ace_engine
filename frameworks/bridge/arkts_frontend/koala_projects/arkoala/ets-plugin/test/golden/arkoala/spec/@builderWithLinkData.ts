import { ArkCommonMethodComponent, ArkFlex, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkTitleCompComponent extends ArkStructBase<ArkTitleCompComponent, TitleCompOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TitleCompOptions): void {
        this.__backing_title = initializers!.__backing_title!;
    }
    private __backing_title?: MutableState<string>;
    private get title(): string {
        return this.__backing_title!.value;
    }
    private set title(value: string) {
        this.__backing_title!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TitleCompOptions) {
        ArkText(__builder, undefined, this.title);
    }
}
/** @memo:stable */
class ArkTestPageComponent extends ArkStructBase<ArkTestPageComponent, TestPageOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TestPageOptions): void {
        this.__backing_value = stateOf<string>(initializers?.value ?? ('hello world'), this);
    }
    private __backing_value?: MutableState<string>;
    private get value(): string {
        return this.__backing_value!.value;
    }
    private set value(value: string) {
        this.__backing_value!.value = observableProxy(value);
    }
    /** @memo */
    TitleCompView() {
        TitleComp(undefined, undefined, { __backing_title: this.__backing_value } as TitleCompOptions);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TestPageOptions) {
        ArkFlex(__builder, () => {
            this.TitleCompView();
        });
    }
}
export {};
/** @memo */
export function TitleComp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TitleCompOptions): void {
    const updatedInitializers: TitleCompOptions = {
        __backing_title: initializers?.__backing_title
    };
    ArkTitleCompComponent._instantiate(style, () => new ArkTitleCompComponent, content, updatedInitializers);
}
/** @memo */
export function TestPage(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TestPageOptions): void {
    const updatedInitializers: TestPageOptions = {
        __backing_value: initializers?.__backing_value
    };
    ArkTestPageComponent._instantiate(style, () => new ArkTestPageComponent, content, updatedInitializers);
}
export interface TitleCompOptions {
    __backing_title?: MutableState<string>;
    title?: string;
}
export interface TestPageOptions {
    __backing_value?: MutableState<string>;
    value?: string;
}
registerArkuiEntry(TestPage, "@builderWithLinkData");
export const __Entry = TestPage;
