/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// 测试代码路径
import scrollAttributeTest from '../MyTest/ScrollAttributeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

class MyScrollModifier implements AttributeModifier<ScrollAttribute> {
  isDark: boolean = false

  applyNormalAttribute(instance: ScrollAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

@Entry
@Component
struct ScrollAttributeSample {
  @State modifier: MyScrollModifier = new MyScrollModifier()
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    loadComponentTestEntry(scrollAttributeTest)
  }

  build() {
    Row() {
      Scroll(this.scroller) {
        Column() {
          Text('ScrollAttribute1')
            .width('90%')
            .height('40%')
            .margin({ top: 10 })
          Text('ScrollAttribute2')
            .width('90%')
            .height('40%')
            .margin({ top: 10 })
          Text('ScrollAttribute3')
            .width('90%')
            .height('40%')
            .margin({ top: 10 })
        }
      }
      .attributeModifier(this.modifier)
      .scrollable(ScrollDirection.Vertical)
      .id('scrollAttribute')
      .width('100%')
    }
    .height('100%')
  }
}