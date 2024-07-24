/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
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
  Component,
  defineTest,
  Matcher,
  TestCaseLevel,
  Tester
} from '@ohos.arkui.componentTest'

export default async function scrollAttributeTest() {
  /*
   * Scroll组件 Attribute属性
   * 找到画面id为scrollAttribute的Scroll组件
   * 获取scrollAttribute的attributeModifier.backgroundColor属性与期待值Color.Red比对
   */
  defineTest('scrollAttributeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log('scrollAttributeTestDemo running')
    let driver: Tester = Tester.create()
    let scrollAttribute: Component = await driver.findComponent(Matcher.create().id('scrollAttribute').enabled(true))

    let attribute: string = await scrollAttribute.getInspectorInfo()
    assertEqual(JSON.parse(attribute).$attrs.backgroundColor.toLowerCase(), Color.Red)
  }, 0)
}