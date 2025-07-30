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
import { ILocalDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { IComputedDecoratedVariable, ComputedFunction } from 'stateManagement/interface/iComputedDecorator.ets'
import { ObserveSingleton } from 'stateManagement/base/observeSingleton.ets';

import { IMonitorFunctionDecorator, IMonitorPathsInfo, MonitorPathLambda, MonitorFunction } from 'stateManagement/interface/iMonitorFunctionDecorator.ets'
import { IMonitor } from 'stateManagement/sdk/iMonitor.ets'
import { UIUtilsPlugin, UIUtils } from 'stateManagement/sdk/uiutils.ets';
import { WrappedDate } from 'stateManagement/base/observeWrappedDate'

// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
import { int32 } from '../../mock/env_mock.ets'


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
    stateA?: ClassA
    stateN?: number
    stateM?: number
}

/*
ETS:

@ComponentV2 struct CompA {
   @Local n : number = 8;
   @Computed get squareN() : number {
        return this.n * this.n
   }
    build() {
        Text(this.squareN)
    }
}

UIPlugin output:

class CompA extends CustomComponentBase {

    private _computed_squareN : IComputedVariable<number>
        = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                return this.n * this.n
            }
        );
    get squareN() : number {
        return this._computed_squareN.get()
    }
    // no set()
*/

class EntryComputedComponent extends ExtendableComponent {

    private _backing_stateA: IStateDecoratedVariable<ClassA>;
    private _backing_stateN: ILocalDecoratedVariable<number>;
    private _backing_stateM: ILocalDecoratedVariable<number>;

    private _computed_squareN : IComputedDecoratedVariable<number>;
    private _computed_sum : IComputedDecoratedVariable<number>;

    // == Notes about wrapping of the returned value ==
    // We have to make returned value observable object as in 1.1
    // That means that we call corresponding UIUtilsPlugin.makeObservedXXX method
    // for simple types we can not do wrapping
    //
    // If return value is of type Date, Array, Set, Map or InterfaceObjectLiteral
    // code for get function will look like that:
    //
    // get computedDate(): Date {
    //     return UIUtilsPlugin.makeObservedDate(new Date())
    // }
    //
    // UIUtilsPlugin defined makeObservedSet, makeObservedMap,
    // makeObservedArray, makeObservedProxied

    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get squareN() : int32 {
        return this._computed_squareN.get()
    }

    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get sumNM() : int32 {
        return this._computed_sum.get()
    }
    get stateN(): int32 {
        return this._backing_stateN!.get();
    }
    set stateN(newValue: int32) {
        this._backing_stateN!.set(newValue);
    }
    get stateM(): int32 {
        return this._backing_stateM!.get();
    }
    set stateM(newValue: int32) {
        this._backing_stateM!.set(newValue);
    }

    get stateA(): ClassA {
        return this._backing_stateA!.get();
    }
    set stateA(newValue: ClassA) {
        this._backing_stateA!.set(newValue);
    }

    public watchFuncRunCtr : number = 0;

    onStateAChanged(propertyName : string) : void { 
        this.watchFuncRunCtr++;
        stateMgmtConsole.log(`VPAK @State stateA @Watch exec: propertyName='${propertyName}', newValue propA: ${this.stateA.propA}  RUN CNT='${this.watchFuncRunCtr}'`) 
    };

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);

        // StateDecoratedVariable
        this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
            this,
            "stateA",
            param.stateA !== undefined
            ? param.stateA!
            :  new ClassA("name1", 100),
            undefined
         );

         this._backing_stateN = StateMgmtFactory.makeLocal<number>(
            this,
            "stateN",
            param.stateN !== undefined
            ? param.stateN!
            :  3
        );

        this._backing_stateM = StateMgmtFactory.makeLocal<number>(
            this,
            "stateM",
            param.stateM !== undefined
            ? param.stateM!
            :  100
        );

        // We have to define all state variables first
        this._computed_squareN = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                stateMgmtConsole.error("_computed_squareN lambda  .......................")
                return this.stateN * this.stateN
            },
            "SquareN"
        )

        this._computed_sum = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                stateMgmtConsole.error("_computed_sum lambda  .......................")
                return this.stateN + this.stateM
            },
            "sum"
        )
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

