import { Callback } from '@ohos.base';
declare namespace inspector {
    export interface ComponentObserver {
        on(type: 'layout' | 'draw', callback: Callback<void>): void;
 
        off(type: 'layout' | 'draw', callback?: Callback<void>): void;
        
        onLayout(type: 'layout', callback: Callback<void>): void;
        
        offLayout(type: 'layout', callback?: Callback<void>): void;
        
        onDraw(type: 'draw', callback: Callback<void>): void;
        
        offDraw(type: 'draw', callback?: Callback<void>): void;
    }
    export function createComponentObserver(id: string): ComponentObserver | undefined;
}
export default inspector;