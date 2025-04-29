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

export default async function timePickerDialogOnAcceptTest() {
  /* TimePickerDialogOnAccept 属性
   * 找到画面id为 timePickerDialogOnAccept1 和 timePickerDialogOnAccept2 的Text组件
   * 找到画面文本为 TimePickerDialogOnAccept 的 Button 组件
   * 点击 TimePickerDialogOnAccept 打开弹窗
   * 找到画面文本为 确定 的 Button 组件
   * 点击 确定 关闭弹窗
   * 创建 currentDate 获取当前时间
   * 用 hours 和 minutes 细分获取小时分钟
   * 将获取到的时分存储到 myTime 中
   * 获取 timePickerDialogOnAccept1 的属性与期望值 onAccept 比对
   * 获取 timePickerDialogOnAccept2 的属性与期望值 myTime 比对
   */
  defineTest('timePickerDialogOnAcceptTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogOnAcceptTestDemo running')
    let driver: Tester = Tester.create()
    let timePickerDialogOnAccept1: Component =
      await driver.findComponent(Matcher.create().id('timePickerDialogOnAccept1').enabled(true))
    let timePickerDialogOnAccept2: Component =
      await driver.findComponent(Matcher.create().id('timePickerDialogOnAccept2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TimePickerDialogOnAccept').enabled(true))
    await button1.tap()
    let button2: Component = await driver.findComponent(Matcher.create().text('确定').enabled(true))
    await button2.tap()

    let currentDate = new Date();
    let hours = currentDate.getHours();
    let minutes = currentDate.getMinutes();
    let myTime: string = `${hours} : ${minutes}`;
    let timePickerDialog3: string = await timePickerDialogOnAccept1.getInspectorInfo()
    let timePickerDialog4: string = await timePickerDialogOnAccept2.getInspectorInfo()
    assertEqual(JSON.parse(timePickerDialog3).$attrs.content, 'onAccept')
    assertEqual(JSON.parse(timePickerDialog4).$attrs.content, myTime)
  }, 0)
}