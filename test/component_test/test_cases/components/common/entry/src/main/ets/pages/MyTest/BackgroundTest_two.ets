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

export default async function backgroundTest_two() {
  /*
   * background 通用属性
   * 找到画面id为 rowBackground3 的 Row 容器
   * 找到画面文本为 ButtonBackground1 ButtonBackground2 ButtonBackground3 的Button组件
   * 获取 rowBackground3 的属性
   * rowBackground3 的 background.options.align 与期望值 Alignment.TopStart 比对
   * 点击 button1 变更 rowBackground3 的属性
   * 获取 rowBackground3 的属性
   * rowBackground3 的 background.options.align 与期望值 Alignment.TopEnd 比对
   * 点击 button2 变更 rowBackground3 的属性
   * 获取 rowBackground3 的属性
   * rowBackground3 的 background.options.align 与期望值 Alignment.Start 比对
   * 点击 button3 变更 rowBackground3 的属性
   * 获取 rowBackground3 的属性
   * rowBackground3 的 background.options.align 与期望值 Alignment.Center 比对
   * */
  defineTest('backgroundTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('ackgroundTest_twoDemo running')
    let driver: Tester = Tester.create()
    let rowBackground3: Component = await driver.findComponent(Matcher.create().id('rowBackground3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBackground1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('ButtonBackground2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('ButtonBackground3').enabled(true))

    let background1: string = await rowBackground3.getInspectorInfo()
    assertFalse(JSON.parse(background1).$attrs.background == undefined)
    assertEqual(JSON.parse(background1).$attrs.background.align, 'Alignment.TopStart')

    await button1.tap()
    let background2: string = await rowBackground3.getInspectorInfo()
    assertEqual(JSON.parse(background2).$attrs.background.align, 'Alignment.TopEnd')

    await button2.tap()
    let background3: string = await rowBackground3.getInspectorInfo()
    assertEqual(JSON.parse(background3).$attrs.background.align, 'Alignment.Start')

    await button3.tap()
    let background4: string = await rowBackground3.getInspectorInfo()
    assertEqual(JSON.parse(background4).$attrs.background.align, 'Alignment.Center')
  }, 0)
}