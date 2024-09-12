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

export default async function navigationNavBarWidthTest() {
  /*
* Navigation组件 NavBarWidth属性
* 找到画面id为navigationNavBarWidth的Navigation组件
* 找到画面文本为NavigationNavBarWidth1,NavigationNavBarWidth2的Button组件
* 获取navigation1的NavBarWidth属性与期待值'200.00vp'比对
* 点击button1，变更navigation1的NavBarWidth属性值为'150.00px'
* 获取navigation1的NavBarWidth属性与期待值'150.00px'比对
* 点击button2，变更navigation1的NavBarWidth属性值为$r("app.string.navigation_nav_width")
* 获取navigation1的NavBarWidth属性与期待值$r("app.string.navigation_nav_width")比对
*/
  defineTest('navigationNavBarWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationNavBarWidthTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component = await driver.findComponent(Matcher.create().id('navigationNavBarWidth').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('NavigationNavBarWidth1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('NavigationNavBarWidth2').enabled(true))
    let navBarWidth1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(navBarWidth1).$attrs.navBarWidth, '200.00vp')
    await button1.tap()
    let navBarWidth2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(navBarWidth2).$attrs.navBarWidth, '150.00px')
    await button2.tap()
    let navBarWidth3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(navBarWidth3).$attrs.navBarWidth, $r("app.string.navigation_nav_width"))
  }, 0)
}