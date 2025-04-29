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
struct DataPanelLevel1_0 {
  @State clip1: boolean = false
  public color1: LinearGradient =
    new LinearGradient([{ color: '#ffeca908', offset: -10 }, { color: 'rgba(49, 239, 16, 1.00)', offset: 11 }])
  public color2: LinearGradient = new LinearGradient([{ color: '#FF67F9D4', offset: '0.6' },
    { color: '#FFFF9554', offset: $r('app.string.string_float') }])
  public color3: LinearGradient =
    new LinearGradient([{ color: $r('app.color.green'), offset: 0.5 }, { color: Color.Blue, offset: 0.11 },
      { color: '#ffeca908', offset: -10 }])
  public color4: LinearGradient =
    new LinearGradient([{ color: 0xff747aec, offset: 0.01 }, { color: 0xffe554f, offset: 0.3 }])
  public colorShadow1: LinearGradient =
    new LinearGradient([{ color: '#65EEC9A3', offset: 0 }, { color: '#65EF629F', offset: 1 }])
  public colorShadow2: LinearGradient =
    new LinearGradient([{ color: $r('app.color.yellow'), offset: 0 }, { color: 0x65efbd0, offset: 10 }])
  public colorShadow3: LinearGradient =
    new LinearGradient([{ color: '#6572B513', offset: 0 }, { color: '#6508efa6', offset: 0.41 }])
  public colorShadow4: LinearGradient =
    new LinearGradient([{ color: '#65ed08f5', offset: 0 }, { color: '#65ef0849', offset: 1 }])
  @State shadowColorArray1: Array<LinearGradient | ResourceColor> =
    [this.colorShadow1, this.colorShadow2, this.colorShadow3, this.colorShadow4]
  @State colorArray1: Array<LinearGradient | ResourceColor> = [this.color1, this.color2, '#00FF00', '#20FF0000']
  @State values: number[] = [20, 20, 20, 20]
  @State trackBackgroundColor: string = '#ff000000'

  build() {
    Scroll() {
      Column() {
        Scroll() {
          Column() {
            Text('DataPanel组件 布局及剪裁规则测试')
              .fontSize(12)
              .fontColor(Color.Black)
              .width('100%')
              .margin({ top: 10 })
            Text('DataPanel组件设置宽高且设置LinearGradient样式')
              .fontSize(9)
              .fontColor(0xCCCCCC)
              .width('100%')
              .margin({ top: 10, bottom: 10 })
            DataPanel({ values: [20, 20, 20, 20], max: 100, type: DataPanelType.Circle })
              .width(200)
              .height(300)
              .borderWidth(1)
              .key('datapanel1')
              .valueColors(this.colorArray1)
              .trackShadow({
                colors: this.shadowColorArray1,
                offsetX: 15,
                offsetY: 15
              })
              .strokeWidth(30)
              .trackBackgroundColor(this.trackBackgroundColor)
              .closeEffect(true)
              .backgroundColor(Color.Gray)
              .align(Alignment.Top)
              .onClick(() => {
                this.colorArray1 = [this.color3, '#ffffdd00', '#ed0686f3', this.color4]
                this.shadowColorArray1 = [this.colorShadow3, this.colorShadow2, this.colorShadow4, this.colorShadow1]
                this.trackBackgroundColor = '#ff0d26fa'
              })
            Text('DataPanel组件设置宽高且设置LinearGradient样式   clip: ' + this.clip1)
              .key('clip')
              .fontSize(9)
              .width('100%')
              .margin({ top: 10, bottom: 10 })
              .onClick(() => {
                this.clip1 = !this.clip1
              })
            DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
              .width(200)
              .aspectRatio(2)
              .borderWidth(1)
              .clip(this.clip1)
              .key('datapanel2')
              .valueColors(this.colorArray1)
              .trackShadow({
                colors: this.shadowColorArray1,
                offsetX: 15,
                offsetY: 15
              })
              .strokeWidth(30)
              .trackBackgroundColor('#08182431')
              .closeEffect(true)
              .backgroundColor(Color.Orange)
              .borderRadius(50)
              .onAppear(() => {
                console.log('hbx datapanel onAppear')
              })
              .onDisAppear(() => {
                console.log('hbx datapanel onDisAppear')
              })
            Text('DataPanel组件不设置宽高').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
            Column() {
              DataPanel({ values: [10, 10, 10, 10], max: 150, type: DataPanelType.Circle })
                .borderWidth(1)
                .borderStyle(BorderStyle.Dotted)
                .trackBackgroundColor($r('app.color.blue'))
                .closeEffect(true)
                .align(Alignment.Bottom)
            }.width(200).height(200).backgroundColor(Color.Pink)

            Text('DataPanel组件不设置宽高父容器为scroll').fontSize(9).width('100%').margin({ top: 10, bottom: 10 })
            Scroll() {
              DataPanel({ values: [10, 10, 10, 10], max: 150, type: DataPanelType.Circle })
                .borderWidth(1)
                .borderStyle(BorderStyle.Dotted)
                .trackBackgroundColor($r('app.color.blue'))
                .closeEffect(true)
                .align(Alignment.Bottom)
            }.scrollBar(BarState.Off)
          }
        }
        .width('100%')
        .height('100%')
        .borderWidth(1)
        .borderColor(Color.Green)
        .scrollBar(BarState.Off)
      }
    }.scrollBar(BarState.Off)
  }
}