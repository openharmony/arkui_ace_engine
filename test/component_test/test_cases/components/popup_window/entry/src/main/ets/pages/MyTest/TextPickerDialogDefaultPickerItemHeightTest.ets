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

export default async function textPickerDialogDefaultPickerItemHeightTest() {
  /*
   * TextPickerDialog组件 DefaultPickerItemHeight对象
   * 找到画面文本为TextPickerDialogDefaultPickerItemHeight1,TextPickerDialogDefaultPickerItemHeight2的Button组件
   * 点击Button1改变DefaultPickerItemHeight对象属性为50
   * 找到可以滚动的TextPickerDialog组件
   * 获取defaultPickerItemHeight1的DefaultPickerItemHeight对象属性与期待值50比对
   * 点击屏幕坐标(100，100)
   * 点击Button2改变DefaultPickerItemHeight对象属性为'20'
   * 找到可以滚动的TextPickerDialog组件
   * 获取defaultPickerItemHeight2的DefaultPickerItemHeight对象属性与期待值'20'比对
   * 点击屏幕坐标(100，100)
   */
  defineTest('textPickerDialogDefaultPickerItemHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogDefaultPickerItemHeightTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogDefaultPickerItemHeight1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogDefaultPickerItemHeight2').enabled(true))

    await button1.tap()
    let textDefaultPickerItemHeight1: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let defaultPickerItemHeight1: string = await textDefaultPickerItemHeight1.getInspectorInfo()
    assertFalse(JSON.parse(defaultPickerItemHeight1).$attrs.defaultPickerItemHeight == undefined)
    assertEqual(JSON.parse(defaultPickerItemHeight1).$attrs.defaultPickerItemHeight, 50)
    await driver.tap(100, 100)

    await button2.tap()
    let textDefaultPickerItemHeight2: Component =
      await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let defaultPickerItemHeight2: string = await textDefaultPickerItemHeight2.getInspectorInfo()
    assertEqual(JSON.parse(defaultPickerItemHeight2).$attrs.defaultPickerItemHeight, '20')
    await driver.tap(100, 100)

  }, 0)
}