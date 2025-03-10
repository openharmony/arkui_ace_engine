import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, GestureEvent, LocalStorage, MutableState, SwipeDirection, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo:stable */
class ArkSwipeGestureExampleComponent extends ArkStructBase<ArkSwipeGestureExampleComponent, SwipeGestureExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: SwipeGestureExampleOptions): void {
        this.__backing_rotateAngle = stateOf<number>(initializers?.rotateAngle ?? (0), this);
        this.__backing_speed = stateOf<number>(initializers?.speed ?? (1), this);
    }
    private __backing_rotateAngle?: MutableState<number>;
    private get rotateAngle(): number {
        return this.__backing_rotateAngle!.value;
    }
    private set rotateAngle(value: number) {
        this.__backing_rotateAngle!.value = observableProxy(value);
    }
    private __backing_speed?: MutableState<number>;
    private get speed(): number {
        return this.__backing_speed!.value;
    }
    private set speed(value: number) {
        this.__backing_speed!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: SwipeGestureExampleOptions) {
        ArkColumn(__instance => {
            {
                __instance.border({ width: 2 })
                    .width(260).height(260)
                    .rotate({ x: 0, y: 0, z: 1, angle: this.rotateAngle })
                    .gesture(SwipeGesture({ fingers: 1, direction: SwipeDirection.Vertical })
                    .onAction((event: GestureEvent) => {
                    this.speed = event.speed;
                    this.rotateAngle = event.angle;
                }));
            }
            __builder?.(__instance);
        }, () => {
            ArkText(undefined, undefined, "SwipGesture speed ： " + this.speed);
            ArkText(undefined, undefined, "SwipGesture angle ： " + this.rotateAngle);
        });
    }
}
export {};
/** @memo */
export function SwipeGestureExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: SwipeGestureExampleOptions): void {
    const updatedInitializers: SwipeGestureExampleOptions = {
        __backing_rotateAngle: initializers?.__backing_rotateAngle,
        __backing_speed: initializers?.__backing_speed
    };
    ArkSwipeGestureExampleComponent._instantiate(style, () => new ArkSwipeGestureExampleComponent, content, updatedInitializers);
}
export interface SwipeGestureExampleOptions {
    __backing_rotateAngle?: MutableState<number>;
    rotateAngle?: number;
    __backing_speed?: MutableState<number>;
    speed?: number;
}
registerArkuiEntry(SwipeGestureExample, "swipeGesture");
export const __Entry = SwipeGestureExample;
