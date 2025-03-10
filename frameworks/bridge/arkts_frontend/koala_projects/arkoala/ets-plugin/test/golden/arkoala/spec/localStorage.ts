import { ArkColumn, ArkColumnComponent, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, ArkText, ArkTextComponent, LocalStorage, MutableState, StorageLinkState, SyncedProperty, observableProxy, propState } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
let storage = LocalStorage.GetShared();
class ClassA {
    public id: number = 1;
    public type: number = 2;
    public a: string = "aaa";
    constructor(a: string) {
        this.a = a;
    }
}
/** @memo:stable */
class ArkLocalStorageComponentComponent extends ArkStructBase<ArkLocalStorageComponentComponent, LocalStorageComponentOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageComponentOptions): void {
        this.__backing_simpleVarName = StorageLinkState<number>(this._entry_local_storage_, "storageSimpleProp", 0);
        this.__backing_objectName = propState<ClassA>(StorageLinkState<ClassA>(this._entry_local_storage_, "storageObjectProp", new ClassA("x")).value);
    }
    private __backing_simpleVarName?: MutableState<number>;
    private get simpleVarName(): number {
        return this.__backing_simpleVarName!.value;
    }
    private set simpleVarName(value: number) {
        this.__backing_simpleVarName!.value = observableProxy(value);
    }
    private __backing_objectName?: SyncedProperty<ClassA>;
    private get objectName(): ClassA {
        return this.__backing_objectName!.value;
    }
    private set objectName(value: ClassA) {
        this.__backing_objectName!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStorageComponentOptions | undefined): void {
        this.__backing_objectName?.update(StorageLinkState<ClassA>(this._entry_local_storage_, "storageObjectProp", new ClassA("x")).value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStorageComponentOptions) {
        ArkColumn(__instance => {
            {
                __instance.height(500);
            }
            __builder?.(__instance);
        }, () => {
            ArkText((__instance: ArkTextComponent) => {
                __instance.onClick(() => {
                    this.simpleVarName += 1;
                    this.objectName.a = this.objectName.a === 'x' ? 'yex' : 'no';
                });
            }, undefined, this.objectName.a);
        });
    }
}
export {};
/** @memo */
export function LocalStorageComponent(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStorageComponentOptions): void {
    const updatedInitializers: LocalStorageComponentOptions = {
        __backing_simpleVarName: initializers?.__backing_simpleVarName,
        __backing_objectName: initializers?.__backing_objectName
    };
    ArkLocalStorageComponentComponent._instantiate(style, () => new ArkLocalStorageComponentComponent, content, updatedInitializers);
}
export interface LocalStorageComponentOptions {
    __backing_simpleVarName?: MutableState<number>;
    simpleVarName?: number;
    __backing_objectName?: SyncedProperty<ClassA>;
    objectName?: ClassA;
}
registerArkuiEntry(LocalStorageComponent, "localStorage");
export const __Entry = LocalStorageComponent;
