import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, SyncedProperty, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, objectLinkState, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { MutableState } from "@koalaui/runtime";
import { observableProxy } from "@koalaui/common";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
var nextID: number = 0;
class Model {
    private __backing_text: MutableState<string> = stateOf<string>('');
    get text(): string {
        return this.__backing_text.value;
    }
    set text(value: string) {
        this.__backing_text.value = observableProxy(value);
    }
    private __backing_color: MutableState<string> = stateOf<string>('#00ff00');
    get color(): string {
        return this.__backing_color.value;
    }
    set color(value: string) {
        this.__backing_color.value = observableProxy(value);
    }
    constructor(t: string, c: string) {
        this.text = t;
        this.color = c;
    }
}
/** @memo:stable */
class ArkCustomTextComponent extends ArkStructBase<ArkCustomTextComponent, CustomTextOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: CustomTextOptions): void {
        this.__backing_model = objectLinkState<Model>();
    }
    private __backing_model?: SyncedProperty<Model>;
    private get model(): Model {
        return this.__backing_model!.value;
    }
    private set model(value: Model) {
        this.__backing_model!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: CustomTextOptions | undefined): void {
        this.__backing_model?.update(initializers?.model);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: CustomTextOptions) {
        ArkRow(__builder, () => {
            ArkText(undefined, undefined, this.model.text);
        });
    }
}
/** @memo:stable */
class ArkParentComponent extends ArkStructBase<ArkParentComponent, ParentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentOptions): void {
        this.__backing_nextId = initializers?.nextId ?? (1);
        this.__backing_models = stateOf<Model[]>(initializers?.models ?? ([new Model('0', '#ffffff'), new Model('1', '#fff456')]), this);
    }
    private __backing_nextId?: number;
    private get nextId(): number {
        return this.__backing_nextId as number;
    }
    private set nextId(value: number) {
        this.__backing_nextId = value;
    }
    private __backing_models?: MutableState<Model[]>;
    private get models(): Model[] {
        return this.__backing_models!.value;
    }
    private set models(value: Model[]) {
        this.__backing_models!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ParentOptions) {
        ArkColumn(__builder, () => {
            ForEach(this.models, (item) => {
                CustomText(undefined, undefined, { model: item } as CustomTextOptions);
            }, (item) => item.text);
        });
    }
}
export {};
/** @memo */
export function CustomText(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: CustomTextOptions): void {
    const updatedInitializers: CustomTextOptions = {
        model: initializers?.model,
        __backing_model: initializers?.__backing_model
    };
    ArkCustomTextComponent._instantiate(style, () => new ArkCustomTextComponent, content, updatedInitializers);
}
/** @memo */
export function Parent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentOptions): void {
    const updatedInitializers: ParentOptions = {
        nextId: initializers?.nextId,
        __backing_models: initializers?.__backing_models
    };
    ArkParentComponent._instantiate(style, () => new ArkParentComponent, content, updatedInitializers);
}
export interface CustomTextOptions {
    __backing_model?: SyncedProperty<Model>;
    model?: Model;
}
export interface ParentOptions {
    nextId?: number;
    __backing_models?: MutableState<Model[]>;
    models?: Model[];
}
registerArkuiEntry(Parent, "@objectLink");
export const __Entry = Parent;
