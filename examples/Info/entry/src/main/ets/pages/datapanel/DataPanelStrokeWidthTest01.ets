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
struct DataPanelStrokeWidthTest01 {
  public valueArray01: number[] = [20, 20, 20, 20, 20]

  build() {
    Column({ space: 5 }) {
      Row(){
        Text('strokeWidth属性测试01').fontSize(22).fontColor(0x000000).fontWeight(FontWeight.Bold)
      }.height('6%').width('95%').borderRadius(15).backgroundColor(0x7B68EE).justifyContent(FlexAlign.Center)

      Column({ space: 2 }){
        Text('strokeWidth不设置').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01 }).width('90%').height('22%')
        Text('strokeWidth("10vp")').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01 }).width('90%').height('22%')
          .strokeWidth('10vp')
        Text('strokeWidth("20abc")').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01 }).width('90%').height('22%')
          .strokeWidth('20abc')
        Text('strokeWidth("-20vp")').fontSize(12).fontColor(0x696969).width('95%')
        DataPanel({ values: this.valueArray01 }).width('90%').height('22%')
          .strokeWidth('-20vp')
      }.width('90%').height('90%')
    }.width('100%').height('100%').alignItems(HorizontalAlign.Center)
  }
}