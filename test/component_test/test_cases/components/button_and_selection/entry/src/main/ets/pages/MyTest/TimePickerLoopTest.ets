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

export default async function timePickerLoopTest() {
  /*
   * TimePicker组件 Loop属性
   * 找到画面id为timePickerLoop的TimePicker组件
   * 找到画面文本为TimePickerLoop的Button组件
   * 获取timePickerLoop的Loop属性与期待值true比对
   * 点击button，变更timePickerLoop的Loop属性值为false
   * 获取timePickerLoop的Loop属性与期待值false比对
   */
  defineTest('timePickerLoopTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('timePickerLoopTestDemo running')
    let driver: Tester = Tester.create()
    let timePickerLoop: Component = await driver.findComponent(Matcher.create().id('timePickerLoop').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TimePickerLoop').enabled(true))

    let loop1: string = await timePickerLoop.getInspectorInfo()
    assertTrue(JSON.parse(loop1).$attrs.loop)

    await button.tap()
    let loop2: string = await timePickerLoop.getInspectorInfo()
    assertFalse(JSON.parse(loop2).$attrs.loop)
  }, 0)
}