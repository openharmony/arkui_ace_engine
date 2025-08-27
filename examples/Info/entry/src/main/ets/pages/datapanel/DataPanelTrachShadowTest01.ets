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
struct DataPanelTrackShadowTest01 {
  public valueArray01: number[] = [ 50, 50 ]

  build() {
    Column({ space: 5 }) {
      Row(){
        Text('trackShadow属性测试01').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center).margin({ bottom: 10 })
      Column({ space: 15 }){
        Text('radius参数测试').fontColor(0x696969).width('95%')

        Text('radius: 不设置时为默认值20vp').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: 40 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: 40,
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: 0 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: 0,
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: -40 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: -40,
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: $r("app.string.string_value_40") ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: $r('app.string.string_value_40'),
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: $r("app.float.float_value_40") ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: $r('app.float.float_value_40'),
            colors:  [Color.Blue, Color.Green]
          })

        Text('radius: $r("app.integer.integer_value_40") ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: $r('app.integer.integer_value_40'),
            colors:  [Color.Blue, Color.Green]
          })

        Text('多次设置最后一次生效: 40 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, type: DataPanelType.Line }).width('90%').height('4%')
          .trackShadow({
            radius: $r('app.integer.integer_value_40'),
            colors:  [Color.Blue, Color.Green]
          })
          .trackShadow({
            radius: $r('app.string.string_value_40'),
            colors:  [Color.Blue, Color.Green]
          })
          .trackShadow({
            radius: $r('app.float.float_value_40'),
            colors:  [Color.Blue, Color.Green]
          })
          .trackShadow({
            radius: -40,
            colors:  [Color.Blue, Color.Green]
          })
          .trackShadow({
            radius: 0,
            colors:  [Color.Blue, Color.Green]
          })
          .trackShadow({
            radius: 40,
            colors:  [Color.Blue, Color.Green]
          })
      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}