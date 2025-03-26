import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  Search,
  searchParentBlock,
  searchRadio,
  titleSearch,
  getToggle,
  searchToggle
} from '../../utils/index';
import { On, Point } from '@ohos.UiTest';


/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function RowBootcampTest() {
  describe('RowBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('行列与堆叠'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('横向布局/Row'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
    })
    beforeEach(() => {
      // Presets an action, which is performed before each unit test case starts.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: preset action function.
    })
    afterEach(() => {
      // Presets a clear action, which is performed after each unit test case ends.
      // The number of execution times is the same as the number of test cases defined by **it**.
      // This API supports only one parameter: clear action function.
    })
    afterAll(() => {
      // Presets a clear action, which is performed after all test cases of the test suite end.
      // This API supports only one parameter: clear action function.
    })
    it('ArkUI_Row_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'space');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Row',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value)
        ],
        assertEqual: '0.00vp'
      })
      done();

    })
    it('ArkUI_Row_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'Row',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'VerticalAlign.Top'
      })
      done();
    })
    it('ArkUI_Row_0003', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Row',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'VerticalAlign.Center'
      })
      done();
    })
    it('ArkUI_Row_0004', 0, async (done: Function) => {
      await searchParentBlock('alignItems', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignItems', JsonType.value)
        ],
        assertEqual: 'VerticalAlign.Bottom'
      })
      await searchParentBlock('alignItems', false, '参数列表');
      done();
    })
    it('ArkUI_Row_0005', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Start'
      })
      done();
    })
    it('ArkUI_Row_0006', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.Center'
      })
      done();
    })
    it('ArkUI_Row_0007', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 2,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.End'
      })
      done();
    })
    it('ArkUI_Row_0008', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 3,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceBetween'
      })
      done();
    })
    it('ArkUI_Row_0009', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 4,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceAround'
      })
      done();
    })
    it('ArkUI_Row_0010', 0, async (done: Function) => {
      await searchParentBlock('justifyContent', true, '参数列表');
      await radioClick({
        radioClickObj: 5,
        id: 'Row',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'justifyContent'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('justifyContent', JsonType.value)
        ],
        assertEqual: 'FlexAlign.SpaceEvenly'
      })
      await searchParentBlock('justifyContent', false, '参数列表');
      done();
    })
    it('ArkUI_Row_0011', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('isReversed', true, '参数列表');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'isReversed'
        }
      })
      done();
    })
    it('ArkUI_Row_0012', 0, async (done: Function) => {
      // 获取不到
      await searchParentBlock('isReversed', true, '参数列表');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'isReversed'
        }
      })
      done();
    })
    it('ArkUI_Row_0013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'flexBasis');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'Row',
        toggleClick: {
          toggleClickObj: 'flexBasis'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value)
        ],
        assertEqual: '200.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'Row',
        toggleClick: {
          toggleClickObj: 'flexBasis',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('flexBasis', JsonType.value)
        ],
        assertEqual: '10.00vp'
      })
      done();

    })
  })
}