/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
'use static';

import { Color } from '@ohos.arkui.component'

export class ArrayEntity {
  public static array_5: Array<number> = new Array<number>(5).fill(10);
  public static array_100: Array<number> = new Array<number>(100).fill(10);
  public static arr: number[] = [];
  public static flowItems: number[] = [];
  public static textTenLength: string = 'aaaaaaaaaa';
  public static textTwentyLength: string = 'aaaaaaaaaaaaaaaaaaaa';
  public static textOneHundredHuLength: string =
    'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
  public static bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow];
  public static STATE_LOOP: number = 500;

  public static pushData(arrLength: number) {
    ArrayEntity.arr = [];
    for (let i = 0; i < arrLength; i++) {
      ArrayEntity.arr.push(i);
    }
  }
}


export class ArrayEntityOnce {
  public static flowItems: number[] = [];
  public static array_5: Array<number> = new Array<number>(5).fill(10);
  public static array_100: Array<number> = new Array<number>(100).fill(10);
  public static arr: number[] = [];
  public static textTenLength: string = 'aaaaaaaaaa';
  public static textTwentyLength: string = 'aaaaaaaaaaaaaaaaaaaa';
  public static textOneHundredHuLength: string =
    'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
  public static bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow];
  public static STATE_LOOP: number = 50;

  public static pushData(arrLength: number) {
    ArrayEntityOnce.arr = [];
    for (let i = 0; i < arrLength; i++) {
      ArrayEntityOnce.arr.push(i);
    }
  }
}
