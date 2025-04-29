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
import {
  assertEqual,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function textInputShowErrorTest() {
  /*
   * TextInput组件 ShowError属性
   * 找到画面id为textInputShowError的TextInput组件
   * 找到画面文本为TextInputShowError的Button组件
   * 获取textInput的ShowError属性与期待值'Error'比对
   * 点击button，变更textInput的ShowError属性值为''
   * 获取textInput的ShowError属性与期待值''比对
   */
  defineTest('textInputShowErrorTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputShowErrorTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputShowError').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextInputShowError').enabled(true))

    let showError1: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(showError1).$attrs.showError, 'Error')

    await button.tap()
    let showError2: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(showError2).$attrs.showError, '')
  }, 0)
}