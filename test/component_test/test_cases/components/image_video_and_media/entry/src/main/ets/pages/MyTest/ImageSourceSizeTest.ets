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

/*
* Image组件 SourceSize属性
* 找到画面id为imageSourceSize1,imageSourceSize2,imageSourceSize3的Image组件
* 获取image1的SourceSize属性与期待值[10.00 x 10.00]比对
* 获取image2的SourceSize属性与期待值[10.00 x 10.00]比对
* 获取image3的SourceSize属性与期待值[1000.00 x 1000.00]比对
*/

export default async function imageSourceSizeTest() {
  defineTest('imageSourceSizeTestDemo', {
    level: TestCaseLevel.LEVEL0
  }, async () => {
    console.log("imageSourceSizeTestDemo running")
    let driver: Tester = Tester.create()
    let image1: Component = await driver.findComponent(Matcher.create().id('imageSourceSize1').enabled(true))
    let image2: Component = await driver.findComponent(Matcher.create().id('imageSourceSize2').enabled(true))
    let image3: Component = await driver.findComponent(Matcher.create().id('imageSourceSize3').enabled(true))
    let sourceSize1: string = await image1.getInspectorInfo()
    assertEqual(JSON.parse(sourceSize1).$attrs.sourceSize, "[10.00 x 10.00]")
    let sourceSize2: string = await image2.getInspectorInfo()
    assertEqual(JSON.parse(sourceSize2).$attrs.sourceSize, "[10.00 x 10.00]")
    let sourceSize3: string = await image3.getInspectorInfo()
    assertEqual(JSON.parse(sourceSize3).$attrs.sourceSize, "[1000.00 x 1000.00]")
  }, 0)
}