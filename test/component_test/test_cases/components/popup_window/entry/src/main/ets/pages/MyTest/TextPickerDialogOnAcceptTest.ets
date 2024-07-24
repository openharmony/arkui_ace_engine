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

export default async function textPickerDialogOnAcceptTest() {
  /*
   * TextPickerDialog组件 OnAccept对象
   * 找到画面文本为TextPickerDialogOnAccept1的Button组件
   * 找到画面中id为textPickerDialogOnAccept的文本组件
   * 点击Button1弹出弹窗
   * 找到可以滚动的TextPickerDialog组件
   * 找到画面中文本为‘确定’的按钮button2
   * 点击button2触发onAccept，更改文本内容为'apple1'
   * 获取文本的text值与期待值'apple1'比对
   */
  defineTest('textPickerDialogOnAcceptTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textPickerDialogOnAcceptTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component =
      await driver.findComponent(Matcher.create().text('TextPickerDialogOnAccept').enabled(true))

    await button1.tap()
    let textPickerDialog: Component =
      await driver.findComponent(Matcher.create().id('textPickerDialogOnAccept').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('确定').enabled(true))
    await button2.tap()
    let OnAccept: string = await textPickerDialog.getText()
    assertEqual(OnAccept, 'apple1')
  }, 0)
}