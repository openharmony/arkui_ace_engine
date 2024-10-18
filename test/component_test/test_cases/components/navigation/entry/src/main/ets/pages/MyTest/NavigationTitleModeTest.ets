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

export default async function navigationTitleModeTest() {
  /*
* Navigation组件 TitleMode属性
* 找到画面id为navigationTitleMode的Navigation组件
* 找到画面文本为NavigationNavBarWidth1,NavigationNavBarWidth2的Button组件
* 获取navigation1的TitleMode属性与期待值NavigationTitleMode.Free比对
* 点击button1，变更navigation1的TitleMode属性值为NavigationTitleMode.Full
* 获取navigation1的TitleMode属性与期待值NavigationTitleMode.Full比对
* 点击button2，变更navigation1的TitleMode属性值为NavigationTitleMode.Mini
* 获取navigation1的TitleMode属性与期待值NavigationTitleMode.Mini比对
*/
  defineTest('navigationTitleModeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationTitleModeTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component = await driver.findComponent(Matcher.create().id('navigationTitleMode').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationTitleMode1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavigationTitleMode2').enabled(true))
    let titleMode1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(titleMode1).$attrs.titleMode, 'NavigationTitleMode.Free')
    await button1.tap()
    let titleMode2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(titleMode2).$attrs.titleMode, 'NavigationTitleMode.Full')
    await button2.tap()
    let titleMode3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(titleMode3).$attrs.titleMode, 'NavigationTitleMode.Mini')
  }, 0)
}