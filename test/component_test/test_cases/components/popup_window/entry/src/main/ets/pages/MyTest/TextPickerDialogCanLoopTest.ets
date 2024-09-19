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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest';

export default async function textPickerDialogCanLoopTest() {
  /*
   * TextPickerDialog组件 CanLoop对象
   * 找到画面文本为TextPickerDialogCanLoop1,TextPickerDialogCanLoop2的Button组件
   * 点击Button1改变CanLoop对象属性为true
   * 找到可以滚动的TextPickerDialog组件
   * 获取canLoop1的CanLoop1对象属性与期待值判断是否为真
   * 点击屏幕坐标(100，100)
   * 点击Button2改变CanLoop对象属性为false
   * 找到可以滚动的TextPickerDialog组件
   * 获取canLoop2的CanLoop2对象属性与期待值判断是否为假
   * 点击屏幕坐标(100，100)
   */
  defineTest('TextPickerDialogCanLoopTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("TextPickerDialogCanLoopTestDemo running")
    let driver: Tester = Tester.create()

    let button1: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogCanLoop1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextPickerDialogCanLoop2').enabled(true))

    await button1.tap()
    let textCanLoop1: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let canLoop1: string = await textCanLoop1.getInspectorInfo()
    assertFalse(JSON.parse(canLoop1).$attrs.canLoop == undefined)
    assertTrue(JSON.parse(canLoop1).$attrs.canLoop)
    await driver.tap(100, 100)

    await button2.tap()
    let textCanLoop2: Component = await driver.findComponent(Matcher.create().type('Dialog').enabled(true))
    let canLoop2: string = await textCanLoop2.getInspectorInfo()
    assertFalse(JSON.parse(canLoop2).$attrs.canLoop)
    await driver.tap(100, 100)
  }, 0)
}