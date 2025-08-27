/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { GlobalStateManager, MutableState } from "@koalaui/runtime"

/**
 * @param storage - a local storage associated with an entry
 * @param name - a state name in the specified storage
 * @param value - a default value used to create a state if it is absent
 * @returns a global named state from the specified storage
 */
export function StorageLinkState<Value>(storage: LocalStorage, name: string, value: Value): MutableState<Value> {
    return storage.map.link(name, value).state
}

/**
 * @param name - a state name in the application-based storage
 * @param value - a default value used to create a state if it is absent
 * @returns a global named state from the application-based storage
 */
export function AppStorageLinkState<Value>(name: string, value: Value): MutableState<Value> {
    return StorageMap.shared.link(name, value).state
}

///// ArkUI ///// see common_ts_ets_api.d.ts /////

/**
 * Defines the AppStorage interface.
 * @since 7
 */
class AppStorage {
    /**
     * Called when a link is set.
     * @since 7
     * @deprecated since 10
     */
    static Link<T>(propName: string): SubscribedAbstractProperty<T> {
        return AppStorage.link<T>(propName)
    }
    /**
     * Called when a link is set.
     * @since 10
     */
    static link<T>(propName: string): SubscribedAbstractProperty<T> {
        throw new Error("AppStorage.link is not implemented")
    }

    /**
     * Called when a hyperlink is set.
     * @since 7
     * @deprecated since 10
     */
    static SetAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        return AppStorage.setAndLink(propName, defaultValue)
    }
    /**
     * Called when a hyperlink is set.
     * @since 10
     */
    static setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        throw new Error("AppStorage.setAndLink is not implemented")
    }

    /**
     * Called when a property is set.
     * @since 7
     * @deprecated since 10
     */
    static Prop<T>(propName: string): SubscribedAbstractProperty<T> {
        return AppStorage.prop<T>(propName)
    }
    /**
     * Called when a property is set.
     * @since 10
     */
    static prop<T>(propName: string): SubscribedAbstractProperty<T> {
        throw new Error("AppStorage.prop is not implemented")
    }

    /**
     * Called when dynamic properties are set.
     * @since 7
     * @deprecated since 10
     */
    static SetAndProp<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        return AppStorage.setAndProp(propName, defaultValue)
    }
    /**
     * Called when dynamic properties are set.
     * @since 10
     */
    static setAndProp<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        throw new Error("AppStorage.setAndProp is not implemented")
    }

    /**
     * Called when owning or not.
     * @since 7
     * @deprecated since 10
     */
    static Has(propName: string): boolean {
        return AppStorage.has(propName)
    }
    /**
     * Called when owning or not.
     * @since 10
     */
    static has(propName: string): boolean {
        return StorageMap.shared.has(propName)
    }

    /**
     * Called when data is obtained.
     * @since 7
     * @deprecated since 10
     */
    static Get<T>(propName: string): T | undefined {
        return AppStorage.get<T>(propName)
    }
    /**
     * Called when data is obtained.
     * @since 10
     */
    static get<T>(propName: string): T | undefined {
        return StorageMap.shared.get<T>(propName)
    }

    /**
     * Called when setting.
     * @since 7
     * @deprecated since 10
     */
    static Set<T>(propName: string, newValue: T): boolean {
        return AppStorage.set(propName, newValue)
    }
    /**
     * Called when setting.
     * @since 10
     */
    static set<T>(propName: string, newValue: T): boolean {
        return StorageMap.shared.set(propName, newValue, false)
    }

    /**
     * Called when setting or creating.
     * @since 7
     * @deprecated since 10
     */
    static SetOrCreate<T>(propName: string, newValue: T): void {
        AppStorage.setOrCreate(propName, newValue)
    }
    /**
     * Called when setting or creating.
     * @since 10
     */
    static setOrCreate<T>(propName: string, newValue: T): void {
        StorageMap.shared.set(propName, newValue, true)
    }

    /**
     * Called when a deletion is made.
     * @since 7
     * @deprecated since 10
     */
    static Delete(propName: string): boolean {
        return AppStorage.delete(propName)
    }
    /**
     * Called when a deletion is made.
     * @since 10
     */
    static delete(propName: string): boolean {
        return StorageMap.shared.delete(propName)
    }

    /**
     * Called when a dictionary is sorted.
     * @since 7
     * @deprecated since 10
     */
    static Keys(): IterableIterator<string> {
        return AppStorage.keys()
    }
    /**
     * Called when a dictionary is sorted.
     * @since 10
     */
    static keys(): IterableIterator<string> {
        return StorageMap.shared.keys()
    }

    /**
     * Called when a cleanup occurs.
     * @since 7
     * @deprecated since 9
     * @useinstead AppStorage.Clear
     */
    static staticClear(): boolean {
        return AppStorage.clear()
    }

    /**
     * Called when a cleanup occurs.
     * @since 9
     * @deprecated since 10
     */
    static Clear(): boolean {
        return AppStorage.clear()
    }
    /**
     * Called when a cleanup occurs.
     * @since 10
     */
    static clear(): boolean {
        return StorageMap.shared.clear()
    }

    /**
     * Called when the data can be changed.
     * @since 7
     */
    static IsMutable(propName: string): boolean {
        const entry = StorageMap.shared.entryObject(propName)
        return entry ? (entry as EntryObject).mutable : false
    }

    /**
     * Called when you check how much data is stored.
     * @since 7
     */
    static Size(): number {
        return AppStorage.size()
    }
    /**
     * Called when you check how much data is stored.
     * @since 10
     */
    static size(): number {
        return StorageMap.shared.size
    }
}

