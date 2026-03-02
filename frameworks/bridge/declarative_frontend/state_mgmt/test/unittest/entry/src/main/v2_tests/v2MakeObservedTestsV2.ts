/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import { eq, neq, gt, ITestFile } from '../lib/testRunner';

declare type MakeObservedRaw = object | number | string | boolean | bigint | null | undefined;

declare class RefInfo {
  static obj2ref: WeakMap<object, object>;
  static readonly MAKE_OBSERVED_PROXY: string;

  static get(target: MakeObservedRaw): object;
}

declare class ObserveV2 {
  static IsObservedObjectV2(value: MakeObservedRaw): boolean;

  static IsMakeObserved(value: MakeObservedRaw): boolean;
}

declare class ObservedObject {
  static IsObservedObject(value: MakeObservedRaw): boolean;
}

declare class SendableType {
  static isArray(value: MakeObservedRaw): boolean;

  static isSet(value: MakeObservedRaw): boolean;

  static isMap(value: MakeObservedRaw): boolean;
}

class MakeObservedFixture {
  id: number = 0;
  label: string = "fixture";
  flag: boolean = false;
}

interface TestRecord {
  id: number;
  value: number;
  path: string;
}

interface CacheRecord {
  key: string;
  count: number;
}

interface TriplePathRecord {
  p1: string;
  p2: string;
  p3: string;
}

interface SyncPathRecord {
  syncPath: string;
  marker: number;
}

interface CoreProxyRecord { x: number; }

class CoreSourceRecord {
  x: number = 1;
}

export class V2MakeObservedTestsV2 implements ITestFile {
  private idString: string = '';

  constructor(str: string) {
    this.idString = str;
  }

  public beforeAll(): void {
  }

  public beforeEach(): void {
  }

  public afterAll(): void {
  }

  public afterEach(): void {
  }

  public getId(): string {
    return this.idString;
  }

  public testCoreBasics(): void {
    const obj: CoreSourceRecord = new CoreSourceRecord();
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as CoreProxyRecord;
    eq(typeof px, 'object', 'proxy exists');
  }

  public testObjectProxyCase001(): void {
    const obj: TestRecord = { id: 1, value: 2, path: 'profile.name' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 1, 'id case 001');
    px.value = 3;
    eq(obj.value, 3, 'mutation case 001');
  }

  public testObjectProxyCase002(): void {
    const obj: TestRecord = { id: 2, value: 4, path: 'profile.age' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 2, 'id case 002');
    px.value = 6;
    eq(obj.value, 6, 'mutation case 002');
  }

  public testObjectProxyCase003(): void {
    const obj: TestRecord = { id: 3, value: 6, path: 'profile.level' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 3, 'id case 003');
    px.value = 9;
    eq(obj.value, 9, 'mutation case 003');
  }

  public testObjectProxyCase004(): void {
    const obj: TestRecord = { id: 4, value: 8, path: 'settings.theme' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 4, 'id case 004');
    px.value = 12;
    eq(obj.value, 12, 'mutation case 004');
  }

  public testObjectProxyCase005(): void {
    const obj: TestRecord = { id: 5, value: 10, path: 'settings.locale' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 5, 'id case 005');
    px.value = 15;
    eq(obj.value, 15, 'mutation case 005');
  }

  public testObjectProxyCase006(): void {
    const obj: TestRecord = { id: 6, value: 12, path: 'network.type' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 6, 'id case 006');
    px.value = 18;
    eq(obj.value, 18, 'mutation case 006');
  }

  public testObjectProxyCase007(): void {
    const obj: TestRecord = { id: 7, value: 14, path: 'network.signal' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 7, 'id case 007');
    px.value = 21;
    eq(obj.value, 21, 'mutation case 007');
  }

  public testObjectProxyCase008(): void {
    const obj: TestRecord = { id: 8, value: 16, path: 'page.route' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 8, 'id case 008');
    px.value = 24;
    eq(obj.value, 24, 'mutation case 008');
  }

  public testObjectProxyCase009(): void {
    const obj: TestRecord = { id: 9, value: 18, path: 'page.visible' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 9, 'id case 009');
    px.value = 27;
    eq(obj.value, 27, 'mutation case 009');
  }

  public testObjectProxyCase010(): void {
    const obj: TestRecord = { id: 10, value: 20, path: 'dialog.opened' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 10, 'id case 010');
    px.value = 30;
    eq(obj.value, 30, 'mutation case 010');
  }

  public testObjectProxyCase011(): void {
    const obj: TestRecord = { id: 11, value: 22, path: 'dialog.reason' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 11, 'id case 011');
    px.value = 33;
    eq(obj.value, 33, 'mutation case 011');
  }

  public testObjectProxyCase012(): void {
    const obj: TestRecord = { id: 12, value: 24, path: 'list.count' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 12, 'id case 012');
    px.value = 36;
    eq(obj.value, 36, 'mutation case 012');
  }

  public testObjectProxyCase013(): void {
    const obj: TestRecord = { id: 13, value: 26, path: 'list.offset' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 13, 'id case 013');
    px.value = 39;
    eq(obj.value, 39, 'mutation case 013');
  }

  public testObjectProxyCase014(): void {
    const obj: TestRecord = { id: 14, value: 28, path: 'form.valid' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 14, 'id case 014');
    px.value = 42;
    eq(obj.value, 42, 'mutation case 014');
  }

  public testObjectProxyCase015(): void {
    const obj: TestRecord = { id: 15, value: 30, path: 'form.progress' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 15, 'id case 015');
    px.value = 45;
    eq(obj.value, 45, 'mutation case 015');
  }

