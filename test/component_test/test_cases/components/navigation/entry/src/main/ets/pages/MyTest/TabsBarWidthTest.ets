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
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function tabsBarWidthTest() {
  /*
* Tabs组件 BarWidth属性
* 找到画面id为tabsBarWidth的Tabs组件
* 找到画面文本为TabsBarWidth1、 TabsBarWidth2、 TabsBarWidth3的Button组件
* 获取tabs的BarWidth属性与期待值'100.000000'比对
* 点击button1，变更tabs的BarWidth属性值为150
* 获取tabs的BarWidth属性与期待值'150.000000'比对
* 点击button2，变更tabs的BarWidth属性值为$r("app.string.tabs_resource1")
* 获取tabs的BarWidth属性与期待值$r("app.string.tabs_resource1")比对
* 点击button3，变更tabs的BarWidth属性值为-1
* 获取tabs的BarWidth属性与期待值'360.000000'比对
*/
  defineTest('tabsBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarWidthTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsBarWidth').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsBarWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsBarWidth2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TabsBarWidth3').enabled(true))

    let barWidth1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barWidth1).$attrs.barWidth, '100.000000')
    await button1.tap()
    let barWidth2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barWidth2).$attrs.barWidth, '150.000000')
    await button2.tap()
    let barWidth3: string = await tabs.getInspectorInfo()
    assertEqual((JSON.parse(barWidth3).$attrs.barWidth), $r("app.string.tabs_resource1"))
    await button3.tap()
    let barWidth4: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barWidth4).$attrs.barWidth, '360.000000')
  }, 0)
}