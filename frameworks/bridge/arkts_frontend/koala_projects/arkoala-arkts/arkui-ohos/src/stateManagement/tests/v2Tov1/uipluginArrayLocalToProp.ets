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
// Interoperable Tests using WrappedArray of objects from V2 @Local to V1 @Prop

import { int32 } from 'stateManagement/mock/env_mock'
import { WrappedArray } from 'stateManagement/base/observeWrappedArray'
import { ExtendableComponent } from 'stateManagement/base/extendableComponent'
import { IObservedObject, RenderIdType } from 'stateManagement/interface/iObservedObject'
import { Observe } from 'stateManagement/interface/iObserve'
import { IWatchSubscriberRegister, ISubscribedWatches, WatchIdType } from 'stateManagement/interface/iWatch'
import { IMutableStateMeta } from 'stateManagement/interface/iMutableStateMeta'
import { stateMgmtConsole } from 'stateManagement/tools/stateMgmtConsoleTrace';
import { StateMgmtFactory } from 'stateManagement/interface/iStateMgmtFactory.ets'
import { ILocalDecoratedVariable, IPropRefDecoratedVariable } from 'stateManagement/interface/iDecorators.ets'

// unit testing
import { TestMSM } from 'stateManagement/utest/lib/testAddRefFireChange'
import { tsuite, tcase, test, eq } from 'stateManagement/utest/lib/testFramework'
/*
  @Observed
  class FoodData {
    @Track id: string;
    @Track name: string;
    @Track calories: number;

    constructor(name: string, calories: number) {
        this.id = `${NextId++}`;
        this.name = name;
        this.calories = calories;
    }
  }

*/

// global unique ID
let NextId = 1;

// random string generation
function getRandomName(): string {
  const names = ["Strawberry", "BlueBerry", "Banana", "Pomegranate", "Custard", "Brownie", "Guava", "Grape", "Cucumber", "Calsa", "Haramba"];
  return names[2];
}

export class FoodData implements IObservedObject, IWatchSubscriberRegister {
 
    constructor(name: string, calories: number) {
        // init in constructor
        // need to change to _backing, 
        // otherwise compiler warns about uninitialized 
        // __backing
        this.__backing_id = `${NextId++}`;
        this.__backing_name = name;
        this.__backing_calories = calories;
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
    private __backing_name: string;
    
    // @JsonIgnore
    private readonly __meta_name: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get name(): string {
        stateMgmtConsole.log(`ClassD: get @Track name`);
        this.conditionalAddRef(this.__meta_name);
        return this.__backing_name
    }
    public set name(newValue: string) {
        if (this.__backing_name !== newValue) {
            stateMgmtConsole.log(`ClassD: set @Track name`);
            this.__backing_name = newValue;
            this.__meta_name.fireChange();
            this.executeOnSubscribingWatches("name");
        }
    }    

    // @Track propD2 : number;
    // @JsonRename("propD2")
    private __backing_calories: number;

    // @JsonIgnore
    private readonly __meta_calories: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get calories(): number {
        stateMgmtConsole.log(`ClassD: get @Track calories`);
        this.conditionalAddRef(this.__meta_calories);
        return this.__backing_calories
    }
    public set calories(newValue: number) {
        stateMgmtConsole.log(`ClassD: set @Track calories`);
        if (this.__backing_calories !== newValue) {
            this.__backing_calories = newValue;
            this.__meta_calories.fireChange();
            this.executeOnSubscribingWatches("calories");
        }
    }
    
    private __backing_id: string;

    // @JsonIgnore
    private readonly __meta_id: IMutableStateMeta
        = StateMgmtFactory.makeMutableStateMeta();

    public get id(): string {
        stateMgmtConsole.log(`ClassD: get @Track id`);
        this.conditionalAddRef(this.__meta_id);
        return this.__backing_id
    }
    public set id(newValue: string) {
        stateMgmtConsole.log(`ClassD: set @Track id`);
        if (this.__backing_id !== newValue) {
            this.__backing_id = newValue;
            this.__meta_id.fireChange();
            this.executeOnSubscribingWatches("id");
        }
    }

}

/*
    @Observed
    class FoodDataDB {
        // public FoodData[] will be updated from outside
        @Track foodItems : FoodData[];

        constructor() {
            // init with a default value
            this.foodItems = [
            new FoodData("Carrot", 10),
            new FoodData("Apple", 50),
            new FoodData("Biriyani", 100),
            ];
        }
    }
*/

class FoodDataDB implements IObservedObject, IWatchSubscriberRegister {
  