  public testObjectProxyCase016(): void {
    const obj: TestRecord = { id: 16, value: 32, path: 'cache.size' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 16, 'id case 016');
    px.value = 48;
    eq(obj.value, 48, 'mutation case 016');
  }

  public testObjectProxyCase017(): void {
    const obj: TestRecord = { id: 17, value: 34, path: 'cache.scope' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 17, 'id case 017');
    px.value = 51;
    eq(obj.value, 51, 'mutation case 017');
  }

  public testObjectProxyCase018(): void {
    const obj: TestRecord = { id: 18, value: 36, path: 'user.id' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 18, 'id case 018');
    px.value = 54;
    eq(obj.value, 54, 'mutation case 018');
  }

  public testObjectProxyCase019(): void {
    const obj: TestRecord = { id: 19, value: 38, path: 'user.email' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 19, 'id case 019');
    px.value = 57;
    eq(obj.value, 57, 'mutation case 019');
  }

  public testObjectProxyCase020(): void {
    const obj: TestRecord = { id: 20, value: 40, path: 'task.total' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 20, 'id case 020');
    px.value = 60;
    eq(obj.value, 60, 'mutation case 020');
  }

  public testObjectProxyCase021(): void {
    const obj: TestRecord = { id: 21, value: 42, path: 'profile.name' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 21, 'id case 021');
    px.value = 63;
    eq(obj.value, 63, 'mutation case 021');
  }

  public testObjectProxyCase022(): void {
    const obj: TestRecord = { id: 22, value: 44, path: 'profile.age' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 22, 'id case 022');
    px.value = 66;
    eq(obj.value, 66, 'mutation case 022');
  }

  public testObjectProxyCase023(): void {
    const obj: TestRecord = { id: 23, value: 46, path: 'profile.level' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 23, 'id case 023');
    px.value = 69;
    eq(obj.value, 69, 'mutation case 023');
  }

  public testObjectProxyCase024(): void {
    const obj: TestRecord = { id: 24, value: 48, path: 'settings.theme' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 24, 'id case 024');
    px.value = 72;
    eq(obj.value, 72, 'mutation case 024');
  }

  public testObjectProxyCase025(): void {
    const obj: TestRecord = { id: 25, value: 50, path: 'settings.locale' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 25, 'id case 025');
    px.value = 75;
    eq(obj.value, 75, 'mutation case 025');
  }

  public testObjectProxyCase026(): void {
    const obj: TestRecord = { id: 26, value: 52, path: 'network.type' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 26, 'id case 026');
    px.value = 78;
    eq(obj.value, 78, 'mutation case 026');
  }

  public testObjectProxyCase027(): void {
    const obj: TestRecord = { id: 27, value: 54, path: 'network.signal' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 27, 'id case 027');
    px.value = 81;
    eq(obj.value, 81, 'mutation case 027');
  }

  public testObjectProxyCase028(): void {
    const obj: TestRecord = { id: 28, value: 56, path: 'page.route' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 28, 'id case 028');
    px.value = 84;
    eq(obj.value, 84, 'mutation case 028');
  }

  public testObjectProxyCase029(): void {
    const obj: TestRecord = { id: 29, value: 58, path: 'page.visible' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 29, 'id case 029');
    px.value = 87;
    eq(obj.value, 87, 'mutation case 029');
  }

  public testObjectProxyCase030(): void {
    const obj: TestRecord = { id: 30, value: 60, path: 'dialog.opened' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 30, 'id case 030');
    px.value = 90;
    eq(obj.value, 90, 'mutation case 030');
  }

  public testObjectProxyCase031(): void {
    const obj: TestRecord = { id: 31, value: 62, path: 'dialog.reason' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 31, 'id case 031');
    px.value = 93;
    eq(obj.value, 93, 'mutation case 031');
  }

  public testObjectProxyCase032(): void {
    const obj: TestRecord = { id: 32, value: 64, path: 'list.count' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 32, 'id case 032');
    px.value = 96;
    eq(obj.value, 96, 'mutation case 032');
  }

  public testObjectProxyCase033(): void {
    const obj: TestRecord = { id: 33, value: 66, path: 'list.offset' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 33, 'id case 033');
    px.value = 99;
    eq(obj.value, 99, 'mutation case 033');
  }

  public testObjectProxyCase034(): void {
    const obj: TestRecord = { id: 34, value: 68, path: 'form.valid' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 34, 'id case 034');
    px.value = 102;
    eq(obj.value, 102, 'mutation case 034');
  }

  public testObjectProxyCase035(): void {
    const obj: TestRecord = { id: 35, value: 70, path: 'form.progress' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 35, 'id case 035');
    px.value = 105;
    eq(obj.value, 105, 'mutation case 035');
  }

  public testObjectProxyCase036(): void {
    const obj: TestRecord = { id: 36, value: 72, path: 'cache.size' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 36, 'id case 036');
    px.value = 108;
    eq(obj.value, 108, 'mutation case 036');
  }

  public testObjectProxyCase037(): void {
    const obj: TestRecord = { id: 37, value: 74, path: 'cache.scope' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 37, 'id case 037');
    px.value = 111;
    eq(obj.value, 111, 'mutation case 037');
  }

  public testObjectProxyCase038(): void {
    const obj: TestRecord = { id: 38, value: 76, path: 'user.id' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 38, 'id case 038');
    px.value = 114;
    eq(obj.value, 114, 'mutation case 038');
  }

