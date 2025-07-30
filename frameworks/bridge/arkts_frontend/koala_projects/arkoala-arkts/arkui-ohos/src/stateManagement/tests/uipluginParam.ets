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
import { ILocalDecoratedVariable, IParamV2DecoratedVariable } from 'stateManagement/interface/iDecorators'
import { IMonitorFunctionDecorator, IMonitorPathsInfo, MonitorPathLambda, MonitorFunction } from 'stateManagement/interface/iMonitorFunctionDecorator.ets'
import { IMonitor } from 'stateManagement/sdk/iMonitor.ets'
import { ObserveSingleton } from '../../base/observeSingleton.ets';
import { IComputedDecoratedVariable, ComputedFunction } from 'stateManagement/interface/iComputedDecorator.ets'

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { StateTracker } from 'stateManagement/utest/lib/stateTracker'
import { int32 } from '../../mock/env_mock.ets'
let childComp: ChildComponent | null = null ;

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
        stateMgmtConsole.log(`ClassD: get @Track propA`);
        this.conditionalAddRef(this.__meta_propA);
        return this.__backing_propA
    }
    public set propA(newValue: string) {
        if (this.__backing_propA !== newValue) {
            stateMgmtConsole.log(`ClassD: set @Track propA`);
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
        stateMgmtConsole.log(`ClassD: get @Track propB`);
        this.conditionalAddRef(this.__meta_propB);
        return this.__backing_propB;
    }
    public set propB(newValue: number) {
        stateMgmtConsole.log(`ClassD: set @Track propB`);
        if (this.__backing_propB !== newValue) {
            this.__backing_propB = newValue;
            this.__meta_propB.fireChange();
            this.executeOnSubscribingWatches("propB");
        }
    }
}

interface EntryComponent_init_update_struct {
    localA?: ClassA
    localPrice?: number
}

class EntryComponent extends ExtendableComponent {

    // @Local localA: ClassA = (new ClassA());
    private _backing_localA: ILocalDecoratedVariable<ClassA>;
    private _backing_localPrice: ILocalDecoratedVariable<number>;

    get localA(): ClassA {
        return this._backing_localA!.get();
    }
    set localA(newValue: ClassA) {
        this._backing_localA!.set(newValue);
    }


    get localPrice(): number {
        return this._backing_localPrice!.get();
    }
    set localPrice(newValue: number) {
        this._backing_localPrice!.set(newValue);
    }


    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);

      this._backing_localA = StateMgmtFactory.makeLocal<ClassA>(
        this,
        "stateA",
        param.localA !== undefined
        ? param.localA!
        :  new ClassA("name1", 100)
      );

      this._backing_localPrice = StateMgmtFactory.makeLocal<number>(
        this,
        "localPrice",
        100
      );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    incrPropB() {
      this.localA.propB += 1;
    }

    resetName() {
      this.localA.propA = this.localA.propA+'_A'
    }

    assignNewA() {
      this.localA = new ClassA("newObject", 1101)
    }

    setNewPrice(num : number) {
      this.localPrice = num;
    }

    build() {
        childComp = new ChildComponent(this, { paramA: this.localA })

    }
}


interface ChildComponent_init_update_struct {
    // @Parem init and update form parent
    // UIPlugin needs to consider the @Required deco.
    paramA: ClassA
    paramPrice: number
}

// @Component struct ChildComponent
class ChildComponent extends ExtendableComponent{


    private _computed_sum : IComputedDecoratedVariable<number>;
    private _backing_statePrice: IParamV2DecoratedVariable<number>;

    get computedPrice() : int32 {
        return this._computed_sum.get()
    }

    get paramPrice(): int32 {
        console.log("EntryComputedComponent, paramPrice get")
        return this._backing_statePrice!.get();
    }

    // @Required @Param paramA : number;  // no local value
    private _backing_paramA: IParamV2DecoratedVariable<ClassA>;
    get paramA(): ClassA {
        return this._backing_paramA.get();
    }

    public monitorFunctionRunCount: number = 0;

    private _monitor: IMonitorFunctionDecorator;
    public onPropBChanged?: (m: IMonitor) => void;

