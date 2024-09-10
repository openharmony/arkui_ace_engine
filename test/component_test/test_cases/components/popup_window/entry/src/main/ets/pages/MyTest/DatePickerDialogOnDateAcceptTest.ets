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

export default async function datePickerDialogOnDateAcceptTest() {
  /*
   * DatePickerDialog组件 OnDateAccept对象
   * 找到画面text为DatePickerDialogOnDateAccept的Button组件
   * 点击button，弹出弹窗
   * 获取画面text为 确定 的Button组件
   * 点击 确定 按钮，退出弹窗
   * 变更画面文本DatePickerDialogOnDateAccept为Hello
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogOnDateAcceptTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogOnDateAcceptTestDemo running')
    let driver: Tester = Tester.create()
    let button: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogOnDateAccept').enabled(true))

    await button.tap()
    let dialog: Component = await driver.findComponent(Matcher.create().text('确定').enabled(true))
    await dialog.tap()
    let onDateAccept1: string = await button.getText()
    assertEqual(onDateAccept1, "Hello")
    await driver.tap(1, 1)
  }, 0)
}