/**
 * Defines the subscribed abstract property.
 * @since 7
 * @systemapi
 */
abstract class SubscribedAbstractProperty<T> {
    /**
     * Returns the property name,
     * e.g. let link = AppStorage.Link("foo") then link.info() == "foo"
     *
     * @returns { string } the property name if set or undefined
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    info(): string {
        return "TODO"
    }
    /**
     * Called when data is obtained.
     * @since 7
     * @systemapi
     */
    abstract get(): T

    /**
     * Called when data is created.
     * @since 7
     * @systemapi
     */
    abstract set(newValue: T): void
    /**
     * An app needs to call this function before the instance of SubscribedAbstractProperty
     * goes out of scope / is subject to garbage collection. Its purpose is to unregister the
     * variable from the two-way/one-way sync relationship that AppStorage/LocalStorage.link()/prop()
     * and related functions create.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    abstract aboutToBeDeleted(): void
}

/**
 * EnvProps object
 *
 * @interface EnvPropsOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @since 10
 */
interface EnvPropsOptions {
    /**
     * Property name
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    key: string;
    /**
     * DefaultValue is the default value if cannot get the environment property value
     *
     * @type { number | string | boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    defaultValue: number | string | boolean;
}


/**
 * Defines the Environment interface.
 * @since 7
 */
export class Environment {
    /**
     * Called when a property value is checked.
     * @since 7
     * @deprecated since 10
     */
    static EnvProp<T>(key: string, value: T): boolean {
        return Environment.envProp(key, value)
    }
    /**
     * Called when a property value is checked.
     * @since 10
     */
    static envProp<T>(key: string, value: T): boolean {
        throw new Error("Environment.EnvProp is not implemented")
    }

    /**
     * Called when multiple property values are checked.
     * @since 10
     */
    static envProps(props: EnvPropsOptions[]): void {
        for (const prop of props) Environment.envProp(prop.key, prop.defaultValue)
    }

