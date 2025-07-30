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

import { int32 } from 'stateManagement/mock/env_mock'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from '../../interface/iStateMgmtFactory.ets'

// unit testing
import { StateTracker } from 'stateManagement/utest/lib/stateTracker'
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { ObserveSingleton } from '../../base/observeSingleton.ets'

/*
    @Observed class ClassD  {
        @Track propD1 : number;
        @Track propD2 : number;

        constructor(a : number, b: number) {
            this.propD1 = a;
            this.propD2 = this.propD1 + 2*b;
        }
    }

    @Observe ClassE extends ClassD
        @Track propE : number;

    constructor(a : number, b: number, c: number)
        super(a, b) {
            this.propE = this.propD2 + c;
        }
    }
*/

export class ClassD implements IObservedObject, IWatchSubscriberRegister {

    constructor(a: number, b: number) {
        // init in constructor
        // need to change to _backing,
        // otherwise compiler warns about uninitialized
        // __backing
        this.__backing_propD1 = a;
        this.__backing_propD2 = this.propD1 + 2 * b;
    }

    // @Watch
    // Watches firing when this object's property changes
    // @JsonIgnore
    private readonly subscribedWatches_: ISubscribedWatches = StateMgmtFactory.makeSubscribedWatches();

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_.executeOnSubscribingWatches("propE");
    }


    // IObservedObject interface
    // @JsonIgnore
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    // helper
    // do not inline, will not work for
    // inherited classes.
    protected conditionalAddRef(meta: IMutableStateMeta): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }

    // @Track propD1 : number;
    // @JsonRename("propD1")
    private __backing_propD1: number;

    // @JsonIgnore
    private readonly __meta_propD1: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propD1(): number {
        stateMgmtConsole.log(`ClassD: get @Track propD1`);
        this.conditionalAddRef(this.__meta_propD1);
        return this.__backing_propD1
    }
    public set propD1(newValue: number) {
        if (this.__backing_propD1 !== newValue) {
            stateMgmtConsole.log(`ClassD: set @Track propD1`);
            this.__backing_propD1 = newValue;
            this.__meta_propD1.fireChange();
            this.executeOnSubscribingWatches("propD1");
        }
    }

    // @Track propD2 : number;
    // @JsonRename("propD2")
    private __backing_propD2: number;

    // @JsonIgnore
    private readonly __meta_propD2: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propD2(): number {
        stateMgmtConsole.log(`ClassD: get @Track propD2`);
        this.conditionalAddRef(this.__meta_propD2);
        return this.__backing_propD2
    }
    public set propD2(newValue: number) {
        stateMgmtConsole.log(`ClassD: set @Track propD2`);
        if (this.__backing_propD2 !== newValue) {
            this.__backing_propD2 = newValue;
            this.__meta_propD2.fireChange();
            this.executeOnSubscribingWatches("propD2");
        }
    }
}


export class ClassE extends ClassD implements IObservedObject, IWatchSubscriberRegister {

    constructor(a: number, b: number, c: number) {
        super(a, b)
        this.__backing_propE = this.propD2 + c;
    }


    // @Watch
    // skip, code already in base class

    // IObservedObject interface
    // skip, code already in base class

    // helper
    // conditionalAddRef already in base class

    // @Track propE : number;
    // @JsonRename("propE")
    private __backing_propE: number;

    // @JsonIgnore
    private readonly __meta_propE: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propE(): number {
        stateMgmtConsole.log(`ClassE: get @Track propE`);
        this.conditionalAddRef(this.__meta_propE);
        return this.__backing_propE
    }
    public set propE(newValue: number) {
        stateMgmtConsole.log(`ClassE: set @Track propE`);
        if (this.__backing_propE !== newValue) {
            this.__backing_propE = newValue;
            stateMgmtConsole.log(`ClassE: set @Track propE - newValue: ${newValue}`);
            this.__meta_propE.fireChange();
            this.executeOnSubscribingWatches("propE");
        }
    }
}

