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
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function timePickerDialogBackgroundBlurStyleTest() {
  /*
   * TimePickerDialog.show 的 backgroundBlurStyle 属性
   * 获取文本为 TimePickerDialogBackgroundBlurStyle 的按钮，点击打开弹窗
   * 获取 scrollable 可滑动的组件 命名为 timePickerDialog1
   * 获取 timePickerDialog1 的值与 BlurStyle.Thin 比对
   * 点击组件外部回到主页
   * 以此类推将 backgroundBlurStyle 测完
   */
  defineTest('timePickerDialogBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerDialogBackgroundBlurStyleTestDemo running')
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TimePickerDialogBackgroundBlurStyle').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('ClickToggleBackgroundBlurStyle').enabled(true))
    await button1.tap()
    let timePickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle1: string = await timePickerDialog1.getInspectorInfo()
    assertTrue(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value == 'BlurStyle.NONE')
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value, 'BlurStyle.THIN')

    await driver.tap(1, 1)
    await button2.tap()
    await button1.tap()
    let timePickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle2: string = await timePickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.backgroundBlurStyle.value, 'BlurStyle.REGULAR')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle3: string = await timePickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.backgroundBlurStyle.value, 'BlurStyle.THICK')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle4: string = await timePickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_THIN')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle5: string = await timePickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_REGULAR')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    assertFalse(timePickerDialog1 == null)
    let backgroundBlurStyle6: string = await timePickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_THICK')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle7: string = await timePickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.backgroundBlurStyle.value, 'BlurStyle.BACKGROUND_ULTRA_THICK')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle8: string = await timePickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle8).$attrs.backgroundBlurStyle.value, ' BlurStyle.NONE')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle9: string = await timePickerDialog9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_ULTRA_THIN')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle10: string = await timePickerDialog10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_THIN')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog11: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle11: string = await timePickerDialog11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_REGULAR')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog12: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle12: string = await timePickerDialog12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_THICK')
    await driver.tap(1, 1)

    await button2.tap()
    await button1.tap()
    let timePickerDialog13: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle13: string = await timePickerDialog13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.backgroundBlurStyle.value, 'BlurStyle.COMPONENT_ULTRA_THICK')
    await driver.tap(1, 1)
  }, 0)
}