interface ChainedComputedComponent_init_update_struct {
    celcius?: number
}

/*
    @Computed get fahrenheit() : number {
        console.error("computing fahrenheit")
        return this.celcius * 9 / 5 + 32; // C -> F
    }

    @Computed get kelvin(): number {
        console.error("computing kelvin")
        return (this.fahrenheit - 32) * 5/9 + 273.15; // F -> K
    }
*/

class ChainedComputedComponent extends ExtendableComponent {
    private _backing_celcius: ILocalDecoratedVariable<number>;
    private _computed_fahrenheit : IComputedDecoratedVariable<number>;
    private _computed_kelvin : IComputedDecoratedVariable<number>;

    get celcius(): number {
        stateMgmtConsole.log("EntryComputedComponent, celcius get")
        return this._backing_celcius!.get();
    }
    set celcius(newValue: number) {
        stateMgmtConsole.log("EntryComputedComponent, celcius set " + newValue)
        this._backing_celcius!.set(newValue);
    }
    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get kelvin() : number {
        return this._computed_kelvin.get()
    }
    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get fahrenheit(): number {
        return this._computed_fahrenheit.get()
    }

    public monitorFunctionRunCount: number = 0;

    private _monitorDecorator: IMonitorFunctionDecorator;
    public _monitorFunction?: (m: IMonitor) => void;

    constructor(parent : ExtendableComponent | null, param : ChainedComputedComponent_init_update_struct) {
        super(parent);

        /**
         * First step: we initialize state variables
         */
        this._backing_celcius = StateMgmtFactory.makeLocal<number>(
            this,
            "celcius",
            param.celcius !== undefined ? param.celcius! :  3
        );

        /**
         * Second step: we initialize @Computed
         * @Computed code generated at the end of constructor after initialization code for
         * @Local variables.
         */
        this._computed_fahrenheit = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                stateMgmtConsole.error("computing fahrenheit")
                return this.celcius * 9 / 5 + 32; // C -> F
            },
            "fahrenheit"
        )

        this._computed_kelvin = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                stateMgmtConsole.error("computing kelvin")
                return (this.fahrenheit - 32) * 5/9 + 273.15; // F -> K
            },
            "Kelvin"
        )

        /**
         *  TODO: what is the correct place to put monitor initialization code?
         **/
        this._monitorDecorator = StateMgmtFactory.makeMonitor(new Array<IMonitorPathsInfo>(
            StateMgmtFactory.makeMonitorPath("kelvin", () => {
                const result = this.kelvin;
                stateMgmtConsole.log("lamda for path kelvin, value: "+result);
                return result;
            })
        ),
            (m: IMonitor) => {
                if(this._monitorFunction) {
                    this.monitorFunctionRunCount++;
                    this._monitorFunction!(m)
                }
            }
        );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }
    build() {
    }
}

/*
@ObservedV2 class ClassWithComputed {
    @Track propB1: string = "Kelvinkatu";
    @Track propB2: boolean = false;
    @Computed get computed_homeAddress(): string {
        console.error("computing fahrenheit")
        return "Home address: " + this.propB1
    }
}
*/

export class ClassWithComputed implements IObservedObject {
    private ____V1RenderId: RenderIdType = 0;
    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }
    public addWatchSubscriber(watchId: WatchIdType): void {
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return false;
    }

    private readonly __meta: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    // IObservedObject interface
    // @JsonIgnore

    private __backing_propB1: string = "Kelvinkatu";

    public get propB1(): string {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB1`);
        this.__meta.addRef();
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB1`);
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            this.__meta.fireChange();
        }
    }
    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        stateMgmtConsole.log(`ClassB (@Observe compat): get propB2`);
        this.__meta.addRef();
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
        stateMgmtConsole.log(`ClassB (@Observe compat): set propB2`);
        if (this.__backing_propB2 !== newValue) {
            this.__backing_propB2 = newValue;
            this.__meta.fireChange();
        }
    }
    /**
     * @Computed generated code:
     */
    private __computed_homeAddress : IComputedDecoratedVariable<string>;
    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get homeAddress() : string {
        return this.__computed_homeAddress.get()
    }
    constructor(homeAddress:string) {
        /**
         * First step: we initialize state variables
         */
        this.propB1 = homeAddress
        /**
         * Second step: we initialize @Computed
         */
        this.__computed_homeAddress = StateMgmtFactory.makeComputedVariable<string>(
            () : string => {
                console.error("computing fahrenheit")
                return "Home address: " + this.propB1
            },
            "homeAddress"
        )
    }
}

