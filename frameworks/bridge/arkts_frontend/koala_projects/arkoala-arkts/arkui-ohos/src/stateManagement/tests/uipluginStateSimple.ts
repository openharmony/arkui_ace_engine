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
import { IStateDecoratedVariable } from '../decorator'
import { WatchFuncType } from '../decorator'
import { tsuite, tcase, test, eq } from './lib/testFramework'
import { ObserveSingleton } from '../base/observeSingleton';
import { STATE_MGMT_FACTORY } from '../decorator'
let StateMgmtFactory = STATE_MGMT_FACTORY;
let stateMgmtConsole=console;

interface EntryComponent_init_update_struct {
    stateA?: number
}

class EntryComponent extends ExtendableComponent {

    private _backing_stateA: IStateDecoratedVariable<number>;

    get stateA(): number {
        return this._backing_stateA!.get();
    }
    set stateA(newValue: number) {
        this._backing_stateA!.set(newValue);
    }

    public watchFuncRunCtr : number = 0;

    onStateAChanged(propertyName : string) : void {
        this.watchFuncRunCtr++;
    };

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);
        const watchFunc : WatchFuncType =  (propName: string) => { this.onStateAChanged(propName) };
        this._backing_stateA = StateMgmtFactory.makeState<number>(
            this,
            "stateA",
            param.stateA !== undefined
            ? param.stateA!
            : 100,
            watchFunc
        );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }
 
    resetName() {
      this.stateA = 100;
    }

    assignA200() {
        this.stateA = 200;
    }

    build() {
    }
}

export function run_stateNumber() : Boolean {
  const tests = tsuite("@State tests", () => {

    const compA = new EntryComponent(null, {});
    ObserveSingleton.instance.renderingComponent = ObserveSingleton.RenderingComponentV1;

    tcase("Test 1: @State init value ", () => {
        compA.build();
        test(`compA.stateA = ${compA.stateA} === 100`, eq(compA.stateA, 100));

    })
    tcase("Test 2: @State update value ", () => {
        compA.assignA200()
        test(`compA.stateA = ${compA.stateA} === 200`, eq(compA.stateA, 200));

    })
  });

  tests();
  return true;
}
