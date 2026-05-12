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
struct ItemHeightDividerComboTest {
  private dataArray: string[] = [];
  @State selectedIndex: number = 0;
  @State itemHeightValue: LengthMetrics | undefined = LengthMetrics.vp(40);
  @State itemHeightLabel: string = '40vp（默认）';
  @State itemHeightVpValue: number = 40;
  @State strokeWidthValue: LengthMetrics = LengthMetrics.vp(1);
  @State strokeWidthLabel: string = '1vp（默认）';

  aboutToAppear(): void {
    for (let i = 1; i <= 20; i++) {
      this.dataArray.push(i.toString())
    }
  }

  private setItemHeight(value: LengthMetrics | undefined, label: string, vpValue: number = 40): void {
    this.itemHeightValue = value;
    this.itemHeightLabel = label;
    this.itemHeightVpValue = vpValue;
  }

  private setStrokeWidth(value: LengthMetrics, label: string): void {
    this.strokeWidthValue = value;
    this.strokeWidthLabel = label;
  }

  build() {
    Column({ space: 12 }) {
      Row({ space: 12 }) {
        Button('返回首页')
          .onClick(() => {
            router.back();
          })
        Text('itemHeight + divider.strokeWidth 组合测试')
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .margin({ top: 8 })

      Column({ space: 8 }) {
        Text('itemHeight: ' + this.itemHeightLabel)
          .fontSize(13)
          .width('100%')
        Text('selectionIndicator.divider.strokeWidth: ' + this.strokeWidthLabel)
          .fontSize(13)
          .width('100%')

        UIPickerComponent({
          selectedIndex: this.selectedIndex
        }) {
          ForEach(this.dataArray, (item: string) => {
            Text(item)
              .width('100%')
              .border({color: Color.Black, width: 1})
          })
        }
        .onChange((selectedIndex: number) => {
          this.selectedIndex = selectedIndex
        })
        .onScrollStop((selectedIndex: number) => {
          this.selectedIndex = selectedIndex
        })
        .width('95%')
        .itemHeight(this.itemHeightValue)
        .selectionIndicator({
          type: PickerIndicatorType.DIVIDER,
          strokeWidth: this.strokeWidthValue,
          startMargin: LengthMetrics.vp(20)
        })
      }
      .width('100%')
      .padding(12)
      .borderRadius(12)
      .backgroundColor('#FFFFFF')

      Scroll() {
        Column({ space: 10 }) {
          Text('动态修改 itemHeight')
            .fontSize(15)
            .fontWeight(FontWeight.Medium)
            .width('100%')

          Row({ space: 8 }) {
            Button('40vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(40), '40vp', 40); })
            Button('56vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(56), '56vp', 56); })
            Button('64vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(64), '64vp', 64); })
            Button('undefined').onClick(() => { this.setItemHeight(undefined, 'undefined', 40); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('-20vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(-20), '-20vp（异常）', -20); })
            Button('10vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(10), '10vp（异常）', 10); })
            Button('120vp').onClick(() => { this.setItemHeight(LengthMetrics.vp(120), '120vp（异常）', 120); })
          }
          .width('100%')

          Text('动态修改 strokeWidth（最小/最大/异常）')
            .fontSize(15)
            .fontWeight(FontWeight.Medium)
            .width('100%')
            .margin({ top: 6 })

          Row({ space: 8 }) {
            Button('最小: 0vp').onClick(() => { this.setStrokeWidth(LengthMetrics.vp(0), '0vp（最小）'); })
            Button('最大: 100vp').onClick(() => { this.setStrokeWidth(LengthMetrics.vp(100), '100vp（最大）'); })
            Button('1/2 itemHeight').onClick(() => {
              this.setStrokeWidth(
                LengthMetrics.vp(this.itemHeightVpValue / 2),
                (this.itemHeightVpValue / 2) + 'vp（itemHeight/2）'
              );
            })
            Button('默认: 1vp').onClick(() => { this.setStrokeWidth(LengthMetrics.vp(1), '1vp（默认）'); })
          }
          .width('100%')

          Row({ space: 8 }) {
            Button('异常: -1vp').onClick(() => { this.setStrokeWidth(LengthMetrics.vp(-1), '-1vp（异常）'); })
            Button('异常: 9999vp').onClick(() => { this.setStrokeWidth(LengthMetrics.vp(9999), '9999vp（异常）'); })
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
