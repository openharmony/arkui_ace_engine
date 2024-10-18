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

export default async function menuFontColorTest() {
  /*
* Menu组件 FontColor属性
* 找到画面id为menuFontColor1，menuFontColor2的Menu组件
* 找到画面文本为MenuFontColor1， MenuFontColor2的Button组件
* 获取menu1的FontColor属性与期待值Color.Blue比对
* 获取menu2的FontColor属性与期待值'#FFF00FFF'比对
* 点击button1，变更menu2的FontColor属性值为'#FFFFC0CB'
* 获取menu2的FontColor属性与期待值'#FFFFC0CB'比对
* 点击button2，变更menu2的FontColor属性值为$r('sys.color.ohos_id_color_badge_red')
* 获取menu2的FontColor属性与期待值$r('sys.color.ohos_id_color_badge_red')比对
*/
  defineTest('menuFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('menuFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let menu1: Component = await driver.findComponent(Matcher.create().id('menuFontColor1').enabled(true))
    let menu2: Component = await driver.findComponent(Matcher.create().id('menuFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('MenuFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('MenuFontColor2').enabled(true))

    let fontColor1: string = await menu1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor.toLowerCase(), Color.Blue)

    let fontColor2: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor, '#FFF00FFF')
    await button1.tap()
    let fontColor3: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, '#FFFFC0CB')
    await button2.tap()
    let fontColor4: string = await menu2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('sys.color.ohos_id_color_badge_red'))
  }, 0)
}