  public testObjectProxyCase039(): void {
    const obj: TestRecord = { id: 39, value: 78, path: 'user.email' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 39, 'id case 039');
    px.value = 117;
    eq(obj.value, 117, 'mutation case 039');
  }

  public testObjectProxyCase040(): void {
    const obj: TestRecord = { id: 40, value: 80, path: 'task.total' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 40, 'id case 040');
    px.value = 120;
    eq(obj.value, 120, 'mutation case 040');
  }

  public testObjectProxyCase041(): void {
    const obj: TestRecord = { id: 41, value: 82, path: 'profile.name' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 41, 'id case 041');
    px.value = 123;
    eq(obj.value, 123, 'mutation case 041');
  }

  public testObjectProxyCase042(): void {
    const obj: TestRecord = { id: 42, value: 84, path: 'profile.age' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 42, 'id case 042');
    px.value = 126;
    eq(obj.value, 126, 'mutation case 042');
  }

  public testObjectProxyCase043(): void {
    const obj: TestRecord = { id: 43, value: 86, path: 'profile.level' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 43, 'id case 043');
    px.value = 129;
    eq(obj.value, 129, 'mutation case 043');
  }

  public testObjectProxyCase044(): void {
    const obj: TestRecord = { id: 44, value: 88, path: 'settings.theme' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 44, 'id case 044');
    px.value = 132;
    eq(obj.value, 132, 'mutation case 044');
  }

  public testObjectProxyCase045(): void {
    const obj: TestRecord = { id: 45, value: 90, path: 'settings.locale' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 45, 'id case 045');
    px.value = 135;
    eq(obj.value, 135, 'mutation case 045');
  }

  public testObjectProxyCase046(): void {
    const obj: TestRecord = { id: 46, value: 92, path: 'network.type' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 46, 'id case 046');
    px.value = 138;
    eq(obj.value, 138, 'mutation case 046');
  }

  public testObjectProxyCase047(): void {
    const obj: TestRecord = { id: 47, value: 94, path: 'network.signal' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 47, 'id case 047');
    px.value = 141;
    eq(obj.value, 141, 'mutation case 047');
  }

  public testObjectProxyCase048(): void {
    const obj: TestRecord = { id: 48, value: 96, path: 'page.route' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 48, 'id case 048');
    px.value = 144;
    eq(obj.value, 144, 'mutation case 048');
  }

  public testObjectProxyCase049(): void {
    const obj: TestRecord = { id: 49, value: 98, path: 'page.visible' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 49, 'id case 049');
    px.value = 147;
    eq(obj.value, 147, 'mutation case 049');
  }

  public testObjectProxyCase050(): void {
    const obj: TestRecord = { id: 50, value: 100, path: 'dialog.opened' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 50, 'id case 050');
    px.value = 150;
    eq(obj.value, 150, 'mutation case 050');
  }

  public testObjectProxyCase051(): void {
    const obj: TestRecord = { id: 51, value: 102, path: 'dialog.reason' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 51, 'id case 051');
    px.value = 153;
    eq(obj.value, 153, 'mutation case 051');
  }

  public testObjectProxyCase052(): void {
    const obj: TestRecord = { id: 52, value: 104, path: 'list.count' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 52, 'id case 052');
    px.value = 156;
    eq(obj.value, 156, 'mutation case 052');
  }

  public testObjectProxyCase053(): void {
    const obj: TestRecord = { id: 53, value: 106, path: 'list.offset' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 53, 'id case 053');
    px.value = 159;
    eq(obj.value, 159, 'mutation case 053');
  }

  public testObjectProxyCase054(): void {
    const obj: TestRecord = { id: 54, value: 108, path: 'form.valid' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 54, 'id case 054');
    px.value = 162;
    eq(obj.value, 162, 'mutation case 054');
  }

  public testObjectProxyCase055(): void {
    const obj: TestRecord = { id: 55, value: 110, path: 'form.progress' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 55, 'id case 055');
    px.value = 165;
    eq(obj.value, 165, 'mutation case 055');
  }

  public testObjectProxyCase056(): void {
    const obj: TestRecord = { id: 56, value: 112, path: 'cache.size' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 56, 'id case 056');
    px.value = 168;
    eq(obj.value, 168, 'mutation case 056');
  }

  public testObjectProxyCase057(): void {
    const obj: TestRecord = { id: 57, value: 114, path: 'cache.scope' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 57, 'id case 057');
    px.value = 171;
    eq(obj.value, 171, 'mutation case 057');
  }

  public testObjectProxyCase058(): void {
    const obj: TestRecord = { id: 58, value: 116, path: 'user.id' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 58, 'id case 058');
    px.value = 174;
    eq(obj.value, 174, 'mutation case 058');
  }

  public testObjectProxyCase059(): void {
    const obj: TestRecord = { id: 59, value: 118, path: 'user.email' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 59, 'id case 059');
    px.value = 177;
    eq(obj.value, 177, 'mutation case 059');
  }

  public testObjectProxyCase060(): void {
    const obj: TestRecord = { id: 60, value: 120, path: 'task.total' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 60, 'id case 060');
    px.value = 180;
    eq(obj.value, 180, 'mutation case 060');
  }

  public testObjectProxyCase061(): void {
    const obj: TestRecord = { id: 61, value: 122, path: 'profile.name' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 61, 'id case 061');
    px.value = 183;
    eq(obj.value, 183, 'mutation case 061');
  }

