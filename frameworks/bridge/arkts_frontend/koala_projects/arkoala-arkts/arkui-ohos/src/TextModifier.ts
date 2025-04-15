import { TextAttribute } from "./component/text";
import { AttributeModifier } from "./component/common"; 

export class TextModifier  implements AttributeModifier<TextAttribute> {
     /** @memo */
    applyNormalAttribute(instance: TextAttribute): void {}
     /** @memo */
    applyPressedAttribute(instance: TextAttribute): void {}
     /** @memo */
    applyFocusedAttribute(instance: TextAttribute): void {}
     /** @memo */
    applyDisabledAttribute(instance: TextAttribute): void {}
     /** @memo */
    applySelectedAttribute(instance: TextAttribute): void {}
}