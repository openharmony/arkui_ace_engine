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

export default async function textInputShowUnitTest() {
  /*
   * TextInput组件 ShowUnit属性
   * 找到text为MB的select组件
   * 获取select的type类型与期待值'Select'比对
   */
  defineTest('textInputShowUnitTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textInputShowUnitTestDemo running")
    let driver: Tester = Tester.create()
    let select: Component = await driver.findComponent(Matcher.create().text('MB').enabled())
    let type: string = await select.getType()
    assertEqual(type, 'Select')
  }, 0)
}