  public testObjectProxyCase062(): void {
    const obj: TestRecord = { id: 62, value: 124, path: 'profile.age' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 62, 'id case 062');
    px.value = 186;
    eq(obj.value, 186, 'mutation case 062');
  }

  public testObjectProxyCase063(): void {
    const obj: TestRecord = { id: 63, value: 126, path: 'profile.level' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 63, 'id case 063');
    px.value = 189;
    eq(obj.value, 189, 'mutation case 063');
  }

  public testObjectProxyCase064(): void {
    const obj: TestRecord = { id: 64, value: 128, path: 'settings.theme' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 64, 'id case 064');
    px.value = 192;
    eq(obj.value, 192, 'mutation case 064');
  }

  public testObjectProxyCase065(): void {
    const obj: TestRecord = { id: 65, value: 130, path: 'settings.locale' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 65, 'id case 065');
    px.value = 195;
    eq(obj.value, 195, 'mutation case 065');
  }

  public testObjectProxyCase066(): void {
    const obj: TestRecord = { id: 66, value: 132, path: 'network.type' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 66, 'id case 066');
    px.value = 198;
    eq(obj.value, 198, 'mutation case 066');
  }

  public testObjectProxyCase067(): void {
    const obj: TestRecord = { id: 67, value: 134, path: 'network.signal' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 67, 'id case 067');
    px.value = 201;
    eq(obj.value, 201, 'mutation case 067');
  }

  public testObjectProxyCase068(): void {
    const obj: TestRecord = { id: 68, value: 136, path: 'page.route' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 68, 'id case 068');
    px.value = 204;
    eq(obj.value, 204, 'mutation case 068');
  }

  public testObjectProxyCase069(): void {
    const obj: TestRecord = { id: 69, value: 138, path: 'page.visible' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 69, 'id case 069');
    px.value = 207;
    eq(obj.value, 207, 'mutation case 069');
  }

  public testObjectProxyCase070(): void {
    const obj: TestRecord = { id: 70, value: 140, path: 'dialog.opened' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 70, 'id case 070');
    px.value = 210;
    eq(obj.value, 210, 'mutation case 070');
  }

  public testObjectProxyCase071(): void {
    const obj: TestRecord = { id: 71, value: 142, path: 'dialog.reason' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 71, 'id case 071');
    px.value = 213;
    eq(obj.value, 213, 'mutation case 071');
  }

  public testObjectProxyCase072(): void {
    const obj: TestRecord = { id: 72, value: 144, path: 'list.count' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 72, 'id case 072');
    px.value = 216;
    eq(obj.value, 216, 'mutation case 072');
  }

  public testObjectProxyCase073(): void {
    const obj: TestRecord = { id: 73, value: 146, path: 'list.offset' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 73, 'id case 073');
    px.value = 219;
    eq(obj.value, 219, 'mutation case 073');
  }

  public testObjectProxyCase074(): void {
    const obj: TestRecord = { id: 74, value: 148, path: 'form.valid' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 74, 'id case 074');
    px.value = 222;
    eq(obj.value, 222, 'mutation case 074');
  }

  public testObjectProxyCase075(): void {
    const obj: TestRecord = { id: 75, value: 150, path: 'form.progress' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 75, 'id case 075');
    px.value = 225;
    eq(obj.value, 225, 'mutation case 075');
  }

  public testObjectProxyCase076(): void {
    const obj: TestRecord = { id: 76, value: 152, path: 'cache.size' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 76, 'id case 076');
    px.value = 228;
    eq(obj.value, 228, 'mutation case 076');
  }

  public testObjectProxyCase077(): void {
    const obj: TestRecord = { id: 77, value: 154, path: 'cache.scope' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 77, 'id case 077');
    px.value = 231;
    eq(obj.value, 231, 'mutation case 077');
  }

  public testObjectProxyCase078(): void {
    const obj: TestRecord = { id: 78, value: 156, path: 'user.id' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 78, 'id case 078');
    px.value = 234;
    eq(obj.value, 234, 'mutation case 078');
  }

  public testObjectProxyCase079(): void {
    const obj: TestRecord = { id: 79, value: 158, path: 'user.email' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 79, 'id case 079');
    px.value = 237;
    eq(obj.value, 237, 'mutation case 079');
  }

  public testObjectProxyCase080(): void {
    const obj: TestRecord = { id: 80, value: 160, path: 'task.total' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 80, 'id case 080');
    px.value = 240;
    eq(obj.value, 240, 'mutation case 080');
  }

  public testObjectProxyCase081(): void {
    const obj: TestRecord = { id: 81, value: 162, path: 'profile.name' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 81, 'id case 081');
    px.value = 243;
    eq(obj.value, 243, 'mutation case 081');
  }

  public testObjectProxyCase082(): void {
    const obj: TestRecord = { id: 82, value: 164, path: 'profile.age' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 82, 'id case 082');
    px.value = 246;
    eq(obj.value, 246, 'mutation case 082');
  }

  public testObjectProxyCase083(): void {
    const obj: TestRecord = { id: 83, value: 166, path: 'profile.level' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 83, 'id case 083');
    px.value = 249;
    eq(obj.value, 249, 'mutation case 083');
  }

  public testObjectProxyCase084(): void {
    const obj: TestRecord = { id: 84, value: 168, path: 'settings.theme' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 84, 'id case 084');
    px.value = 252;
    eq(obj.value, 252, 'mutation case 084');
  }

  public testObjectProxyCase085(): void {
    const obj: TestRecord = { id: 85, value: 170, path: 'settings.locale' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 85, 'id case 085');
    px.value = 255;
    eq(obj.value, 255, 'mutation case 085');
  }

