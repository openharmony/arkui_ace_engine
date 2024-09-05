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

export default async function datePickerDialogBackgroundBlurStyleTest() {
  /*
   * DatePickerDialog组件 BackgroundBlurStyle对象
   * 找到画面text为DatePickerDialogBackgroundBlurStyle1，DatePickerDialogBackgroundBlurStyle2的Button组件
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle1的BackgroundBlurStyle对象与期待值BlurStyle.Thin对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle2的BackgroundBlurStyle对象为BlurStyle.Regular
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle2的BackgroundBlurStyle对象与期待值BlurStyle.Regular对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle3的BackgroundBlurStyle对象为BlurStyle.Thick
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle3的BackgroundBlurStyle对象与期待值BlurStyle.Thick对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle4的BackgroundBlurStyle对象为BlurStyle.BACKGROUND_THIN
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle4的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_THIN对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle5的BackgroundBlurStyle对象为BlurStyle.BACKGROUND_REGULAR
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle5的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_REGULAR对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle6的BackgroundBlurStyle对象为BlurStyle.BACKGROUND_THICK
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle6的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle7的BackgroundBlurStyle对象为BlurStyle.BACKGROUND_ULTRA_THICK
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle7的BackgroundBlurStyle对象与期待值BlurStyle.BACKGROUND_ULTRA_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle8的BackgroundBlurStyle对象为BlurStyle.NONE
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle8的BackgroundBlurStyle对象与期待值BlurStyle.NONE对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle9的BackgroundBlurStyle对象为BlurStyle.COMPONENT_ULTRA_THIN
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle9的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_ULTRA_THIN对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle10的BackgroundBlurStyle对象为BlurStyle.COMPONENT_THIN
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle10的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_THIN对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle11的BackgroundBlurStyle对象为BlurStyle.COMPONENT_REGULAR
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle11的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_REGULAR对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle12的BackgroundBlurStyle对象为BlurStyle.COMPONENT_THICK
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle12的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   * 点击button2，变更datePickerDialogBackgroundBlurStyle13的BackgroundBlurStyle对象为BlurStyle.COMPONENT_ULTRA_THICK
   * 点击button1，弹出弹窗
   * 获取datePickerDialogBackgroundBlurStyle13的BackgroundBlurStyle对象与期待值BlurStyle.COMPONENT_ULTRA_THICK对比
   * 点击坐标(1, 1)，退出弹窗
   */

  defineTest('datePickerDialogBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerDialogBackgroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogBackgroundBlurStyle1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('DatePickerDialogBackgroundBlurStyle2').enabled(true))
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle1: string = await datePickerDialogBackgroundBlurStyle1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value, BlurStyle.Thin)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle2: string = await datePickerDialogBackgroundBlurStyle2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.backgroundBlurStyle, BlurStyle.Regular)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle3: string = await datePickerDialogBackgroundBlurStyle3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.backgroundBlurStyle, BlurStyle.Thick)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle4: string = await datePickerDialogBackgroundBlurStyle4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_THIN)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle5: string = await datePickerDialogBackgroundBlurStyle5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_REGULAR)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle6: string = await datePickerDialogBackgroundBlurStyle6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_THICK)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle7: string = await datePickerDialogBackgroundBlurStyle7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_ULTRA_THICK)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle8: string = await datePickerDialogBackgroundBlurStyle8.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle8).$attrs.backgroundBlurStyle, BlurStyle.NONE)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle9: string = await datePickerDialogBackgroundBlurStyle9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THIN)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle10: string = await datePickerDialogBackgroundBlurStyle10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_THIN)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle11: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle11: string = await datePickerDialogBackgroundBlurStyle11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_REGULAR)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle12: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle12: string = await datePickerDialogBackgroundBlurStyle12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_THICK)
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let datePickerDialogBackgroundBlurStyle13: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle13: string = await datePickerDialogBackgroundBlurStyle13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THICK)
    await driver.tap(1, 1)
  }, 0)
}