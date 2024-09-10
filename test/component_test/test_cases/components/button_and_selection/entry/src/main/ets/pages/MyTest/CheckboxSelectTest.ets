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

export default async function checkboxSelectTest() {
  /*
   * Checkbox组件 Select属性
   * 找到画面id为checkboxSelect的Checkbox组件
   * 找到画面文本为CheckboxSelect的Button组件
   * 获取checkboxSelect的select属性与期待值true比对
   * 点击button，变更checkboxSelect的Select属性值为false
   * 获取checkboxSelect的select属性与期待值false比对
   */
  defineTest('checkboxSelectTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxSelectTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxSelect: Component = await driver.findComponent(Matcher.create().id('checkboxSelect').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CheckboxSelect').enabled(true))

    let select1: string = await checkboxSelect.getInspectorInfo()
    assertTrue(JSON.parse(select1).$attrs.select)

    await button.tap()
    let select2: string = await checkboxSelect.getInspectorInfo()
    assertFalse(JSON.parse(select2).$attrs.select)
  }, 0)
}