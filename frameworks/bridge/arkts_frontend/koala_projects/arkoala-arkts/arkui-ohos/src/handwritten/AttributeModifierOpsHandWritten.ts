/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from '../component/common';
import { ArkButtonComponent, ButtonAttribute } from '../component/button';
import { ArkTextComponent, TextAttribute, ArkTextPeer, TextOptions } from '../component/text';
import { ArkBlankComponent, BlankAttribute, ArkBlankPeer } from '../component/blank';
import { ArkColumnComponent, ColumnAttribute, ArkColumnPeer } from '../component/column';
import { ArkColumnSplitComponent, ColumnSplitAttribute, ArkColumnSplitPeer } from '../component/columnSplit';
import { ArkDividerComponent, DividerAttribute, ArkDividerPeer } from '../component/divider';
import { ArkFlexComponent, FlexAttribute, ArkFlexPeer } from '../component/flex';
import { ArkFolderStackComponent, FolderStackAttribute, ArkFolderStackPeer } from '../component/folderStack';
import { ArkGridColComponent, GridColAttribute, ArkGridColPeer } from '../component/gridCol';
import { ArkGridRowComponent, GridRowAttribute, ArkGridRowPeer } from '../component/gridRow';
import { ArkRelativeContainerComponent, RelativeContainerAttribute, ArkRelativeContainerPeer } from '../component/relativeContainer';
import { ArkRowComponent, RowAttribute, ArkRowPeer } from '../component/row';
import { ArkRowSplitComponent, RowSplitAttribute, ArkRowSplitPeer } from '../component/rowSplit';
import { ArkStackComponent, StackAttribute, ArkStackPeer } from '../component/stack';
import { ArkSymbolGlyphComponent, SymbolGlyphAttribute, ArkSymbolGlyphPeer } from '../component/symbolglyph';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { ButtonModifier } from "../ButtonModifier";
import { TextModifier } from '../TextModifier';
import { BlankModifier } from '../BlankModifier';
import { ColumnModifier } from '../ColumnModifier';
import { ColumnSplitModifier } from '../ColumnSplitModifier';
import { DividerModifier } from '../DividerModifier';
import { FlexModifier } from '../FlexModifier';
import { FolderStackModifier } from '../FolderStackModifier';
import { GridColModifier } from '../GridColModifier';
import { GridRowModifier } from '../GridRowModifier';
import { RelativeContainerModifier } from '../RelativeContainerModifier';
import { RowModifier } from '../RowModifier';
import { RowSplitModifier } from '../RowSplitModifier';
import { StackModifier } from '../StackModifier';
import { SymbolGlyphModifier } from '../SymbolGlyphModifier';
import { Resource } from 'global.resource';
import { runtimeType, RuntimeType } from '@koalaui/interop';
import { ArkGridComponent, GridAttribute } from '../component/grid';
import { GridModifier } from '../GridModifier';
import { ArkGridItemComponent, GridItemAttribute } from '../component/gridItem';
import { GridItemModifier } from '../GridItemModifier';
import { ArkListComponent, ListAttribute } from '../component/list';
import { ListModifier } from '../ListModifier';
import { ArkListItemComponent, ListItemAttribute } from '../component/listItem';
import { ListItemModifier } from '../ListItemModifier';
import { ArkListItemGroupComponent, ListItemGroupAttribute } from '../component/listItemGroup';
import { ListItemGroupModifier } from '../ListItemGroupModifier';
import { ArkRefreshComponent, RefreshAttribute } from '../component/refresh';
import { RefreshModifier } from '../RefreshModifier';
import { ArkScrollComponent, ScrollAttribute } from '../component/scroll';
import { ScrollModifier } from '../ScrollModifier';
import { ArkWaterFlowComponent, WaterFlowAttribute } from '../component/waterFlow';
import { WaterFlowModifier } from '../WaterFlowModifier';


