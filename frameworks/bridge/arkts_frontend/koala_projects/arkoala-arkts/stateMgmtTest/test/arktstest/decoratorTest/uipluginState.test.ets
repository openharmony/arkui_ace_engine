/*
* Copyright (C) 2026 Huawei Device Co., Ltd.
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
import { describe, it, expect, TestType, Size, Level, beforeAll, beforeEach, afterEach, afterAll } from "index";

import { STATE_MGMT_FACTORY, LocalStorage, IStateDecoratedVariable, IObservedObject, ISubscribedWatches, WatchIdType, RenderIdType, IMutableStateMeta } from "@ohos.arkui.stateManagement";
import { CustomComponent, CustomDelegate } from "@ohos.arkui.component";
import { memo } from '@koalaui/runtime/annotations';

/*
    classA {
      @Track propA: string;
      @Track propB: number;
      constructor(propA: string, propB: number) {
        this.propA = propA;
        this.propB = propB;
      }
    }

    @Component
    struct Index {
        @State stateA: number = 100;
        @Watch('onStateAChanged') @State stateB: ClassA = new ClassA('name1', 100);
        onStateAChanged(propertyName : string) {
          console.log(`@State stateA @Watch exec: propertyName='${propertyName}', newValue propA: ${this.stateA.propA}`)
        }
        build() {}
    }
*/

class ClassA implements IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: (ISubscribedWatches | undefined) = STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    if (((this.subscribedWatches) !== (undefined))) {
      this.subscribedWatches!.addWatchSubscriber(watchId);
    }
  }

  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    if (((this.subscribedWatches) !== (undefined))) {
      return this.subscribedWatches!.removeWatchSubscriber(watchId);
    }
    return false;
  }

  public executeOnSubscribingWatches(propertyName: string): void {
    if (((this.subscribedWatches) !== (undefined))) {
      this.subscribedWatches!.executeOnSubscribingWatches(propertyName);
    }
  }

  public setV1RenderId(renderId: RenderIdType): void {}

  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }

  @JSONRename({newName:"propA"}) public __backing_propA?: string;
  @JSONStringifyIgnore() @JSONParseIgnore() private __meta_propA: IMutableStateMeta = STATE_MGMT_FACTORY.makeMutableStateMeta(this, "__meta_propA");
  public get propA(): string {
    this.conditionalAddRef(this.__meta_propA);
    return (this.__backing_propA as string);
  }

  public set propA(newValue: string) {
    if (((this.__backing_propA) !== (newValue))) {
      this.__backing_propA = newValue;
      this.__meta_propA.fireChange();
      this.executeOnSubscribingWatches("propA");
    }
  }

  @JSONRename({newName:"propB"}) public __backing_propB?: number;
  @JSONStringifyIgnore() @JSONParseIgnore() private __meta_propB: IMutableStateMeta = STATE_MGMT_FACTORY.makeMutableStateMeta(this, "__meta_propB");
  public get propB(): number {
    this.conditionalAddRef(this.__meta_propB);
    return (this.__backing_propB as number);
  }

  public set propB(newValue: number) {
    if (((this.__backing_propB) !== (newValue))) {
      this.__backing_propB = newValue;
      this.__meta_propB.fireChange();
      this.executeOnSubscribingWatches("propB");
    }
  }

  public constructor(propA: string, propB: number) {
    this.propA = propA;
    this.propB = propB;
  }
}

class Index extends CustomComponent<Index, __Options_Index> {
  public __initializeStruct(initializers: (__Options_Index | undefined), @memo() content: ((()=> void) | undefined)): void {
    this.__backing_stateA = STATE_MGMT_FACTORY.makeState<number>(this, "stateA", initializers?.stateA ?? 100);
    this.__backing_stateB = STATE_MGMT_FACTORY.makeState<ClassA>(this, "stateB", initializers?.stateB ?? (new ClassA("name1", 100)), ((_: string): void => {
      this.onStateBChanged(_);
    }));
  }

