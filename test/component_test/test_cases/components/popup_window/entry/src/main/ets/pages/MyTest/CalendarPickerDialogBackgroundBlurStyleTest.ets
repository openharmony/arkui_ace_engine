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
} from '@ohos.arkui.componentTest';

export default async function calendarPickerDialogBackgroundBlurStyleTest() {
  /*
  * CalendarPickerDialog弹窗 BackgroundBlurStyle对象说明
  * 找到画面文本为Show CalendarPicker Dialog，CalendarPickerDialogBackgroundBlurStyle的Button组件
  * 点击button1，弹出CalendarPickerDialog弹窗
  * 获取calendarPickerDialog1属性与期待值BlurStyle.Thin比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog2属性与期待值BlurStyle.Regular比对
  * 获取calendarPickerDialog2属性与期待值BlurStyle.Regular比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog3属性与期待值BlurStyle.Thick比对
  * 获取calendarPickerDialog3属性与期待值BlurStyle.Thick比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog4属性与期待值BlurStyle.BACKGROUND_THIN比对
  * 获取calendarPickerDialog4属性与期待值BlurStyle.BACKGROUND_THIN比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog5属性与期待值BlurStyle.BACKGROUND_REGULAR比对
  * 获取calendarPickerDialog5属性与期待值BlurStyle.BACKGROUND_REGULAR比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog6属性与期待值BlurStyle.BACKGROUND_THICK比对
  * 获取calendarPickerDialog6属性与期待值BlurStyle.BACKGROUND_THICK比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog7属性与期待值BlurStyle.BACKGROUND_ULTRA_THICK比对
  * 获取calendarPickerDialog7属性与期待值BlurStyle.BACKGROUND_ULTRA_THICK比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog8属性与期待值BlurStyle.NONE比对
  * 获取calendarPickerDialog8属性与期待值BlurStyle.NONE比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog9属性与期待值BlurStyle.COMPONENT_ULTRA_THIN比对
  * 获取calendarPickerDialog9属性与期待值BlurStyle.COMPONENT_ULTRA_THIN比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog10属性与期待值BlurStyle.COMPONENT_THIN比对
  * 获取calendarPickerDialog10属性与期待值BlurStyle.COMPONENT_THIN比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog11属性与期待值BlurStyle.COMPONENT_REGULAR比对
  * 获取calendarPickerDialog11属性与期待值BlurStyle.COMPONENT_REGULAR比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog12属性与期待值BlurStyle.COMPONENT_THICK比对
  * 获取calendarPickerDialog12属性与期待值BlurStyle.COMPONENT_THICK比对
  * 点击(100,100)处退出
  * 点击button2
  * 再点击button1，弹出CalendarPickerDialog弹窗
  * 变更calendarPickerDialog13属性与期待值BlurStyle.COMPONENT_ULTRA_THICK比对
  * 获取calendarPickerDialog13属性与期待值BlurStyle.COMPONENT_ULTRA_THICK比对
  * 点击(100,100)处退出
  */
  defineTest('calendarPickerDialogBackgroundBlurStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("calendarPickerDialogBackgroundBlurStyleTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('Show CalendarPicker Dialog').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('CalendarPickerDialogBackgroundBlurStyle').enabled(true))

    await button1.tap()
    let calendarPickerDialog1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle1: string = await calendarPickerDialog1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle1).$attrs.backgroundBlurStyle.value, BlurStyle.Thin)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle2: string = await calendarPickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle2).$attrs.backgroundBlurStyle, BlurStyle.Regular)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog3: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle3: string = await calendarPickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle3).$attrs.backgroundBlurStyle, BlurStyle.Thick)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog4: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle4: string = await calendarPickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle4).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_THIN)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog5: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle5: string = await calendarPickerDialog5.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle5).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_REGULAR)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog6: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle6: string = await calendarPickerDialog6.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle6).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_THICK)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog7: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle7: string = await calendarPickerDialog7.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle7).$attrs.backgroundBlurStyle, BlurStyle.BACKGROUND_ULTRA_THICK)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog8: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle8: string = await calendarPickerDialog8.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle8).$attrs.backgroundBlurStyle, BlurStyle.NONE)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog9: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle9: string = await calendarPickerDialog9.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle9).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THIN)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog10: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle10: string = await calendarPickerDialog10.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle10).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_THIN)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog11: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle11: string = await calendarPickerDialog11.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle11).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_REGULAR)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog12: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle12: string = await calendarPickerDialog12.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle12).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_THICK)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog13: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundBlurStyle13: string = await calendarPickerDialog13.getInspectorInfo()
    assertEqual(JSON.parse(backgroundBlurStyle13).$attrs.backgroundBlurStyle, BlurStyle.COMPONENT_ULTRA_THICK)
    await driver.tap(100, 100)
  }, 0)
}