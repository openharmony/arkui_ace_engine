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

export default async function datePickerDialogOnCancelTest() {
  /*
   * DatePickerDialog组件 OnCancel对象
   * 找到画面text为DatePickerDialogOnCancel的Button组件
   * 找到画面id为onCancel的text组件
   * 点击button，弹出弹窗
   * 获取画面text为 取消 的Button组件
   * 点击 取消 按钮，退出弹窗
   * 变更画面文本DatePickerDialogOnCancel为Hello
   * 获取text的参数content与期待值'Hello'比对
   */

  defineTest('datePickerDialogOnCancelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogOnCancelTestDemo running')
    let driver: Tester = Tester.create()
    let button: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogOnCancel').enabled(true))
    await button.tap()
    let button2: Component = await driver.findComponent(Matcher.create().text('取消').enabled(true))
    await button2.tap()
    let text: Component = await driver.findComponent(Matcher.create().id('onCancel').enabled(true))
    let onCancel: string = await text.getText()
    assertEqual(onCancel, "Hello")
  }, 0)
}