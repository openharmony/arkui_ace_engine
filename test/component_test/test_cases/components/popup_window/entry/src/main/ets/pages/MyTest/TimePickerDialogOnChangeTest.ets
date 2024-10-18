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

export default async function timePickerDialogOnChangeTest() {
  /*
   * TimePickerDialogOnChange 属性
   * 找到画面id为 timePickerDialogOnChange1 timePickerDialogOnChange2 的Text组件
   * 找到画面文本为 TimePickerDialogOnChange 的 Button 组件
   * 点击 TimePickerDialogOnChange 打开弹窗
   * 获取画面文本为 确定 的 Button 组件
   * 创建 currentDate 获取当前时间
   * 用 hours 细分获取减去一个小时后的时间
   * 将获取到的 时间 存储到 myTime 中
   * 找到画面文本为 myTime 的 文本
   * 点击 myTime 切换时间
   * 点击 确定 关闭弹窗
   * 将 hours + 1 回到正确时间
   * 获取当前分钟存到 minutes 中
   * 将 时 分 存储到 myTime 中
   * 获取 timePickerDialogOnCancel1 的属性与期望值 onChange 比对
   * 获取 timePickerDialogOnCancel2 的属性与期望值 myTime 比对
   * */
  defineTest('timePickerDialogOnChangeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogOnChangeTestDemo running')
    let driver: Tester = Tester.create()
    let timePickerDialogOnChange1: Component =
      await driver.findComponent(Matcher.create().id('timePickerDialogOnChange1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TimePickerDialogOnChange').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let rect = await timePickerDialog1.getBounds()
    let width = rect.right / 2
    let height = rect.bottom / 2
    await driver.drag(width, height, width, height + 100)
    let button2: Component = await driver.findComponent(Matcher.create().text('确定').enabled(true))
    await button2.tap()
    let timePickerDialog3: string = await timePickerDialogOnChange1.getInspectorInfo()
    assertEqual(JSON.parse(timePickerDialog3).$attrs.content, 'onChange')
  }, 0)
}