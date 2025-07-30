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

import { ExtendableComponent } from 'stateManagement/base/extendableComponent'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType, WatchFuncType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory'
import { IStateDecoratedVariable } from 'stateManagement/interface/iDecorators'

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { StateTracker } from 'stateManagement/utest/lib/stateTracker'
import { ObserveSingleton } from '../../base/observeSingleton.ets'

export class ClassA implements IObservedObject, IWatchSubscriberRegister {

    constructor(propA: string, propB: number) {
        // init in constructor
        // need to change to _backing,
        // otherwise compiler warns about uninitialized
        // __backing
        this.__backing_propA = propA;
        this.__backing_propB = propB;
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

    // @Track name : string;
    // @JsonRename("name")
    private __backing_propA: string;

    // @JsonIgnore
    private readonly __meta_propA: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propA(): string {
        stateMgmtConsole.log(`ClassA: get @Track propA`);
        this.conditionalAddRef(this.__meta_propA);
        return this.__backing_propA
    }
    public set propA(newValue: string) {
        if (this.__backing_propA !== newValue) {
            stateMgmtConsole.log(`ClassA: set @Track propA`);
            this.__backing_propA = newValue;
            this.__meta_propA.fireChange();
            this.executeOnSubscribingWatches("propA");
        }
    }

    // @Track propD2 : number;
    // @JsonRename("propD2")
    private __backing_propB: number;

    // @JsonIgnore
    private readonly __meta_propB: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propB(): number {
        stateMgmtConsole.log(`ClassA: get @Track propB`);
        this.conditionalAddRef(this.__meta_propB);
        return this.__backing_propB;
    }
    public set propB(newValue: number) {
        stateMgmtConsole.log(`ClassA: set @Track propB`);
        if (this.__backing_propB !== newValue) {
            this.__backing_propB = newValue;
            this.__meta_propB.fireChange();
            this.executeOnSubscribingWatches("propB");
        }
    }
}


interface EntryComponent_init_update_struct {
    stateA?: ClassA
}

class EntryComponent extends ExtendableComponent {

    // @State eatenFoodItems: ClassA = (new ClassA());
    private _backing_stateA: IStateDecoratedVariable<ClassA>;

    get stateA(): ClassA {
        console.log(`EntryComponent: get @State stateA`);
        return this._backing_stateA!.get();
    }
    set stateA(newValue: ClassA) {
        this._backing_stateA!.set(newValue);
    }

    public watchFuncRunCtr : number = 0;

    onStateAChanged(propertyName : string) : void {
        this.watchFuncRunCtr++;
        stateMgmtConsole.log(`@State stateA @Watch exec: propertyName='${propertyName}', newValue propA: ${this.stateA.propA}  RUN CNT='${this.watchFuncRunCtr}'`)
    };

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);
        const watchFunc : WatchFuncType =  (propName: string) => { this.onStateAChanged(propName) };


      this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
        this,
        "stateA",
        param.stateA !== undefined
        ? param.stateA!
        :  new ClassA("name1", 100),
        watchFunc
      );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    incrPropB() {
      this.stateA.propB += 1;
    }

    resetName() {
      this.stateA.propA = this.stateA.propA+'_A'
    }

    assignNewA() {
      this.stateA = new ClassA("newObject", 1101)
    }

    build() {
    }
}



export function run_state() : Boolean {

  const tests = tsuite("@State tests", () => {
    stateMgmtConsole.log(`run @State tests=======================`);

    const compA = new EntryComponent(null, {});
    ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;

    tcase("Test 1: @State init value ", () => {
        compA.build();
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'name1'`, eq(compA.stateA.propA, 'name1'));
        test(`compA.stateA.propB = ${compA.stateA.propB} === 100`, eq(compA.stateA.propB, 100));

    })

    tcase("Test 2: @State increment object value ", () => {
        compA.incrPropB();
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'name1'`, eq(compA.stateA.propA, 'name1'));
        test(`compA.stateA.propB = ${compA.stateA.propB} === 101`, eq(compA.stateA.propB, 101));

    })

    tcase("Test 3: @State reset object property ", () => {
        compA.resetName();
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'name1_A'`, eq(compA.stateA.propA, 'name1_A'));
        test(`compA.stateA.propA = ${compA.stateA.propB} === 101`, eq(compA.stateA.propB, 101));

    })

    tcase("Test 4: @State reset object ", () => {
        compA.assignNewA();
        test(`compA.stateA.propA = ${compA.stateA.propA} === 'newObject'`, eq(compA.stateA.propA, 'newObject'));
        test(`compA.stateA.propA = ${compA.stateA.propB} === 1101`, eq(compA.stateA.propB, 1101));

    })

    tcase("Test 5: @State AddRef test ", () => {
        StateTracker.reset();
        compA.stateA.propA;
        test("Assign to: AddRef, expect 3", eq(StateTracker.getRefCnt(), 3));
    })

    tcase("Test 6: @State FireChange test ", () => {
        StateTracker.reset();
        compA.stateA.propA = "newName";
        test("Assign to: FireChange, expect 1", eq(StateTracker.getFireChangeCnt(), 1));
    })

    tcase("Test 7: @State @Watch test ", () => {
        compA.watchFuncRunCtr = 0;
        compA.assignNewA();
        test("Assign to: Watch func exec once", eq(compA.watchFuncRunCtr, 1));

        compA.watchFuncRunCtr = 0;
        compA.incrPropB();
        test("@Observed property change: Watch func exec once", eq(compA.watchFuncRunCtr, 1));
    })

  });

  tests();
  return true;

}
