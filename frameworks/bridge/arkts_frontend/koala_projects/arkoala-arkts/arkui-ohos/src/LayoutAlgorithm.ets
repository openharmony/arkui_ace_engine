/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { memo, memo_stable } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { extractors, initializers } from '#handwritten'
import { Vector2 } from 'arkui.Graphics'
import { CallbackTransformer } from './CallbackTransformer'
import { arkui_Graphics_LengthMetrics_serializer } from './framework/Graphics'
import { UIUtils as UIUtils } from 'arkui.stateManagement.utils';
import { IObservedObject as IObservedObject } from 'arkui.stateManagement.decorator';
import { IMutableStateMeta as IMutableStateMeta } from 'arkui.stateManagement.decorator';
import { RenderIdType as RenderIdType } from 'arkui.stateManagement.decorator';
import { WatchIdType as WatchIdType } from 'arkui.stateManagement.decorator';
import { ISubscribedWatches as ISubscribedWatches } from 'arkui.stateManagement.decorator';
import { STATE_MGMT_FACTORY as STATE_MGMT_FACTORY } from 'arkui.stateManagement.decorator';
import { FrameNode as FrameNode, LayoutConstraint as LayoutConstraint } from 'arkui.FrameNode';
import { LengthMetrics as LengthMetrics, NodePosition as NodePosition, LengthUnit as LengthUnit } from 'arkui.Graphics';
import { HorizontalAlign as HorizontalAlign, FlexAlign as FlexAlign, VerticalAlign as VerticalAlign, LocalizedAlignment as LocalizedAlignment } from './component/enums';
import { ItemFillPolicy as ItemFillPolicy } from './component/units';
export interface LayoutAlgorithm {
}

export interface GridLayoutAlgorithmOptions {
    columnsTemplate?: string | ItemFillPolicy;
    rowsGap?: LengthMetrics;
    columnsGap?: LengthMetrics;
}

export class GridLayoutAlgorithm implements LayoutAlgorithm, IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: ISubscribedWatches =
    STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    this.subscribedWatches.addWatchSubscriber(watchId);
  }
  
  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    return this.subscribedWatches.removeWatchSubscriber(watchId);
  }
 
  public executeOnSubscribingWatches(propertyName: string): void {
    this.subscribedWatches.executeOnSubscribingWatches(propertyName);
  }
 
  public setV1RenderId(renderId: RenderIdType): void {}
 
  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }
 
  @JSONRename({newName:'columnsTemplate'}) public backingColumnsTemplate?: (string | ItemFillPolicy | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaColumnsTemplate: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_columnsTemplate');
  public get columnsTemplate(): (string | ItemFillPolicy | undefined) {
    this.conditionalAddRef(this.metaColumnsTemplate);
    return UIUtils.makeObserved((this.backingColumnsTemplate as (string | ItemFillPolicy | undefined)));
  }
 
  public set columnsTemplate(newValue: (string | ItemFillPolicy | undefined)) {
    if (((this.backingColumnsTemplate) !== (newValue))) {
      this.backingColumnsTemplate = newValue;
      this.metaColumnsTemplate.fireChange();
      this.executeOnSubscribingWatches('columnsTemplate');
    }
  }
 
  @JSONRename({newName:'rowsGap'}) public backingRowsGap?: (LengthMetrics | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaRowsGap: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_rowsGap');
  public get rowsGap(): (LengthMetrics | undefined) {
    this.conditionalAddRef(this.metaRowsGap);
    return UIUtils.makeObserved((this.backingRowsGap as (LengthMetrics | undefined)));
  }
 
  public set rowsGap(newValue: (LengthMetrics | undefined)) {
    if (((this.backingRowsGap) !== (newValue))) {
      this.backingRowsGap = newValue;
      this.metaRowsGap.fireChange();
      this.executeOnSubscribingWatches('rowsGap');
    }
  }
 
  @JSONRename({newName:'columnsGap'}) public backingColumnsGap?: (LengthMetrics | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaColumnsGap: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_columnsGap');
  public get columnsGap(): (LengthMetrics | undefined) {
    this.conditionalAddRef(this.metaColumnsGap);
    return UIUtils.makeObserved((this.backingColumnsGap as (LengthMetrics | undefined)));
  }
 
  public set columnsGap(newValue: (LengthMetrics | undefined)) {
    if (((this.backingColumnsGap) !== (newValue))) {
      this.backingColumnsGap = newValue;
      this.metaColumnsGap.fireChange();
      this.executeOnSubscribingWatches('columnsGap');
    }
  }
 
  constructor(option?: GridLayoutAlgorithmOptions) {
    if (option) {
        this.backingColumnsTemplate = option.columnsTemplate !== undefined ? option.columnsTemplate : undefined
        this.backingRowsGap = option.rowsGap !== undefined ? option.rowsGap : undefined
        this.backingColumnsGap = option.columnsGap !== undefined ? option.columnsGap : undefined
    }
  }
}

export class CustomLayoutAlgorithm implements LayoutAlgorithm, IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: ISubscribedWatches =
    STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    this.subscribedWatches.addWatchSubscriber(watchId);
  }

  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    return this.subscribedWatches.removeWatchSubscriber(watchId);
  }

  public executeOnSubscribingWatches(propertyName: string): void {
    this.subscribedWatches.executeOnSubscribingWatches(propertyName);
  }

  public setV1RenderId(renderId: RenderIdType): void {}

  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }
}

