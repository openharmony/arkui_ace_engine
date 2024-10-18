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
import { assertEqual, Component, defineTest, Matcher, TestCaseLevel, Tester } from '@ohos.arkui.componentTest';

export default async function textHeightAdaptivePolicyTest() {
  /*
   * Text组件 HeightAdaptivePolicy属性
   * 找到画面id为textHeightAdaptivePolicy1,textHeightAdaptivePolicy2的Text组件
   * 找到画面文本为TextHeightAdaptivePolicy的Button组件
   * 获取text1的HeightAdaptivePolicy属性与期待值'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST'比对
   * 获取text2的HeightAdaptivePolicy属性与期待值'TextHeightAdaptivePolicy.MAX_LINES_FIRST'比对
   * 点击button，变更text2的HeightAdaptivePolicy属性值为TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST
   * 获取text2的HeightAdaptivePolicy属性与期待值'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST'比对
   */
  defineTest('textHeightAdaptivePolicyTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("textHeightAdaptivePolicyTestDemo running")
    let driver: Tester = Tester.create()
    let text1: Component = await driver.findComponent(Matcher.create().id('textHeightAdaptivePolicy1').enabled(true))
    let text2: Component = await driver.findComponent(Matcher.create().id('textHeightAdaptivePolicy2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('TextHeightAdaptivePolicy').enabled(true))

    let heightAdaptivePolicy1: string = await text1.getInspectorInfo()
    assertEqual(JSON.parse(heightAdaptivePolicy1).$attrs.heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST')
    let heightAdaptivePolicy2: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(heightAdaptivePolicy2).$attrs.heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.MAX_LINES_FIRST')

    await button.tap()
    let heightAdaptivePolicy3: string = await text2.getInspectorInfo()
    assertEqual(JSON.parse(heightAdaptivePolicy3).$attrs.heightAdaptivePolicy,
      'TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST')
  }, 0)
}