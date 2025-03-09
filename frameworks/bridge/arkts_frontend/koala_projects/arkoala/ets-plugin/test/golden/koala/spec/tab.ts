import { $r, $rawfile, AppStorage, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkTabContent, ArkTabContentComponent, ArkTabs, ArkText, ArkTextComponent, BarPosition, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo:stable */
class ArkTabSimpleComponent extends ArkStructBase<ArkTabSimpleComponent, TabSimpleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TabSimpleOptions): void {
        this.__backing_controller = initializers?.controller ?? (new TabsController());
    }
    private __backing_controller?: TabsController;
    private get controller(): TabsController {
        return this.__backing_controller as TabsController;
    }
    private set controller(value: TabsController) {
        this.__backing_controller = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TabSimpleOptions) {
        ArkColumn(__builder, () => {
            ArkTabs(undefined, () => {
                ArkTabContent((__instance: ArkTabContentComponent) => {
                    __instance.tabBar("TabBar")
                        .height(100)
                        .width(200);
                }, () => {
                    ArkFlex((__instance: ArkFlexComponent) => {
                        __instance.height(100)
                            .width(200);
                    }, () => {
                        ArkColumn((__instance: ArkColumnComponent) => {
                            __instance.height(100)
                                .width(200);
                        }, () => {
                            ArkText((__instance: ArkTextComponent) => {
                                __instance.height(100)
                                    .width(200);
                            }, undefined, 'text1');
                            ArkText((__instance: ArkTextComponent) => {
                                __instance.height(100)
                                    .width(200);
                            }, undefined, 'xxx');
                        });
                    });
                });
                ArkTabContent((__instance: ArkTabContentComponent) => {
                    __instance.tabBar("TabBar 2")
                        .height(100)
                        .width(200);
                }, () => {
                    ArkText(undefined, undefined, 'text2');
                });
            }, { barPosition: BarPosition.Start, index: 1, controller: this.controller });
        });
    }
}
export {};
/** @memo */
export function TabSimple(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TabSimpleOptions): void {
    const updatedInitializers: TabSimpleOptions = {
        controller: initializers?.controller
    };
    ArkTabSimpleComponent._instantiate(style, () => new ArkTabSimpleComponent, content, updatedInitializers);
}
export interface TabSimpleOptions {
    controller?: TabsController;
}
registerArkuiEntry(TabSimple, "tab");
export const __Entry = TabSimple;
