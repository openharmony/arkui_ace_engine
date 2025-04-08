import { int32, propDeepCopy} from "@koalaui/compat";
import { mutableState } from "./GlobalStateManager";
import { MutableState } from "./State";

/***************************************************** IObservedObject ********************************************** */
export interface IObservedObject {
    _permissibleAddRefDepth: number;
}

// function castToIObservedObject<T>(obj: T): IObservedObject | undefined {
//     return isIObservedObject(obj) ? (obj as IObservedObject) : undefined;
// }


/**
* The helper function sets the observation depth in given `IObservedObject`
*/
export function setObservationDepth<T>(obj: T, depth: number): void {
    // const objOpt = castToIObservedObject(obj);
    // if (objOpt) {
    //     objOpt._permissibleAddRefDepth = depth;
    // }
}

/***************************************************** BackingValue ********************************************** */
export class BackingValue<T> {
    private current_ : T;

    constructor(initValue : T) {
        this.current_ = initValue;
    }

    public get value() : T {
        return this.current_;
    }
    public set value(newValue : T)  {
        this.current_ = newValue;
    }
}

/***************************************************** @MutableStateMeta ********************************************** */
class MutableStateMetaBase {
    public readonly decorator: string;

    constructor(decorator: string) {
        this.decorator = decorator;
    }
}

export class MutableStateMeta extends MutableStateMetaBase {
    // meta MutableState to record dependencies in addRef
    // and mutate in fireChange
    private __metaDependency: MutableState<int32> = mutableState<int32>(0)

    constructor(decorator: string) {
        super(decorator);
    }

    public addRef(): void {
        this.__metaDependency.value;
    }

    public fireChange(): void {
        this.__metaDependency.value += 1;
    }
}

export class MutableKeyedStateMeta extends MutableStateMetaBase {
    public static readonly OB_LENGTH = "__OB_LENGTH";
    private readonly __metaDependencies = new Map<string, MutableState<int32>>();


    public addRef(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependencies.get(key);
        if (!metaDependency) {
            metaDependency = mutableState<int32>(0)
            this.__metaDependencies.set(key, metaDependency);
        }
        metaDependency.value;
    }

    public fireChange(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependencies.get(key);
        if (metaDependency) {
            metaDependency.value += 1;
        }
    }

    constructor(decorator: string) {
        super(decorator);
    }
}

/***************************************************** WatchFuncType ********************************************** */
export type WatchFuncType = ((propertyName: string) => void);
export type WatchIdType = number;

// WatchFunc: Representaton of a @Watch function isnide V1 decorator class
export class WatchFunc {
    private static nextWatchId_: WatchIdType = 1;
    private static readonly watchId2WatchFunc: Map<WatchIdType, WatchFunc>
        = new Map<WatchIdType, WatchFunc>();
    private static readonly watchFinalizer: FinalizationRegistry<WatchIdType>
        = new FinalizationRegistry<WatchIdType>((watchId: WatchIdType) => {
            // remove @Watch id from watchId2WatchFunc Map to avoid memory growth
            WatchFunc.watchId2WatchFunc.delete(watchId);
        });

    public static execWatchById(watchId: WatchIdType, propertyName: string): boolean {
        const watchFuncOpt = WatchFunc.watchId2WatchFunc.get(watchId);
        if (watchFuncOpt) {
            watchFuncOpt!.execute(propertyName);
            return true;
        } else {
            return false;
        }
    }

    public func_: WatchFuncType;
    private readonly id_: WatchIdType;

    constructor(func: WatchFuncType) {
        this.id_ = WatchFunc.nextWatchId_++;
        WatchFunc.watchId2WatchFunc.set(this.id_, this);
        this.func_ = func;
        WatchFunc.watchFinalizer.register(this, this.id_);
    }

    public id() {
        return this.id_
    }

    public setFunc(newFunc : WatchFuncType) : void {
        this.func_ = newFunc;
    }

