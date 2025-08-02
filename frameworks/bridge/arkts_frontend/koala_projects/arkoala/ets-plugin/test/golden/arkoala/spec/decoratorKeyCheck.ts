import { AppStorageLinkState, ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkRow, ArkStructBase, LocalStorage, MutableState, StorageLinkState, SyncedProperty, contextLocal, contextLocalStateOf, observableProxy, propState } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
import { stringVariable, stringObj, stringFunction } from './test/pages/decoratorKeyCheck';
let para: Record<string, number> = { 'PropA': 47 };
let storage: LocalStorage = new LocalStorage(para);
/** @memo:stable */
class ArkIndexComponent extends ArkStructBase<ArkIndexComponent, IndexOptions> {
    private _entry_local_storage_ = new LocalStorage();
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions): void {
        this.__backing_LocalStorageLink = StorageLinkState<string>(this._entry_local_storage_, stringVariable, 'LocalStorageLink');
        this.__backing_LocalStorageLink1 = StorageLinkState<string>(this._entry_local_storage_, stringObj.stringKey, 'LocalStorageLink1');
        this.__backing_LocalStorageLink2 = StorageLinkState<string>(this._entry_local_storage_, stringFunction(), 'LocalStorageLink2');
        this.__backing_LocalStorageLink3 = StorageLinkState<string>(this._entry_local_storage_, 'LocalStorageLink3', 'LocalStorageLink3');
        this.__backing_LocalStorageProp = propState<string>(StorageLinkState<string>(this._entry_local_storage_, stringVariable, 'LocalStorageProp').value);
        this.__backing_LocalStorageProp1 = propState<string>(StorageLinkState<string>(this._entry_local_storage_, stringObj.stringKey, 'LocalStorageProp1').value);
        this.__backing_LocalStorageProp2 = propState<string>(StorageLinkState<string>(this._entry_local_storage_, stringFunction(), 'LocalStorageProp2').value);
        this.__backing_LocalStorageProp3 = propState<string>(StorageLinkState<string>(this._entry_local_storage_, 'LocalStorageProp3', 'LocalStorageProp3').value);
        this.__backing_StorageProp = propState<string>(AppStorageLinkState<string>(stringVariable, 'StorageProp').value);
        this.__backing_StorageProp1 = propState<string>(AppStorageLinkState<string>(stringObj.stringKey, 'StorageProp1').value);
        this.__backing_StorageProp2 = propState<string>(AppStorageLinkState<string>(stringFunction(), 'StorageProp2').value);
        this.__backing_StorageProp3 = propState<string>(AppStorageLinkState<string>('StorageProp3', 'StorageProp3').value);
        this.__backing_StorageLink = AppStorageLinkState<string>(stringVariable, 'StorageLink');
        this.__backing_StorageLink1 = AppStorageLinkState<string>(stringObj.stringKey, 'StorageLink1');
        this.__backing_StorageLink2 = AppStorageLinkState<string>(stringFunction(), 'StorageLink2');
        this.__backing_StorageLink3 = AppStorageLinkState<string>('StorageLink3', 'StorageLink3');
        this.__backing_Provide = initializers!.__backing_Provide!;
        this.__backing_Provide3 = initializers!.__backing_Provide3!;
        this.__backing_Provide4 = initializers!.__backing_Provide4!;
        this.__backing_Consume = initializers!.__backing_Consume!;
        this.__backing_Consume3 = initializers!.__backing_Consume3!;
        this.__backing_Consume4 = initializers!.__backing_Consume4!;
    }
    private __backing_LocalStorageLink?: MutableState<string>;
    private get LocalStorageLink(): string {
        return this.__backing_LocalStorageLink!.value;
    }
    private set LocalStorageLink(value: string) {
        this.__backing_LocalStorageLink!.value = observableProxy(value);
    }
    private __backing_LocalStorageLink1?: MutableState<string>;
    private get LocalStorageLink1(): string {
        return this.__backing_LocalStorageLink1!.value;
    }
    private set LocalStorageLink1(value: string) {
        this.__backing_LocalStorageLink1!.value = observableProxy(value);
    }
    private __backing_LocalStorageLink2?: MutableState<string>;
    private get LocalStorageLink2(): string {
        return this.__backing_LocalStorageLink2!.value;
    }
    private set LocalStorageLink2(value: string) {
        this.__backing_LocalStorageLink2!.value = observableProxy(value);
    }
    private __backing_LocalStorageLink3?: MutableState<string>;
    private get LocalStorageLink3(): string {
        return this.__backing_LocalStorageLink3!.value;
    }
    private set LocalStorageLink3(value: string) {
        this.__backing_LocalStorageLink3!.value = observableProxy(value);
    }
    private __backing_LocalStorageProp?: SyncedProperty<string>;
    private get LocalStorageProp(): string {
        return this.__backing_LocalStorageProp!.value;
    }
    private set LocalStorageProp(value: string) {
        this.__backing_LocalStorageProp!.value = observableProxy(value);
    }
    private __backing_LocalStorageProp1?: SyncedProperty<string>;
    private get LocalStorageProp1(): string {
        return this.__backing_LocalStorageProp1!.value;
    }
    private set LocalStorageProp1(value: string) {
        this.__backing_LocalStorageProp1!.value = observableProxy(value);
    }
    private __backing_LocalStorageProp2?: SyncedProperty<string>;
    private get LocalStorageProp2(): string {
        return this.__backing_LocalStorageProp2!.value;
    }
    private set LocalStorageProp2(value: string) {
        this.__backing_LocalStorageProp2!.value = observableProxy(value);
    }
    private __backing_LocalStorageProp3?: SyncedProperty<string>;
    private get LocalStorageProp3(): string {
        return this.__backing_LocalStorageProp3!.value;
    }
    private set LocalStorageProp3(value: string) {
        this.__backing_LocalStorageProp3!.value = observableProxy(value);
    }
    private __backing_StorageProp?: SyncedProperty<string>;
    private get StorageProp(): string {
        return this.__backing_StorageProp!.value;
    }
    private set StorageProp(value: string) {
        this.__backing_StorageProp!.value = observableProxy(value);
    }
    private __backing_StorageProp1?: SyncedProperty<string>;
    private get StorageProp1(): string {
        return this.__backing_StorageProp1!.value;
    }
    private set StorageProp1(value: string) {
        this.__backing_StorageProp1!.value = observableProxy(value);
    }
    private __backing_StorageProp2?: SyncedProperty<string>;
    private get StorageProp2(): string {
        return this.__backing_StorageProp2!.value;
    }
    private set StorageProp2(value: string) {
        this.__backing_StorageProp2!.value = observableProxy(value);
    }
    private __backing_StorageProp3?: SyncedProperty<string>;
    private get StorageProp3(): string {
        return this.__backing_StorageProp3!.value;
    }
    private set StorageProp3(value: string) {
        this.__backing_StorageProp3!.value = observableProxy(value);
    }
    private __backing_StorageLink?: MutableState<string>;
    private get StorageLink(): string {
        return this.__backing_StorageLink!.value;
    }
    private set StorageLink(value: string) {
        this.__backing_StorageLink!.value = observableProxy(value);
    }
    private __backing_StorageLink1?: MutableState<string>;
    private get StorageLink1(): string {
        return this.__backing_StorageLink1!.value;
    }
    private set StorageLink1(value: string) {
        this.__backing_StorageLink1!.value = observableProxy(value);
    }
    private __backing_StorageLink2?: MutableState<string>;
    private get StorageLink2(): string {
        return this.__backing_StorageLink2!.value;
    }
    private set StorageLink2(value: string) {
        this.__backing_StorageLink2!.value = observableProxy(value);
    }
    private __backing_StorageLink3?: MutableState<string>;
    private get StorageLink3(): string {
        return this.__backing_StorageLink3!.value;
    }
    private set StorageLink3(value: string) {
        this.__backing_StorageLink3!.value = observableProxy(value);
    }
    private __backing_Provide?: MutableState<string>;
    private get Provide(): string {
        return this.__backing_Provide!.value;
    }
    private set Provide(value: string) {
        this.__backing_Provide!.value = observableProxy(value);
    }
    private __backing_Provide3?: MutableState<string>;
    private get Provide3(): string {
        return this.__backing_Provide3!.value;
    }
    private set Provide3(value: string) {
        this.__backing_Provide3!.value = observableProxy(value);
    }
    private __backing_Provide4?: MutableState<string>;
    private get Provide4(): string {
        return this.__backing_Provide4!.value;
    }
    private set Provide4(value: string) {
        this.__backing_Provide4!.value = observableProxy(value);
    }
    private __backing_Consume?: MutableState<string>;
    private get Consume(): string {
        return this.__backing_Consume!.value;
    }
    private set Consume(value: string) {
        this.__backing_Consume!.value = observableProxy(value);
    }
    private __backing_Consume3?: MutableState<string>;
    private get Consume3(): string {
        return this.__backing_Consume3!.value;
    }
    private set Consume3(value: string) {
        this.__backing_Consume3!.value = observableProxy(value);
    }
    private __backing_Consume4?: MutableState<string>;
    private get Consume4(): string {
        return this.__backing_Consume4!.value;
    }
    private set Consume4(value: string) {
        this.__backing_Consume4!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: IndexOptions | undefined): void {
        this.__backing_LocalStorageProp?.update(StorageLinkState<string>(this._entry_local_storage_, stringVariable, 'LocalStorageProp').value);
        this.__backing_LocalStorageProp1?.update(StorageLinkState<string>(this._entry_local_storage_, stringObj.stringKey, 'LocalStorageProp1').value);
        this.__backing_LocalStorageProp2?.update(StorageLinkState<string>(this._entry_local_storage_, stringFunction(), 'LocalStorageProp2').value);
        this.__backing_LocalStorageProp3?.update(StorageLinkState<string>(this._entry_local_storage_, 'LocalStorageProp3', 'LocalStorageProp3').value);
        this.__backing_StorageProp?.update(AppStorageLinkState<string>(stringVariable, 'StorageProp').value);
        this.__backing_StorageProp1?.update(AppStorageLinkState<string>(stringObj.stringKey, 'StorageProp1').value);
        this.__backing_StorageProp2?.update(AppStorageLinkState<string>(stringFunction(), 'StorageProp2').value);
        this.__backing_StorageProp3?.update(AppStorageLinkState<string>('StorageProp3', 'StorageProp3').value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: IndexOptions) {
        ArkRow(__builder, undefined);
    }
}
export {};
/** @memo */
export function Index(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: IndexOptions): void {
    const __provide_stringVariable = contextLocalStateOf<string>("stringVariable", () => 'Provide');
    const __provide_Provide32 = contextLocalStateOf<string>("Provide32", () => 'Provide3');
    const __provide_Provide4 = contextLocalStateOf<string>("Provide4", () => 'Provide4');
    const __consume_stringVariable = contextLocal<string>("stringVariable") as MutableState<string>;
    const __consume_Consume3 = contextLocal<string>("Consume3") as MutableState<string>;
    const __consume_Consume4 = contextLocal<string>("Consume4") as MutableState<string>;
    const updatedInitializers: IndexOptions = {
        __backing_LocalStorageLink: initializers?.__backing_LocalStorageLink,
        __backing_LocalStorageLink1: initializers?.__backing_LocalStorageLink1,
        __backing_LocalStorageLink2: initializers?.__backing_LocalStorageLink2,
        __backing_LocalStorageLink3: initializers?.__backing_LocalStorageLink3,
        __backing_LocalStorageProp: initializers?.__backing_LocalStorageProp,
        __backing_LocalStorageProp1: initializers?.__backing_LocalStorageProp1,
        __backing_LocalStorageProp2: initializers?.__backing_LocalStorageProp2,
        __backing_LocalStorageProp3: initializers?.__backing_LocalStorageProp3,
        __backing_StorageProp: initializers?.__backing_StorageProp,
        __backing_StorageProp1: initializers?.__backing_StorageProp1,
        __backing_StorageProp2: initializers?.__backing_StorageProp2,
        __backing_StorageProp3: initializers?.__backing_StorageProp3,
        __backing_StorageLink: initializers?.__backing_StorageLink,
        __backing_StorageLink1: initializers?.__backing_StorageLink1,
        __backing_StorageLink2: initializers?.__backing_StorageLink2,
        __backing_StorageLink3: initializers?.__backing_StorageLink3,
        __backing_Provide: __provide_stringVariable,
        __backing_Provide3: __provide_Provide32,
        __backing_Provide4: __provide_Provide4,
        __backing_Consume: __consume_stringVariable,
        __backing_Consume3: __consume_Consume3,
        __backing_Consume4: __consume_Consume4
    };
    ArkIndexComponent._instantiate(style, () => new ArkIndexComponent, content, updatedInitializers);
}
export interface IndexOptions {
    __backing_LocalStorageLink?: MutableState<string>;
    LocalStorageLink?: string;
    __backing_LocalStorageLink1?: MutableState<string>;
    LocalStorageLink1?: string;
    __backing_LocalStorageLink2?: MutableState<string>;
    LocalStorageLink2?: string;
    __backing_LocalStorageLink3?: MutableState<string>;
    LocalStorageLink3?: string;
    __backing_LocalStorageProp?: SyncedProperty<string>;
    LocalStorageProp?: string;
    __backing_LocalStorageProp1?: SyncedProperty<string>;
    LocalStorageProp1?: string;
    __backing_LocalStorageProp2?: SyncedProperty<string>;
    LocalStorageProp2?: string;
    __backing_LocalStorageProp3?: SyncedProperty<string>;
    LocalStorageProp3?: string;
    __backing_StorageProp?: SyncedProperty<string>;
    StorageProp?: string;
    __backing_StorageProp1?: SyncedProperty<string>;
    StorageProp1?: string;
    __backing_StorageProp2?: SyncedProperty<string>;
    StorageProp2?: string;
    __backing_StorageProp3?: SyncedProperty<string>;
    StorageProp3?: string;
    __backing_StorageLink?: MutableState<string>;
    StorageLink?: string;
    __backing_StorageLink1?: MutableState<string>;
    StorageLink1?: string;
    __backing_StorageLink2?: MutableState<string>;
    StorageLink2?: string;
    __backing_StorageLink3?: MutableState<string>;
    StorageLink3?: string;
    __backing_Provide?: MutableState<string>;
    Provide?: string;
    __backing_Provide3?: MutableState<string>;
    Provide3?: string;
    __backing_Provide4?: MutableState<string>;
    Provide4?: string;
    __backing_Consume?: MutableState<string>;
    Consume?: string;
    __backing_Consume3?: MutableState<string>;
    Consume3?: string;
    __backing_Consume4?: MutableState<string>;
    Consume4?: string;
}
registerArkuiEntry(Index, "decoratorKeyCheck");
export const __Entry = Index;
