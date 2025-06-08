import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, FlexAlign, FlexDirection, ForEach, GestureGroup, IDataSource, ItemAlign, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkTapGestureExampleComponent extends ArkStructBase<ArkTapGestureExampleComponent, TapGestureExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TapGestureExampleOptions): void {
        this.__backing_value = stateOf<string>(initializers?.value ?? (''), this);
    }
    private __backing_value?: MutableState<string>;
    private get value(): string {
        return this.__backing_value!.value;
    }
    private set value(value: string) {
        this.__backing_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TapGestureExampleOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(200).width(300).padding(60).border({ width: 1 }).margin(30)
                    .gesture(TapGesture({ count: 2 })
                    .onAction(() => {
                    this.value = 'TapGesture onAction';
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText(undefined, undefined, 'Click twice');
            ArkText(undefined, undefined, this.value);
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function TapGestureExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TapGestureExampleOptions): void {
    const updatedInitializers: TapGestureExampleOptions = {
        __backing_value: initializers?.__backing_value
    };
    ArkTapGestureExampleComponent._instantiate(style, () => new ArkTapGestureExampleComponent, content, updatedInitializers);
}
export interface TapGestureExampleOptions {
    __backing_value?: MutableState<string>;
    value?: string;
}
registerArkuiEntry(TapGestureExample, "tapGesture");
export const __Entry = TapGestureExample;
