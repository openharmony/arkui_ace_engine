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
struct DataPanelValueColorsTest01 {
  public valueArray01: number[] = [10, 10, 10, 10, 10, 10, 10, 10]

  build() {
    Column({ space: 5 }) {
      Row() {
        Text('valueColors属性测试01').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }
      .height('6%')
      .width('95%')
      .borderRadius(15)
      .backgroundColor(0x7B68EE)
      .justifyContent(FlexAlign.Center)

      Column({ space: 3 }) {
        Text('ResourceColor:Color-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([Color.Blue, Color.Brown, Color.Black, Color.Green, Color.Orange, Color.Pink, Color.Red,
            Color.Yellow])

        Text('ResourceColor:number-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([0x0000ff, 0xa52a2a, 0x000000, 0x008000, 0xffa500, 0xffc0cb, 0xff0000, 0xffff00])

        Text('ResourceColor:#ffffff-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['#0000ff', '#a52a2a', '#000000', '#008000', '#ffa500', '#ffc0cb', '#ff0000', '#ffff00'])

        Text('ResourceColor:#ffffffff-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['#ff0000ff', '#ffa52a2a', '#ff000000', '#ff008000', '#ffffa500', '#ffffc0cb', '#ffff0000',
            '#ffffff00'])

        Text('ResourceColor:rgb-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['rgb(0,0,255)', 'rgb(165,42,42)', 'rgb(0,0,0)', 'rgb(0,128,0)', 'rgb(255,165,0)',
            'rgb(255,192,203)', 'rgb(255,0,0)', 'rgb(255,255,0)'])

        Text('ResourceColor:rgba-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['rgba(0,0,255,1)', 'rgba(165,42,42,1)', 'rgba(0,0,0,1)', 'rgba(0,128,0,1)', 'rgba(255,165,0,1)',
            'rgba(255,192,203,1)', 'rgba(255,0,0,1)', 'rgba(255,255,0,1)'])

        Text('ResourceColor:$r-8个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([$r('app.color.ColorBlue'), $r('app.color.ColorBrown'), $r('app.color.ColorBlack'),
            $r('app.color.ColorGreen'), $r('app.color.ColorOrange'), $r('app.color.ColorPink'),
            $r('app.color.ColorRed'), $r('app.color.ColorYellow')])

        Text('ResourceColor:Color-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([Color.Red])
        Text('ResourceColor:number-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([0xff0000])
        Text('ResourceColor:#ffffff-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['#FF0000'])
        Text('ResourceColor:#ffffffff-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['#FFFF0000'])
        Text('ResourceColor:rgb-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['rgb(255,0,0)'])
        Text('ResourceColor:rgba-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors(['rgba(255,0,0,1)'])
        Text('ResourceColor:$r-1个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line }).width('90%').height('3%')
          .valueColors([$r('app.color.ColorRed')])

        Text('多次设置最后一次生效:0x0000ff').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 80, type: DataPanelType.Line })
          .width('90%')
          .height('3%')
          .valueColors([$r('app.color.ColorBlue'), $r('app.color.ColorBrown'), $r('app.color.ColorBlack'),
            $r('app.color.ColorGreen'), $r('app.color.ColorOrange'), $r('app.color.ColorPink'),
            $r('app.color.ColorRed'), $r('app.color.ColorYellow')])
          .valueColors([$r('app.color.ColorGreen')])
          .valueColors(['rgba(30,144,255,0.5)'])
          .valueColors(['rgba(0,0,255,0.5)', 'rgba(165,42,42,0.5)', 'rgba(0,0,0,0.5)', 'rgba(0,128,0,0.5)',
            'rgba(255,165,0,0.5)', 'rgba(255,192,203,0.5)', 'rgba(255,0,0,0.5)', 'rgba(255,255,0,0.5)'])
          .valueColors(['rgb(138,43,226)'])
          .valueColors(['#FFEFD500', '#FFA07A00', '#FF69B400', '#FF000000', '#F0E68C00', '#E0FFFF00', '#ADFF2F00',
            '#6A5ACD00'])
          .valueColors(['rgb(250,255,240)', 'rgb(210,105,30)', 'rgb(124,252,0)', 'rgb(138,43,226)', 'rgb(30,144,255)',
            'rgb(0,255,0)', 'rgb(253,245,230)', 'rgb(255,192,203)'])
          .valueColors(['#E0FFFF00'])
          .valueColors([Color.Red])
          .valueColors([0xFFE4C4, 0xFF0000, 0x4169E1, 0x32CD32, 0x00FFFF, 0x0000FF, 0x8A2BE2, 0x90EE90])
          .valueColors([Color.Blue, Color.Brown, Color.Green, Color.Orange, Color.Pink, Color.Red, Color.Yellow,
            Color.Grey])
          .valueColors([0x0000ff])

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}