/*
Instrumented class let us verify the order of initialization of state variables and @Computed
Conclusion is that all @Computed executed after the class constructor execution 
in the order of their definition in the class
```ts
@ObservedV2
class Point
{
  x: number
  y: number = 0;
  @Computed get d(): number {
    console.log("### @Computed d() start " + this.y)
    let r =  1./this.y
    console.log("### @Computed d() end " + this.y)
    return r
  }

  @Computed get e(): number {
    console.log("### @Computed e() start " + this.x)
    let r =  1./this.x + this.d
    console.log("### @Computed f() end " + this.x)
    return r
  }

  constructor(x: number)
  {
    console.log("### @Computed CTOR start")
    this.x = x
    this.y = 1;
    console.log("### @Computed CTOR end")
  }
}

@Local computedPoint : Point = new Point(10)

### @Computed CTOR start
### @Computed CTOR end
### @Computed d() start 1
### @Computed d() end 1
### @Computed e() start 10
### @Computed f() end 10
```
*/

interface ComputedComponentWithException_init_update_struct {
    stateN?: number
}

class ComputedComponentWithException extends ExtendableComponent {

    private _backing_stateN: ILocalDecoratedVariable<number>;

    private _computed_sumWithError : IComputedDecoratedVariable<number>;

    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get sumWithError() : int32 {
        return this._computed_sumWithError.get()
    }
    get stateN(): int32 {
        return this._backing_stateN!.get();
    }
    set stateN(newValue: int32) {
        this._backing_stateN!.set(newValue);
    }

    public watchFuncRunCtr : number = 0;

    constructor(parent : ExtendableComponent | null, param : ComputedComponentWithException_init_update_struct) {
        super(parent);

        // StateDecoratedVariable
         this._backing_stateN = StateMgmtFactory.makeLocal<number>(
            this,
            "stateN",
            param.stateN !== undefined
            ? param.stateN!
            :  3
        );

        this._computed_sumWithError = StateMgmtFactory.makeComputedVariable<number>(
            () : number => {
                console.error("_computed_sumWithError lambda  .......................")
                this.stateN = this.stateN + 1; // That is not allowed to do
                return this.stateN + this.stateN
            },
            "sumWithError"
        )
        console.error("ExtendableComponent CTOR end")
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    build() {
    }
}

interface InterfacePerson {
    first: string
    last: string

}
class ComputedComponentWithInterfaceLiteral extends ExtendableComponent {
    private _backing_person_interface: IStateDecoratedVariable<InterfacePerson>;
    get PersonInterface(): InterfacePerson {
        console.log("EntryComputedComponent, stateN get")
        return this._backing_person_interface!.get();
    }
    set PersonInterface(newValue: InterfacePerson) {
        console.log("EntryComputedComponent, stateN set " + newValue)
        this._backing_person_interface!.set(newValue);
    }

    /**
     * @Computed generated code:
     */
    private __computed_fullName : IComputedDecoratedVariable<string>;

    // We do not wrap returned simple types, they are not observed objects
    // See sample with Date for functional code
    get fullName() : string {
        return this.__computed_fullName.get()
    }