 constructor(a: WrappedArray<FoodData>) {
    this._backing_foodItems = a;
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
  private _backing_foodItems: WrappedArray<FoodData>;
  
  // @JsonIgnore
  private readonly __meta_foodItems: IMutableStateMeta
      = StateMgmtFactory.makeMutableStateMeta();

  public get foodItems(): WrappedArray<FoodData> {
      stateMgmtConsole.log(`ClassD: get @Track foodItems`);
      this.conditionalAddRef(this.__meta_foodItems);
      return this._backing_foodItems
  }
  public set foodItems(newValue: WrappedArray<FoodData>) {
      if (this._backing_foodItems !== newValue) {
          stateMgmtConsole.log(`ClassD: set @Track foodItems`);
          this._backing_foodItems = newValue;
          this.__meta_foodItems.fireChange();
          this.executeOnSubscribingWatches("foodItems");
      }
  }    
}

/*
@Entry
@Component
struct EntryComponent {
  @State eatenFoodItems: FoodData[] = (new FoodDataDB().foodItems);

  build() {
    Column() {
      CompV1({eatenFoodItems: UIUtils.enableV2Compatibility(this.eatenFoodItems)})

      // Button to map each food item's calories to double
      Button(`Map * 2`).onClick(() => {
        console.info(`Map arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems = this.eatenFoodItems.map(item => {
          item.calories = item.calories * 2;  // Double the calories for each food item
          return item;
        });
        console.info(`Map arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to reset the food items array to its default state
      Button(`Reset`).onClick(() => {
        console.info(`Reset arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems = new FoodDataDB().foodItems;
        console.info(`Reset arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)
    }
  }
}
*/
let childComp: CompV1 | null = null ;


interface EntryComponent_init_update_struct {
    eatenFoodItems?: WrappedArray<FoodData>
}

class EntryComponent extends ExtendableComponent {

    // @State eatenFoodItems: FoodData[] = (new FoodDataDB().foodItems);
    private _backing_eatenFoodItems: ILocalDecoratedVariable<WrappedArray<FoodData>>;

    get eatenFoodItems(): WrappedArray<FoodData> {
        return this._backing_eatenFoodItems!.get();
    }
    set eatenFoodItems(newValue: WrappedArray<FoodData>) {
        this._backing_eatenFoodItems!.set(newValue);
    }

    constructor(parent : ExtendableComponent | null, param : EntryComponent_init_update_struct) {
        super(parent);

        // Create an empty WrappedArray first
      const foodArray: Array<FoodData> = new Array<FoodData>();
      foodArray.push(new FoodData("name1", 100));
      foodArray.push(new FoodData("name2", 200));
      foodArray.push(new FoodData("name3", 300));
      const wrappedFoodArray = new WrappedArray<FoodData>(foodArray);

      this._backing_eatenFoodItems = StateMgmtFactory.makeLocal<WrappedArray<FoodData>>(
        this,
        "eatenFoodItems",
        param.eatenFoodItems !== undefined
        ? param.eatenFoodItems!
        :  new FoodDataDB(wrappedFoodArray).foodItems
      );
    }

    __updateStruct(param: EntryComponent_init_update_struct) : void {
        // @State nothing, can not update from parent
    }

    doubleCalories() {
      //console.info(`Before doubling: ` +  JSON.stringify(Array.from(this.eatenFoodItems)));

      for (let item of this.eatenFoodItems) {
        item.calories *= 2;
      }

      //console.info(`After doubling: ` + JSON.stringify(Array.from(this.eatenFoodItems)));
    }

    resetEatenFoodItems() {
      const foodArray: Array<FoodData> = new Array<FoodData>();

      foodArray.push(new FoodData("test1", 10));
      foodArray.push(new FoodData("test2", 20));

      this.eatenFoodItems = new WrappedArray<FoodData>(foodArray);
    }

    pushNewFoodItem() {
      const newFood = new FoodData(getRandomName(), 50);
      this.eatenFoodItems.push(newFood);
    }


    funcCopyWithin() {
      // Copy items from index 1 to index 0
      this.eatenFoodItems = this.eatenFoodItems.copyWithin(0, 1, 2);
    }

