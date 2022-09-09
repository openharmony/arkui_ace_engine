/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

const testViewAppStorage = tsuite("@StorageLink - AppStorge", () => {


  class SubscribingViewPU implements IMultiPropertiesChangeSubscriber {

    private id_: number = SubscriberManager.Get().MakeId();
    private label_: string;

    constructor(label: string) {
      SubscriberManager.Get().add(this);
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
      SubscriberManager.Get().delete(this.id__());
    }

    // implements IMultiPropertiesChangePublisher
    propertyHasChanged(info?: PropertyInfo): void {
      console.log(`SubscribingView '${this.label_}' object property ${info ? info : 'unknown'} has changed.`);
    }
  }

  let storeView = new SubscribingViewPU("v1p1b1");

  /* @StorageLink(moveDistance) storeProp:number=  0;  */
  let __storeProp: ObservedPropertyAbstract<number> =
    AppStorage.SetAndLink<number>('storeProp', /* default value */  7,  /* subscriber */ storeView, /* var name in View */ "viewVar");


  tcase("read back", () => {
    test("readback from AppStorage", AppStorage.Get("storeProp") == 7);
    test("readback from view variable", __storeProp.get() == 7);
  });

  tcase("modify via AppStore", () => {
    let spy = spyOn(storeView, "propertyHasChanged");
    AppStorage.Set("storeProp", 47);

    test("readback from AppStorage", AppStorage.Get("storeProp") == 47);
    test("readback from view variable", __storeProp.get() == 47);
    test("View.propertyHasChanged has been called", spy.called && spy.args[0] == "viewVar");
  });

  tcase("modify via @StorageLink", () => {
    let spy2 = spyOn(storeView, "propertyHasChanged");
    __storeProp.set(101);
    test("readback from AppStorage", AppStorage.Get("storeProp") == 101);
    test("readback from view variable", __storeProp.get() == 101);
    test("View.propertyHasChanged has been called", spy2.called && spy2.args[0] == "viewVar");
  });

});