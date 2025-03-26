import { abilityDelegatorRegistry, Driver,Component,ON} from '@kit.TestKit';
import {Point } from '@ohos.UiTest';

const TAG = 'MenuItemGroupBootcamp001'

/*获取AbilityDelegator实例,管理Ability的生命周期和事件*/
const delegator: abilityDelegatorRegistry.AbilityDelegator = abilityDelegatorRegistry.getAbilityDelegator()

/*初始化与UI元素交互的驱动对象*/
const driver = Driver.create();

export async function MenuItemGroupStart(done:Function) {
  await delegator.startAbility({
    bundleName: 'cn.ohos.components',
    abilityName: 'EntryAbility'
  });

  await driver.delayMs(3500);
  console.info(TAG + 'MenuItemGroupBootcamp001' + ' begin');

  let ListItemGroup: Array<Component> = await driver.findComponents(ON.type('ListItemGroup'))
  console.info(TAG + 'ListItemGroup' + ListItemGroup.toString());
  let ListItemGroup1: Point = await ListItemGroup[0].getBoundsCenter()
  let ListItemGroup2: Point = await ListItemGroup[2].getBoundsCenter()
  await driver.swipe(ListItemGroup1.x, ListItemGroup2.y, ListItemGroup1.x, ListItemGroup1.y, 2000)
  await driver.delayMs(3500);

  let atomDisplays: Component = await driver.findComponent(ON.text('菜单'));
  await atomDisplays.click();
  await driver.delayMs(4000);


  let scrollSearch: Component = await driver.findComponent(ON.text('菜单分组/MenuItemGroup'))
  await scrollSearch.click()
  await driver.delayMs(1000);

  let Buttons: Component[] = await driver.findComponents(ON.type('Button'));
  await Buttons[1].click()
  await driver.delayMs(1000);


  console.info(`beforeAll end`);
  done();
}

