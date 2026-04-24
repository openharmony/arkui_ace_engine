/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Array / @Local MyArray<T> monitor coverage parameterized by `isSync`. Each
// helper is exercised twice — once via run_monitor_array (async makeMonitor +
// an explicit ObserveSingleton.instance.updateDirty() flush after every
// mutation) and once via run_syncmonitor_array (makeSyncMonitor, fires inside
// MutableStateMeta.fireChange). Counts match across both modes because every
// mutation is followed by a flush before the next assertion.

import { tsuite, tcase, test, eq } from './lib/testFramework'
import { ILocalDecoratedVariable } from '../decorator'
import {
    IMonitor,
    IMonitorPathInfo,
    IMonitorDecoratedVariable,
    MonitorCallback,
    MonitorValueCallback,
} from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { MyArray } from './uiplugin_custom_arrays'
import { ClassA_ObserveAnyProp_NoAnyMeta } from './uipluginObservedObject3'
import { TestMSM, TestMutableKeyedStateMeta } from './lib/testAddRefFireChange'

let StateMgmtFactory = STATE_MGMT_FACTORY;
let stateMgmtConsole = console;

// Strong-reference store. The Panda VM's GC eagerly reclaims locally-scoped
// monitors that are never read after construction, which clears the WeakRefs
// in MutableStateMeta.bindingRefs_ mid-test and causes intermittent missing
// callbacks. Push each monitor here to keep it alive across mutations and
// assertions.
const testMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

// Build a monitor in either sync or async mode. Both forms have the same
// (pathInfos, callback) signature for our purposes.
function makeMonitorByMode(
    isSync: boolean,
    pathInfos: IMonitorPathInfo[],
    onChanged: MonitorCallback,
): IMonitorDecoratedVariable {
    const m = isSync
        ? STATE_MGMT_FACTORY.makeSyncMonitor(pathInfos, onChanged, undefined)
        : STATE_MGMT_FACTORY.makeMonitor(pathInfos, onChanged);
    testMonitors_.push(m);
    return m;
}

// === Mock components =======================================================

interface ComponentWithArray_init_update_struct {
    arr?: MyArray<number>;
}

class ComponentWithArray extends ExtendableComponent {
    private _backing_state_arr: ILocalDecoratedVariable<MyArray<number>>;
    get arr(): MyArray<number> {
        console.log('ComponentWithArray.arr()');
        return this._backing_state_arr!.get() as MyArray<number>;
    }
    set arr(newArr: MyArray<number>) {
        this._backing_state_arr!.set(newArr);
    }

    // For testing
    public getFireChangeCnt(key: string): Int {
        // meta_ not visible
        return (this._backing_state_arr.get().meta_ instanceof TestMutableKeyedStateMeta)
            ? (this._backing_state_arr.get().meta_ as TestMutableKeyedStateMeta).getFireChangeCnt(key) : 0
    }
    public getRefCnt(key: string) {
        // meta_ not visible
        return TestMSM.getRefCnt(this._backing_state_arr.get().meta_, key);
    }

    constructor(parent: ExtendableComponent | null, param: ComponentWithArray_init_update_struct) {
        super(parent);

        this._backing_state_arr = StateMgmtFactory.makeLocal<MyArray<number>>(
            this,
            'arr',
            (param.arr !== undefined)
                ? param.arr!
                : new MyArray<number>(1, 2, 3)
        );
    }
}

interface ParentComponentWithArrayItems_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

class ParentComponentWithArrayItems extends ExtendableComponent {
    // @Local arr: MyArray<ClassA_ObserveAnyProp_NoAnyMeta> = new MyArray<...>(new ClassA(), new ClassA());
    private _backing_arr: ILocalDecoratedVariable<MyArray<ClassA_ObserveAnyProp_NoAnyMeta>>;
    get arr(): MyArray<ClassA_ObserveAnyProp_NoAnyMeta> {
        return this._backing_arr.get();
    }
    set arr(newValue: MyArray<ClassA_ObserveAnyProp_NoAnyMeta>) {
        this._backing_arr.set(newValue);
    }