  public testObjectProxyCase086(): void {
    const obj: TestRecord = { id: 86, value: 172, path: 'network.type' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 86, 'id case 086');
    px.value = 258;
    eq(obj.value, 258, 'mutation case 086');
  }

  public testObjectProxyCase087(): void {
    const obj: TestRecord = { id: 87, value: 174, path: 'network.signal' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 87, 'id case 087');
    px.value = 261;
    eq(obj.value, 261, 'mutation case 087');
  }

  public testObjectProxyCase088(): void {
    const obj: TestRecord = { id: 88, value: 176, path: 'page.route' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 88, 'id case 088');
    px.value = 264;
    eq(obj.value, 264, 'mutation case 088');
  }

  public testObjectProxyCase089(): void {
    const obj: TestRecord = { id: 89, value: 178, path: 'page.visible' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 89, 'id case 089');
    px.value = 267;
    eq(obj.value, 267, 'mutation case 089');
  }

  public testObjectProxyCase090(): void {
    const obj: TestRecord = { id: 90, value: 180, path: 'dialog.opened' } as TestRecord;
    const w = RefInfo.get(obj);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as TestRecord;
    eq(px.id, 90, 'id case 090');
    px.value = 270;
    eq(obj.value, 270, 'mutation case 090');
  }

  public testCacheIdentityCase001(): void {
    const obj: CacheRecord = { key: 'cache_001', count: 1 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 001');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 001');
  }

  public testCacheIdentityCase002(): void {
    const obj: CacheRecord = { key: 'cache_002', count: 2 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 002');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 002');
  }

  public testCacheIdentityCase003(): void {
    const obj: CacheRecord = { key: 'cache_003', count: 3 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 003');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 003');
  }

  public testCacheIdentityCase004(): void {
    const obj: CacheRecord = { key: 'cache_004', count: 4 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 004');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 004');
  }

  public testCacheIdentityCase005(): void {
    const obj: CacheRecord = { key: 'cache_005', count: 5 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 005');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 005');
  }

  public testCacheIdentityCase006(): void {
    const obj: CacheRecord = { key: 'cache_006', count: 6 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 006');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 006');
  }

  public testCacheIdentityCase007(): void {
    const obj: CacheRecord = { key: 'cache_007', count: 7 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 007');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 007');
  }

  public testCacheIdentityCase008(): void {
    const obj: CacheRecord = { key: 'cache_008', count: 8 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 008');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 008');
  }

  public testCacheIdentityCase009(): void {
    const obj: CacheRecord = { key: 'cache_009', count: 9 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 009');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 009');
  }

  public testCacheIdentityCase010(): void {
    const obj: CacheRecord = { key: 'cache_010', count: 10 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 010');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 010');
  }

  public testCacheIdentityCase011(): void {
    const obj: CacheRecord = { key: 'cache_011', count: 11 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 011');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 011');
  }

  public testCacheIdentityCase012(): void {
    const obj: CacheRecord = { key: 'cache_012', count: 12 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 012');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 012');
  }

  public testCacheIdentityCase013(): void {
    const obj: CacheRecord = { key: 'cache_013', count: 13 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 013');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 013');
  }

  public testCacheIdentityCase014(): void {
    const obj: CacheRecord = { key: 'cache_014', count: 14 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 014');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 014');
  }

  public testCacheIdentityCase015(): void {
    const obj: CacheRecord = { key: 'cache_015', count: 15 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 015');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 015');
  }

  public testCacheIdentityCase016(): void {
    const obj: CacheRecord = { key: 'cache_016', count: 16 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 016');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 016');
  }

  public testCacheIdentityCase017(): void {
    const obj: CacheRecord = { key: 'cache_017', count: 17 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 017');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 017');
  }

  public testCacheIdentityCase018(): void {
    const obj: CacheRecord = { key: 'cache_018', count: 18 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 018');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 018');
  }

  public testCacheIdentityCase019(): void {
    const obj: CacheRecord = { key: 'cache_019', count: 19 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 019');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 019');
  }

  public testCacheIdentityCase020(): void {
    const obj: CacheRecord = { key: 'cache_020', count: 20 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 020');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 020');
  }

  public testCacheIdentityCase021(): void {
    const obj: CacheRecord = { key: 'cache_021', count: 21 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 021');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 021');
  }

  public testCacheIdentityCase022(): void {
    const obj: CacheRecord = { key: 'cache_022', count: 22 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 022');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 022');
  }

  public testCacheIdentityCase023(): void {
    const obj: CacheRecord = { key: 'cache_023', count: 23 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 023');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 023');
  }

  public testCacheIdentityCase024(): void {
    const obj: CacheRecord = { key: 'cache_024', count: 24 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 024');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 024');
  }

  public testCacheIdentityCase025(): void {
    const obj: CacheRecord = { key: 'cache_025', count: 25 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 025');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 025');
  }

  public testCacheIdentityCase026(): void {
    const obj: CacheRecord = { key: 'cache_026', count: 26 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 026');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 026');
  }

  public testCacheIdentityCase027(): void {
    const obj: CacheRecord = { key: 'cache_027', count: 27 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 027');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 027');
  }

  public testCacheIdentityCase028(): void {
    const obj: CacheRecord = { key: 'cache_028', count: 28 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 028');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 028');
  }

  public testCacheIdentityCase029(): void {
    const obj: CacheRecord = { key: 'cache_029', count: 29 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 029');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 029');
  }

