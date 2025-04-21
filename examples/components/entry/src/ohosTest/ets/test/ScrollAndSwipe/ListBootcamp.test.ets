import { describe, beforeAll, beforeEach, afterEach, afterAll, it, expect } from '@ohos/hypium'
import { abilityDelegatorRegistry, Component, Driver, ON } from '@kit.TestKit';

import {
  buttonClick,
  JsonType,
  Search,
  KeyStruct,
  radioClick,
  Slide,
  sliderDrag,
  ToggleClick,
  scroll,
  titleSearch,
  searchToggle,
  getToggle,
  searchParentBlock
} from '../../utils';
import { Point } from '@ohos.UiTest';

const TAG = 'ListBootcampTest'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();


export default function ListBootcampTest() {
  describe('ListBootcampTest', () => {
    // Defines a test suite. Two parameters are supported: test suite name and test suite function.
    beforeAll(async (done: Function) => {
      // Presets an action, which is performed only once before all test cases of the test suite start.
      // This API supports only one parameter: preset action function.
      console.info('beforeAll begin');

      try {

        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });

        await driver.delayMs(5000);
        console.info(TAG + 'ListBootcamp001' + ' begin');

        let atomDisplays: Component = await driver.findComponent(ON.text('滚动与滑动'));
        await atomDisplays.click();
        await driver.delayMs(1000);

        let scrollSearch: Component = await driver.findComponent(ON.text('列表/List'))
        await scrollSearch.click()
        await driver.delayMs(1000);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(1000);

      } catch (err) {

        console.info(`beforeAll error: ${JSON.stringify(err)}`);

      }
      console.info(`beforeAll end`);
      done();
    })

    /**
     * 测试组件space
     */
    it('ArkUI_List_001', 0, async (done: Function) => {
      await titleSearch('参数列表', 'space')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('space', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })

    // initialIndex
    it('ArkUI_List_002', 0, async (done: Function) => {
      await titleSearch('参数列表', 'initialIndex')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialIndex', JsonType.value),
        ],
        assertEqual: '5'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('initialIndex', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();

    })

    // cachedCount
    it('ArkUI_List_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'cachedCount')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: '50'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: '0'
      })

      done();

    })

    // edgeEffect.options.alwaysEnabled
    it('ArkUI_List_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'edgeEffect.options.alwaysEnabled')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })

    it('ArkUI_List_005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'edgeEffect.options.alwaysEnabled')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('edgeEffectOptions', JsonType.obj),
          new KeyStruct('alwaysEnabled', JsonType.value),
        ],
        assertEqual: false
      })

      done();

    })

    // chainAnimation
    it('ArkUI_List_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'chainAnimation')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('chainAnimation', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })

    it('ArkUI_List_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'chainAnimation')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('chainAnimation', JsonType.value),
        ],
        assertEqual: false
      })

      done();

    })

    // multiSelectable
    it('ArkUI_List_008', 0, async (done: Function) => {
      await titleSearch('参数列表', 'multiSelectable')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('multiSelectable', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })

    it('ArkUI_List_009', 0, async (done: Function) => {
      await titleSearch('参数列表', 'multiSelectable')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('multiSelectable', JsonType.value),
        ],
        assertEqual: false
      })

      done();

    })

    // lanes.minLength
    it('ArkUI_List_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'lanes.minLength')
      // 设置minLength无效果
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })

      done();

    })

    // lanes.maxLength
    it('ArkUI_List_011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'lanes.maxLength')
      // 设置maxLength无效果
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        }
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

    // lanes.gutter
    it('ArkUI_List_012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'lanes.gutter')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('laneGutter', JsonType.value),
        ],
        assertEqual: '10.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('laneGutter', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })

      done();

    })

    // alignListItem
    it('ArkUI_List_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignListItem')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignListItem', JsonType.value),
        ],
        assertEqual: 'ListItemAlign.Center'
      })

      done();

    })

    it('ArkUI_List_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignListItem')

      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignListItem', JsonType.value),
        ],
        assertEqual: 'ListItemAlign.End'
      })

      done();

    })

    it('ArkUI_List_015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'alignListItem')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('alignListItem', JsonType.value),
        ],
        assertEqual: 'ListItemAlign.Start'
      })

      done();

    })

    // sticky
    it('ArkUI_List_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sticky')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sticky', JsonType.value),
        ],
        assertEqual: 'StickyStyle.Header'
      })

      done();

    })

    it('ArkUI_List_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sticky')

      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sticky', JsonType.value),
        ],
        assertEqual: 'StickyStyle.Footer'
      })

      done();

    })

    it('ArkUI_List_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'sticky')

      await radioClick({
        radioClickObj: 0,
        id: 'List',
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('sticky', JsonType.value),
        ],
        assertEqual: 'StickyStyle.None'
      })

      done();

    })

    // scrollSnapAlign
    it('ArkUI_List_019', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scrollSnapAlign')

      await radioClick({
        radioClickObj: 1,
        id: 'List',
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value),
        ],
        assertEqual: 'ScrollSnapAlign.START'
      })

      done();

    })

    it('ArkUI_List_020', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scrollSnapAlign')

      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value),
        ],
        assertEqual: 'ScrollSnapAlign.CENTER'
      })

      done();

    })

    it('ArkUI_List_021', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scrollSnapAlign')

      await radioClick({
        radioClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value),
        ],
        assertEqual: 'ScrollSnapAlign.END'
      })

      done();

    })

    it('ArkUI_List_022', 0, async (done: Function) => {
      await titleSearch('参数列表', 'scrollSnapAlign')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('scrollSnapAlign', JsonType.value),
        ],
        assertEqual: 'ScrollSnapAlign.NONE'
      })

      done();

    })

    // enableScrollInteraction
    it('ArkUI_List_023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'enableScrollInteraction')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableScrollInteraction', JsonType.value),
        ],
        assertEqual: true
      })

      done();

    })

    it('ArkUI_List_024', 0, async (done: Function) => {
      await titleSearch('参数列表', 'enableScrollInteraction')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('enableScrollInteraction', JsonType.value),
        ],
        assertEqual: false
      })

      done();

    })

    //nestedScroll.scrollForward
    it('ArkUI_List_025', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      })

      done();

    })

    it('ArkUI_List_026', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      })

      done();

    })

    it('ArkUI_List_027', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      })

      done();

    })

    it('ArkUI_List_028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      })

      done();

    })

    // nestedScroll.scrollBackward
    it('ArkUI_List_029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      })

      done();

    })

    it('ArkUI_List_030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 2,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      })

      done();

    })

    it('ArkUI_List_031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 3,
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      })

      done();

    })

    it('ArkUI_List_032', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')

      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      })

      done();

    })

    // friction
    it('ArkUI_List_033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'friction')

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 0.75
      })

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 5
      })

      done();

    })

    // contentStartOffset
    it('ArkUI_List_034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'contentStartOffset')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentStartOffset', JsonType.value),
        ],
        assertEqual: "200.000000"
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentStartOffset', JsonType.value),
        ],
        assertEqual: "0.000000"
      })

      done();

    })

    // contentEndOffset
    it('ArkUI_List_035', 0, async (done: Function) => {
      await titleSearch('参数列表', 'contentEndOffset')

      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentEndOffset', JsonType.value),
        ],
        assertEqual: "200.000000"
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'List',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('contentEndOffset', JsonType.value),
        ],
        assertEqual: "0.000000"
      })

      done();

    })

    // childrenMainSize
    it('ArkUI_List_036', 0, async (done: Function) => {
      await titleSearch('参数列表', 'childrenMainSize')
      //childrenMainSize值无法获取
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })

      done();

    })

    it('ArkUI_List_037', 0, async (done: Function) => {
      await titleSearch('参数列表', 'childrenMainSize')
      //childrenMainSize值无法获取
      await radioClick({
        radioClickObj: 1,
      })

      done();

    })

    it('ArkUI_List_038', 0, async (done: Function) => {
      await titleSearch('参数列表', 'childrenMainSize')
      //childrenMainSize值无法获取
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        }
      })

      done();

    })

  })
}