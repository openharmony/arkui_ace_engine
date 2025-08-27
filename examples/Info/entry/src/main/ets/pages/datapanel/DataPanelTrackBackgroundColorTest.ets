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
struct DataPanelTrackBackgroundColorTest {
  public valueArray01: number[] = [10, 10, 10, 10, 10, 10, 10, 10, 10]

  build() {
    Column({ space: 5 }) {
      Row(){
        Text('trackBackgroundColor属性测试').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center)

      Column({ space: 4 }){
        Text('trackBackgroundColor:Color.Yellow').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor(Color.Yellow)

        Text('trackBackgroundColor:0xFFFF00').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor(0xFFFF00)

        Text('trackBackgroundColor："#FFFF00"').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor('#FFFF00')

        Text('trackBackgroundColor:"rgb(255,255,0)"').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor('rgb(255,255,0)')

        Text('trackBackgroundColor:"rgba(255,255,0,0.5)"').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor('rgba(255,255,0,0.5)')

        Text('trackBackgroundColor：$r("app.color.ColorYellow")').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor($r('app.color.ColorYellow'))

        Text('多次设置最后一次生效:Color.Blue').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor(Color.Yellow)
          .trackBackgroundColor($r('app.color.ColorYellow'))
          .trackBackgroundColor(0xFFFF00)
          .trackBackgroundColor('rgba(255,255,0,0.5)')
          .trackBackgroundColor('#FFFF00')
          .trackBackgroundColor('rgb(255,255,0)')
          .trackBackgroundColor(Color.Blue)

        Text('backgroundColor:Color.Red').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('4%')
          .trackBackgroundColor(Color.Yellow)
          .backgroundColor(Color.Red)
          .border({width: 1, color:Color.Black })

        Text('backgroundColor:Color.Red').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('30%')
          .trackBackgroundColor(Color.Yellow)
          .backgroundColor(Color.Red)

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}