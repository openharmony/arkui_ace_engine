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

export default async function textClockFontColorTest() {
  /*
  * TextClock组件 FontColor属性
  * 找到画面id为textClockFontColor1，textClockFontColor2的TextClock组件
  * 找到画面文本为TextClockFontColor1，TextClockFontColor2的Button组件
  * 获取textClock1的FontColor属性与期待值0xff0000比对
  * 获取textClock2的FontColor属性与期待值"#ffc007f3"比对
  * 点击button1，变更textClock1的FontColor属性值为Color.Blue
  * 获取textClock1的FontColor属性与期待值Color.Blue比对
  * 点击button2，变更textClock1的FontColor属性值为$r('app.color.data_panel_resource_color5')
  * 获取textClock1的FontColor属性与期待值$r('app.color.data_panel_resource_color5')比对
  */
  defineTest('textClockFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textClockFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let textClock1: Component = await driver.findComponent(Matcher.create().id('textClockFontColor1').enabled(true))
    let textClock2: Component = await driver.findComponent(Matcher.create().id('textClockFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextClockFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextClockFontColor2').enabled(true))
    let fontColor1: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor, '#FFFF0000')
    let fontColor2: string = await textClock2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor.toLowerCase(), "#ffc007f3")
    await button1.tap()
    let fontColor3: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor.toLowerCase(), Color.Blue)
    await button2.tap()
    let fontColor4: string = await textClock1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('app.color.data_panel_resource_color5'))
  }, 0)
}