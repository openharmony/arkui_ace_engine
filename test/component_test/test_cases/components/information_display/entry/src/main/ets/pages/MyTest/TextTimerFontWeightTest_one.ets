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

export default async function textTimerFontWeightTest_one() {
  /*
* TextTimer组件 FontWeight属性
* 找到画面id为textTimerFontWeight1，textTimerFontWeight2，textTimerFontWeight3的TextTimer组件
* 找到画面文本为TextTimerFontWeight的Button组件
* 获取textTimer1的FontWeight属性与期待值FontWeight.Lighter比对
* 获取textTimer2的FontWeight属性与期待值FontWeight.Normal比对
* 点击button，变更textTimer2的FontWeight属性值为FontWeight.Bold
* 获取textTimer2的FontWeight属性与期待值FontWeight.Bold比对
* 获取textTimer3的FontWeight属性与期待值FontWeight.Regular比对

*/
  defineTest('textTimerFontWeightTestDemo_one', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerFontWeightTestDemo_one running')
    let driver: Tester = Tester.create()
    let textTimer1: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight1').enabled(true))
    let textTimer2: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight2').enabled(true))
    let textTimer3: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTimerFontWeight').enabled(true))
    let fontWeight1: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Lighter')
    let fontWeight2: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Normal')
    await button.tap()
    let fontWeight3: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Bold')
    let fontWeight4: string = await textTimer3.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, 'FontWeight.Regular')
  }, 0)
}