    registerMeTo(obj: IWatchTrigger) {
        obj.addWatchSubscriber(this.id_);
    }
    unregisterMeFrom(obj: IWatchTrigger) {
        obj.removeWatchSubscriber(this.id_);
    }
    execute(propertyName: string): void {
        this.func_(propertyName);
    }
}

export interface IWatchTrigger {
    addWatchSubscriber(watchId: WatchIdType): void;
    removeWatchSubscriber(watchId: WatchIdType): boolean;
    executeOnSubscribingWatches(propertyName: string): void;
}

// IObserveObject object instances also need to implement WatchTrigger
export class SubscribedWatches implements IWatchTrigger {
    private subscribers_: Set<WatchIdType> = new Set<WatchIdType>();
    public addWatchSubscriber(id: WatchIdType): void {
        this.subscribers_.add(id);
    }
    public removeWatchSubscriber(id: WatchIdType): boolean {
        return this.subscribers_.delete(id);
    }
    public executeOnSubscribingWatches(propertyName: string): void {
    }
}

/***************************************************** DecoratedV1VariableBase ********************************************** */
export interface IDecoratedImmutableVariable<T> {
    get(): T;
}

export interface DecoratedMutableVariable<T> {
    get(): T;
    set(newValue: T): void;
}

export interface IDecoratedUpdatableVariable<T> {
    update(newValue: T): void;
}


/**
* Base class of all decorated variable classes
*/
export abstract class DecoratedVariableBase<T> {
    protected readonly meta_: MutableStateMeta = new MutableStateMeta("@State");
    // FIXME compiler bug , change to protected
    public readonly varName_: string;

    constructor(varName: string) {
        this.varName_ = varName;
    }

    // FIXME compiler bug: why public is needed that derived class can use
    public validateValue(newValue: T): boolean {
        return ((typeof newValue === 'object'));
    }
}

export abstract class DecoratedV1VariableBase<T> extends DecoratedVariableBase<T> {

    public readonly _watchFuncs: Map<WatchIdType, WatchFunc> = new Map<WatchIdType, WatchFunc>();

    constructor(varName: string, watchFunc?: WatchFuncType) {
        super(varName);
        if (watchFunc) {
            const w = new WatchFunc(watchFunc);
            this._watchFuncs.set(w.id(), w);
        }
    }

    /**
     * remove WatchFunc with given id
     * @param watchId 
     * @returns 
     */
    public removeWatch(watchId : WatchIdType) : boolean {
        return this._watchFuncs.delete(watchId);
    }

    /* compiler BUG: change to protcted */
    public registerWatchForObservedObjectChanges(value: T): void {

    }


    /* compiler BUG: change to protcted */
    public unregisterWatchFromObservedObjectChanges(value: T): void {

    }
}

/***************************************************** @Prop ********************************************** */
function deepCopy<T>(value: T): T {
    return propDeepCopy<T>(value) as T;
}

export class StateMgmtLoop {
    static callbacks: Array<() => void> = new Array<() => void>();
    static add(callback: () => void) {
        StateMgmtLoop.callbacks.push(callback);
    }
    static consume(): void {
        StateMgmtLoop.callbacks.forEach((callback: () => void) => {
            callback();
        });
        StateMgmtLoop.callbacks.length = 0;
    }
}

export class PropDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements DecoratedMutableVariable<T>, IDecoratedUpdatableVariable<T> {
    private __backing: BackingValue<T>;
    private __sourceValue: T;

    constructor(parentInitValue: T, watchFunc?: WatchFuncType) {
        super("", watchFunc);
        this.__backing = new BackingValue<T>(deepCopy<T>(parentInitValue));
        this.__sourceValue = parentInitValue;
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }

    public getInfo(): string {
        return `@Prop ${this.varName_} (PropDecoratedVariable)`;
    }

    public get(): T {
        setObservationDepth(this.__backing.value, 1);
        this.meta_.addRef();
        return this.__backing.value;
    }

