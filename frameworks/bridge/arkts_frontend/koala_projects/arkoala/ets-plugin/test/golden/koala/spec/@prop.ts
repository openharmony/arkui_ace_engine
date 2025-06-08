import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, SyncedProperty, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, propState, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { observableProxy } from "@koalaui/common";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo:stable */
class ArkCustomXComponent extends ArkStructBase<ArkCustomXComponent, CustomXOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomXOptions): void {
        this.__backing_fruit = propState<string>('香蕉');
    }
    private __backing_fruit?: SyncedProperty<string>;
    private get fruit(): string {
        return this.__backing_fruit!.value;
    }
    private set fruit(value: string) {
        this.__backing_fruit!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: CustomXOptions | undefined): void {
        this.__backing_fruit?.update(initializers?.fruit);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomXOptions) {
    }
}
/** @memo:stable */
class ArkCustomYComponent extends ArkStructBase<ArkCustomYComponent, CustomYOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomYOptions): void {
        this.__backing_parentFruit = stateOf<string>(initializers?.parentFruit ?? ('苹果'), this);
    }
    private __backing_parentFruit?: MutableState<string>;
    private get parentFruit(): string {
        return this.__backing_parentFruit!.value;
    }
    private set parentFruit(value: string) {
        this.__backing_parentFruit!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomYOptions) {
        ArkRow(__builder, () => {
            CustomX(undefined, undefined, { fruit: this.parentFruit } as CustomXOptions);
            CustomX(undefined, undefined, {} as CustomXOptions);
        });
    }
}
export {};
/** @memo */
export function CustomX(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomXOptions): void {
    const updatedInitializers: CustomXOptions = {
        fruit: initializers?.fruit,
        __backing_fruit: initializers?.__backing_fruit
    };
    ArkCustomXComponent._instantiate(style, () => new ArkCustomXComponent, content, updatedInitializers);
}
/** @memo */
export function CustomY(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomYOptions): void {
    const updatedInitializers: CustomYOptions = {
        __backing_parentFruit: initializers?.__backing_parentFruit
    };
    ArkCustomYComponent._instantiate(style, () => new ArkCustomYComponent, content, updatedInitializers);
}
export interface CustomXOptions {
    __backing_fruit?: SyncedProperty<string>;
    fruit?: string;
}
export interface CustomYOptions {
    __backing_parentFruit?: MutableState<string>;
    parentFruit?: string;
}
registerArkuiEntry(CustomY, "@prop");
export const __Entry = CustomY;
