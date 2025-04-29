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

import {
  assertEqual,
  assertFalse,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function alignRulesTest() {
  /*
   * alignRules 通用属性
   * 找到画面id为 qRCodeAlignRules1 qRCodeAlignRules2 的 QRCode 组件
   * 找到画面文本为 ButtonAlignRules1 的 Button 组件
   * 获取 qRCode1 qRCode2 两个组件中的alignRules属性
   * 将 alignRules 属性中的 anchor 属性与期望值 "__container__" 比对
   * 将 alignRules属性的 bias 中的 horizontal vertical 属性与期望值 0 比对
   * 将alignRules属性中的 align 属性与期望值 VerticalAlign.? 进行比对
   * 点击 button1 变更 qRCode1 QRCode2 的属性
   * 获取 qRCode1 组件中的 alignRules属性
   * 将 alignRules属性中的 align 属性与期望值 VerticalAlign.? 进行比对
   * */
  defineTest('alignRulesTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('alignRulesTestDemo running')
    let driver: Tester = Tester.create()
    let qRCodeAlignRules1: Component =
      await driver.findComponent(Matcher.create().id('qRCodeAlignRules1').enabled(true))
    let qRCodeAlignRules2: Component =
      await driver.findComponent(Matcher.create().id('qRCodeAlignRules2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonAlignRules1').enabled(true))
    let alignRules1: string = await qRCodeAlignRules1.getInspectorInfo()
    let alignRules2: string = await qRCodeAlignRules2.getInspectorInfo()
    assertFalse(JSON.parse(alignRules1).$attrs.alignRules == undefined)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .top
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .bottom
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .left
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .right
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .middle
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .center
      .anchor, "__container__")
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .bias
      .horizontal, 0)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .bias
      .vertical, 0)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .top
      .align, VerticalAlign.Top)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .bottom
      .align, VerticalAlign.Bottom)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .left
      .align, HorizontalAlign.Start)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .right
      .align, HorizontalAlign.End)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .middle
      .align, HorizontalAlign.Center)
    assertEqual(JSON.parse(alignRules1)
      .$attrs
      .alignRules
      .center
      .align, VerticalAlign.Center)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .top
      .align, VerticalAlign.Center)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .bottom
      .align, VerticalAlign.Center)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .left
      .align, HorizontalAlign.Center)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .right
      .align, HorizontalAlign.Center)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .middle
      .align, HorizontalAlign.End)
    assertEqual(JSON.parse(alignRules2)
      .$attrs
      .alignRules
      .center
      .align, VerticalAlign.Bottom)
    await button.tap()
    let alignRules3: string = await qRCodeAlignRules1.getInspectorInfo()
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .top
      .align, VerticalAlign.Bottom)
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .bottom
      .align, VerticalAlign.Top)
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .left
      .align, HorizontalAlign.End)
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .right
      .align, HorizontalAlign.Start)
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .middle
      .align, HorizontalAlign.Start)
    assertEqual(JSON.parse(alignRules3)
      .$attrs
      .alignRules
      .center
      .align, VerticalAlign.Top)
  }, 0)
}







