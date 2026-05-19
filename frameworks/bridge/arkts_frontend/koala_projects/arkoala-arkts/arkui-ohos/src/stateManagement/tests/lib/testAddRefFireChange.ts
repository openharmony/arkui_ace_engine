import { IFactoryInternal } from '../../base/iFactoryInternal';
import { IBackingValue } from '../../base/iBackingValue';
import { IBackingValue } from '../../base/iBackingValue';
import { IMutableStateMeta, IObservedObject } from '../../decorator';
import { IMutableKeyedStateMeta } from '../../decorator';
import { DecoratorBackingValue } from '../../base/backingValue';
import {
    MutableStateMeta, MutableKeyedStateMeta, MonitorTarget,
} from '../../base/mutableStateMeta'
import { StateTracker } from './stateTracker.ts';
import { int32 } from '@koalaui/common';
import { TestMutableKeyedStateMeta } from '../../mock/trackedKeyedStateMeta';
export { TestMutableKeyedStateMeta };

export class TestFactory implements IFactoryInternal {

    public mkDecoratorValue<T>(info: string,
        initValue: T): IBackingValue<T> {
        return new TestDecoratorBackingValue<T>(info, initValue)
    }

    mkMutableStateMeta(info: string, target?: MonitorTarget): IMutableStateMeta {
        return new TestMutableStateMeta(info, target);
    }

    // IMutableKeyedStateMeta used by wrapper classes for Array, Map, Set, Date
    mkMutableKeyedStateMeta(info: string, observed?: IObservedObject): IMutableKeyedStateMeta {
        return new TestMutableKeyedStateMeta(info, observed);
    }

    mkObservedInterfaceProxy<T extends Object>(x: T): T {
        console.log('mkObservedInterfaceProxy not supported by TestFactory');
        return x;
    }

    mkInteropDecoratorValue<T>(info: string, initValue: T): IBackingValue<T> {
        return new TestDecoratorBackingValue<T>(info, initValue);
    }

    mkInteropV2DecoratorValue<T>(info: string, initValue: T): IBackingValue<T> {
        return new TestDecoratorBackingValue<T>(info, initValue);
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
    }

    public override fireChange(): void {
        super.fireChange();
        this.__fireChangeCount += 1;
        StateTracker.increaseFireChangeCnt();
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

export class TestMutableStateMeta extends MutableStateMeta {

    constructor(info: string, target?: MonitorTarget) {
        super(info, target);
    }

    private __refsCount: int32 = 0;
    private __fireChangeCount: int32 = 0;

    public override addRef(): void {
        super.addRef();
        this.__refsCount += 1;
    }

    public override fireChange(): void {
        super.fireChange();
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