export interface StackLayoutAlgorithmOptions {
    alignContent?: LocalizedAlignment;
}
 
export class StackLayoutAlgorithm implements LayoutAlgorithm, IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: ISubscribedWatches =
    STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    this.subscribedWatches.addWatchSubscriber(watchId);
  }
  
  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    return this.subscribedWatches.removeWatchSubscriber(watchId);
  }
  
  public executeOnSubscribingWatches(propertyName: string): void {
    this.subscribedWatches.executeOnSubscribingWatches(propertyName);
  }
  
  public setV1RenderId(renderId: RenderIdType): void {}
  
  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }
  
  @JSONRename({newName:'alignContent'}) public backingAlignContent?: (LocalizedAlignment | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaAlignContent: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_alignContent');
  public get alignContent(): (LocalizedAlignment | undefined) {
    this.conditionalAddRef(this.metaAlignContent);
    return UIUtils.makeObserved((this.backingAlignContent as (LocalizedAlignment | undefined)));
  }
  
  public set alignContent(newValue: (LocalizedAlignment | undefined)) {
    if (((this.backingAlignContent) !== (newValue))) {
      this.backingAlignContent = newValue;
      this.metaAlignContent.fireChange();
      this.executeOnSubscribingWatches('alignContent');
    }
  }
  
  constructor(option?: StackLayoutAlgorithmOptions) {
    if (option) {
        this.backingAlignContent = option.alignContent !== undefined ? option.alignContent : LocalizedAlignment.CENTER
    }
  }
}
 
export interface RowLayoutAlgorithmOptions {
    space?: LengthMetrics;
    alignItems?: VerticalAlign;
    justifyContent?: FlexAlign;
    isReverse?: boolean;
}
 
