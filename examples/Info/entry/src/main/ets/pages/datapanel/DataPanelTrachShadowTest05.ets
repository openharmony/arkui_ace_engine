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
struct DataPanelTrackShadowTest05 {
  public valueArray01: number[] = [40, 40, 40]
  public valueArray02: number[] = [100]
  public shadowColors07: LinearGradient =
    new LinearGradient([{ color: '#0000ff', offset: 0 }, { color: '#a52a2a', offset: 0.5 },
      { color: '#000000', offset: 1 }])
  public shadowColors08: LinearGradient =
    new LinearGradient([{ color: '#008000', offset: 0 }, { color: '#ffa500', offset: 0.5 },
      { color: '#ffc0cb', offset: 1 }])
  public shadowColors09: LinearGradient =
    new LinearGradient([{ color: '#ff0000', offset: 0 }, { color: '#ffffff', offset: 0.5 },
      { color: '#ffff00', offset: 1 }])
  @State shadowColorsArray03: Array<LinearGradient | ResourceColor> =
    [this.shadowColors07, this.shadowColors08, this.shadowColors09]
  public shadowColors19: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorBlue'), offset: 0 },
    { color: $r('app.color.ColorBrown'), offset: 0.5 }, { color: $r('app.color.ColorBlack'), offset: 1 }])
  public shadowColors20: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])
  public shadowColors21: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorRed'), offset: 0 },
    { color: $r('app.color.ColorWhite'), offset: 0.5 }, { color: $r('app.color.ColorYellow'), offset: 1 }])
  @State shadowColorsArray07: Array<LinearGradient | ResourceColor> =
    [this.shadowColors19, this.shadowColors20, this.shadowColors21]
  public shadowColors01: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(0,128,0)', offset: 0.8 },
      { color: 'rgb(0,0,0)', offset: 0.5 }, { color: 'rgb(255,0,0)', offset: 0.2 },
      { color: 'rgb(255,255,255)', offset: 0.7 }, { color: 'rgb(255,255,0)', offset: 1 }])
  @State shadowColorsArray01: Array<LinearGradient | ResourceColor> = [this.shadowColors01]
  public shadowColors02: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(0,128,0)', offset: 1 },
      { color: 'rgb(0,0,0)', offset: 0.5 }, { color: 'rgb(255,0,0)', offset: 0.2 },
      { color: 'rgb(255,255,255)', offset: 0.7 }, { color: 'rgb(255,255,0)', offset: 0.4 }])
  @State shadowColorsArray02: Array<LinearGradient | ResourceColor> = [this.shadowColors02]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('trackShadow属性测试05').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 2 }) {
        Text('colors参数LinearGradient类型测试').fontColor(0x696969).width('95%')

        Text('LinearGradient:#ffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('35%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray03
          })

        Text('LinearGradient:$r-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('35%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray07
          })

        Text('offset断点乱序-蓝色0 绿色0.8 黑色0.5 红色0.2 白色0.7 黄色1').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray02, max: 120, type: DataPanelType.Line }).width('90%').height('3%')
          .trackShadow({
            radius: 0,
            offsetX: 30,
            offsetY: 30,
            colors: this.shadowColorsArray01
          })

        Text('offset断点乱序-蓝色0 绿色1 黑色0.5 红色0.2 白色0.7 黄色0.4')
          .fontSize(12)
          .fontColor(0x696969)
          .width('95%')
          .margin({ top: 40 })
        DataPanel({ values: this.valueArray02, max: 120, type: DataPanelType.Line }).width('90%').height('3%')
          .trackShadow({
            radius: 0,
            offsetX: 30,
            offsetY: 30,
            colors: this.shadowColorsArray02
          })

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}