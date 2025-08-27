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
struct DataPanelValueColorsTest04 {
  public valueArray01: number[] = [30, 30, 30]
  public color01: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Brown, offset: 0.5 },
      { color: Color.Black, offset: 1 }])
  public color02: LinearGradient =
    new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Orange, offset: 0.5 },
      { color: Color.Pink, offset: 1 }])
  public color03: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.White, offset: 0.5 },
      { color: Color.Yellow, offset: 1 }])
  @State colorArray01: Array<LinearGradient | ResourceColor> = [this.color01, this.color02, this.color03]
  public color07: LinearGradient =
    new LinearGradient([{ color: '#0000ff', offset: 0 }, { color: '#a52a2a', offset: 0.5 },
      { color: '#000000', offset: 1 }])
  public color08: LinearGradient =
    new LinearGradient([{ color: '#008000', offset: 0 }, { color: '#ffa500', offset: 0.5 },
      { color: '#ffc0cb', offset: 1 }])
  public color09: LinearGradient =
    new LinearGradient([{ color: '#ff0000', offset: 0 }, { color: '#ffffff', offset: 0.5 },
      { color: '#ffff00', offset: 1 }])
  @State colorArray03: Array<LinearGradient | ResourceColor> = [this.color07, this.color08, this.color09]
  public color29: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Black, offset: 0.3 },
      { color: Color.Green, offset: 0.6 }, { color: Color.Orange, offset: 0.8 }, { color: Color.Red, offset: 1 }])
  @State colorArray15: Array<LinearGradient | ResourceColor> = [this.color29]
  public color30: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Black, offset: 1 },
      { color: Color.Green, offset: 0.2 }, { color: Color.Orange, offset: 0.8 }, { color: Color.Red, offset: 0.6 }])
  @State colorArray16: Array<LinearGradient | ResourceColor> = [this.color30]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('valueColors属性测试04').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 3 }) {

        Text('LinearGradient:Color-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Circle }).width('90%').height('35%')
          .valueColors(this.colorArray01)

        Text('LinearGradient:#ffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Circle }).width('90%').height('35%')
          .valueColors(this.colorArray03)

        Text('offset断点乱序-蓝色0 黑色0.3 绿色0.6 橙色0.8 红色1').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: [100], max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .valueColors(this.colorArray15)

        Text('offset断点乱序-蓝色0 黑色1 绿色0.2 橙色0.8 红色0.6').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: [100], max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .valueColors(this.colorArray16)

      }.width('90%').height('90%')

      // .backgroundColor(0xE6E6FA)
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}