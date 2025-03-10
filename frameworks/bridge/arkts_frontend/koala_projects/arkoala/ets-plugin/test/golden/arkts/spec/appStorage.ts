import { AppStorage, AppStorageLinkState, ArkButton, ArkButtonComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, RowOptions, SyncedProperty, propState } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
let varA = AppStorage.Link('varA');
let envLang = AppStorage.Prop('languageCode');
/** @memo:stable */
class ArkMyComponentComponent extends ArkStructBase<ArkMyComponentComponent, MyComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions): void {
        this.__backing_varA = AppStorageLinkState<number>('varA', 2);
        this.__backing_lang = propState<string>(AppStorageLinkState<string>('languageCode', 'en').value);
        this.__backing_label = initializers?.label ?? ('count');
    }
    private __backing_varA?: MutableState<number>;
    private get varA(): number {
        return this.__backing_varA!.value;
    }
    private set varA(value: number) {
        this.__backing_varA!.value = observableProxy(value);
    }
    private __backing_lang?: SyncedProperty<string>;
    private get lang(): string {
        return this.__backing_lang!.value;
    }
    private set lang(value: string) {
        this.__backing_lang!.value = observableProxy(value);
    }
    private __backing_label?: string;
    private get label(): string {
        return this.__backing_label as string;
    }
    private set label(value: string) {
        this.__backing_label = value;
    }
    /** @memo */
    __updateStruct(initializers: MyComponentOptions | undefined): void {
        this.__backing_lang?.update(AppStorageLinkState<string>('languageCode', 'en').value);
    }
    aboutToAppear() {
        this.label = (this.lang === 'zh') ? '数' : 'Count';
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions) {
        ArkRow(__builder, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    AppStorage.Set<number>('varA', AppStorage.Get<number>('varA') + 1);
                });
            }, undefined, this.label + ': ' + this.varA);
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    if (this.lang === 'zh') {
                        AppStorage.Set<string>('languageCode', 'en');
                    }
                    else {
                        AppStorage.Set<string>('languageCode', 'zh');
                    }
                    this.label = (this.lang === 'zh') ? '数' : 'Count';
                });
            }, undefined, 'lang: ' + this.lang);
        }, { space: 20 } as RowOptions);
    }
}
export {};
/** @memo */
export function MyComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: MyComponentOptions): void {
    const updatedInitializers: MyComponentOptions = {
        __backing_varA: initializers?.__backing_varA,
        __backing_lang: initializers?.__backing_lang,
        label: initializers?.label
    };
    ArkMyComponentComponent._instantiate(style, () => new ArkMyComponentComponent, content, updatedInitializers);
}
export interface MyComponentOptions {
    __backing_varA?: MutableState<number>;
    varA?: number;
    __backing_lang?: SyncedProperty<string>;
    lang?: string;
    label?: string;
}
