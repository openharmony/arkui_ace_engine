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

export default async function attributeModifierTest() {
  /*
  * button组件 attributeModifier属性
  * 找到画面id为buttonAttributeModifier1的组件
  * 找到画面文本为ButtonAttributeModifier的Button按钮命名为button1
  * 获取buttonAttributeModifier1的backgroundColor属性与期待值Color.Red比对
  * 点击button1，变更buttonAttributeModifier1的backgroundColor属性值为Color.Black
  * 获取buttonAttributeModifier1的backgroundColor属性与期待值与Color.Black比对
  */
  defineTest('attributeModifierTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("attributeModifierTestDemo running")
    let driver: Tester = Tester.create()
    let buttonAttributeModifier1: Component =
      await driver.findComponent(Matcher.create().id('buttonAttributeModifier1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonAttributeModifier').enabled(true))
    let attributeModifier1: string = await buttonAttributeModifier1.getInspectorInfo()
    assertEqual(JSON.parse(attributeModifier1).$attrs.backgroundColor.toLowerCase(), Color.Red)

    await button1.tap()
    let attributeModifier2: string = await buttonAttributeModifier1.getInspectorInfo()
    assertEqual(JSON.parse(attributeModifier2).$attrs.backgroundColor.toLowerCase(), Color.Black)
  }, 0)
}