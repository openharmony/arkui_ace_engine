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

export default async function checkboxGroupSelectAllTest() {
  /*
   * CheckboxGroup组件 SelectAll属性
   * 找到画面id为checkboxGroupSelectAll1，checkboxGroupSelectAll2的CheckboxGroup组件
   * 找到画面文本为CheckboxGroupSelectAll的Button组件
   * 获取checkboxGroupSelectAll1的SelectAll属性与期待值true比对
   * 获取checkboxGroupSelectAll2的SelectAll属性与期待值false比对
   * 点击button，变更checkboxGroupSelectAll1的SelectAll属性值为false
   * 获取checkboxGroupSelectAll1的SelectAll属性与期待值false比对
   */
  defineTest('checkboxGroupSelectAllTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxGroupSelectAllTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxGroupSelectAll1: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupSelectAll1').enabled(true))
    let checkboxGroupSelectAll2: Component =
      await driver.findComponent(Matcher.create().id('checkboxGroupSelectAll2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CheckboxGroupSelectAll').enabled(true))

    let selectAll1: string = await checkboxGroupSelectAll1.getInspectorInfo()
    assertTrue(JSON.parse(selectAll1).$attrs.selectAll)

    let selectAll2: string = await checkboxGroupSelectAll2.getInspectorInfo()
    assertFalse(JSON.parse(selectAll2).$attrs.selectAll)

    await button.tap()
    let selectAll3: string = await checkboxGroupSelectAll1.getInspectorInfo()
    assertFalse(JSON.parse(selectAll3).$attrs.selectAll)
  }, 0)
}