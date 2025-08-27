import { ArkCommonAttributeSet } from "./handwritten/modifiers/ArkCommonModifier";
import {  AttributeModifier, ClickEvent, CommonAttribute, Length, ResourceColor, SizeOptions} from "./";

export class CommonModifier implements AttributeModifier<CommonAttribute> {
    
    attributeSet: ArkCommonAttributeSet = new ArkCommonAttributeSet();

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

    size(value: SizeOptions): this {
        this.attributeSet.size(value);
        return this;
    }
    onClick(event: (event: ClickEvent) => void): this {
        this.attributeSet.onClick(event);
        return this;
    }
    width(value: Length | undefined): this {
        this.attributeSet.width(value);
        return this;
    }
    height(value: Length | undefined): this {
        this.attributeSet.height(value);
        return this;
    }
    backgroundColor(value: ResourceColor | undefined): this {
        this.attributeSet.backgroundColor(value);
        return this;
    }

}