    /**
     * Set the key value.
     * @since 7
     * @deprecated since 10
     */
    static Keys(): Array<string> {
        return Environment.keys()
    }
    /**
     * Set the key value.
     * @since 10
     */
    static keys(): Array<string> {
        throw new Error("Environment.Keys is not implemented")
    }
}

/**
 * PersistProps object
 *
 * @interface PersistPropsOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @since 10
 */
declare interface PersistPropsOptions {
    /**
     * Property name
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    key: string;
    /**
     * If AppStorage does not include this property it will be initialized with this value
     *
     * @type { number | string | boolean | Object }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @crossplatform
     * @since 10
     */
    defaultValue: number | string | boolean | Object;
}

/**
 * Defines the PersistentStorage interface.
 * @since 7
 */
export class PersistentStorage {
    /**
     * Called when a persistence property is stored.
     * @since 7
     * @deprecated since 10
     */
    static PersistProp<T>(key: string, defaultValue: T): void {
        PersistentStorage.persistProp(key, defaultValue)
    }
    /**
     * Called when a persistence property is stored.
     * @since 10
     */
    static persistProp<T>(key: string, defaultValue: T): void {
        throw new Error("PersistentStorage.persistProp is not implemented")
    }

    /**
     * Called when a property is deleted.
     * @since 7
     * @deprecated since 10
     */
    static DeleteProp(key: string): void {
        PersistentStorage.deleteProp(key)
    }
    /**
     * Called when a property is deleted.
     * @since 10
     */
    static deleteProp(key: string): void {
        throw new Error("PersistentStorage.deleteProp is not implemented")
    }

    /**
     * Called when multiple persistence properties are stored.
     * @since 10
     */
    static persistProps(properties: PersistPropsOptions[]): void {
        for (const prop of properties) PersistentStorage.persistProp(prop.key, prop.defaultValue)
    }

    /**
     * Set the key value.
     * @since 7
     * @deprecated since 10
     */
    static Keys(): Array<string> {
        return PersistentStorage.keys()
    }
    /**
     * Set the key value.
     * @since 10
     */
    static keys(): Array<string> {
        throw new Error("PersistentStorage.keys is not implemented")
    }
}

/**
 * Define LocalStorage.
 * @since 9
 */
class LocalStorage {
    private static shared?: LocalStorage
    /** @internal */ readonly map: StorageMap

    /**
     * Constructor.
     * @since 9
     */
    constructor(initializingProperties?: IterableIterator<[string, Object]>) {
        this.map = new StorageMap(initializingProperties)
    }

    /**
     * Get current LocalStorage shared from stage.
     * @StageModelOnly
     * @since 9
     * @deprecated since 10
     */
    static GetShared(): LocalStorage {
        return LocalStorage.getShared()
    }
    /**
     * Get current LocalStorage shared from stage.
     * @StageModelOnly
     * @since 10
     */
    static getShared(): LocalStorage {
        let shared = LocalStorage.shared
        if (shared) return shared
        LocalStorage.shared = shared = new LocalStorage()
        return shared
    }

    /**
     * Return true if property with given name exists
     * @since 9
     */
    has(propName: string): boolean {
        return this.map.has(propName)
    }

    /**
     * Return a Map Iterator
     * @since 9
     */
    keys(): IterableIterator<string> {
        return this.map.keys()
    }

    /**
     * Return number of properties
     * @since 9
     */
    size(): number {
        return this.map.size
    }

    /**
     * Return value of given property
     * @since 9
     */
    get<T>(propName: string): T | undefined {
        return this.map.get<T>(propName)
    }

    /**
     * Set value of given property
     * @since 9
     */
    set<T>(propName: string, newValue: T): boolean {
        return this.map.set(propName, newValue, false)
    }

    /**
     * Add property if not property with given name
     * @since 9
     */
    setOrCreate<T>(propName: string, newValue: T): boolean {
        this.map.set(propName, newValue, true)
        return newValue != undefined
    }

    /**
     * Create and return a 'link' (two-way sync) to named property
     * @since 9
     */
    link<T>(propName: string): SubscribedAbstractProperty<T> {
        throw new Error("LocalStorage.link is not implemented")
    }

