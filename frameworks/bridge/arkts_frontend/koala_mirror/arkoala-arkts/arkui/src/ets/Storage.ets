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

import { observableProxy } from "@koalaui/common"
import { MutableState, GlobalStateManager } from "@koalaui/runtime"
import { AbstractProperty, SubscribedAbstractProperty } from "./ArkState"


///// ArkUI ///// see common_ts_ets_api.d.ts /////

/**
 * Defines the AppStorage interface.
 * @since 7
 */
export class AppStorage {
    /**
     * Returns an alias to the AppStorage property with given name.
     * @param propName - a property name
     * @returns an AbstractProperty by the given name, or `undefined` if it does not exist
     */
    static ref<T>(propName: string): AbstractProperty<T> | undefined {
        return StorageMap.shared.entry<T>(propName)
    }

    /**
     * Returns an alias to the AppStorage property with given name.
     * If property does not exist in AppStorage, create it with the given value.
     * @param propName - a property name
     * @param defaultValue - a value used to create property if it does not exist
     * @returns an AbstractProperty for the given name
     */
    static setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> {
        return StorageMap.shared.entryOrCreate(propName, defaultValue)
    }

    /**
     * Called when a link is set.
     * @since 7
     * @deprecated since 10
     */
    static Link<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return AppStorage.link<T>(propName)
    }
    /**
     * Called when a link is set.
     * @since 10
     */
    static link<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return StorageMap.shared.link<T>(propName)
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
        return StorageMap.shared.setAndLink(propName, defaultValue)
    }

    /**
     * Called when a property is set.
     * @since 7
     * @deprecated since 10
     */
    static Prop<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return AppStorage.prop<T>(propName)
    }
    /**
     * Called when a property is set.
     * @since 10
     */
    static prop<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return StorageMap.shared.prop<T>(propName)
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
        return StorageMap.shared.setAndProp(propName, defaultValue)
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
        return StorageMap.shared.map.get(propName)?.mutable ?? false
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
export class LocalStorage {
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
     * Returns an alias to the LocalStorage property with given name.
     * @param propName - a property name
     * @returns an AbstractProperty by the given name, or `undefined` if it does not exist
     */
    public ref<T>(propName: string): AbstractProperty<T> | undefined {
        return this.map.entry<T>(propName)
    }

    /**
     * Returns an alias to the LocalStorage property with given name.
     * If property does not exist in LocalStorage, create it with the given value.
     * @param propName - a property name
     * @param defaultValue - a value used to create property if it does not exist
     * @returns an AbstractProperty for the given name
     */
    setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> {
        return this.map.entryOrCreate(propName, defaultValue)
    }

    /**
     * Create and return a 'link' (two-way sync) to named property
     * @since 9
     */
    link<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return this.map.link<T>(propName)
    }

    /**
     * Like link(), will create and initialize a new source property in LocalStorge if missing
     * @since 9
     */
    setAndLink<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        return this.map.setAndLink(propName, defaultValue)
    }

    /**
     * Create and return a 'prop' (one-way sync) to named property
     * @since 9
     */
    prop<T>(propName: string): SubscribedAbstractProperty<T> | undefined {
        return this.map.prop<T>(propName)
    }

    /**
     * Like prop(), will create and initialize a new source property in LocalStorage if missing
     * @since 9
     */
    setAndProp<T>(propName: string, defaultValue: T): SubscribedAbstractProperty<T> {
        return this.map.setAndProp(propName, defaultValue)
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
    /*readonly*/ mutable: boolean
    dispose(): void
}

//////////////////////////////////////////////////

class StorageEntry<T> implements EntryObject, SubscribedAbstractProperty<T> {
    private map: StorageMap | undefined = undefined
    private name: string
    private state: MutableState<T>
    private listeners: Set<() => void> | undefined = undefined
    /*readonly*/ mutable: boolean

    constructor(map: StorageMap, name: string, value: T, mutable: boolean = true) {
        this.map = map
        this.state = map.mutableState(value)
        this.mutable = mutable
        this.name = name
    }

