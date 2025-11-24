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

import { ExtendableComponent } from '../mock/extendableComponent';

import { IObservedObject, RenderIdType } from '../decorator'
import { IWatchSubscriberRegister, WatchIdType, WatchFuncType } from '../decorator'
import { ISubscribedWatches } from '../decorator';

import { IStateDecoratedVariable } from '../decorator'
import { ILocalDecoratedVariable } from '../decorator'
import { IMutableStateMeta } from '../decorator'
import { IComputedDecoratedVariable } from '../decorator'
import { IMonitorDecoratedVariable, IMonitorPathInfo} from '../decorator'
import { IVariableOwner } from '../decorator'
import { IMonitor } from '../decorator'
import { WrappedDate } from '../base/observeWrappedDate'

import { tsuite, tcase, test, eq } from './lib/testFramework'
import { UIUtils } from '../utils';
import { UIUtilsImpl } from '../base/uiUtilsImpl';
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
import { int32 } from '@koalaui/common';
let StateMgmtFactory = STATE_MGMT_FACTORY;

let stateMgmtConsole=console;

class ClassA implements IObservedObject, IWatchSubscriberRegister 
{
    private readonly subscribedWatches_: ISubscribedWatches;

    constructor(propA: string, propB: int) {
        // init in constructor
        // need to change to _backing, 
        // otherwise compiler warns about uninitialized 
        // __backing
        this.__backing_propA = propA;
        this.__backing_propB = propB;
        this.subscribedWatches_ = StateMgmtFactory.makeSubscribedWatches();
    }


    // @Watch
    // Watches firing when this object's property changes
    // @JsonIgnore

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches_!.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches_!.removeWatchSubscriber(watchId);
    }
    protected executeOnSubscribingWatches(changedPropName: string): void {
        this.subscribedWatches_!.executeOnSubscribingWatches(changedPropName);
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
        if (ObserveSingleton.instance.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        }
    }
    
    // @Track name : string;
    // @JsonRename("name")
    private  __backing_propA: string;
    
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
    private __backing_propB: int;

    // @JsonIgnore
    private readonly __meta_propB: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get propB(): int {
        this.conditionalAddRef(this.__meta_propB);
        return this.__backing_propB;
    }
    public set propB(newValue: int) {
        if (this.__backing_propB !== newValue) {
            this.__backing_propB = newValue;
            this.__meta_propB.fireChange();
            this.executeOnSubscribingWatches("propB");
        }
    }
}
 
interface EntryComponent_init_update_struct {
    stateA?: ClassA
    stateN?: int32
    stateM?: int32
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

class EntryComputedComponent extends ExtendableComponent implements IVariableOwner {

    private _backing_stateA: IStateDecoratedVariable<ClassA>;
    private _backing_stateN: ILocalDecoratedVariable<int32>;
    private _backing_stateM: ILocalDecoratedVariable<int32>;

