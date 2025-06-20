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
struct DataPanelTrackShadowTest08 {
  public valueArray01: number[] = [40, 40, 40]
  public trackShadowColors01: Color[] = [Color.Blue, Color.Yellow, Color.Green]
  
  build() {
    Column({ space: 5 }) {
      Row(){
        Text('trackShadow属性测试08').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center)

      Column({ space: 2 }){
        Text('offsetX:设置为number 40 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('30%')
          .trackShadow({
            radius: 0,
            colors: this.trackShadowColors01,
            offsetX: 40
          })

        Text('offsetY:设置为number -40 ').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('30%')
          .trackShadow({
            radius: 0,
            colors: this.trackShadowColors01,
            offsetY: -40
          })

        Text('offsetX: 40 , offsetY: -40').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01, max: 120, type: DataPanelType.Circle }).width('90%').height('30%')
          .trackShadow({
            radius: 0,
            colors: this.trackShadowColors01,
            offsetX: 40,
            offsetY: -40
          })
      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}