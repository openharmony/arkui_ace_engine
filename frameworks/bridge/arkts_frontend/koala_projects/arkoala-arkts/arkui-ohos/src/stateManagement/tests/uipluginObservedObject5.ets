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

    // @Observe compat mode, no @Track
    @Observe class ClassF {
        propF1 : string = "FFF";
        propF2 : string = "FFF";

        constructor(f1? : string, f2?: string) {
            if (f1) {
              this.propF1 = f1
            }
            if (f2) {
              this.propF2 = f2
            }
        }
    }

    // @Observe compat mode, no @Track
    @Observe class ClassG extends ClassF {
        propG : string = "GGG";

        constructor(f1? : string, f2?: string, g?: string) {
           super(f1, f2)
              if (g) {
                this.propG = g
              }
    }
*/

export class ClassF implements IObservedObject, IWatchSubscriberRegister {

    constructor(f1?: string, f2?: string) {
        if (f1) {
            this.__backing_propF1 = f1
        }
        if (f2) {
            this.__backing_propF2 = f2
        }
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
    protected conditionalAddRef(): void {
        if (Observe.shouldAddRef(this.____V1RenderId)) {
            this.__meta.addRef();
        }
    }

    // @JsonIgnore
    // needs to be protected for sub-class to
    // call fireChange.
    protected readonly __meta: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();


    //   propF1 : string = "FFF";
    //   propF2 : string = "FFF";
    // @JsonRename("propF1")
    private __backing_propF1: string = "FFF";
    public get propF1(): string {
        stateMgmtConsole.log(`ClassF (@Observe compat): get propF1`);
        this.conditionalAddRef();
        return this.__backing_propF1;
    }
    public set propF1(newValue: string) {
        stateMgmtConsole.log(`ClassF (@Observe compat): set propF1`);
        if (this.__backing_propF1 !== newValue) {
            this.__backing_propF1 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propF1");
        }
    }

    //   propF2 : string = "FFF";
    // @JsonRename("propF1")
    private __backing_propF2: string = "FFF";
    public get propF2(): string {
        stateMgmtConsole.log(`ClassF (@Observe compat): get propF2`);
        this.conditionalAddRef();
        return this.__backing_propF2;
    }
    public set propF2(newValue: string) {
        stateMgmtConsole.log(`ClassF (@Observe compat): set propF2`);
        if (this.__backing_propF2 !== newValue) {
            this.__backing_propF2 = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propF2");
        }
    }
}




export class ClassG extends ClassF implements IObservedObject, IWatchSubscriberRegister {

    constructor(f1?: string, f2?: string, g?: string) {
        super(f1, f2)
        if (g) {
            this.__backing_propG = g
        }
    }


    // @Watch
    // source code is in base class already

    // IObservedObject interface
    // source code is in base class already

    // helper conditionalAddRef
    // source code is in base class already
    // must share same __meta, do not generate another one here!

    //  propG : string = "GGG";
    // @JsonRename("propG")
    private __backing_propG: string = "GGG";
    public get propG(): string {
        stateMgmtConsole.log(`ClassG (@Observe compat): get propG`);
        this.conditionalAddRef();
        return this.__backing_propG;
    }
    public set propG(newValue: string) {
        stateMgmtConsole.log(`ClassG (@Observe compat): set propG`);
        if (this.__backing_propG !== newValue) {
            this.__backing_propG = newValue;
            this.__meta.fireChange();
            this.executeOnSubscribingWatches("propG");
        }
    }
}

export function run_observed_object5(): Boolean {

    const ttest = tsuite("@Observe compat inheritance") {

        tcase("init, read and modify properties") {

            let classF = new ClassF("f1", "f2");

            test("classF.propE1 - expect 'f1'", eq(classF.propF1, 'f1'))
            test("classF.propE2 - expect 'f2'", eq(classF.propF2, 'f2'))

            let classG = new ClassG("f1", "f2", "g");

            test("classG.propE1 - expect 'f1'", eq(classG.propF1, 'f1'))
            test("classG.propE2 - expect 'f2'", eq(classG.propF2, 'f2'))
            test("classG.propG - expect 'g'", eq(classG.propG, 'g'))

            console.log("set values to captital letters")
            classG.propF1 = "F1"
            classG.propF2 = "F2"
            classG.propG = "G"

            test("classG.propE1 - expect 'F1'", eq(classG.propF1, 'F1'))
            test("classG.propE2 - expect 'F2'", eq(classG.propF2, 'F2'))
            test("classG.propG - expect 'G'", eq(classG.propG, 'G'))
        }

        tcase("Test 2: Verify AddRef for V1") {

                ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
                let classF = new ClassF('OpenHarmony', 'V1');
                StateTracker.reset();
                classF.propF1;
                test("Use classF.propF1 expect 1 add ref for classF", eq(StateTracker.getRefCnt(), 1))

                classF.propF2;
                test("Use classA.propF2 expect 1 new add ref. Total = 2", eq(StateTracker.getRefCnt(), 2))
        }

        tcase("Test 3: Verify AddRef for V2") {

                ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
                let classF = new ClassF('OpenHarmony', 'V2');
                StateTracker.reset();
                classF.propF1;
                test("Use classF.propF1 expect 1 add ref for classF", eq(StateTracker.getRefCnt(), 1))

                classF.propF2;
                test("Use classA.propF2 expect 1 new add ref. Total = 2", eq(StateTracker.getRefCnt(), 2))
        }

        tcase("Test 4: Verify FireChange for V1") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classF = new ClassF('OpenHarmony', 'V1');
                StateTracker.reset();
                classF.propF2;
                test("classF.propF1 referenced but not changed. Firecount = 0", eq(StateTracker.getFireChangeCnt(), 0))

                const lastItem = 5;
                for (let i = 1; i <= lastItem; i++) {
                    classF.propF2 = `OpenHarmony ${i}`;
                    test(`classF.propF2 changed. Firecount = ${i}`, eq(StateTracker.getFireChangeCnt(), i))
                }
                classF.propF2 = `OpenHarmony ${lastItem}`;
                test("classF.propF2 set to the same value. Firecount = 0", eq(StateTracker.getFireChangeCnt(), lastItem))
        }

        tcase("Test 4: Verify FireChange for V2") {

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classF = new ClassF('OpenHarmony', 'V1');
                StateTracker.reset();
                classF.propF2;
                test("classF.propF1 referenced but not changed. Firecount = 0", eq(StateTracker.getFireChangeCnt(), 0))

                const lastItem = 5;
                for (let i = 1; i <= lastItem; i++) {
                    classF.propF2 = `OpenHarmony ${i}`;
                    test(`classF.propF2 changed. Firecount = ${i}`, eq(StateTracker.getFireChangeCnt(), i))
                }
                classF.propF2 = `OpenHarmony ${lastItem}`;
                test("classF.propF2 set to the same value. Firecount = 0", eq(StateTracker.getFireChangeCnt(), lastItem))
        }

        // Should in some schenarios ref count be increased only once when accessing the same property?
        tcase("Test 5: Multiple accesses to same prop increase addRef") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classF = new ClassF('OpenHarmony', 'V1');
            StateTracker.reset();

            classF.propF1;
            classF.propF1;
            classF.propF1;

            test("Repeated access to propF1 still results 3 addRef", eq(StateTracker.getRefCnt(), 3));
        }

        tcase("Test 6: Switch renderingComponent between accesses") {
            let classF = new ClassF('OpenHarmony', 'V1');
            StateTracker.reset();

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            classF.propF1;

            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            classF.propF2;

            test("Switching components still counts both addRefs", eq(StateTracker.getRefCnt(), 2));
        }

        tcase("Test 7: Setting same value repeatedly does not increase FireChange") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classF = new ClassF('OpenHarmony', 'V1');
            classF.propF1;
            StateTracker.reset();
            classF.propF1 = "OpenHarmonyX";
            classF.propF1 = "OpenHarmonyX";
            classF.propF1 = "OpenHarmonyX";

            test("Setting same value multiple times should only fire once", eq(StateTracker.getFireChangeCnt(), 1));
        }

        tcase("Test 8: No fire change without first referencing") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV2;
            let classF = new ClassF('OpenHarmony', 'V2');
            StateTracker.reset();

            classF.propF2 = "X";
            test("Set before referencing = no fire", eq(StateTracker.getFireChangeCnt(), 0));

            classF.propF2;
            classF.propF2 = "Y";
            test("After referencing, set causes fire", eq(StateTracker.getFireChangeCnt(), 1));
        }

        tcase("Test 9: Access and modify both props for full coverage") {
            ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;
            let classF = new ClassF('HarmonyOS', 'V1');
            StateTracker.reset();

            classF.propF1;
            classF.propF2;

            classF.propF1 = "New F1";
            classF.propF2 = "New F2";

            test("Both props referenced = 2 addRefs", eq(StateTracker.getRefCnt(), 2));
            test("propF2 modified = 1 fire change", eq(StateTracker.getFireChangeCnt(), 2));
        }
    }

    ttest();
    return true;
}


// add addRef/Firechnage count
// for V1 and for V2