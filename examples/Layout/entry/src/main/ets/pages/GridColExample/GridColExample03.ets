/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct GridColExample3 {
  @Builder
  private GridColOffsetWithExample(gridColOffset: number | GridColColumnOption | undefined | null, tip: string, bgColors: Color[]) {
    Column() {
      Text(tip).fontSize(14).fontColor(Color.Gray)
      GridRow({
        columns: 5,
        gutter: { x: 5, y: 10 },
      }) {
        ForEach(bgColors, (color: Color, index: number) => {
          GridCol() {
            Row() {
            }.width('100%').height('20vp')
          }.borderColor(color).borderWidth(2).gridColOffset(gridColOffset)
        })
      }
      .border({ color: '#880606', width: 2 })
      .width('100%')
    }
    .margin(10)
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Scroll() {
      Column() {
        Text('gridColOffset 设置相对于前一个栅格子组件偏移的列数')
          .fontSize(20).fontWeight(FontWeight.Bold)
        this.GridColOffsetWithExample(1, 'gridColOffset: 1', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample(3, 'gridColOffset: 3', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample({ xs:2, md:4, lg:8 }, 'gridColOffset: { xs:2, md:4, lg:8 }', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample({ md:4, lg:8 }, 'gridColOffset: { md:4, lg:8 }', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample(0, 'gridColOffset: 0', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample(undefined, 'gridColOffset: undefined', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample(-1, 'gridColOffset: -1', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
        this.GridColOffsetWithExample(null, 'gridColOffset: null', [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink])
      }
      .padding(16)
    }
    .width('100%')
    .height('100%')
  }
}