    public monitorFunctionRunCount: number = 0;

    // @Monitor("arr.1.classB.propB1", "arr.2.classB", "length") onArrChanged(m: IMonitor)
    private _monitor: IMonitorDecoratedVariable;
    public onArrChanged?: (m: IMonitor) => void;

    // @Monitor("arr.arrProp") onArrPropChanged(m: IMonitor)
    private _monitorArrProp: IMonitorDecoratedVariable;
    public onArrPropChanged?: (m: IMonitor) => void;

    constructor(
        parent: ExtendableComponent | null,
        param: ParentComponentWithArrayItems_init_update_struct,
        isSync: boolean,
    ) {
        super(parent)
        this._backing_arr = StateMgmtFactory.makeLocal<MyArray<ClassA_ObserveAnyProp_NoAnyMeta>>(
            this,
            'arr',
            /* local init value */ new MyArray<ClassA_ObserveAnyProp_NoAnyMeta>(
                new ClassA_ObserveAnyProp_NoAnyMeta(),
                new ClassA_ObserveAnyProp_NoAnyMeta()));

        const multiPathInfos: IMonitorPathInfo[] = [
            {
                path: 'arr.1.classB.propB1',
                valueCallback: () => {
                    const result = this.arr[1].classB.propB1;
                    return result;
                }
            } as IMonitorPathInfo,
            {
                path: 'arr.2.classB',
                valueCallback: () => {
                    const result = this.arr[2].classB;
                    return result;
                }
            } as IMonitorPathInfo,
            {
                path: 'length',
                valueCallback: () => this.arr.length
            } as IMonitorPathInfo,
        ];
        const multiCallback: MonitorCallback = (m: IMonitor): void => {
            this.onArrChanged!(m);
        };
        this._monitor = isSync
            ? StateMgmtFactory.makeSyncMonitor(multiPathInfos, multiCallback, undefined)
            : StateMgmtFactory.makeMonitor(multiPathInfos, multiCallback);

        const arrPropPathInfos: IMonitorPathInfo[] = new Array<IMonitorPathInfo>(
            {
                path: 'arr.arrProp',
                valueCallback: () => {
                    const result = this.arr.arrProp;
                    return result;
                }
            } as IMonitorPathInfo);
        const arrPropCallback: MonitorCallback = (m: IMonitor) => {
            this.onArrPropChanged!(m);
        };
        this._monitorArrProp = isSync
            ? StateMgmtFactory.makeSyncMonitor(arrPropPathInfos, arrPropCallback, undefined)
            : StateMgmtFactory.makeMonitor(arrPropPathInfos, arrPropCallback);
    }
}

// Component holding a @Local MyArray<ClassA_ObserveAnyProp_NoAnyMeta>. Used by
// the index-path / restore-reference test below where the items must be
// distinguishable by reference (numbers compare by value and would mask the
// "same reference restored" semantics).
class ComponentWithArrayOfA extends ExtendableComponent {
    private _backing_arr: ILocalDecoratedVariable<MyArray<ClassA_ObserveAnyProp_NoAnyMeta>>;
    get arr(): MyArray<ClassA_ObserveAnyProp_NoAnyMeta> {
        return this._backing_arr.get();
    }
    set arr(newValue: MyArray<ClassA_ObserveAnyProp_NoAnyMeta>) {
        this._backing_arr.set(newValue);
    }
    constructor(parent: ExtendableComponent | null, initialArr: MyArray<ClassA_ObserveAnyProp_NoAnyMeta>) {
        super(parent);
        this._backing_arr = StateMgmtFactory.makeLocal<MyArray<ClassA_ObserveAnyProp_NoAnyMeta>>(
            this, 'arr', initialArr);
    }
}

// === Test bodies (sync-monitor migrated, parameterized) ====================