export function hookButtonAttributeModifier(component: ArkButtonComponent, modifier: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ButtonModifier => {
        let isButtonModifier: boolean = modifier instanceof ButtonModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ButtonModifier();
        if (isButtonModifier) {
            let buttonModifier = modifier as object as ButtonModifier;
            initModifier.mergeModifier(buttonModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkButtonComponent => {
        let componentNew: ArkButtonComponent = new ArkButtonComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ButtonAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookTextAttributeModifier(component: ArkTextComponent, modifier: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return ;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return ;
    }
    let attributeSet = (): TextModifier => {
        let isTextModifier: boolean = modifier instanceof TextModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new TextModifier();
        if (isTextModifier) {
            let textModifier = modifier as object as TextModifier;
            initModifier.mergeModifier(textModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length > 2) {
            throw new Error('more than 2 parameters')
        }
        let content_casted: string | Resource | undefined = undefined
        let value_casted: TextOptions | undefined = undefined
        if (params.length >= 1) {
            if (typeof (params[0]) == "string") {
                content_casted = params[0] as string
            } else if (typeof (params[0]) == "object") {
                content_casted = params[0] as string
            }
        }
        if (params.length == 2) {
            const param1_type = runtimeType(params[1])
            if (RuntimeType.OBJECT == param1_type) {
                value_casted = params[1] as TextOptions
            }
        }
        let textPeer: ArkTextPeer = component.getPeer() as Object as ArkTextPeer;
        textPeer.setTextOptionsAttribute(content_casted, value_casted)
    };
    let updaterReceiver = (): ArkTextComponent => {
        let initComponent: ArkTextComponent = new ArkTextComponent();
        initComponent.setPeer(component.getPeer());
        return initComponent;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<TextAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookBlankAttributeModifier(component: ArkBlankComponent,
    modifier: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): BlankModifier => {
        let isBlankModifier: boolean = modifier instanceof BlankModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new BlankModifier();
        if (isBlankModifier) {
            let BlankModifier = modifier as object as BlankModifier;
            initModifier.mergeModifier(BlankModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkBlankComponent => {
        let componentNew: ArkBlankComponent = new ArkBlankComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<BlankAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookColumnAttributeModifier(component: ArkColumnComponent,
    modifier: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ColumnModifier => {
        let isColumnModifier: boolean = modifier instanceof ColumnModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ColumnModifier();
        if (isColumnModifier) {
            let ColumnModifier = modifier as object as ColumnModifier;
            initModifier.mergeModifier(ColumnModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkColumnComponent => {
        let componentNew: ArkColumnComponent = new ArkColumnComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ColumnAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookColumnSplitAttributeModifier(component: ArkColumnSplitComponent,
    modifier: AttributeModifier<ColumnSplitAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ColumnSplitModifier => {
        let isColumnSplitModifier: boolean = modifier instanceof ColumnSplitModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ColumnSplitModifier();
        if (isColumnSplitModifier) {
            let ColumnSplitModifier = modifier as object as ColumnSplitModifier;
            initModifier.mergeModifier(ColumnSplitModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkColumnSplitComponent => {
        let componentNew: ArkColumnSplitComponent = new ArkColumnSplitComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ColumnSplitAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookDividerAttributeModifier(component: ArkDividerComponent,
    modifier: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): DividerModifier => {
        let isDividerModifier: boolean = modifier instanceof DividerModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new DividerModifier();
        if (isDividerModifier) {
            let DividerModifier = modifier as object as DividerModifier;
            initModifier.mergeModifier(DividerModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkDividerComponent => {
        let componentNew: ArkDividerComponent = new ArkDividerComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<DividerAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookFlexAttributeModifier(component: ArkFlexComponent,
    modifier: AttributeModifier<FlexAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): FlexModifier => {
        let isFlexModifier: boolean = modifier instanceof FlexModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new FlexModifier();
        if (isFlexModifier) {
            let FlexModifier = modifier as object as FlexModifier;
            initModifier.mergeModifier(FlexModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkFlexComponent => {
        let componentNew: ArkFlexComponent = new ArkFlexComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<FlexAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookFolderStackAttributeModifier(component: ArkFolderStackComponent,
    modifier: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): FolderStackModifier => {
        let isFolderStackModifier: boolean = modifier instanceof FolderStackModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new FolderStackModifier();
        if (isFolderStackModifier) {
            let FolderStackModifier = modifier as object as FolderStackModifier;
            initModifier.mergeModifier(FolderStackModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkFolderStackComponent => {
        let componentNew: ArkFolderStackComponent = new ArkFolderStackComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<FolderStackAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookGridColAttributeModifier(component: ArkGridColComponent,
    modifier: AttributeModifier<GridColAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): GridColModifier => {
        let isGridColModifier: boolean = modifier instanceof GridColModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new GridColModifier();
        if (isGridColModifier) {
            let GridColModifier = modifier as object as GridColModifier;
            initModifier.mergeModifier(GridColModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkGridColComponent => {
        let componentNew: ArkGridColComponent = new ArkGridColComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<GridColAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookGridRowAttributeModifier(component: ArkGridRowComponent,
    modifier: AttributeModifier<GridRowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): GridRowModifier => {
        let isGridRowModifier: boolean = modifier instanceof GridRowModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new GridRowModifier();
        if (isGridRowModifier) {
            let GridRowModifier = modifier as object as GridRowModifier;
            initModifier.mergeModifier(GridRowModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkGridRowComponent => {
        let componentNew: ArkGridRowComponent = new ArkGridRowComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<GridRowAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookRelativeContainerAttributeModifier(component: ArkRelativeContainerComponent,
    modifier: AttributeModifier<RelativeContainerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): RelativeContainerModifier => {
        let isRelativeContainerModifier: boolean = modifier instanceof RelativeContainerModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new RelativeContainerModifier();
        if (isRelativeContainerModifier) {
            let RelativeContainerModifier = modifier as object as RelativeContainerModifier;
            initModifier.mergeModifier(RelativeContainerModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkRelativeContainerComponent => {
        let componentNew: ArkRelativeContainerComponent = new ArkRelativeContainerComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<RelativeContainerAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookRowAttributeModifier(component: ArkRowComponent,
    modifier: AttributeModifier<RowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): RowModifier => {
        let isRowModifier: boolean = modifier instanceof RowModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new RowModifier();
        if (isRowModifier) {
            let RowModifier = modifier as object as RowModifier;
            initModifier.mergeModifier(RowModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkRowComponent => {
        let componentNew: ArkRowComponent = new ArkRowComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<RowAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookRowSplitAttributeModifier(component: ArkRowSplitComponent,
    modifier: AttributeModifier<RowSplitAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): RowSplitModifier => {
        let isRowSplitModifier: boolean = modifier instanceof RowSplitModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new RowSplitModifier();
        if (isRowSplitModifier) {
            let RowSplitModifier = modifier as object as RowSplitModifier;
            initModifier.mergeModifier(RowSplitModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkRowSplitComponent => {
        let componentNew: ArkRowSplitComponent = new ArkRowSplitComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<RowSplitAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookStackAttributeModifier(component: ArkStackComponent,
    modifier: AttributeModifier<StackAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): StackModifier => {
        let isStackModifier: boolean = modifier instanceof StackModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new StackModifier();
        if (isStackModifier) {
            let StackModifier = modifier as object as StackModifier;
            initModifier.mergeModifier(StackModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkStackComponent => {
        let componentNew: ArkStackComponent = new ArkStackComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<StackAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookSymbolGlyphAttributeModifier(component: ArkSymbolGlyphComponent,
    modifier: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): SymbolGlyphModifier => {
        let isSymbolGlyphModifier: boolean = modifier instanceof SymbolGlyphModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new SymbolGlyphModifier();
        if (isSymbolGlyphModifier) {
            let symbolGlyphModifier = modifier as object as SymbolGlyphModifier;
            initModifier.mergeModifier(symbolGlyphModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length > 1) {
            throw new Error('more than 1 parameters')
        }
        let value_casted: Resource | undefined = undefined
        if (params.length >= 0) {
            value_casted = params[0] as Resource
        }
        let symbolGlyphPeer: ArkSymbolGlyphPeer = component.getPeer() as Object as ArkSymbolGlyphPeer;
        symbolGlyphPeer.setSymbolGlyphOptionsAttribute(value_casted)
    };
    let updaterReceiver = (): ArkSymbolGlyphComponent => {
        let componentNew: ArkSymbolGlyphComponent = new ArkSymbolGlyphComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<SymbolGlyphAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookGridAttributeModifier(component: ArkGridComponent,
    modifier: AttributeModifier<GridAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): GridModifier => {
        let isGridModifier: boolean = modifier instanceof GridModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new GridModifier();
        if (isGridModifier) {
            let gridModifier = modifier as object as GridModifier;
            initModifier.mergeModifier(gridModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkGridComponent => {
        let componentNew: ArkGridComponent = new ArkGridComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<GridAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookGridItemAttributeModifier(component: ArkGridItemComponent,
    modifier: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): GridItemModifier => {
        let isGridItemModifier: boolean = modifier instanceof GridItemModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new GridItemModifier();
        if (isGridItemModifier) {
            let gridItemModifier = modifier as object as GridItemModifier;
            initModifier.mergeModifier(gridItemModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkGridItemComponent => {
        let componentNew: ArkGridItemComponent = new ArkGridItemComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<GridItemAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}

export function hookListAttributeModifier(component: ArkListComponent,
    modifier: AttributeModifier<ListAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ListModifier => {
        let isListModifier: boolean = modifier instanceof ListModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ListModifier();
        if (isListModifier) {
            let listModifier = modifier as object as ListModifier;
            initModifier.mergeModifier(listModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkListComponent => {
        let componentNew: ArkListComponent = new ArkListComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ListAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}

export function hookListItemAttributeModifier(component: ArkListItemComponent,
    modifier: AttributeModifier<ListItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ListItemModifier => {
        let isListItemModifier: boolean = modifier instanceof ListItemModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ListItemModifier();
        if (isListItemModifier) {
            let listItemModifier = modifier as object as ListItemModifier;
            initModifier.mergeModifier(listItemModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkListItemComponent => {
        let componentNew: ArkListItemComponent = new ArkListItemComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ListItemAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}

export function hookListItemGroupAttributeModifier(component: ArkListItemGroupComponent,
    modifier: AttributeModifier<ListItemGroupAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ListItemGroupModifier => {
        let isListItemGroupModifier: boolean = modifier instanceof ListItemGroupModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ListItemGroupModifier();
        if (isListItemGroupModifier) {
            let listItemGroupModifier = modifier as object as ListItemGroupModifier;
            initModifier.mergeModifier(listItemGroupModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkListItemGroupComponent => {
        let componentNew: ArkListItemGroupComponent = new ArkListItemGroupComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ListItemGroupAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}

export function hookRefreshAttributeModifier(component: ArkRefreshComponent,
    modifier: AttributeModifier<RefreshAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): RefreshModifier => {
        let isRefreshModifier: boolean = modifier instanceof RefreshModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new RefreshModifier();
        if (isRefreshModifier) {
            let refreshModifier = modifier as object as RefreshModifier;
            initModifier.mergeModifier(refreshModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkRefreshComponent => {
        let componentNew: ArkRefreshComponent = new ArkRefreshComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<RefreshAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}
export function hookScrollAttributeModifier(component: ArkScrollComponent,
    modifier: AttributeModifier<ScrollAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ScrollModifier => {
        let isScrollModifier: boolean = modifier instanceof ScrollModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ScrollModifier();
        if (isScrollModifier) {
            let scrollModifier = modifier as object as ScrollModifier;
            initModifier.mergeModifier(scrollModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkScrollComponent => {
        let componentNew: ArkScrollComponent = new ArkScrollComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ScrollAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}

export function hookWaterFlowAttributeModifier(component: ArkWaterFlowComponent,
    modifier: AttributeModifier<WaterFlowAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): WaterFlowModifier => {
        let isWaterFlowModifier: boolean = modifier instanceof WaterFlowModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new WaterFlowModifier();
        if (isWaterFlowModifier) {
            let waterFlowModifier = modifier as object as WaterFlowModifier;
            initModifier.mergeModifier(waterFlowModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkWaterFlowComponent => {
        let componentNew: ArkWaterFlowComponent = new ArkWaterFlowComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<WaterFlowAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());

}