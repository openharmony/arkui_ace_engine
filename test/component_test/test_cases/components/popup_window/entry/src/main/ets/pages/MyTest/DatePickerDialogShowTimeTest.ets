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

export default async function datePickerDialogShowTimeTest() {
  /*
   * DatePickerDialog组件 ShowTime对象
   * 找到画面text为DatePickerDialogShowTime1，DatePickerDialogShowTime2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogShowTime的ShowTime对象与期待值true对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogShowTime的ShowTime对象为false
   * 点击button1，弹出弹窗
   * 获取datePickerDialogShowTime的ShowTime对象与期待值false对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogShowTimeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogShowTimeTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogShowTime1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogShowTime2').enabled(true))
    await button1.tap()
    let datePickerDialogShowTime1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let showTime1: string = await datePickerDialogShowTime1.getInspectorInfo()
    assertFalse(JSON.parse(showTime1).$attrs.showTime == undefined)
    assertFalse(JSON.parse(showTime1).$attrs.showTime)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogShowTime2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let showTime2: string = await datePickerDialogShowTime2.getInspectorInfo()
    assertTrue(JSON.parse(showTime2).$attrs.showTime)
    await driver.tap(1, 1)
  }, 0)
}