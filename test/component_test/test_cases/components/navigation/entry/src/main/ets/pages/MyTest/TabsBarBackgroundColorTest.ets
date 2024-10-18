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

export default async function tabsBarBackgroundColorTest() {
  /*
* Tabs组件 BarBackgroundColor属性
* 找到画面id为tabsBarBackgroundColor的Tabs组件
* 找到画面文本为TabsBarBackgroundColor1、 TabsBarBackgroundColor2、 TabsBarBackgroundColor3的Button组件
* 获取tabs的BarBackgroundColor属性与期待值'#FFF1F3F5'比对
* 点击button1，变更tabs的BarBackgroundColor属性值为'#FFFFA500'
* 获取tabs的BarBackgroundColor属性与期待值'#FFFFA500'比对
* 点击button2，变更tabs的BarBackgroundColor属性值为'#FFFFF000'
* 获取tabs的BarBackgroundColor属性与期待值'#FFFFF000'比对
* 点击button3，变更tabs的BarBackgroundColor属性值为$r('app.color.tabs_color')
* 获取tabs的BarBackgroundColor属性与期待值$r('app.color.tabs_color')比对
*/
  defineTest('tabsBarBackgroundColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarBackgroundColorTestDemo running')
    let driver: Tester = Tester.create()
    let tabs: Component = await driver.findComponent(Matcher.create().id('tabsBarBackgroundColor').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsBarBackgroundColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsBarBackgroundColor2').enabled(true))
    let button3: Component = await driver.findComponent(Matcher.create().text('TabsBarBackgroundColor3').enabled(true))

    let barBackgroundColor1: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundColor1).$attrs.barBackgroundColor, '#FFF1F3F5')
    await button1.tap()
    let barBackgroundColor2: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundColor2).$attrs.barBackgroundColor, '#FFFFA500')
    await button2.tap()
    let barBackgroundColor3: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundColor3).$attrs.barBackgroundColor, '#FFFFF000')
    await button3.tap()
    let barBackgroundColor4: string = await tabs.getInspectorInfo()
    assertEqual(JSON.parse(barBackgroundColor4).$attrs.barBackgroundColor, $r('app.color.tabs_color'))
  }, 0)
}