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

export default async function textClockFontWeightTestOne() {
  /*
  * TextClock组件 FontWeight属性
  * 找到画面id为textClockFontWeight1，textClockFontWeight2，textClockFontWeight3的TextClock组件
  * 找到画面文本为TextClockFontWeight1，TextClockFontWeight2的Button组件
  * 获取textClock1的FontWeight属性与期待值500比对
  * 获取textClock2的FontWeight属性与期待值FontWeight.Normal比对
  * 获取textClock3的FontWeight属性与期待值FontWeight.Lighter比对
  * 点击button1，变更textClockFont1的FontWeight属性值为"lighter"
  * 获取textClock1的FontStyle属性与期待值"lighter"比对
  * 点击button2，变更textClock1的FontWeight属性值为FontWeight.Bold
  * 获取textClock1的FontStyle属性与期待值FontWeight.Bold比对
  */
  defineTest('textClockFontWeightTestOne', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontWeightTestOne running')
    let driver: Tester = Tester.create()
    let textClock1: Component = await driver.findComponent(Matcher.create().id('textClockFontWeight1').enabled(true))
    let textClock2: Component = await driver.findComponent(Matcher.create().id('textClockFontWeight2').enabled(true))
    let textClock3: Component = await driver.findComponent(Matcher.create().id('textClockFontWeight3').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextClockFontWeight1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextClockFontWeight2').enabled(true))
    let fontWeight1: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, '500')
    let fontWeight2: string = await textClock2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Normal')
    let fontWeight3: string = await textClock3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Lighter')
    await button1.tap()
    let fontWeight4: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, "FontWeight.Lighter")
    await button2.tap()
    let fontWeight5: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, 'FontWeight.Bold')
  }, 0)
}