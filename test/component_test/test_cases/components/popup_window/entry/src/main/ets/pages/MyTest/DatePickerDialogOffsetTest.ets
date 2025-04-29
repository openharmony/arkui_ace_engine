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

export default async function datePickerDialogOffsetTest() {
  /*
   * DatePickerDialog组件 Offset对象
   * 找到画面text为DatePickerDialogOffset1，DatePickerDialogOffset2，DatePickerDialogOffset3的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogOffset1的MaskRect对象与期待值{ dx: 60, dy: 60 }对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，弹出弹窗
   * 获取datePickerDialogOffset2的MaskRect对象与期待值{ dx: '300px', dy: '100px' }对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button3，变更datePickerDialogOffset3的MaskRect对象为{ dx: $r('app.string.offset_num'),
                 dy: $r('app.string.offset_num') }
   * 点击button1，弹出弹窗
   * 获取datePickerDialogOffset3的MaskRect对象与期待值{ dx: $r('app.string.offset_num'),
                 dy: $r('app.string.offset_num') }对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogOffsetTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogOffsetTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogOffset1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogOffset2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('DatePickerDialogOffset3').enabled(true))

    await button1.tap()
    let datePickerDialogOffset1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset1: string = await datePickerDialogOffset1.getInspectorInfo()
    assertEqual(JSON.parse(offset1).$attrs.offset.dX, 60)
    assertEqual(JSON.parse(offset1).$attrs.offset.dY, 60)
    await driver.tap(1, 1)

    await button2.tap()
    let datePickerDialogOffset2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset2: string = await datePickerDialogOffset2.getInspectorInfo()
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dX), '300')
    assertEqual(String(JSON.parse(offset2).$attrs.offset.dY), '100')
    await driver.tap(1, 1)

    await button3.tap()
    await button1.tap()
    let datePickerDialogOffset3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let offset3: string = await datePickerDialogOffset3.getInspectorInfo()
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dX), $r('app.string.offset_num'))
    assertEqual(String(JSON.parse(offset3).$attrs.offset.dY), $r('app.string.offset_num'))
    await driver.tap(1, 1)
  }, 0)
}