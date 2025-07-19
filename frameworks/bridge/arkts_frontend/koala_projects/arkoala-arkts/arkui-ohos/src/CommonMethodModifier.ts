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
import { ArkCommonMethodPeer, ClickEvent, CommonMethod } from './component/common'
import { PeerNode } from './PeerNode'
import { ResourceColor, SizeOptions } from './component/units'

export enum AttributeUpdateFlag {
    INITIAL = 0,
    UPDATE = 1,
    SKIP = 2,
    RESET = 3,
}
export class CommonMethodModifier implements CommonMethod {
   _width_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
   _width0_value?: Length | LayoutPolicy | undefined
  
   _backgroundColor_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
   _backgroundColor0_value?: ResourceColor | undefined
  
   _size_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
   _size0_value?: SizeOptions | undefined
  
   _onClick_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
   _onClick0_value?: ((event: ClickEvent) => void) | undefined
  
   _zIndex_flag: AttributeUpdateFlag = AttributeUpdateFlag.INITIAL
   _zIndex0_value?: number | undefined
  
   public width(value: Length | LayoutPolicy | undefined): this {
     if (this._width_flag === AttributeUpdateFlag.INITIAL || this._width0_value !== value || !Type.of(value).isPrimitive()) {
       this._width0_value = value
       this._width_flag = AttributeUpdateFlag.UPDATE
     } else {
       this._width_flag = AttributeUpdateFlag.SKIP
     }
     return this
   }
   public backgroundColor(value: ResourceColor | undefined): this {
  
     if (this._backgroundColor_flag === AttributeUpdateFlag.INITIAL || this._backgroundColor0_value !== value || !Type.of(value).isPrimitive()) {
       this._backgroundColor0_value = value
       this._backgroundColor_flag = AttributeUpdateFlag.UPDATE
     } else {
       this._backgroundColor_flag = AttributeUpdateFlag.SKIP
     }
     return this
   }
   public onClick(value: ((event: ClickEvent) => void) | undefined): this {
     if (this._onClick_flag === AttributeUpdateFlag.INITIAL || this._onClick0_value !== value || !Type.of(value).isPrimitive()) {
       this._onClick0_value = value
       this._onClick_flag = AttributeUpdateFlag.UPDATE
     } else {
       this._onClick_flag = AttributeUpdateFlag.SKIP
     }
     return this
   }
   public size(value: SizeOptions | undefined): this {
     if (this._size_flag === AttributeUpdateFlag.INITIAL || this._size0_value !== value || !Type.of(value).isPrimitive()) {
       this._size0_value = value
       this._size_flag = AttributeUpdateFlag.UPDATE
     } else {
       this._size_flag = AttributeUpdateFlag.SKIP
     }
     return this
   }
   public zIndex(value: number | undefined): this {
     if (this._zIndex_flag === AttributeUpdateFlag.INITIAL || this._zIndex0_value !== value || !Type.of(value).isPrimitive()) {
       this._zIndex0_value = value
       this._zIndex_flag = AttributeUpdateFlag.UPDATE
     } else {
       this._zIndex_flag = AttributeUpdateFlag.SKIP
     }
     return this
   }
   applyModifierPatch(node: PeerNode): void {
     const peerNode: ArkCommonMethodPeer = node as ArkCommonMethodPeer
     if (this._width_flag != AttributeUpdateFlag.INITIAL) {
       switch (this._width_flag) {
         case AttributeUpdateFlag.UPDATE: {
           peerNode.width1Attribute((this._width0_value as Length | LayoutPolicy | undefined))
           this._width_flag = AttributeUpdateFlag.RESET
           break
         }
         case AttributeUpdateFlag.SKIP: {
           this._width_flag = AttributeUpdateFlag.RESET
           break
         }
         default: {
           this._width_flag = AttributeUpdateFlag.INITIAL
           peerNode.width1Attribute(undefined)
         }
       }
     }
     if (this._backgroundColor_flag != AttributeUpdateFlag.INITIAL) {
       switch (this._backgroundColor_flag) {
         case AttributeUpdateFlag.UPDATE: {
           peerNode.backgroundColor0Attribute((this._backgroundColor0_value as ResourceColor | undefined))
           this._backgroundColor_flag = AttributeUpdateFlag.RESET
           break
         }
         case AttributeUpdateFlag.SKIP: {
           this._backgroundColor_flag = AttributeUpdateFlag.RESET
           break
         }
         default: {
           this._backgroundColor_flag = AttributeUpdateFlag.INITIAL
           peerNode.backgroundColor0Attribute(undefined)
         }
       }
     }
     if (this._onClick_flag != AttributeUpdateFlag.INITIAL) {
       switch (this._onClick_flag) {
         case AttributeUpdateFlag.UPDATE: {
           peerNode.onClick0Attribute((this._onClick0_value as ((event: ClickEvent) => void) | undefined))
           this._onClick_flag = AttributeUpdateFlag.RESET
           break
         }
         case AttributeUpdateFlag.SKIP: {
           this._onClick_flag = AttributeUpdateFlag.RESET
           break
         }
         default: {
           this._onClick_flag = AttributeUpdateFlag.INITIAL
           peerNode.onClick0Attribute(undefined)
         }
       }
     }
  
     if (this._size_flag != AttributeUpdateFlag.INITIAL) {
       switch (this._size_flag) {
         case AttributeUpdateFlag.UPDATE: {
           peerNode.sizeAttribute(this._size0_value as (SizeOptions | undefined))
           this._size_flag = AttributeUpdateFlag.RESET
           break
         }
         case AttributeUpdateFlag.SKIP: {
           this._size_flag = AttributeUpdateFlag.RESET
           break
         }
         default: {
           this._size_flag = AttributeUpdateFlag.INITIAL
           peerNode.sizeAttribute(undefined)
         }
       }
     }
     if (this._zIndex_flag != AttributeUpdateFlag.INITIAL) {
       switch (this._zIndex_flag) {
         case AttributeUpdateFlag.UPDATE: {
           peerNode.zIndexAttribute(this._zIndex0_value as (number | undefined))
           this._zIndex_flag = AttributeUpdateFlag.RESET
           break
         }
         case AttributeUpdateFlag.SKIP: {
           this._zIndex_flag = AttributeUpdateFlag.RESET
           break
         }
         default: {
           this._zIndex_flag = AttributeUpdateFlag.INITIAL
           peerNode.zIndexAttribute(undefined)
         }
       }
     }
   }
   mergeModifier(value: CommonMethodModifier): void {
     if (value._width_flag != AttributeUpdateFlag.INITIAL) {
       switch (value._width_flag) {
         case AttributeUpdateFlag.UPDATE:
         case AttributeUpdateFlag.SKIP: {
           this.width(value._width0_value)
           break
         }
         default: {
           this.width(undefined)
         }
       }
     }
  
     if (value._backgroundColor_flag != AttributeUpdateFlag.INITIAL) {
       switch (value._backgroundColor_flag) {
         case AttributeUpdateFlag.UPDATE:
         case AttributeUpdateFlag.SKIP: {
           this.backgroundColor(value._backgroundColor0_value)
           break
         }
         default: {
           this.backgroundColor(undefined)
         }
       }
     }
  
     if (value._size_flag != AttributeUpdateFlag.INITIAL) {
       switch (value._size_flag) {
         case AttributeUpdateFlag.UPDATE:
         case AttributeUpdateFlag.SKIP: {
           this.size(value._size0_value)
           break
         }
         default: {
           this.size(undefined)
         }
       }
     }
  
     if (value._onClick_flag != AttributeUpdateFlag.INITIAL) {
       switch (value._onClick_flag) {
         case AttributeUpdateFlag.UPDATE:
         case AttributeUpdateFlag.SKIP: {
           this.onClick(value._onClick0_value)
           break
         }
         default: {
           this.onClick(undefined)
         }
       }
     }
     if (value._zIndex_flag != AttributeUpdateFlag.INITIAL) {
       switch (value._zIndex_flag) {
         case AttributeUpdateFlag.UPDATE:
         case AttributeUpdateFlag.SKIP: {
           this.zIndex(value._zIndex0_value)
           break
         }
         default: {
           this.zIndex(undefined)
         }
       }
     }
   }
}