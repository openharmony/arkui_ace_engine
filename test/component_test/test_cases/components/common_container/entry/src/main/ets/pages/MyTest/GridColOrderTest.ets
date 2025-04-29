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

import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest'

export default async function GridColOrderTest() {
  /*
   * GridCol组件 Order属性
   * 找到画面id为gridColOrder1、gridColOrder2的Order组件
   * 找到画面文本为GridColOrder的Button组件
   * 获取gridCol1的Order属性与期待值1比对
   * 获取gridCol2的Order属性与期待值2比对
   * 点击button，变更gridCol1的Order属性值为{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }
   * 获取gridCol1的Order属性与期待值{ xs: 1, sm: 2, md: 3, lg: 4, xl: 5, xxl: 6 }比对
   */
  defineTest('GridColOrderTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('gridColOrderTestDemo running')
    let driver: Tester = Tester.create()
    let gridCol1: Component = await driver.findComponent(Matcher.create().id('gridColOrder1').enabled(true))
    let gridCol2: Component = await driver.findComponent(Matcher.create().id('gridColOrder2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('GridColOrder').enabled(true))

    let order1: string = await gridCol1.getInspectorInfo()
    assertEqual(JSON.parse(order1).$attrs.order, '1')

    let order2: string = await gridCol2.getInspectorInfo()
    assertEqual(JSON.parse(order2).$attrs.order, '2')

    await button.tap()
    let order3: string = await gridCol1.getInspectorInfo()
    assertEqual(JSON.parse(order3).$attrs.order.xs, 1)
    assertEqual(JSON.parse(order3).$attrs.order.sm, 2)
    assertEqual(JSON.parse(order3).$attrs.order.md, 3)
    assertEqual(JSON.parse(order3).$attrs.order.lg, 4)
    assertEqual(JSON.parse(order3).$attrs.order.xl, 5)
    assertEqual(JSON.parse(order3).$attrs.order.xxl, 6)
  })
}