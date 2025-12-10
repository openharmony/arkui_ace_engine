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

import deviceInfo from '@ohos.deviceInfo';
import { Entry, Text, BuilderParam, LaunchMode, Builder,PopInfo,NavigationInterception,Callback,Component, NavPathStack, TouchType, Navigation,NavPathInfo, NavDestination, NavigationMode, NavigationOptions, AttributeModifier, NavigationAttribute, Percentage} from '@ohos.arkui.component'  // TextAttribute should be insert by ui-plugins
import { State, Observed, ObjectLink, Link } from '@ohos.arkui.stateManagement' // should be insert by ui-plugins
import hilog from '@ohos.hilog'
import mediaquery from '@ohos.mediaquery';
import display from '@ohos.display';

const TAG = 'DeviceHelper';

/**
 * device info util
 *
 */
export class DeviceHelper {
  static readonly TYPE_DEFAULT = 'default';
  static readonly TYPE_PHONE = 'phone';
  static readonly TYPE_TABLET = 'tablet';
  static readonly DEVICE_TYPE = deviceInfo.deviceType;

  /**
   * whether the device type is phone
   *
   * @returns true if is phone
   */
  static isPhone(): boolean {
    return (DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_PHONE ||
      DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_DEFAULT);
  }

  /**
   * whether the device type is tablet
   *
   * @returns true if is tablet
   */
  public static isTablet(): boolean {
    return DeviceHelper.DEVICE_TYPE === DeviceHelper.TYPE_TABLET;
  }

  /**
   * Check if is foldable
   *
   * @returns true if is foldable
   */
  static isFold(): boolean {
    let isFold: boolean = false;
    try {
      isFold = display.isFoldable();
    } catch (e) {
      hilog.error(0x0000, TAG, 'isFold -> isFoldable try error:', e);
    }
    return isFold;
  }

  /**
   * Check if is expanded
   *
   * @returns true if is expanded
   */
  static isExpanded(): boolean {
    let isExpanded: boolean = false;
    try {
      isExpanded = display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED;
    } catch (e) {
      hilog.error(0x0000, TAG, 'isExpanded -> try error:', e);
    }
    return isExpanded;
  }

  /**
   * Check if is column
   *
   * @returns true if is column
   */
  static isColumn(): boolean {
    let isColumn: boolean = false;
    try {
      isColumn = display.isFoldable() && (display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_EXPANDED ||
        display.getFoldStatus() === display.FoldStatus.FOLD_STATUS_HALF_FOLDED);
    } catch (e) {
      hilog.error(0x0000, TAG, 'isColumn -> try error:', e);
    }
    return isColumn;
  }

  /**
   * Check if is straight product
   *
   * @returns true if is straight product
   */
  public static isStraightProduct(): boolean {
    return DeviceHelper.isPhone() && !DeviceHelper.isFold();
  }
}

export class DeviceListenerManager {
  private static instance: DeviceListenerManager | undefined;
  private portraitListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(orientation: portrait)');
  private drawableWidthLargeListener: mediaquery.MediaQueryListener = mediaquery.matchMediaSync('(width >= 600vp)');
  private isPortrait: boolean | undefined = undefined;
  private onOrientationChange: (val:boolean | undefined) => void = (val:boolean | undefined) => {};
  private isLarge: boolean | undefined = undefined;
  private onDrawableWidthChange: (val:boolean | undefined) => void = (val:boolean | undefined) => {};

  public static getInstance(): DeviceListenerManager {
    if (DeviceListenerManager.instance === undefined) {
      DeviceListenerManager.instance = new DeviceListenerManager();
    }
    return DeviceListenerManager.instance as DeviceListenerManager;
  }

  public onPortraitChange(result: mediaquery.MediaQueryResult) {
    let isChanged: boolean = false;
    if (DeviceListenerManager.getInstance().isPortrait === undefined) {
      DeviceListenerManager.getInstance().isPortrait = result.matches;
      isChanged = true;
    } else {
      if (result.matches) {
        if (!DeviceListenerManager.getInstance().isPortrait) {
          DeviceListenerManager.getInstance().isPortrait = true;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display portrait');
        }
      } else {
        if (DeviceListenerManager.getInstance().isPortrait) {
          DeviceListenerManager.getInstance().isPortrait = false;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display landscape');
        }
      }
    }
    if (isChanged) {
      DeviceListenerManager.getInstance().notifyOrientationChange();
    }
  }

  private notifyOrientationChange() {
    this.onOrientationChange(this.isPortrait);
  }

  public onDrawableWidthLargeChange(result: mediaquery.MediaQueryResult) {
    let isChanged: boolean = false;
    if (DeviceListenerManager.getInstance().isLarge === undefined) {
      DeviceListenerManager.getInstance().isLarge = result.matches;
      isChanged = true;
    } else {
      if (result.matches) {
        if (!DeviceListenerManager.getInstance().isLarge) {
          DeviceListenerManager.getInstance().isLarge = true;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display isLarge');
        }
      } else {
        if (DeviceListenerManager.getInstance().isLarge) {
          DeviceListenerManager.getInstance().isLarge = false;
          isChanged = true;
          hilog.debug(0x0000, 'MultiNavigation', 'display not large');
        }
      }
    }

    if (isChanged) {
      DeviceListenerManager.getInstance().notifyWidthChange();
    }
  }

  private notifyWidthChange() {
    this.onDrawableWidthChange(this.isLarge);
  }

  public registerOrientationLister(func: (val: Boolean|undefined)=>void): void {
    this.onOrientationChange = func;
    if (this.isPortrait) {
      this.onOrientationChange(this.isPortrait);
    }
  }

  public unregisterOrientationLister(): void {
    this.onOrientationChange = (val:boolean | undefined) => {};
  }

  public registerDrawableWidthLister(func: (val: Boolean|undefined)=>void): void {
    this.onDrawableWidthChange = func;
    if (this.isLarge) {
      this.onDrawableWidthChange(this.isLarge);
    }
  }

  public unregisterDrawableWidthLister(): void {
    this.onDrawableWidthChange = (val:boolean | undefined) => {};
  }

  public initListener(): void {
    try {
        this.portraitListener.on('change', this.onPortraitChange);
        this.drawableWidthLargeListener.on('change', this.onDrawableWidthLargeChange);
    } catch(err) {
        console.log('multiNavigation initListener on err: ' + err);
    }
  }

  public finalizeListener() {
    try {
        this.portraitListener.off('change', this.onPortraitChange);
        this.drawableWidthLargeListener.off('change', this.onDrawableWidthLargeChange);
    } catch(err) {
        console.log('multiNavigation finalizeListener off err: ' + err);
    }
  }
}

@Observed
export class NavWidthRangeAttrModifier implements AttributeModifier<NavigationAttribute> {
  public isApplicationSet: boolean = false;
  public minHomeWidth: Percentage = '50%';
  public maxHomeWidth: Percentage = '50%';

  public applyNormalAttribute(instance: NavigationAttribute): void {
    if (this.isApplicationSet) {
      instance.navBarWidthRange([this.minHomeWidth, this.maxHomeWidth]);
    }
  }
}


@Component
export struct SubNavigation {
  @Link isPortrait: boolean;
  @State displayMode: number = 0;
  @ObjectLink multiStack: MultiNavPathStack;
  @BuilderParam navDestination: ((name: String, param: Object|undefined) => void) | undefined;
  @State primaryWidth: number | string = '50%';
  @ObjectLink needRenderIsFullScreen: NeedRenderIsFullScreen;
  @ObjectLink needRenderLeftClickCount: NeedRenderLeftClickCount;
  @ObjectLink navWidthRangeModifier: NavWidthRangeAttrModifier;
  @ObjectLink needRenderDisplayMode: NeedRenderDisplayMode;
  onNavigationModeChange?: OnNavigationModeChangeCallback = (mode: NavigationMode) => {};
  @State primaryStack: MyNavPathStack = new MyNavPathStack();
  @State secondaryStack: MyNavPathStack = new MyNavPathStack();

