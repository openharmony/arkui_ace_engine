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

export default async function textInputFontColorTest() {
  /*
   * TextInput组件 FontColor属性
   * 找到画面id为textInputFontColor1,textInputFontColor2的TextInput组件
   * 找到画面文本为TextInputFontColor1,TextInputFontColor2的Button组件
   * 获取textInput1的FontColor属性与期待值Color.Pink比对
   * 获取textInput2的FontColor属性与期待值'#ffffffff'比对
   * 点击button1，变更textInput2的FontColor属性值为'rgb(255, 100, 255)'
   * 获取textInput2的FontColor属性与期待值'#FFFF64FF'比对
   * 点击button2，变更textInput2的FontColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取textInput2的FontColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textInputFontColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputFontColorTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputFontColor1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputFontColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputFontColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputFontColor2').enabled(true))

    let fontColor1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(fontColor1).$attrs.fontColor.toLowerCase(), Color.Pink)

    let fontColor2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor2).$attrs.fontColor.toLowerCase(), '#ffffffff')

    await button1.tap()
    let fontColor3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor3).$attrs.fontColor, '#FFFF64FF')

    await button2.tap()
    let fontColor4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(fontColor4).$attrs.fontColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}