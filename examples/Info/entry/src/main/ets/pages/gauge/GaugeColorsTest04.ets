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
struct GaugeColorsTest04 {
  public color01: LinearGradient =
    new LinearGradient([{ color: Color.Blue, offset: 0 }, { color: Color.Brown, offset: 0.5 },
      { color: Color.Black, offset: 1 }])
  public color02: LinearGradient =
    new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Orange, offset: 0.5 },
      { color: Color.Pink, offset: 1 }])
  public color03: LinearGradient =
    new LinearGradient([{ color: Color.Red, offset: 0 }, { color: Color.White, offset: 0.5 },
      { color: Color.Yellow, offset: 1 }])
  @State colorArray01: Array<LinearGradient | LinearGradient> = [this.color01, this.color02, this.color03]
  public color04: LinearGradient = new LinearGradient([{ color: 0x0000ff, offset: 0 }, { color: 0xa52a2a, offset: 0.5 },
    { color: 0x000000, offset: 1 }])
  public color05: LinearGradient = new LinearGradient([{ color: 0x008000, offset: 0 }, { color: 0xffa500, offset: 0.5 },
    { color: 0xffc0cb, offset: 1 }])
  public color06: LinearGradient = new LinearGradient([{ color: 0xff0000, offset: 0 }, { color: 0xffffff, offset: 0.5 },
    { color: 0xffff00, offset: 1 }])
  @State colorArray02: Array<LinearGradient | LinearGradient> = [this.color04, this.color05, this.color06]
  public color07: LinearGradient =
    new LinearGradient([{ color: '#0000ff', offset: 0 }, { color: '#a52a2a', offset: 0.5 },
      { color: '#000000', offset: 1 }])
  public color08: LinearGradient =
    new LinearGradient([{ color: '#008000', offset: 0 }, { color: '#ffa500', offset: 0.5 },
      { color: '#ffc0cb', offset: 1 }])
  public color09: LinearGradient =
    new LinearGradient([{ color: '#ff0000', offset: 0 }, { color: '#ffffff', offset: 0.5 },
      { color: '#ffff00', offset: 1 }])
  @State colorArray03: Array<LinearGradient | LinearGradient> = [this.color07, this.color08, this.color09]
  public color10: LinearGradient =
    new LinearGradient([{ color: '#ff0000ff', offset: 0 }, { color: '#ffa52a2a', offset: 0.5 },
      { color: '#ff000000', offset: 1 }])
  public color11: LinearGradient =
    new LinearGradient([{ color: '#ff008000', offset: 0 }, { color: '#ffffa500', offset: 0.5 },
      { color: '#ffffc0cb', offset: 1 }])
  public color12: LinearGradient =
    new LinearGradient([{ color: '#ffff0000', offset: 0 }, { color: '#ffffffff', offset: 0.5 },
      { color: '#ffffff00', offset: 1 }])
  @State colorArray04: Array<LinearGradient | LinearGradient> = [this.color10, this.color11, this.color12]
  public color13: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,0,255)', offset: 0 }, { color: 'rgb(165,42,42)', offset: 0.5 },
      { color: 'rgb(0,0,0)', offset: 1 }])
  public color14: LinearGradient =
    new LinearGradient([{ color: 'rgb(0,128,0)', offset: 0 }, { color: 'rgb(255,165,0)', offset: 0.5 },
      { color: 'rgb(255,192,203)', offset: 1 }])
  public color15: LinearGradient =
    new LinearGradient([{ color: 'rgb(255,0,0)', offset: 0 }, { color: 'rgb(255,255,255)', offset: 0.5 },
      { color: 'rgb(255,255,0)', offset: 1 }])
  @State colorArray05: Array<LinearGradient | LinearGradient> = [this.color13, this.color14, this.color15]
  public color16: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,0,255,1)', offset: 0 }, { color: 'rgba(165,42,42,1)', offset: 0.5 },
      { color: 'rgba(0,0,0,1)', offset: 1 }])
  public color17: LinearGradient =
    new LinearGradient([{ color: 'rgba(0,128,0,1)', offset: 0 }, { color: 'rgba(255,165,0,1)', offset: 0.5 },
      { color: 'rgba(255,192,203,1)', offset: 1 }])
  public color18: LinearGradient =
    new LinearGradient([{ color: 'rgba(255,0,0,1)', offset: 0 }, { color: 'rgba(255,255,255,1)', offset: 0.5 },
      { color: 'rgba(255,255,0,1)', offset: 1 }])
  @State colorArray06: Array<LinearGradient | LinearGradient> = [this.color16, this.color17, this.color18]
  public color19: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorBlue'), offset: 0 },
    { color: $r('app.color.ColorBrown'), offset: 0.5 }, { color: $r('app.color.ColorBlack'), offset: 1 }])
  public color20: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorGreen'), offset: 0 },
    { color: $r('app.color.ColorOrange'), offset: 0.5 }, { color: $r('app.color.ColorPink'), offset: 1 }])
  public color21: LinearGradient = new LinearGradient([{ color: $r('app.color.ColorRed'), offset: 0 },
    { color: $r('app.color.ColorWhite'), offset: 0.5 }, { color: $r('app.color.ColorYellow'), offset: 1 }])
  @State colorArray07: Array<LinearGradient | LinearGradient> = [this.color19, this.color20, this.color21]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('Colors属性测试04').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 8 }) {
        Row({ space: 3 }) {
          Column({ space: 3 }) {
            Text('LinearGradient:ColorArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color01, 6],
                [this.color02, 7],
                [this.color03, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('LinearGradient:NumberArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color04, 6],
                [this.color05, 7],
                [this.color06, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column({ space: 3 }) {
            Text('LinearGradient:#ffffffArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color07, 6],
                [this.color08, 7],
                [this.color09, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('LinearGradient:#ffffffffArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color10, 6],
                [this.color11, 7],
                [this.color12, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:rgbArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color13, 6],
                [this.color14, 7],
                [this.color15, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:rgbaArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color16, 6],
                [this.color17, 7],
                [this.color18, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')
        }

        Row({ space: 3 }) {
          Column() {
            Text('LinearGradient:$rArr').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })
              .colors([
                [this.color19, 6],
                [this.color20, 7],
                [this.color21, 8]
              ])
              .strokeWidth(12)
              .width('90%')
              .height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:null').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })// .colors(null)
              .colors([
                [null, 6],
                [null, 7],
                [null, 8]
              ])
              .strokeWidth(12).width('90%').height('15%')
          }.width('28%')

          Column() {
            Text('LinearGradient:undefined').fontSize(12).fontColor(0x696969).width('95%')
            Gauge({ value: 50, min: 1, max: 100 })// .colors(undefined)
              .colors([
                [undefined, 6],
                [undefined, 7],
                [undefined, 8]
              ])
              .strokeWidth(12).width('90%').height('15%')
          }.width('28%')
        }
      }.width('100%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}