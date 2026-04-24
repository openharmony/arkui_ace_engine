/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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


import { tsuite, tcase, test, eq } from './lib/testFramework'
import { ILocalDecoratedVariable }  from '../decorator'
import { IMonitor, IMonitorPathInfo, IMonitorDecoratedVariable, MonitorCallback, MonitorValueCallback } from '../decorator'
import { ExtendableComponent } from '../mock/extendableComponent';

import { ClassB_SingleMeta } from './uipluginObservedObject3'
import { MyArray } from './uiplugin_custom_arrays'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { uiUtils } from '../base/uiUtilsImpl';
import { UIUtils, MonitorOptions } from '../utils';
import { TestMSM, TestMutableKeyedStateMeta } from './lib/testAddRefFireChange'

let StateMgmtFactory = STATE_MGMT_FACTORY;
let stateMgmtConsole=console;

// === Test helpers ===========================================================

// Counter shared by a sync-monitor callback (writer) and the assertion (reader).
class CallCounter {
    public count: int = 0;
    public increment(): void {
        this.count++;
    }
}

// Strong-reference store for monitors created by installSyncMonitor. The
// Panda VM's GC eagerly reclaims locally-scoped monitors that are never read
// after `const _monitor = installSyncMonitor(...)`, which clears the WeakRefs
// in MutableStateMeta.bindingRefs_ mid-test and causes intermittent missing
// callbacks. Pushing each created monitor here keeps it alive across the
// helper's mutations and assertions.
const installedSyncMonitors_: Array<IMonitorDecoratedVariable> = new Array<IMonitorDecoratedVariable>();

// Install a sync monitor for a single path. Wraps the verbose
// IMonitorPathInfo[] construction passed to makeSyncMonitor.
function installSyncMonitor(
    path: string,
    valueCallback: MonitorValueCallback,
    monitorCallback: MonitorCallback,
    isWildcard: boolean = false
): IMonitorDecoratedVariable {
    const m = StateMgmtFactory.makeSyncMonitor(
        [{ path: path, valueCallback: valueCallback, enableWildcard: isWildcard } as IMonitorPathInfo] as IMonitorPathInfo[],
        monitorCallback,
        undefined
    );
    installedSyncMonitors_.push(m);
    return m;
}

// Build a MonitorCallback that increments the counter and logs each trigger.
function countingMonitorCallback(counter: CallCounter, label: string): MonitorCallback {
    return (m: IMonitor): void => {
        counter.increment();
        console.log(`Monitor '${label}' triggered: count=${counter.count} dirty=${JSON.stringify(m.dirty)}`);
    };
}


// === Mock components =======================================================

/*
    @Observed class ClassA  {
        propA : number;
        @Track classB : ClassB_SingleMeta;

        // init with declaration
        @Track classC : ClassC = new ClassC;

        constructor() {
            // init in constructor
            this.classB = new ClassB_SingleMeta();
            this.propA = 8;
        }
    }

    // @Observe compat mode, no @Track
    @Observe class ClassB_SingleMeta {
        propB1 : string = "BBB111";
        propB2 : boolean = false;
    }

    // untracked
    class ClassC  {
        propC : number = 888;
    }
*/


// UI plugin generate
interface ParentComponent_init_update_struct {
    // @Local nothing, @Local can not init from parent @Component/V2
}

class ParentComponent extends ExtendableComponent {
    public monitorFunctionRunCount: number = 0;

    // @Monitor("b.obj.propA") onAChanged(m: IMonitor)
    public onAChanged?: (m: IMonitor) => void;

    constructor(parent: ExtendableComponent | null, param: ParentComponent_init_update_struct) {
        super(parent)
    }
}

// UI plugin generates
interface ComponentWithArray_init_update_struct {
    arr?: MyArray<number>;
}

class ComponentWithArray extends ExtendableComponent {
    private _backing_state_arr: ILocalDecoratedVariable<MyArray<number>>;
    get arr(): MyArray<number> {
        console.log('ParentComponent.arr()');
        return this._backing_state_arr!.get() as MyArray<number>;
    }
    set arr(newArr: MyArray<number>) {
        this._backing_state_arr!.set(newArr);
    }

    // For testing
    public getFireChangeCnt(key:string): Int {
        // meta_ not visible
        return (this._backing_state_arr.get().meta_ instanceof TestMutableKeyedStateMeta)
            ? (this._backing_state_arr.get().meta_ as TestMutableKeyedStateMeta).getFireChangeCnt(key) : 0
    }
    public getRefCnt(key:string) {
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
                : new MyArray<number>(1,2,3)
        );
    }
}

class NonObservedClass {
    prop1: string = 'p1';
    prop2: string = 'p2';
}

interface NonObservedInterface {
    prop1: string;
    prop2: string;
}

// === Test bodies ===========================================================

