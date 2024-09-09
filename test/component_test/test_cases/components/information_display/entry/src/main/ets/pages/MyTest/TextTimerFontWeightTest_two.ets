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

export default async function textTimerFontWeightTest_two() {
  /*
* TextTimer组件 FontWeight属性
* 找到画面id为textTimerFontWeight4，textTimerFontWeight5，textTimerFontWeight6、 textTimerFontWeight7的TextTimer组件
* 找到画面文本为TextTimerFontWeight的Button组件
* 获取textTimer4的FontWeight属性与期待值FontWeight.Medium比对
* 获取textTimer5的FontWeight属性与期待值FontWeight.Bolder比对
* 获取textTimer6的FontWeight属性与期待值500比对
* 点击button，变更textTimer6的FontWeight属性值为"lighter"
* 获取textTimer6的FontWeight属性与期待值"lighter"比对
* 获取textTimer7的FontWeight属性与期待值'400'比对
*/
  defineTest('textTimerFontWeightTestDemo_two', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerFontWeightTestDemo_two running')
    let driver: Tester = Tester.create()
    let textTimer4: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight4').enabled(true))
    let textTimer5: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight5').enabled(true))
    let textTimer6: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight6').enabled(true))
    let textTimer7: Component = await driver.findComponent(Matcher.create().id('textTimerFontWeight7').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTimerFontWeight').enabled(true))
    let fontWeight1: string = await textTimer4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Medium')
    let fontWeight2: string = await textTimer5.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Bolder')
    let fontWeight3: string = await textTimer6.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, '500')
    await button.tap()
    let fontWeight4: string = await textTimer6.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight4).$attrs.fontWeight, "FontWeight.Lighter")
    let fontWeight5: string = await textTimer7.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight5).$attrs.fontWeight, '400')
  }, 0)
}