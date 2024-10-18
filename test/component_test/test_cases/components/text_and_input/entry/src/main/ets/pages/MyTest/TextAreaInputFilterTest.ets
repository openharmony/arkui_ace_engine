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
import { logLibrary } from '@kit.PerformanceAnalysisKit'

export default async function textAreaInputFilterTest() {
  /*
   * TextArea组件 InputFilter属性
   * 找到画面id为textAreaInputFilter的TextArea组件
   * 找到画面文本为TextAreaInputFilter的Button组件
   * 获取textArea的InputFilter属性inputFilter与期待值'^[a-z]$'比对
   * 点击button，变更textArea的InputFilter属性inputFilter.value值为$r("app.string.value_resource_str")
   * 获取textArea的InputFilter属性inputFilter与期待值$r("app.string.value_resource_str")比对
   */
  defineTest('textAreaInputFilterTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaInputFilterTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component = await driver.findComponent(Matcher.create().id('textAreaInputFilter').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextAreaInputFilter').enabled(true))

    let inputFilter1: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(inputFilter1).$attrs.inputFilter, '^[a-z]$')

    await button.tap()
    let inputFilter2: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(inputFilter2).$attrs.inputFilter, $r("app.string.value_resource_str"))
  }, 0)
}