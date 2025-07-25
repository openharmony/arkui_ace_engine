import { $r, $rawfile, AppStorage, AppStorageLinkState, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, StorageLinkState, SubscribedAbstractProperty, SwipeGesture, SwiperController, SyncedProperty, TabsController, TapGesture, TextAreaController, VideoController, animateTo, contextLocalStateOf, fp2px, getContext, getInspectorByKey, lpx2px, propState, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
/** @memo:stable */
class ArkStateToStateComponent extends ArkStructBase<ArkStateToStateComponent, StateToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToStateOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToPropComponent extends ArkStructBase<ArkStateToPropComponent, StateToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToPropOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StateToPropOptions | undefined): void {
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToProvideComponent extends ArkStructBase<ArkStateToProvideComponent, StateToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToProvideOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToStorageLinkComponent extends ArkStructBase<ArkStateToStorageLinkComponent, StateToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToStorageLinkOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToLocalStorageLinkComponent extends ArkStructBase<ArkStateToLocalStorageLinkComponent, StateToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToLocalStorageLinkOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToStoragePropComponent extends ArkStructBase<ArkStateToStoragePropComponent, StateToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToStoragePropOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StateToStoragePropOptions | undefined): void {
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToLocalStoragePropComponent extends ArkStructBase<ArkStateToLocalStoragePropComponent, StateToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToLocalStoragePropOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StateToLocalStoragePropOptions | undefined): void {
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStateToPlainComponent extends ArkStructBase<ArkStateToPlainComponent, StateToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StateToPlainOptions): void {
        this.__backing_state = stateOf<string>(initializers?.state ?? ('Hello World'), this);
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StateToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToStateComponent extends ArkStructBase<ArkPropToStateComponent, PropToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToStateOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToStateOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToPropComponent extends ArkStructBase<ArkPropToPropComponent, PropToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToPropOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToPropOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToProvideComponent extends ArkStructBase<ArkPropToProvideComponent, PropToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToProvideOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToProvideOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToStorageLinkComponent extends ArkStructBase<ArkPropToStorageLinkComponent, PropToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToStorageLinkOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToStorageLinkOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToLocalStorageLinkComponent extends ArkStructBase<ArkPropToLocalStorageLinkComponent, PropToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToLocalStorageLinkOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToLocalStorageLinkOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToStoragePropComponent extends ArkStructBase<ArkPropToStoragePropComponent, PropToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToStoragePropOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToStoragePropOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToLocalStoragePropComponent extends ArkStructBase<ArkPropToLocalStoragePropComponent, PropToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToLocalStoragePropOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PropToLocalStoragePropOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPropToPlainComponent extends ArkStructBase<ArkPropToPlainComponent, PropToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PropToPlainOptions): void {
        this.__backing_state = propState<string>('Hello World');
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __updateStruct(initializers: PropToPlainOptions | undefined): void {
        this.__backing_state?.update(initializers?.state);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PropToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToStateComponent extends ArkStructBase<ArkProvideToStateComponent, ProvideToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStateOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToPropComponent extends ArkStructBase<ArkProvideToPropComponent, ProvideToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToPropOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ProvideToPropOptions | undefined): void {
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToProvideComponent extends ArkStructBase<ArkProvideToProvideComponent, ProvideToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToProvideOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToStorageLinkComponent extends ArkStructBase<ArkProvideToStorageLinkComponent, ProvideToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStorageLinkOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToLocalStorageLinkComponent extends ArkStructBase<ArkProvideToLocalStorageLinkComponent, ProvideToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToLocalStorageLinkOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToStoragePropComponent extends ArkStructBase<ArkProvideToStoragePropComponent, ProvideToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStoragePropOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ProvideToStoragePropOptions | undefined): void {
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToLocalStoragePropComponent extends ArkStructBase<ArkProvideToLocalStoragePropComponent, ProvideToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToLocalStoragePropOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ProvideToLocalStoragePropOptions | undefined): void {
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkProvideToPlainComponent extends ArkStructBase<ArkProvideToPlainComponent, ProvideToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ProvideToPlainOptions): void {
        this.__backing_state = initializers!.__backing_state!;
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ProvideToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToStateComponent extends ArkStructBase<ArkStorageLinkToStateComponent, StorageLinkToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStateOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToPropComponent extends ArkStructBase<ArkStorageLinkToPropComponent, StorageLinkToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToPropOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StorageLinkToPropOptions | undefined): void {
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToProvideComponent extends ArkStructBase<ArkStorageLinkToProvideComponent, StorageLinkToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToProvideOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToStorageLinkComponent extends ArkStructBase<ArkStorageLinkToStorageLinkComponent, StorageLinkToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStorageLinkOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToLocalStorageLinkComponent extends ArkStructBase<ArkStorageLinkToLocalStorageLinkComponent, StorageLinkToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToLocalStorageLinkOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToStoragePropComponent extends ArkStructBase<ArkStorageLinkToStoragePropComponent, StorageLinkToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStoragePropOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StorageLinkToStoragePropOptions | undefined): void {
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToLocalStoragePropComponent extends ArkStructBase<ArkStorageLinkToLocalStoragePropComponent, StorageLinkToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToLocalStoragePropOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StorageLinkToLocalStoragePropOptions | undefined): void {
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStorageLinkToPlainComponent extends ArkStructBase<ArkStorageLinkToPlainComponent, StorageLinkToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToPlainOptions): void {
        this.__backing_state = AppStorageLinkState<string>("key", 'Hello World');
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StorageLinkToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToStateComponent extends ArkStructBase<ArkLocalStorageLinkToStateComponent, LocalStorageLinkToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStateOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToPropComponent extends ArkStructBase<ArkLocalStorageLinkToPropComponent, LocalStorageLinkToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToPropOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStorageLinkToPropOptions | undefined): void {
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToProvideComponent extends ArkStructBase<ArkLocalStorageLinkToProvideComponent, LocalStorageLinkToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToProvideOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToStorageLinkComponent extends ArkStructBase<ArkLocalStorageLinkToStorageLinkComponent, LocalStorageLinkToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStorageLinkOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToLocalStorageLinkComponent extends ArkStructBase<ArkLocalStorageLinkToLocalStorageLinkComponent, LocalStorageLinkToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToLocalStorageLinkOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToStoragePropComponent extends ArkStructBase<ArkLocalStorageLinkToStoragePropComponent, LocalStorageLinkToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStoragePropOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStorageLinkToStoragePropOptions | undefined): void {
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToLocalStoragePropComponent extends ArkStructBase<ArkLocalStorageLinkToLocalStoragePropComponent, LocalStorageLinkToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToLocalStoragePropOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStorageLinkToLocalStoragePropOptions | undefined): void {
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStorageLinkToPlainComponent extends ArkStructBase<ArkLocalStorageLinkToPlainComponent, LocalStorageLinkToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToPlainOptions): void {
        this.__backing_state = StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World');
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: MutableState<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageLinkToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToStateComponent extends ArkStructBase<ArkStoragePropToStateComponent, StoragePropToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStateOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToStateOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToPropComponent extends ArkStructBase<ArkStoragePropToPropComponent, StoragePropToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToPropOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToPropOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToProvideComponent extends ArkStructBase<ArkStoragePropToProvideComponent, StoragePropToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToProvideOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToProvideOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToStorageLinkComponent extends ArkStructBase<ArkStoragePropToStorageLinkComponent, StoragePropToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStorageLinkOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToStorageLinkOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToLocalStorageLinkComponent extends ArkStructBase<ArkStoragePropToLocalStorageLinkComponent, StoragePropToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToLocalStorageLinkOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToLocalStorageLinkOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToStoragePropComponent extends ArkStructBase<ArkStoragePropToStoragePropComponent, StoragePropToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStoragePropOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToStoragePropOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToLocalStoragePropComponent extends ArkStructBase<ArkStoragePropToLocalStoragePropComponent, StoragePropToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToLocalStoragePropOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToLocalStoragePropOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkStoragePropToPlainComponent extends ArkStructBase<ArkStoragePropToPlainComponent, StoragePropToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToPlainOptions): void {
        this.__backing_state = propState<string>(AppStorageLinkState<string>("key", 'Hello World').value);
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __updateStruct(initializers: StoragePropToPlainOptions | undefined): void {
        this.__backing_state?.update(AppStorageLinkState<string>("key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: StoragePropToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToStateComponent extends ArkStructBase<ArkLocalStoragePropToStateComponent, LocalStoragePropToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStateOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToStateOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToPropComponent extends ArkStructBase<ArkLocalStoragePropToPropComponent, LocalStoragePropToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToPropOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToPropOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToProvideComponent extends ArkStructBase<ArkLocalStoragePropToProvideComponent, LocalStoragePropToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToProvideOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToProvideOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToStorageLinkComponent extends ArkStructBase<ArkLocalStoragePropToStorageLinkComponent, LocalStoragePropToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStorageLinkOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToStorageLinkOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToLocalStorageLinkComponent extends ArkStructBase<ArkLocalStoragePropToLocalStorageLinkComponent, LocalStoragePropToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToLocalStorageLinkOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToLocalStorageLinkOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToStoragePropComponent extends ArkStructBase<ArkLocalStoragePropToStoragePropComponent, LocalStoragePropToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStoragePropOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToStoragePropOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToLocalStoragePropComponent extends ArkStructBase<ArkLocalStoragePropToLocalStoragePropComponent, LocalStoragePropToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToLocalStoragePropOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToLocalStoragePropOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkLocalStoragePropToPlainComponent extends ArkStructBase<ArkLocalStoragePropToPlainComponent, LocalStoragePropToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToPlainOptions): void {
        this.__backing_state = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: SyncedProperty<string>;
    private get state(): string {
        return this.__backing_state!.value;
    }
    private set state(value: string) {
        this.__backing_state!.value = observableProxy(value);
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropToPlainOptions | undefined): void {
        this.__backing_state?.update(StorageLinkState<string>(this._entry_local_storage_, "key", 'Hello World').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkBuilderToBuilderParamComponent extends ArkStructBase<ArkBuilderToBuilderParamComponent, BuilderToBuilderParamOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuilderToBuilderParamOptions): void {
        this.__backing_builderParam = initializers?.builderParam ?? (/**/
        /** @memo */
        () => {
            this.builder();
        });
        this.__backing_anotherParam = initializers?.anotherParam ?? (/**/
        /** @memo */
        () => {
            this.builder();
        });
        if (this.__backing_builderParam === undefined && content !== undefined)
            this.__backing_builderParam = content;
    }
    /** @memo */
    private __backing_builderParam?: () => void;
    /** @memo */
    private get builderParam(): () => void {
        return this.__backing_builderParam!;
    }
    private set builderParam(/**/
    /** @memo */
    value: () => void) {
        this.__backing_builderParam = value;
    }
    /** @memo */
    private __backing_anotherParam?: () => void;
    /** @memo */
    private get anotherParam(): () => void {
        return this.__backing_anotherParam!;
    }
    private set anotherParam(/**/
    /** @memo */
    value: () => void) {
        this.__backing_anotherParam = value;
    }
    /** @memo */
    builder() { }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuilderToBuilderParamOptions) {
        this.builderParam();
        BuilderToBuilderParam(undefined, undefined, { builderParam: this.anotherParam } as BuilderToBuilderParamOptions);
    }
}
/** @memo:stable */
class ArkBuilderParamToBuilderParamComponent extends ArkStructBase<ArkBuilderParamToBuilderParamComponent, BuilderParamToBuilderParamOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BuilderParamToBuilderParamOptions): void {
        this.__backing_builderParam = initializers?.builderParam ?? (/**/
        /** @memo */
        () => {
            this.builder();
        });
        this.__backing_anotherParam = initializers?.anotherParam ?? (/**/
        /** @memo */
        () => {
            this.builderParam();
        });
        if (this.__backing_builderParam === undefined && content !== undefined)
            this.__backing_builderParam = content;
    }
    /** @memo */
    private __backing_builderParam?: () => void;
    /** @memo */
    private get builderParam(): () => void {
        return this.__backing_builderParam!;
    }
    private set builderParam(/**/
    /** @memo */
    value: () => void) {
        this.__backing_builderParam = value;
    }
    /** @memo */
    private __backing_anotherParam?: () => void;
    /** @memo */
    private get anotherParam(): () => void {
        return this.__backing_anotherParam!;
    }
    private set anotherParam(/**/
    /** @memo */
    value: () => void) {
        this.__backing_anotherParam = value;
    }
    /** @memo */
    builder() { }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BuilderParamToBuilderParamOptions) {
        this.anotherBuilderParam();
        BuilderToBuilderParam(undefined, undefined, { anotherParam: this.anotherParam } as BuilderToBuilderParamOptions);
    }
}
/** @memo:stable */
class ArkPlainToStateComponent extends ArkStructBase<ArkPlainToStateComponent, PlainToStateOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToStateOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = stateOf<string>(initializers?.test ?? (this.state + "!"), this);
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToStateOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToPropComponent extends ArkStructBase<ArkPlainToPropComponent, PlainToPropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToPropOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = propState<string>(this.state + "!");
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PlainToPropOptions | undefined): void {
        this.__backing_test?.update(initializers?.test);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToPropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToProvideComponent extends ArkStructBase<ArkPlainToProvideComponent, PlainToProvideOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToProvideOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = initializers!.__backing_test!;
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToProvideOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToStorageLinkComponent extends ArkStructBase<ArkPlainToStorageLinkComponent, PlainToStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToStorageLinkOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = AppStorageLinkState<string>("test", this.state + "!");
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToLocalStorageLinkComponent extends ArkStructBase<ArkPlainToLocalStorageLinkComponent, PlainToLocalStorageLinkOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToLocalStorageLinkOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!");
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: MutableState<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToLocalStorageLinkOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToStoragePropComponent extends ArkStructBase<ArkPlainToStoragePropComponent, PlainToStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToStoragePropOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = propState<string>(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PlainToStoragePropOptions | undefined): void {
        this.__backing_test?.update(AppStorageLinkState<string>("test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToLocalStoragePropComponent extends ArkStructBase<ArkPlainToLocalStoragePropComponent, PlainToLocalStoragePropOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToLocalStoragePropOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: SyncedProperty<string>;
    private get test(): string {
        return this.__backing_test!.value;
    }
    private set test(value: string) {
        this.__backing_test!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: PlainToLocalStoragePropOptions | undefined): void {
        this.__backing_test?.update(StorageLinkState<string>(this._entry_local_storage_, "test", this.state + "!").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToLocalStoragePropOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo:stable */
class ArkPlainToPlainComponent extends ArkStructBase<ArkPlainToPlainComponent, PlainToPlainOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: PlainToPlainOptions): void {
        this.__backing_state = initializers?.state ?? ('Hello World');
        this.__backing_test = initializers?.test ?? (this.state + "!");
    }
    private __backing_state?: string;
    private get state(): string {
        return this.__backing_state as string;
    }
    private set state(value: string) {
        this.__backing_state = value;
    }
    private __backing_test?: string;
    private get test(): string {
        return this.__backing_test as string;
    }
    private set test(value: string) {
        this.__backing_test = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: PlainToPlainOptions) {
        ArkText(__builder, undefined, this.test);
    }
}
/** @memo */
export function StateToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToStateOptions): void {
    const updatedInitializers: StateToStateOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToStateComponent._instantiate(style, () => new ArkStateToStateComponent, content, updatedInitializers);
}
/** @memo */
export function StateToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToPropOptions): void {
    const updatedInitializers: StateToPropOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToPropComponent._instantiate(style, () => new ArkStateToPropComponent, content, updatedInitializers);
}
/** @memo */
export function StateToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: StateToProvideOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkStateToProvideComponent._instantiate(style, () => new ArkStateToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function StateToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToStorageLinkOptions): void {
    const updatedInitializers: StateToStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToStorageLinkComponent._instantiate(style, () => new ArkStateToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StateToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToLocalStorageLinkOptions): void {
    const updatedInitializers: StateToLocalStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToLocalStorageLinkComponent._instantiate(style, () => new ArkStateToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StateToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToStoragePropOptions): void {
    const updatedInitializers: StateToStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToStoragePropComponent._instantiate(style, () => new ArkStateToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StateToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToLocalStoragePropOptions): void {
    const updatedInitializers: StateToLocalStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStateToLocalStoragePropComponent._instantiate(style, () => new ArkStateToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StateToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StateToPlainOptions): void {
    const updatedInitializers: StateToPlainOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkStateToPlainComponent._instantiate(style, () => new ArkStateToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function PropToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToStateOptions): void {
    const updatedInitializers: PropToStateOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToStateComponent._instantiate(style, () => new ArkPropToStateComponent, content, updatedInitializers);
}
/** @memo */
export function PropToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToPropOptions): void {
    const updatedInitializers: PropToPropOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToPropComponent._instantiate(style, () => new ArkPropToPropComponent, content, updatedInitializers);
}
/** @memo */
export function PropToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: PropToProvideOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkPropToProvideComponent._instantiate(style, () => new ArkPropToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function PropToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToStorageLinkOptions): void {
    const updatedInitializers: PropToStorageLinkOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToStorageLinkComponent._instantiate(style, () => new ArkPropToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function PropToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToLocalStorageLinkOptions): void {
    const updatedInitializers: PropToLocalStorageLinkOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToLocalStorageLinkComponent._instantiate(style, () => new ArkPropToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function PropToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToStoragePropOptions): void {
    const updatedInitializers: PropToStoragePropOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToStoragePropComponent._instantiate(style, () => new ArkPropToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function PropToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToLocalStoragePropOptions): void {
    const updatedInitializers: PropToLocalStoragePropOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkPropToLocalStoragePropComponent._instantiate(style, () => new ArkPropToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function PropToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PropToPlainOptions): void {
    const updatedInitializers: PropToPlainOptions = {
        state: initializers?.state,
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkPropToPlainComponent._instantiate(style, () => new ArkPropToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToStateOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToStateOptions = {
        __backing_state: __provide_state,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToStateComponent._instantiate(style, () => new ArkProvideToStateComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToPropOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToPropOptions = {
        __backing_state: __provide_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToPropComponent._instantiate(style, () => new ArkProvideToPropComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToProvideOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: ProvideToProvideOptions = {
        __backing_state: __provide_state,
        __backing_test: __provide_test
    };
    ArkProvideToProvideComponent._instantiate(style, () => new ArkProvideToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToStorageLinkOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToStorageLinkOptions = {
        __backing_state: __provide_state,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToStorageLinkComponent._instantiate(style, () => new ArkProvideToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToLocalStorageLinkOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToLocalStorageLinkOptions = {
        __backing_state: __provide_state,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToLocalStorageLinkComponent._instantiate(style, () => new ArkProvideToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToStoragePropOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToStoragePropOptions = {
        __backing_state: __provide_state,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToStoragePropComponent._instantiate(style, () => new ArkProvideToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToLocalStoragePropOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToLocalStoragePropOptions = {
        __backing_state: __provide_state,
        __backing_test: initializers?.__backing_test
    };
    ArkProvideToLocalStoragePropComponent._instantiate(style, () => new ArkProvideToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function ProvideToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ProvideToPlainOptions): void {
    const __provide_state = contextLocalStateOf<string>("state", () => 'Hello World');
    const updatedInitializers: ProvideToPlainOptions = {
        __backing_state: __provide_state,
        test: initializers?.test
    };
    ArkProvideToPlainComponent._instantiate(style, () => new ArkProvideToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToStateOptions): void {
    const updatedInitializers: StorageLinkToStateOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToStateComponent._instantiate(style, () => new ArkStorageLinkToStateComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToPropOptions): void {
    const updatedInitializers: StorageLinkToPropOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToPropComponent._instantiate(style, () => new ArkStorageLinkToPropComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: StorageLinkToProvideOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkStorageLinkToProvideComponent._instantiate(style, () => new ArkStorageLinkToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToStorageLinkOptions): void {
    const updatedInitializers: StorageLinkToStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToStorageLinkComponent._instantiate(style, () => new ArkStorageLinkToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToLocalStorageLinkOptions): void {
    const updatedInitializers: StorageLinkToLocalStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToLocalStorageLinkComponent._instantiate(style, () => new ArkStorageLinkToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToStoragePropOptions): void {
    const updatedInitializers: StorageLinkToStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToStoragePropComponent._instantiate(style, () => new ArkStorageLinkToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToLocalStoragePropOptions): void {
    const updatedInitializers: StorageLinkToLocalStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStorageLinkToLocalStoragePropComponent._instantiate(style, () => new ArkStorageLinkToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StorageLinkToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StorageLinkToPlainOptions): void {
    const updatedInitializers: StorageLinkToPlainOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkStorageLinkToPlainComponent._instantiate(style, () => new ArkStorageLinkToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToStateOptions): void {
    const updatedInitializers: LocalStorageLinkToStateOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToStateComponent._instantiate(style, () => new ArkLocalStorageLinkToStateComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToPropOptions): void {
    const updatedInitializers: LocalStorageLinkToPropOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToPropComponent._instantiate(style, () => new ArkLocalStorageLinkToPropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: LocalStorageLinkToProvideOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkLocalStorageLinkToProvideComponent._instantiate(style, () => new ArkLocalStorageLinkToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToStorageLinkOptions): void {
    const updatedInitializers: LocalStorageLinkToStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToStorageLinkComponent._instantiate(style, () => new ArkLocalStorageLinkToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToLocalStorageLinkOptions): void {
    const updatedInitializers: LocalStorageLinkToLocalStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToLocalStorageLinkComponent._instantiate(style, () => new ArkLocalStorageLinkToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToStoragePropOptions): void {
    const updatedInitializers: LocalStorageLinkToStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToStoragePropComponent._instantiate(style, () => new ArkLocalStorageLinkToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToLocalStoragePropOptions): void {
    const updatedInitializers: LocalStorageLinkToLocalStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStorageLinkToLocalStoragePropComponent._instantiate(style, () => new ArkLocalStorageLinkToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStorageLinkToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageLinkToPlainOptions): void {
    const updatedInitializers: LocalStorageLinkToPlainOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkLocalStorageLinkToPlainComponent._instantiate(style, () => new ArkLocalStorageLinkToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToStateOptions): void {
    const updatedInitializers: StoragePropToStateOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToStateComponent._instantiate(style, () => new ArkStoragePropToStateComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToPropOptions): void {
    const updatedInitializers: StoragePropToPropOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToPropComponent._instantiate(style, () => new ArkStoragePropToPropComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: StoragePropToProvideOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkStoragePropToProvideComponent._instantiate(style, () => new ArkStoragePropToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToStorageLinkOptions): void {
    const updatedInitializers: StoragePropToStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToStorageLinkComponent._instantiate(style, () => new ArkStoragePropToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToLocalStorageLinkOptions): void {
    const updatedInitializers: StoragePropToLocalStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToLocalStorageLinkComponent._instantiate(style, () => new ArkStoragePropToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToStoragePropOptions): void {
    const updatedInitializers: StoragePropToStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToStoragePropComponent._instantiate(style, () => new ArkStoragePropToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToLocalStoragePropOptions): void {
    const updatedInitializers: StoragePropToLocalStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkStoragePropToLocalStoragePropComponent._instantiate(style, () => new ArkStoragePropToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function StoragePropToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: StoragePropToPlainOptions): void {
    const updatedInitializers: StoragePropToPlainOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkStoragePropToPlainComponent._instantiate(style, () => new ArkStoragePropToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToStateOptions): void {
    const updatedInitializers: LocalStoragePropToStateOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToStateComponent._instantiate(style, () => new ArkLocalStoragePropToStateComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToPropOptions): void {
    const updatedInitializers: LocalStoragePropToPropOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToPropComponent._instantiate(style, () => new ArkLocalStoragePropToPropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: LocalStoragePropToProvideOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: __provide_test
    };
    ArkLocalStoragePropToProvideComponent._instantiate(style, () => new ArkLocalStoragePropToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToStorageLinkOptions): void {
    const updatedInitializers: LocalStoragePropToStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToStorageLinkComponent._instantiate(style, () => new ArkLocalStoragePropToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToLocalStorageLinkOptions): void {
    const updatedInitializers: LocalStoragePropToLocalStorageLinkOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToLocalStorageLinkComponent._instantiate(style, () => new ArkLocalStoragePropToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToStoragePropOptions): void {
    const updatedInitializers: LocalStoragePropToStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToStoragePropComponent._instantiate(style, () => new ArkLocalStoragePropToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToLocalStoragePropOptions): void {
    const updatedInitializers: LocalStoragePropToLocalStoragePropOptions = {
        __backing_state: initializers?.__backing_state,
        __backing_test: initializers?.__backing_test
    };
    ArkLocalStoragePropToLocalStoragePropComponent._instantiate(style, () => new ArkLocalStoragePropToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function LocalStoragePropToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropToPlainOptions): void {
    const updatedInitializers: LocalStoragePropToPlainOptions = {
        __backing_state: initializers?.__backing_state,
        test: initializers?.test
    };
    ArkLocalStoragePropToPlainComponent._instantiate(style, () => new ArkLocalStoragePropToPlainComponent, content, updatedInitializers);
}
/** @memo */
export function BuilderToBuilderParam(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuilderToBuilderParamOptions): void {
    const updatedInitializers: BuilderToBuilderParamOptions = {
        builderParam: initializers?.builderParam,
        anotherParam: initializers?.anotherParam
    };
    ArkBuilderToBuilderParamComponent._instantiate(style, () => new ArkBuilderToBuilderParamComponent, content, updatedInitializers);
}
/** @memo */
export function BuilderParamToBuilderParam(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BuilderParamToBuilderParamOptions): void {
    const updatedInitializers: BuilderParamToBuilderParamOptions = {
        builderParam: initializers?.builderParam,
        anotherParam: initializers?.anotherParam
    };
    ArkBuilderParamToBuilderParamComponent._instantiate(style, () => new ArkBuilderParamToBuilderParamComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToState(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToStateOptions): void {
    const updatedInitializers: PlainToStateOptions = {
        state: initializers?.state,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToStateComponent._instantiate(style, () => new ArkPlainToStateComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToPropOptions): void {
    const updatedInitializers: PlainToPropOptions = {
        state: initializers?.state,
        test: initializers?.test,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToPropComponent._instantiate(style, () => new ArkPlainToPropComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToProvide(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToProvideOptions): void {
    const __provide_test = contextLocalStateOf<string>("test", () => this.state + "!");
    const updatedInitializers: PlainToProvideOptions = {
        state: initializers?.state,
        __backing_test: __provide_test
    };
    ArkPlainToProvideComponent._instantiate(style, () => new ArkPlainToProvideComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToStorageLinkOptions): void {
    const updatedInitializers: PlainToStorageLinkOptions = {
        state: initializers?.state,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToStorageLinkComponent._instantiate(style, () => new ArkPlainToStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToLocalStorageLink(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToLocalStorageLinkOptions): void {
    const updatedInitializers: PlainToLocalStorageLinkOptions = {
        state: initializers?.state,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToLocalStorageLinkComponent._instantiate(style, () => new ArkPlainToLocalStorageLinkComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToStoragePropOptions): void {
    const updatedInitializers: PlainToStoragePropOptions = {
        state: initializers?.state,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToStoragePropComponent._instantiate(style, () => new ArkPlainToStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToLocalStorageProp(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToLocalStoragePropOptions): void {
    const updatedInitializers: PlainToLocalStoragePropOptions = {
        state: initializers?.state,
        __backing_test: initializers?.__backing_test
    };
    ArkPlainToLocalStoragePropComponent._instantiate(style, () => new ArkPlainToLocalStoragePropComponent, content, updatedInitializers);
}
/** @memo */
export function PlainToPlain(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: PlainToPlainOptions): void {
    const updatedInitializers: PlainToPlainOptions = {
        state: initializers?.state,
        test: initializers?.test
    };
    ArkPlainToPlainComponent._instantiate(style, () => new ArkPlainToPlainComponent, content, updatedInitializers);
}
export interface StateToStateOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StateToPropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StateToProvideOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StateToStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StateToLocalStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StateToStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StateToLocalStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StateToPlainOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    test?: string;
}
export interface PropToStateOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PropToPropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PropToProvideOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PropToStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PropToLocalStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PropToStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PropToLocalStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PropToPlainOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    test?: string;
}
export interface ProvideToStateOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface ProvideToPropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface ProvideToProvideOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface ProvideToStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface ProvideToLocalStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface ProvideToStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface ProvideToLocalStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface ProvideToPlainOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    test?: string;
}
export interface StorageLinkToStateOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StorageLinkToPropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StorageLinkToProvideOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StorageLinkToStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StorageLinkToLocalStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StorageLinkToStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StorageLinkToLocalStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StorageLinkToPlainOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    test?: string;
}
export interface LocalStorageLinkToStateOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStorageLinkToPropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStorageLinkToProvideOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStorageLinkToStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStorageLinkToLocalStorageLinkOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStorageLinkToStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStorageLinkToLocalStoragePropOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStorageLinkToPlainOptions {
    __backing_state?: MutableState<string>;
    state?: string;
    test?: string;
}
export interface StoragePropToStateOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StoragePropToPropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StoragePropToProvideOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StoragePropToStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StoragePropToLocalStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface StoragePropToStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StoragePropToLocalStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface StoragePropToPlainOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    test?: string;
}
export interface LocalStoragePropToStateOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStoragePropToPropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStoragePropToProvideOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStoragePropToStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStoragePropToLocalStorageLinkOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface LocalStoragePropToStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStoragePropToLocalStoragePropOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface LocalStoragePropToPlainOptions {
    __backing_state?: SyncedProperty<string>;
    state?: string;
    test?: string;
}
export interface BuilderToBuilderParamOptions {
    /** @memo */
    builderParam?: () => void;
    /** @memo */
    anotherParam?: () => void;
}
export interface BuilderParamToBuilderParamOptions {
    /** @memo */
    builderParam?: () => void;
    /** @memo */
    anotherParam?: () => void;
}
export interface PlainToStateOptions {
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PlainToPropOptions {
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PlainToProvideOptions {
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PlainToStorageLinkOptions {
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PlainToLocalStorageLinkOptions {
    state?: string;
    __backing_test?: MutableState<string>;
    test?: string;
}
export interface PlainToStoragePropOptions {
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PlainToLocalStoragePropOptions {
    state?: string;
    __backing_test?: SyncedProperty<string>;
    test?: string;
}
export interface PlainToPlainOptions {
    state?: string;
    test?: string;
}
