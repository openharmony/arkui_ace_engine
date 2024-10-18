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

export default async function textInputTypeTest() {
  /*
   * TextInput组件 Type属性
   * 找到画面id为textInputType1,textInputType2,textInputType3的TextInput组件
   * 找到画面文本为TextInputType1的Button组件
   * 获取textInput1的Type属性与期待值'InputType.Normal'比对
   * 获取textInput2的Type属性与期待值'InputType.Password'比对
   * 获取textInput3的Type属性与期待值'InputType.Email'比对
   * 点击button，变更textInput3的Type属性值为InputType.Number
   * 获取textInput3的Type属性与期待值'InputType.Number'比对
   * 点击button，变更textInput3的Type属性值为InputType.PhoneNumber
   * 获取textInput3的Type属性与期待值'InputType.PhoneNumber'比对
   * 点击button，变更textInput3的Type属性值为InputType.USER_NAME
   * 获取textInput3的Type属性与期待值'InputType.USER_NAME'比对
   * 点击button，变更textInput3的Type属性值为InputType.NEW_PASSWORD
   * 获取textInput3的Type属性与期待值'InputType.NEW_PASSWORD'比对
   * 点击button，变更textInput3的Type属性值为InputType.NUMBER_PASSWORD
   * 获取textInput3的Type属性与期待值'InputType.NUMBER_PASSWORD'比对
   * 点击button，变更textInput3的Type属性值为InputType.NUMBER_DECIMAL
   * 获取textInput3的Type属性与期待值'InputType.NUMBER_DECIMAL'比对
   */
  defineTest('textInputTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputTypeTestDemo running")
    let driver: Tester = Tester.create()
    let textInput1: Component = await driver.findComponent(Matcher.create().id('textInputType1').enabled(true))
    let textInput2: Component = await driver.findComponent(Matcher.create().id('textInputType2').enabled(true))
    let textInput3: Component = await driver.findComponent(Matcher.create().id('textInputType3').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputType1').enabled(true))

    let type1: string = await textInput1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'InputType.Normal')
    let type2: string = await textInput2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'InputType.Password')
    let type3: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'InputType.Email')

    await button.tap()
    let type4: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type4).$attrs.type, 'InputType.Number')
    await button.tap()
    let type5: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type5).$attrs.type, 'InputType.PhoneNumber')
    await button.tap()
    let type6: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type6).$attrs.type, 'InputType.USER_NAME')
    await button.tap()
    let type7: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type7).$attrs.type, 'InputType.NEW_PASSWORD')
    await button.tap()
    let type8: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type8).$attrs.type, 'InputType.NUMBER_PASSWORD')
    await button.tap()
    let type9: string = await textInput3.getInspectorInfo()
    assertEqual(JSON.parse(type9).$attrs.type, 'InputType.NUMBER_DECIMAL')
  }, 0)
}