    build() {
      childComp = new CompV1(this, { eatenFoodItems: this.eatenFoodItems })
    }
}

/*

@ComponentV2
struct CompV1 {
  @Require @Param eatenFoodItems: FoodData[];
  private nextNum: number = 100;

  build() {
    Column({ space: 5 }) {
      ForEach(this.eatenFoodItems, (item:FoodData) => {
        Text(`${item.name} - Calories: ${item.calories}`)
      },
        (item:FoodData, index) => `${index}-${item.name}`
      )

      // Button to sort the food items by calories
      Button(`Sort by Calories`).onClick(() => {
        console.info(`Sort arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems.sort((a, b) => a.calories - b.calories);
        console.info(`Sort arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to push a new food item
      Button(`Push New Food Item`).onClick(() => {
        console.info(`Push arr :` + JSON.stringify(this.eatenFoodItems));
        const newFood = new FoodData(getRandomName(), Math.floor(Math.random() * 300) + 50);
        this.eatenFoodItems.push(newFood);
        console.info(`Push arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to pop the last food item
      Button(`Pop Last Food Item`).onClick(() => {
        console.info(`Pop arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems.pop();
        console.info(`Pop arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to splice a food item (remove and/or add a new one)
      Button(`Splice(1, 1, NewFood)`).onClick(() => {
        console.info(`Splice arr :` + JSON.stringify(this.eatenFoodItems));
        const newFood = new FoodData("NewFood", 1111);
        this.eatenFoodItems.splice(1, 1, newFood);
        console.info(`Splice arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to fill the array with a specific food item
      Button(`Fill Food Items`).onClick(() => {
        console.info(`Fill arr :` + JSON.stringify(this.eatenFoodItems));
        const newFood = new FoodData("FilledFood", 50);
        this.eatenFoodItems.fill(newFood, 0, 2);  // Fill the first two items with "FilledFood"
        console.info(`Fill arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to reverse the array
      Button(`Reverse Food Items`).onClick(() => {
        console.info(`Reverse arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems.reverse();
        console.info(`Reverse arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to splice and sort
      Button(`Splice(1,0,200,300).Sort()`).onClick(() => {
        console.info(`Splice and Sort arr :` + JSON.stringify(this.eatenFoodItems));
        const newFood1 = new FoodData("200Calories", 200);
        const newFood2 = new FoodData("300Calories", 300);
        this.eatenFoodItems.splice(1, 0, newFood1, newFood2).sort((a, b) => a.calories - b.calories);
        console.info(`Splice and Sort arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button to chain methods like sort, filter, map, join
      Button(`Sort().Filter(..).Map(..).Join()`).onClick(() => {
        console.info(`Chain arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems
          .sort((a, b) => a.calories - b.calories)
          .filter(i => i.calories >= 50)
          .map(item => `${item.name}_m`)
          .join();
        console.info(`Chain arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

      // Button for copyWithin functionality
      Button('CopyWithin').onClick(() => {
        console.info(`CopyWithin arr :` + JSON.stringify(this.eatenFoodItems));
        this.eatenFoodItems.copyWithin(0, 1, 2);  // Copy items from index 1 to index 0
        console.info(`CopyWithin arr end:` + JSON.stringify(this.eatenFoodItems));
      })
        .width(300).height(50)

    }
  }
}
*/

interface CompV1_init_update_struct {
    // @Parem init and update form parent
    // UIPlugin needs to consider the @Required deco.
    eatenFoodItems:  WrappedArray<FoodData>
}

// @Component struct CompV1
class CompV1 extends ExtendableComponent{
    // @Required @Param eatenFoodItems : number;  // no local value
    private _backing_eatenFoodItems: IPropRefDecoratedVariable<WrappedArray<FoodData>>;
    get eatenFoodItems(): WrappedArray<FoodData> {
        return this._backing_eatenFoodItems.get();
    }

    constructor(parent : ExtendableComponent | null, param: CompV1_init_update_struct) {
        super(parent);
        // @Param can init from parent, can have local value;
        this._backing_eatenFoodItems = StateMgmtFactory.makePropRef<WrappedArray<FoodData>>(
            this,
            "eatenFoodItems",
            param.eatenFoodItems)

    }

    sortOptions() {
      this.eatenFoodItems.sort((a, b) => a.calories - b.calories);
    }

    popLastFoodItem() {
      this.eatenFoodItems.pop();
    }

    reverseFoodItems() {
      this.eatenFoodItems.reverse();
    }

    spliceFoodItem() {
      const newFood = new FoodData("NewFood", 111);
      this.eatenFoodItems.splice(1, 1, newFood);
    }

