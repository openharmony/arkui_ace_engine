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

import { assertEqual, assertFalse, assertTrue } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function bindSheetTest_two() {
  /*
* bindSheet 通用属性
* 找到画面id为 buttonBindSheet3 buttonBindSheet4 的 Button 组件
* 找到画面文本为 ButtonBindSheet 按钮
* 获取 buttonBindSheet3 buttonBindSheet4 的属性与期望值比对
* 点击 button1 变更 buttonBindSheet3 buttonBindSheet4 的属性
* 获取 buttonBindSheet3 buttonBindSheet4 的属性与期望值比对
* */
  defineTest('bindSheetTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('bindSheetTest_twoDemo running')
    let driver: Tester = Tester.create()
    let buttonBindSheet3: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet3').enabled(true))
    let buttonBindSheet4: Component = await driver.findComponent(Matcher.create().id('buttonBindSheet4').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonBindSheet').enabled(true))
    let bindSheet1: string = await buttonBindSheet3.getInspectorInfo()
    let bindSheet2: string = await buttonBindSheet4.getInspectorInfo()
    assertFalse(JSON.parse(bindSheet1).$attrs.bindSheet == undefined)
    assertTrue(JSON.parse(bindSheet1).$attrs.bindSheet.isShow)
    assertEqual(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .option
      .preferType, SheetType.CENTER)
    assertTrue(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .option
      .showClose)
    assertTrue(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .option
      .dragBar)
    assertEqual(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .option
      .blurStyle, BlurStyle.Thin)
    assertTrue(JSON.parse(bindSheet1)
      .$attrs
      .bindSheet
      .option
      .enableOutsideInteractive)
    assertTrue(JSON.parse(bindSheet2)
      .$attrs
      .bindSheet
      .option
      .showClose)
    assertEqual(JSON.parse(bindSheet2)
      .$attrs
      .bindSheet
      .option
      .blurStyle, BlurStyle.Regular)
    await button1.tap()
    let bindSheet3: string = await buttonBindSheet3.getInspectorInfo()
    let bindSheet4: string = await buttonBindSheet4.getInspectorInfo()
    assertEqual(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .option
      .preferType, SheetType.POPUP)
    assertTrue(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .option
      .showClose)
    assertTrue(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .option
      .dragBar)
    assertEqual(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .option
      .blurStyle, BlurStyle.Thick)
    assertTrue(JSON.parse(bindSheet3)
      .$attrs
      .bindSheet
      .option
      .enableOutsideInteractive)
    assertEqual(JSON.parse(bindSheet4)
      .$attrs
      .bindSheet
      .option
      .blurStyle, BlurStyle.NONE)
  }, 0)
}