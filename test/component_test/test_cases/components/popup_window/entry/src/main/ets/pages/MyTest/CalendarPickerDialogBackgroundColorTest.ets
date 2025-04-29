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

export default async function calendarPickerDialogBackgroundColorTest() {
  /*
   * CalendarPickerDialog弹窗 BackgroundColor对象说明
   * 找到画面文本为Show CalendarPicker Dialog，CalendarPickerDialogBackgroundColor1的Button组件
   * 点击button1，弹出CalendarPickerDialog弹窗
   * 获取backgroundColor1属性与期待值Color.Pink比对
   * 点击空白退出
   * 点击button2
   * 点击button1，弹出CalendarPickerDialog弹窗
   * 获取backgroundColor2属性与期待值0xffff0000比对
   * 点击空白退出
   * 点击button2
   * 点击button1，弹出CalendarPickerDialog弹窗
   * 获取backgroundColor3属性与期待值'rgb(233, 100, 201)'比对
   * 点击空白退出
   * 点击button2
   * 点击button1，弹出CalendarPickerDialog弹窗
   * 获取backgroundColor4属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   * 点击空白退出
   */
  defineTest('calendarPickerDialogBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("calendarPickerDialogBackgroundColorTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('Show CalendarPicker Dialog').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('CalendarPickerDialogBackgroundColor1').enabled(true))

    await button1.tap()
    let calendarPickerDialog1: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor1: string = await calendarPickerDialog1.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor1).$attrs.backgroundColor.toLowerCase(), Color.Pink)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog2: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor2: string = await calendarPickerDialog2.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor2).$attrs.backgroundColor, 0xffff0000)
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog3: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor3: string = await calendarPickerDialog3.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor3).$attrs.backgroundColor, 'rgb(233, 100, 201)')
    await driver.tap(100, 100)

    await button2.tap()
    await button1.tap()
    let calendarPickerDialog4: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let backgroundColor4: string = await calendarPickerDialog4.getInspectorInfo()
    assertEqual(JSON.parse(backgroundColor4).$attrs.backgroundColor, $r('sys.color.ohos_id_color_text_hyperlink'))
    await driver.tap(100, 100)
  }, 0)
}