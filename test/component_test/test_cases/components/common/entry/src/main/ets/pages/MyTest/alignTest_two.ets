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

export default async function alignTest_two() {
  /*
  * stack组件 align属性
  * 找到画面id为stackAlign2的stack组件
  * 找到画面文本为ButtonAlign1的Button组件
  * 获取stackAlign2的align属性值与期待值Alignment.End比对
  * 点击button1，变更stackAlign2的align属性值与期待值Alignment.BottomStart比对
  * 点击button1，变更stackAlign2的align属性值与期待值Alignment.Bottom比对
  * 点击button1，变更stackAlign2的align属性值与期待值Alignment.BottomEnd比对
  */
  defineTest('alignTest_twoDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("alignTest_twoDemo running")
    let driver: Tester = Tester.create()
    let stackAlign2: Component = await driver.findComponent(Matcher.create().id('stackAlign2').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonAlign1').enabled(true))
    let align1: string = await stackAlign2.getInspectorInfo()
    assertEqual(JSON.parse(align1).$attrs.align, 'Alignment.End')

    await button1.tap()
    let align2: string = await stackAlign2.getInspectorInfo()
    assertEqual(JSON.parse(align2).$attrs.align, 'Alignment.BottomStart')

    await button1.tap()
    let align3: string = await stackAlign2.getInspectorInfo()
    assertEqual(JSON.parse(align3).$attrs.align, 'Alignment.Bottom')

    await button1.tap()
    let align4: string = await stackAlign2.getInspectorInfo()
    assertEqual(JSON.parse(align4).$attrs.align, 'Alignment.BottomEnd')
  }, 0)
}