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

import { AppStorageV2 } from '../storage/appStorageV2'
import { tsuite, tcase, test, eq, not_eq } from './lib/testFramework'
import { IObservedObject, RenderIdType } from '../decorator'
import { IWatchSubscriberRegister, WatchIdType, WatchFuncType } from '../decorator'
import { ISubscribedWatches } from '../decorator';
import { IMutableStateMeta } from '../decorator'

import { STATE_MGMT_FACTORY } from '../decorator'

let StateMgmtFactory = STATE_MGMT_FACTORY;

let stateMgmtConsole=console;

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
        //if (Observe.shouldAddRef(this.____V1RenderId)) {
            meta.addRef();
        //}
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


// non-observed, no change
class ClassC {
    propC: number = 888;
}


class ClassB {
    propB: number = 500;
}

class ClassIB implements InfB {
    propB: number = 500;
}

interface InfB {
    propB: number;
}


export function run_app_storage_v2(): Boolean {
    const ClassATypeValue = Type.of(new ClassA());
    const ClassBTypeValue = Type.of(new ClassB());
    const ClassIBTypeValue = Type.of(new ClassIB());
    const InfBType = Type.of({ propB: 8 } as InfB)

    const ttest = tsuite("AppStorageV2 API - FULL") {
        tcase("connect, delete different ttypes") {
            let valA1 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca", () => { return new ClassA; })

            let valA2 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca", () => { return new ClassA; })

            let valA3 = AppStorageV2.connect<ClassA>(
                ClassATypeValue, "ca3", () => { return new ClassA; })
    
            test("ClassA type: has check", eq(valA1, valA2));
            test("ClassA propA: has check", eq(valA1?.propA, valA2?.propA));
            test("ClassA type: not eq", not_eq(valA1, valA3));

            AppStorageV2.remove("ca");

            let detected = false;
            try {
                let valAD = AppStorageV2.connect<ClassA>(ClassATypeValue, "ca")
            } catch (e) {
                detected = true;
            } finally {
                test(`Connect to missing key - Exception detected`, detected);
            }

            // Access with the wrong type
            detected = false;
            try {
                let valAx = AppStorageV2.connect<ClassB>(ClassBTypeValue, "ca3")
            } catch (e) {
                detected = true;
            } finally {
                test(`Access with wrong type - Exception detected`, detected);
            }

            let valB1 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb", () => { return new ClassB; })
            let valB2 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb", () => { return new ClassB; })
            let valB3 = AppStorageV2.connect<ClassB>(
                ClassBTypeValue, "keyb3", () => { return new ClassB; })

            test("ClassA type: has check", eq(valB1, valB2));
            test("ClassA propA: has check", eq(valB1?.propB, valB2?.propB));
            test("ClassA type: not eq", not_eq(valB1, valB3));

            // Check that we can get Class that implements interface
            // as an interface, not as a class
            let valCIB1 = AppStorageV2.connect<ClassIB>(
                ClassIBTypeValue, "keycib", () => { return new ClassIB; })

            // Access via interface
            // test below **fails**
            // Even tough ClassIB implements interface InfB
            // It looks that we have some dynamic type name generated
            // uipluginAppStorageV2.gensym%%_62
            // So InfBType in reality is type of interface instance
            detected = false;
            try {
                let valIB1 = AppStorageV2.connect<InfB>(InfBType, "keycib")
            } catch (e) {
                detected = true;
            } finally {
                test(`Access Access via interface - Exception detected`, detected);
            }
        }
    }

    ttest();
    return true;
}
