import { describe, beforeAll, it } from '@ohos/hypium'
import { abilityDelegatorRegistry, Driver, Component, ON } from '@kit.TestKit';
import { Point } from '@ohos.UiTest';
import {
  buttonClick,
  getToggle,
  JsonType,
  KeyStruct,
  radioClick,
  searchParentBlock,
  searchToggle,
  Slide,
  sliderDrag,
  titleSearch,
  ToggleClick,
  Search
} from '../utils';

const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()
const driver = Driver.create();

export default function WaterFlowBootcampTest() {
  describe('WaterFlowBootcampTest', () => {
    /**
     * 打开应用
     */
    beforeAll(async (done: Function) => {
      try {
        await delegator.startAbility({
          bundleName: 'cn.ohos.components',
          abilityName: 'EntryAbility'
        });
        await driver.delayMs(5000);

        let atomNavigates: Component = await driver.findComponent(ON.text('滚动与滑动'));
        await atomNavigates.click();
        await driver.delayMs(3500);

        let ListItems: Array<Component> = await driver.findComponents(ON.type('ListItem'))
        let width: Point = await ListItems[0].getBoundsCenter()
        let width2: Point = await ListItems[5].getBoundsCenter()
        await driver.swipe(width.x, width2.y, width.x, width.y, 1000)
        await driver.delayMs(3500);

        let scrollSearch: Component = await driver.findComponent(ON.text('瀑布流容器/WaterFlow'))
        await scrollSearch.click()
        await driver.delayMs(3500);

        let Buttons: Array<Component> = await driver.findComponents(ON.type('Button'));
        await Buttons[1].click()
        await driver.delayMs(3500);

      } catch (err) {
        console.info(`beforeAll error: ${JSON.stringify(err)}`);
      }
      done();
    })

    /**
     * 测试组件'layoutMode'支持设置包含单个子组件为'ALWAYS_TOP_DOWN'且获取属性正确
     */
    it('ArkUI_WaterFlow_001', 0, async (done: Function) => {
      //获取不到断言值
      await titleSearch('参数列表', 'layoutMode')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'layoutMode'支持设置包含单个子组件为'SLIDING_WINDOW'且获取属性正确
     */
    it('ArkUI_WaterFlow_002', 0, async (done: Function) => {
      //获取不到断言值
      await titleSearch('参数列表', 'layoutMode')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'layoutDirection'支持设置包含单个子组件为'Column'且获取属性正确
     */
    it('ArkUI_WaterFlow_003', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      done();
    })

    /**
     * 测试组件'layoutDirection'支持设置包含单个子组件为'ColumnReverse'且获取属性正确
     */
    it('ArkUI_WaterFlow_004', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.ColumnReverse'
      })
      done();
    })

    /**
     * 测试组件'layoutDirection'支持设置包含单个子组件为'Row'且获取属性正确
     */
    it('ArkUI_WaterFlow_005', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      done();
    })

    /**
     * 测试组件'layoutDirection'支持设置包含单个子组件为'RowReverse'且获取属性正确
     */
    it('ArkUI_WaterFlow_006', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.RowReverse'
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_007', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_008', 0, async (done: Function) => {
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_009', 0, async (done: Function) => {
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr 1fr 2fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_010', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_011', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件'columnsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_012', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Column'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'columnsTemplate')
      await radioClick({
        radioClickObj: 5,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_013', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_014', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 1,
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_015', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 2,
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr 1fr 2fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_016', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 3,
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_017', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 4,
      })
      done();
    })

    /**
     * 测试组件'rowsTemplate'支持设置包含单个子组件为'1fr 1fr 1fr 1fr 1fr'且获取属性正确
     */
    it('ArkUI_WaterFlow_018', 0, async (done: Function) => {
      await titleSearch('参数列表', 'layoutDirection')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('layoutDirection', JsonType.value),
        ],
        assertEqual: 'FlexDirection.Row'
      })
      //获取不到断言值
      await titleSearch('参数列表', 'rowsTemplate')
      await radioClick({
        radioClickObj: 5,
      })
      done();
    })

    /**
     * 测试组件'itemConstraintSize.minWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_019', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'itemConstraintSize.minWidth')
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

    /**
     * 测试组件'itemConstraintSize.maxWidth'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_020', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'itemConstraintSize.maxWidth')
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

    /**
     * 测试组件'itemConstraintSize.minHeight'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_021', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'itemConstraintSize.minHeight')
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

    /**
     * 测试组件'itemConstraintSize.maxHeight'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_022', 0, async (done: Function) => {
      //没有断言参数
      await titleSearch('参数列表', 'itemConstraintSize.maxHeight')
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

    /**
     * 测试组件'columnsGap'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_023', 0, async (done: Function) => {
      await titleSearch('参数列表', 'columnsGap')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsGap', JsonType.value),
        ],
        assertEqual: '20.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('columnsGap', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件'columnsGap'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_024', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'rowsGap')
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

    /**
     * 测试组件'enableScrollInteraction'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_WaterFlow_025', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'enableScrollInteraction')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'enableScrollInteraction'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_WaterFlow_026', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'enableScrollInteraction')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollForward'支持设置包含单个子组件为'NestedScrollMode.SELF_ONLY'且获取属性正确
     */
    it('ArkUI_WaterFlow_027', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollForward'支持设置包含单个子组件为'NestedScrollMode.SELF_FIRST'且获取属性正确
     */
    it('ArkUI_WaterFlow_028', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollForward'支持设置包含单个子组件为'NestedScrollMode.PARENT_FIRST'且获取属性正确
     */
    it('ArkUI_WaterFlow_029', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollForward'支持设置包含单个子组件为'NestedScrollMode.PARALLEL'且获取属性正确
     */
    it('ArkUI_WaterFlow_030', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollForward')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollForward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollBackward'支持设置包含单个子组件为'NestedScrollMode.SELF_ONLY'且获取属性正确
     */
    it('ArkUI_WaterFlow_031', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_ONLY'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollBackward'支持设置包含单个子组件为'NestedScrollMode.SELF_FIRST'且获取属性正确
     */
    it('ArkUI_WaterFlow_032', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.SELF_FIRST'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollBackward'支持设置包含单个子组件为'NestedScrollMode.PARENT_FIRST'且获取属性正确
     */
    it('ArkUI_WaterFlow_033', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARENT_FIRST'
      })
      done();
    })

    /**
     * 测试组件'nestedScroll.scrollBackward'支持设置包含单个子组件为'NestedScrollMode.PARALLEL'且获取属性正确
     */
    it('ArkUI_WaterFlow_034', 0, async (done: Function) => {
      await titleSearch('参数列表', 'nestedScroll.scrollBackward')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('nestedScroll', JsonType.obj),
          new KeyStruct('scrollBackward', JsonType.value),
        ],
        assertEqual: 'NestedScrollMode.PARALLEL'
      })
      done();
    })

    /**
     * 测试组件'friction'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_035', 0, async (done: Function) => {
      await titleSearch('参数列表', 'friction')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('friction', JsonType.value),
        ],
        assertEqual: 0.75
      })
      done();
    })

    /**
     * 测试组件'cachedCount'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_036', 0, async (done: Function) => {
      await titleSearch('参数列表', 'cachedCount')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 30
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('cachedCount', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'fadingEdge'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_WaterFlow_037', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'fadingEdge'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_WaterFlow_038', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('fadingEdge', JsonType.value),
        ],
        assertEqual: false
      })
      done();
    })

    /**
     * 测试组件'fadingEdge.length'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_039', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length')
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

    /**
     * 测试组件'fadingEdge.length.unit'支持设置包含单个子组件为'LengthUnit.PX'且获取属性正确
     */
    it('ArkUI_WaterFlow_040', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length.unit')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'fadingEdge.length.unit'支持设置包含单个子组件为'LengthUnit.VP'且获取属性正确
     */
    it('ArkUI_WaterFlow_041', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length.unit')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'fadingEdge.length.unit'支持设置包含单个子组件为'LengthUnit.FP'且获取属性正确
     */
    it('ArkUI_WaterFlow_042', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length.unit')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'fadingEdge.length.unit'支持设置包含单个子组件为'LengthUnit.PERCENT'且获取属性正确
     */
    it('ArkUI_WaterFlow_043', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length.unit')
      await radioClick({
        radioClickObj: 3,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'fadingEdge.length.unit'支持设置包含单个子组件为'LengthUnit.LPX'且获取属性正确
     */
    it('ArkUI_WaterFlow_044', 0, async (done: Function) => {
      await titleSearch('参数列表', 'fadingEdge')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      //获取不到断言参数
      await titleSearch('参数列表', 'fadingEdge.length.unit')
      await radioClick({
        radioClickObj: 4,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'width'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_045', 0, async (done: Function) => {
      await titleSearch('参数列表', 'width')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '600.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })

    /**
     * 测试组件'height'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_046', 0, async (done: Function) => {
      await titleSearch('参数列表', 'height')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '400.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '50.00vp'
      })
      done();
    })

    /**
     * 测试组件'padding'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_047', 0, async (done: Function) => {
      await titleSearch('参数列表', 'padding')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '50.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件'padding'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_048', 0, async (done: Function) => {
      await titleSearch('参数列表', 'margin')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为1号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_049', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF0A59F7'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为2号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_050', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 1,
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF646AFD'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为3号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_051', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 2,
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFE7062'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为4号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_052', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 3,
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFE9E8ED'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为5号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_053', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 4,
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FF1C1C1C'
      })
      done();
    })

    /**
     * 测试组件'borderColor'支持设置页签容器的颜色为6号色显示且获取属性正确
     */
    it('ArkUI_WaterFlow_054', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderColor')
      await buttonClick({
        buttonClickObj: 5,
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderColor', JsonType.value),
        ],
        assertEqual: '#FFFFFFFF'
      })
      done();
    })

    /**
     * 测试组件'borderRadius'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_055', 0, async (done: Function) => {
      await titleSearch('参数列表', 'borderRadius')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderRadius', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('borderRadius', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })

    /**
     * 测试组件'borderStyle'支持设置包含单个子组件为'Solid'且获取属性正确
     */
    it('ArkUI_WaterFlow_056', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'borderStyle'支持设置包含单个子组件为'Dotted'且获取属性正确
     */
    it('ArkUI_WaterFlow_057', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
      })
      done();
    })

    /**
     * 测试组件'borderStyle'支持设置包含单个子组件为'Dashed'且获取属性正确
     */
    it('ArkUI_WaterFlow_058', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'borderStyle')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
      })
      done();
    })

    /**
     * 测试组件'flexBasis'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_059', 0, async (done: Function) => {
      //获取不到断言参数
      await titleSearch('参数列表', 'flexBasis')
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

    /**
     * 测试组件'opacity'支持设置页签容器的数据值且获取属性正确
     */
    it('ArkUI_WaterFlow_060', 0, async (done: Function) => {
      await titleSearch('参数列表', 'opacity')
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 1
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('opacity', JsonType.value),
        ],
        assertEqual: 0
      })
      done();
    })

    /**
     * 测试组件'visibility'支持设置包含单个子组件为'None'且获取属性正确
     */
    it('ArkUI_WaterFlow_061', 0, async (done: Function) => {
      await titleSearch('参数列表', 'visibility')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'visibility'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.None'
      })
      done();
    })

    /**
     * 测试组件'visibility'支持设置包含单个子组件为'Hidden'且获取属性正确
     */
    it('ArkUI_WaterFlow_062', 0, async (done: Function) => {
      await titleSearch('参数列表', 'visibility')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'visibility'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Hidden'
      })
      done();
    })

    /**
     * 测试组件'visibility'支持设置包含单个子组件为'Visible'且获取属性正确
     */
    it('ArkUI_WaterFlow_063', 0, async (done: Function) => {
      await titleSearch('参数列表', 'visibility')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
          toggleClickObj: 'visibility'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('visibility', JsonType.value),
        ],
        assertEqual: 'Visibility.Visible'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Auto'且获取属性正确
     */
    it('ArkUI_WaterFlow_064', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Auto'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Ltr'且获取属性正确
     */
    it('ArkUI_WaterFlow_065', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Ltr'
      })
      done();
    })

    /**
     * 测试组件'direction'支持设置包含单个子组件为'Rtl'且获取属性正确
     */
    it('ArkUI_WaterFlow_066', 0, async (done: Function) => {
      await titleSearch('参数列表', 'direction')
      await radioClick({
        radioClickObj: 2,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'direction'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('direction', JsonType.value),
        ],
        assertEqual: 'Direction.Rtl'
      })
      done();
    })

    /**
     * 测试组件'clip'支持设置包含单个子组件为'true'且获取属性正确
     */
    it('ArkUI_WaterFlow_067', 0, async (done: Function) => {
      await titleSearch('参数列表', 'clip')
      await radioClick({
        radioClickObj: 0,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'clip'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'true'
      })
      done();
    })

    /**
     * 测试组件'clip'支持设置包含单个子组件为'false'且获取属性正确
     */
    it('ArkUI_WaterFlow_068', 0, async (done: Function) => {
      await titleSearch('参数列表', 'clip')
      await radioClick({
        radioClickObj: 1,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
          toggleClickObj: 'clip'
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('clip', JsonType.value),
        ],
        assertEqual: 'false'
      })
      done();
    })

    /**
     * 测试组件width且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0001', 0, async (done: Function) => {
      await titleSearch('基础属性', 'width');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('width', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })
    /**
     * 测试组件height且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0002', 0, async (done: Function) => {
      await titleSearch('基础属性', 'height');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '500.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('height', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })
      done();
    })
    /**
     * 测试组件padding且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0003', 0, async (done: Function) => {
      await titleSearch('基础属性', 'padding');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('padding', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    /**
     * 测试组件margin且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0004', 0, async (done: Function) => {
      await titleSearch('基础属性', 'margin');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '100.00vp'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('margin', JsonType.value),
        ],
        assertEqual: '0.00vp'
      })
      done();
    })
    /**
     * 测试开启constraintSize
     */
    it('ArkUI_WaterFlow_Comp_0005', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      await toggle[0].click()
      await driver.delayMs(3500);
      done();
    })
    /**
     * 测试组件constraintSize.minWidth且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0006', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"500.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"100.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })
      done();
    })
    /**
     * 测试组件constraintSize.minHeight且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0007', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.minHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open,
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"500.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"100.00vp","maxWidth":"Infinityvp","maxHeight":"Infinityvp"}'
      })
      done();
    })
    /**
     * 测试组件constraintSize.maxWidth且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0008', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxWidth');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"500.00vp","maxHeight":"Infinityvp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"100.00vp","maxHeight":"Infinityvp"}'
      })
      done();
    })
    /**
     * 测试组件constraintSize.maxHeight且获取属性正确
     */
    it('ArkUI_WaterFlow_Comp_0009', 0, async (done: Function) => {
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Component =
        await driver.findComponent(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')))
      if (await toggle.isChecked() === false) {
        await toggle.click();
      }
      await titleSearch('基础属性', 'constraintSize.maxHeight');
      await sliderDrag({
        slideStar: Slide.start,
        toggleClick: {
          toggleClickType: ToggleClick.Open
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"500.00vp"}'
      })

      await sliderDrag({
        slideStar: Slide.end,
        toggleClick: {
          toggleClickType: ToggleClick.Close
        },
        id: 'WaterFlow',
        arr: [
          new KeyStruct('$attrs', JsonType.obj),
          new KeyStruct('constraintSize', JsonType.obj)
        ],
        assertEqual: '{"minWidth":"0.00vp","minHeight":"0.00vp","maxWidth":"Infinityvp","maxHeight":"100.00vp"}'
      })
      done();
    })
    /**
     * 测试关闭constraintSize,无断言
     */
    it('ArkUI_WaterFlow_Comp_0010', 0, async (done: Function) => {
      // 无断言
      await titleSearch('基础属性', 'constraintSize');
      let toggle: Array<Component> =
        await driver.findComponents(ON.type('Toggle').within(ON.type('Scroll')).isAfter(ON.text('constraintSize')));
      if (await toggle[0].isChecked() === true) {
        await toggle[0].click()
      }
      await driver.delayMs(3500);
      done();
    })
  })
}