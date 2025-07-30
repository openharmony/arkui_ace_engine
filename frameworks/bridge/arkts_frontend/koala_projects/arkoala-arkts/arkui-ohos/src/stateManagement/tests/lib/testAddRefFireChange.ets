
import { iFactoryInternal } from "stateManagement/base/iFactoryInternal";
import { IBackingValue } from "stateManagement/base/iBackingValue";
import { IMutableStateMeta, IMutableKeyedStateMeta } from "stateManagement/interface/iMutableStateMeta";
import { InterfaceProxyHandler } from "stateManagement/base/observeInterfaceProxy.ets";
import { DecoratorBackingValue } from "stateManagement/base/backingValue"
import { MutableStateMeta, MutableKeyedStateMeta } from 'stateManagement/base/mutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace'
import { int32 } from 'stateManagement/mock/env_mock'
import { StateTracker } from "./stateTracker.ets";

export class TestFactory implements iFactoryInternal {

    public mkDecoratorValue<T>(info: string,
        initValue: T): IBackingValue<T> {
        return new TestDecoratorBackingValue<T>(info, initValue)
    }

    makeMutableStateMeta(info: string): IMutableStateMeta {
        return new TestMutableStateMeta(info);
    }

    // IMutableKeyedStateMeta used by wrapper classes for Array, Map, Set, Date
    mkMutableKeyedStateMeta(info: string): IMutableKeyedStateMeta {
        return new TestMutableKeyedStateMeta(info);
    }

    mkObservedInterfaceProxy<T extends Object>(x: T): T {
        return Proxy.create(x, new InterfaceProxyHandler<T>()) as T;
    }
}


class TestDecoratorBackingValue<T> extends DecoratorBackingValue<T> {
    constructor(propertyName: string, initValue: T) {
        super(propertyName, initValue);
    }

    private __refsCount: int32 = 0;
    private __fireChangeCount: int32 = 0;

    public override addRef(): void {
        super.addRef();
        this.__refsCount += 1;
        StateTracker.increaseRefCnt();
        stateMgmtConsole.propertyAccess(`ADD REF ${this.propertyName_} ${this.__refsCount}`);
    }

    public override fireChange(): void {
        super.fireChange();
        this.__fireChangeCount += 1;
        StateTracker.increaseFireChangeCnt();
        stateMgmtConsole.propertyAccess(`Fire change ${this.propertyName_} ${this.__fireChangeCount}`);
    }

    public getFireChangeCnt(): int32 {
        return this.__fireChangeCount;
    }

    public getRefCnt(): int32 {
        return this.__refsCount;
    }

    public reset() {
        this.__fireChangeCount = 0;
        this.__refsCount = 0;
        StateTracker.reset();
    }
}


class TestMutableStateMeta extends MutableStateMeta {

    constructor(info: string) {
        super(info);
    }

    private __refsCount: int32 = 0;
    private __fireChangeCount: int32 = 0;

    public override addRef(): void {
        super.addRef();
        this.__refsCount += 1;
        stateMgmtConsole.propertyAccess(`ADD REF ${this!.info_} ${this.__refsCount}`);
    }

    public override fireChange(): void {
        super.fireChange();
        stateMgmtConsole.propertyAccess(`Fire change ${this.info_} ${this.__fireChangeCount}`);
        this.__fireChangeCount += 1;
    }

    public getFireChangeCnt(): int32 {
        return this.__fireChangeCount;
    }

    public getRefCnt(): int32 {
        return this.__refsCount;
    }

    public reset() {
        this.__fireChangeCount = 0;
        this.__refsCount = 0;
    }
}


export class TestMutableKeyedStateMeta extends MutableKeyedStateMeta {

    constructor(info: string) {
        super(info);
    }

    private refsMap: Map<string, number> = new Map<string, number>();
    private fireChangeMap: Map<string, int32> = new Map<string, number>();

    public override addRef(key: string): void {
        if (this.refsMap.get(key) === undefined) {
            this.refsMap.set(key, 0);
        }
        this.refsMap.set(key, this.refsMap.get(key)! + 1);

        super.addRef(key);

        stateMgmtConsole.propertyAccess(`MutableKeyedStateMeta addRef('${key}')`);
    }


    public override fireChange(key: string): void {
        if (this.fireChangeMap.get(key) === undefined) {
            this.fireChangeMap.set(key, 0);
        }
        this.fireChangeMap.set(key, this.fireChangeMap.get(key)! + 1);

        super.fireChange(key);

        if (this.__metaDependencies.get(key)) {
            stateMgmtConsole.propertyAccess(`MutableKeyedStateMeta fireChange('${key}')`);
        }
    }

    public getFireChangeCnt(key: string): int32 {
        const dep = this.fireChangeMap.get(key);
        return dep ?? 0;
    }

    public getRefCnt(key: string): int32 {
        return this.refsMap.get(key) ?? 0;
    }
}

// use this class to easier write assertions on
// addRef and fireChange count
export class TestMSM {
    // assert on TestMutableState
    public static getFireChangeCnt(obj: IMutableStateMeta): int32 {
        return (obj instanceof TestMutableStateMeta)
            ? obj.getFireChangeCnt() : 0;
    }
    public static getRefCnt(obj: IMutableStateMeta): int32 {
        return (obj instanceof TestMutableStateMeta)
            ? obj.getRefCnt() : 0;
    }

    // assert on TestKeyedMutableStateMeta
    public static getFireChangeCnt(obj: IMutableKeyedStateMeta, key: string): int32 {
        return (obj instanceof TestMutableKeyedStateMeta)
            ? obj.getFireChangeCnt(key) : 0
    }

    public static getRefCnt(obj: IMutableKeyedStateMeta, key: string): int32 {
        return (obj instanceof TestMutableKeyedStateMeta)
            ? obj.getRefCnt(key) : 0;
    }
}