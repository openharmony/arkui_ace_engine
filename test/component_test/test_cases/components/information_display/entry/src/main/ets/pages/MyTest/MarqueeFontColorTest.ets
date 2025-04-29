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

export default async function marqueeFontColorTest() {
  /*
* Marquee组件 FontColor属性
* 找到画面id为marqueeFontColor1，marqueeFontColor2， marqueeFontColor3的Marquee组件
* 找到画面文本为MarqueeFontColor的Button组件
* 获取marquee1的FontColor属性与期待值0x66FF66比对
* 获取marquee2的FontColor属性与期待值Color.Red比对
* 获取marquee3的FontColor属性与期待值"#FFF000"比对
* 点击button，变更marquee3的FontColor属性值为$r('app.color.marquee_font_color')
* 获取marquee3的FontColor属性与期待值$r('app.color.marquee_color')比对
*/
  defineTest('marqueeFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('marqueeFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let marquee1: Component = await driver.findComponent(Matcher.create().id('marqueeFontColor1').enabled(true))
    let marquee2: Component = await driver.findComponent(Matcher.create().id('marqueeFontColor2').enabled(true))
    let marquee3: Component = await driver.findComponent(Matcher.create().id('marqueeFontColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('MarqueeFontColor').enabled(true))
    let fontColor1: string = await marquee1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor, '#FF66FF66')
    let fontColor2: string = await marquee2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor.toLowerCase(), Color.Red)
    let fontColor3: string = await marquee3.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, "#FFFFF000")
    await button.tap()
    let fontColor4: string = await marquee3.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r("app.color.marquee_font_color"))
  }, 0)
}