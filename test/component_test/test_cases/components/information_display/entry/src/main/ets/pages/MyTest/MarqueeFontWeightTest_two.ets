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

export default async function marqueeFontWeightTest_two() {
  /*
 * Marquee组件 FontWeight属性
 * 找到画面id为marqueeFontWeight4，marqueeFontWeight5的Marquee组件
 * 找到画面文本为MarqueeFontWeight1， MarqueeFontWeight2的Button组件
 * 获取marquee4的FontWeight属性与期待值FontWeight.Medium比对
 * 点击button1，变更marquee4的FontWeight属性值为"lighter"
 * 获取marquee4的FontWeight属性与期待值"lighter"比对
 * 获取marquee5的FontWeight属性与期待值FontWeight.Regular比对
 * 点击button2，变更marquee5的FontWeight属性值为FontWeight.Bolder
 * 获取marquee5的FontWeight属性与期待值FontWeight.Bolder比对
 */
  defineTest('marqueeFontWeightTestDemo_two', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeFontWeightTestDemo_two running')
    let driver: Tester = Tester.create()
    let marquee4: Component = await driver.findComponent(Matcher.create().id('marqueeFontWeight4').enabled(true))
    let marquee5: Component = await driver.findComponent(Matcher.create().id('marqueeFontWeight5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MarqueeFontWeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MarqueeFontWeight2').enabled(true))
    let fontWeight1: string = await marquee4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Medium')
    await button1.tap()
    let fontWeight2: string = await marquee4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Lighter')
    let fontWeight3: string = await marquee5.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Regular')
    await button2.tap()
    let fontWeight4: string = await marquee5.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Bolder')
  }, 0)
}