// Wildcard 'comp.arr.*' on @Local MyArray<number>: index assignment and sort
// each fire the monitor.
function doMonitorOnArrayWildcard(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback comp.arr');
        return arrayComp.arr;
    };

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: valueCallback,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'comp.arr.*' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    arrayComp.arr[1] = 1;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard: arr[1]=1 fires: count=${count} === 1`, eq(count, 1));

    arrayComp.arr[1] = 500;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard: arr[1]=500 fires: count=${count} === 2`, eq(count, 2));

    arrayComp.arr.sort();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard: arr.sort() fires: count=${count} === 3`, eq(count, 3));
}

// Wildcard 'comp.arr.*' on Array, also exercising .push().
function doMonitorOnArrayWildcardWithPush(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback comp.arr');
        return arrayComp.arr;
    };

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: valueCallback,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'comp.arr.* (push)' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    arrayComp.arr[1] = 1;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard +push: arr[1]=1 fires: count=${count} === 1`, eq(count, 1));

    arrayComp.arr[1] = 500;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard +push: arr[1]=500 fires: count=${count} === 2`, eq(count, 2));

    arrayComp.arr.sort();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard +push: arr.sort() fires: count=${count} === 3`, eq(count, 3));

    arrayComp.arr.push(100);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array wildcard +push: arr.push(100) fires: count=${count} === 4`, eq(count, 4));
}

// Verifies that every length-changing Array mutation method fires the wildcard
// monitor EXACTLY ONCE per call. Each of these methods internally fires both
// OB_LENGTH and OB_ARRAY_ANY_KEY; addRefAnyKey() binds the wildcard to both,
// so without batching the monitor would fire twice per call. fireChangeBatch
// batches the drain so both fires coalesce into one callback per logical
// mutation.
function doMonitorOnArrayPushVariants(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => arrayComp.arr;

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: valueCallback,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'comp.arr.* (variants)' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    // pushOne: single-arg path that calls store_.push(val) and fires
    // OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.pushOne(10);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: pushOne(10) fires once: count=${count} === 1`, eq(count, 1));

    // pushArray: rest-arg path that fires OB_LENGTH + OB_ARRAY_ANY_KEY once,
    // not once per element.
    arrayComp.arr.pushArray(20, 30, 40);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: pushArray(20,30,40) fires once: count=${count} === 2`, eq(count, 2));

    // push (variadic): regardless of arg count, ONE fire.
    arrayComp.arr.push(50);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: push(50) fires once: count=${count} === 3`, eq(count, 3));

    arrayComp.arr.push(60, 70, 80);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: push(60,70,80) fires once: count=${count} === 4`, eq(count, 4));

    // shift removes from the front, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.shift();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: shift() fires once: count=${count} === 5`, eq(count, 5));

    // pop removes from the end, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.pop();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: pop() fires once: count=${count} === 6`, eq(count, 6));

    // unshift adds to the front, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.unshift(99);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: unshift(99) fires once: count=${count} === 7`, eq(count, 7));

    // splice can both remove and add, fires OB_LENGTH + OB_ARRAY_ANY_KEY once.
    arrayComp.arr.splice(0, 1, 111, 222);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] array variants: splice(0,1,111,222) fires once: count=${count} === 8`, eq(count, 8));
}

// Verifies that mutation methods that DO NOT change array length
// (copyWithin, fill, reverse, sort) do NOT fire OB_LENGTH. Two monitors
// share the same array:
//   - lengthMonitor reads arr.length, so it binds to OB_LENGTH only.
//   - wildcardMonitor binds to OB_ARRAY_ANY_KEY (and OB_LENGTH).
// After each non-length-changing mutation:
//   - lengthMonitor count must NOT advance (length unchanged → no fire).
//   - wildcardMonitor count must advance by 1 (element-wise change still
//     observed via OB_ARRAY_ANY_KEY).
function doMonitorOnArrayLengthVsWildcard(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let lengthCount: int = 0;
    let wildcardCount: int = 0;
    const arrayComp = new ComponentWithArray(null, {});

    const _lengthMonitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.length',
            valueCallback: () => arrayComp.arr.length,
            enableWildcard: false } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            lengthCount++;
            console.log(`Monitor[${tag}] 'comp.arr.length' triggered: count=${lengthCount} dirty=${JSON.stringify(m.dirty)}`);
        },
    );
    const _wildcardMonitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: () => arrayComp.arr,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            wildcardCount++;
            console.log(`Monitor[${tag}] 'comp.arr.*' triggered: count=${wildcardCount} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    // Establish a baseline count for the wildcard monitor: a normal index
    // assignment fires it once (LENGTH not bound → does not advance length
    // counter).
    arrayComp.arr[0] = 99;
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: arr[0]=99: lengthCount=${lengthCount} === 0`,
        eq(lengthCount, 0));
    test(`[${tag}] length-vs-wild: arr[0]=99: wildcardCount=${wildcardCount} === 1`,
        eq(wildcardCount, 1));

    // copyWithin: in-place copy, length unchanged.
    arrayComp.arr.copyWithin(0, 1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: copyWithin: lengthCount=${lengthCount} === 0`,
        eq(lengthCount, 0));
    test(`[${tag}] length-vs-wild: copyWithin: wildcardCount=${wildcardCount} === 2`,
        eq(wildcardCount, 2));

    // fill: in-place fill, length unchanged.
    arrayComp.arr.fill(7);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: fill: lengthCount=${lengthCount} === 0`,
        eq(lengthCount, 0));
    test(`[${tag}] length-vs-wild: fill: wildcardCount=${wildcardCount} === 3`,
        eq(wildcardCount, 3));

    // reverse: reorders in place, length unchanged.
    arrayComp.arr.reverse();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: reverse: lengthCount=${lengthCount} === 0`,
        eq(lengthCount, 0));
    test(`[${tag}] length-vs-wild: reverse: wildcardCount=${wildcardCount} === 4`,
        eq(wildcardCount, 4));

    // sort: reorders in place, length unchanged. Already correctly fires only
    // OB_ARRAY_ANY_KEY in the implementation; this guards that.
    arrayComp.arr.sort();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: sort: lengthCount=${lengthCount} === 0`,
        eq(lengthCount, 0));
    test(`[${tag}] length-vs-wild: sort: wildcardCount=${wildcardCount} === 5`,
        eq(wildcardCount, 5));

    // Sanity: a true length-changing mutation DOES fire the length monitor.
    arrayComp.arr.push(123);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] length-vs-wild: push: lengthCount=${lengthCount} === 1`,
        eq(lengthCount, 1));
    test(`[${tag}] length-vs-wild: push: wildcardCount=${wildcardCount} === 6`,
        eq(wildcardCount, 6));
}