    /**
     * Like link(), will create and initialize a new source property in LocalStorge if missing
     * @since 9
     */
    setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        throw new Error("LocalStorage.setAndLink is not implemented")
    }

    /**
     * Create and return a 'prop' (one-way sync) to named property
     * @since 9
     */
    prop<T>(propName: string): SubscribedAbstractProperty<T> {
        throw new Error("LocalStorage.prop is not implemented")
    }

    /**
     * Like prop(), will create and initialize a new source property in LocalStorage if missing
     * @since 9
     */
    setAndProp<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        throw new Error("LocalStorage.setAndProp is not implemented")
    }

    /**
     * Delete property from StorageBase
     * @since 9
     * @returns false if method failed
     */
    delete(propName: string): boolean {
        return this.map.delete(propName)
    }

    /**
     * Delete all properties from the StorageBase
     * @since 9
     */
    clear(): boolean {
        return this.map.clear()
    }
}

///// interface without generic types to workaround issues with ArkTS compiler /////

interface EntryObject {
    readonly mutable: boolean
    dispose(): void
}

//////////////////////////////////////////////////

class StorageEntry<T> extends SubscribedAbstractProperty<T> implements EntryObject {
    readonly state: MutableState<T>
    mutable: boolean

    constructor(state: MutableState<T>, mutable: boolean = true) {
        super()
        this.state = state
        this.mutable = mutable
    }

    get(): T {
        return this.state.value
    }

    set(value: T): void {
        if (this.mutable) this.state.value = value
    }

    dispose(): void {
        this.state.dispose()
    }

    aboutToBeDeleted(): void {
        // TODO:
    }
}

class StorageMap {
    private static _shared?: StorageMap
    private readonly manager = GlobalStateManager.instance
    private readonly map = new Map<string, EntryObject>()

    static get shared(): StorageMap {
        let shared = StorageMap._shared
        if (shared?.manager === GlobalStateManager.instance) return shared as StorageMap
        StorageMap._shared = shared = new StorageMap() // recreate shared storage if state manager is changed
        return shared
    }

    constructor(initializer?: IterableIterator<[string, Object]>) {
        if (initializer) {
            for (const entry of initializer) {
                this.create<Object>(entry[0], entry[1])
            }
        }
    }

    keys(): IterableIterator<string> {
        return this.map.keys()
    }

    get size(): number {
        return this.map.size
    }

    has(key: string): boolean {
        return this.map.has(key)
    }

    entry<T>(key: string): StorageEntry<T> | undefined {
        const entry = this.entryObject(key)
        return entry ? entry as StorageEntry<T> : undefined
    }

    entryObject(key: string): EntryObject | undefined {
        return this.map.get(key)
    }

    get<T>(key: string): T | undefined {
        return this.entry<T>(key)?.get()
    }

    set<T>(key: string, value: T, create: boolean = true, mutable: boolean = true): boolean {
        const entry = this.entry<T>(key)
        if (entry) {
            entry.set(value)
            return true
        }
        if (create) {
            this.create(key, value, mutable)
        }
        return false
    }

    link<T>(key: string, value: T): StorageEntry<T> {
        const entry = this.entry<T>(key)
        return entry ? entry : this.create(key, value)
    }

    delete(key: string): boolean {
        const entry = this.entryObject(key)
        if (!entry) return false
        entry.dispose()
        return this.map.delete(key)
    }

    clear(): boolean {
        if (this.map.size == 0) return false
        for (const entry of this.map.values()) {
            entry.dispose()
        }
        this.map.clear()
        return true
    }

    private create<T>(key: string, value: T, mutable: boolean = true): StorageEntry<T> {
        const entry = new StorageEntry<T>(this.manager.mutableState(value, true), mutable)
        this.map.set(key, entry)
        return entry
    }
}
