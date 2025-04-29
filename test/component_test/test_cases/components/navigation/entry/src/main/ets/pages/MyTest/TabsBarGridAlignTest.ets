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

export default async function tabsBarGridAlignTest() {
  /*
* Tabs组件 BarGridAlign属性
* 找到画面id为tabsBarGridAlign的Tabs组件
* 找到画面文本为TabsBarGridAlign1、 TabsBarGridAlign2的Button组件
* 获取tabs的BarGridAlign属性与期待值{ sm: '2', margin: '10.00px', gutter: '10.00px' }比对
* 点击button1，变更tabs的BarGridAlign属性值为{ md: 2, margin: '10fp', gutter: '10fp' }
* 获取tabs的BarGridAlign属性与期待值{ md: '2', margin: '10.00fp', gutter: '10.00fp' }比对
* 点击button2，变更tabs的BarGridAlign属性值为{ lg: 0, margin: '5lpx', gutter: '5lpx' }
* 获取tabs的BarGridAlign属性与期待值{ lg: '0', margin: '5.00lpx', gutter: '5.00lpx' }比对
*/
  defineTest('tabsBarGridAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarGridAlignTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsBarGridAlign').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsBarGridAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsBarGridAlign2').enabled(true))

    let barGridAlign1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barGridAlign1).$attrs.barGridAlign.sm, '2')
    assertEqual(JSON.parse(barGridAlign1).$attrs.barGridAlign.margin, '10.00px')
    assertEqual(JSON.parse(barGridAlign1).$attrs.barGridAlign.gutter, '10.00px')
    await button1.tap()
    let barGridAlign2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barGridAlign2).$attrs.barGridAlign.md, '2')
    assertEqual(JSON.parse(barGridAlign2).$attrs.barGridAlign.margin, '10.00fp')
    assertEqual(JSON.parse(barGridAlign2).$attrs.barGridAlign.gutter, '10.00fp')
    await button2.tap()
    let barGridAlign3: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barGridAlign3).$attrs.barGridAlign.lg, '0')
    assertEqual(JSON.parse(barGridAlign3).$attrs.barGridAlign.margin, '5.00lpx')
    assertEqual(JSON.parse(barGridAlign3).$attrs.barGridAlign.gutter, '5.00lpx')
  }, 0)
}