    constructor(parent : ExtendableComponent | null, param: ChildComponent_init_update_struct) {
        super(parent);
        // @Param can init from parent, can have local value;
        this._backing_paramA = StateMgmtFactory.makeParamV2<ClassA>(
            this,
            "paramA",
            param.paramA)

        // when @Param has a local value
        // param.paramA  // FIXME, need to check if paramA is defined, chk for undefined is WRONG
        // ? param.paramA
        // : localValue;

        this._monitor = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("paramA.propB", () => {
                const result = this.paramA.propB;
                console.log("===== lamda for path paramA.probB, value: ", result);
                return result;
            })
        ),
            (m: IMonitor) => {
                this.monitorFunctionRunCount += 1;
            }
        );

        this._backing_statePrice = StateMgmtFactory.makeParamV2<number>(
            this,
            "paramPrice",
            param.paramPrice
        );

        this._computed_sum = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                console.error(`_computed_sum lambda  ${this.paramPrice + this.paramPrice}`)
                return this.paramPrice + this.paramPrice
            },
            "sum"
        )

    }

    updateValue() {
        this.paramA.propB += 200;
    }

    update_struct(param: ChildComponent_init_update_struct) {
        console.log(`uiplugin-param ChildComponent constructor update_struct`)
        this._backing_paramA.update(param.paramA);
        this._backing_statePrice.update(param.paramPrice);
    }

}

export function run_param() : Boolean {

  const tests = tsuite("@Param  tests", () => {
    stateMgmtConsole.log(`run @Param  tests=======================`);

    const compA = new EntryComponent(null, {});
    compA.build();

    tcase("Test 1: @Local init value ", () => {
        compA.build();
        test(`compA.localA.propA = ${compA.localA.propA} === 'name1'`, eq(compA.localA.propB,100));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'name1'`, eq(childComp!.paramA.propB,100));
    })

    tcase("Test 2: @Local increment object value ", () => {
        compA.incrPropB();
        test(`compA.localA.propA = ${compA.localA.propA} === 'name1'`,  eq(compA.localA.propB,101));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'name1'`, eq(childComp!.paramA.propB,101));
    })

    tcase("Test 3: @Local reset object property ", () => {
        compA.resetName();
        test(`compA.localA.propA = ${compA.localA.propA} === 'name1_A'`, eq(compA.localA.propB,101));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'name1_A'`, eq(childComp!.paramA.propB,101));
    })

    tcase("Test 4: @Param update value ", () => {
        compA!.incrPropB();
        test(`compA.localA.propA = ${compA.localA.propA} === 'name1_A'`, eq(compA.localA.propB,102));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'name1_A'`, eq(childComp!.paramA.propB,102));
    })

    tcase("Test 5: @Local reset object property ", () => {
        compA.assignNewA();
        childComp!.update_struct({ paramA: compA.localA, paramPrice: compA.localPrice });
        test(`compA.localA.propA = ${compA.localA.propA} === 'newObject'`, eq(compA.localA.propB,1101));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propA,'newObject'));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propB,1101));
    })

    tcase("Test 6: @Local reset object property - fireChange Test", () => {
        StateTracker.reset();
        compA.assignNewA();
        childComp!.update_struct({ paramA: compA.localA, paramPrice: compA.localPrice });
        test(`compA.localA.propA = ${compA.localA.propA} === 'newObject'`, eq(compA.localA.propB,1101));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propA,'newObject'));
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propB,1101));
        test("Expect Fire change count for  Monitor, stateA, paramA", eq(StateTracker.getFireChangeCnt(), 3));
    })

    tcase("Test 7: @Local reset object property - addRef Test", () => {
        compA.assignNewA();
        childComp!.update_struct({ paramA: compA.localA, paramPrice: compA.localPrice });
        StateTracker.reset();
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propB,1101));
        test("Expect AddRef to paramA 2 times", eq(StateTracker.getRefCnt(), 0))
    })

    tcase("Test 8: @Local reset object property - Monitor Test", () => {
        compA.assignNewA();
        childComp!.update_struct({ paramA: compA.localA, paramPrice: compA.localPrice });

        StateTracker.reset();
        test(`childComp.paramA.propA = ${childComp!.paramA.propA} === 'newObject'`, eq(childComp!.paramA.propB,1101));
        ObserveSingleton.instance.updateDirty2();
        test("Expect Monitor to paramA 1 times", eq(childComp!.monitorFunctionRunCount, 1))
    })

    tcase("Test 9: @Local update val. Verify childComp Computed", () => {
        // Computed value is 2 * paramPrice
        compA.setNewPrice(5);
        childComp!.update_struct({ paramA: compA.localA, paramPrice: compA.localPrice });
        ObserveSingleton.instance.updateDirty2()
        console.log(`Getting sum compA.localPrice ${compA.localPrice} childComp!.computedPrice ${childComp!.computedPrice}`)
        test(`entryComponent.squareN = ${childComp!.computedPrice} === 10`, eq(childComp!.computedPrice, 10));
    })

    });

  tests();
  return true;

}
