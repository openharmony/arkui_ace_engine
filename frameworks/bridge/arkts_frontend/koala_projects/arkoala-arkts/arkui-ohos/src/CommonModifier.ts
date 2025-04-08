import { CommonAttribute } from "./component/common";
import { AttributeModifier } from "./component/common"; 

export class CommonModifier  implements AttributeModifier<CommonAttribute> {
     /** @memo */
    applyNormalAttribute(instance: CommonAttribute): void {
    }
     /** @memo */
    applyPressedAttribute(instance: CommonAttribute): void {
       
    }
     /** @memo */
    applyFocusedAttribute(instance: CommonAttribute): void {
        
    }
     /** @memo */
    applyDisabledAttribute(instance: CommonAttribute): void {
      
    }
     /** @memo */
    applySelectedAttribute(instance: CommonAttribute): void {
        
    }
}