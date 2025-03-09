import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
/** @memo:stable */
class ArkParentStructComponent extends ArkStructBase<ArkParentStructComponent, ParentStructOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ParentStructOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ParentStructOptions) {
        ArkColumn(__builder, () => {
            ChildStruct(undefined, () => {
                ArkText(undefined, undefined, "xxx");
            });
        });
    }
}
/** @memo:stable */
class ArkChildStructComponent extends ArkStructBase<ArkChildStructComponent, ChildStructOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ChildStructOptions): void {
        if (initializers?.content) {
            this.__backing_content = initializers?.content;
        }
        if (this.__backing_content === undefined && content !== undefined)
            this.__backing_content = content;
    }
    /** @memo */
    private __backing_content?: () => void;
    /** @memo */
    private get content(): () => void {
        return this.__backing_content!;
    }
    private set content(/**/
    /** @memo */
    value: () => void) {
        this.__backing_content = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ChildStructOptions) {
        this.content();
    }
}
/** @memo */
export function ParentStruct(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ParentStructOptions): void {
    const updatedInitializers: ParentStructOptions = {};
    ArkParentStructComponent._instantiate(style, () => new ArkParentStructComponent, content, updatedInitializers);
}
/** @memo */
export function ChildStruct(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ChildStructOptions): void {
    const updatedInitializers: ChildStructOptions = {
        content: initializers?.content
    };
    ArkChildStructComponent._instantiate(style, () => new ArkChildStructComponent, content, updatedInitializers);
}
export interface ParentStructOptions {
}
export interface ChildStructOptions {
    /** @memo */
    content?: () => void;
}
