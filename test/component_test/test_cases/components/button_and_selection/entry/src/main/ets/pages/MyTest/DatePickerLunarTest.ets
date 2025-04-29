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
} from '@ohos.arkui.componentTest'

export default async function datePickerLunarTest() {
  /*
   * DatePicker组件 Lunar属性
   * 找到画面id为datePickerLunar的DatePicker组件
   * 找到画面文本为DatePickerLunar的Button组件
   * 获取datePickerLunar的Lunar属性与期待值true比对
   * 点击button，变更datePickerLunar的Lunar属性值为false
   * 获取datePickerLunar的Lunar属性与期待值false比对
   */
  defineTest('datePickerLunarTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('datePickerLunarTestDemo running')
    let driver: Tester = Tester.create()
    let datePickerLunar: Component = await driver.findComponent(Matcher.create().id('datePickerLunar').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('DatePickerLunar').enabled(true))

    let lunar1: string = await datePickerLunar.getInspectorInfo()
    assertTrue(JSON.parse(lunar1).$attrs.lunar)

    await button.tap()
    let lunar2: string = await datePickerLunar.getInspectorInfo()
    assertFalse(JSON.parse(lunar2).$attrs.lunar)
  }, 0)
}