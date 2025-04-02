import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkStatePageComponent extends ArkStructBase<ArkStatePageComponent, StatePageOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StatePageOptions): void {
        this.__backing_counter = stateOf<number>(initializers?.counter ?? (0), this);
    }
    private __backing_counter?: MutableState<number>;
    private get counter(): number {
        return this.__backing_counter!.value;
    }
    private set counter(value: number) {
        this.__backing_counter!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StatePageOptions) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, "counter:" + this.counter);
        });
    }
}
export {};
/** @memo */
export function StatePage(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StatePageOptions): void {
    const updatedInitializers: StatePageOptions = {
        __backing_counter: initializers?.__backing_counter
    };
    ArkStatePageComponent._instantiate(style, () => new ArkStatePageComponent, content, updatedInitializers);
}
export interface StatePageOptions {
    __backing_counter?: MutableState<number>;
    counter?: number;
}
registerArkuiEntry(StatePage, "@state");
export const __Entry = StatePage;