    constructor(parent : ExtendableComponent | null, param : ComputedComponentWithInterfaceLiteral_init_update_struct) {
        super(parent);

        // StateDecoratedVariable
         this._backing_person_interface = StateMgmtFactory.makeState<InterfacePerson>(
            this,
            "PersonInterface",
            UIUtils.makeObserved(
                param.person !== undefined
                    ? param.person!
                    : {first: "first", last: "last"} as InterfacePerson
            )
        );

        this.__computed_fullName = StateMgmtFactory.makeComputedVariable<string>(
            () : string => {
                return this.PersonInterface.first + "-" + this.PersonInterface.last;
            },
            "fullName"
        )
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    build() {
    }
}

interface ComputedComponentWithInterfaceLiteral_init_update_struct {
    person?: InterfacePerson
}

class ComputedComponentWithDate extends ExtendableComponent {
    public current: Date;

    /**
     * @Computed generated code:
     */
    private __computed_tomorrow : IComputedDecoratedVariable<Date>;

    // We Do wrap returned Date types,
    // so that is it observable object
    // Similar wrapping to be done if returned value is
    // Set, Map, Array of Interface Object Literal
    get tomorrow() : Date {
        // We return Date type, so make it observable by wrapping
        // in WrappedDate class
        return UIUtilsPlugin.makeObservedDate(this.__computed_tomorrow.get())!
    }

    constructor(parent : ExtendableComponent | null, param : ComputedComponentWithDate_init_update_struct) {
        super(parent);
        this.current = new Date()
        this.__computed_tomorrow = StateMgmtFactory.makeComputedVariable<Date>(
            () : Date => {
                let d = new Date();
                d.setDate(d.getDate() + 1)
                return d;
            },
            "tomorrow"
        )
    }

    __updateStruct(param: ComputedComponentWithDate_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    build() {
    }
}

interface ComputedComponentWithDate_init_update_struct {
    current?: Date
}

export function run_computed() : Boolean {
    console.log(`run_computed() =======================`);
    const tests = tsuite("@Computed tests", () => {
    stateMgmtConsole.log(`run making entry...`);
    const entryComponent = new EntryComputedComponent(null, {stateN: 2, stateM: 100});
    stateMgmtConsole.log(`run making entry... done`);

    tcase("Test 1: @Computed square 25", () => {
        console.log(`============= entryComponent.stateN to 5 >>>>>>>>>>>>>>>>>>>`)
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty2()
        test(`entryComponent.squareN = ${entryComponent.squareN} === 25`, entryComponent.squareN === 25);
    })

    tcase("Test 2: @Computed square 36, after update", () => {
        console.log(`============= entryComponent.stateN to 5 >>>>>>>>>>>>>>>>>>>`)
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty2()
        entryComponent.stateN = 6
        ObserveSingleton.instance.updateDirty2()
        test(`entryComponent.squareN = ${entryComponent.squareN} === 36`, entryComponent.squareN === 36);
    })

    tcase("Test 3: @Computed sumMN ", () => {
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty2()
        console.log(`<<<< getting squareN? ${entryComponent.stateN},  ${entryComponent.squareN}`)
        console.log(`<<<< getting sum ${entryComponent.stateN}, ${entryComponent.stateM}: ${entryComponent.sumNM}`)
        test(`entryComponent.squareN = ${entryComponent.sumNM} === 105`, entryComponent.sumNM === 105);
    })

    tcase("Test 4: @Computed 2nd sumMN ", () => {
        console.log(`============= entryComponent.stateN to 5 >>>>>>>>>>>>>>>>>>>`)
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty2()
        console.log(`<<<< getting squareN? ${entryComponent.stateN},  ${entryComponent.squareN}`)
        console.log(`<<<< getting sum ${entryComponent.stateN}, ${entryComponent.stateM}: ${entryComponent.sumNM}`)

        entryComponent.stateM = 200
        ObserveSingleton.instance.updateDirty2()
        console.log(`<<<< getting squareN? ${entryComponent.stateN}, 36? ${entryComponent.squareN}`)
        console.log(`<<<< getting sum ${entryComponent.stateN}, ${entryComponent.stateM}: ${entryComponent.sumNM}`)
        test(`entryComponent.squareN = ${entryComponent.sumNM} === 205`, entryComponent.sumNM === 205);
    })

    tcase("Test 5: @Computed chained ", () => {
        console.log(`============= Chained start`)
        const chainedComponent = new ChainedComputedComponent(null, {celcius: 10});
        console.log(`============= Chained ---> updateDirty`)
        ObserveSingleton.instance.updateDirty2()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 50`, eq(chainedComponent.fahrenheit, 50));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 283.15`, eq(chainedComponent.kelvin, 283.15));

        console.log(`============= Chained ---> chainedComponent.celcius = 20  =================================================`)
        chainedComponent.celcius = 20
        ObserveSingleton.instance.updateDirty2()
        console.log(`<<<< getting celcius? ${chainedComponent.celcius}`)
        console.log(`<<<< getting fahrenheit? ${chainedComponent.fahrenheit}`)
        console.log(`<<<< getting kelvin? ${chainedComponent.kelvin}`)
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 68`, eq(chainedComponent.fahrenheit, 68));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
    })

    tcase("Test 5: @Computed chained with Kelvin Monitor", () => {
        const chainedComponent = new ChainedComputedComponent(null, {celcius: 10});
        ObserveSingleton.instance.updateDirty2()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 50`, eq(chainedComponent.fahrenheit, 50));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 283.15`, eq(chainedComponent.kelvin, 283.15));

        let monitorFunction = (m: IMonitor) => {
            console.log(`>>>>>> KELVIN monitor called ${chainedComponent.kelvin} <<<<<<<<<<<<<<<<`)
        }

        chainedComponent._monitorFunction = monitorFunction
        chainedComponent.celcius = 20
        ObserveSingleton.instance.updateDirty2()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 68`, eq(chainedComponent.fahrenheit, 68));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
        test(`monitor count = ${chainedComponent.monitorFunctionRunCount} === 1`, eq(chainedComponent.monitorFunctionRunCount, 1));
    })

