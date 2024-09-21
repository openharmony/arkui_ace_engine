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

export default async function textInputCaretStyleTest() {
  /*
   * TextInput组件 CaretStyle属性
   * 找到画面id为textInputCaretStyle1,textInputCaretStyle2的TextInput组件
   * 找到画面文本为TextInputCaretPosition的Button组件
   * 获取textInput1的CaretStyle属性与期待值'2.00vp'比对
   * 获取textInput2的CaretStyle属性与期待值'100.00vp'比对
   * 点击button，变更textInput2的CaretStyle属性值为$r('app.string.vp_length')
   * 获取textInput2的CaretStyle属性与期待值$r('app.string.vp_length')比对
   */
  defineTest('textInputCaretStyleTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputCaretStyleTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputCaretStyle1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputCaretStyle2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputCaretStyle').enabled(true))

    let caretStyle1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(caretStyle1).$attrs.caretStyle).width, '2.00vp')
    let caretStyle2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(caretStyle2).$attrs.caretStyle).width, '100.00vp')
    await button.tap()
    let caretStyle3: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(JSON.parse(caretStyle3).$attrs.caretStyle).width, $r('app.string.vp_length'))
  }, 0)
}