// Wildcard 'comp.arr.*' on @Local MyArray<number>: index assignment and sort
// each fire the monitor synchronously.
function testWildcardOnArray(): void {
    const counter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback comp.arr');
        return arrayComp.arr;
    };

    const _monitor = installSyncMonitor(
        'comp.arr.*',
        valueCallback,
        countingMonitorCallback(counter, 'comp.arr.*'),
        /* isWildcard */ true,
    );

    arrayComp.arr[1] = 1;
    test(`array wildcard: arr[1]=1 fires sync: count=${counter.count} === 1`, eq(counter.count, 1));
    arrayComp.arr[1] = 500;
    test(`array wildcard: arr[1]=500 fires sync: count=${counter.count} === 2`, eq(counter.count, 2));
    arrayComp.arr.sort();
    test(`array wildcard: arr.sort() fires sync: count=${counter.count} === 3`, eq(counter.count, 3));
}


// Path 'proxiedClass.prop1' on UIUtils.makeObserved(NonObservedClass).
function testPathOnMakeObservedClass(): void {
    const counter = new CallCounter();
    const proxiedClass = UIUtils.makeObserved(new NonObservedClass());

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback proxiedClass.prop1');
        return proxiedClass.prop1;
    };

    const _monitor = installSyncMonitor(
        'proxiedClass.prop1',
        valueCallback,
        countingMonitorCallback(counter, 'proxiedClass.prop1'),
    );

    proxiedClass.prop1 = 'newstring';
    test(`makeObserved class: prop1 set fires sync: count=${counter.count} === 1`, eq(counter.count, 1));
}

// Path 'proxiedObjectLiteral.prop1' on UIUtils.makeObserved(NonObservedInterface).
function testPathOnMakeObservedInterface(): void {
    const counter = new CallCounter();
    const proxiedObjectLiteral: NonObservedInterface = UIUtils.makeObserved(
        { prop1: 'A', prop2: 'B' } as NonObservedInterface);

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback proxiedObjectLiteral.prop1');
        return proxiedObjectLiteral.prop1;
    };

    const _monitor = installSyncMonitor(
        'proxiedObjectLiteral.prop1',
        valueCallback,
        countingMonitorCallback(counter, 'proxiedObjectLiteral.prop1'),
    );

    proxiedObjectLiteral.prop1 = 'newstring';
    test(`makeObserved object literal: prop1 set fires sync: count=${counter.count} === 1`, eq(counter.count, 1));
}

// Wildcard 'v1Observed.*' on @Observed (V1) ClassB_SingleMeta. Reading any single tracked
// property in the valueCallback is enough to record the wildcard dependency;
// idempotent assignments do not refire.
function testWildcardOnV1Observed(): void {
    const counter = new CallCounter();
    const v1Observed = new ClassB_SingleMeta();

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback v1Observed.*');
        return v1Observed;
    };

    v1Observed.propB2 = true;
    const _monitor = installSyncMonitor(
        'v1Observed.*',
        valueCallback,
        countingMonitorCallback(counter, 'v1Observed.*'),
        /* isWildcard */ true,
    );

    v1Observed.propB1 = 'new string';
    test(`V1 wildcard: propB1 set fires sync: count=${counter.count} === 1`, eq(counter.count, 1));
    v1Observed.propB1 = 'newer string';
    test(`V1 wildcard: propB1 reassigned fires sync: count=${counter.count} === 2`, eq(counter.count, 2));
    v1Observed.propB2 = false;
    test(`V1 wildcard: propB2=false fires sync: count=${counter.count} === 3`, eq(counter.count, 3));
    v1Observed.propB2 = true;
    test(`V1 wildcard: propB2=true fires sync: count=${counter.count} === 4`, eq(counter.count, 4));
    v1Observed.propB2 = true;              // idempotent — no refire
    test(`V1 wildcard: propB2=true idempotent does not refire: count=${counter.count} === 4`, eq(counter.count, 4));
}

// Wildcard 'comp.arr.*' on Array, also exercising .push().
function testWildcardOnArrayWithPush(): void {
    const counter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => {
        console.log('valueCallback comp.arr');
        return arrayComp.arr;
    };

    const _monitor = installSyncMonitor(
        'comp.arr.*',
        valueCallback,
        countingMonitorCallback(counter, 'comp.arr.* (push)'),
        /* isWildcard */ true,
    );

    arrayComp.arr[1] = 1;
    test(`array wildcard +push: arr[1]=1 fires sync: count=${counter.count} === 1`, eq(counter.count, 1));
    arrayComp.arr[1] = 500;
    test(`array wildcard +push: arr[1]=500 fires sync: count=${counter.count} === 2`, eq(counter.count, 2));
    arrayComp.arr.sort();
    test(`array wildcard +push: arr.sort() fires sync: count=${counter.count} === 3`, eq(counter.count, 3));
    arrayComp.arr.push(100);
    test(`array wildcard +push: arr.push(100) fires sync: count=${counter.count} === 4`, eq(counter.count, 4));
}

