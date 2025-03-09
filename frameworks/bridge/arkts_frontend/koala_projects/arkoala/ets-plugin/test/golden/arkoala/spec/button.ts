import { ArkButton, ArkButtonComponent, ArkCommonMethodComponent, ArkFlex, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, ArkText, ArkTextComponent, ButtonType, FlexAlign, FlexDirection, ItemAlign, LocalStorage, VerticalAlign } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkButtonExampleComponent extends ArkStructBase<ArkButtonExampleComponent, ButtonExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ButtonExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ButtonExampleOptions) {
        ArkFlex(__builder, () => {
            ArkFlex(undefined, () => {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.borderRadius(8).backgroundColor(0x317aff).width(90);
                }, undefined, 'Ok', { type: ButtonType.Normal, stateEffect: true });
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.borderRadius(8).backgroundColor(0x317aff).width(90);
                }, () => {
                    ArkRow((__instance: ArkRowComponent) => {
                        __instance.alignItems(VerticalAlign.Center);
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.fontSize(12).fontColor(0xffffff).margin({ left: 5, right: 12 });
                        }, undefined, 'loading');
                    });
                }, { type: ButtonType.Normal, stateEffect: true });
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.opacity(0.5)
                        .borderRadius(8).backgroundColor(0x317aff).width(90);
                }, undefined, 'Disable', { type: ButtonType.Normal, stateEffect: false });
            }, { alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function ButtonExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ButtonExampleOptions): void {
    const updatedInitializers: ButtonExampleOptions = {};
    ArkButtonExampleComponent._instantiate(style, () => new ArkButtonExampleComponent, content, updatedInitializers);
}
export interface ButtonExampleOptions {
}
registerArkuiEntry(ButtonExample, "button");
export const __Entry = ButtonExample;
