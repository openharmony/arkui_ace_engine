import { $r, $rawfile, AppStorage, ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, CanvasRenderingContext2D, Color, Curve, CustomDialogController, DataChangeListener, Environment, FlexDirection, ForEach, GestureGroup, IDataSource, ItemAlign, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, PlayMode, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, TransitionType, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkTransitionExampleComponent extends ArkStructBase<ArkTransitionExampleComponent, TransitionExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TransitionExampleOptions): void {
        this.__backing_btnW = stateOf<number>(initializers?.btnW ?? (50), this);
        this.__backing_btnH = stateOf<number>(initializers?.btnH ?? (50), this);
        this.__backing_btn1 = stateOf<boolean>(initializers?.btn1 ?? (false), this);
        this.__backing_show = stateOf<string>(initializers?.show ?? ("show"), this);
        this.__backing_color = stateOf<Color>(initializers?.color ?? (Color.Red), this);
        this.__backing_width1 = stateOf<number>(initializers?.width1 ?? (100), this);
        this.__backing_height1 = stateOf<number>(initializers?.height1 ?? (100), this);
        this.__backing_opacity1 = stateOf<number>(initializers?.opacity1 ?? (1), this);
        this.__backing_borderRaius1 = stateOf<number>(initializers?.borderRaius1 ?? (10), this);
    }
    private __backing_btnW?: MutableState<number>;
    private get btnW(): number {
        return this.__backing_btnW!.value;
    }
    private set btnW(value: number) {
        this.__backing_btnW!.value = observableProxy(value);
    }
    private __backing_btnH?: MutableState<number>;
    private get btnH(): number {
        return this.__backing_btnH!.value;
    }
    private set btnH(value: number) {
        this.__backing_btnH!.value = observableProxy(value);
    }
    private __backing_btn1?: MutableState<boolean>;
    private get btn1(): boolean {
        return this.__backing_btn1!.value;
    }
    private set btn1(value: boolean) {
        this.__backing_btn1!.value = observableProxy(value);
    }
    private __backing_show?: MutableState<string>;
    private get show(): string {
        return this.__backing_show!.value;
    }
    private set show(value: string) {
        this.__backing_show!.value = observableProxy(value);
    }
    private __backing_color?: MutableState<Color>;
    private get color(): Color {
        return this.__backing_color!.value;
    }
    private set color(value: Color) {
        this.__backing_color!.value = observableProxy(value);
    }
    private __backing_width1?: MutableState<number>;
    private get width1(): number {
        return this.__backing_width1!.value;
    }
    private set width1(value: number) {
        this.__backing_width1!.value = observableProxy(value);
    }
    private __backing_height1?: MutableState<number>;
    private get height1(): number {
        return this.__backing_height1!.value;
    }
    private set height1(value: number) {
        this.__backing_height1!.value = observableProxy(value);
    }
    private __backing_opacity1?: MutableState<number>;
    private get opacity1(): number {
        return this.__backing_opacity1!.value;
    }
    private set opacity1(value: number) {
        this.__backing_opacity1!.value = observableProxy(value);
    }
    private __backing_borderRaius1?: MutableState<number>;
    private get borderRaius1(): number {
        return this.__backing_borderRaius1!.value;
    }
    private set borderRaius1(value: number) {
        this.__backing_borderRaius1!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TransitionExampleOptions) {
        ArkFlex(__instance => {
            {
                __instance.height(400).width("100%").padding({ top: 100 });
            }
            __builder?.(__instance);
        }, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    animateTo({ duration: 1000 }, () => {
                        this.btn1 = !this.btn1;
                        if (this.btn1) {
                            this.show = "hide";
                        }
                        else {
                            this.show = "show";
                        }
                    });
                });
            }, undefined, this.show);
            if (this.btn1) {
                ArkButton((__instance: ArkButtonComponent) => {
                    __instance.width("80%").height(30)
                        .transition({ type: TransitionType.Insert, scale: { x: 0, y: 1.0 } })
                        .transition({ type: TransitionType.Delete, scale: { x: 1.0, y: 0.0 } });
                }, undefined);
            }
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.width(this.btnW).height(this.btnH)
                    .onClick(() => {
                    this.btnW += 50;
                })
                    .animation({
                    duration: 1000,
                    curve: Curve.EaseOut,
                    delay: 200,
                    iterations: 1,
                    playMode: PlayMode.Normal // 动画模式
                });
            }, undefined, 'animation');
            ArkColumn((__instance: ArkColumnComponent) => {
                __instance.width("100%")
                    .height("100%");
            }, () => {
                ArkColumn((__instance: ArkColumnComponent) => {
                    __instance.opacity(this.opacity1)
                        .backgroundColor(this.color)
                        .animation({ duration: 1000 })
                        .width(this.width1)
                        .animation({ duration: 2000 })
                        .height(this.height1)
                        .borderRadius(this.borderRaius1)
                        .animation({ duration: 3000 })
                        .onClick(() => {
                        this.color = Color.Green;
                        this.borderRaius1 = 20;
                        this.opacity1 = 0.5;
                        this.height1 = 200;
                        this.width1 = 200;
                    });
                }, undefined);
            }, { space: 5 });
        }, { direction: FlexDirection.Column, alignItems: ItemAlign.Center, });
    }
}
export {};
/** @memo */
export function TransitionExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TransitionExampleOptions): void {
    const updatedInitializers: TransitionExampleOptions = {
        __backing_btnW: initializers?.__backing_btnW,
        __backing_btnH: initializers?.__backing_btnH,
        __backing_btn1: initializers?.__backing_btn1,
        __backing_show: initializers?.__backing_show,
        __backing_color: initializers?.__backing_color,
        __backing_width1: initializers?.__backing_width1,
        __backing_height1: initializers?.__backing_height1,
        __backing_opacity1: initializers?.__backing_opacity1,
        __backing_borderRaius1: initializers?.__backing_borderRaius1
    };
    ArkTransitionExampleComponent._instantiate(style, () => new ArkTransitionExampleComponent, content, updatedInitializers);
}
export interface TransitionExampleOptions {
    __backing_btnW?: MutableState<number>;
    btnW?: number;
    __backing_btnH?: MutableState<number>;
    btnH?: number;
    __backing_btn1?: MutableState<boolean>;
    btn1?: boolean;
    __backing_show?: MutableState<string>;
    show?: string;
    __backing_color?: MutableState<Color>;
    color?: Color;
    __backing_width1?: MutableState<number>;
    width1?: number;
    __backing_height1?: MutableState<number>;
    height1?: number;
    __backing_opacity1?: MutableState<number>;
    opacity1?: number;
    __backing_borderRaius1?: MutableState<number>;
    borderRaius1?: number;
}
registerArkuiEntry(TransitionExample, "animateTo");
export const __Entry = TransitionExample;
