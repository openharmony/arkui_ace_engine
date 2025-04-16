import { CommonAttribute } from "./component/common";
import { AttributeModifier } from "./component/common"; 
export class CommonModifier   implements AttributeModifier<CommonAttribute> {

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