import { $r, $rawfile, AppStorage, ArkButton, ArkButtonComponent, ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkRowComponent, ArkStructBase, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, SyncedProperty, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, objectLinkState, px2fp, px2lpx, px2vp, stateOf, vp2px } from "@koalaui/arkui";
import { observableProxy } from "@koalaui/common";
import { MutableState } from "@koalaui/runtime";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
import { ClassB as ClassA } from './test/pages/import@Observed';
/** @memo:stable */
class ArkViewAComponent extends ArkStructBase<ArkViewAComponent, ViewAOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ViewAOptions): void {
        this.__backing_label = initializers?.label ?? ('ViewA1');
        this.__backing_a = objectLinkState<ClassA>();
    }
    private __backing_label?: string;
    private get label(): string {
        return this.__backing_label as string;
    }
    private set label(value: string) {
        this.__backing_label = value;
    }
    private __backing_a?: SyncedProperty<ClassA>;
    private get a(): ClassA {
        return this.__backing_a!.value;
    }
    private set a(value: ClassA) {
        this.__backing_a!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: ViewAOptions | undefined): void {
        this.__backing_a?.update(initializers?.a);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ViewAOptions) {
        ArkRow(__instance => {
            {
                __instance.margin({ top: 10 });
            }
            __builder?.(__instance);
        }, () => {
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.onClick(() => {
                    this.a.c += 1;
                });
            }, undefined, 'ViewA' + JSON.stringify(this.label) + 'this.a.c=' + JSON.stringify(this.a.c));
        });
    }
}
/** @memo:stable */
class ArkViewBComponent extends ArkStructBase<ArkViewBComponent, ViewBOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: ViewBOptions): void {
        this.__backing_arrA = stateOf<ClassA[]>(initializers?.arrA ?? ([new ClassA(0), new ClassA(0)]), this);
    }
    private __backing_arrA?: MutableState<ClassA[]>;
    private get arrA(): ClassA[] {
        return this.__backing_arrA!.value;
    }
    private set arrA(value: ClassA[]) {
        this.__backing_arrA!.value = observableProxy(value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: ViewBOptions) {
        ArkColumn(__instance => {
            {
                __instance.width('100%');
            }
            __builder?.(__instance);
        }, () => {
            ForEach(this.arrA, (item) => {
                ViewA(undefined, undefined, { label: JSON.stringify(item.id), a: item } as ViewAOptions);
            }, (item) => item.id.toString());
            ViewA(undefined, undefined, { label: JSON.stringify(this.arrA[0]), a: this.arrA[0] } as ViewAOptions);
            ViewA(undefined, undefined, { label: JSON.stringify(this.arrA[this.arrA.length - 1]), a: this.arrA[this.arrA.length - 1] } as ViewAOptions);
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.margin({ top: 10 })
                    .onClick(() => {
                    this.arrA = [new ClassA(0), new ClassA(0)];
                });
            }, undefined, 'ViewB: reset array');
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.margin({ top: 10 })
                    .onClick(() => {
                    this.arrA.push(new ClassA(0));
                });
            }, undefined, 'ViewB: push');
            ArkButton((__instance: ArkButtonComponent) => {
                __instance.margin({ top: 10 })
                    .onClick(() => {
                    this.arrA.shift();
                });
            }, undefined, 'ViewB: shift');
        });
    }
}
export {};
/** @memo */
export function ViewA(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ViewAOptions): void {
    const updatedInitializers: ViewAOptions = {
        label: initializers?.label,
        a: initializers?.a,
        __backing_a: initializers?.__backing_a
    };
    ArkViewAComponent._instantiate(style, () => new ArkViewAComponent, content, updatedInitializers);
}
/** @memo */
export function ViewB(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: ViewBOptions): void {
    const updatedInitializers: ViewBOptions = {
        __backing_arrA: initializers?.__backing_arrA
    };
    ArkViewBComponent._instantiate(style, () => new ArkViewBComponent, content, updatedInitializers);
}
export interface ViewAOptions {
    label?: string;
    __backing_a?: SyncedProperty<ClassA>;
    a?: ClassA;
}
export interface ViewBOptions {
    __backing_arrA?: MutableState<ClassA[]>;
    arrA?: ClassA[];
}
registerArkuiEntry(ViewB, "import@Observed");
export const __Entry = ViewB;