// Verifies that every length-changing Array mutation method fires the sync
// wildcard monitor EXACTLY ONCE per call. Each of these methods internally
// fires both OB_LENGTH and OB_ARRAY_ANY_KEY; addRefAnyKey() binds the wildcard
// to both, so without sync-monitor batching the monitor would fire twice per
// call. fireChangeMany batches the sync drain so both fires coalesce into one
// callback per logical mutation.
function testSyncMonitorPushVariants(): void {
    const counter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {});

    const valueCallback: MonitorValueCallback = () => arrayComp.arr;

    const _monitor = installSyncMonitor(
        'comp.arr.*',
        valueCallback,
        countingMonitorCallback(counter, 'comp.arr.* (variants)'),
        /* isWildcard */ true,
    );

    // pushOne: single-arg path that calls store_.push(val) and fires
    // OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.pushOne(10);
    test(`array variants: pushOne(10) fires once: count=${counter.count} === 1`, eq(counter.count, 1));

    // pushArray: rest-arg path that fires OB_LENGTH + OB_ARRAY_ANY_KEY once,
    // not once per element.
    arrayComp.arr.pushArray(20, 30, 40);
    test(`array variants: pushArray(20,30,40) fires once: count=${counter.count} === 2`, eq(counter.count, 2));

    // push (variadic): regardless of arg count, ONE fire.
    arrayComp.arr.push(50);
    test(`array variants: push(50) fires once: count=${counter.count} === 3`, eq(counter.count, 3));

    arrayComp.arr.push(60, 70, 80);
    test(`array variants: push(60,70,80) fires once: count=${counter.count} === 4`, eq(counter.count, 4));

    // shift removes from the front, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.shift();
    test(`array variants: shift() fires once: count=${counter.count} === 5`, eq(counter.count, 5));

    // pop removes from the end, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.pop();
    test(`array variants: pop() fires once: count=${counter.count} === 6`, eq(counter.count, 6));

    // unshift adds to the front, fires OB_LENGTH + OB_ARRAY_ANY_KEY.
    arrayComp.arr.unshift(99);
    test(`array variants: unshift(99) fires once: count=${counter.count} === 7`, eq(counter.count, 7));

    // splice can both remove and add, fires OB_LENGTH + OB_ARRAY_ANY_KEY once.
    arrayComp.arr.splice(0, 1, 111, 222);
    test(`array variants: splice(0,1,111,222) fires once: count=${counter.count} === 8`, eq(counter.count, 8));
}

// Verifies that mutation methods that DO NOT change array length
// (copyWithin, fill, reverse, sort) do NOT fire OB_LENGTH. Two sync monitors
// share the same array:
//   - lengthMonitor reads arr.length, so it binds to OB_LENGTH only.
//   - wildcardMonitor binds to OB_ARRAY_ANY_KEY (and OB_LENGTH).
// After each non-length-changing mutation:
//   - lengthMonitor count must NOT advance (length unchanged → no fire).
//   - wildcardMonitor count must advance by 1 (element-wise change still
//     observed via OB_ARRAY_ANY_KEY).
function testSyncMonitorLengthVsWildcardOnNonLengthMutations(): void {
    const lengthCounter = new CallCounter();
    const wildcardCounter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {});

    const _lengthMonitor = installSyncMonitor(
        'comp.arr.length',
        () => arrayComp.arr.length,
        countingMonitorCallback(lengthCounter, 'comp.arr.length'),
        /* isWildcard */ false,
    );
    const _wildcardMonitor = installSyncMonitor(
        'comp.arr.*',
        () => arrayComp.arr,
        countingMonitorCallback(wildcardCounter, 'comp.arr.*'),
        /* isWildcard */ true,
    );

    // Establish a baseline count for the wildcard monitor: a normal index
    // assignment fires it once (LENGTH not bound → does not advance length
    // counter).
    arrayComp.arr[0] = 99;
    test(`length-vs-wild: arr[0]=99: lengthCount=${lengthCounter.count} === 0`,
        eq(lengthCounter.count, 0));
    test(`length-vs-wild: arr[0]=99: wildcardCount=${wildcardCounter.count} === 1`,
        eq(wildcardCounter.count, 1));

    // copyWithin: in-place copy, length unchanged.
    arrayComp.arr.copyWithin(0, 1);
    test(`length-vs-wild: copyWithin: lengthCount=${lengthCounter.count} === 0`,
        eq(lengthCounter.count, 0));
    test(`length-vs-wild: copyWithin: wildcardCount=${wildcardCounter.count} === 2`,
        eq(wildcardCounter.count, 2));

    // fill: in-place fill, length unchanged.
    arrayComp.arr.fill(7);
    test(`length-vs-wild: fill: lengthCount=${lengthCounter.count} === 0`,
        eq(lengthCounter.count, 0));
    test(`length-vs-wild: fill: wildcardCount=${wildcardCounter.count} === 3`,
        eq(wildcardCounter.count, 3));

    // reverse: reorders in place, length unchanged.
    arrayComp.arr.reverse();
    test(`length-vs-wild: reverse: lengthCount=${lengthCounter.count} === 0`,
        eq(lengthCounter.count, 0));
    test(`length-vs-wild: reverse: wildcardCount=${wildcardCounter.count} === 4`,
        eq(wildcardCounter.count, 4));

    // sort: reorders in place, length unchanged. Already correctly fires only
    // OB_ARRAY_ANY_KEY in the implementation; this guards that.
    arrayComp.arr.sort();
    test(`length-vs-wild: sort: lengthCount=${lengthCounter.count} === 0`,
        eq(lengthCounter.count, 0));
    test(`length-vs-wild: sort: wildcardCount=${wildcardCounter.count} === 5`,
        eq(wildcardCounter.count, 5));

    // Sanity: a true length-changing mutation DOES fire the length monitor.
    arrayComp.arr.push(123);
    test(`length-vs-wild: push: lengthCount=${lengthCounter.count} === 1`,
        eq(lengthCounter.count, 1));
    test(`length-vs-wild: push: wildcardCount=${wildcardCounter.count} === 6`,
        eq(wildcardCounter.count, 6));
}

