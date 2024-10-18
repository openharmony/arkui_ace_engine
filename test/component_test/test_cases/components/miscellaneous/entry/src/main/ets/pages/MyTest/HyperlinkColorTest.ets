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

export default async function hyperLinkColorTest() {
  /*
   * Hyperlink组件 Color属性
   * 找到画面id为hyperlinkColor1,hyperlinkColor2的Hyperlink组件
   * 找到画面文本为HyperlinkColor1,HyperlinkColor2的Button组件
   * 获取hyperLink1的Color属性与期待值Color.Green比对
   * 获取hyperLink2的Color属性与期待值'#FF808080'比对
   * 点击button1，变更hyperLink1的Color属性值为'#FFFF64FF'
   * 获取hyperLink1的Color属性与期待值'#FFFF64FF'比对
   * 点击button2，变更hyperLink1的Color属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取hyperLink1的Color属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('hyperlinkColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('hyperlinkColorTestDemo running')
    let driver: Tester = Tester.create()
    let hyperLink1: Component = await driver.findComponent(Matcher.create().id('hyperlinkColor1').enabled(true))
    let hyperLink2: Component = await driver.findComponent(Matcher.create().id('hyperlinkColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('HyperlinkColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('HyperlinkColor2').enabled(true))

    let color1: string = await hyperLink1.getInspectorInfo()
    assertEqual(JSON.parse(color1).$attrs.color.toLowerCase(), Color.Green)

    let color2: string = await hyperLink2.getInspectorInfo()
    assertEqual(JSON.parse(color2).$attrs.color, '#FF808080')

    await button1.tap()
    let color3: string = await hyperLink1.getInspectorInfo()
    assertEqual(JSON.parse(color3).$attrs.color, '#FFFF64FF')

    await button2.tap()
    let color4: string = await hyperLink1.getInspectorInfo()
    assertEqual(JSON.parse(color4).$attrs.color, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}