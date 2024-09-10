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
  assertFalse,
  assertTrue,
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function textAreaShowCounterTest() {
  /*
   * TextArea组件 ShowCounter属性
   * 找到画面id为textAreaShowCounter1,textAreaShowCounter2的TextArea组件
   * 找到画面文本为TextAreaShowCounter1,TextAreaShowCounter2的Button组件
   * 获取textArea1的ShowCounter属性ShowCounter.value与期待值true比对
   * 获取textArea1的ShowCounter属性ShowCounter.options.highlightBorder与期待值false比对
   * 获取textArea2的ShowCounter属性ShowCounter.value与期待值true比对
   * 获取textArea2的ShowCounter.options.thresholdPercentage属性与期待值70比对
   * 获取textArea2的ShowCounter属性ShowCounter.options.highlightBorder与期待值true比对
   * 点击button1，变更textArea1的ShowCounter.value属性值为false
   * 获取textArea1的ShowCounter.value属性与期待值false比对
   * 点击button2，变更textArea1的ShowCounter.options.highlightBorder属性值为true
   * 获取textArea1的ShowCounter.options.highlightBorder属性与期待值true比对
   */
  defineTest('textAreaShowCounterTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textAreaShowCounterTestDemo running")
    let driver: Tester = Tester.create()
    let textArea1: Component = await driver.findComponent(Matcher.create().id('textAreaShowCounter1').enabled(true))
    let textArea2: Component = await driver.findComponent(Matcher.create().id('textAreaShowCounter2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('TextAreaShowCounter1').enabled(true))
    let button2: Component = await driver.findComponent(Matcher.create().text('TextAreaShowCounter2').enabled(true))

    let showCounter1: string = await textArea1.getInspectorInfo()
    assertTrue(JSON.parse(showCounter1).$attrs.showCounter.value)
    assertFalse(JSON.parse(showCounter1)
      .$attrs
      .showCounter
      .options
      .highlightBorder)
    let showCounter2: string = await textArea2.getInspectorInfo()
    assertTrue(JSON.parse(showCounter2).$attrs.showCounter.value)
    assertEqual(JSON.parse(showCounter2)
      .$attrs
      .showCounter
      .options
      .thresholdPercentage, 70)
    assertTrue(JSON.parse(showCounter2)
      .$attrs
      .showCounter
      .options
      .highlightBorder)

    await button1.tap()
    let showCounter3: string = await textArea1.getInspectorInfo()
    assertFalse(JSON.parse(showCounter3).$attrs.showCounter.value)

    await button2.tap()
    let showCounter4: string = await textArea1.getInspectorInfo()
    assertTrue(JSON.parse(showCounter4)
      .$attrs
      .showCounter
      .options
      .highlightBorder)
  }, 0)
}