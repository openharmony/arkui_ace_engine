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
import { IProviderDecoratedVariable, IConsumerDecoratedVariable } from 'stateManagement/interface/iDecorators'
import { ClassA } from 'stateManagement/utest/uiPlugin/uipluginState.ets'
// unit testing
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'

let consumeComp: ConsumerComp | null = null ;

const NumberTypeValue = Type.of(1 as Number);
const BooleanTypeValue = Type.of(true as Boolean);
const StringTypeValue = Type.of("hello" as String);

// UI plugin generate
interface ProviderComp_init_update_struct {
    // @Provide optional to init from parent, not allowed to update
    provideA?: number,
    provideB?: string
}

class ProviderComp extends ExtendableComponent {
    // @Provide @Watch('onProvideAChanged') provideA: number = 8;
    private _backing_provideA: IProviderDecoratedVariable<number>;
    private _backing_provideB: IProviderDecoratedVariable<string>;

    get provideA(): number {
        return this._backing_provideA.get();
    }
    set provideA(newValue: number) {
        this._backing_provideA.set(newValue);
    }

     get provideB(): string {
        return this._backing_provideB.get();
    }
    set provideB(newValue: string) {
        this._backing_provideB.set(newValue);
    }

    public watchFuncRunCtr : number = 0;

    onProvideAChanged(propertyName: string): void {
        stateMgmtConsole.log(`App-Watch: @Provide provideA @Watch exec: '${propertyName}' newValue '${this.provideA}'`)
        this.watchFuncRunCtr++;
    };

    constructor(parent: ExtendableComponent | null, param: ProviderComp_init_update_struct) {
        super(parent);

        this._backing_provideA = StateMgmtFactory.makeProvider<number>(
            this,
            "provideA",
            "provideA", // alias
            (param.provideA !== undefined)
                ? param!.provideA as number
                : 8,
            NumberTypeValue
            );
            
        this._backing_provideB = StateMgmtFactory.makeProvider<string>(
            this,
            "provideB",
            "provideB", // alias
            (param.provideB !== undefined)
                ? param!.provideB as string
                : 'temp',
            StringTypeValue
            );

    }

    update_struct(param: ProviderComp_init_update_struct) {
        // @Provide nothing,
    }

    // build is fake, just for testing
    build() {
        consumeComp = new ConsumerComp(this)
    }
}


// @Component struct ConsumeComp
class ConsumerComp extends ExtendableComponent {
    // @Consume @Watch('onConsumeAChanged') provideA : number;
    private _backing_provideA: IConsumerDecoratedVariable<number>;

    // Enabling the following property will report a type mismatch error.
    // Keeping this comment for reference in uiplugin.
    // private _backing_provideB: IConsumeDecoratedVariable<ClassA>;  // Type mismatch from @Provide provideB

    get provideA(): number {
        return this._backing_provideA.get();
    }

    set provideA(newValue: number) {
        this._backing_provideA.set(newValue);
    }

    constructor(parent: ExtendableComponent | null = null) {

        super(parent);

        this._backing_provideA = StateMgmtFactory.makeConsumer<number>(
            this,
            "provideA",
            "provideA", // alias
            10,
            NumberTypeValue
            );
    }
  
}

export function run_consumer() : Boolean {

    const tests = tsuite("@Consumer tests", () => {
        stateMgmtConsole.log(`run @Consumer =======================`);

        const parent = new ProviderComp(null, {});
        tcase("Test 1: ProviderComp init, default provideA == 8 for both parent and child", () => {
            parent.build();
            stateMgmtConsole.log(`Appe: constructs done : ${consumeComp!.provideA}`);

            test(`consumeComp!.provideA: ${consumeComp!.provideA} === 8`, eq(consumeComp!.provideA, 8));
        });

        tcase("Test 2: Assign 9 to parent.provideA, expect update + Watch on parent", () => {
            stateMgmtConsole.log(`App: assign 9 to parent.provideA, fireChange on provideA and on provideA expected, exec @Watch on both consume and provideA expected, below: ==========`);
            parent!.provideA = 9;

            test(`consumeComp!.provideA: ${consumeComp!.provideA} === 9`, eq(consumeComp!.provideA, 9));
        });

        tcase("Test 3: Assign 19 to consumeComp.provideA, expect update + Watch on child", () => {
            stateMgmtConsole.log(`App: assign 19 to consumeComp.provideA, fireChange on provideA and on provideA expected, exec @Watch on both consume and provideA expected, below: ==========`);
            consumeComp!.provideA = 19;

            test(`consumeComp!.provideA: ${consumeComp!.provideA} === 19`, eq(consumeComp!.provideA, 19));
        });

        tcase("Test 4: Assign 29 to parent.provideA, expect update + Watch on parent", () => {
            stateMgmtConsole.log(`App: assign 29 to parent provideA, fireChange on provideA and on provideA expected, exec @Watch on both consume and provideA expected, below: ==========`);
            parent!.provideA = 29;

            test(`consumeComp!.provideA: ${consumeComp!.provideA} === 29`, eq(consumeComp!.provideA, 29));

        });


    });
    tests();
    return true;
}

    // pls add assertions for provider
    // no test that addRef / Firechnage of the @Provider and @Consumer are working. 
    // add a Monitor on @Provider and on @Consumer variable 
