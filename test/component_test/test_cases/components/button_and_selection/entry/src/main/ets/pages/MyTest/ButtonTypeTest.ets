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

export default async function buttonTypeTest() {
  /*
   * Button组件 Type属性
   * 找到画面id为buttonType1，buttonType2的Button组件
   * 找到画面文本为ButtonType2的Button组件
   * 获取buttonType1的Type属性与期待值ButtonType.Capsule比对
   * 获取buttonType2的Type属性与期待值ButtonType.Circle比对
   * 点击button，变更buttonType2的Type属性值为ButtonType.Normal
   * 获取buttonType2的Type属性与期待值ButtonType.Normal比对
   */
  defineTest('buttonTypeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('buttonTypeTestDemo running')
    let driver: Tester = Tester.create()
    let buttonType1: Component = await driver.findComponent(Matcher.create().id('buttonType1').enabled(true))
    let buttonType2: Component = await driver.findComponent(Matcher.create().id('buttonType2').enabled(true))
    let button: Component = await driver.findComponent(Matcher.create().text('ButtonType2').enabled(true))

    let type1: string = await buttonType1.getInspectorInfo()
    assertEqual(JSON.parse(type1).$attrs.type, 'ButtonType.Capsule')

    let type2: string = await buttonType2.getInspectorInfo()
    assertEqual(JSON.parse(type2).$attrs.type, 'ButtonType.Circle')

    await button.tap()
    let type3: string = await buttonType2.getInspectorInfo()
    assertEqual(JSON.parse(type3).$attrs.type, 'ButtonType.Normal')
  }, 0)
}