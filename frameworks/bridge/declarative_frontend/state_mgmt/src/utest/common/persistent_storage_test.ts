/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

const testPersistentStorage = tsuite("PersistentStorage", () => {
  let ms = new MockStorage("./src/utest/resources/test.db");
  PersistentStorage.configureBackend(ms);

  tcase("persisting existing values in AppStorage", () => {
    AppStorage.setOrCreate<number>("existingPropToPersist", 123);
    PersistentStorage.persistProp<number>("existingPropToPersist", 456);

    test("PersistentStorage 'existingPropToPersist' value retrieved from AppStorage correct", AppStorage.get<number>("existingPropToPersist") == 123);
    test("PersistentStorage 'existingPropToPersist' value retrieved from MockStorage correct", ms.get("existingPropToPersist") == 123);
  });
  tcase("retrieval of values", () => {
    AppStorage.setOrCreate<string>("persistentSay", "Terve");
    AppStorage.setOrCreate<string>("persistentSubject", "Maailma");

    PersistentStorage.persistProps([{
      key: "persistentSay",
      defaultValue: "Terve"
    }, {
      key: "persistentSubject",
      defaultValue: "Maailma"
    }]);

    test(`PersistentStorage 'persistentSay' value retrieved from AppStorage correct`, AppStorage.get<string>("persistentSay") === "Terve");
    test("PersistentStorage 'persistentSubject' value retrieved from AppStorage correct", AppStorage.get<string>("persistentSubject") == "Maailma");
  });

  tcase("writing values to IStorage via PersistentStorage", () => {
    PersistentStorage.persistProps([{
      key: "writeToDb",
      defaultValue: ""
    }, {
      key: "numberToDb",
      defaultValue: 10
    }]);
    AppStorage.set("writeToDb", "test");
    AppStorage.set("numberToDb", 42);
    test("PersistentStorage 'persistentSay' value retrieved from AppStorage correct", AppStorage.get<string>("persistentSay") == "Terve");
    test("PersistentStorage 'persistentSubject' value retrieved from AppStorage correct", AppStorage.get<string>("persistentSubject") == "Maailma");
    test("PersistentStorage 'writeToDb' value retrieved from AppStorage correct", AppStorage.get<string>("writeToDb") == "test");
    test("PersistentStorage 'numberToDb' value retrieved from AppStorage correct", AppStorage.get<number>("numberToDb") == 42);

    test("PersistentStorage 'writeToDb' value retrieved from MockStorage correct", ms.get<string>("writeToDb") == "test");
    test("PersistentStorage 'numberToDb' value retrieved from MockStorage correct", ms.get("numberToDb") == 42);
  });

  tcase("deleting values from IStorage via PersistentStorage", () => {
    PersistentStorage.deleteProp("writeToDb");
    PersistentStorage.deleteProp("numberToDb");
    AppStorage.delete("writeToDb");
    AppStorage.delete("numberToDb");
    test("MockStorage 'writeToDb' value deleted", ms.get("writeToDb") == undefined);
    test("MockStorage 'numberToDb' value deleted", ms.get("numberToDb") == undefined);
  });

  tcase("Persisting new property that does not exist in db", () => {
    PersistentStorage.persistProp("newProp", "new property value");

   test("PersistentStorage 'newProp' value retrieved from AppStorage correct", AppStorage.get<string>("newProp") == "new property value");
   test("MockStorage 'newProp' value retrieved from MockStorage correct", ms.get("newProp") == "new property value");
  });

  tcase("keys retrieval", () => {
    const keys = PersistentStorage.keys();
    for (var i in keys) {
      console.debug(`${keys[i]}`);
    }
  });

  tcase("teardown", () => {
    PersistentStorage.aboutToBeDeleted();
    const deleteOk = AppStorage.delete("persistentSay") && AppStorage.delete("persistentSubject") && AppStorage.delete("newProp") && AppStorage.delete("existingPropToPersist");

    SubscriberManager.DumpSubscriberInfo();

    test("PersistentStorage teardown complete", deleteOk);
    test(`SubscriberManager num of subscribers, is ${SubscriberManager.NumberOfSubscribers()} should be 0`, 
       SubscriberManager.NumberOfSubscribers() == 0);
  });
});
