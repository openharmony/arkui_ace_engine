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

export default async function textAreaMaxLengthTest() {
  /*
   * TextArea组件 MaxLength属性
   * 找到画面id为textAreaMaxLength的TextArea组件
   * 获取textArea的MaxLength属性与期待值'10'比对
   */
  defineTest('textAreaMaxLengthTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaMaxLengthTestDemo running")
    let driver: Tester = Tester.create()
    let textArea: Component = await driver.findComponent(Matcher.create().id('textAreaMaxLength').enabled(true))

    let maxLength: string = await textArea.getInspectorInfo()
    assertEqual(JSON.parse(maxLength).$attrs.maxLength, '10')
  }, 0)
}