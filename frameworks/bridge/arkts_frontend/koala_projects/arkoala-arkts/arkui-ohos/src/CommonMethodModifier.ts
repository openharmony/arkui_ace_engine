/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { CommonAttribute, LayoutPolicy } from 'arkui/component/common'
import { Length } from "arkui/component/units"
import { ArkCommonMethodPeer, ClickEvent, CommonMethod, CustomProperty, ArkCommonMethodComponent } from './component/common';
import { PeerNode } from './PeerNode'
import { ResourceColor, SizeOptions } from './component/units'
import {  hookCustomPropertyImpl } from "./handwritten/CommonHandWritten"

export enum AttributeUpdaterFlag {
    INITIAL = 0,
    UPDATE = 1,
    SKIP = 2,
    RESET = 3,
}
export class CommonMethodModifier implements CommonMethod {
   _width_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _width0_value?: Length | LayoutPolicy | undefined
  
   _backgroundColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _backgroundColor0_value?: ResourceColor | undefined
  
   _size_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _size0_value?: SizeOptions | undefined
  
   _onClick_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _onClick0_value?: ((event: ClickEvent) => void) | undefined
  
   _zIndex_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _zIndex0_value?: number | undefined
  
   _customProperty_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
   _customPropertyMap?: Map<string, CustomProperty>
  
   public width(value: Length | LayoutPolicy | undefined): this {
     if (this._width_flag === AttributeUpdaterFlag.INITIAL || this._width0_value !== value || !Type.of(value).isPrimitive()) {
       this._width0_value = value
       this._width_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._width_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public backgroundColor(value: ResourceColor | undefined): this {
  
     if (this._backgroundColor_flag === AttributeUpdaterFlag.INITIAL || this._backgroundColor0_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundColor0_value = value
       this._backgroundColor_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._backgroundColor_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public onClick(value: ((event: ClickEvent) => void) | undefined): this {
     if (this._onClick_flag === AttributeUpdaterFlag.INITIAL || this._onClick0_value !== value || !Type.of(value).isPrimitive()) {
       this._onClick0_value = value
       this._onClick_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._onClick_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public size(value: SizeOptions | undefined): this {
     if (this._size_flag === AttributeUpdaterFlag.INITIAL || this._size0_value !== value || !Type.of(value).isPrimitive()) {
       this._size0_value = value
       this._size_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._size_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
   public zIndex(value: number | undefined): this {
     if (this._zIndex_flag === AttributeUpdaterFlag.INITIAL || this._zIndex0_value !== value || !Type.of(value).isPrimitive()) {
       this._zIndex0_value = value
       this._zIndex_flag = AttributeUpdaterFlag.UPDATE
     } else {
       this._zIndex_flag = AttributeUpdaterFlag.SKIP
     }
     return this
   }
  public customProperty(name: string, value: CustomProperty): this {
    if (this._customPropertyMap === undefined) {
      this._customPropertyMap = new Map<string, CustomProperty>();
    }
    this._customPropertyMap!.set(name, value);
    this._customProperty_flag = AttributeUpdaterFlag.UPDATE;
    return this;
  }
   applyModifierPatch(node: PeerNode): void {
     const peerNode: ArkCommonMethodPeer = node as ArkCommonMethodPeer
     if (this._width_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._width_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.width1Attribute((this._width0_value as Length | LayoutPolicy | undefined))
           this._width_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._width_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._width_flag = AttributeUpdaterFlag.INITIAL
           peerNode.width1Attribute(undefined)
         }
       }
     }
     if (this._backgroundColor_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._backgroundColor_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.backgroundColor0Attribute((this._backgroundColor0_value as ResourceColor | undefined))
           this._backgroundColor_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._backgroundColor_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._backgroundColor_flag = AttributeUpdaterFlag.INITIAL
           peerNode.backgroundColor0Attribute(undefined)
         }
       }
     }
     if (this._onClick_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onClick_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onClick0Attribute((this._onClick0_value as ((event: ClickEvent) => void) | undefined))
           this._onClick_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onClick_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onClick_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onClick0Attribute(undefined)
         }
       }
     }
  
     if (this._size_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._size_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.sizeAttribute(this._size0_value as (SizeOptions | undefined))
           this._size_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._size_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._size_flag = AttributeUpdaterFlag.INITIAL
           peerNode.sizeAttribute(undefined)
         }
       }
     }
     if (this._zIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._zIndex_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.zIndexAttribute(this._zIndex0_value as (number | undefined))
           this._zIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._zIndex_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._zIndex_flag = AttributeUpdaterFlag.INITIAL
           peerNode.zIndexAttribute(undefined)
         }
       }
     }
     if (this._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (this._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           const arkCommonMethodComponent: ArkCommonMethodComponent = new ArkCommonMethodComponent();
           arkCommonMethodComponent.setPeer(peerNode);
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             hookCustomPropertyImpl(arkCommonMethodComponent, key as (string), value as (CustomProperty));
           });
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         case AttributeUpdaterFlag.SKIP: {
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         default: {
           this._customProperty_flag = AttributeUpdaterFlag.INITIAL;
         }
       }
     }
   }
   mergeModifier(value: CommonMethodModifier): void {
     if (value._width_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._width_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.width(value._width0_value)
           break
         }
         default: {
           this.width(undefined)
         }
       }
     }
  
     if (value._backgroundColor_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundColor_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundColor(value._backgroundColor0_value)
           break
         }
         default: {
           this.backgroundColor(undefined)
         }
       }
     }
  
     if (value._size_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._size_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.size(value._size0_value)
           break
         }
         default: {
           this.size(undefined)
         }
       }
     }
  
     if (value._onClick_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onClick_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onClick(value._onClick0_value)
           break
         }
         default: {
           this.onClick(undefined)
         }
       }
     }
     if (value._zIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._zIndex_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.zIndex(value._zIndex0_value)
           break
         }
         default: {
           this.zIndex(undefined)
         }
       }
     }
     if (value._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             this.customProperty(key as (string), value);
           });
           break;
         }
         default: {
         }
       }
     }
   }
}