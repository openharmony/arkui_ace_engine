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
struct DataPanelTrackShadowTest03 {
  public valueArray01: number[] = [40, 40, 40]
  public shadowColors01: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Brown, offset: 0.5 },
      { color: Color.Black, offset: 1 }])
  public shadowColors02: LinearGradient =
    new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Orange, offset: 0.5 },
      { color: Color.Pink, offset: 1 }])
  public shadowColors03: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.White, offset: 0.5 },
      { color: Color.Yellow, offset: 1 }])
  @State shadowColorsArray01: Array<LinearGradient | ResourceColor> =
    [this.shadowColors01, this.shadowColors02, this.shadowColors03]
  public shadowColors04: LinearGradient =
    new LinearGradient([{ color: 0x0000ff, offset: 0 }, { color: 0xa52a2a, offset: 0.5 },
      { color: 0x000000, offset: 1 }])
  public shadowColors05: LinearGradient =
    new LinearGradient([{ color: 0x008000, offset: 0 }, { color: 0xffa500, offset: 0.5 },
      { color: 0xffc0cb, offset: 1 }])
  public shadowColors06: LinearGradient =
    new LinearGradient([{ color: 0xff0000, offset: 0 }, { color: 0xffffff, offset: 0.5 },
      { color: 0xffff00, offset: 1 }])
  @State shadowColorsArray02: Array<LinearGradient | ResourceColor> =
    [this.shadowColors04, this.shadowColors05, this.shadowColors06]
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
  public shadowColors10: LinearGradient =
    new LinearGradient([{ color: '#ff0000ff', offset: 0 }, { color: '#ffa52a2a', offset: 0.5 },
      { color: '#ff000000', offset: 1 }])
  public shadowColors11: LinearGradient =
    new LinearGradient([{ color: '#ff008000', offset: 0 }, { color: '#ffffa500', offset: 0.5 },
      { color: '#ffffc0cb', offset: 1 }])
  public shadowColors12: LinearGradient =
    new LinearGradient([{ color: '#ffff0000', offset: 0 }, { color: '#ffffffff', offset: 0.5 },
      { color: '#ffffff00', offset: 1 }])
  @State shadowColorsArray04: Array<LinearGradient | ResourceColor> =
    [this.shadowColors10, this.shadowColors11, this.shadowColors12]
  public shadowColors13: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(165,42,42)', offset: 0.5 },
      { color: 'rgb(0,0,0)', offset: 1 }])
  public shadowColors14: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,128,0)', offset: 0 }, { color: 'rgb(255,165,0)', offset: 0.5 },
      { color: 'rgb(255,192,203)', offset: 1 }])
  public shadowColors15: LinearGradient =
    new LinearGradient([{ color: 'rgb(255,0,0)', offset: 0 }, { color: 'rgb(255,255,255)', offset: 0.5 },
      { color: 'rgb(255,255,0)', offset: 1 }])
  @State shadowColorsArray05: Array<LinearGradient | ResourceColor> =
    [this.shadowColors13, this.shadowColors14, this.shadowColors15]
  public shadowColors16: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,0,255,1)', offset: 0 }, { color: 'rgba(165,42,42,1)', offset: 0.5 },
      { color: 'rgba(0,0,0,1)', offset: 1 }])
  public shadowColors17: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,128,0,1)', offset: 0 }, { color: 'rgba(255,165,0,1)', offset: 0.5 },
      { color: 'rgba(255,192,203,1)', offset: 1 }])
  public shadowColors18: LinearGradient =
    new LinearGradient([{ color: 'rgba(255,0,0,1)', offset: 0 }, { color: 'rgba(255,255,255,1)', offset: 0.5 },
      { color: 'rgba(255,255,0,1)', offset: 1 }])
  @State shadowColorsArray06: Array<LinearGradient | ResourceColor> =
    [this.shadowColors16, this.shadowColors17, this.shadowColors18]
  public shadowColors19: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorBlue'), offset: 0 },
    { color: $r('app.color.ColorBrown'), offset: 0.5 }, { color: $r('app.color.ColorBlack'), offset: 1 }])
  public shadowColors20: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])
  public shadowColors21: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorRed'), offset: 0 },
    { color: $r('app.color.ColorWhite'), offset: 0.5 }, { color: $r('app.color.ColorYellow'), offset: 1 }])
  @State shadowColorsArray07: Array<LinearGradient | ResourceColor> =
    [this.shadowColors19, this.shadowColors20, this.shadowColors21]
  public shadowColors22: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Green, offset: 1 }])
  @State shadowColorsArray08: Array<LinearGradient | ResourceColor> = [this.shadowColors22]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('trackShadow属性测试03').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 7 }) {
        Text('colors参数LinearGradient类型测试').fontColor(0x696969).width('95%')
        Text('LinearGradient:不设置时为默认值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
          })

        Text('LinearGradient:Color-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray01
          })

        Text('LinearGradient:number-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray02
          })

        Text('LinearGradient:#ffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray03
          })

        Text('LinearGradient:#ffffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray04
          })

        Text('LinearGradient:rgb-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray05
          })

        Text('LinearGradient:rgba-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray06
          })

        Text('LinearGradient:$r-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray07
          })

        Text('多次设置最后一次生效:设置一组渐变色-2个颜色和2个渐变色断点').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line })
          .width('90%')
          .height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray02
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray05
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray01
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray07
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray03
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray04
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray06
          })
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.shadowColorsArray08
          })

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}