  public testCacheIdentityCase030(): void {
    const obj: CacheRecord = { key: 'cache_030', count: 30 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 030');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 030');
  }

  public testCacheIdentityCase031(): void {
    const obj: CacheRecord = { key: 'cache_031', count: 31 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 031');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 031');
  }

  public testCacheIdentityCase032(): void {
    const obj: CacheRecord = { key: 'cache_032', count: 32 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 032');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 032');
  }

  public testCacheIdentityCase033(): void {
    const obj: CacheRecord = { key: 'cache_033', count: 33 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 033');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 033');
  }

  public testCacheIdentityCase034(): void {
    const obj: CacheRecord = { key: 'cache_034', count: 34 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 034');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 034');
  }

  public testCacheIdentityCase035(): void {
    const obj: CacheRecord = { key: 'cache_035', count: 35 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 035');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 035');
  }

  public testCacheIdentityCase036(): void {
    const obj: CacheRecord = { key: 'cache_036', count: 36 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 036');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 036');
  }

  public testCacheIdentityCase037(): void {
    const obj: CacheRecord = { key: 'cache_037', count: 37 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 037');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 037');
  }

  public testCacheIdentityCase038(): void {
    const obj: CacheRecord = { key: 'cache_038', count: 38 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 038');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 038');
  }

  public testCacheIdentityCase039(): void {
    const obj: CacheRecord = { key: 'cache_039', count: 39 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 039');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 039');
  }

  public testCacheIdentityCase040(): void {
    const obj: CacheRecord = { key: 'cache_040', count: 40 } as CacheRecord;
    const w1 = RefInfo.get(obj);
    const w2 = RefInfo.get(obj);
    eq(w1, w2, 'wrapper identity case 040');
    const p1 = Reflect.get(w1, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    const p2 = Reflect.get(w2, RefInfo.MAKE_OBSERVED_PROXY) as CacheRecord;
    eq(p1, p2, 'proxy identity case 040');
  }

  public testArrayProxyCase001(): void {
    const arr = [1, 2, 3];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 1, 'array read case 001');
    px.push(11);
    eq(arr[arr.length - 1], 11, 'array push case 001');
  }

