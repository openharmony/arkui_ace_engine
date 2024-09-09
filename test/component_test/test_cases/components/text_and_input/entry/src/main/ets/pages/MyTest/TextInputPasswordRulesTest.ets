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
import { assertEqual } from '@ohos.arkui.componentTest'
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function textInputPasswordRulesTest() {
  /*
   * TextInput组件 PasswordRules属性
   * 找到画面id为textInputPasswordRules的TextInput组件
   * 获取textInput的PasswordRules属性与期待值" ^[A-Za-z]$"比对
   */
  defineTest('textInputPasswordRulesTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputPasswordRulesTestDemo running")
    let driver: Tester = Tester.create()
    let textInput: Component = await driver.findComponent(Matcher.create().id('textInputPasswordRules').enabled(true))

    let passwordRules: string = await textInput.getInspectorInfo()
    assertEqual(JSON.parse(passwordRules).$attrs.passwordRules, " ^[A-Za-z]$")
  }, 0)
}