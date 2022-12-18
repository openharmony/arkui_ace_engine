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

const testAppStorage = tsuite("AppStorage", () => {

  tcase("size", () => {
    AppStorage.CreateSingleton({say: "Hello", name: "Gudio"});
    test("AppStrorage has initial two ObservedProperties", AppStorage.Size() == 2);
  });

  tcase("AppStorage has self set value", () => {
    test("added 'say' is in AppStrorage", AppStorage.Has("say"));
  });

  tcase("AppStorage remembers self set value", () => {
    test("added 'say' wrong value", AppStorage.Get<string>("say") == "Hello");
    test("added 'name' wrong value", AppStorage.Get<string>("name") == "Gudio");
  });

  tcase("AppStorage remembers self set boolean value", () => {
    AppStorage.SetOrCreate<boolean>("true", true);
    test("added 'true' wrong boolean value", AppStorage.Get<boolean>("true"));
  });

  tcase("AppStorage remembers self set number value", () => {
    AppStorage.SetOrCreate<number>("favorite", 47);

    test("added 'favorite', has correct number value", AppStorage.Get<number>("favorite") == 47);
    test("added 'favorite' converted to string is '47'", AppStorage.Get<string>("favorite") == "47");
  });


  var link1: SubscribedAbstractProperty<string> = AppStorage.Link<string>("say");
  var link2: SubscribedAbstractProperty<string> = AppStorage.Link<string>("say");

  tcase("AppStorage and link1 update from link1.set",
    () => {
      link1.set("Anton");
      test("AppStorage: 'say' expected updated value is `Anton`.", AppStorage.Get<string>("say") == "Anton");
      test("SyncedPropertyTwoWay#1: 'say' expected updated value is `Anton`.", link2.get() == "Anton");
    });

  tcase("AppStorage and link2 update from link1.set", () => {
    link1.set("Hanna");
    test("AppStorage: 'say' expected updated value is `Hanna`.", AppStorage.Get<string>("say") == "Hanna");
    test("SyncedPropertyTwoWay#2: 'say' expected updated value is `Hanna`.", link2.get() == "Hanna");
  });

  tcase("link1 and link2 update from AppStorage.set", () => {
    AppStorage.Set<string>("say", "Paul");
    test("SyncedPropertyTwoWay#1: 'say' expected updated value is `Paul`.", link1.get() == "Paul");
    test("SyncedPropertyTwoWay#2: 'say' expected updated value is `Paul`.", link2.get() == "Paul");
  });

  AppStorage.Set("say", "Guido");
  let prop = AppStorage.Prop("say");

  tcase("prop.get", () => {
    test("prop value expected `Guido`.", prop.get() == "Guido");
  });


  tcase("prop.set change value only locally.", () => {
    prop.set("Hanna");
    test("prop changed value expected `Hanna`.", prop.get() == "Hanna");
    test("link1 unchanged value expected `Guido`.", link1.get() == "Guido");
    test("app unchanged value expected `Guido`.", AppStorage.Get("say") == "Guido");
  })

  tcase("appstorage set changes prop values", () => {
    AppStorage.Set("say", "Anton");
    test("prop changed value expected `Anton`.", prop.get() == "Anton");
  })

  tcase("unsubscribe proptoLink1, linkToLink2", () => {
    const asSubscribers = AppStorage.NumberOfSubscribersTo("say");
    link2.aboutToBeDeleted();
    test("link2 subscriber has been unsubscribed from as", AppStorage.NumberOfSubscribersTo("say") == asSubscribers - 1);
  })

  class TestAClass {
    public a: number;
    public b: number;
  }

  let objAClass1: TestAClass = { a: 1, b: 2 };
  let objAClass2: TestAClass = { a: 101, b: 201 };

  tcase("ObservedObject create, get, set", () => {
    AppStorage.SetOrCreate<TestAClass>("objAClass", objAClass1);
    test("ObservedObject create, value read back prop 'a'", (AppStorage.Get<TestAClass>("objAClass").a == 1 && AppStorage.Get<TestAClass>("objAClass").b == 2));

    AppStorage.Get<TestAClass>("objAClass").a = 47;
    test("ObservedObject property value change, value read back", AppStorage.Get<TestAClass>("objAClass").a == 47);

    AppStorage.Set<TestAClass>("objAClass", objAClass2);
    test("ObservedProperty of type ObservedObject set new ObservedObject, value read back",
      AppStorage.Get<TestAClass>("objAClass").a == 101 && AppStorage.Get<TestAClass>("objAClass").b == 201);

    AppStorage.Get<TestAClass>("objAClass").a = 102;
    test("Followed by prop value change, value read back",
      AppStorage.Get<TestAClass>("objAClass").a == 102 && AppStorage.Get<TestAClass>("objAClass").b == 201);
  })

  let linktoObsObj = AppStorage.Link<TestAClass>("objAClass");

  tcase("ObservedObject Link create, get, set", () => {

    test("link to ObservedObject, get value", linktoObsObj.get().b == 201);

    linktoObsObj.get().b = 203;
    test("link to ObservedObject, set value, read back link value", linktoObsObj.get().b == 203);
    test("link to ObservedObject, set value, read back value from AppStorage",
      AppStorage.Get<TestAClass>("objAClass").b == 203);
  })

  tcase("ObservedObject Prop to Link create, get, set", () => {
    let propToLinktoObsObj = linktoObsObj.createProp(undefined, "propToLinkObj");

    test("prop to link to ObservedObject, get value", propToLinktoObsObj.get().b == 203);

    propToLinktoObsObj.get().b = 204;
    test("prop to link to ObservedObject, set value locally, read back prop value", propToLinktoObsObj.get().b == 204);
    test("prop to link to ObservedObject, set value locally, read back link value", linktoObsObj.get().b == 203);
    test("prop to link to ObservedObject, set value locally, read back value from AppStorage",
      AppStorage.Get<TestAClass>("objAClass").b == 203);
    linktoObsObj.aboutToBeDeleted();
    propToLinktoObsObj.aboutToBeDeleted();
  })

  let proptoObsObj = AppStorage.Prop<TestAClass>("objAClass");

  tcase("ObservedObject Prop create, get, set", () => {

    test("prop to ObservedObject, get value", proptoObsObj.get().b == 203);

    proptoObsObj.get().b = 201;
    test("prop to ObservedObject, set value locally, read back prop value", proptoObsObj.get().b == 201);
    test("prop to ObservedObject, set value locally, read back original prop value from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 203);

    AppStorage.Set<TestAClass>("objAClass", { a: 42, b: 84 });
    test("prop to ObservedObject, set value to AppStorage, read back from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 84);
    test("prop to ObservedObject, set value to AppStorage, read back from prop", proptoObsObj.get().b == 84);
  })

  tcase("ObservedObject Prop to Prop create, get, set", () => {
    let propToPropObsObj = proptoObsObj.createProp(undefined, "propToProp");

    test("prop to prop to ObservedObject, get value", propToPropObsObj.get().a == 42);

    propToPropObsObj.get().a = 201;
    test("prop to prop to ObservedObject, set value locally, read back prop value", propToPropObsObj.get().a == 201);
    test("prop to prop to ObservedObject, set value locally, read back value from parent prop", proptoObsObj.get().a == 42);
    test("prop to prop to ObservedObject, set value locally, read back original prop value from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").a == 42);

    AppStorage.Set<TestAClass>("objAClass", { a: 421, b: 842 });
    test("prop to prop to ObservedObject, set value to AppStorage, read back from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 842);
    test("prop to prop toObservedObject, set value to AppStorage, read back from prop", propToPropObsObj.get().b == 842);
    test("prop to prop toObservedObject, set value to AppStorage, read back from parent prop", proptoObsObj.get().b == 842);

    propToPropObsObj.aboutToBeDeleted();
    proptoObsObj.aboutToBeDeleted();
  })

  tcase("ObservedObject Prop create, get, set", () => {

    test("prop to ObservedObject, get value", proptoObsObj.get().b == 203);

    proptoObsObj.get().b = 201;
    test("prop to ObservedObject, set value locally, read back prop value", proptoObsObj.get().b == 201);
    test("prop to ObservedObject, set value locally, read back original prop value from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 203);

    AppStorage.Set<TestAClass>("objAClass", { a: 42, b: 84 });
    test("prop to ObservedObject, set value to AppStorage, read back from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 84);
    test("prop to ObservedObject, set value to AppStorage, read back from prop", proptoObsObj.get().b == 84);
  })

  tcase("ObservedObject Prop to Prop create, get, set", () => {
    let propToPropObsObj = proptoObsObj.createProp(undefined, "propToProp");

    test("prop to prop to ObservedObject, get value", propToPropObsObj.get().a == 42);

    propToPropObsObj.get().a = 201;
    test("prop to prop to ObservedObject, set value locally, read back prop value", propToPropObsObj.get().a == 201);
    test("prop to prop to ObservedObject, set value locally, read back value from parent prop", proptoObsObj.get().a == 42);
    test("prop to prop to ObservedObject, set value locally, read back original prop value from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").a == 42);

    AppStorage.Set<TestAClass>("objAClass", { a: 421, b: 842 });
    test("prop to prop to ObservedObject, set value to AppStorage, read back from AppStorage", 
        AppStorage.Get<TestAClass>("objAClass").b == 842);
    test("prop to prop toObservedObject, set value to AppStorage, read back from prop", propToPropObsObj.get().b == 842);
    test("prop to prop toObservedObject, set value to AppStorage, read back from parent prop", proptoObsObj.get().b == 842);

    propToPropObsObj.aboutToBeDeleted();
    proptoObsObj.aboutToBeDeleted();
  })

  tcase("cleanup ok", () => {
    link1.aboutToBeDeleted();
    prop.aboutToBeDeleted();
    // note link2 and linktoLink2 have been deleted already earlier in this test suite!

    const deleteOk = AppStorage.Delete("name") && AppStorage.Delete("say") && AppStorage.Delete("true") && AppStorage.Delete("favorite") && AppStorage.Delete("objAClass");
    test(`Deletion of props form AppStrorage without isuses`, deleteOk)

    // test that manual cleanup has been complete, before calling AppStorage.NboutToBeDeleted();
    test(`AppStrorage has ${AppStorage.Size()} ObservedProperties: >${Array.from(AppStorage.Keys())}<, should be none.`, AppStorage.Size() == 0);

    AppStorage.AboutToBeDeleted();

    test(`SubscriberManager num of subscribers is ${SubscriberManager.NumberOfSubscribers()} should be 0 .`, 
      SubscriberManager.NumberOfSubscribers() == 0);


  });

});
