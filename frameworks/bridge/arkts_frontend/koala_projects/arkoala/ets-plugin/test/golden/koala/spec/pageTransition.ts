import { $r, $rawfile, AppStorage, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkNavigator, ArkNavigatorComponent, ArkPageTransitionEnter, ArkPageTransitionEnterComponent, ArkPageTransitionExit, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, Curve, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, NavigationType, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, RouteType, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkPageTransitionExample1Component extends ArkStructBase<ArkPageTransitionExample1Component, PageTransitionExample1Options> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PageTransitionExample1Options): void {
        this.__backing_scale2 = stateOf<number>(initializers?.scale2 ?? (1), this);
        this.__backing_opacity2 = stateOf<number>(initializers?.opacity2 ?? (1), this);
        this.__backing_active = stateOf<boolean>(initializers?.active ?? (false), this);
    }
    private __backing_scale2?: MutableState<number>;
    private get scale2(): number {
        return this.__backing_scale2!.value;
    }
    private set scale2(value: number) {
        this.__backing_scale2!.value = observableProxy(value);
    }
    private __backing_opacity2?: MutableState<number>;
    private get opacity2(): number {
        return this.__backing_opacity2!.value;
    }
    private set opacity2(value: number) {
        this.__backing_opacity2!.value = observableProxy(value);
    }
    private __backing_active?: MutableState<boolean>;
    private get active(): boolean {
        return this.__backing_active!.value;
    }
    private set active(value: boolean) {
        this.__backing_active!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PageTransitionExample1Options) {
        ArkColumn(__instance => {
            {
                __instance.scale({ x: this.scale2 }).opacity(this.opacity2);
            }
            __builder?.(__instance);
        }, () => {
            ArkNavigator((__instance: ArkNavigatorComponent) => {
                __instance.onClick(() => {
                    this.active = true;
                });
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.width("100%").height("100%");
                }, undefined, 'page transition');
            }, { target: 'pages/page1', type: NavigationType.Push });
        });
    }
    /** @memo */
    pageTransition() {
        ArkPageTransitionEnter((__instance: ArkPageTransitionEnterComponent) => {
            __instance.onEnter((type: RouteType, progress: number) => {
                this.scale2 = 1;
                this.opacity2 = progress;
            });
        }, undefined, { duration: 1200, curve: Curve.Linear });
        ArkPageTransitionExit((__instance: ArkPageTransitionExitComponent) => {
            __instance.onExit((type: RouteType, progress: number) => {
                this.scale2 = 1 - progress;
                this.opacity2 = 1;
            });
        }, undefined, { duration: 1500, curve: Curve.Ease });
    }
}
export {};
/** @memo */
export function PageTransitionExample1(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PageTransitionExample1Options): void {
    const updatedInitializers: PageTransitionExample1Options = {
        __backing_scale2: initializers?.__backing_scale2,
        __backing_opacity2: initializers?.__backing_opacity2,
        __backing_active: initializers?.__backing_active
    };
    ArkPageTransitionExample1Component._instantiate(style, () => new ArkPageTransitionExample1Component, content, updatedInitializers);
}
export interface PageTransitionExample1Options {
    __backing_scale2?: MutableState<number>;
    scale2?: number;
    __backing_opacity2?: MutableState<number>;
    opacity2?: number;
    __backing_active?: MutableState<boolean>;
    active?: boolean;
}
registerArkuiEntry(PageTransitionExample1, "pageTransition");
export const __Entry = PageTransitionExample1;
