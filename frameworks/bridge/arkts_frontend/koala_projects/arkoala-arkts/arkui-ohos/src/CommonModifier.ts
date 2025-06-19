import { CommonAttribute, AttributeModifier } from "./component/common";
import { ArkCommonAttributeSet } from "./handwritten/modifiers/ArkCommonModifier";
import {  ClickEvent, Length, ResourceColor, SizeOptions} from "./";

export class CommonModifier implements AttributeModifier<CommonAttribute> {

    private attributeSet: ArkCommonAttributeSet = new ArkCommonAttributeSet();

    get attribute(): ArkCommonAttributeSet {
        return this.attributeSet;
    }

    applyNormalAttribute(instance: CommonAttribute): void {
    }

    applyPressedAttribute(instance: CommonAttribute): void {

    }

    applyFocusedAttribute(instance: CommonAttribute): void {

    }

    applyDisabledAttribute(instance: CommonAttribute): void {

    }

    applySelectedAttribute(instance: CommonAttribute): void {

    }

}