export class RowLayoutAlgorithm implements LayoutAlgorithm, IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: ISubscribedWatches =
    STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    this.subscribedWatches.addWatchSubscriber(watchId);
  }
 
  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    return this.subscribedWatches.removeWatchSubscriber(watchId);
  }
 
  public executeOnSubscribingWatches(propertyName: string): void {
    this.subscribedWatches.executeOnSubscribingWatches(propertyName);
  }
 
  public setV1RenderId(renderId: RenderIdType): void {}
 
  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }
 
  @JSONRename({newName:'space'}) public backingSpace?: (LengthMetrics | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaSpace: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_space');
  public get space(): (LengthMetrics | undefined) {
    this.conditionalAddRef(this.metaSpace);
    return UIUtils.makeObserved((this.backingSpace as (LengthMetrics | undefined)));
  }
 
  public set space(newValue: (LengthMetrics | undefined)) {
    if (((this.backingSpace) !== (newValue))) {
      this.backingSpace = newValue;
      this.metaSpace.fireChange();
      this.executeOnSubscribingWatches('space');
    }
  }
 
  @JSONRename({newName:'alignItems'}) public backingAlignItems?: (VerticalAlign | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaAlignItems: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_alignItems');
  public get alignItems(): (VerticalAlign | undefined) {
    this.conditionalAddRef(this.metaAlignItems);
    return UIUtils.makeObserved((this.backingAlignItems as (VerticalAlign | undefined)));
  }
 
  public set alignItems(newValue: (VerticalAlign | undefined)) {
    if (((this.backingAlignItems) !== (newValue))) {
      this.backingAlignItems = newValue;
      this.metaAlignItems.fireChange();
      this.executeOnSubscribingWatches('alignItems');
    }
  }
 
  @JSONRename({newName:'justifyContent'}) public backingJustifyContent?: (FlexAlign | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaJusiftyContent: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_justifyContent');
  public get justifyContent(): (FlexAlign | undefined) {
    this.conditionalAddRef(this.metaJusiftyContent);
    return UIUtils.makeObserved((this.backingJustifyContent as (FlexAlign | undefined)));
  }
 
  public set justifyContent(newValue: (FlexAlign | undefined)) {
    if (((this.backingJustifyContent) !== (newValue))) {
      this.backingJustifyContent = newValue;
      this.metaJusiftyContent.fireChange();
      this.executeOnSubscribingWatches('justifyContent');
    }
  }
 
  @JSONRename({newName:'isReverse'}) public backingIsReverse?: (boolean | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaReverse: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_isReverse');
  public get isReverse(): (boolean | undefined) {
    this.conditionalAddRef(this.metaReverse);
    return UIUtils.makeObserved((this.backingIsReverse as (boolean | undefined)));
  }
 
  public set isReverse(newValue: (boolean | undefined)) {
    if (((this.backingIsReverse) !== (newValue))) {
      this.backingIsReverse = newValue;
      this.metaReverse.fireChange();
      this.executeOnSubscribingWatches('isReverse');
    }
  }
 
  constructor(option?: RowLayoutAlgorithmOptions) {
    if (option) {
        this.backingSpace = option.space !== undefined ? option.space : undefined
        this.backingAlignItems = option.alignItems !== undefined ? option.alignItems : undefined
        this.backingJustifyContent = option.justifyContent !== undefined ? option.justifyContent : undefined
        this.backingIsReverse = option.isReverse !== undefined ? option.isReverse : undefined
    }
  }
}
 
export interface ColumnLayoutAlgorithmOptions {
    space?: LengthMetrics;
    alignItems?: HorizontalAlign;
    justifyContent?: FlexAlign;
    isReverse?: boolean;
}
export class ColumnLayoutAlgorithm implements LayoutAlgorithm, IObservedObject, ISubscribedWatches {
  @JSONStringifyIgnore() @JSONParseIgnore() private subscribedWatches: ISubscribedWatches =
    STATE_MGMT_FACTORY.makeSubscribedWatches();
  public addWatchSubscriber(watchId: WatchIdType): void {
    this.subscribedWatches.addWatchSubscriber(watchId);
  }
 
  public removeWatchSubscriber(watchId: WatchIdType): boolean {
    return this.subscribedWatches.removeWatchSubscriber(watchId);
  }
 
  public executeOnSubscribingWatches(propertyName: string): void {
    this.subscribedWatches.executeOnSubscribingWatches(propertyName);
  }
 
  public setV1RenderId(renderId: RenderIdType): void {}
 
  protected conditionalAddRef(meta: IMutableStateMeta): void {
    meta.addRef();
  }
 
  @JSONRename({newName:'space'}) public backingSpace?: (LengthMetrics | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaSpace: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_space');
  public get space(): (LengthMetrics | undefined) {
    this.conditionalAddRef(this.metaSpace);
    return UIUtils.makeObserved((this.backingSpace as (LengthMetrics | undefined)));
  }
 
  public set space(newValue: (LengthMetrics | undefined)) {
    if (((this.backingSpace) !== (newValue))) {
      this.backingSpace = newValue;
      this.metaSpace.fireChange();
      this.executeOnSubscribingWatches('space');
    }
  }
 
  @JSONRename({newName:'alignItems'}) public backingAlignItems?: (HorizontalAlign | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaAlignItems: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_alignItems');
  public get alignItems(): (HorizontalAlign | undefined) {
    this.conditionalAddRef(this.metaAlignItems);
    return UIUtils.makeObserved((this.backingAlignItems as (HorizontalAlign | undefined)));
  }
 
  public set alignItems(newValue: (HorizontalAlign | undefined)) {
    if (((this.backingAlignItems) !== (newValue))) {
      this.backingAlignItems = newValue;
      this.metaAlignItems.fireChange();
      this.executeOnSubscribingWatches('alignItems');
    }
  }
 
  @JSONRename({newName:'justifyContent'}) public backingJustifyContent?: (FlexAlign | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaJusiftyContent: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_justifyContent');
  public get justifyContent(): (FlexAlign | undefined) {
    this.conditionalAddRef(this.metaJusiftyContent);
    return UIUtils.makeObserved((this.backingJustifyContent as (FlexAlign | undefined)));
  }
 
  public set justifyContent(newValue: (FlexAlign | undefined)) {
    if (((this.backingJustifyContent) !== (newValue))) {
      this.backingJustifyContent = newValue;
      this.metaJusiftyContent.fireChange();
      this.executeOnSubscribingWatches('justifyContent');
    }
  }
 
  @JSONRename({newName:'isReverse'}) public backingIsReverse?: (boolean | undefined);
  @JSONStringifyIgnore() @JSONParseIgnore() private metaReverse: IMutableStateMeta =
    STATE_MGMT_FACTORY.makeMutableStateMeta(this, '__metaV2_isReverse');
  public get isReverse(): (boolean | undefined) {
    this.conditionalAddRef(this.metaReverse);
    return UIUtils.makeObserved((this.backingIsReverse as (boolean | undefined)));
  }
 
  public set isReverse(newValue: (boolean | undefined)) {
    if (((this.backingIsReverse) !== (newValue))) {
      this.backingIsReverse = newValue;
      this.metaReverse.fireChange();
      this.executeOnSubscribingWatches('isReverse');
    }
  }
 
  constructor(option?: ColumnLayoutAlgorithmOptions) {
    if (option) {
        this.backingSpace = option.space !== undefined ? option.space : undefined
        this.backingAlignItems = option.alignItems !== undefined ? option.alignItems : undefined
        this.backingJustifyContent = option.justifyContent !== undefined ? option.justifyContent : undefined
        this.backingIsReverse = option.isReverse !== undefined ? option.isReverse : undefined
    }
  }
}