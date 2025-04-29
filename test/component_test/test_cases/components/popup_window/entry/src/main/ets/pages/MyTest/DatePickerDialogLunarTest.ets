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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function datePickerDialogLunarTest() {
  /*
   * DatePickerDialog组件 Lunar对象
   * 找到画面text为DatePickerDialogLunar1，DatePickerDialogLunar2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogLunar的Lunar对象与期待值true对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogLunar的Lunar对象为false
   * 点击button1，弹出弹窗
   * 获取datePickerDialogLunar的Lunar对象与期待值false对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogLunarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogLunarTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogLunar1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogLunar2').enabled(true))

    await button1.tap()
    let datePickerDialogLunar1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let lunar1: string = await datePickerDialogLunar1.getInspectorInfo()
    assertFalse(JSON.parse(lunar1).$attrs.lunar == undefined)
    assertTrue(JSON.parse(lunar1).$attrs.lunar)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogLunar2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let lunar2: string = await datePickerDialogLunar2.getInspectorInfo()
    assertFalse(JSON.parse(lunar2).$attrs.lunar)
    await driver.tap(1, 1)
  }, 0)
}