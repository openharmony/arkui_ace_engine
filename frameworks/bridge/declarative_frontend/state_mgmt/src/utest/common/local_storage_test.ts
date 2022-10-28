/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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


const testLocalStorage = tsuite("LocalStorage Tests", () => {
  
    class TestSubscriber<C> implements ISinglePropertyChangeSubscriber<C>  {

    private id_: number = SubscriberManager.MakeId();
    private label_: string;

    constructor(label: string) {
      SubscriberManager.Add(this);
      this.label_ = label;
    }

      // globally unique id
      id__(): number {
        return this.id_;
      }

      // inform the subscribed property
      // that the subscriber is about to be deleted
      // hence , unsubscribe
      aboutToBeDeleted(): void {
        SubscriberManager.Delete(this.id__());
      }

      // implements IMultiPropertiesChangePublisher
      hasChanged(newValue: C): void {
        console.log(`TestSubscriber '${this.label_}' property changed value (shown stringified): '${ JSON.stringify(newValue) }' `);
      }
    }

  localStorageInstance = new LocalStorage({ say: "Hello", name: "Gudio" });

  tcase("size", () => {
    test("LocalStorage has initial two ObservedProperties", NativeLocalStorage.GetShared().size() == 2);
  });

  tcase("LocalStorage has been init with value", () => {
    test("added 'say'is in LocalStorage", NativeLocalStorage.GetShared().has("say"));
    test("added 'name'is in LocalStorage", NativeLocalStorage.GetShared().has("name"));

    test("added 'say' correct value", NativeLocalStorage.GetShared().get<string>("say") == "Hello");
    test("added 'name' wrong value", NativeLocalStorage.GetShared().get<string>("name") == "Gudio");
  });

  tcase("LocalStorage remembers self set boolean value", () => {
    NativeLocalStorage.GetShared().setOrCreate<boolean>("aBool", true);
    test("added 'aBool' correct boolean value", NativeLocalStorage.GetShared().get<boolean>("aBool"));
  });

  tcase("LocalStorage remembers self set number value", () => {
    NativeLocalStorage.GetShared().setOrCreate<number>("favorite", 47);

    test("added 'favorite', has correct number value", NativeLocalStorage.GetShared().get<number>("favorite") == 47);
    test("added 'favorite' converted to string is '47'", NativeLocalStorage.GetShared().get<string>("favorite") == "47");
  });

  let boolChangeListener = new TestSubscriber<boolean>("boolChangeListener");
  NativeLocalStorage.GetShared().subscribeToChangesOf("aBool", boolChangeListener);
  let childboolChangeListenerSpy = spyOn(boolChangeListener, "hasChanged");
  
  tcase("Notifies listener on property value change", () => {
  NativeLocalStorage.GetShared().set<boolean>("aBool", false);
    test("boolean value readback correct", NativeLocalStorage.GetShared().get<boolean>("aBool") == false);
    test("subscribing listener's 'hasChanged' called, param is newValue", childboolChangeListenerSpy.called && childboolChangeListenerSpy.args[0] == false);
  });


  class TestAClass {
    public a: number;
    public b: number;
  }

  let objAClass1: TestAClass = { a: 1, b: 2 };
  let objAClass2: TestAClass = { a: 101, b: 201 };

  tcase("ObservedObject create, get, set", () => {
    NativeLocalStorage.GetShared().setOrCreate<TestAClass>("objAClass", objAClass1);
    test("ObservedObject create, value read back prop 'a'", (NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a == 1 && NativeLocalStorage.GetShared().get<TestAClass>("objAClass").b == 2));

    NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a = 47;
    test("ObservedObject property value change, value read back", NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a == 47);

    NativeLocalStorage.GetShared().set<TestAClass>("objAClass", objAClass2);
    test("ObservedProperty of type ObservedObject set new ObservedObject, value read back",
      NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a == 101 && NativeLocalStorage.GetShared().get<TestAClass>("objAClass").b == 201);

    NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a = 102;
    test("Followed by prop value change, value read back",
      NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a == 102 && NativeLocalStorage.GetShared().get<TestAClass>("objAClass").b == 201);
  })

  let objAChangeListener = new TestSubscriber<TestAClass>("objAChangeListener");
  NativeLocalStorage.GetShared().subscribeToChangesOf("objAClass", objAChangeListener);
  let objAChangeListenerSpy1 = spyOn(objAChangeListener, "hasChanged");
  let objAClass3: TestAClass = { a: 101, b: 102 };


  tcase("Notifies listener on 'objAClass' property value change", () => {
    NativeLocalStorage.GetShared().set<TestAClass>("objAClass", objAClass3);
    test("ObservedObject property value change, value read back", NativeLocalStorage.GetShared().get<TestAClass>("objAClass").a == 101);
    test("subscribing listener's 'hasChanged' called with correct param", objAChangeListenerSpy1.called && objAChangeListenerSpy1.args[0].b == 102);
  });

  let objAChangeListenerSpy2 = spyOn(objAChangeListener, "hasChanged");

  tcase("Notifies listener on 'objAClass' property's property value change", () => {
    NativeLocalStorage.GetShared().get<TestAClass>("objAClass").b = 103;
    test("ObservedObject property value change, value read back", NativeLocalStorage.GetShared().get<TestAClass>("objAClass").b == 103);
    test("subscribing listener's 'hasChanged' called with correct param", objAChangeListenerSpy2.called && objAChangeListenerSpy2.args[0].b == 103);
  });

  tcase("cleanup ok", () => {
    NativeLocalStorage.GetShared().unsubscribeFromChangesOf("aBool", boolChangeListener.id__());
    boolChangeListener.aboutToBeDeleted();

    NativeLocalStorage.GetShared().unsubscribeFromChangesOf("objAClass", objAChangeListener.id__());
    objAChangeListener.aboutToBeDeleted();

    const deleteOk = NativeLocalStorage.GetShared().delete("name") && NativeLocalStorage.GetShared().delete("say") && NativeLocalStorage.GetShared().delete("aBool") && NativeLocalStorage.GetShared().delete("favorite") && NativeLocalStorage.GetShared().delete("objAClass");
    test(`Deletion of props form AppStrorage without isuses`, deleteOk)

    // test that manual cleanup has been complete, before calling NativeLocalStorage.GetShared().boutToBeDeleted();
    test(`AppStrorage has ${NativeLocalStorage.GetShared().size()} ObservedProperties: >${Array.from(NativeLocalStorage.GetShared().keys())}<, should be none.`, NativeLocalStorage.GetShared().size() == 0);

    NativeLocalStorage.GetShared().aboutToBeDeleted();

    test(`SubscriberManager num of subscribers is ${SubscriberManager.NumberOfSubscribers()} should be 0 .`, 
      SubscriberManager.NumberOfSubscribers() == 0);
  });

});
