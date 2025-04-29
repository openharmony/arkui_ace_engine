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

export default async function textAreaTextAlignTest() {
  /*
   * TextArea组件 TextAlign属性
   * 找到画面id为textAreaTextAlign1,textAreaTextAlign2的TextArea组件
   * 找到画面文本为TextAreaTextAlign1,TextAreaTextAlign2的Button组件
   * 获取textArea1的TextAlign属性与期待值'TextAlign.Start'比对
   * 获取textArea2的TextAlign属性与期待值'TextAlign.Center'比对
   * 点击button1，变更textArea2的TextAlign属性值为TextAlign.End
   * 获取textArea2的TextAlign属性与期待值'TextAlign.End'比对
   * 点击button2，变更textArea2的TextAlign属性值为TextAlign.JUSTIFY
   * 获取textArea2的TextAlign属性与期待值'TextAlign.Justify'比对
   */
  defineTest('textAreaTextAlignTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaTextAlignTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaTextAlign1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaTextAlign2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextAreaTextAlign1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextAreaTextAlign2').enabled(true))

    let textAlign1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(textAlign1).$attrs.textAlign, 'TextAlign.Start')

    let textAlign2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign2).$attrs.textAlign, 'TextAlign.Center')

    await button1.tap()
    let textAlign3: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign3).$attrs.textAlign, 'TextAlign.End')

    await button2.tap()
    let textAlign4: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(textAlign4).$attrs.textAlign, 'TextAlign.Justify')
  }, 0)
}