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

import { LengthMetrics, router } from '@kit.ArkUI';

@Entry
@Component
struct EtsInterfaceTest {
  private dataArray: string[] = [];
  @State selectedIndex: number = 0;
  @State displayedItemCountValue: number | undefined = 7;
  @State itemHeightValue: LengthMetrics | undefined = LengthMetrics.vp(40);
  @State displayedItemCountLabel: string = '7（默认）';
  @State itemHeightLabel: string = '40vp（默认）';

  aboutToAppear(): void {
    for (let i = 1; i <= 20; i++) {
      this.dataArray.push(i.toString())
    }
  }

  private normalizeDisplayedItemCount(input: number): number {
    const defaultCount = 7;
    if (input < 2 || input > 9) {
      return defaultCount;
    }
    if (input % 2 === 0) {
      return Math.min(9, input + 1);
    }
    return input;
  }

  private setDisplayedItemCount(value: number | undefined, label: string): void {
    this.displayedItemCountValue = value;
    this.displayedItemCountLabel = label;
  }

  private setItemHeight(length: LengthMetrics | undefined, label: string): void {
    this.itemHeightValue = length;
    this.itemHeightLabel = label;
  }

  build() {
    Column({ space: 12 }) {
      Row({ space: 12 }) {
        Button('返回首页')
          .onClick(() => {
            router.back();
          })
        Text('ETS 接口测试')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .margin({ top: 8 })

      Column({ space: 8 }) {
        Row() {
          Text('displayedItemCount: ' + this.displayedItemCountLabel).fontSize(13)
          Text('归一化: ' +
            (this.displayedItemCountValue === undefined
              ? '默认值 7'
              : this.normalizeDisplayedItemCount(this.displayedItemCountValue)))
            .fontSize(13)
            .margin({ left: 12 })
        }
        .width('100%')

        Row() {
          Text('itemHeight: ' + this.itemHeightLabel).fontSize(13)
          Text('selectedIndex: ' + this.selectedIndex)
            .fontSize(13)
            .margin({ left: 12 })
        }
        .width('100%')

        UIPickerComponent({
          selectedIndex: this.selectedIndex
        }) {
          ForEach(this.dataArray, (item: string) => {
            Text(item)
          })
        }
        .onChange((selectedIndex: number) => {
          this.selectedIndex = selectedIndex
        })
        .onScrollStop((selectedIndex: number) => {
          this.selectedIndex = selectedIndex
        })
        .width('95%')
        .displayedItemCount(this.displayedItemCountValue)
        .itemHeight(this.itemHeightValue)
      }
      .width('100%')
      .padding(12)
      .borderRadius(12)
      .backgroundColor('#FFFFFF')

      Scroll() {
        Column({ space: 10 }) {
          Text('displayedItemCount')
            .fontSize(15)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 8 }) {
            Button('3').onClick(() => { this.setDisplayedItemCount(3, '3'); })
            Button('5').onClick(() => { this.setDisplayedItemCount(5, '5'); })
            Button('7').onClick(() => { this.setDisplayedItemCount(7, '7'); })
            Button('9').onClick(() => { this.setDisplayedItemCount(9, '9'); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('2').onClick(() => { this.setDisplayedItemCount(2, '2（偶数）'); })
            Button('4').onClick(() => { this.setDisplayedItemCount(4, '4（偶数）'); })
            Button('6').onClick(() => { this.setDisplayedItemCount(6, '6（偶数）'); })
            Button('8').onClick(() => { this.setDisplayedItemCount(8, '8（偶数）'); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('-3').onClick(() => { this.setDisplayedItemCount(-3, '-3'); })
            Button('0').onClick(() => { this.setDisplayedItemCount(0, '0'); })
            Button('10').onClick(() => { this.setDisplayedItemCount(10, '10'); })
            Button('99').onClick(() => { this.setDisplayedItemCount(99, '99'); })
            Button('undefined').onClick(() => { this.setDisplayedItemCount(undefined, 'undefined'); })
          }
          .width('100%')

          Text('itemHeight（越界回默认40vp）')
            .fontSize(15)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ top: 6 })

          Row({ space: 8 }) {
            Button('40vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(40), '40vp'); })
            Button('48vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(48), '48vp'); })
            Button('56vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(56), '56vp'); })
            Button('64vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(64), '64vp'); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('40px').onClick(() => { this.setItemHeight(LengthMetrics.px(40), '40px'); })
            Button('48fp').onClick(() => { this.setItemHeight(LengthMetrics.fp(48), '48fp'); })
            Button('64lpx').onClick(() => { this.setItemHeight(LengthMetrics.lpx(64), '64lpx'); })
            Button('res(48vp)').onClick(() => {
              this.setItemHeight(LengthMetrics.resource($r('app.float.picker_item_height_valid')), 'res:48vp');
            })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('-20vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(-20), '-20vp'); })
            Button('10vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(10), '10vp'); })
            Button('100vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(100), '100vp'); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('120vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(120), '120vp'); })
            Button('200px').onClick(() => { this.setItemHeight(LengthMetrics.px(200), '200px'); })
            Button('res(120vp)').onClick(() => {
              this.setItemHeight(LengthMetrics.resource($r('app.float.picker_item_height_invalid')), 'res:120vp');
            })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('undefined').onClick(() => { this.setItemHeight(undefined, 'undefined'); })
            Button('res(color)').onClick(() => {
              this.setItemHeight(LengthMetrics.resource($r('app.color.start_window_background')), 'res:color');
            })
          }
          .width('100%')
        }
        .width('100%')
        .padding(12)
        .borderRadius(12)
        .backgroundColor('#FFFFFF')
      }
      .layoutWeight(1)
      .scrollBar(BarState.Off)
      .width('100%')
    }
    .padding({ left: 12, right: 12, bottom: 12 })
    .backgroundColor('#F5F5F5')
    .height('100%')
    .width('100%')
  }
}
