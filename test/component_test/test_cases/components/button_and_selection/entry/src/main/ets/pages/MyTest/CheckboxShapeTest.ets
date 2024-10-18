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

import { assertTrue, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function checkboxShapeTest() {
  /*
   * Checkbox组件 Shape属性
   * 找到画面id为checkboxShape的Checkbox组件
   * 找到画面文本为CheckboxShape的Button组件
   * 获取checkboxShape的shape属性与期待值CheckBoxShape.CIRCLE比对
   * 点击button，变更checkboxShape的shape属性值为CheckBoxShape.ROUNDED_SQUARE
   * 获取checkboxShape的shape属性与期待值CheckBoxShape.ROUNDED_SQUARE比对
   */
  defineTest('checkboxShapeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('checkboxShapeTestDemo running')
    let driver: Tester = Tester.create()
    let checkboxShape: Component = await driver.findComponent(Matcher.create().id('checkboxShape').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('CheckboxShape').enabled(true))

    let shape1: string = await checkboxShape.getInspectorInfo()
    assertTrue(JSON.parse(shape1).$attrs.shape == CheckBoxShape.CIRCLE)

    await button.tap()
    let shape2: string = await checkboxShape.getInspectorInfo()
    assertTrue(JSON.parse(shape2).$attrs.shape == CheckBoxShape.ROUNDED_SQUARE)
  }, 0)
}