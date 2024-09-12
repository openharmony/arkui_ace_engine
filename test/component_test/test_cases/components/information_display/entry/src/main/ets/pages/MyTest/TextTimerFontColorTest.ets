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

export default async function textTimerFontColorTest() {
  /*
* TextTimer组件 FontColor属性
* 找到画面id为textTimerFontColor1，textTimerFontColor2、 textTimerFontColor3的TextTimer组件
* 找到画面文本为TextTimerFontColor的Button组件
* 获取textTimer1的FontColor属性与期待值Color.Blue比对
* 点击button，变更textTimer1的FontColor属性值为0xff0000
* 获取textTimer1的FontColor属性与期待值0xff0000比对
* 获取textTimer2的FontColor属性与期待值"#FFF000"比对
* 获取textTimer3的FontColor属性与期待值$r("app.color.text_timer_color1")比对
*/
  defineTest('textTimerFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('textTimerFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let textTimer1: Component = await driver.findComponent(Matcher.create().id('textTimerFontColor1').enabled(true))
    let textTimer2: Component = await driver.findComponent(Matcher.create().id('textTimerFontColor2').enabled(true))
    let textTimer3: Component = await driver.findComponent(Matcher.create().id('textTimerFontColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextTimerFontColor').enabled(true))
    let fontColor1: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor.toLowerCase(), Color.Blue)
    await button.tap()
    let fontColor2: string = await textTimer1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor, '#FFFF0000')
    let fontColor3: string = await textTimer2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, "#FFFFF000")
    let fontColor4: string = await textTimer3.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r("app.color.text_timer_color1"))
  }, 0)
}