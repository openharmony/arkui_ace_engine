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

export default async function tabsDividerTest() {
  /*
* Tabs组件 Divider属性
* 找到画面id为tabsDivider1、 tabsDivider2的Tabs组件
* 找到画面文本为TabsDivider1、 TabsDivider2、 TabsDivider3的Button组件
* 获取tabs的Divider属性与期待值{ strokeWidth: '2.00vp', color: '#FFFFF000', startMargin: '0.00vp', endMargin: '0.00vp' }比对
* 点击button1，变更tabs的Divider属性值为{ strokeWidth: '50.00px', color: '#FFFF60FF', startMargin: '500.00px', endMargin: '500.00px' }
* 获取tabs的Divider属性与期待值{ strokeWidth: '50.00px', color: '#FFFF60FF', startMargin: '500.00px', endMargin: '500.00px' }比对
* 点击button2，变更tabs的Divider属性值为{ strokeWidth: $r("app.string.tabs_resource2"), color: '#FFFFA500',
* startMargin: $r("app.string.tabs_resource2"), endMargin: $r("app.string.tabs_resource2") }
* 获取tabs的Divider属性与期待值{ strokeWidth: $r("app.string.tabs_resource2"), color: '#FFFFA500',
* startMargin: $r("app.string.tabs_resource2"), endMargin: $r("app.string.tabs_resource2") }比对
* 点击button3，变更tabs的Divider属性的color值为$r('app.color.tabs_color')
* 获取tabs的Divider属性的color值与期待值$r('app.color.tabs_color')比对
* 获取tabs的Divider属性与期待值{ strokeWidth: '0.00vp', color: '#33182431', startMargin: '0.00vp', endMargin: '0.00vp' }比对
*/
  defineTest('tabsDividerTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsDividerTestDemo running')
    let driver: Tester = Tester.create()
    let tabs1: Component = await driver.findComponent(Matcher.create().id('tabsDivider1').enabled(true))
    let tabs2: Component = await driver.findComponent(Matcher.create().id('tabsDivider2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsDivider1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsDivider2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TabsDivider3').enabled(true))

    let divider1: string = await tabs1.getInspectorInfo()
    assertEqual(JSON.parse(divider1).$attrs.divider.strokeWidth, '2.00vp')
    assertEqual(JSON.parse(divider1).$attrs.divider.color, '#FFFFF000')
    assertEqual(JSON.parse(divider1).$attrs.divider.startMargin, '0.00vp')
    assertEqual(JSON.parse(divider1).$attrs.divider.endMargin, '0.00vp')
    await button1.tap()
    let divider2: string = await tabs1.getInspectorInfo()
    assertEqual(JSON.parse(divider2).$attrs.divider.strokeWidth, '50.00px')
    assertEqual(JSON.parse(divider2).$attrs.divider.color, '#FFFF60FF')
    assertEqual(JSON.parse(divider2).$attrs.divider.startMargin, '500.00px')
    assertEqual(JSON.parse(divider2).$attrs.divider.endMargin, '500.00px')
    await button2.tap()
    let divider3: string = await tabs1.getInspectorInfo()
    assertEqual(JSON.parse(divider3).$attrs.divider.strokeWidth, $r("app.string.tabs_resource2"))
    assertEqual(JSON.parse(divider3).$attrs.divider.color, '#FFFFA500')
    assertEqual(JSON.parse(divider3).$attrs.divider.startMargin, $r("app.string.tabs_resource2"))
    assertEqual(JSON.parse(divider3).$attrs.divider.endMargin, $r("app.string.tabs_resource2"))
    await button3.tap()
    let divider4: string = await tabs1.getInspectorInfo()
    assertEqual(JSON.parse(divider4).$attrs.divider.color, $r('app.color.tabs_color'))

    let divider5: string = await tabs2.getInspectorInfo()
    assertEqual(JSON.parse(divider5).$attrs.divider.strokeWidth, '0.00px')
    assertEqual(JSON.parse(divider5).$attrs.divider.color, '#33182431')
    assertEqual(JSON.parse(divider5).$attrs.divider.startMargin, '0.00px')
    assertEqual(JSON.parse(divider5).$attrs.divider.endMargin, '0.00px')
  }, 0)
}