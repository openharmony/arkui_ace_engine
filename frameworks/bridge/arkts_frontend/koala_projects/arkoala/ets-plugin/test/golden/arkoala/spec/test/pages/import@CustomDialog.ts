import { ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, ArkTextInput, ArkTextInputComponent, Color, CustomDialogController, FlexAlign, LocalStorage, MutableState, bindCustomDialog, observableProxy } from "@koalaui/arkoala-arkui";
/** @memo:stable */
export class ArkCustomDialogExample1Component extends ArkStructBase<ArkCustomDialogExample1Component, CustomDialogExample1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogExample1Options): void {
        this.__backing_textValue = initializers!.__backing_textValue!;
        this.__backing_inputValue = initializers!.__backing_inputValue!;
        if (initializers?.controller) {
            this.__backing_controller = initializers?.controller;
        }
        if (initializers?.cancel) {
            this.__backing_cancel = initializers?.cancel;
        }
        if (initializers?.confirm) {
            this.__backing_confirm = initializers?.confirm;
        }
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
    private __backing_controller?: CustomDialogController;
    private get controller(): CustomDialogController {
        return this.__backing_controller as CustomDialogController;
    }
    private set controller(value: CustomDialogController) {
        this.__backing_controller = value;
    }
    private __backing_cancel?: () => void;
    private get cancel(): () => void {
        return this.__backing_cancel as () => void;
    }
    private set cancel(value: () => void) {
        this.__backing_cancel = value;
    }
    private __backing_confirm?: () => void;
    private get confirm(): () => void {
        return this.__backing_confirm as () => void;
    }
    private set confirm(value: () => void) {
        this.__backing_confirm = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogExample1Options) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20).margin({ top: 10, bottom: 10 });
            }, undefined, 'Change text');
            ArkTextInput((__instance: ArkTextInputComponent) => {
                __instance.height(60).width('90%')
                    .onChange((value: string) => {
                    this.textValue = value;
                });
            }, undefined, { placeholder: '', text: this.textValue });
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(16).margin({ bottom: 10 });
            }, undefined, 'Whether to change a text?');
            ArkFlex((__instance: ArkFlexComponent) => {
                __instance.margin({ bottom: 10 });
            }, () => {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.controller.close();
                        this.cancel();
                    }).backgroundColor(0xffffff).fontColor(Color.Black);
                }, undefined, 'cancel');
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.inputValue = this.textValue;
                        this.controller.close();
                        this.confirm();
                    }).backgroundColor(0xffffff).fontColor(Color.Red);
                }, undefined, 'confirm');
            }, { justifyContent: FlexAlign.SpaceAround });
        });
    }
}
export {};
/** @memo */
export function CustomDialogExample1Impl(initializers?: CustomDialogExample1Options): void {
    const updatedInitializers: CustomDialogExample1Options = {
        __backing_textValue: initializers?.__backing_textValue,
        __backing_inputValue: initializers?.__backing_inputValue,
        controller: initializers?.controller,
        cancel: initializers?.cancel,
        confirm: initializers?.confirm
    };
    ArkCustomDialogExample1Component._instantiate(undefined, () => new ArkCustomDialogExample1Component, undefined, updatedInitializers);
}
export function CustomDialogExample1(initializer: CustomDialogExample1Options = {}) {
    return { build: bindCustomDialog(CustomDialogExample1Impl, initializer), buildOptions: initializer };
}
export interface CustomDialogExample1Options {
    __backing_textValue?: MutableState<string>;
    textValue?: string;
    __backing_inputValue?: MutableState<string>;
    inputValue?: string;
    controller?: CustomDialogController;
    cancel?: () => void;
    confirm?: () => void;
}
