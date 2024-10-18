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

export default async function textPickerDialogOnChangeTest() {
  /*
   * 找到画面文本为TextPickerDialogOnChange的Button组件
   * 点击Button弹出弹窗
   * 点击页面位置(550, 1227)触发onChange，将文本值更改为’TextPickerDialogOnChange‘
   * 找到画面id为textPickerDialogOnChangeText的Text组件
   * 获取文本的text值与期待值'TextPickerDialogOnChange'比对
   */
  defineTest('textPickerDialogOnChangeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogOnChangeTestDemo running")
    let driver: Tester = Tester.create()
    let button: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogOnChange').enabled(true))

    await button.tap()
    await driver.tap(550, 1227)
    let text: Component = await driver.findComponent(Matcher.create().id('textPickerDialogOnChangeText').enabled(true))
    let onChange: string = await text.getText()
    assertEqual(onChange, 'TextPickerDialogOnChange')
  }, 0)
}