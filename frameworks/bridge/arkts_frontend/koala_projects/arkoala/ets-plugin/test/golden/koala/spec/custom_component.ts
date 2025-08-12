import { $r, $rawfile, AppStorage, ArkColumn, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
/** @memo:stable */
class ArkMyComponentComponent extends ArkStructBase<ArkMyComponentComponent, MyComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions): void {
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: MyComponentOptions) {
        ArkColumn(__builder, () => {
            Banner(undefined, undefined);
            Banner((__instance: ArkCommonMethodComponent) => {
                __instance.width(100);
            }, undefined);
            Banner((__instance: ArkCommonMethodComponent) => {
                __instance.width(100)
                    .height(200);
            }, undefined);
            Banner(undefined, undefined, { value: "Hello" } as BannerOptions);
            Banner((__instance: ArkCommonMethodComponent) => {
                __instance.width(100);
            }, undefined, { value: "Hello" } as BannerOptions);
            Banner((__instance: ArkCommonMethodComponent) => {
                __instance.width(100)
                    .height(200);
            }, undefined, { value: "Hello" } as BannerOptions);
        });
    }
}
/** @memo:stable */
class ArkBannerComponent extends ArkStructBase<ArkBannerComponent, BannerOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: BannerOptions): void {
        this.__backing_value = initializers?.value ?? ("Hello");
    }
    private __backing_value?: string;
    private get value(): string {
        return this.__backing_value as string;
    }
    private set value(value: string) {
        this.__backing_value = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: BannerOptions) {
        ArkColumn(__builder, () => {
            ArkText(undefined, undefined, this.value);
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
    const updatedInitializers: MyComponentOptions = {};
    ArkMyComponentComponent._instantiate(style, () => new ArkMyComponentComponent, content, updatedInitializers);
}
/** @memo */
export function Banner(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: BannerOptions): void {
    const updatedInitializers: BannerOptions = {
        value: initializers?.value
    };
    ArkBannerComponent._instantiate(style, () => new ArkBannerComponent, content, updatedInitializers);
}
export interface MyComponentOptions {
}
registerArkuiEntry(MyComponent, "custom_component");
export const __Entry = MyComponent;
export interface BannerOptions {
    value?: string;
}