// Read-only Array methods (includes, indexOf, find, every, some, etc.)
// register dependency on OB_ARRAY_ANY_KEY when called, so a sync monitor
// whose valueCallback uses them fires on subsequent mutation. Verifies that
// each method establishes the dependency correctly.
function testSyncMonitorOnArrayReadMethods(): void {
    // includes(): start with [1,2,3]. Mutation must flip includes(2) from
    // true to false (non-wildcard monitor fires only on LSV change).
    const arr1 = new ComponentWithArray(null, {});
    const includesCounter = new CallCounter();
    const _includesMonitor = installSyncMonitor(
        'arr.includes(2)',
        () => arr1.arr.includes(2),
        countingMonitorCallback(includesCounter, 'arr.includes(2)'),
    );
    arr1.arr.splice(1, 1); // remove 2 → includes(2) flips true → false
    test(`read methods: includes(2) -> splice removes 2: count=${includesCounter.count} === 1`,
        eq(includesCounter.count, 1));

    // indexOf(): start with [1,2,3]. unshift changes indexOf(2) from 1 to 2.
    const arr2 = new ComponentWithArray(null, {});
    const indexOfCounter = new CallCounter();
    const _indexOfMonitor = installSyncMonitor(
        'arr.indexOf(2)',
        () => arr2.arr.indexOf(2),
        countingMonitorCallback(indexOfCounter, 'arr.indexOf(2)'),
    );
    arr2.arr.unshift(0); // [0,1,2,3] → indexOf(2) flips 1 → 2
    test(`read methods: indexOf(2) -> unshift shifts index: count=${indexOfCounter.count} === 1`,
        eq(indexOfCounter.count, 1));

    // some(): start with [1,2,3]. push(20) flips some(>10) from false to true.
    const arr3 = new ComponentWithArray(null, {});
    const someCounter = new CallCounter();
    const _someMonitor = installSyncMonitor(
        'arr.some(>10)',
        () => arr3.arr.some((v: number) => v > 10),
        countingMonitorCallback(someCounter, 'arr.some(>10)'),
    );
    arr3.arr.push(20); // adds element > 10 → some flips false → true
    test(`read methods: some(>10) -> push 20: count=${someCounter.count} === 1`,
        eq(someCounter.count, 1));

    // every(): start with [1,2,3]. push(-1) flips every(>=0) from true to false.
    const arr4 = new ComponentWithArray(null, {});
    const everyCounter = new CallCounter();
    const _everyMonitor = installSyncMonitor(
        'arr.every(>=0)',
        () => arr4.arr.every((v: number) => v >= 0),
        countingMonitorCallback(everyCounter, 'arr.every(>=0)'),
    );
    arr4.arr.push(-1); // adds negative → every flips true → false
    test(`read methods: every(>=0) -> push -1: count=${everyCounter.count} === 1`,
        eq(everyCounter.count, 1));

    // findIndex(): equivalent to indexOf with a predicate.
    const arr5 = new ComponentWithArray(null, {});
    const findIndexCounter = new CallCounter();
    const _findIndexMonitor = installSyncMonitor(
        'arr.findIndex(==2)',
        () => arr5.arr.findIndex((v: number) => v === 2),
        countingMonitorCallback(findIndexCounter, 'arr.findIndex(==2)'),
    );
    arr5.arr.unshift(0); // findIndex shifts from 1 to 2
    test(`read methods: findIndex -> unshift: count=${findIndexCounter.count} === 1`,
        eq(findIndexCounter.count, 1));
}

