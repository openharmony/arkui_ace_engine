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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textFontColorTest() {
  /*
   * Text组件 FontColor属性
   * 找到画面id为textFontColor1,textFontColor2的Text组件
   * 找到画面文本为TextFontColor1,TextFontColor2的Button组件
   * 获取text1的FontColor属性与期待值Color.Orange比对
   * 获取text2的FontColor属性与期待值0x0000FF比对
   * 点击button1，变更text2的FontColor属性值为'#ffe72727'
   * 获取text2的FontColor属性与期待值'#ffe72727'比对
   * 点击button2，变更text2的FontColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取text2的FontColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textFontColorTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textFontColor1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextFontColor2').enabled(true))

    let fontColor1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor.toLowerCase(), Color.Orange)
    let fontColor2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor, '#FF0000FF')

    await button1.tap()
    let fontColor3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor.toLowerCase(), '#ffe72727')
    await button2.tap()
    let fontColor4: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}