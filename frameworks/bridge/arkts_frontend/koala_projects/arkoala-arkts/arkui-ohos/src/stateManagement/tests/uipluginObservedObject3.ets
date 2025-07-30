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
    @Observed class ClassA  {
               propA : number;
        @Track classB : ClassB;

        // init with declaration
        @Track classC : ClassC = new ClassC;

    constructor() {
        // init in constructor
        this.classB = new ClassB();
        this.propA = 8;
    }

    // @Observe compat mode, no @Track
    @Observe class ClassB {
        propB1 : string = "BBB111";
        propB2 : boolean = false;
    }

   // untracked
   class ClassC  {
        propC : number = 888;
    }
*/

export class ClassA implements IObservedObject, IWatchSubscriberRegister {

    constructor() {
        // init in constructor
        // need to change to _backing,
        // otherwise compiler warns about uninitialized
        // __backing
        this.__backing_classB = new ClassB();
        this.propA = 8;
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
        this.subscribedWatches_.executeOnSubscribingWatches(changedPropName);
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

    // @Track classB : ClassB
    //@JsonRename("classB")
    private __backing_classB: ClassB;

    // @JsonIgnore
    private readonly __meta_classB: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get classB(): ClassB {
        this.conditionalAddRef(this.__meta_classB);
        return this.__backing_classB;
    }
    public set classB(newValue: ClassB) {
        stateMgmtConsole.log(`ClassA: set @Track classB`);
        if (this.__backing_classB !== newValue) {
            this.__backing_classB = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches("classB");
        }
    }

    // @Track classC : ClassC = new ClassC();
    //@JsonRename("classC")
    private __backing_classC: ClassC = new ClassC

    // @JsonIgnore
    private readonly __meta_classC: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();
    public get classC(): ClassC {
        stateMgmtConsole.log(`ClassA: get @Track classC`);
        this.conditionalAddRef(this.__meta_classC);
        return this.__backing_classC;
    }
    public set classC(newValue: ClassC) {
        stateMgmtConsole.log(`ClassA: set @Track classC`);
        if (this.__backing_classC !== newValue) {
            this.__backing_classC = newValue;
            this.__meta_classB.fireChange();
            this.executeOnSubscribingWatches("classC");
        }
    }

    // propA : number (no @Track)
    public propA: number

}

export class ClassB implements IObservedObject, IWatchSubscriberRegister {

    // no constructor defined by app

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
    protected conditionalAddRef(): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            this.__meta.addRef();
        }
    }

    // @JsonIgnore
    private readonly __meta: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    // propB1 : string = "BBB111";
    // @JsonRename("classC")
    private __backing_propB1: string = "BBB111";
    public get propB1(): string {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB1`);
        this.conditionalAddRef();
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB1`);
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            stateMgmtConsole.log(`ClassB (@Observe compat): set propB1 - fireChange`);
            this.__meta.fireChange();
            stateMgmtConsole.log(`ClassB (@Observe compat): set propB1 - fireChange done `);
            this.executeOnSubscribingWatches("propB1");
        }
    }

    // propB2 : boolean = false;
    // @JsonRename("classC")
    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB2`);
        this.conditionalAddRef();
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB2`);
        if (this.__backing_propB2 !== newValue) {
            this.__backing_propB2 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propB2");
        }
    }
}

// non-observed, no change
class ClassC {
    propC: number = 888;
}

export function run_observed_object3(): Boolean {

    // some quick and dirty way to test if
    // init , read and modify properties works
    const ttest = tsuite("@Observe @Track and @Observe compat, plain class: nested objects") {

        tcase("Test 1: init, read and modify properties") {

            let classA = new ClassA()
            test("read classA.propA - expect 8", eq(classA.propA, 8))
            test("read classA.classB.propB1 - expect BBB111", eq(classA.classB.propB1, "BBB111"))
            test("read classA.classB.propB2 - expect false", eq(classA.classB.propB2, false))
            test("read classA.classC.propC - expect 888", eq(classA.classC.propC, 888))

            console.log("set classA.propA +=1")
            classA.propA += 1;

            console.log("set classA.classB.propB1 = '****'")
            classA.classB.propB1 = "****";

            ObserveSingleton.instance.updateDirty2();

            test("read classA.propA - expect 9", eq(classA.propA, 9))
            test("read classA.classB.propB1 - expect ****", eq(classA.classB.propB1, "****"))
        }

        tcase("Test 2: Verify AddRef for V1") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classA = new ClassA()

            StateTracker.reset();
            // Cause addRef
            classA.classB;
            test("Use classA.classB expect 1 add ref for classB", eq(StateTracker.getRefCnt(), 1))
        }

        tcase("Test 3: Verify AddRef for V2") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classA = new ClassA()

            StateTracker.reset();
            // Cause addRef
            classA.classB;
            test("Use classA.classB expect 1 add ref for classB", eq(StateTracker.getRefCnt(), 1))
        }

        tcase("Test 4: Verify 2*AddRef and FireChange for V1") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classA = new ClassA()

            StateTracker.reset();
            // Cause addRef
            classA.classB.propB1;
            test("Use classA.classB.probB1 expect 2 add refs. classB and propB1", eq(StateTracker.getRefCnt(), 2))
            // This causes fireChange event
            classA.classB = new ClassB();
            test("New classA.classB expect fire change", eq(StateTracker.getFireChangeCnt(), 1))
        }

        tcase("Test 5: Verify 2*AddRef and FireChange for V2") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classA = new ClassA()
            StateTracker.reset();
            // Cause addRefs
            classA.classB.propB1;
            test("Use classA.classB.probB1 expect 2 add refs. classB and propB1", eq(StateTracker.getRefCnt(), 2))
            // This causes fireChange event
            classA.classB = new ClassB();
            test("New classA.classB expect fire change", eq(StateTracker.getFireChangeCnt(), 1))

        }
    }

    ttest();
    return true;
}
