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

export default async function textAreaTypeTest() {
  /*
* TextArea组件 Type属性
* 找到画面id为textAreaType1,textAreaType2的TextArea组件
* 找到画面文本为TextAreaType1,TextAreaType2的Button组件
* 获取textArea1的Type属性与期待值TextAreaType.EMAIL比对
* 获取textArea2的Type属性与期待值TextAreaType.NORMAL比对
* 点击button1，变更textArea2的Type属性值为TextAreaType.NUMBER
* 获取textArea2的Type属性与期待值TextAreaType.NUMBER比对
* 点击button2，变更textArea2的Type属性值为TextAreaType.PHONE_NUMBER
* 获取textArea2的Type属性与期待值TextAreaType.PHONE_NUMBER比对
*/
  defineTest('TextAreaTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("TextAreaTypeTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaType1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaType2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextAreaType1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextAreaType2').enabled(true))

    let type1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'TextAreaType.EMAIL')

    let type2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'TextAreaType.NORMAL')

    await button1.tap()
    let type3: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'TextAreaType.NUMBER')

    await button2.tap()
    let type4: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(type4).$attrs.type, 'TextAreaType.PHONE_NUMBER')
  }, 0)
}