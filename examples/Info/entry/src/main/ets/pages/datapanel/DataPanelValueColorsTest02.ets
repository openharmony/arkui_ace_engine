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
struct DataPanelValueColorsTest02 {
  public valueArray01: number[] = [10, 10, 10, 10, 10, 10, 10, 10]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('valueColors属性测试02').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 5 }) {
        Text('ResourceColor:Color-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Circle }).width('90%').height('40%')
          .valueColors([Color.Blue, Color.Brown, Color.Black, Color.Green, Color.Orange, Color.Pink, Color.Red,
            Color.Yellow])

        Text('ResourceColor:$r-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Circle }).width('90%').height('40%')
          .valueColors([$r('app.color.ColorBlue'), $r('app.color.ColorBrown'), $r('app.color.ColorBlack'),
            $r('app.color.ColorGreen'), $r('app.color.ColorOrange'), $r('app.color.ColorPink'),
            $r('app.color.ColorRed'), $r('app.color.ColorYellow')])

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}