    update_struct(param: CompV1_init_update_struct) {
      stateMgmtConsole.log(`uiplugin-eatenFoodItems CompV1 constructor update_struct`)
      this._backing_eatenFoodItems.update(param.eatenFoodItems);
    }
}


export function run_wrappedarray_v2local_to_v1prop() : Boolean {

  const tests = tsuite("Interoperability v2Tov1 with WrappedArray tests", () => {
    stateMgmtConsole.log(`run Interoperability v2Tov1 with WrappedArray=======================`);

    const parent = new EntryComponent(null, {});

    tcase("Test 1: v2Tov1_array mutate objects init value ", () => {
      parent.build();
      stateMgmtConsole.log(`App: constructs done`);

      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 100`,  eq(parent.eatenFoodItems[0].calories, 100));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 200`,  eq(parent.eatenFoodItems[1].calories, 200));
      test(`parent.eatenFoodItems[2].calories = ${parent.eatenFoodItems[2].calories} === 300`,  eq(parent.eatenFoodItems[2].calories, 300));

      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 100`, eq(childComp!.eatenFoodItems[0].calories, 100));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 200`,  eq(childComp!.eatenFoodItems[1].calories, 200));
      test(`childComp!.eatenFoodItems[2].calories = ${childComp!.eatenFoodItems[2].calories} === 300`,  eq(childComp!.eatenFoodItems[2].calories, 300));

    });


    tcase("Test 2: v2Tov1_array mutate objects double Calories ", () => {
      parent.doubleCalories();

      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 200`, eq(parent.eatenFoodItems[0].calories, 200));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 400`, eq(parent.eatenFoodItems[1].calories, 400));
      test(`parent.eatenFoodItems[2].calories = ${parent.eatenFoodItems[2].calories} === 600`, eq(parent.eatenFoodItems[2].calories, 600));

      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 200`, eq(childComp!.eatenFoodItems[0].calories, 200));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 400`, eq(childComp!.eatenFoodItems[1].calories, 400));
      test(`childComp!.eatenFoodItems[2].calories = ${childComp!.eatenFoodItems[2].calories} === 600`, eq(childComp!.eatenFoodItems[2].calories, 600));

    });