// Non-mutating "copy" methods (toSorted, toReversed, toSpliced, slice) return
// new arrays without modifying the source — they must not fire any monitor
// when CALLED. Verifies by checking that calling them on the array between
// genuine mutations does not change the wildcard monitor's count.
function testSyncMonitorArrayCopyMethodsDoNotFire(): void {
    const counter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {}); // [1,2,3]

    const _wildcardMonitor = installSyncMonitor(
        'comp.arr.*',
        () => arrayComp.arr,
        countingMonitorCallback(counter, 'comp.arr.* (copy methods)'),
        /* isWildcard */ true,
    );

    arrayComp.arr.push(4); // baseline mutation, count -> 1
    test(`copy methods: baseline push fires: count=${counter.count} === 1`,
        eq(counter.count, 1));

    // toSorted: returns a new sorted array; source untouched.
    const sorted = arrayComp.arr.toSorted();
    test(`copy methods: toSorted does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));
    test(`copy methods: toSorted result has length 4`, eq(sorted.length, 4));

    // toReversed: returns a new reversed array.
    const reversed = arrayComp.arr.toReversed();
    test(`copy methods: toReversed does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));
    test(`copy methods: toReversed result has length 4`, eq(reversed.length, 4));

    // slice: returns a shallow-copy slice.
    const sliced = arrayComp.arr.slice(0, 2);
    test(`copy methods: slice does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));
    test(`copy methods: slice result has length 2`, eq(sliced.length, 2));

    // toSpliced: returns a new array with the splice applied; source intact.
    const spliced = arrayComp.arr.toSpliced(1, 1);
    test(`copy methods: toSpliced does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));
    test(`copy methods: toSpliced result has length 3`, eq(spliced.length, 3));

    // Sanity: a real mutation still fires after all the copy calls.
    arrayComp.arr.push(5);
    test(`copy methods: push after copies fires: count=${counter.count} === 2`,
        eq(counter.count, 2));
}

// splice can delete only, insert only, both, or be a no-op. Each variant
// fires the wildcard sync monitor exactly once (or never for a true no-op).
function testSyncMonitorSpliceVariants(): void {
    const counter = new CallCounter();
    const arrayComp = new ComponentWithArray(null, {}); // [1,2,3]

    const _monitor = installSyncMonitor(
        'comp.arr.*',
        () => arrayComp.arr,
        countingMonitorCallback(counter, 'comp.arr.* (splice variants)'),
        /* isWildcard */ true,
    );

    // splice(start, deleteCount): delete only.
    arrayComp.arr.splice(0, 1);
    test(`splice variants: delete-only fires once: count=${counter.count} === 1`,
        eq(counter.count, 1));

    // splice(start, 0, ...items): insert only.
    arrayComp.arr.splice(1, 0, 99, 100);
    test(`splice variants: insert-only fires once: count=${counter.count} === 2`,
        eq(counter.count, 2));

    // splice(start, deleteCount, ...items): replace.
    arrayComp.arr.splice(0, 2, 7, 8, 9);
    test(`splice variants: replace fires once: count=${counter.count} === 3`,
        eq(counter.count, 3));

    // splice(start): delete to end.
    arrayComp.arr.splice(2);
    test(`splice variants: delete-to-end fires once: count=${counter.count} === 4`,
        eq(counter.count, 4));
}

// --- WrappedDate tests -----------------------------------------------------

