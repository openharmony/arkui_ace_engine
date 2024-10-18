/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

export class ArrEntity {
  public static arr: number[] = [];
  public static textTenLength: string = 'aaaaaaaaaa';
  public static textTwentyLength: string = 'aaaaaaaaaaaaaaaaaaaa';
  public static textOneHundredHuLength: string =
    'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa';
  //bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink, Color.Grey, Color.Blue, Color.Brown];
  public static bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow];
  public static STATE_LOOP: number = 500;

  public static pushData(arrlength: number) {
    ArrEntity.arr = [];
    for (let i = 0; i < arrlength; i++) {
      ArrEntity.arr.push(i);
    }
  }
}