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

export default async function backGroundBrightnessTest() {
  /*
   * backgroundBrightness 通用属性
   * 找到画面id为 rowBackgroundBrightness1 的 Row 组件
   * 找到画面文本为 RowBackgroundBrightness1 RowBackgroundBrightness2 的 Button 组件
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性rate参数与期望值400比对
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性lightUpDegree参数与期望值-1比对
   * 点击 button1 变更 rowBackgroundBrightness1 的rate lightUpDegree属性
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性rate参数与期望值0比对
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性lightUpDegree参数与期望值0比对
   * 点击 button2 变更 rowBackgroundBrightness1 的rate lightUpDegree属性
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性rate参数与期望值999比对
   * 获取 rowBackgroundBrightness1 的backgroundBrightness属性lightUpDegree参数与期望值1比对
   * */
  defineTest('backGroundBrightnessTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('backGroundBrightnessTestDemo running')
    let driver: Tester = Tester.create()
    let rowBackgroundBrightness1: Component =
      await driver.findComponent(Matcher.create().id('rowBackgroundBrightness1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('RowBackgroundBrightness1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('RowBackgroundBrightness2').enabled(true))
    let backgroundBrightness1: string = await rowBackgroundBrightness1.getInspectorInfo()
    assertFalse(JSON.parse(backgroundBrightness1).$attrs.backgroundBrightness == undefined)
    assertEqual(JSON.parse(backgroundBrightness1)
      .$attrs
      .backgroundBrightness
      .rate, 400)
    assertEqual(JSON.parse(backgroundBrightness1)
      .$attrs
      .backgroundBrightness
      .lightUpDegree, -1)
    await button1.tap()
    let backgroundBrightness2: string = await rowBackgroundBrightness1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBrightness2)
      .$attrs
      .backgroundBrightness
      .rate, 0)
    assertEqual(JSON.parse(backgroundBrightness2)
      .$attrs
      .backgroundBrightness
      .lightUpDegree, 0)
    await button2.tap()
    let backgroundBrightness3: string = await rowBackgroundBrightness1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBrightness3)
      .$attrs
      .backgroundBrightness
      .rate, 999)
    assertEqual(JSON.parse(backgroundBrightness3)
      .$attrs
      .backgroundBrightness
      .lightUpDegree, 1)
  }, 0)
}