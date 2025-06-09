import { $r, $rawfile, AppStorage, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
/* TODO: not yet implemented in the plugin */
// @AnimatableExtend
class FooAttribute {
    bar(): this {
        console.log("bar");
        return this;
    }
    qux(): this {
        console.log("qux");
        return this;
    }
}
@BuilderLambda("_Foo")
declare function Foo(arg1: string): FooAttribute;
function _Foo(builder: (instance) => FooAttribute, arg1: string): void {
    builder(new FooAttribute());
}
_Foo(__instance => {
    __instance.bar()
        .qux();
}, "label");