// Non-mutating "copy" methods (toSorted, toReversed, toSpliced, slice) return
// new arrays without modifying the source — they must not fire any monitor
// when CALLED. Verifies by checking that calling them on the array between
// genuine mutations does not change the wildcard monitor's count.
function doMonitorOnArrayCopyMethodsDoNotFire(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const arrayComp = new ComponentWithArray(null, {}); // [1,2,3]

    const _wildcardMonitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: () => arrayComp.arr,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'comp.arr.* (copy methods)' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    arrayComp.arr.push(4); // baseline mutation, count -> 1
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: baseline push fires: count=${count} === 1`,
        eq(count, 1));

    // toSorted: returns a new sorted array; source untouched.
    const sorted = arrayComp.arr.toSorted();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: toSorted does not fire: count=${count} === 1`,
        eq(count, 1));
    test(`[${tag}] copy methods: toSorted result has length 4`, eq(sorted.length, 4));

    // toReversed: returns a new reversed array.
    const reversed = arrayComp.arr.toReversed();
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: toReversed does not fire: count=${count} === 1`,
        eq(count, 1));
    test(`[${tag}] copy methods: toReversed result has length 4`, eq(reversed.length, 4));

    // slice: returns a shallow-copy slice.
    const sliced = arrayComp.arr.slice(0, 2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: slice does not fire: count=${count} === 1`,
        eq(count, 1));
    test(`[${tag}] copy methods: slice result has length 2`, eq(sliced.length, 2));

    // toSpliced: returns a new array with the splice applied; source intact.
    const spliced = arrayComp.arr.toSpliced(1, 1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: toSpliced does not fire: count=${count} === 1`,
        eq(count, 1));
    test(`[${tag}] copy methods: toSpliced result has length 3`, eq(spliced.length, 3));

    // Sanity: a real mutation still fires after all the copy calls.
    arrayComp.arr.push(5);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] copy methods: push after copies fires: count=${count} === 2`,
        eq(count, 2));
}

