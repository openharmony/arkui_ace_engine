import { int32 } from "@koalaui/compat";
import { mutableState } from "./GlobalStateManager";
import { MutableState } from "./State";
import { propDeepCopy } from "@koalaui/compat";

type WatchFunc = () => void;
export class MutableStateMetaBase {
    public readonly deco: string;
    constructor(deco: string) {
        this.deco = deco;
    }
}

export class MutableStateMeta extends MutableStateMetaBase {
    private __metaDependency: MutableState<int32> = mutableState<int32>(0);
    constructor(deco: string) {
        super(deco);
    }
    public addRef(): void {
        this.__metaDependency.value;
    }
    public fireChange(): void {
        this.__metaDependency.value++;
    }
}

export class MutableKeyedStateMeta extends MutableStateMetaBase {
    public static readonly OB_LENGTH = '__OB_LENGTH';
    private __metaDependency: Map<string, MutableState<int32>> = new Map<string, MutableState<int32>>();

    public addRef(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependency.get(key);
        if (!metaDependency) {
            metaDependency = mutableState<int32>(0);
            this.__metaDependency.set(key, metaDependency);
        }
        metaDependency.value;
    }

    public fireChange(key: string): void {
        let metaDependency: MutableState<int32> | undefined = this.__metaDependency.get(key);
        if (metaDependency) {
            metaDependency.value++;
        }
    }
    constructor(deco: string) {
        super(deco);
    }
}

export interface IObservedObject {
    _permissibleAddRefDepth: int32;
    subscribers: Set<int32>;
    // subscribe(id: int32): void;
    // unsubscribe(id: int32): void;
    // trigger(): void;
}

export function castToIObservedObject<T>(obj: T): T | undefined {
    // return (obj && typeof obj === 'object') 
    // ? (obj as unknown as IObservedObject) 
    // : undefined;
    return obj;
}

export function setObservationDepth<T>(obj: T, depth: number): void {
    const objOpt = castToIObservedObject(obj);
    if (objOpt) {
        // (objOpt as IObservedObject)._permissibleAddRefDepth = depth
    }
}

export interface DecoratedImmutableVariable<T> {
    get(): T;
}
export interface DecoratedMutableVariable<T> {
    get(): T;
    set(newValue: T): void;
}
export interface DecoratedUpdatableVariable<T> {
    update(newValue: T): void;
}
export interface DecoratedV1Variable {
    _watchFunc: WatchFunc | undefined;
}
export abstract class DecoratedVariableBase<T> {
    public readonly _meta: MutableState<int32> = mutableState<int32>(0);
    constructor() {
    }
    public addRef(): void {
        this._meta.value;
    }
    public fireChange(): void {
        this._meta.value += 1;
    }
    public validateValue(newValue: T): boolean {
        // if ()
        return true;
    }
}
export class StateDecoratedVariable<T> extends DecoratedVariableBase<T> implements DecoratedMutableVariable<T>, DecoratedUpdatableVariable<T>, DecoratedV1Variable {
    public readonly _watchFunc: WatchFunc | undefined;
    private __backing: T;

    constructor(localInitValue: T, watchFunc?: ()=>void) {
        super();
        this.validateValue(localInitValue);
        this.__backing = localInitValue;
        this._watchFunc = watchFunc;
    }
    public get(): T {
        const value = this.__backing;
        setObservationDepth(value, 1);
        this.addRef();
        return value;
    }

    public set(newValue: T): void {
        if (this.__backing != newValue) {
            this.validateValue(newValue);
            this.__backing = newValue;
            this.fireChange();
            this._watchFunc?.();
        }
    }
    public update(newValue: T): void {
        if (this.__backing != newValue) {
            this.validateValue(newValue);
            this.__backing = newValue;
            this.fireChange();
        }
    }
}
export class LinkDecoratedVariable<T>  implements DecoratedMutableVariable<T>, DecoratedV1Variable {
	public _watchFunc: WatchFunc | undefined;
	private sourceGet_: () => T;
    private sourceSet_?: (newValue: T) => void;
	
	constructor(sourceGet_: ()=>T, sourceSet_?: (newValue: T)=>void, watchFunc?: WatchFunc) {
		this._watchFunc = watchFunc;
        this.sourceGet_ = sourceGet_;
        this.sourceSet_ = sourceSet_;
	}
	
	public get(): T {
		const value = this.sourceGet_();
		setObservationDepth(value, 1);
		return value;
	}
	public set(newValue: T): void {
		if (this.sourceGet_() != newValue) {
            if (this.sourceSet_ === undefined) {
                return;
            }
        }
        this.sourceSet_!(newValue);
        this._watchFunc?.();
	}
}

function deepCopy<T>(value: T): T {
    return propDeepCopy<T>(value) as T;
}

export class PropDecoratedVariable<T> extends DecoratedVariableBase<T> implements DecoratedMutableVariable<T>, DecoratedV1Variable, DecoratedUpdatableVariable<T> {
    public readonly _watchFunc: WatchFunc | undefined;
    private __backing: T;
    private __sourceValue: T;
    constructor(source_value: T, watchFunc?: WatchFunc) {
        super();
        this._watchFunc = watchFunc;
        this.__backing = deepCopy<T>(source_value);
        this.__sourceValue = source_value;
    }
    public get(): T {
        setObservationDepth(this.__backing, 1);
        this.addRef();
        return this.__backing;
    }

    public set(newValue: T): void {
        if (this.__backing != newValue) {
            this.__backing = deepCopy<T>(newValue);
            this.fireChange();
            this._watchFunc?.();
        }
    }
    public update(newValue: T): void {
        this.addRef();
        if (this.__sourceValue != newValue) {
            this.__backing = deepCopy<T>(newValue);
            this.__sourceValue = newValue;
            StateMgmtLoop.add(() => {
                this.fireChange();
                this._watchFunc?.();
            });
        }
    }
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