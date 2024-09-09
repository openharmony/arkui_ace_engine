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

export default async function datePickerDialogAlignmentTest() {
  /*
   * DatePickerDialog组件 Alignment对象
   * 找到画面text为DatePickerDialogAlignment1，DatePickerDialogAlignment2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment1的Alignment对象与期待值DialogAlignment.TOP对比
   * 点击坐标(650, 1050)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment2的Alignment对象为DialogAlignment.Center
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment2的Alignment对象与期待值DialogAlignment.CENTER对比
   * 点击坐标(300, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment3的Alignment对象为DialogAlignment.Bottom
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment3的Alignment对象与期待值DialogAlignment.BOTTOM对比
   * 点击坐标(300, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment4的Alignment对象为DialogAlignment.Default
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment4的Alignment对象与期待值DialogAlignment.DEFAULT对比
   * 点击坐标(300, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment5的Alignment对象为DialogAlignment.TopStart
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment5的Alignment对象与期待值DialogAlignment.TOP_START对比
   * 点击坐标(650, 1050)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment6的Alignment对象为DialogAlignment.TopEnd
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment6的Alignment对象与期待值DialogAlignment.TopEnd对比
   * 点击坐标(650, 1050)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment7的Alignment对象为DialogAlignment.CenterStart
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment7的Alignment对象与期待值DialogAlignment.CenterStart对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment8的Alignment对象为DialogAlignment.CenterEnd
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment8的Alignment对象与期待值DialogAlignment.CenterEnd对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment9的Alignment对象为DialogAlignment.BottomStart
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment9的Alignment对象与期待值DialogAlignment.BottomStart对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogAlignment10的Alignment对象为DialogAlignment.BottomEnd
   * 点击button1，弹出弹窗
   * 获取datePickerDialogAlignment10的Alignment对象与期待值DialogAlignment.BottomEnd对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogAlignmentTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogAlignmentTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogAlignment1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogAlignment2').enabled(true))

    await button1.tap()
    let datePickerDialogAlignment1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment1: string = await datePickerDialogAlignment1.getInspectorInfo()
    assertEqual(JSON.parse(alignment1).$attrs.alignment, 'DialogAlignment.TOP')
    await driver.tap(650, 1050)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment2: string = await datePickerDialogAlignment2.getInspectorInfo()
    assertEqual(JSON.parse(alignment2).$attrs.alignment, 'DialogAlignment.CENTER')
    await driver.tap(300, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment3: string = await datePickerDialogAlignment3.getInspectorInfo()
    assertEqual(JSON.parse(alignment3).$attrs.alignment, 'DialogAlignment.BOTTOM')
    await driver.tap(300, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment4: string = await datePickerDialogAlignment4.getInspectorInfo()
    assertEqual(JSON.parse(alignment4).$attrs.alignment, 'DialogAlignment.DEFAULT')
    await driver.tap(300, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment5: string = await datePickerDialogAlignment5.getInspectorInfo()
    assertEqual(JSON.parse(alignment5).$attrs.alignment, 'DialogAlignment.TOP_START')
    await driver.tap(650, 1050)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment6: string = await datePickerDialogAlignment6.getInspectorInfo()
    assertEqual(JSON.parse(alignment6).$attrs.alignment, 'DialogAlignment.TOP_END')
    await driver.tap(650, 1050)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment7: string = await datePickerDialogAlignment7.getInspectorInfo()
    assertEqual(JSON.parse(alignment7).$attrs.alignment, 'DialogAlignment.CENTER_START')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment8: string = await datePickerDialogAlignment8.getInspectorInfo()
    assertEqual(JSON.parse(alignment8).$attrs.alignment, 'DialogAlignment.CENTER_END')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment9: string = await datePickerDialogAlignment9.getInspectorInfo()
    assertEqual(JSON.parse(alignment9).$attrs.alignment, 'DialogAlignment.BOTTOM_START')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogAlignment10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let alignment10: string = await datePickerDialogAlignment10.getInspectorInfo()
    assertEqual(JSON.parse(alignment10).$attrs.alignment, 'DialogAlignment.BOTTOM_END')
    await driver.tap(1, 1)
  }, 0)
}