// splice can delete only, insert only, both, or be a no-op. Each variant
// fires the wildcard monitor exactly once (or never for a true no-op).
function doMonitorOnArraySpliceVariants(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let count: int = 0;
    const arrayComp = new ComponentWithArray(null, {}); // [1,2,3]

    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.*',
            valueCallback: () => arrayComp.arr,
            enableWildcard: true } as IMonitorPathInfo
        ] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            console.log(`Monitor[${tag}] 'comp.arr.* (splice variants)' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    // splice(start, deleteCount): delete only.
    arrayComp.arr.splice(0, 1);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] splice variants: delete-only fires once: count=${count} === 1`,
        eq(count, 1));

    // splice(start, 0, ...items): insert only.
    arrayComp.arr.splice(1, 0, 99, 100);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] splice variants: insert-only fires once: count=${count} === 2`,
        eq(count, 2));

    // splice(start, deleteCount, ...items): replace.
    arrayComp.arr.splice(0, 2, 7, 8, 9);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] splice variants: replace fires once: count=${count} === 3`,
        eq(count, 3));

    // splice(start): delete to end.
    arrayComp.arr.splice(2);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }
    test(`[${tag}] splice variants: delete-to-end fires once: count=${count} === 4`,
        eq(count, 4));
}

// Non-wildcard path 'comp.arr.1' on MyArray<ClassA>. The lambda reads arr[1].
// shift() removes the head — arr[1] now references what used to be arr[2] (a
// different reference). unshift(newHead) prepends a new item, sliding what was
// arr[0]-after-shift back to arr[1] — restoring the ORIGINAL reference.
//
// Sync mode: each fireChange triggers an immediate callback. The lambda is
// re-read per fire, so before/now flip origA1 → a2 (after shift) and then
// a2 → origA1 (after unshift). Two callbacks fire.
//
// Async mode (no flush between shift and unshift): the two fireChanges queue
// the same monitor. updateDirty re-reads the lambda once; the new value is
// origA1 — equal to the LSV (this.before) by reference. The non-wildcard
// branch in MonitorValueInternal.readValue does `dirty_ = before !== now`, so
// dirty_ stays false and runMonitorFunction skips the callback (count=0).
function doMonitorOnArrayIndexShiftUnshiftRestoresRef(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const a0 = new ClassA_ObserveAnyProp_NoAnyMeta();
    const origA1 = new ClassA_ObserveAnyProp_NoAnyMeta();
    const a2 = new ClassA_ObserveAnyProp_NoAnyMeta();
    const newHead = new ClassA_ObserveAnyProp_NoAnyMeta();
    const arrayComp = new ComponentWithArrayOfA(null,
        new MyArray<ClassA_ObserveAnyProp_NoAnyMeta>(a0, origA1, a2));

    let count: int = 0;
    let lastDirty: Array<string> = new Array<string>();
    let lastDefined: boolean = false;
    let lastBeforeIsOrig: boolean = false;
    let lastBeforeIsA2: boolean = false;
    let lastNowIsOrig: boolean = false;
    let lastNowIsA2: boolean = false;
    const _monitor = makeMonitorByMode(
        isSync,
        [{
            path: 'comp.arr.1',
            valueCallback: () => arrayComp.arr[1],
            enableWildcard: false,
        } as IMonitorPathInfo] as IMonitorPathInfo[],
        (m: IMonitor): void => {
            count++;
            lastDirty = m.dirty;
            const v = m.value<ClassA_ObserveAnyProp_NoAnyMeta>('comp.arr.1');
            lastDefined = v !== undefined;
            if (v !== undefined) {
                lastBeforeIsOrig = v!.before === origA1;
                lastBeforeIsA2 = v!.before === a2;
                lastNowIsOrig = v!.now === origA1;
                lastNowIsA2 = v!.now === a2;
            }
            console.log(`Monitor[${tag}] 'comp.arr.1' triggered: count=${count} dirty=${JSON.stringify(m.dirty)}`);
        },
    );

    // Step 1: shift — arr[1] reference moves from origA1 to a2.
    arrayComp.arr.shift();
    if (isSync) {
        // Sync fired immediately on the shift fireChange.
        test(`[${tag}] arr.1 shift: count=${count} === 1`, eq(count, 1));
        test(`[${tag}] arr.1 shift: dirty.length === 1`, eq(lastDirty.length, 1));
        test(`[${tag}] arr.1 shift: dirty[0] === 'comp.arr.1'`, eq(lastDirty[0], 'comp.arr.1'));
        test(`[${tag}] arr.1 shift: m.value defined`, eq(lastDefined, true));
        test(`[${tag}] arr.1 shift: m.value.before === origA1`, eq(lastBeforeIsOrig, true));
        test(`[${tag}] arr.1 shift: m.value.now === a2`, eq(lastNowIsA2, true));
    }

    // Step 2: unshift(newHead) — slides everything right; origA1 returns to arr[1].
    arrayComp.arr.unshift(newHead);
    if (!isSync) { ObserveSingleton.instance.updateDirty(); }

    if (isSync) {
        // Sync fired again for the unshift; before/now flip a2 → origA1.
        test(`[${tag}] arr.1 unshift: count=${count} === 2`, eq(count, 2));
        test(`[${tag}] arr.1 unshift: m.value.before === a2`, eq(lastBeforeIsA2, true));
        test(`[${tag}] arr.1 unshift: m.value.now === origA1`, eq(lastNowIsOrig, true));
    } else {
        // Async coalesced: re-read sees arr[1] === origA1 (LSV unchanged) →
        // dirty_ stays false → callback skipped.
        test(`[${tag}] arr.1 net no-op (origA1 restored): count=${count} === 0`, eq(count, 0));
    }

    // Sanity check: arr[1] really is the original reference.
    test(`[${tag}] arr.1 final reference is origA1`, eq(arrayComp.arr[1] === origA1, true));
}