    private revalidate() {
        const map = this.map
        if (map && this.state.disposed) {
            this.state = map.mutableState(this.state.value)
        }
    }

    info(): string {
        return this.name
    }

    get(): T {
        this.revalidate()
        return this.state.value
    }

    set(value: T): void {
        if (this.mutable) {
            this.revalidate()
            this.state.value = observableProxy(value)
            this.listeners?.forEach(notify)
        }
    }

    subscribe(listener: () => void): void {
        if (this.mutable) {
            if (!this.listeners) this.listeners = new Set<() => void>()
            this.listeners?.add(listener)
        }
    }

    unsubscribe(listener: () => void): void {
        this.listeners?.delete(listener)
    }

    aboutToBeDeleted(): void {
    }

    get modified(): boolean {
        return this.state.modified
    }

    dispose(): void {
        this.listeners?.clear()
        this.state.dispose()
    }
}

class StorageMap {
    private static _shared?: StorageMap
    readonly manager = GlobalStateManager.instance
    readonly map = new Map<string, EntryObject>()

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
        const entry = this.map.get(key)
        return entry ? entry as StorageEntry<T> : undefined
    }

    entryOrCreate<T>(key: string, value: T): StorageEntry<T> {
        const entry = this.entry<T>(key)
        if (entry) return entry
        return this.create(key, value)
    }

    get<T>(key: string): T | undefined {
        const entry = this.entry<T>(key)
        return entry
            ? entry.get()
            : undefined
    }

    set<T>(key: string, value: T, create: boolean = true, mutable: boolean = true): boolean {
        const entry = this.entry<T>(key)
        if (entry) {
            entry.set(value)
            return true
        }
        if (create) {
            this.create(key, value, mutable)
            return true
        }
        return false
    }

    link<T>(key: string): SubscribedAbstractProperty<T> | undefined {
        return this.entry<T>(key)
    }

    setAndLink<T>(key: string, value: T): SubscribedAbstractProperty<T> {
        return this.entryOrCreate(key, value)
    }

    prop<T>(key: string): SubscribedAbstractProperty<T> | undefined {
        const entry = this.entry<T>(key)
        return entry ? new StorageProp<T>(this, key, entry.get()) : undefined
    }

    setAndProp<T>(key: string, value: T): SubscribedAbstractProperty<T> {
        return new StorageProp<T>(this, key, value)
    }

    delete(key: string): boolean {
        const entry = this.map.get(key)
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
        const entry = new StorageEntry<T>(this, key, value, mutable)
        this.map.set(key, entry)
        return entry
    }

    mutableState<T>(value: T): MutableState<T> {
        return this.manager.mutableState(observableProxy(value), true)
    }
}

/**
 * This is a @Prop implementation for backward compatibility.
 */
class StorageProp<T> implements SubscribedAbstractProperty<T> {
    private map: StorageMap
    private name: string
    private state: MutableState<T>
    private listeners: Set<() => void> | undefined = undefined

    constructor(map: StorageMap, name: string, value: T) {
        super()
        this.map = map
        this.name = name
        this.state = map.mutableState(value)
    }

    private revalidate() {
        const map = this.map
        if (map && this.state.disposed) {
            this.state = map.mutableState(this.state.value)
        }
    }
    info(): string {
        return this.name
    }

    get(): T {
        this.revalidate()
        let value = this.state.value
        const entry = this.map.entryOrCreate<T>(this.name, value)
        if (entry.modified) {
            value = entry.get()
            if (this.map.manager.frozen) {
                this.map.manager.scheduleCallback(() => { this.set(value) })
            } else {
                this.set(value)
            }
        }
        return value
    }

    set(value: T): void {
        this.revalidate()
        this.state.value = observableProxy(value)
        this.listeners?.forEach(notify)
    }

    subscribe(listener: () => void): void {
        if (!this.listeners) this.listeners = new Set<() => void>()
        this.listeners?.add(listener)
    }

    unsubscribe(listener: () => void): void {
        this.listeners?.delete(listener)
    }

    aboutToBeDeleted(): void {
        this.listeners?.clear()
        this.state.dispose()
    }
}

function notify(listener: () => void) {
    listener()
}
