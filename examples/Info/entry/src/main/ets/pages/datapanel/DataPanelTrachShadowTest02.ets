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
struct DataPanelTrackShadowTest02 {
  public valueArray01: number[] = [30, 30, 30, 30]

  public colors01: Color[] = [Color.Blue, Color.Green, Color.Yellow, Color.Orange]
  public colors02: number[] = [0x0000ff,0x008000, 0xffff00, 0xffa500]
  public colors03: string[] = ['#0000ff', '#008000', '#ffff00', '#ffa500']
  public colors04: string[] = ['#ff0000ff', '#ff008000', '#ffffff00', '#ffffa500']
  public colors05: string[] = ['rgb(0,0,255)', 'rgb(0,128,0)', 'rgb(255,255,0)', 'rgb(255,165,0)']
  public colors06: string[] = ['rgba(0,0,255,1)', 'rgba(0,128,0,1)', 'rgba(255,255,0,1)', 'rgba(255,165,0,1)']
  public colors07: Resource[] = [$r('app.color.ColorBlue'), $r('app.color.ColorGreen'), $r('app.color.ColorYellow'),
    $r('app.color.ColorOrange')]

  build() {
    Column({ space: 5 }) {
      Row(){
        Text('trackShadow属性测试02').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center)

      Column({ space: 7 }){
        Text('colors参数ResourceColor类型测试').fontColor(0x696969).width('95%')
        Text('ResourceColor:不设置时为默认值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
          })

        Text('ResourceColor:Color-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors01
          })

        Text('ResourceColor:number-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors02
          })

        Text('ResourceColor:#ffffff-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors03
          })

        Text('ResourceColor:#ffffffff-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors04
          })

        Text('ResourceColor:rgb-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors05
          })

        Text('ResourceColor:rgba-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors06
          })

        Text('ResourceColor:$r-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors07
          })

        Text('多次设置最后一次生效:colors: [0xFF0000]').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Line }).width('90%').height('5%')
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors02 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors05 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors01 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors07 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors03 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors04 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: this.colors06 })
          .trackShadow({ radius: 0, offsetX: 10, offsetY: 10, colors: [0xFF0000] })
      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}