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

@Entry
@Component
struct Complicate {
  @State items: TextCascadePickerRangeContent[] = [];
  @State tip: string = '';

  async refreshData() {
    this.items = [];
    this.tip = '开始计算';
    setTimeout(() => {
      const arr: TextCascadePickerRangeContent[] = [];
      for (let index = 1900; index < 2150; index++) {
        const subArr: TextCascadePickerRangeContent[] = [];
        const content: TextCascadePickerRangeContent = {
          text: `${index}年`,
          children: subArr
        }
        for (let j = 1; j <= 12; j++) {
          const dayArr: TextCascadePickerRangeContent[] = [];
          subArr.push({
            text: `${j}月`,
            children: dayArr
          })
          for (let i = 1; i <= 30; i++) {
            dayArr.push({
              text: `${i}日`
            })
          }
        }
        arr.push(content);
      }
      this.tip = '渲染完成'
      this.items = arr;
    }, 10);
  }

  build() {
    Column() {
      Column({ space: 10 }) {
        Text(this.tip)
      }
      .alignItems(HorizontalAlign.Center)
      .justifyContent(FlexAlign.End)
      .layoutWeight(1)

      TextPicker({ range: this.items }) {

      }
      .width('100%')
      .height(250)
      .defaultPickerItemHeight(50)
      .canLoop(false)

      Blank().height(40)

      Button('刷新数据')
        .onClick(() => {
          this.refreshData();
        })
      Blank().layoutWeight(1)
    }
    .alignItems(HorizontalAlign.Center)
    .justifyContent(FlexAlign.Center)
    .width('100%')
    .height('100%')
  }
}
