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

export default async function textClockFontSizeTest() {
  /*
  * TextClock组件 FontSize属性
  * 找到画面id为textClockFontSize1，textClockFontSize2的TextClock组件
  * 找到画面文本为TextClockFontSize的Button组件
  * 获取textClock1的FontSize属性与期待值30比对
  * 获取textClock2的FontSize属性与期待值$r('app.integer.data_panel_number')比对
  * 点击button，变更textClock1的FontSize属性值为"200px"
  * 获取textClock1的FontSize属性与期待值"200px"比对
  */
  defineTest('textClockFontSizeTest', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontSizeTest running')
    let driver: Tester = Tester.create()
    let textClock1: Component = await driver.findComponent(Matcher.create().id('textClockFontSize1').enabled(true))
    let textClock2: Component = await driver.findComponent(Matcher.create().id('textClockFontSize2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextClockFontSize').enabled(true))
    let fontSize1: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize1).$attrs.fontSize, '30.00fp')
    let fontSize2: string = await textClock2.getInspectorInfo()
    assertEqual(JSON.parse(fontSize2).$attrs.fontSize, $r("app.string.data_panel_number"))
    await button.tap()
    let fontSize3: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontSize3).$attrs.fontSize, "200.00px")
  }, 0)
}