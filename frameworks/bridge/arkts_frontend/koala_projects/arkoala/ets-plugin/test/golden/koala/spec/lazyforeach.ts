import { $r, $rawfile, AppStorage, ArkCommonMethodComponent, ArkGridItem, ArkLazyGrid, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, CanvasRenderingContext2D, CustomDialogController, DataChangeListener, Environment, ForEach, GestureGroup, IDataSource, LazyForEach, LocalStorage, LongPressGesture, PanGesture, PanGestureOptions, PersistentStorage, PinchGesture, RenderingContextSettings, RotationGesture, Scroller, SubscribedAbstractProperty, SwipeGesture, SwiperController, TabsController, TapGesture, TextAreaController, VideoController, animateTo, fp2px, getContext, getInspectorByKey, lpx2px, px2fp, px2lpx, px2vp, vp2px } from "@koalaui/arkui";
import { registerArkuiEntry } from "@koalaui/arkui/ohos.router";
class BasicDataSource implements IDataSource {
    private listeners: DataChangeListener[] = [];
    public totalCount(): number {
        return 0;
    }
    public getData(index: number): any {
        return undefined;
    }
    registerDataChangeListener(listener: DataChangeListener): void {
        if (this.listeners.indexOf(listener) < 0) {
            console.info('add listener');
            this.listeners.push(listener);
        }
    }
    unregisterDataChangeListener(listener: DataChangeListener): void {
        const pos = this.listeners.indexOf(listener);
        if (pos >= 0) {
            console.info('remove listener');
            this.listeners.splice(pos, 1);
        }
    }
    notifyDataReload(): void {
        this.listeners.forEach(listener => {
            listener.onDataReloaded();
        });
    }
    notifyDataAdd(index: number): void {
        this.listeners.forEach(listener => {
            listener.onDataAdd(index);
        });
    }
    notifyDataChange(index: number): void {
        this.listeners.forEach(listener => {
            listener.onDataChange(index);
        });
    }
    notifyDataDelete(index: number): void {
        this.listeners.forEach(listener => {
            listener.onDataDelete(index);
        });
    }
    notifyDataMove(from: number, to: number): void {
        this.listeners.forEach(listener => {
            listener.onDataMove(from, to);
        });
    }
}
class MyDataSource extends BasicDataSource {
    private dataArray: string[] = ['/path/image0', '/path/image1', '/path/image2', '/path/image3'];
    public totalCount(): number {
        return this.dataArray.length;
    }
    public getData(index: number): any {
        return this.dataArray[index];
    }
    public addData(index: number, data: string): void {
        this.dataArray.splice(index, 0, data);
        this.notifyDataAdd(index);
    }
    public pushData(data: string): void {
        this.dataArray.push(data);
        this.notifyDataAdd(this.dataArray.length - 1);
    }
}
/** @memo:stable */
class ArkTestComponent extends ArkStructBase<ArkTestComponent, TestOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: TestOptions): void {
        this.__backing_data = initializers?.data ?? (new MyDataSource());
    }
    private __backing_data?: MyDataSource;
    private get data(): MyDataSource {
        return this.__backing_data as MyDataSource;
    }
    private set data(value: MyDataSource) {
        this.__backing_data = value;
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: TestOptions) {
        ArkLazyGrid(__builder, () => {
            LazyForEach(this.data, (row) => {
                ArkGridItem(undefined, () => {
                    ArkText(undefined, undefined, row);
                });
            }, row => row);
        });
    }
}
export {};
/** @memo */
export function Test(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: TestOptions): void {
    const updatedInitializers: TestOptions = {
        data: initializers?.data
    };
    ArkTestComponent._instantiate(style, () => new ArkTestComponent, content, updatedInitializers);
}
export interface TestOptions {
    data?: MyDataSource;
}
registerArkuiEntry(Test, "lazyforeach");
export const __Entry = Test;
