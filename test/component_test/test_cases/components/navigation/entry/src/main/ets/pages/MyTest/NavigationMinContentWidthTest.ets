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

export default async function navigationMinContentWidthTestTest() {
  /*
* Navigation组件 MinContentWidth属性
* 找到画面id为navigationMinContentWidth的Navigation组件
* 找到画面文本为NavigationMinContentWidth1,NavigationMinContentWidth2的Button组件
* 获取navigation1的MinContentWidth属性与期待值'300.00vp'比对
* 点击button1，变更navigation1的MinContentWidth属性值为'10.00lpx'
* 获取navigation1的MinContentWidth属性与期待值'10.00lpx'比对
* 点击button2，变更navigation1的MinContentWidth属性值为'5.00fp'
* 获取navigation1的MinContentWidth属性与期待值'5.00fp'比对
*/
  defineTest('navigationMinContentWidthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("navigationMinContentWidthTestDemo running")
    let driver: Tester = Tester.create()
    let navigation1: Component =
      await driver.findComponent(Matcher.create().id('navigationMinContentWidth').enabled(true))
    let button1: Component =
      await driver.findComponent(Matcher.create().text('NavigationMinContentWidth1').enabled(true))
    let button2: Component =
      await driver.findComponent(Matcher.create().text('NavigationMinContentWidth2').enabled(true))
    let minContentWidth1: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth1).$attrs.minContentWidth, '300.00vp')
    await button1.tap()
    let minContentWidth2: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth2).$attrs.minContentWidth, '10.00lpx')
    await button2.tap()
    let minContentWidth3: string = await navigation1.getInspectorInfo()
    assertEqual(JSON.parse(minContentWidth3).$attrs.minContentWidth, '5.00fp')
  }, 0)
}