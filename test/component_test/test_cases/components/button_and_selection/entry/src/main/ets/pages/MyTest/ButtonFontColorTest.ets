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

export default async function buttonFontColorTest() {
  /*
   * Button组件 FontColor属性
   * 找到画面id为buttonFontColor1，buttonFontColor2， buttonFontColor3的Button组件
   * 找到画面文本为ButtonFontColor3的Button组件
   * 获取buttonFontColor1的FontColor属性与期待值Color.Black比对
   * 获取buttonFontColor2的FontColor属性与期待值'#FF008000'比对
   * 获取buttonFontColor3的FontColor属性与期待值'#FF8EFF65'比对
   * 点击button，变更buttonFontColorColor3的FontColor属性值为$r('sys.color.ohos_fa_palette1')
   * 获取buttonFontColor3的FontColor属性与期待值$r('sys.color.ohos_fa_palette1')比对
   */
  defineTest('buttonFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonFontColorTestDemo running')
    let driver: Tester = Tester.create()
    let buttonFontColor1: Component = await driver.findComponent(Matcher.create().id('buttonFontColor1').enabled(true))
    let buttonFontColor2: Component = await driver.findComponent(Matcher.create().id('buttonFontColor2').enabled(true))
    let buttonFontColor3: Component = await driver.findComponent(Matcher.create().id('buttonFontColor3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonFontColor3').enabled(true))

    let fontColor1: string = await buttonFontColor1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor.toLowerCase(), Color.Black)

    let fontColor2: string = await buttonFontColor2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor, '#FF008000')

    let fontColor3: string = await buttonFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, '#FF8EFF65')

    await button.tap()
    let fontColor4: string = await buttonFontColor3.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('sys.color.ohos_fa_palette1'))
  }, 0)
}