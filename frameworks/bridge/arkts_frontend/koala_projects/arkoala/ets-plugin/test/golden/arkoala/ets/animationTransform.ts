import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkCommonMethodInterface, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, Color, Curve, LocalStorage, MutableState, observableProxy, stateOf } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/** @memo */
function myStyles<T extends ArkCommonMethodInterface<T>>(CommonInstance: T): T {
    return CommonInstance.opacity(1)
        .backgroundColor(Color.Red)
        .animation({ delay: 100, duration: 1000 })
        .width(100)
        .animation({ duration: 2000 })
        .height(100)
        .borderRadius(10)
        .animation({
        delay: 100,
        curve: Curve.EaseOut,
        duration: 3000
    });
}
/** @memo:stable */
class ArkAnimationExampleComponent extends ArkStructBase<ArkAnimationExampleComponent, AnimationExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: AnimationExampleOptions): void {
        this.__backing_myOpacity = stateOf<number>(initializers?.myOpacity ?? (1), this);
        this.__backing_myColor = stateOf<Color>(initializers?.myColor ?? (Color.Red), this);
        this.__backing_myWidth = stateOf<number>(initializers?.myWidth ?? (100), this);
        this.__backing_myHeight = stateOf<number>(initializers?.myHeight ?? (100), this);
        this.__backing_myRadius = stateOf<number>(initializers?.myRadius ?? (10), this);
    }
    private __backing_myOpacity?: MutableState<number>;
    private get myOpacity(): number {
        return this.__backing_myOpacity!.value;
    }
    private set myOpacity(value: number) {
        this.__backing_myOpacity!.value = observableProxy(value);
    }
    private __backing_myColor?: MutableState<Color>;
    private get myColor(): Color {
        return this.__backing_myColor!.value;
    }
    private set myColor(value: Color) {
        this.__backing_myColor!.value = observableProxy(value);
    }
    private __backing_myWidth?: MutableState<number>;
    private get myWidth(): number {
        return this.__backing_myWidth!.value;
    }
    private set myWidth(value: number) {
        this.__backing_myWidth!.value = observableProxy(value);
    }
    private __backing_myHeight?: MutableState<number>;
    private get myHeight(): number {
        return this.__backing_myHeight!.value;
    }
    private set myHeight(value: number) {
        this.__backing_myHeight!.value = observableProxy(value);
    }
    private __backing_myRadius?: MutableState<number>;
    private get myRadius(): number {
        return this.__backing_myRadius!.value;
    }
    private set myRadius(value: number) {
        this.__backing_myRadius!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: AnimationExampleOptions) {
        ArkColumn(__instance => {
            {
                __instance.__applyStyle(myStyles)
                    .opacity(this.myOpacity)
                    .backgroundColor(this.myColor)
                    .animation({ delay: 100, duration: 1000 })
                    .width(this.myWidth)
                    .animation({ duration: 2000 })
                    .height(this.myHeight)
                    .borderRadius(this.myRadius)
                    .animation({
                    delay: 100,
                    curve: Curve.EaseOut,
                    duration: 3000
                })
                    .onClick(() => {
                    this.myOpacity = 0.5;
                    this.myColor = Color.Green;
                    this.myWidth = 200;
                    this.myHeight = 200;
                    this.myRadius = 20;
                });
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo */
export function AnimationExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: AnimationExampleOptions): void {
    const updatedInitializers: AnimationExampleOptions = {
        __backing_myOpacity: initializers?.__backing_myOpacity,
        __backing_myColor: initializers?.__backing_myColor,
        __backing_myWidth: initializers?.__backing_myWidth,
        __backing_myHeight: initializers?.__backing_myHeight,
        __backing_myRadius: initializers?.__backing_myRadius
    };
    ArkAnimationExampleComponent._instantiate(style, () => new ArkAnimationExampleComponent, content, updatedInitializers);
}
export interface AnimationExampleOptions {
    __backing_myOpacity?: MutableState<number>;
    myOpacity?: number;
    __backing_myColor?: MutableState<Color>;
    myColor?: Color;
    __backing_myWidth?: MutableState<number>;
    myWidth?: number;
    __backing_myHeight?: MutableState<number>;
    myHeight?: number;
    __backing_myRadius?: MutableState<number>;
    myRadius?: number;
}
registerArkuiEntry(AnimationExample, "animationTransform");
export const __Entry = AnimationExample;
