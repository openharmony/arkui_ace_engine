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

export default async function datePickerDialogBackgroundColorTest() {
  /*
   * DatePickerDialog组件 BackgroundColor对象
   * 找到画面text为DatePickerDialogBackgroundColor1，DatePickerDialogBackgroundColor2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundColor1的BackgroundColor对象与期待值Color.Orange对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundColor2的BackgroundColor对象为0xa52a2a
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundColor2的BackgroundColor对象与期待值0xa52a2a对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundColor3的BackgroundColor对象为'rgb(142, 255, 101)'
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundColor3的BackgroundColor对象与期待值'rgb(142, 255, 101)'对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundColor4的BackgroundColor对象为$r('sys.color.ohos_fa_palette1')
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundColor4的BackgroundColor对象与期待值$r('sys.color.ohos_fa_palette1')对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogBackgroundColor1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogBackgroundColor2').enabled(true))

    await button1.tap()
    let datePickerDialogBackgroundColor1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor1: string = await datePickerDialogBackgroundColor1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor, Color.Orange)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundColor2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor2: string = await datePickerDialogBackgroundColor2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, 0xa52a2a)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundColor3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor3: string = await datePickerDialogBackgroundColor3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, 'rgb(142, 255, 101)')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundColor4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor4: string = await datePickerDialogBackgroundColor4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, $r('sys.color.ohos_fa_palette1'))
    await driver.tap(1, 1)
  }, 0)
}