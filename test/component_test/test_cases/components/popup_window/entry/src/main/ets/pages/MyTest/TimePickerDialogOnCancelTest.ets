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

export default async function timePickerDialogOnCancelTest() {
  /* TimePickerDialogOnAccept 属性
   * 找到画面id为 timePickerDialogOnCancel 的Text组件
   * 找到画面文本为 TimePickerDialogOnCancel 的 Button 组件
   * 点击 TimePickerDialogOnCancel 打开弹窗
   * 找到画面文本为 取消 的 Button 组件
   * 点击 取消 关闭弹窗
   * 获取 timePickerDialogOnCancel 的属性与期望值 onCancel 比对
   */
  defineTest('timePickerDialogOnCancelTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogOnCancelTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('TimePickerDialogOnCancel').enabled(true))
    await button1.tap()
    let button2: Component = await driver.findComponent(Matcher.create().text('取消').enabled(true))
    await button2.tap()
    let timePickerDialogOnCancel: Component =
      await driver.findComponent(Matcher.create().id('timePickerDialogOnCancel').enabled(true))
    let timePickerDialog: string = await timePickerDialogOnCancel.getInspectorInfo()
    assertEqual(JSON.parse(timePickerDialog).$attrs.content, 'onCancel')
  }, 0)
}