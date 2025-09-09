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

import { CustomSelectDialog } from './CustomSelectDialog';
import { LengthMetrics } from '@kit.ArkUI';

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

@Entry
@Component
struct Index {
  @State selectId: number = 12;
  @State pickerSelectId: number = 12;
  @State selectValue: Resource = getAgeString(this.pickerSelectId);
  pickerRange: TextCascadePickerRangeContent[] = getPickerRange(18);
  private apfruits: string[] = ['apple1', 'apple2', 'apple3', 'apple4']
  private orfruits: string[] = ['orange1', 'orange2', 'orange3', 'orange4']
  private multi: string[][] = [this.apfruits, this.orfruits]
  private singleColumnWidths: LengthMetrics[] = [
    LengthMetrics.percent(50)
  ];
  private multipleColumnWidths: LengthMetrics[] = [
    LengthMetrics.vp(100),
    LengthMetrics.vp(200),
    LengthMetrics.vp(100)
  ];
  private cascadeColumnWidths: LengthMetrics[] = [
    LengthMetrics.percent(20),
    LengthMetrics.percent(50),
    LengthMetrics.percent(50)
  ];
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomSelectDialog({
      title: '选择年龄',
      contentBuilder: () => {
        this.buildDownPicker()
      },
      primaryButton: {
        value: '取消',
        background: '#33F1F3F5',
        isShowBorder: true,
        action: () => {
          this.dialogController?.close();
          let timerId = setTimeout(() => {
            this.pickerSelectId = this.selectId;
            clearTimeout(timerId);
          }, 300)
        }
      },
      secondaryButton: {
        value: '确认',
        background: '#33F1F3F5',
        isShowBorder: true,
        action: async () => {
          this.dialogController?.close();
          this.selectId = this.pickerSelectId;
          this.selectValue = getAgeString(this.pickerSelectId);
        }
      }
    }),
    autoCancel: true,
    showInSubWindow: true,
    backgroundColor: '#A6ACAF',
    maskColor: '#CC000000'
  });

  aboutToDisappear(): void {
    this.dialogController = null;
  }

  @Builder
  buildDownPicker() {
    Column() {
      TextPicker({
        range: this.pickerRange,
        selected: this.pickerSelectId,
      })
        .onChange((value: string | string[], index: number | number[]) => {
          if (typeof index === 'number') {
            this.pickerSelectId = index
          }
        })
        .selectedTextStyle({ color: $r('sys.color.font_primary'), font: { size: 30, family: 'HarmonyHeiTi' } })
        .textStyle({ color: $r('sys.color.font_secondary'), font: { size: 28, family: 'HarmonyHeiTi' } })
        .canLoop(false)
        .width(306)
        .height(200)
        .alignSelf(ItemAlign.Start)
        .alignRules({ left: { anchor: '__container__', align: HorizontalAlign.Start } })
        .align(Alignment.Start)
    }
  }

  build() {
    Column({ space: 40 }) {
      Button('点击打开picker')
        .onClick(() => {
          this.dialogController?.open();
        })
      Text(this.selectValue)
    }
    .height('100%')
    .width('100%')
  }
}
