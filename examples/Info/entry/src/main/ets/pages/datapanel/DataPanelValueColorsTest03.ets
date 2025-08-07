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
struct DataPanelValueColorsTest03 {
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
  public color04: LinearGradient = new LinearGradient([{ color: 0x0000ff, offset: 0 }, { color: 0xa52a2a, offset: 0.5 },
    { color: 0x000000, offset: 1 }])
  public color05: LinearGradient = new LinearGradient([{ color: 0x008000, offset: 0 }, { color: 0xffa500, offset: 0.5 },
    { color: 0xffc0cb, offset: 1 }])
  public color06: LinearGradient = new LinearGradient([{ color: 0xff0000, offset: 0 }, { color: 0xffffff, offset: 0.5 },
    { color: 0xffff00, offset: 1 }])
  @State colorArray02: Array<LinearGradient | ResourceColor> = [this.color04, this.color05, this.color06]
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
  public color10: LinearGradient =
    new LinearGradient([{ color: '#ff0000ff', offset: 0 }, { color: '#ffa52a2a', offset: 0.5 },
      { color: '#ff000000', offset: 1 }])
  public color11: LinearGradient =
    new LinearGradient([{ color: '#ff008000', offset: 0 }, { color: '#ffffa500', offset: 0.5 },
      { color: '#ffffc0cb', offset: 1 }])
  public color12: LinearGradient =
    new LinearGradient([{ color: '#ffff0000', offset: 0 }, { color: '#ffffffff', offset: 0.5 },
      { color: '#ffffff00', offset: 1 }])
  @State colorArray04: Array<LinearGradient | ResourceColor> = [this.color10, this.color11, this.color12]
  public color13: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(165,42,42)', offset: 0.5 },
      { color: 'rgb(0,0,0)', offset: 1 }])
  public color14: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,128,0)', offset: 0 }, { color: 'rgb(255,165,0)', offset: 0.5 },
      { color: 'rgb(255,192,203)', offset: 1 }])
  public color15: LinearGradient =
    new LinearGradient([{ color: 'rgb(255,0,0)', offset: 0 }, { color: 'rgb(255,255,255)', offset: 0.5 },
      { color: 'rgb(255,255,0)', offset: 1 }])
  @State colorArray05: Array<LinearGradient | ResourceColor> = [this.color13, this.color14, this.color15]
  public color16: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,0,255,1)', offset: 0 }, { color: 'rgba(165,42,42,1)', offset: 0.5 },
      { color: 'rgba(0,0,0,1)', offset: 1 }])
  public color17: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,128,0,1)', offset: 0 }, { color: 'rgba(255,165,0,1)', offset: 0.5 },
      { color: 'rgba(255,192,203,1)', offset: 1 }])
  public color18: LinearGradient =
    new LinearGradient([{ color: 'rgba(255,0,0,1)', offset: 0 }, { color: 'rgba(255,255,255,1)', offset: 0.5 },
      { color: 'rgba(255,255,0,1)', offset: 1 }])
  @State colorArray06: Array<LinearGradient | ResourceColor> = [this.color16, this.color17, this.color18]
  public color19: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorBlue'), offset: 0 },
    { color: $r('app.color.ColorBrown'), offset: 0.5 }, { color: $r('app.color.ColorBlack'), offset: 1 }])
  public color20: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])
  public color21: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorRed'), offset: 0 },
    { color: $r('app.color.ColorWhite'), offset: 0.5 }, { color: $r('app.color.ColorYellow'), offset: 1 }])
  @State colorArray07: Array<LinearGradient | ResourceColor> = [this.color19, this.color20, this.color21]
  public color22: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Brown, offset: 0.5 },
      { color: Color.Black, offset: 1 }])
  @State colorArray08: Array<LinearGradient | ResourceColor> = [this.color22]
  public color23: LinearGradient = new LinearGradient([{ color: 0x0000ff, offset: 0 }, { color: 0xa52a2a, offset: 0.5 },
    { color: 0x000000, offset: 1 }])
  @State colorArray09: Array<LinearGradient | ResourceColor> = [this.color23]
  public color24: LinearGradient =
    new LinearGradient([{ color: '#0000ff', offset: 0 }, { color: '#a52a2a', offset: 0.5 },
      { color: '#000000', offset: 1 }])
  @State colorArray10: Array<LinearGradient | ResourceColor> = [this.color24]
  public color25: LinearGradient =
    new LinearGradient([{ color: '#ff0000ff', offset: 0 }, { color: '#ffa52a2a', offset: 0.5 },
      { color: '#ff000000', offset: 1 }])
  @State colorArray11: Array<LinearGradient | ResourceColor> = [this.color25]
  public color26: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(165,42,42)', offset: 0.5 },
      { color: 'rgb(0,0,0)', offset: 1 }])
  @State colorArray12: Array<LinearGradient | ResourceColor> = [this.color26]
  public color27: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,0,255,1)', offset: 0 }, { color: 'rgba(165,42,42,1)', offset: 0.5 },
      { color: 'rgba(0,0,0,1)', offset: 1 }])
  @State colorArray13: Array<LinearGradient | ResourceColor> = [this.color27]
  public color28: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorBlue'), offset: 0 },
    { color: $r('app.color.ColorBrown'), offset: 0.5 }, { color: $r('app.color.ColorBlack'), offset: 1 }])
  @State colorArray14: Array<LinearGradient | ResourceColor> = [this.color28]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('valueColors属性测试03').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 3 }) {
        Text('LinearGradient:Color-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray01)

        Text('LinearGradient:number-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray02)

        Text('LinearGradient:#ffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray03)

        Text('LinearGradient:#ffffffff-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray04)

        Text('LinearGradient:rgb-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray05)

        Text('LinearGradient:rgba-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray06)

        Text('LinearGradient:$r-3*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray07)

        Text('LinearGradient:Color-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray08)

        Text('LinearGradient:number-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray09)

        Text('LinearGradient:#ffffff-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray10)

        Text('LinearGradient:#ffffffff-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray11)

        Text('LinearGradient:rgb-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray12)

        Text('LinearGradient:rgba-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray13)

        Text('LinearGradient:$r-1*3个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(this.colorArray14)

        Text('多次设置最后一次生效:colorArray03').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 90, type: DataPanelType.Line })
          .width('90%')
          .height('3%')
          .valueColors(this.colorArray01)
          .valueColors(this.colorArray06)
          .valueColors(this.colorArray04)
          .valueColors(this.colorArray07)
          .valueColors(this.colorArray05)
          .valueColors(this.colorArray01)
          .valueColors(this.colorArray14)
          .valueColors(this.colorArray02)
          .valueColors(this.colorArray13)
          .valueColors(this.colorArray03)
      }.width('90%').height('90%')

    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}