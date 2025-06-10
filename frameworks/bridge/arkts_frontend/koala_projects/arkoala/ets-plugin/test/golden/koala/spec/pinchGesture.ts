import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, FlexAlign, FlexDirection, ForEach, GestureEvent, GestureGroup, IDataSource, ItemAlign, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkPinchGestureExampleComponent extends ArkStructBase<ArkPinchGestureExampleComponent, PinchGestureExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PinchGestureExampleOptions): void {
        this.__backing_scale2 = stateOf<number>(initializers?.scale2 ?? (1), this);
    }
    private __backing_scale2?: MutableState<number>;
    private get scale2(): number {
        return this.__backing_scale2!.value;
    }
    private set scale2(value: number) {
        this.__backing_scale2!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PinchGestureExampleOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(100).width(200).padding(20).border({ width: 1 }).margin(80)
                    .scale({ x: this.scale2, y: this.scale2, z: this.scale2 })
                    .gesture(PinchGesture()
                    .onActionStart((event: GestureEvent) => {
                    console.info('Pinch start');
                })
                    .onActionUpdate((event: GestureEvent) => {
                    this.scale2 = event.scale;
                })
                    .onActionEnd(() => {
                    console.info('Pinch end');
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText(undefined, undefined, 'PinchGesture scale:' + this.scale2);
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function PinchGestureExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PinchGestureExampleOptions): void {
    const updatedInitializers: PinchGestureExampleOptions = {
        __backing_scale2: initializers?.__backing_scale2
    };
    ArkPinchGestureExampleComponent._instantiate(style, () => new ArkPinchGestureExampleComponent, content, updatedInitializers);
}
export interface PinchGestureExampleOptions {
    __backing_scale2?: MutableState<number>;
    scale2?: number;
}
registerArkuiEntry(PinchGestureExample, "pinchGesture");
export const __Entry = PinchGestureExample;
