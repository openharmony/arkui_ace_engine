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

export default async function textAreaFontFamilyTest() {
  /*
   * TextArea组件 FontFamily属性
   * 找到画面id为textAreaFontFamily的TextArea组件
   * 找到画面文本为TextAreaFontFamily的Button组件
   * 获取textArea的FontFamily属性与期待值'Arial'比对
   * 点击button，变更textArea的FontFamily属性值为'TESTFONTRawFile'
   * 获取textArea的FontFamily属性与期待值'TESTFONTRawFile'比对
   */
  defineTest('textAreaFontFamilyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaFontFamilyTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component = await driver.findComponent(Matcher.create().id('textAreaFontFamily').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaFontFamily').enabled(true))

    let fontFamily1: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily1).$attrs.fontFamily, 'Arial')

    await button.tap()
    let fontFamily2: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(fontFamily2).$attrs.fontFamily, 'TESTFONTRawFile')
  }, 0)
}