  public __updateStruct(initializers: (__Options_Index | undefined)): void {}

  @memo()
  public static _invoke(style: (@memo() ((instance: Index)=> void) | undefined), initializers: ((()=> __Options_Index) | undefined), storage: ((()=> LocalStorage) | undefined), reuseId: (string | undefined), @memo() content: ((()=> void) | undefined)): void {
    CustomComponent._invokeImpl<Index, __Options_Index>(style, ((): Index => {
        return new Index(false, storage?.());
      }), initializers, reuseId, content);
    }

    private __backing_stateA?: IStateDecoratedVariable<number>;
    public get stateA(): number {
      return this.__backing_stateA!.get();
    }

    public set stateA(value: number) {
      this.__backing_stateA!.set(value);
    }

    private __backing_stateB?: IStateDecoratedVariable<ClassA>;
    public get stateB(): ClassA {
      return this.__backing_stateB!.get();
    }

    public set stateB(value: ClassA) {
      this.__backing_stateB!.set(value);
    }
    
    public watchFuncRunCtr : number = 0;

    public onStateBChanged(propertyName: string) {
      this.watchFuncRunCtr++;
      console.log(`@State stateB @Watch exec: propertyName='${propertyName}', newValue propA: ${this.stateB.propA}'`);
    }

    @memo()
    public build() {}

    public constructor(useSharedStorage?: boolean, storage?: LocalStorage) {
      super(useSharedStorage, storage);
    }
}

interface __Options_Index {
    stateA?: number;
    __backing_stateA?: IStateDecoratedVariable<number>;
    options_has_stateA?: boolean;
    stateB?: ClassA;
    __backing_stateB?: IStateDecoratedVariable<ClassA>;
    __options_has_stateB?: boolean;
}

export function UipluginStateTest() {
    let compA: Index = new Index();
    compA.__initializeStruct(undefined, undefined);
    compA.__setDelegate__Internal(new CustomDelegate<Index, __Options_Index>(undefined, compA, undefined));
    describe('uiplugin @State tests', () => {
        beforeAll(() => {
            // 在所有测试之前执行的代码
        });

        beforeEach(()=>{
            // 在每个测试之前执行的代码
        })

        afterEach(() => {
            // 在每个测试之后执行的代码
        });

        afterAll(() => {
            // 在所有测试之后执行的代码
        });

        it('Test 1: @State simple init value', 0, () => {
            expect(compA.stateA).assertEqual(100);
        });

        it('Test 2: @State simple update value', 0, () => {
            compA.stateA = 200;
            expect(compA.stateA).assertEqual(200);
        });

        it('Test 3: @State object init value', 0, () => {
            expect(compA.stateB.propA).assertEqual('name1');
            expect(compA.stateB.propB).assertEqual(100);
        });
    
        it('Test 4: @State increment object value', 0, () => {
            compA.stateB.propB += 1;
            expect(compA.stateB.propA).assertEqual('name1');
            expect(compA.stateB.propB).assertEqual(101);
        });

        it('Test 5: @State reset object property', 0, () => {
            compA.stateB.propA = compA.stateB.propA + '_A';
            expect(compA.stateB.propA).assertEqual('name1_A');
            expect(compA.stateB.propB).assertEqual(101);
        });

        it('Test 6: @State reset object', 0, () => {
            compA.stateB = new ClassA('newObject', 1101);
            expect(compA.stateB.propA).assertEqual('newObject');
            expect(compA.stateB.propB).assertEqual(1101);
        });

        it('Test 7: @State @Watch test', 0, () => {
            compA.watchFuncRunCtr = 0;
            compA.stateB = new ClassA('newObject', 1101);
            expect(compA.watchFuncRunCtr).assertEqual(1);
            compA.watchFuncRunCtr = 0;
            compA.stateB.propB += 1;
            expect(compA.watchFuncRunCtr).assertEqual(1);
        });
    });
}