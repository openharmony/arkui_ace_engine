import { $$, AlphabetIndexerOptions, ArkAlphabetIndexer, ArkButton, ArkButtonComponent, ArkCheckbox, ArkCheckboxComponent, ArkCheckboxGroup, ArkCheckboxGroupComponent, ArkColumn, ArkCommonMethodComponent, ArkDatePicker, ArkDatePickerComponent, ArkGrid, ArkGridItem, ArkGridItemComponent, ArkList, ArkListItem, ArkListItemComponent, ArkListItemGroup, ArkMenuItem, ArkMenuItemComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkPanel, ArkPanelComponent, ArkRadio, ArkRadioComponent, ArkRefresh, ArkSearch, ArkSearchComponent, ArkSelect, ArkSelectComponent, ArkSideBarContainer, ArkSideBarContainerComponent, ArkSlider, ArkStepper, ArkStructBase, ArkSwiper, ArkSwiperComponent, ArkTabs, ArkText, ArkTextArea, ArkTextInput, ArkTextPicker, ArkTimePicker, ArkTimePickerComponent, ArkToggle, ArkToggleComponent, DatePickerOptions, GridItemOptions, ListItemOptions, ListItemStyle, PanelMode, RadioOptions, RefreshOptions, SearchOptions, SideBarContainerType, SliderOptions, StepperOptions, TabsOptions, TextAreaOptions, TextInputOptions, TextPickerOptions, TimePickerOptions, ToggleOptions, ToggleType, contextLocalStateOf, stateOf } from "@koalaui/arkts-arkui";
import { MutableState } from "@koalaui/runtime";
import { LocalStorage } from "@koalaui/arkui-common";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkDollarDollarComponent extends ArkStructBase<ArkDollarDollarComponent, DollarDollarOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: DollarDollarOptions): void {
        this.__backing_n = stateOf<number>(initializers?.n ?? (0.5), this);
        this.__backing_s = stateOf<string>(initializers?.s ?? ("0.5"), this);
        this.__backing_b = stateOf<boolean>(initializers?.b ?? (true), this);
        this.__backing_d = stateOf<Date>(initializers?.d ?? (new Date('2021-08-08')), this);
        this.__backing_m = stateOf<PanelMode>(initializers?.m ?? (PanelMode.Mini), this);
        this.__backing_l = stateOf<ListItemStyle>(initializers?.l ?? (ListItemStyle.NONE), this);
    }
    private __backing_n?: MutableState<number>;
    private get n(): number {
        return this.__backing_n!.value;
    }
    private set n(value: number) {
        this.__backing_n!.value = observableProxy(value);
    }
    private __backing_s?: MutableState<string>;
    private get s(): string {
        return this.__backing_s!.value;
    }
    private set s(value: string) {
        this.__backing_s!.value = observableProxy(value);
    }
    private __backing_b?: MutableState<boolean>;
    private get b(): boolean {
        return this.__backing_b!.value;
    }
    private set b(value: boolean) {
        this.__backing_b!.value = observableProxy(value);
    }
    private __backing_d?: MutableState<Date>;
    private get d(): Date {
        return this.__backing_d!.value;
    }
    private set d(value: Date) {
        this.__backing_d!.value = observableProxy(value);
    }
    private __backing_m?: MutableState<PanelMode>;
    private get m(): PanelMode {
        return this.__backing_m!.value;
    }
    private set m(value: PanelMode) {
        this.__backing_m!.value = observableProxy(value);
    }
    private __backing_l?: MutableState<ListItemStyle>;
    private get l(): ListItemStyle {
        return this.__backing_l!.value;
    }
    private set l(value: ListItemStyle) {
        this.__backing_l!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: DollarDollarOptions) {
        ArkColumn(__builder, () => {
            ArkSlider(undefined, undefined, { value: this.n } as SliderOptions);
            ArkToggle((__instance: ArkToggleComponent) => {
                __instance._onChangeEvent_isOn((isOn: boolean): void => { this.b = isOn; });
            }, undefined, { type: ToggleType.Switch, isOn: this.b } as ToggleOptions);
            ArkStepper(undefined, undefined, { index: this.n } as StepperOptions);
            ArkCheckbox((__instance: ArkCheckboxComponent) => {
                __instance.select(this.b);
            }, undefined);
            ArkCheckboxGroup((__instance: ArkCheckboxGroupComponent) => {
                __instance.selectAll(this.b);
            }, undefined);
            ArkDatePicker((__instance: ArkDatePickerComponent) => {
                __instance._onChangeEvent_selected((selected: Date): void => { this.d = selected; });
            }, undefined, { selected: this.d } as DatePickerOptions);
            ArkTimePicker((__instance: ArkTimePickerComponent) => {
                __instance._onChangeEvent_selected((selected: Date): void => { this.d = selected; });
            }, undefined, { selected: this.d } as TimePickerOptions);
            ArkMenuItem((__instance: ArkMenuItemComponent) => {
                __instance.selected(this.b);
            }, undefined);
            ArkPanel((__instance: ArkPanelComponent) => {
                __instance.mode(this.m);
            }, undefined, false);
            ArkRadio((__instance: ArkRadioComponent) => {
                __instance.checked(this.b);
            }, undefined, { group: "", value: "" } as RadioOptions);
            ArkSearch((__instance: ArkSearchComponent) => {
                __instance._onChangeEvent_value((value: string): void => { this.s = value; });
            }, undefined, { value: this.s } as SearchOptions);
            ArkSideBarContainer((__instance: ArkSideBarContainerComponent) => {
                __instance.showSideBar(this.b);
            }, undefined, SideBarContainerType.Embed);
            ArkSwiper((__instance: ArkSwiperComponent) => {
                __instance.index(this.n);
            }, undefined);
            ArkTabs(undefined, undefined, { index: this.n } as TabsOptions);
            ArkTextInput(undefined, undefined, { text: this.s } as TextInputOptions);
            ArkTextArea(undefined, undefined, { text: this.s } as TextAreaOptions);
            ArkTextInput(undefined, undefined, { text: this.s } as TextInputOptions);
            ArkToggle((__instance: ArkToggleComponent) => {
                __instance._onChangeEvent_isOn((isOn: boolean): void => { this.b = isOn; });
            }, undefined, { type: ToggleType.Checkbox, isOn: this.b } as ToggleOptions);
            ArkAlphabetIndexer(undefined, undefined, { arrayValue: [], selected: this.n } as AlphabetIndexerOptions);
            ArkRefresh(undefined, undefined, { refreshing: this.b } as RefreshOptions);
            ArkTextPicker(undefined, undefined, { range: [], value: this.s, selected: this.n } as TextPickerOptions);
            ArkSelect((__instance: ArkSelectComponent) => {
                __instance.value(this.s)
                    .selected(this.n);
            }, undefined, []);
            ArkList(undefined, () => {
                ArkListItemGroup(undefined, () => {
                    ArkListItem((__instance: ArkListItemComponent) => {
                        __instance.selected(this.b);
                    }, undefined, { style: this.l } as ListItemOptions);
                });
            });
            ArkGrid(undefined, () => {
                ArkGridItem((__instance: ArkGridItemComponent) => {
                    __instance.selected(this.b);
                }, undefined, {} as GridItemOptions);
            });
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.bindSheet(this.b, builder)
                    .bindContentCover(this.b, builder);
            }, undefined);
        });
    }
}
/** @memo */
function builder() {
    ArkText(undefined, undefined);
}
/** @memo */
export function DollarDollar(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: DollarDollarOptions): void {
    contextLocalStateOf("contextLocalMapOfRadioGroups", () => new Map<string, object>());
    contextLocalStateOf("contextLocalMapOfCheckboxGroups", () => new Map<string, object>());
    const updatedInitializers: DollarDollarOptions = {
        __backing_n: initializers?.__backing_n,
        __backing_s: initializers?.__backing_s,
        __backing_b: initializers?.__backing_b,
        __backing_d: initializers?.__backing_d,
        __backing_m: initializers?.__backing_m,
        __backing_l: initializers?.__backing_l
    };
    ArkDollarDollarComponent._instantiate(style, () => new ArkDollarDollarComponent, content, updatedInitializers);
}
export interface DollarDollarOptions {
    __backing_n?: MutableState<number>;
    n?: number;
    __backing_s?: MutableState<string>;
    s?: string;
    __backing_b?: MutableState<boolean>;
    b?: boolean;
    __backing_d?: MutableState<Date>;
    d?: Date;
    __backing_m?: MutableState<PanelMode>;
    m?: PanelMode;
    __backing_l?: MutableState<ListItemStyle>;
    l?: ListItemStyle;
}
