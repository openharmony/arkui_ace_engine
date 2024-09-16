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

export default async function tabsBarHeightTest() {
  /*
* Tabs组件 BarHeight属性
* 找到画面id为tabsBarHeight的Tabs组件
* 找到画面文本为TabsBarHeight1、 TabsBarHeight2、 TabsBarHeight3的Button组件
* 获取tabs的BarHeight属性与期待值'100.000000'比对
* 点击button1，变更tabs的BarHeight属性值为50
* 获取tabs的BarHeight属性与期待值'50.000000'比对
* 点击button2，变更tabs的BarHeight属性值为$r("app.string.tabs_resource1")
* 获取tabs的BarHeight属性与期待值$r("app.string.tabs_resource1")比对
* 点击button3，变更tabs的BarHeight属性值为-1
* 获取tabs的BarHeight属性与期待值'56.000000'比对
*/
  defineTest('tabsBarHeightTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarHeightTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsBarHeight').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsBarHeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsBarHeight2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TabsBarHeight3').enabled(true))

    let barHeight1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barHeight1).$attrs.barHeight, '100.000000')
    await button1.tap()
    let barHeight2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barHeight2).$attrs.barHeight, '50.000000')
    await button2.tap()
    let barHeight3: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barHeight3).$attrs.barHeight, $r("app.string.tabs_resource1"))
    await button3.tap()
    let barHeight4: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barHeight4).$attrs.barHeight, '56.000000')
  }, 0)
}