    private _computed_squareN : IComputedDecoratedVariable<int32>;
    private _computed_sum : IComputedDecoratedVariable<int32>;

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
    };

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);
        // StateDecoratedVariable
        this._backing_stateA = StateMgmtFactory.makeState<ClassA>(
            this,
            "stateA",
            param.stateA !== undefined
                ? param.stateA!
                : new ClassA("name1", 100),
            undefined
         );

         this._backing_stateN = StateMgmtFactory.makeLocal<int32>(
            this,
            "stateN",
            param.stateN !== undefined
            ? param.stateN!
            :  3
        );

        this._backing_stateM = StateMgmtFactory.makeLocal<int32>(
            this,
            "stateM",
            param.stateM !== undefined
            ? param.stateM!
            :  100
        );

        // We have to define all state variables first
        this._computed_squareN = StateMgmtFactory.makeComputed<int32>(
            () : int32 => {
                stateMgmtConsole.log("_computed_squareN lambda")
                return this.stateN * this.stateN
            },
            "SquareN"
        )

        this._computed_sum = StateMgmtFactory.makeComputed<int32>(
            () : int32 => {
                stateMgmtConsole.log("_computed_sum lambda")
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
        return this._backing_celcius!.get();
    }
    set celcius(newValue: number) {
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

    private _monitorDecorator: IMonitorDecoratedVariable | undefined = undefined;
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
        this._computed_fahrenheit = StateMgmtFactory.makeComputed<number>(
            () : number => {
                stateMgmtConsole.log("computing fahrenheit")
                return this.celcius * 9 / 5 + 32; // C -> F
            },
            "fahrenheit"
        )

        this._computed_kelvin = StateMgmtFactory.makeComputed<number>(
            () : number => {
                stateMgmtConsole.log("computing kelvin")
                return (this.fahrenheit - 32) * 5/9 + 273.15; // F -> K
            },
            "Kelvin"
        )

        /*
        this._monitorDecorator = StateMgmtFactory.makeMonitor(new Array<IMonitorPathInfo>(
            StateMgmtFactory.makeMonitorPath("kelvin", () => {
                const result = this.kelvin;
                //stateMgmtConsole.log("lamda for path kelvin, value: "+result);
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
        */
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
        this.__meta.addRef();
        return this.__backing_propB1;
    }
    public set propB1(newValue: string) {
        if (this.__backing_propB1 !== newValue) {
            this.__backing_propB1 = newValue;
            this.__meta.fireChange();
        }
    }
    private __backing_propB2: boolean = false;
    public get propB2(): boolean {
        this.__meta.addRef();
        return this.__backing_propB2;
    }
    public set propB2(newValue: boolean) {
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
        this.__computed_homeAddress = StateMgmtFactory.makeComputed<string>(
            () : string => {
                stateMgmtConsole.log("computing fahrenheit")
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
    stateN?: int32
}

class ComputedComponentWithException extends ExtendableComponent {

    private _backing_stateN: ILocalDecoratedVariable<int32>;

    private _computed_sumWithError : IComputedDecoratedVariable<int32>;

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
         this._backing_stateN = StateMgmtFactory.makeLocal<int32>(
            this,
            "stateN",
            param.stateN !== undefined
            ? param.stateN!
            :  3
        );

        this._computed_sumWithError = StateMgmtFactory.makeComputed<int32>(
            () : int32 => {
                stateMgmtConsole.log("_computed_sumWithError lambda")
                this.stateN = this.stateN + 1; // That is not allowed to do
                return this.stateN + this.stateN
            },
            "sumWithError"
        )
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
        return this._backing_person_interface!.get();
    }
    set PersonInterface(newValue: InterfacePerson) {
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

        this.__computed_fullName = StateMgmtFactory.makeComputed<string>(
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
        //return UIUtilsImpl.makeObservedDate(this.__computed_tomorrow.get())!
        return this.__computed_tomorrow.get()!
    }

    constructor(parent : ExtendableComponent | null, param : ComputedComponentWithDate_init_update_struct) {
        super(parent);
        this.current = new Date()
        this.__computed_tomorrow = StateMgmtFactory.makeComputed<Date>(
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
    StateMgmtFactory = STATE_MGMT_FACTORY;

    const tests = tsuite("@Computed tests", () => {
    const entryComponent = new EntryComputedComponent(null, 
        {stateN: 2, stateM: 100} as EntryComponent_init_update_struct);

    tcase("Test 1: @Computed square 25", () => {
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty()
        test(`entryComponent.squareN = ${entryComponent.squareN} === 25`, entryComponent.squareN === 25);
    })

    tcase("Test 2: @Computed square 36, after update", () => {
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty()
        entryComponent.stateN = 6
        ObserveSingleton.instance.updateDirty()
        test(`entryComponent.squareN = ${entryComponent.squareN} === 36`, entryComponent.squareN === 36);
    })

    tcase("Test 3: @Computed sumMN ", () => {
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty()
        test(`entryComponent.squareN = ${entryComponent.sumNM} === 105`, entryComponent.sumNM === 105);
    })

    tcase("Test 4: @Computed 2nd sumMN ", () => {
        entryComponent.stateN = 5
        ObserveSingleton.instance.updateDirty()

        entryComponent.stateM = 200
        ObserveSingleton.instance.updateDirty()
        test(`entryComponent.squareN = ${entryComponent.sumNM} === 205`, entryComponent.sumNM === 205);
    })

    tcase("Test 5: @Computed chained ", () => {
        const chainedComponent = new ChainedComputedComponent(null, {celcius: 10});
        ObserveSingleton.instance.updateDirty()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 50`, eq(chainedComponent.fahrenheit, 50));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 283.15`, eq(chainedComponent.kelvin, 283.15));

        chainedComponent.celcius = 20
        ObserveSingleton.instance.updateDirty()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 68`, eq(chainedComponent.fahrenheit, 68));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
    })

    tcase("Test 5: @Computed chained with Kelvin Monitor", () => {
        const chainedComponent = new ChainedComputedComponent(null, {celcius: 10});
        ObserveSingleton.instance.updateDirty()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 50`, eq(chainedComponent.fahrenheit, 50));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 283.15`, eq(chainedComponent.kelvin, 283.15));

        let monitorFunction = (m: IMonitor) => {
            stateMgmtConsole.log(`KELVIN monitor called ${chainedComponent.kelvin} <<<<<<<<<<<<<<<<`)
        }

        chainedComponent._monitorFunction = monitorFunction
        chainedComponent.celcius = 20
        ObserveSingleton.instance.updateDirty()
        test(`chainedComponent.fahrenheit = ${chainedComponent.fahrenheit} === 68`, eq(chainedComponent.fahrenheit, 68));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
        test(`chainedComponent.kelvin = ${chainedComponent.kelvin} === 293.15`, eq(chainedComponent.kelvin, 293.15));
        // Test will be reenable after monitors are fixed
        //test(`monitor count = ${chainedComponent.monitorFunctionRunCount} === 1`, eq(chainedComponent.monitorFunctionRunCount, 1));
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
        ObserveSingleton.instance.updateDirty()
        test(`ObjLiteral.fullName = ${ObjLiteral.fullName} === John-Ripper`, eq(ObjLiteral.fullName, "John-Ripper"));
    })
    
    tcase("Test 9: @Computed using wrapped Date", () => {
        let d = new Date();
        let comp = new ComputedComponentWithDate(null, {})
        comp.current = d;
        d.setDate(d.getDate() + 1)
        // No test for modification of WrappedDate
        test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(comp.tomorrow.getDate(), d.getDate()));
        //test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(Type.of(comp.tomorrow).getName(), "observeWrappedDate.WrappedDate"));
        //test(`Component.tomorrow = ${comp.tomorrow} === ??`, eq(comp.tomorrow instanceof WrappedDate, true));
    })

    });

    tests();
    return true;
}
