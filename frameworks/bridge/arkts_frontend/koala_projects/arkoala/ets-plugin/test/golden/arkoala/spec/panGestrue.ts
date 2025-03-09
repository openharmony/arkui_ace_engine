import { ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, FlexAlign, FlexDirection, GestureEvent, ItemAlign, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkPanGestureExampleComponent extends ArkStructBase<ArkPanGestureExampleComponent, PanGestureExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PanGestureExampleOptions): void {
        this.__backing_offsetX = stateOf<number>(initializers?.offsetX ?? (0), this);
        this.__backing_offsetY = stateOf<number>(initializers?.offsetY ?? (0), this);
    }
    private __backing_offsetX?: MutableState<number>;
    private get offsetX(): number {
        return this.__backing_offsetX!.value;
    }
    private set offsetX(value: number) {
        this.__backing_offsetX!.value = observableProxy(value);
    }
    private __backing_offsetY?: MutableState<number>;
    private get offsetY(): number {
        return this.__backing_offsetY!.value;
    }
    private set offsetY(value: number) {
        this.__backing_offsetY!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PanGestureExampleOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(100).width(200).padding(20).border({ width: 1 }).margin(80)
                    .translate({ x: this.offsetX, y: this.offsetY, z: 5 })
                    .gesture(PanGesture({})
                    .onActionStart((event: GestureEvent) => {
                    console.info('Pan start');
                })
                    .onActionUpdate((event: GestureEvent) => {
                    this.offsetX = event.offsetX;
                    this.offsetY = event.offsetY;
                })
                    .onActionEnd(() => {
                    console.info('Pan end');
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText(undefined, undefined, 'PanGesture offset X: ' + this.offsetX);
            ArkText(undefined, undefined, 'PanGesture offset Y: ' + this.offsetY);
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.SpaceBetween });
    }
}
export {};
/** @memo */
export function PanGestureExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PanGestureExampleOptions): void {
    const updatedInitializers: PanGestureExampleOptions = {
        __backing_offsetX: initializers?.__backing_offsetX,
        __backing_offsetY: initializers?.__backing_offsetY
    };
    ArkPanGestureExampleComponent._instantiate(style, () => new ArkPanGestureExampleComponent, content, updatedInitializers);
}
export interface PanGestureExampleOptions {
    __backing_offsetX?: MutableState<number>;
    offsetX?: number;
    __backing_offsetY?: MutableState<number>;
    offsetY?: number;
}
registerArkuiEntry(PanGestureExample, "panGestrue");
export const __Entry = PanGestureExample;
