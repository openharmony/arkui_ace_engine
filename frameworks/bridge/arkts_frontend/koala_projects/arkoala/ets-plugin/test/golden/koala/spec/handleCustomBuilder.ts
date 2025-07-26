import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, DragEvent, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo */
function global() {
    ArkText(undefined, undefined, 'Global Builder');
}
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_judge = initializers?.judge ?? (true);
    }
    private __backing_judge?: boolean;
    private get judge(): boolean {
        return this.__backing_judge as boolean;
    }
    private set judge(value: boolean) {
        this.__backing_judge = value;
    }
    /** @memo */
    inner(param: string) {
        ArkText((__instance: ArkTextComponent) => {
            __instance.bindPopup(false, {
                onStateChange: (e) => { },
                builder: /* */
                /** @memo */
                (): void => global()
            });
        }, undefined, 'Inner Builder Text');
        ArkText((__instance: ArkTextComponent) => {
            __instance.bindPopup(false, {
                onStateChange: (e) => { },
                builder: this.judge ? global : undefined
            });
        }, undefined, 'Inner Builder Text2');
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkColumn(__builder, () => {
            ArkRow((__instance: ArkRowComponent) => {
                __instance.bindMenu(/* */
                /** @memo */
                (): void => this.inner("111"));
            }, undefined);
            ArkRow((__instance: ArkRowComponent) => {
                __instance.bindMenu(this.judge ? /* */
                /** @memo */
                (): void => this.inner("111") : global);
            }, undefined);
            ArkRow((__instance: ArkRowComponent) => {
                __instance.onDragStart((event: DragEvent, extraParams: string) => {
                    console.log('Text onDragStarts, ' + extraParams);
                    return this.judge ? /* */
                    /** @memo */
                    (): void => this.inner("222") : /* */
                    /** @memo */
                    (): void => global();
                });
            }, undefined);
            ArkRow((__instance: ArkRowComponent) => {
                __instance.onDragStart((event: DragEvent, extraParams: string) => {
                    console.log('Text onDragStarts, ' + extraParams);
                    return {
                        builder: this.judge ? /* */
                        /** @memo */
                        (): void => this.inner("333") : undefined
                    };
                });
            }, undefined);
            ArkText((__instance: ArkTextComponent) => {
                __instance.bindPopup(false, {
                    onStateChange: (e) => { },
                    builder: undefined
                });
            }, undefined, 'Text');
        });
    }
}
export {};
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const updatedInitializers: IndexOptions = {
        judge: initializers?.judge
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
export interface IndexOptions {
    judge?: boolean;
}
registerArkuiEntry(Index, "handleCustomBuilder");
export const __Entry = Index;
