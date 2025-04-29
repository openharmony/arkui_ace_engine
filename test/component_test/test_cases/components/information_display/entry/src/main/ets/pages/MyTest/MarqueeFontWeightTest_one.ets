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

export default async function marqueeFontWeightTest_one() {
  /*
* Marquee组件 FontWeight属性
* 找到画面id为marqueeFontWeight1，marqueeFontWeight2， marqueeFontWeight3的Marquee组件
* 找到画面文本为MarqueeFontWeight1， MarqueeFontWeight2的Button组件
* 获取marquee1的FontWeight属性与期待值FontWeight.Normal比对
* 点击button1，变更marquee1的FontWeight属性值为FontWeight.Bold
* 获取marquee1的FontWeight属性与期待值FontWeight.Bold比对
* 获取marquee2的FontWeight属性与期待值FontWeight.Lighter比对
* 点击button2，变更marquee2的FontWeight属性值为500
* 获取marquee2的FontWeight属性与期待值500比对
* 获取marquee3的FontWeight属性与期待值'400'比对
*/
  defineTest('marqueeFontWeightTestDemo_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeFontWeightTestDemo_one running')
    let driver: Tester = Tester.create()
    let marquee1: Component = await driver.findComponent(Matcher.create().id('marqueeFontWeight1').enabled(true))
    let marquee2: Component = await driver.findComponent(Matcher.create().id('marqueeFontWeight2').enabled(true))
    let marquee3: Component = await driver.findComponent(Matcher.create().id('marqueeFontWeight3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MarqueeFontWeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MarqueeFontWeight2').enabled(true))
    let fontWeight1: string = await marquee1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Normal')
    await button1.tap()
    let fontWeight2: string = await marquee1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Bold')
    let fontWeight3: string = await marquee2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Lighter')
    await button2.tap()
    let fontWeight4: string = await marquee2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, '500')
    let fontWeight5: string = await marquee3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, '400')
  }, 0)
}