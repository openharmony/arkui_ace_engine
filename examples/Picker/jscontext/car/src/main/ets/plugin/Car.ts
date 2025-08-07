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
globalThis.aaa = "i am from plugin.";
globalThis.width = 10;
class Car {
  callCar(): string {
    return 'yes. call car success. from ' + globalThis.aaa;
  }

  callCarAsync(): Promise<string> {
    return new Promise<string>((resolve) => {
      resolve('hello async => ' + globalThis.aaa);
    });
  }

  callFileIo(filePath:string) {
    // Load native module failed, so is @ohos:file.fs
    setTimeout("");
    console.log('callFileIo plugin. hms = ' + globalThis.hms);
    let isAccess = globalThis.hms.callFile(filePath);
    console.log('Car isAccess = ' + isAccess + ' , ' + globalThis.aaa);
  }
}

export const car = new Car();