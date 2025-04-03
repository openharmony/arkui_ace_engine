import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkDivider, ArkDividerComponent, ArkList, ArkListItem, ArkListItemComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, ArkTabContent, ArkTabContentComponent, ArkTabs, ArkText, ArkTextComponent, ArkXComponent, ArkXComponentComponent, BarPosition, Color, ListOptions, TabsController, TabsOptions, XComponentOptions } from "@koalaui/arkts-arkui";
import { LocalStorage } from "@koalaui/arkui-common";
/** @memo:stable */
class ArkMyComponentComponent extends ArkStructBase<ArkMyComponentComponent, MyComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions): void {
        this.__backing_pass = initializers?.pass ?? (true);
        this.__backing_count = initializers?.count ?? (10);
        this.__backing_controller = initializers?.controller ?? (new TabsController());
    }
    private __backing_pass?: boolean;
    private get pass(): boolean {
        return this.__backing_pass as boolean;
    }
    private set pass(value: boolean) {
        this.__backing_pass = value;
    }
    private __backing_count?: number;
    private get count(): number {
        return this.__backing_count as number;
    }
    private set count(value: number) {
        this.__backing_count = value;
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
    content?: () => void, initializers?: MyComponentOptions) {
        ArkColumn(__builder, () => {
            if (this.pass) {
                if (this.count < 0) {
                    ArkText((__instance: ArkTextComponent) => {
                        __instance.fontSize(32)
                            .id('id1');
                    }, undefined, 'count is negative');
                }
                else if (this.count % 2 === 0) {
                    ArkDivider((__instance: ArkDividerComponent) => {
                        __instance.id('id2');
                    }, undefined);
                    ArkText((__instance: ArkTextComponent) => {
                        __instance.fontSize(32)
                            .id('id3');
                    }, undefined, 'even');
                }
                else {
                    ArkDivider((__instance: ArkDividerComponent) => {
                        __instance.id('id4');
                    }, undefined);
                    ArkColumn((__instance: ArkColumnComponent) => {
                        __instance.id('id10');
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.fontSize(32)
                                .id('id5');
                        }, undefined, 'odd');
                    });
                }
            }
            else {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.id('id6')
                        .fontSize(32);
                }, undefined, 'fail');
            }
            if (this.pass)
                ArkText((__instance: ArkTextComponent) => {
                    __instance.fontSize(32).id('id7');
                }, undefined, 'odd2');
            ArkList(undefined, () => {
                if (this.pass) {
                    ArkListItem((__instance: ArkListItemComponent) => {
                        __instance.id('id8');
                    }, () => {
                        ArkRow((__instance: ArkRowComponent) => {
                            __instance.margin({ left: 10, right: 10 }).id('id11');
                        }, () => {
                            ArkText((__instance: ArkTextComponent) => {
                                __instance.fontSize(20).margin({ left: 10 });
                            }, undefined);
                        });
                    });
                }
            }, { space: 3 } as ListOptions);
            ArkTabs(undefined, () => {
                if (this.pass) {
                    ArkTabContent((__instance: ArkTabContentComponent) => {
                        __instance.tabBar('pink')
                            .id('id9');
                    }, () => {
                        ArkText((__instance: ArkTextComponent) => {
                            __instance.width('100%').height('20').backgroundColor(Color.Pink);
                        }, undefined, '111');
                    });
                }
            }, { barPosition: BarPosition.Start, controller: this.controller } as TabsOptions);
            if (this.pass) {
                if (this.count === 10) {
                    ArkColumn(undefined, () => {
                        ArkText(undefined, undefined, '111');
                    });
                    ArkXComponent((__instance: ArkXComponentComponent) => {
                        __instance.id('id12');
                    }, undefined, { id: 'special', type: '' } as XComponentOptions);
                    ArkColumn((__instance: ArkColumnComponent) => {
                        __instance.id('id13');
                    }, () => {
                        ArkText(undefined, undefined, '11');
                    });
                    ArkColumn(undefined, () => {
                        ArkText(undefined, undefined, '222');
                    });
                }
            }
            if (this.pass) {
                Child((__instance: ArkCommonMethodComponent) => {
                    __instance.id('id14');
                }, undefined);
                ArkText(undefined, undefined, '111');
            }
        });
    }
}
/** @memo:stable */
class ArkChildComponent extends ArkStructBase<ArkChildComponent, ChildOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.fontSize(50);
            }, undefined, 'Child');
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
        pass: initializers?.pass,
        count: initializers?.count,
        controller: initializers?.controller
    };
    ArkMyComponentComponent._instantiate(style, () => new ArkMyComponentComponent, content, updatedInitializers);
}
/** @memo */
export function Child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ChildOptions): void {
    const updatedInitializers: ChildOptions = {};
    ArkChildComponent._instantiate(style, () => new ArkChildComponent, content, updatedInitializers);
}
export interface MyComponentOptions {
    pass?: boolean;
    count?: number;
    controller?: TabsController;
}
export interface ChildOptions {
}