  @Builder
  SubNavDestination(name: string, param?: object) {
    this.navDestination!(name, param as Object);
  }

  getMode(): NavigationMode {
    this.displayMode = this.needRenderDisplayMode.displayMode;
    if (DeviceHelper.isPhone() && DeviceHelper.isStraightProduct()) {
      return NavigationMode.Stack;
    }
    if (this.displayMode === display.FoldStatus.FOLD_STATUS_UNKNOWN) {
      try {
        this.displayMode = display.getFoldStatus();
      } catch (err) {
        hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
      }
    }
    if (DeviceHelper.isTablet() && this.isPortrait) {
      console.log('SubNavigation getMode tablet portrait');
      return NavigationMode.Stack;
    }
    if (this.needRenderIsFullScreen.isFullScreen == undefined) {
      if (DeviceHelper.isPhone()) {
        return this.secondaryStack.size() > 0 && DeviceHelper.isColumn() ? NavigationMode.Auto : NavigationMode.Stack;
      }
      return this.secondaryStack.size() > 0 ? NavigationMode.Auto : NavigationMode.Stack;
    }
    return this.needRenderIsFullScreen.isFullScreen ? NavigationMode.Stack : NavigationMode.Auto;
  }

  aboutToAppear(): void {
    hilog.debug(0x0000, 'MultiNavigation', 'SubNavigation aboutToAppear param = ' + JSON.stringify(this.primaryStack));

  }

  build() {
    NavDestination() {
      Navigation(this.secondaryStack) {
        Navigation(this.primaryStack) {
        }
        .hideNavBar(true)
        .mode(NavigationMode.Stack)
        .navDestination(this.SubNavDestination)
        .hideTitleBar(true, true)
        .hideToolBar(true, true)
        .hideBackButton(true)
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            this.needRenderLeftClickCount.leftClickCount = 2;
          }
        })
      }
      .mode(this.getMode())
      .onNavigationModeChange(this.onNavigationModeChange)
      .hideBackButton(true)
      .hideTitleBar(true, true)
      .navDestination(this.SubNavDestination)
      .navBarWidth(this.primaryWidth)
      .attributeModifier(this.navWidthRangeModifier)
      .onTouch((event) => {
        if (event.type === TouchType.Down) {
          console.log('outer navigation this.outerStack.leftClickCount ' +
          this.needRenderLeftClickCount.leftClickCount);
          this.needRenderLeftClickCount.leftClickCount--;
        }
      })
    }
    .onBackPressed(() => {
      hilog.debug(0x0000, 'MultiNavigation', 'subNavigation NavDestination onBackPressed');
      if (this.multiStack && this.secondaryStack.size() === 1) {
        console.log('subNavigation NavDestination onBackPressed multiStack.pop');
        this.multiStack.pop({}, true);
        return true;
      }
      return false;
    })
    .hideTitleBar(true, true)
  }
}

export enum SplitPolicy {
  HOME_PAGE = 0,
  DETAIL_PAGE = 1,
  FULL_PAGE = 2,
  // PlACE_HOLDER_PAGE is not declared in SDK
  PlACE_HOLDER_PAGE = 3,
}

let that: MultiNavigation;

class SubNavigationStack {
  public primaryStack: MyNavPathStack = new MyNavPathStack();
  public secondaryStack: MyNavPathStack = new MyNavPathStack();
  public needRenderIsFullScreen: NeedRenderIsFullScreen = new NeedRenderIsFullScreen();
  public multiOperates:MultiNavPathStackOperate[] = [];

  public primaryNavPathStackOperate:NavPathStackOperate = {
    onSystemPop:() => {
      this.multiOperates.forEach((item) => {
        item.onPrimaryPop();
      })
    }
  }

  public secondaryNavPathStackOperate:NavPathStackOperate = {
    onSystemPop:() => {
      this.multiOperates.forEach((item) => {
        item.onSecondaryPop();
      })
      this.refreshFullScreen();
    }
  }

  constructor() {
    this.primaryStack.registerStackOperateCallback(this.primaryNavPathStackOperate);
    this.secondaryStack.registerStackOperateCallback(this.secondaryNavPathStackOperate);
  }

  public registerMultiStackOperateCallback(operate: MultiNavPathStackOperate) {
    let index = this.multiOperates.findIndex((item) => { return item === operate});
    if (index === -1) {
      this.multiOperates.push(operate);
    }
  }

  public unregisterMultiStackOperateCallback(operate: MultiNavPathStackOperate) {
    let index = this.multiOperates.findIndex((item) => { return item === operate});
    if (index !== -1) {
      this.multiOperates.splice(index, 1);
    }
  }

  public getPrimaryPolicy(): SplitPolicy | undefined {
    if (this.primaryStack.policyInfoList.length < 1) {
      return undefined;
    }
    return this.primaryStack.policyInfoList[0].policy;
  }

  public getPrimaryInfoList(): MultiNavPolicyInfo[] {
    return this.primaryStack.policyInfoList.slice();
  }

  public getSecondaryInfoList(): MultiNavPolicyInfo[] {
    return this.secondaryStack.policyInfoList.slice();
  }

  public getAllInfoLength(): int {
    return this.primaryStack.size() + this.secondaryStack.size();
  }

  public hasPrimaryInfo(): boolean {
    return this.primaryStack.size() !== 0;
  }

  public hasSecondaryInfo(): boolean {
    return this.secondaryStack.size() !== 0;
  }

  public pushPrimaryPath(policyStack: MultiNavPolicyInfo, animated?: boolean) {
    this.primaryStack.policyInfoList.push(policyStack);
    this.primaryStack.pushPath(policyStack.navInfo as NavPathInfo, animated);
    this.refreshFullScreen();
  }

  public pushSecondaryPath(policyStack: MultiNavPolicyInfo, animated?: boolean) {
    this.secondaryStack.policyInfoList.push(policyStack);
    this.secondaryStack.pushPath(policyStack.navInfo as NavPathInfo, animated);
    this.refreshFullScreen();
  }

  public removeByIndexes(indexes: int[]): void {
    if (indexes.length < 1) {
      return;
    }
    if (indexes[0] === 0) {
      console.log('SubNavigationStack removeByIndexes primaryStack');
      this.primaryStack.removeByIndexes([0]);
      this.primaryStack.policyInfoList.pop();
      this.clear(false);
      return;
    }
    if (indexes.length !== 0) {
      let slaveIndexes: int[] = [];
      indexes.forEach((value: int) => {
        slaveIndexes.push(value - 1);
      });
      this.secondaryStack.removeByIndexes(slaveIndexes);
      let tempArr: MultiNavPolicyInfo[] = []
      this.secondaryStack.policyInfoList.forEach((value, index) => {
        if (value && !slaveIndexes.includes(index)) {
          tempArr.push(value)
        }
      })
      this.secondaryStack.policyInfoList = tempArr
    }
    this.refreshFullScreen();
  }

  public removeByName(name: string): void {
    this.primaryStack.removeByName(name);
    this.primaryStack.policyInfoList = this.primaryStack.policyInfoList.filter((value) => {
      return value.navInfo?.name !== name
    });
    if (!this.hasPrimaryInfo()) {
      this.clear(false);
      return;
    }
    this.secondaryStack.removeByName(name);
    this.secondaryStack.policyInfoList = this.secondaryStack.policyInfoList.filter((value) => {
      return value.navInfo?.name !== name
    });
    this.refreshFullScreen();
  }

