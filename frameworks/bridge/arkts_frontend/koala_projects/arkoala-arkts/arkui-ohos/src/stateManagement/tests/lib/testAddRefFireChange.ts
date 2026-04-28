import { IFactoryInternal } from '../../base/iFactoryInternal';
import { IBackingValue } from '../../base/iBackingValue';
import { IBackingValue } from '../../base/iBackingValue';
import { IMutableStateMeta } from '../../decorator';
import { IMutableKeyedStateMeta } from '../../decorator';
import { DecoratorBackingValue } from '../../base/backingValue';
import { MutableStateMeta, MutableKeyedStateMeta } from '../../base/mutableStateMeta'
import { StateTracker } from "./stateTracker.ts";
import { int32 } from '@koalaui/common';

export class TestFactory implements IFactoryInternal {

    public mkDecoratorValue<T>(info: string,
        initValue: T): IBackingValue<T> {
        return new TestDecoratorBackingValue<T>(info, initValue)
    }

    mkMutableStateMeta(info: string): IMutableStateMeta {
        return new TestMutableStateMeta(info);
    }

    // IMutableKeyedStateMeta used by wrapper classes for Array, Map, Set, Date
    mkMutableKeyedStateMeta(info: string): IMutableKeyedStateMeta {
        return new TestMutableKeyedStateMeta(info);
    }

    mkObservedInterfaceProxy<T extends Object>(x: T): T {
        console.log("mkObservedInterfaceProxy not supported by TestFactory");
        return x;
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
        //StateMgmtConsole.propertyAccess(`ADD REF ${this.propertyName_} ${this.__refsCount}`);
    }

    public override fireChange(): void {
        super.fireChange();
        this.__fireChangeCount += 1;
        StateTracker.increaseFireChangeCnt();
        //StateMgmtConsole.propertyAccess(`Fire change ${this.propertyName_} ${this.__fireChangeCount}`);
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
        //stateMgmtConsole.propertyAccess(`ADD REF ${this!.info_} ${this.__refsCount}`);
    }

    public override fireChange(): void {
        super.fireChange();
        //stateMgmtConsole.propertyAccess(`Fire change ${this.info_} ${this.__fireChangeCount}`);
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

    private refsMap: Map<string, int> = new Map<string, int>();
    private fireChangeMap: Map<string, int32> = new Map<string, int32>();

    public override addRef(key: string): void {
        if (this.refsMap.get(key) === undefined) {
            this.refsMap.set(key, 0);
        }
        this.refsMap.set(key, this.refsMap.get(key)! + 1);

        super.addRef(key);

        //stateMgmtConsole.propertyAccess(`MutableKeyedStateMeta addRef('${key}')`);
    }


    public override fireChange(key: string): void {
        if (this.fireChangeMap.get(key) === undefined) {
            this.fireChangeMap.set(key, 0);
        }
        this.fireChangeMap.set(key, this.fireChangeMap.get(key)! + 1);

        super.fireChange(key);

        if (this.__metaDependencies.get(key)) {
            //stateMgmtConsole.propertyAccess(`MutableKeyedStateMeta fireChange('${key}')`);
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