// WrappedDate has a single shared __meta — every getter conditionalAddRefs
// it, every setter fireChange()s it. A sync monitor on any property reading
// from the same Date sees ALL setter calls, regardless of which field they
// touched.
function testSyncMonitorOnDateGetSetters(): void {
    const counter = new CallCounter();
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const _monitor = installSyncMonitor(
        'date.getDate()',
        () => d.getDate(),
        countingMonitorCallback(counter, 'date.getDate()'),
    );

    d.setDate(20); // 15 → 20
    test(`date: setDate(20) fires: count=${counter.count} === 1`, eq(counter.count, 1));

    d.setDate(20); // idempotent — same value, lambda result unchanged
    test(`date: setDate(20) idempotent does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));

    d.setDate(25); // change value
    test(`date: setDate(25) fires: count=${counter.count} === 2`, eq(counter.count, 2));
}

// Verify that a setter on a different field still fires a monitor reading
// any field, because WrappedDate has only one shared meta.
function testSyncMonitorDateSharedMetaCrossField(): void {
    const counter = new CallCounter();
    const d = UIUtils.makeObserved(new Date(2020, 0, 15));

    const _monitor = installSyncMonitor(
        'date.getMonth()',
        () => d.getMonth(),
        countingMonitorCallback(counter, 'date.getMonth()'),
    );

    // Setting the YEAR fires the shared meta. The lambda re-reads getMonth()
    // which is unchanged, so the LSV check suppresses the callback.
    d.setFullYear(2021);
    test(`date shared meta: setFullYear (different field) does not fire month monitor when month unchanged: count=${counter.count} === 0`,
        eq(counter.count, 0));

    // Setting the month directly DOES change the lambda's value.
    d.setMonth(5);
    test(`date shared meta: setMonth fires: count=${counter.count} === 1`, eq(counter.count, 1));
}

// setHours has 4 overloads (1-arg through 4-arg). Each fires once.
function testSyncMonitorDateSetHoursOverloads(): void {
    const counter = new CallCounter();
    const d = UIUtils.makeObserved(new Date(2020, 0, 15, 10, 30, 45, 100));

    const _monitor = installSyncMonitor(
        'date.getTime()',
        () => d.getTime(),
        countingMonitorCallback(counter, 'date.getTime()'),
    );

    d.setHours(11);
    test(`date setHours(h): fires: count=${counter.count} === 1`, eq(counter.count, 1));

    d.setHours(12, 0);
    test(`date setHours(h,m): fires: count=${counter.count} === 2`, eq(counter.count, 2));

    d.setHours(13, 0, 0);
    test(`date setHours(h,m,s): fires: count=${counter.count} === 3`, eq(counter.count, 3));

    d.setHours(14, 0, 0, 0);
    test(`date setHours(h,m,s,ms): fires: count=${counter.count} === 4`, eq(counter.count, 4));
}

// setTime is the most direct mutation: changes the underlying timestamp.
function testSyncMonitorDateSetTime(): void {
    const counter = new CallCounter();
    const d = UIUtils.makeObserved(new Date(0));

    const _monitor = installSyncMonitor(
        'date.valueOf()',
        () => d.valueOf(),
        countingMonitorCallback(counter, 'date.valueOf()'),
    );

    d.setTime(1_000_000_000);
    test(`date setTime: fires: count=${counter.count} === 1`, eq(counter.count, 1));

    d.setTime(2_000_000_000);
    test(`date setTime again: fires: count=${counter.count} === 2`, eq(counter.count, 2));
}

// --- WrappedMap tests ------------------------------------------------------

// A wildcard sync monitor over a WrappedMap fires once per logical mutation.
// addRefAnyKey() binds OB_LENGTH AND OB_MAP_ANY_PROPERTY, so without
// fireChangeMany batching set/delete/clear would fire multiple sync drains
// per call.
function testSyncMonitorOnMapWildcardFiresOnce(): void {
    const counter = new CallCounter();
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = installSyncMonitor(
        'map.*',
        () => map,
        countingMonitorCallback(counter, 'map.*'),
        /* isWildcard */ true,
    );

    map.set('a', 1); // new key: LENGTH + MAP_ANY_PROPERTY → batched, count 1
    test(`map wildcard: set new key fires once: count=${counter.count} === 1`,
        eq(counter.count, 1));

    map.set('b', 2);
    test(`map wildcard: set second new key fires once: count=${counter.count} === 2`,
        eq(counter.count, 2));

    map.set('a', 100); // existing key with new value: per-key + MAP_ANY_PROPERTY → batched, count 1
    test(`map wildcard: update existing key fires once: count=${counter.count} === 3`,
        eq(counter.count, 3));

    map.set('a', 100); // idempotent: only MAP_ANY_PROPERTY (single fire)
    test(`map wildcard: idempotent set still fires (touch behavior): count=${counter.count} === 4`,
        eq(counter.count, 4));

    map.delete('b'); // per-key + MAP_ANY_PROPERTY + LENGTH → batched, count 1
    test(`map wildcard: delete fires once: count=${counter.count} === 5`,
        eq(counter.count, 5));

    map.set('c', 3);
    map.set('d', 4);
    test(`map wildcard: two more sets: count=${counter.count} === 7`,
        eq(counter.count, 7));

    map.clear(); // all keys + LENGTH + MAP_ANY_PROPERTY → batched, count 1
    test(`map wildcard: clear fires once: count=${counter.count} === 8`,
        eq(counter.count, 8));
}

// A non-wildcard sync monitor on map.has(key) registers a dependency on
// either the per-key meta (when has is true) or OB_LENGTH (when has is
// false). Mutations that flip has's result fire the monitor; LSV-equal
// changes do not.
function testSyncMonitorOnMapHas(): void {
    const counter = new CallCounter();
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = installSyncMonitor(
        'map.has("a")',
        () => map.has('a'),
        countingMonitorCallback(counter, 'map.has("a")'),
    );

    map.set('a', 1); // has('a') flips false → true
    test(`map.has: set fires: count=${counter.count} === 1`, eq(counter.count, 1));

    map.set('a', 2); // has('a') stays true — LSV check suppresses
    test(`map.has: same-key update LSV suppressed: count=${counter.count} === 1`,
        eq(counter.count, 1));

    map.delete('a'); // has('a') flips true → false
    test(`map.has: delete fires: count=${counter.count} === 2`, eq(counter.count, 2));
}

// A non-wildcard sync monitor on map.get(key) registers a per-key dep when
// the key exists. Updating that key changes the lambda's value and fires.
function testSyncMonitorOnMapGet(): void {
    const counter = new CallCounter();
    const map = UIUtils.makeObserved(new Map<string, number>());
    map.set('a', 1);
    map.set('b', 2);
    counter.count = 0; // reset baseline (sets fired the wildcard if any)

    const _monitor = installSyncMonitor(
        'map.get("a")',
        () => map.get('a'),
        countingMonitorCallback(counter, 'map.get("a")'),
    );

    map.set('a', 100); // updates value of 'a' → lambda flips 1 → 100
    test(`map.get: update fires: count=${counter.count} === 1`, eq(counter.count, 1));

    map.set('b', 200); // updates 'b' (different key) — LSV unchanged for get('a')
    test(`map.get: unrelated-key update does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));
}