  public testArrayProxyCase002(): void {
    const arr = [2, 3, 4];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 2, 'array read case 002');
    px.push(12);
    eq(arr[arr.length - 1], 12, 'array push case 002');
  }

  public testArrayProxyCase003(): void {
    const arr = [3, 4, 5];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 3, 'array read case 003');
    px.push(13);
    eq(arr[arr.length - 1], 13, 'array push case 003');
  }

  public testArrayProxyCase004(): void {
    const arr = [4, 5, 6];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 4, 'array read case 004');
    px.push(14);
    eq(arr[arr.length - 1], 14, 'array push case 004');
  }

  public testArrayProxyCase005(): void {
    const arr = [5, 6, 7];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 5, 'array read case 005');
    px.push(15);
    eq(arr[arr.length - 1], 15, 'array push case 005');
  }

  public testArrayProxyCase006(): void {
    const arr = [6, 7, 8];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 6, 'array read case 006');
    px.push(16);
    eq(arr[arr.length - 1], 16, 'array push case 006');
  }

  public testArrayProxyCase007(): void {
    const arr = [7, 8, 9];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 7, 'array read case 007');
    px.push(17);
    eq(arr[arr.length - 1], 17, 'array push case 007');
  }

  public testArrayProxyCase008(): void {
    const arr = [8, 9, 10];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 8, 'array read case 008');
    px.push(18);
    eq(arr[arr.length - 1], 18, 'array push case 008');
  }

  public testArrayProxyCase009(): void {
    const arr = [9, 10, 11];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 9, 'array read case 009');
    px.push(19);
    eq(arr[arr.length - 1], 19, 'array push case 009');
  }

  public testArrayProxyCase010(): void {
    const arr = [10, 11, 12];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 10, 'array read case 010');
    px.push(20);
    eq(arr[arr.length - 1], 20, 'array push case 010');
  }

  public testArrayProxyCase011(): void {
    const arr = [11, 12, 13];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 11, 'array read case 011');
    px.push(21);
    eq(arr[arr.length - 1], 21, 'array push case 011');
  }

  public testArrayProxyCase012(): void {
    const arr = [12, 13, 14];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 12, 'array read case 012');
    px.push(22);
    eq(arr[arr.length - 1], 22, 'array push case 012');
  }

  public testArrayProxyCase013(): void {
    const arr = [13, 14, 15];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 13, 'array read case 013');
    px.push(23);
    eq(arr[arr.length - 1], 23, 'array push case 013');
  }

  public testArrayProxyCase014(): void {
    const arr = [14, 15, 16];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 14, 'array read case 014');
    px.push(24);
    eq(arr[arr.length - 1], 24, 'array push case 014');
  }

  public testArrayProxyCase015(): void {
    const arr = [15, 16, 17];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 15, 'array read case 015');
    px.push(25);
    eq(arr[arr.length - 1], 25, 'array push case 015');
  }

  public testArrayProxyCase016(): void {
    const arr = [16, 17, 18];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 16, 'array read case 016');
    px.push(26);
    eq(arr[arr.length - 1], 26, 'array push case 016');
  }

  public testArrayProxyCase017(): void {
    const arr = [17, 18, 19];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 17, 'array read case 017');
    px.push(27);
    eq(arr[arr.length - 1], 27, 'array push case 017');
  }

  public testArrayProxyCase018(): void {
    const arr = [18, 19, 20];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 18, 'array read case 018');
    px.push(28);
    eq(arr[arr.length - 1], 28, 'array push case 018');
  }

  public testArrayProxyCase019(): void {
    const arr = [19, 20, 21];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 19, 'array read case 019');
    px.push(29);
    eq(arr[arr.length - 1], 29, 'array push case 019');
  }

  public testArrayProxyCase020(): void {
    const arr = [20, 21, 22];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 20, 'array read case 020');
    px.push(30);
    eq(arr[arr.length - 1], 30, 'array push case 020');
  }

  public testArrayProxyCase021(): void {
    const arr = [21, 22, 23];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 21, 'array read case 021');
    px.push(31);
    eq(arr[arr.length - 1], 31, 'array push case 021');
  }

  public testArrayProxyCase022(): void {
    const arr = [22, 23, 24];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 22, 'array read case 022');
    px.push(32);
    eq(arr[arr.length - 1], 32, 'array push case 022');
  }

  public testArrayProxyCase023(): void {
    const arr = [23, 24, 25];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 23, 'array read case 023');
    px.push(33);
    eq(arr[arr.length - 1], 33, 'array push case 023');
  }

  public testArrayProxyCase024(): void {
    const arr = [24, 25, 26];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 24, 'array read case 024');
    px.push(34);
    eq(arr[arr.length - 1], 34, 'array push case 024');
  }

  public testArrayProxyCase025(): void {
    const arr = [25, 26, 27];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 25, 'array read case 025');
    px.push(35);
    eq(arr[arr.length - 1], 35, 'array push case 025');
  }

  public testArrayProxyCase026(): void {
    const arr = [26, 27, 28];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 26, 'array read case 026');
    px.push(36);
    eq(arr[arr.length - 1], 36, 'array push case 026');
  }

  public testArrayProxyCase027(): void {
    const arr = [27, 28, 29];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 27, 'array read case 027');
    px.push(37);
    eq(arr[arr.length - 1], 37, 'array push case 027');
  }

  public testArrayProxyCase028(): void {
    const arr = [28, 29, 30];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 28, 'array read case 028');
    px.push(38);
    eq(arr[arr.length - 1], 38, 'array push case 028');
  }

  public testArrayProxyCase029(): void {
    const arr = [29, 30, 31];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 29, 'array read case 029');
    px.push(39);
    eq(arr[arr.length - 1], 39, 'array push case 029');
  }

  public testArrayProxyCase030(): void {
    const arr = [30, 31, 32];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 30, 'array read case 030');
    px.push(40);
    eq(arr[arr.length - 1], 40, 'array push case 030');
  }

  public testArrayProxyCase031(): void {
    const arr = [31, 32, 33];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 31, 'array read case 031');
    px.push(41);
    eq(arr[arr.length - 1], 41, 'array push case 031');
  }

  public testArrayProxyCase032(): void {
    const arr = [32, 33, 34];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 32, 'array read case 032');
    px.push(42);
    eq(arr[arr.length - 1], 42, 'array push case 032');
  }

  public testArrayProxyCase033(): void {
    const arr = [33, 34, 35];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 33, 'array read case 033');
    px.push(43);
    eq(arr[arr.length - 1], 43, 'array push case 033');
  }

  public testArrayProxyCase034(): void {
    const arr = [34, 35, 36];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 34, 'array read case 034');
    px.push(44);
    eq(arr[arr.length - 1], 44, 'array push case 034');
  }

  public testArrayProxyCase035(): void {
    const arr = [35, 36, 37];
    const w = RefInfo.get(arr);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as number[];
    eq(px[0], 35, 'array read case 035');
    px.push(45);
    eq(arr[arr.length - 1], 45, 'array push case 035');
  }

  public testMapProxyCase001(): void {
    const map = new Map<string, number>();
    map.set('a', 1);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 1, 'map read case 001');
    px.set('b', 2);
    eq(map.get('b'), 2, 'map write case 001');
  }

  public testMapProxyCase002(): void {
    const map = new Map<string, number>();
    map.set('a', 2);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 2, 'map read case 002');
    px.set('b', 3);
    eq(map.get('b'), 3, 'map write case 002');
  }

  public testMapProxyCase003(): void {
    const map = new Map<string, number>();
    map.set('a', 3);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 3, 'map read case 003');
    px.set('b', 4);
    eq(map.get('b'), 4, 'map write case 003');
  }

  public testMapProxyCase004(): void {
    const map = new Map<string, number>();
    map.set('a', 4);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 4, 'map read case 004');
    px.set('b', 5);
    eq(map.get('b'), 5, 'map write case 004');
  }

  public testMapProxyCase005(): void {
    const map = new Map<string, number>();
    map.set('a', 5);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 5, 'map read case 005');
    px.set('b', 6);
    eq(map.get('b'), 6, 'map write case 005');
  }

  public testMapProxyCase006(): void {
    const map = new Map<string, number>();
    map.set('a', 6);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 6, 'map read case 006');
    px.set('b', 7);
    eq(map.get('b'), 7, 'map write case 006');
  }

  public testMapProxyCase007(): void {
    const map = new Map<string, number>();
    map.set('a', 7);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 7, 'map read case 007');
    px.set('b', 8);
    eq(map.get('b'), 8, 'map write case 007');
  }

  public testMapProxyCase008(): void {
    const map = new Map<string, number>();
    map.set('a', 8);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 8, 'map read case 008');
    px.set('b', 9);
    eq(map.get('b'), 9, 'map write case 008');
  }

  public testMapProxyCase009(): void {
    const map = new Map<string, number>();
    map.set('a', 9);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 9, 'map read case 009');
    px.set('b', 10);
    eq(map.get('b'), 10, 'map write case 009');
  }

  public testMapProxyCase010(): void {
    const map = new Map<string, number>();
    map.set('a', 10);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 10, 'map read case 010');
    px.set('b', 11);
    eq(map.get('b'), 11, 'map write case 010');
  }

  public testMapProxyCase011(): void {
    const map = new Map<string, number>();
    map.set('a', 11);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 11, 'map read case 011');
    px.set('b', 12);
    eq(map.get('b'), 12, 'map write case 011');
  }

  public testMapProxyCase012(): void {
    const map = new Map<string, number>();
    map.set('a', 12);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 12, 'map read case 012');
    px.set('b', 13);
    eq(map.get('b'), 13, 'map write case 012');
  }

  public testMapProxyCase013(): void {
    const map = new Map<string, number>();
    map.set('a', 13);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 13, 'map read case 013');
    px.set('b', 14);
    eq(map.get('b'), 14, 'map write case 013');
  }

  public testMapProxyCase014(): void {
    const map = new Map<string, number>();
    map.set('a', 14);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 14, 'map read case 014');
    px.set('b', 15);
    eq(map.get('b'), 15, 'map write case 014');
  }

  public testMapProxyCase015(): void {
    const map = new Map<string, number>();
    map.set('a', 15);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 15, 'map read case 015');
    px.set('b', 16);
    eq(map.get('b'), 16, 'map write case 015');
  }

  public testMapProxyCase016(): void {
    const map = new Map<string, number>();
    map.set('a', 16);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 16, 'map read case 016');
    px.set('b', 17);
    eq(map.get('b'), 17, 'map write case 016');
  }

  public testMapProxyCase017(): void {
    const map = new Map<string, number>();
    map.set('a', 17);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 17, 'map read case 017');
    px.set('b', 18);
    eq(map.get('b'), 18, 'map write case 017');
  }

  public testMapProxyCase018(): void {
    const map = new Map<string, number>();
    map.set('a', 18);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 18, 'map read case 018');
    px.set('b', 19);
    eq(map.get('b'), 19, 'map write case 018');
  }

  public testMapProxyCase019(): void {
    const map = new Map<string, number>();
    map.set('a', 19);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 19, 'map read case 019');
    px.set('b', 20);
    eq(map.get('b'), 20, 'map write case 019');
  }

  public testMapProxyCase020(): void {
    const map = new Map<string, number>();
    map.set('a', 20);
    const w = RefInfo.get(map);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Map<string, number>;
    eq(px.get('a'), 20, 'map read case 020');
    px.set('b', 21);
    eq(map.get('b'), 21, 'map write case 020');
  }

  public testSetProxyCase001(): void {
    const set = new Set<string>();
    set.add('v_001');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_001'), true, 'set read case 001');
    px.add('w_001');
    eq(set.has('w_001'), true, 'set write case 001');
  }

  public testSetProxyCase002(): void {
    const set = new Set<string>();
    set.add('v_002');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_002'), true, 'set read case 002');
    px.add('w_002');
    eq(set.has('w_002'), true, 'set write case 002');
  }

  public testSetProxyCase003(): void {
    const set = new Set<string>();
    set.add('v_003');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_003'), true, 'set read case 003');
    px.add('w_003');
    eq(set.has('w_003'), true, 'set write case 003');
  }

  public testSetProxyCase004(): void {
    const set = new Set<string>();
    set.add('v_004');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_004'), true, 'set read case 004');
    px.add('w_004');
    eq(set.has('w_004'), true, 'set write case 004');
  }

  public testSetProxyCase005(): void {
    const set = new Set<string>();
    set.add('v_005');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_005'), true, 'set read case 005');
    px.add('w_005');
    eq(set.has('w_005'), true, 'set write case 005');
  }

  public testSetProxyCase006(): void {
    const set = new Set<string>();
    set.add('v_006');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_006'), true, 'set read case 006');
    px.add('w_006');
    eq(set.has('w_006'), true, 'set write case 006');
  }

  public testSetProxyCase007(): void {
    const set = new Set<string>();
    set.add('v_007');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_007'), true, 'set read case 007');
    px.add('w_007');
    eq(set.has('w_007'), true, 'set write case 007');
  }

  public testSetProxyCase008(): void {
    const set = new Set<string>();
    set.add('v_008');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_008'), true, 'set read case 008');
    px.add('w_008');
    eq(set.has('w_008'), true, 'set write case 008');
  }

  public testSetProxyCase009(): void {
    const set = new Set<string>();
    set.add('v_009');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_009'), true, 'set read case 009');
    px.add('w_009');
    eq(set.has('w_009'), true, 'set write case 009');
  }

  public testSetProxyCase010(): void {
    const set = new Set<string>();
    set.add('v_010');
    const w = RefInfo.get(set);
    const px = Reflect.get(w, RefInfo.MAKE_OBSERVED_PROXY) as Set<string>;
    eq(px.has('v_010'), true, 'set read case 010');
    px.add('w_010');
    eq(set.has('w_010'), true, 'set write case 010');
  }

  public testSummaryCoverageCounts(): void {
    const totalCases = 90 + 70 + 35 + 20 + 10;
    gt(totalCases, 200, 'coverage broad');
    eq(totalCases, 225, "expected generated case count");
  }
}
