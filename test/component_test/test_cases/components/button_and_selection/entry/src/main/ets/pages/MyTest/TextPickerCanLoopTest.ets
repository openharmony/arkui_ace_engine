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

export default async function textPickerCanLoopTest() {
  /*
   * TextPicker组件 CanLoop属性
   * 找到画面id为textPickerCanLoop的TextPicker组件
   * 找到画面文本为TextPickerCanLoop的Button组件
   * 获取textPickerCanLoop的CanLoop属性与期待值true比对
   * 点击button，变更textPickerCanLoop的CanLoop属性值为false
   * 获取textPickerCanLoop的CanLoop属性与期待值false比对
   */
  defineTest('textPickerCanLoopTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textPickerCanLoopTestDemo running')
    let driver: Tester = Tester.create()
    let textPickerCanLoop: Component =
      await driver.findComponent(Matcher.create().id('textPickerCanLoop').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextPickerCanLoop').enabled(true))

    let canLoop1: string = await textPickerCanLoop.getInspectorInfo()
    assertTrue(JSON.parse(canLoop1).$attrs.canLoop)

    await button.tap()
    let canLoop2: string = await textPickerCanLoop.getInspectorInfo()
    assertFalse(JSON.parse(canLoop2).$attrs.canLoop)
  }, 0)
}