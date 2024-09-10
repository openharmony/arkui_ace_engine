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

export default async function tabsBarModeTest() {
  /*
* Tabs组件 BarMode属性
* 找到画面id为tabsBarMode1,tabsBarMode2的Tabs组件
* 找到画面文本为TabsBarMode1,TabsBarMode2的Button组件
* 获取tabs1的BarMode属性与期待值'BarMode.Fixed'比对
* 获取tabs2的BarMode属性与期待值'BarMode.Scrollable,{"margin":"10.00px","nonScrollableLayoutStyle":"LayoutStyle.ALWAYS_CENTER"}'比对
* 点击button1，变更tabs2的BarMode属性值为'BarMode.Scrollable,{"margin":"10.00vp","nonScrollableLayoutStyle":"LayoutStyle.ALWAYS_AVERAGE_SPLIT"}'
* 获取tabs2的BarMode属性与期待值'BarMode.Scrollable,{"margin":"10.00vp","nonScrollableLayoutStyle":"LayoutStyle.ALWAYS_AVERAGE_SPLIT"}'比对
* 点击button2，变更tabs2的BarMode属性值为'BarMode.Scrollable,{"margin":"10.00fp","nonScrollableLayoutStyle":"LayoutStyle.SPACE_BETWEEN_OR_CENTER"}'
* 获取tabs2的BarMode属性与期待值'BarMode.Scrollable,{"margin":"10.00fp","nonScrollableLayoutStyle":"LayoutStyle.SPACE_BETWEEN_OR_CENTER"}'比对
*/
  defineTest('tabsBarModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('tabsBarModeTestDemo running')
    let driver: Tester = Tester.create()
    let tabs1: Component = await driver.findComponent(Matcher.create().id('tabsBarMode1').enabled(true))
    let tabs2: Component = await driver.findComponent(Matcher.create().id('tabsBarMode2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TabsBarMode1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TabsBarMode2').enabled(true))

    let barMode1: string = await tabs1.getInspectorInfo()
    assertEqual(JSON.parse(barMode1).$attrs.barMode, 'BarMode.Fixed')

    let barMode2: string = await tabs2.getInspectorInfo()
    assertEqual(JSON.parse(barMode2).$attrs.barMode,
      'BarMode.Scrollable,{"margin":"10.00px","nonScrollableLayoutStyle":"LayoutStyle.ALWAYS_CENTER"}')
    await button1.tap()
    let barMode3: string = await tabs2.getInspectorInfo()
    assertEqual(JSON.parse(barMode3).$attrs.barMode,
      'BarMode.Scrollable,{"margin":"10.00vp","nonScrollableLayoutStyle":"LayoutStyle.ALWAYS_AVERAGE_SPLIT"}')

    await button2.tap()
    let barMode4: string = await tabs2.getInspectorInfo()
    assertEqual(JSON.parse(barMode4).$attrs.barMode,
      'BarMode.Scrollable,{"margin":"10.00fp","nonScrollableLayoutStyle":"LayoutStyle.SPACE_BETWEEN_OR_CENTER"}')
  }, 0)
}