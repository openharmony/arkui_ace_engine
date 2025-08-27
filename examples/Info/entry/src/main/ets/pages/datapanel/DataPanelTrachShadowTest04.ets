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
struct DataPanelTrackShadowTest04 {
  public valueArray01: number[] = [30, 30, 30, 30]

  public colors01: Color[] = [Color.Blue, Color.Green, Color.Orange, Color.Yellow]
  public colors02: number[] = [0x0000ff,0x008000, 0xffa500, 0xffff00]

  build() {
    Column({ space: 5 }) {
      Row(){
        Text('trackShadow属性测试04').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center)

      Column({ space: 5 }){
        Text('colors参数ResourceColor类型测试').fontColor(0x696969).width('95%')
        Text('ResourceColor:Color-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('40%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors01
          })

        Text('ResourceColor:number-4个颜色值').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('40%')
          .trackShadow({
            radius: 0,
            offsetX: 10,
            offsetY: 10,
            colors: this.colors02
          })

      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}