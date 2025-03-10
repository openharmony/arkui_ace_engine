import { $r, $rawfile, AppStorage, ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, SyncedProperty, TabsController, TapGesture, TextAreaController, VideoController, animateTo, bindCustomDialog, fp2px, getContext, getInspectorByKey, lpx2px, propState, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo:stable */
class ArkDialogExampleComponent extends ArkStructBase<ArkDialogExampleComponent, DialogExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: DialogExampleOptions): void {
        this.__backing_count = propState<number>();
        this.__backing_isPlaying = initializers!.__backing_isPlaying!;
        if (initializers?.controller) {
            this.__backing_controller = initializers?.controller;
        }
        this.__backing_termsToAccept = initializers?.termsToAccept ?? ("");
        if (initializers?.action1) {
            this.__backing_action1 = initializers?.action1;
        }
        if (initializers?.action2) {
            this.__backing_action2 = initializers?.action2;
        }
    }
    private __backing_count?: SyncedProperty<number>;
    private get count(): number {
        return this.__backing_count!.value;
    }
    private set count(value: number) {
        this.__backing_count!.value = observableProxy(value);
    }
    private __backing_isPlaying?: MutableState<boolean>;
    private get isPlaying(): boolean {
        return this.__backing_isPlaying!.value;
    }
    private set isPlaying(value: boolean) {
        this.__backing_isPlaying!.value = observableProxy(value);
    }
    private __backing_controller?: CustomDialogController;
    private get controller(): CustomDialogController {
        return this.__backing_controller as CustomDialogController;
    }
    private set controller(value: CustomDialogController) {
        this.__backing_controller = value;
    }
    private __backing_termsToAccept?: string;
    private get termsToAccept(): string {
        return this.__backing_termsToAccept as string;
    }
    private set termsToAccept(value: string) {
        this.__backing_termsToAccept = value;
    }
    private __backing_action1?: () => void;
    private get action1(): () => void {
        return this.__backing_action1 as () => void;
    }
    private set action1(value: () => void) {
        this.__backing_action1 = value;
    }
    private __backing_action2?: (x: number, s: string) => void;
    private get action2(): (x: number, s: string) => void {
        return this.__backing_action2 as (x: number, s: string) => void;
    }
    private set action2(value: (x: number, s: string) => void) {
        this.__backing_action2 = value;
    }
    /** @memo */
    __updateStruct(initializers: DialogExampleOptions | undefined): void {
        this.__backing_count?.update(initializers?.count);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: DialogExampleOptions) {
        ArkColumn(__builder, () => {
            ArkRow(undefined, () => {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.count++;
                    });
                }, undefined, 'current count is: ' + this.count);
            });
            ArkRow(undefined, () => {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.isPlaying = !this.isPlaying;
                    });
                }, undefined, this.isPlaying ? 'play' : 'pause');
            });
            ArkRow(undefined, () => {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.controller.close();
                        this.action1();
                    });
                }, undefined, "Option A");
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.onClick(() => {
                        this.controller.close();
                        this.action2(47, "Option B is great choice");
                    });
                }, undefined, "Option B");
            });
        });
    }
}
/** @memo:stable */
class ArkCustomDialogUserComponent extends ArkStructBase<ArkCustomDialogUserComponent, CustomDialogUserOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogUserOptions): void {
        this.__backing_countInitValue = stateOf<number>(initializers?.countInitValue ?? (10), this);
        this.__backing_playingInitValue = stateOf<boolean>(initializers?.playingInitValue ?? (false), this);
        this.__backing_dialogController = initializers?.dialogController ?? (new CustomDialogController({
            builder: DialogExample({
                termsToAccept: "Please accept the terms.",
                action1: this.onAccept,
                action2: this.existApp,
                count: this.countInitValue,
                __backing_isPlaying: this.__backing_playingInitValue
            }),
            cancel: this.existApp,
            autoCancel: false
        }));
    }
    private __backing_countInitValue?: MutableState<number>;
    private get countInitValue(): number {
        return this.__backing_countInitValue!.value;
    }
    private set countInitValue(value: number) {
        this.__backing_countInitValue!.value = observableProxy(value);
    }
    private __backing_playingInitValue?: MutableState<boolean>;
    private get playingInitValue(): boolean {
        return this.__backing_playingInitValue!.value;
    }
    private set playingInitValue(value: boolean) {
        this.__backing_playingInitValue!.value = observableProxy(value);
    }
    private __backing_dialogController?: CustomDialogController;
    private get dialogController(): CustomDialogController {
        return this.__backing_dialogController as CustomDialogController;
    }
    private set dialogController(value: CustomDialogController) {
        this.__backing_dialogController = value;
    }
    onAccept() {
        console.log("onAccept");
    }
    existApp() {
        console.log("Cancel dialog!");
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogUserOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'current countInitValue is: ' + this.countInitValue);
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'current playingInitValue is: ' + this.playingInitValue);
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.countInitValue--;
                    this.dialogController.open();
                });
            }, undefined, "Click to open Dialog -1");
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.countInitValue++;
                    this.dialogController.close();
                });
            }, undefined, "Click to close Dialog +1");
        });
    }
}
export {};
/** @memo */
export function DialogExampleImpl(initializers?: DialogExampleOptions): void {
    const updatedInitializers: DialogExampleOptions = {
        count: initializers?.count,
        __backing_count: initializers?.__backing_count,
        __backing_isPlaying: initializers?.__backing_isPlaying,
        controller: initializers?.controller,
        termsToAccept: initializers?.termsToAccept,
        action1: initializers?.action1,
        action2: initializers?.action2
    };
    ArkDialogExampleComponent._instantiate(undefined, () => new ArkDialogExampleComponent, undefined, updatedInitializers);
}
export function DialogExample(initializer: DialogExampleOptions = {}) {
    return { build: bindCustomDialog(DialogExampleImpl, initializer), buildOptions: initializer };
}
/** @memo */
export function CustomDialogUser(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomDialogUserOptions): void {
    const updatedInitializers: CustomDialogUserOptions = {
        __backing_countInitValue: initializers?.__backing_countInitValue,
        __backing_playingInitValue: initializers?.__backing_playingInitValue,
        dialogController: initializers?.dialogController
    };
    ArkCustomDialogUserComponent._instantiate(style, () => new ArkCustomDialogUserComponent, content, updatedInitializers);
}
export interface DialogExampleOptions {
    __backing_count?: SyncedProperty<number>;
    count?: number;
    __backing_isPlaying?: MutableState<boolean>;
    isPlaying?: boolean;
    controller?: CustomDialogController;
    termsToAccept?: string;
    action1?: () => void;
    action2?: (x: number, s: string) => void;
}
export interface CustomDialogUserOptions {
    __backing_countInitValue?: MutableState<number>;
    countInitValue?: number;
    __backing_playingInitValue?: MutableState<boolean>;
    playingInitValue?: boolean;
    dialogController?: CustomDialogController;
}
registerArkuiEntry(CustomDialogUser, "@customDialog");
export const __Entry = CustomDialogUser;
