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

export default async function textInputEnterKeyTypeTest() {
  /*
   * TextInput组件 EnterKeyType属性
   * 找到画面id为textInputEnterKeyType1,textInputEnterKeyType2,textInputEnterKeyType3,textInputEnterKeyType4,textInputEnterKeyType5的TextInput组件
   * 找到画面文本为TextInputEnterKeyType1,TextInputEnterKeyType2的Button组件
   * 获取textInput1的EnterKeyType属性与期待值'EnterKeyType.Go'比对
   * 获取textInput2的EnterKeyType属性与期待值'EnterKeyType.Search'比对
   * 获取textInput3的EnterKeyType属性与期待值'EnterKeyType.Next'比对
   * 获取textInput4的EnterKeyType属性与期待值'EnterKeyType.Done'比对
   * 获取textInput5的EnterKeyType属性与期待值'EnterKeyType.NEW_LINE'比对
   * 点击button1，变更textInput2的EnterKeyType属性值为EnterKeyType.Send
   * 获取textInput2的EnterKeyType属性与期待值'EnterKeyType.Send'比对
   * 点击button2，变更textInput4的EnterKeyType属性值为EnterKeyType.PREVIOUS
   * 获取textInput4的EnterKeyType属性与期待值'EnterKeyType.PREVIOUS'比对
   */
  defineTest('textInputEnterKeyTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputEnterKeyTypeTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputEnterKeyType1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputEnterKeyType2').enabled(true))
    let textInput3: Component = await driver.findComponent(Matcher.create().id('textInputEnterKeyType3').enabled(true))
    let textInput4: Component = await driver.findComponent(Matcher.create().id('textInputEnterKeyType4').enabled(true))
    let textInput5: Component = await driver.findComponent(Matcher.create().id('textInputEnterKeyType5').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextInputEnterKeyType1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextInputEnterKeyType2').enabled(true))

    let enterKeyType1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType1).$attrs.enterKeyType, 'EnterKeyType.Go')

    let enterKeyType2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType2).$attrs.enterKeyType, 'EnterKeyType.Search')

    let enterKeyType3: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType3).$attrs.enterKeyType, 'EnterKeyType.Next')

    let enterKeyType4: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType4).$attrs.enterKeyType, 'EnterKeyType.Done')

    let enterKeyType5: string = await textInput5.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType5).$attrs.enterKeyType, 'EnterKeyType.NEW_LINE')

    await button1.tap()
    let enterKeyType6: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType6).$attrs.enterKeyType, 'EnterKeyType.Send')

    await button2.tap()
    let enterKeyType7: string = await textInput4.getInspectorInfo()
    assertEqual(JSON.parse(enterKeyType7).$attrs.enterKeyType, 'EnterKeyType.PREVIOUS')
  }, 0)
}