export function run_observed_object4(): Boolean {

    const ttest = tsuite("@Observe @Track inheritance") {

        tcase("init, read and modify properties") {

        // some quick and dirty way to test if
        // init , read and modify properties works
        // test for addRef, freChange TODO

        let classD = new ClassD(1, 2);

        test("read classD.propD1 - expect 1", eq(classD.propD1, 1))
        test("read classD.propD2 - expect 5", eq(classD.propD2, 5))

        let classE = new ClassE(1, 2, 3);
        test("read classE.propD1 - expect 1", eq(classE.propD1, 1))
        test("read classE.propD2 - expect 5", eq(classE.propD2, 5))
        test("read classE.propE - expect 8", eq(classE.propE, 8))
        }

        tcase("Test 2: Verify AddRef for V1") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classD = new ClassD(1, 2);
            StateTracker.reset();
            // Cause addRef
            classD.propD1;
            test("Add ref first", eq(StateTracker.getRefCnt(), 1))
            // Cause addRef
            classD.propD1;
            test("Add ref second", eq(StateTracker.getRefCnt(), 2))
                        // Cause addRef
            classD.propD2;
            test("Add ref third", eq(StateTracker.getRefCnt(), 3))
        }

        tcase("Test 3: Verify AddRef for V2") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classD = new ClassD(1, 2);
            StateTracker.reset();
            classD.propD1;
            test("Add ref first", eq(StateTracker.getRefCnt(), 1))
            classD.propD1;
            test("Add ref second", eq(StateTracker.getRefCnt(), 2))
            classD.propD2;
            test("Add ref third", eq(StateTracker.getRefCnt(), 3))
            let classE = new ClassE(1, 2, 3);
            classE.propE;
            classE.propE = 4;
            test("Add ref third", eq(StateTracker.getFireChangeCnt(), 1))
        }

         tcase("Test 4: Verify Firecount for V1") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            StateTracker.reset();

            let classE = new ClassE(1, 2, 3);
            // Cause addRef otherwise there are not fire change when we set the value
            classE.propE;
            // Change value causing FireChange
            classE.propE = 4;
            test("Check fire change after changing the value", eq(StateTracker.getFireChangeCnt(), 1))
        }

        tcase("Test 5: Verify Firecount for V2") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            StateTracker.reset();

            let classE = new ClassE(3, 2, 1);
            // Cause addRef otherwise there are not fire change when we set the value
            classE.propE;
            // Change value causing FireChange
            classE.propE = 0;
            test("Check fire change after changing the value", eq(StateTracker.getFireChangeCnt(), 1))
        }

        tcase("Test 6: Multiple FireChange triggers for ClassE in V1") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            StateTracker.reset();

            let classE = new ClassE(5, 5, 5);
            classE.propE;

            classE.propE = 6;
            classE.propE = 7;
            classE.propE = 8;

            test("FireChange count should be 3 after 3 distinct updates", eq(StateTracker.getFireChangeCnt(), 3));
        }

        tcase("Test 7: Setting the same value repeatedly does not fire for ClassE in V2") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            StateTracker.reset();

            let classE = new ClassE(9, 9, 9);
            classE.propE;

            classE.propE = 10;
            classE.propE = 10;
            classE.propE = 10;

            test("Only first assignment should trigger FireChange", eq(StateTracker.getFireChangeCnt(), 1));
        }

        tcase("Test 8: FireChange without initial reference should not trigger in V1") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            StateTracker.reset();

            let classE = new ClassE(1, 2, 3);
            classE.propE = 10;

            test("No fire change without addRef", eq(StateTracker.getFireChangeCnt(), 0));
        }

        tcase("Test 9: FireChange starts only after reference in V2") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            StateTracker.reset();

            let classE = new ClassE(2, 2, 2);
            classE.propE = 3; // Should not trigger
            classE.propE;     // AddRef happens here
            classE.propE = 4; // Should now trigger

            test("Only the second change should trigger fire count", eq(StateTracker.getFireChangeCnt(), 1));
        }

        tcase("Test 10: Track addRefs and FireChange across ClassD and ClassE in V1") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classD = new ClassD(0, 0);
            let classE = new ClassE(0, 0, 0);
            StateTracker.reset();
            classD.propD1;
            classD.propD2;
            classE.propE;
            classE.propE = 1;

            test("Expect 2 addRefs for classD and 1 for classE (total 3)", eq(StateTracker.getRefCnt(), 3));
            test("Expect 1 fireChange for classE,propE", eq(StateTracker.getFireChangeCnt(), 1));
        }
    }

    ttest();
    return true;
}