    tcase("Test 3: v2Tov1_array mutate objects resetEatenFoodItems ", () => {
      parent.resetEatenFoodItems();

      const foodArray: Array<FoodData> = new Array<FoodData>();

      foodArray.push(new FoodData("test1", 100));
      foodArray.push(new FoodData("test2", 20));

      parent.eatenFoodItems = new WrappedArray<FoodData>(foodArray)

      childComp!.update_struct({
          eatenFoodItems: new WrappedArray<FoodData>(foodArray)
        });

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test1'`, eq(parent.eatenFoodItems[0].name, 'test1'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 100`, eq(parent.eatenFoodItems[0].calories, 100));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test2' `, eq(parent.eatenFoodItems[1].name, "test2"));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 20`, eq(parent.eatenFoodItems[1].calories, 20));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test1'`, eq(childComp!.eatenFoodItems[0].name, 'test1'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 100`, eq(childComp!.eatenFoodItems[0].calories, 100));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test2'`, eq(childComp!.eatenFoodItems[1].name, 'test2'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 20`, eq(childComp!.eatenFoodItems[1].calories, 20));
    });

    tcase("Test 4: v2Tov1_array mutate objects sortOptions ", () => {

      childComp!.sortOptions()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test2'`, eq(parent.eatenFoodItems[0].name, 'test2'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 20`, eq(parent.eatenFoodItems[0].calories, 20));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test1'`, eq(parent.eatenFoodItems[1].name, 'test1'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 100`, eq(parent.eatenFoodItems[1].calories, 100));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test2'`, eq(childComp!.eatenFoodItems[0].name, 'test2'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 20`, eq(childComp!.eatenFoodItems[0].calories, 20));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test1'`, eq(childComp!.eatenFoodItems[1].name, 'test1'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 100`, eq(childComp!.eatenFoodItems[1].calories, 100));

    });

    tcase("Test 5: v2Tov1_array mutate objects pushNewFoodItem ", () => {

      parent.pushNewFoodItem()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test2'`,  eq(parent.eatenFoodItems[0].name, 'test2'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 20`,  eq(parent.eatenFoodItems[0].calories, 20));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test1'`,  eq(parent.eatenFoodItems[1].name, 'test1'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 100`,  eq(parent.eatenFoodItems[1].calories, 100));
      test(`parent.eatenFoodItems[2].name = ${parent.eatenFoodItems[2].name} === 'Banana'`,  eq(parent.eatenFoodItems[2].name, 'Banana'));
      test(`parent.eatenFoodItems[2].calories = ${parent.eatenFoodItems[2].calories} === 50`,  eq(parent.eatenFoodItems[2].calories, 50));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test2'`, eq(childComp!.eatenFoodItems[0].name, 'test2'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 20`, eq(childComp!.eatenFoodItems[0].calories, 20));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test1'`, eq(childComp!.eatenFoodItems[1].name, 'test1'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 100`, eq(childComp!.eatenFoodItems[1].calories, 100));
      test(`childComp!.eatenFoodItems[2].name = ${childComp!.eatenFoodItems[2].name} === 'Banana'`, eq(childComp!.eatenFoodItems[2].name, 'Banana'));
      test(`childComp!.eatenFoodItems[2].calories = ${childComp!.eatenFoodItems[2].calories} === 50`, eq(childComp!.eatenFoodItems[2].calories, 50));

    });

    tcase("Test 6: v2Tov1_array mutate objects popLastFoodItem ", () => {

      childComp!.popLastFoodItem()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test2'`,  eq(parent.eatenFoodItems[0].name, 'test2'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 20`,  eq(parent.eatenFoodItems[0].calories, 20));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test1'`,  eq(parent.eatenFoodItems[1].name, 'test1'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 100`,  eq(parent.eatenFoodItems[1].calories, 100));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test2'`, eq(childComp!.eatenFoodItems[0].name, 'test2'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 20`, eq(childComp!.eatenFoodItems[0].calories, 20));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test1'`, eq(childComp!.eatenFoodItems[1].name, 'test1'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 100`, eq(childComp!.eatenFoodItems[1].calories, 100));

    });


    tcase("Test 7: v2Tov1_array mutate objects reverseFoodItems ", () => {

      childComp!.reverseFoodItems()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test1'`, eq(parent.eatenFoodItems[0].name, 'test1'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 100`, eq(parent.eatenFoodItems[0].calories, 100));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test2'`, eq(parent.eatenFoodItems[1].name, 'test2'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 20`, eq(parent.eatenFoodItems[1].calories, 20));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test1'`, eq(childComp!.eatenFoodItems[0].name, 'test1'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 100`, eq(childComp!.eatenFoodItems[0].calories, 100));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test2'`, eq(childComp!.eatenFoodItems[1].name, 'test2'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 20`, eq(childComp!.eatenFoodItems[1].calories, 20));

    });

    tcase("Test 8: v2Tov1_array mutate objects funcCopyWithin ", () => {

      parent.funcCopyWithin()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test2'`, eq(parent.eatenFoodItems[0].name, 'test2'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 20`, eq(parent.eatenFoodItems[0].calories, 20));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'test2'`, eq(parent.eatenFoodItems[1].name, 'test2'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 20`, eq(parent.eatenFoodItems[1].calories, 20));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test2'`, eq(childComp!.eatenFoodItems[0].name, 'test2'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 20`, eq(childComp!.eatenFoodItems[0].calories, 20));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'test2'`, eq(childComp!.eatenFoodItems[1].name, 'test2'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 20`, eq(childComp!.eatenFoodItems[1].calories, 20));

    });

    tcase("Test 9: v2Tov1_array mutate objects spliceFoodItem ", () => {

      childComp!.spliceFoodItem()

      test(`parent.eatenFoodItems[0].name = ${parent.eatenFoodItems[0].name} === 'test2'`, eq(parent.eatenFoodItems[0].name, 'test2'));
      test(`parent.eatenFoodItems[0].calories = ${parent.eatenFoodItems[0].calories} === 20`, eq(parent.eatenFoodItems[0].calories, 20));
      test(`parent.eatenFoodItems[1].name = ${parent.eatenFoodItems[1].name} === 'NewFood'`, eq(parent.eatenFoodItems[1].name,'NewFood'));
      test(`parent.eatenFoodItems[1].calories = ${parent.eatenFoodItems[1].calories} === 111`, eq(parent.eatenFoodItems[1].calories, 111));

      test(`childComp!.eatenFoodItems[0].name = ${childComp!.eatenFoodItems[0].name} === 'test2'`, eq(childComp!.eatenFoodItems[0].name, 'test2'));
      test(`childComp!.eatenFoodItems[0].calories = ${childComp!.eatenFoodItems[0].calories} === 20`, eq(childComp!.eatenFoodItems[0].calories, 20));
      test(`childComp!.eatenFoodItems[1].name = ${childComp!.eatenFoodItems[1].name} === 'NewFood'`, eq(childComp!.eatenFoodItems[1].name, 'NewFood'));
      test(`childComp!.eatenFoodItems[1].calories = ${childComp!.eatenFoodItems[1].calories} === 111`, eq(childComp!.eatenFoodItems[1].calories, 111));

    });

  });

  tests();
  return true;

}
