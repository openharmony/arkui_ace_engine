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

export default async function textAreaCopyOptionTest() {
  /*
   * TextArea组件 CopyOption属性
   * 找到画面id为textAreaCopyOption1,textAreaCopyOption2的TextArea组件
   * 找到画面文本为TextAreaCopyOption1,TextAreaCopyOption2的Button组件
   * 获取textArea1的CopyOption属性与期待值'CopyOptions.None'比对
   * 获取textArea2的CopyOption属性与期待值'CopyOptions.InApp'比对
   * 点击button1，变更textArea2的CopyOption属性值为CopyOptions.LocalDevice
   * 获取textArea2的CopyOption属性与期待值'CopyOptions.Local'比对
   * 点击button2，变更textArea2的CopyOption属性值为CopyOptions.CROSS_DEVICE
   * 获取textArea2的CopyOption属性与期待值'CopyOptions.CROSS_DEVICE'比对
   */
  defineTest('textAreaCopyOptionTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaCopyOptionTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaCopyOption1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaCopyOption2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextAreaCopyOption1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextAreaCopyOption2').enabled(true))

    let copyOption1: string = await textArea1.getInspectorInfo()
    assertEqual(JSON.parse(copyOption1).$attrs.copyOption, 'CopyOptions.None')
    let copyOption2: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(copyOption2).$attrs.copyOption, 'CopyOptions.InApp')

    await button1.tap()
    let copyOption3: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(copyOption3).$attrs.copyOption, 'CopyOptions.Local')

    await button2.tap()
    let copyOption4: string = await textArea2.getInspectorInfo()
    assertEqual(JSON.parse(copyOption4).$attrs.copyOption, 'CopyOptions.CROSS_DEVICE')
  }, 0)
}