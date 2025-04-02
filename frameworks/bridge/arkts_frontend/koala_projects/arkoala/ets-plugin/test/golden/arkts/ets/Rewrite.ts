import { AppStorageLinkState, ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkCommonMethodInterface, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, Color, CustomDialogController, DialogAlignment, SyncedProperty, bindCustomDialog, contextLocalStateOf, objectLinkState, propState, stateOf } from "@koalaui/arkts-arkui";
import { LocalStorage } from "@koalaui/arkui-common";
import { MutableState, OnChange, contextLocal } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
export class ArkEntryExampleComponent extends ArkStructBase<ArkEntryExampleComponent, EntryExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: EntryExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: EntryExampleOptions) { }
}
/** @memo:stable */
class ArkComponentExampleComponent extends ArkStructBase<ArkComponentExampleComponent, ComponentExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ComponentExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ComponentExampleOptions) { }
}
/** @memo:stable */
class ArkBuildExampleComponent extends ArkStructBase<ArkBuildExampleComponent, BuildExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuildExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuildExampleOptions) {
        ArkText(__instance => {
            {
                __instance.fontColor(Color.Red)
                    .width(100);
            }
            __builder?.(__instance);
        }, undefined, "message");
    }
}
/** @memo:stable */
class ArkStateExampleComponent extends ArkStructBase<ArkStateExampleComponent, StateExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateExampleOptions): void {
        this.__backing_x = stateOf<string>(initializers?.x ?? ("hello"), this);
    }
    private __backing_x?: MutableState<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkLinkExampleComponent extends ArkStructBase<ArkLinkExampleComponent, LinkExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LinkExampleOptions): void {
        this.__backing_x = initializers!.__backing_x!;
    }
    private __backing_x?: MutableState<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LinkExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkPropExampleComponent extends ArkStructBase<ArkPropExampleComponent, PropExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropExampleOptions): void {
        this.__backing_x = propState<string>();
    }
    private __backing_x?: SyncedProperty<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropExampleOptions | undefined): void {
        this.__backing_x?.update(initializers?.x);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkPropInitializedExampleComponent extends ArkStructBase<ArkPropInitializedExampleComponent, PropInitializedExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropInitializedExampleOptions): void {
        this.__backing_x = propState<string>("init");
    }
    private __backing_x?: SyncedProperty<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropInitializedExampleOptions | undefined): void {
        this.__backing_x?.update(initializers?.x);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropInitializedExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkProvideExampleComponent extends ArkStructBase<ArkProvideExampleComponent, ProvideExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideExampleOptions): void {
        this.__backing_x = initializers!.__backing_x!;
    }
    private __backing_x?: MutableState<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkConsumeExampleComponent extends ArkStructBase<ArkConsumeExampleComponent, ConsumeExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ConsumeExampleOptions): void {
        this.__backing_x = initializers!.__backing_x!;
    }
    private __backing_x?: MutableState<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ConsumeExampleOptions) {
        ArkText(__builder, undefined, this.x);
    }
}
/** @memo:stable */
class ArkBuilderExampleComponent extends ArkStructBase<ArkBuilderExampleComponent, BuilderExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuilderExampleOptions): void {
    }
    /** @memo */
    foo() {
        ArkText(undefined, undefined, "hello");
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuilderExampleOptions) {
        this.foo();
    }
}
/** @memo */
function bar() {
    ArkText(undefined, undefined, "hello");
}
/** @memo:stable */
class ArkGlobalBuilderExampleComponent extends ArkStructBase<ArkGlobalBuilderExampleComponent, GlobalBuilderExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: GlobalBuilderExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: GlobalBuilderExampleOptions) {
        bar();
    }
}
/** @memo:stable */
class ArkBuilderParamExampleComponent extends ArkStructBase<ArkBuilderParamExampleComponent, BuilderParamExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuilderParamExampleOptions): void {
        if (initializers?.foo) {
            this.__backing_foo = initializers?.foo;
        }
        if (this.__backing_foo === undefined && content !== undefined)
            this.__backing_foo = content;
    }
    /** @memo */
    private __backing_foo?: () => {};
    /** @memo */
    private get foo(): () => {} {
        return this.__backing_foo!;
    }
    private set foo(/**/
    /** @memo */
    value: () => {}) {
        this.__backing_foo = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuilderParamExampleOptions) {
        this.foo();
    }
}
/** @memo */
function looks<T extends ArkCommonMethodInterface<T>>(CommonInstance: T): T {
    return CommonInstance.height(500)
        .width(400)
        .backgroundColor(Color.Gray);
}
/** @memo:stable */
class ArkStylesExampleComponent extends ArkStructBase<ArkStylesExampleComponent, StylesExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StylesExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StylesExampleOptions) {
        ArkText(__instance => {
            {
                __instance.width(17).__applyStyle(looks);
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo:stable */
class ArkStylesMethodExampleComponent extends ArkStructBase<ArkStylesMethodExampleComponent, StylesMethodExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StylesMethodExampleOptions): void {
    }
    /** @memo */
    nice<T extends ArkCommonMethodInterface<T>>(CommonInstance: T): T {
        return CommonInstance.height(500)
            .width(400)
            .backgroundColor(Color.Gray);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StylesMethodExampleOptions) {
        ArkText(__instance => {
            {
                __instance.width(17).__applyStyle(this.nice.bind(this));
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo */
function clown__Column<T extends ArkColumnComponent>(ColumnInstance: T): T {
    return ColumnInstance.height(500)
        .width(400)
        .backgroundColor(Color.Gray);
}
/** @memo:stable */
class ArkExtendExampleComponent extends ArkStructBase<ArkExtendExampleComponent, ExtendExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ExtendExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ExtendExampleOptions) {
        ArkColumn(__instance => {
            {
                __instance.width(17).__applyStyle(clown__Column);
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo */
function attributeExtend__Text<T extends ArkTextComponent>(TextInstance: T, n: number, unused: string): T {
    return TextInstance.fontSize(n);
}
/** @memo:stable */
class ArkAnimatableExtendExampleComponent extends ArkStructBase<ArkAnimatableExtendExampleComponent, AnimatableExtendExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: AnimatableExtendExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: AnimatableExtendExampleOptions) {
        ArkText(__instance => {
            {
                __instance.width(17).__applyAnimatableExtend(attributeExtend__Text, 50, "unused");
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo:stable */
class ArkWatchExampleComponent extends ArkStructBase<ArkWatchExampleComponent, WatchExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: WatchExampleOptions): void {
        this.__backing_x = stateOf<string>(initializers?.x ?? ("hello"), this);
    }
    private __backing_x?: MutableState<string>;
    private get x(): string {
        return this.__backing_x!.value;
    }
    private set x(value: string) {
        this.__backing_x!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: WatchExampleOptions | undefined): void {
        OnChange(this.x, (_: string) => this.watchFunction("x"));
    }
    watchFunction() {
        console.log("Watch function");
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: WatchExampleOptions) {
    }
}
/** @memo:stable */
class ArkStorageLinkExampleComponent extends ArkStructBase<ArkStorageLinkExampleComponent, StorageLinkExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkExampleOptions): void {
        this.__backing_link = AppStorageLinkState<string>("storage", "Start");
    }
    private __backing_link?: MutableState<string>;
    private get link(): string {
        return this.__backing_link!.value;
    }
    private set link(value: string) {
        this.__backing_link!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkExampleOptions) {
    }
}
/** @memo:stable */
class ArkStoragePropExampleComponent extends ArkStructBase<ArkStoragePropExampleComponent, StoragePropExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropExampleOptions): void {
        this.__backing_prop = propState<string>(AppStorageLinkState<string>("storage", "Start").value);
    }
    private __backing_prop?: SyncedProperty<string>;
    private get prop(): string {
        return this.__backing_prop!.value;
    }
    private set prop(value: string) {
        this.__backing_prop!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropExampleOptions | undefined): void {
        this.__backing_prop?.update(AppStorageLinkState<string>("storage", "Start").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropExampleOptions) {
    }
}
/** @memo:stable */
class ArkCustomDialogExampleComponent extends ArkStructBase<ArkCustomDialogExampleComponent, CustomDialogExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogExampleOptions): void {
        if (initializers?.controller) {
            this.__backing_controller = initializers?.controller;
        }
    }
    private __backing_controller?: CustomDialogController;
    private get controller(): CustomDialogController {
        return this.__backing_controller as CustomDialogController;
    }
    private set controller(value: CustomDialogController) {
        this.__backing_controller = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogExampleOptions) {
    }
}
/** @memo:stable */
export class ArkCustomDialogControllerExampleComponent extends ArkStructBase<ArkCustomDialogControllerExampleComponent, CustomDialogControllerExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogControllerExampleOptions): void {
        this.__backing_dialogController = initializers?.dialogController ?? (new CustomDialogController({
            builder: CustomDialogExample(),
            autoCancel: true,
            alignment: DialogAlignment.Default,
            offset: { dx: 0, dy: 0 },
            gridCount: 4,
            customStyle: false
        }));
    }
    private __backing_dialogController?: CustomDialogController;
    private get dialogController(): CustomDialogController {
        return this.__backing_dialogController as CustomDialogController;
    }
    private set dialogController(value: CustomDialogController) {
        this.__backing_dialogController = value;
    }
    aboutToAppear() {
        this.dialogController.open();
    }
    aboutToDisappear() {
        this.dialogController.close();
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomDialogControllerExampleOptions) {
    }
}
// ObjectLink and Observed
class ObservedExample {
    private __backing_c?: MutableState<number>;
    public get c(): number {
        return this.__backing_c!.value;
    }
    public set c(value: number) {
        if (this.__backing_c)
            this.__backing_c!.value = observableProxy(value);
        else
            this.__backing_c = stateOf<number>(value);
    }
    constructor(c: number) {
        this.c = c;
    }
}
/** @memo:stable */
class ArkObjectLinkExampleComponent extends ArkStructBase<ArkObjectLinkExampleComponent, ObjectLinkExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ObjectLinkExampleOptions): void {
        this.__backing_a = objectLinkState<ObservedExample>();
    }
    private __backing_a?: SyncedProperty<ObservedExample>;
    private get a(): ObservedExample {
        return this.__backing_a!.value;
    }
    private set a(value: ObservedExample) {
        this.__backing_a!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ObjectLinkExampleOptions | undefined): void {
        this.__backing_a?.update(initializers?.a);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ObjectLinkExampleOptions) {
        ArkButton(__instance => {
            {
                __instance.onClick(() => {
                    this.a.c += 1;
                });
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo:stable */
class ArkObjectLinkExampleParentComponent extends ArkStructBase<ArkObjectLinkExampleParentComponent, ObjectLinkExampleParentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ObjectLinkExampleParentOptions): void {
        this.__backing_a = stateOf<ObservedExample[]>(initializers?.a ?? ([new ObservedExample(0), new ObservedExample(0)]), this);
    }
    private __backing_a?: MutableState<ObservedExample[]>;
    private get a(): ObservedExample[] {
        return this.__backing_a!.value;
    }
    private set a(value: ObservedExample[]) {
        this.__backing_a!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ObjectLinkExampleParentOptions) {
        ObjectLinkExample(__builder, undefined);
    }
}
/** @memo:stable */
class ArkPlainPropertyExampleComponent extends ArkStructBase<ArkPlainPropertyExampleComponent, PlainPropertyExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainPropertyExampleOptions): void {
        this.__backing_field = initializers?.field ?? (17);
    }
    private __backing_field?: number;
    private get field(): number {
        return this.__backing_field as number;
    }
    private set field(value: number) {
        this.__backing_field = value;
    }
}
/** @memo:stable */
class ArkCallExampleComponent extends ArkStructBase<ArkCallExampleComponent, CallExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CallExampleOptions): void {
        this.__backing_state = stateOf<number>(initializers?.state ?? (17), this);
    }
    private __backing_state?: MutableState<number>;
    private get state(): number {
        return this.__backing_state!.value;
    }
    private set state(value: number) {
        this.__backing_state!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CallExampleOptions) {
        Child(__builder, undefined, { __backing_counter: this.__backing_state } as ChildOptions);
    }
}
/** @memo:stable */
class ArkChildComponent extends ArkStructBase<ArkChildComponent, ChildOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions): void {
        this.__backing_counter = initializers!.__backing_counter!;
    }
    private __backing_counter?: MutableState<number>;
    private get counter(): number {
        return this.__backing_counter!.value;
    }
    private set counter(value: number) {
        this.__backing_counter!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ChildOptions) { }
}
/** @memo:stable */
class ArkBuilderPropagationExampleComponent extends ArkStructBase<ArkBuilderPropagationExampleComponent, BuilderPropagationExampleOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuilderPropagationExampleOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuilderPropagationExampleOptions) {
        ChildWithBuilder(__instance => {
            {
                __instance.width(100);
            }
            __builder?.(__instance);
        }, undefined);
    }
}
/** @memo:stable */
class ArkChildWithBuilderComponent extends ArkStructBase<ArkChildWithBuilderComponent, ChildWithBuilderOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ChildWithBuilderOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ChildWithBuilderOptions) {
        ArkColumn(__builder, undefined);
    }
}
/** @memo:stable */
class ArkStaticFieldComponent extends ArkStructBase<ArkStaticFieldComponent, StaticFieldOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StaticFieldOptions): void {
    }
    static x: number = 17;
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StaticFieldOptions) { }
}
/** @memo */
export function EntryExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: EntryExampleOptions): void {
    const updatedInitializers: EntryExampleOptions = {};
    ArkEntryExampleComponent._instantiate(style, () => new ArkEntryExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ComponentExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ComponentExampleOptions): void {
    const updatedInitializers: ComponentExampleOptions = {};
    ArkComponentExampleComponent._instantiate(style, () => new ArkComponentExampleComponent, content, updatedInitializers);
}
/** @memo */
export function BuildExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuildExampleOptions): void {
    const updatedInitializers: BuildExampleOptions = {};
    ArkBuildExampleComponent._instantiate(style, () => new ArkBuildExampleComponent, content, updatedInitializers);
}
/** @memo */
export function StateExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateExampleOptions): void {
    const updatedInitializers: StateExampleOptions = {
        __backing_x: initializers?.__backing_x
    };
    ArkStateExampleComponent._instantiate(style, () => new ArkStateExampleComponent, content, updatedInitializers);
}
/** @memo */
export function LinkExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LinkExampleOptions): void {
    const updatedInitializers: LinkExampleOptions = {
        __backing_x: initializers?.__backing_x
    };
    ArkLinkExampleComponent._instantiate(style, () => new ArkLinkExampleComponent, content, updatedInitializers);
}
/** @memo */
export function PropExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropExampleOptions): void {
    const updatedInitializers: PropExampleOptions = {
        x: initializers?.x,
        __backing_x: initializers?.__backing_x
    };
    ArkPropExampleComponent._instantiate(style, () => new ArkPropExampleComponent, content, updatedInitializers);
}
/** @memo */
export function PropInitializedExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropInitializedExampleOptions): void {
    const updatedInitializers: PropInitializedExampleOptions = {
        x: initializers?.x,
        __backing_x: initializers?.__backing_x
    };
    ArkPropInitializedExampleComponent._instantiate(style, () => new ArkPropInitializedExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideExampleOptions): void {
    const __provide_name = contextLocalStateOf<string>("name", () => "text");
    const updatedInitializers: ProvideExampleOptions = {
        __backing_x: __provide_name
    };
    ArkProvideExampleComponent._instantiate(style, () => new ArkProvideExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ConsumeExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ConsumeExampleOptions): void {
    const __consume_name = contextLocal<string>("name") as MutableState<string>;
    const updatedInitializers: ConsumeExampleOptions = {
        __backing_x: __consume_name
    };
    ArkConsumeExampleComponent._instantiate(style, () => new ArkConsumeExampleComponent, content, updatedInitializers);
}
/** @memo */
export function BuilderExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuilderExampleOptions): void {
    const updatedInitializers: BuilderExampleOptions = {};
    ArkBuilderExampleComponent._instantiate(style, () => new ArkBuilderExampleComponent, content, updatedInitializers);
}
/** @memo */
export function GlobalBuilderExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: GlobalBuilderExampleOptions): void {
    const updatedInitializers: GlobalBuilderExampleOptions = {};
    ArkGlobalBuilderExampleComponent._instantiate(style, () => new ArkGlobalBuilderExampleComponent, content, updatedInitializers);
}
/** @memo */
export function BuilderParamExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuilderParamExampleOptions): void {
    const updatedInitializers: BuilderParamExampleOptions = {
        foo: initializers?.foo
    };
    ArkBuilderParamExampleComponent._instantiate(style, () => new ArkBuilderParamExampleComponent, content, updatedInitializers);
}
/** @memo */
export function StylesExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StylesExampleOptions): void {
    const updatedInitializers: StylesExampleOptions = {};
    ArkStylesExampleComponent._instantiate(style, () => new ArkStylesExampleComponent, content, updatedInitializers);
}
/** @memo */
export function StylesMethodExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StylesMethodExampleOptions): void {
    const updatedInitializers: StylesMethodExampleOptions = {};
    ArkStylesMethodExampleComponent._instantiate(style, () => new ArkStylesMethodExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ExtendExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ExtendExampleOptions): void {
    const updatedInitializers: ExtendExampleOptions = {};
    ArkExtendExampleComponent._instantiate(style, () => new ArkExtendExampleComponent, content, updatedInitializers);
}
/** @memo */
export function AnimatableExtendExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: AnimatableExtendExampleOptions): void {
    const updatedInitializers: AnimatableExtendExampleOptions = {};
    ArkAnimatableExtendExampleComponent._instantiate(style, () => new ArkAnimatableExtendExampleComponent, content, updatedInitializers);
}
/** @memo */
export function WatchExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: WatchExampleOptions): void {
    const updatedInitializers: WatchExampleOptions = {
        __backing_x: initializers?.__backing_x
    };
    ArkWatchExampleComponent._instantiate(style, () => new ArkWatchExampleComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkExampleOptions): void {
    const updatedInitializers: StorageLinkExampleOptions = {
        __backing_link: initializers?.__backing_link
    };
    ArkStorageLinkExampleComponent._instantiate(style, () => new ArkStorageLinkExampleComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropExampleOptions): void {
    const updatedInitializers: StoragePropExampleOptions = {
        __backing_prop: initializers?.__backing_prop
    };
    ArkStoragePropExampleComponent._instantiate(style, () => new ArkStoragePropExampleComponent, content, updatedInitializers);
}
/** @memo */
export function CustomDialogExampleImpl(initializers?: CustomDialogExampleOptions): void {
    const updatedInitializers: CustomDialogExampleOptions = {
        controller: initializers?.controller
    };
    ArkCustomDialogExampleComponent._instantiate(undefined, () => new ArkCustomDialogExampleComponent, undefined, updatedInitializers);
}
export function CustomDialogExample(initializer: CustomDialogExampleOptions = {}) {
    return { build: bindCustomDialog(CustomDialogExampleImpl, initializer), buildOptions: initializer };
}
/** @memo */
export function CustomDialogControllerExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomDialogControllerExampleOptions): void {
    const updatedInitializers: CustomDialogControllerExampleOptions = {
        dialogController: initializers?.dialogController
    };
    ArkCustomDialogControllerExampleComponent._instantiate(style, () => new ArkCustomDialogControllerExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ObjectLinkExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ObjectLinkExampleOptions): void {
    const updatedInitializers: ObjectLinkExampleOptions = {
        a: initializers?.a,
        __backing_a: initializers?.__backing_a
    };
    ArkObjectLinkExampleComponent._instantiate(style, () => new ArkObjectLinkExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ObjectLinkExampleParent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ObjectLinkExampleParentOptions): void {
    const updatedInitializers: ObjectLinkExampleParentOptions = {
        __backing_a: initializers?.__backing_a
    };
    ArkObjectLinkExampleParentComponent._instantiate(style, () => new ArkObjectLinkExampleParentComponent, content, updatedInitializers);
}
/** @memo */
export function PlainPropertyExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainPropertyExampleOptions): void {
    const updatedInitializers: PlainPropertyExampleOptions = {
        field: initializers?.field
    };
    ArkPlainPropertyExampleComponent._instantiate(style, () => new ArkPlainPropertyExampleComponent, content, updatedInitializers);
}
/** @memo */
export function CallExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CallExampleOptions): void {
    const updatedInitializers: CallExampleOptions = {
        __backing_state: initializers?.__backing_state
    };
    ArkCallExampleComponent._instantiate(style, () => new ArkCallExampleComponent, content, updatedInitializers);
}
/** @memo */
export function Child(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ChildOptions): void {
    const updatedInitializers: ChildOptions = {
        __backing_counter: initializers?.__backing_counter
    };
    ArkChildComponent._instantiate(style, () => new ArkChildComponent, content, updatedInitializers);
}
/** @memo */
export function BuilderPropagationExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuilderPropagationExampleOptions): void {
    const updatedInitializers: BuilderPropagationExampleOptions = {};
    ArkBuilderPropagationExampleComponent._instantiate(style, () => new ArkBuilderPropagationExampleComponent, content, updatedInitializers);
}
/** @memo */
export function ChildWithBuilder(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ChildWithBuilderOptions): void {
    const updatedInitializers: ChildWithBuilderOptions = {};
    ArkChildWithBuilderComponent._instantiate(style, () => new ArkChildWithBuilderComponent, content, updatedInitializers);
}
/** @memo */
export function StaticField(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StaticFieldOptions): void {
    const updatedInitializers: StaticFieldOptions = {};
    ArkStaticFieldComponent._instantiate(style, () => new ArkStaticFieldComponent, content, updatedInitializers);
}
export interface EntryExampleOptions {
}
export interface ComponentExampleOptions {
}
export interface BuildExampleOptions {
}
export interface StateExampleOptions {
    __backing_x?: MutableState<string>;
    x?: string;
}
export interface LinkExampleOptions {
    __backing_x?: MutableState<string>;
    x?: string;
}
export interface PropExampleOptions {
    __backing_x?: SyncedProperty<string>;
    x?: string;
}
export interface PropInitializedExampleOptions {
    __backing_x?: SyncedProperty<string>;
    x?: string;
}
export interface ProvideExampleOptions {
    __backing_x?: MutableState<string>;
    x?: string;
}
export interface ConsumeExampleOptions {
    __backing_x?: MutableState<string>;
    x?: string;
}
export interface BuilderExampleOptions {
}
export interface GlobalBuilderExampleOptions {
}
export interface BuilderParamExampleOptions {
    /** @memo */
    foo?: () => {};
}
export interface StylesExampleOptions {
}
export interface StylesMethodExampleOptions {
}
export interface ExtendExampleOptions {
}
export interface AnimatableExtendExampleOptions {
}
export interface WatchExampleOptions {
    __backing_x?: MutableState<string>;
    x?: string;
}
export interface StorageLinkExampleOptions {
    __backing_link?: MutableState<string>;
    link?: string;
}
export interface StoragePropExampleOptions {
    __backing_prop?: SyncedProperty<string>;
    prop?: string;
}
export interface CustomDialogExampleOptions {
    controller?: CustomDialogController;
}
export interface CustomDialogControllerExampleOptions {
    dialogController?: CustomDialogController;
}
export interface ObjectLinkExampleOptions {
    __backing_a?: SyncedProperty<ObservedExample>;
    a?: ObservedExample;
}
export interface ObjectLinkExampleParentOptions {
    __backing_a?: MutableState<ObservedExample[]>;
    a?: ObservedExample[];
}
export interface PlainPropertyExampleOptions {
    field?: number;
}
export interface CallExampleOptions {
    __backing_state?: MutableState<number>;
    state?: number;
}
export interface ChildOptions {
    __backing_counter?: MutableState<number>;
    counter?: number;
}
export interface BuilderPropagationExampleOptions {
}
export interface ChildWithBuilderOptions {
}
export interface StaticFieldOptions {
}
