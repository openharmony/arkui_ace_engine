import { $r, $rawfile, AppStorage, ArkButton, ArkButtonComponent, ArkColumn, ArkCommonMethodComponent, ArkDivider, ArkDividerComponent, ArkFlex, ArkFlexComponent, ArkList, ArkListComponent, ArkListItem, ArkListItemComponent, ArkNavigation, ArkNavigationComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, ArkTabContent, ArkTabContentComponent, ArkTabs, ArkText, ArkTextComponent, Axis, BarPosition, CanvasRenderingContext2D, Color, CustomDialogController, DataChangeListener, DragEvent, Environment, FlexAlign, FlexDirection, ForEach, GestureGroup, IDataSource, ItemAlign, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, ResponseType, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAlign, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { observableProxy } from "@koalaui/common";
/** @memo */
function noParam() {
    ArkRow(undefined, () => {
        ArkText(undefined, undefined, 'this is a no param builder');
    });
}
/** @memo */
function specificParam(label1: string, label2: string) {
    ArkColumn(undefined, () => {
        ArkText(undefined, undefined, label1);
        ArkText(undefined, undefined, label2);
    });
}
/** @memo:stable */
class ArkMyComponentComponent extends ArkStructBase<ArkMyComponentComponent, MyComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions): void {
        this.__backing_arr = initializers?.arr ?? ([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
        this.__backing_controller = initializers?.controller ?? (new TabsController());
        this.__backing_hideBar = stateOf<boolean>(initializers?.hideBar ?? (true), this);
    }
    private __backing_arr?: number[];
    private get arr(): number[] {
        return this.__backing_arr as number[];
    }
    private set arr(value: number[]) {
        this.__backing_arr = value;
    }
    private __backing_controller?: TabsController;
    private get controller(): TabsController {
        return this.__backing_controller as TabsController;
    }
    private set controller(value: TabsController) {
        this.__backing_controller = value;
    }
    private __backing_hideBar?: MutableState<boolean>;
    private get hideBar(): boolean {
        return this.__backing_hideBar!.value;
    }
    private set hideBar(value: boolean) {
        this.__backing_hideBar!.value = observableProxy(value);
    }
    /** @memo */
    textBuilder() {
        ArkText((__instance: ArkTextComponent) => {
            __instance.fontSize(30);
        }, undefined, "文本");
    }
    /** @memo */
    NavigationTitlePara(label: string) {
        ArkColumn(undefined, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.width(80)
                    .bindMenu(this.textBuilder);
            }, undefined, label);
        });
    }
    /** @memo */
    MenuBuilder() {
        ArkFlex((__instance: ArkFlexComponent) => {
            __instance.width(100);
        }, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'Test menu item 1');
            ArkDivider((__instance: ArkDividerComponent) => {
                __instance.height(10);
            }, undefined);
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(20);
            }, undefined, 'Test menu item 2');
        }, { direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center });
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions) {
        ArkColumn(__builder, () => {
            ArkRow((__instance: ArkRowComponent) => {
                __instance.padding(10)
                    .bindMenu(/* */
                /** @memo */
                (): void => this.NavigationTitlePara("111"));
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.onDragStart((event: DragEvent, extraParams: string) => {
                        console.log('Text onDragStarts, ' + extraParams);
                    });
                }, undefined, "Drag Me");
                specificParam('test1', 'test2');
            });
            ArkRow((__instance: ArkRowComponent) => {
                __instance.padding(10)
                    .bindPopup(false, {
                    builder: this.MenuBuilder,
                    onStateChange: (e) => {
                        if (!e.isVisible) {
                            console.warn(JSON.stringify(e.isVisible));
                        }
                    }
                });
            }, () => {
                ArkText(undefined, undefined, 'Test Text');
            });
            ArkRow((__instance: ArkRowComponent) => {
                __instance.padding(10)
                    .bindContextMenu(this.MenuBuilder, ResponseType.RightClick);
            }, () => {
                ArkText(undefined, undefined, 'rightclick for menu');
            });
            ArkRow((__instance: ArkRowComponent) => {
                __instance.padding(10);
            }, () => {
                ArkNavigation((__instance: ArkNavigationComponent) => {
                    __instance.title(noParam)
                        .menus(this.textBuilder)
                        .toolBar({ items: [
                            { value: 'app', text: 'Grid', action: () => {
                                    console.log("app");
                                } },
                            { value: 'add', text: 'Add', action: () => {
                                    console.log("add");
                                } },
                            { value: 'collect', text: 'Collect', action: () => {
                                    console.log("collect");
                                } }
                        ] })
                        .hideToolBar(this.hideBar);
                }, () => {
                    ArkList((__instance: ArkListComponent) => {
                        __instance.listDirection(Axis.Vertical)
                            .height(300)
                            .margin({ top: 10, left: 18 })
                            .width('100%');
                    }, () => {
                        ForEach(this.arr, (item) => {
                            ArkListItem((__instance: ArkListItemComponent) => {
                                __instance.editable(true);
                            }, () => {
                                ArkText((__instance: ArkTextComponent) => {
                                    __instance.width('90%')
                                        .height(80)
                                        .backgroundColor('#3366CC')
                                        .borderRadius(15)
                                        .fontSize(16)
                                        .textAlign(TextAlign.Center);
                                }, undefined, '' + item);
                            });
                        }, item => item);
                    }, { space: 5, initialIndex: 0 });
                    ArkButton((__instance: ArkButtonComponent) => {
                        __instance.onClick(() => {
                            this.hideBar = !this.hideBar;
                        })
                            .margin({ left: 135, top: 60 });
                    }, undefined, this.hideBar ? "tool bar" : "hide bar");
                });
            });
            ArkRow((__instance: ArkRowComponent) => {
                __instance.padding(10);
            }, () => {
                ArkTabs(undefined, () => {
                    ArkTabContent((__instance: ArkTabContentComponent) => {
                        __instance.tabBar('pink');
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.width('100%').height('20').backgroundColor(Color.Pink);
                        }, undefined, '111');
                    });
                    ArkTabContent((__instance: ArkTabContentComponent) => {
                        __instance.tabBar('yellow');
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.width('100%').height('20').backgroundColor(Color.Yellow);
                        }, undefined, '222');
                    });
                    ArkTabContent((__instance: ArkTabContentComponent) => {
                        __instance.tabBar('blue');
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.width('100%').height('20').backgroundColor(Color.Blue);
                        }, undefined, '333');
                    });
                }, { barPosition: BarPosition.Start, controller: this.controller });
            });
        });
    }
}
export {};
/** @memo */
export function MyComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: MyComponentOptions): void {
    const updatedInitializers: MyComponentOptions = {
        arr: initializers?.arr,
        controller: initializers?.controller,
        __backing_hideBar: initializers?.__backing_hideBar
    };
    ArkMyComponentComponent._instantiate(style, () => new ArkMyComponentComponent, content, updatedInitializers);
}
export interface MyComponentOptions {
    arr?: number[];
    controller?: TabsController;
    __backing_hideBar?: MutableState<boolean>;
    hideBar?: boolean;
}
registerArkuiEntry(MyComponent, "@builder");
export const __Entry = MyComponent;