  public pop(animated?: boolean): NavPathInfo | undefined {
    let ret: NavPathInfo | undefined = undefined
    if (this.secondaryStack.policyInfoList.length > 0) {
      ret = this.popSecondary(animated);
    } else {
      ret = this.popPrimary(animated);
    }
    this.refreshFullScreen();
    return ret;
  }

  public clearSecondary(animated?: boolean) {
    this.secondaryStack.clear(animated);
    this.secondaryStack.policyInfoList.splice(0);
    this.refreshFullScreen();
  }

  public clearSecondaryKeepPlaceHolder(animated?: boolean) {
    this.secondaryStack.popToIndex(0, animated);
    this.secondaryStack.policyInfoList.splice(1);
    this.refreshFullScreen();
  }

  public clear(animated?: boolean) {
    this.secondaryStack.clear(animated);
    this.primaryStack.clear(animated);
    this.secondaryStack.policyInfoList.splice(0);
    this.primaryStack.policyInfoList.splice(0);
  }

  public disableAnimation(value: boolean): void {
    this.primaryStack.disableAnimation(value);
    this.secondaryStack.disableAnimation(value);
  }

  public replacePath(info: MultiNavPolicyInfo, animated?: boolean): void {
    if (this.secondaryStack.policyInfoList.length > 0) {
      this.replaceSecond(info, animated);
    } else {
      this.replacePrimary(info, animated);
    }
    this.refreshFullScreen();
  }

  public refreshFullScreen() {
    let secondInfoListLength = this.secondaryStack.policyInfoList.length
    if (secondInfoListLength > 0) {
      this.needRenderIsFullScreen.isFullScreen =
        this.secondaryStack.policyInfoList[secondInfoListLength - 1].isFullScreen;
      return;
    }
    let primaryInfoListLength = this.primaryStack.policyInfoList.length
    if (primaryInfoListLength > 0) {
      this.needRenderIsFullScreen.isFullScreen =
        this.primaryStack.policyInfoList[primaryInfoListLength - 1].isFullScreen;
    }
  }

  private replacePrimary(info: MultiNavPolicyInfo, animated?: boolean): void {
    this.primaryStack.policyInfoList.pop();
    this.primaryStack.policyInfoList.push(info)
    return this.primaryStack.replacePath(info.navInfo as NavPathInfo,
      {launchMode:LaunchMode.STANDARD,animated: animated} as NavigationOptions);
  }

  private replaceSecond(info: MultiNavPolicyInfo, animated?: boolean): void {
    this.secondaryStack.policyInfoList.pop();
    this.secondaryStack.policyInfoList.push(info)
    return this.secondaryStack.replacePath(info.navInfo as NavPathInfo, 
      {launchMode:LaunchMode.STANDARD,animated: animated} as NavigationOptions);
  }

  private popPrimary(animated?: boolean): NavPathInfo | undefined {
    this.primaryStack.policyInfoList.pop();
    return this.primaryStack.popInner(animated);
  }

  private popSecondary(animated?: boolean): NavPathInfo | undefined {
    this.secondaryStack.policyInfoList.pop();
    return this.secondaryStack.popInner(animated);
  }
}

@Component
export struct MultiNavigation {
  private foldStatusCallback: Callback<display.FoldStatus> = (data: display.FoldStatus): void => {
    console.log('foldStatusCallback data.valueOf()=' + data.valueOf());
    this.multiStack.needRenderDisplayMode.displayMode = data.valueOf();
    this.multiStack.handleRefreshPlaceHolderIfNeeded();
  };
  @State multiStack: MultiNavPathStack = new MultiNavPathStack();

  @BuilderParam navDestination: ((name: String, param: Object|undefined) => void) | undefined;
  mode: NavigationMode | undefined = undefined;
  onNavigationModeChangeCallback?: (mode: NavigationMode) => void = (mode: NavigationMode) => {};
  onHomeShowOnTop?: OnHomeShowOnTopCallback = (name: string) => {};
  @State isPortrait: boolean = false;

  @Builder
  MultiNavDestination(name: string, param?: object|SubNavigationStack) {
    if (name === 'SubNavigation' && param) {
      SubNavigation({
        isPortrait: this.isPortrait,
        multiStack: this.multiStack,
        navDestination: this.navDestination,
        needRenderIsFullScreen: (param as SubNavigationStack).needRenderIsFullScreen,
        primaryStack: (param as SubNavigationStack).primaryStack,
        secondaryStack: (param as SubNavigationStack).secondaryStack,
        needRenderLeftClickCount: this.multiStack.needRenderLeftClickCount,
        navWidthRangeModifier: this.multiStack.navWidthRangeModifier,
        onNavigationModeChange: this.callback,
        needRenderDisplayMode: this.multiStack.needRenderDisplayMode,
      });
    } else {
      this.navDestination!(name, param as Object);
    }
  }

  callback(mode: NavigationMode): void {
    if (that.onNavigationModeChangeCallback !== undefined) {
      if (mode !== that.mode || that.mode === undefined) {
        that.onNavigationModeChangeCallback!(mode);
      }
      that.mode = mode;
    }
  }

  aboutToAppear(): void {
    that = this;
    console.log('MultiNavigation aboutToAppear');
    try {
      display.onFoldStatusChange(this.foldStatusCallback);
    } catch (exception) {
      console.error('Failed to register callback. Code: ' + JSON.stringify(exception));
    }
    DeviceListenerManager.getInstance().registerOrientationLister((isPortrait: boolean|undefined) => {
      console.log('MultiNavigation orientation change ' + isPortrait);
      this.isPortrait = isPortrait as Boolean;
      this.multiStack.isPortrait = isPortrait as Boolean;
      this.multiStack.handleRefreshPlaceHolderIfNeeded();
    });
    DeviceListenerManager.getInstance().registerDrawableWidthLister((isLarge: boolean|undefined) => {
      hilog.debug(0x0000, 'MultiNavigation', 'MultiNavigation Drawable width change ' + isLarge);
      this.multiStack.isLarge = isLarge as Boolean;
      this.multiStack.handleRefreshPlaceHolderIfNeeded();
    });
    try {
      this.multiStack.needRenderDisplayMode.displayMode = display.getFoldStatus();
    } catch (err) {
      hilog.warn(0x0000, 'MultiNavigation', 'Failed to get fold status. error:' + JSON.stringify(err));
    }
    DeviceListenerManager.getInstance().initListener();
    this.multiStack.registerHomeChangeListener({
      onHomeShowOnTop: (name:string) => {
        this.onHomeShowOnTop!(name);
      },
    })
  }

  aboutToDisappear(): void {
    try {
      display.offFoldStatusChange();
    } catch (exception) {
      console.error('Failed to unregister callback. Code: ' + JSON.stringify(exception));
    }
    DeviceListenerManager.getInstance().unregisterOrientationLister();
    DeviceListenerManager.getInstance().unregisterDrawableWidthLister();
    DeviceListenerManager.getInstance().finalizeListener();
    this.multiStack.unregisterHomeChangeListener();
  }

  build() {
    Navigation(this.multiStack.outerStack) {

    }
    .mode(NavigationMode.Stack)
    .navDestination(this.MultiNavDestination)
    .hideBackButton(true)
    .hideTitleBar(true, true)
    .hideToolBar(true, true)
    .hideNavBar(true)
  }
}

