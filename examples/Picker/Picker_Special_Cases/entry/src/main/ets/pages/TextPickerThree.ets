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

import { LengthMetrics } from '@kit.ArkUI';

class Bottom {
  private bottom: number = 50
}

namespace IPicker {
  export enum EPickerMode {
    region = 'region',
    time = 'time',
    selector = 'selector',
    multiSelector = 'multiSelector',
    date = 'date'
  }

  export interface PickerInfo {
    range: string[][] | string[],
    current?: string,
    selected: number[] | number | undefined,
    fields?: string;
    start?: string;
    end?: string;
    requestId?: string;
    mode?: EPickerMode;
    level?: string;
    webviewId?: number;
  }
  export interface PickerStyle {
    // mask 颜色
    maskColor: string,

    // 背景
    backgroundColor: string,

    // 选择中的字体颜色
    selectedTextColor: string,

    // 待选择的字体颜色
    defaultTextColor: string,

    // 最上和最下两个选项的文本颜色
    disappearTextColor: string,
  }
}

let bott: Bottom = new Bottom()

const AGE_0: number = 0;

function getAgeString(age: number): Resource {
  if (age === AGE_0) {
    return $r('app.string.zero_age', 1);
  }
  return $r('app.plural.minors_temp_user_age', age, age);
}

function getPickerRange(maxAge: number) {
  const list: TextCascadePickerRangeContent[] = [];
  for (let index = AGE_0; index < maxAge; index++) {
    list.push({
      text: getAgeString(index)
    });
  }
  return list;
}

const lightStyle: IPicker.PickerStyle = {
  maskColor: 'rgba(0, 0, 0, 0.5)',
  backgroundColor: '#FEFFFF',
  selectedTextColor: '#FF0000',
  defaultTextColor: '#00FF00',
  disappearTextColor: '#0000FF',
}

@Entry
@Component
struct TextPickerExample {
  @State pickerSelectId: number = 5;
  @State pickerRange: TextCascadePickerRangeContent[] = getPickerRange(18);
  private fruits: string[] = ['apple', 'orange', 'pineapple', 'peach', 'grape', 'banana', 'watermelon']
  @State isShow: boolean = true;
  @State selected0: number = 0;
  @State selected1: number = 0;
  @State selected22: number = 0;
  @State value: string = '';
  private year: string[] = ['2023', '2024', '2025'];
  @State private month: string[] = ['1', '2', '3', '4', '5', '6', '7'];
  @State multiDate: string[][] = [this.year, this.month];
  @State strSelected1: string = '';
  @State strSelected2: string = '';
  @State selected2: number = 0;
  @State valueText: ResourceStr = $r('app.string.border_radius');
  private textWidth: number = 100;
  @State isCascade: boolean = true;
  private multipleColumnWidths1: LengthMetrics[] = [
    LengthMetrics.percent(20),
    LengthMetrics.percent(50),
    LengthMetrics.percent(50)
  ];
  private multipleColumnWidths2: LengthMetrics[] = [
    LengthMetrics.vp(100),
    LengthMetrics.vp(100),
    LengthMetrics.vp(100)
  ];

  aboutToAppear(): void {
    console.log('aboutToAppear()..')
  }

  build() {
    Column() {
      Text('基础 TextPicker')
        .fontSize(30)
        .backgroundColor(Color.Pink)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Center)


      Row() {
        Button('Visibility: ' + this.isShow)
          .onClick(() => {
            this.isShow = !this.isShow
          })
      }

      Column() {
        Row() {
          TextPicker({
            range: this.fruits,
            selected: $$this.selected0,
          })
            .width(this.textWidth)
            .canLoop(true)
            .align(Alignment.Center)
            .enableHapticFeedback(false)
            .disableTextStyleAnimation(false)
            .selectedTextStyle({ color: lightStyle.selectedTextColor, font: { size: 25, family: 'HarmonyHeiTi' } })
            .textStyle({ color: Color.Blue, font: { size: 20, weight: FontWeight.Normal, family: 'HarmonyHeiTi' } })
            .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
            .onChange((value: string | string[], index: number | number[]) => {
              console.log('value : ' + JSON.stringify(value) + ', selected : ' + JSON.stringify(index) + '\n' +
                'this.selected : ' + this.selected0 + ' this.value : ' + this.value)
            })

          TextPicker({
            range: this.fruits,
            selected: $$this.selected1,
          })
            .width(this.textWidth)
            .canLoop(true)
            .align(Alignment.Center)
            .enableHapticFeedback(false)
            .disableTextStyleAnimation(false)
            .selectedTextStyle({ color: lightStyle.selectedTextColor, font: { size: 25, family: 'HarmonyHeiTi' } })
            .textStyle({ color: Color.Blue, font: { size: 20, weight: FontWeight.Normal, family: 'HarmonyHeiTi' } })
            .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })

          TextPicker({
            range: this.fruits,
            selected: $$this.selected2,
          })
            .width(this.textWidth)
            .canLoop(true)
            .align(Alignment.Center)
            .enableHapticFeedback(false)
            .disableTextStyleAnimation(false)
            .selectedTextStyle({ color: lightStyle.selectedTextColor, font: { size: 25, family: 'HarmonyHeiTi' } })
            .textStyle({ color: Color.Blue, font: { size: 20, weight: FontWeight.Normal, family: 'HarmonyHeiTi' } })
            .disappearTextStyle({ color: Color.Red, font: { size: 15, weight: FontWeight.Lighter } })
        }
      }.alignRules({ center: { anchor: '__container__', align: VerticalAlign.Center } })
    }
    .backgroundColor('#90EE90')
    .width('100%')
    .height('100%')
  }
}
