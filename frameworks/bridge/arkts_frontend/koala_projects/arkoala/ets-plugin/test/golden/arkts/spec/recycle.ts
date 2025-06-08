import { ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkFlex, ArkFlexComponent, ArkListItem, ArkListItemComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkReusableStruct, ArkStructBase, ArkTabContent, ArkTabContentComponent, ArkTabs, ArkTabsComponent, ArkText, ArkTextComponent, BarPosition, Color, SyncedProperty, TabsController, TabsOptions, propState, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkHomeComponentComponent extends ArkStructBase<ArkHomeComponentComponent, HomeComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions): void {
        this.__backing_state_value = stateOf<string>(initializers?.state_value ?? ("100%"), this);
        this.__backing_value = stateOf<number>(initializers?.value ?? (1), this);
    }
    private __backing_state_value?: MutableState<string>;
    private get state_value(): string {
        return this.__backing_state_value!.value;
    }
    private set state_value(value: string) {
        this.__backing_state_value!.value = observableProxy(value);
    }
    private __backing_value?: MutableState<number>;
    private get value(): number {
        return this.__backing_value!.value;
    }
    private set value(value: number) {
        this.__backing_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: HomeComponentOptions) {
        ArkColumn(__instance => {
            {
                __instance.width(this.state_value)
                    .height(100);
            }
            __builder?.(__instance);
        }, () => {
            child((__instance: ArkCommonMethodComponent) => {
                __instance.border({ width: 3, color: Color.Red })
                    .width(this.state_value);
            }, undefined, { propvalue: this.value, linkvalue: this.value } as childOptions);
            ArkText((__instance: ArkTextComponent) => {
                __instance.width(this.state_value)
                    .height(100);
            }, undefined, "aa");
        });
    }
}
/** @memo:stable */
class ArkchildComponent extends ArkReusableStruct<ArkchildComponent, childOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: childOptions): void {
        this.__backing_propvalue = propState<number>();
        this.__backing_linkvalue = initializers!.__backing_linkvalue!;
        this.__backing_state_value = stateOf<number>(initializers?.state_value ?? (1), this);
        this.__backing_width_value = stateOf<string>(initializers?.width_value ?? ("100%"), this);
        this.__backing_reguar_value = initializers?.reguar_value ?? (50);
        this.__backing_controller = initializers?.controller ?? (new TabsController());
        this.__backing_heightValue = stateOf<number>(initializers?.heightValue ?? (100), this);
    }
    private __backing_propvalue?: SyncedProperty<number>;
    private get propvalue(): number {
        return this.__backing_propvalue!.value;
    }
    private set propvalue(value: number) {
        this.__backing_propvalue!.value = observableProxy(value);
    }
    private __backing_linkvalue?: MutableState<number>;
    private get linkvalue(): number {
        return this.__backing_linkvalue!.value;
    }
    private set linkvalue(value: number) {
        this.__backing_linkvalue!.value = observableProxy(value);
    }
    private __backing_state_value?: MutableState<number>;
    private get state_value(): number {
        return this.__backing_state_value!.value;
    }
    private set state_value(value: number) {
        this.__backing_state_value!.value = observableProxy(value);
    }
    private __backing_width_value?: MutableState<string>;
    private get width_value(): string {
        return this.__backing_width_value!.value;
    }
    private set width_value(value: string) {
        this.__backing_width_value!.value = observableProxy(value);
    }
    private __backing_reguar_value?: number;
    private get reguar_value(): number {
        return this.__backing_reguar_value as number;
    }
    private set reguar_value(value: number) {
        this.__backing_reguar_value = value;
    }
    private __backing_controller?: TabsController;
    private get controller(): TabsController {
        return this.__backing_controller as TabsController;
    }
    private set controller(value: TabsController) {
        this.__backing_controller = value;
    }
    private __backing_heightValue?: MutableState<number>;
    private get heightValue(): number {
        return this.__backing_heightValue!.value;
    }
    private set heightValue(value: number) {
        this.__backing_heightValue!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: childOptions | undefined): void {
        this.__backing_propvalue?.update(initializers?.propvalue);
    }
    __rebindStates(initializers?: childOptions): void {
        this.__backing_propvalue?.update(initializers?.propvalue);
        this.__backing_linkvalue = initializers!.__backing_linkvalue!;
        if (initializers?.state_value)
            this.state_value = initializers!.state_value!;
        if (initializers?.width_value)
            this.width_value = initializers!.width_value!;
        if (initializers?.heightValue)
            this.heightValue = initializers!.heightValue!;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: childOptions) {
        ArkColumn(__builder, () => {
            AnimationTest((__instance: ArkCommonMethodComponent) => {
                __instance.border({ width: 3, color: Color.Red })
                    .height(this.heightValue);
            }, undefined);
            ArkText((__instance: ArkTextComponent) => {
                __instance.width(this.propvalue)
                    .fontSize(this.reguar_value)
                    .height(100)
                    .fontColor(Color.Red)
                    .border({ width: this.propvalue, color: Color.Red, radius: 100 });
            }, undefined, "hello");
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.border({ width: this.reguar_value, color: Color.Red, radius: 100 });
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.fontSize(this.state_value)
                        .width(100);
                }, undefined, "hhhhhhhhhhhhh");
            });
            ArkListItem((__instance: ArkListItemComponent) => {
                __instance.width(this.width_value)
                    .height(100);
            }, () => {
                ArkText((__instance: ArkTextComponent) => {
                    __instance.width(this.width_value)
                        .height(100);
                }, undefined, 'ListItem');
            }, 'true');
            ArkListItem((__instance: ArkListItemComponent) => {
                __instance.width(this.width_value)
                    .height(100);
            }, undefined, 'true');
            ArkTabs((__instance: ArkTabsComponent) => {
                __instance.width(this.width_value)
                    .height(100);
            }, () => {
                ArkTabContent((__instance: ArkTabContentComponent) => {
                    __instance.tabBar("TabBar")
                        .width(this.width_value)
                        .height(100);
                }, () => {
                    ArkFlex((__instance: ArkFlexComponent) => {
                        __instance.width(this.width_value)
                            .height(100);
                    }, () => {
                        ArkColumn((__instance: ArkColumnComponent) => {
                            __instance.width(this.width_value)
                                .height(100);
                        }, () => {
                            ArkText((__instance: ArkTextComponent) => {
                                __instance.width(this.width_value)
                                    .height(100);
                            }, undefined, 'text1');
                        });
                    });
                });
                ArkTabContent((__instance: ArkTabContentComponent) => {
                    __instance.tabBar("TabBar 2")
                        .width(this.width_value)
                        .height(100);
                }, () => {
                    ArkText((__instance: ArkTextComponent) => {
                        __instance.width(this.width_value)
                            .height(100);
                    }, undefined, 'text2');
                });
                ArkTabContent((__instance: ArkTabContentComponent) => {
                    __instance.width(this.width_value)
                        .height(100);
                }, undefined);
            }, { barPosition: BarPosition.Start, index: 1, controller: this.controller } as TabsOptions);
        });
    }
}
/** @memo:stable */
class ArkNormalComponentComponent extends ArkStructBase<ArkNormalComponentComponent, NormalComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: NormalComponentOptions): void {
        this.__backing_width_value = stateOf<string>(initializers?.width_value ?? ("100%"), this);
    }
    private __backing_width_value?: MutableState<string>;
    private get width_value(): string {
        return this.__backing_width_value!.value;
    }
    private set width_value(value: string) {
        this.__backing_width_value!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: NormalComponentOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.width(this.width_value)
                    .height(100);
            }, undefined, "hello");
        });
    }
}
/** @memo:stable */
class ArkAnimationTestComponent extends ArkReusableStruct<ArkAnimationTestComponent, AnimationTestOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: AnimationTestOptions): void {
        this.__backing_width_value = stateOf<string>(initializers?.width_value ?? ("100%"), this);
    }
    private __backing_width_value?: MutableState<string>;
    private get width_value(): string {
        return this.__backing_width_value!.value;
    }
    private set width_value(value: string) {
        this.__backing_width_value!.value = observableProxy(value);
    }
    override __toRecord(initializers: Object): Record<string, Object> {
        const _optionData = initializers as AnimationTestOptions;
        return { "width_value": _optionData.__backing_width_value?.value ?? (new Object()) };
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: AnimationTestOptions) {
        ArkColumn(__builder, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.animationStart({ duration: 300 }).height(100)
                    .width(this.width_value).animationStop();
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
        __backing_state_value: initializers?.__backing_state_value,
        __backing_value: initializers?.__backing_value
    };
    ArkHomeComponentComponent._instantiate(style, () => new ArkHomeComponentComponent, content, updatedInitializers);
}
/** @memo */
export function child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: childOptions): void {
    const updatedInitializers: childOptions = {
        propvalue: initializers?.propvalue,
        __backing_propvalue: initializers?.__backing_propvalue,
        __backing_linkvalue: initializers?.__backing_linkvalue,
        __backing_state_value: initializers?.__backing_state_value,
        __backing_width_value: initializers?.__backing_width_value,
        reguar_value: initializers?.reguar_value,
        controller: initializers?.controller,
        __backing_heightValue: initializers?.__backing_heightValue
    };
    ArkchildComponent._instantiate(style, () => new ArkchildComponent, content, updatedInitializers, "ArkchildComponent");
}
/** @memo */
export function NormalComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: NormalComponentOptions): void {
    const updatedInitializers: NormalComponentOptions = {
        __backing_width_value: initializers?.__backing_width_value
    };
    ArkNormalComponentComponent._instantiate(style, () => new ArkNormalComponentComponent, content, updatedInitializers);
}
/** @memo */
export function AnimationTest(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: AnimationTestOptions): void {
    const updatedInitializers: AnimationTestOptions = {
        __backing_width_value: initializers?.__backing_width_value
    };
    ArkAnimationTestComponent._instantiate(style, () => new ArkAnimationTestComponent, content, updatedInitializers, "ArkAnimationTestComponent");
}
export interface HomeComponentOptions {
    __backing_state_value?: MutableState<string>;
    state_value?: string;
    __backing_value?: MutableState<number>;
    value?: number;
}
export interface childOptions {
    __backing_propvalue?: SyncedProperty<number>;
    propvalue?: number;
    __backing_linkvalue?: MutableState<number>;
    linkvalue?: number;
    __backing_state_value?: MutableState<number>;
    state_value?: number;
    __backing_width_value?: MutableState<string>;
    width_value?: string;
    reguar_value?: number;
    controller?: TabsController;
    __backing_heightValue?: MutableState<number>;
    heightValue?: number;
}
export interface NormalComponentOptions {
    __backing_width_value?: MutableState<string>;
    width_value?: string;
}
export interface AnimationTestOptions {
    __backing_width_value?: MutableState<string>;
    width_value?: string;
}