@Observed
export class MultiNavPathStack extends NavPathStack {
  public outerStack: MyNavPathStack = new MyNavPathStack();
  public totalStack: MultiNavPolicyInfo[] = [];
  public subStackList: Array<SubNavigationStack> = [] as Array<SubNavigationStack>;
  public needRenderLeftClickCount: NeedRenderLeftClickCount = new NeedRenderLeftClickCount();
  public needRenderDisplayMode: NeedRenderDisplayMode = new NeedRenderDisplayMode();
  public disableAllAnimation: boolean = false;
  private mPolicyMap:Map<String,SplitPolicy> = new Map<string, SplitPolicy>();
  public navWidthRangeModifier: NavWidthRangeAttrModifier = new NavWidthRangeAttrModifier();
  public homeWidthPercents: double[] = [50.0, 50.0];
  public keepBottomPageFlag: boolean = false;
  public homeChangeListener: HomeChangeListener | undefined = undefined;
  public placeHolderPolicyInfo: MultiNavPolicyInfo | undefined = undefined;
  public isPortrait: boolean = false;
  public isLarge: boolean = false;

  public navPathStackOperate:MultiNavPathStackOperate = {
    onPrimaryPop:() => {
      this.totalStack.pop();
      this.subStackList.pop();
      this.outerStack.popInner(false);
    },
    onSecondaryPop:() => {
      this.totalStack.pop();
      this.checkAndNotifyHomeChange();
    }
  };

  public outerStackOperate: NavPathStackOperate = {
    onSystemPop:() => {
      this.totalStack.pop();
      this.subStackList.pop();
      this.checkAndNotifyHomeChange();
    }
  };

  constructor() {
    super();
    this.outerStack.registerStackOperateCallback(this.outerStackOperate);
  }

  public pushPath(info: NavPathInfo, animated?: boolean, policy?: SplitPolicy): void {
    animated = typeof animated === 'undefined' ? true : animated
    policy = (policy === undefined) ? SplitPolicy.DETAIL_PAGE : policy;
    const subStackLength = this.subStackList.length;
    const multiPolicyStack = new MultiNavPolicyInfo(policy, info);
    if (subStackLength > 0) {
      console.log('pushPath currentTopPrimaryPolicy = ' +
      this.subStackList[subStackLength - 1].getPrimaryPolicy());
    }

    if (policy === SplitPolicy.DETAIL_PAGE && subStackLength > 0 &&
      this.subStackList[subStackLength - 1].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
      let detailSize = this.subStackList[subStackLength - 1].getSecondaryInfoList().length;
      if (detailSize === 0) {
        this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
      } else {
        if (this.needRenderLeftClickCount.leftClickCount > 0) {
          // click on home, so we need to clear detail
          if (this.placeHolderPolicyInfo === undefined) {
            this.subStackList[subStackLength - 1].clearSecondary(false);
            this.totalStack.splice(this.totalStack.length - detailSize);
            this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
          } else {
            const firstSecondaryPolicy = this.subStackList[subStackLength - 1].getSecondaryInfoList()[0].policy;
            if (firstSecondaryPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
              if (detailSize === 1 ) {
                // detail has only place holder, so just push
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
              } else {
                this.subStackList[subStackLength - 1].clearSecondaryKeepPlaceHolder(false);
                this.totalStack.splice(this.totalStack.length - detailSize + 1);
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
              }
            } else {
              this.subStackList[subStackLength - 1].clearSecondary(false);
              this.totalStack.splice(this.totalStack.length - detailSize);
              this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
            }
          }
        } else {
          // click on detail, so just push
          this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
        }
      }
    } else {
      let subStack:SubNavigationStack = new SubNavigationStack();
      subStack.registerMultiStackOperateCallback(this.navPathStackOperate);
      subStack.disableAnimation(this.disableAllAnimation);
      this.subStackList.push(subStack);
      let info: NavPathInfo = new NavPathInfo('SubNavigation', subStack)
      this.outerStack.pushPath(info, animated);
      setTimeout(() => {
        subStack.pushPrimaryPath(multiPolicyStack as MultiNavPolicyInfo, false);
      }, 500)
    }

    this.totalStack.push(multiPolicyStack);
    if (policy === SplitPolicy.HOME_PAGE && this.placeHolderPolicyInfo !== undefined && this.needShowPlaceHolder()) {
      this.pushPlaceHolder(subStackLength);
    }
    console.log('=== MultiNavPathStack pushPath policy = ' + policy +
      ' stackSize = ' + this.totalStack.length +
      ' this.leftClickCount = ' + this.needRenderLeftClickCount.leftClickCount);
    this.needRenderLeftClickCount.leftClickCount = 0;
  }
  public pushPath(info: NavPathInfo, optionParam?:NavigationOptions, policy?: SplitPolicy): void {
    console.log('=== pushPath policy = ' + policy + ', info.name = ' + info.name);
    let animated: boolean = true;
    if (optionParam !== undefined) {
      animated = Boolean((optionParam as NavigationOptions).animated);
    }
    policy = (policy === undefined) ? SplitPolicy.DETAIL_PAGE : policy;
    const subStackLength = this.subStackList.length;
    const multiPolicyStack = new MultiNavPolicyInfo(policy, info);
    console.log('=== pushPath subStackLength = ' + subStackLength);
    if (subStackLength > 0) {
      console.log('pushPath currentTopPrimaryPolicy = ' +
      this.subStackList[subStackLength - 1].getPrimaryPolicy());
    }

    if (policy === SplitPolicy.DETAIL_PAGE && subStackLength > 0 &&
      this.subStackList[subStackLength - 1].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
      let detailSize = this.subStackList[subStackLength - 1].getSecondaryInfoList().length;
      console.log('=== pushPath detailSize = ' + detailSize );
      if (detailSize === 0) {
        this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
      } else {
        if (this.needRenderLeftClickCount.leftClickCount > 0) {
          // click on home, so we need to clear detail
          if (this.placeHolderPolicyInfo === undefined) {
            this.subStackList[subStackLength - 1].clearSecondary(false);
            this.totalStack.splice(this.totalStack.length - detailSize);
            this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
          } else {
            const firstSecondaryPolicy = this.subStackList[subStackLength - 1].getSecondaryInfoList()[0].policy;
            if (firstSecondaryPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
              if (detailSize === 1 ) {
                // detail has only place holder, so just push
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
              } else {
                this.subStackList[subStackLength - 1].clearSecondaryKeepPlaceHolder(false);
                this.totalStack.splice(this.totalStack.length - detailSize + 1);
                this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
              }
            } else {
              this.subStackList[subStackLength - 1].clearSecondary(false);
              this.totalStack.splice(this.totalStack.length - detailSize);
              this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, false);
            }
          }
        } else {
          // click on detail, so just push
          this.subStackList[subStackLength - 1].pushSecondaryPath(multiPolicyStack, animated);
        }
      }
    } else {
      let subStack:SubNavigationStack = new SubNavigationStack();
      subStack.registerMultiStackOperateCallback(this.navPathStackOperate);
      subStack.disableAnimation(this.disableAllAnimation);
      this.subStackList.push(subStack);
      let info: NavPathInfo = new NavPathInfo('SubNavigation', subStack)
      this.outerStack.pushPath(info, animated);
      setTimeout(() => {
        subStack.pushPrimaryPath(multiPolicyStack as MultiNavPolicyInfo, false);
      }, 500)
    }

