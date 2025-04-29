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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function accessibilityLevelTest() {
  /*
   * accessibilityLevel 通用属性
   * 找到画面id为 gaugeAccessibilityLevel1 blankAccessibilityLevel1 的 Gauge Blank 组件
   * 找到画面文本为 ButtonAccessibilityLevel1 ButtonAccessibilityLevel2 ButtonAccessibilityLevel3 的 Button 组件
   * 获取 gauge1 blank1 的accessibilityLevel属性与期望值 "auto" 比对
   * 点击 button1 变更 blank1 的accessibilityLevel属性与期望值"no-hide-descendants"比对
   * 点击 button2 变更 blank1 的accessibilityLevel属性与期望值"no"比对
   * 点击 button3 变更 blank1 的accessibilityLevel属性与期望值"yes"比对
   * */
  defineTest('accessibilityLevelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('accessibilityLevelTestDemo running')
    let driver: Tester = Tester.create()
    let gauge1: Component = await driver.findComponent(Matcher.create().id('gaugeAccessibilityLevel1').enabled(true))
    let blank1: Component = await driver.findComponent(Matcher.create().id('blankAccessibilityLevel1').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('ButtonAccessibilityLevel1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ButtonAccessibilityLevel2').enabled(true))
    let button3: Component =
      await driver.findComponent(Matcher.create().text('ButtonAccessibilityLevel3').enabled(true))
    let accessibilityLevel1: string = await gauge1.getInspectorInfo()
    let accessibilityLevel2: string = await blank1.getInspectorInfo()
    assertEqual(JSON.parse(accessibilityLevel1).$attrs.accessibilityLevel, "auto")
    assertEqual(JSON.parse(accessibilityLevel2).$attrs.accessibilityLevel, "auto")

    await button1.tap()
    let accessibilityLevel3: string = await blank1.getInspectorInfo()
    assertEqual(JSON.parse(accessibilityLevel3).$attrs.accessibilityLevel,
      "no-hide-descendants")

    await button2.tap()
    let accessibilityLevel4: string = await blank1.getInspectorInfo()
    assertEqual(JSON.parse(accessibilityLevel4).$attrs.accessibilityLevel, "no")

    await button3.tap()
    let accessibilityLevel5: string = await blank1.getInspectorInfo()
    assertEqual(JSON.parse(accessibilityLevel5).$attrs.accessibilityLevel, "yes")
  }, 0)
}