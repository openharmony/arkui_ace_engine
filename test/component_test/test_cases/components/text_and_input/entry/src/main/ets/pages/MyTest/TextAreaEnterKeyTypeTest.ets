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

export default async function textAreaEnterKeyTypeTest() {
  /*
   * TextArea组件 EnterKeyType属性
   * 找到画面id为textAreaEnterKeyType1,textAreaEnterKeyType2,textAreaEnterKeyType3,textAreaEnterKeyType4的TextArea组件
   * 找到画面文本为TextAreaEnterKeyType的Button组件
   * 获取textArea1的EnterKeyType属性与期待值'EnterKeyType.Go'比对
   * 获取textArea2的EnterKeyType属性与期待值'EnterKeyType.Next'比对
   * 获取textArea3的EnterKeyType属性与期待值'EnterKeyType.NEW_LINE'比对
   * 获取textArea4的EnterKeyType属性与期待值'EnterKeyType.Search'比对
   * 点击button，变更textArea4的EnterKeyType属性值为EnterKeyType.Done
   * 获取textArea4的EnterKeyType属性与期待值'EnterKeyType.Done'比对
   * 点击button，变更textArea4的EnterKeyType属性值为EnterKeyType.PREVIOUS
   * 获取textArea4的EnterKeyType属性与期待值'EnterKeyType.PREVIOUS'比对
   * 点击button，变更textArea4的EnterKeyType属性值为EnterKeyType.Send
   * 获取textArea4的EnterKeyType属性与期待值'EnterKeyType.Send'比对
   */
  defineTest('textAreaEnterKeyTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaEnterKeyTypeTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaEnterKeyType1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaEnterKeyType2').enabled(true))
    let textArea3: Component = await driver.findComponent(Matcher.create().id('textAreaEnterKeyType3').enabled(true))
    let textArea4: Component = await driver.findComponent(Matcher.create().id('textAreaEnterKeyType4').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaEnterKeyType').enabled(true))

    let enterKeyType1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType1).$attrs.enterKeyType, 'EnterKeyType.Go')
    let enterKeyType2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType2).$attrs.enterKeyType, 'EnterKeyType.Next')
    let enterKeyType3: string = await textArea3.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType3).$attrs.enterKeyType, 'EnterKeyType.NEW_LINE')
    let enterKeyType4: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType4).$attrs.enterKeyType, 'EnterKeyType.Search')

    await button.tap()
    let enterKeyType5: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType5).$attrs.enterKeyType, 'EnterKeyType.Done')

    await button.tap()
    let enterKeyType6: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType6).$attrs.enterKeyType, 'EnterKeyType.PREVIOUS')

    await button.tap()
    let enterKeyType7: string = await textArea4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType7).$attrs.enterKeyType, 'EnterKeyType.Send')
  }, 0)
}