    tcase("Test 6: @Computed in the class", () => {
        const classWithComputed = new ClassWithComputed("Celciuskatu")
        test(`classWithComputed.propB1 = ${classWithComputed.propB1} === Celciuskatu`, eq(classWithComputed.propB1, "Celciuskatu"));
        test(`classWithComputed.propB1 = ${classWithComputed.homeAddress} === Home Address: Celciuskatu`, eq(classWithComputed.homeAddress, "Home address: Celciuskatu"));
    })

    tcase("Test 7: @Computed that changes state -> Exception", () => {
        let detected:Boolean = false;
        try {
            let comp = new ComputedComponentWithException(null, {stateN: 2})
            let a = comp.sumWithError
        } catch(e) {
            detected = true;
        } finally {
            test(`Exception detected as expected`, detected);
        }
    })

    tcase("Test 8: @Computed using Observed Interface object", () => {
        let ObjLiteral = new ComputedComponentWithInterfaceLiteral(null,
            {person: {first: "Jack", last: "Ripper"} as InterfacePerson})
        test(`ObjLiteral.fullName = ${ObjLiteral.fullName} === Jack-Ripper`, eq(ObjLiteral.fullName, "Jack-Ripper"));
        ObjLiteral.PersonInterface.first = "John"
        test(`ObjLiteral.fullName = ${ObjLiteral.fullName} === Jack-Ripper`, eq(ObjLiteral.fullName, "Jack-Ripper"));
        ObserveSingleton.instance.updateDirty2()
        test(`ObjLiteral.fullName = ${ObjLiteral.fullName} === John-Ripper`, eq(ObjLiteral.fullName, "John-Ripper"));
    })

    tcase("Test 9: @Computed using wrapped Date", () => {
        let d = new Date();
        let comp = new ComputedComponentWithDate(null, {})
        comp.current = d;
        d.setDate(d.getDate() + 1)
        // No test for modification of WrappedDate
        test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(comp.tomorrow.getDate(), d.getDate()));
        test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(Type.of(comp.tomorrow).getName(), "observeWrappedDate.WrappedDate"));
        test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(comp.tomorrow instanceof WrappedDate, true));
   })

    });

    tests();
    return true;
}