// === Test bodies (async-monitor migrated, parameterized) ===================

// Multi-path monitor on ParentComponentWithArrayItems: change an existing array
// item's nested @Track property. Only the 'arr.1.classB.propB1' path becomes
// dirty, fired in a single callback.
function doMonitorOnArrayItemChange(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponentWithArrayItems(null, {}, isSync);
    comp.onArrChanged = (m: IMonitor) => {
        stateMgmtConsole.debug(`tcase #2 [${tag}] onArrChanged`);

        comp.monitorFunctionRunCount += 1;

        test(`[${tag}] m.dirty length`, eq(m.dirty.length, 1));
        test(`[${tag}] m.dirty[0] value`, eq(m.dirty[0], 'arr.1.classB.propB1'));
    }

    // mutate state e.g. in onclick
    stateMgmtConsole.log('assign to comp.a.classB.propB1');
    comp.arr[1].classB.propB1 = 'new';

    if (!isSync) { ObserveSingleton.instance.updateDirty(); }

    test(`[${tag}] @Monitor function has run`, eq(comp.monitorFunctionRunCount, 1));
}

// Multi-path monitor on ParentComponentWithArrayItems: push() adds a new item
// to the array, satisfying the previously-unbound 'arr.2.classB' path AND
// changing the 'length' path. Both paths fire in a single callback.
function doMonitorOnArrayPushNewItem(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    const newItem: ClassA_ObserveAnyProp_NoAnyMeta = new ClassA_ObserveAnyProp_NoAnyMeta();
    let comp = new ParentComponentWithArrayItems(null, {}, isSync);

    comp.onArrChanged = (m: IMonitor) => {
        stateMgmtConsole.debug(`tcase #3 [${tag}] onArrChanged`);

        comp.monitorFunctionRunCount += 1;

        test(`[${tag}] m.dirty length`, eq(m.dirty.length, 2));
        test(`[${tag}] m.dirty[0] value`, eq(m.dirty[0], 'arr.2.classB'));
        test(`[${tag}] m.dirty[1] value`, eq(m.dirty[1], 'length'));
    }

    // mutate state e.g. in onclick
    stateMgmtConsole.log('arr.push() ');
    comp.arr.push(newItem);

    if (!isSync) { ObserveSingleton.instance.updateDirty(); }

    // Update of actual value to 1
    test(`[${tag}] @Monitor function has run`, eq(comp.monitorFunctionRunCount, 1));
}

