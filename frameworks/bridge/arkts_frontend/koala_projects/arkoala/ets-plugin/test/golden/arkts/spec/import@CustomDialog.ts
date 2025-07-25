import { ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, CustomDialogController, DialogAlignment, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
import { CustomDialogExample1 as CustomDialogExample, CustomDialogExampleOptions } from './test/pages/import@CustomDialog';
/** @memo:stable */
class ArkCustomDialogUserComponent extends ArkStructBase<ArkCustomDialogUserComponent, CustomDialogUserOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogUserOptions): void {
        this.__backing_textValue = stateOf<string>(initializers?.textValue ?? (''), this);
        this.__backing_inputValue = stateOf<string>(initializers?.inputValue ?? ('click me'), this);
        this.__backing_dialogController = initializers?.dialogController ?? (new CustomDialogController({
            builder: CustomDialogExample({
                cancel: this.onCancel,
                confirm: this.onAccept,
                __backing_textValue: this.__backing_textValue,
                __backing_inputValue: this.__backing_inputValue
            }),
            cancel: this.existApp,
            autoCancel: true,
            alignment: DialogAlignment.Default,
            offset: { dx: 0, dy: -20 },
            gridCount: 4,
            customStyle: false
        }));
    }
    private __backing_textValue?: MutableState<string>;
    private get textValue(): string {
        return this.__backing_textValue!.value;
    }
    private set textValue(value: string) {
        this.__backing_textValue!.value = observableProxy(value);
    }
    private __backing_inputValue?: MutableState<string>;
    private get inputValue(): string {
        return this.__backing_inputValue!.value;
    }
    private set inputValue(value: string) {
        this.__backing_inputValue!.value = observableProxy(value);
    }
    private __backing_dialogController?: CustomDialogController;
    private get dialogController(): CustomDialogController {
        return this.__backing_dialogController as CustomDialogController;
    }
    private set dialogController(value: CustomDialogController) {
        this.__backing_dialogController = value;
    }
    onCancel() {
        console.info('Callback when the first button is clicked');
    }
    onAccept() {
        console.info('Callback when the second button is clicked');
    }
    existApp() {
        console.info('Click the callback in the blank area');
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogUserOptions) {
        ArkColumn(__instance => {
            {
                __instance.width('100%').margin({ top: 5 });
            }
            __builder?.(__instance);
        }, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.dialogController.open();
                }).backgroundColor(0x317aff);
            }, undefined, this.inputValue);
        });
    }
}
export {};
/** @memo */
export function CustomDialogUser(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomDialogUserOptions): void {
    const updatedInitializers: CustomDialogUserOptions = {
        __backing_textValue: initializers?.__backing_textValue,
        __backing_inputValue: initializers?.__backing_inputValue,
        dialogController: initializers?.dialogController
    };
    ArkCustomDialogUserComponent._instantiate(style, () => new ArkCustomDialogUserComponent, content, updatedInitializers);
}
export interface CustomDialogUserOptions {
    __backing_textValue?: MutableState<string>;
    textValue?: string;
    __backing_inputValue?: MutableState<string>;
    inputValue?: string;
    dialogController?: CustomDialogController;
}