    public set(newValue: T): void {
        if (this.__backing.value != newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);

            this.__backing.value = deepCopy<T>(newValue);
            this.meta_.fireChange();
            this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
        }
    }

    public update(newValue: T): void {
        this.meta_.addRef();
        if (this.__sourceValue != newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);

            this.__backing.value = deepCopy<T>(newValue);
            this.__sourceValue = newValue;
            StateMgmtLoop.add(() => {
                this.meta_.fireChange();
                this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
            });
        }
    }
}

/***************************************************** @State ********************************************** */
export interface __MkPropReturnType<T> {
    prop: PropDecoratedVariable<T>;
    watchId: WatchIdType
}

export class StateDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements DecoratedMutableVariable<T> {
    private __backing: BackingValue<T>;

    constructor(initValue: T, watchFunc?: WatchFuncType) {
        super('', watchFunc);
    
        this.__backing = new BackingValue<T>(initValue);
        this.registerWatchForObservedObjectChanges(this.__backing.value);
    }

    public getInfo(): string {
        return `@State ${this.varName_} (StateDecoratedVariable)`;
    }

    public get(): T {
        setObservationDepth(this.__backing.value, 1);
        this.meta_.addRef();
        return this.__backing.value;
    }

    public set(newValue: T): void {
        if (this.__backing.value != newValue) {
            this.unregisterWatchFromObservedObjectChanges(this.__backing.value);
            this.registerWatchForObservedObjectChanges(newValue);

            this.__backing.value = newValue;

            this.meta_.fireChange();
            this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
        }
    }

    public mkLink(varName: string): LinkDecoratedVariable<T> {
        return new LinkDecoratedVariable<T>(() => this.get(), (newValue: T) => this.set(newValue));
    }

    public mkProp(varName: string): __MkPropReturnType<T> {
        const prop = new PropDecoratedVariable<T>(this.get());
        const weakProp = new WeakRef<PropDecoratedVariable<T>>(prop);
        const watchThis = new WatchFunc((_: string) => { });
        const watchFunc: WatchFuncType = (_: string) => {
            if (weakProp.deref()) {
                weakProp.deref()!.update(this.get());
            } else {
                this._watchFuncs.delete(watchThis.id());
            }
        }
        watchThis.setFunc(watchFunc);
        this._watchFuncs.set(watchThis.id(), watchThis);
        return { prop: prop, watchId: watchThis.id() };
    }
}

/***************************************************** @Link ********************************************** */
export class LinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements DecoratedMutableVariable<T> {

    private sourceGet_: () => T;
    private sourceSet_?: (newValue: T) => void;

    constructor(sourceGet: () => T, sourceSet?: (newValue: T) => void, watchFunc?: WatchFuncType) {
        super('', watchFunc);
        this.sourceGet_ = sourceGet;
        this.sourceSet_ = sourceSet;
        this.registerWatchForObservedObjectChanges(sourceGet());
    }