// A non-wildcard sync monitor on map.size: fires when LENGTH changes.
function testSyncMonitorOnMapSize(): void {
    const counter = new CallCounter();
    const map = UIUtils.makeObserved(new Map<string, number>());

    const _monitor = installSyncMonitor(
        'map.size',
        () => map.size,
        countingMonitorCallback(counter, 'map.size'),
    );

    map.set('x', 1);
    test(`map.size: set new key fires: count=${counter.count} === 1`, eq(counter.count, 1));

    map.set('x', 100); // existing key — does not change size
    test(`map.size: update existing key does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));

    map.delete('x');
    test(`map.size: delete fires: count=${counter.count} === 2`, eq(counter.count, 2));

    map.set('y', 2);
    map.set('z', 3);
    test(`map.size: two more sets: count=${counter.count} === 4`, eq(counter.count, 4));

    map.clear();
    test(`map.size: clear fires: count=${counter.count} === 5`, eq(counter.count, 5));
}

// --- WrappedSet tests ------------------------------------------------------

// A wildcard sync monitor over a WrappedSet fires once per logical mutation.
// addRefAnyKey() binds OB_SET_ANY_PROPERTY AND OB_LENGTH, so without
// fireChangeMany batching add/delete/clear would fire multiple sync drains
// per call.
function testSyncMonitorOnSetWildcardFiresOnce(): void {
    const counter = new CallCounter();
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = installSyncMonitor(
        'set.*',
        () => set,
        countingMonitorCallback(counter, 'set.*'),
        /* isWildcard */ true,
    );

    set.add(1); // per-value + ANY_PROPERTY + LENGTH → batched, count 1
    test(`set wildcard: add new value fires once: count=${counter.count} === 1`,
        eq(counter.count, 1));

    set.add(2);
    test(`set wildcard: add second new value fires once: count=${counter.count} === 2`,
        eq(counter.count, 2));

    set.add(1); // already present — no fire
    test(`set wildcard: add existing value does not fire: count=${counter.count} === 2`,
        eq(counter.count, 2));

    set.delete(1); // per-value + ANY_PROPERTY + LENGTH → batched, count 1
    test(`set wildcard: delete fires once: count=${counter.count} === 3`,
        eq(counter.count, 3));

    set.delete(99); // not present — no fire
    test(`set wildcard: delete non-existent value does not fire: count=${counter.count} === 3`,
        eq(counter.count, 3));

    set.add(3);
    set.add(4);
    test(`set wildcard: two more adds: count=${counter.count} === 5`,
        eq(counter.count, 5));

    set.clear(); // all values + LENGTH + ANY_PROPERTY → batched, count 1
    test(`set wildcard: clear fires once: count=${counter.count} === 6`,
        eq(counter.count, 6));

    set.clear(); // empty already — no fire
    test(`set wildcard: clear on empty set does not fire: count=${counter.count} === 6`,
        eq(counter.count, 6));
}

// A non-wildcard sync monitor on set.has(value) registers a dependency on
// either the per-value meta (when value is present) or OB_LENGTH (when not).
// Mutations that flip has's result fire the monitor.
function testSyncMonitorOnSetHas(): void {
    const counter = new CallCounter();
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = installSyncMonitor(
        'set.has(7)',
        () => set.has(7),
        countingMonitorCallback(counter, 'set.has(7)'),
    );

    set.add(7); // has(7) flips false → true
    test(`set.has: add fires: count=${counter.count} === 1`, eq(counter.count, 1));

    set.add(8); // adds different value — has(7) still true, LSV suppressed
    test(`set.has: add unrelated value does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));

    set.delete(7); // has(7) flips true → false
    test(`set.has: delete fires: count=${counter.count} === 2`, eq(counter.count, 2));
}