    this.totalStack.push(multiPolicyStack);
    if (policy === SplitPolicy.HOME_PAGE && this.placeHolderPolicyInfo !== undefined && this.needShowPlaceHolder()) {
      this.pushPlaceHolder(subStackLength);
    }
    console.log('=== MultiNavPathStack pushPath policy = ' + policy +
      ' stackSize = ' + this.totalStack.length +
      ' this.leftClickCount = ' + this.needRenderLeftClickCount.leftClickCount);
    this.needRenderLeftClickCount.leftClickCount = 0;
  }

  public pushPathByName(name: string, param: Object, animated?: boolean, policy?: SplitPolicy): void {
    animated = typeof animated === 'undefined' ? true : animated
    let info: NavPathInfo = new NavPathInfo(name,param)
    this.pushPath(info, animated, policy);
  }

  public pushPathByName(name: string, param: Object, onPop?: Callback<PopInfo>,
    animated?: boolean, policy?: SplitPolicy): void {
    animated = typeof animated === 'undefined' ? true : animated
    let info: NavPathInfo = new NavPathInfo(name,param)
    if (onPop !== undefined) {
      info.onPop = onPop as Callback<PopInfo>
    }
    this.pushPath(info, animated, policy);
  }

  public pushDestination(info: NavPathInfo, animated?: boolean, policy?: SplitPolicy): Promise<void> {
    console.log('pushDestination is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }
  public pushDestination(info: NavPathInfo, option?: NavigationOptions, policy?: SplitPolicy): Promise<void> {
    console.log('pushDestination is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }

  public pushDestinationByName(name: string, param: Object, animated?: boolean, policy?: SplitPolicy): Promise<void> {
    console.log('pushDestinationByName is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }
  public pushDestinationByName(name: string, param: Object, onPop: Callback<PopInfo>,
    animated?: boolean, policy?: SplitPolicy): Promise<void> {
    console.log('pushDestinationByName is not support');
    let promise: Promise<void> = Promise.reject({message: 'not support'});
    return promise;
  }

  public replacePath(info: NavPathInfo, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    let totalSize = this.totalStack.length;
    let subStackSize = this.subStackList.length;
    if (totalSize < 1 || subStackSize < 1) {
      console.log('replacePath fail stack is empty');
      return;
    }
    let currentTopPolicy = this.totalStack[totalSize - 1].policy;
    if (currentTopPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
      hilog.warn(0x0000, 'MultiNavigation', 'replacePath fail, not support replace placeHolder');
      return;
    }
    const newPolicyInfo = new MultiNavPolicyInfo(currentTopPolicy, info);
    this.subStackList[subStackSize - 1].replacePath(newPolicyInfo, animated);
    this.totalStack.pop();
    this.totalStack.push(newPolicyInfo);
  }

  public replacePath(info: NavPathInfo, optionParam?: NavigationOptions): void {
    let animated: boolean = true;
    if (optionParam !== undefined) {
      animated = Boolean((optionParam as NavigationOptions).animated);
    }
    let totalSize = this.totalStack.length;
    let subStackSize = this.subStackList.length;
    if (totalSize < 1 || subStackSize < 1) {
      console.log('replacePath fail stack is empty');
      return;
    }
    let currentTopPolicy = this.totalStack[totalSize - 1].policy;
    if (currentTopPolicy === SplitPolicy.PlACE_HOLDER_PAGE) {
      hilog.warn(0x0000, 'MultiNavigation', 'replacePath fail, not support replace placeHolder');
      return;
    }
    const newPolicyInfo = new MultiNavPolicyInfo(currentTopPolicy, info);
    this.subStackList[subStackSize - 1].replacePath(newPolicyInfo, animated);
    this.totalStack.pop();
    this.totalStack.push(newPolicyInfo);
  }
  public replacePathByName(name: string, param: Object, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    let info: NavPathInfo = new NavPathInfo(name, param)
    this.replacePath(info, animated);
  }

  public removeByIndexes(indexes: int[]): int {
    let indexesLength = indexes.length;
    console.log('removeByIndexes indexesLength=' + indexesLength);
    if (indexesLength <= 0) {
      return 0;
    }
    let oriStackSize = this.totalStack.length;
    console.log('removeByIndexes oriStackSize=' + oriStackSize);
    indexes.sort((a, b) => a - b);
    let i: int = 0;
    let currentStackInfoLength: int = 0;
    let outerIndexes: int[] = [];
    console.log('removeByIndexes this.subStackList.length=' + this.subStackList.length +
      ', oriStackSize=' + oriStackSize);
    this.subStackList.forEach((subStack, subStackIndex) => {
      let stepStartIndex = currentStackInfoLength;
      currentStackInfoLength += subStack.getAllInfoLength();
      const subIndexes: int[] = [];
      for (; i < indexes.length; ) {
        if (indexes[i] < currentStackInfoLength) {
          subIndexes.push(indexes[i] - stepStartIndex);
          i++;
        } else {
          break;
        }
      }
      subStack.removeByIndexes(subIndexes);
      if (!subStack.hasPrimaryInfo()) {
        outerIndexes.push(subStackIndex);
      }
    });
    console.log('removeByIndexes outerIndexes.length=' + outerIndexes.length);
    this.outerStack.removeByIndexes(outerIndexes);
    this.subStackList = this.subStackList.filter((subStack) => {
      return subStack.hasPrimaryInfo()
    });

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    let size = oriStackSize - this.totalStack.length;
    console.log('removeByIndexes size=' + size);
    return size;
  }

  public removeByName(name: string): int {
    let oriStackSize = this.totalStack.length;
    console.log('removeByName name=' + name + ', oriStackSize=' + oriStackSize);
    let outerIndexes: int[] = [];
    this.subStackList.forEach((subStack, index) => {
      subStack.removeByName(name);
      if (!subStack.hasPrimaryInfo()) {
        outerIndexes.push(index);
      }
    });
    this.outerStack.removeByIndexes(outerIndexes);
    console.log('removeByName outerIndexes.length=' + outerIndexes.length);
    this.subStackList = this.subStackList.filter((subStack) => {
      return subStack.hasPrimaryInfo()
    });

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    let size = oriStackSize - this.totalStack.length;
    console.log('removeByName size=' + size);
    return size;
  }

  public pop(result?: Object | boolean, animated?: boolean): NavPathInfo | undefined {
    animated = typeof animated === 'undefined' ? true : animated
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      console.log('MultiNavPathStack pop fail stack is empty!');
      return undefined;
    }
    console.log('MultiNavPathStack pop totalSize=' + totalSize +
      ', subStackLength' + subStackLength);

    if (this.keepBottomPageFlag && (totalSize === 1 ||
      (this.placeHolderPolicyInfo !== undefined && totalSize === 2 &&
        this.totalStack[1].policy === SplitPolicy.PlACE_HOLDER_PAGE))) {
      console.log('MultiNavPathStack pop fail for keep bottom');
      return undefined;
    }
    let currentPath = this.totalStack[totalSize - 1].navInfo;
    let allInfoLength = this.subStackList[subStackLength - 1].getAllInfoLength();
    if (allInfoLength < 1) {
      console.log('MultiNavPathStack pop fail sub stack is empty');
      return undefined;
    }
    let secondaryStackFirstPolice: SplitPolicy | undefined = undefined;
    if (allInfoLength > 1) {
      secondaryStackFirstPolice = this.subStackList[subStackLength - 1].getSecondaryInfoList()[0].policy;
    }
    console.log('MultiNavPathStack pop allInfoLength=' + allInfoLength +
      ', secondaryStackFirstPolice' + secondaryStackFirstPolice);
    this.totalStack.pop();
    if (allInfoLength === 1) {
      // pop home
      this.outerStack.popInner(animated);
      let subStack = this.subStackList.pop();
      setTimeout(() => {
        subStack?.pop(false);
        subStack = undefined;
      }, 300);
    } else {
      if (allInfoLength === 2) {
        if (this.placeHolderPolicyInfo !== undefined) {
          if (secondaryStackFirstPolice === SplitPolicy.PlACE_HOLDER_PAGE) {
            this.outerStack.popInner(animated);
            let subStack = this.subStackList.pop();
            setTimeout(() => {
              subStack?.clear(false);
              subStack = undefined;
            }, 300);
            currentPath = this.totalStack.pop()?.navInfo;
          } else {
            if (this.needShowPlaceHolder()) {
              this.subStackList[subStackLength - 1].pop(animated);
              this.pushPlaceHolder(subStackLength - 1)
            } else {
              this.subStackList[subStackLength - 1].pop(animated);
            }
          }
        } else {
          this.subStackList[subStackLength - 1].pop(animated);
        }
      } else {
        this.subStackList[subStackLength - 1].pop(animated);
      }
    }
    console.log('MultiNavPathStack pop currentPath.name = ' + currentPath?.name);

    if (result !== undefined && typeof result !== 'boolean' &&
      currentPath !== undefined && currentPath.onPop !== undefined) {
      let popInfo: PopInfo = {
        info: currentPath,
        result: result,
      };
      currentPath.onPop!(popInfo);
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    console.log('MultiNavPathStack pop stackSize = ' + this.totalStack.length);
    return currentPath;
  }

  public popToName(name: string, animated?: boolean): int {
    animated = typeof animated === 'undefined' ? true : animated
    let index = this.totalStack.findIndex((value: MultiNavPolicyInfo) => {
      return value.navInfo?.name === name;
    })
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      console.log('popToName fail stack is empty!');
      return -1;
    }
    if (index !== -1) {
      let currentPath = this.totalStack[totalSize - 1].navInfo;
      let secondaryStackSize: int[] = [];
      this.subStackList.forEach((subStack) => {
        secondaryStackSize.push(subStack.secondaryStack.size());
      });
      let removeIndex = 0;
      for (let i = 0; i < subStackLength; i++) {
        removeIndex++;
        if (index === removeIndex - 1) {
          this.subStackList[i]?.secondaryStack.clear();
          this.subStackList[i].secondaryStack.policyInfoList.splice(0);
          this.totalStack.splice(index.toInt() + 1);
          this.clearTrashStack(i + 1, {}, animated);
          break;
        } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
          this.subStackList[i].secondaryStack.popToIndex(index - removeIndex, {}, true);
          this.subStackList[i].secondaryStack.policyInfoList.splice(index.toInt() - removeIndex.toInt() + 1);
          this.totalStack.splice(index.toInt() + 1);
          this.clearTrashStack(i + 1, {}, animated);
        }
        removeIndex += secondaryStackSize[i];
      }
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    return index;
  }
  public popToName(name: string, result: Object, animated?: boolean): int {
    animated = typeof animated === 'undefined' ? true : animated
    let index = this.totalStack.findIndex((value: MultiNavPolicyInfo) => {
      return value.navInfo?.name === name;
    })
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      console.log('popToName fail stack is empty!');
      return -1;
    }
    if (index !== -1) {
      let currentPath = this.totalStack[totalSize - 1].navInfo;
      let secondaryStackSize: int[] = [];
      this.subStackList.forEach((subStack) => {
        secondaryStackSize.push(subStack.secondaryStack.size());
      });
      let removeIndex = 0;
      for (let i = 0; i < subStackLength; i++) {
        removeIndex++;
        if (index === removeIndex - 1) {
          this.subStackList[i]?.secondaryStack.clear();
          this.subStackList[i].secondaryStack.policyInfoList.splice(0);
          this.totalStack.splice(index.toInt() + 1);
          this.clearTrashStack(i + 1, result, animated);
          break;
        } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
          this.subStackList[i].secondaryStack.popToIndex(index - removeIndex, {}, true);
          this.subStackList[i].secondaryStack.policyInfoList.splice(index.toInt() - removeIndex.toInt() + 1);
          this.totalStack.splice(index.toInt() + 1);
          this.clearTrashStack(i + 1, result, animated);
        }
        removeIndex += secondaryStackSize[i];
      }
      if (currentPath !== undefined && currentPath.onPop !== undefined) {
        let popInfo: PopInfo = {
          info: currentPath,
          result: result,
        };
        currentPath.onPop!(popInfo);
      }
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
    return index;
  }

  public popToIndex(index: int, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    console.log('MultiNavPathStack popToIndex index = ' + index);
    if (index > this.totalStack.length || index < 0) {
      console.log('popToIndex fail wrong index');
      return;
    }
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      console.log('popToIndex fail stack is empty!');
      return;
    }
    let currentPath = this.totalStack[totalSize - 1].navInfo;
    let secondaryStackSize: int[] = [];
    this.subStackList.forEach((subStack) => {
      secondaryStackSize.push(subStack.secondaryStack.size());
    });
    let removeIndex = 0;
    for (let i = 0; i < subStackLength; i++) {
      removeIndex++;
      if (index === removeIndex - 1) {
        console.log('MultiNavPathStack popToIndex home' + i);
        this.subStackList[i]?.secondaryStack.clear();
        this.subStackList[i].secondaryStack.policyInfoList.splice(0);
        this.totalStack.splice(index.toInt() + 1);
        this.clearTrashStack(i + 1, {}, animated);
        console.log('MultiNavPathStack popToIndex totalStack=' + this.totalStack.length);
        break;
      } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
        this.subStackList[i].secondaryStack.popToIndex(index - removeIndex, {}, true);
        this.subStackList[i].secondaryStack.policyInfoList.splice(index.toInt() - removeIndex + 1);
        this.totalStack.splice(index.toInt() + 1);
        this.clearTrashStack(i + 1, {}, animated);
      }
      removeIndex += secondaryStackSize[i];
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
  }
  public popToIndex(index: int, result: Object, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    console.log('MultiNavPathStack popToIndex index = ' + index);
    if (index > this.totalStack.length || index < 0) {
      console.log('popToIndex fail wrong index');
      return;
    }
    let totalSize = this.totalStack.length;
    let subStackLength = this.subStackList.length;
    if (totalSize < 1 || subStackLength < 1) {
      console.log('popToIndex fail stack is empty!');
      return;
    }
    let currentPath = this.totalStack[totalSize - 1].navInfo;
    let secondaryStackSize: int[] = [];
    this.subStackList.forEach((subStack) => {
      secondaryStackSize.push(subStack.secondaryStack.size());
    });
    let removeIndex = 0;
    for (let i = 0; i < subStackLength; i++) {
      removeIndex++;
      if (index === removeIndex - 1) {
        console.log('MultiNavPathStack popToIndex home' + i);
        this.subStackList[i]?.secondaryStack.clear();
        this.subStackList[i].secondaryStack.policyInfoList.splice(0);
        this.totalStack.splice(index.toInt() + 1);
        this.clearTrashStack(i + 1, result, animated);
        console.log('MultiNavPathStack popToIndex totalStack=' + this.totalStack.length);
        break;
      } else if (index > removeIndex - 1 && index < removeIndex + secondaryStackSize[i]) {
        this.subStackList[i].secondaryStack.popToIndex(index - removeIndex, {}, true);
        this.subStackList[i].secondaryStack.policyInfoList.splice(index.toInt() - removeIndex + 1);
        this.totalStack.splice(index.toInt() + 1);
        this.clearTrashStack(i + 1, result, animated);
      }
      removeIndex += secondaryStackSize[i];
    }

    if (currentPath !== undefined && currentPath.onPop !== undefined) {
      let popInfo: PopInfo = {
        info: currentPath,
        result: result,
      };
      currentPath.onPop!(popInfo);
    }
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
  }

  private clearTrashStack(index: int, result?: Object, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    result = typeof result === 'undefined' ? {} as Object : result
    console.log('MultiNavPathStack popToIndex clearTrashStack' + index);
    for (let i = index; i < this.subStackList.length; i++) {
      console.log('MultiNavPathStack popToIndex subStackList' + index);
      this.subStackList[i].primaryStack.clear();
      this.subStackList[i].secondaryStack.clear();
      this.subStackList[i].primaryStack.policyInfoList.splice(0);
      this.subStackList[i].secondaryStack.policyInfoList.splice(0);
    }
    this.subStackList.splice(index.toInt());
    console.log('MultiNavPathStack popToIndex subStackList.length=' + this.subStackList.length);
    this.outerStack.popToIndex(index - 1, result as Object, animated);
    console.log('MultiNavPathStack popToIndex outerStack.size=' + this.outerStack.size());
  }

  public moveToTop(name: string, animated?: boolean): int {
    animated = typeof animated === 'undefined' ? true : animated
    console.log('MultiNavPathStack moveToTop name=' + name);
    let index = this.totalStack.findIndex((value) => {
      return value.navInfo?.name === name;
    });
    if (index !== -1) {
      this.moveIndexToTop(index, animated);
    }

    return index;
  }

  public moveIndexToTop(index: int, animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    console.log('MultiNavPathStack moveIndexToTop index=' + index);
    if (index < 0 || index > this.totalStack.length) {
      console.log('MultiNavPathStack moveIndexToTop wrong index');
      return;
    }
    let subStackLength = this.subStackList.length;
    let currentStackInfoLength: int = 0;
    let outerIndex: int = -1;
    for (let subIndex = 0; subIndex < subStackLength; subIndex++) {
      let stepStartIndex = currentStackInfoLength;
      currentStackInfoLength += this.subStackList[subIndex].getAllInfoLength();
      if (index < currentStackInfoLength) {
        outerIndex = subIndex;
        if (this.subStackList[subIndex].getPrimaryPolicy() === SplitPolicy.HOME_PAGE) {
          let innerIndex = index - stepStartIndex;
          if (innerIndex !== 0) {
            this.subStackList[subIndex].secondaryStack.moveIndexToTop(innerIndex - 1, animated);
            const subInfo = this.subStackList[subIndex].secondaryStack.policyInfoList.splice(innerIndex.toInt() - 1, 1);
            this.subStackList[subIndex].secondaryStack.policyInfoList.push(...subInfo);
          }
        }
        break;
      }
    }
    if (outerIndex !== -1) {
      let subStack = this.subStackList.splice(outerIndex.toInt(), 1);
      this.subStackList.push(...subStack);
      this.outerStack.moveIndexToTop(outerIndex, animated);
    }

    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    });
    this.handleRefreshPlaceHolderIfNeeded();
    this.checkAndNotifyHomeChange();
  }

  public clear(animated?: boolean): void {
    animated = typeof animated === 'undefined' ? true : animated
    console.log('MultiNavPathStack clear animated = ' + animated + ', keepBottomPage=' +
    this.keepBottomPageFlag);

    if (this.subStackList.length === 0 || this.totalStack.length === 0) {
      console.log('MultiNavPathStack clear return size is 0');
      return;
    }
    if (this.keepBottomPageFlag) {
      let subStackLength = this.subStackList.length;
      for (let i = 1; i < subStackLength; i++) {
        this.subStackList[i].clear(animated);
      }
      this.outerStack.popToIndex(0, {}, animated);
      this.subStackList.splice(1);
      if (this.placeHolderPolicyInfo !== undefined) {
        if (this.subStackList[0].getSecondaryInfoList().length > 1 &&
          this.subStackList[0].secondaryStack.policyInfoList[0].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
          this.subStackList[0].clearSecondaryKeepPlaceHolder(animated);
          this.totalStack.splice(2);
        } else {
          this.subStackList[0].clearSecondary(animated);
          this.totalStack.splice(1);
          if (this.needShowPlaceHolder()) {
            this.subStackList[0].pushSecondaryPath(this.placeHolderPolicyInfo as MultiNavPolicyInfo, animated);
            this.totalStack.push(this.placeHolderPolicyInfo as MultiNavPolicyInfo);
          }
        }
      } else {
        this.subStackList[0].clearSecondary(animated);
        this.totalStack.splice(1);
      }

      this.checkAndNotifyHomeChange();
      return;
    }
    this.subStackList.forEach((subStack) => {
      subStack.clear(animated);
    })
    this.outerStack.clear(animated);
    this.subStackList.splice(0);
    this.totalStack.splice(0)
  }

  public getAllPathName(): string[] {
    let result: string[] = [];
    this.totalStack.forEach((value) => {
      if (value.navInfo !== undefined) {
        result.push(value!.navInfo!.name);
      }
    })
    return result;
  }

  public getParamByIndex(index: int): Object | undefined {
    let result: Object | undefined = undefined;
    if (index >= 0 && index < this.totalStack.length) {
      result = this.totalStack[index.toInt()].navInfo?.param as Object;
    }
    return result;
  }

  public getParamByName(name: string): (Object | null | undefined)[] {
    let result: (Object | null | undefined)[] = [];
    this.totalStack.forEach((value) => {
      if (value.navInfo !== undefined && value.navInfo!.name == name) {
        result.push(value!.navInfo!.param);
      }
    })
    return result;
  }

  public getIndexByName(name: string): int[] {
    let result: int[] = [];
    for (let i = 0; i < this.totalStack.length; i++) {
      if (this.totalStack[i].navInfo?.name === name) {
        result.push(i);
      }
    }
    return result;
  }

  public getParent(): NavPathStack {
    console.log('getParent is not support!');
    throw new Error('getParent is not support in multi navigation');
  }

  public size(): int {
    return this.totalStack.length;
  }

  public disableAnimation(value: boolean): void {
    for (const subStack of this.subStackList) {
      subStack.disableAnimation(value);
    }
    this.outerStack.disableAnimation(value);
    this.disableAllAnimation = value;
  }

  public setInterception(interception: NavigationInterception): void {
    console.log('setInterception is not support!');
    throw new Error('setInterception is not support in multi navigation');
  }

  public setPagePolicy(policyMap: Map<string, SplitPolicy>): void {
    this.mPolicyMap = policyMap;
  }

  public switchFullScreenState(isFullScreen?: boolean): boolean {
    let totalStackSize = this.totalStack.length;
    let subStackListLength = this.subStackList.length;
    if (subStackListLength < 1 || totalStackSize < 1) {
      return false;
    }
    if (this.subStackList[subStackListLength - 1].getPrimaryPolicy() !== SplitPolicy.HOME_PAGE) {
      return false;
    }
    if (this.totalStack[totalStackSize - 1].policy === SplitPolicy.PlACE_HOLDER_PAGE) {
      return false;
    }
    if (this.totalStack[totalStackSize - 1].isFullScreen === isFullScreen) {
      console.log('switchFullScreen is same:' + isFullScreen);
      return true;
    }
    console.log('switchFullScreen name=' +
      this.totalStack[totalStackSize - 1].navInfo?.name +
      ', from ' + this.totalStack[totalStackSize - 1].isFullScreen + ' to ' + isFullScreen);
    this.totalStack[totalStackSize - 1].isFullScreen = isFullScreen;
    this.subStackList[subStackListLength - 1].refreshFullScreen();
    return true;
  }

  public setHomeWidthRange(minPercent: double, maxPercent: double): void {
    if (!this.checkInputPercent(minPercent) || !this.checkInputPercent(maxPercent)) {
      console.log('setHomeWidthRange failed, wrong param:' +
        ', ' + minPercent + ', ' + maxPercent)
      return;
    }
    this.homeWidthPercents = [minPercent, maxPercent];
    this.refreshHomeWidth();
  }

  public keepBottomPage(keepBottom: boolean): void {
    this.keepBottomPageFlag = keepBottom;
  }

  public registerHomeChangeListener(lister: HomeChangeListener): void {
    if (this.homeChangeListener === undefined) {
      this.homeChangeListener = lister;
    }
  }

  public unregisterHomeChangeListener(): void {
    this.homeChangeListener = undefined;
  }

  public setPlaceholderPage(info: NavPathInfo): void {
    this.placeHolderPolicyInfo = new MultiNavPolicyInfo(SplitPolicy.PlACE_HOLDER_PAGE, info);
  }

  public handleRefreshPlaceHolderIfNeeded() {
    if (this.placeHolderPolicyInfo === undefined) {
      return;
    }
    const subStackListLength = this.subStackList.length;
    if (subStackListLength < 1) {
      return;
    }
    const topStackPrimaryPolicy = this.subStackList[subStackListLength - 1].getPrimaryPolicy();
    if (topStackPrimaryPolicy !== SplitPolicy.HOME_PAGE) {
      return;
    }
    const subStackAllInfoLength = this.subStackList[subStackListLength - 1].getAllInfoLength();
    let secondaryStackFirstPolice: SplitPolicy | undefined = undefined;
    if (subStackAllInfoLength > 1) {
      secondaryStackFirstPolice = this.subStackList[subStackListLength - 1].getSecondaryInfoList()[0].policy;
    }
    if (this.needShowPlaceHolder()) {
      if (subStackAllInfoLength === 1) {
        this.pushPlaceHolder(subStackListLength - 1);
      }
    } else {
      if (secondaryStackFirstPolice === SplitPolicy.PlACE_HOLDER_PAGE) {
        if (subStackAllInfoLength === 2) {
          this.popPlaceHolder(subStackListLength - 1);
        } else {
          this.removeFirstPlaceHolder(subStackListLength - 1);
        }
      }
    }
  }

  private removeFirstPlaceHolder(subIndex: int): void {
    this.subStackList[subIndex].removeByIndexes([1]);
    this.totalStack = [];
    this.subStackList.forEach((subStack) => {
      this.totalStack.push(...subStack.getPrimaryInfoList());
      this.totalStack.push(...subStack.getSecondaryInfoList());
    })
  }

  private pushPlaceHolder(subIndex: int): void {
    this.subStackList[subIndex].pushSecondaryPath(this.placeHolderPolicyInfo!, false);
    this.totalStack.push(this.placeHolderPolicyInfo!);
  }

  private popPlaceHolder(subIndex: int): void {
    this.subStackList[subIndex].pop(false);
    this.totalStack.pop();
    this.checkAndNotifyHomeChange();
  }

  private needShowPlaceHolder(): boolean {
    if (!this.isLarge) {
      console.log('do not show placeHolder for drawable width is less then breakpoint');
      return false;
    }
    if (DeviceHelper.isStraightProduct()) {
      console.log('do not show placeHolder for straight product');
      return false;
    }
    if (DeviceHelper.isPhone() && DeviceHelper.isFold() &&
      this.needRenderDisplayMode.displayMode === display.FoldStatus.FOLD_STATUS_FOLDED) {
      console.log('do not show placeHolder for fold status');
      return false;
    }
    if (DeviceHelper.isTablet() && this.isPortrait) {
      console.log('do not show placeHolder for portrait tablet');
      return false;
    }
    return true;
  }

  private checkAndNotifyHomeChange(): void {
    if (this.totalStack.length === 0) {
      return;
    }
    let topPolicyInfo = this.totalStack[this.totalStack.length - 1];
    if (topPolicyInfo === undefined) {
      return;
    }
    if (topPolicyInfo.policy === SplitPolicy.HOME_PAGE && topPolicyInfo.navInfo !== undefined) {
      if (this.homeChangeListener) {
        this.homeChangeListener!.onHomeShowOnTop(topPolicyInfo!.navInfo!.name);
      }
    }
    if (this.totalStack.length <= 1) {
      return;
    }
    let secondPolicyInfo = this.totalStack[this.totalStack.length - 2];
    if (secondPolicyInfo === undefined) {
      return;
    }
    if (topPolicyInfo.policy === SplitPolicy.PlACE_HOLDER_PAGE &&
      secondPolicyInfo.policy === SplitPolicy.HOME_PAGE && secondPolicyInfo.navInfo !== undefined) {
      if (this.homeChangeListener && this.homeChangeListener!.onHomeShowOnTop) {
        this.homeChangeListener!.onHomeShowOnTop!(secondPolicyInfo!.navInfo!.name);
      }
    }
  }

  private refreshHomeWidth(): void {
    this.navWidthRangeModifier.minHomeWidth = `${this.homeWidthPercents[0]}%`;
    this.navWidthRangeModifier.maxHomeWidth = `${this.homeWidthPercents[1]}%`;
    this.navWidthRangeModifier.isApplicationSet = true;
  }

  private checkInputPercent(inputPercent: double): boolean {
    return (0 <= inputPercent && inputPercent <= 100);
  }
}

