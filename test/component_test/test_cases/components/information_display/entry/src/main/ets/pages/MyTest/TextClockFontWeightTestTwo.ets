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

export default async function textClockFontWeightTestTwo() {
  /*
  * TextClock组件 FontWeight属性
  * 找到画面id为textClockFontWeight4，textClockFontWeight5的TextClock组件
  * 找到画面文本为TextClockFontWeight的Button组件
  * 获取textClock4的FontWeight属性与期待值FontWeight.Regular比对
  * 获取textClock5的FontWeight属性与期待值FontWeight.Medium比对
  * 点击button，变更textClock4的FontWeight属性值为FontWeight.Bolder
  * 获取textClock4的FontStyle属性与期待值FontWeight.Bolder比对
  */
  defineTest('textClockFontWeightTestTwo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontWeightTestTwo running')
    let driver: Tester = Tester.create()
    let textClock4: Component = await driver.findComponent(Matcher.create().id('textClockFontWeight4').enabled(true))
    let textClock5: Component = await driver.findComponent(Matcher.create().id('textClockFontWeight5').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextClockFontWeight').enabled(true))
    let fontWeight1: string = await textClock4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight1).$attrs.fontWeight, 'FontWeight.Regular')
    let fontWeight2: string = await textClock5.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight2).$attrs.fontWeight, 'FontWeight.Medium')
    await button.tap()
    let fontWeight3: string = await textClock4.getInspectorInfo()
    assertEqual(JSON.parse(fontWeight3).$attrs.fontWeight, 'FontWeight.Bolder')
  }, 0)
}