    public getInfo(): string {
        return `@Link ${this.varName_} (LinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.sourceGet_();
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        if (this.sourceGet_() != newValue) {
            if (this.sourceSet_ === undefined) {
                throw new Error(`${this.getInfo()}: Can not set @Link value. @Link source is immutable error.`);
            }

            this.unregisterWatchFromObservedObjectChanges(this.sourceGet_());
            this.registerWatchForObservedObjectChanges(newValue);
            this.sourceSet_!(newValue);
            this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
        }
    }
}

/***************************************************** LocalStorage ********************************************** */
type StorageLinkPropIdType = number;

interface StorageLinkPropRegistration {
    id: StorageLinkPropIdType;
    propName: string;
    watchIdToKeepPropUpdated?: WatchIdType
}
  
export class LocalStorage {

  private storage_: Map<string, StateDecoratedVariable<Object>>; 
  private nextLinkPropId: StorageLinkPropIdType = 1;
  private linksPropRegistrations_: Map<string, Set<StorageLinkPropIdType>> = new Map<string, Set<StorageLinkPropIdType>>();

  constructor() {
    this.storage_ = new Map<string, StateDecoratedVariable<Object>>();
  }

  private getInfo(): string {
    return '@LocalStorage';
  }

  public has(propName: string): boolean {
    return this.storage_.has(propName);
  }

  public keys(): IterableIterator<string> {
    return this.storage_.keys();
  }

  public size(): number {
    return this.storage_.size;
  }

  public get<T>(propName: string): T | undefined {
    const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    return p ? p!.get() as T: undefined;
  }

  public set<T>(propName: string, newValue: T): boolean {
    const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p === undefined) {
      return false;
    }
    p.set(newValue as Object);
    return true;
  }

  public setOrCreate<T>(propName: string, newValue: T): boolean {
    let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p !== undefined) {
      p.set(newValue as Object);
      return true;
    }
    this.addNewPropertyInternal(propName, newValue as Object);
    return true;
  }

  private addNewPropertyInternal(propName: string, value: Object): StateDecoratedVariable<Object> {
    const newProp = new StateDecoratedVariable<Object>(value);
    this.storage_.set(propName, newProp);
    return newProp;
  }

  public link(propName: string): LinkDecoratedVariable<Object> | undefined {
    const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p === undefined) {
      return undefined;
    }
    return this.linkInternal(p!, propName);
  }

  public setAndLink(propName: string, defaultValue: Object): LinkDecoratedVariable<Object> {
    let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (!p) {
      p = this.addNewPropertyInternal(propName, defaultValue);
    }
    return this.linkInternal(p!, propName)!;
  }


  private linkInternal(p: StateDecoratedVariable<Object>, propName: string): LinkDecoratedVariable<Object> {
    const link: LinkDecoratedVariable<Object> = p.mkLink(propName);

    const id = this.nextLinkPropId++;
    let reg = this.linksPropRegistrations_.get(propName)
    if (reg === undefined) {
      reg = new Set<StorageLinkPropIdType>();
      this.linksPropRegistrations_.set(propName, reg);
    }
    reg.add(id);
    const regEntry: StorageLinkPropRegistration = { propName: propName, id: id };
    return link;
  }
  public prop(propName: string): PropDecoratedVariable<Object> | undefined {
    const p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p === undefined) {
      return undefined;
    }

    return this.propInternal(propName, p!);
  }

  public setAndProp(propName: string, defaultValue: Object): PropDecoratedVariable<Object> {
    let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p === undefined) {
      p = this.addNewPropertyInternal(propName, defaultValue);
    }

    return this.propInternal(propName, p);
  }


  private propInternal(propName: string, p: StateDecoratedVariable<Object>): PropDecoratedVariable<Object> {
    const result: __MkPropReturnType<Object> = p.mkProp(propName);
    const prop = result.prop;
   
    const id = this.nextLinkPropId++;
    let reg = this.linksPropRegistrations_.get(propName)
    if (reg === undefined) {
      reg = new Set<StorageLinkPropIdType>();
      this.linksPropRegistrations_.set(propName, reg);
    }
    reg.add(id);
    return prop;
  }

  public delete(propName: string): boolean {
    let p: StateDecoratedVariable<Object> | undefined = this.storage_.get(propName);
    if (p === undefined) {
      return false;
    }

    const registrations = this.linksPropRegistrations_.get(propName);
    if (registrations && registrations.size > 0) {
      return false;
    }

    // can delete
    this.linksPropRegistrations_.delete(propName);
    this.storage_.delete(propName);
    return true;
  }

  protected clear(): boolean {
    if (this.linksPropRegistrations_.size > 0) {
      for (let propName of this.keys()) {
        if ((this.linksPropRegistrations_.get(propName) !== undefined)
          && (this.linksPropRegistrations_.get(propName)!.size > 0)) {
          return false;
        }
      }
    }
    this.storage_.clear();
    this.linksPropRegistrations_.clear();
    return true;
  }
}

/***************************************************** AppStorage ********************************************** */
export class AppStorage extends LocalStorage {
    public static createSingleton(/*initializingPropersties?: Object */): void {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage( /* initializingPropersties */);
        } else {
        }
    }

    /* TODO
    public static ref<T>(propName: string): AbstractProperty<T> | undefined {
       return AppStorage.getOrCreate().ref(propName);
    }*/


    /* TODO
    public static setAndRef<T>(propName: string, defaultValue: T): AbstractProperty<T> {
        return AppStorage.getOrCreate().setAndRef(propName, defaultValue);
    }*/


    public static link(key: string): LinkDecoratedVariable<Object> | undefined  {
        return AppStorage.getOrCreate().link(key);
    }

    public static setAndLink(key: string, defaultValue: Object) : LinkDecoratedVariable<Object>  {
        return AppStorage.getOrCreate().setAndLink(key, defaultValue);
    }

    public static prop(propName: string) : PropDecoratedVariable<Object> | undefined {
        return AppStorage.getOrCreate().prop(propName);
    }

    public static setAndProp(key: string, defaultValue: Object) : PropDecoratedVariable<Object> {
        return AppStorage.getOrCreate().setAndProp(key, defaultValue);
    }

    public static has(key: string): boolean {
        return AppStorage.getOrCreate().has(key);
    }

    public static get<T>(key: string): T | undefined {
        return AppStorage.getOrCreate().get<T>(key);
    }

    public static set<T>(key: string, newValue: T): boolean {
        return AppStorage.getOrCreate().set(key, newValue);
    }

    public static setOrCreate<T>(key: string, newValue: T): void {
        AppStorage.getOrCreate().setOrCreate(key, newValue);
    }

    public static delete(key: string): boolean {
        return AppStorage.getOrCreate().delete(key);
    }

    public static keys(): IterableIterator<string> {
        return AppStorage.getOrCreate().keys();
    }

    public static size(): number {
        return AppStorage.getOrCreate().size();
    }

    public static clear(): boolean {
        return AppStorage.getOrCreate().clear();
    }

    private static instance_: AppStorage | undefined = undefined;

    private static getOrCreate(): AppStorage {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage();
        }
        return AppStorage.instance_!;
    }

    protected constructor(/* initializingProperties: Object */) {
        super( /* initializingProperties */);
    }
}

/***************************************************** @StorageLink ********************************************** */
export class StorageLinkDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements DecoratedMutableVariable<T> {

    private asLink : LinkDecoratedVariable<Object> | undefined;
    constructor(propName: string, varName_: string, localValue: T, watchFunc?: WatchFuncType) {
        super(varName_, watchFunc);
        this.asLink = AppStorage.setAndLink(propName, localValue as Object);
        const value : T = this.asLink!.get() as T;
        this.registerWatchForObservedObjectChanges(value);
    }

    public getInfo(): string {
        return `@StorageLink ${this.varName_} (StorageLinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.asLink!.get() as T;
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        const oldValue : T = this.asLink!.get() as T;
        if ( oldValue != newValue) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(newValue);
            this.asLink!.set(newValue as Object);
            this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
        }
    }
}

/***************************************************** @StorageProp ********************************************** */
export class StoragePropDecoratedVariable<T> extends DecoratedV1VariableBase<T>
    implements DecoratedMutableVariable<T> {

    private asProp : PropDecoratedVariable<Object> | undefined;
    constructor(propName: string, varName:string, localVal: T, watchFunc?: WatchFuncType) {
        super(varName, watchFunc);
        this.asProp = AppStorage.setAndProp(propName, localVal as Object);
        const value : T = this.asProp!.get() as T;
        this.registerWatchForObservedObjectChanges(value);
    }

    public getInfo(): string {
        return `@StorageLink ${this.varName_} (StorageLinkDecoratedVariable)`;
    }

    public get(): T {
        const value = this.asProp!.get() as T;
        setObservationDepth(value, 1);
        return value;
    }

    public set(newValue: T): void {
        const oldValue : T = this.asProp!.get() as T;
        if ( oldValue != newValue) {
            this.unregisterWatchFromObservedObjectChanges(oldValue);
            this.registerWatchForObservedObjectChanges(newValue);
            this.asProp!.set(newValue as Object);
            this._watchFuncs.forEach((watchFunc) => { watchFunc.execute(this.varName_) });
        }
    }
}