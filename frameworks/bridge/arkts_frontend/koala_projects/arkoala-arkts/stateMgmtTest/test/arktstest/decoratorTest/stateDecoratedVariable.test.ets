/*
* Copyright (C) 2026 Huawei Device Co., Ltd.
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
import { describe, it, expect, beforeEach } from "index";
import {
    StateDecoratedVariable,
    WatchFuncType,
} from "@ohos.arkui.stateManagement";

// ArkTS does not allow object literals, use class instead
class TestData {
    public x: number;
    public y: number;
    constructor(x: number, y: number) {
        this.x = x;
        this.y = y;
    }
}

// module-level shared state (ArkTS forbids nested functions)
let watchCallCount: number = 0;
let lastWatchPropName: string = '';

function makeWatchFunc(): WatchFuncType {
    return (propertyName: string) => {
        watchCallCount++;
        lastWatchPropName = propertyName;
    };
}

export function StateDecoratedVariableTest() {
    describe('StateDecoratedVariable UT', () => {
        beforeEach(() => {
            watchCallCount = 0;
            lastWatchPropName = '';
        });

        // ==================== Constructor / get ====================
        // Primitive and object init cover two distinct constructor branches:
        //   else: mkDecoratorValue (primitive)
        //   else: mkDecoratorValue (object, then registerWatchForObservedObjectChanges)

        it('should init with primitive value', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 42);
            expect(sv.get()).assertEqual(42);
        });

        it('should init with object value', 0, () => {
            const sv = new StateDecoratedVariable<TestData>(undefined, "data", new TestData(1, 2));
            const result = sv.get();
            expect(result.x).assertEqual(1);
            expect(result.y).assertEqual(2);
        });

        // ==================== set ====================
        // Primitive set and object set cover two distinct paths in set():
        //   both go through backing_.setNoCheck(value), but
        //   object path additionally exercises uiUtils.makeV1Observed,
        //   registerWatchForObservedObjectChanges, updateObservedObjectRegistration

        it('should update primitive value via set', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            sv.set(100);
            expect(sv.get()).assertEqual(100);
        });

        it('should update object value via set', 0, () => {
            const sv = new StateDecoratedVariable<TestData>(undefined, "data", new TestData(1, 0));
            sv.set(new TestData(2, 3));
            const result = sv.get();
            expect(result.x).assertEqual(2);
            expect(result.y).assertEqual(3);
        });

        // set() early return: oldValue === newValue → no-op, watch not triggered
        it('should skip set when value unchanged', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 42, makeWatchFunc());
            sv.set(42);
            expect(watchCallCount).assertEqual(0);
        });

        // ==================== @Watch ====================
        // execWatchFuncs normal path (owningComponent_ === undefined → else branch)

        it('should trigger watch on value change', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "myState", 0, makeWatchFunc());
            sv.set(1);
            expect(watchCallCount).assertEqual(1);
            expect(lastWatchPropName).assertEqual("myState");
        });

        it('should trigger watch for each distinct value', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0, makeWatchFunc());
            sv.set(1);
            sv.set(2);
            sv.set(3);
            expect(watchCallCount).assertEqual(3);
        });

        // ==================== resetOnReuse ====================
        // resetOnReuse intentionally does NOT call execWatchFuncs — silent reset
        // object path additionally exercises registerWatchForObservedObjectChanges with object

        it('should reset value silently (primitive)', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0, makeWatchFunc());
            sv.resetOnReuse(999);
            expect(sv.get()).assertEqual(999);
            expect(watchCallCount).assertEqual(0);
        });

        it('should reset value silently (object)', 0, () => {
            const sv = new StateDecoratedVariable<TestData>(undefined, "data", new TestData(1, 0), makeWatchFunc());
            sv.resetOnReuse(new TestData(99, 0));
            const result = sv.get();
            expect(result.x).assertEqual(99);
            expect(watchCallCount).assertEqual(0);
        });

        // ==================== mkLink ====================
        // Creates LinkDecoratedVariable synced via getter/setter + registerWatchToSource

        it('should create link synced with state', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 42);
            const link = sv.mkLink("linkedCounter");
            expect(link.get()).assertEqual(42);
        });

        it('should propagate state change to link', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            const link = sv.mkLink("linkedCounter");
            sv.set(100);
            expect(link.get()).assertEqual(100);
        });

        it('should propagate link change back to state', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            const link = sv.mkLink("linkedCounter");
            link.set(200);
            expect(sv.get()).assertEqual(200);
        });

        // ==================== mkProp ====================
        // Creates PropDecoratedVariable synced via WeakRef + updateForStorage

        it('should create prop synced with state', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 42);
            const propResult = sv.mkProp("propCounter");
            expect(propResult.prop.get()).assertEqual(42);
        });

        it('should propagate state change to prop', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            const propResult = sv.mkProp("propCounter");
            sv.set(100);
            expect(propResult.prop.get()).assertEqual(100);
        });

        // ==================== fireChange ====================

        it('should not throw on fireChange', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 42);
            sv.fireChange();
        });

        // ==================== setProxyValue callback ====================
        // Covers the `if (this.setProxyValue)` branch in set() and resetOnReuse()

        it('should invoke setProxyValue on set', 0, () => {
            let capturedValue: number = -1;
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            sv.setProxyValue = (value: number) => { capturedValue = value; };
            sv.set(100);
            expect(capturedValue).assertEqual(100);
        });

        it('should invoke setProxyValue on resetOnReuse', 0, () => {
            let capturedValue: number = -1;
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            sv.setProxyValue = (value: number) => { capturedValue = value; };
            sv.resetOnReuse(999);
            expect(capturedValue).assertEqual(999);
        });

        // ==================== API ====================

        it('should return correct getInfo, varName, info', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "myVar", 0);
            expect(sv.getInfo()).assertEqual("@State myVar (StateDecoratedVariable)");
            expect(sv.varName).assertEqual("myVar");
            expect(sv.info()).assertEqual("myVar");
        });

        // ==================== aboutToBeDeletedInternal ====================
        // Without watch: only unregisterFromObservedObject + super cleanup
        // With watch: additionally cleans up _watchFuncs and WatchFunc registry

        it('should cleanup without watch without error', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0);
            sv.aboutToBeDeletedInternal();
        });

        it('should cleanup with watch without error', 0, () => {
            const sv = new StateDecoratedVariable<number>(undefined, "counter", 0, makeWatchFunc());
            sv.set(1);
            sv.aboutToBeDeletedInternal();
        });
    });
}