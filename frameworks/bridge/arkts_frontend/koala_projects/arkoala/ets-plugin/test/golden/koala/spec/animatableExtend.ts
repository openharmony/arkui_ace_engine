import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkPolyline, ArkPolylineComponent, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, Color, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
function animatablePoints__Polyline<T extends ArkPolylineComponent>(PolylineInstance: T, points: number): T {
    return PolylineInstance.strokeOpacity(points)
        .backgroundColor(Color.Red);
}
function attributeExtend__Text<T extends ArkTextComponent>(TextInstance: T): T {
    return TextInstance.fontSize(50);
}
/** @memo:stable */
class ArkHomeComponentComponent extends ArkStructBase<ArkHomeComponentComponent, HomeComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions): void {
        this.__backing_points = initializers?.points ?? (1);
    }
    private __backing_points?: number;
    private get points(): number {
        return this.__backing_points as number;
    }
    private set points(value: number) {
        this.__backing_points = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions) {
        ArkColumn(__builder, () => {
            ArkPolyline((__instance: ArkPolylineComponent) => {
                __instance.__applyAnimatableExtend(animatablePoints__Polyline, this.points)
                    .strokeWidth(3)
                    .height(100)
                    .width(100);
            }, undefined);
            ArkText((__instance: ArkTextComponent) => {
                __instance.__applyAnimatableExtend(attributeExtend__Text);
            }, undefined, "hello");
        });
    }
}
export {};
/** @memo */
export function HomeComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: HomeComponentOptions): void {
    const updatedInitializers: HomeComponentOptions = {
        points: initializers?.points
    };
    ArkHomeComponentComponent._instantiate(style, () => new ArkHomeComponentComponent, content, updatedInitializers);
}
export interface HomeComponentOptions {
    points?: number;
}
registerArkuiEntry(HomeComponent, "animatableExtend");
export const __Entry = HomeComponent;
