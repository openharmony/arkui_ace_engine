import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkGrid, ArkGridItem, ArkGridItemComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo:stable */
class ArkParentViewComponent extends ArkStructBase<ArkParentViewComponent, ParentViewOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentViewOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ParentViewOptions) {
        ArkGrid(__builder, () => {
            ArkGridItem((__instance: ArkGridItemComponent) => {
                __instance.width(200).height(100);
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.width(100);
                }, undefined, 'xx');
            });
        });
    }
}
export {};
/** @memo */
export function ParentView(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentViewOptions): void {
    const updatedInitializers: ParentViewOptions = {};
    ArkParentViewComponent._instantiate(style, () => new ArkParentViewComponent, content, updatedInitializers);
}
export interface ParentViewOptions {
}
registerArkuiEntry(ParentView, "GridItem");
export const __Entry = ParentView;