interface HomeChangeListener {
  onHomeShowOnTop: OnHomeShowOnTopCallback;
}

@Observed
export class NeedRenderIsFullScreen {
  public isFullScreen: boolean | undefined = undefined;
}

@Observed
export class NeedRenderLeftClickCount {
  public leftClickCount: number = 0;
}

@Observed
export class NeedRenderDisplayMode {
  public displayMode: number = 0;
}

class MultiNavPolicyInfo {
  public policy: SplitPolicy = SplitPolicy.DETAIL_PAGE;
  public navInfo: NavPathInfo | undefined = undefined;
  public isFullScreen: boolean | undefined = undefined;

  constructor(policy: SplitPolicy, navInfo: NavPathInfo) {
    this.policy = policy;
    this.navInfo = navInfo;
  }
}

export class MyNavPathStack extends NavPathStack {
  public operates:NavPathStackOperate[] = [];
  public type:string = 'NavPathStack';
  public policyInfoList: MultiNavPolicyInfo[] = [];

  public registerStackOperateCallback(operate: NavPathStackOperate) {
    let index = this.operates.findIndex((item) => { return item === operate});
    if (index === -1) {
      this.operates.push(operate);
    }
  }

  public unregisterStackOperateCallback(operate: NavPathStackOperate) {
    let index = this.operates.findIndex((item) => { return item === operate});
    if (index !== -1) {
      this.operates.splice(index, 1);
    }
  }

  public popInner(animated?: boolean): NavPathInfo | undefined {
    console.log('MyNavPathStack pop from inner:');
    return super.pop({}, animated);
  }

  public pop(animated?: boolean): NavPathInfo | undefined {
    console.log('MyNavPathStack pop from system:');
    animated = typeof animated === 'undefined' ? true : animated
    let ret: NavPathInfo | undefined = undefined;
    ret = super.pop({}, animated);
    this.policyInfoList.pop();
    this.operates.forEach((item) => {
      item.onSystemPop();
    })
    return ret;
  }
}

interface NavPathStackOperate {
  onSystemPop: ()=>void;
}

interface MultiNavPathStackOperate {
  onPrimaryPop: ()=>void;
  onSecondaryPop: ()=>void;
}


declare type OnNavigationModeChangeCallback = (mode: NavigationMode) => void;

declare type OnHomeShowOnTopCallback = (name: string) => void;