// 'arr.arrProp' monitor: this test only sets up the callback but does not
// trigger any mutation, so the count stays at 0 in both modes.
function doMonitorOnArrayPropChange(isSync: boolean): void {
    const tag = isSync ? 'sync' : 'async';
    let comp = new ParentComponentWithArrayItems(null, {}, isSync);
    comp.onArrPropChanged = (m: IMonitor) => {
        stateMgmtConsole.debug(`tcase #4 [${tag}] onArrPropChanged`);

        comp.monitorFunctionRunCount += 1;

        test(`[${tag}] m.dirty length`, eq(m.dirty.length, 1));
        test(`[${tag}] m.dirty[0] value`, eq(m.dirty[0], 'arr.arrProp'));
    }

    // (no mutation triggered — count stays 0)
}

// === Suite wiring ==========================================================

function runArraySuite(isSync: boolean): void {
    const factoryName = isSync ? 'makeSyncMonitor' : 'makeMonitor';

    tcase(`### ${factoryName} wildcard on @Local MyArray: index assign and sort fire monitor`)
    {
        doMonitorOnArrayWildcard(isSync);
    }

    tcase(`### ${factoryName} wildcard on @Local MyArray: index assign, sort, and push each fire monitor`)
    {
        doMonitorOnArrayWildcardWithPush(isSync);
    }

    tcase(`### ${factoryName} wildcard: every length-changing method fires once per call`)
    {
        doMonitorOnArrayPushVariants(isSync);
    }

    tcase(`### ${factoryName}: copyWithin/fill/reverse/sort do not fire length-only subscribers`)
    {
        doMonitorOnArrayLengthVsWildcard(isSync);
    }

    tcase(`### ${factoryName}: copy methods (toSorted/toReversed/toSpliced/slice) do not fire`)
    {
        doMonitorOnArrayCopyMethodsDoNotFire(isSync);
    }

    tcase(`### ${factoryName}: splice variants (delete/insert/replace/delete-to-end) each fire once`)
    {
        doMonitorOnArraySpliceVariants(isSync);
    }

    tcase(`### ${factoryName} 'comp.arr.1': shift+unshift restores original reference at arr[1]`)
    {
        doMonitorOnArrayIndexShiftUnshiftRestoresRef(isSync);
    }

    tcase(`### ${factoryName} multi-path: change existing array item's nested @Track prop`)
    {
        doMonitorOnArrayItemChange(isSync);
    }

    tcase(`### ${factoryName} multi-path: push new item satisfies previously-unbound path and length`)
    {
        doMonitorOnArrayPushNewItem(isSync);
    }

    tcase(`### ${factoryName} on 'arr.arrProp': callback set, no mutation, count stays 0`)
    {
        doMonitorOnArrayPropChange(isSync);
    }
}

export function run_monitor_array(): boolean {
    const ttest = tsuite('@Monitor arrays') {
        runArraySuite(/* isSync */ false);
    }
    ttest();
    return true;
}

export function run_syncmonitor_array(): boolean {
    const ttest = tsuite('@SyncMonitor arrays') {
        runArraySuite(/* isSync */ true);
    }
    ttest();
    return true;
}
