/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { describe, it, expect, beforeAll } from '@ohos/hypium';
// 导入测试依赖kit
import { abilityDelegatorRegistry, Driver, ON, MouseButton, Component, MatchPattern } from '@kit.TestKit';
import { UIAbility, Want } from '@kit.AbilityKit';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator();
const bundleName = abilityDelegatorRegistry.getArguments().bundleName;
let want: Want;

export default function IndexTest() {

  describe('IndexTest', () => {

    beforeAll(async () => {
      want = {
        bundleName: bundleName,
        abilityName: 'EntryAbility'
      };
      await delegator.startAbility(want);
      let driver = Driver.create();
      await driver.delayMs(1000);
      const ability: UIAbility = await delegator.getCurrentTopAbility();
      console.info('get top ability');
      expect(ability.context.abilityInfo.name).assertEqual('EntryAbility');
    })

    /**
     * @tc.number UiTest_001
     * @tc.name testTapGesture
     * @tc.desc 测试点击手势示例
     */
    it('testTapGesture', 0, async (done: Function) => {
      console.info('uitest: testTapGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('TapGesture', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testTapGesture end');
      done();
    })

    /**
     * @tc.number UiTest_002
     * @tc.name testLongPressGesture
     * @tc.desc 测试长按手势示例
     */
    it('testLongPressGesture', 0, async (done: Function) => {
      console.info('uitest: testLongPressGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('LongPressGesture', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.longClick();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('longPressGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testLongPressGesture end');
      done();
    })

    /**
     * @tc.number UiTest_003
     * @tc.name testPanGesture
     * @tc.desc 测试滑动手势示例
     */
    it('testPanGesture', 0, async (done: Function) => {
      console.info('uitest: testPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('PanGesture', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(200, 600, 250, 600, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_004
     * @tc.name testPinchGesture
     * @tc.desc 测试捏合手势示例
     */
    it('testPinchGesture', 0, async (done: Function) => {
      console.info('uitest: testPinchGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('PinchGesture', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.pinchIn(0.5);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('pinchGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testPinchGesture end');
      done();
    })

    /**
     * @tc.number UiTest_005
     * @tc.name testSwipeGesture
     * @tc.desc 测试快滑手势示例
     */
    it('testSwipeGesture', 0, async (done: Function) => {
      console.info('uitest: testSwipeGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('SwipeGesture', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(500, 800, 650, 800, 2000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('swipeGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testSwipeGesture end');
      done();
    })

    /**
     * @tc.number UiTest_006
     * @tc.name testTapGestureWithDistance
     * @tc.desc 测试带距离阈值的点击手势示例
     */
    it('testTapGestureWithDistance', 0, async (done: Function) => {
      console.info('uitest: testTapGestureWithDistance begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('TapGestureWithDistance', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('createTapGestureWithDistanceThreshold is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testTapGestureWithDistance end');
      done();
    })

    /**
     * @tc.number UiTest_007
     * @tc.name testHorizontalPanGesture
     * @tc.desc 测试水平方向的滑动手势示例
     */
    it('testHorizontalPanGesture', 0, async (done: Function) => {
      console.info('uitest: testHorizontalPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Pan-Horizontal', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(500, 1000, 650, 1000, 2000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testHorizontalPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_008
     * @tc.name testVerticalPanGesture
     * @tc.desc 测试垂直方向的滑动手势示例
     */
    it('testVerticalPanGesture', 0, async (done: Function) => {
      console.info('uitest: testVerticalPanGesture begin');
      let driver = Driver.create();
      await driver.swipe(200, 1000, 250, 350, 2000);
      await driver.delayMs(1000);
      let button = await driver.findComponent(ON.text('Pan-Vertical', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(300, 400, 300, 450, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testVerticalPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_009
     * @tc.name testLeftPanGesture
     * @tc.desc 测试左方向的滑动手势示例
     */
    it('testLeftPanGesture', 0, async (done: Function) => {
      console.info('uitest: testLeftPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Pan-Left', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(600, 400, 500, 450, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testLeftPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_010
     * @tc.name testRightPanGesture
     * @tc.desc 测试右方向的滑动手势示例
     */
    it('testRightPanGesture', 0, async (done: Function) => {
      console.info('uitest: testRightPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Pan-Right', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(200, 600, 250, 600, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testRightPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_011
     * @tc.name testUpPanGesture
     * @tc.desc 测试上方向的滑动手势示例
     */
    it('testUpPanGesture', 0, async (done: Function) => {
      console.info('uitest: testUpPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Pan-Up', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(600, 600, 600, 550, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testUpPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_012
     * @tc.name testDownPanGesture
     * @tc.desc 测试下方向的滑动手势示例
     */
    it('testDownPanGesture', 0, async (done: Function) => {
      console.info('uitest: testDownPanGesture begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Pan-Down', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await driver.swipe(200, 800, 200, 850, 1000);
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('panGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testDownPanGesture end');
      done();
    })

    /**
     * @tc.number UiTest_013
     * @tc.name testVerticalPanGesture
     * @tc.desc 测试互斥手势组示例
     */
    it('testExclusiveGroup', 0, async (done: Function) => {
      console.info('uitest: testExclusiveGroup begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Group-Exclusive', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.longClick();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('longPressGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testExclusiveGroup end');
      done();
    })

    /**
     * @tc.number UiTest_014
     * @tc.name testParallelGroup
     * @tc.desc 测试并行手势组示例
     */
    it('testParallelGroup', 0, async (done: Function) => {
      console.info('uitest: testParallelGroup begin');
      let driver = Driver.create();
      await driver.swipe(200, 1000, 250, 350, 2000);
      await driver.delayMs(1000);
      let button = await driver.findComponent(ON.text('Group-Parallel', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.longClick();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('longPressGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testParallelGroup end');
      done();
    })

    /**
     * @tc.number UiTest_015
     * @tc.name testNormalMask
     * @tc.desc 测试普通响应方式示例
     */
    it('testNormalMask', 0, async (done: Function) => {
      console.info('uitest: testNormalMask begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('NORMAL_GESTURE_MASK', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testNormalMask end');
      done();
    })

    /**
     * @tc.number UiTest_016
     * @tc.name testIgnoreInternalMask
     * @tc.desc 测试忽略子组件响应方式示例
     */
    it('testIgnoreInternalMask', 0, async (done: Function) => {
      console.info('uitest: testIgnoreInternalMask begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('IGNORE_INTERNAL_GESTURE_MASK', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testIgnoreInternalMask end');
      done();
    })

    /**
     * @tc.number UiTest_017
     * @tc.name testNormalPriority
     * @tc.desc 测试普通优先级手势示例
     */
    it('testNormalPriority', 0, async (done: Function) => {
      console.info('uitest: testNormalPriority begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Priority-Normal', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testNormalPriority end');
      done();
    })

    /**
     * @tc.number UiTest_018
     * @tc.name testParallelPriority
     * @tc.desc 测试并行优先级手势示例
     */
    it('testParallelPriority', 0, async (done: Function) => {
      console.info('uitest: testParallelPriority begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Priority-Parallel', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testParallelPriority end');
      done();
    })

    /**
     * @tc.number UiTest_019
     * @tc.name testHighPriority
     * @tc.desc 测试高优先级手势示例
     */
    it('testHighPriority', 0, async (done: Function) => {
      console.info('uitest: testHighPriority begin');
      let driver = Driver.create();
      let button = await driver.findComponent(ON.text('Priority-Priority', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testHighPriority end');
      done();
    })

    /**
     * @tc.number UiTest_020
     * @tc.name testJudgeBegin
     * @tc.desc 测试自定义手势判断示例
     */
    it('testJudgeBegin', 0, async (done: Function) => {
      console.info('uitest: testJudgeBegin begin');
      let driver = Driver.create();
      await driver.swipe(200, 1000, 250, 500, 2000);
      await driver.delayMs(1000);
      let button = await driver.findComponent(ON.text('JudgeBeginTest', MatchPattern.CONTAINS));
      expect(button === null).assertFalse();
      await button.click();
      await driver.delayMs(1000);
      let result = await driver.findComponent(ON.text('tapGesture is called', MatchPattern.CONTAINS));
      expect(result === null).assertFalse();
      await driver.delayMs(1000);
      console.info('uitest: testJudgeBegin end');
      done();
    })
  })
}