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

export default async function navigationNavBarWidthRangeTest() {
  /*
* Navigation组件 NavBarWidthRange属性
* 找到画面id为navigationNavBarWidthRange的Navigation组件
* 找到画面文本为NavigationNavBarWidthRange的Button组件
* 获取navigation1的NavBarWidthRange属性与期待值'200.00vp, 400.00vp'比对
* 点击button1，变更navigation1的NavBarWidthRange属性值为[$r("app.float.navigation_min_width"), $r("app.float.navigation_max_width")]
* 获取navigation1的NavBarWidthRange属性与期待值[$r("app.float.navigation_min_width"), $r("app.float.navigation_max_width")]比对
*/
  defineTest('navigationNavBarWidthRangeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationNavBarWidthRangeTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component =
      await driver.findComponent(Matcher.create().id('navigationNavBarWidthRange').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('NavigationNavBarWidthRange').enabled(true))

    let navBarWidthRange1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(navBarWidthRange1).$attrs.navBarWidthRange, '200.00vp, 400.00vp')
    await button1.tap()
    let navBarWidthRange2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(navBarWidthRange2).$attrs.navBarWidthRange,
      [$r("app.float.navigation_min_width"), $r("app.float.navigation_max_width")])
  }, 0)
}