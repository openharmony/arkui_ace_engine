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

export default async function textInputCaretColorTest() {
  /*
   * TextInput组件 CaretColor属性
   * 找到画面id为textInputCaretColor1,textInputCaretColor2的TextInput组件
   * 找到画面文本为TextInputCaretColor1,TextInputCaretColor2的Button组件
   * 获取textInput1的CaretColor属性与期待值Color.Pink比对
   * 获取textInput2的CaretColor属性与期待值'#ffffffff'比对
   * 点击button1，变更textInput2的CaretColor属性值为'rgb(255, 100, 255)'
   * 获取textInput2的CaretColor属性与期待值'#FFFF64FF'比对
   * 点击button2，变更textInput2的CaretColor属性值为$r('sys.color.ohos_id_color_text_hyperlink')
   * 获取textInput2的CaretColor属性与期待值$r('sys.color.ohos_id_color_text_hyperlink')比对
   */
  defineTest('textInputCaretColorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputCaretColorTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputCaretColor1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputCaretColor2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputCaretColor1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputCaretColor2').enabled(true))

    let caretColor1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(caretColor1).$attrs.caretColor.toLowerCase(), Color.Pink)
    let caretColor2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(caretColor2).$attrs.caretColor.toLowerCase(), '#ffffffff')

    await button1.tap()
    let caretColor3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(caretColor3).$attrs.caretColor, '#FFFF64FF')

    await button2.tap()
    let caretColor4: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(caretColor4).$attrs.caretColor, $r('sys.color.ohos_id_color_text_hyperlink'))
  }, 0)
}