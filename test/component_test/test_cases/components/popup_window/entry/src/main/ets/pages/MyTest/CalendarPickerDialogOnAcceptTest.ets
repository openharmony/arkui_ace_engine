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

export default async function calendarPickerDialogOnAcceptTest() {
  /*
  * CalendarPickerDialog弹窗 OnAccept对象说明
  * 找到id为changeButton的Button组件
  * 点击button1，弹出CalendarPickerDialog弹窗
  * 获取到text文本为'确定'的Button组件
  * 点击buttonValue,更改该按钮为文本为 'calendar onAccept'
  * 获取button1的label属性将其与期待值'calendar onAccept' 对比
  */
  defineTest('calendarPickerDialogOnAcceptTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("calendarPickerDialogOnAcceptTestDemo running")
    let driver: Tester = Tester.create()
    let button1: Component = await driver.findComponent(Matcher.create().id('changeButton').enabled(true))

    await button1.tap()
    let buttonValue: Component = await driver.findComponent(Matcher.create().text('确定').enabled(true))
    await buttonValue.tap()
    let onAccept: string = await button1.getInspectorInfo()
    assertEqual(JSON.parse(onAccept).$attrs.label, 'calendar onAccept')
  }, 0)
}