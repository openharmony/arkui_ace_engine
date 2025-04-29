/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import alignSelfTest from '../MyTest/AlignSelfTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlignSelfSample {
  @State alignSelfCenter: ItemAlign = ItemAlign.Center

  aboutToAppear(): void {
    loadComponentTestEntry(alignSelfTest)
  }

  build() {
    Column() {
      Text('alignSelf').fontSize(15).fontColor(0xCCCCCC).width('90%')
      Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
        Text('alignSelf Baseline')
          .id('textAlignSelf1')
          .alignSelf(ItemAlign.Baseline)
          .width('33%')
          .height(70)
          .backgroundColor(0xF5DEB3)
          .textAlign(TextAlign.Center)
        Text('alignSelf End')
          .id('textAlignSelf2')
          .alignSelf(ItemAlign.End)
          .width('33%')
          .height(70)
          .backgroundColor(0xD2B48C)
          .textAlign(TextAlign.Center)
        Text('alignSelf Center')
          .id('textAlignSelf3')
          .alignSelf(this.alignSelfCenter)
          .width('33%')
          .height(70)
          .backgroundColor(0xD2B48C)
          .textAlign(TextAlign.End)
        Button('ButtonAlignSelf1')
          .onClick(() => {
            this.alignSelfCenter = ItemAlign.Auto
          })
        Button('ButtonAlignSelf2')
          .onClick(() => {
            this.alignSelfCenter = ItemAlign.Start
          })
        Button('ButtonAlignSelf3')
          .onClick(() => {
            this.alignSelfCenter = ItemAlign.Stretch
          })
      }.width('90%').height(120).padding(10).backgroundColor(0xAFEEEE)
    }.width('100%').margin({ top: 5 })
  }
}

