import { $r, $rawfile, AppStorage, ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_WIDTH_AND_HEIGHT = stateOf<Array<{
            w: number;
            h: number;
        }>>(initializers?.WIDTH_AND_HEIGHT ?? ([
            { w: 10, h: 10 },
            { w: 20, h: 20 },
            { w: 30, h: 30 },
            { w: 40, h: 40 },
            { w: 50, h: 50 }
        ]), this);
    }
    private __backing_WIDTH_AND_HEIGHT?: MutableState<Array<{
        w: number;
        h: number;
    }>>;
    private get WIDTH_AND_HEIGHT(): Array<{
        w: number;
        h: number;
    }> {
        return this.__backing_WIDTH_AND_HEIGHT!.value;
    }
    private set WIDTH_AND_HEIGHT(value: Array<{
        w: number;
        h: number;
    }>) {
        this.__backing_WIDTH_AND_HEIGHT!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkRow(__instance => {
            {
                __instance.height('100%');
            }
            __builder?.(__instance);
        }, () => {
            ArkColumn((__instance: ArkColumnComponent) => {
                __instance.width('100%');
            }, () => {
                ForEach(this.WIDTH_AND_HEIGHT, ({ w, h }) => {
                    ArkButton((__instance: ArkButtonComponent) => {
                        __instance.width(w)
                            .height(h);
                    }, undefined);
                }, item => item.toString());
            });
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
        __backing_WIDTH_AND_HEIGHT: initializers?.__backing_WIDTH_AND_HEIGHT
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
export interface IndexOptions {
    __backing_WIDTH_AND_HEIGHT?: MutableState<Array<{
        w: number;
        h: number;
    }>>;
    WIDTH_AND_HEIGHT?: Array<{
        w: number;
        h: number;
    }>;
}
registerArkuiEntry(Index, "forEachTwo");
export const __Entry = Index;
