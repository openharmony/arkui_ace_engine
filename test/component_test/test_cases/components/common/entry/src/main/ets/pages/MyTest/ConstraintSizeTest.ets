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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function constraintSizeTest() {
  /*
   * Row组件 ConstraintSize属性
   * 找到画面id为rowConstraintSize的Row组件
   * 找到画面text为ButtonConstraintSize的button组件
   * 获取rowConstraintSize的ConstraintSize属性与期待值
   * { minWidth: '8px', maxWidth: '10px', minHeight: '8px', maxHeight: '10px'}比较
   * 点击button，变更rowConstraintSize的ConstraintSize属性与期待值
   * { minWidth: '5.00vp', maxWidth: '10.00vp', minHeight: '5.00vp', maxHeight: '10.00vp'}比较
   * 点击button，变更rowConstraintSize的ConstraintSize属性与期待值
   * { minWidth: $r('app.string.common_length'), maxWidth: $r('app.string.common_breadth'),
   * minHeight: $r('app.string.common_length'), maxHeight: $r('app.string.common_breadth') } 比较
   */
  defineTest('constraintSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('constraintSizeTestDemo running')
    let driver: Tester = Tester.create()
    let rowConstraintSize: Component =
      await driver.findComponent(Matcher.create().id('rowConstraintSize').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonConstraintSize').enabled(true))

    let constraintSize1: string = await rowConstraintSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(constraintSize1).$attrs.constraintSize).minWidth, '8.00px')
    assertEqual(JSON.parse(JSON.parse(constraintSize1).$attrs.constraintSize).maxWidth, '10.00px')
    assertEqual(JSON.parse(JSON.parse(constraintSize1).$attrs.constraintSize).minHeight, '8.00px')
    assertEqual(JSON.parse(JSON.parse(constraintSize1).$attrs.constraintSize).maxHeight, '10.00px')

    await button.tap()
    let constraintSize2: string = await rowConstraintSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(constraintSize2).$attrs.constraintSize).minWidth, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(constraintSize2).$attrs.constraintSize).maxWidth, '10.00vp')
    assertEqual(JSON.parse(JSON.parse(constraintSize2).$attrs.constraintSize).minHeight, '5.00vp')
    assertEqual(JSON.parse(JSON.parse(constraintSize2).$attrs.constraintSize).maxHeight, '10.00vp')

    await button.tap()
    let constraintSize3: string = await rowConstraintSize.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(constraintSize3).$attrs.constraintSize).maxWidth, $r('app.string.common_length'))
    assertEqual(JSON.parse(JSON.parse(constraintSize3).$attrs.constraintSize).minWidth, $r('app.string.common_breadth'))
    assertEqual(JSON.parse(JSON.parse(constraintSize3).$attrs.constraintSize).maxHeight, $r('app.string.common_length'))
    assertEqual(JSON.parse(JSON.parse(constraintSize3).$attrs.constraintSize).minHeight,
      $r('app.string.common_breadth'))
  }, 0)
}