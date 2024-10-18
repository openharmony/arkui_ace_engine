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

import { assertEqual, assertFalse } from '@ohos.arkui.componentTest';
import { TestCaseLevel, defineTest } from '@ohos.arkui.componentTest'
import { Tester, Component, Matcher } from '@ohos.arkui.componentTest'

export default async function rotateTest() {
  /*
  * rotate属性
  * 找到画面id为alphabetIndexerRotate1的AlphabetIndexer组件
  * 找到画面文本为 ButtonRotate1 的Button组件
  * 获取alphabetIndexerRotate1的属性
  * x 与期待值0.000000比对
  * y 与期待值0.000000比对
  * z 与期待值1.000000比对
  * angle 与期待值10.000000比对
  * centerX 与期待值10.000000比对
  * centerY 与期待值10.000000比对
  * centerZ 与期待值10.000000比对
  * perspective 与期待值10.000000比对
  * 点击button1，变更alphabetIndexerRotate1的属性值
  * 获取alphabetIndexerRotate1的属性(angle centerX centerY
  * angle 与期待值"90.000000"比对
  * centerX 与期待值"90.00vp"比对
  * centerY 与期待值"90.00vp"比对
  */
  defineTest('rotateTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("rotateTestDemo running")
    let driver: Tester = Tester.create()
    let alphabetIndexerRotate1: Component =
      await driver.findComponent(Matcher.create().id('alphabetIndexerRotate1').enabled(true))
    let button1: Component = await driver.findComponent(Matcher.create().text('ButtonRotate1').enabled(true))
    let rotate1: string = await alphabetIndexerRotate1.getInspectorInfo()
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .x, '0.000000')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .y, '0.000000')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .z, '1.000000')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .angle, '10.000000')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .centerX, '10.00vp')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .centerY, '10.00vp')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .centerZ, '10.00vp')
    assertEqual(JSON.parse(rotate1)
      .$attrs
      .rotate
      .perspective, '10.000000')
    await button1.tap()
    let rotate2: string = await alphabetIndexerRotate1.getInspectorInfo()
    assertEqual(JSON.parse(rotate2)
      .$attrs
      .rotate
      .angle, "90.000000")
    assertEqual(JSON.parse(rotate2)
      .$attrs
      .rotate
      .centerX, "90.00vp")
    assertEqual(JSON.parse(rotate2)
      .$attrs
      .rotate
      .centerY, "90.00vp")
  }, 0)
}