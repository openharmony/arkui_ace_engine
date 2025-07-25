import { $r, $rawfile, AppStorage, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
import { CustomContainerExport, CustomContainerExportOptions } from './test/pages/TestComponent';
/** @memo:stable */
class ArkCustomContainerComponent extends ArkStructBase<ArkCustomContainerComponent, CustomContainerOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerOptions): void {
        this.__backing_header = initializers?.header ?? ("");
        if (initializers?.content) {
            this.__backing_content = initializers?.content;
        }
        if (initializers?.callContent) {
            this.__backing_callContent = initializers?.callContent;
        }
        this.__backing_footer = initializers?.footer ?? ("");
        if (this.__backing_content === undefined && content !== undefined)
            this.__backing_content = content;
    }
    private __backing_header?: string;
    private get header(): string {
        return this.__backing_header as string;
    }
    private set header(value: string) {
        this.__backing_header = value;
    }
    /** @memo */
    private __backing_content?: () => void;
    /** @memo */
    private get content(): () => void {
        return this.__backing_content!;
    }
    private set content(/**/
    /** @memo */
    value: () => void) {
        this.__backing_content = value;
    }
    /** @memo */
    private __backing_callContent?: any;
    /** @memo */
    private get callContent(): any {
        return this.__backing_callContent!;
    }
    private set callContent(/**/
    /** @memo */
    value: any) {
        this.__backing_callContent = value;
    }
    private __backing_footer?: string;
    private get footer(): string {
        return this.__backing_footer as string;
    }
    private set footer(value: string) {
        this.__backing_footer = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerOptions) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, this.header);
            this.content();
            this.callContent();
            ArkText(undefined, undefined, this.footer);
        });
    }
}
/** @memo:stable */
class ArkCustomContainer2Component extends ArkStructBase<ArkCustomContainer2Component, CustomContainer2Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomContainer2Options): void {
        this.__backing_header = initializers?.header ?? ("");
        if (initializers?.content) {
            this.__backing_content = initializers?.content;
        }
        if (this.__backing_content === undefined && content !== undefined)
            this.__backing_content = content;
    }
    private __backing_header?: string;
    private get header(): string {
        return this.__backing_header as string;
    }
    private set header(value: string) {
        this.__backing_header = value;
    }
    /** @memo */
    private __backing_content?: () => void;
    /** @memo */
    private get content(): () => void {
        return this.__backing_content!;
    }
    private set content(/**/
    /** @memo */
    value: () => void) {
        this.__backing_content = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomContainer2Options) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, this.header);
            this.content();
        });
    }
}
/** @memo */
function specificWithParam(label1: string, label2: string) {
    ArkColumn(undefined, () => {
        ArkText((__instance: ArkTextComponent) => {
            __instance.fontSize(50);
        }, undefined, label1);
        ArkText((__instance: ArkTextComponent) => {
            __instance.fontSize(50);
        }, undefined, label2);
    });
}
/** @memo:stable */
class ArkCustomContainerUserComponent extends ArkStructBase<ArkCustomContainerUserComponent, CustomContainerUserOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerUserOptions): void {
        this.__backing_text = stateOf<string>(initializers?.text ?? ('header'), this);
    }
    private __backing_text?: MutableState<string>;
    private get text(): string {
        return this.__backing_text!.value;
    }
    private set text(value: string) {
        this.__backing_text!.value = observableProxy(value);
    }
    /** @memo */
    specificParam() {
        ArkColumn(undefined, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, "content");
        });
    }
    /** @memo */
    callSpecificParam(label1: string, label2: string) {
        ArkColumn(undefined, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, label1);
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, label2);
        });
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomContainerUserOptions) {
        ArkColumn(__builder, () => {
            CustomContainerExport(undefined, () => {
                ArkColumn((__instance: ArkColumnComponent) => {
                    __instance.onClick(() => {
                        this.text = "changeHeader";
                    });
                }, () => {
                    specificWithParam("111", "22");
                });
            }, {
                header: this.text,
            });
            ArkRow(undefined, () => {
                CustomContainer(undefined, undefined, {
                    header: this.text,
                    content: this.specificParam,
                    callContent: /* */
                    /** @memo */
                    (): void => this.callSpecificParam("callContent1", 'callContent2'),
                    footer: "Footer",
                } as CustomContainerOptions);
            });
            ArkRow(undefined, () => {
                CustomContainer2(undefined, () => {
                    ArkColumn((__instance: ArkColumnComponent) => {
                        __instance.onClick(() => {
                            this.text = "changeHeader";
                        });
                    }, () => {
                        this.callSpecificParam("111", '222');
                    });
                }, {
                    header: this.text,
                });
            });
        });
    }
}
export {};
/** @memo */
export function CustomContainer(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomContainerOptions): void {
    const updatedInitializers: CustomContainerOptions = {
        header: initializers?.header,
        content: initializers?.content,
        callContent: initializers?.callContent,
        footer: initializers?.footer
    };
    ArkCustomContainerComponent._instantiate(style, () => new ArkCustomContainerComponent, content, updatedInitializers);
}
/** @memo */
export function CustomContainer2(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomContainer2Options): void {
    const updatedInitializers: CustomContainer2Options = {
        header: initializers?.header,
        content: initializers?.content
    };
    ArkCustomContainer2Component._instantiate(style, () => new ArkCustomContainer2Component, content, updatedInitializers);
}
/** @memo */
export function CustomContainerUser(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomContainerUserOptions): void {
    const updatedInitializers: CustomContainerUserOptions = {
        __backing_text: initializers?.__backing_text
    };
    ArkCustomContainerUserComponent._instantiate(style, () => new ArkCustomContainerUserComponent, content, updatedInitializers);
}
export interface CustomContainerOptions {
    header?: string;
    /** @memo */
    content?: () => void;
    /** @memo */
    callContent?: any;
    footer?: string;
}
export interface CustomContainer2Options {
    header?: string;
    /** @memo */
    content?: () => void;
}
export interface CustomContainerUserOptions {
    __backing_text?: MutableState<string>;
    text?: string;
}
registerArkuiEntry(CustomContainerUser, "@builderParam");
export const __Entry = CustomContainerUser;
