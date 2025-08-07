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

/*用例描述
  本用例通过调整索引条高度和索引项尺寸体现自适应折叠模式的自适应效果。
*/

@Entry
@Component
struct AutoCollapseSample {
  private arrayA: string[] = ['安']
  private arrayB: string[] = ['卜', '白', '包', '毕', '丙']
  private arrayC: string[] = ['曹', '成', '陈', '催']
  private arrayJ: string[] = ['嘉', '贾']
  private value: string[] = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z']
  @State isNeedAutoCollapse: boolean | undefined = undefined;
  @State indexerHeight: string | number | undefined = undefined;
  @State selectedIndex: number = 0;
  @State itemHeight: number | undefined = undefined

  build() {
    Column() {
      // 开启或关闭自适应折叠模式
      Button('autoCollapse: ' + this.isNeedAutoCollapse)
        .margin('5vp')
        .onClick(() => {
          this.isNeedAutoCollapse = !this.isNeedAutoCollapse;
        })

      // 设置索引项尺寸大小itemSize
      Column() {
        Text('itemSize: ' + this.itemHeight?.toString())
        Slider({ min: 5, max: 50, value: 16 }).onChange((value: number) => {
          this.itemHeight = value
        })
      }

      // 设置索引条高度
      Column() {
        Text('height: ' + this.indexerHeight?.toString())
        Slider({ min: 50, max: 800, value: 200 }).onChange((value: number) => {
          this.indexerHeight = value
        })
      }

      // 设置选中索引项
      Column() {
        Text('selectedIndex: ' + this.selectedIndex?.toString())
        Slider({ min: -1, max: 30, value: 0 }).onChange((value: number) => {
          this.selectedIndex = value
        })
      }

      AlphabetIndexer({ arrayValue: this.value, selected: this.selectedIndex!! })
        .autoCollapse(this.isNeedAutoCollapse)
        .height(this.indexerHeight)
        .selectedColor(0xFFFFFF)// 选中项文本颜色
        .popupColor(0xFFFAF0)// 弹出框文本颜色
        .selectedBackgroundColor(0xCCCCCC)// 选中项背景颜色
        .popupBackground(0xD2B48C)// 弹出框背景颜色
        .usingPopup(true)// 是否显示弹出框
        .selectedFont({ size: 16, weight: FontWeight.Bolder })// 选中项字体样式
        .popupFont({ size: 24, weight: FontWeight.Bolder })// 弹出框内容的字体样式
        .itemSize(this.itemHeight)// 每一项的尺寸大小
        .alignStyle(IndexerAlign.Right)// 弹出框在索引条左侧弹出
        .popupTitleBackground('#D2B48C')// 弹出框首个索引项背板颜色
        .popupSelectedColor(0x00FF00)
        .popupUnselectedColor(0x0000FF)
        .popupItemFont({ size: 30, style: FontStyle.Normal })
        .popupItemBackgroundColor(0xCCCCCC)
        .onSelect((index: number) => {
          console.info(this.value[index] + ' ' + this.selectedIndex + ' Selected!');
        })
        .onRequestPopupData((index: number) => {
          console.info('onRequestPopupData:' + index);
          if (this.value[index] == 'A') {
            return this.arrayA;
          } else if (this.value[index] == 'B') {
            return this.arrayB;
          } else if (this.value[index] == 'C') {
            return this.arrayC;
          } else if (this.value[index] == 'J') {
            return this.arrayJ;
          } else {
            return [];
          }
        })
        .onPopupSelect((index: number) => {
          console.info('onPopupSelected:' + index);
        })
    }
  }
}