// A non-wildcard sync monitor on set.size: fires only on length changes.
function testSyncMonitorOnSetSize(): void {
    const counter = new CallCounter();
    const set = UIUtils.makeObserved(new Set<number>());

    const _monitor = installSyncMonitor(
        'set.size',
        () => set.size,
        countingMonitorCallback(counter, 'set.size'),
    );

    set.add(1);
    test(`set.size: add new value fires: count=${counter.count} === 1`, eq(counter.count, 1));

    set.add(1); // already present, no length change
    test(`set.size: add existing value does not fire: count=${counter.count} === 1`,
        eq(counter.count, 1));

    set.delete(1);
    test(`set.size: delete fires: count=${counter.count} === 2`, eq(counter.count, 2));

    set.add(2);
    set.add(3);
    test(`set.size: two more adds: count=${counter.count} === 4`, eq(counter.count, 4));

    set.clear();
    test(`set.size: clear fires: count=${counter.count} === 5`, eq(counter.count, 5));
}

// === Test suites ===========================================================

export function run_sync_monitor(): boolean {

    const ttest = tsuite('@SyncMonitor basics') {

    tcase('### makeSyncMonitor wildcard on @Local MyArray: index assign and sort fire monitor') {
        testWildcardOnArray();
    }

    // TODO: proxy fails for current version of the framework
    // node_modules-62220
    tcase('### makeSyncMonitor non-wildcard path on UIUtils.makeObserved(class instance)') {
        testPathOnMakeObservedClass();
    }

    // TODO: proxy fails in sdk
    tcase('### makeSyncMonitor non-wildcard path on UIUtils.makeObserved(object literal)') {
        testPathOnMakeObservedInterface();
    }

    tcase('### makeSyncMonitor wildcard on V1 @Observed object: only props read in valueCallback fire') {
        testWildcardOnV1Observed();
    }

}

ttest();
return true;
}

export function run_sync_monitor_set(): boolean {
    const tests = tsuite('@SyncMonitor WrappedSet') {

    tcase('### makeSyncMonitor wildcard on WrappedSet: add/delete/clear each fire once per call')
    {
        testSyncMonitorOnSetWildcardFiresOnce();
    }

    tcase('### makeSyncMonitor set.has(value): only fires on flips, not on unrelated adds')
    {
        testSyncMonitorOnSetHas();
    }

    tcase('### makeSyncMonitor set.size: fires only on length-changing mutations')
    {
        testSyncMonitorOnSetSize();
    }
    }

    tests();
    return true;
}

export function run_sync_monitor_map(): boolean {
    const tests = tsuite('@SyncMonitor WrappedMap') {

    tcase('### makeSyncMonitor wildcard on WrappedMap: set/delete/clear each fire once per call')
    {
        testSyncMonitorOnMapWildcardFiresOnce();
    }

    tcase('### makeSyncMonitor map.has(key): only fires on flips, not on same-key updates')
    {
        testSyncMonitorOnMapHas();
    }

    tcase('### makeSyncMonitor map.get(key): fires on key update, not on unrelated-key update')
    {
        testSyncMonitorOnMapGet();
    }

    tcase('### makeSyncMonitor map.size: fires only on length-changing mutations (set new / delete / clear)')
    {
        testSyncMonitorOnMapSize();
    }
    }

    tests();
    return true;
}

export function run_sync_monitor_date(): boolean {
    const tests = tsuite('@SyncMonitor WrappedDate') {

    tcase('### makeSyncMonitor on WrappedDate: setDate fires; idempotent set does not')
    {
        testSyncMonitorOnDateGetSetters();
    }

    tcase('### makeSyncMonitor on WrappedDate: shared __meta — cross-field setter governed by LSV check')
    {
        testSyncMonitorDateSharedMetaCrossField();
    }

    tcase('### makeSyncMonitor on WrappedDate: setHours overloads (1/2/3/4 args) each fire once')
    {
        testSyncMonitorDateSetHoursOverloads();
    }

    tcase('### makeSyncMonitor on WrappedDate: setTime fires the monitor')
    {
        testSyncMonitorDateSetTime();
    }
    }

    tests();
    return true;
}

export function run_sync_monitor_arrays(): boolean {
    const tests = tsuite('@SyncMonitor arrays') {

    tcase('### makeSyncMonitor wildcard on @Local MyArray: index assign, sort, and push each fire monitor')
    {
        testWildcardOnArrayWithPush();
    }

    tcase('### makeSyncMonitor wildcard: every length-changing method fires once per call')
    {
        testSyncMonitorPushVariants();
    }

    tcase('### makeSyncMonitor: copyWithin/fill/reverse/sort do not fire length-only subscribers')
    {
        testSyncMonitorLengthVsWildcardOnNonLengthMutations();
    }

    tcase('### makeSyncMonitor: read-only Array methods establish dependency on the array')
    {
        testSyncMonitorOnArrayReadMethods();
    }

    tcase('### makeSyncMonitor: copy methods (toSorted/toReversed/toSpliced/slice) do not fire')
    {
        testSyncMonitorArrayCopyMethodsDoNotFire();
    }

    tcase('### makeSyncMonitor: splice variants (delete/insert/replace/delete-to-end) each fire once')
    {
        testSyncMonitorSpliceVariants();
    }
    }

    tests();
    return true;
}
