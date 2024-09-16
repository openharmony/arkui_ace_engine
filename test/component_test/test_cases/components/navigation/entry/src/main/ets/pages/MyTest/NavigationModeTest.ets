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

export default async function navigationModeTest() {
  /*
* Navigation组件 Mode属性
* 找到画面id为navigationMode的Navigation组件
* 找到画面文本为NavigationMode1,NavigationMode2的Button组件
* 获取navigation1的Mode属性与期待值NavigationMode.Stack比对
* 点击button1，变更navigation1的Mode属性值为NavigationMode.Split
* 获取navigation1的Mode属性与期待值NavigationMode.Split比对
* 点击button2，变更navigation1的Mode属性值为NavigationMode.Auto
* 获取navigation1的Mode属性与期待值NavigationMode.Auto比对
*/
  defineTest('navigationModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationModeTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component = await driver.findComponent(Matcher.create().id('navigationMode').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationMode1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavigationMode2').enabled(true))
    let mode1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(mode1).$attrs.mode, 'NavigationMode.STACK')
    await button1.tap()
    let mode2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(mode2).$attrs.mode, 'NavigationMode.SPLIT')
    await button2.tap()
    let mode3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(mode3).$attrs.mode, 'NavigationMode.AUTO')
  }, 0)
}