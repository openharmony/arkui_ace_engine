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


export default function GridRowBootcampTest() {
  describe('GridRowBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {

      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(1500);

        let atomDisplays: Component = await driver.findComponent(ON.text('栅格与分栏'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('栅格行/GridRow'))
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
    it('ArkUI_GridRow_0001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '20'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '20'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columns.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'columns.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columns', JsonType.value)
        ],
        assertEqual: '12'
      })
      done();

    })
    it('ArkUI_GridRow_0007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '30.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '30.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.x.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.x.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('x', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.xs');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xs'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '30.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xs',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.sm');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.sm'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '30.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.sm',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.md');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.md'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.md',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.lg');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.lg'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.lg',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.xl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'gutter.y.xxl');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xxl'
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })

      await sliderDrag({
        slideStar: Slide.end,
        id: 'GridRow',
        toggleClick: {
          toggleClickObj: 'gutter.y.xxl',
          toggleClickType: ToggleClick.Close
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('gutter', JsonType.obj),
          new KeyStruct('y', JsonType.value)
        ],
        assertEqual: '0.000000'
      })
      done();

    })
    it('ArkUI_GridRow_0019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.value');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'breakpoints.value'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: ['100vp', '200vp']
      })
      done();
    })
    it('ArkUI_GridRow_0020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.value');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'breakpoints.value'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: ['320vp', '600vp', '840vp']
      })
      done();
    })
    it('ArkUI_GridRow_0021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.value');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'breakpoints.value'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: ['400vp', '600vp', '800vp']
      })
      done();
    })
    it('ArkUI_GridRow_0022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.value');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'breakpoints.value'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('value', JsonType.value)
        ],
        assertEqual: ['320vp', '600vp', '840vp', '1080vp']
      })
      done();
    })
    it('ArkUI_GridRow_0023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.reference');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'breakpoints.reference'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('reference', JsonType.value)
        ],
        assertEqual: 'BreakPointsReference.WindowSize'
      })
      done();
    })
    it('ArkUI_GridRow_0024', 0, async (done: Function) => {
      await titleSearch('参数列表', 'breakpoints.reference');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'breakpoints.reference'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('breakpoints', JsonType.obj),
          new KeyStruct('reference', JsonType.value)
        ],
        assertEqual: 'BreakPointsReference.ComponentSize'
      })
      done();
    })
    it('ArkUI_GridRow_0025', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'GridRow.direction');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'GridRow.direction'
        }
      })
      done();
    })
    it('ArkUI_GridRow_0026', 0, async (done: Function) => {
      // 获取不到
      await titleSearch('参数列表', 'GridRow.direction');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'GridRow.direction'
        }
      })
      done();
    })
    it('ArkUI_GridRow_0027', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'alignItems'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemAlign', JsonType.value)
        ],
        assertEqual: "ItemAlign.Start"
      })
      done();
    })
    it('ArkUI_GridRow_0028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'alignItems'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemAlign', JsonType.value)
        ],
        assertEqual: "ItemAlign.Center"
      })
      done();
    })
    it('ArkUI_GridRow_0029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'alignItems'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemAlign', JsonType.value)
        ],
        assertEqual: "ItemAlign.End"
      })
      done();
    })
    it('ArkUI_GridRow_0030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignItems');
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'alignItems'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('itemAlign', JsonType.value)
        ],
        assertEqual: "ItemAlign.Stretch"
      })
      done();
    })
    it('ArkUI_GridRow_0031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'flexBasis');
      await sliderDrag({
        slideStar: Slide.start,
        id: 'GridRow',
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
        id: 'GridRow',
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
    it('ArkUI_GridRow_0032', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction');
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Auto'
      })
      done();
    })
    it('ArkUI_GridRow_0033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction');
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Ltr'
      })
      done();
    })
    it('ArkUI_GridRow_0034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction');
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'direction'
        },
        id: 'GridRow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value)
        ],
        assertEqual: 'Direction.Rtl'
      })
      done();
    })
  })
}