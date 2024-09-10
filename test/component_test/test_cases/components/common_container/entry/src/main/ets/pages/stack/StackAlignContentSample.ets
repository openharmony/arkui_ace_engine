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

//测试代码路径
import StackAlignContentTest from '../MyTest/StackAlignContentTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct StackAlignContentSample {
  @State alignContentStatus: Alignment = Alignment.Center

  aboutToAppear(): void {
    loadComponentTestEntry(StackAlignContentTest)
  }

  build() {
    Column() {
      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent1')
      .width('100%')
      .height(50)
      .alignContent(this.alignContentStatus)
      .margin({ bottom: "10" })

      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent2')
      .width('100%')
      .height(50)
      .alignContent(Alignment.Bottom)
      .align(Alignment.Top)
      .margin({ bottom: "10" })

      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent3')
      .width('100%')
      .height(50)
      .alignContent(Alignment.Bottom)
      .margin({ bottom: "10" })

      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent4')
      .width('100%')
      .height(50)
      .alignContent(Alignment.BottomStart)
      .margin({ bottom: "10" })

      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent5')
      .width('100%')
      .height(50)
      .alignContent(Alignment.BottomEnd)
      .margin({ bottom: "10" })

      Stack() {
        Text().width('100%').height('100%').backgroundColor(0xd2cab3)
        Text().width('70%').height('60%').backgroundColor(0xc1cbac)
      }
      .id('stackAlignContent6')
      .width('100%')
      .height(50)
      .alignContent(Alignment.End)
      .margin({ bottom: "10" })

      Button('StackAlignContent1')
        .onClick(() => {
          this.alignContentStatus = Alignment.Start
        })
      Button('StackAlignContent2')
        .onClick(() => {
          this.alignContentStatus = Alignment.TopEnd
        })
      Button('StackAlignContent3')
        .onClick(() => {
          this.alignContentStatus = Alignment.Top
        })
      Button('StackAlignContent4')
        .onClick(() => {
          this.alignContentStatus = Alignment.TopStart
        })
    }
  }
}